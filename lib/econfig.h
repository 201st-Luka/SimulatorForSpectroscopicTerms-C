/*
 * econfig header file
 * contains macros and function prototypes
 */

#ifndef SIMULATORFORSPECTROSCOPICTERMS_ECONFIG_H
#define SIMULATORFORSPECTROSCOPICTERMS_ECONFIG_H

#include <stdio.h>


// colors

#define ColorRed "\e[31m"
#define ColorGreen "\e[32m"
#define ColorYellow "\e[33m"
#define ColorBlue "\e[34m"
#define ColorMagenta "\e[35m"
#define ColorCyan "\e[36m"
#define ColorWhite "\e[0;37m"

// text styles

#define UnderlineColorWhite "\e[4;37m"
#define TextReset "\e[0m"

// orbitals

#define S 2
#define P 6
#define D 10
#define F 14

// harpoon arrows

#define ArrowSpinUp "\u21bf"
#define ArrowSpinDown "\u21c2"
#define ArrowSpinBoth "\u296e"
#define BracketSpace "\u02FD"


/*
 * ElectronConfig struct
 * 76 bytes
 */
typedef struct {
    unsigned int orbitals;
    short ml;
    float ms;
    unsigned short group;
} ElectronConfig;


/*
 * enumerates over the electronConfig array to fill in the values
 * @precondition:   s_possibilities, p_possibilities, d_possibilities, f_possibilities, number_of_electrons != NULL
 *                  and number_of_electrons is valid
 * @postcondition:  combinations are saved in s_possibilities, p_possibilities, d_possibilities, f_possibilities
 */
void permutationCreation(unsigned short *s_possibilities, unsigned short *p_possibilities, unsigned short *d_possibilities, unsigned short *f_possibilities,
                         const unsigned short *number_of_electrons);
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
void printEConfigElement(ElectronConfig *electronConfig);

/*
 * prints out every single element of the electronConfig array
 * @precondition:   electronConfig != NULL and array_len > 0
 * @postcondition:  /
 */
void printEConfig(ElectronConfig *electronConfig, unsigned int array_len);

/*
 * set the values of the ElectronConfig array orbitals to the values of the created permutations
 * @precondition:   electronConfig != NULL, s_possibilities, p_possibilities, d_possibilities, f_possibilities
 *                  have the right values
 *                  and possibilities_s, possibilities_p, possibilities_d, possibilities_f > 0
 * @postcondition:  electronConfig gets the right pointer values and ms, ml are calculated
 */
void eConfigManipulation(ElectronConfig *electronConfig,
                         unsigned int possibilities_f, unsigned int possibilities_d, unsigned int possibilities_p, unsigned int possibilities_s,
                         const unsigned short *s_possibilities, const unsigned short *p_possibilities, const unsigned short *d_possibilities, const unsigned short *f_possibilities);

void saveEConfigElementInFile(ElectronConfig *electron_config_array, FILE *file);

void saveEConfigInFile(ElectronConfig *electron_config_array, unsigned int array_len);

#endif //SIMULATORFORSPECTROSCOPICTERMS_ECONFIG_H
