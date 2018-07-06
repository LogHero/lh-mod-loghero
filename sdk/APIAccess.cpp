#include "APIAccess.h"
#include "Zlib.h"


#include <iostream>


namespace loghero {

  APIAccess::APIAccess() {
  }

  APIAccess::~APIAccess() {
  }

  void APIAccess::submitLogPackage(const std::string &payloadAsJson) const {
    std::string compressed = Zlib::deflate(payloadAsJson);
    std::string decompressed = Zlib::inflate(compressed);
    std::cout << decompressed << std::endl;
  }

}
