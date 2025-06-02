#pragma once
#include <iostream>
#include <vector>
#include <time.h>
#include "RoomData.h"
#define LOGIN_CODE 1
#define SIGNUP_CODE 2
#define ERROR_CODE 3
#define LOGOUT_CODE 4
#define GET_ROOMS_CODE 5
#define JOIN_ROOM_CODE 6
#define CREATE_ROOM_CODE 7
#define GET_PLAYERS_IN_ROOM_CODE 8
#define GET_HIGH_SCORE_CODE 9
#define GET_PERSONAL_STATS_CODE 10
#define CLOSE_ROOM_CODE 11
#define START_GAME_ROOM_CODE 12
#define GET_ROOM_STATE_CODE 13
#define LEAVE_ROOM_CODE 14

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

struct LeaveRoomResponse
{
    unsigned int status;
};

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