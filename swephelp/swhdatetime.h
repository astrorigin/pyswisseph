/*
    Swephelp

    Copyright 2007-2009 Stanislas Marquis <stnsls@gmail.com>

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

/** @file swhdatetime.h
** @brief swephelp date and time functions
*/

#ifndef SWHDATETIME_H
#define SWHDATETIME_H

#ifndef SWH_USE_ALIASES
#define SWH_USE_ALIASES     1
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#include <swephexp.h>
#include <time.h>
#include <stdio.h>

/** @brief Get current Julian day number, Gregorian calendar
** @return Julian day number
*/
double swh_jdnow(void);

/** @brief Get Julian day number from a date and time
**
** A conveniance function that, compared to swe_julday, does not require
** hour in decimal format, but accepts integers only.
**
** @attention Does not check date validity. See swe_date_conversion.
**
** @see swh_revjul()
**
** @param year Year (4 digits)
** @param mon Month [1;12]
** @param day Day [1;31]
** @param hour Hour [0;23]
** @param min Minutes [0;59]
** @param sec Seconds [0;59]
** @param flag Calendar type (SE_GREG_CAL|SE_JUL_CAL)
** @return Julian day number
*/
#define swh_julday(year, mon, day, hour, min, sec, flag)\
        swe_julday(year, mon, day, ((hour)+((min)/60.0)+((sec)/3600.0)), flag)

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
int swh_revjul(double jd, int flag, int *dt);

/** @brief Get integers from datetime representation
**
** As a habit we keep dates and times in a personal, yet
** unambiguous format: "{yyyy}/{mm}/{dd} {hh}:{mm}:{ss}".
**
** @param coord datetime string
** @param ret Returned integers declared as int[6]
** @return 0 on success, or -1 if string is invalid
*/
int swh_dt2i(const char *dt, int *ret);

#if SWH_USE_ALIASES

/** @def DateTime_Split
*/
#define DateTime_Split(dt, ret)     swh_dt2i(dt, ret)

#endif /* SWH_USE_ALIASES */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SWHDATETIME_H */
