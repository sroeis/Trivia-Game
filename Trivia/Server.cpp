#include "Server.h"


Server::Server()
	:m_communicator(Communicator())
{
}

void Server::run()
{

	std::string input;


	std::thread t_connector(&Communicator::startHandleRequests, &m_communicator);
	t_connector.detach();

	try
	{
		while (true)
		{

			std::getline(std::cin, input);
			if (input == "EXIT")
				break;
		}
	}
	catch (...) {}

}


