//
// Created by Victor Navarro on 19/02/24.
//

#ifndef RPG_UTILS_H
#define RPG_UTILS_H
#include <cstdlib>

namespace combat_utils {
    int getRolledAttack(int attack) {
        srand(time(NULL));
        int lowerLimit = attack * .80;
        return (rand() % (attack - lowerLimit)) + lowerLimit;
    }
}


#endif //RPG_UTILS_H
