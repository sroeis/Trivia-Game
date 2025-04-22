#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"

#include <stdlib.h>
#include <fstream>

#include <exception>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <map>
#include<ctime>

#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

#include "RequestHandlerFactory.h"
#define PORT 6969


class Communicator
{

public:
	Communicator(RequestHandlerFactory handler);
	void startHandleRequests();

private:
	void bindAndListen();
	void handleNewClient(SOCKET clientSocket);
	void sendMsg(const Buffer& msg, SOCKET clientSocket);

	RequestHandlerFactory m_handlerFactory;
	SOCKET m_serverSocket;
	std::mutex mtx;
	std::map<SOCKET, IRequestHandler*> m_clients;

};



