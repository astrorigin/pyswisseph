/*
    Swephelp

    Copyright 2007-2011 Stanislas Marquis <stnsls@gmail.com>

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

/** @file swhsearch.h
** @brief swephelp search functions
*/

#ifndef SWHSEARCH_H
#define SWHSEARCH_H

#ifndef SWH_USE_ALIASES
#define SWH_USE_ALIASES     1
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/** @brief Get the minimum retrogradation time of a planet, in days
**
** This function is mainly used in swephelp search routines.
**
** The returned value is ~3 days inferior to the "real" minimum
** retrogradation time (tested from 1.1.-3000 to 1.1.3000 when possible).
**
** @remarks May return 10 (default) if the planet is not implemented.
** This may be the case if you want some unusual asteroid. If you need to
** speed search routines, you may try to compute the retrogradation time
** using the minretro.py script, add one line to the source code, and recompile.
**
** @todo Implement more planets, main asteroids...
**
** @param planet Planet number (SE_*, etc)
** @param err Buffer for errors, declared as char[32] (or more)
** @return Number of days, or -1 if planet is never retrograde.
*/
int swh_min_retro_time(int planet, char *err);

/** @brief Get the maximum retrogradation time of a planet, in days
**
** Thought this function would be usefull in search routines, but
** seems like it is not (?).
**
** @remarks The returned value is ~2 days superior to the "real" maximum
** retrogradation time (tested from 1.1.-3000 to 1.1.3000 when possible).
**
** @deprecated This function is not usefull. May disappear one day
**
** @param planet Planet number (SE_*, etc)
** @param err Buffer for errors, declared as char[32] (or more)
** @return Number of days, or -1 if planet is never retrograde.
*/
int swh_max_retro_time(int planet, char *err);

/** @brief Find next direction changing of object
**
** This function tries to find when and where a planet in direct or
** retrograde motion goes retrograde or direct (respectively).
**
** @attention If step is set to 0, use a predefined step (recommended); it must
** be inferior to the planet's minimum retrogradation time.
**
** @remarks If dayspan is set to 0, the search is not limited in time.
** Otherwise, the function may return 1 when time limit has been reached.
** Flag must include SEFLG_SPEED, and SEFLG_NOGDEFL to avoid bad surprises;
** alternatively use true positions.
**
** @see swh_min_retro_time()
**
** @param planet Planet number (SE_*, etc)
** @param jdstart Julian day number, when search is starting
** @param step Number of days used in the dichotomic search process
** @param backw Search before jdstart [1], or after [0] (boolean)
** @param dayspan Limit search to a certain time, expressed in days
** @param flag Calculation flags, see swisseph docs
** @param jdret Julian day number found
** @param posret Planet's positions found
** @param err Buffer for error, declared as char[256]
** @return 0 on success, 1 if time limit reached, -1 on error
*/
int swh_next_retro(int planet, double jdstart, double step, int backw,
    double dayspan, int flag, double *jdret, double *posret, char *err);

/** @brief Get an estimation of when a planet is gone past a fixed point
**
** Get Julian day number and positions when a celestial object is gone past
** a fixed point expressed in longitude degrees. This is not meant to be
** precise at all. Mainly used in swephelp search routines.
**
** @attention Same warning as in swh_next_retro.
**
** @remarks If step is set to 0, use a predefined step (recommended).
**
** @param planet Planet number (SE_*, etc)
** @param fixedpt Fixed pointed targeted [0;360[
** @param jdstart Julian day number, when search is starting
** @param step Number of days used in the dichotomic search process
** @param backw Search before jdstart [1], or after [0] (boolean)
** @param flag Calculation flags, see swisseph docs
** @param jdret Julian day number found
** @param posret Planet's positions found
** @param err Buffer for errors, declared as char[256]
** @return 0 on success, -1 on error
*/
int swh_go_past(int planet, double fixedpt, double jdstart, double step,
    int backw, int flag, double *jdret, double *posret, char *err);

