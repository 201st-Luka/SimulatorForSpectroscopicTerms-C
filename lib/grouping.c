/*
 * grouping file
 * contains the implementations of functions
 */

#include <stdlib.h>
#include <assert.h>

#include "grouping.h"


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

short findMaxMlNoGroup(ElectronConfig *electronConfig, unsigned int arrayLen) {
    assert(electronConfig != NULL && arrayLen > 0);
    short maxMl = -32768;
    for (unsigned int i = 0; i < arrayLen; i++ ) {
        if (!electronConfig[i].group && electronConfig[i].ml > maxMl) {
            maxMl = electronConfig[i].ml;
        }
    }
    return maxMl;
}

float findMaxMsNoGroupWithMl(ElectronConfig *electronConfig, unsigned int arrayLen, short ml) {
    assert(electronConfig != NULL && arrayLen > 0);
    float maxMs = 0;
    for (unsigned int i = 0; i < arrayLen; i++ ) {
        if (!electronConfig[i].group && electronConfig[i].ml == ml && electronConfig[i].ms > maxMs) {
            maxMs = electronConfig[i].ms;
        }
    }
    return maxMs;
}

void setGroup(ElectronConfig *electronConfig, unsigned int arrayLen, Group *group) {
    assert(electronConfig != NULL && arrayLen > 0 && group != NULL);
    for (int iMl = group->absMl; iMl >= -group->absMl; --iMl) {
        for (short iMs = (short)(group->absMs * 2); (((float)iMs) / 2) >= -group->absMs; iMs -= 2) {
            short found = 0;
            for (unsigned int i = 0; i < arrayLen && !found; ++i) {
                if (electronConfig[i].ml == iMl && electronConfig[i].ms == (((float)iMs) / 2) && !(electronConfig[i].group)) {
                    electronConfig[i].group = group->id;
                    found = 1;
                }
            }
        }
    }
}

void printGroupsContent(Groups *groups) {
    assert(groups != NULL);
    for (unsigned short i = 0; i < groups->groupCount; i++) {
        printf("absMl: %hd, absMs: %4.1f, id: %hu\n", groups->group[i].absMl, groups->group[i].absMs, groups->group[i].id);
    }
}

Groups *constructGroups() {
    Groups *groups = malloc(sizeof(Groups));
    Group *groups_ptr = malloc(sizeof(Group));
    groups->group = groups_ptr;
    groups->groupCount = 1;
    return groups;
}

void freeGroup(Group *group) {
    assert(group != NULL);
}

void freeGroups(Groups *groups){
    assert(groups != NULL);
    for (int iGroup = 0; iGroup < groups->groupCount; ++iGroup) {
        freeGroup(&(groups->group[iGroup]));
    }
    free(groups->group);
}
short checkElementsGroup(ElectronConfig *electronConfig, unsigned int array_len) {
    assert(electronConfig != NULL && array_len > 0);
    short result = 1;
    for (int i = 0; i < array_len && result; ++i) {
        if (electronConfig[i].group == 0) {
            result = 0;
        }
    }
    return result;
}

void setGroups(ElectronConfig *electronConfig, unsigned int arrayLen, Groups *groups) {
    assert(electronConfig != NULL && arrayLen > 0 && groups != NULL);
    unsigned short groupIndex = 1;
    groups->group[groupIndex - 1].absMl = findMaxMlNoGroup(electronConfig, arrayLen);
    groups->group[groupIndex - 1].absMs = findMaxMsNoGroupWithMl(electronConfig, arrayLen, groups->group[groupIndex - 1].absMl);
    groups->group[groupIndex - 1].id = groupIndex;
    setGroup(electronConfig, arrayLen, &(groups->group[groupIndex - 1]));
    while (!checkElementsGroup(electronConfig, arrayLen)) {
        groupIndex += 1;
        if (appendGroup(groups)) {
            groups->group[groupIndex - 1].absMl = findMaxMlNoGroup(electronConfig, arrayLen);
            groups->group[groupIndex - 1].absMs = findMaxMsNoGroupWithMl(electronConfig, arrayLen, groups->group[groupIndex - 1].absMl);
            groups->group[groupIndex - 1].id = groupIndex;
            setGroup(electronConfig, arrayLen, &groups->group[groupIndex - 1]);
        } else {
            printf(ColorRed "An Error occurred while building the groups." TextReset);
            break;
        }
    }
}
