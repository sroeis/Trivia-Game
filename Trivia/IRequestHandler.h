#pragma once
#include "Responses.h"

class IRequestHandler;
typedef struct RequestInfo
{
    unsigned char id;
    time_t receivalTime;
    Buffer buffer;
}RequestInfo;

typedef struct RequestResult
{
    Buffer response;
    IRequestHandler* newHandler;
}RequestResult;

class IRequestHandler
{
public:
    virtual bool isRequestRelevant(const RequestInfo& request) = 0;
    virtual const RequestResult handleRequest(const RequestInfo& request) = 0;
};