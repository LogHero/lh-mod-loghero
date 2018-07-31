#ifndef LIBLOGHERO_H
#define LIBLOGHERO_H

#ifdef __cplusplus
extern "C" {
#endif

  struct LogEvent {
    const char *landingPagePath;
    const char *userAgent;
    const char *ipAddress;
    const char *hostname;
    const char *method;
    const char *referer;
    long timestamp;
    long pageLoadTimeMilliSec;
    int statusCode;
  };

  void submitLogEvent(const char *apiKey, struct LogEvent *logEvent);

#ifdef __cplusplus
}
#endif


#endif // LIBLOGHERO_H
