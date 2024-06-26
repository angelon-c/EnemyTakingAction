//
// Created by Victor Navarro on 19/02/24.
//

#ifndef RPG_COMBAT_H
#define RPG_COMBAT_H
#pragma once
#include "../Character/Character.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "Action.h"
#include <vector>
#include <string>
#include <queue>

using namespace std;

class Combat {
private:
    vector<Character*> participants;
    vector<Player*> teamMembers;
    vector<Enemy*> enemies;
    priority_queue<Action> actions;
    int expAmount=0;
    bool lvlUp=false;

    void prepareCombat();
    Character* getTarget(Character* target);
    void registerActions();
    void executeActions();
    int getExpAmount(Character* enemy);
    void checkForLvlUp(Character* subscriber);


    void checkParticipantStatus(Character* participant);
    void checkForFlee(Character* character);
    bool eraseAction(Character* subscriber, Character* target);
public:
    Combat(vector<Character*> _participants);
    Combat(vector<Player*> _teamMembers, vector<Enemy*> _enemies);
    Combat();
    void addParticipant(Character *participant);
    void doCombat();
    string participantsToString();
};


#endif //RPG_COMBAT_H
