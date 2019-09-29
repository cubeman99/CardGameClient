#include "NetworkManager.h"
#include <sstream>
#include "ClientApp.h"


NetworkManager::NetworkManager()
{
}

NetworkManager::~NetworkManager()
{
	if (m_connected)
	{
		int result = shutdown(m_socket, SD_SEND);
		
		if (result == SOCKET_ERROR)
		{
			printf("shutdown failed: %d\n", WSAGetLastError());
		}

		closesocket(m_socket);
		WSACleanup();

		m_socket = INVALID_SOCKET;
	}
}

bool NetworkManager::Connect(const std::string& address, int port, ReceiveCallback* callback)
{
	std::string portString = std::to_string(port);
	m_callback = callback;

	struct addrinfo *result = NULL;
	struct addrinfo *ptr = NULL;
	struct addrinfo hints;
	
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family		= AF_INET;
	hints.ai_socktype	= SOCK_STREAM;
	hints.ai_protocol	= IPPROTO_TCP;

	int iResult;
	WSADATA wsaData;
	
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return false;
	}

	// Resolve the server address and port
	iResult = getaddrinfo(address.c_str(),
		portString.c_str(), &hints, &result);
	if (iResult != 0)
	{
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return false;
	}
	
	m_socket = INVALID_SOCKET;

	// Attempt to connect to the first address returned by
	// the call to getaddrinfo
	ptr = result;

	// Create a SOCKET for connecting to server
	m_socket = socket(ptr->ai_family, ptr->ai_socktype, 
		ptr->ai_protocol);

	if (m_socket == INVALID_SOCKET) 
	{
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return false;
	}

	// Connect to server.
	iResult = connect(m_socket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}

	// Should really try the next address returned by getaddrinfo
	// if the connect call failed
	// But for this simple example we just free the resources
	// returned by getaddrinfo and print an error message

	freeaddrinfo(result);
	
	if (m_socket == INVALID_SOCKET)
	{
		printf("Unable to connect to server!\n");
		WSACleanup();
		return false;
	}

	DWORD timeout = 250;
	setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (char*) &timeout, sizeof(timeout));

	// Start the receive thread.
	m_receiveThread = std::thread(NetworkManager::ReceiveThreadFunction, this, callback);

	m_connected = true;
	return true;
}

bool NetworkManager::Disconnect(bool graceful)
{
	if (!m_connected)
		return false;

	if (graceful)
	{
		// Send the disconnect message.
		Send({{"Type", "Disconnect"}});

		// Wait for the receiveing thread to terminate.
		m_connected = false;
		Sleep(50);
		m_receiveThread.join();
	}

	int result = shutdown(m_socket, SD_SEND);
		
	if (result == SOCKET_ERROR)
	{
		printf("shutdown failed: %d\n", WSAGetLastError());
	}

	m_connected = false;
	closesocket(m_socket);
	WSACleanup();
	m_socket = INVALID_SOCKET;
	return (result != SOCKET_ERROR);
}

bool NetworkManager::Send(json message)
{
	std::string serializedMessage = message.dump();
	int length = serializedMessage.length();
	char* data = new char[length + 4];
	memcpy(data, &length, 4);
	memcpy(data + 4, serializedMessage.data(), length);

	printf("Sending: %s\n", serializedMessage.c_str());
	printf("Sending %d bytes\n", length);

	int result = send(m_socket, data, length + 4, 0);
	
	delete [] data;

	if (result == SOCKET_ERROR)
	{
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(m_socket);
		WSACleanup();
		m_connected = false;
		m_socket = INVALID_SOCKET;
		return false;
	}

	return true;
}

int select_recv(SOCKET socket, char* buffer, int length)
{
    int recv_size = recv(socket, buffer, length, 0);

	if (recv_size == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAETIMEDOUT)
			return -1;
		else
			return 0;
	}

	return recv_size;
}

bool NetworkManager::Receive(json* message)
{
	char buffer[40000]; // TODO: figure this size out.
	int bufferLength = sizeof(buffer);

	// Receive the message length.
	int result = 0;
	while (result < 4 && m_connected)
	{
		int count = select_recv(m_socket, buffer, 4);
		result += count;
	}
	if (!m_connected)
		return false;
	int messageLength = *((int*) buffer);
	
	// Receive the message contents.
	int remainingBytes = messageLength;
	int bytesReceived = 0;
	char* messageBuffer = buffer;
	while (remainingBytes > 0 && m_connected)
	{
		int length = select_recv(m_socket, messageBuffer, remainingBytes);
		bytesReceived += length;
		messageBuffer += length;
		remainingBytes -= length;
	}
	if (!m_connected)
		return false;

	// Parse the message contents into a json object.
	messageBuffer = buffer;
	messageBuffer[messageLength] = '\0';
	*message = json::parse(std::string(messageBuffer));

	printf("Received %d bytes\n", messageLength);
	//std::cout << "Reveived message: " << message->dump() << std::endl;

	return true;
}


void NetworkManager::ReceiveThreadFunction(NetworkManager* network, ReceiveCallback* callback)
{
	json message;
	bool result;

	printf("Started receive thread\n");

	while (network->IsConnected() && callback->IsReceiving())
	{
		result = network->Receive(&message);

		if (!network->IsConnected() || !callback->IsReceiving())
			break;

		if (result)
		{
			callback->Receive(message);
		}
	}

	printf("Stopped receive thread\n");
}

