
#include "anyrpc/anyrpc.h"

#if defined(ANYRPC_THREADING)
#include <thread>
#endif

#if defined(__CYGWIN__)
#include <strings.h>
#endif
#include "common/common.h"
#include <anyrpc/error.h>

/*
 *  This application should be used with exampleServer.
 *  The parameters to the application are strictly positions so that a
 *  command line parser in not needed.
 *
 *  Param 1 : client type - must be defined
 *  Param 2 : IpAddress for the server - defaults to 127.0.0.1
 *  Param 3 : Port for the server - defaults to 9000
 *  Param 4 : Number of clients - only useful if threading is enabled
 *
 *  When testing with multiple clients, you should start the server with
 *  a multithreaded version or the client access will be serialized.
 */
using common::kIPAddress;
using common::kRobotPort;
using common::kShutdownTimeout;

using std::cerr;
using std::cout;
using std::make_unique;

using anyrpc::AnyRpcException;
using anyrpc::Value;

int main(int argc, char *argv[]) {
  auto client = std::make_unique<anyrpc::XmlTcpClient>();
  try {
    client->SetServer(kIPAddress, kRobotPort);
    client->SetTimeout(kShutdownTimeout);
    {
      Value params{};
      Value result{};
      bool success{false};
      // blocking
      success = client->Call("add", params, result);
      cout << "success: " << success << ", add:      " << result << "\n";
    }
  } catch (const anyrpc::AnyRpcException &exc) {
    cerr << "Client failed: " << exc.GetCode() << "\n";
  }
  return 0;
}
