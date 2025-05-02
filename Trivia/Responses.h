#pragma once
#include <iostream>
#include <vector>
#include <time.h>

#define LOGIN_CODE 1
#define SIGNUP_CODE 2
#define ERROR_CODE 3
#define LOGOUT_CODE 4

typedef std::vector<unsigned char> Buffer;

//structs
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

struct LogoutResponse {
    unsigned int status;
};

struct JoinRoomResponse {
    unsigned int status;
};

struct GetRoomsResponse {
    unsigned int status;
   std::vector<RoomData> rooms;
};

struct CreateRoomResponse {
    unsigned int status;
};

struct GetPlayersInRoomResponse {
    std::vector<std::string> players;
};

struct GetHighScoreResponse {
    unsigned int status;
    std::vector<std::string> statistics;
};

struct GetPersonalStatsResponse {
    unsigned int status;
    std::vector<std::string> statistics;
};

typedef struct LoginResponse {
    unsigned int status;
} LoginResponse;

typedef struct SignupResponse {
    unsigned int status;
} SignupResponse;

typedef struct ErrorResponse {
    std::string message;
} ErrorResponse;

typedef struct LoginRequest {
    std::string username;
    std::string password;
} LoginRequest;

typedef struct SignupRequest {
    std::string username;
    std::string password;
    std::string email;
} SignupRequest;