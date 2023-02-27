/**
 * @author  201st-Luka
 * @brief   groups header file
 * @brief   contains the prototypes of the functions
 */


#ifndef SIMULATORFORSPECTROSCOPICTERMS_GROUPS_H
#define SIMULATORFORSPECTROSCOPICTERMS_GROUPS_H


#include "../econfig.h"
#include "group.h"


/**
 * @brief   Groups struct
 *
 * @typedef Groups
 *
 * @struct  Group *group
 * @struct  unsigned int groupCount
 *
 * @size    12 - 16 bytes
 */
typedef struct {
    Group *group;
    unsigned int groupCount;
} Groups;


/**
 * @brief   appends the group array by 1 element
 *
 * @param   groups is a pointer to a Groups struct
 *
 * @pre     *groups != NULL and groups.group != NULL
 * @post    appendGroup becomes 1 if succeeded else 0
 *
 * @return  1 if succeeded
 * @return  0 if failed
 */
short appendGroup(Groups *groups);

/**
 * @brief   prints the group values in the console
 *
 * @param   groups is a pointer to a groups struct
 *
 * @pre     groups != NULL
 * @post    /
 */
void printGroupsContent(Groups *groups);

/**
 * @brief   constructs the groups
 *
 * @param electronConfig is a pointer to a ElectronConfig struct
 *
 * @pre     electronConfig != NULL
 * @post    constructGroups becomes a pointer to the allocated groups
 *
 * @return  pointer to the allocated memory if succeeded
 * @return  NULL if failed
 */
Groups *createGroups(ElectronConfig *electronConfig);

/**
 * @brief   frees the groups
 *
 * @param   groups is a pointer to a Groups struct
 *
 * @pre     groups != NULL
 * @post    /
 */
void destroyGroups(Groups *groups);

/**
 * @brief   initialises the group setting
 *
 * @param electronConfig is a pointer to an ElectronConfig struct
 * @param groups is a pointer to a Groups struct
 *
 * @pre     electronConfig != NULL && arrayLen  > 0 && groups != NULL
 * @post    /
 */
void setGroups(ElectronConfig *electronConfig, Groups *groups);


#endif //SIMULATORFORSPECTROSCOPICTERMS_GROUPS_H
