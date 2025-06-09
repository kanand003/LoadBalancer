#pragma once

#include <string>
#include <atomic>
#include "Config.h"

class BackendServer {
public:
	BackendServer(const BackendServerDetails& details)
		: m_details(details), m_isHealthy(false), m_active_connections(0) {}
	const std::string& GetIP() const { return m_details.ip; }
	int getPort() const { return m_details.port; }

	bool isHealthy() const { return m_isHealthy.load(); }

	void setHealthStatus(bool status) {
		m_isHealthy.store(status);
	}

	int getActiveConnections() const {
		return m_active_connections.load();
	}

	void incrementActiveConnections() {
		++m_active_connections;
	}

	void decrementActiveConnections()[
		--m_active_connections;
	]

private :
	BackendServerDetails m_details; // Static details : IP, port, etc.
	std::atomic<bool> m_isHealthy; // Dynamic state : health status of the server
	std::atomic<int> m_active_connections; // Dynamic state : active connections