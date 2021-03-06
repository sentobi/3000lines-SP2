/******************************************************************************/
/*!
\file	Bullet.h
\author 3000 Lines Studio
\brief
Bullet header file
*/
/******************************************************************************/

#include "Vector3.h"
#include "Character.h"

#ifndef BULLET_H 
#define BULLET_H 

/******************************************************************************/
/*!
Struct PlayerBullet:
\brief	Stores info on player's bullets
*/
/******************************************************************************/
struct PlayerBullet
{
    Vector3 p_bulletPos;        ///<Current bullet position (player)
    Vector3 p_bulletDir;        ///<Direction where bullet shoots from player
    float p_pitch, p_yaw;       ///<Rotation of Bullet
    bool p_ifCollide;           ///<Check if Bullet collide with enemy.
};

/******************************************************************************/
/*!
Struct EnemyBullet:
\brief	Stores info on enemy's bullet
*/
/******************************************************************************/
struct EnemyBullet
{
    Vector3 e_bulletPos;        ///<Current bullet position
    Vector3 e_bulletDir;        ///<Direction where bullet shoot
    float e_pitch, e_yaw;       ///<Rotation of Bullet
    float e_phi;                ///<Angle of Rotation of Bullet
    bool e_ifCollide;           ///<Check if Bullet Collides with player.
};

#endif /* BULLET_H */