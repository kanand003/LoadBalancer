#pragma once

#define WIN32_LEAN_AND_MEAN

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <vector>
#include <memory>
#include <mutex>
#include <thread>
#include <map>

#include "Config.h"
#include "BackendServer.h"

struct ClientBackendPair {
	SOCKET client_socket;
	SOCKET backend_socket;
};

class LoadBalancer {
public:
	LoadBalancer(const Config& config);
	~LoadBalancer();

	LoadBalancer(const LoadBalancer&) = delete; // Disable copy constructor
	LoadBalancer& operator=(const LoadBalancer&) = delete; // Disable copy assignment operator

	void run();
private:
	// Initialize Methods
	void initializeWinSock();
	void setupListenSocket();
	void startHealthChecker();

	void mainLoop();
	void handleNewConnection();
	void forwardData(SOCKET source_socket);
	void closeConnection(SOCKET socket_to_close);

	void healthCheckLoop();

	int findNextBackend();
	int findBackendByLeastConnections();

	const Config& m_config;
	SOCKET m_listen_socket;

	// Pool of backend servers
	std::vector<std::unique_ptr<BackendServer>> m_backend_servers;
	std::mutex m_server_mutex; // Mutex for backend server access
	int m_round_robin_index;

	std::map<SOCKET, ClientBackendPair> m_client_backend_map; // Maps client sockets to backend sockets
	fd_set m_master_fds;
};
