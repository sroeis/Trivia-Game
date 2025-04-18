#include <iostream>
#include <vector>
#include <time.h>
#include "IRequestHandler.h"

#define LOGIN_CODE 100
#define ERROR_CODE 400
#define SIGNUP_CODE 200


typedef std::vector<unsigned char> Buffer;

//structs
struct LoginResponse
{
	unsigned int status;
};

struct SignupResponse
{
	unsigned int status;
};

struct ErrorResponse
{
	std::string message;
};

struct LoginRequest
{
	std::string username;
	std::string password;
};

struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
};

struct Requestinfo
{
	unsigned char id;
	time_t receivalTime;
	Buffer buffer;
};

struct RequestResult
{
	Buffer response;
	IRequestHandler* newHandler;
};