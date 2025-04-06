#pragma comment (lib, "ws2_32.lib")

#include "Server.h"
#include "WSAInitializer.h"

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

	return 0;
}
