#include "Zlib.h"

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zlib.hpp>

#include <sstream>


namespace loghero {

  std::string Zlib::deflate(const std::string &input) {
    std::stringstream compressed;
    std::stringstream original;
    original << input;
    boost::iostreams::filtering_streambuf<boost::iostreams::input> out;
    out.push(boost::iostreams::zlib_compressor());
    out.push(original);
    boost::iostreams::copy(out, compressed);
    return compressed.str();
  }

  std::string Zlib::inflate(const std::string &input) {
    std::stringstream decompressed;
    std::stringstream compressed;
    compressed << input;
    boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
    in.push(boost::iostreams::zlib_decompressor());
    in.push(compressed);
    boost::iostreams::copy(in, decompressed);
    return decompressed.str();
  }

}
