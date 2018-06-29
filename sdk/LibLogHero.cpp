#include "LibLogHero.h"
#include <iostream>
#include <string>


void submitLogEvent(struct LogEvent *logEvent) {
    std::string pagePath(logEvent->pagePath);
    std::cout << " ** Lib function was called with page path " << pagePath << std::endl;
}
