#include "LoadBalancer.h"
#include <iostream>
#include <stdexcept>
#include <chrono>

#pragma comment(lib, "ws2_32.lib")

LoadBalancer::LoadBalancer(const Config& config)
	:m_config(config), m_listen_socket(INVALID_SOCKET), m_round_robin_index(0)

	for (const auto& server_details : m_config.BACKEND_SERVERS) {
		m_servers.push_back(std::make_unique<BackendServer>(server_details));
	}