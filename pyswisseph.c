/*
    This file is part of Pyswisseph.

    Copyright (c) 2007-2021 Stanislas Marquis <stan@astrorigin.com>

    Pyswisseph is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Pyswisseph is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with Pyswisseph.  If not, see <https://www.gnu.org/licenses/>.

*/

/**
 *  \file pyswisseph.c
 *
 *  Python extension to the Swiss Ephemeris
 *
 *  Author/maintainer: Stanislas Marquis <stan@astrorigin.com>
 *  Homepage: https://astrorigin.com/pyswisseph
 *
 *  Swisseph authors: Alois Treindl, Dieter Koch (et al.)
 *  Swisseph homepage: https://www.astro.com/swisseph
 *
 *  Swisseph version: 2.08.00
 *  Last revision: 2020-06-01
 */

#define PYSWISSEPH_VERSION      20210723

/* Set the default argument for set_ephe_path function */
#ifndef PYSWE_DEFAULT_EPHE_PATH
#ifdef WIN32
#define PYSWE_DEFAULT_EPHE_PATH     "C:\\swisseph"
#else
#define PYSWE_DEFAULT_EPHE_PATH     "/usr/share/swisseph:/usr/local/share/swisseph"
#endif
#endif /* PYSWE_DEFAULT_EPHE_PATH */

/* Wether to automaticly set ephemeris path on module import */
#ifndef PYSWE_AUTO_SET_EPHE_PATH
#define PYSWE_AUTO_SET_EPHE_PATH    1
#endif

/* Wether to build swephelp functions */
#ifndef PYSWE_USE_SWEPHELP
#define PYSWE_USE_SWEPHELP      1
#endif

/* Dont modify below */

#include <Python.h>
#include <swephexp.h>

#if PYSWE_USE_SWEPHELP
#include <swephelp.h>
#endif

/* Needed for compilation with Python < 2.4 */
#if PY_MAJOR_VERSION < 2 || (PY_MAJOR_VERSION == 2 && PY_MINOR_VERSION <= 3)
#define Py_RETURN_NONE Py_INCREF(Py_None); return Py_None;
#define Py_RETURN_TRUE Py_INCREF(Py_True); return Py_True;
#define Py_RETURN_FALSE Py_INCREF(Py_False); return Py_False;
#endif

/* Macros */
#define FUNCARGS_SELF       (PyObject *self)
#define FUNCARGS_KEYWDS     (PyObject *self, PyObject *args, PyObject *keywds)
#define PyModule_AddFloatConstant(m, nam, d) \
        PyModule_AddObject(m, nam, Py_BuildValue("d", d))

/* swisseph.Error (module exception type) */
static PyObject * pyswe_Error;

/* swisseph.azalt */
PyDoc_STRVAR(pyswe_azalt__doc__,
"Calculate horizontal coordinates (azimuth and altitude) of a planet or a star"
" from either ecliptical or equatorial coordinates.\n\n"
"Args: float tjdut, int calcflag, float geolon, float geolat, float geohei,"
" float x1, float x2, float x3, float atpress, float attemp\n"
"Return: (float azimuth, float true_altitude, float apparent_altitude)\n\n"
" - tjdut: julian day (UT)\n"
" - calcflag: either ECL2HOR (from ecliptical coord) or EQU2HOR (equatorial)\n"
" - geolon: geographical longitude\n"
" - geolat: geographical latitude\n"
" - geohei: geographical height\n"
" - x1: if calcflag==ECL2HOR, ecl. longitude. If EQU2HOR, right ascension.\n"
" - x2: if calcflag==ECL2HOR, ecl. latitude. If EQU2HOR, declination.\n"
" - x3: distance (not required)\n"
" - atpress: atmospheric pressure in mbar (hPa)\n"
" - attemp: atmospheric temperature in degrees Celsius\n"
" - azimuth: position degree, measured from south point to west\n"
" - true_altitude: true altitude above horizon in degrees\n"
" - apparent_altitude: apparent (refracted) altitude above horizon in degrees\n\n"
"The apparent altitude of a body depends on the atmospheric pressure and temperature."
" If only the true altitude is required, these parameters can be neglected.\n"
"If atpress is given the value 0, the function estimates the pressure from the"
" geographical altitude given in x3 and attemp. If x3 is 0, atpress will be"
" estimated for sea level.");

static PyObject * pyswe_azalt FUNCARGS_KEYWDS
{
    double jd, geo[3], xin[3], press, temp, xaz[3];
    int flag;
    static char *kwlist[] = {"tjdut", "calcflag", "geolon", "geolat", "geohei",
        "x1", "x2", "x3", "atpress", "attemp", NULL};
    xin[2] = 0.0;
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "didddddddd", kwlist,
        &jd, &flag, &geo[0], &geo[1], &geo[2], &xin[0], &xin[1], &xin[2],
        &press, &temp))
        return NULL;
    swe_azalt(jd, flag, geo, press, temp, xin, xaz);
    return Py_BuildValue("(ddd)", xaz[0], xaz[1], xaz[2]);
}

/* swisseph.azalt_rev */
PyDoc_STRVAR(pyswe_azalt_rev__doc__,
"Calculate either ecliptical or equatorial coordinates from azimuth and true"
" altitude.\n\n"
"Args: float tjdut, int calcflag, float geolon, float geolat, float geohei,"
" double azimuth, double true_altitude\n"
"Return: (float x1, float x2)\n\n"
" - tjdut: julian day (UT)\n"
" - calcflag: either HOR2ECL (to ecliptical coord) or HOR2EQU (to equatorial)\n"
" - geolon: geographical longitude\n"
" - geolat: geographical latitude\n"
" - geohei: geographical height\n"
" - azimuth: position degree, measured from south point to west\n"
" - true_altitude: true altitude above horizon in degrees\n"
" - x1, x2: ecliptical or equatorial coordinates, depending on calcflag\n\n"
"This function is not precisely the reverse of azalt(). It computes either"
" ecliptical or equatorial coordinates from azimuth and true altitude. If"
" only an apparent altitude is given, the true altitude has to be computed"
" first with the function refrac().");

static PyObject * pyswe_azalt_rev FUNCARGS_KEYWDS
{
    double jd, geo[3], xin[2], xout[2];
    int flag;
    static char *kwlist[] = {"tjdut", "calcflag", "geolon", "geolat", "geohei",
        "azimuth", "true_altitude", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "diddddd", kwlist,
        &jd, &flag, &geo[0], &geo[1], &geo[2], &xin[0], &xin[1]))
        return NULL;
    swe_azalt_rev(jd, flag, geo, xin, xout);
    return Py_BuildValue("(dd)", xout[0], xout[1]);
}

/* swisseph.calc */
PyDoc_STRVAR(pyswe_calc__doc__,
"Calculate planetary positions (ET).\n\n"
"Args: float tjdet, int planet, int flags=FLG_SWIEPH|FLG_SPEED\n"
"Return: ((float x1, x2, x3, x4, x5, x6), int retflags)\n\n"
" - tjdet: julian day, ephemeris time, where tjdet == tjdut + deltat(tjdut)\n"
" - planet: body number\n"
" - flags: bit flags indicating what kind of computation is wanted\n"
" - x1, x2, x3, x4, x5, x6: results\n"
" - retflags: bit flags indicating what kind of computation was done\n\n"
"This function can raise an exception (swisseph.Error) in case of fatal error.");

static PyObject * pyswe_calc FUNCARGS_KEYWDS
{
    double jd, val[6];
    int ret, ipl, flag = SEFLG_SWIEPH|SEFLG_SPEED;
    char err[256] = {0};
    static char *kwlist[] = {"tjdet", "planet", "flags", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "di|i", kwlist,
        &jd, &ipl, &flag))
        return NULL;
    ret = swe_calc(jd, ipl, flag, val, err);
    if (ret < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(dddddd)i",val[0],val[1],val[2],val[3],val[4],val[5],ret);
}

/* swisseph.calc_pctr */
PyDoc_STRVAR(pyswe_calc_pctr__doc__,
"Calculate planetocentric positions of planets (terrestrial time).\n\n"
"Args: float tjd, int planet, int center, int flags=FLG_SWIEPH|FLG_SPEED\n"
"Return: ((float x1, x2, x3, x4, x5, x6), int retflags)\n\n"
" - tjd: julian day in TT (ET)\n"
" - planet: body number of target object\n"
" - center: body number of center object\n"
" - flags: bit flags indicating what kind of computation is wanted\n"
" - x1, x2, x3, x4, x5, x6: results\n"
" - retflags: bit flags indicating what kind of computation was done\n\n"
"This function calculates planetocentric positions of planets, ie. positions as"
" observed from some different planet, eg. Jupiter-centric ephemerides. The"
" function can actually calculate any object as observed from any other object,"
" eg. also the position of some asteroid as observed from another asteroid or"
" from a planetary moon.\n"
"This function can raise an exception (swisseph.Error) in case of fatal error.");

static PyObject * pyswe_calc_pctr FUNCARGS_KEYWDS
{
    double jd, xx[6];
    int ret, ipl, iplctr, flag = SEFLG_SWIEPH|SEFLG_SPEED;
    char err[256] = {0};
    static char* kwlist[] = {"tjd", "planet", "center", "flags", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dii|i", kwlist,
        &jd, &ipl, &iplctr, &flag))
        return NULL;
    ret = swe_calc_pctr(jd, ipl, iplctr, flag, xx, err);
    if (ret < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(dddddd)i",xx[0],xx[1],xx[2],xx[3],xx[4],xx[5],ret);
}

/* swisseph.calc_ut */
PyDoc_STRVAR(pyswe_calc_ut__doc__,
"Calculate planetary positions (UT).\n\n"
"Args: float tjdut, int planet, int flags=FLG_SWIEPH|FLG_SPEED\n"
"Return: ((float x1, x2, x3, x4, x5, x6), int retflags)\n\n"
" - tjdut: julian day number, universla time\n"
" - planet: body number\n"
" - flags: bit flags indicating what kind of computation is wanted\n"
" - x1, x2, x3, x4, x5, x6: results\n"
" - retflags: bit flags indicating what kind of computation was done\n\n"
"Functions calc_ut() and calc() work exactly the same way except that calc()"
" requires Ephemeris Time (more accurately Terrestrial Time) as a parameter"
" whereas calc_ut() expects Universal Time (UT). For common astrological"
" calculations, you will only need calc_ut() and will not have to think any"
" more about the conversion between Universal Time and Ephemeris Time.\n"
"This function can raise an exception (swisseph.Error) in case of fatal error.");

static PyObject * pyswe_calc_ut FUNCARGS_KEYWDS
{
    double jd, xx[6];
    int ret, ipl, flag = SEFLG_SWIEPH|SEFLG_SPEED;
    char err[256] = {0};
    static char *kwlist[] = {"tjdut", "planet", "flags", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "di|i", kwlist,
        &jd, &ipl, &flag))
        return NULL;
    ret = swe_calc_ut(jd, ipl, flag, xx, err);
    if (ret < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(dddddd)i",xx[0],xx[1],xx[2],xx[3],xx[4],xx[5],ret);
}

/* swisseph.close */
PyDoc_STRVAR(pyswe_close__doc__,
"Close swiss ephemeris.\n\n"
"Args: -\n"
"Return: None");

static PyObject * pyswe_close FUNCARGS_SELF
{
    swe_close();
    Py_RETURN_NONE;
}

/* swisseph.cotrans */
PyDoc_STRVAR(pyswe_cotrans__doc__,
"Coordinate transformation from ecliptic to equator or vice-versa.\n\n"
"Args: float lon, float lat, float dist, float obliquity\n"
"Return: tuple of 3 float (longitude, latitude, distance)");

static PyObject * pyswe_cotrans FUNCARGS_KEYWDS
{
    double xpo[3], xpn[3], eps;
    static char *kwlist[] = {"lon", "lat", "dist", "obliquity", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dddd", kwlist,
        &xpo[0], &xpo[1], &xpo[2], &eps))
        return NULL;
    swe_cotrans(xpo, xpn, eps);
    return Py_BuildValue("(ddd)", xpn[0], xpn[1], xpn[2]);
}

/* swisseph.cotrans_sp */
PyDoc_STRVAR(pyswe_cotrans_sp__doc__,
"Coordinate transformation of position and speed, from ecliptic to equator"
" or vice-versa.\n\n"
"Args: float lon, float lat, float dist, float lonspeed, float latspeed,"
" float distspeed, float obliquity\n"
"Return: tuple of 6 float");

static PyObject * pyswe_cotrans_sp FUNCARGS_KEYWDS
{
    double xpo[6], xpn[6], eps;
    static char *kwlist[] = {"lon", "lat", "dist", "lonspeed",
        "latspeed", "distspeed", "obliquity", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ddddddd", kwlist,
        &xpo[0], &xpo[1], &xpo[2], &xpo[3], &xpo[4], &xpo[5], &eps))
        return NULL;
    swe_cotrans(xpo, xpn, eps);
    return Py_BuildValue("(dddddd)", xpn[0], xpn[1], xpn[2], xpn[3],
        xpn[4], xpn[5]);
}

/* swisseph.cs2degstr */
PyDoc_STRVAR(pyswe_cs2degstr__doc__,
"Get degrees string from centiseconds.\n\n"
"Args: int cs\n"
"Return: str");

static PyObject * pyswe_cs2degstr FUNCARGS_KEYWDS
{
    int cs;
    char ret[9];
    static char *kwlist[] = {"cs", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i", kwlist, &cs))
        return NULL;
    swe_cs2degstr(cs, ret);
    return Py_BuildValue("s", ret);
}

/* swisseph.cs2lonlatstr */
PyDoc_STRVAR(pyswe_cs2lonlatstr__doc__,
"Get longitude or latitude string from centiseconds.\n\n"
"Args: int cs, char plus, char minus\n"
"Return: str");

static PyObject * pyswe_cs2lonlatstr FUNCARGS_KEYWDS
{
    int cs;
    char ret[10], p, m;
    static char *kwlist[] = {"cs", "plus", "minus", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "icc", kwlist,
        &cs, &p, &m))
        return NULL;
    swe_cs2lonlatstr(cs, p, m, ret);
    return Py_BuildValue("s", ret);
}

/* swisseph.cs2timestr */
PyDoc_STRVAR(pyswe_cs2timestr__doc__,
"Get time string from centiseconds.\n\n"
"Args: int cs, char sep, bool suppresszero=True\n"
"Return: str");

static PyObject * pyswe_cs2timestr FUNCARGS_KEYWDS
{
    int cs, sep, suppresszero = 1;
    char ret[9];
    static char *kwlist[] = {"cs", "sep", "suppresszero", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ic|i", kwlist,
        &cs, &sep, &suppresszero))
        return NULL;
    swe_cs2timestr(cs, sep, suppresszero, ret);
    return Py_BuildValue("s", ret);
}

/* swisseph.csnorm */
PyDoc_STRVAR(pyswe_csnorm__doc__,
"Normalization of any centisecond number to the range [0;360].\n\n"
"Args: int x\n"
"Return: int");

static PyObject * pyswe_csnorm FUNCARGS_KEYWDS
{
    int x;
    static char *kwlist[] = {"x", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i", kwlist, &x))
        return NULL;
    return Py_BuildValue("i", swe_csnorm(x));
}

/* swisseph.csroundsec */
PyDoc_STRVAR(pyswe_csroundsec__doc__,
"Round centiseconds, but at 29.5959 always down.\n\n"
"Args: int x\n"
"Return: int");

static PyObject * pyswe_csroundsec FUNCARGS_KEYWDS
{
    int x;
    static char *kwlist[] = {"x", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i", kwlist, &x))
        return NULL;
    return Py_BuildValue("i", swe_csroundsec(x));
}

/* swisseph.d2l */
PyDoc_STRVAR(pyswe_d2l__doc__,
"Double to integer with rounding, no overflow check.\n\n"
"Args: float x\n"
"Return: int");

static PyObject * pyswe_d2l FUNCARGS_KEYWDS
{
    double x;
    static char *kwlist[] = {"x", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &x))
        return NULL;
    return Py_BuildValue("i", swe_d2l(x));
}

/* swisseph.date_conversion */
PyDoc_STRVAR(pyswe_date_conversion__doc__,
"Calculate Julian day number with check wether date is correct.\n\n"
"Args: int year, int month, int day, float hour=12.0, char cal='g'\n"
"Return: tuple (int result, float jd)");

static PyObject * pyswe_date_conversion FUNCARGS_KEYWDS
{
    int year, month, day, ret;
    double jd, hour = 12.0;
    char cal = 'g';
    static char *kwlist[] = {"year", "month", "day", "hour", "cal", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "iii|dc", kwlist,
        &year, &month, &day, &hour, &cal))
        return NULL;
    if (cal != 'g' && cal != 'j') {
        PyErr_SetString(pyswe_Error,
            "swisseph.date_conversion: Invalid calendar (g/j)");
        return NULL;
    }
    ret = swe_date_conversion(year, month, day, hour, cal, &jd);
    return Py_BuildValue("id", ret, jd);
}

/* swisseph.day_of_week */
PyDoc_STRVAR(pyswe_day_of_week__doc__,
"Calculate day of week number [0;6] from julian day number.\n\n"
"Args: float julday\n"
"Return: int");

static PyObject * pyswe_day_of_week FUNCARGS_KEYWDS
{
    double jd;
    static char *kwlist[] = {"julday", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &jd))
        return NULL;
    return Py_BuildValue("i", swe_day_of_week(jd));
}

/* swisseph.deg_midp */
PyDoc_STRVAR(pyswe_deg_midp__doc__,
"Calculate midpoint (in degrees).\n\n"
"Args: float x, float y\n"
"Return: float");

static PyObject * pyswe_deg_midp FUNCARGS_KEYWDS
{
    double x, y;
    static char *kwlist[] = {"x", "y", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dd", kwlist, &x, &y))
        return NULL;
    return Py_BuildValue("d", swe_deg_midp(x, y));
}

/* swisseph.degnorm */
PyDoc_STRVAR(pyswe_degnorm__doc__,
"Normalization of any degree number to the range [0;360].\n\n"
"Args: float x\n"
"Return: float");

static PyObject * pyswe_degnorm FUNCARGS_KEYWDS
{
    double x;
    static char *kwlist[] = {"x", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &x))
        return NULL;
    return Py_BuildValue("d", swe_degnorm(x));
}

/* swisseph.deltat */
PyDoc_STRVAR(pyswe_deltat__doc__,
"Calculate value of delta T.\n\n"
"Args: float julday\n"
"Return: float");

static PyObject * pyswe_deltat FUNCARGS_KEYWDS
{
    double jd;
    static char *kwlist[] = {"julday", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &jd))
        return NULL;
    return Py_BuildValue("d", swe_deltat(jd));
}

/* swisseph.difcs2n */
PyDoc_STRVAR(pyswe_difcs2n__doc__,
"Calculate distance in centisecs p1 - p2 normalized to [-180;180].\n\n"
"Args: int p1, int p2\n"
"Return: int");

static PyObject * pyswe_difcs2n FUNCARGS_KEYWDS
{
    int p1, p2;
    static char *kwlist[] = {"p1", "p2", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ii", kwlist, &p1, &p2))
        return NULL;
    return Py_BuildValue("i", swe_difcs2n(p1, p2));
}

/* swisseph.difcsn */
PyDoc_STRVAR(pyswe_difcsn__doc__,
"Calculate distance in centisecs p1 - p2.\n\n"
"Args: int p1, int p2\n"
"Return: int");

static PyObject * pyswe_difcsn FUNCARGS_KEYWDS
{
    int p1, p2;
    static char *kwlist[] = {"p1", "p2", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ii", kwlist, &p1, &p2))
        return NULL;
    return Py_BuildValue("i", swe_difcsn(p1, p2));
}

/* swisseph.difdeg2n */
PyDoc_STRVAR(pyswe_difdeg2n__doc__,
"Calculate distance in degrees p1 - p2 normalized to [-180;180].\n\n"
"Args: float p1, float p2\n"
"Return: float");

static PyObject * pyswe_difdeg2n FUNCARGS_KEYWDS
{
    double p1, p2;
    static char *kwlist[] = {"p1", "p2", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dd", kwlist, &p1, &p2))
        return NULL;
    return Py_BuildValue("d", swe_difdeg2n(p1, p2));
}

/* swisseph.difdegn */
PyDoc_STRVAR(pyswe_difdegn__doc__,
"Calculate distance in degrees p1 - p2.\n\n"
"Args: float p1, float p2\n"
"Return: float");

static PyObject * pyswe_difdegn FUNCARGS_KEYWDS
{
    double p1, p2;
    static char *kwlist[] = {"p1", "p2", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dd", kwlist, &p1, &p2))
        return NULL;
    return Py_BuildValue("d", swe_difdegn(p1, p2));
}

/* swisseph.difrad2n */
PyDoc_STRVAR(pyswe_difrad2n__doc__,
"Calculate distance in radians p1 - p2 normalized to [-180;180].\n\n"
"Args: float p1, float p2\n"
"Return: float");

static PyObject * pyswe_difrad2n FUNCARGS_KEYWDS
{
    double p1, p2;
    static char *kwlist[] = {"p1", "p2", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dd", kwlist, &p1, &p2))
        return NULL;
    return Py_BuildValue("d", swe_difrad2n(p1, p2));
}

/* swisseph.fixstar */
PyDoc_STRVAR(pyswe_fixstar__doc__,
"Calculate fixed star positions (ET).\n\n"
"Args: str star, float julday, int flag=FLG_SWIEPH\n"
"Return: tuple of 6 float, returned star name, and returned flags\n\n"
"Usage example:\n\n"
"\tres, stnam, flg = swisseph.fixstar(st, jd)");

static PyObject * pyswe_fixstar FUNCARGS_KEYWDS
{
    char *star, st[(SE_MAX_STNAME*2)+1], err[256];
    double jd, val[6];
    int ret, flag = SEFLG_SWIEPH;
    static char *kwlist[] = {"star", "julday", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "sd|i", kwlist,
        &star, &jd, &flag))
        return NULL;
    memset(st, 0, (SE_MAX_STNAME*2)+1);
    strncpy(st, star, SE_MAX_STNAME*2);
    ret = swe_fixstar(st, jd, flag, val, err);
    if (ret < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(dddddd)si",val[0],val[1],val[2],val[3],val[4],val[5],st,ret);
}

/* swisseph.fixstar2 */
PyDoc_STRVAR(pyswe_fixstar2__doc__,
"Calculate fixed star positions (fast) (ET).\n\n"
"Args: str star, float julday, int flag=FLG_SWIEPH\n"
"Return: tuple of 6 float, returned star name, and returned flags\n\n"
"Usage example:\n\n"
"\tres, stnam, flg = swisseph.fixstar2(st, jd)");

static PyObject * pyswe_fixstar2 FUNCARGS_KEYWDS
{
    char *star, st[(SE_MAX_STNAME*2)+1], err[256];
    double jd, val[6];
    int ret, flag = SEFLG_SWIEPH;
    static char *kwlist[] = {"star", "julday", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "sd|i", kwlist,
        &star, &jd, &flag))
        return NULL;
    memset(st, 0, (SE_MAX_STNAME*2)+1);
    strncpy(st, star, SE_MAX_STNAME*2);
    ret = swe_fixstar2(st, jd, flag, val, err);
    if (ret < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(dddddd)si",val[0],val[1],val[2],val[3],val[4],val[5],st,ret);
}

/* swisseph.fixstar2_mag */
PyDoc_STRVAR(pyswe_fixstar2_mag__doc__,
"Get fixed star magnitude (fast).\n\n"
"Args: str star\n"
"Return: float");

static PyObject * pyswe_fixstar2_mag FUNCARGS_KEYWDS
{
    char *star, st[41], err[256];
    int ret;
    double mag;
    static char *kwlist[] = {"star", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "s", kwlist, &star))
        return NULL;
    memset(st, 0, 41);
    strncpy(st, star, 40);
    ret = swe_fixstar2_mag(st, &mag, err);
    if (ret < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("d", mag);
}

/* swisseph.fixstar2_ut */
PyDoc_STRVAR(pyswe_fixstar2_ut__doc__,
"Calculate fixed star positions (fast) (UT).\n\n"
"Args: str star, float julday, int flag=FLG_SWIEPH\n"
"Return: tuple of 6 float, returned star name, and returned flags\n\n"
"Usage example:\n\n"
"\tres, stnam, flg = swisseph.fixstar2_ut(st, jd)");

static PyObject * pyswe_fixstar2_ut FUNCARGS_KEYWDS
{
    char *star, st[(SE_MAX_STNAME*2)+1], err[256];
    double jd, val[6];
    int ret, flag = SEFLG_SWIEPH;
    static char *kwlist[] = {"star", "julday", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "sd|i", kwlist,
        &star, &jd, &flag))
        return NULL;
    memset(st, 0, (SE_MAX_STNAME*2)+1);
    strncpy(st, star, SE_MAX_STNAME*2);
    ret = swe_fixstar2_ut(st, jd, flag, val, err);
    if (ret < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(dddddd)si",val[0],val[1],val[2],val[3],val[4],val[5],st,ret);
}

/* swisseph.fixstar_mag */
PyDoc_STRVAR(pyswe_fixstar_mag__doc__,
"Get fixed star magnitude.\n\n"
"Args: str star\n"
"Return: float");

static PyObject * pyswe_fixstar_mag FUNCARGS_KEYWDS
{
    char *star, st[41], err[256];
    int ret;
    double mag;
    static char *kwlist[] = {"star", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "s", kwlist, &star))
        return NULL;
    memset(st, 0, 41);
    strncpy(st, star, 40);
    ret = swe_fixstar_mag(st, &mag, err);
    if (ret < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("d", mag);
}

/* swisseph.fixstar_ut */
PyDoc_STRVAR(pyswe_fixstar_ut__doc__,
"Calculate fixed star positions (UT).\n\n"
"Args: str star, float julday, int flag=FLG_SWIEPH\n"
"Return: tuple of 6 float, returned star name, and returned flags\n\n"
"Usage example:\n\n"
"\tres, stnam, flg = swisseph.fixstar_ut(st, jd)");

static PyObject * pyswe_fixstar_ut FUNCARGS_KEYWDS
{
    char *star, st[(SE_MAX_STNAME*2)+1], err[256];
    double jd, val[6];
    int ret, flag = SEFLG_SWIEPH;
    static char *kwlist[] = {"star", "julday", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "sd|i", kwlist,
        &star, &jd, &flag))
        return NULL;
    memset(st, 0, (SE_MAX_STNAME*2)+1);
    strncpy(st, star, SE_MAX_STNAME*2);
    ret = swe_fixstar_ut(st, jd, flag, val, err);
    if (ret < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(dddddd)si",val[0],val[1],val[2],val[3],val[4],val[5],st,ret);
}

/* swisseph.gauquelin_sector */
PyDoc_STRVAR(pyswe_gauquelin_sector__doc__,
"Calculate Gauquelin sector position of a body (UT).\n\n"
"Args: float julday, int or str body, float lon, float lat, float alt,"
" float press=0, float temp=0, int method=0, int flag=FLG_SWIEPH\n"
"Return: float");

static PyObject * pyswe_gauquelin_sector FUNCARGS_KEYWDS
{
    double jd, geopos[3], res, ret, press = 0.0, temp = 0.0;
    int plt = 0, flag = SEFLG_SWIEPH, method = 0;
    char *star = "", err[256];
    PyObject *body;
    static char *kwlist[] = {"julday", "body", "lon", "lat", "alt", "press",
        "temp", "method", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dOddd|ddii", kwlist,
        &jd, &body, &geopos[0], &geopos[1], &geopos[2], &press, &temp, &method,
        &flag))
        return NULL;
    if (PyLong_CheckExact(body)) /* long -> planet */
        plt = (int) PyLong_AsLong(body);
#if PY_MAJOR_VERSION >= 3
    else if (PyUnicode_CheckExact(body)) /* unicode -> fixed star */
        star = (char*) PyUnicode_AsUTF8(body);
#elif PY_MAJOR_VERSION < 3
    else if (PyInt_CheckExact(body)) /* int -> planet */
        plt = (int) PyInt_AsLong(body);
    else if (PyString_CheckExact(body)) /* str -> fixed star */
        star = PyString_AsString(body);
#endif
    else {
        PyErr_SetString(pyswe_Error,
            "swisseph.gauquelin_sector: Invalid body type");
        return NULL;
    }
    res = swe_gauquelin_sector(jd, plt, star, flag, method, geopos, press,
        temp, &ret, err);
    if (res < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("d", ret);
}

/* swisseph.get_ayanamsa */
PyDoc_STRVAR(pyswe_get_ayanamsa__doc__,
"Calculate ayanamsa (ET).\n\n"
"Args: float julday\n"
"Return: float");

static PyObject * pyswe_get_ayanamsa FUNCARGS_KEYWDS
{
    double jd, ret;
    static char *kwlist[] = {"julday", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &jd))
        return NULL;
    ret = swe_get_ayanamsa(jd);
    return Py_BuildValue("d", ret);
}

/* swisseph.get_ayanamsa_name */
PyDoc_STRVAR(pyswe_get_ayanamsa_name__doc__,
"Get ayanamsa name from sidereal mode constant.\n\n"
"Args: int sidmode\n"
"Return: str");

static PyObject * pyswe_get_ayanamsa_name FUNCARGS_KEYWDS
{
    int mode;
    char *name;
    static char *kwlist[] = {"sidmode", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i", kwlist, &mode))
        return NULL;
    name = (char*) swe_get_ayanamsa_name(mode);
    return Py_BuildValue("s", name);
}

/* swisseph.get_ayanamsa_ut */
PyDoc_STRVAR(pyswe_get_ayanamsa_ut__doc__,
"Calculate ayanamsa (UT).\n\n"
"Args: float julday\n"
"Return: float");

static PyObject * pyswe_get_ayanamsa_ut FUNCARGS_KEYWDS
{
    double jd, ret;
    static char *kwlist[] = {"julday", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &jd))
        return NULL;
    ret = swe_get_ayanamsa_ut(jd);
    return Py_BuildValue("d", ret);
}

/* swisseph.get_current_file_data */
PyDoc_STRVAR(pyswe_get_current_file_data__doc__,
"Find start and end date of an se1 ephemeris file after a function call.\n\n"
"Args: int fno\n"
"Return: str path or None, float start, float end, int denum");

static PyObject * pyswe_get_current_file_data FUNCARGS_KEYWDS
{
    int fno, denum = 0;
    char* path = NULL;
    double start = 0, end = 0;
    static char* kwlist[] = {"fno", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i", kwlist, &fno))
        return NULL;
    path = (char*) swe_get_current_file_data(fno, &start, &end, &denum);
    return Py_BuildValue("sddi", path, start, end, denum);
}

/* swisseph.get_library_path */
PyDoc_STRVAR(pyswe_get_library_path__doc__,
"Find the path of the swisseph library (dll) actually in use.\n\n"
"Args: -\n"
"Return: str");

static PyObject * pyswe_get_library_path FUNCARGS_SELF
{
    char buf[256];
    memset(buf, 0, sizeof(char) * 256);
    return Py_BuildValue("s", swe_get_library_path(buf));
}

/* swisseph.get_planet_name */
PyDoc_STRVAR(pyswe_get_planet_name__doc__,
"Get planet name.\n\n"
"Args: int planet\n"
"Return: str");

static PyObject * pyswe_get_planet_name FUNCARGS_KEYWDS
{
    int ipl;
    char name[256];
    static char *kwlist[] = {"planet", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i", kwlist, &ipl))
        return NULL;
    swe_get_planet_name(ipl, name);
    return Py_BuildValue("s", name);
}

/* swisseph.get_orbital_elements */
PyDoc_STRVAR(pyswe_get_orbital_elements__doc__,
"Calculate osculating elements (Kepler elements) and orbital periods for a"
" planet, the Earth-Moon barycenter, or an asteroid.\n\n"
"Args: float jdet, int pl, int flag\n"
"Return: ");

static PyObject * pyswe_get_orbital_elements FUNCARGS_KEYWDS
{
    int i, pl, flg;
    double jd, dret[50];
    char err[256];
    static char *kwlist[] = {"jdet", "pl", "flag", NULL};
    memset(dret, 0, sizeof(double) * 50);
    if(!PyArg_ParseTupleAndKeywords(args, keywds, "dii", kwlist, &jd, &pl, &flg))
        return NULL;
    i = swe_get_orbital_elements(jd, pl, flg, dret, err);
    if (i == 0)
        return Py_BuildValue("dddddddddddddddddddddddddddddddddddddddddddddddddd",
            dret[0],dret[1],dret[2],dret[3],dret[4],dret[5],dret[6],dret[7],dret[8],dret[9],
            dret[10],dret[11],dret[12],dret[13],dret[14],dret[15],dret[16],dret[17],dret[18],dret[19],
            dret[20],dret[21],dret[22],dret[23],dret[24],dret[25],dret[26],dret[27],dret[28],dret[29],
            dret[30],dret[31],dret[32],dret[33],dret[34],dret[35],dret[36],dret[37],dret[38],dret[39],
            dret[40],dret[41],dret[42],dret[43],dret[44],dret[45],dret[46],dret[47],dret[48],dret[49]);
    PyErr_SetString(pyswe_Error, err);
    return NULL;
}

/* swisseph.get_tid_acc */
PyDoc_STRVAR(pyswe_get_tid_acc__doc__,
"Get tidal acceleration.\n\n"
"Args: -\n"
"Return: float");

static PyObject * pyswe_get_tid_acc FUNCARGS_SELF
{
    return Py_BuildValue("d", swe_get_tid_acc());
}

/* swisseph.heliacal_pheno_ut */
PyDoc_STRVAR(pyswe_heliacal_pheno_ut__doc__,
"Provides data that are relevant for the calculation of heliacal risings and settings.\n\n"
"Args: float jd_start, seq geopos, seq atmo, seq observer, str object, int eventtype, int helflag\n"
"Return: tuple of 50 float");

static PyObject * pyswe_heliacal_pheno_ut FUNCARGS_KEYWDS
{
    double jdstart, geopos[3], atmo[4], observ[6], dret[50];
    char serr[255], *obj = 0; /* dummy assign */
    int i, evnt, flg;
    PyObject *o1=0, *o2=0, *o3=0, *o4, *o5, *o6, *o7, *o8, *o9;
    memset(dret, 0, sizeof(double) * 50);
    static char *kwlist[] = {"jd_start", "geopos", "atmo", "observer", "object",
        "eventtype", "helflag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dOOOsii", kwlist,
        &jdstart, &o1, &o2, &o3, &obj, &evnt, &flg))
        return NULL;
    if (!PySequence_Check(o1) || PySequence_Length(o1) != 3) {
        PyErr_SetString(pyswe_Error, "Invalid geopos sequence");
        return NULL;
    }
    else {
        o4 = PySequence_ITEM(o1, 0);
        o5 = PySequence_ITEM(o1, 1);
        o6 = PySequence_ITEM(o1, 2);
        if (!PyNumber_Check(o4) || !PyNumber_Check(o5) || !PyNumber_Check(o6)) {
            PyErr_SetString(pyswe_Error, "Invalid geopos value type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
            return NULL;
        }
        /* checking longitude */
        if (PyFloat_Check(o4))
            geopos[0] = PyFloat_AsDouble(o4);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
            geopos[0] = (double) PyInt_AsLong(o4);
#endif
        else if (PyLong_Check(o4))
            geopos[0] = (double) PyLong_AsLong(o4);
        else {
            PyErr_SetString(pyswe_Error, "Invalid longitude type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
            return NULL;
        }
        /* checking latitude */
        if (PyFloat_Check(o5))
            geopos[1] = PyFloat_AsDouble(o5);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
            geopos[1] = (double) PyInt_AsLong(o5);
#endif
        else if (PyLong_Check(o5))
            geopos[1] = (double) PyLong_AsLong(o5);
        else {
            PyErr_SetString(pyswe_Error, "Invalid latitude type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
            return NULL;
        }
        /* checking altitude */
        if (PyFloat_Check(o6))
            geopos[2] = PyFloat_AsDouble(o6);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
            geopos[2] = (double) PyInt_AsLong(o6);
#endif
        else if (PyLong_Check(o6))
            geopos[2] = (double) PyLong_AsLong(o6);
        else {
            PyErr_SetString(pyswe_Error, "Invalid altitude type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
            return NULL;
        }
        Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
    }
    if (!PySequence_Check(o2) || PySequence_Length(o2) != 4) {
        PyErr_SetString(pyswe_Error, "Invalid atmospheric sequence");
        return NULL;
    }
    else {
        o4 = PySequence_ITEM(o2, 0);
        o5 = PySequence_ITEM(o2, 1);
        o6 = PySequence_ITEM(o2, 2);
        o7 = PySequence_ITEM(o2, 3);
        if (!PyNumber_Check(o4) || !PyNumber_Check(o5) || !PyNumber_Check(o6)
            || !PyNumber_Check(o7)) {
            PyErr_SetString(pyswe_Error, "Invalid atmospheric value type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }
        /* atmospheric pressure */
        if (PyFloat_Check(o4))
            atmo[0] = PyFloat_AsDouble(o4);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o4))
            atmo[0] = (double) PyInt_AsLong(o4);
#endif
        else if (PyLong_Check(o4))
            atmo[0] = (double) PyLong_AsLong(o4);
        else {
            PyErr_SetString(pyswe_Error, "Invalid atmospheric pressure");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }
        /* atmospheric temperature */
        if (PyFloat_Check(o5))
            atmo[1] = PyFloat_AsDouble(o5);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
            atmo[1] = (double) PyInt_AsLong(o5);
#endif
        else if (PyLong_Check(o5))
            atmo[1] = (double) PyLong_AsLong(o5);
        else {
            PyErr_SetString(pyswe_Error, "Invalid atmospheric temperature");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }
        /* humidity */
        if (PyFloat_Check(o6))
            atmo[2] = PyFloat_AsDouble(o6);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o6))
            atmo[2] = (double) PyInt_AsLong(o6);
#endif
        else if (PyLong_Check(o6))
            atmo[2] = (double) PyLong_AsLong(o6);
        else {
            PyErr_SetString(pyswe_Error, "Invalid humidity");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }
        /* meteorological range */
        if (PyFloat_Check(o7))
            atmo[3] = PyFloat_AsDouble(o7);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o7))
            atmo[3] = (double) PyInt_AsLong(o7);
#endif
        else if (PyLong_Check(o7))
            atmo[3] = (double) PyLong_AsLong(o7);
        else {
            PyErr_SetString(pyswe_Error, "Invalid meteorological range");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }
        Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
    }
    if (!PySequence_Check(o3) || PySequence_Length(o3) != 6) {
        PyErr_SetString(pyswe_Error, "Invalid observer sequence");
        return NULL;
    }
    else {
        o4 = PySequence_ITEM(o3, 0);
        o5 = PySequence_ITEM(o3, 1);
        o6 = PySequence_ITEM(o3, 2);
        o7 = PySequence_ITEM(o3, 3);
        o8 = PySequence_ITEM(o3, 4);
        o9 = PySequence_ITEM(o3, 5);
        if (!PyNumber_Check(o4) || !PyNumber_Check(o5) || !PyNumber_Check(o6)
            || !PyNumber_Check(o7) || !PyNumber_Check(o8) || !PyNumber_Check(o9)) {
            PyErr_SetString(pyswe_Error, "Invalid observer value type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }
        /* observer age */
        if (PyFloat_Check(o4))
            observ[0] = PyFloat_AsDouble(o4);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o4))
            observ[0] = (double) PyInt_AsLong(o4);
#endif
        else if (PyLong_Check(o4))
            observ[0] = (double) PyLong_AsLong(o4);
        else {
            PyErr_SetString(pyswe_Error, "Invalid observer age");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }
        /* snellen ratio */
        if (PyFloat_Check(o5))
            observ[1] = PyFloat_AsDouble(o5);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
            observ[1] = (double) PyInt_AsLong(o5);
#endif
        else if (PyLong_Check(o5))
            observ[1] = (double) PyLong_AsLong(o5);
        else {
            PyErr_SetString(pyswe_Error, "Invalid snellen ratio");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }
        /* mono/binocular */
        if (PyFloat_Check(o6))
            observ[2] = PyFloat_AsDouble(o6);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o6))
            observ[2] = (double) PyInt_AsLong(o6);
#endif
        else if (PyLong_Check(o6))
            observ[2] = (double) PyLong_AsLong(o6);
        else {
            PyErr_SetString(pyswe_Error, "Invalid telescope");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }
        /* telescope magnification */
        if (PyFloat_Check(o7))
            observ[3] = PyFloat_AsDouble(o7);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o7))
            observ[3] = (double) PyInt_AsLong(o7);
#endif
        else if (PyLong_Check(o7))
            observ[3] = (double) PyLong_AsLong(o7);
        else {
            PyErr_SetString(pyswe_Error, "Invalid telescope magnification");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }
        /* optical aperture */
        if (PyFloat_Check(o8))
            observ[4] = PyFloat_AsDouble(o8);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o8))
            observ[4] = (double) PyInt_AsLong(o8);
#endif
        else if (PyLong_Check(o8))
            observ[4] = (double) PyLong_AsLong(o8);
        else {
            PyErr_SetString(pyswe_Error, "Invalid telescope aperture");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }
        /* optical transmission */
        if (PyFloat_Check(o9))
            observ[5] = PyFloat_AsDouble(o9);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o9))
            observ[5] = (double) PyInt_AsLong(o9);
