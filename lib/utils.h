//
// Created by luka on 20.02.23.
//

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


/*
 * returns 1 if the electrons are valid else 0
 * @precondition:   electrons != NULL
 * @postcondition:  checkElectronsValid becomes 1 if the electrons are valid else 0
 */
short checkElectronsValid(const unsigned short electrons[4]);

/*
 * checks if countAll elements have a group
 * @precondition:   electronConfig != NULL && array_len  > 0
 * @postcondition:  1 if countAll elements have a group else 0
 */
short checkElementsGroup(ElectronConfig *electronConfig, unsigned int array_len);

void collectInput(unsigned short *input);


#endif //SIMULATORFORSPECTROSCOPICTERMS_UTILS_H
