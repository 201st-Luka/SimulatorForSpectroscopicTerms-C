/**
 * @author 201st-Luka
 *
 * @brief   econfig header file
 * @brief   contains macros and function prototypes
 */


#ifndef SIMULATORFORSPECTROSCOPICTERMS_ECONFIG_H
#define SIMULATORFORSPECTROSCOPICTERMS_ECONFIG_H


#include <stdio.h>

#include "combinatoric/combinations.h"
#include "combinatoric/possibilities.h"


/**
 * @brief   E config struct
 *
 * @typedef EConfig
 *
 * @struct   unsigned int orbitals
 * @struct   short ml
 * @struct   float ms
 * @struct   unsigned int group
 *
 * @size    12 bytes
 */
typedef struct {
    unsigned int orbitals;
    short ml;
    float ms;
    unsigned int group;
} EConfig;

/**
 * @brief   Electron config struct
 *
 * @typedef ElectronConfig
 *
 * @struct  unsigned short electrons[4]
 * @struct  EConfig *eCArray
 * @struct  Possibilities possibilities
 *
 * @size    24 bytes
 */
typedef struct {
    unsigned short electrons[4];
    EConfig *eCArray;
    Possibilities *possibilities;
} ElectronConfig;


/**
 * @brief   prints out the right arrow for the orbital
 *
 * @param   spins is the spin of the electron (can be 1, 10, 11)
 *
 * @pre     /
 * @post    /
 */
void printArrow(unsigned short spins);

/**
 * @brief   prints out the values of an ElectronConfig element
 *
 * @param   eConfig is a pointer to an EConfig struct
 *
 * @pre     electronConfig != NULL
 * @post    /
 */
void printEConfigElement(EConfig *eConfig);

/**
 * @brief   prints out every single element of the electronConfig array
 *
 * @param   electronConfig is a pointer to an ElectronConfig struct
 *
 * @pre     electronConfig != NULL and array_len > 0
 * @post    /
 */
void printEConfig(ElectronConfig *electronConfig);

/**
 * @brief   set the values of the ElectronConfig array orbitals to the values of the created permutations
 * @brief   (electronConfig gets the right pointer values and ms, ml are calculated)
 *
 * @param   electronConfig is a pointer to an ElectronConfig struct
 *
 * @pre     electronConfig != NULL
 * @pre     electronConfig->possibilities != NULL
 * @pre     electronConfig->possibilities->possibilitiesS != NULL
 * @pre     electronConfig->possibilities->possibilitiesP != NULL
 * @pre     electronConfig->possibilities->possibilitiesD != NULL
 * @pre     electronConfig->possibilities->possibilitiesF != NULL
 * @post    /
 */
void eConfigManipulation(ElectronConfig *electronConfig);

/**
 * @brief   creates an electron config and returns its pointer
 *
 * @param   electrons is an unsigned short array (size = 4) that contains the number of electrons for the simulator
 *
 * @pre     electrons != NULL
 * @post    createElectronConfig becomes a pointer to the allocated memory if success else NULL
 *
 * @return  a pointer to the allocated memory if succeeded
 * @return  NULL if failed
 */
ElectronConfig *createElectronConfig(unsigned short electrons[4]);

/**
 * @brief   destroys an electron config
 *
 * @param   electronConfig is a pointer to an ElectronConfig struct
 *
 * @precondition:   electronConfig != NULL
 * @postcondition:  /
 */
void destroyElectronConfig(ElectronConfig *electronConfig);


#endif //SIMULATORFORSPECTROSCOPICTERMS_ECONFIG_H
