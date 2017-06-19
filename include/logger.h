/* logger.h --- 
 * 
 * Filename: logger.h
 * Author: Jules <archjules>
 * Created: Fri Dec  2 18:57:11 2016 (+0100)
 * Last-Updated: Mon Jun 19 12:44:45 2017 (+0200)
 *           By: Jules <archjules>
 */
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#define LOG_DEBG  0
#define LOG_INFO  1
#define LOG_WARN  2
#define LOG_ERR   3
#define LOG_FATAL 4
#define LOG_SHUT  5

# define log(P, S, ...) fprintf(stdout, P "%s: " S "\n", __FUNCTION__, ##__VA_ARGS__)

# if LOGLEVEL <= LOG_DEBG
#  define log_debug(S, ...) log("[debug] ", S, ##__VA_ARGS__)
# else
#  define log_debug(S, ...)
# endif

# if LOGLEVEL <= LOG_INFO
#  define log_info(S, ...) log("[info]  ", S, ##__VA_ARGS__)
# else
#  define log_info(S, ...)
# endif

# if LOGLEVEL <= LOG_WARN
#  define log_warn(S, ...) log("[warn]  ", S, ##__VA_ARGS__)
# else
#  define log_warn(S, ...)
# endif

# if LOGLEVEL <= LOG_ERR
#  define log_err(S, ...) log("[error] ", S, ##__VA_ARGS__)
# else
#  define log_err(S, ...)
# endif

# if LOGLEVEL <= LOG_FATAL
#  define log_fatal(S, ...) log("[fatal] ", S, ##__VA_ARGS__)
# else
#  define log_fatal(S, ...)
# endif

#endif
