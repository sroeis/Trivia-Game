#pragma once
#include "Responses.h"

class IRequestHandler;
typedef struct Requestinfo
{
    unsigned char id;
    time_t receivalTime;
    Buffer buffer;
}Requestinfo;

typedef struct RequestResult
{
    Buffer response;
    IRequestHandler* newHandler;
}RequestResult;

class IRequestHandler
{
public:
    virtual bool isRequestRelevant(Requestinfo request) = 0;
    virtual RequestResult handleRequest(Requestinfo request) = 0;
};