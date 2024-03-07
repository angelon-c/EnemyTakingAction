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

void Combat::doCombat() {
    prepareCombat();

    while(enemies.size() != 0 && teamMembers.size() != 0) {
        vector<Character*>::iterator participant = participants.begin();

        while(participant != participants.end()) {
            Character* target = nullptr;
            if((*participant)->getIsPlayer()){
                ActionResult playerAction = ((Player*)*participant)->takeAction(enemies);
                if(playerAction.target && playerAction.target->getHealth() <= 0) {
                    participant = participants.erase(remove(participants.begin(), participants.end(), playerAction.target), participants.end());
                    enemies.erase(remove(enemies.begin(), enemies.end(), playerAction.target), enemies.end());
                } else if (playerAction.fleed) {
                    teamMembers.erase(remove(teamMembers.begin(), teamMembers.end(), ((Player*)*participant)), teamMembers.end());
                    participant = participants.erase(remove(participants.begin(), participants.end(), ((Player*)*participant)), participants.end());

                    if (teamMembers.size() == 0) {
                        break;
                    }
                } else {
                    participant++;
                }
            }
            else {

                ActionResult enemyAction = ((Enemy*)*participant)->takeaction(teamMembers);
                if (enemyAction.target && enemyAction.target->getHealth() <= 0) {
                    if (enemyAction.target->getIsPlayer()) {
                        participant = participants.erase(remove(participants.begin(), participants.end(), enemyAction.target), participants.end());
                        teamMembers.erase(remove(teamMembers.begin(), teamMembers.end(), enemyAction.target), teamMembers.end());

                    }
                    else {
                        participant = participants.erase(remove(participants.begin(), participants.end(), enemyAction.target), participants.end());
                        enemies.erase(remove(enemies.begin(), enemies.end(), enemyAction.target), enemies.end());
                    }
                } else if (enemyAction.fleed) {
                    participant = participants.erase(remove(participants.begin(), participants.end(), ((Enemy*)*participant)), participants.end());
                    enemies.erase(remove(enemies.begin(), enemies.end(), ((Enemy*)*participant)), enemies.end());
                } else {
                    participant++;
                }


            }

        }
    }

    //No se imprime el nombre del ganador
    if(enemies.size() == 0) {
        cout<<"You have won the combat"<<endl;
    }
    else {
        cout<<"The enemies have won the combat - Game Over"<<endl;
    }
}

string Combat::participantsToString() {
    string result = "";
    for (int i = 0; i < participants.size(); i++) {
        result += participants[i]->toString() + "\n";
    }
    return result;
}