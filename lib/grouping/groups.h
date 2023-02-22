//
// Created by luka on 20.02.23.
//

#ifndef SIMULATORFORSPECTROSCOPICTERMS_GROUPS_H
#define SIMULATORFORSPECTROSCOPICTERMS_GROUPS_H


#include "../econfig.h"
#include "group.h"



/*
 * Groups struct
 * 10 bytes
 */
typedef struct {
    Group *group;
    unsigned int groupCount;
} Groups;


/*
 * appends the group array by 1 element
 * @precondition:   *groups != NULL and groups.group != NULL
 * @postcondition:  appendGroup becomes 1 if succeeded else 0
 */
short appendGroup(Groups *groups);

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
Groups *createGroups(ElectronConfig *electronConfig);


/*
 * frees the groups
 * @precondition:   groups != NULL
 * @postcondition:  /
 */
void destroyGroups(Groups *groups);


/*
 * initialises the group setting
 * @precondition:   electronConfig != NULL && arrayLen  > 0 && groups != NULL
 * @postcondition:  /
 */
void setGroups(ElectronConfig *electronConfig, Groups *groups);


#endif //SIMULATORFORSPECTROSCOPICTERMS_GROUPS_H
