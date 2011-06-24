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

/** @file swhsearch.c
** @brief swephelp search functions
*/

#ifdef __cplusplus
extern "C"
{
#endif

#include "swhsearch.h"
#include <swephexp.h>

/** @brief Half a second of time (expressed in day)
** Used to set the precision of search functions.
*/
static double swh_precision = ((1.0/86400)/2);

/** @def ISPOSITIVE
** @brief Return 1 if x is greater than 0, else return 0
*/
#define ISPOSITIVE(x)   ((x) > 0 ? 1 : 0)

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
int swh_min_retro_time(int planet, char *err)
{
    int days;
    switch (planet)
    { /* days MUST be inferior to the minimum retrogradation time
        tested from 1.1.-3000 to 1.1.3000 when possible */
    case SE_SUN: strcpy(err, "Sun retro?"); return -1;
    case SE_MOON: strcpy(err, "Moon retro?"); return -1;
    case SE_MERCURY: days = 16; break; /* ~19 days */
    case SE_VENUS: days = 37; break; /* ~40 days */
    case SE_MARS: days = 56; break; /* ~59 days */
    case SE_JUPITER: days = 114; break; /* ~117 days */
    case SE_SATURN: days = 129; break; /* ~132 days */
    case SE_URANUS: days = 145; break; /* ~148 days */
    case SE_NEPTUNE: days = 153; break; /* ~156 days */
    case SE_PLUTO: days = 153; break; /* ~156 days */
    case SE_MEAN_NODE: strcpy(err, "Mean node retro?"); return -1;
    case SE_TRUE_NODE: strcpy(err, "True node retro?"); return -1;
    case SE_MEAN_APOG: strcpy(err, "Mean apogee retro?"); return -1;
    case SE_OSCU_APOG: strcpy(err, "Oscul. apogee retro?"); return -1;
    case SE_EARTH: strcpy(err, "Earth retro?"); return -1;
    case SE_CHIRON: days = 125; break; /* ~128 days */
    case SE_PHOLUS: days = 125; break; /* ~128 days */
    case SE_CERES: days = 85; break; /* ~88 days */
    case SE_PALLAS: days = 46; break; /* ~49 days */
    case SE_JUNO: days = 68; break; /* ~71 days */
    case SE_VESTA: days = 81; break; /* ~84 days */
    /* TODO more planets */
    default: days = 10; /* default... */
    }
    return days;
}

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
int swh_max_retro_time(int planet, char *err)
{
    int days;
    switch (planet)
    { /* days MUST be superior to maximum retrogradation time
        tested from 1.1.-3000 to 1.1.3000 when possible */
    case SE_SUN: strcpy(err, "Sun retro?"); return -1;
    case SE_MOON: strcpy(err, "Moon retro?"); return -1;
    case SE_MERCURY: days = 27; break; /* ~25 days */
    case SE_VENUS: days = 46; break; /* ~44 days */
    case SE_MARS: days = 84; break; /* ~84 days */
    case SE_JUPITER: days = 126; break; /* ~124 days */
    case SE_SATURN: days = 145; break; /* ~143 days */
    case SE_URANUS: days = 157; break; /* ~155 days */
    case SE_NEPTUNE: days = 163; break; /* ~161 days */
    case SE_PLUTO: days = 168; break; /* ~166 days */
    case SE_MEAN_NODE: strcpy(err, "Mean node retro?"); return -1;
    case SE_TRUE_NODE: strcpy(err, "True node retro?"); return -1;
    case SE_MEAN_APOG: strcpy(err, "Mean apogee retro?"); return -1;
    case SE_OSCU_APOG: strcpy(err, "Oscul. apogee retro?"); return -1;
    case SE_EARTH: strcpy(err, "Earth retro?"); return -1;
    case SE_CHIRON: days = 160; break; /* ~158 days */
    case SE_PHOLUS: days = 172; break; /* ~170 days */
    case SE_CERES: days = 109; break; /* ~107 days */
    case SE_PALLAS: days = 123; break; /* ~121 days */
    case SE_JUNO: days = 116; break; /* ~114 days */
    case SE_VESTA: days = 100; break; /* ~98 days */
    /* TODO more planets */
    default: days = 150; /* default... */
    }
    return days;
}

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
    double dayspan, int flag, double *jdret, double *posret, char *err)
{
    int res, direct[3]; direct[2] = 0; /* dummy assign */
    double jdstop = 0; /* dummy assign */
    /* set limit */
    dayspan = fabs(dayspan);
    if (dayspan)
    {
        jdstop = (backw) ? jdstart-dayspan : jdstart+dayspan;
        direct[2] = (backw) ? 0 : 1;
    }
    /* find step if 0 */
    if (step == 0)
    {
        step = swh_min_retro_time(planet, err);
        if (step < 0) { return -1; } /* never retro */
    } else { step = fabs(step); }
    /* find current direction */
    res = swe_calc_ut(jdstart, planet, flag, posret, err);
    if (res < 0) { return -1; }
    direct[1] = direct[0] = (posret[3] > 0) ? 1 : 0;
    /* step till direction changes */
    *jdret = jdstart;
    while (step > swh_precision)
    {
        *jdret = (backw) ? *jdret-step : *jdret+step;
        res = swe_calc_ut(*jdret, planet, flag, posret, err);
        if (res < 0) { return -1; }
        direct[0] = (posret[3] > 0) ? 1 : 0;
        if (direct[0] != direct[1]) /* invert step */
        {
            if (dayspan && backw == direct[2])
            {
                if (direct[2]) { if (*jdret > jdstop) return 1; }
                else { if (*jdret < jdstop) return 1; }
            }
            step = step/2;
            backw = (backw) ? 0 : 1;
            direct[1] = direct[0];
        }
        else if (dayspan && backw != direct[2])
        {
            if (direct[2]) { if (*jdret > jdstop) return 1; }
            else { if (*jdret < jdstop) return 1; }
        }
    }
    return 0;
}

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
    int backw, int flag, double *jdret, double *posret, char *err)
{
    int res;
    double testjd, difdegn[2], difdeg2n[2];
    /* find step if 0 */
    if (step == 0)
    {
        step = swh_min_retro_time(planet, err);
        if (step < 0) { step = 10; } /* never retro, use default step */
    } else { step = fabs(step); }
    /* get start position */
    res = swe_calc_ut(jdstart, planet, flag, posret, err);
    if (res < 0) { return -1; }
    /* get difference between start pt and fixed pt */
    difdegn[1] = swe_difdegn(posret[0], fixedpt);
    difdeg2n[1] = swe_difdeg2n(posret[0], fixedpt);
    *jdret = jdstart;
    while (1)
    {
        *jdret = (backw) ? *jdret-step : *jdret+step;
        res = swe_calc_ut(*jdret, planet, flag, posret, err);
        if (res < 0) { return -1; }
        if (posret[3] < 0)
        {
            res = swh_next_retro(planet, *jdret, step, (backw) ? 0 : 1,
                0, flag, &testjd, posret, err);
            if (res < 0) { return -1; }
        }
        else { testjd = *jdret; }
        difdegn[0] = swe_difdegn(posret[0], fixedpt);
        difdeg2n[0] = swe_difdeg2n(posret[0], fixedpt);
        if (ISPOSITIVE(difdeg2n[1]) != ISPOSITIVE(difdeg2n[0])
            && fabs(difdegn[1]-difdegn[0]) > 180)
        {
            *jdret = testjd;
            return 0;
        }
        difdegn[1] = difdegn[0];
        difdeg2n[1] = difdeg2n[0];
    }
}

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
    double *posret, char *err)
{
    int res, direct = 0; /* dummy assign */
    double jdstop = 0; /* dummy assign */
    dayspan = fabs(dayspan);
    if (dayspan)
    {
        jdstop = (backw) ? jdstart-dayspan : jdstart+dayspan;
        direct = (backw) ? 0 : 1;
    }
    if (step == 0)
    {
        step = swh_min_retro_time(planet, err);
        if (step < 0) { step = 10; } /* default step */
    } else { step = fabs(step); }
    fixedpt = swe_degnorm(fixedpt + aspect);
    *jdret = jdstart;
    while (step > swh_precision)
    {
        res = swh_go_past(planet, fixedpt, *jdret, step, backw, flag,
            jdret, posret, err);
        if (res < 0) { return -1; }
        if (dayspan && backw == direct)
        {
            if (direct) { if (*jdret > jdstop) return 1; }
            else { if (*jdret < jdstop) return 1; }
        }
        backw = (backw) ? 0 : 1;
        step = step/2;
    }
    return 0;
}

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
    double *posret, char *err)
{
    aspect = fabs(swe_difdeg2n(0, aspect));
    if (aspect == 0 || aspect == 180)
    {
        return swh_next_aspect(planet, aspect, fixedpt, jdstart, step, backw,
            dayspan, flag, jdret, posret, err);
    }
    /* else try both */
    int res, res2;
    double jdtmp, postmp[6];
    res = swh_next_aspect(planet, aspect, fixedpt, jdstart, step, backw,
        dayspan, flag, jdret, posret, err);
    if (res < 0) { return -1; }
    res2 = swh_next_aspect(planet, 0-aspect, fixedpt, jdstart, step, backw,
        dayspan, flag, &jdtmp, postmp, err);
    if (res2 < 0) { return -1; }
    if (res == 1 && res2 == 1) { return 1; } /* both reached time limit */
    else if (res != res2) /* one reached limit */
    {
        if (res2 == 0)
        {
            *jdret = jdtmp;
            for (res = 0; res < 6; res++) { posret[res] = postmp[res]; }
        }
    }
    else /* both found something */
    {
        if (backw)
        {
            if (jdtmp > *jdret)
            {
                *jdret = jdtmp;
                for (res = 0; res < 6; res++) { posret[res] = postmp[res]; }
            }
        }
        else
        {
            if (jdtmp < *jdret)
            {
                *jdret = jdtmp;
                for (res = 0; res < 6; res++) { posret[res] = postmp[res]; }
            }
        }
    }
    return 0;
}

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
    double *jdret, double *posret0, double *posret1, char *err)
{
    int res, starflag, direct = 0; /* dummy assign */
    double jdstop = 0, diff[4]; /* dummy assign */
    char starbuf[41];
    aspect = swe_degnorm(aspect);
    step = fabs(step);
    if (step == 0) { step = 10; }
    dayspan = fabs(dayspan);
    if (dayspan)
    {
        jdstop = (backw) ? jdstart-dayspan : jdstart+dayspan;
        direct = (backw) ? 0 : 1;
    }
    /* get planets positions */
    res = swe_calc_ut(jdstart, planet, flag, posret0, err);
    if (res < 0) { return -1; }
    if (strcmp("", star) != 0)
    {
        strcpy(starbuf, star); /* only first time */
        res = swe_fixstar_ut(starbuf, jdstart, flag, posret1, err);
        if (res < 0) { return -1; }
        starflag = 1;
    }
    else
    {
        res = swe_calc_ut(jdstart, other, flag, posret1, err);
        if (res < 0) { return -1; }
        starflag = 0;
    }
    /* compare */
    diff[1] = swe_difdeg2n(posret0[0], posret1[0] + aspect);
    diff[3] = swe_difdegn(posret0[0], posret1[0] + aspect);
    *jdret = jdstart;
    while (step > swh_precision)
    {
        *jdret = (backw) ? *jdret-step : *jdret+step;
        /* get planets positions */
        res = swe_calc_ut(*jdret, planet, flag, posret0, err);
        if (res < 0) { return -1; }
        if (starflag)
        {
            res = swe_fixstar_ut(starbuf, *jdret, flag, posret1, err);
            if (res < 0) { return -1; }
        }
        else
        {
            res = swe_calc_ut(*jdret, other, flag, posret1, err);
            if (res < 0) { return -1; }
        }
        /* compare */
        diff[0] = swe_difdeg2n(posret0[0], posret1[0] + aspect);
        diff[2] = swe_difdegn(posret0[0], posret1[0] + aspect);
        if (ISPOSITIVE(diff[1]) != ISPOSITIVE(diff[0])
            && fabs(diff[3]-diff[2]) > 180) /* invert step */
        {
            if (dayspan && backw == direct)
            {
                if (direct) { if (*jdret > jdstop) return 1; }
                else { if (*jdret < jdstop) return 1; }
            }
            backw = (backw) ? 0 : 1;
            step = step/2;
        }
        else if (dayspan && backw != direct)
        {
            if (direct) { if (*jdret > jdstop) return 1; }
            else { if (*jdret < jdstop) return 1; }
        }
        diff[1] = diff[0];
        diff[3] = diff[2];
    }
    return 0;
}

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
    double *jdret, double *posret0, double *posret1, char *err)
{
    aspect = fabs(swe_difdeg2n(0, aspect));
    if (aspect == 0 || aspect == 180)
    {
        return swh_next_aspect_with(planet, aspect, other, star, jdstart, step,
            backw, dayspan, flag, jdret, posret0, posret1, err);
    }
    /* else try both */
    int res, res2;
    double jdtmp, postmp0[6], postmp1[6];
    res = swh_next_aspect_with(planet, aspect, other, star, jdstart, step,
        backw, dayspan, flag, jdret, posret0, posret1, err);
    if (res < 0) { return -1; }
    res2 = swh_next_aspect_with(planet, 0-aspect, other, star, jdstart, step,
        backw, dayspan, flag, &jdtmp, postmp0, postmp1, err);
    if (res2 < 0) { return -1; }
    if (res == 1 && res2 == 1) { return 1; } /* both reached time limit */
    else if (res != res2) /* one reached limit */
    {
        if (res2 == 0)
        {
            *jdret = jdtmp;
            for (res = 0; res < 6; res++) { posret0[res] = postmp0[res]; }
            for (res = 0; res < 6; res++) { posret1[res] = postmp1[res]; }
        }
    }
    else /* both found something */
    {
        if (backw)
        {
            if (jdtmp > *jdret)
            {
                *jdret = jdtmp;
                for (res = 0; res < 6; res++) { posret0[res] = postmp0[res]; }
                for (res = 0; res < 6; res++) { posret1[res] = postmp1[res]; }
            }
        }
        else
        {
            if (jdtmp < *jdret)
            {
                *jdret = jdtmp;
                for (res = 0; res < 6; res++) { posret0[res] = postmp0[res]; }
                for (res = 0; res < 6; res++) { posret1[res] = postmp1[res]; }
            }
        }
    }
    return 0;
}

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
    char *err)
{
    int res, starflag;
    double diff[4];
    char starbuf[41];
    aspect = swe_degnorm(aspect);
    step = fabs(step);
    if (step == 0) { step = 0.2; }
    /* get start position */
    if (strcmp("", star) != 0)
    {
        strcpy(starbuf, star); /* only first time */
        res = swe_fixstar_ut(starbuf, jdstart, flag, posret, err);
        if (res < 0) { return -1; }
        starflag = 1;
    }
    else
    {
        res = swe_calc_ut(jdstart, planet, flag, posret, err);
        if (res < 0) { return -1; }
        starflag = 0;
    }
    res = swe_houses_ex(jdstart, flag, lat, lon, hsys, cuspsret, ascmcret);
    if (res < 0) { return -1; }
    /* compare */
    diff[1] = swe_difdeg2n(posret[0], cuspsret[cusp] + aspect);
    diff[3] = swe_difdegn(posret[0], cuspsret[cusp] + aspect);
    *jdret = jdstart;
    while (step > swh_precision)
    {
        *jdret = (backw) ? *jdret-step : *jdret+step;
        /* get positions */
        if (starflag)
        {
            res = swe_fixstar_ut(starbuf, *jdret, flag, posret, err);
            if (res < 0) { return -1; }
        }
        else
        {
            res = swe_calc_ut(*jdret, planet, flag, posret, err);
            if (res < 0) { return -1; }
        }
        res = swe_houses_ex(*jdret, flag, lat, lon, hsys, cuspsret, ascmcret);
        if (res < 0) { return -1; }
        /* compare */
        diff[0] = swe_difdeg2n(posret[0], cuspsret[cusp] + aspect);
        diff[2] = swe_difdegn(posret[0], cuspsret[cusp] + aspect);
        if (ISPOSITIVE(diff[1]) != ISPOSITIVE(diff[0])
            && fabs(diff[3]-diff[2]) > 180)
        {
            backw = (backw) ? 0 : 1;
            step = step/2;
        }
        diff[1] = diff[0];
        diff[3] = diff[2];
    }
    return 0;
}

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
    char *err)
{
    aspect = fabs(swe_difdeg2n(0, aspect));
    if (aspect == 0 || aspect == 180)
    {
        return swh_next_aspect_cusp(planet, star, aspect, cusp, jdstart, lat,
            lon, hsys, step, backw, flag, jdret, posret, cuspsret, ascmcret,
            err);
    }
    /* else try both */
    int res, res2;
    double jdtmp, postmp[6], cuspstmp[37], ascmctmp[10];
    res = swh_next_aspect_cusp(planet, star, aspect, cusp, jdstart, lat,
            lon, hsys, step, backw, flag, jdret, posret, cuspsret, ascmcret,
            err);
    if (res < 0) { return -1; }
    res2 = swh_next_aspect_cusp(planet, star, aspect, cusp, jdstart, lat,
            lon, hsys, step, backw, flag, &jdtmp, postmp, cuspstmp, ascmctmp,
            err);
    if (res2 < 0) { return -1; }
    if (backw)
    {
        if (jdtmp > *jdret)
        {
            *jdret = jdtmp;
            for (res = 0; res < 6; res++) { posret[res] = postmp[res]; }
            for (res = 0; res < 37; res++) { cuspsret[res] = cuspstmp[res]; }
            for (res = 0; res < 10; res++) { ascmcret[res] = ascmctmp[res]; }
        }
    }
    else
    {
        if (jdtmp < *jdret)
        {
            *jdret = jdtmp;
            for (res = 0; res < 6; res++) { posret[res] = postmp[res]; }
            for (res = 0; res < 37; res++) { cuspsret[res] = cuspstmp[res]; }
            for (res = 0; res < 10; res++) { ascmcret[res] = ascmctmp[res]; }
        }
    }
    return 0;
}

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
    double aspect, double orb, double *diffret, int *applic, double *factor)
{
    aspect = fabs(aspect);
    orb = fabs(orb);
    double diff = swe_difdegn(pos0, pos1);
    if (diff > aspect)
    {
        if (speed1 > speed0) { *applic = -1; }
        else if (speed1 < speed0) { *applic = 1; }
        else { *applic = 0; }
        *diffret = diff-aspect;
    }
    else if (diff < aspect)
    {
        if (speed1 > speed0) { *applic = 1; }
        else if (speed1 < speed0) { *applic = -1; }
        else { *applic = 0; }
        *diffret = aspect-diff;
    }
    else /* aspect is exact, cannot applic */
    {
        if (speed1 != speed0) { *applic = 1; }
        else { *applic = 0; }
        *diffret = 0;
        *factor = 0;
        return 0;
    }
    *factor = *diffret / orb;
    if (aspect-orb <= diff && diff <= aspect+orb) { return 0; } /* match */
    else { return -1; } /* no match */
}

