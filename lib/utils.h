/**
 * @author  201st-Luka
 *
 * @brief   utils header file
 * @brief   contains the prototypes of the functions
 */


#ifndef SIMULATORFORSPECTROSCOPICTERMS_UTILS_H
#define SIMULATORFORSPECTROSCOPICTERMS_UTILS_H


#include "econfig.h"


// colors
#define COLOR_RED "\e[31m"
#define COLOR_GREEN "\e[32m"
#define COLOR_YELLOW "\e[33m"
#define COLOR_BLUE "\e[34m"
#define COLOR_MAGENTA "\e[35m"
#define COLOR_CYAN "\e[36m"
#define COLOR_WHITE "\e[0;37m"

// text styles
#define UNDERLINE_COLOR_WHITE "\e[4;37m"
#define TEXT_RESET "\e[0m"

// orbitals
#define S_ORBITAL 2
#define P_ORBITAL 6
#define D_ORBITAL 10
#define F_ORBITAL 14

// harpoon arrows
#define ARROW_SPIN_UP "\u21bf"
#define ARROW_SPIN_DOWN "\u21c2"
#define ARROW_SPIN_BOTH "\u296e"
#define BRACKET_SPACE "\u02FD"


/**
 * @brief   returns 1 if the electrons are valid else 0
 *
 * @param   electrons is an unsigned short array (size = 4) that contains the number of electrons for the simulator
 *
 * @pre     electrons != NULL
 * @post    checkElectronsValid becomes 1 if the electrons are valid else 0
 *
 * @return  1 if the electrons are valid
 * @return  0 if not
 */
short checkElectronsValid(const unsigned short electrons[4]);

/**
 * @brief   reads the input stream and saves the values for the simulation
 *
 * @param   input is the array where the terminal input is saved
 *
 * @pre     input != NULL
 * @post    /
 */
void collectInput(unsigned short *input);

/**
 * @brief   this function checks if there is any electronConfig->eCArray element whose group is 0 (not set)
 *
 * @param   electronConfig is a pointer to an ElectronConfig struct
 *
 * @pre     electronConfig != NULL
 * @pre     electronConfig->eCArray != NULL
 * @post    checkElementsGroup becomes 1 if no element is found else 0
 *
 * @return  1 if no element is found
 * @return  0 if there is at least 1 element without a group
 */
int checkElementsGroup(ElectronConfig *electronConfig);


#endif //SIMULATORFORSPECTROSCOPICTERMS_UTILS_H
