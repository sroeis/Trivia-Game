#pragma once
#include <iostream>
#include <vector>
#include <time.h>
#include "RoomData.h"
enum RequestCode {
    LOGIN_CODE = 1,
    SIGNUP_CODE,              
    ERROR_CODE,               
    LOGOUT_CODE,              
    GET_ROOMS_CODE,           
    JOIN_ROOM_CODE,           
    CREATE_ROOM_CODE,         
    GET_PLAYERS_IN_ROOM_CODE, 
    GET_HIGH_SCORE_CODE,      
    GET_PERSONAL_STATS_CODE,  
    CLOSE_ROOM_CODE,          
    START_GAME_CODE,          
    GET_ROOM_STATE_CODE,      
    LEAVE_ROOM_CODE           
};


#define STATUS_OK 200

using std::vector;
using std::string;

typedef std::vector<unsigned char> Buffer;

//structs


struct LogoutResponse {
    unsigned int status;
};

struct JoinRoomResponse {
    unsigned int status;
};

struct DeleteRoomResponse {
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

struct CloseRoomResponse
{
    unsigned int status;
};

struct StartGameResponse
{
    unsigned int status;
};

struct GetRoomStateResponse
{
    unsigned int status;
    bool hasGameBegun;
    vector<string> players;
    unsigned int questionCount;
    time_t answerTimeout;
};

typedef struct LeaveRoomResponse
{
    unsigned int status;
}LeaveRoomResponse;

typedef struct LeaveRoomRequest
{
    unsigned int roomId;
}LeaveRoomRequest;

typedef struct LoginRequest {
    std::string username;
    std::string password;
} LoginRequest;

typedef struct SignupRequest {
    std::string username;
    std::string password;
    std::string email;
} SignupRequest;

typedef struct GetPlayersInRoomRequest {
	unsigned int roomId;
} GetPlayersInRoomRequest;

typedef struct JoinRoomRequest {
    unsigned int roomId;
} JoinRoomRequest;

typedef struct DeleteRoomRequest {
    unsigned int roomId;
} DeleteRoomRequest;

typedef struct CreateRoomRequest {
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeOut;
} CreateRoomRequest;