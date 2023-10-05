#pragma once
#include <memory>
#include "logger.hpp"

class Proxy
{
public:
	Proxy( uint16_t client_port,
		const std::string &server_ip, uint16_t server_port,
		LoggerBase &logger, int threads = 5 );
	~Proxy();
	bool run();
	void stop();

private:
	struct Private;
	std::unique_ptr<Private> data_;
};
