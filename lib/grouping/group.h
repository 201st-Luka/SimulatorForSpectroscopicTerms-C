//
// Created by luka on 20.02.23.
//

#ifndef SIMULATORFORSPECTROSCOPICTERMS_GROUP_H
#define SIMULATORFORSPECTROSCOPICTERMS_GROUP_H


#include "../econfig.h"


/*
 * Group struct
 * 24 bytes
 */
typedef struct {
    unsigned short id;
    short absMl;
    float absMs;
} Group;


/*
 * returns the max ml of an electron config without a group in the electronConfig array
 * @precondition:   electronConfig != NULL and arrayLen > 0
 * @postcondition:  findMaxMlNoGroup becomes the highest ml value of an electron config that is not in any group
 */
short findMaxMlNoGroup(ElectronConfig *electronConfig);

/*
 * returns the max ms of an electron config without a group in the electronConfig array and with a ml value
 * @precondition:   electronConfig != NULL and arrayLen > 0
 * @postcondition:  findMaxMsNoGroupWithMl becomes the highest ms value of an electron config that is not in any group and ml is ml
 */
float findMaxMsNoGroupWithMl(ElectronConfig *electronConfig, short ml);

/*
 * sets the groups and fills in the corresponding values
 * @precondition:   electronConfig != NULL && arrayLen  > 0 && group != NULL
 * @postcondition:  /
 */
void setGroup(ElectronConfig *electronConfig, Group *group);

/*
 * prints the electronConfig elements by groups
 * @precondition:   electronConfig != NULL && arrayLen > 0 && groups != NULL && groups->groupCount > 0
 * @postcondition:  /
 */
void printGroupElements(ElectronConfig *electronConfig, unsigned int arrayLen, Group *group);


#endif //SIMULATORFORSPECTROSCOPICTERMS_GROUP_H
