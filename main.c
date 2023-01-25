#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/econfig.h"
#include "lib/combinations.h"
#include "lib/grouping.h"


#define MaxConsoleLines 1680

#define gitHubLink "https://github.com/201st-Luka/SimulatorForSpectroscopicTerms"
#define gitHubWikiLink "https://github.com/201st-Luka/SimulatorForSpectroscopicTerms/wiki"

typedef struct {
    unsigned short master_version,
            version;
} SimulatorVersion;

typedef enum {
    closeProgram,
    printValuesAndGroups,
    printGroups,
    gitHub,
    gitHubWiki
} Task;

const SimulatorVersion simulator_version = {0, 1};

void collectInput(unsigned short *input) {
    printf("Enter your electron configuration (format: s, p, d, f):\n");
    // keyboard input demand for number of electrons
    scanf(" %hu, %hu, %hu, %hu", &input[0], &input[1], &input[2], &input[3]);
    while ((getchar()) != '\n');
}

void close() {
    printf("Exit...");
}

void simulator(short b_print, short by_args, unsigned short *electrons) {
    // check if electrons is valid
    if (electrons[0] <= S && electrons[1] <= P && electrons[2] <= D && electrons[3] <= F) {
        // electrons is valid
        if (!by_args) printf("Processing your inputs...\n");
        // calculate combinations
        unsigned int possibilities_for_s = possibilities_for_combination(electrons[0], S),
                possibilities_for_p = possibilities_for_combination(electrons[1], P),
                possibilities_for_d = possibilities_for_combination(electrons[2], D),
                possibilities_for_f = possibilities_for_combination(electrons[3], F);

        unsigned short s_possibilities[possibilities_for_s],
                p_possibilities[possibilities_for_p],
                d_possibilities[possibilities_for_d],
                f_possibilities[possibilities_for_f];

        ElectronConfig *electron_config_array = (ElectronConfig*) malloc(
                possibilities_for_s * possibilities_for_p * possibilities_for_d * possibilities_for_f * sizeof(ElectronConfig)
        );
        if (electron_config_array != NULL) {

            permutation_creation(s_possibilities, p_possibilities, d_possibilities, f_possibilities,
                                 electrons);

            econfig_manipulation(electron_config_array,
                                 possibilities_for_f, possibilities_for_d, possibilities_for_p, possibilities_for_s,
                                 s_possibilities, p_possibilities, d_possibilities, f_possibilities);

            Group *groups_ptr = malloc(sizeof(Group));
            Groups groups;
            groups.group = groups_ptr;
            groups.group_count = 1;

            if (b_print) {
                if (possibilities_for_s * possibilities_for_p * possibilities_for_d * possibilities_for_f <= MaxConsoleLines) {
                    printf("Number of possibilities: %u\n", possibilities_for_s * possibilities_for_p * possibilities_for_d * possibilities_for_f);
                    print_econfig(electron_config_array, possibilities_for_s * possibilities_for_p * possibilities_for_d * possibilities_for_f);
                } else {
                    printf(ColorRed "So many combinations can not be printed in the console. The maximum is %d.\n" TextReset, MaxConsoleLines);
                }
            }

            printf("max ml: %hd, max ms for max ml: %.1f\n", findMaxMlNoGroup(
                           electron_config_array,
                           possibilities_for_s * possibilities_for_p * possibilities_for_d * possibilities_for_f
                   ), findMaxMsNoGroupWithMl(
                           electron_config_array,
                           possibilities_for_s * possibilities_for_p * possibilities_for_d * possibilities_for_f,
                           findMaxMlNoGroup(
                                   electron_config_array,
                                   possibilities_for_s * possibilities_for_p * possibilities_for_d * possibilities_for_f
                           )
                   )
            );

            // free the memory for electron_config_array (because of dynamic allocation)
            free(electron_config_array);
        } else {
            printf(ColorRed "MEMORY ERROR:" TextReset " Not enough free memory.");
        }
    } else {
        // electrons is invalid
        printf("Your entered values are not valid.\n"
               "The maximal valid values are %d, %d, %d, %d for s, p, d, f.\n"
               "Your values were:\n", S, P, D, F);
        if (electrons[0] <= S) printf("%u, ", electrons[0]);
        else printf(ColorRed "%u" TextReset ", ", electrons[0]);
        if (electrons[1] <= P) printf("%u, ", electrons[1]);
        else printf(ColorRed "%u" TextReset ", ", electrons[1]);
        if (electrons[2] <= D) printf("%u, ", electrons[2]);
        else printf(ColorRed "%u" TextReset ", ", electrons[2]);
        if (electrons[3] <= F) printf("%u\n", electrons[3]);
        else printf(ColorRed "%u" TextReset "\n", electrons[3]);
    }
}

