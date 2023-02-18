/*
 * econfig file
 * contains the implementations of the functions
 */


#include <stdio.h>
#include <assert.h>

#include "econfig.h"
#include "combinations.h"


void permutationCreation(unsigned short *s_possibilities, unsigned short *p_possibilities, unsigned short *d_possibilities, unsigned short *f_possibilities,
                         const unsigned short *number_of_electrons) {
    assert(
            s_possibilities != NULL && p_possibilities != NULL && d_possibilities != NULL && f_possibilities != NULL &&
            number_of_electrons != NULL &&
            number_of_electrons[0] <= S && number_of_electrons[1] <= P && number_of_electrons[2] <= D && number_of_electrons[3] <= F
    );
    generate_permutation(number_of_electrons[0], S, s_possibilities);
    generate_permutation(number_of_electrons[1], P, p_possibilities);
    generate_permutation(number_of_electrons[2], D, d_possibilities);
    generate_permutation(number_of_electrons[3], F, f_possibilities);
}

void printArrow(unsigned short spins) {
    if ((spins & 2) && (spins & 1)) {
        printf(ArrowSpinBoth);
    } else if (spins & 2) {
        printf(ArrowSpinUp);
    } else if (spins & 1) {
        printf(ArrowSpinDown);
    } else {
        printf(BracketSpace);
    }
}

void printEConfigElement(ElectronConfig *electronConfig) {
    assert(electronConfig != NULL);
    printf(ColorGreen "s: ");
    printArrow((electronConfig->orbitals & (3 << (P + D + F))) >> (P + D + F));
    printf(ColorBlue " p: ");
    for (int p = P / 2; p > 0; --p) {
        printArrow((electronConfig->orbitals & (3 << ((p - 1) * 2 + D + F))) >> ((p - 1) * 2 + D + F));
    }
    printf(ColorYellow " d: ");
    for (int d = D / 2; d > 0; --d) {
        printArrow((electronConfig->orbitals & (3 << ((d - 1) * 2 + F))) >> ((d - 1) * 2 + F));
    }
    printf(ColorMagenta " f: ");
    for (int f = F / 2; f > 0; --f) {
        printArrow((electronConfig->orbitals & (3 << ((f - 1) * 2))) >> ((f - 1) * 2));
    }
    printf(ColorWhite " Ml: %2d Ms: %4.1f group: %hu" TextReset "\n", electronConfig->ml, electronConfig->ms, electronConfig->group);
}

void printEConfig(ElectronConfig *electronConfig, unsigned int array_len) {
    assert(electronConfig != NULL && array_len > 0);
    printf("Possibilities:\n");
    for (unsigned int i = 0; i < array_len; i++) {
        printf(ColorCyan "line: %4u ", i + 1);
        printEConfigElement(&electronConfig[i]);
    }
}

void eConfigManipulation(ElectronConfig *electronConfig,
                         unsigned int possibilities_f, unsigned int possibilities_d, unsigned int possibilities_p, unsigned int possibilities_s,
                         const unsigned short *s_possibilities, const unsigned short *p_possibilities,
                         const unsigned short *d_possibilities, const unsigned short *f_possibilities) {
    assert(electronConfig != NULL && s_possibilities != NULL && p_possibilities != NULL && d_possibilities != NULL && f_possibilities != NULL);
    unsigned int d_combs = possibilities_f * possibilities_d;
    unsigned int p_combs = d_combs * possibilities_p;
    unsigned int s_combs = p_combs * possibilities_s;

    for (unsigned int i = 0; i < s_combs; i++) {
        electronConfig[i].orbitals = ((((
                (s_possibilities[i / p_combs] << P)
                | p_possibilities[(i % p_combs) / d_combs]) << D)
                        | d_possibilities[(i % d_combs) / possibilities_f]) << F)
                                | f_possibilities[i % possibilities_f];
        electronConfig[i].ms = (float)((electronConfig[i].orbitals & (1 << 31)) >> 31) - (float)((electronConfig[i].orbitals & (1 << 30)) >> 30);
        electronConfig[i].ml = 0;
        for (int pdf = (P + D + F) / 2 - 1; pdf >= (D + F) / 2; --pdf) {
            electronConfig[i].ms += (float)((electronConfig[i].orbitals & (1 << (pdf * 2 + 1))) >> (pdf * 2 + 1)) - (float)((electronConfig[i].orbitals & (1 << (pdf * 2))) >> (pdf * 2));
            electronConfig[i].ml += (((electronConfig[i].orbitals & (1 << (pdf * 2 + 1))) >> (pdf * 2 + 1)) + ((electronConfig[i].orbitals & (1 << (pdf * 2))) >> (pdf * 2))) * (-(pdf - (D + F) / 2) + 1);
        }
        for (int df = (D + F) / 2 - 1; df >= F / 2; --df) {
            electronConfig[i].ms += (float)((electronConfig[i].orbitals & (1 << (df * 2 + 1))) >> (df * 2 + 1)) - (float)((electronConfig[i].orbitals & (1 << (df * 2))) >> (df * 2));
            electronConfig[i].ml += (((electronConfig[i].orbitals & (1 << (df * 2 + 1))) >> (df * 2 + 1)) + ((electronConfig[i].orbitals & (1 << (df * 2))) >> (df * 2))) * (-(df - F / 2) + 2);
        }
        for (int f = F / 2 - 1; f >= 0 / 2; --f) {
            electronConfig[i].ms += (float)((electronConfig[i].orbitals & (1 << (f * 2 + 1))) >> (f * 2 + 1)) - (float)((electronConfig[i].orbitals & (1 << (f * 2))) >> (f * 2));
            electronConfig[i].ml += (((electronConfig[i].orbitals & (1 << (f * 2 + 1))) >> (f * 2 + 1)) + ((electronConfig[i].orbitals & (1 << (f * 2))) >> (f * 2))) * (-f + 3);
        }
        electronConfig[i].group = 0;
        electronConfig[i].ms /= 2;
    }
}
