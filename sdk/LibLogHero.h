#ifndef LIBLOGHERO_H
#define LIBLOGHERO_H

extern "C" {

    struct LogEvent;

    void submitLogEvent(LogEvent *logEvent);
}


#endif // LIBLOGHERO_H
