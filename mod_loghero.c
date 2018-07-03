/*
    Install httpd-devel

    https://httpd.apache.org/docs/2.4/developer/modguide.html

    Doxygen for request_rec: https://ci.apache.org/projects/httpd/trunk/doxygen/structrequest__rec.html

    Default log module for httpd: https://github.com/omnigroup/Apache/blob/master/httpd/modules/loggers/mod_log_config.c

*/


#include <stdio.h>
//#include "apr_hash.h"
//#include "ap_config.h"
//#include "ap_provider.h"
#include "httpd.h"
#include "http_core.h"
#include "http_config.h"
#include "http_log.h"
#include "http_protocol.h"
#include "http_request.h"
#include "LibLogHero.h"


static int loghero_handler(request_rec *r) {
  struct LogEvent logEvent;
  // Use apr_pescape_echo or ap_escape_logitem
  logEvent.landingPagePath = r->uri;
  logEvent.hostname = r->hostname;
  logEvent.ipAddress = r->connection->client_ip;
  logEvent.userAgent = apr_table_get(r->headers_in, "user-agent");
  logEvent.timestamp = r->request_time / 1000000; // httpd request_time is number of microseconds since 00:00:00 January 1, 1970 UTC
  submitLogEvent(&logEvent);
  ap_log_rerror(APLOG_MARK, APLOG_ALERT, 0, r, APLOGNO(00644) "My loghero handler was called!!! %s %i", r->uri, r->status);
  return DECLINED;
}


static void loghero_register_hooks(apr_pool_t *pool) {
  printf("\n ** loghero_register_hooks **\n\n");
  // TODO: Is this the correct hook? APR_HOOK_MIDDLE??
  ap_hook_log_transaction(loghero_handler, NULL, NULL, APR_HOOK_MIDDLE);
}


module AP_MODULE_DECLARE_DATA   loghero_module = {
  STANDARD20_MODULE_STUFF,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  loghero_register_hooks
};
