//
// Created by Victor Navarro on 13/02/24.
//
#include "Player.h"
#include <iostream>
#include "../Utils.h"
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;
using namespace combat_utils;



Player::Player(const char * name, int health, int attack, int defense, int speed) : Character(name, health, attack, defense, speed, true) {
    level = 0;
    experience = 0;
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
    experience-=100;
    int counter = 3;
    size_t options;
    cout<<"Congratulations on leveling up you can choose up to 3 attributes do upgdrade with 2 points each" << endl;
   while(counter != 0){
       if (counter==3){
           cout<<"Pick your first attribute to upgrade"<<endl;
       }
       else if(counter==2){
           cout<<"Pick your next attribute to upgrade"<<endl;
       }
       else{
           cout<<"Pick your last attribute to upgrade"<<endl;
       }

       cout<<"1. Health\n2. Attack\n3. Defense\n4. speed"<<endl;
    cin >> options;

       switch (options) {

           case 1:
               health += 2;
               break;
           case 2:
               attack += 2;
               break;
           case 3:
               defense += 2;
               break;
           case 4:
               speed += 2;
               break;
           default:
               cout << options << " Is not an option" << endl;
               break;
       }
    counter--;
   }
}

void Player::gainExperience(int exp) {
    experience += exp;

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

void Player::flee(vector<Enemy *> enemies) {
    std::sort(enemies.begin(), enemies.end(), compareSpeed);
    Enemy *fastestEnemy = enemies[0];
    bool fleed = false;
    if (this->getSpeed() > fastestEnemy->getSpeed()) {
        fleed = true;
    } else {
        srand(time(NULL));
        int chance = rand() % 100;
        cout << "chance: " << chance << endl;
        fleed = chance > 99;
    }

    this->fleed = fleed;
}


Action Player::takeAction(vector<Enemy *> enemies) {
    int option = 0;
    if(experience>=100)
        levelUp();

    cout << "Choose an action" << endl;
    cout << "1. Attack" << endl;
    cout << "2. Flee" << endl;
    cin >> option;
    Character *target = nullptr;

    //Esta variable guarda
    //1. Que voy a hacer?
    //2. Con que velocidad/prioridad?
    Action myAction;
    //2.
    myAction.speed = this->getSpeed();
    myAction.subscriber = this;

    switch (option) {
        case 1:
            target = getTarget(enemies);
            myAction.target = target;
            //1.
            myAction.action = [this, target]() {
                doAttack(target);
                if(target->getHealth()<=0){
                    gainExperience(getExperienceAmount(target->getLevel()));

                }
            };
            break;
        case 2:

            myAction.action = [this, enemies]() {
                flee(enemies);

            };
            break;
        default:
            cout << "Invalid option" << endl;
            break;
    }

    return myAction;
}
char* Player::serialize(){
    char* iterator = buffer;
    memcpy(iterator,name, sizeof name);
    iterator +=sizeof name;

    memcpy(iterator,&health,sizeof health);
    iterator+=sizeof  health;

    memcpy(iterator,&attack,sizeof attack);
    iterator+=sizeof  attack;

    memcpy(iterator,&defense,sizeof defense);
    iterator+=sizeof  defense;

    memcpy(iterator,&speed,sizeof speed);
    iterator+=sizeof  speed;

    memcpy(iterator,&isPlayer,sizeof isPlayer);
    iterator+=sizeof  isPlayer;

    memcpy(iterator,&level,sizeof level);
    iterator+=sizeof  level;

    memcpy(iterator,&experience,sizeof experience);
    iterator+=sizeof  experience;


}

Player* Player::unserialize(char *_buffer) {
    char* iterator = _buffer;
    char _name[30];
    int _health;
    int _attack;
    int _defense;
    int _speed;
    bool _isPlayer;
    int _experience;
    int _level;

    memcpy(_name,iterator, sizeof _name);
    iterator += sizeof _name;

    memcpy(&_health,iterator, sizeof _health);
    iterator += sizeof _health;

    memcpy(&_attack,iterator, sizeof _attack);
    iterator += sizeof _attack;

    memcpy(&_defense,iterator, sizeof _defense);
    iterator += sizeof _defense;

    memcpy(&_speed,iterator, sizeof _speed);
    iterator += sizeof _speed;

    memcpy(&_isPlayer,iterator, sizeof _isPlayer);
    iterator += sizeof _name;

    memcpy(&_experience,iterator, sizeof _experience);
    iterator += sizeof _experience;

    memcpy(&_level,iterator, sizeof _level);
    iterator += sizeof _level;

}

int Player::getExperienceAmount(int level) {
    int experience = 0;
    if(level>0 && level<=2){
        experience = 10;
    }
    else if(level>2 && level<=4){
        experience = 20;
    }
    else if(level>4 && level <= 6){
        experience = 40;
    }
    else if(level>6 && level<=8){
        experience = 80;
    }
    else if(level>8 && level<=10){
        experience = 120;
    }
    return experience;
}