#endif
        else if (PyLong_Check(o9))
            observ[5] = (double) PyLong_AsLong(o9);
        else {
            PyErr_SetString(pyswe_Error, "Invalid telescope aperture");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }
        Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
        Py_DECREF(o8); Py_DECREF(o9);
    }
    i = swe_heliacal_pheno_ut(jdstart, geopos, atmo, observ, obj, evnt, flg, dret, serr);
    if (i == 0)
        return Py_BuildValue("dddddddddddddddddddddddddddddddddddddddddddddddddd",
            dret[0],dret[1],dret[2],dret[3],dret[4],dret[5],dret[6],dret[7],dret[8],dret[9],
            dret[10],dret[11],dret[12],dret[13],dret[14],dret[15],dret[16],dret[17],dret[18],dret[19],
            dret[20],dret[21],dret[22],dret[23],dret[24],dret[25],dret[26],dret[27],dret[28],dret[29],
            dret[30],dret[31],dret[32],dret[33],dret[34],dret[35],dret[36],dret[37],dret[38],dret[39],
            dret[40],dret[41],dret[42],dret[43],dret[44],dret[45],dret[46],dret[47],dret[48],dret[49]);
    PyErr_SetString(pyswe_Error, serr);
    return NULL;
}

/* swisseph.heliacal_ut */
PyDoc_STRVAR(pyswe_heliacal_ut__doc__,
"Find the Julian day of the next heliacal phenomenon after a given start date.\n"
"It works between geographic latitudes 60s - 60n.\n\n"
"Args: float jd_start, seq geopos, seq atmo, seq observer, str object,"
" int eventtype, int helflag\n"
"Return: tuple with 3 julian days");

static PyObject * pyswe_heliacal_ut FUNCARGS_KEYWDS
{
    double jdstart, geopos[3], atmo[4], observ[6], dret[3];
    char serr[255], *obj = 0; /* dummy assign */
    int i, evnt, flg;
    PyObject *o1=0, *o2=0, *o3=0, *o4, *o5, *o6, *o7, *o8, *o9;
    static char *kwlist[] = {"jd_start", "geopos", "atmo", "observer", "object",
        "eventtype", "helflag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dOOOsii", kwlist,
        &jdstart, &o1, &o2, &o3, &obj, &evnt, &flg))
        return NULL;
    if (!PySequence_Check(o1) || PySequence_Length(o1) != 3) {
        PyErr_SetString(pyswe_Error, "Invalid geopos sequence");
        return NULL;
    }
    else {
        o4 = PySequence_ITEM(o1, 0);
        o5 = PySequence_ITEM(o1, 1);
        o6 = PySequence_ITEM(o1, 2);
        if (!PyNumber_Check(o4) || !PyNumber_Check(o5) || !PyNumber_Check(o6)) {
            PyErr_SetString(pyswe_Error, "Invalid geopos value type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
            return NULL;
        }
        /* checking longitude */
        if (PyFloat_Check(o4))
            geopos[0] = PyFloat_AsDouble(o4);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
            geopos[0] = (double) PyInt_AsLong(o4);
#endif
        else if (PyLong_Check(o4))
            geopos[0] = (double) PyLong_AsLong(o4);
        else {
            PyErr_SetString(pyswe_Error, "Invalid longitude type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
            return NULL;
        }
        /* checking latitude */
        if (PyFloat_Check(o5))
            geopos[1] = PyFloat_AsDouble(o5);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
            geopos[1] = (double) PyInt_AsLong(o5);
#endif
        else if (PyLong_Check(o5))
            geopos[1] = (double) PyLong_AsLong(o5);
        else {
            PyErr_SetString(pyswe_Error, "Invalid latitude type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
            return NULL;
        }
        /* checking altitude */
        if (PyFloat_Check(o6))
            geopos[2] = PyFloat_AsDouble(o6);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
            geopos[2] = (double) PyInt_AsLong(o6);
#endif
        else if (PyLong_Check(o6))
            geopos[2] = (double) PyLong_AsLong(o6);
        else {
            PyErr_SetString(pyswe_Error, "Invalid altitude type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
            return NULL;
        }
        Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
    }
    if (!PySequence_Check(o2) || PySequence_Length(o2) != 4) {
        PyErr_SetString(pyswe_Error, "Invalid atmospheric sequence");
        return NULL;
    }
    else {
        o4 = PySequence_ITEM(o2, 0);
        o5 = PySequence_ITEM(o2, 1);
        o6 = PySequence_ITEM(o2, 2);
        o7 = PySequence_ITEM(o2, 3);
        if (!PyNumber_Check(o4) || !PyNumber_Check(o5) || !PyNumber_Check(o6)
            || !PyNumber_Check(o7)) {
            PyErr_SetString(pyswe_Error, "Invalid atmospheric value type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }
        /* atmospheric pressure */
        if (PyFloat_Check(o4))
            atmo[0] = PyFloat_AsDouble(o4);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o4))
            atmo[0] = (double) PyInt_AsLong(o4);
#endif
        else if (PyLong_Check(o4))
            atmo[0] = (double) PyLong_AsLong(o4);
        else {
            PyErr_SetString(pyswe_Error, "Invalid atmospheric pressure");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }
        /* atmospheric temperature */
        if (PyFloat_Check(o5))
            atmo[1] = PyFloat_AsDouble(o5);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
            atmo[1] = (double) PyInt_AsLong(o5);
#endif
        else if (PyLong_Check(o5))
            atmo[1] = (double) PyLong_AsLong(o5);
        else {
            PyErr_SetString(pyswe_Error, "Invalid atmospheric temperature");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }
        /* humidity */
        if (PyFloat_Check(o6))
            atmo[2] = PyFloat_AsDouble(o6);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o6))
            atmo[2] = (double) PyInt_AsLong(o6);
#endif
        else if (PyLong_Check(o6))
            atmo[2] = (double) PyLong_AsLong(o6);
        else {
            PyErr_SetString(pyswe_Error, "Invalid humidity");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }
        /* meteorological range */
        if (PyFloat_Check(o7))
            atmo[3] = PyFloat_AsDouble(o7);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o7))
            atmo[3] = (double) PyInt_AsLong(o7);
#endif
        else if (PyLong_Check(o7))
            atmo[3] = (double) PyLong_AsLong(o7);
        else {
            PyErr_SetString(pyswe_Error, "Invalid meteorological range");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }
        Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
    }

    if (!PySequence_Check(o3) || PySequence_Length(o3) != 6) {
        PyErr_SetString(pyswe_Error, "Invalid observer sequence");
        return NULL;
    }
    else {
        o4 = PySequence_ITEM(o3, 0);
        o5 = PySequence_ITEM(o3, 1);
        o6 = PySequence_ITEM(o3, 2);
        o7 = PySequence_ITEM(o3, 3);
        o8 = PySequence_ITEM(o3, 4);
        o9 = PySequence_ITEM(o3, 5);
        if (!PyNumber_Check(o4) || !PyNumber_Check(o5) || !PyNumber_Check(o6)
            || !PyNumber_Check(o7) || !PyNumber_Check(o8) || !PyNumber_Check(o9)) {
            PyErr_SetString(pyswe_Error, "Invalid observer value type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }
        /* observer age */
        if (PyFloat_Check(o4))
            observ[0] = PyFloat_AsDouble(o4);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o4))
            observ[0] = (double) PyInt_AsLong(o4);
#endif
        else if (PyLong_Check(o4))
            observ[0] = (double) PyLong_AsLong(o4);
        else {
            PyErr_SetString(pyswe_Error, "Invalid observer age");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }
        /* snellen ratio */
        if (PyFloat_Check(o5))
            observ[1] = PyFloat_AsDouble(o5);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
            observ[1] = (double) PyInt_AsLong(o5);
#endif
        else if (PyLong_Check(o5))
            observ[1] = (double) PyLong_AsLong(o5);
        else {
            PyErr_SetString(pyswe_Error, "Invalid snellen ratio");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }
        /* mono/binocular */
        if (PyFloat_Check(o6))
            observ[2] = PyFloat_AsDouble(o6);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o6))
            observ[2] = (double) PyInt_AsLong(o6);
#endif
        else if (PyLong_Check(o6))
            observ[2] = (double) PyLong_AsLong(o6);
        else {
            PyErr_SetString(pyswe_Error, "Invalid telescope");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }
        /* telescope magnification */
        if (PyFloat_Check(o7))
            observ[3] = PyFloat_AsDouble(o7);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o7))
            observ[3] = (double) PyInt_AsLong(o7);
#endif
        else if (PyLong_Check(o7))
            observ[3] = (double) PyLong_AsLong(o7);
        else {
            PyErr_SetString(pyswe_Error, "Invalid telescope magnification");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }
        /* optical aperture */
        if (PyFloat_Check(o8))
            observ[4] = PyFloat_AsDouble(o8);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o8))
            observ[4] = (double) PyInt_AsLong(o8);
#endif
        else if (PyLong_Check(o8))
            observ[4] = (double) PyLong_AsLong(o8);
        else {
            PyErr_SetString(pyswe_Error, "Invalid telescope aperture");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }
        /* optical transmission */
        if (PyFloat_Check(o9))
            observ[5] = PyFloat_AsDouble(o9);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o9))
            observ[5] = (double) PyInt_AsLong(o9);
#endif
        else if (PyLong_Check(o9))
            observ[5] = (double) PyLong_AsLong(o9);
        else {
            PyErr_SetString(pyswe_Error, "Invalid telescope aperture");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }
        Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
        Py_DECREF(o8); Py_DECREF(o9);
    }
    i = swe_heliacal_ut(jdstart, geopos, atmo, observ, obj, evnt, flg, dret, serr);
    if (i == 0)
        return Py_BuildValue("ddd", dret[0], dret[1], dret[2]);
    PyErr_SetString(pyswe_Error, serr);
    return NULL;
}

/* swisseph.house_name */
PyDoc_STRVAR(pyswe_house_name__doc__,
"Get the name of the house method.\n\n"
"Args: char hsys\n"
"Return: house system name");

static PyObject * pyswe_house_name FUNCARGS_KEYWDS
{
    char hsys;
    static char *kwlist[] = {"hsys", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "c", kwlist, &hsys))
        return NULL;
    return Py_BuildValue("s", swe_house_name(hsys));
}

/* swisseph.house_pos */
PyDoc_STRVAR(pyswe_house_pos__doc__,
"Calculate house position of a body.\n\n"
"Args: float armc, float geolat, float obliquity, float objlon,"
" float objlat=0.0, char hsys='P'\n"
"Return: float");

static PyObject * pyswe_house_pos FUNCARGS_KEYWDS
{
    double armc, lat, obl, res;
    double obj[] = {0.0, 0.0};
    int hsys = 'P';
    char err[256];
    static char *kwlist[] = {"armc", "geolat", "obliquity", "objlon", "objlat",
        "hsys", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dddd|dc", kwlist,
        &armc, &lat, &obl, &obj[0], &obj[1], &hsys))
        return NULL;
    res = swe_house_pos(armc, lat, obl, hsys, obj, err);
    if (res < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("d", res);
}

/* swisseph.houses */
PyDoc_STRVAR(pyswe_houses__doc__,
"Calculate houses cusps (UT).\n\n"
"Args: float julday, float lat, float lon, char hsys='P'\n"
"Return: 2 tuples of 12 and 8 float (cusps, ascmc) (except Gauquelin)");

static PyObject * pyswe_houses FUNCARGS_KEYWDS
{
    double jd, lat, lon, cusps[37], ascmc[10];
    int ret, hsys = 'P';
    static char *kwlist[] = {"julday", "lat", "lon", "hsys", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ddd|c", kwlist,
        &jd, &lat, &lon, &hsys))
        return NULL;
    ret = swe_houses(jd, lat, lon, hsys, cusps, ascmc);
    if (ret < 0) {
        PyErr_SetString(pyswe_Error, "swisseph.houses: error while computing");
        return NULL;
    }
    if (hsys == 71) /* Gauquelin houses */
        return Py_BuildValue("(dddddddddddddddddddddddddddddddddddd)(dddddddd)",
        cusps[1],cusps[2],cusps[3],cusps[4],cusps[5],cusps[6],cusps[7],cusps[8],
        cusps[9],cusps[10],cusps[11],cusps[12],cusps[13],cusps[14],cusps[15],
        cusps[16],cusps[17],cusps[18],cusps[19],cusps[20],cusps[21],cusps[22],
        cusps[23],cusps[24],cusps[25],cusps[26],cusps[27],cusps[28],cusps[29],
        cusps[30],cusps[31],cusps[32],cusps[33],cusps[34],cusps[35],cusps[36],
        ascmc[0],ascmc[1],ascmc[2],ascmc[3],ascmc[4],ascmc[5],ascmc[6],ascmc[7]);
    return Py_BuildValue("(dddddddddddd)(dddddddd)", cusps[1],cusps[2],
    cusps[3],cusps[4],cusps[5],cusps[6],cusps[7],cusps[8],cusps[9],cusps[10],
    cusps[11],cusps[12],ascmc[0],ascmc[1],ascmc[2],ascmc[3],ascmc[4],ascmc[5],
    ascmc[6],ascmc[7]);
}

/* swisseph.houses_armc */
PyDoc_STRVAR(pyswe_houses_armc__doc__,
"Calculate houses cusps with ARMC.\n\n"
"Args: float armc, float lat, float obliquity, char hsys='P'\n"
"Return: 2 tuples of 12 and 8 float (cusps, ascmc) (except Gauquelin)");

static PyObject * pyswe_houses_armc FUNCARGS_KEYWDS
{
    double armc, lat, obl, cusps[37], ascmc[10];
    int ret, hsys = 'P';
    static char *kwlist[] = {"armc", "lat", "obliquity", "hsys", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ddd|c", kwlist,
        &armc, &lat, &obl, &hsys))
        return NULL;
    ret = swe_houses_armc(armc, lat, obl, hsys, cusps, ascmc);
    if (ret < 0) {
        PyErr_SetString(pyswe_Error, "swisseph.houses_armc: error while computing");
        return NULL;
    }
    if (hsys == 71) /* Gauquelin houses */
        return Py_BuildValue("(dddddddddddddddddddddddddddddddddddd)(dddddddd)",
        cusps[1],cusps[2],cusps[3],cusps[4],cusps[5],cusps[6],cusps[7],cusps[8],
        cusps[9],cusps[10],cusps[11],cusps[12],cusps[13],cusps[14],cusps[15],
        cusps[16],cusps[17],cusps[18],cusps[19],cusps[20],cusps[21],cusps[22],
        cusps[23],cusps[24],cusps[25],cusps[26],cusps[27],cusps[28],cusps[29],
        cusps[30],cusps[31],cusps[32],cusps[33],cusps[34],cusps[35],cusps[36],
        ascmc[0],ascmc[1],ascmc[2],ascmc[3],ascmc[4],ascmc[5],ascmc[6],ascmc[7]);
    return Py_BuildValue("(dddddddddddd)(dddddddd)", cusps[1],cusps[2],
    cusps[3],cusps[4],cusps[5],cusps[6],cusps[7],cusps[8],cusps[9],
    cusps[10],cusps[11],cusps[12],ascmc[0],ascmc[1],ascmc[2],ascmc[3],
    ascmc[4],ascmc[5],ascmc[6],ascmc[7]);
}

/* swisseph.houses_armc_ex2 */
PyDoc_STRVAR(pyswe_houses_armc_ex2__doc__,
"Calculate houses cusps and speeds with ARMC.\n\n"
"Args: float armc, float lat, float obliquity, char hsys='P'\n"
"Return: 4 tuples of 12 and 8 float (cusps, ascmc, cusps_speed, ascmc_speed)");

static PyObject * pyswe_houses_armc_ex2 FUNCARGS_KEYWDS
{
    double armc, lat, obl, cusps[37], ascmc[10], cuspspeed[37], ascmcspeed[10];
    int ret, hsys = 'P';
    char err[256] = {0};
    static char *kwlist[] = {"armc", "lat", "obliquity", "hsys", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ddd|c", kwlist,
        &armc, &lat, &obl, &hsys))
        return NULL;
    ret = swe_houses_armc_ex2(armc, lat, obl, hsys, cusps, ascmc,
                              cuspspeed, ascmcspeed, err);
    if (ret < 0)
        return PyErr_Format(pyswe_Error, "swisseph.houses_armc_ex2: %s", err);
    if (hsys == 71) /* Gauquelin sectors */
        return Py_BuildValue("(dddddddddddddddddddddddddddddddddddd)(dddddddd)"
                             "(dddddddddddddddddddddddddddddddddddd)(dddddddd)",
        cusps[1],cusps[2],cusps[3],cusps[4],cusps[5],cusps[6],cusps[7],cusps[8],
        cusps[9],cusps[10],cusps[11],cusps[12],cusps[13],cusps[14],cusps[15],
        cusps[16],cusps[17],cusps[18],cusps[19],cusps[20],cusps[21],cusps[22],
        cusps[23],cusps[24],cusps[25],cusps[26],cusps[27],cusps[28],cusps[29],
        cusps[30],cusps[31],cusps[32],cusps[33],cusps[34],cusps[35],cusps[36],
        ascmc[0],ascmc[1],ascmc[2],ascmc[3],ascmc[4],ascmc[5],ascmc[6],ascmc[7],
        cuspspeed[1],cuspspeed[2],cuspspeed[3],cuspspeed[4],cuspspeed[5],
        cuspspeed[6],cuspspeed[7],cuspspeed[8],cuspspeed[9],cuspspeed[10],
        cuspspeed[11],cuspspeed[12],cuspspeed[13],cuspspeed[14],cuspspeed[15],
        cuspspeed[16],cuspspeed[17],cuspspeed[18],cuspspeed[19],cuspspeed[20],
        cuspspeed[21],cuspspeed[22],cuspspeed[23],cuspspeed[24],cuspspeed[25],
        cuspspeed[26],cuspspeed[27],cuspspeed[28],cuspspeed[29],cuspspeed[30],
        cuspspeed[31],cuspspeed[32],cuspspeed[33],cuspspeed[34],cuspspeed[35],
        cuspspeed[36],ascmcspeed[0],ascmcspeed[1],ascmcspeed[2],ascmcspeed[3],
        ascmcspeed[4],ascmcspeed[5],ascmcspeed[6],ascmcspeed[7]);
    return Py_BuildValue("(dddddddddddd)(dddddddd)(dddddddddddd)(dddddddd)",
    cusps[1],cusps[2],cusps[3],cusps[4],cusps[5],cusps[6],cusps[7],cusps[8],
    cusps[9],cusps[10],cusps[11],cusps[12],ascmc[0],ascmc[1],ascmc[2],ascmc[3],
    ascmc[4],ascmc[5],ascmc[6],ascmc[7],cuspspeed[1],cuspspeed[2],cuspspeed[3],
    cuspspeed[4],cuspspeed[5],cuspspeed[6],cuspspeed[7],cuspspeed[8],
    cuspspeed[9],cuspspeed[10],cuspspeed[11],cuspspeed[12],ascmcspeed[0],
    ascmcspeed[1],ascmcspeed[2],ascmcspeed[3],ascmcspeed[4],ascmcspeed[5],
    ascmcspeed[6],ascmcspeed[7]);
}

/* swisseph.houses_ex */
PyDoc_STRVAR(pyswe_houses_ex__doc__,
"Calculate houses cusps (extended) (UT).\n\n"
"Args: float julday, float lat, float lon, char hsys='P', int flag=0\n"
"Return: 2 tuples of 12 and 8 float (cusps, ascmc) (except Gauquelin)");

static PyObject * pyswe_houses_ex FUNCARGS_KEYWDS
{
    double jd, lat, lon, cusps[37], ascmc[10];
    int ret, hsys = 'P', flag = 0;
    static char *kwlist[] = {"julday", "lat", "lon", "hsys", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ddd|ci", kwlist,
        &jd, &lat, &lon, &hsys, &flag))
        return NULL;
    ret = swe_houses_ex(jd, flag, lat, lon, hsys, cusps, ascmc);
    if (ret < 0) {
        PyErr_SetString(pyswe_Error, "swisseph.houses_ex: error while computing");
        return NULL;
    }
    if (hsys == 71) /* Gauquelin houses */
        return Py_BuildValue("(dddddddddddddddddddddddddddddddddddd)(dddddddd)",
        cusps[1],cusps[2],cusps[3],cusps[4],cusps[5],cusps[6],cusps[7],cusps[8],
        cusps[9],cusps[10],cusps[11],cusps[12],cusps[13],cusps[14],cusps[15],
        cusps[16],cusps[17],cusps[18],cusps[19],cusps[20],cusps[21],cusps[22],
        cusps[23],cusps[24],cusps[25],cusps[26],cusps[27],cusps[28],cusps[29],
        cusps[30],cusps[31],cusps[32],cusps[33],cusps[34],cusps[35],cusps[36],
        ascmc[0],ascmc[1],ascmc[2],ascmc[3],ascmc[4],ascmc[5],ascmc[6],ascmc[7]);
    return Py_BuildValue("(dddddddddddd)(dddddddd)", cusps[1],cusps[2],
    cusps[3],cusps[4],cusps[5],cusps[6],cusps[7],cusps[8],cusps[9],
    cusps[10],cusps[11],cusps[12],ascmc[0],ascmc[1],ascmc[2],ascmc[3],
    ascmc[4],ascmc[5],ascmc[6],ascmc[7]);
}

/* swisseph.houses_ex2 */
PyDoc_STRVAR(pyswe_houses_ex2__doc__,
"Calculate houses cusps and cusps speeds (UT).\n\n"
"Args: float julday, float lat, float lon, char hsys='P', int flag=0\n"
"Return: 4 tuples of 12 and 8 float (cusps, ascmc, cusps_speed, ascmc_speed)");