/** @brief Find next exact aspect to a fixed point
**
** Get Julian day number and positions when a celestial object makes a
** longitudinal aspect to a fixed point expressed in longitude degrees.
**
** @attention Same warning as in swh_next_retro.
**
** @remarks If step is set to 0, use a predefined step (recommended).
** If dayspan is set to 0, the search is not limited in time.
** Otherwise, the function may return 1 when time limit has been reached.
**
** @param planet Planet number (SE_*, etc)
** @param aspect Aspect, in degrees [0;360[
** @param fixedpt Fixed point targeted [0;360[
** @param jdstart Julian day number, when search is starting
** @param step Number of days used in the dichotomic search process
** @param backw Search before jdstart [1], or after [0] (boolean)
** @param dayspan Limit search to a certain time, expressed in days
** @param flag Calculation flags, see swisseph docs
** @param jdret Julian day number found
** @param posret Planet's positions found
** @param err Buffer for errors, declared as char[256]
** @return 0 on success, 1 if time limit reached, -1 on error
*/
int swh_next_aspect(int planet, double aspect, double fixedpt, double jdstart,
    double step, int backw, double dayspan, int flag, double *jdret,
    double *posret, char *err);

/** @brief Find next exact aspect to a fixed point
**
** Same as swh_next_aspect but with aspect in [0;180], instead of [0;360[.
**
** @see swh_next_aspect()
**
** @remarks If aspect is not 0 or 180, it will try two aspects [0;360[,
** and return the nearest from jdstart. It may then be faster to use
** swh_next_aspect several times, especially when scanning long periods of time.
*/
int swh_next_aspect2(int planet, double aspect, double fixedpt, double jdstart,
    double step, int backw, double dayspan, int flag, double *jdret,
    double *posret, char *err);

/** @brief Find next aspect between two moving objects
**
** Get Julian day number and positions when a celestial object makes a
** longitudinal aspect to another moving object.
**
** @attention Here, step may not be set to 0. If you estimate that the aspect
** is to occur in a very long time, you better set it to a high value, for
** faster results. In doubt, set it to 10.
**
** @remarks If star != "", the other planet is ignored.
** If dayspan is set to 0, the search is not limited in time.
** Otherwise, the function may return 1 when time limit has been reached.
**
** @param planet Planet number (SE_*, etc)
** @param aspect Aspect, in degrees [0;360[
** @param other Other planet number
** @param star Fixed star
** @param jdstart Julian day number, when search is starting
** @param step Number of days used in the dichotomic search process
** @param backw Search before jdstart [1], or after [0] (boolean)
** @param dayspan Limit search to a certain time, expressed in days
** @param flag Calculation flags, see swisseph docs
** @param jdret Julian day number found
** @param posret0 Planet's positions found
** @param posret1 Other planet (or star) positions found
** @param err Buffer for errors, declared as char[256]
** @return 0 on success, 1 if time limit reached, -1 on error
*/
int swh_next_aspect_with(int planet, double aspect, int other, char *star,
    double jdstart, double step, int backw, double dayspan, int flag,
    double *jdret, double *posret0, double *posret1, char *err);

/** @brief Find next aspect between two moving objects
**
** Same as swh_next_aspect_with, but aspect in [0;180], instead of [0;360[.
**
** @see swh_next_aspect_with()
**
** @remarks If aspect is not 0 or 180, it will try two aspects [0;360[, and
** return the nearest from jdstart. It may then be faster to use
** swh_next_aspect_with several times, especially when scanning
** long periods of time.
*/
int swh_next_aspect_with2(int planet, double aspect, int other, char *star,
    double jdstart, double step, int backw, double dayspan, int flag,
    double *jdret, double *posret0, double *posret1, char *err);

