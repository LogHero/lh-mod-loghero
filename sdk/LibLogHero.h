#ifndef LIBLOGHERO_H
#define LIBLOGHERO_H

#ifdef __cplusplus
extern "C" {
#endif

    struct LogEvent {
        char *pagePath;
    };

    void submitLogEvent(struct LogEvent *logEvent);

#ifdef __cplusplus
}
#endif


#endif // LIBLOGHERO_H
