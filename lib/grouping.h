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
    unsigned short absMl, id, elementsCount;
    float absMs;
    unsigned int *elements;
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
unsigned short findMaxMlNoGroup(ElectronConfig *electronConfig, unsigned int arrayLen);

/*
 * appends the group array by 1 element
 * @precondition:   *groups != NULL and groups.group != NULL
 * @postcondition:  appendGroup becomes 1 if succeeded
 */
short appendGroup(Groups *groups);

/*
 * returns the max ms of an electron config without a group in the electronConfig array and with a ml value
 * @precondition:   electronConfig != NULL and arrayLen > 0
 * @postcondition:  findMaxMsNoGroupWithMl becomes the highest ms value of an electron config that is not in any group and ml is ml
 */
float findMaxMsNoGroupWithMl(ElectronConfig *electronConfig, unsigned int arrayLen, unsigned short ml);

int groupElementCount(float ms);

void setGroup(ElectronConfig *electron_config, unsigned int array_len, Group *group);

void printGroupsContent(Groups *groups);

Groups *constructGroups();

void freeGroup(Group *group);

void freeGroups(Groups *groups);

unsigned int sumGroupElements(Groups *groups);

void setGroups(ElectronConfig *electron_config, unsigned int array_len, Groups *groups);


#endif //SIMULATORFORSPECTROSCOPICTERMS_GROUPING_H
