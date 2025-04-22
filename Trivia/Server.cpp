#include "Server.h"


Server::Server(IDataBase* db) : m_database(db), m_handlerFactory(db), m_communicator(m_handlerFactory)
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