static PyObject * pyswe_houses_ex2 FUNCARGS_KEYWDS
{
    double jd, lat, lon, cusps[37], ascmc[10], cuspspeed[37], ascmcspeed[10];
    int ret, hsys = 'P', flag = 0;
    char err[256] = {0};
    static char *kwlist[] = {"julday", "lat", "lon", "hsys", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ddd|ci", kwlist,
        &jd, &lat, &lon, &hsys, &flag))
        return NULL;
    ret = swe_houses_ex2(jd, flag, lat, lon, hsys, cusps, ascmc,
                         cuspspeed, ascmcspeed, err);
    if (ret < 0)
        return PyErr_Format(pyswe_Error, "swisseph.houses_ex2: %s", err);
    if (hsys == 71) /* Gauquelin sectors */
        return Py_BuildValue("(dddddddddddddddddddddddddddddddddddd)(dddddddd)"
                             "(dddddddddddddddddddddddddddddddddddd)(dddddddd)",
        cusps[1],cusps[2],cusps[3],cusps[4],cusps[5],cusps[6],cusps[7],cusps[8],
        cusps[9],cusps[10],cusps[11],cusps[12],cusps[13],cusps[14],cusps[15],
        cusps[16],cusps[17],cusps[18],cusps[19],cusps[20],cusps[21],cusps[22],
        cusps[23],cusps[24],cusps[25],cusps[26],cusps[27],cusps[28],cusps[29],
        cusps[30],cusps[31],cusps[32],cusps[33],cusps[34],cusps[35],cusps[36],
        ascmc[0],ascmc[1],ascmc[2],ascmc[3],ascmc[4],ascmc[5],ascmc[6],ascmc[7],
        cuspspeed[1],cuspspeed[2],cuspspeed[3],cuspspeed[4],cuspspeed[5],
        cuspspeed[6],cuspspeed[7],cuspspeed[8],cuspspeed[9],cuspspeed[10],
        cuspspeed[11],cuspspeed[12],cuspspeed[13],cuspspeed[14],cuspspeed[15],
        cuspspeed[16],cuspspeed[17],cuspspeed[18],cuspspeed[19],cuspspeed[20],
        cuspspeed[21],cuspspeed[22],cuspspeed[23],cuspspeed[24],cuspspeed[25],
        cuspspeed[26],cuspspeed[27],cuspspeed[28],cuspspeed[29],cuspspeed[30],
        cuspspeed[31],cuspspeed[32],cuspspeed[33],cuspspeed[34],cuspspeed[35],
        cuspspeed[36],ascmcspeed[0],ascmcspeed[1],ascmcspeed[2],ascmcspeed[3],
        ascmcspeed[4],ascmcspeed[5],ascmcspeed[6],ascmcspeed[7]);
    return Py_BuildValue("(dddddddddddd)(dddddddd)(dddddddddddd)(dddddddd)",
    cusps[1],cusps[2],cusps[3],cusps[4],cusps[5],cusps[6],cusps[7],cusps[8],
    cusps[9],cusps[10],cusps[11],cusps[12],ascmc[0],ascmc[1],ascmc[2],ascmc[3],
    ascmc[4],ascmc[5],ascmc[6],ascmc[7],cuspspeed[1],cuspspeed[2],cuspspeed[3],
    cuspspeed[4],cuspspeed[5],cuspspeed[6],cuspspeed[7],cuspspeed[8],
    cuspspeed[9],cuspspeed[10],cuspspeed[11],cuspspeed[12],ascmcspeed[0],
    ascmcspeed[1],ascmcspeed[2],ascmcspeed[3],ascmcspeed[4],ascmcspeed[5],
    ascmcspeed[6],ascmcspeed[7]);
}

/* swisseph.jdet_to_utc */
PyDoc_STRVAR(pyswe_jdet_to_utc__doc__,
"Convert ET julian day number to UTC.\n\n"
"Args: float et, int flag\n"
"Return: tuple (int year, int month, int day, int hour, int minutes, float seconds)");

static PyObject * pyswe_jdet_to_utc FUNCARGS_KEYWDS
{
    int y, m, d, h, mi, flg;
    double s, et;
    static char *kwlist[] = {"et", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "di", kwlist, &et, &flg))
        return NULL;
    swe_jdet_to_utc(et, flg, &y, &m, &d, &h, &mi, &s);
    return Py_BuildValue("iiiiid", y, m, d, h, mi, s);
}

/* swisseph.jdut1_to_utc */
PyDoc_STRVAR(pyswe_jdut1_to_utc__doc__,
"Convert UT julian day number to UTC.\n\n"
"Args: float ut, int flag\n"
"Return: tuple (int year, int month, int day, int hour, int minutes, float seconds)");

static PyObject * pyswe_jdut1_to_utc FUNCARGS_KEYWDS
{
    int y, m, d, h, mi, flg;
    double s, ut;
    static char *kwlist[] = {"ut", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "di", kwlist, &ut, &flg))
        return NULL;
    swe_jdut1_to_utc(ut, flg, &y, &m, &d, &h, &mi, &s);
    return Py_BuildValue("iiiiid", y, m, d, h, mi, s);
}

/* swisseph.julday */
PyDoc_STRVAR(pyswe_julday__doc__,
"Calculate Julian day number.\n\n"
"Args: int year, int month, int day, float hour=12.0, int cal=GREG_CAL\n"
"Return: float");

static PyObject * pyswe_julday FUNCARGS_KEYWDS
{
    int year, month, day;
    double ret, hour = 12.0;
    int cal = SE_GREG_CAL;
    static char *kwlist[] = {"year", "month", "day", "hour", "cal", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "iii|di", kwlist,
        &year, &month, &day, &hour, &cal))
        return NULL;
    ret = swe_julday(year, month, day, hour, cal);
    return Py_BuildValue("d", ret);
}

/* swisseph.lat_to_lmt */
PyDoc_STRVAR(pyswe_lat_to_lmt__doc__,
"Translate local apparent time (LAT) to local mean time (LMT).\n\n"
"Args: float julday, float geolon\n"
"Return: float");

static PyObject * pyswe_lat_to_lmt FUNCARGS_KEYWDS
{
    int res;
    double jd, lon, ret;
    char err[256];
    static char *kwlist[] = {"julday", "geolon" , NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dd", kwlist, &jd, &lon))
        return NULL;
    res = swe_lat_to_lmt(jd, lon, &ret, err);
    if (res < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("d", ret);
}

/* swisseph.lmt_to_lat */
PyDoc_STRVAR(pyswe_lmt_to_lat__doc__,
"Translate local mean time (LMT) to local apparent time (LAT).\n\n"
"Args: float julday, float geolon\n"
"Return: float");

static PyObject * pyswe_lmt_to_lat FUNCARGS_KEYWDS
{
    int res;
    double jd, lon, ret;
    char err[256];
    static char *kwlist[] = {"julday", "geolon" , NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dd", kwlist, &jd, &lon))
        return NULL;
    res = swe_lmt_to_lat(jd, lon, &ret, err);
    if (res < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("d", ret);
}

/* swisseph.lun_eclipse_how */
PyDoc_STRVAR(pyswe_lun_eclipse_how__doc__,
"Calculate attributes of a lunar eclipse (UTC).\n\n"
"Args: float julday, float lon, float lat, float alt=0.0, int flag=FLG_SWIEPH\n"
"Return: int retflag, (float attr)");

static PyObject * pyswe_lun_eclipse_how FUNCARGS_KEYWDS
{
    double jd, geopos[3] = {0, 0, 0};
    double attr[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int res, flag = SEFLG_SWIEPH;
    char err[256];
    static char *kwlist[] = {"julday", "lon", "lat", "alt", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ddd|di", kwlist,
        &jd, &geopos[0], &geopos[1], &geopos[2], &flag))
        return NULL;
    res = swe_lun_eclipse_how(jd, flag, geopos, attr, err);
    if (res < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("i(ddddddddddd)", res,attr[0],attr[1],attr[2],attr[3],
        attr[4],attr[5],attr[6],attr[7],attr[8],attr[9],attr[10]);
}

/* swisseph.lun_eclipse_when */
PyDoc_STRVAR(pyswe_lun_eclipse_when__doc__,
"Find the next lunar eclipse (UTC).\n\n"
"Args: float jd_start, int ecl_type=0, bool backward=False, int flag=FLG_SWIEPH\n"
"Return: int retflag, (float tret)");

static PyObject * pyswe_lun_eclipse_when FUNCARGS_KEYWDS
{
    double jd, tret[10] = {0,0,0,0,0,0,0,0,0,0};
    int res, ecltype = 0, backward = 0, flag = SEFLG_SWIEPH;
    char err[256];
    static char *kwlist[] = {"jd_start", "ecl_type", "backward", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d|iii", kwlist,
        &jd, &ecltype, &backward, &flag))
        return NULL;
    res = swe_lun_eclipse_when(jd, flag, ecltype, tret, backward, err);
    if (res < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("i(dddddddd)", res,tret[0],tret[1],tret[2],tret[3],
        tret[4],tret[5],tret[6],tret[7]);
}

/* swisseph.lun_eclipse_when_loc */
PyDoc_STRVAR(pyswe_lun_eclipse_when_loc__doc__,
"Find the next lunar eclipse observable from a given geographic position.\n\n"
"Args: float jd_start, float lon, float lat, float alt=0.0, bool backward=False,"
" int flag=FLG_SWIEPH\n"
"Return: int retflag, (float tret), (float attr)");

static PyObject * pyswe_lun_eclipse_when_loc FUNCARGS_KEYWDS
{
    double jd, geopos[3] = { 0, 0, 0 };
    double tret[10] = {0,0,0,0,0,0,0,0,0,0};
    double attr[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int res, backward = 0, flag = SEFLG_SWIEPH;
    char err[256];
    static char *kwlist[] = {"jd_start", "lon", "lat", "alt", "backward",
        "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ddd|dii", kwlist, &jd,
        &geopos[0], &geopos[1], &geopos[2], &backward, &flag))
        return NULL;
    res = swe_lun_eclipse_when_loc(jd, flag, geopos, tret, attr, backward, err);
    if ( res < 0 ) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("i(dddddddddd)(dddddddddd)", res,tret[0],tret[1],
        tret[2],tret[3],tret[4],tret[5],tret[6],tret[7],tret[8],tret[9],
        attr[0],attr[1],attr[2],attr[3],attr[4],attr[5],attr[6],attr[7],
        attr[8],attr[9]);
}

/* swisseph.lun_occult_when_glob */
PyDoc_STRVAR(pyswe_lun_occult_when_glob__doc__,
"Find the next occultation of a planet or star by the moon globally (UTC).\n\n"
"Args: float jd_start, int or str body, int ecl_type=0, bool backward=False,"
" int flag=FLG_SWIEPH\n"
"Return: int retflag, (float tret)");

static PyObject * pyswe_lun_occult_when_glob FUNCARGS_KEYWDS
{
    double jd, tret[10];
    int res, plt = 0, ecltype = 0, backward = 0, flag = SEFLG_SWIEPH;
    char *star = "", err[256];
    PyObject *body;
    static char *kwlist[] = {"jd_start", "body", "ecl_type", "backward", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dO|iii", kwlist,
        &jd, &body, &ecltype, &backward, &flag))
        return NULL;
    if (PyLong_CheckExact(body)) /* long -> planet */
        plt = (int) PyLong_AsLong(body);
#if PY_MAJOR_VERSION >= 3
    else if (PyUnicode_CheckExact(body)) /* unicode -> fixed star */
        star = (char*) PyUnicode_AsUTF8(body);
#elif PY_MAJOR_VERSION < 3
    else if (PyInt_CheckExact(body)) /* int -> planet */
        plt = (int) PyInt_AsLong(body);
    else if (PyString_CheckExact(body)) /* str -> fixed star */
        star = PyString_AsString(body);
#endif
    else {
        PyErr_SetString(pyswe_Error, "swisseph.lun_occult_when_glob: Invalid body type");
        return NULL;
    }
    res = swe_lun_occult_when_glob(jd, plt, star, flag, ecltype, tret, backward, err);
    if (res < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("i(dddddddddd)", res,tret[0],tret[1],tret[2],
        tret[3],tret[4],tret[5],tret[6],tret[7],tret[8],tret[9]);
}

/* swisseph.lun_occult_when_loc */
PyDoc_STRVAR(pyswe_lun_occult_when_loc__doc__,
"Find next occultation of a body by the moon for a given geographic position (UTC).\n\n"
"Args: float julday, int or str body, float lon, float lat, float alt=0.0,"
" bool backward=False, int flag=FLG_SWIEPH\n"
"Return: int retflag, (float tret), (float attr)");

static PyObject * pyswe_lun_occult_when_loc FUNCARGS_KEYWDS
{
    double jd, tret[10], attr[20], geopos[3] = {0.0, 0.0, 0.0};
    int res, plt = 0, backward = 0, flag = SEFLG_SWIEPH;
    char *star = "", err[256];
    PyObject *body;
    static char *kwlist[] = {"julday", "body", "lon", "lat", "alt", "backward", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dOdd|dii", kwlist,
        &jd, &body, &geopos[0], &geopos[1], &geopos[2], &backward, &flag))
        return NULL;
    if (PyLong_CheckExact(body)) /* long -> planet */
        plt = (int) PyLong_AsLong(body);
#if PY_MAJOR_VERSION >= 3
    else if (PyUnicode_CheckExact(body)) /* unicode -> fixed star */
        star = (char*) PyUnicode_AsUTF8(body);
#elif PY_MAJOR_VERSION < 3
    else if (PyInt_CheckExact(body)) /* int -> planet */
        plt = (int) PyInt_AsLong(body);
    else if (PyString_CheckExact(body)) /* str -> fixed star */
        star = PyString_AsString(body);
#endif
    else {
        PyErr_SetString(pyswe_Error, "swisseph.lun_occult_when_loc: Invalid body type");
        return NULL;
    }
    res = swe_lun_occult_when_loc(jd, plt, star, flag, geopos, tret, attr, backward, err);
    if (res < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("i(ddddddd)(dddddddd)", res,tret[0],tret[1],
        tret[2],tret[3],tret[4],tret[5],tret[6],attr[0],attr[1],attr[2],
        attr[3],attr[4],attr[5],attr[6],attr[7]);
}

/* swisseph.lun_occult_where */
PyDoc_STRVAR(pyswe_lun_occult_where__doc__,
"Find where a lunar occultation is central or maximal (UTC).\n\n"
"Args: float julday, int or str body, int flag=FLG_SWIEPH\n"
"Return: int retval, (float geopos), (float attr)");

static PyObject * pyswe_lun_occult_where FUNCARGS_KEYWDS
{
    double jd, geopos[10] = {0,0,0,0,0,0,0,0,0,0};
    double attr[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int res, plt = 0, flag = SEFLG_SWIEPH;
    char *star = "", err[256];
    PyObject *body;
    static char *kwlist[] = {"julday", "body", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dO|i", kwlist,
        &jd, &body, &flag))
        return NULL;
    if (PyLong_CheckExact(body)) /* long -> planet */
        plt = (int) PyLong_AsLong(body);
#if PY_MAJOR_VERSION >= 3
    else if (PyUnicode_CheckExact(body)) /* unicode -> fixed star */
        star = (char*) PyUnicode_AsUTF8(body);
#elif PY_MAJOR_VERSION < 3
    else if (PyInt_CheckExact(body)) /* int -> planet */
        plt = (int) PyInt_AsLong(body);
    else if (PyString_CheckExact(body)) /* str -> fixed star */
        star = PyString_AsString(body);
#endif
    else {
        PyErr_SetString(pyswe_Error, "swisseph.lun_occult_where: Invalid body type");
        return NULL;
    }
    res = swe_lun_occult_where(jd, plt, star, flag, geopos, attr, err);
    if (res < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("i(dddddddddd)(dddddddd)", res,geopos[0],geopos[1],
        geopos[2],geopos[3],geopos[4],geopos[5],geopos[6],geopos[7],geopos[8],
        geopos[9],attr[0],attr[1],attr[2],attr[3],attr[4],attr[5],attr[6],attr[7]);
}

/* swisseph.nod_aps */
PyDoc_STRVAR(pyswe_nod_aps__doc__,
"Calculate planetary nodes and apsides (ET).\n\n"
"Args: float julday, int planet, int method=NODBIT_MEAN, int flag=FLG_SWIEPH+FLG_SPEED\n"
"Return: 4 tuples of 6 float (asc, des, per, aph)");

static PyObject * pyswe_nod_aps FUNCARGS_KEYWDS
{
    char err[256];
    double jd, xasc[6], xdsc[6], xper[6], xaph[6];
    int ret, planet, method = SE_NODBIT_MEAN, flag = SEFLG_SWIEPH + SEFLG_SPEED;
    static char *kwlist[] = {"julday", "planet", "method", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "di|ii", kwlist,
        &jd, &planet, &method, &flag))
        return NULL;
    ret = swe_nod_aps(jd, planet, flag, method, xasc, xdsc, xper, xaph, err);
    if (ret < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(dddddd)(dddddd)(dddddd)(dddddd)", xasc[0],xasc[1],
        xasc[2],xasc[3],xasc[4],xasc[5],xdsc[0],xdsc[1],xdsc[2],xdsc[3],xdsc[4],
        xdsc[5],xper[0],xper[1],xper[2],xper[3],xper[4],xper[5],xaph[0],xaph[1],
        xaph[2],xaph[3],xaph[4],xaph[5]);
}

/* swisseph.nod_aps_ut */
PyDoc_STRVAR(pyswe_nod_aps_ut__doc__,
"Calculate planetary nodes and apsides (UT).\n\n"
"Args: float julday, int planet, int method=NODBIT_MEAN, int flag=FLG_SWIEPH+FLG_SPEED\n"
"Return: 4 tuples of 6 float (asc, des, per, aph)");

static PyObject * pyswe_nod_aps_ut FUNCARGS_KEYWDS
{
    char err[256];
    double jd, xasc[6], xdsc[6], xper[6], xaph[6];
    int ret, planet, method = SE_NODBIT_MEAN, flag = SEFLG_SWIEPH + SEFLG_SPEED;
    static char *kwlist[] = {"julday", "planet", "method", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "di|ii", kwlist,
        &jd, &planet, &method, &flag))
        return NULL;
    ret = swe_nod_aps_ut(jd, planet, flag, method, xasc, xdsc, xper, xaph, err);
    if (ret < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(dddddd)(dddddd)(dddddd)(dddddd)", xasc[0],xasc[1],
        xasc[2],xasc[3],xasc[4],xasc[5],xdsc[0],xdsc[1],xdsc[2],xdsc[3],xdsc[4],
        xdsc[5],xper[0],xper[1],xper[2],xper[3],xper[4],xper[5],xaph[0],xaph[1],
        xaph[2],xaph[3],xaph[4],xaph[5]);
}

/* swisseph.orbit_max_min_true_distance */
PyDoc_STRVAR(pyswe_orbit_max_min_true_distance__doc__,
"Calculate the maximum possible distance, the minimum possible distance, and"
" the current true distance of planet, the EMB, or an asteroid.\n\n"
"Args: float jdet, int pl, int flag\n"
"Return: tuple (max, min, true)");

static PyObject * pyswe_orbit_max_min_true_distance FUNCARGS_KEYWDS
{
    int pl, flg, i;
    double jd, dmax, dmin, dtrue;
    char err[256];
    static char *kwlist[] = {"jdet", "pl", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dii", kwlist,
        &jd, &pl, &flg))
        return NULL;
    i = swe_orbit_max_min_true_distance(jd, pl, flg, &dmax, &dmin, &dtrue, err);
    if (i == 0) {
        return Py_BuildValue("(ddd)", dmax, dmin, dtrue);
    }
    PyErr_SetString(pyswe_Error, err);
    return NULL;
}

/* swisseph.pheno */
PyDoc_STRVAR(pyswe_pheno__doc__,
"Calculate planetary phenomena (ET).\n\n"
"Args: float julday, int planet, int flag=FLG_SWIEPH\n"
"Return: tuple of results");

static PyObject * pyswe_pheno FUNCARGS_KEYWDS
{
    double jd, attr[20];
    int res, plt, flag = SEFLG_SWIEPH;
    char err[256];
    static char *kwlist[] = {"julday", "planet", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "di|i", kwlist,
        &jd, &plt, &flag))
        return NULL;
    res = swe_pheno(jd, plt, flag, attr, err);
    if (res < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(ddddd)", attr[0],attr[1],attr[2],attr[3],attr[4]);
}

/* swisseph.pheno_ut */
PyDoc_STRVAR(pyswe_pheno_ut__doc__,
"Calculate planetary phenomena (UTC).\n\n"
"Args: float julday, int planet, int flag=FLG_SWIEPH\n"
"Return: tuple of results");

static PyObject * pyswe_pheno_ut FUNCARGS_KEYWDS
{
    double jd, attr[20];
    int res, plt, flag = SEFLG_SWIEPH;
    char err[256];
    static char *kwlist[] = {"julday", "planet", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "di|i", kwlist,
        &jd, &plt, &flag))
        return NULL;
    res = swe_pheno(jd, plt, flag, attr, err);
    if (res < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(ddddd)", attr[0],attr[1],attr[2],attr[3],attr[4]);
}

/* swisseph.rad_midp */
PyDoc_STRVAR(pyswe_rad_midp__doc__,
"Calculate midpoint (in radians).\n\n"
"Args: float x, float y\n"
"Return: float");

static PyObject * pyswe_rad_midp FUNCARGS_KEYWDS
{
    double x, y;
    static char *kwlist[] = {"x", "y", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dd", kwlist, &x, &y))
        return NULL;
    return Py_BuildValue("d", swe_rad_midp(x, y));
}

/* swisseph.radnorm */
PyDoc_STRVAR(pyswe_radnorm__doc__,
"Normalization of any radian number to the range [0;2*pi].\n\n"
"Args: float x\n"
"Return: float");

static PyObject * pyswe_radnorm FUNCARGS_KEYWDS
{
    double x;
    static char *kwlist[] = {"x", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &x))
        return NULL;
    return Py_BuildValue("d", swe_radnorm(x));
}

/* swisseph.refrac */
PyDoc_STRVAR(pyswe_refrac__doc__,
"Calculate either true altitude from apparent altitude, or apparent altitude"
" from true altitude.\n\n"
"Args: float alt, float press=0.0, float temp=0.0, int flag=TRUE_TO_APP\n"
"Return: float");

static PyObject * pyswe_refrac FUNCARGS_KEYWDS
{
    double alt, press = 0.0, temp = 0.0;
    int flag = SE_TRUE_TO_APP;
    static char *kwlist[] = {"alt", "press", "temp", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d|ddi", kwlist,
        &alt, &press, &temp, &flag))
        return NULL;
    return Py_BuildValue("d", swe_refrac(alt, press, temp, flag));
}

/* swisseph.refrac_extended */
PyDoc_STRVAR(pyswe_refrac_extended__doc__,
"Calculate either true altitude from apparent altitude, or apparent altitude"
" from true altitude, for geographical altitudes above sea level.\n\n"
"Args: float alt, float geoalt, float lrate, float press=0.0, float temp=0.0,"
" int flag=TRUE_TO_APP\n"
"Return: 2 tuples of 1 and 4 float");

static PyObject * pyswe_refrac_extended FUNCARGS_KEYWDS
{
    double alt, geoalt, lapserate, ret, dret[4], press = 0.0, temp = 0.0;
    int flag = SE_TRUE_TO_APP;
    static char *kwlist[] = {"alt", "geoalt", "lrate", "press",
        "temp", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ddd|ddi", kwlist,
        &alt, &geoalt, &lapserate, &press, &temp, &flag))
        return NULL;
    ret = swe_refrac_extended(alt, geoalt, press, temp, lapserate, flag, dret);
    return Py_BuildValue("(d)(dddd)", ret, dret[0], dret[1], dret[2], dret[3]);
}

/* swisseph.revjul */
PyDoc_STRVAR(pyswe_revjul__doc__,
"Calculate year, month, day, hour from Julian day number.\n\n"
"Args: float julday, int cal=GREG_CAL\n"
"Return: tuple of 3 int and 1 float");

static PyObject * pyswe_revjul FUNCARGS_KEYWDS
{
    int year, month, day, cal = SE_GREG_CAL;
    double hour, jd;
    static char *kwlist[] = {"julday", "cal", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d|i", kwlist,
        &jd, &cal))
        return NULL;
    swe_revjul(jd, cal, &year, &month, &day, &hour);
    return Py_BuildValue("(iiid)", year, month, day, hour);
}

/* swisseph.rise_trans */
PyDoc_STRVAR(pyswe_rise_trans__doc__,
"Calculate times of rising, setting and meridian transits.\n\n"
"Args: float jd_start, int or str body, float lon, float lat, float alt=0.0,"
" float press=0.0, float temp=0.0, int rsmi=0, int flag=FLG_SWIEPH\n"
"Return: int res, (float tret)");

static PyObject * pyswe_rise_trans FUNCARGS_KEYWDS
{
    double jd, tret[10], press = 0.0, temp = 0.0, geopos[3] = {0.0, 0.0, 0.0};
    int res, plt = 0, rsmi = 0, flag = SEFLG_SWIEPH;
    char *star = "", err[256];
    PyObject *body;
    static char *kwlist[] = {"jd_start", "body", "lon", "lat", "alt", "press",
        "temp", "rsmi", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dOdd|dddii", kwlist,
        &jd, &body, &geopos[0], &geopos[1], &geopos[2], &press, &temp, &rsmi, &flag))
        return NULL;
    if (PyLong_CheckExact(body)) /* long -> planet */
        plt = (int) PyLong_AsLong(body);
#if PY_MAJOR_VERSION >= 3
    else if (PyUnicode_CheckExact(body)) /* unicode -> fixed star */
        star = (char*) PyUnicode_AsUTF8(body);
#elif PY_MAJOR_VERSION < 3
    else if (PyInt_CheckExact(body)) /* int -> planet */
        plt = (int) PyInt_AsLong(body);
    else if (PyString_CheckExact(body)) /* str -> fixed star */
        star = PyString_AsString(body);
#endif
    else {
        PyErr_SetString(pyswe_Error, "swisseph.rise_trans: Invalid body type");
        return NULL;
    }
    res = swe_rise_trans(jd, plt, star, flag, rsmi, geopos, press, temp, tret, err);
    if (res == -1) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("i(dddddddddd)", res,tret[0],tret[1],tret[2],
        tret[3],tret[4],tret[5],tret[6],tret[7],tret[8],tret[9]);
}

/* swisseph.set_ephe_path */
PyDoc_STRVAR(pyswe_set_ephe_path__doc__,
"Set ephemeris files path.\n\n"
"Args: str path=\"" PYSWE_DEFAULT_EPHE_PATH "\"\n"
"Return: None");

static PyObject * pyswe_set_ephe_path FUNCARGS_KEYWDS
{
    char *path = PYSWE_DEFAULT_EPHE_PATH;
    static char *kwlist[] = {"path", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "|z", kwlist, &path))
        return NULL;
    swe_set_ephe_path(path);
    Py_RETURN_NONE;
}

/* swisseph.set_jpl_file */
PyDoc_STRVAR(pyswe_set_jpl_file__doc__,
"Set JPL file path.\n\n"
"Args: str path\n"
"Return: None");

static PyObject * pyswe_set_jpl_file FUNCARGS_KEYWDS
{
    char *path;
    static char *kwlist[] = {"path", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "s", kwlist, &path))
        return NULL;
    swe_set_jpl_file(path);
    Py_RETURN_NONE;
}

/* swisseph.set_lapse_rate */
PyDoc_STRVAR(pyswe_set_lapse_rate__doc__,
"Set lapse rate.\n\nArgs: float lrate\nReturn: None");

static PyObject * pyswe_set_lapse_rate FUNCARGS_KEYWDS
{
    double lapserate;
    static char *kwlist[] = {"lrate", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
        &lapserate))
        return NULL;
    swe_set_lapse_rate(lapserate);
    Py_RETURN_NONE;
}

/* swisseph.set_sid_mode */
PyDoc_STRVAR(pyswe_set_sid_mode__doc__,
"Set sidereal mode.\n\n"
"Args: int mode, float t0=0.0, float ayan_t0=0.0\n"
"Return: None");

static PyObject * pyswe_set_sid_mode FUNCARGS_KEYWDS
{
    int mode;
    double t0 = 0.0, ayan_t0 = 0.0;
    static char *kwlist[] = {"mode", "t0", "ayan_t0", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i|dd", kwlist,
        &mode, &t0, &ayan_t0))
        return NULL;
    swe_set_sid_mode(mode, t0, ayan_t0);
    Py_RETURN_NONE;
}

/* swisseph.set_tid_acc */
PyDoc_STRVAR(pyswe_set_tid_acc__doc__,
"Set tidal acceleration.\n\n"
"Args: float acc\n"
"Return: None");

static PyObject * pyswe_set_tid_acc FUNCARGS_KEYWDS
{
    double acc;
    static char *kwlist[] = {"acc", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &acc))
        return NULL;
    swe_set_tid_acc(acc);
    Py_RETURN_NONE;
}

/* swisseph.set_topo */
PyDoc_STRVAR(pyswe_set_topo__doc__,
"Set topocentric parameters.\n\n"
"Args: float lon, float lat, float alt=0.0\n"
"Return: None");

static PyObject * pyswe_set_topo FUNCARGS_KEYWDS
{
    double lon, lat, alt = 0.0;
    static char *kwlist[] = {"lon", "lat", "alt", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dd|d", kwlist,
        &lon, &lat, &alt))
        return NULL;
    swe_set_topo(lon, lat, alt);
    Py_RETURN_NONE;
}

/* swisseph.sidtime */
PyDoc_STRVAR(pyswe_sidtime__doc__,
"Calculate sidereal time (UT).\n\n"
"Args: float julday\n"
"Return: float");

static PyObject * pyswe_sidtime FUNCARGS_KEYWDS
{
    double jd, ret;
    static char *kwlist[] = {"julday", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &jd))
        return NULL;
    ret = swe_sidtime(jd);
    return Py_BuildValue("d", ret);
}

/* swisseph.sidtime0 */
PyDoc_STRVAR(pyswe_sidtime0__doc__,
"Calculate sidereal time, given obliquity and nutation (UT).\n\n"
"Args: float julday, float obliquity, float nutation\n"
"Return: float");

static PyObject * pyswe_sidtime0 FUNCARGS_KEYWDS
{
    double jd, ret, obliquity, nutation;
    static char *kwlist[] = {"julday", "obliquity", "nutation", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ddd", kwlist,
        &jd, &obliquity, &nutation))
        return NULL;
    ret = swe_sidtime0(jd, obliquity, nutation);
    return Py_BuildValue("d", ret);
}

/* swisseph.sol_eclipse_how */
PyDoc_STRVAR(pyswe_sol_eclipse_how__doc__,
"Calculate attributes of a solar eclipse.\n\n"
"Args: float julday, float lon, float lat, float alt=0.0, int flag=FLG_SWIEPH\n"
"Return: int res, (float attr)");

