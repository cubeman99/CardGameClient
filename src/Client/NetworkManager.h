#ifndef _NETWORK_MANAGER_H_
#define _NETWORK_MANAGER_H_

#include <vector>
#include "Tags.h"
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
//#include <Windows.h>
#include <thread>


class ReceiveCallback
{
public:
	virtual void Receive(const json& message) = 0;
	virtual bool IsReceiving() = 0;
};


class NetworkManager
{
public:

public:
	NetworkManager();
	~NetworkManager();
	
	bool Connect(const std::string& address, int port, ReceiveCallback* callback);
	bool Disconnect(bool graceful = true);
	bool Send(json message);
	bool Receive(json* message);
	inline bool IsConnected() const { return m_connected; }

private:
	static void ReceiveThreadFunction(NetworkManager* network, ReceiveCallback* callback);

	SOCKET m_socket;
	bool m_connected;
	std::thread m_receiveThread;
	ReceiveCallback* m_callback;
};



#endif // _NETWORK_MANAGER_H_