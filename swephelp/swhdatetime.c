/*
    Swephelp

    Copyright 2007-2014 Stanislas Marquis <smarquis@astrorigin.ch>

    Swephelp is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of
    the License, or (at your option) any later version.

    Swephelp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Swephelp.  If not, see <http://www.gnu.org/licenses/>.
*/

/** @file swhdatetime.c
** @brief swephelp date and time functions
*/

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <swephexp.h>

#include "swhdatetime.h"
#include "swhwin.h"

/** @brief Get current Julian day number, Gregorian calendar
** @return Julian day number
*/
double swh_jdnow(void)
{
    time_t t = time(NULL);
#ifdef WIN32 /* has not gmtime_r ? */
    struct tm *tmp = gmtime(&t);
    return swe_julday(tmp->tm_year+1900, tmp->tm_mon+1, tmp->tm_mday,
        (tmp->tm_hour+(tmp->tm_min/60.0)+(tmp->tm_sec/3600.0)), SE_GREG_CAL);
#else
    struct tm tmp;
    gmtime_r(&t, &tmp);
    return swe_julday(tmp.tm_year+1900, tmp.tm_mon+1, tmp.tm_mday,
        (tmp.tm_hour+(tmp.tm_min/60.0)+(tmp.tm_sec/3600.0)), SE_GREG_CAL);
#endif
}

/** @brief Reverse Julian day to date and time
**
** Similar to swe_revjul, but returns time with three integers instead
** of one double. (Also tries to avoid some floating points rounding errors.)
**
** @see swh_julday()
**
** @param jd Julian day
** @param flag Calendar type (SE_GREG_CAL|SE_JUL_CAL)
** @param dt Results, declared as int[6] (year, month, day, hour, min, sec)
** @return 0
*/
int swh_revjul(double jd, int flag, int *dt)
{
    double t;
    assert(flag == SE_GREG_CAL || flag == SE_JUL_CAL);
    swe_revjul(jd, flag, &dt[0], &dt[1], &dt[2], &t);
    dt[3] = (int) floor(t);
    t -= dt[3];
    dt[4] = (int) floor(t * 60);
    t -= dt[4]/60.0;
    dt[5] = (int) lround(t * 3600);
    if (dt[5] == 60) /* rounding error */
    {
        dt[5] = 0;
        dt[4] += 1;
        if (dt[4] == 60)
        {
            dt[4] = 0;
            dt[3] += 1;
            /* wont go further? */
        }
    }
    return 0;
}

/** @brief Get integers from datetime representation
**
** As a habit we keep dates and times in a personal, yet
** unambiguous format: "{yyyy}/{mm}/{dd} {hh}:{mm}:{ss}".
**
** @param coord datetime string
** @param ret Returned integers declared as int[6]
** @return 0 on success, or -1 if string is invalid
*/
int swh_dt2i(const char *dt, int *ret)
{
    char *ptr, buf[22];
#ifndef WIN32
    char *saveptr;
#endif
    strcpy(buf, dt);
#ifndef WIN32
    ptr = strtok_r(buf, "/", &saveptr);
#else
    ptr = strtok(buf, "/");
#endif
    if (ptr == NULL || strspn(ptr, "-0123456789") != strlen(ptr))
        return -1;
    else
        ret[0] = atoi(ptr); /* year */
#ifndef WIN32
    ptr = strtok_r(NULL, "/", &saveptr);
#else
    ptr = strtok(NULL, "/");
#endif
    if (ptr == NULL || strspn(ptr, "0123456789") != strlen(ptr))
        return -1;
    else
        ret[1] = atoi(ptr); /* month */
    assert(ret[1] > 0 && ret[1] < 13);
#ifndef WIN32
    ptr = strtok_r(NULL, " ", &saveptr);
#else
    ptr = strtok(NULL, " ");
#endif
    if (ptr == NULL || strspn(ptr, "0123456789") != strlen(ptr))
        return -1;
    else
        ret[2] = atoi(ptr); /* mday */
    assert(ret[2] > 0 && ret[2] < 32);
#ifndef WIN32
    ptr = strtok_r(NULL, ":", &saveptr);
#else
    ptr = strtok(NULL, ":");
#endif
    if (ptr == NULL || strspn(ptr, "0123456789") != strlen(ptr))
        return -1;
    else
        ret[3] = atoi(ptr); /* hour */
    assert(ret[3] > -1 && ret[3] < 24);
#ifndef WIN32
    ptr = strtok_r(NULL, ":", &saveptr);
#else
    ptr = strtok(NULL, ":");
#endif
    if (ptr == NULL || strspn(ptr, "0123456789") != strlen(ptr))
        return -1;
    else
        ret[4] = atoi(ptr); /* minutes */
    assert(ret[4] > -1 && ret[4] < 60);
#ifndef WIN32
    ptr = strtok_r(NULL, ":", &saveptr);
#else
    ptr = strtok(NULL, ":");
#endif
    if (ptr == NULL || strspn(ptr, "0123456789") != strlen(ptr))
        return -1;
    else
        ret[5] = atoi(ptr); /* seconds */
    assert(ret[5] > -1 && ret[5] < 60);
    return 0;
}

/* vi: set fenc=utf-8 ff=unix et sw=4 ts=4 sts=4 : */
