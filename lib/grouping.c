/*
 * grouping file
 * contains the implementations of functions
 */

#include <stdlib.h>
#include <assert.h>

#include "grouping.h"


short appendGroup(Groups *groups) {
    assert(groups != NULL && groups->group != NULL);
    Group *tmp_group = realloc(groups->group, sizeof(Group) * (groups->groupCount + 1));
    if (tmp_group != NULL) {
        groups->group = tmp_group;
        groups->groupCount++;
        return 1;
    } else {
        return 0;
    }
}

unsigned short findMaxMlNoGroup(ElectronConfig *electronConfig, unsigned int arrayLen) {
    assert(electronConfig != NULL && arrayLen > 0);
    unsigned short max_ml = 0;
    for (unsigned int i = 0; i < arrayLen / 2; i++ ) {
        if (!electronConfig[i].group && electronConfig[i].ml > max_ml) {
            max_ml = electronConfig[i].ml;
        }
        if (!electronConfig[arrayLen - i - 1].group && electronConfig[arrayLen - i - 1].ml > max_ml) {
            max_ml = electronConfig[arrayLen - i - 1].ml;
        }
    }
    return max_ml;
}

float findMaxMsNoGroupWithMl(ElectronConfig *electronConfig, unsigned int arrayLen, unsigned short ml) {
    assert(electronConfig != NULL && arrayLen > 0);
    float max_ms = 0;
    for (unsigned int i = 0; i < arrayLen / 2; i++ ) {
        if (!electronConfig[i].group && electronConfig[i].ml == ml && electronConfig[i].ms > max_ms) {
            max_ms = electronConfig[i].ms;
        }
        if (!electronConfig[arrayLen - i - 1].group && electronConfig[i].ml == ml && electronConfig[arrayLen - i - 1].ms > max_ms) {
            max_ms = electronConfig[arrayLen - i - 1].ms;
        }
    }
    return max_ms;
}

int groupElementCount(float ms) {
    return (int)ms * 2 + 1;
}

void setGroup(ElectronConfig *electron_config, unsigned int array_len, Group *group) {
    group->elements = malloc(sizeof(unsigned int) * groupElementCount(group->absMs));
    for (short i_ms = (short)(-group->absMs * 2); (((float)i_ms) / 2) <= group->absMs; ++i_ms) {
        unsigned short groupElementIndex = 0;
        short found = 0;
        for (unsigned int i = 0; i < array_len && !found; ++i) {
            if (electron_config[i].ml == group->absMl && electron_config[i].ms == ((float)i_ms / 2) && !(electron_config[i].group)) {
                electron_config[i].group = group->id;
                group->elements[groupElementIndex++] = i;
                found = 1;
            }
        }
    }
}

void printGroupsContent(Groups *groups) {
    for (unsigned short i = 0; i < groups->groupCount; i++) {
        printf("absMl: %hu, absMs: %4.1f, id: %hu\n", groups->group[i].absMl, groups->group[i].absMs, groups->group[i].id);
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
    free(group->elements);
}

void freeGroups(Groups *groups){
    for (int iGroup = 0; iGroup < groups->groupCount; ++iGroup) {
        freeGroup(&(groups->group[iGroup]));
    }
    free(groups->group);
}

unsigned int sumGroupElements(Groups *groups) {
    return 0;
}

void setGroups(ElectronConfig *electron_config, unsigned int array_len, Groups *groups) {
    groups->group[0].absMl = findMaxMlNoGroup(electron_config, array_len);
    groups->group[0].absMs = findMaxMsNoGroupWithMl(electron_config, array_len, groups->group[0].absMl);
    groups->group[0].id = 1;
    setGroup(electron_config, array_len, &(groups->group[0]));
}