void startArgs(int argc, char **argv) {
    unsigned short command_line_input[4] = {0, 0, 0, 0};
    unsigned short mode = 0;
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-s") || !strcmp(argv[i], "-S")) {
            mode = 2;
            command_line_input[0] = atoi(argv[++i]);
        }
        if (!strcmp(argv[i], "-p") || !strcmp(argv[i], "-P")) {
            mode = 2;
            command_line_input[1] = atoi(argv[++i]);
        }
        if (!strcmp(argv[i], "-d") || !strcmp(argv[i], "-D")) {
            mode = 2;
            command_line_input[2] = atoi(argv[++i]);
        }
        if (!strcmp(argv[i], "-f") || !strcmp(argv[i], "-F")) {
            mode = 2;
            command_line_input[3] = atoi(argv[++i]);
        }
        if (!strcmp(argv[i], "-help") || !strcmp(argv[i], "-h") || !strcmp(argv[i], "-H")) mode = 0;
        if (!strcmp(argv[i], "-version") || !strcmp(argv[i], "-v") || !strcmp(argv[i], "-V")) mode = 1;
    }
    switch (mode) {
        case 0:
            printf("usage: SimulatorForSpectroscopicTerms [-option] ...\n"
                   "Options and arguments:\n"
                   "-help  : show this list\n"
                   "-s val : val is the number of electrons for the s-orbital (0 -> %d)\n"
                   "-p val : val is the number of electrons for the p-orbital (0 -> %d)\n"
                   "-d val : val is the number of electrons for the d-orbital (0 -> %d)\n"
                   "-f val : val is the number of electrons for the f-orbital (0 -> %d)\n"
                   "-v     : show the simulators version\n", S, P, D, F);
            break;
        case 1:
            printf("Version: %u.%u", simulator_version.master_version, simulator_version.version);
            break;
        case 2:
            printf("s=%hd, p=%hd, d=%2hd, f=%hd\n",
                   command_line_input[0], command_line_input[1], command_line_input[2], command_line_input[3]);
            simulator(0, 1, command_line_input);
            break;
    }
}

int main(int argc, char **argv) {
    unsigned short user_command;
    if (argc != 1) {
        startArgs(argc, argv);
        user_command = 0;
    } else {
        printf(UnderlineColorWhite "Started the Chemistry Program\n" TextReset);
        user_command = 1;

        // main loop
        while (user_command) {
            unsigned short input[4];
            printf(" 1 Enter values and print out electron configuration possibilities with groups\n"
                   " 2 Enter values and print out groups\n"
                   " 3 Show GitHub page\n"
                   " 4 Show GitHub wiki page\n"
                   " 0 Close the program\n"
                   "Selection: ");
            scanf("%1hu", &user_command);
            // catch all chars that are in the input buffer
            while ((getchar()) != '\n');

            if (user_command != 3 && user_command != 4 && user_command !=0) {
                collectInput(input);
            }

            // switch different cases for the entered user command
            switch (user_command) {
                case closeProgram:
                    close();
                    break;
                case printValuesAndGroups:
                    simulator(1, 0, input);
                    break;
                case printGroups:
                    simulator(0, 0, input);
                    break;
                case gitHub:
                    printf("The GitHub link is:\n%s\n", gitHubLink);
                    system("open " gitHubLink);
                    break;
                case gitHubWiki:
                    printf("The GitHub wiki link is:\n%s\n", gitHubWikiLink);
                    system("open " gitHubWikiLink);
                    break;
                default:
                    printf("Default selected (1)");
                    simulator(1, 0, input);
                    user_command = 1;
            }
            printf("\n");
        }
    }

    return 0;
}
