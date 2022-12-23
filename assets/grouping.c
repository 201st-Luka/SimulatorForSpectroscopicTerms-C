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

float findMaxMsNoGroupWithMl(ElectronConfig *electron_config, unsigned int array_len, unsigned int ml) {
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
