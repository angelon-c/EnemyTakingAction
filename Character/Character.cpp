//
// Created by Victor Navarro on 13/02/24.
//
#include "Character.h"

#include "../Player/Player.h"
#include <algorithm>
#include <vector>
#include<iostream>
#include <cstring>
#include <cstdio>


Character::Character(const char * _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer) {
    strncpy(this->name,_name,20 );
    health = _health;
    attack = _attack;
    defense = _defense;
    speed = _speed;
    isPlayer = _isPlayer;
    maxHealth= _health;
    fleed = false;
    isDead = false;
}


void Character::setName(char const *_name) {
    strncpy(this->name, name, 20);

}

const char * Character::getName(){
    return name;
}

int Character::getLevel() {
    return level;
}

void Character::setHealth(int _health) {
    health = _health;
}

int Character::getHealth() {
    return health;
}

void Character::setAttack(int _attack) {
    attack = _attack;
}

int Character::getAttack() {
    return attack;
}

void Character::setDefense(int _defense) {
    defense = _defense;
}

int Character::getDefense() {
    return defense;
}

void Character::setSpeed(int _speed) {
    speed = _speed;
}

int Character::getSpeed() {
    return speed;
}

string Character::toString() {

    return "Name: " + string(name) + "\nHealth: " + to_string(health) + "\nAttack: " + to_string(attack) + "\nDefense: " + to_string(defense) + "\nSpeed: " + to_string(speed);


}

bool Character::getIsPlayer() {
    return isPlayer;
}

bool Character::compareSpeed(Character *a, Character *b) {
    return a->getSpeed() > b->getSpeed();
}
int Character::getmaxHealth() {
    return maxHealth;
}
bool Character::hasFleed() {
    return fleed;
}
bool Character::hasDied() {
    return isDead;
}







