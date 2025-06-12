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
    LEAVE_ROOM_CODE,
	LEAVE_GAME_CODE,
    GET_QUESTION_CODE,
	SUBMIT_ANSWER_CODE,
	GET_GAME_RESULTS_CODE,
    
};


#define STATUS_OK 200

using std::vector;
using std::string;
using std::map;

typedef vector<unsigned char> Buffer;

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
   vector<RoomData> rooms;
};

struct CreateRoomResponse {
    unsigned int status;
};

struct GetPlayersInRoomResponse {
   vector<string> players;
};

struct GetHighScoreResponse {
    unsigned int status;
    vector<string> statistics;
};

struct GetPersonalStatsResponse {
    unsigned int status;
    vector<string> statistics;
};

typedef struct LoginResponse {
    unsigned int status;
} LoginResponse;

typedef struct SignupResponse {
    unsigned int status;
} SignupResponse;

typedef struct ErrorResponse {
    string message;
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
    string username;
    string password;
} LoginRequest;

typedef struct SignupRequest {
    string username;
    string password;
    string email;
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
	string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeOut;
} CreateRoomRequest;

struct LeaveGameResponse
{
    unsigned int status;
};

struct GetQuestionResponse {
    unsigned int status;
    string question;
    map<unsigned int, string> answers;
};

struct SubmitAnswerResponse {
    unsigned int status;
    unsigned int correctAnswerId;
};

struct PlayerResults {
    string username;
    unsigned int correctAnswerCount;
    unsigned int wrongAnswerCount;
    unsigned int averageAnswerTime;
};

struct GetGameResultsResponse {
    unsigned int status;
    vector<PlayerResults> results;
};

struct SubmitAnswerRequest
{
    unsigned int answerId;
};

