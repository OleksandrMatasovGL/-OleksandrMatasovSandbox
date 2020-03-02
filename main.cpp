// Copyright 2020 Oleksandr Matasov
// main.cpp : This file contains the 'main' function. Program execution begins
// TODO(Oleksandr Matasov) move server code to server component
//

#include <atomic>
#include <chrono>
#include <iostream>
#include <memory>
#include <sstream>
#include <thread>

#include "export_header.h"
#include "server.h"

#include <anyrpc/anyrpc.h>
#include <anyrpc/internal/time.h>
#include <anyrpc/xml/xmlserver.h>

#if defined(__CYGWIN__)
#include <strings.h>
#endif

#ifndef _WIN32
#include <arpa/inet.h>
#endif // WIN32

#include "common/common.h"
#include "method.h"
#include "printer.h"

int main() {
  std::cout << "Starting.\n";

  std::unique_ptr<anyrpc::XmlTcpServer> server =
      std::make_unique<anyrpc::XmlTcpServer>();
  std::atomic<bool> quit{false};
  //   std::thread thread([&server, &quit]() {
  server->BindAndListen(common::kRobotPort);
  auto methodManager = server->GetMethodManager();
  methodManager->AddFunction(&Add, "add", "Add two numbers");
  // TODO(aom): imitate changing of class
  // object with RTTR lib info
  server->StartThread();
  std::thread thread([&quit, &server]() {
    while (!quit) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1024));
      print::connectionSockInfo(*server);
      std::cout << "."
                << "\n";
    }
  });
  std::this_thread::sleep_for(
      std::chrono::milliseconds(common::kShutdownTimeout));
  quit = true;
  server->StopThread();
  thread.join();
  print::connectionSockInfo(*server);
  server->Exit();
  std::cout << "Quitting.\n";
}
