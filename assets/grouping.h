/*
 * grouping header file
 * contains function prototypes
 */

#include "econfig.h"

#ifndef SIMULATORFORSPECTROSCOPICTERMS_GROUPING_H
#define SIMULATORFORSPECTROSCOPICTERMS_GROUPING_H


/*
 * Group struct
 * 10 bytes
 */
typedef struct {
    unsigned short abs_ml, abs_ms, group_id;
    unsigned int group_elements_count;
} Group;

/*
 * Groups struct
 * 10 bytes
 */
typedef struct {
    Group *group;
    unsigned short group_count;
} Groups;


/*
 * returns the max ml of an electron config without a group in the electron_config array
 * @precondition:   electron_config != NULL and array_len > 0
 * @postcondition:  findMaxMlNoGroup becomes the highest ml value of an electron config that is not in any group
 */
short findMaxMlNoGroup(ElectronConfig *electron_config, unsigned int array_len);

/*
 * appends the group array by 1 element
 * @precondition:   *groups != NULL and groups.group != NULL
 * @postcondition:  appendGroup becomes 1 if succeeded
 */
short appendGroup(Groups *groups);

/*
 * returns the max ms of an electron config without a group in the electron_config array and with a ml value
 * @precondition:   electron_config != NULL and array_len > 0
 * @postcondition:  findMaxMsNoGroupWithMl becomes the highest ms value of an electron config that is not in any group and ml is ml
 */
float findMaxMsNoGroupWithMl(ElectronConfig *electron_config, unsigned int array_len, unsigned int ml);


#endif //SIMULATORFORSPECTROSCOPICTERMS_GROUPING_H
