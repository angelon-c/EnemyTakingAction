//
// Created by Victor Navarro on 19/02/24.
//
#include "Combat.h"
#include <iostream>
#include <algorithm>

using namespace std;

bool compareSpeed(Character *a, Character *b) {
    return a->getSpeed() > b->getSpeed();
}

Combat::Combat(vector<Character *> _participants) {
    participants = std::move(_participants);
    for(auto participant: participants) {
        if(participant->getIsPlayer()) {
            teamMembers.push_back((Player*)participant);
        }
        else {
            enemies.push_back((Enemy*)participant);
        }
    }
}

Combat::Combat(vector<Player*> _teamMembers, vector<Enemy*> _enemies) {
    teamMembers = std::move(_teamMembers);
    enemies = std::move(_enemies);
}

Combat::Combat() {
    participants = vector<Character*>();
}

void Combat::addParticipant(Character *participant) {
    participants.push_back(participant);
    if(participant->getIsPlayer()) {
        teamMembers.push_back((Player*)participant);
    }
    else {
        enemies.push_back((Enemy*)participant);
    }
}


void Combat::prepareCombat() {
    sort(participants.begin(), participants.end(), compareSpeed);
}



string Combat::participantsToString() {
    string result = "";
    for (int i = 0; i < participants.size(); i++) {
        result += participants[i]->toString() + "\n";
    }
    return result;
}

void Combat::doCombat() {
    prepareCombat();

    //Este while es 1 iteracion por ronda
    while(enemies.size() != 0 && teamMembers.size() != 0) {
        registerActions();
        executeActions();
    }

    //No se imprime el nombre del ganador
    if(enemies.size() == 0) {
        cout<<"You have won the combat"<<endl;
    }
    else {
        cout<<"The enemies have won the combat - Game Over"<<endl;
    }
}

void Combat::registerActions() {
    vector<Character*>::iterator participant = participants.begin();
    //Una iteracion por turno de cada participante (player y enemigo)
    while(participant != participants.end()) {
        Character* target = nullptr;
        Action currentAction;
        if((*participant)->getIsPlayer()) {
            currentAction = ((Player*)*participant)->takeAction(enemies);
        }
        else {
            currentAction = ((Enemy*)*participant)->takeAction(teamMembers);
        }
        actions.push(currentAction);
        participant++;
    }
}

void Combat::executeActions() {
    //Aqui se ejecutan las acciones
    while(!actions.empty()) {
        Action currentAction = actions.top();
        if(eraseAction(currentAction.subscriber, currentAction.target)) {
            actions.pop();
            continue;
        }
        currentAction.action();
        checkForFlee(currentAction.subscriber);

        checkParticipantStatus(currentAction.subscriber);
        checkParticipantStatus(currentAction.target);
        checkForLvlUp(currentAction.subscriber);

        actions.pop();
    }
}

void Combat::checkParticipantStatus(Character* participant) {


    if (participant== nullptr) {
        return;
    }
    if(participant->getHealth() <= 0) {
        if(participant->getIsPlayer()) {
            teamMembers.erase(remove(teamMembers.begin(), teamMembers.end(), participant), teamMembers.end());
        }
        else {
            expAmount = getExpAmount(participant);
            enemies.erase(remove(enemies.begin(), enemies.end(), participant), enemies.end());
        }
        participants.erase(remove(participants.begin(), participants.end(), participant), participants.end());
    }
}

void Combat::checkForFlee(Character *character) {
    bool fleed = character->hasFleed();
    if(fleed) {
        if(character->getIsPlayer()) {
            cout<<"You have fled the combat"<<endl;
            teamMembers.erase(remove(teamMembers.begin(), teamMembers.end(), character), teamMembers.end());

            character->hasDied();
        }
        else {
            cout<<character->getName()<<" has fled the combat"<<endl;
            enemies.erase(remove(enemies.begin(), enemies.end(), character), enemies.end());
            character->hasDied();
        }
        participants.erase(remove(participants.begin(), participants.end(), character), participants.end());
    }
}
bool Combat::eraseAction(Character* subscriber, Character* target){
    bool result = false;
    bool targetFound = false;
    bool subsciberFound = false;
    if(target == nullptr) targetFound = true;
    if(subscriber == nullptr) targetFound = true;

    for (int i = 0; i < participants.size(); ++i) {
        if(target==participants[i]) {
            targetFound = true;
        }
        if(subscriber==participants[i]) {
            subsciberFound = true;
        }
    }
    result = !(targetFound && subsciberFound);
    return result;
}


int Combat::getExpAmount(Character * enemy) {
    int experience = 0;
    if(enemy->getLevel()>0 && enemy->getLevel()<=2){
        experience = 10;
    }
    else if(enemy->getLevel()>2 && enemy->getLevel()<=4){
        experience = 20;
    }
    else if(enemy->getLevel()>4 && enemy->getLevel() <= 6){
        experience = 40;
    }
    else if(enemy->getLevel()>6 && enemy->getLevel()<=8){
        experience = 80;
    }
    else if(enemy->getLevel()>8 && enemy->getLevel()<=10){
        experience = 120;
    }
    return experience;
}

void Combat::checkForLvlUp(Character *subscriber) {
    if(subscriber->getIsPlayer()){
        for(Player* player:teamMembers)
        {
            player->gainExperience(expAmount);
            if(player->getExp()>=100){
                player->levelUp();
                lvlUp = true;
            }
        }
        expAmount = 0;
        if(lvlUp){
            for(Enemy* enemy:enemies){
                enemy->levelUp();
            }
        }
        lvlUp = false;
    }
    else{
        return;
    }
}