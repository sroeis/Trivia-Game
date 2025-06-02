#pragma once
#include <string>

#define GAME_STARTED 1
#define GAME_NOT_STARTED 0

typedef struct RoomData
{
    unsigned int id;
    std::string name;
    unsigned int maxPlayers;
    unsigned int numOfQuestionsInGame;
    unsigned int timePerQuestion;
    //RoomStatus status; 
    //idk what they meant by this so i did this 
    unsigned int status;
}RoomData;