#ifndef GAMESTATE_H
#define GAMESTATE_H


enum GAME_STATE
{
    GAME_STATE_FREE = 0,
    GAME_STATE_SHOP,
    GAME_STATE_WSGAME,
    GAME_STATE_CHONGAME,
    GAME_STATE_VEEGAME,
    GAME_STATE_PAUSED,
    GAME_STATE_RABBIT,

    GAME_STATE_TOTAL,
};

enum LOCATION
{
    OUTSIDE,    //0
    HANGAR,     //1
    CORRIDOR,   //2
    SHOP,       //3
    LABORATORY, //4
    CONTROLROOM,    //5
    CANTEEN,    //6
    TOILET,     //7
    ROOM1,      //8
    ROOM2,      //9
    ROOM3,      //10
    ROOM4,      //11

    LOCATION_TOTAL
};

//GAME_STATE gamestate;

#endif /* GAMESTATE_H */