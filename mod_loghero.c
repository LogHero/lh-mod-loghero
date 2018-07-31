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


typedef struct {
  char api_key[256];
} lh_mod_config;

static lh_mod_config global_config;

const char *loghero_set_api_key(cmd_parms *cmd, void *cfg, const char *arg);
static void loghero_register_hooks(apr_pool_t *pool);

static const command_rec loghero_directives[] = {
  AP_INIT_TAKE1(
    "logHeroApiKey",
    loghero_set_api_key,
    NULL,
    RSRC_CONF,
    "LogHero API key (For more information visit log-hero.com"
  ),
  { NULL }
};

module AP_MODULE_DECLARE_DATA loghero_module = {
  STANDARD20_MODULE_STUFF,
  NULL,
  NULL,
  NULL,
  NULL,
  loghero_directives,
  loghero_register_hooks
};

const char *loghero_set_api_key(cmd_parms *cmd, void *cfg, const char *arg) {
  strcpy(global_config.api_key, arg);
  return NULL;
}

static int loghero_handler(request_rec *r) {
  struct LogEvent logEvent;
  // Use apr_pescape_echo or ap_escape_logitem
  logEvent.landingPagePath = r->uri;
  logEvent.hostname = r->hostname;
  logEvent.ipAddress = r->connection->client_ip;
  logEvent.userAgent = apr_table_get(r->headers_in, "user-agent");
  logEvent.referer = apr_table_get(r->headers_in, "referer");
  // httpd request_time is number of microseconds since 00:00:00 January 1, 1970 UTC
  logEvent.timestamp = apr_time_msec(r->request_time);
  logEvent.statusCode = r->status;
  logEvent.method = r->method;
  logEvent.pageLoadTimeMilliSec = apr_time_msec(apr_time_now() - r->request_time);
  submitLogEvent(global_config.api_key, &logEvent);
  return DECLINED;
}

static void loghero_register_hooks(apr_pool_t *pool) {
  printf("\n ** LogHero module loaded! **\n\n");
  global_config.api_key[0] = '\0';
  ap_hook_log_transaction(loghero_handler, NULL, NULL, APR_HOOK_MIDDLE);
}
