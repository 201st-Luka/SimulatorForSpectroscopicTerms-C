#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/lib.h"

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
    gitHubWiki,
    version
} Task;

const SimulatorVersion simulator_version = {0, 1};

void close() {
    printf("Exit...");
}

void simulator(short b_print, unsigned short *electrons) {
    // check if electrons is valid
    if (electrons[0] <= S_ORBITAL && electrons[1] <= P_ORBITAL && electrons[2] <= D_ORBITAL && electrons[3] <= F_ORBITAL) {
        // electrons is valid
        printf("Processing your inputs...\n");

        ElectronConfig *electronConfig = createElectronConfig(electrons);
        // print possibilities
        if (electronConfig != NULL) {
            Groups *groups;
            if (b_print) {
                printf("Number of possibilities: %u\n",
                       electronConfig->possibilities->countAll);
                groups = createGroups(electronConfig);
                if (electronConfig->possibilities->countAll <= MaxConsoleLines) {
                    printEConfig(electronConfig);
                } else {
                    printf(COLOR_RED "So many combinations can not be printed in the console. The maximum is %d.\n" TEXT_RESET,
                           MaxConsoleLines);
                }
            } else groups = createGroups(electronConfig);
            printGroupsContent(groups);
            //printGroupsElements(electronConfig);

            // free the memory for electron_config_array, groups (because of dynamic allocation)
            destroyElectronConfig(electronConfig);
            destroyGroups(groups);
        } else {
            printf(COLOR_RED "MEMORY ERROR:" TEXT_RESET " Not enough free memory.");
        }
    } else {
        // electrons array is invalid
        printf("Your entered values are not valid.\n"
               "The maximal valid values are %d, %d, %d, %d for S, P, D, F.\n"
               "Your values were:\n", S_ORBITAL, P_ORBITAL, D_ORBITAL, F_ORBITAL);
        if (electrons[0] <= S_ORBITAL) printf("%u, ", electrons[0]);
        else printf(COLOR_RED "%u" TEXT_RESET ", ", electrons[0]);
        if (electrons[1] <= P_ORBITAL) printf("%u, ", electrons[1]);
        else printf(COLOR_RED "%u" TEXT_RESET ", ", electrons[1]);
        if (electrons[2] <= D_ORBITAL) printf("%u, ", electrons[2]);
        else printf(COLOR_RED "%u" TEXT_RESET ", ", electrons[2]);
        if (electrons[3] <= F_ORBITAL) printf("%u\n", electrons[3]);
        else printf(COLOR_RED "%u" TEXT_RESET "\n", electrons[3]);
    }
}

int main() {
    unsigned short user_command;

    printf(UNDERLINE_COLOR_WHITE "Simulator for spectroscopic terms\n" TEXT_RESET);
    user_command = 1;

    // main loop
    while (user_command) {
        unsigned short input[4] = {0, 0, 0, 0};
        printf(" 1 Enter values and print out electron configuration possibilities with groups\n"
               " 2 Enter values and print out groups\n"
               " 3 Show GitHub page\n"
               " 4 Show GitHub wiki page\n"
               " 5 Show version\n"
               " 0 Close the program\n"
               "Selection: ");
        scanf("%1hu", &user_command);
        // catch countAll chars that are in the input buffer
        while ((getchar()) != '\n');

        if (user_command != 3 && user_command != 4 && user_command != 0) {
            collectInput(input);
        }

        // switch different cases for the entered user command
        switch (user_command) {
            case closeProgram:
                close();
                break;
            case printValuesAndGroups:
                simulator(1, input);
                break;
            case printGroups:
                simulator(0, input);
                break;
            case gitHub:
                printf("The GitHub link is:\n%s\n", gitHubLink);
                system("open " gitHubLink);
                break;
            case gitHubWiki:
                printf("The GitHub wiki link is:\n%s\n", gitHubWikiLink);
                system("open " gitHubWikiLink);
                break;
            case version:
                printf("The version of the Simulator is %hu.%hu.",
                       simulator_version.master_version,
                       simulator_version.version);
                break;
            default:
                printf("Default selected (1)\n");
                simulator(1, input);
                user_command = 1;
        }
        printf("\n");
    }

    return 0;
}
