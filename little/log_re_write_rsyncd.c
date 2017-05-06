/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: log_re_write_rsyncd.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年05月11日 01时26分09秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年05月11日                  build this moudle  
 *****************************************************************************/
void log_open(void)
{
        static int initialised;
        int options = LOG_PID;
        time_t t;
        char *logf;

        if (initialised) return;
        initialised = 1;

        /* this looks pointless, but it is needed in order for the
           C library on some systems to fetch the timezone info
           before the chroot */
        t = time(NULL);
        localtime(&t);

        /* optionally use a log file instead of syslog */
        logf = lp_log_file();
        if (logf && *logf) {
                extern int orig_umask;
                int old_umask = umask(022 | orig_umask);
                logfile = fopen(logf, "a");
                umask(old_umask);
                return;
        }

#ifdef LOG_NDELAY
        options |= LOG_NDELAY;
#endif

#ifdef LOG_DAEMON
        openlog("rsyncd", options, lp_syslog_facility());
#else
        openlog("rsyncd", options);
#endif

#ifndef LOG_NDELAY
        logit(LOG_INFO,"rsyncd started\n");
#endif
}

/* this is the rsync debugging function. Call it with FINFO, FERROR or FLOG */
void rprintf(enum logcode code, const char *format, ...)
{
        va_list ap; 
        char buf[1024];
        int len;

        va_start(ap, format);
        len = vslprintf(buf, sizeof(buf), format, ap);
        va_end(ap);

        if (len > sizeof(buf)-1) exit_cleanup(RERR_MESSAGEIO);

        rwrite(code, buf, len);
}

/* this is the underlying (unformatted) rsync debugging function. Call
   it with FINFO, FERROR or FLOG */
void rwrite(enum logcode code, char *buf, int len)
{
        FILE *f=NULL;
        extern int am_daemon;
        extern int am_server;
        extern int quiet;
        /* recursion can happen with certain fatal conditions */

        if (quiet && code == FINFO) return;

        if (len < 0) exit_cleanup(RERR_MESSAGEIO);

        buf[len] = 0;

        if (code == FLOG) {
                if (am_daemon) logit(LOG_INFO, buf);
                return;
        }

        /* first try to pass it off the our sibling */
        if (am_server && io_error_write(log_error_fd, code, buf, len)) {
                return;
        }

        /* then try to pass it to the other end */
        if (am_server && io_multiplex_write(code, buf, len)) {
                return;
        }

        if (am_daemon) {
                static int depth;
                int priority = LOG_INFO;
                if (code == FERROR) priority = LOG_WARNING;

                if (depth) return;

                depth++;

                log_open();
                logit(priority, buf);

                depth--;
                return;
        }

        if (code == FERROR) {
                f = stderr;
        } 

        if (code == FINFO) {
                if (am_server) 
                        f = stderr;
                else
                        f = stdout;
        } 

        if (!f) exit_cleanup(RERR_MESSAGEIO);

        if (fwrite(buf, len, 1, f) != 1) exit_cleanup(RERR_MESSAGEIO);

        if (buf[len-1] == '\r' || buf[len-1] == '\n') fflush(f);
}

static void logit(int priority, char *buf)
{
        if (logfile) {
                fprintf(logfile,"%s [%d] %s", 
                        timestring(time(NULL)), (int)getpid(), buf);
                fflush(logfile);
        } else {
                syslog(priority, "%s", buf);
        }
}