static PyObject * pyswe_sol_eclipse_how FUNCARGS_KEYWDS
{
    double jd, geopos[3] = {0, 0, 0};
    double attr[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int res, flag = SEFLG_SWIEPH;
    char err[256];
    static char *kwlist[] = {"julday", "lon", "lat", "alt", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ddd|di", kwlist,
        &jd, &geopos[0], &geopos[1], &geopos[2], &flag))
        return NULL;
    res = swe_sol_eclipse_how(jd, flag, geopos, attr, err);
    if (res < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("i(ddddddddddd)", res,attr[0],attr[1],attr[2],attr[3],
        attr[4],attr[5],attr[6],attr[7],attr[8],attr[9],attr[10]);
}

/* swisseph.sol_eclipse_when_glob */
PyDoc_STRVAR(pyswe_sol_eclipse_when_glob__doc__,
"Find the next solar eclipse globally (UTC).\n\n"
"Args: float jd_start, ecl_type=0, bool backward=False, int flag=FLG_SWIEPH\n"
"Return: int res, (float tret)");

static PyObject * pyswe_sol_eclipse_when_glob FUNCARGS_KEYWDS
{
    double jd, tret[10] = {0,0,0,0,0,0,0,0,0,0};
    int res, ecltype = 0, backward = 0, flag = SEFLG_SWIEPH;
    char err[256];
    static char *kwlist[] = {"jd_start", "ecl_type", "backward", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d|iii", kwlist,
        &jd, &ecltype, &backward, &flag))
        return NULL;
    res = swe_sol_eclipse_when_glob(jd, flag, ecltype, tret, backward, err);
    if (res < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("i(dddddddddd)", res,tret[0],tret[1],tret[2],tret[3],
        tret[4],tret[5],tret[6],tret[7],tret[8],tret[9]);
}

/* swisseph.sol_eclipse_when_loc */
PyDoc_STRVAR(pyswe_sol_eclipse_when_loc__doc__,
"Find the next solar eclipse for a given geographic position (UTC).\n\n"
"Args: float julday, float lon, float lat, float alt=0.0, bool backward=False,"
" int flag=FLG_SWIEPH\n"
"Return: int res, (float tret), (float attr)");

static PyObject * pyswe_sol_eclipse_when_loc FUNCARGS_KEYWDS
{
    double jd, geopos[3] = {0, 0, 0};
    double tret[10] = {0,0,0,0,0,0,0,0,0,0};
    double attr[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int res, backward = 0, flag = SEFLG_SWIEPH;
    char err[256];
    static char *kwlist[] = {"julday", "lon", "lat", "alt", "backward", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ddd|dii", kwlist,
        &jd, &geopos[0], &geopos[1], &geopos[2], &backward, &flag))
        return NULL;
    res = swe_sol_eclipse_when_loc(jd, flag, geopos, tret, attr, backward, err);
    if (res < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("i(ddddddd)(ddddddddddd)", res,
        tret[0],tret[1],tret[2],tret[3],tret[4],tret[5],tret[6],
        attr[0],attr[1],attr[2],attr[3],attr[4],attr[5],attr[6],attr[7],attr[8],
        attr[9],attr[10]);
}

/* swisseph.sol_eclipse_where */
PyDoc_STRVAR(pyswe_sol_eclipse_where__doc__,
"Find where a solar eclipse is central or maximal (UTC).\n\n"
"Args: float julday, int flag=FLG_SWIEPH\n"
"Return: int res, (float geopos), (float attr)");

static PyObject * pyswe_sol_eclipse_where FUNCARGS_KEYWDS
{
    double jd, geopos[10] = {0,0,0,0,0,0,0,0,0,0};
    double attr[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int res, flag = SEFLG_SWIEPH;
    char err[256];
    static char *kwlist[] = {"julday", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d|i", kwlist, &jd, &flag))
        return NULL;
    res = swe_sol_eclipse_where(jd, flag, geopos, attr, err);
    if (res < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("i(dddddddddd)(ddddddddddd)", res,geopos[0],geopos[1],
        geopos[2],geopos[3],geopos[4],geopos[5],geopos[6],geopos[7],geopos[8],
        geopos[9],attr[0],attr[1],attr[2],attr[3],attr[4],attr[5],attr[6],
        attr[7],attr[8],attr[9],attr[10]);
}

/* swisseph.split_deg */
PyDoc_STRVAR(pyswe_split_deg__doc__,
"Provide sign or nakshatra, degree, minutes, seconds and fraction of second"
" from decimal degree. Can also round to seconds, minutes, degrees.\n\n"
"Args: float ddeg, int roundflag\n"
"Return: tuple (deg, min, sec, secfr, sign)");

static PyObject * pyswe_split_deg FUNCARGS_KEYWDS
{
    double ddeg, secfr;
    int deg, min, sec, sign, flag;
    static char *kwlist[] = {"ddeg", "roundflag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "di", kwlist, &ddeg, &flag))
        return NULL;
    swe_split_deg(ddeg, flag, &deg, &min, &sec, &secfr, &sign);
    return Py_BuildValue("(iiidi)", deg, min, sec, secfr, sign);
}

/* swisseph.time_equ */
PyDoc_STRVAR(pyswe_time_equ__doc__,
"Calculate equation of time (UT).\n\n"
"Args: float julday\n"
"Return: float");

static PyObject * pyswe_time_equ FUNCARGS_KEYWDS
{
    int res;
    double jd, ret;
    char err[256];
    static char *kwlist[] = {"julday", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &jd))
        return NULL;
    res = swe_time_equ(jd, &ret, err);
    if (res < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("d", ret);
}

/* swisseph.utc_time_zone */
PyDoc_STRVAR(pyswe_utc_time_zone__doc__,
"Transform local time to UTC or UTC to local time.\n\n"
"Args: int year, int month, int day, int hour, int minutes, int seconds, float offset\n"
"Return: tuple (year, month, day, hour, minutes, seconds)");

static PyObject * pyswe_utc_time_zone FUNCARGS_KEYWDS
{
    int y, m, d, h, mi, y2, m2, d2, h2, mi2;
    double s, tz, s2;
    static char *kwlist[] = {"year", "month", "day", "hour", "minutes",
        "seconds", "offset", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "iiiiiid", kwlist,
        &y, &m, &d, &h, &mi, &s, &tz))
        return NULL;
    swe_utc_time_zone(y, m, d, h, mi, s, tz, &y2, &m2, &d2, &h2, &mi2, &s2);
    return Py_BuildValue("(iiiiid)", y2, m2, d2, h2, mi2, s2);
}

/* swisseph.utc_to_jd */
PyDoc_STRVAR(pyswe_utc_to_jd__doc__,
"Convert UTC to julian day.\n\n"
"Args: int year, int month, int day, int hour, int minutes, float seconds, int flag\n"
"Return: tuple (float et, float ut)");

static PyObject * pyswe_utc_to_jd FUNCARGS_KEYWDS
{
    int i, y, m, d, h, mi, flg;
    double s, dret[2];
    char serr[255];
    static char *kwlist[] = {"year", "month", "day", "hour", "minutes",
        "seconds", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "iiiiidi", kwlist,
        &y, &m, &d, &h, &mi, &s, &flg))
        return NULL;
    i = swe_utc_to_jd(y, m, d, h, mi, s, flg, dret, serr);
    if (i < 0) {
        PyErr_SetString(pyswe_Error, serr);
        return NULL;
    }
    return Py_BuildValue("dd", dret[0], dret[1]);
}

/* swisseph.vis_limit_mag */
PyDoc_STRVAR(pyswe_vis_limit_mag__doc__,
"Find the limiting visual magnitude in dark skies.\n\n"
"Args: float jd, seq geopos, seq atmo, seq observer, str object, int helflag\n"
"Return: tuple (float res, float magnitude)");

static PyObject * pyswe_vis_limit_mag FUNCARGS_KEYWDS
{
    double jd, geopos[3], atmo[4], observ[6], dres, dret;
    char serr[255], *obj = 0;
    int flg;
    PyObject *o1=0, *o2=0, *o3=0, *o4, *o5, *o6, *o7, *o8, *o9;
    static char *kwlist[] = {"jd", "geopos", "atmo", "observer", "object",
        "helflag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dOOOsi", kwlist,
        &jd, &o1, &o2, &o3, &obj, &flg))
        return NULL;

    if (!PySequence_Check(o1) || PySequence_Length(o1) != 3) {
        PyErr_SetString(pyswe_Error, "Invalid geopos sequence");
        return NULL;
    }
    else {
        o4 = PySequence_ITEM(o1, 0);
        o5 = PySequence_ITEM(o1, 1);
        o6 = PySequence_ITEM(o1, 2);
        if (!PyNumber_Check(o4) || !PyNumber_Check(o5) || !PyNumber_Check(o6)) {
            PyErr_SetString(pyswe_Error, "Invalid geopos value type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
            return NULL;
        }
        /* checking longitude */
        if (PyFloat_Check(o4))
            geopos[0] = PyFloat_AsDouble(o4);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
            geopos[0] = (double) PyInt_AsLong(o4);
#endif
        else if (PyLong_Check(o4))
            geopos[0] = (double) PyLong_AsLong(o4);
        else {
            PyErr_SetString(pyswe_Error, "Invalid longitude type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
            return NULL;
        }
        /* checking latitude */
        if (PyFloat_Check(o5))
            geopos[1] = PyFloat_AsDouble(o5);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
            geopos[1] = (double) PyInt_AsLong(o5);
#endif
        else if (PyLong_Check(o5))
            geopos[1] = (double) PyLong_AsLong(o5);
        else {
            PyErr_SetString(pyswe_Error, "Invalid latitude type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
            return NULL;
        }
        /* checking altitude */
        if (PyFloat_Check(o6))
            geopos[2] = PyFloat_AsDouble(o6);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
            geopos[2] = (double) PyInt_AsLong(o6);
#endif
        else if (PyLong_Check(o6))
            geopos[2] = (double) PyLong_AsLong(o6);
        else {
            PyErr_SetString(pyswe_Error, "Invalid altitude type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
            return NULL;
        }
        Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
    }
    if (!PySequence_Check(o2) || PySequence_Length(o2) != 4) {
        PyErr_SetString(pyswe_Error, "Invalid atmospheric sequence");
        return NULL;
    }
    else {
        o4 = PySequence_ITEM(o2, 0);
        o5 = PySequence_ITEM(o2, 1);
        o6 = PySequence_ITEM(o2, 2);
        o7 = PySequence_ITEM(o2, 3);
        if (!PyNumber_Check(o4) || !PyNumber_Check(o5) || !PyNumber_Check(o6)
            || !PyNumber_Check(o7)) {
            PyErr_SetString(pyswe_Error, "Invalid atmospheric value type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }
        /* atmospheric pressure */
        if (PyFloat_Check(o4))
            atmo[0] = PyFloat_AsDouble(o4);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o4))
            atmo[0] = (double) PyInt_AsLong(o4);
#endif
        else if (PyLong_Check(o4))
            atmo[0] = (double) PyLong_AsLong(o4);
        else {
            PyErr_SetString(pyswe_Error, "Invalid atmospheric pressure");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }
        /* atmospheric temperature */
        if (PyFloat_Check(o5))
            atmo[1] = PyFloat_AsDouble(o5);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
            atmo[1] = (double) PyInt_AsLong(o5);
#endif
        else if (PyLong_Check(o5))
            atmo[1] = (double) PyLong_AsLong(o5);
        else {
            PyErr_SetString(pyswe_Error, "Invalid atmospheric temperature");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }
        /* humidity */
        if (PyFloat_Check(o6))
            atmo[2] = PyFloat_AsDouble(o6);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o6))
            atmo[2] = (double) PyInt_AsLong(o6);
#endif
        else if (PyLong_Check(o6))
            atmo[2] = (double) PyLong_AsLong(o6);
        else {
            PyErr_SetString(pyswe_Error, "Invalid humidity");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }
        /* meteorological range */
        if (PyFloat_Check(o7))
            atmo[3] = PyFloat_AsDouble(o7);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o7))
            atmo[3] = (double) PyInt_AsLong(o7);
#endif
        else if (PyLong_Check(o7))
            atmo[3] = (double) PyLong_AsLong(o7);
        else {
            PyErr_SetString(pyswe_Error, "Invalid meteorological range");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }
        Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
    }
    if (!PySequence_Check(o3) || PySequence_Length(o3) != 6) {
        PyErr_SetString(pyswe_Error, "Invalid observer sequence");
        return NULL;
    }
    else {
        o4 = PySequence_ITEM(o3, 0);
        o5 = PySequence_ITEM(o3, 1);
        o6 = PySequence_ITEM(o3, 2);
        o7 = PySequence_ITEM(o3, 3);
        o8 = PySequence_ITEM(o3, 4);
        o9 = PySequence_ITEM(o3, 5);
        if (!PyNumber_Check(o4) || !PyNumber_Check(o5) || !PyNumber_Check(o6)
            || !PyNumber_Check(o7) || !PyNumber_Check(o8) || !PyNumber_Check(o9)) {
            PyErr_SetString(pyswe_Error, "Invalid observer value type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }
        /* observer age */
        if (PyFloat_Check(o4))
            observ[0] = PyFloat_AsDouble(o4);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o4))
            observ[0] = (double) PyInt_AsLong(o4);
#endif
        else if (PyLong_Check(o4))
            observ[0] = (double) PyLong_AsLong(o4);
        else {
            PyErr_SetString(pyswe_Error, "Invalid observer age");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }
        /* snellen ratio */
        if (PyFloat_Check(o5))
            observ[1] = PyFloat_AsDouble(o5);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
            observ[1] = (double) PyInt_AsLong(o5);
#endif
        else if (PyLong_Check(o5))
            observ[1] = (double) PyLong_AsLong(o5);
        else {
            PyErr_SetString(pyswe_Error, "Invalid snellen ratio");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }
        /* mono/binocular */
        if (PyFloat_Check(o6))
            observ[2] = PyFloat_AsDouble(o6);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o6))
            observ[2] = (double) PyInt_AsLong(o6);
#endif
        else if (PyLong_Check(o6))
            observ[2] = (double) PyLong_AsLong(o6);
        else {
            PyErr_SetString(pyswe_Error, "Invalid telescope");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }
        /* telescope magnification */
        if (PyFloat_Check(o7))
            observ[3] = PyFloat_AsDouble(o7);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o7))
            observ[3] = (double) PyInt_AsLong(o7);
#endif
        else if (PyLong_Check(o7))
            observ[3] = (double) PyLong_AsLong(o7);
        else {
            PyErr_SetString(pyswe_Error, "Invalid telescope magnification");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }
        /* optical aperture */
        if (PyFloat_Check(o8))
            observ[4] = PyFloat_AsDouble(o8);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o8))
            observ[4] = (double) PyInt_AsLong(o8);
#endif
        else if (PyLong_Check(o8))
            observ[4] = (double) PyLong_AsLong(o8);
        else {
            PyErr_SetString(pyswe_Error, "Invalid telescope aperture");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }
        /* optical transmission */
        if (PyFloat_Check(o9))
            observ[5] = PyFloat_AsDouble(o9);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o9))
            observ[5] = (double) PyInt_AsLong(o9);
#endif
        else if (PyLong_Check(o9))
            observ[5] = (double) PyLong_AsLong(o9);
        else {
            PyErr_SetString(pyswe_Error, "Invalid telescope aperture");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }
        Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
        Py_DECREF(o8); Py_DECREF(o9);
    }
    dres = swe_vis_limit_mag(jd, geopos, atmo, observ, obj, flg, &dret, serr);
    if (dres != -1)
        return Py_BuildValue("dd", dres, dret);
    PyErr_SetString(pyswe_Error, serr);
    return NULL;
}

#if PYSWE_USE_SWEPHELP /* Pyswisseph contrib submodule */

/* generic object holding a pointer */

#define pyswh_Object_new(tp)    ((pyswh_Object*) (tp)->tp_alloc((tp), 0))

typedef struct {
    PyObject_HEAD
    void* p;
} pyswh_Object;

typedef struct {
    double (*get)(void*);
    int (*set)(void*, double);
} pyswh_double_getsetters;

typedef struct {
    int (*get)(void*);
    int (*set)(void*, int);
} pyswh_int_getsetters;

typedef struct {
    const char* (*get)(void*);
    int (*set)(void*, const char*);
} pyswh_string_getsetters;

static PyObject * pyswh_Object_get_double(pyswh_Object* self, void* cl)
{
    double d = ((pyswh_double_getsetters*)cl)->get(self->p);
    PyObject* o = PyFloat_FromDouble(d);
    return o ? o : PyErr_NoMemory();
}

static int pyswh_Object_set_double(pyswh_Object* self, PyObject* val, void* cl)
{
    double d;
    if (!val || (!PyLong_Check(val) && !PyFloat_Check(val))) {
        PyErr_SetString(PyExc_TypeError, "must be a float");
        return -1;
    }
    d = PyLong_Check(val) ? PyLong_AsLong(val) :
        PyFloat_Check(val) ? PyFloat_AsDouble(val) : -1;
    if (d == -1  && PyErr_Occurred())
        return -1;
    if (((pyswh_double_getsetters*)cl)->set(self->p, d)) {
        PyErr_SetString(PyExc_AttributeError, swhxx_get_error(self->p));
        swhxx_clear_error(self->p);
        return -1;
    }
    return 0;
}

static PyObject * pyswh_Object_get_int(pyswh_Object* self, void* cl)
{
    int i = ((pyswh_int_getsetters*)cl)->get(self->p);
    PyObject* o = PyLong_FromLong(i);
    return o ? o : PyErr_NoMemory();
}

static int pyswh_Object_set_int(pyswh_Object* self, PyObject* val, void* cl)
{
    int i;
    if (!val || !PyLong_Check(val)) {
        PyErr_SetString(PyExc_TypeError, "must be an int");
        return -1;
    }
    i = PyLong_AsLong(val);
    if (i == -1 && PyErr_Occurred())
        return -1;
    if (((pyswh_int_getsetters*)cl)->set(self->p, i)) {
        PyErr_SetString(PyExc_AttributeError, swhxx_get_error(self->p));
        swhxx_clear_error(self->p);
        return -1;
    }
    return 0;
}

static PyObject * pyswh_Object_get_string(pyswh_Object* self, void* cl)
{
    const char* s = ((pyswh_string_getsetters*)cl)->get(self->p);
    PyObject* o = PyUnicode_FromString(s);
    return o ? o : PyErr_NoMemory();
}

static int pyswh_Object_set_string(pyswh_Object* self, PyObject* val, void* cl)
{
    char* str;
    if (!val || !PyUnicode_Check(val)) {
        PyErr_SetString(PyExc_TypeError, "must be a string");
        return -1;
    }
    str = (char*) PyUnicode_AsUTF8(val);
    if (((pyswh_string_getsetters*)cl)->set(self->p, str)) {
        PyErr_SetString(PyExc_AttributeError, swhxx_get_error(self->p));
        swhxx_clear_error(self->p);
        return -1;
    }
    return 0;
}

/* swisseph.contrib.User */
PyDoc_STRVAR(pyswh_User__doc__,
"User of the database");
PyDoc_STRVAR(pyswh_User_idx__doc__,
"User idx");
PyDoc_STRVAR(pyswh_User_name__doc__,
"User name");
PyDoc_STRVAR(pyswh_User_pswd__doc__,
"User password");
PyDoc_STRVAR(pyswh_User_mail__doc__,
"User mail");
PyDoc_STRVAR(pyswh_User_info__doc__,
"User info");
PyDoc_STRVAR(pyswh_User_drop__doc__,
"Delete user from database.\n\n"
"Args: -\n"
"Return: None");
PyDoc_STRVAR(pyswh_User_list__doc__,
"List all users in database.\n\n"
"Args: -\n"
"Return: list of swh.User instances");
PyDoc_STRVAR(pyswh_User_root__doc__,
"Load the default user (root) from database (static method)\n\n"
"Args: -\n"
"Return: swh.User instance");
PyDoc_STRVAR(pyswh_User_save__doc__,
"Save user in database.\n\n"
"Args: -\n"
"Return: None");
PyDoc_STRVAR(pyswh_User_select__doc__,
"Load a user from database (static method)\n\n"
"Args: str name\n"
"Return: swh.User instance");

static PyObject * pyswh_User_new(PyTypeObject* tp, PyObject* args, PyObject* kwds)
{
    pyswh_Object* self = pyswh_Object_new(tp);
    if (self)
        swhxx_db_user_new(&self->p);
    else
        self->p = NULL;
    return (PyObject*) self;
}

static void pyswh_User_dealloc(pyswh_Object* self)
{
    if (self->p)
        swhxx_db_user_dealloc(&self->p);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pyswh_User_init(pyswh_Object* self, PyObject* args, PyObject* kwds)
{
    char* name = "?", *pswd = "", *mail = "", *info = "";
    static char* kwlist[] = {"name", "pswd", "mail", "info", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|ssss", kwlist,
                                     &name, &pswd, &mail, &info))
        return -1;
    if (swhxx_db_user_set_name(self->p, name)
        || swhxx_db_user_set_pswd(self->p, pswd)
        || swhxx_db_user_set_mail(self->p, mail)
        || swhxx_db_user_set_info(self->p, info)) {
        PyErr_SetString(PyExc_AttributeError, swhxx_get_error(self->p));
        swhxx_clear_error(self->p);
        return -1;
    }
    return 0;
}

static pyswh_int_getsetters pyswh_User_getset_idx = {
    &swhxx_db_user_get_idx, &swhxx_db_user_set_idx
};
static pyswh_string_getsetters pyswh_User_getset_name = {
    &swhxx_db_user_get_name, &swhxx_db_user_set_name
};
static pyswh_string_getsetters pyswh_User_getset_pswd = {
    &swhxx_db_user_get_pswd, &swhxx_db_user_set_pswd
};
static pyswh_string_getsetters pyswh_User_getset_mail = {
    &swhxx_db_user_get_mail, &swhxx_db_user_set_mail
};
static pyswh_string_getsetters pyswh_User_getset_info = {
    &swhxx_db_user_get_info, &swhxx_db_user_set_info
};

static PyGetSetDef pyswh_User_getsetters[] = {
{"_idx", (getter) pyswh_Object_get_int, (setter) pyswh_Object_set_int,
    pyswh_User_idx__doc__, &pyswh_User_getset_idx},
{"name", (getter) pyswh_Object_get_string, (setter) pyswh_Object_set_string,
    pyswh_User_name__doc__, &pyswh_User_getset_name},
{"pswd", (getter) pyswh_Object_get_string, (setter) pyswh_Object_set_string,
    pyswh_User_pswd__doc__, &pyswh_User_getset_pswd},
{"mail", (getter) pyswh_Object_get_string, (setter) pyswh_Object_set_string,
    pyswh_User_mail__doc__, &pyswh_User_getset_mail},
{"info", (getter) pyswh_Object_get_string, (setter) pyswh_Object_set_string,
    pyswh_User_info__doc__, &pyswh_User_getset_info},
{NULL}
};

PyObject * pyswh_User_drop FUNCARGS_SELF;
PyObject * pyswh_User_list FUNCARGS_SELF;
PyObject * pyswh_User_root FUNCARGS_SELF;
PyObject * pyswh_User_save FUNCARGS_SELF;
PyObject * pyswh_User_select FUNCARGS_KEYWDS;

static PyMethodDef pyswh_User_methods[] = {
{"drop", (PyCFunction) pyswh_User_drop,
    METH_NOARGS, pyswh_User_drop__doc__},
{"list", (PyCFunction) pyswh_User_list,
    METH_STATIC|METH_NOARGS, pyswh_User_list__doc__},
{"root", (PyCFunction) pyswh_User_root,
    METH_STATIC|METH_NOARGS, pyswh_User_root__doc__},
{"save", (PyCFunction) pyswh_User_save,
    METH_NOARGS, pyswh_User_save__doc__},
{"select", (PyCFunction) pyswh_User_select,
    METH_STATIC|METH_VARARGS|METH_KEYWORDS, pyswh_User_select__doc__},
{NULL}
};

static PyTypeObject pyswh_User_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "swisseph.contrib.User",
    .tp_doc = pyswh_User__doc__,
    .tp_basicsize = sizeof(pyswh_Object),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE,
    .tp_new = pyswh_User_new,
    .tp_init = (initproc) pyswh_User_init,
    .tp_dealloc = (destructor) pyswh_User_dealloc,
    /*.tp_members = pyswh_User_members,*/
    .tp_methods = pyswh_User_methods,
    .tp_getset = pyswh_User_getsetters,
};

PyObject * pyswh_User_drop FUNCARGS_SELF
{
    pyswh_Object* o = (pyswh_Object*) self;
    int x;
    if ((x = swhxx_db_user_drop(o->p))) {
        PyErr_SetString(x == 1 ? PyExc_KeyError : pyswe_Error,
                        swhxx_get_error(o->p));
        swhxx_clear_error(o->p);
        return NULL;
    }
    Py_RETURN_NONE;
}

int pyswh_User_list_cb(void* p, int argc, char** argv, char** cols)
{
    PyObject* lst = (PyObject*) p;
    pyswh_Object* u = pyswh_Object_new(&pyswh_User_type);
    if (!u)
        return 1;
    swhxx_db_user_new(&u->p);
    if (!u->p
        || swhxx_db_user_set_idx(u->p, atoi(argv[0]))
        || swhxx_db_user_set_name(u->p, argv[1])
        || swhxx_db_user_set_pswd(u->p, argv[2])
        || swhxx_db_user_set_mail(u->p, argv[3])
        || swhxx_db_user_set_info(u->p, argv[4]))
        return 1;
    if (PyList_Append(lst, (PyObject*) u))
        return 1;
    return 0;
}

PyObject * pyswh_User_list FUNCARGS_SELF
{
    char err[512] = {0};
    PyObject* lst = PyList_New(0);
    if (!lst)
        return PyErr_NoMemory();
    if (swh_db_exec("select * from Users order by _idx;", &pyswh_User_list_cb,
                    lst, err)) {
        PyErr_SetString(pyswe_Error, err);
        Py_DECREF(lst);
        return NULL;
    }
    return lst;
}

PyObject * pyswh_User_root FUNCARGS_SELF
{
    void* p;
    pyswh_Object* o;
    char err[512];
    int x;
    if ((x = swhxx_db_user_root(&p, err))) {
        PyErr_SetString(x == 1 ? PyExc_KeyError : pyswe_Error, err);
        return NULL;
    }
    if (!(o = pyswh_Object_new(&pyswh_User_type))) {
        swhxx_db_user_dealloc(&p);
        return PyErr_NoMemory();
    }
    o->p = p;
    return (PyObject*) o;
}

PyObject * pyswh_User_save FUNCARGS_SELF
{
    pyswh_Object* o = (pyswh_Object*) self;
    int x;
    if ((x = swhxx_db_user_save(o->p))) {
        PyErr_SetString(x == 1 ? PyExc_KeyError : pyswe_Error,
                        swhxx_get_error(o->p));
        swhxx_clear_error(o->p);
        return NULL;
    }
    Py_RETURN_NONE;
}

PyObject * pyswh_User_select FUNCARGS_KEYWDS
{
    char* name;
    void* p;
    pyswh_Object* o;
    char err[512];
    int x;
    static char* kwlist[] = {"name", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "s", kwlist, &name))
        return NULL;
    if ((x = swhxx_db_user_select(name, &p, err))) {
        PyErr_SetString(x == 1 ? PyExc_KeyError : pyswe_Error, err);
        return NULL;
    }
    if (!p)
        return PyErr_Format(PyExc_KeyError, "no such user (%s)", name);
    if (!(o = pyswh_Object_new(&pyswh_User_type))) {
        swhxx_db_user_dealloc(&p);
        return PyErr_NoMemory();
    }
    o->p = p;
    return (PyObject*) o;
}

/* swisseph.contrib.Data */
PyDoc_STRVAR(pyswh_Data__doc__,
"Astro data");
PyDoc_STRVAR(pyswh_Data_idx__doc__,
"Data idx");
PyDoc_STRVAR(pyswh_Data_uidx__doc__,
"Data uidx");
PyDoc_STRVAR(pyswh_Data_title__doc__,
"Data title");
PyDoc_STRVAR(pyswh_Data_jd__doc__,
"Data julian day");
PyDoc_STRVAR(pyswh_Data_lat__doc__,
"Data latitude");
PyDoc_STRVAR(pyswh_Data_lon__doc__,
"Data longitude");
PyDoc_STRVAR(pyswh_Data_alt__doc__,
"Data altitude");
PyDoc_STRVAR(pyswh_Data_datetime__doc__,
"Data date and time");
PyDoc_STRVAR(pyswh_Data_timezone__doc__,
"Data timezone");
PyDoc_STRVAR(pyswh_Data_isdst__doc__,
"Data isdst");
PyDoc_STRVAR(pyswh_Data_location__doc__,
"Data location");
PyDoc_STRVAR(pyswh_Data_country__doc__,
"Data country");
PyDoc_STRVAR(pyswh_Data_owner__doc__,
"Get owner of data\n\n"
"Args: -\n"
"Return: swh.User found, or None");

static PyObject * pyswh_Data_new(PyTypeObject* tp, PyObject* args, PyObject* kwds)
{
    pyswh_Object* self = pyswh_Object_new(tp);
    if (self)
        swhxx_db_data_new(&self->p);
    else
        self->p = NULL;
    return (PyObject*) self;
}

static void pyswh_Data_dealloc(pyswh_Object* self)
{
    if (self->p)
        swhxx_db_data_dealloc(&self->p);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pyswh_Data_init(pyswh_Object* self, PyObject* args, PyObject* kwds)
{
    char* title = "now", *dt = "", *tz = "", *loc = "", *ctry = "";
    double jd = swh_jdnow(), lat = 0, lon = 0;
    int alt = 0, isdst = -1;
    static char* kwlist[] = {"title", "jd", "lat", "lon", "alt", "datetime",
                             "timezone", "isdst", "location", "country", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|sdddississ", kwlist,
            &title, &jd, &lat, &lon, &alt, &dt, &tz, &loc, &ctry))
        return -1;
    if (swhxx_db_data_set_title(self->p, title)
        || swhxx_db_data_set_jd(self->p, jd)
        || swhxx_db_data_set_lat(self->p, lat)
        || swhxx_db_data_set_lon(self->p, lon)
        || swhxx_db_data_set_alt(self->p, alt)
        || swhxx_db_data_set_datetime(self->p, dt)
        || swhxx_db_data_set_timezone(self->p, tz)
        || swhxx_db_data_set_isdst(self->p, isdst)
        || swhxx_db_data_set_location(self->p, loc)
        || swhxx_db_data_set_country(self->p, ctry)) {
        PyErr_SetString(PyExc_AttributeError, swhxx_get_error(self->p));
        swhxx_clear_error(self->p);
        return -1;
    }
    return 0;
}

static pyswh_int_getsetters pyswh_Data_getset_idx = {
    &swhxx_db_data_get_idx, &swhxx_db_data_set_idx
};
static pyswh_int_getsetters pyswh_Data_getset_uidx = {
    &swhxx_db_data_get_uidx, &swhxx_db_data_set_uidx
};
static pyswh_string_getsetters pyswh_Data_getset_title = {
    &swhxx_db_data_get_title, &swhxx_db_data_set_title
};
static pyswh_double_getsetters pyswh_Data_getset_jd = {
    &swhxx_db_data_get_jd, &swhxx_db_data_set_jd
};
static pyswh_double_getsetters pyswh_Data_getset_lat = {
    &swhxx_db_data_get_lat, &swhxx_db_data_set_lat
};
static pyswh_double_getsetters pyswh_Data_getset_lon = {
    &swhxx_db_data_get_lon, &swhxx_db_data_set_lon
};
static pyswh_int_getsetters pyswh_Data_getset_alt = {
    &swhxx_db_data_get_alt, &swhxx_db_data_set_alt
};
static pyswh_string_getsetters pyswh_Data_getset_datetime = {
    &swhxx_db_data_get_datetime, &swhxx_db_data_set_datetime
};
static pyswh_string_getsetters pyswh_Data_getset_timezone = {
    &swhxx_db_data_get_timezone, &swhxx_db_data_set_timezone
};
static pyswh_int_getsetters pyswh_Data_getset_isdst = {
    &swhxx_db_data_get_isdst, &swhxx_db_data_set_isdst
};
static pyswh_string_getsetters pyswh_Data_getset_location = {
    &swhxx_db_data_get_location, &swhxx_db_data_set_location
};
static pyswh_string_getsetters pyswh_Data_getset_country = {
    &swhxx_db_data_get_country, &swhxx_db_data_set_country
};

static PyGetSetDef pyswh_Data_getsetters[] = {
{"_idx", (getter) pyswh_Object_get_int, (setter) pyswh_Object_set_int,
    pyswh_Data_idx__doc__, &pyswh_Data_getset_idx},
{"_uidx", (getter) pyswh_Object_get_int, (setter) pyswh_Object_set_int,
    pyswh_Data_uidx__doc__, &pyswh_Data_getset_uidx},
{"title", (getter) pyswh_Object_get_string, (setter) pyswh_Object_set_string,
    pyswh_Data_title__doc__, &pyswh_Data_getset_title},
{"jd", (getter) pyswh_Object_get_double, (setter) pyswh_Object_set_double,
    pyswh_Data_jd__doc__, &pyswh_Data_getset_jd},
{"lat", (getter) pyswh_Object_get_double, (setter) pyswh_Object_set_double,
    pyswh_Data_lat__doc__, &pyswh_Data_getset_lat},
{"lon", (getter) pyswh_Object_get_double, (setter) pyswh_Object_set_double,
    pyswh_Data_lon__doc__, &pyswh_Data_getset_lon},
{"alt", (getter) pyswh_Object_get_int, (setter) pyswh_Object_set_int,
    pyswh_Data_alt__doc__, &pyswh_Data_getset_alt},
{"datetime", (getter) pyswh_Object_get_string, (setter) pyswh_Object_set_string,
    pyswh_Data_datetime__doc__, &pyswh_Data_getset_datetime},
{"timezone", (getter) pyswh_Object_get_string, (setter) pyswh_Object_set_string,
    pyswh_Data_timezone__doc__, &pyswh_Data_getset_timezone},
{"isdst", (getter) pyswh_Object_get_int, (setter) pyswh_Object_set_int,
    pyswh_Data_isdst__doc__, &pyswh_Data_getset_isdst},
{"location", (getter) pyswh_Object_get_string, (setter) pyswh_Object_set_string,
    pyswh_Data_location__doc__, &pyswh_Data_getset_location},
{"country", (getter) pyswh_Object_get_string, (setter) pyswh_Object_set_string,
    pyswh_Data_country__doc__, &pyswh_Data_getset_country},
{NULL}
};

PyObject * pyswh_Data_owner FUNCARGS_SELF;

