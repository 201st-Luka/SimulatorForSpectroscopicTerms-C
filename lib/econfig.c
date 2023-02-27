/*
 * econfig file
 * contains the implementations of the functions
 */


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "econfig.h"
#include "utils.h"


void printArrow(unsigned short spins) {
    if ((spins & 2) && (spins & 1)) {
        printf(ARROW_SPIN_BOTH);
    } else if (spins & 2) {
        printf(ARROW_SPIN_UP);
    } else if (spins & 1) {
        printf(ARROW_SPIN_DOWN);
    } else {
        printf(BRACKET_SPACE);
    }
}

void printEConfigElement(EConfig *eConfig) {
    assert(eConfig != NULL);
    printf(COLOR_GREEN "S: ");
    printArrow((eConfig->orbitals & (3 << (P_ORBITAL + D_ORBITAL + F_ORBITAL))) >> (P_ORBITAL + D_ORBITAL + F_ORBITAL));
    printf(COLOR_BLUE " P: ");
    for (int p = P_ORBITAL / 2; p > 0; --p) {
        printArrow((eConfig->orbitals & (3 << ((p - 1) * 2 + D_ORBITAL + F_ORBITAL))) >> ((p - 1) * 2 + D_ORBITAL + F_ORBITAL));
    }
    printf(COLOR_YELLOW " D: ");
    for (int d = D_ORBITAL / 2; d > 0; --d) {
        printArrow((eConfig->orbitals & (3 << ((d - 1) * 2 + F_ORBITAL))) >> ((d - 1) * 2 + F_ORBITAL));
    }
    printf(COLOR_MAGENTA " F: ");
    for (int f = F_ORBITAL / 2; f > 0; --f) {
        printArrow((eConfig->orbitals & (3 << ((f - 1) * 2))) >> ((f - 1) * 2));
    }
    printf(COLOR_WHITE " Ml: %2d Ms: %4.1f group: %hu" TEXT_RESET "\n", eConfig->ml, eConfig->ms, eConfig->group);
}

void printEConfig(ElectronConfig *electronConfig) {
    assert(electronConfig != NULL);
    printf("Possibilities:\n");
    for (unsigned int i = 0; i < electronConfig->possibilities->countAll; i++) {
        printf(COLOR_CYAN "line: %4u ", i + 1);
        printEConfigElement(&electronConfig->eCArray[i]);
    }
}

void eConfigManipulation(ElectronConfig *electronConfig) {
    assert(
            electronConfig != NULL &&
            electronConfig->possibilities != NULL &&
            electronConfig->possibilities->possibilitiesS != NULL &&
            electronConfig->possibilities->possibilitiesP != NULL &&
            electronConfig->possibilities->possibilitiesD != NULL &&
            electronConfig->possibilities->possibilitiesF != NULL
            );

    unsigned int d_combs = electronConfig->possibilities->countF * electronConfig->possibilities->countD;
    unsigned int p_combs = d_combs * electronConfig->possibilities->countP;

    for (unsigned int i = 0; i < electronConfig->possibilities->countAll; i++) {
        electronConfig->eCArray[i].orbitals = ((((
                (electronConfig->possibilities->possibilitiesS[i / p_combs] << P_ORBITAL)
                | electronConfig->possibilities->possibilitiesP[(i % p_combs) / d_combs]) << D_ORBITAL)
                        | electronConfig->possibilities->possibilitiesD[(i % d_combs) / electronConfig->possibilities->countF]) << F_ORBITAL)
                                | electronConfig->possibilities->possibilitiesF[i % electronConfig->possibilities->countF];
        electronConfig->eCArray[i].ms = (float)((electronConfig->eCArray[i].orbitals & (1 << 31)) >> 31) - (float)((electronConfig->eCArray[i].orbitals & (1 << 30)) >> 30);
        electronConfig->eCArray[i].ml = 0;
        for (int pdf = (P_ORBITAL + D_ORBITAL + F_ORBITAL) / 2 - 1; pdf >= (D_ORBITAL + F_ORBITAL) / 2; --pdf) {
            electronConfig->eCArray[i].ms += (float)((electronConfig->eCArray[i].orbitals & (1 << (pdf * 2 + 1))) >> (pdf * 2 + 1)) - (float)((electronConfig->eCArray[i].orbitals & (1 << (pdf * 2))) >> (pdf * 2));
            electronConfig->eCArray[i].ml += (((electronConfig->eCArray[i].orbitals & (1 << (pdf * 2 + 1))) >> (pdf * 2 + 1)) + ((electronConfig->eCArray[i].orbitals & (1 << (pdf * 2))) >> (pdf * 2))) * (-(pdf - (D_ORBITAL + F_ORBITAL) / 2) + 1);
        }
        for (int df = (D_ORBITAL + F_ORBITAL) / 2 - 1; df >= F_ORBITAL / 2; --df) {
            electronConfig->eCArray[i].ms += (float)((electronConfig->eCArray[i].orbitals & (1 << (df * 2 + 1))) >> (df * 2 + 1)) - (float)((electronConfig->eCArray[i].orbitals & (1 << (df * 2))) >> (df * 2));
            electronConfig->eCArray[i].ml += (((electronConfig->eCArray[i].orbitals & (1 << (df * 2 + 1))) >> (df * 2 + 1)) + ((electronConfig->eCArray[i].orbitals & (1 << (df * 2))) >> (df * 2))) * (-(df - F_ORBITAL / 2) + 2);
        }
        for (int f = F_ORBITAL / 2 - 1; f >= 0 / 2; --f) {
            electronConfig->eCArray[i].ms += (float)((electronConfig->eCArray[i].orbitals & (1 << (f * 2 + 1))) >> (f * 2 + 1)) - (float)((electronConfig->eCArray[i].orbitals & (1 << (f * 2))) >> (f * 2));
            electronConfig->eCArray[i].ml += (((electronConfig->eCArray[i].orbitals & (1 << (f * 2 + 1))) >> (f * 2 + 1)) + ((electronConfig->eCArray[i].orbitals & (1 << (f * 2))) >> (f * 2))) * (-f + 3);
        }
        electronConfig->eCArray[i].group = 0;
        electronConfig->eCArray[i].ms /= 2;
    }
}

ElectronConfig *createElectronConfig(unsigned short electrons[4]) {
    ElectronConfig *electronConfig = (ElectronConfig *) malloc(sizeof(ElectronConfig));
    if (electronConfig == NULL) return NULL;

    Possibilities *possibilities = createPossibilities(electrons);

    if (possibilities == NULL) {
        free(electronConfig);
        return NULL;
    }

    electronConfig->possibilities = possibilities;

    EConfig *eConfig = (EConfig *) malloc(sizeof(EConfig) * electronConfig->possibilities->countAll);

    if (eConfig == NULL) {
        destroyPossibilities(electronConfig->possibilities);
        free(electronConfig);
        return NULL;
    }

    electronConfig->eCArray = eConfig;
    eConfigManipulation(electronConfig);
    return electronConfig;
}

void destroyElectronConfig(ElectronConfig *electronConfig) {
    //destroyGroups(electronConfig->groups);
    destroyPossibilities(electronConfig->possibilities);
    free(electronConfig);
}
