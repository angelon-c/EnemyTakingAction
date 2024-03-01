//
// Created by Victor Navarro on 13/02/24.
//
#include "Player.h"
#include <iostream>
#include "../Utils.h"
#include <algorithm>
using namespace std;
using namespace combat_utils;



Player::Player(string name, int health, int attack, int defense, int speed) : Character(name, health, attack, defense, speed, true) {
    experience = 0;
    level = 1;
}

void Player::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
}

void Player::takeDamage(int damage) {
    setHealth(health - damage);

    if(health <= 0) {
        cout<<"You have died"<<endl;
    }
    else {
        cout<<"You have taken " << damage << " damage" << endl;
    }
}

void Player::emote() {
    cout<<"Jokes on you" << endl;
}

void Player::levelUp() {
    level++;
    setHealth(getHealth() + 10);
    setAttack(getAttack() + 5);
    setDefense(getDefense() + 5);
    setSpeed(getSpeed() + 5);
}

void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        levelUp();
        experience = 0;
    }
}

Character* Player::getTarget(vector<Enemy *> enemies) {
    cout << "Choose a target" << endl;
    int targetIndex = 0;
    for(int i = 0; i < enemies.size(); i++) {
        cout << i << ". " << enemies[i]->getName() << endl;
    }
    cin >> targetIndex;
    //TODO: Add input validation
    return enemies[targetIndex];
}

ActionResult Player::takeAction(vector<Enemy*>enemies) {
    int option = 0;
    cout<<"Choose an action"<<endl;
    cout<<"1. Attack"<<endl;
    cout<<"2. Flee"<<endl;
    cin >> option;
    Character* target = nullptr;
    bool fleed = false;
    switch(option) {
        case 1:
            target = getTarget(enemies);
            doAttack(target);
            break;
        case 2: {
            vector <Character*> characters (enemies.begin(),enemies.end());
            fleed = flee(characters);
            if(fleed) {
                cout<<"You have fled"<<endl;
            }
            else {
                cout<<"You couldn't flee"<<endl;
            }
            break;
        }
        default:
            cout<<"Invalid option"<<endl;
            break;
    }

    return ActionResult(target, fleed);
}