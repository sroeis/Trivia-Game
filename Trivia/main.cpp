#pragma comment (lib, "ws2_32.lib")

#include "Server.h"
#include "WSAInitializer.h"
#include "JsonResponsePacketSerializer.h"
#include "SqliteDatabase.h"

int main()
{
	try
	{
		WSAInitializer wsaInit;
		
		// Create and open database
		SqliteDatabase db;
		if (!db.open())
		{
			throw std::runtime_error("Failed to open database");
		}

		// Create server with database
		Server myServer(&db);
		myServer.run();

		// Close database
		if (!db.close())
		{
			std::cerr << "Warning: Failed to close database properly" << std::endl;
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Error occurred: " << e.what() << std::endl;
	}
	system("PAUSE");

	std::cout << "Returning from main at line " << __LINE__ << std::endl;
	return 0;
}
