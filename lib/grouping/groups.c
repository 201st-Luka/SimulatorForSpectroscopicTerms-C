/*
 * groups file
 * contains the implementations of functions
 */


#include <stdlib.h>
#include <assert.h>

#include "groups.h"
#include "../utils.h"


short appendGroup(Groups *groups) {
    assert(groups != NULL && groups->group != NULL);
    Group *tmpGroup = realloc(groups->group, sizeof(Group) * (++groups->groupCount));
    if (tmpGroup != NULL) {
        groups->group = tmpGroup;
        return 1;
    } else {
        return 0;
    }
}

void printGroupsContent(Groups *groups) {
    assert(groups != NULL);
    for (unsigned int i = 0; i < groups->groupCount; i++) {
        printf("absMl: %hd, absMs: %4.1f, id: %hu\n", groups->group[i].absMl, groups->group[i].absMs, groups->group[i].id);
    }
}

Groups *createGroups(ElectronConfig *electronConfig) {
    Groups *groups = malloc(sizeof(Groups));
    Group *groups_ptr = malloc(sizeof(Group));

    if (groups == NULL || groups_ptr == NULL) return NULL;

    groups->group = groups_ptr;
    groups->groupCount = 1;

    setGroups(electronConfig, groups);

    return groups;
}

void destroyGroup(Group *group) {
    assert(group != NULL);
}

void destroyGroups(Groups *groups){
    assert(groups != NULL);
    for (int iGroup = 0; iGroup < groups->groupCount; ++iGroup) {
        destroyGroup(&(groups->group[iGroup]));
    }
    free(groups->group);
    free(groups);
}

void setGroups(ElectronConfig *electronConfig, Groups *groups) {
    assert(electronConfig != NULL);
    unsigned short groupIndex = 1;
    groups->group[groupIndex - 1].absMl = findMaxMlNoGroup(electronConfig);
    groups->group[groupIndex - 1].absMs = findMaxMsNoGroupWithMl(electronConfig, groups->group[0].absMl);
    groups->group[groupIndex - 1].id = groupIndex;
    setGroup(electronConfig, &groups->group[0]);
    while (!checkElementsGroup(electronConfig)) {
        groupIndex += 1;
        if (appendGroup(groups)) {
            groups->group[groupIndex - 1].absMl = findMaxMlNoGroup(electronConfig);
            groups->group[groupIndex - 1].absMs = findMaxMsNoGroupWithMl(electronConfig, groups->group[groupIndex - 1].absMl);
            groups->group[groupIndex - 1].id = groupIndex;
            setGroup(electronConfig, &groups->group[groupIndex - 1]);
        } else {
            printf(COLOR_RED "An Error occurred while building the groups." TEXT_RESET);
            break;
        }
    }
}
