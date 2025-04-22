#pragma once
#include <WinSock2.h>
#include <Windows.h>

#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <string>
#include "SqliteDatabase.h"
#include "Communicator.h"
#include "RequestHandlerFactory.h"


class Server
{
public:
	Server(IDataBase* db);
	void run();
private:
	IDataBase* m_database;
	RequestHandlerFactory m_handlerFactory;
	Communicator m_communicator;

	
};
