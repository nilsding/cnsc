#include "log.h"

static int
log_vflogf(FILE *fd, int level, const char *format, va_list args)
{
    int retval = 0;

    if (VERBOSE >= level) {
        retval = vfprintf(fd, format, args);
    }

    return retval;
}

int
log_logf(int level, const char *format, ...)
{
    int retval = 0;
    va_list args;

    va_start(args, format);
    retval = log_vflogf(stdout, level, format, args);
    va_end(args);

    return retval;
}

int
log_errlogf(int level, const char *format, ...)
{
    int retval = 0;
    va_list args;

    va_start(args, format);
    retval = log_vflogf(stderr, level, format, args);
    va_end(args);

    return retval;
}

int
log_flogf(FILE* fd, int level, const char *format, ...)
{
    int retval = 0;
    va_list args;

    va_start(args, format);
    retval = log_vflogf(fd, level, format, args);
    va_end(args);

    return retval;
}

