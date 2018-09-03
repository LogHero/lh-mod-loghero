#include "LoggingPolicyBoost.h"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace loghero {


  void LoggingPolicyBoost::debug(const std::string &message) {
    BOOST_LOG_TRIVIAL(debug) << message;
  }

  void LoggingPolicyBoost::init() {
    namespace keywords = boost::log::keywords;
    namespace sinks = boost::log::sinks;
    boost::log::add_file_log(
      keywords::file_name = "/home/user/tmp/sample_%N.log",
      keywords::rotation_size = 10 * 1024 * 1024,
      keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
      keywords::format = "[%TimeStamp%]: %Message%"
    );
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::debug);
    boost::log::add_common_attributes();
  }


}

