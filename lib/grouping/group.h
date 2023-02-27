/*
 * group header file
 * contains the function prototypes
 */


#ifndef SIMULATORFORSPECTROSCOPICTERMS_GROUP_H
#define SIMULATORFORSPECTROSCOPICTERMS_GROUP_H


#include "../econfig.h"


/**
 * @brief   Group struct
 *
 * @typedef Group
 *
 * @struct  unsigned int id
 * @struct  short absMl
 * @struct  float absMs
 *
 * @size 24 bytes
 */
typedef struct {
    unsigned int id;
    short absMl;
    float absMs;
} Group;


/**
 * @brief   Function that returns the max ml of an electron config without a group in the electronConfig array
 *
 * @param   electronConfig The electron config struct in which to search
 *
 * @pre     electronConfig != NULL, arrayLen > 0
 * @post    findMaxMlNoGroup becomes the highest ml value of an electron config that is not in any group
 *
 * @return  The max ml of an electron config which is not in a group is returned
 */
short findMaxMlNoGroup(ElectronConfig *electronConfig);

/**
 * @brief   Function that returns the max ms of an electron config without a group in the electronConfig array and with a ml value
 *
 * @param   electronConfig The electron config struct in which to search
 * @param   ml The ml value which the ms value has to have
 *
 * @pre     electronConfig != NULL and arrayLen > 0
 * @post    findMaxMsNoGroupWithMl becomes the highest ms value of an electron config that is not in any group and ml is ml
 *
 * @return
 */
float findMaxMsNoGroupWithMl(ElectronConfig *electronConfig, short ml);

/**
 * @brief   sets the groups and fills in the corresponding values
 *
 * @param   electronConfig is a pointer to an electron config struct
 * @param   group is a pointer to a group struct
 *
 * @pre     electronConfig != NULL && arrayLen  > 0 && group != NULL
 * @post    /
 */
void setGroup(ElectronConfig *electronConfig, Group *group);

/**
 * @brief   prints the electronConfig elements by groups
 *
 * @param   electronConfig is a pointer to an electron config struct
 *
 * @pre     electronConfig != NULL && arrayLen > 0 && groups != NULL && groups->groupCount > 0
 * @post    /
 */
void printGroupElements(ElectronConfig *electronConfig, Group *group);


#endif //SIMULATORFORSPECTROSCOPICTERMS_GROUP_H
