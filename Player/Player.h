//
// Created by Victor Navarro on 13/02/24.
//

#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H

#include "../Character/Character.h"
#include "../Enemy/Enemy.h"
#include "../Combat/Action.h"

#include <vector>

class Enemy;

class Player: public Character {
public:
protected:
    int experience;

public:
    static const unsigned int BUFFER_SIZE = sizeof name + sizeof health + sizeof attack + sizeof defense + sizeof speed + sizeof experience + sizeof level;
    Player(const char * _name, int _health, int _attack, int _defense, int _speed);
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;
    Character* getTarget(vector<Enemy*> enemies);
    void emote();
    void levelUp();
    void gainExperience(int);
    void flee(vector<Enemy*> enemies);
    Action takeAction(vector<Enemy*> enemies);
    char* serialize();
    static Player* unserialize(char* buffer);
    int getExp();
private:
    char buffer[BUFFER_SIZE];
};


#endif //RPG_PLAYER_H
