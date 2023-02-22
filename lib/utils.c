//
// Created by luka on 20.02.23.
//

#include <assert.h>

#include "utils.h"


short checkElectronsValid(const unsigned short electrons[4]) {
    assert(electrons != NULL);
    if (electrons[0] <= S_ORBITAL && electrons[1] <= P_ORBITAL && electrons[2] <= D_ORBITAL && electrons[3] <= F_ORBITAL)
        return 1;
    else
        return 0;
}

short checkElementsGroup(ElectronConfig *electronConfig, unsigned int array_len) {
    assert(electronConfig != NULL && array_len > 0);
    short result = 1;
    for (int i = 0; i < array_len && result; ++i) {
        if (electronConfig->eCArray[i].group == 0) {
            result = 0;
        }
    }
    return result;
}

void collectInput(unsigned short *input) {
    printf("Enter your electron configuration (format: S, P, D, F):\n");
    // keyboard input demand for number of electrons
    scanf(" %hu, %hu, %hu, %hu", &input[0], &input[1], &input[2], &input[3]);
    while ((getchar()) != '\n');
}
