#include "framework/server.h"
#include "framework/base_handler.h"
#include "fake_types.pb.h"

namespace example {
class FakeHandler1 : public ::framework::BaseHandler<FakeRequest, FakeResponse> {
 public:
  FakeResponse Handle(const FakeRequest& req) const {
    FakeResponse r;
    r.set_value("protoresponse1");
    return r;
  }
};

class FakeHandler2 : public ::framework::BaseHandler<FakeRequest, FakeResponse> {
 public:
  FakeResponse Handle(const FakeRequest& req) const {
    FakeResponse r;
    r.set_value("protoresponse2");
    return r;
  }
};
} // namespace example

int main() {
  ::framework::BaseServer server;
  example::FakeHandler1 fh1;
  server.RegisterHandler("rpc1", &fh1);
  
  example::FakeHandler2 fh2;
  server.RegisterHandler("rpc2", &fh2);
  server.Start();
  return 0;
} 
