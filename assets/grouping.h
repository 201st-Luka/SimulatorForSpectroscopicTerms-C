/*
 * grouping header file
 * contains function prototypes
 */

#include "econfig.h"

#ifndef SIMULATORFORSPECTROSCOPICTERMS_GROUPING_H
#define SIMULATORFORSPECTROSCOPICTERMS_GROUPING_H

/*
 * returns the max ml index of an electron config without a group in the electron_config array
 * @precondition:   electron_config != NULL and array_len > 0
 * @postcondition:  findMaxMlNoGroup becames the index of the highest ml value of an electron config that is not in any group
 */
unsigned int findMaxMlNoGroup(ElectronConfig *electron_config, unsigned int array_len);


#endif //SIMULATORFORSPECTROSCOPICTERMS_GROUPING_H