static PyMethodDef pyswh_Data_methods[] = {
{"owner", (PyCFunction) pyswh_Data_owner,
    METH_NOARGS, pyswh_Data_owner__doc__},
{NULL}
};

static PyTypeObject pyswh_Data_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "swisseph.contrib.Data",
    .tp_doc = pyswh_Data__doc__,
    .tp_basicsize = sizeof(pyswh_Object),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE,
    .tp_new = pyswh_Data_new,
    .tp_init = (initproc) pyswh_Data_init,
    .tp_dealloc = (destructor) pyswh_Data_dealloc,
    /*.tp_members = pyswh_Data_members,*/
    .tp_methods = pyswh_Data_methods,
    .tp_getset = pyswh_Data_getsetters,
};

PyObject * pyswh_Data_owner FUNCARGS_SELF
{
    pyswh_Object* o = (pyswh_Object*) self;
    void* p;
    char err[512];
    if (swhxx_db_data_owner(o->p, &p, err)) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    if (!p)
        Py_RETURN_NONE;
    if (!(o = pyswh_Object_new(&pyswh_User_type))) {
        swhxx_db_user_dealloc(&p);
        return PyErr_NoMemory();
    }
    o->p = p;
    return (PyObject*) o;
}

/* swisseph.contrib.antiscion */
PyDoc_STRVAR(pyswh_antiscion__doc__,
"Calculate antiscion and contrantiscion of an object\n\n"
"Usage example:\n\n"
"\tpos, flg = swh.calc_ut(jd, pl)\n"
"\tantis, contrantis = swh.antiscion(*pos)\n\n"
"Args: float lon, float lat=0, float dist=0, float lonspeed=0, float latspeed=0,"
" float distspeed=0, float axis=90\n"
"Return: antiscion (lon, lat, dist, lonspeed, latspeed, distspeed) contrantiscion (...)");

static PyObject * pyswh_antiscion FUNCARGS_KEYWDS
{
    double p[6] = {0,0,0,0,0,0}, antis[6], contrantis[6], axis = 90;
    static char* kwlist[] = {"lon", "lat", "dist", "lonspeed", "latspeed",
                             "distspeed", "axis", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d|dddddd", kwlist,
        &p[0], &p[1], &p[2], &p[3], &p[4], &p[5], &axis))
        return NULL;
    swh_antiscion(p, axis, antis, contrantis);
    return Py_BuildValue("(dddddd)(dddddd)", antis[0],antis[1],antis[2],antis[3],
        antis[4],antis[5],contrantis[0],contrantis[1],contrantis[2],contrantis[3],
        contrantis[4],contrantis[5]);
}

/* swisseph.contrib.atlas_close */
PyDoc_STRVAR(pyswh_atlas_close__doc__,
"Close previously connected atlas database\n\n"
"Args: -\n"
"Return: None");

static PyObject * pyswh_atlas_close FUNCARGS_SELF
{
    if (swh_atlas_close()) {
        PyErr_SetString(pyswe_Error, "swisseph.contrib.atlas_close: error");
        return NULL;
    }
    Py_RETURN_NONE;
}

/* swisseph.contrib.atlas_connect */
PyDoc_STRVAR(pyswh_atlas_connect__doc__,
"Connect to the atlas database\n\n"
"The environment variable SWH_ATLAS_PATH will be searched for a valid string"
" and will override the path argument given.\n\n"
"Args: str path=''\n"
"Return: None");

static PyObject * pyswh_atlas_connect FUNCARGS_KEYWDS
{
    char* p = NULL;
    static char* kwlist[] = {"path", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "|s", kwlist, &p))
        return NULL;
    if (swh_atlas_connect(p)) {
        PyErr_SetString(pyswe_Error, "swisseph.contrib.atlas_connect: error");
        return NULL;
    }
    Py_RETURN_NONE;
}

/* swisseph.contrib.atlas_countries_list */
PyDoc_STRVAR(pyswh_atlas_countries_list__doc__,
"Get a list of all countries (and ISO codes) in the atlas database\n\n"
"Args: -\n"
"Return: list of (country, code)");

int pyswh_atlas_countries_list_cb(void* p, int argc, char** argv, char** cols)
{
    PyObject* lst = (PyObject*) p;
    PyObject* tup = Py_BuildValue("(ss)", argv[5], argv[1]);
    if (!tup)
        return 1;
    if (PyList_Append(lst, tup))
        return 1;
    return 0;
}

static PyObject * pyswh_atlas_countries_list FUNCARGS_SELF
{
    int x;
    char err[512] = {'\0'};
    PyObject* p = PyList_New(0);
    if (!p)
        return PyErr_NoMemory();
    x = swh_atlas_countries_list(&pyswh_atlas_countries_list_cb, p, err);
    if (x) {
        if (*err)
            return PyErr_Format(pyswe_Error, "swisseph.contrib.atlas_countries: %s", err);
        else
            PyErr_SetString(pyswe_Error, "swisseph.contrib.atlas_countries: error");
        Py_DECREF(p);
        return NULL;
    }
    return p;
}

/* swisseph.contrib.atlas_search */
PyDoc_STRVAR(pyswh_atlas_search__doc__,
"Search for a location in the atlas database.\n\n"
"Location and country names can be abbreviated. If country is a 2-character"
" string, it will be evaluated as an ISO country code, and the search will be"
" faster.\n\n"
"Usage example:\n\n"
"\tlst = swh.atlas_search('zurich', 'swi')\n"
"\tlst = swh.atlas_search('zurich', 'ch')\n\n"
"Args: str location, str country\n"
"Return: list of (name, asciiname, alternatenames, countrycode, latitude,"
" longitude, elevation, timezone)");

int pyswh_atlas_search_cb(void* p, int argc, char** argv, char** cols)
{
    PyObject* lst = (PyObject*) p;
    PyObject* tup = Py_BuildValue("(ssssddis)", argv[0], argv[1], argv[2],
        argv[3], *argv[4] ? atof(argv[4]) : 0, *argv[5] ? atof(argv[5]) : 0,
        *argv[6] ? atoi(argv[6]) : 0, argv[7]);
    if (!tup)
        return 1;
    if (PyList_Append(lst, tup))
        return 1;
    return 0;
}

static PyObject * pyswh_atlas_search FUNCARGS_KEYWDS
{
    char* loc, *ctry;
    int x;
    char err[512] = {'\0'};
    PyObject* p = NULL;
    static char* kwlist[] = {"location", "country", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ss", kwlist, &loc, &ctry))
        return NULL;
    if (!(p = PyList_New(0)))
        return PyErr_NoMemory();
    x = swh_atlas_search(loc, ctry, &pyswh_atlas_search_cb, p, err);
    if (x) {
        if (*err)
            return PyErr_Format(pyswe_Error, "swisseph.contrib.atlas_search: %s", err);
        else
            PyErr_SetString(pyswe_Error, "swisseph.contrib.atlas_search: error");
        Py_DECREF(p);
        return NULL;
    }
    return p;
}

/* swisseph.contrib.calc_ut */
PyDoc_STRVAR(pyswh_calc_ut__doc__,
"Calculate positions of either a planet (using function calc_ut)"
" or a fixed star (using function fixstar2_ut).\n\n"
"Args: float tjdut, int or str obj, flags=FLG_SWIEPH+FLG_SPEED\n"
"Return: 2 tuples: positions of object (on success), returned flags and object name\n\n"
"Usage examples:\n\n"
"\tres, xtra = swh.calc_ut(swh.jdnow(), swisseph.SUN)\n"
"\tres, xtra = swh.calc_ut(swh.jdnow(), \"Regulus\")");

static PyObject * pyswh_calc_ut FUNCARGS_KEYWDS
{
    int x, pl = 0, flags = SEFLG_SWIEPH+SEFLG_SPEED;
    double t, res[6] = {0,0,0,0,0,0};
    char err[256], nam[256] = {'\0'}, st[(SE_MAX_STNAME*2)+1] = {'\0'};
    char* star = NULL;
    PyObject* p;
    static char* kwlist[] = {"tjdut", "obj", "flags", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dO|i", kwlist,
        &t, &p, &flags))
        return NULL;
    if (PyLong_CheckExact(p)) /* long -> planet */
        pl = (int) PyLong_AsLong(p);
#if PY_MAJOR_VERSION >= 3
    else if (PyUnicode_CheckExact(p)) /* unicode -> fixed star */
        star = (char*) PyUnicode_AsUTF8(p);
#elif PY_MAJOR_VERSION < 3
    else if (PyInt_CheckExact(p)) /* int -> planet */
        pl = (int) PyInt_AsLong(p);
    else if (PyString_CheckExact(p)) /* str -> fixed star */
        star = PyString_AsString(p);
#endif
    else {
        PyErr_SetString(pyswe_Error, "swisseph.contrib.calc_ut: invalid body type");
        return NULL;
    }
    x = swh_calc_ut(t, pl, star, flags, res, st, err);
    if (x < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return star ?
        Py_BuildValue("(dddddd)(is)",res[0],res[1],res[2],res[3],res[4],res[5],
                x, st)
        : Py_BuildValue("(dddddd)(is)",res[0],res[1],res[2],res[3],res[4],res[5],
                x, swe_get_planet_name(pl, nam));
}

/* swisseph.contrib.db_close */
PyDoc_STRVAR(pyswh_db_close__doc__,
"Close previously connected astro database\n\n"
"Args: -\n"
"Return: None");

static PyObject * pyswh_db_close FUNCARGS_SELF
{
    if (swh_db_close()) {
        PyErr_SetString(pyswe_Error, "swisseph.contrib.db_close: error");
        return NULL;
    }
    Py_RETURN_NONE;
}

/* swisseph.contrib.db_connect */
PyDoc_STRVAR(pyswh_db_connect__doc__,
"Args: str path='', bool check=True\n"
"Return: None");

static PyObject * pyswh_db_connect FUNCARGS_KEYWDS
{
    int check = 1;
    char* p = NULL;
    char err[512];
    static char* kwlist[] = {"path", "check", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "|sp", kwlist, &p, &check))
        return NULL;
    if (swh_db_connect(p, check, err))
        return PyErr_Format(pyswe_Error, "swisseph.contrib.db_connect: %s", err);
    Py_RETURN_NONE;
}

/* swisseph.contrib.degsplit */
PyDoc_STRVAR(pyswh_degsplit__doc__,
"Get degrees [0;29], sign number [0;11], minutes [0;59], seconds [0;59],"
" from a longitude position [0;360[.\n\n"
"Args: float deg\n"
"Return: 4 int (degree, sign, minutes, seconds)");

static PyObject * pyswh_degsplit FUNCARGS_KEYWDS
{
    int ret[6];
    double pos;
    static char *kwlist[] = {"deg", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &pos))
        return NULL;
    swh_degsplit(pos, ret);
    return Py_BuildValue("iiii", ret[0], ret[1], ret[2], ret[3]);
}

/* swisseph.contrib.dt2i */
PyDoc_STRVAR(pyswh_dt2i__doc__,
"Split a standardized datetime string 'YYYY-mm-dd HH:MM:SS' into integers.\n\n"
"Datetimes are expected to roughly follow the ISO 8601 standard,"
" 'Year-Month-Day Hour:Minutes:Seconds'.\n"
"All non-digits in the given string are ignored and any of them can be"
" used as separator, including spaces. A minus is evaluated only in"
" front of the year, as first char of the string.\n"
"Optionaly, the time part (hour etc) can be omitted, in that case will"
" return zeros.\n\n"
"Args: str dt\n"
"Return: 6 int (year, month, day, hour, minutes, seconds)");

static PyObject * pyswh_dt2i FUNCARGS_KEYWDS
{
    int x;
    char* dt;
    int ret[6];
    static char* kwlist[] = {"dt", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "s", kwlist, &dt))
        return NULL;
    x = swh_dt2i(dt, ret);
    if (x) {
        PyErr_SetString(pyswe_Error, "swisseph.contrib.dt2i: invalid string");
        return NULL;
    }
    return Py_BuildValue("iiiiii",ret[0],ret[1],ret[2],ret[3],ret[4],ret[5]);
}

/* swisseph.contrib.geoc2d */
PyDoc_STRVAR(pyswh_geoc2d__doc__,
"Get float from given string meant as a geographical coordinates.\n\n"
"Possible string formats:\n"
" - DMSx\n"
" - DxMS\n"
" - DMx\n"
" - DxM\n"
" - DMS\n"
" - Dx\n"
" - DM\n"
" - D\n"
"Where D is degrees, M is minutes, S is seconds, x is a char in \"NSEW\""
" (direction).\n"
"The last number given can be a floating point number.\n"
"If no direction is given, a negative degree value is accepted down to -180.\n"
"Decorations chars (like °\"':/,) can serve as separators and are accepted"
" anywhere (ignored), as well as spaces.\n\n"
"Args: str coord\n"
"Return: float");

static PyObject * pyswh_geoc2d FUNCARGS_KEYWDS
{
    int res;
    double ret;
    char *coord;
    static char *kwlist[] = {"coord", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "s", kwlist, &coord))
        return NULL;
    res = swh_geoc2d(coord, &ret);
    if (res) {
        PyErr_SetString(pyswe_Error, "swisseph.contrib.geoc2d: invalid coord string");
        return NULL;
    }
    return Py_BuildValue("d", ret);
}

/* swisseph.contrib.geolat2c */
PyDoc_STRVAR(pyswh_geolat2c__doc__,
"Get formated string of given geographical latitude.\n\n"
"Args: float lat\n"
"Return: str");

static PyObject * pyswh_geolat2c FUNCARGS_KEYWDS
{
    int res;
    double lat;
    char ret[11];
    static char *kwlist[] = {"lat", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &lat))
        return NULL;
    res = swh_geolat2c(lat, ret);
    if (res == -1) {
        PyErr_SetString(pyswe_Error, "swisseph.contrib.geolat2c: invalid latitude");
        return NULL;
    }
    return Py_BuildValue("s", ret);
}

/* swisseph.contrib.geolon2c */
PyDoc_STRVAR(pyswh_geolon2c__doc__,
"Get formated string of given geographical longitude.\n\n"
"Args: float lon\n"
"Return: str");

static PyObject * pyswh_geolon2c FUNCARGS_KEYWDS
{
    int res;
    double lon;
    char ret[12];
    static char *kwlist[] = {"lon", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &lon))
        return NULL;
    res = swh_geolon2c(lon, ret);
    if (res == -1) {
        PyErr_SetString(pyswe_Error, "swisseph.contrib.geolon2c: invalid longitude");
        return NULL;
    }
    return Py_BuildValue("s", ret);
}

/* swisseph.contrib.get_nakshatra_name */
PyDoc_STRVAR(pyswh_get_nakshatra_name__doc__,
"Get nakshatra name from nakshatra number [0:26].\n\n"
"Args: int nakshatra\n"
"Return: str");

static PyObject * pyswh_get_nakshatra_name FUNCARGS_KEYWDS
{
    char ret[15];
    int nak;
    static char *kwlist[] = {"nakshatra", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i", kwlist, &nak))
        return NULL;
    if (swh_get_nakshatra_name(nak, ret) == -1) {
        PyErr_SetString(pyswe_Error, "swisseph.contrib.get_nakshatra_name: invalid nakshatra number");
        return NULL;
    }
    return Py_BuildValue("s", ret);
}

/* swisseph.contrib.house_system_name */
PyDoc_STRVAR(pyswh_house_system_name__doc__,
"Get house system name from given char identifier.\n\n"
"Will check for identifier validity instead of just returning 'Placidus' when"
" given char is unknown/invalid.\n\n"
"Args: str hsys\n"
"Return: str");

static PyObject * pyswh_house_system_name FUNCARGS_KEYWDS
{
    char* hsys, str[50];
    static char *kwlist[] = {"hsys", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "s", kwlist, &hsys))
        return NULL;
    if (strlen(hsys) != 1 || swh_house_system_name(*hsys, str)) {
        PyErr_SetString(pyswe_Error,
            "swisseph.contrib.house_system_name: invalid house system identifier");
        return NULL;
    }
    return Py_BuildValue("s", str);
}

/* swisseph.contrib.jd2isostr */
PyDoc_STRVAR(pyswh_jd2isostr__doc__,
"Get an ISO 8601 style string from given JD number.\n\n"
"Args: float jd, int cal=GREG_CAL\n"
"Return: str");

static PyObject * pyswh_jd2isostr FUNCARGS_KEYWDS
{
    int cal = SE_GREG_CAL;
    double jd;
    char ret[64];
    static char* kwlist[] = {"jd", "cal", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d|i", kwlist, &jd, &cal))
        return NULL;
    if (swh_jd2isostr(jd, cal, ret)) {
        PyErr_SetString(pyswe_Error, "swisseph.contrib.jd2isostr: error");
        return NULL;
    }
    return Py_BuildValue("s", ret);
}

/* swisseph.contrib.jdnow */
PyDoc_STRVAR(pyswh_jdnow__doc__,
"Get current Julian day number (Gregorian calendar, UTC).\n\n"
"Args: -\n"
"Return: float");

static PyObject * pyswh_jdnow FUNCARGS_SELF
{
    return Py_BuildValue("d", swh_jdnow());
}

/* swisseph.contrib.jduration */
PyDoc_STRVAR(pyswh_jduration__doc__,
"Get duration between JD numbers.\n\n"
"Args: float jdstart, float jdend\n"
"Return: 4 ints (days, hours, minutes, seconds)");

static PyObject * pyswh_jduration FUNCARGS_KEYWDS
{
    double jd1, jd2;
    int ret[4];
    static char* kwlist[] = {"jdstart", "jdend", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dd", kwlist, &jd1, &jd2))
        return NULL;
    swh_jduration(jd1, jd2, ret);
    return Py_BuildValue("iiii", ret[0],ret[1],ret[2],ret[3]);
}

/* swisseph.contrib.julday */
PyDoc_STRVAR(pyswh_julday__doc__,
"Get Julian day number (UTC), without having to calculate hour in decimal.\n\n"
"Args: int year, int month, int day, int hour=12, int minutes=0, int seconds=0,"
" int flag=GREG_FLAG\n"
"Return: float");

static PyObject * pyswh_julday FUNCARGS_KEYWDS
{
    int year, mon, day, hour=12, min=0, sec=0, flag=SE_GREG_CAL;
    static char *kwlist[] = {"year", "month", "day", "hour", "minutes",
        "seconds", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "iii|iiii", kwlist,
        &year, &mon, &day, &hour, &min, &sec, &flag))
        return NULL;
    return Py_BuildValue("d", swh_julday(year, mon, day, hour,
        min, sec, flag));
}

/* swisseph.contrib.long2nakshatra */
PyDoc_STRVAR(pyswh_long2nakshatra__doc__,
"Get nakshatra and pada from ecliptical longitude.\n\n"
"Args: float lon\n"
"Return: 2 int");

static PyObject * pyswh_long2nakshatra FUNCARGS_KEYWDS
{
    int ret[2];
    double lon;
    static char *kwlist[] = {"lon", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &lon))
        return NULL;
    swh_long2nakshatra(lon, ret);
    return Py_BuildValue("ii", ret[0], ret[1]);
}

/* swisseph.contrib.long2navamsa */
PyDoc_STRVAR(pyswh_long2navamsa__doc__,
"Get navamsa from ecliptical longitude.\n\n"
"Args: float lon\n"
"Return: int");

static PyObject * pyswh_long2navamsa FUNCARGS_KEYWDS
{
    double lon;
    static char *kwlist[] = {"lon", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &lon))
        return NULL;
    return Py_BuildValue("i", swh_long2navamsa(lon));
}

/* swisseph.contrib.long2rasi */
PyDoc_STRVAR(pyswh_long2rasi__doc__,
"Get rasi number from ecliptical longitude.\n\n"
"Args: float lon\n"
"Return: int");

static PyObject * pyswh_long2rasi FUNCARGS_KEYWDS
{
    double lon;
    static char *kwlist[] = {"lon", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &lon))
        return NULL;
    return Py_BuildValue("i", swh_long2rasi(lon));
}

/* swisseph.contrib.lord */
PyDoc_STRVAR(pyswh_lord__doc__,
"Get sign lord.\n\n"
"Args: int sign [0:11]\n"
"Return: int planet number");

static PyObject * pyswh_lord FUNCARGS_KEYWDS
{
    int sign, i;
    static char *kwlist[] = {"sign", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i", kwlist, &sign))
        return NULL;
    i = swh_lord(sign);
    if (i == -1) {
        PyErr_SetString(pyswe_Error, "swisseph.contrib.lord: invalid sign number");
        return NULL;
    }
    return Py_BuildValue("i", i);
}

/* swisseph.contrib.match_aspect */
PyDoc_STRVAR(pyswh_match_aspect__doc__,
"Aspect matching - aspect in range [0;360[\n\n"
"Check if the two given positions match the aspect within the given orb.\n"
"This also calculates the difference between targeted aspect and objects"
" distance (so that pos1 + asp + delta = pos2), and its speed (so that"
" a negative speed indicates an applying aspect). Returned factor simply"
" is that difference expressed in orb units (so that orb * factor = delta).\n\n"
"If you are not interested in that mumbo-jumbo, just set objects speeds to"
" zero, and consider only the boolean returned by the function.\n\n"
"Args: float pos1, float speed1, float pos2, float speed2, float aspect,"
" float orb\n"
"Return: True if match, else False, and tuple (delta, deltaspeed, factor)");

static PyObject * pyswh_match_aspect FUNCARGS_KEYWDS
{
    double x, pos0, pos1, sp0, sp1, asp, orb, diff, applic, ftor;
    static char *kwlist[] = {"pos1", "speed1", "pos2", "speed2", "aspect",
        "orb", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dddddd", kwlist,
        &pos0, &sp0, &pos1, &sp1, &asp, &orb))
        return NULL;
    x = swh_match_aspect(pos0, sp0, pos1, sp1, asp, orb, &diff, &applic, &ftor);
    return Py_BuildValue("O(ddd)", x ? Py_False : Py_True, diff, applic, ftor);
}

/* swisseph.contrib.match_aspect2 */
PyDoc_STRVAR(pyswh_match_aspect2__doc__,
"Aspect matching - aspect in range [0;180]\n\n"
"Same as match_aspect, but with aspect in range [0;180].\n\n"
"Args: float pos1, float speed1, float pos2, float speed2, float aspect,"
" float orb\n"
"Return: True if match, else False, and tuple (delta, deltaspeed, factor)");

static PyObject * pyswh_match_aspect2 FUNCARGS_KEYWDS
{
    double x, pos0, pos1, sp0, sp1, asp, orb, diff, applic, ftor;
    static char *kwlist[] = {"pos1", "speed1", "pos2", "speed2", "aspect",
        "orb", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dddddd", kwlist,
        &pos0, &sp0, &pos1, &sp1, &asp, &orb))
        return NULL;
    x = swh_match_aspect2(pos0, sp0, pos1, sp1, asp, orb, &diff, &applic, &ftor);
    return Py_BuildValue("O(ddd)", x ? Py_False : Py_True, diff, applic, ftor);
}

/* swisseph.contrib.match_aspect3 */
PyDoc_STRVAR(pyswh_match_aspect3__doc__,
"Aspect matching - aspect in range [0;360[ and complex orb\n\n"
"Same as match_aspect, but with specific orbs for applying/separating/stable"
" aspects.\n\n"
"Args: float pos1, float speed1, float pos2, float speed2, float aspect,"
" float app_orb, float sep_orb, float sta_orb\n"
"Return: True if match, else False, and tuple (delta, deltaspeed, factor)");

static PyObject * pyswh_match_aspect3 FUNCARGS_KEYWDS
{
    double x, pos0, pos1, sp0, sp1, asp, app_orb, sep_orb, sta_orb, diff, applic, ftor;
    static char *kwlist[] = {"pos1", "speed1", "pos2", "speed2", "aspect",
        "app_orb", "sep_orb", "sta_orb", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dddddddd", kwlist,
        &pos0, &sp0, &pos1, &sp1, &asp, &app_orb, &sep_orb, &sta_orb))
        return NULL;
    x = swh_match_aspect3(pos0, sp0, pos1, sp1, asp, app_orb, sep_orb, sta_orb,
        &diff, &applic, &ftor);
    return Py_BuildValue("O(ddd)", x ? Py_False : Py_True, diff, applic, ftor);
}

/* swisseph.contrib.match_aspect4 */
PyDoc_STRVAR(pyswh_match_aspect4__doc__,
"Aspect matching - aspect in range [0;180] and complex orb\n\n"
"Same as match_aspect2, but with specific orbs for applying/separating/stable"
" aspects.\n\n"
"Args: float pos1, float speed1, float pos2, float speed2, float aspect,"
" float app_orb, float sep_orb, float sta_orb\n"
"Return: True if match, else False, and tuple (delta, deltaspeed, factor)");

static PyObject * pyswh_match_aspect4 FUNCARGS_KEYWDS
{
    double x, pos0, pos1, sp0, sp1, asp, app_orb, sep_orb, sta_orb, diff, applic, ftor;
    static char *kwlist[] = {"pos1", "speed1", "pos2", "speed2", "aspect",
        "app_orb", "sep_orb", "sta_orb", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dddddddd", kwlist,
        &pos0, &sp0, &pos1, &sp1, &asp, &app_orb, &sep_orb, &sta_orb))
        return NULL;
    x = swh_match_aspect4(pos0, sp0, pos1, sp1, asp, app_orb, sep_orb, sta_orb,
        &diff, &applic, &ftor);
    return Py_BuildValue("O(ddd)", x ? Py_False : Py_True, diff, applic, ftor);
}

/* swisseph.contrib.naisargika_relation */
PyDoc_STRVAR(pyswh_naisargika_relation__doc__,
"Get the naisargika relation between two planets.\n\n"
"Args: int gr1, int gr2\n"
"Return: int 1 (Mitra) 0 (Sama) or -1 (Satru)");

static PyObject * pyswh_naisargika_relation FUNCARGS_KEYWDS
{
    int gr1, gr2, i, ret;
    static char *kwlist[] = {"gr1", "gr2", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ii", kwlist, &gr1, &gr2))
        return NULL;
    i = swh_naisargika_relation(gr1, gr2, &ret);
    if (i == -1) {
        PyErr_SetString(pyswe_Error, "swisseph.contrib.naisargika_relation: invalid planet");
        return NULL;
    }
    return Py_BuildValue("i", ret);
}

/* swisseph.contrib.next_aspect */
PyDoc_STRVAR(pyswh_next_aspect__doc__,
"Get Julian day number and positions when celestial object makes longitudinal"
" aspect to a fixed point expressed in longitude degrees.\n\n"
"Aspect and fixed point in the range [0;360[.\n"
"Can return None if time limit (variable stop, expressed in days) has been"
" reached.\n\n"
"Args: int planet, float aspect, float fixedpt, float jdstart,"
" bool backw=False, float stop=0, int flags=FLG_SWIEPH+FLG_SPEED+FLG_NOGDEFL\n"
"Return: Julian day, positions (or None if time limit has been reached)");

static PyObject * pyswh_next_aspect FUNCARGS_KEYWDS
{
    int res, plnt, backw=0, flag=SEFLG_SWIEPH|SEFLG_SPEED|SEFLG_NOGDEFL;
    double asp, fix, jd, trange=0, jdret, posret[6];
    char err[256];
    static char *kwlist[] = {"planet", "aspect", "fixedpt", "jdstart",
        "backw", "stop", "flags", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "iddd|idi", kwlist,
        &plnt, &asp, &fix, &jd, &backw, &trange, &flag))
        return NULL;
    res = swh_next_aspect(plnt, asp, fix, jd, backw, trange, flag,
        &jdret, posret, err);
    switch (res) {
    case 1: /* internal error */
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    case 2: /* time limit reached */
        return Py_BuildValue("O(OOOOOO)", Py_None, Py_None, Py_None, Py_None,
            Py_None, Py_None, Py_None);
    default:
        return Py_BuildValue("d(dddddd)", jdret, posret[0], posret[1],
            posret[2], posret[3], posret[4], posret[5]);
    }
}

/* swisseph.contrib.next_aspect2 */
PyDoc_STRVAR(pyswh_next_aspect2__doc__,
"Same as next_aspect, but with aspect in range [0;180].\n\n"
"Args: int planet, float aspect, float fixedpt, float jdstart,"
" bool backw=False, float stop=0, int flags=FLG_SWIEPH+FLG_SPEED+FLG_NOGDEFL\n"
"Return: Julian day, positions (or None if time limit has been reached)");

static PyObject * pyswh_next_aspect2 FUNCARGS_KEYWDS
{
    int res, plnt, backw=0, flag=SEFLG_SWIEPH|SEFLG_SPEED|SEFLG_NOGDEFL;
    double asp, fix, jd, trange=0, jdret, posret[6];
    char err[256];
    static char *kwlist[] = {"planet", "aspect", "fixedpt", "jdstart",
        "backw", "stop", "flags", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "iddd|idi", kwlist,
        &plnt, &asp, &fix, &jd, &backw, &trange, &flag))
        return NULL;
    res = swh_next_aspect2(plnt, asp, fix, jd, backw, trange, flag,
        &jdret, posret, err);
    switch (res) {
    case 1: /* internal error */
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    case 2: /* time limit reached */
        return Py_BuildValue("O(OOOOOO)", Py_None, Py_None, Py_None, Py_None,
            Py_None, Py_None, Py_None);
    default:
        return Py_BuildValue("d(dddddd)", jdret, posret[0], posret[1],
            posret[2], posret[3], posret[4], posret[5]);
    }
}

/* swisseph.contrib.next_aspect_cusp */
PyDoc_STRVAR(pyswh_next_aspect_cusp__doc__,
"Get Julian day number and positions, and houses cusps and ascmc, when celestial"
" object makes longitudinal aspect to a house cusp.\n\n"
"House cusp expressed as an integer in range [1;12] or [1;36] for Gauquelin.\n"
"Aspect in the range [0;360[.\n"
"Body can be a fixed star.\n"
"For risings, settings, meridian transits, see rise_trans.\n\n"
"Args: int or str body, float aspect, int cusp, float jdstart, float lat,"
" float lon, char hsys='P', bool backw=False, int flags=FLG_SWIEPH+FLG_SPEED\n"
"Return: Julian day, body positions, cusps, ascmc");

static PyObject * pyswh_next_aspect_cusp FUNCARGS_KEYWDS
{
    int res, plnt = 0, cusp, hsys='P', backw=0, flag=SEFLG_SWIEPH|SEFLG_SPEED;
    double asp, jd, lat, lon, jdret, posret[6], cusps[37], ascmc[10];
    char err[256], *star=NULL;
    PyObject *body;
    static char *kwlist[] = {"body", "aspect", "cusp", "jdstart", "lat", "lon",
        "hsys", "backw", "flags", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "Odiddd|cii", kwlist,
        &body, &asp, &cusp, &jd, &lat, &lon, &hsys, &backw, &flag))
        return NULL;
    if (PyLong_CheckExact(body)) /* long -> planet */
        plnt = (int) PyLong_AsLong(body);
#if PY_MAJOR_VERSION >= 3
    else if (PyUnicode_CheckExact(body)) /* unicode -> fixed star */
        star = (char*) PyUnicode_AsUTF8(body);
#elif PY_MAJOR_VERSION < 3
    else if (PyInt_CheckExact(body)) /* int -> planet */
        plnt = (int) PyInt_AsLong(body);
    else if (PyString_CheckExact(body)) /* str -> fixed star */
        star = PyString_AsString(body);
