#include "APIAccess.h"
#include "Zlib.h"
#include "HttpRequestCurl.h"


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

    HttpRequestCurl request("https://test.loghero.io/logs/");
    //HttpRequestCurl request("http://localhost:8081/logs/");
    request.setHeader("Content-type: application/json");
    request.setHeader("Content-encoding: deflate");
    request.setHeader("Authorization: YOUR_API_KEY");
    request.setHeader("User-Agent: C++ SDK Prototype");
    request.setData(compressed);
    request.execute();
    std::cout << "REQUEST DONE!!" << std::endl;
  }

}
