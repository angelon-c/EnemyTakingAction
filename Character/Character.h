//
// Created by Victor Navarro on 13/02/24.
//

#ifndef RPG_CHARACTER_H
#define RPG_CHARACTER_H
#include<string>
#include <vector>

using namespace std;

class Character {
protected:
    char name[20]{};
    int health;
    int attack;
    int defense;
    int speed;
    bool isPlayer;
    int maxHealth;
    bool fleed;
    bool isDead;
    int level;
public:
    Character(const char *, int, int, int, int, bool);

    virtual void doAttack(Character *target) = 0;
    virtual void takeDamage(int damage) = 0;

    void setName(char const *);
    char const * getName();
    void setHealth(int);
    int getHealth();
    void setAttack(int);
    int getAttack();
    void setDefense(int);
    int getDefense();
    void setSpeed(int);
    int getSpeed();
    string toString();
    bool getIsPlayer();
    static bool compareSpeed(Character *a, Character *b);
    void setmaxHealth(int);
    int getmaxHealth();
    bool hasFleed();
    bool hasDied();
    int getLevel();


};


#endif //RPG_CHARACTER_H
