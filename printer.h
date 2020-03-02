// Copyright 2020 Oleksandr Matasov
#pragma once
#include <anyrpc/anyrpc.h>
#include <anyrpc/xml/xmlserver.h>
#include <list>
#include <sstream>

namespace print {
void connectionSockInfo(const anyrpc::XmlTcpServer &server) noexcept {
  std::list<std::string> ips;
  std::list<uint32_t> ports;
  std::stringstream ss;
  server.GetConnectionsSockInfo(ips, ports);
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
}; // namespace print