#endif
    else {
        PyErr_SetString(pyswe_Error,
            "swisseph.contrib.next_aspect_cusp: invalid body type");
        return NULL;
    }
    res = swh_next_aspect_cusp(plnt, star, asp, cusp, jd, lat, lon, hsys,
        backw, flag, &jdret, posret, cusps, ascmc, err);
    if (res == 1) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    assert(!res);
    if (hsys == 71) /* Gauquelin sectors */
        return Py_BuildValue("d(dddddd)(dddddddddddddddddddddddddddddddddddd)(dddddddd)",
        jdret,
        posret[0], posret[1], posret[2], posret[3], posret[4], posret[5],
        cusps[1], cusps[2], cusps[3], cusps[4], cusps[5], cusps[6], cusps[7],
        cusps[8], cusps[9], cusps[10], cusps[11], cusps[12], cusps[13],
        cusps[14], cusps[15], cusps[16], cusps[17], cusps[18], cusps[19],
        cusps[20], cusps[21], cusps[22], cusps[23], cusps[24], cusps[25],
        cusps[26], cusps[27], cusps[28], cusps[29], cusps[30], cusps[31],
        cusps[32], cusps[33], cusps[34], cusps[35], cusps[36],
        ascmc[0], ascmc[1], ascmc[2], ascmc[3], ascmc[4], ascmc[5], ascmc[6],
        ascmc[7]);
    return Py_BuildValue("d(dddddd)(dddddddddddd)(dddddddd)", jdret,
    posret[0], posret[1], posret[2], posret[3], posret[4], posret[5],
    cusps[1], cusps[2], cusps[3], cusps[4], cusps[5], cusps[6], cusps[7],
    cusps[8], cusps[9], cusps[10], cusps[11], cusps[12],
    ascmc[0], ascmc[1], ascmc[2], ascmc[3], ascmc[4], ascmc[5], ascmc[6],
    ascmc[7]);
}

/* swisseph.contrib.next_aspect_cusp2 */
PyDoc_STRVAR(pyswh_next_aspect_cusp2__doc__,
"Same as next_aspect_cusp, but aspect in range[0;180].\n\n"
"Args: int or str body, float aspect, int cusp, float jdstart, float lat,"
" float lon, char hsys='P', bool backw=False, int flags=FLG_SWIEPH+FLG_SPEED\n"
"Return: Julian day, body positions, cusps, ascmc");

static PyObject * pyswh_next_aspect_cusp2 FUNCARGS_KEYWDS
{
    int res, plnt=0, cusp, hsys='P', backw=0, flag=SEFLG_SWIEPH|SEFLG_SPEED;
    double asp, jd, lat, lon, jdret, posret[6], cusps[37], ascmc[10];
    char err[256], *star=NULL;
    PyObject *body;
    static char *kwlist[] = {"body", "aspect", "cusp", "jdstart", "lat", "lon",
        "hsys", "backw", "flags", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "Odiddd|cii", kwlist,
        &body, &asp, &cusp, &jd, &lat, &lon, &hsys, &backw, &flag))
        return NULL;
    if (PyLong_CheckExact(body)) /* long -> planet */
        plnt = (int) PyLong_AsLong(body);
#if PY_MAJOR_VERSION >= 3
    else if (PyUnicode_CheckExact(body)) /* unicode -> fixed star */
        star = (char*) PyUnicode_AsUTF8(body);
#elif PY_MAJOR_VERSION < 3
    else if (PyInt_CheckExact(body)) /* int -> planet */
        plnt = (int) PyInt_AsLong(body);
    else if (PyString_CheckExact(body)) /* str -> fixed star */
        star = PyString_AsString(body);
#endif
    else {
        PyErr_SetString(pyswe_Error,
            "swisseph.contrib.next_aspect_cusp2: invalid body type");
        return NULL;
    }
    res = swh_next_aspect_cusp2(plnt, star, asp, cusp, jd, lat, lon, hsys,
        backw, flag, &jdret, posret, cusps, ascmc, err);
    if (res == 1) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    assert(!res);
    if (hsys == 71) /* Gauquelin sectors */
        return Py_BuildValue("d(dddddd)(dddddddddddddddddddddddddddddddddddd)(dddddddd)",
        jdret,
        posret[0], posret[1], posret[2], posret[3], posret[4], posret[5],
        cusps[1], cusps[2], cusps[3], cusps[4], cusps[5], cusps[6], cusps[7],
        cusps[8], cusps[9], cusps[10], cusps[11], cusps[12], cusps[13],
        cusps[14], cusps[15], cusps[16], cusps[17], cusps[18], cusps[19],
        cusps[20], cusps[21], cusps[22], cusps[23], cusps[24], cusps[25],
        cusps[26], cusps[27], cusps[28], cusps[29], cusps[30], cusps[31],
        cusps[32], cusps[33], cusps[34], cusps[35], cusps[36],
        ascmc[0], ascmc[1], ascmc[2], ascmc[3], ascmc[4], ascmc[5], ascmc[6],
        ascmc[7]);
    return Py_BuildValue("d(dddddd)(dddddddddddd)(dddddddd)", jdret,
    posret[0], posret[1], posret[2], posret[3], posret[4], posret[5],
    cusps[1], cusps[2], cusps[3], cusps[4], cusps[5], cusps[6], cusps[7],
    cusps[8], cusps[9], cusps[10], cusps[11], cusps[12],
    ascmc[0], ascmc[1], ascmc[2], ascmc[3], ascmc[4], ascmc[5], ascmc[6],
    ascmc[7]);
}

/* swisseph.contrib.next_aspect_with */
PyDoc_STRVAR(pyswh_next_aspect_with__doc__,
"Get Julian day number and positions when celestial object makes longitudinal"
" aspect to another moving object.\n\n"
"Aspect in the range [0;360[.\n"
"Other object can be a fixed star.\n\n"
"Args: int planet, float aspect, int or str other, float jdstart,"
" bool backw=False, float stop=0, int flags=FLG_SWIEPH+FLG_SPEED\n"
"Return: Julian day, planet positions, other positions (or None if limit has been reached)");

static PyObject * pyswh_next_aspect_with FUNCARGS_KEYWDS
{
    int res, plnt, other=0, backw=0, flag=SEFLG_SWIEPH|SEFLG_SPEED;
    double asp, jd, trange=0, jdret, posret0[6], posret1[6];
    char err[256], *star=NULL;
    PyObject *body;
    static char *kwlist[] = {"planet", "aspect", "other", "jdstart",
        "backw", "stop", "flags", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "idOd|idi", kwlist,
        &plnt, &asp, &body, &jd, &backw, &trange, &flag))
        return NULL;
    if (PyLong_CheckExact(body)) /* long -> planet */
        other = (int) PyLong_AsLong(body);
#if PY_MAJOR_VERSION >= 3
    else if (PyUnicode_CheckExact(body)) /* unicode -> fixed star */
        star = (char*) PyUnicode_AsUTF8(body);
#elif PY_MAJOR_VERSION < 3
    else if (PyInt_CheckExact(body)) /* int -> planet */
        other = (int) PyInt_AsLong(body);
    else if (PyString_CheckExact(body)) /* str -> fixed star */
        star = PyString_AsString(body);
#endif
    else {
        PyErr_SetString(pyswe_Error,
            "swisseph.contrib.next_aspect_with: invalid body type");
        return NULL;
    }
    res = swh_next_aspect_with(plnt, asp, other, star, jd, backw, trange,
        flag, &jdret, posret0, posret1, err);
    switch (res) {
    case 1: /* internal error */
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    case 2: /* time limit reached */
        return Py_BuildValue("O(OOOOOO)(OOOOOO)", Py_None, Py_None, Py_None,
        Py_None, Py_None, Py_None, Py_None, Py_None, Py_None, Py_None, Py_None,
        Py_None, Py_None);
    default:
        return Py_BuildValue("d(dddddd)(dddddd)", jdret, posret0[0],
        posret0[1], posret0[2], posret0[3], posret0[4], posret0[5], posret1[0],
        posret1[1], posret1[2], posret1[3], posret1[4], posret1[5]);
    }
}

/* swisseph.contrib.next_aspect_with2 */
PyDoc_STRVAR(pyswh_next_aspect_with2__doc__,
"Same as next_aspect_with, but aspect in range [0;180].\n\n"
"Args: int planet, float aspect, int or str other, float jdstart,"
" bool backw=False, float stop=0, int flags=FLG_SWIEPH+FLG_SPEED\n"
"Return: Julian day, planet positions, other positions (or None if limit has been reached)");

static PyObject * pyswh_next_aspect_with2 FUNCARGS_KEYWDS
{
    int res, plnt, other=0, backw=0, flag=SEFLG_SWIEPH|SEFLG_SPEED;
    double asp, jd, trange=0, jdret, posret0[6], posret1[6];
    char err[256], *star=NULL;
    PyObject *body;
    static char *kwlist[] = {"planet", "aspect", "other", "jdstart",
        "backw", "stop", "flags", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "idOd|idi", kwlist,
        &plnt, &asp, &body, &jd, &backw, &trange, &flag))
        return NULL;
    if (PyLong_CheckExact(body)) /* long -> planet */
        other = (int) PyLong_AsLong(body);
#if PY_MAJOR_VERSION >= 3
    else if (PyUnicode_CheckExact(body)) /* unicode -> fixed star */
        star = (char*) PyUnicode_AsUTF8(body);
#elif PY_MAJOR_VERSION < 3
    else if (PyInt_CheckExact(body)) /* int -> planet */
        other = (int) PyInt_AsLong(body);
    else if (PyString_CheckExact(body)) /* str -> fixed star */
        star = PyString_AsString(body);
#endif
    else {
        PyErr_SetString(pyswe_Error,
            "swisseph.contrib.next_aspect_with2: invalid body type");
        return NULL;
    }
    res = swh_next_aspect_with2(plnt, asp, other, star, jd, backw, trange,
        flag, &jdret, posret0, posret1, err);
    switch (res) {
    case 1: /* internal error */
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    case 2: /* time limit reached */
        return Py_BuildValue("O(OOOOOO)(OOOOOO)", Py_None, Py_None, Py_None,
        Py_None, Py_None, Py_None, Py_None, Py_None, Py_None, Py_None, Py_None,
        Py_None, Py_None);
    default:
        return Py_BuildValue("d(dddddd)(dddddd)", jdret, posret0[0],
        posret0[1], posret0[2], posret0[3], posret0[4], posret0[5], posret1[0],
        posret1[1], posret1[2], posret1[3], posret1[4], posret1[5]);
    }
}

/* swisseph.contrib.next_retro */
PyDoc_STRVAR(pyswh_next_retro__doc__,
"Find next direction changing of object.\n\n"
"Flag should include FLG_SPEED, and FLG_NOGDEFL to avoid bad surprises;"
" alternatively use true positions.\n"
"If argument stop != 0, can return None if time limit has been reached.\n\n"
"Args: int planet, float jdstart, bool backw=False,"
" float stop=0, int flags=FLG_SWIEPH+FLG_SPEED+FLG_NOGDEFL\n"
"Return: Julian day, positions (or None if time limit has been reached)");

static PyObject * pyswh_next_retro FUNCARGS_KEYWDS
{
    int res, plnt, backw=0, flag=SEFLG_SWIEPH|SEFLG_SPEED|SEFLG_NOGDEFL;
    double jd, trange=0, jdret, posret[6];
    char err[256];
    static char *kwlist[] = {"planet", "jdstart", "backw", "stop", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "id|idi", kwlist,
        &plnt, &jd, &backw, &trange, &flag))
        return NULL;
    res = swh_next_retro(plnt, jd, backw, trange, flag, &jdret, posret, err);
    switch (res) {
    case 1: /* internal error */
    case 3: /* bad argument */
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    case 2: /* time limit reached */
        return Py_BuildValue("O(OOOOOO)", Py_None, Py_None, Py_None, Py_None,
            Py_None, Py_None, Py_None);
    default:
        return Py_BuildValue("d(dddddd)", jdret, posret[0], posret[1],
            posret[2], posret[3], posret[4], posret[5]);
    }
}

/* swisseph.contrib.ochchabala */
PyDoc_STRVAR(pyswh_ochchabala__doc__,
"Get the ochchabala for a planet.\n\n"
"Args: int pl, float longitude\n"
"Return: float shashtiamsa");

static PyObject * pyswh_ochchabala FUNCARGS_KEYWDS
{
    int ipl;
    double lon, d;
    static char *kwlist[] = {"pl", "longitude", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "id", kwlist, &ipl, &lon))
        return NULL;
    d = swh_ochchabala(ipl, lon);
    if (d == -1) {
        PyErr_SetString(pyswe_Error, "swisseph.contrib.ochchabala: invalid planet");
        return NULL;
    }
    return Py_BuildValue("d", d);
}

/* swisseph.contrib.raman_houses */
PyDoc_STRVAR(pyswh_raman_houses__doc__,
"Get Raman houses cusps (bhavamadhya the default, or arambhasandhi).\n\n"
"Args: float asc, float mc, bool sandhi=False\n"
"Return: tuple of 12 float");

