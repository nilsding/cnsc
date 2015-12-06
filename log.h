/* -*- C -*- */
#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>
#include "cnsc.h"

//!
//! \brief log_logf writes a formatted message to `stdout`.  It works the same
//!     as calling `flogf(stdout, level, format, ...)`.
//! \param level The log level.
//! \param format The format string.
//! \return Same return values as the `printf` function family
//!
int log_logf(int level, const char *format, ...);

//!
//! \brief log_errlogf writes a formatted message to `stderr`.  It works the
//!     same as calling `flogf(stderr, level, format, ...)`.
//! \param level The log level.
//! \param format The format string.
//! \return Same return values as the `printf` function family
//!
int log_errlogf(int level, const char *format, ...);

//!
//! \brief log_flogf writes a formatted message to the file descriptor `fd`.
//! \param fd The file descriptor to write the message to.
//! \param level The log level.
//! \param format The format string.
//! \return Same return values as the `printf` function family
//!
int log_flogf(FILE* fd, int level, const char *format, ...);

#endif // LOG_H
