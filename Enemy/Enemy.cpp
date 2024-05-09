//
// Created by Victor Navarro on 13/02/24.
//
#include "Enemy.h"

#include <climits>
#include <iostream>
#include <vector>


using namespace std;

//TODO: Check the circular dependency
int getRolledAttack(int attack) {
    int lowerLimit = attack * .80;
    return (rand() % (attack - lowerLimit)) + lowerLimit;
}

Enemy::Enemy(const char *name, int health, int attack, int defense, int speed,int _level) : Character(name, health, attack, defense, speed, false) {
    level=_level;
}


void Enemy::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
}

void Enemy::takeDamage(int damage) {
    setHealth(getHealth() - damage);
    if(getHealth() <= 0) {
        cout<<getName()<<" has died"<<endl;
    }
    else {
        cout<<getName()<<" has taken " << damage << " damage" << endl;
    }
}

Character* Enemy::getTarget(vector<Player *> teamMembers) {
    // Obtiene el miembro del equipo con menos vida
    int targetIndex = 0;
    int lowestHealth = INT_MAX;
    for(int i=0; i < teamMembers.size(); i++) {
        if(teamMembers[i]->getHealth() < lowestHealth) {
            lowestHealth = teamMembers[i]->getHealth();
            targetIndex = i;
        }
    }

    return teamMembers[targetIndex];
}

void Enemy::flee(vector<Player*> players) {
    std::sort(players.begin(), players.end(), compareSpeed);
    Player *fastestPlayer = players[0];
    bool fleed = false;
    if (this->getSpeed()>fastestPlayer->getSpeed()) {
        fleed = true;
    }
    else{
        srand(time(NULL));
        int chance = rand()%100;
        cout << "chance: " << chance << endl;fleed - chance >99;
        fleed = chance > 99;
    }
    this->fleed = fleed;
}

Action Enemy::takeAction(vector<Player *> player) {
    Action myAction;
    myAction.speed = getSpeed();
    myAction.subscriber = this;
    Character* target = getTarget(player);
    myAction.target = target;
    //myAction.action = [this, target]() {
      //  doAttack(target);
    if(getHealth()<0.15*getmaxHealth())
    {
        if(rand()%100<5)
        {
            myAction.action = [this, player]() {
                flee(player);
            };
        }
        else
        {
            myAction.action = [this, target]() {
                doAttack(target);
            };
        }
    }
    else
    {
        myAction.action = [this, target]() {
            doAttack(target);
        };
    }

    return myAction;
}

void Enemy::levelUp() {
    level++;
    int counter = 3;
    size_t options;
    while(counter != 0){

        options =rand()%3;

        switch (options) {

            case 0:
                health += 2;
                cout<<"Enemy Incrased it's health by 2 points"<<endl;
                break;
            case 1:
                attack += 2;
                cout<<"Enemy Increased it's attack by 2 points"<<endl;
                break;
            case 2:
                defense += 2;
                cout<<"Enemy Increased it's defense by 2 points"<<endl;
                break;
            case 3:
                speed += 2;
                cout<<"Enemy Incrased it's speed by 2 points"<<endl;
                break;
            default:
                cout << options << " Is not an option" << endl;
                break;
        }
        counter--;
    }
    cout<<"Enemies got stronger!"<<endl;
}




