/*
 * econfig header file
 * contains macros and function prototypes
 */

#ifndef SIMULATORFORSPECTROSCOPICTERMS_ECONFIG_H
#define SIMULATORFORSPECTROSCOPICTERMS_ECONFIG_H

#include <stdio.h>

#include "combinatoric/combinations.h"
#include "combinatoric/possibilities.h"



/*
 * ElectronConfig struct
 * 76 bytes
 */
typedef struct {
    unsigned int orbitals;
    short ml;
    float ms;
    unsigned short group;
} EConfig;

typedef struct {
    unsigned short electrons[4];
    EConfig *eCArray;
    Possibilities *possibilities;
} ElectronConfig;


/*
 * prints out the right arrow for the orbital
 * @precondition:   /
 * @postcondition:  /
 */
void printArrow(unsigned short spins);

/*
 * prints out the values of an ElectronConfig element
 * @precondition:   electronConfig != NULL
 * @postcondition:  /
 */
void printEConfigElement(EConfig *eConfig);

/*
 * prints out every single element of the electronConfig array
 * @precondition:   electronConfig != NULL and array_len > 0
 * @postcondition:  /
 */
void printEConfig(ElectronConfig *electronConfig);

/*
 * set the values of the ElectronConfig array orbitals to the values of the created permutations
 * @precondition:   electronConfig != NULL, s_possibilities, p_possibilities, d_possibilities, f_possibilities
 *                  have the right values
 *                  and possibilities_s, possibilities_p, possibilities_d, possibilities_f > 0
 * @postcondition:  electronConfig gets the right pointer values and ms, ml are calculated
 */
void eConfigManipulation(ElectronConfig *electronConfig);

ElectronConfig *createElectronConfig(unsigned short electrons[4]);

void destroyElectronConfig(ElectronConfig *electronConfig);


#endif //SIMULATORFORSPECTROSCOPICTERMS_ECONFIG_H
