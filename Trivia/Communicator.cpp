 #include "Communicator.h"

#define CODE_POS 0
#define SIZE_START 1 
#define SIZE_END 5
#define MSG_START 5

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
	char bitBuff[1024] = { 0 };
	int bytesReceived = recv(clientSocket, bitBuff, sizeof(bitBuff), 0);
	Requestinfo ri; 
	ri.receivalTime = time(nullptr);
	RequestResult reqResult;

	int reqCode = getCode(bitBuff);

	ri.id = reqCode;


	size_t length = std::strlen(bitBuff);  // Get the length of the buffer
	Buffer bitBuffer(bitBuff, bitBuff + length);

	ri.buffer = bitBuffer;

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

int Communicator::getCode (const char bits[])
{
	int result = 0;
	for (int i = 0; i < 8; ++i) 
	{
		result = (result << 1) | (bits[i] - '0');
	}
	return result;
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