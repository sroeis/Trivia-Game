#pragma once
#include <iostream>
#include <vector>
#include <time.h>

#define LOGIN_CODE 1
#define ERROR_CODE 3
#define SIGNUP_CODE 2


typedef std::vector<unsigned char> Buffer;

//structs
typedef struct LoginResponse
{
    unsigned int status;
}LoginResponse;

typedef struct SignupResponse
{
    unsigned int status;
}SignupResponse;

typedef struct ErrorResponse
{
    std::string message;
}ErrorResponse;

typedef struct LoginRequest
{
    std::string username;
    std::string password;
}LoginRequest;

typedef struct SignupRequest
{
    std::string username;
    std::string password;
    std::string email;
}SignupRequest;