//
// Created by luka on 20.02.23.
//

#ifndef SIMULATORFORSPECTROSCOPICTERMS_POSSIBILITIES_H
#define SIMULATORFORSPECTROSCOPICTERMS_POSSIBILITIES_H


typedef struct {
    unsigned int countS, countP, countD, countF, countAll;
    unsigned short *possibilitiesS, *possibilitiesP, *possibilitiesD, *possibilitiesF;
} Possibilities;


/*
 * enumerates over the electronConfig array to fill in the values
 * @precondition:   s_possibilities, p_possibilities, d_possibilities, f_possibilities, number_of_electrons != NULL
 *                  and number_of_electrons is valid
 * @postcondition:  combinatoric are saved in s_possibilities, p_possibilities, d_possibilities, f_possibilities
 */
void permutationCreation(Possibilities *possibilities, const unsigned short *number_of_electrons);

/*
 * creates a pointer for the Possibilities struct and fills in the values
 * @precondition:   electrons != NULL && checkElectronsValid
 * @postcondition:  createPossibilities becomes a pointer to the allocated Possibilities struct
 */
Possibilities *createPossibilities(unsigned short electrons[4]);

/*
 * destructs a Possibilities struct (free)
 * @precondition:   possibilities != NULL
 * @postcontition:  /
 */
void destroyPossibilities(Possibilities *possibilities);




#endif //SIMULATORFORSPECTROSCOPICTERMS_POSSIBILITIES_H
