//
// Created by luka on 20.02.23.
//

#include <stdlib.h>
#include <assert.h>

#include "possibilities.h"
#include "../utils.h"
#include "combinations.h"


void permutationCreation(Possibilities *possibilities, const unsigned short *number_of_electrons) {
    assert(possibilities != NULL && number_of_electrons != NULL && checkElectronsValid(number_of_electrons));
    generate_permutation(number_of_electrons[0], S_ORBITAL, possibilities->possibilitiesS);
    generate_permutation(number_of_electrons[1], P_ORBITAL, possibilities->possibilitiesP);
    generate_permutation(number_of_electrons[2], D_ORBITAL, possibilities->possibilitiesD);
    generate_permutation(number_of_electrons[3], F_ORBITAL, possibilities->possibilitiesF);
}

Possibilities *createPossibilities(unsigned short electrons[4]) {
    assert(electrons != NULL && checkElectronsValid(electrons));

    Possibilities *possibilitiesPtr = (Possibilities *) malloc(sizeof(Possibilities));

    possibilitiesPtr->countS = possibilities_for_combination(electrons[0], S_ORBITAL);
    possibilitiesPtr->countP = possibilities_for_combination(electrons[1], P_ORBITAL);
    possibilitiesPtr->countD = possibilities_for_combination(electrons[2], D_ORBITAL);
    possibilitiesPtr->countF = possibilities_for_combination(electrons[3], F_ORBITAL);
    possibilitiesPtr->countAll = possibilitiesPtr->countS * possibilitiesPtr->countP * possibilitiesPtr->countD * possibilitiesPtr->countF;

    possibilitiesPtr->possibilitiesS = malloc(sizeof(unsigned short) * possibilitiesPtr->countS);
    possibilitiesPtr->possibilitiesP = malloc(sizeof(unsigned short) * possibilitiesPtr->countP);
    possibilitiesPtr->possibilitiesD = malloc(sizeof(unsigned short) * possibilitiesPtr->countD);
    possibilitiesPtr->possibilitiesF = malloc(sizeof(unsigned short) * possibilitiesPtr->countF);

    permutationCreation(possibilitiesPtr, electrons);

    return possibilitiesPtr;
}

void destroyPossibilities(Possibilities *possibilities) {
    assert(possibilities != NULL);

    free(possibilities->possibilitiesS);
    free(possibilities->possibilitiesP);
    free(possibilities->possibilitiesD);
    free(possibilities->possibilitiesF);

    free(possibilities);
}

