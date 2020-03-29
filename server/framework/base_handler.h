#ifndef PRIMITIVEAGE_SERVER_FRAMEWORK_BASE_HANDLER_H__
#define PRIMITIVEAGE_SERVER_FRAMEWORK_BASE_HANDLER_H__

#include <google/protobuf/message_lite.h>
#include "sys/types.h"
#include <string>
#include <type_traits>
#include <iostream>

namespace framework {

class BaseHandlerInterface {
 public:
  virtual std::string BaseHandle(const std::string& req) const = 0;
};

template <typename Input, typename Output>
class BaseHandler : public BaseHandlerInterface {
 public:
  std::string BaseHandle(const std::string& req) const final {
    using google::protobuf::MessageLite;
    static_assert(std::is_base_of<MessageLite, Input>::value, 
      "Input must inherit from MessageLite");
    static_assert(std::is_base_of<MessageLite, Output>::value,
      "Output must inherit from MessageLite");
    // Parse into type
    Input input;
    if (!input.ParseFromString(req)) {
      std::cout << "Failed to parse " << req << std::endl;      
    }
    // call impl
    const Output& output = Handle(input);
    // Convert response into string
    return output.SerializeAsString();
  }

 protected:
  virtual Output Handle(const Input& input) const = 0;
};
}  // namespace framework
#endif
