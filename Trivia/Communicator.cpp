 #include "Communicator.h"

#define CODE_POS 0
#define SIZE_LENGTH 4
#define MSG_START 5
#define HEADER_SIZE 5 //code + size
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
	char headerBuff[HEADER_SIZE] = { 0 }; //size + code
	unsigned int msgSize = 0;
	Requestinfo ri;
	
	RequestResult reqResult;

	int bytesReceived = recv(clientSocket, headerBuff, HEADER_SIZE, 0); //recive size and code
	ri.receivalTime = time(nullptr);

	// Code = 1 byte
	int reqCode = headerBuff[CODE_POS];
	// Size = 4 bytes
	std::memcpy(&msgSize, &headerBuff[CODE_POS], SIZE_LENGTH);
	// Make buffer with the correct size
	Buffer buffer(msgSize);

	// Receive the payload
	bytesReceived = recv(clientSocket, reinterpret_cast<char*>(buffer.data()), msgSize, MSG_WAITALL);

	// Complete RequestInfo
	ri.buffer = buffer;
	ri.id = reqCode;

	if (m_clients[clientSocket]->isRequestRelevant(ri))
	{
		reqResult = m_clients[clientSocket]->handleRequest(ri);
	}
	else
	{
		ErrorResponse err;
		err.message = "Error in request code.";
		throw err;
	}

	sendMsg(reqResult.response, clientSocket);
}

void Communicator::sendMsg(const Buffer& msg, SOCKET clientSocket)
{
	int sendResult = send(clientSocket, reinterpret_cast<const char*>(msg.data()), msg.size(), 0);
	if (sendResult == SOCKET_ERROR)
	{
		std::cerr << "Error sending message to client socket " << clientSocket << std::endl;
		closesocket(clientSocket);
		return;
	}
}