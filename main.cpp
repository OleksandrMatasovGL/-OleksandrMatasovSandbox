// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include <sstream>

#include "export_header.h"
#include "server.h"

#include <anyrpc/anyrpc.h>
#include <anyrpc/internal/time.h>
#include <anyrpc/xml/xmlserver.h>

#if defined(__CYGWIN__)
# include <strings.h>
#endif

#ifndef _WIN32
# include <arpa/inet.h>
#endif // WIN32

constexpr int robotPort = 8270;

int main()
{
    std::cout << "Starting.\n";
	std::unique_ptr<anyrpc::XmlTcpServer> server = std::make_unique<anyrpc::XmlTcpServer>();
	server->BindAndListen(robotPort);
	{
		std::list<std::string> ips;
		std::list<uint32_t> ports;
		std::stringstream ss;
		server->GetConnectionsSockInfo(ips, ports);
		for (auto &ip : ips) {
			ss << ip << "; ";
		}
		ss << " | ports: ";
		for (auto &ip : ips) {
			ss << ip << "; ";
		}
		ss << "\n";
		std::cout << ss.str().c_str() << "\n";
	}
	server->Exit();
    std::cout << "Quitting.\n";
}
