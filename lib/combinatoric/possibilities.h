/**
 * @author  201st-Luka
 * @brief   possibilities header file
 * @brief   contains the prototypes of the functions
 */


#ifndef SIMULATORFORSPECTROSCOPICTERMS_POSSIBILITIES_H
#define SIMULATORFORSPECTROSCOPICTERMS_POSSIBILITIES_H


/**
 * @typedef Possibilities
 *
 * @struct  unsigned int countS
 * @struct  unsigned int countP
 * @struct  unsigned int countD
 * @struct  unsigned int countF
 * @struct  unsigned int countAll
 * @struct  unsidned short *possibilitiesS
 * @struct  unsidned short *possibilitiesP
 * @struct  unsidned short *possibilitiesD
 * @struct  unsidned short *possibilitiesF
 *
 * @brief   Possibilities struct typedef
 *
 * @size    56 bytes
 */
typedef struct {
    unsigned int countS, countP, countD, countF, countAll;
    unsigned short *possibilitiesS, *possibilitiesP, *possibilitiesD, *possibilitiesF;
} Possibilities;


/**
 * @brief   enumerates over the electronConfig array to fill in the values
 *
 * combinations are saved in possibilities->possibilitiesS, possibilities->possibilitiesP, possibilities->possibilitiesD, possibilities->possibilitiesF
 *
 * @param   possibilities is a pointer to a Possibilities struct
 * @param   numberOfElectrons is an array (size = 4)
 *
 * @pre     possibilities != NULL
 * @pre     possibilities->possibilitiesS != NULL
 * @pre     possibilities->possibilitiesP != NULL
 * @pre     possibilities->possibilitiesD != NULL
 * @pre     possibilities->possibilitiesF != NULL
 * @pre     numberOfElectrons != NULL
 * @pre     checkElectronsValid(numberOfElectrons)
 * @post    /
 */
void permutationCreation(Possibilities *possibilities, const unsigned short *numberOfElectrons);

/**
 * @brief   creates a pointer for the Possibilities struct and fills in the values
 *
 * @param   electrons is an array
 *
 * @pre     electrons != NULL
 * @pre     checkElectronsValid(electrons)
 * @post    createPossibilities becomes a pointer to the allocated Possibilities struct
 *
 * @return  pointer to the allocated memory
 */
Possibilities *createPossibilities(unsigned short electrons[4]);

/**
 * @brief   destructs a Possibilities struct (free)
 *
 * @param possibilities is a pointer to a possibilities struct
 *
 * @pre     possibilities != NULL
 * @post    /
 */
void destroyPossibilities(Possibilities *possibilities);


#endif //SIMULATORFORSPECTROSCOPICTERMS_POSSIBILITIES_H
