 #include "Communicator.h"

void Communicator::startHandleRequests()
{
	bindAndListen();

	while (true)
	{
		SOCKET Client_socket = accept(m_serverSocket,NULL,NULL);
		if (Client_socket == INVALID_SOCKET) {
			throw std::exception(__FUNCTION__);
		}

		std::cout << "Client accepted." << std::endl;

		std::thread user_thread(&Communicator::handleNewClient, this, Client_socket);
		user_thread.detach();

		std::lock_guard<std::mutex> lock(mtx);
		LoginRequestHandler* Handler = new LoginRequestHandler();
		m_clients[Client_socket] = Handler;
	}
}

void Communicator::bindAndListen()
{

	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");

	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << PORT << std::endl;



}

void Communicator::handleNewClient(SOCKET clientSocket)
{
	const std::string helloMsg = "Hello";
	char buffer[1024] = { 0 };


	int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
	if (bytesReceived <= 0)
	{
		std::cerr << "Error receiving message from client socket " << clientSocket << std::endl;
		closesocket(clientSocket);
		return;
	}


	int sendResult = send(clientSocket, helloMsg.c_str(), helloMsg.size(), 0);
	if (sendResult == SOCKET_ERROR)
	{
		std::cerr << "Error sending message to client socket " << clientSocket << std::endl;
		closesocket(clientSocket);
		return;
	}



}
