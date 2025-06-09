#include "Config.h"
#include "LoadBalancer.h"
#include <iostream>
	
int main() {
	Config config;
	LoadBalancer loadBalancer(config);
	loadBalancer.run();
	return 0;
}