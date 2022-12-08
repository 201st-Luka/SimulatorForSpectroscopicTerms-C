#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "assets/econfig.h"
#include "assets/combinations.h"


#define MaxConsoleLines 500
#define MaxFileLines 1048575


void saveEConfigLineInFile(ElectronConfig *electron_config_array, FILE *file) {
    fprintf(file, ", %hu, %hu",
            electron_config_array->sOrbital.spinUp, electron_config_array->sOrbital.spinDown);
    for (int i_p = 0; i_p < P / 2; ++i_p) {
        fprintf(file, " ,%hu, %hu",
                electron_config_array->pOrbital[i_p].spinUp, electron_config_array->pOrbital[i_p].spinDown);
    }
    for (int i_d = 0; i_d < D / 2; ++i_d) {
        fprintf(file, " ,%hu, %hu",
                electron_config_array->dOrbital[i_d].spinUp, electron_config_array->dOrbital[i_d].spinDown);
    }
    for (int i_f = 0; i_f < F / 2; ++i_f) {
        fprintf(file, " ,%hu, %hu",
                electron_config_array->fOrbital[i_f].spinUp, electron_config_array->fOrbital[i_f].spinDown);
    }
    fprintf(file, ", %f, %d\n", electron_config_array->ms, electron_config_array->ml);
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
    filename[5] = (time_formatted->tm_year + 1900) / 1000 + 48;
    filename[6] = ((time_formatted->tm_year + 1900) % 1000) / 100 + 48;
    filename[7] = ((time_formatted->tm_year + 1900) % 100) / 10 + 48;
    filename[8] = (time_formatted->tm_year + 1900) % 10 + 48;
    filename[9] = '-';
    filename[10] = (time_formatted->tm_mon + 1) / 10 + 48;
    filename[11] = (time_formatted->tm_mon + 1) % 10 + 48;
    filename[12] = '-';
    filename[13] = time_formatted->tm_mday / 10 + 48;
    filename[14] = time_formatted->tm_mday % 10 + 48;
    filename[15] = '_';
    filename[16] = time_formatted->tm_hour / 10 + 48;
    filename[17] = time_formatted->tm_hour % 10 + 48;
    filename[18] = '-';
    filename[19] = time_formatted->tm_min / 10 + 48;
    filename[20] = time_formatted->tm_min % 10 + 48;
    filename[21] = '-';
    filename[22] = time_formatted->tm_sec / 10 + 48;
    filename[23] = time_formatted->tm_sec % 10 + 48;
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
            saveEConfigLineInFile(&(electron_config_array[i]), file);
        }
        fclose(file);
        printf("Saved.\n");
    } else {
        printf("Could not save values in a file. Please try again.\n");
    }

}

void close() {
    printf("Exit...");
}

void startCalculation(short b_print, short b_save) {
    printf("Enter your electron configuration (format: s, p, d, f):\n");
    unsigned short input[4] = {0, 0, 0, 0};
    // keyboard input demand for number of electrons
    scanf(" %hu, %hu, %hu, %hu", &input[0], &input[1], &input[2], &input[3]);
    while ((getchar()) != '\n');

    // check if input is valid
    if (input[0] <= S && input[1] <= P && input[2] <= D && input[3] <= F) {
        // input is valid
        printf("Processing your inputs...\n");
        // calculate combinations
        unsigned int possibilities_s = possibilities_for_combination(input[0], S),
                possibilities_p = possibilities_for_combination(input[1], P),
                possibilities_d = possibilities_for_combination(input[2], D),
                possibilities_f = possibilities_for_combination(input[3], F);

        short s_possibilities[possibilities_s][S],
                p_possibilities[possibilities_p][P],
                d_possibilities[possibilities_d][D],
                f_possibilities[possibilities_f][F];

        memset(s_possibilities, 0, possibilities_s * S * sizeof(short));
        memset(p_possibilities, 0, possibilities_p * P * sizeof(short));
        memset(d_possibilities, 0, possibilities_d * D * sizeof(short));
        memset(f_possibilities, 0, possibilities_f * F * sizeof(short));

        ElectronConfig *electron_config_array = (ElectronConfig*) malloc(
                possibilities_s * possibilities_p * possibilities_d * possibilities_f * sizeof(ElectronConfig)
        );

        permutation_creation(s_possibilities, p_possibilities, d_possibilities, f_possibilities,
                             input);

        econfig_manipulation(electron_config_array,
                             possibilities_f, possibilities_d, possibilities_p, possibilities_s,
                             s_possibilities, p_possibilities, d_possibilities, f_possibilities);

        if (b_print) {
            if (possibilities_s * possibilities_p * possibilities_d * possibilities_f < MaxConsoleLines) {
                printf("Number of possibilities: %u\n", possibilities_s * possibilities_p * possibilities_d * possibilities_f);
                print_econfig(electron_config_array, possibilities_s * possibilities_p * possibilities_d * possibilities_f);
            } else {
                printf(ColorRed "So much combinations can not printed in the console. The maximum is %d.\n" TextReset, MaxConsoleLines);
            }
        }

        if (b_save) {
            if (possibilities_s * possibilities_p * possibilities_d * possibilities_f < MaxFileLines) {
                saveEConfigInFile(electron_config_array, possibilities_s * possibilities_p * possibilities_d * possibilities_f);
            } else {
                printf(ColorRed "So many combinations can not be saved in a file. The maximum is %d.\n" TextReset, MaxFileLines);
            }
        }

        // free the memory for electron_config_array (because of dynamic allocation)
        free(electron_config_array);

    } else {
        // input is invalid
        printf("Your entered values are not valid.\n"
               "The maximal valid values are %d, %d, %d, %d for s, p, d, f.\n"
               "Your values were:\n", S, P, D, F);
        if (input[0] <= S) printf("%u, ", input[0]);
        else printf(ColorRed "%u" TextReset ", ", input[0]);
        if (input[1] <= P) printf("%u, ", input[1]);
        else printf(ColorRed "%u" TextReset ", ", input[1]);
        if (input[2] <= D) printf("%u, ", input[2]);
        else printf(ColorRed "%u" TextReset ", ", input[2]);
        if (input[3] <= F) printf("%u\n", input[3]);
        else printf(ColorRed "%u" TextReset "\n", input[3]);
    }
}

int main(int argc, char **argv) {
    printf("%lu", sizeof(ElectronConfig));
    printf(UnderlineColorWhite "Started the Chemistry Program\n" TextReset);
    unsigned short user_command;
    if (argc != 1) {
        printf("multiple arguments");
        user_command = 0;
    } else user_command = 1;

    // main loop
    while (user_command) {
        printf(" 1 Enter values and print out electron configuration possibilities\n"
               " 2 Enter values and save electron configuration possibilities in file\n"
               " 3 Enter values, print out electron configuration possibilities and save electron configuration possibilities in file\n"
               " 4 Enter values\n"
               " 0 Close the program\n"
               "Selection: ");
        scanf("%1hu", &user_command);
        // catch all chars that are in the buffer
        while ((getchar()) != '\n');

        // switch different cases for the entered user command
        switch (user_command) {
            case 0:
                close();
                break;
            case 1:
                startCalculation(1, 0);
                break;
            case 2:
                startCalculation(0, 1);
                break;
            case 3:
                startCalculation(1, 1);
                break;
            case 4:
                startCalculation(0, 0);
                break;
            default:
                user_command = 1;
        }
        printf("\n");
    }
    return 0;
}
