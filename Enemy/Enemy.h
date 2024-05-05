//
// Created by Victor Navarro on 13/02/24.
//

#ifndef RPG_ENEMY_H
#define RPG_ENEMY_H
#include "../Combat/Action.h"
#include "../Character/Character.h"
#include "../Player/Player.h"
#include <vector>

class Player;

class Enemy: public Character {
public:
    Enemy(const char *, int, int, int, int, int);
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;
    Character* getTarget(vector<Player*> teamMembers);
    Action takeAction(vector<Player*> player);
    void flee(vector<Player*> players);
    bool hasFleed();
};


#endif //RPG_ENEMY_H
