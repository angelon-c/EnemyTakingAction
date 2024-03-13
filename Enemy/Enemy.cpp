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

Enemy::Enemy(string name, int health, int attack, int defense, int speed) : Character(name, health, attack, defense, speed, false) {
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


/*Action Enemy::takeaction(vector<Player*> players) {
    Character* target = nullptr;
    bool fleed = false;
    if (getHealth()<0.15 * getmaxHealth()) {
        if (rand()% 100< 60) {
            vector <Character*> characters (players.begin(),players.end());
            fleed= flee(characters);
            if (fleed) {
                cout<<"Enemy has fleed"<<endl;
            }
            else {
                cout <<"Enemy tried to flee but failed"<<endl;
            }
        }
        else {
            target = getTarget(players);
            doAttack(target);
        }
    } else {
        target = getTarget(players);
        doAttack(target);
    }

    return ActionResult(target, fleed);
}*/
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





2