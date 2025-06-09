#pragma once
#include <string>
#include <vector>

enum class RoutingAlgorithm {
	RoundRobin,
	LeastConnections,
};

struct BackendServerDetails {
	std::string ipAddress;
	int port;
};

struct Config {
	const std::string LISTENING_IP = "0.0.0.0";
	const int LISTENING_PORT = 8080;
	const RoutingAlgorithm algorithm = RoutingAlgorithm::LeastConnections;

	const std::vector<BackendServerDetails> backendServers = {
		{"127.0.0.1", 9091},
		{"127.0.0.1", 9092},
	};
	const int HEALTH_CHECK_INTERVAL_MS = 5000;

	const int HEALTH_CHECK_TIMEOUT_MS = 2000; // 2 seconds

	const int MAX_CLIENTS = 100;

	const int BUFFER_SIZE = 4096;
}