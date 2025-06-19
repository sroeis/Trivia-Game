#pragma once
//#include "IDataBase.h"
#include "LoginManager.h"
class LoginRequestHandler; // Forward declaration
#include "LoginRequestHandler.h"
class MenuRequestHandler; // Forward declaration
#include "MenuRequestHandler.h"
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;
#include "GameRequestHandler.h"
#include "GameManager.h"
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

	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser& user,Room& room);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser& user,Room& room);

	GameRequestHandler* createGameRequestHandler(const LoggedUser& user);
	GameManager& getGameManager();

private:
	LoginManager m_loginManager;
	IDataBase* m_dataBase;
	RoomManager m_roomManager;
	StatisticsManager m_statisticsManager;
	GameManager m_gameManager;
};
