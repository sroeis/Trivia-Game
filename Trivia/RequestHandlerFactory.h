#pragma once
//#include "IDataBase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "IRequestHandler.h"

class RequestHandlerFactory
{
public:
	LoginRequestHandler createLoginRequestHandler();
	LoginManager& getLoginManager();

	//MenuRequestHandler createMenuRequestHandler(LoggedUser user);
	//StatisticsManager& getStatisticsManager();
	//RoomManager& getRoomManager();

	//RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser user);
	//RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser user);

	//GameRequestHandler* createGameRequestHandler(LoggedUser user)
	//GameManager& getGameManager()

private:
	//IdataBase* m_dataBase;
	LoginManager m_loginManager;
	//RoomManager m_roomManager;
	//GameManager m_gameManager;
};
