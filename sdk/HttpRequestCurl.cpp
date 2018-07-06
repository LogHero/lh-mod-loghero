#include "HttpRequestCurl.h"

#include <curl/curl.h>

#include <iostream>
#include <cassert>


namespace loghero {

  struct HttpRequestCurl::HttpRequestCurl::CurlContainer {
    CurlContainer() :
    pCurl(NULL),
    pHeaderList(NULL) {
      // TODO: Move curl_global_init to SDK factory
      curl_global_init(CURL_GLOBAL_ALL);
      this->pCurl = curl_easy_init();
      assert(this->pCurl);
    }

    ~CurlContainer() {
      curl_easy_cleanup(this->pCurl);
    }

    CURL *pCurl;
    struct curl_slist *pHeaderList;
  };

  HttpRequestCurl::HttpRequestCurl(const std::string &url) :
  pCurlContainer(new CurlContainer()) {
    curl_easy_setopt(this->pCurlContainer->pCurl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(this->pCurlContainer->pCurl, CURLOPT_CUSTOMREQUEST, "PUT");
  }

  HttpRequestCurl::~HttpRequestCurl() {
  }

  void HttpRequestCurl::setData(const std::string &data) {
    std::cout << "HttpRequestCurl::setData() DATA LENGTH: " << data.size() << std::endl;
    curl_easy_setopt(this->pCurlContainer->pCurl, CURLOPT_POSTFIELDSIZE, data.size());
    curl_easy_setopt(this->pCurlContainer->pCurl, CURLOPT_POSTFIELDS, data.c_str());
  }

  void HttpRequestCurl::setHeader(const std::string &header) {
    this->pCurlContainer->pHeaderList = curl_slist_append(this->pCurlContainer->pHeaderList, header.c_str());
  }

  void HttpRequestCurl::execute() {
    curl_easy_setopt(this->pCurlContainer->pCurl, CURLOPT_HTTPHEADER, this->pCurlContainer->pHeaderList);
    CURLcode res = curl_easy_perform(this->pCurlContainer->pCurl);
    if(res != CURLE_OK)
          fprintf(stderr, "curl_easy_perform() failed: %s\n",
                  curl_easy_strerror(res));
  }

}
