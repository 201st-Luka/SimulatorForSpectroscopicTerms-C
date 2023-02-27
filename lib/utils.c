/*
 * utils file
 * contains the implementations of the functions
 */


#include <assert.h>

#include "utils.h"


short checkElectronsValid(const unsigned short electrons[4]) {
    assert(electrons != NULL);
    if (electrons[0] <= S_ORBITAL && electrons[1] <= P_ORBITAL && electrons[2] <= D_ORBITAL && electrons[3] <= F_ORBITAL)
        return 1;
    else
        return 0;
}

void collectInput(unsigned short *input) {
    printf("Enter your electron configuration (format: S, P, D, F):\n");
    // keyboard input demand for number of electrons
    scanf(" %hu, %hu, %hu, %hu", &input[0], &input[1], &input[2], &input[3]);
    while ((getchar()) != '\n');
}

int checkElementsGroup(ElectronConfig *electronConfig) {
    int notFound = 1;
    for (unsigned int i = 0; i < electronConfig->possibilities->countAll / 2 && notFound; ++i) {
        if (!electronConfig->eCArray[i].group || !electronConfig->eCArray[electronConfig->possibilities->countAll - 1 - i].group)
            notFound = 0;
    }
    return notFound;
}