/** @brief Find next aspect to a house cusp
**
** Get Julian day number and positions, and houses cusps, when a
** celestial object makes longitudinal aspect to a house cusp.
**
** @attention Here, step may not be too high, or 0. Setting it to 0.2 is enough.
**
** @remarks If star != "", the planet is ignored.
**
** @see For risings, settings, meridian transits, see swe_rise_trans.
**
** @param planet Planet number (SE_*, etc)
** @param star Fixed star
** @param aspect Aspect, in degrees [0;360[
** @param cusp House cusp number [1;12], or [1;36] for Gauquelin sectors
** @param jdstart Julian day number, when search is starting
** @param lat Latitude, in degrees (north is positive)
** @param lon Longitude, in degrees (east is positive)
** @param hsys House system, see swisseph docs
** @param step Number of days used in the dichotomic search process
** @param backw Search before jdstart [1], or after [0] (boolean)
** @param flag Calculation flags, see swisseph docs
** @param jdret Julian day number found
** @param posret Planet (or fixed star) positions found
** @param cuspsret House cusps positions found
** @param ascmcret Asc-Mc-etc found, see swisseph docs
** @param err Buffer for errors, declared as char[256]
** @return 0 on success, -1 on error
*/
int swh_next_aspect_cusp(int planet, char *star, double aspect, int cusp,
    double jdstart, double lat, double lon, int hsys, double step, int backw,
    int flag, double *jdret, double *posret, double *cuspsret, double *ascmcret,
    char *err);

/** @brief Find next aspect to a house cusp
**
** Same as swh_next_aspect_cusp, but aspect in [0;180], instead of [0;360[.
**
** @see swh_next_aspect_cusp()
**
** @remarks If aspect is not 0 or 180, it will try two aspects [0;360[, and
** return the nearest from jdstart. It may then be faster to use
** swh_next_aspect_cusp several times, especially when scanning
** long periods of time.
*/
int swh_next_aspect_cusp2(int planet, char *star, double aspect, int cusp,
    double jdstart, double lat, double lon, int hsys, double step, int backw,
    int flag, double *jdret, double *posret, double *cuspsret, double *ascmcret,
    char *err);

/** @brief Aspect matching
**
** Check if the two given positions match the aspect within the given orb.
** This also calculates the difference between targeted aspect and distance
** between objects, and if aspect is applicating or separating, or stable due
** to equal speeds.
**
** @param pos0 First object longitude, in degrees [0;360[
** @param speed0 First object longitude speed, in degrees per day
** @param pos1 Second object longitude, in degrees [0;360[
** @param speed1 Second object longitude speed, in degrees per day
** @param aspect Aspect targeted, in degrees [0;360[
** @param orb Orb allowed, in degrees
** @param diffret Difference between aspect and objects distance, in degrees
** @param applic Aspect applicating [-1], separating [1], or stable [0]
** @param factor Aspect strength, compared to orb
** @return 0 if aspect match, else -1
*/
int swh_match_aspect(double pos0, double speed0, double pos1, double speed1,
    double aspect, double orb, double *diffret, int *applic, double *factor);

/** @brief Aspect matching
**
** Same as swh_match_aspect, but aspect in [0;180], instead of [0;360[
**
** @see swh_match_aspect()
*/
int swh_match_aspect2(double pos0, double speed0, double pos1, double speed1,
    double aspect, double orb, double *diffret, int *applic, double *factor);

/** @brief Aspect matching
**
** Same as swh_match_aspect, but with a different orb in case aspect is
** applying, separating, or stable.
**
** @see swh_match_aspect()
*/
int swh_match_aspect3(double pos0, double speed0, double pos1, double speed1,
    double aspect, double app_orb, double sep_orb, double def_orb,
    double *diffret, int *applic, double *factor);

/** @brief Aspect matching
**
** Same as swh_match_aspect2, but with a different orb in case aspect is
** applying, separating, or stable.
**
** @see swh_match_aspect2()
*/
int swh_match_aspect4(double pos0, double speed0, double pos1, double speed1,
    double aspect, double app_orb, double sep_orb, double def_orb,
    double *diffret, int *applic, double *factor);

/** @brief Get number of years difference between two julian days
**
** One exact "astrological" year can be considered as one solar return.
** Then is it varying with the type of zodiac in use.
**
** @param jd1 First Julian day
** @param jd2 Second Julian day
** @param flag Calculation flag
** @param years Result, declared as double
** @param err Buffer for errors, declared as char[256]
** @return 0 on success, else -1
**/
int swh_years_diff(double jd1, double jd2, int flag, double *years, char *err);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SWHSEARCH_H */
