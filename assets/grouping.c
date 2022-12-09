/*
 * grouping file
 * contains the implementations of functions
 */

#include <stdlib.h>
#include <assert.h>

#include "grouping.h"


unsigned int findMaxMlNoGroup(ElectronConfig *electron_config, unsigned int array_len){
    assert(electron_config != NULL && array_len > 0);
    unsigned int max_ml_index = 0;
    for (unsigned int i = 0; i < array_len / 2; i++ ) {
        if (electron_config[i].ml < electron_config[array_len - i].ml) {
            if (electron_config[array_len - i].ml > electron_config[max_ml_index].ml) {
                max_ml_index = array_len - i;
            }
        } else {
            if (electron_config[i].ml > electron_config[max_ml_index].ml) {
                max_ml_index = i;
            }
        }
    }
    return max_ml_index;
}
