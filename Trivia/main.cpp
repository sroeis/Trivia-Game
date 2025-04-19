#pragma comment (lib, "ws2_32.lib")

#include "Server.h"
#include "WSAInitializer.h"
#include "JsonResponsePacketSerializer.h"

int main()
{
	try
	{
		WSAInitializer wsaInit;
		Server myServer;

		myServer.run();
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	system("PAUSE");

	std::cout << "Returning from main at line " << __LINE__ << std::endl;
	return 0;
}
