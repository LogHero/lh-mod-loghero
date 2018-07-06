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

  HttpRequestCurl::HttpRequestCurl() :
  pCurlContainer(new CurlContainer()) {
  }

  HttpRequestCurl::~HttpRequestCurl() {
  }

  void HttpRequestCurl::setUrl(const std::string &url) {
    curl_easy_setopt(this->pCurlContainer->pCurl, CURLOPT_URL, url.c_str());
  }

  void HttpRequestCurl::setMethod(const std::string &method) {
    curl_easy_setopt(this->pCurlContainer->pCurl, CURLOPT_CUSTOMREQUEST, method.c_str());
  }

  void HttpRequestCurl::setData(const std::string &data) {
    curl_easy_setopt(this->pCurlContainer->pCurl, CURLOPT_POSTFIELDSIZE, data.size());
    curl_easy_setopt(this->pCurlContainer->pCurl, CURLOPT_POSTFIELDS, data.c_str());
  }

  void HttpRequestCurl::setHeader(const std::string &header) {
    this->pCurlContainer->pHeaderList = curl_slist_append(this->pCurlContainer->pHeaderList, header.c_str());
  }

  void HttpRequestCurl::execute() {
    curl_easy_setopt(this->pCurlContainer->pCurl, CURLOPT_HTTPHEADER, this->pCurlContainer->pHeaderList);
    CURLcode res = curl_easy_perform(this->pCurlContainer->pCurl);
    // TODO: Throw exception here!!
    if(res != CURLE_OK)
          fprintf(stderr, "curl_easy_perform() failed: %s\n",
                  curl_easy_strerror(res));
  }

}