/** @brief Aspect matching
**
** Same as swh_match_aspect, but aspect in [0;180], instead of [0;360[
**
** @see swh_match_aspect()
*/
int swh_match_aspect2(double pos0, double speed0, double pos1, double speed1,
    double aspect, double orb, double *diffret, int *applic, double *factor)
{
    aspect = fabs(aspect);
    orb = fabs(orb);
    double difdeg2n = swe_difdeg2n(pos0, pos1);
    double diff = fabs(difdeg2n);
    if (difdeg2n > 0)
    {
        if (diff > aspect)
        {
            if (speed1 > speed0) { *applic = -1; }
            else if (speed1 < speed0) { *applic = 1; }
            else { *applic = 0; }
            *diffret = diff-aspect;
        }
        else if (diff < aspect)
        {
            if (speed1 > speed0) { *applic = 1; }
            else if (speed1 < speed0) { *applic = -1; }
            else { *applic = 0; }
            *diffret = aspect-diff;
        }
        else /* aspect exact */
        {
            if (speed1 != speed0) { *applic = 1; }
            else { *applic = 0; }
            *diffret = 0;
            *factor = 0;
            return 0;
        }
    }
    else if (difdeg2n > -180)
    {
        if (diff > aspect)
        {
            if (speed1 > speed0) { *applic = 1; }
            else if (speed1 < speed0) { *applic = -1; }
            else { *applic = 0; }
            *diffret = diff-aspect;
        }
        else if (diff < aspect)
        {
            if (speed1 > speed0) { *applic = -1; }
            else if (speed1 < speed0) { *applic = 1; }
            else { *applic = 0; }
            *diffret = aspect-diff;
        }
        else /* aspect exact */
        {
            if (speed1 != speed0) { *applic = 1; }
            else { *applic = 0; }
            *diffret = 0;
            *factor = 0;
            return 0;
        }
    }
    else /* exact conjunction or opposition */
    {
        if (speed1 != speed0) { *applic = 1; }
        else { *applic = 0; }
        *diffret = 0;
        *factor = 0;
        return 0;
    }
    *factor = *diffret / orb;
    if (aspect-orb <= diff && diff <= aspect+orb) { return 0; } /* match */
    else { return -1; } /* no match */
}