static PyObject * pyswh_raman_houses FUNCARGS_KEYWDS
{
    int sdi = 0;
    double asc, mc, ret[12];
    static char *kwlist[] = {"asc", "mc", "sandhi", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dd|b", kwlist, &asc, &mc, &sdi))
        return NULL;
    swh_raman_houses(asc, mc, ret, sdi);
    return Py_BuildValue("dddddddddddd", ret[0],ret[1],ret[2],ret[3],ret[4],
        ret[5],ret[6],ret[7],ret[8],ret[9],ret[10],ret[11]);
}

/* swisseph.contrib.rasi_dif */
PyDoc_STRVAR(pyswh_rasi_dif__doc__,
"Get number of rasi between two rasis, from 0 to 11.\n\n"
"Args: int r1, int r2\n"
"Return: int");

static PyObject * pyswh_rasi_dif FUNCARGS_KEYWDS
{
    int r1, r2;
    static char *kwlist[] = {"r1", "r2", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ii", kwlist, &r1, &r2))
        return NULL;
    return Py_BuildValue("i", swh_rasi_dif(r1, r2));
}

/* swisseph.contrib.rasi_dif2 */
PyDoc_STRVAR(pyswh_rasi_dif2__doc__,
"Get number of rasi between two rasis, from -5 to 6.\n\n"
"Args: int r1, int r2\n"
"Return: int");

static PyObject * pyswh_rasi_dif2 FUNCARGS_KEYWDS
{
    int r1, r2;
    static char *kwlist[] = {"r1", "r2", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ii", kwlist, &r1, &r2))
        return NULL;
    return Py_BuildValue("i", swh_rasi_dif2(r1, r2));
}

/* swisseph.contrib.rasinorm */
PyDoc_STRVAR(pyswh_rasinorm__doc__,
"Get a normalized rasi number between 0 and 11.\n\n"
"Args: int rasi\n"
"Return: int");

static PyObject * pyswh_rasinorm FUNCARGS_KEYWDS
{
    int rasi;
    static char *kwlist[] = {"rasi", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i", kwlist, &rasi))
        return NULL;
    return Py_BuildValue("i", swh_rasinorm(rasi));
}

/* swisseph.contrib.residential_strength */
PyDoc_STRVAR(pyswh_residential_strength__doc__,
"Get the residential strength for a planet, given its longitude and bhavamadhya"
" longitudes in a 12 items sequence.\n\n"
"Args: int plon, seq bhavas\n"
"Return: float strength");

static PyObject * pyswh_residential_strength FUNCARGS_KEYWDS
{
    int i;
    double bh[12], ret, plon;
    PyObject *seq, *p;
    static char *kwlist[] = {"plon", "bhavas", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dO", kwlist, &plon, &seq))
        return NULL;
    if ((PySequence_Check(seq) != 1) || (PySequence_Length(seq) < 12)) {
        PyErr_SetString(pyswe_Error, "swisseph.contrib.residential_strength: invalid bhavas");
        return NULL;
    }
    for (i = 0; i < 12; ++i) { /* check sequence has 12 numbers */
        p = PySequence_GetItem(seq, i);
        if (PyFloat_CheckExact(p))
            bh[i] = PyFloat_AS_DOUBLE(p);
        else if (PyLong_CheckExact(p))
            bh[i] = PyLong_AsDouble(p);
#if PY_MAJOR_VERSION < 3
        else if (PyInt_CheckExact(p))
            bh[i] = PyInt_AS_LONG(p);
#endif
        else {
            PyErr_SetString(pyswe_Error, "swisseph.contrib.residential_strength: invalid bhavas type");
            return NULL;
        }
    }
    i = swh_residential_strength(plon, bh, &ret);
    if (i == -1) { /* should not happen... */
        PyErr_SetString(pyswe_Error, "swisseph.contrib.residential_strength: invalid error");
        return NULL;
    }
    return Py_BuildValue("d", ret);
}

/* swisseph.contrib.revjul */
PyDoc_STRVAR(pyswh_revjul__doc__,
"Reverse Julian day to date & time (UTC).\n\n"
"Args: double julday, int flag=GREG_CAL\n"
"Return: tuple of 6 int");

static PyObject * pyswh_revjul FUNCARGS_KEYWDS
{
    int dt[6], flag=SE_GREG_CAL;
    double jd;
    static char *kwlist[] = {"julday", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d|i", kwlist,
        &jd, &flag))
        return NULL;
    swh_revjul(jd, flag, dt);
    return Py_BuildValue("(iiiiii)", dt[0], dt[1], dt[2], dt[3], dt[4], dt[5]);
}

/* swisseph.contrib.saturn_4_stars */
PyDoc_STRVAR(pyswh_saturn_4_stars__doc__,
"Compute Halbronn's 'Saturn 4 Stars' index.\n\n"
"Args: float jd, int flag=FLG_SWIEPH+FLG_SPEED\n"
"Return: tuple of 6 float (Sat, Ald, Reg, Ant, Fom, and index value)");

static PyObject * pyswh_saturn_4_stars FUNCARGS_KEYWDS
{
    double jd, ret[6] = {0,0,0,0,0,0};
    int res, flag = SEFLG_SWIEPH | SEFLG_SPEED;
    char err[256];
    static char *kwlist[] = {"jd", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d|i", kwlist, &jd, &flag))
        return NULL;
    res = swh_saturn_4_stars(jd, flag, ret, err);
    if (res < 0) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(dddddd)", ret[0],ret[1],ret[2],ret[3],ret[4],ret[5]);
}

/* swisseph.contrib.signtostr */
PyDoc_STRVAR(pyswh_signtostr__doc__,
"Get a string representing the sign number given [0;11].\n\n"
"Args: int sign\n"
"Return: str");

static PyObject * pyswh_signtostr FUNCARGS_KEYWDS
{
    int res, sign;
    char str[12];
    static char *kwlist[] = {"sign", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i", kwlist, &sign))
        return NULL;
    res = swh_signtostr(sign, str);
    if (res < 0) {
        PyErr_SetString(pyswe_Error, "swisseph.contrib.signtostr: invalid sign number");
        return NULL;
    }
    return Py_BuildValue("s", str);
}

/* swisseph.contrib.t2i */
PyDoc_STRVAR(pyswh_t2i__doc__,
"Split a standardized time string 'HH:MM:SS' into integers.\n\n"
"Similar to function _dt2i, but just for time.\n"
"All non-digits in the given string are ignored and any of them can be"
" used as separator, including spaces.\n"
"Optionaly, minutes and seconds can be omitted, in that case will"
" return zeros.\n\n"
"Args: str t\n"
"Return: 3 int (hour, minutes, seconds)");

static PyObject * pyswh_t2i FUNCARGS_KEYWDS
{
    int x;
    char* t;
    int ret[3];
    static char* kwlist[] = {"t", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "s", kwlist, &t))
        return NULL;
    x = swh_t2i(t, ret);
    if (x) {
        PyErr_SetString(pyswe_Error, "swisseph.contrib.t2i: invalid string");
        return NULL;
    }
    return Py_BuildValue("iii",ret[0],ret[1],ret[2]);
}

/* swisseph.contrib.tatkalika_relation */
PyDoc_STRVAR(pyswh_tatkalika_relation__doc__,
"Get the tatkalika relation between two planets, given their rasi numbers.\n\n"
"Args: int r1, int r2\n"
"Return: int 1 (Mitra) or -1 (Satru)");

static PyObject * pyswh_tatkalika_relation FUNCARGS_KEYWDS
{
    int r1, r2;
    static char *kwlist[] = {"r1", "r2", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ii", kwlist, &r1, &r2))
        return NULL;
    return Py_BuildValue("i", swh_tatkalika_relation(r1, r2));
}

/* swisseph.contrib.tzabbr_find */
PyDoc_STRVAR(pyswh_tzabbr_find__doc__,
"Find details about a timezone given its abbreviated name.\n\n"
"If timezone is found, a list containing up to 3 tuples is returned.\n"
"Each tuple contains the name of the timezone, a short description, its"
" definition in the ISO 8601 standard, hours and minutes from UTC.\n\n"
"Usage example:\n\n"
"\t>>> swh.tzabbr_find('cet')\n"
"\t[('CET', 'Central European Time', 'UTC+01', 1, 0)]\n\n"
"Args: str tz\n"
"Return: list of (name, description, iso, hours, minutes)");

static PyObject * pyswh_tzabbr_find FUNCARGS_KEYWDS
{
    char* tz;
    struct swh_tzabbr* ret[4];
    struct swh_tzabbr** p = ret;
    static char* kwlist[] = {"tz", NULL};
    PyObject* lst;
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "s", kwlist, &tz))
        return NULL;
    if (!(lst = PyList_New(0)))
        return PyErr_NoMemory();
    if (swh_tzabbr_find(tz, ret))
        return lst;
    do {
        PyObject* tup = Py_BuildValue("(sssii)", (*p)->name, (*p)->desc,
                                      (*p)->iso, (*p)->hours, (*p)->minutes);
        if (!tup) {
            Py_DECREF(lst);
            return PyErr_NoMemory();
        }
        PyList_Append(lst, tup);
    } while (*++p);
    return lst;
}

/* swisseph.contrib.tzabbr_list */
PyDoc_STRVAR(pyswh_tzabbr_list__doc__,
"Provide a list of all timezone abbreviations.\n\n"
"Args: -\n"
"Return: list of (name, description, iso, hours, minutes)");

static PyObject * pyswh_tzabbr_list FUNCARGS_SELF
{
    size_t i = 0;
    struct swh_tzabbr* p = (struct swh_tzabbr*) swh_tzabbrlist;
    PyObject* lst = PyList_New(SWH_TZABBR_NUM);
    if (!lst)
        return PyErr_NoMemory();
    for (; i < SWH_TZABBR_NUM; ++p) {
        PyObject* tup = Py_BuildValue("(sssii)", p->name, p->desc, p->iso,
                                      p->hours, p->minutes);
        if (!tup) {
            Py_DECREF(lst);
            return PyErr_NoMemory();
        }
        PyList_SET_ITEM(lst, i++, tup);
    }
    return lst;
}

/* swisseph.contrib.years_diff */
PyDoc_STRVAR(pyswh_years_diff__doc__,
"Get number of 'astrological' years between two Julian days.\n\n"
"Args: float jd1, float jd2, int flags=FLG_SWIEPH|FLG_SPEED|FLG_NOGDEFL\n"
"Return: float");

static PyObject * pyswh_years_diff FUNCARGS_KEYWDS
{
    double jd1, jd2, years = 0;
    int flags = SEFLG_SWIEPH|SEFLG_SPEED|SEFLG_NOGDEFL, res;
    char err[256];
    static char *kwlist[] = {"jd1", "jd2", "flags", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dd|i", kwlist,
        &jd1, &jd2, &flags))
        return NULL;
    res = swh_years_diff(jd1, jd2, flags, &years, err);
    if (res) {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("d", years);
}

#endif /* PYSWE_USE_SWEPHELP */

/* Methods */
static struct PyMethodDef pyswe_methods[] = {
    {"azalt", (PyCFunction) pyswe_azalt,
        METH_VARARGS|METH_KEYWORDS, pyswe_azalt__doc__},
    {"azalt_rev", (PyCFunction) pyswe_azalt_rev,
        METH_VARARGS|METH_KEYWORDS, pyswe_azalt_rev__doc__},
    {"calc", (PyCFunction) pyswe_calc,
        METH_VARARGS|METH_KEYWORDS, pyswe_calc__doc__},
    {"calc_pctr", (PyCFunction) pyswe_calc_pctr,
        METH_VARARGS|METH_KEYWORDS, pyswe_calc_pctr__doc__},
    {"calc_ut", (PyCFunction) pyswe_calc_ut,
        METH_VARARGS|METH_KEYWORDS, pyswe_calc_ut__doc__},
    {"close", (PyCFunction) pyswe_close,
        METH_NOARGS, pyswe_close__doc__},
    {"cotrans", (PyCFunction) pyswe_cotrans,
        METH_VARARGS|METH_KEYWORDS, pyswe_cotrans__doc__},
    {"cotrans_sp", (PyCFunction) pyswe_cotrans_sp,
        METH_VARARGS|METH_KEYWORDS, pyswe_cotrans_sp__doc__},
    {"cs2degstr", (PyCFunction) pyswe_cs2degstr,
        METH_VARARGS|METH_KEYWORDS, pyswe_cs2degstr__doc__},
    {"cs2lonlatstr", (PyCFunction) pyswe_cs2lonlatstr,
        METH_VARARGS|METH_KEYWORDS, pyswe_cs2lonlatstr__doc__},
    {"cs2timestr", (PyCFunction) pyswe_cs2timestr,
        METH_VARARGS|METH_KEYWORDS, pyswe_cs2timestr__doc__},
    {"csnorm", (PyCFunction) pyswe_csnorm,
        METH_VARARGS|METH_KEYWORDS, pyswe_csnorm__doc__},
    {"csroundsec", (PyCFunction) pyswe_csroundsec,
        METH_VARARGS|METH_KEYWORDS, pyswe_csroundsec__doc__},
    {"d2l", (PyCFunction) pyswe_d2l,
        METH_VARARGS|METH_KEYWORDS, pyswe_d2l__doc__},
    {"date_conversion", (PyCFunction) pyswe_date_conversion,
        METH_VARARGS|METH_KEYWORDS, pyswe_date_conversion__doc__},
    {"day_of_week", (PyCFunction) pyswe_day_of_week,
        METH_VARARGS|METH_KEYWORDS, pyswe_day_of_week__doc__},
    {"deg_midp", (PyCFunction) pyswe_deg_midp,
        METH_VARARGS|METH_KEYWORDS, pyswe_deg_midp__doc__},
    {"degnorm", (PyCFunction) pyswe_degnorm,
        METH_VARARGS|METH_KEYWORDS, pyswe_degnorm__doc__},
    {"deltat", (PyCFunction) pyswe_deltat,
        METH_VARARGS|METH_KEYWORDS, pyswe_deltat__doc__},
    {"difcs2n", (PyCFunction) pyswe_difcs2n,
        METH_VARARGS|METH_KEYWORDS, pyswe_difcs2n__doc__},
    {"difcsn", (PyCFunction) pyswe_difcsn,
        METH_VARARGS|METH_KEYWORDS, pyswe_difcsn__doc__},
    {"difdeg2n", (PyCFunction) pyswe_difdeg2n,
        METH_VARARGS|METH_KEYWORDS, pyswe_difdeg2n__doc__},
    {"difdegn", (PyCFunction) pyswe_difdegn,
        METH_VARARGS|METH_KEYWORDS, pyswe_difdegn__doc__},
    {"difrad2n", (PyCFunction) pyswe_difrad2n,
        METH_VARARGS|METH_KEYWORDS, pyswe_difrad2n__doc__},
    {"fixstar", (PyCFunction) pyswe_fixstar,
        METH_VARARGS|METH_KEYWORDS, pyswe_fixstar__doc__},
    {"fixstar2", (PyCFunction) pyswe_fixstar2,
        METH_VARARGS|METH_KEYWORDS, pyswe_fixstar2__doc__},
    {"fixstar2_mag", (PyCFunction) pyswe_fixstar2_mag,
        METH_VARARGS|METH_KEYWORDS, pyswe_fixstar2_mag__doc__},
    {"fixstar2_ut", (PyCFunction) pyswe_fixstar2_ut,
        METH_VARARGS|METH_KEYWORDS, pyswe_fixstar2_ut__doc__},
    {"fixstar_mag", (PyCFunction) pyswe_fixstar_mag,
        METH_VARARGS|METH_KEYWORDS, pyswe_fixstar_mag__doc__},
    {"fixstar_ut", (PyCFunction) pyswe_fixstar_ut,
        METH_VARARGS|METH_KEYWORDS, pyswe_fixstar_ut__doc__},
    {"gauquelin_sector", (PyCFunction) pyswe_gauquelin_sector,
        METH_VARARGS|METH_KEYWORDS, pyswe_gauquelin_sector__doc__},
    {"get_ayanamsa", (PyCFunction) pyswe_get_ayanamsa,
        METH_VARARGS|METH_KEYWORDS, pyswe_get_ayanamsa__doc__},
    {"get_ayanamsa_name", (PyCFunction) pyswe_get_ayanamsa_name,
        METH_VARARGS|METH_KEYWORDS, pyswe_get_ayanamsa_name__doc__},
    {"get_ayanamsa_ut", (PyCFunction) pyswe_get_ayanamsa_ut,
        METH_VARARGS|METH_KEYWORDS, pyswe_get_ayanamsa_ut__doc__},
    {"get_current_file_data", (PyCFunction) pyswe_get_current_file_data,
        METH_VARARGS|METH_KEYWORDS, pyswe_get_current_file_data__doc__},
    {"get_library_path", (PyCFunction) pyswe_get_library_path,
        METH_NOARGS, pyswe_get_library_path__doc__},
    {"get_orbital_elements", (PyCFunction) pyswe_get_orbital_elements,
        METH_VARARGS|METH_KEYWORDS, pyswe_get_orbital_elements__doc__},
    {"get_planet_name", (PyCFunction) pyswe_get_planet_name,
        METH_VARARGS|METH_KEYWORDS, pyswe_get_planet_name__doc__},
    {"get_tid_acc", (PyCFunction) pyswe_get_tid_acc,
        METH_NOARGS, pyswe_get_tid_acc__doc__},
    {"heliacal_pheno_ut", (PyCFunction) pyswe_heliacal_pheno_ut,
        METH_VARARGS|METH_KEYWORDS, pyswe_heliacal_pheno_ut__doc__},
    {"heliacal_ut", (PyCFunction) pyswe_heliacal_ut,
        METH_VARARGS|METH_KEYWORDS, pyswe_heliacal_ut__doc__},
    {"house_name", (PyCFunction) pyswe_house_name,
        METH_VARARGS|METH_KEYWORDS, pyswe_house_name__doc__},
    {"house_pos", (PyCFunction) pyswe_house_pos,
        METH_VARARGS|METH_KEYWORDS, pyswe_house_pos__doc__},
    {"houses", (PyCFunction) pyswe_houses,
        METH_VARARGS|METH_KEYWORDS, pyswe_houses__doc__},
    {"houses_armc", (PyCFunction) pyswe_houses_armc,
        METH_VARARGS|METH_KEYWORDS, pyswe_houses_armc__doc__},
    {"houses_armc_ex2", (PyCFunction) pyswe_houses_armc_ex2,
        METH_VARARGS|METH_KEYWORDS, pyswe_houses_armc_ex2__doc__},
    {"houses_ex", (PyCFunction) pyswe_houses_ex,
        METH_VARARGS|METH_KEYWORDS, pyswe_houses_ex__doc__},
    {"houses_ex2", (PyCFunction) pyswe_houses_ex2,
        METH_VARARGS|METH_KEYWORDS, pyswe_houses_ex2__doc__},
    {"jdet_to_utc", (PyCFunction) pyswe_jdet_to_utc,
        METH_VARARGS|METH_KEYWORDS, pyswe_jdet_to_utc__doc__},
    {"jdut1_to_utc", (PyCFunction) pyswe_jdut1_to_utc,
        METH_VARARGS|METH_KEYWORDS, pyswe_jdut1_to_utc__doc__},
    {"julday", (PyCFunction) pyswe_julday,
        METH_VARARGS|METH_KEYWORDS, pyswe_julday__doc__},
    {"lat_to_lmt", (PyCFunction) pyswe_lat_to_lmt,
        METH_VARARGS|METH_KEYWORDS, pyswe_lat_to_lmt__doc__},
    {"lmt_to_lat", (PyCFunction) pyswe_lmt_to_lat,
        METH_VARARGS|METH_KEYWORDS, pyswe_lmt_to_lat__doc__},
    {"lun_eclipse_how", (PyCFunction) pyswe_lun_eclipse_how,
        METH_VARARGS|METH_KEYWORDS, pyswe_lun_eclipse_how__doc__},
    {"lun_eclipse_when", (PyCFunction) pyswe_lun_eclipse_when,
        METH_VARARGS|METH_KEYWORDS, pyswe_lun_eclipse_when__doc__},
    {"lun_eclipse_when_loc", (PyCFunction) pyswe_lun_eclipse_when_loc,
        METH_VARARGS|METH_KEYWORDS, pyswe_lun_eclipse_when_loc__doc__},
    {"lun_occult_when_glob", (PyCFunction) pyswe_lun_occult_when_glob,
        METH_VARARGS|METH_KEYWORDS, pyswe_lun_occult_when_glob__doc__},
    {"lun_occult_when_loc", (PyCFunction) pyswe_lun_occult_when_loc,
        METH_VARARGS|METH_KEYWORDS, pyswe_lun_occult_when_loc__doc__},
    {"lun_occult_where", (PyCFunction) pyswe_lun_occult_where,
        METH_VARARGS|METH_KEYWORDS, pyswe_lun_occult_where__doc__},
    {"nod_aps", (PyCFunction) pyswe_nod_aps,
        METH_VARARGS|METH_KEYWORDS, pyswe_nod_aps__doc__},
    {"nod_aps_ut", (PyCFunction) pyswe_nod_aps_ut,
        METH_VARARGS|METH_KEYWORDS, pyswe_nod_aps_ut__doc__},
    {"orbit_max_min_true_distance", (PyCFunction) pyswe_orbit_max_min_true_distance,
        METH_VARARGS|METH_KEYWORDS, pyswe_orbit_max_min_true_distance__doc__},
    {"pheno", (PyCFunction) pyswe_pheno,
        METH_VARARGS|METH_KEYWORDS, pyswe_pheno__doc__},
    {"pheno_ut", (PyCFunction) pyswe_pheno_ut,
        METH_VARARGS|METH_KEYWORDS, pyswe_pheno_ut__doc__},
    {"rad_midp", (PyCFunction) pyswe_rad_midp,
        METH_VARARGS|METH_KEYWORDS, pyswe_rad_midp__doc__},
    {"radnorm", (PyCFunction) pyswe_radnorm,
        METH_VARARGS|METH_KEYWORDS, pyswe_radnorm__doc__},
    {"refrac", (PyCFunction) pyswe_refrac,
        METH_VARARGS|METH_KEYWORDS, pyswe_refrac__doc__},
    {"refrac_extended", (PyCFunction) pyswe_refrac_extended,
        METH_VARARGS|METH_KEYWORDS, pyswe_refrac_extended__doc__},
    {"revjul", (PyCFunction) pyswe_revjul,
        METH_VARARGS|METH_KEYWORDS, pyswe_revjul__doc__},
    {"rise_trans", (PyCFunction) pyswe_rise_trans,
        METH_VARARGS|METH_KEYWORDS, pyswe_rise_trans__doc__},
    {"set_ephe_path", (PyCFunction) pyswe_set_ephe_path,
        METH_VARARGS|METH_KEYWORDS, pyswe_set_ephe_path__doc__},
    {"set_jpl_file", (PyCFunction) pyswe_set_jpl_file,
        METH_VARARGS|METH_KEYWORDS, pyswe_set_jpl_file__doc__},
    {"set_lapse_rate", (PyCFunction) pyswe_set_lapse_rate,
        METH_VARARGS|METH_KEYWORDS, pyswe_set_lapse_rate__doc__},
    {"set_sid_mode", (PyCFunction) pyswe_set_sid_mode,
        METH_VARARGS|METH_KEYWORDS, pyswe_set_sid_mode__doc__},
    {"set_tid_acc", (PyCFunction) pyswe_set_tid_acc,
        METH_VARARGS|METH_KEYWORDS, pyswe_set_tid_acc__doc__},
    {"set_topo", (PyCFunction) pyswe_set_topo,
        METH_VARARGS|METH_KEYWORDS, pyswe_set_topo__doc__},
    {"sidtime", (PyCFunction) pyswe_sidtime,
        METH_VARARGS|METH_KEYWORDS, pyswe_sidtime__doc__},
    {"sidtime0", (PyCFunction) pyswe_sidtime0,
        METH_VARARGS|METH_KEYWORDS, pyswe_sidtime0__doc__},
    {"sol_eclipse_how", (PyCFunction) pyswe_sol_eclipse_how,
        METH_VARARGS|METH_KEYWORDS, pyswe_sol_eclipse_how__doc__},
    {"sol_eclipse_when_glob", (PyCFunction) pyswe_sol_eclipse_when_glob,
        METH_VARARGS|METH_KEYWORDS, pyswe_sol_eclipse_when_glob__doc__},
    {"sol_eclipse_when_loc", (PyCFunction) pyswe_sol_eclipse_when_loc,
        METH_VARARGS|METH_KEYWORDS, pyswe_sol_eclipse_when_loc__doc__},
    {"sol_eclipse_where", (PyCFunction) pyswe_sol_eclipse_where,
        METH_VARARGS|METH_KEYWORDS, pyswe_sol_eclipse_where__doc__},
    {"split_deg", (PyCFunction) pyswe_split_deg,
        METH_VARARGS|METH_KEYWORDS, pyswe_split_deg__doc__},
    {"time_equ", (PyCFunction) pyswe_time_equ,
        METH_VARARGS|METH_KEYWORDS, pyswe_time_equ__doc__},
    {"utc_time_zone", (PyCFunction) pyswe_utc_time_zone,
        METH_VARARGS|METH_KEYWORDS, pyswe_utc_time_zone__doc__},
    {"utc_to_jd", (PyCFunction) pyswe_utc_to_jd,
        METH_VARARGS|METH_KEYWORDS, pyswe_utc_to_jd__doc__},
    {"vis_limit_mag", (PyCFunction) pyswe_vis_limit_mag,
        METH_VARARGS|METH_KEYWORDS, pyswe_vis_limit_mag__doc__},
    {NULL, (PyCFunction) NULL, 0, NULL}
};

#if PYSWE_USE_SWEPHELP
static struct PyMethodDef pyswh_methods[] = {
    /* pyswisseph/swephelp functions. */
    {"atlas_close", (PyCFunction) pyswh_atlas_close,
        METH_NOARGS, pyswh_atlas_close__doc__},
    {"atlas_connect", (PyCFunction) pyswh_atlas_connect,
        METH_VARARGS|METH_KEYWORDS, pyswh_atlas_connect__doc__},
    {"atlas_countries_list", (PyCFunction) pyswh_atlas_countries_list,
        METH_NOARGS, pyswh_atlas_countries_list__doc__},
    {"atlas_search", (PyCFunction) pyswh_atlas_search,
        METH_VARARGS|METH_KEYWORDS, pyswh_atlas_search__doc__},
    {"antiscion", (PyCFunction) pyswh_antiscion,
        METH_VARARGS|METH_KEYWORDS, pyswh_antiscion__doc__},
    {"calc_ut", (PyCFunction) pyswh_calc_ut,
        METH_VARARGS|METH_KEYWORDS, pyswh_calc_ut__doc__},
    {"db_close", (PyCFunction) pyswh_db_close,
        METH_NOARGS, pyswh_db_close__doc__},
    {"db_connect", (PyCFunction) pyswh_db_connect,
        METH_VARARGS|METH_KEYWORDS, pyswh_db_connect__doc__},
    {"degsplit", (PyCFunction) pyswh_degsplit,
        METH_VARARGS|METH_KEYWORDS, pyswh_degsplit__doc__},
    {"dt2i", (PyCFunction) pyswh_dt2i,
        METH_VARARGS|METH_KEYWORDS, pyswh_dt2i__doc__},
    {"geoc2d", (PyCFunction) pyswh_geoc2d,
        METH_VARARGS|METH_KEYWORDS, pyswh_geoc2d__doc__},
    {"geolat2c", (PyCFunction) pyswh_geolat2c,
        METH_VARARGS|METH_KEYWORDS, pyswh_geolat2c__doc__},
    {"geolon2c", (PyCFunction) pyswh_geolon2c,
        METH_VARARGS|METH_KEYWORDS, pyswh_geolon2c__doc__},
    {"get_nakshatra_name", (PyCFunction) pyswh_get_nakshatra_name,
        METH_VARARGS|METH_KEYWORDS, pyswh_get_nakshatra_name__doc__},
    {"house_system_name", (PyCFunction) pyswh_house_system_name,
        METH_VARARGS|METH_KEYWORDS, pyswh_house_system_name__doc__},
    {"jd2isostr", (PyCFunction) pyswh_jd2isostr,
        METH_VARARGS|METH_KEYWORDS, pyswh_jd2isostr__doc__},
    {"jdnow", (PyCFunction) pyswh_jdnow,
        METH_NOARGS, pyswh_jdnow__doc__},
    {"jduration", (PyCFunction) pyswh_jduration,
        METH_VARARGS|METH_KEYWORDS, pyswh_jduration__doc__},
    {"julday", (PyCFunction) pyswh_julday,
        METH_VARARGS|METH_KEYWORDS, pyswh_julday__doc__},
    {"long2nakshatra", (PyCFunction) pyswh_long2nakshatra,
        METH_VARARGS|METH_KEYWORDS, pyswh_long2nakshatra__doc__},
    {"long2navamsa", (PyCFunction) pyswh_long2navamsa,
        METH_VARARGS|METH_KEYWORDS, pyswh_long2navamsa__doc__},
    {"long2rasi", (PyCFunction) pyswh_long2rasi,
        METH_VARARGS|METH_KEYWORDS, pyswh_long2rasi__doc__},
    {"lord", (PyCFunction) pyswh_lord,
        METH_VARARGS|METH_KEYWORDS, pyswh_lord__doc__},
    {"match_aspect", (PyCFunction) pyswh_match_aspect,
        METH_VARARGS|METH_KEYWORDS, pyswh_match_aspect__doc__},
    {"match_aspect2", (PyCFunction) pyswh_match_aspect2,
        METH_VARARGS|METH_KEYWORDS, pyswh_match_aspect2__doc__},
    {"match_aspect3", (PyCFunction) pyswh_match_aspect3,
        METH_VARARGS|METH_KEYWORDS, pyswh_match_aspect3__doc__},
    {"match_aspect4", (PyCFunction) pyswh_match_aspect4,
        METH_VARARGS|METH_KEYWORDS, pyswh_match_aspect4__doc__},
    {"naisargika_relation", (PyCFunction) pyswh_naisargika_relation,
        METH_VARARGS|METH_KEYWORDS, pyswh_naisargika_relation__doc__},
    {"next_aspect", (PyCFunction) pyswh_next_aspect,
        METH_VARARGS|METH_KEYWORDS, pyswh_next_aspect__doc__},
    {"next_aspect2", (PyCFunction) pyswh_next_aspect2,
        METH_VARARGS|METH_KEYWORDS, pyswh_next_aspect2__doc__},
    {"next_aspect_cusp", (PyCFunction) pyswh_next_aspect_cusp,
        METH_VARARGS|METH_KEYWORDS, pyswh_next_aspect_cusp__doc__},
    {"next_aspect_cusp2", (PyCFunction) pyswh_next_aspect_cusp2,
        METH_VARARGS|METH_KEYWORDS, pyswh_next_aspect_cusp2__doc__},
    {"next_aspect_with", (PyCFunction) pyswh_next_aspect_with,
        METH_VARARGS|METH_KEYWORDS, pyswh_next_aspect_with__doc__},
    {"next_aspect_with2", (PyCFunction) pyswh_next_aspect_with2,
        METH_VARARGS|METH_KEYWORDS, pyswh_next_aspect_with2__doc__},
    {"next_retro", (PyCFunction) pyswh_next_retro,
        METH_VARARGS|METH_KEYWORDS, pyswh_next_retro__doc__},
    {"ochchabala", (PyCFunction) pyswh_ochchabala,
        METH_VARARGS|METH_KEYWORDS, pyswh_ochchabala__doc__},
    {"raman_houses", (PyCFunction) pyswh_raman_houses,
        METH_VARARGS|METH_KEYWORDS, pyswh_raman_houses__doc__},
    {"rasi_dif", (PyCFunction) pyswh_rasi_dif,
        METH_VARARGS|METH_KEYWORDS, pyswh_rasi_dif__doc__},
    {"rasi_dif2", (PyCFunction) pyswh_rasi_dif2,
        METH_VARARGS|METH_KEYWORDS, pyswh_rasi_dif2__doc__},
    {"rasinorm", (PyCFunction) pyswh_rasinorm,
        METH_VARARGS|METH_KEYWORDS, pyswh_rasinorm__doc__},
    {"residential_strength", (PyCFunction) pyswh_residential_strength,
        METH_VARARGS|METH_KEYWORDS, pyswh_residential_strength__doc__},
    {"revjul", (PyCFunction) pyswh_revjul,
        METH_VARARGS|METH_KEYWORDS, pyswh_revjul__doc__},
    {"saturn_4_stars", (PyCFunction) pyswh_saturn_4_stars,
        METH_VARARGS|METH_KEYWORDS, pyswh_saturn_4_stars__doc__},
    {"signtostr", (PyCFunction) pyswh_signtostr,
        METH_VARARGS|METH_KEYWORDS, pyswh_signtostr__doc__},
    {"t2i", (PyCFunction) pyswh_t2i,
        METH_VARARGS|METH_KEYWORDS, pyswh_t2i__doc__},
    {"tatkalika_relation", (PyCFunction) pyswh_tatkalika_relation,
        METH_VARARGS|METH_KEYWORDS, pyswh_tatkalika_relation__doc__},
    {"tzabbr_find", (PyCFunction) pyswh_tzabbr_find,
        METH_VARARGS|METH_KEYWORDS, pyswh_tzabbr_find__doc__},
    {"tzabbr_list", (PyCFunction) pyswh_tzabbr_list,
        METH_NOARGS, pyswh_tzabbr_list__doc__},
    {"years_diff", (PyCFunction) pyswh_years_diff,
        METH_VARARGS|METH_KEYWORDS, pyswh_years_diff__doc__},
    {NULL, (PyCFunction) NULL, 0, NULL}
};

PyDoc_STRVAR(pyswh_module_documentation,
"Contrib module (swephelp).\n"
"Usage example:\n\n"
"\tfrom swisseph import contrib as swh\n"
"\t...");

#if PY_MAJOR_VERSION >= 3
struct PyModuleDef pyswh_module =
{
    PyModuleDef_HEAD_INIT,
    "swisseph.contrib", /* module name */
    pyswh_module_documentation, /* module docstring */
    -1, /* size of per-interpreter state of the module,
        or -1 if the module keeps state in global variables. */
    pyswh_methods
};
#endif
#endif /* PYSWE_USE_SWEPHELP */

#if PYSWE_AUTO_SET_EPHE_PATH
PyDoc_STRVAR(pyswe_module_documentation,
"Python extension to AstroDienst Swiss Ephemeris library.\n\n"
"Extended documentation can be found at AstroDienst website.\n"
"Please refer to: https://www.astro.com/swisseph/swephprg.htm\n\n"
"Import of this extension module does automagicaly set the ephemeris path"
" to \"" PYSWE_DEFAULT_EPHE_PATH "\".\n\n"
"    Pyswisseph homepage: https://astrorigin.com/pyswisseph/\n"
"    AstroDienst: https://www.astro.com/swisseph/\n"
"    PyPI: https://pypi.org/project/pyswisseph/");
#else /* no auto set ephe path */
PyDoc_STRVAR(pyswe_module_documentation,
"Python extension to AstroDienst Swiss Ephemeris library.\n\n"
"Extended documentation can be found at AstroDienst website.\n"
"Please refer to: https://www.astro.com/swisseph/swephprg.htm\n\n"
"    Pyswisseph homepage: https://astrorigin.com/pyswisseph/\n"
"    AstroDienst: https://www.astro.com/swisseph/\n"
"    PyPI: https://pypi.org/project/pyswisseph/");
#endif

#if PY_MAJOR_VERSION >= 3
struct PyModuleDef pyswe_module =
{
    PyModuleDef_HEAD_INIT,
    "swisseph", /* module name */
    pyswe_module_documentation, /* module docstring */
    -1, /* size of per-interpreter state of the module,
        or -1 if the module keeps state in global variables. */
    pyswe_methods
};

PyMODINIT_FUNC PyInit_swisseph(void)
#elif PY_MAJOR_VERSION < 3
PyMODINIT_FUNC initswisseph(void)
#endif
{
    PyObject *m;
#if PYSWE_USE_SWEPHELP
    PyObject *m2;
#endif
    char buf[256]; /* for swe_version */

    memset(buf, 0, sizeof(char) * 256);

#if PY_MAJOR_VERSION >= 3
    m = PyModule_Create(&pyswe_module);
    if (m == NULL)
        Py_FatalError("Can't create module swisseph!");
#elif PY_MAJOR_VERSION < 3
    m = Py_InitModule4("swisseph", pyswe_methods,
        pyswe_module_documentation,
        (PyObject*) NULL, PYTHON_API_VERSION);
#endif

    pyswe_Error = PyErr_NewException("swisseph.Error", NULL, NULL);
    Py_INCREF(pyswe_Error);
    PyModule_AddObject(m, "Error", pyswe_Error);

    /* Constants */

    PyModule_AddFloatConstant(m, "AUNIT_TO_KM", SE_AUNIT_TO_KM);
    PyModule_AddFloatConstant(m, "AUNIT_TO_LIGHTYEAR", SE_AUNIT_TO_LIGHTYEAR);
    PyModule_AddFloatConstant(m, "AUNIT_TO_PARSEC", SE_AUNIT_TO_PARSEC);

    PyModule_AddIntConstant(m, "JUL_CAL", SE_JUL_CAL);
    PyModule_AddIntConstant(m, "GREG_CAL", SE_GREG_CAL);

    PyModule_AddIntConstant(m, "ECL_NUT", SE_ECL_NUT);
    PyModule_AddIntConstant(m, "SUN", SE_SUN);
    PyModule_AddIntConstant(m, "MOON", SE_MOON);
    PyModule_AddIntConstant(m, "MERCURY", SE_MERCURY);
    PyModule_AddIntConstant(m, "VENUS", SE_VENUS);
    PyModule_AddIntConstant(m, "MARS", SE_MARS);
    PyModule_AddIntConstant(m, "JUPITER", SE_JUPITER);
    PyModule_AddIntConstant(m, "SATURN", SE_SATURN);
    PyModule_AddIntConstant(m, "URANUS", SE_URANUS);
    PyModule_AddIntConstant(m, "NEPTUNE", SE_NEPTUNE);
    PyModule_AddIntConstant(m, "PLUTO", SE_PLUTO);
    PyModule_AddIntConstant(m, "MEAN_NODE", SE_MEAN_NODE);
    PyModule_AddIntConstant(m, "TRUE_NODE", SE_TRUE_NODE);
    PyModule_AddIntConstant(m, "MEAN_APOG", SE_MEAN_APOG);
    PyModule_AddIntConstant(m, "OSCU_APOG", SE_OSCU_APOG);
    PyModule_AddIntConstant(m, "EARTH", SE_EARTH);
    PyModule_AddIntConstant(m, "CHIRON", SE_CHIRON);
    PyModule_AddIntConstant(m, "PHOLUS", SE_PHOLUS);
    PyModule_AddIntConstant(m, "CERES", SE_CERES);
    PyModule_AddIntConstant(m, "PALLAS", SE_PALLAS);
    PyModule_AddIntConstant(m, "JUNO", SE_JUNO);
    PyModule_AddIntConstant(m, "VESTA", SE_VESTA);
    PyModule_AddIntConstant(m, "INTP_APOG", SE_INTP_APOG);
    PyModule_AddIntConstant(m, "INTP_PERG", SE_INTP_PERG);

    PyModule_AddIntConstant(m, "NPLANETS", SE_NPLANETS);

    PyModule_AddIntConstant(m, "PLMOON_OFFSET", SE_PLMOON_OFFSET);
    PyModule_AddIntConstant(m, "AST_OFFSET", SE_AST_OFFSET);
    PyModule_AddIntConstant(m, "VARUNA", SE_VARUNA);
    PyModule_AddIntConstant(m, "FICT_OFFSET", SE_FICT_OFFSET);
    PyModule_AddIntConstant(m, "FICT_OFFSET_1", SE_FICT_OFFSET_1);
    PyModule_AddIntConstant(m, "FICT_MAX", SE_FICT_MAX);
    PyModule_AddIntConstant(m, "NFICT_ELEM", SE_NFICT_ELEM);
    PyModule_AddIntConstant(m, "COMET_OFFSET", SE_COMET_OFFSET);
    PyModule_AddIntConstant(m, "NALL_NAT_POINTS", SE_NALL_NAT_POINTS);

    PyModule_AddIntConstant(m, "CUPIDO", SE_CUPIDO);
    PyModule_AddIntConstant(m, "HADES", SE_HADES);
    PyModule_AddIntConstant(m, "ZEUS", SE_ZEUS);
    PyModule_AddIntConstant(m, "KRONOS", SE_KRONOS);
    PyModule_AddIntConstant(m, "APOLLON", SE_APOLLON);
    PyModule_AddIntConstant(m, "ADMETOS", SE_ADMETOS);
    PyModule_AddIntConstant(m, "VULKANUS", SE_VULKANUS);
    PyModule_AddIntConstant(m, "POSEIDON", SE_POSEIDON);

    PyModule_AddIntConstant(m, "ISIS", SE_ISIS);
    PyModule_AddIntConstant(m, "NIBIRU", SE_NIBIRU);
    PyModule_AddIntConstant(m, "HARRINGTON", SE_HARRINGTON);
    PyModule_AddIntConstant(m, "NEPTUNE_LEVERRIER", SE_NEPTUNE_LEVERRIER);
    PyModule_AddIntConstant(m, "NEPTUNE_ADAMS", SE_NEPTUNE_ADAMS);
    PyModule_AddIntConstant(m, "PLUTO_LOWELL", SE_PLUTO_LOWELL);
    PyModule_AddIntConstant(m, "PLUTO_PICKERING", SE_PLUTO_PICKERING);
    PyModule_AddIntConstant(m, "VULCAN", SE_VULCAN);
    PyModule_AddIntConstant(m, "WHITE_MOON", SE_WHITE_MOON);
    PyModule_AddIntConstant(m, "PROSERPINA", SE_PROSERPINA);
    PyModule_AddIntConstant(m, "WALDEMATH", SE_WALDEMATH);

    PyModule_AddIntConstant(m, "FIXSTAR", SE_FIXSTAR);

    PyModule_AddIntConstant(m, "ASC", SE_ASC);
    PyModule_AddIntConstant(m, "MC", SE_MC);
    PyModule_AddIntConstant(m, "ARMC", SE_ARMC);
    PyModule_AddIntConstant(m, "VERTEX", SE_VERTEX);
    PyModule_AddIntConstant(m, "EQUASC", SE_EQUASC);
    PyModule_AddIntConstant(m, "COASC1", SE_COASC1);
    PyModule_AddIntConstant(m, "COASC2", SE_COASC2);
    PyModule_AddIntConstant(m, "POLASC", SE_POLASC);
    PyModule_AddIntConstant(m, "NASCMC", SE_NASCMC);

    PyModule_AddIntConstant(m, "FLG_JPLEPH", SEFLG_JPLEPH);
    PyModule_AddIntConstant(m, "FLG_SWIEPH", SEFLG_SWIEPH);
    PyModule_AddIntConstant(m, "FLG_MOSEPH", SEFLG_MOSEPH);

    PyModule_AddIntConstant(m, "FLG_HELCTR", SEFLG_HELCTR);
    PyModule_AddIntConstant(m, "FLG_TRUEPOS", SEFLG_TRUEPOS);
    PyModule_AddIntConstant(m, "FLG_J2000", SEFLG_J2000);
    PyModule_AddIntConstant(m, "FLG_NONUT", SEFLG_NONUT);
    PyModule_AddIntConstant(m, "FLG_SPEED3", SEFLG_SPEED3);
    PyModule_AddIntConstant(m, "FLG_SPEED", SEFLG_SPEED);
    PyModule_AddIntConstant(m, "FLG_NOGDEFL", SEFLG_NOGDEFL);
    PyModule_AddIntConstant(m, "FLG_NOABERR", SEFLG_NOABERR);
    PyModule_AddIntConstant(m, "FLG_ASTROMETRIC", SEFLG_ASTROMETRIC);
    PyModule_AddIntConstant(m, "FLG_EQUATORIAL", SEFLG_EQUATORIAL);
    PyModule_AddIntConstant(m, "FLG_XYZ", SEFLG_XYZ);
    PyModule_AddIntConstant(m, "FLG_RADIANS", SEFLG_RADIANS);
    PyModule_AddIntConstant(m, "FLG_BARYCTR", SEFLG_BARYCTR);
    PyModule_AddIntConstant(m, "FLG_TOPOCTR", SEFLG_TOPOCTR);
    PyModule_AddIntConstant(m, "FLG_ORBEL_AA", SEFLG_ORBEL_AA);
    PyModule_AddIntConstant(m, "FLG_TROPICAL", SEFLG_TROPICAL);
    PyModule_AddIntConstant(m, "FLG_SIDEREAL", SEFLG_SIDEREAL);
    PyModule_AddIntConstant(m, "FLG_ICRS", SEFLG_ICRS);
    PyModule_AddIntConstant(m, "FLG_DPSIDEPS_1980", SEFLG_DPSIDEPS_1980);
    PyModule_AddIntConstant(m, "FLG_JPLHOR", SEFLG_JPLHOR);
    PyModule_AddIntConstant(m, "FLG_JPLHOR_APPROX", SEFLG_JPLHOR_APPROX);
    PyModule_AddIntConstant(m, "FLG_CENTER_BODY", SEFLG_CENTER_BODY);
    PyModule_AddIntConstant(m, "FLG_TEST_PLMOON", SEFLG_TEST_PLMOON);

    PyModule_AddIntConstant(m, "SIDBITS", SE_SIDBITS);
    PyModule_AddIntConstant(m, "SIDBIT_ECL_T0", SE_SIDBIT_ECL_T0);
    PyModule_AddIntConstant(m, "SIDBIT_SSY_PLANE", SE_SIDBIT_SSY_PLANE);
    PyModule_AddIntConstant(m, "SIDBIT_USER_UT", SE_SIDBIT_USER_UT);
    PyModule_AddIntConstant(m, "SIDBIT_ECL_DATE", SE_SIDBIT_ECL_DATE);
    PyModule_AddIntConstant(m, "SIDBIT_NO_PREC_OFFSET", SE_SIDBIT_NO_PREC_OFFSET);
    PyModule_AddIntConstant(m, "SIDBIT_PREC_ORIG", SE_SIDBIT_PREC_ORIG);

    PyModule_AddIntConstant(m, "SIDM_FAGAN_BRADLEY", SE_SIDM_FAGAN_BRADLEY);
    PyModule_AddIntConstant(m, "SIDM_LAHIRI", SE_SIDM_LAHIRI);
    PyModule_AddIntConstant(m, "SIDM_DELUCE", SE_SIDM_DELUCE);
    PyModule_AddIntConstant(m, "SIDM_RAMAN", SE_SIDM_RAMAN);
    PyModule_AddIntConstant(m, "SIDM_USHASHASHI", SE_SIDM_USHASHASHI);
    PyModule_AddIntConstant(m, "SIDM_KRISHNAMURTI", SE_SIDM_KRISHNAMURTI);
    PyModule_AddIntConstant(m, "SIDM_DJWHAL_KHUL", SE_SIDM_DJWHAL_KHUL);
    PyModule_AddIntConstant(m, "SIDM_YUKTESHWAR", SE_SIDM_YUKTESHWAR);
    PyModule_AddIntConstant(m, "SIDM_JN_BHASIN", SE_SIDM_JN_BHASIN);
    PyModule_AddIntConstant(m, "SIDM_BABYL_KUGLER1", SE_SIDM_BABYL_KUGLER1);
    PyModule_AddIntConstant(m, "SIDM_BABYL_KUGLER2", SE_SIDM_BABYL_KUGLER2);
    PyModule_AddIntConstant(m, "SIDM_BABYL_KUGLER3", SE_SIDM_BABYL_KUGLER3);
    PyModule_AddIntConstant(m, "SIDM_BABYL_HUBER", SE_SIDM_BABYL_HUBER);
    PyModule_AddIntConstant(m, "SIDM_BABYL_ETPSC", SE_SIDM_BABYL_ETPSC);
    PyModule_AddIntConstant(m, "SIDM_ALDEBARAN_15TAU", SE_SIDM_ALDEBARAN_15TAU);
    PyModule_AddIntConstant(m, "SIDM_HIPPARCHOS", SE_SIDM_HIPPARCHOS);
    PyModule_AddIntConstant(m, "SIDM_SASSANIAN", SE_SIDM_SASSANIAN);
    PyModule_AddIntConstant(m, "SIDM_GALCENT_0SAG", SE_SIDM_GALCENT_0SAG);
    PyModule_AddIntConstant(m, "SIDM_J2000", SE_SIDM_J2000);
    PyModule_AddIntConstant(m, "SIDM_J1900", SE_SIDM_J1900);
    PyModule_AddIntConstant(m, "SIDM_B1950", SE_SIDM_B1950);
    PyModule_AddIntConstant(m, "SIDM_SURYASIDDHANTA", SE_SIDM_SURYASIDDHANTA);
    PyModule_AddIntConstant(m, "SIDM_SURYASIDDHANTA_MSUN", SE_SIDM_SURYASIDDHANTA_MSUN);
    PyModule_AddIntConstant(m, "SIDM_ARYABHATA", SE_SIDM_ARYABHATA);
    PyModule_AddIntConstant(m, "SIDM_ARYABHATA_MSUN", SE_SIDM_ARYABHATA_MSUN);
    PyModule_AddIntConstant(m, "SIDM_SS_REVATI", SE_SIDM_SS_REVATI);
    PyModule_AddIntConstant(m, "SIDM_SS_CITRA", SE_SIDM_SS_CITRA);
    PyModule_AddIntConstant(m, "SIDM_TRUE_CITRA", SE_SIDM_TRUE_CITRA);
    PyModule_AddIntConstant(m, "SIDM_TRUE_REVATI", SE_SIDM_TRUE_REVATI);
    PyModule_AddIntConstant(m, "SIDM_TRUE_PUSHYA", SE_SIDM_TRUE_PUSHYA);
    PyModule_AddIntConstant(m, "SIDM_GALCENT_RGILBRAND", SE_SIDM_GALCENT_RGILBRAND);
    PyModule_AddIntConstant(m, "SIDM_GALEQU_IAU1958", SE_SIDM_GALEQU_IAU1958);
    PyModule_AddIntConstant(m, "SIDM_GALEQU_TRUE", SE_SIDM_GALEQU_TRUE);
    PyModule_AddIntConstant(m, "SIDM_GALEQU_MULA", SE_SIDM_GALEQU_MULA);
    PyModule_AddIntConstant(m, "SIDM_GALALIGN_MARDYKS", SE_SIDM_GALALIGN_MARDYKS);
    PyModule_AddIntConstant(m, "SIDM_TRUE_MULA", SE_SIDM_TRUE_MULA);
    PyModule_AddIntConstant(m, "SIDM_GALCENT_MULA_WILHELM", SE_SIDM_GALCENT_MULA_WILHELM);
    PyModule_AddIntConstant(m, "SIDM_ARYABHATA_522", SE_SIDM_ARYABHATA_522);
    PyModule_AddIntConstant(m, "SIDM_BABYL_BRITTON", SE_SIDM_BABYL_BRITTON);
    PyModule_AddIntConstant(m, "SIDM_TRUE_SHEORAN", SE_SIDM_TRUE_SHEORAN);
    PyModule_AddIntConstant(m, "SIDM_GALCENT_COCHRANE", SE_SIDM_GALCENT_COCHRANE);
    PyModule_AddIntConstant(m, "SIDM_GALEQU_FIORENZA", SE_SIDM_GALEQU_FIORENZA);
    PyModule_AddIntConstant(m, "SIDM_VALENS_MOON", SE_SIDM_VALENS_MOON);
    PyModule_AddIntConstant(m, "SIDM_LAHIRI_1940", SE_SIDM_LAHIRI_1940);
    PyModule_AddIntConstant(m, "SIDM_LAHIRI_VP285", SE_SIDM_LAHIRI_VP285);
    PyModule_AddIntConstant(m, "SIDM_KRISHNAMURTI_VP291", SE_SIDM_KRISHNAMURTI_VP291);
    PyModule_AddIntConstant(m, "SIDM_LAHIRI_ICRC", SE_SIDM_LAHIRI_ICRC);
    PyModule_AddIntConstant(m, "SIDM_USER", SE_SIDM_USER);

    PyModule_AddIntConstant(m, "NSIDM_PREDEF", SE_NSIDM_PREDEF);

    PyModule_AddIntConstant(m, "NODBIT_MEAN", SE_NODBIT_MEAN);
    PyModule_AddIntConstant(m, "NODBIT_OSCU", SE_NODBIT_OSCU);
    PyModule_AddIntConstant(m, "NODBIT_OSCU_BAR", SE_NODBIT_OSCU_BAR);
    PyModule_AddIntConstant(m, "NODBIT_FOPOINT", SE_NODBIT_FOPOINT);

    PyModule_AddIntConstant(m, "FLG_DEFAULTEPH", SEFLG_DEFAULTEPH);

    PyModule_AddIntConstant(m, "MAX_STNAME", SE_MAX_STNAME);

    PyModule_AddIntConstant(m, "ECL_CENTRAL", SE_ECL_CENTRAL);
    PyModule_AddIntConstant(m, "ECL_NONCENTRAL", SE_ECL_NONCENTRAL);
    PyModule_AddIntConstant(m, "ECL_TOTAL", SE_ECL_TOTAL);
    PyModule_AddIntConstant(m, "ECL_ANNULAR", SE_ECL_ANNULAR);
    PyModule_AddIntConstant(m, "ECL_PARTIAL", SE_ECL_PARTIAL);
    PyModule_AddIntConstant(m, "ECL_ANNULAR_TOTAL", SE_ECL_ANNULAR_TOTAL);
    PyModule_AddIntConstant(m, "ECL_HYBRID", SE_ECL_HYBRID);
    PyModule_AddIntConstant(m, "ECL_PENUMBRAL", SE_ECL_PENUMBRAL);
    PyModule_AddIntConstant(m, "ECL_ALLTYPES_SOLAR", SE_ECL_ALLTYPES_SOLAR);
    PyModule_AddIntConstant(m, "ECL_ALLTYPES_LUNAR", SE_ECL_ALLTYPES_LUNAR);
    PyModule_AddIntConstant(m, "ECL_VISIBLE", SE_ECL_VISIBLE);
    PyModule_AddIntConstant(m, "ECL_MAX_VISIBLE", SE_ECL_MAX_VISIBLE);
    PyModule_AddIntConstant(m, "ECL_1ST_VISIBLE", SE_ECL_1ST_VISIBLE);
    PyModule_AddIntConstant(m, "ECL_PARTBEG_VISIBLE", SE_ECL_PARTBEG_VISIBLE);
    PyModule_AddIntConstant(m, "ECL_2ND_VISIBLE", SE_ECL_2ND_VISIBLE);
    PyModule_AddIntConstant(m, "ECL_TOTBEG_VISIBLE", SE_ECL_TOTBEG_VISIBLE);
    PyModule_AddIntConstant(m, "ECL_3RD_VISIBLE", SE_ECL_3RD_VISIBLE);
    PyModule_AddIntConstant(m, "ECL_TOTEND_VISIBLE", SE_ECL_TOTEND_VISIBLE);
    PyModule_AddIntConstant(m, "ECL_4TH_VISIBLE", SE_ECL_4TH_VISIBLE);
    PyModule_AddIntConstant(m, "ECL_PARTEND_VISIBLE", SE_ECL_PARTEND_VISIBLE);
    PyModule_AddIntConstant(m, "ECL_PENUMBBEG_VISIBLE", SE_ECL_PENUMBBEG_VISIBLE);
    PyModule_AddIntConstant(m, "ECL_PENUMBEND_VISIBLE", SE_ECL_PENUMBEND_VISIBLE);
    PyModule_AddIntConstant(m, "ECL_OCC_BEG_DAYLIGHT", SE_ECL_OCC_BEG_DAYLIGHT);
    PyModule_AddIntConstant(m, "ECL_OCC_END_DAYLIGHT", SE_ECL_OCC_END_DAYLIGHT);
    PyModule_AddIntConstant(m, "ECL_ONE_TRY", SE_ECL_ONE_TRY);

    PyModule_AddIntConstant(m, "CALC_RISE", SE_CALC_RISE);
    PyModule_AddIntConstant(m, "CALC_SET", SE_CALC_SET);
    PyModule_AddIntConstant(m, "CALC_MTRANSIT", SE_CALC_MTRANSIT);
    PyModule_AddIntConstant(m, "CALC_ITRANSIT", SE_CALC_ITRANSIT);
    PyModule_AddIntConstant(m, "BIT_DISC_CENTER", SE_BIT_DISC_CENTER);
    PyModule_AddIntConstant(m, "BIT_DISC_BOTTOM", SE_BIT_DISC_BOTTOM);
    PyModule_AddIntConstant(m, "BIT_NO_REFRACTION", SE_BIT_NO_REFRACTION);
    PyModule_AddIntConstant(m, "BIT_CIVIL_TWILIGHT", SE_BIT_CIVIL_TWILIGHT);
    PyModule_AddIntConstant(m, "BIT_NAUTIC_TWILIGHT", SE_BIT_NAUTIC_TWILIGHT);
    PyModule_AddIntConstant(m, "BIT_ASTRO_TWILIGHT", SE_BIT_ASTRO_TWILIGHT);
    PyModule_AddIntConstant(m, "BIT_FIXED_DISC_SIZE", SE_BIT_FIXED_DISC_SIZE);
    PyModule_AddIntConstant(m, "BIT_FORCE_SLOW_METHOD", SE_BIT_FORCE_SLOW_METHOD);
    PyModule_AddIntConstant(m, "BIT_HINDU_RISING", SE_BIT_HINDU_RISING);

    PyModule_AddIntConstant(m, "ECL2HOR", SE_ECL2HOR);
    PyModule_AddIntConstant(m, "EQU2HOR", SE_EQU2HOR);
    PyModule_AddIntConstant(m, "HOR2ECL", SE_HOR2ECL);
    PyModule_AddIntConstant(m, "HOR2EQU", SE_HOR2EQU);

    PyModule_AddIntConstant(m, "TRUE_TO_APP", SE_TRUE_TO_APP);
    PyModule_AddIntConstant(m, "APP_TO_TRUE", SE_APP_TO_TRUE);

    PyModule_AddIntConstant(m, "DE_NUMBER", SE_DE_NUMBER);
    PyModule_AddStringConstant(m, "FNAME_DE200", SE_FNAME_DE200);
    PyModule_AddStringConstant(m, "FNAME_DE403", SE_FNAME_DE403);
    PyModule_AddStringConstant(m, "FNAME_DE404", SE_FNAME_DE404);
    PyModule_AddStringConstant(m, "FNAME_DE405", SE_FNAME_DE405);
    PyModule_AddStringConstant(m, "FNAME_DE406", SE_FNAME_DE406);
    PyModule_AddStringConstant(m, "SE_FNAME_DE431", SE_FNAME_DE431);
    PyModule_AddStringConstant(m, "FNAME_DFT", SE_FNAME_DFT);
    PyModule_AddStringConstant(m, "FNAME_DFT2", SE_FNAME_DFT2);
    PyModule_AddStringConstant(m, "STARFILE_OLD", SE_STARFILE_OLD);
    PyModule_AddStringConstant(m, "STARFILE", SE_STARFILE);
    PyModule_AddStringConstant(m, "ASTNAMFILE", SE_ASTNAMFILE);
    PyModule_AddStringConstant(m, "FICTFILE", SE_FICTFILE);

    PyModule_AddStringConstant(m, "EPHE_PATH", SE_EPHE_PATH);

    PyModule_AddIntConstant(m, "SPLIT_DEG_ROUND_SEC", SE_SPLIT_DEG_ROUND_SEC);
    PyModule_AddIntConstant(m, "SPLIT_DEG_ROUND_MIN", SE_SPLIT_DEG_ROUND_MIN);
    PyModule_AddIntConstant(m, "SPLIT_DEG_ROUND_DEG", SE_SPLIT_DEG_ROUND_DEG);
    PyModule_AddIntConstant(m, "SPLIT_DEG_ZODIACAL", SE_SPLIT_DEG_ZODIACAL);
    PyModule_AddIntConstant(m, "SPLIT_DEG_KEEP_SIGN", SE_SPLIT_DEG_KEEP_SIGN);
    PyModule_AddIntConstant(m, "SPLIT_DEG_KEEP_DEG", SE_SPLIT_DEG_KEEP_DEG);

    PyModule_AddIntConstant(m, "HELIACAL_RISING", SE_HELIACAL_RISING);
    PyModule_AddIntConstant(m, "HELIACAL_SETTING", SE_HELIACAL_SETTING);
    PyModule_AddIntConstant(m, "EVENING_FIRST", SE_EVENING_FIRST);
    PyModule_AddIntConstant(m, "EVENING_LAST", SE_EVENING_LAST);
    PyModule_AddIntConstant(m, "MORNING_LAST", SE_MORNING_LAST);
    PyModule_AddIntConstant(m, "MORNING_FIRST", SE_MORNING_FIRST);
    PyModule_AddIntConstant(m, "ACRONYCHAL_RISING", SE_ACRONYCHAL_RISING);
    PyModule_AddIntConstant(m, "COSMICAL_SETTING", SE_COSMICAL_SETTING);
    PyModule_AddIntConstant(m, "ACRONYCHAL_SETTING", SE_ACRONYCHAL_SETTING);

    PyModule_AddIntConstant(m, "HELFLAG_LONG_SEARCH", SE_HELFLAG_LONG_SEARCH);
    PyModule_AddIntConstant(m, "HELFLAG_HIGH_PRECISION", SE_HELFLAG_HIGH_PRECISION);
    PyModule_AddIntConstant(m, "HELFLAG_OPTICAL_PARAMS", SE_HELFLAG_OPTICAL_PARAMS);
    PyModule_AddIntConstant(m, "HELFLAG_NO_DETAILS", SE_HELFLAG_NO_DETAILS);
    PyModule_AddIntConstant(m, "HELFLAG_SEARCH_1_PERIOD", SE_HELFLAG_SEARCH_1_PERIOD);
    PyModule_AddIntConstant(m, "HELFLAG_VISLIM_DARK", SE_HELFLAG_VISLIM_DARK);
    PyModule_AddIntConstant(m, "HELFLAG_VISLIM_NOMOON", SE_HELFLAG_VISLIM_NOMOON);
    PyModule_AddIntConstant(m, "HELFLAG_VISLIM_PHOTOPIC", SE_HELFLAG_VISLIM_PHOTOPIC);
    PyModule_AddIntConstant(m, "HELFLAG_AV", SE_HELFLAG_AV);
    PyModule_AddIntConstant(m, "HELFLAG_AVKIND_VR", SE_HELFLAG_AVKIND_VR);
    PyModule_AddIntConstant(m, "HELFLAG_AVKIND_PTO", SE_HELFLAG_AVKIND_PTO);
    PyModule_AddIntConstant(m, "HELFLAG_AVKIND_MIN7", SE_HELFLAG_AVKIND_MIN7);
    PyModule_AddIntConstant(m, "HELFLAG_AVKIND_MIN9", SE_HELFLAG_AVKIND_MIN9);
    PyModule_AddIntConstant(m, "HELFLAG_AVKIND", SE_HELFLAG_AVKIND);
    PyModule_AddFloatConstant(m, "TJD_INVALID", TJD_INVALID);
    PyModule_AddIntConstant(m, "SIMULATE_VICTORVB", SIMULATE_VICTORVB);
#if 0 /* Unused */
    PyModule_AddIntConstant(m, "HELIACAL_LONG_SEARCH", SE_HELIACAL_LONG_SEARCH);
    PyModule_AddIntConstant(m, "HELIACAL_HIGH_PRECISION", SE_HELIACAL_HIGH_PRECISION);
    PyModule_AddIntConstant(m, "HELIACAL_OPTICAL_PARAMS", SE_HELIACAL_OPTICAL_PARAMS);
    PyModule_AddIntConstant(m, "HELIACAL_NO_DETAILS", SE_HELIACAL_NO_DETAILS);
    PyModule_AddIntConstant(m, "HELIACAL_SEARCH_1_PERIOD", SE_HELIACAL_SEARCH_1_PERIOD);
    PyModule_AddIntConstant(m, "HELIACAL_VISLIM_DARK", SE_HELIACAL_VISLIM_DARK);
    PyModule_AddIntConstant(m, "HELIACAL_VISLIM_NOMOON", SE_HELIACAL_VISLIM_NOMOON);
    PyModule_AddIntConstant(m, "HELIACAL_VISLIM_PHOTOPIC", SE_HELIACAL_VISLIM_PHOTOPIC);
    PyModule_AddIntConstant(m, "HELIACAL_AVKIND_VR", SE_HELIACAL_AVKIND_VR);
    PyModule_AddIntConstant(m, "HELIACAL_AVKIND_PTO", SE_HELIACAL_AVKIND_PTO);
    PyModule_AddIntConstant(m, "HELIACAL_AVKIND_MIN7", SE_HELIACAL_AVKIND_MIN7);
    PyModule_AddIntConstant(m, "HELIACAL_AVKIND_MIN9", SE_HELIACAL_AVKIND_MIN9);
    PyModule_AddIntConstant(m, "HELIACAL_AVKIND", SE_HELIACAL_AVKIND);
#endif
    PyModule_AddIntConstant(m, "PHOTOPIC_FLAG", SE_PHOTOPIC_FLAG);
    PyModule_AddIntConstant(m, "SCOTOPIC_FLAG", SE_SCOTOPIC_FLAG);
    PyModule_AddIntConstant(m, "MIXEDOPIC_FLAG", SE_MIXEDOPIC_FLAG);

    PyModule_AddFloatConstant(m, "TIDAL_DE200", SE_TIDAL_DE200);
    PyModule_AddFloatConstant(m, "TIDAL_DE403", SE_TIDAL_DE403);
    PyModule_AddFloatConstant(m, "TIDAL_DE404", SE_TIDAL_DE404);
    PyModule_AddFloatConstant(m, "TIDAL_DE405", SE_TIDAL_DE405);
    PyModule_AddFloatConstant(m, "TIDAL_DE406", SE_TIDAL_DE406);
    PyModule_AddFloatConstant(m, "TIDAL_DE421", SE_TIDAL_DE421);
    PyModule_AddFloatConstant(m, "TIDAL_DE422", SE_TIDAL_DE422);
    PyModule_AddFloatConstant(m, "TIDAL_DE430", SE_TIDAL_DE430);
    PyModule_AddFloatConstant(m, "TIDAL_DE431", SE_TIDAL_DE431);
    PyModule_AddFloatConstant(m, "TIDAL_DE441", SE_TIDAL_DE441);
    PyModule_AddFloatConstant(m, "TIDAL_26", SE_TIDAL_26);
    PyModule_AddFloatConstant(m, "TIDAL_STEPHENSON_2016", SE_TIDAL_STEPHENSON_2016);
    PyModule_AddFloatConstant(m, "TIDAL_DEFAULT", SE_TIDAL_DEFAULT);
    PyModule_AddIntConstant(m, "TIDAL_AUTOMATIC", SE_TIDAL_AUTOMATIC);
    PyModule_AddFloatConstant(m, "TIDAL_MOSEPH", SE_TIDAL_MOSEPH);
    PyModule_AddFloatConstant(m, "TIDAL_SWIEPH", SE_TIDAL_SWIEPH);
    PyModule_AddFloatConstant(m, "TIDAL_JPLEPH", SE_TIDAL_JPLEPH);

    PyModule_AddFloatConstant(m, "DELTAT_AUTOMATIC", SE_DELTAT_AUTOMATIC);
    PyModule_AddIntConstant(m, "MODEL_DELTAT", SE_MODEL_DELTAT);
    PyModule_AddIntConstant(m, "MODEL_PREC_LONGTERM", SE_MODEL_PREC_LONGTERM);
    PyModule_AddIntConstant(m, "MODEL_PREC_SHORTTERM", SE_MODEL_PREC_SHORTTERM);
    PyModule_AddIntConstant(m, "MODEL_NUT", SE_MODEL_NUT);
    PyModule_AddIntConstant(m, "MODEL_BIAS", SE_MODEL_BIAS);
    PyModule_AddIntConstant(m, "MODEL_JPLHOR_MODE", SE_MODEL_JPLHOR_MODE);
    PyModule_AddIntConstant(m, "MODEL_JPLHORA_MODE", SE_MODEL_JPLHORA_MODE);
    PyModule_AddIntConstant(m, "MODEL_SIDT", SE_MODEL_SIDT);
    PyModule_AddIntConstant(m, "NSE_MODELS", NSE_MODELS);

    PyModule_AddIntConstant(m, "MOD_NPREC", SEMOD_NPREC);
    PyModule_AddIntConstant(m, "MOD_PREC_IAU_1976", SEMOD_PREC_IAU_1976);
    PyModule_AddIntConstant(m, "MOD_PREC_LASKAR_1986", SEMOD_PREC_LASKAR_1986);
    PyModule_AddIntConstant(m, "MOD_PREC_WILL_EPS_LASK", SEMOD_PREC_WILL_EPS_LASK);
    PyModule_AddIntConstant(m, "MOD_PREC_WILLIAMS_1994",SEMOD_PREC_WILLIAMS_1994);
    PyModule_AddIntConstant(m, "MOD_PREC_SIMON_1994",SEMOD_PREC_SIMON_1994);
    PyModule_AddIntConstant(m, "MOD_PREC_IAU_2000", SEMOD_PREC_IAU_2000);
    PyModule_AddIntConstant(m, "MOD_PREC_BRETAGNON_2003", SEMOD_PREC_BRETAGNON_2003);
    PyModule_AddIntConstant(m, "MOD_PREC_IAU_2006", SEMOD_PREC_IAU_2006);
    PyModule_AddIntConstant(m, "MOD_PREC_VONDRAK_2011", SEMOD_PREC_VONDRAK_2011);
    PyModule_AddIntConstant(m, "MOD_PREC_OWEN_1990", SEMOD_PREC_OWEN_1990);
    PyModule_AddIntConstant(m, "MOD_PREC_NEWCOMB", SEMOD_PREC_NEWCOMB);
    PyModule_AddIntConstant(m, "MOD_PREC_DEFAULT", SEMOD_PREC_DEFAULT);
    PyModule_AddIntConstant(m, "MOD_PREC_DEFAULT_SHORT", SEMOD_PREC_DEFAULT_SHORT);

    PyModule_AddIntConstant(m, "MOD_NNUT", SEMOD_NNUT);
    PyModule_AddIntConstant(m, "MOD_NUT_IAU_1980", SEMOD_NUT_IAU_1980);
    PyModule_AddIntConstant(m, "MOD_NUT_IAU_CORR_1987", SEMOD_NUT_IAU_CORR_1987);
    PyModule_AddIntConstant(m, "MOD_NUT_IAU_2000A", SEMOD_NUT_IAU_2000A);
    PyModule_AddIntConstant(m, "MOD_NUT_IAU_2000B", SEMOD_NUT_IAU_2000B);
    PyModule_AddIntConstant(m, "MOD_NUT_WOOLARD", SEMOD_NUT_WOOLARD);
    PyModule_AddIntConstant(m, "MOD_NUT_DEFAULT", SEMOD_NUT_DEFAULT);

    PyModule_AddIntConstant(m, "MOD_NBIAS", SEMOD_NBIAS);
    PyModule_AddIntConstant(m, "MOD_BIAS_NONE", SEMOD_BIAS_NONE);
    PyModule_AddIntConstant(m, "MOD_BIAS_IAU2000", SEMOD_BIAS_IAU2000);
    PyModule_AddIntConstant(m, "MOD_BIAS_IAU2006", SEMOD_BIAS_IAU2006);
    PyModule_AddIntConstant(m, "MOD_BIAS_DEFAULT", SEMOD_BIAS_DEFAULT);

    PyModule_AddIntConstant(m, "MOD_NJPLHOR", SEMOD_NJPLHOR);
    PyModule_AddIntConstant(m, "MOD_JPLHOR_LONG_AGREEMENT", SEMOD_JPLHOR_LONG_AGREEMENT);
    PyModule_AddIntConstant(m, "MOD_JPLHOR_DEFAULT", SEMOD_JPLHOR_DEFAULT);
    PyModule_AddIntConstant(m, "MOD_NJPLHORA", SEMOD_NJPLHORA);
    PyModule_AddIntConstant(m, "MOD_JPLHORA_1", SEMOD_JPLHORA_1);
    PyModule_AddIntConstant(m, "MOD_JPLHORA_2", SEMOD_JPLHORA_2);
    PyModule_AddIntConstant(m, "MOD_JPLHORA_3", SEMOD_JPLHORA_3);
    PyModule_AddIntConstant(m, "MOD_JPLHORA_DEFAULT", SEMOD_JPLHORA_DEFAULT);

    PyModule_AddIntConstant(m, "MOD_NDELTAT", SEMOD_NDELTAT);
    PyModule_AddIntConstant(m, "MOD_DELTAT_STEPHENSON_MORRISON_1984", SEMOD_DELTAT_STEPHENSON_MORRISON_1984);
    PyModule_AddIntConstant(m, "MOD_DELTAT_STEPHENSON_1997", SEMOD_DELTAT_STEPHENSON_1997);
    PyModule_AddIntConstant(m, "MOD_DELTAT_STEPHENSON_MORRISON_2004", SEMOD_DELTAT_STEPHENSON_MORRISON_2004);
    PyModule_AddIntConstant(m, "MOD_DELTAT_ESPENAK_MEEUS_2006", SEMOD_DELTAT_ESPENAK_MEEUS_2006);
    PyModule_AddIntConstant(m, "MOD_DELTAT_STEPHENSON_ETC_2016", SEMOD_DELTAT_STEPHENSON_ETC_2016);
    PyModule_AddIntConstant(m, "MOD_DELTAT_DEFAULT", SEMOD_DELTAT_DEFAULT);

#if PYSWE_USE_SWEPHELP
#if PY_MAJOR_VERSION >= 3
    m2 = PyModule_Create(&pyswh_module);
    if (m2 == NULL)
        Py_FatalError("Can't create module swisseph.contrib!");
#elif PY_MAJOR_VERSION < 3
    m2 = Py_InitModule4("swisseph.contrib", pyswh_methods,
        pyswh_module_documentation,
        (PyObject*) NULL, PYTHON_API_VERSION);
#endif

    if (PyType_Ready(&pyswh_User_type) < 0)
        Py_FatalError("User type not ready!");
    Py_INCREF(&pyswh_User_type);
    PyModule_AddObject(m2, "User", (PyObject*) &pyswh_User_type);

    if (PyType_Ready(&pyswh_Data_type) < 0)
        Py_FatalError("Data type not ready!");
    Py_INCREF(&pyswh_Data_type);
    PyModule_AddObject(m2, "Data", (PyObject*) &pyswh_Data_type);

    /* *** Additional constants -- not swiss ephemeris ***/

    /* Aspects */
    PyModule_AddIntConstant(m2, "CONJUNCTION", SWH_CONJUNCTION);
    PyModule_AddIntConstant(m2, "SQUISEXTILE", SWH_SQUISEXTILE);
    PyModule_AddIntConstant(m2, "SEMINOVILE", SWH_SEMINOVILE);
    PyModule_AddFloatConstant(m2, "SQUISQUARE", SWH_SQUISQUARE);
    PyModule_AddFloatConstant(m2, "UNDECILE", SWH_UNDECILE);
    PyModule_AddIntConstant(m2, "SEMISEXTILE", SWH_SEMISEXTILE);
    PyModule_AddIntConstant(m2, "SEMIQUINTILE", SWH_SEMIQUINTILE);
    PyModule_AddIntConstant(m2, "NOVILE", SWH_NOVILE);
    PyModule_AddIntConstant(m2, "SEMISQUARE", SWH_SEMISQUARE);
    PyModule_AddFloatConstant(m2, "SEPTILE", SWH_SEPTILE);
    PyModule_AddIntConstant(m2, "SEXTILE", SWH_SEXTILE);
    PyModule_AddFloatConstant(m2, "BIUNDECILE", SWH_BIUNDECILE);
    PyModule_AddIntConstant(m2, "QUINTILE", SWH_QUINTILE);
    PyModule_AddIntConstant(m2, "BINOVILE", SWH_BINOVILE);
    PyModule_AddIntConstant(m2, "SQUARE", SWH_SQUARE);
    PyModule_AddFloatConstant(m2, "TRIUNDECILE", SWH_TRIUNDECILE);
    PyModule_AddFloatConstant(m2, "BISEPTILE", SWH_BISEPTILE);
    PyModule_AddIntConstant(m2, "TRINE", SWH_TRINE);
    PyModule_AddFloatConstant(m2, "QUADUNDECILE", SWH_QUADUNDECILE);
    PyModule_AddIntConstant(m2, "SESQUISQUARE", SWH_SESQUISQUARE);
    PyModule_AddIntConstant(m2, "BIQUINTILE", SWH_BIQUINTILE);
    PyModule_AddIntConstant(m2, "QUINCUNX", SWH_QUINCUNX);
    PyModule_AddFloatConstant(m2, "TRISEPTILE", SWH_TRISEPTILE);
    PyModule_AddIntConstant(m2, "QUATRONOVILE", SWH_QUATRONOVILE);
    PyModule_AddFloatConstant(m2, "QUINUNDECILE", SWH_QUINUNDECILE);
    PyModule_AddIntConstant(m2, "OPPOSITION", SWH_OPPOSITION);

    /* Signs */
    PyModule_AddIntConstant(m2, "ARIES", SWH_ARIES);
    PyModule_AddIntConstant(m2, "TAURUS", SWH_TAURUS);
    PyModule_AddIntConstant(m2, "GEMINI", SWH_GEMINI);
    PyModule_AddIntConstant(m2, "CANCER", SWH_CANCER);
    PyModule_AddIntConstant(m2, "LEO", SWH_LEO);
    PyModule_AddIntConstant(m2, "VIRGO", SWH_VIRGO);
    PyModule_AddIntConstant(m2, "LIBRA", SWH_LIBRA);
    PyModule_AddIntConstant(m2, "SCORPIO", SWH_SCORPIO);
    PyModule_AddIntConstant(m2, "SAGITTARIUS", SWH_SAGITTARIUS);
    PyModule_AddIntConstant(m2, "CAPRICORN", SWH_CAPRICORN);
    PyModule_AddIntConstant(m2, "AQUARIUS", SWH_AQUARIUS);
    PyModule_AddIntConstant(m2, "PISCES", SWH_PISCES);

    PyModule_AddIntConstant(m2, "MESHA", SWH_MESHA);
    PyModule_AddIntConstant(m2, "VRISHABA", SWH_VRISHABA);
    PyModule_AddIntConstant(m2, "MITHUNA", SWH_MITHUNA);
    PyModule_AddIntConstant(m2, "KATAKA", SWH_KATAKA);
    PyModule_AddIntConstant(m2, "SIMHA", SWH_SIMHA);
    PyModule_AddIntConstant(m2, "KANYA", SWH_KANYA);
    PyModule_AddIntConstant(m2, "THULA", SWH_THULA);
    PyModule_AddIntConstant(m2, "VRISHIKA", SWH_VRISHIKA);
    PyModule_AddIntConstant(m2, "DHANUS", SWH_DHANUS);
    PyModule_AddIntConstant(m2, "MAKARA", SWH_MAKARA);
    PyModule_AddIntConstant(m2, "KUMBHA", SWH_KUMBHA);
    PyModule_AddIntConstant(m2, "MEENA", SWH_MEENA);

    /* Planets */
    PyModule_AddIntConstant(m2, "RAVI", SWH_RAVI);
    PyModule_AddIntConstant(m2, "CHANDRA", SWH_CHANDRA);
    PyModule_AddIntConstant(m2, "BUDHA", SWH_BUDHA);
    PyModule_AddIntConstant(m2, "SUKRA", SWH_SUKRA);
    PyModule_AddIntConstant(m2, "KUJA", SWH_KUJA);
    PyModule_AddIntConstant(m2, "GURU", SWH_GURU);
    PyModule_AddIntConstant(m2, "SANI", SWH_SANI);
    PyModule_AddIntConstant(m2, "RAHU", SWH_RAHU);
    PyModule_AddIntConstant(m2, "KETU", SWH_KETU);

    PyModule_AddIntConstant(m2, "SURYA", SWH_SURYA);
    PyModule_AddIntConstant(m2, "SOMA", SWH_SOMA);
    PyModule_AddIntConstant(m2, "SOUMYA", SWH_SOUMYA);
    PyModule_AddIntConstant(m2, "BHARGAVA", SWH_BHARGAVA);
    PyModule_AddIntConstant(m2, "ANGARAKA", SWH_ANGARAKA);
    PyModule_AddIntConstant(m2, "BRIHASPATI", SWH_BRIHASPATI);
    PyModule_AddIntConstant(m2, "MANDA", SWH_MANDA);
    PyModule_AddIntConstant(m2, "THAMA", SWH_THAMA);
    PyModule_AddIntConstant(m2, "SIKHI", SWH_SIKHI);

    /* Nakshatras */
    PyModule_AddIntConstant(m2, "ASWINI", SWH_ASWINI);
    PyModule_AddIntConstant(m2, "BHARANI", SWH_BHARANI);
    PyModule_AddIntConstant(m2, "KRITIKHA", SWH_KRITHIKA);
    PyModule_AddIntConstant(m2, "ROHINI", SWH_ROHINI);
    PyModule_AddIntConstant(m2, "MRIGASIRA", SWH_MRIGASIRA);
    PyModule_AddIntConstant(m2, "ARIDRA", SWH_ARIDRA);
    PyModule_AddIntConstant(m2, "PUNARVASU", SWH_PUNARVASU);
    PyModule_AddIntConstant(m2, "PUSHYAMI", SWH_PUSHYAMI);
    PyModule_AddIntConstant(m2, "ASLESHA", SWH_ASLESHA);
    PyModule_AddIntConstant(m2, "MAKHA", SWH_MAKHA);
    PyModule_AddIntConstant(m2, "PUBBA", SWH_PUBBA);
    PyModule_AddIntConstant(m2, "UTTARA", SWH_UTTARA);
    PyModule_AddIntConstant(m2, "HASTA", SWH_HASTA);
    PyModule_AddIntConstant(m2, "CHITTA", SWH_CHITTA);
    PyModule_AddIntConstant(m2, "SWATHI", SWH_SWATHI);
    PyModule_AddIntConstant(m2, "VISHAKA", SWH_VISHAKA);
    PyModule_AddIntConstant(m2, "ANURADHA", SWH_ANURADHA);
    PyModule_AddIntConstant(m2, "JYESTA", SWH_JYESTA);
    PyModule_AddIntConstant(m2, "MOOLA", SWH_MOOLA);
    PyModule_AddIntConstant(m2, "POORVASHADA", SWH_POORVASHADA);
    PyModule_AddIntConstant(m2, "UTTARASHADA", SWH_UTTARASHADA);
    PyModule_AddIntConstant(m2, "SRAVANA", SWH_SRAVANA);
    PyModule_AddIntConstant(m2, "DHANISHTA", SWH_DHANISHTA);
    PyModule_AddIntConstant(m2, "SATABISHA", SWH_SATABISHA);
    PyModule_AddIntConstant(m2, "POORVABHADRA", SWH_POORVABHADRA);
    PyModule_AddIntConstant(m2, "UTTARABHADRA", SWH_UTTARABHADRA);
    PyModule_AddIntConstant(m2, "REVATHI", SWH_REVATHI);

    PyModule_AddObject(m, "contrib", m2);
#endif /* PYSWE_USE_SWEPHELP */

    PyModule_AddIntConstant(m, "__version__", PYSWISSEPH_VERSION);
    PyModule_AddStringConstant(m, "version", swe_version(buf));

    if (PyErr_Occurred())
        Py_FatalError("Can't initialize module swisseph!");

#if PYSWE_AUTO_SET_EPHE_PATH
    /* Automaticly set ephemeris path on module import */
    swe_set_ephe_path(PYSWE_DEFAULT_EPHE_PATH);
#endif /* PYSWE_AUTO_SET_EPHE_PATH */

#if PY_MAJOR_VERSION >= 3
    return m;
#endif
}

/* vi: set fenc=utf-8 ff=unix et sw=4 ts=4 sts=4 : */
