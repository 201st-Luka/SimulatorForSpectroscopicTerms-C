/*
 * econfig file
 * contains the implementations of the functions
 */


#include <stdio.h>

#include "econfig.h"
#include "combinations.h"


void permutation_creation(short s_possibilities[][S], short p_possibilities[][P], short d_possibilities[][D], short f_possibilities[][F],
                          const unsigned short *number_of_electrons) {
    generate_permutation(number_of_electrons[0], S, s_possibilities);
    generate_permutation(number_of_electrons[1], P, p_possibilities);
    generate_permutation(number_of_electrons[2], D, d_possibilities);
    generate_permutation(number_of_electrons[3], F, f_possibilities);
}

void printArrow(const short *spinUp, const short *spinDown) {
    if (*spinUp && *spinDown) {
        printf(ArrowSpinBoth);
    } else if (*spinUp) {
        printf(ArrowSpinUp);
    } else if (*spinDown) {
        printf(ArrowSpinDown);
    } else {
        printf(".");
    }
}

void print_econfig_element(ElectronConfig *electronConfig) {
    printf(ColorGreen "s: ");
    printArrow(electronConfig->sOrbital.spinUp, electronConfig->sOrbital.spinDown);
    printf(ColorBlue " p: ");
    for (int i_p = 0; i_p < P / 2; ++i_p) {
        printArrow(electronConfig->pOrbital[i_p].spinUp, electronConfig->pOrbital[i_p].spinDown);
    }
    printf(ColorYellow " d: ");
    for (int i_d = 0; i_d < D / 2; ++i_d) {
        printArrow(electronConfig->dOrbital[i_d].spinUp, electronConfig->dOrbital[i_d].spinDown);
    }
    printf(ColorMagenta " f: ");
    for (int i_f = 0; i_f < F / 2; ++i_f) {
        printArrow(electronConfig->fOrbital[i_f].spinUp, electronConfig->fOrbital[i_f].spinDown);
    }
    printf(ColorWhite " Ms: %4.1f Ml: %2d" TextReset "\n", electronConfig->ms, electronConfig->ml);
}

void print_econfig(ElectronConfig *electronConfig, unsigned int array_len) {
    printf("Possibilities:\n");
    for (unsigned int i = 0; i < array_len; i++) {
        printf(ColorCyan "line: %8u ", i + 1);
        print_econfig_element(&electronConfig[i]);
    }
}

void econfig_manipulation(ElectronConfig *electronConfig,
                          unsigned int possibilities_f, unsigned int possibilities_d, unsigned int possibilities_p, unsigned int possibilities_s,
                          short s_possibilities[][S], short p_possibilities[][P], short d_possibilities[][D], short f_possibilities[][F]) {
    unsigned int d_combs = possibilities_f * possibilities_d;
    unsigned int p_combs = d_combs * possibilities_p;
    unsigned int s_combs = p_combs * possibilities_s;

    for (unsigned int i = 0; i < s_combs; i++) {
        electronConfig[i].sOrbital.spinUp = &(s_possibilities[i / p_combs][0]);
        electronConfig[i].sOrbital.spinDown = &(s_possibilities[i / p_combs][1]);
        electronConfig[i].ms = (float)*electronConfig[i].sOrbital.spinUp - (float)*electronConfig[i].sOrbital.spinDown;
        electronConfig[i].ml = 0;
        for (unsigned short i_p = 0; i_p < P / 2; i_p++) {
            electronConfig[i].pOrbital[i_p].spinUp = &(p_possibilities[(i % p_combs) / d_combs][2 * i_p]);
            electronConfig[i].pOrbital[i_p].spinDown = &(p_possibilities[(i % p_combs) / d_combs][2 * i_p + 1]);
            electronConfig[i].ms += (float)*electronConfig[i].pOrbital[i_p].spinUp - (float)*electronConfig[i].pOrbital[i_p].spinDown;
            electronConfig[i].ml += (*electronConfig[i].pOrbital[i_p].spinUp + *electronConfig[i].pOrbital[i_p].spinDown) * (i_p - 1);
        }
        for (unsigned short i_d = 0; i_d < D / 2; i_d++) {
            electronConfig[i].dOrbital[i_d].spinUp = &(d_possibilities[(i % d_combs) / possibilities_f][2 * i_d]);
            electronConfig[i].dOrbital[i_d].spinDown = &(d_possibilities[(i % d_combs) / possibilities_f][2 * i_d + 1]);
            electronConfig[i].ms += (float)*electronConfig[i].dOrbital[i_d].spinUp - (float)*electronConfig[i].dOrbital[i_d].spinDown;
            electronConfig[i].ml += (*electronConfig[i].dOrbital[i_d].spinUp + *electronConfig[i].dOrbital[i_d].spinDown) * (i_d - 2);
        }
        for (unsigned short i_f = 0; i_f < F / 2; i_f++) {
            electronConfig[i].fOrbital[i_f].spinUp = &(f_possibilities[i % possibilities_f][2 * i_f]);
            electronConfig[i].fOrbital[i_f].spinDown = &(f_possibilities[i % possibilities_f][2 * i_f + 1]);
            electronConfig[i].ms += (float)*electronConfig[i].fOrbital[i_f].spinUp - (float)*electronConfig[i].fOrbital[i_f].spinDown;
            electronConfig[i].ml += (*electronConfig[i].fOrbital[i_f].spinUp + *electronConfig[i].fOrbital[i_f].spinDown) * (i_f - 3);
        }
        electronConfig[i].ms /= 2;
    }
}