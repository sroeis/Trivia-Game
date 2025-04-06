#pragma once
#include <WinSock2.h>
#include <Windows.h>

#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <string>

#include "Communicator.h"


class Server
{
public:
	Server();
	void run();
private:
	Communicator m_communicator;
};
