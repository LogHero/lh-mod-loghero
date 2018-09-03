#include "LoggingPolicyBoost.h"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace loghero {

  boost::log::trivial::severity_level getSeverityLevel(const std::string &logLevel) {
    if (logLevel == "debug") {
      return boost::log::trivial::debug;
    }
    else if (logLevel == "info") {
      return boost::log::trivial::info;
    }
    return boost::log::trivial::warning;
  }

  void LoggingPolicyBoost::debug(const std::string &message) {
    BOOST_LOG_TRIVIAL(debug) << message;
  }

  void LoggingPolicyBoost::info(const std::string &message) {
    BOOST_LOG_TRIVIAL(info) << message;
  }

  void LoggingPolicyBoost::warning(const std::string &message) {
    BOOST_LOG_TRIVIAL(warning) << message;
  }

  void LoggingPolicyBoost::error(const std::string &message) {
    BOOST_LOG_TRIVIAL(error) << message;
  }

  void LoggingPolicyBoost::fatal(const std::string &message) {
    BOOST_LOG_TRIVIAL(fatal) << message;
  }

  void LoggingPolicyBoost::init(const std::string &logDirectory, const std::string &logLevel) {
    if (LoggingPolicyBoost::loggingIsSetup) {
      return;
    }
    LoggingPolicyBoost::loggingIsSetup = true;
    namespace keywords = boost::log::keywords;
    namespace sinks = boost::log::sinks;
    boost::log::add_file_log(
      keywords::file_name = logDirectory + "/mod_loghero_%Y-%m-%d_%H-%M-%S.%N.log",
      keywords::rotation_size = 10 * 1024 * 1024,
      keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
      keywords::format = "[%TimeStamp%][%ProcessID%]: %Message%",
      keywords::open_mode = std::ios_base::app,
      keywords::auto_flush = true
    );
    boost::log::trivial::severity_level severityLevel = getSeverityLevel(logLevel);
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= severityLevel);
    boost::log::add_common_attributes();
    LoggingPolicyBoost::debug("Log setup done");
  }

  bool LoggingPolicyBoost::loggingIsSetup = false;

}

