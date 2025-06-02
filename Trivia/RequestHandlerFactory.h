#pragma once
//#include "IDataBase.h"
#include "LoginManager.h"
class LoginRequestHandler; // Forward declaration
#include "LoginRequestHandler.h"
class MenuRequestHandler; // Forward declaration
#include "MenuRequestHandler.h"

#include "RoomAdminRequestHandler.h" 
#include "RoomMemberRequestHandler.h" 

#include "IRequestHandler.h"
#include "SqliteDatabase.h"
#include "RoomManager.h"
#include "StatisticsManager.h"


class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDataBase* db);
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();

	MenuRequestHandler* createMenuRequestHandler(const LoggedUser& user);
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();

	RoomAdminRequestHandler* createRoomAdminRequestHandler(const LoggedUser& user, const Room& room);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(const LoggedUser& user, const Room& room);

	//GameRequestHandler* createGameRequestHandler(LoggedUser user)
	//GameManager& getGameManager()

private:
	LoginManager m_loginManager;
	IDataBase* m_dataBase;
	RoomManager m_roomManager;
	StatisticsManager m_statisticsManager;
	//GameManager m_gameManager;
};
