#pragma once

#include <vector>
#include <iostream>
#include <bitset>
#include "json.hpp"

#define LOGIN_CODE 100
#define ERROR_CODE 400
#define SIGNUP_CODE 200

//just to make typing it easier
using json = nlohmann::json;


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



class JsonResponsePacketSerializer  
{
public:
	Buffer serializeResponse(ErrorResponse Er); 
	Buffer serializeResponse(LoginResponse Lr);
	Buffer serializeResponse(SignupResponse Sr);

private:
	//turn the input string into a string holding the binary of the original
	std::string TurnToBinary(std::string Str);
	//get the data into the protocol format : Code - Size - Data
	Buffer PackIntoBuffer(int Code,std::string Str);

};

//macro from json.hpp that turn struct to json and the other way
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(LoginResponse, status)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SignupResponse, status)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ErrorResponse, message)
