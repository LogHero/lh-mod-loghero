#ifndef ZLIB_H
#define ZLIB_H

#include <string>


namespace loghero {

  class Zlib {
    public:
      static std::string deflate(const std::string &input);
      static std::string inflate(const std::string &input);

    private:
      Zlib();
      ~Zlib();
  };

}


#endif // ZLIB_H