/** @brief Aspect matching
**
** Same as swh_match_aspect, but with a different orb in case aspect is
** applying, separating, or stable.
**
** @see swh_match_aspect()
*/
int swh_match_aspect3(double pos0, double speed0, double pos1, double speed1,
    double aspect, double app_orb, double sep_orb, double def_orb,
    double *diffret, int *applic, double *factor)
{
    app_orb = fabs(app_orb);
    sep_orb = fabs(sep_orb);
    def_orb = fabs(def_orb);
    if (speed0 == speed1)
    { /* stable aspect */
        return swh_match_aspect(pos0, speed0, pos1, speed1, aspect,
            def_orb, diffret, applic, factor);
    }
    if (app_orb == sep_orb)
    {
        return swh_match_aspect(pos0, speed0, pos1, speed1, aspect, app_orb,
            diffret, applic, factor);
    }
    int i;
    if (app_orb > sep_orb)
    {
        i = swh_match_aspect(pos0, speed0, pos1, speed1, aspect, app_orb,
            diffret, applic, factor);
        if (i == 0)
        {
            if (*applic == -1)
            {
                return 0;
            }
            else if (*diffret <= sep_orb)
            {
                *factor = *diffret / sep_orb;
                return 0;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            return -1;
        }
    }
    else
    {
        i = swh_match_aspect(pos0, speed0, pos1, speed1, aspect, sep_orb,
            diffret, applic, factor);
        if (i == 0)
        {
            if (*applic == 1)
            {
                return 0;
            }
            else if (*diffret <= app_orb)
            {
                *factor = *diffret / app_orb;
                return 0;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            return -1;
        }
    }
}

/** @brief Aspect matching
**
** Same as swh_match_aspect2, but with a different orb in case aspect is
** applying, separating, or stable.
**
** @see swh_match_aspect2()
*/
int swh_match_aspect4(double pos0, double speed0, double pos1, double speed1,
    double aspect, double app_orb, double sep_orb, double def_orb,
    double *diffret, int *applic, double *factor)
{
    app_orb = fabs(app_orb);
    sep_orb = fabs(sep_orb);
    def_orb = fabs(def_orb);
    if (speed0 == speed1)
    { /* stable aspect */
        return swh_match_aspect2(pos0, speed0, pos1, speed1, aspect,
            def_orb, diffret, applic, factor);
    }
    if (app_orb == sep_orb)
    {
        return swh_match_aspect2(pos0, speed0, pos1, speed1, aspect, app_orb,
            diffret, applic, factor);
    }
    int i;
    if (app_orb > sep_orb)
    {
        i = swh_match_aspect2(pos0, speed0, pos1, speed1, aspect, app_orb,
            diffret, applic, factor);
        if (i == 0)
        {
            if (*applic == -1)
            {
                return 0;
            }
            else if (*diffret <= sep_orb)
            {
                *factor = *diffret / sep_orb;
                return 0;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            return -1;
        }
    }
    else
    {
        i = swh_match_aspect2(pos0, speed0, pos1, speed1, aspect, sep_orb,
            diffret, applic, factor);
        if (i == 0)
        {
            if (*applic == 1)
            {
                return 0;
            }
            else if (*diffret <= app_orb)
            {
                *factor = *diffret / app_orb;
                return 0;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            return -1;
        }
    }
}

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
int swh_years_diff(double jd1, double jd2, int flag, double *years, char *err)
{
    double pos1[6], pos2[6], dec;
    double corr = 2 * swh_precision;
    int res;
    res = swe_calc_ut(jd1, SE_SUN, flag, pos1, err);
    if (res < 0) { return -1; }
    res = swe_calc_ut(jd2, SE_SUN, flag, pos2, err);
    if (res < 0) { return -1; }
    *years = 0;
    if (jd1 < jd2) /* forward search */
    {
        dec = swe_difdegn(pos2[0], pos1[0]) / 360.0;
        while (1)
        {
            res = swh_next_aspect(SE_SUN, 0, pos1[0], jd1+corr, 120, 0, 0,
                flag, &jd1, pos2, err);
            if (res < 0) { return -1; }
            if (jd1+corr < jd2) { *years += 1; }
            else { break; }
        }
        *years += dec;
    }
    else if (jd1 > jd2) /* backward search */
    {
        dec = swe_difdegn(pos1[0], pos2[0]) / 360.0;
        while (1)
        {
            res = swh_next_aspect(SE_SUN, 0, pos1[0], jd1-corr, 120, 1, 0,
                flag, &jd1, pos2, err);
            if (res < 0) { return -1; }
            if (jd1-corr > jd2) { *years -= 1; }
            else { break; }
        }
        *years -= dec;
    }
    /* else equal julian days */
    return 0;
}

#ifdef __cplusplus
} /* extern "C" */
#endif
