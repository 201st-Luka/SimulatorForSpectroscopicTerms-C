/*
 * grouping header file
 * contains function prototypes
 */

#include "econfig.h"

#ifndef SIMULATORFORSPECTROSCOPICTERMS_GROUPING_H
#define SIMULATORFORSPECTROSCOPICTERMS_GROUPING_H


/*
 * Group struct
 * 24 bytes
 */
typedef struct {
    unsigned short id, elementsCount;
    short absMl;
    float absMs;
} Group;

/*
 * Groups struct
 * 10 bytes
 */
typedef struct {
    Group *group;
    unsigned short groupCount;
} Groups;


/*
 * returns the max ml of an electron config without a group in the electronConfig array
 * @precondition:   electronConfig != NULL and arrayLen > 0
 * @postcondition:  findMaxMlNoGroup becomes the highest ml value of an electron config that is not in any group
 */
short findMaxMlNoGroup(ElectronConfig *electronConfig, unsigned int arrayLen);

/*
 * appends the group array by 1 element
 * @precondition:   *groups != NULL and groups.group != NULL
 * @postcondition:  appendGroup becomes 1 if succeeded else 0
 */
short appendGroup(Groups *groups);

/*
 * returns the max ms of an electron config without a group in the electronConfig array and with a ml value
 * @precondition:   electronConfig != NULL and arrayLen > 0
 * @postcondition:  findMaxMsNoGroupWithMl becomes the highest ms value of an electron config that is not in any group and ml is ml
 */
float findMaxMsNoGroupWithMl(ElectronConfig *electronConfig, unsigned int arrayLen, short ml);

/*
 * sets the groups and fills in the corresponding values
 * @precondition:   electronConfig != NULL && arrayLen  > 0 && group != NULL
 * @postcondition:  /
 */
void setGroup(ElectronConfig *electronConfig, unsigned int arrayLen, Group *group);

/*
 * prints the group values in the console
 * @precondition:   groups != NULL
 * @postcondition:  /
 */
void printGroupsContent(Groups *groups);

/*
 * constructs the groups
 * @precondition:   /
 * @postcondition:  constructGroups becomes a pointer to the allocated groups
 */
Groups *constructGroups();

/*
 * frees a group
 * @precondition:   group != NULL
 * @postcondition:  /
 */
void freeGroup(Group *group);

/*
 * frees the groups
 * @precondition:   groups != NULL
 * @postcondition:  /
 */
void freeGroups(Groups *groups);

/*
 * checks if all elements have a group
 * @precondition:   electronConfig != NULL && array_len  > 0
 * @postcondition:  1 if all elements have a group else 0
 */
short checkElementsGroup(ElectronConfig *electronConfig, unsigned int array_len);

/*
 * initialises the group setting
 * @precondition:   electronConfig != NULL && arrayLen  > 0 && groups != NULL
 * @postcondition:  /
 */
void setGroups(ElectronConfig *electronConfig, unsigned int arrayLen, Groups *groups);

/*
 * prints the electronConfig elements that are in the group
 * @precondition:   electronConfig != NULL && arrayLen > 0 && group != NULL
 * @postcondition:  /
 */
void printGroupElements(ElectronConfig *electronConfig, unsigned int arrayLen, Group *group);

/*
 * prints the electronConfig elements by groups
 * @precondition:   electronConfig != NULL && arrayLen > 0 && groups != NULL && groups->groupCount > 0
 * @postcondition:  /
 */
void printGroupsElements(ElectronConfig *electronConfig, unsigned int arrayLen, Groups *groups);


#endif //SIMULATORFORSPECTROSCOPICTERMS_GROUPING_H
