#include "Vector3.h"
#include "Item.h"
#include "GameState.h"

#include <string>
#include <map>

using std::map;

#ifndef CHARACTER_H
#define CHARACTER_H

class Character
{
private:
    std::string name_;

protected:
    Character(std::string name, Vector3 position, float 
        
        );

public:
    virtual ~Character();
    std::string getName();
    Vector3 position_;
    float direction_;
};

class Player : public Character
{
private:
    int hunger_;
    unsigned int health_;
    unsigned int gold_;

public:
    Player();
    Player(std::string name);
    virtual ~Player();
    void Walk(double dt);
    void CheckCollision(float newX, float newZ, bool& zMovement, bool& xMovement);
    void CheckInteraction();
	int footstepsound;

    int getHunger();
    unsigned int getHealth();
    unsigned int getGold();

    void setName();

    void setHunger(int hungee);
    void setHealth();
    void setGold(int moneh);
    void changeGold(int change);

    bool isDead();

    //movement
    float R_leg_rotation;
    float L_leg_rotation;

    //inventory
    int invselect;
    int inventory[8];
    int addItem(int itemID);
    int removeItem(int itemPos);
	void useItem(int itemID);
	void convertItem(int itemID1, int itemID2);
    int itemHave(int itemID);
	bool invfull();
	bool invfulldisplay;

    //Taking Damage
    bool iftakeDamage;
    void takeDamage();
};

class NPC : public Character
{
private:
    int loveMeter_;

public:
    int numberCompliments_;
    bool minigameComplete_;

    NPC(std::string name, const Vector3& pos, std::string textDirectory);
    virtual ~NPC();
    int getLoveMeter();
    void setLoveMeter(const int newLoveMeter);
    map<CONVO_STATE, std::string> dialogues;    //map for dialogues
    std::string Speech();
};

class Enemy : public Character
{
private:
    int e_damage_;
    unsigned int e_health_;

public:
    Enemy();
    Enemy(std::string name, const Vector3& pos);
    virtual ~Enemy();

    //Health Set and Get
    unsigned int getHealth();
    void setHealth(int health);
    void setDamage(int damage);

    //State of Enemy
    bool isDead();

    //Take Damage
    bool iftakeDamage;
    void takeDamage(int receiveddamage);

    float yaw;
};

#endif