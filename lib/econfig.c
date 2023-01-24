/*
 * econfig file
 * contains the implementations of the functions
 */


#include <stdio.h>
#include <assert.h>
#include <time.h>

#include "econfig.h"
#include "combinations.h"


void permutation_creation(unsigned short *s_possibilities, unsigned short *p_possibilities, unsigned short *d_possibilities, unsigned short *f_possibilities,
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

void print_econfig_element(ElectronConfig *electronConfig) {
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
    printf(ColorWhite " Ml: %2d Ms: %4.1f" TextReset "\n", electronConfig->ml, electronConfig->ms);
}

void print_econfig(ElectronConfig *electronConfig, unsigned int array_len) {
    assert(electronConfig != NULL && array_len > 0);
    printf("Possibilities:\n");
    for (unsigned int i = 0; i < array_len; i++) {
        printf(ColorCyan "line: %4u ", i + 1);
        print_econfig_element(&electronConfig[i]);
    }
}

void econfig_manipulation(ElectronConfig *electronConfig,
                          unsigned int possibilities_f, unsigned int possibilities_d, unsigned int possibilities_p, unsigned int possibilities_s,
                          unsigned short *s_possibilities, unsigned short *p_possibilities, unsigned short *d_possibilities, unsigned short *f_possibilities) {
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

void saveEConfigElementInFile(ElectronConfig *electron_config_array, FILE *file) {
    for (short i = 31; i >= 0; --i) {
        fprintf(file, ", %u", (electron_config_array->orbitals & (1 << i)) >> i);
    }
    fprintf(file, ", %d, %.1f\n", electron_config_array->ml, electron_config_array->ms);
}

void saveEConfigInFile(ElectronConfig *electron_config_array, unsigned int array_len) {
    time_t time_raw;
    struct tm *time_formatted;
    time( &time_raw );
    time_formatted = localtime(&time_raw );
    char filename[28];
    filename[0] = 't';
    filename[1] = 'a';
    filename[2] = 's';
    filename[3] = 'k';
    filename[4] = '_';
    filename[5] = (char)((time_formatted->tm_year + 1900) / 1000 + 48);
    filename[6] = (char)(((time_formatted->tm_year + 1900) % 1000) / 100 + 48);
    filename[7] = (char)(((time_formatted->tm_year + 1900) % 100) / 10 + 48);
    filename[8] = (char)((time_formatted->tm_year + 1900) % 10 + 48);
    filename[9] = '-';
    filename[10] = (char)((time_formatted->tm_mon + 1) / 10 + 48);
    filename[11] = (char)((time_formatted->tm_mon + 1) % 10 + 48);
    filename[12] = '-';
    filename[13] = (char)(time_formatted->tm_mday / 10 + 48);
    filename[14] = (char)(time_formatted->tm_mday % 10 + 48);
    filename[15] = '_';
    filename[16] = (char)(time_formatted->tm_hour / 10 + 48);
    filename[17] = (char)(time_formatted->tm_hour % 10 + 48);
    filename[18] = '-';
    filename[19] = (char)(time_formatted->tm_min / 10 + 48);
    filename[20] = (char)(time_formatted->tm_min % 10 + 48);
    filename[21] = '-';
    filename[22] = (char)(time_formatted->tm_sec / 10 + 48);
    filename[23] = (char)(time_formatted->tm_sec % 10 + 48);
    filename[24] = '.';
    filename[25] = 'c';
    filename[26] = 's';
    filename[27] = 'v';
    filename[28] = '\0';

    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        printf("Values are saved in '%s'...\n", filename);
        fprintf(file,
                "line, s_up, s_down, "
                "p1_up, p1_down, p2_up, p2_down, p3_up, p3_down, "
                "d1_up, d1_down, d2_up, d2_down, d3_up, d3_down, d4_up, d4_down, d5_up, d5_down, "
                "f1_up, f1_down, f2_up, f2_down, f3_up, f3_down, f4_up, f4_down, f5_up, f5_down, f6_up, f6_down, f7_up, f7_down, "
                "ms, ml\n");
        for (unsigned int i = 0; i < array_len; i++) {
            fprintf(file, "%u", i + 1);
            saveEConfigElementInFile(&(electron_config_array[i]), file);
        }
        fclose(file);
        printf("Saved.\n");
    } else {
        printf("Could not save values in a file. Please try again.\n");
    }
}
