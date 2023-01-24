/*
 * grouping file
 * contains the implementations of functions
 */

#include <stdlib.h>
#include <assert.h>

#include "grouping.h"


short findMaxMlNoGroup(ElectronConfig *electron_config, unsigned int array_len) {
    assert(electron_config != NULL && array_len > 0);
    short max_ml = 0;
    for (unsigned int i = 0; i < array_len / 2; i++ ) {
        if (!electron_config[i].group && electron_config[i].ml > max_ml) {
            max_ml = electron_config[i].ml;
        }
        if (!electron_config[array_len - i - 1].group && electron_config[array_len - i - 1].ml > max_ml) {
            max_ml = electron_config[array_len - i - 1].ml;
        }
    }
    return max_ml;
}

short appendGroup(Groups *groups) {
    assert(groups != NULL && groups->group != NULL);
    Group *tmp_group = realloc(groups->group, sizeof(Group) * (groups->group_count + 1));
    if (tmp_group != NULL) {
        groups->group = tmp_group;
        groups->group_count++;
        return 1;
    } else {
        return 0;
    }
}

float findMaxMsNoGroupWithMl(ElectronConfig *electron_config, unsigned int array_len, short ml) {
    assert(electron_config != NULL && array_len > 0);
    float max_ms = 0;
    for (unsigned int i = 0; i < array_len / 2; i++ ) {
        if (!electron_config[i].group && electron_config[i].ml == ml && electron_config[i].ms > max_ms) {
            max_ms = electron_config[i].ms;
        }
        if (!electron_config[array_len - i - 1].group && electron_config[i].ml == ml && electron_config[array_len - i - 1].ms > max_ms) {
            max_ms = electron_config[array_len - i - 1].ms;
        }
    }
    return max_ms;
}

void setGroups(ElectronConfig *electron_config, unsigned int array_len, short ml, float ms, unsigned short group_id) {
    /*
     * how is the structure of the groups? are there any rules or predefined sizes??
     * construction of groups is difficult to make without any knowledge about the groups
     */
    for (short i_ms = (short)(-ms * 2); (((float)i_ms) / 2) <= ms; ++i_ms) {
        short found = 0;
        for (unsigned int i = 0; i < array_len && !found; ++i) {
            if (electron_config[i].ml == ml && electron_config[i].ms == ((float)i_ms / 2) && !(electron_config[i].group)) {
                electron_config[i].group = group_id;
                found = 1;
            }
        }
    }
}

void fillGroups(Groups *groups, short ml, float ms) {

}

void printGroups(Groups *groups) {
    for (unsigned short i = 0; i < groups->group_count; i++) {
        printf("abs_ml: %hu, abs_ms: %f, group_id: %hu", groups->group[i].abs_ml, groups->group[i].abs_ms, groups->group[i].group_id);
    }
}
