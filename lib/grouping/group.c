//
// Created by luka on 20.02.23.
//

#include <assert.h>

#include "group.h"


short findMaxMlNoGroup(ElectronConfig *electronConfig) {
    assert(electronConfig != NULL);
    short maxMl = -32768;
    for (unsigned int i = 0; i < electronConfig->possibilities->countAll / 2; i++ ) {
        if (!electronConfig->eCArray[i].group) {
            if (!electronConfig->eCArray[electronConfig->possibilities->countAll - 1 - i].group) {
                if (electronConfig->eCArray[i].ml > electronConfig->eCArray[electronConfig->possibilities->countAll - 1 - i].ml) {
                    if (electronConfig->eCArray[i].ml > maxMl)
                        maxMl = electronConfig->eCArray[i].ml;
                } else {
                    if (electronConfig->eCArray[electronConfig->possibilities->countAll - 1 - i].ml > maxMl)
                        maxMl = electronConfig->eCArray[electronConfig->possibilities->countAll - 1 - i].ml;
                }
            } else {
                if (electronConfig->eCArray[i].ml > maxMl)
                    maxMl = electronConfig->eCArray[i].ml;
            }
        } else {
            if (!electronConfig->eCArray[electronConfig->possibilities->countAll - 1 - i].group &&
                electronConfig->eCArray[electronConfig->possibilities->countAll - 1 - i].ml > maxMl)
                maxMl = electronConfig->eCArray[electronConfig->possibilities->countAll - 1 - i].ml;
        }
        //if (!electronConfig->eCArray[i].group && electronConfig->eCArray[i].ml > maxMl) {
        //    maxMl = electronConfig->eCArray[i].ml;
        //}
    }
    return maxMl;
}

float findMaxMsNoGroupWithMl(ElectronConfig *electronConfig, short ml) {
    assert(electronConfig != NULL && electronConfig->possibilities->countAll > 0);
    float maxMs = 0;
    for (unsigned int i = 0; i < electronConfig->possibilities->countAll / 2; i++ ) {
        if (!electronConfig->eCArray[i].group && electronConfig->eCArray[i].ml == ml) {
            if (!electronConfig->eCArray[electronConfig->possibilities->countAll - 1 - i].group && electronConfig->eCArray[electronConfig->possibilities->countAll - 1 - i].ml == ml) {
                if (electronConfig->eCArray[i].ms > electronConfig->eCArray[electronConfig->possibilities->countAll - 1 - i].ms) {
                    if (electronConfig->eCArray[i].ms > maxMs) {
                        maxMs = electronConfig->eCArray[i].ms;
                    }
                } else {
                    if (electronConfig->eCArray[electronConfig->possibilities->countAll - 1 - i].ms > maxMs) {
                        maxMs = electronConfig->eCArray[electronConfig->possibilities->countAll - 1 - i].ms;
                    }
                }
            } else {
                if (electronConfig->eCArray[i].ms > maxMs) {
                    maxMs = electronConfig->eCArray[i].ms;
                }
            }
        } else {
            if (!electronConfig->eCArray[electronConfig->possibilities->countAll - 1 - i].group && electronConfig->eCArray[electronConfig->possibilities->countAll - 1 - i].ml == ml && electronConfig->eCArray[electronConfig->possibilities->countAll - 1 - i].ms > maxMs) {
                maxMs = electronConfig->eCArray[electronConfig->possibilities->countAll - 1 - i].ms;
            }
        }
        //if (!electronConfig->eCArray[i].group && electronConfig->eCArray[i].ml == ml && electronConfig->eCArray[i].ms > maxMs) {
        //    maxMs = electronConfig->eCArray[i].ms;
        //}
    }
    return maxMs;
}

void setGroup(ElectronConfig *electronConfig, Group *group) {
    assert(electronConfig != NULL && group != NULL);
    for (int iMl = group->absMl; iMl >= -group->absMl; --iMl) {
        for (short iMs = (short)(group->absMs * 2); (((float)iMs) / 2) >= -group->absMs; iMs -= 2) {
            short found = 0;
            for (unsigned int i = 0; i < electronConfig->possibilities->countAll / 2 && !found; ++i) {
                if (electronConfig->eCArray[i].ml == iMl && electronConfig->eCArray[i].ms == (((float)iMs) / 2) && !(electronConfig->eCArray[i].group)) {
                    electronConfig->eCArray[i].group = group->id;
                    found = 1;
                } else if (electronConfig->eCArray[electronConfig->possibilities->countAll - 1 - i].ml == iMl && electronConfig->eCArray[electronConfig->possibilities->countAll - 1 - i].ms == (((float)iMs) / 2) && !(electronConfig->eCArray[electronConfig->possibilities->countAll - 1 - i].group)) {
                    electronConfig->eCArray[electronConfig->possibilities->countAll - 1 - i].group = group->id;
                    found = 1;
                }
            }
        }
    }
}

void printGroupElements(ElectronConfig *electronConfig, unsigned int arrayLen, Group *group) {
    assert(electronConfig != NULL && arrayLen > 0 && group != NULL);
    for (int i = 0; i < arrayLen; ++i) {
        if (electronConfig->eCArray[i].group == group->id)
            printEConfigElement(&electronConfig->eCArray[i]);
    }
}
