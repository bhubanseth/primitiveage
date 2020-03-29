#include "server.h"
#include "base_handler.h"
#include "fake_types.pb.h"

namespace example {
class FakeHandler : public ::framework::BaseHandler<FakeRequest, FakeResponse> {
 public:
  FakeResponse Handle(const FakeRequest& req) const {
    FakeResponse r;
    r.set_value("protoresponse");
    return r;
  }
};
}  // namespace example

int main() {
  ::framework::BaseServer server;
  example::FakeHandler fh;
  const framework::BaseHandlerInterface* i = &fh;
  server.RegisterHandler("path", i);
  server.Start();
  return 0;
} 
