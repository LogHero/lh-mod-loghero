/*
    Install httpd-devel

    https://httpd.apache.org/docs/2.4/developer/modguide.html

    Doxygen for request_rec: https://ci.apache.org/projects/httpd/trunk/doxygen/structrequest__rec.html

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
    ap_log_rerror(APLOG_MARK, APLOG_ALERT, 0, r, APLOGNO(00644) "My loghero handler was called!!! %s %i", r->uri, r->status);
    return DECLINED;
}


static void loghero_register_hooks(apr_pool_t *pool) {
    printf("\n ** loghero_register_hooks **\n\n");
    struct LogEvent logEvent;
    logEvent.pagePath = "/my/page/path";
    submitLogEvent(&logEvent);
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
