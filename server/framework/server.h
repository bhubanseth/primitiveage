#ifndef PRIMTIVEAGE_SERVER_FRAMEWORK_SERVER_H__
#define PRIMTIVEAGE_SERVER_FRAMEWORK_SERVER_H__
#include <sys/types.h>
#include <unordered_map>
#include "base_handler.h"

namespace framework {

class BaseServer {
 public:
  BaseServer() = default;
  ~BaseServer() = default;

  void RegisterHandler(const std::string& path, const BaseHandlerInterface* handler);

  // Starts the server to receive requests and serve them if corresponding handler is registered.
  // Returns true if the server exists successfully, otherwise returns false.
  bool Start() const;

 private:
  std::unordered_map<std::string, const BaseHandlerInterface*> handlers;
};

}  // namespace framework
#endif
