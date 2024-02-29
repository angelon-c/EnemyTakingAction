//
// Created by Victor Navarro on 26/02/24.
//

#include "../Character/Character.h"
#ifndef RPG_ACTIONRESULT_H
#define RPG_ACTIONRESULT_H


class Character;

struct ActionResult {
    Character *target = nullptr;
    bool fleed = false;

    ActionResult(Character *_target, bool _fleed) {
        target = _target;
        fleed = _fleed;
    }
};

#endif //RPG_ACTIONRESULT_H
