/*
    This file is part of Pyswisseph.

    Copyright (c) 2007-2014 Stanislas Marquis <smarquis@astrorigin.ch>

    Pyswisseph is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Pyswisseph is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Pyswisseph.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 *  \file pyswisseph.c
 *
 *  Python extension to the Swiss Ephemeris
 *
 *  Author/maintainer: Stanislas Marquis <smarquis@astrorigin.ch>
 *  Homepage: http://astrorigin.ch/pyswisseph
 *
 *  Swisseph authors: Alois Treindl, Dieter Koch (et al.)
 *  Swisseph homepage: http://www.astro.com/swisseph
 *
 *  Swisseph version: 2.00.00
 *  Last revision: 14.03.2014
 */

#define PYSWISSEPH_VERSION      20140314

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

/* swisseph.Error (module exception type) */
static PyObject * pyswe_Error;

/* swisseph.set_ephe_path */
static char pyswe_set_ephe_path__doc__[] =
"Set ephemeris files path.\n\n"
"Args: str path=\"" PYSWE_DEFAULT_EPHE_PATH "\"\n"
"Return: None";

static PyObject * pyswe_set_ephe_path FUNCARGS_KEYWDS
{
    char *path = PYSWE_DEFAULT_EPHE_PATH;
    static char *kwlist[] = {"path", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "|s", kwlist, &path))
        return NULL;
    swe_set_ephe_path(path);
    Py_RETURN_NONE;
}

/* swisseph.set_jpl_file */
static char pyswe_set_jpl_file__doc__[] =
"Set JPL file path.\n\n"
"Args: str path\n"
"Return: None";

static PyObject * pyswe_set_jpl_file FUNCARGS_KEYWDS
{
    char *path;
    static char *kwlist[] = {"path", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "s", kwlist, &path))
        return NULL;
    swe_set_jpl_file(path);
    Py_RETURN_NONE;
}

/* swisseph.set_topo */
static char pyswe_set_topo__doc__[] =
"Set topocentric parameters.\n\n"
"Args: float lon, float lat, float alt=0.0\n"
"Return: None";

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

/* swisseph.set_sid_mode */
static char pyswe_set_sid_mode__doc__[] =
"Set sidereal mode.\n\n"
"Args: int mode, float t0=0.0, float ayan_t0=0.0\n"
"Return: None";

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

/* swisseph.get_ayanamsa */
static char pyswe_get_ayanamsa__doc__[] =
"Calculate ayanamsa (ET).\n\n"
"Args: float julday\n"
"Return: float";

static PyObject * pyswe_get_ayanamsa FUNCARGS_KEYWDS
{
    double jd, ret;
    static char *kwlist[] = {"julday", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &jd))
        return NULL;
    ret = swe_get_ayanamsa(jd);
    return Py_BuildValue("f", ret);
}

/* swisseph.get_ayanamsa_ut */
static char pyswe_get_ayanamsa_ut__doc__[] =
"Calculate ayanamsa (UT).\n\n"
"Args: float julday\n"
"Return: float";

static PyObject * pyswe_get_ayanamsa_ut FUNCARGS_KEYWDS
{
    double jd, ret;
    static char *kwlist[] = {"julday", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &jd))
        return NULL;
    ret = swe_get_ayanamsa_ut(jd);
    return Py_BuildValue("f", ret);
}

/* swisseph.get_ayanamsa_name */
static char pyswe_get_ayanamsa_name__doc__[] =
"Get ayanamsa name from sidereal mode constant.\n\n"
"Args: int sidmode\n"
"Return: str";

static PyObject * pyswe_get_ayanamsa_name FUNCARGS_KEYWDS
{
    int mode;
    char *name;
    static char *kwlist[] = {"sidmode", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i", kwlist, &mode))
        return NULL;
    name = swe_get_ayanamsa_name(mode);
    return Py_BuildValue("s", name);
}

/* swisseph.close */
static char pyswe_close__doc__[] =
"Close swiss ephemeris.\n\n"
"Args: -\n"
"Return: None";

static PyObject * pyswe_close FUNCARGS_SELF
{
    swe_close();
    Py_RETURN_NONE;
}

/* swisseph.get_planet_name */
static char pyswe_get_planet_name__doc__[] =
"Get planet name.\n\n"
"Args: int planet\n"
"Return: str";

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

/* swisseph.calc */
static char pyswe_calc__doc__[] =
"Calculate body positions (ET).\n\n"
"Args: float julday, int planet, int flag=FLG_SWIEPH+FLG_SPEED\n"
"Return: tuple of 6 float";

static PyObject * pyswe_calc FUNCARGS_KEYWDS
{
    double jd, val[6];
    int ret, ipl, flag = SEFLG_SWIEPH + SEFLG_SPEED;
    char err[256];
    static char *kwlist[] = {"julday", "planet", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "di|i", kwlist,
        &jd, &ipl, &flag))
        return NULL;
    ret = swe_calc(jd, ipl, flag, val, err);
    if (ret < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(ffffff)",val[0],val[1],val[2],val[3],val[4],val[5]);
}

/* swisseph.calc_ut */
static char pyswe_calc_ut__doc__[] =
"Calculate body positions (UT).\n\n"
"Args: float julday, int planet, int flag=FLG_SWIEPH+FLG_SPEED\n"
"Return: tuple of 6 float";

static PyObject * pyswe_calc_ut FUNCARGS_KEYWDS
{
    double jd, val[6];
    int ret, ipl, flag = SEFLG_SWIEPH + SEFLG_SPEED;
    char err[256];
    static char *kwlist[] = {"julday", "planet", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "di|i", kwlist,
        &jd, &ipl, &flag))
        return NULL;
    ret = swe_calc_ut(jd, ipl, flag, val, err);
    if (ret < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(ffffff)",val[0],val[1],val[2],val[3],val[4],val[5]);
}

/* swisseph.fixstar */
static char pyswe_fixstar__doc__[] =
"Calculate fixed star positions (ET).\n\n"
"Args: str star, float julday, int flag=FLG_SWIEPH\n"
"Return: tuple of 6 float";

static PyObject * pyswe_fixstar FUNCARGS_KEYWDS
{
    char *star, st[41], err[256];
    double jd, val[6];
    int ret, flag = SEFLG_SWIEPH;
    static char *kwlist[] = {"star", "julday", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "sd|i", kwlist,
        &star, &jd, &flag))
        return NULL;
    strcpy(st, star);
    ret = swe_fixstar(st, jd, flag, val, err);
    if (ret < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(ffffff)",val[0],val[1],val[2],val[3],val[4],val[5]);
}

/* swisseph.fixstar_ut */
static char pyswe_fixstar_ut__doc__[] =
"Calculate fixed star positions (UT).\n\n"
"Args: str star, float julday, int flag=FLG_SWIEPH\n"
"Return: tuple of 6 float";

static PyObject * pyswe_fixstar_ut FUNCARGS_KEYWDS
{
    char *star, st[41], err[256];
    double jd, val[6];
    int ret, flag = SEFLG_SWIEPH;
    static char *kwlist[] = {"star", "julday", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "sd|i", kwlist,
        &star, &jd, &flag))
        return NULL;
    strcpy(st, star);
    ret = swe_fixstar_ut(st, jd, flag, val, err);
    if (ret < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(ffffff)",val[0],val[1],val[2],val[3],val[4],val[5]);
}

/* swisseph.nod_aps */
static char pyswe_nod_aps__doc__[] =
"Calculate planetary nodes and apsides (ET).\n\n"
"Args: float julday, int planet, int method=NODBIT_MEAN, int flag=FLG_SWIEPH+FLG_SPEED\n"
"Return: 4 tuples of 6 float (asc, des, per, aph)";

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
    if (ret < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(ffffff)(ffffff)(ffffff)(ffffff)", xasc[0],xasc[1],
        xasc[2],xasc[3],xasc[4],xasc[5],xdsc[0],xdsc[1],xdsc[2],xdsc[3],xdsc[4],
        xdsc[5],xper[0],xper[1],xper[2],xper[3],xper[4],xper[5],xaph[0],xaph[1],
        xaph[2],xaph[3],xaph[4],xaph[5]);
}

/* swisseph.nod_aps_ut */
static char pyswe_nod_aps_ut__doc__[] =
"Calculate planetary nodes and apsides (UT).\n\n"
"Args: float julday, int planet, int method=NODBIT_MEAN, int flag=FLG_SWIEPH+FLG_SPEED\n"
"Return: 4 tuples of 6 float (asc, des, per, aph)";

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
    if (ret < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(ffffff)(ffffff)(ffffff)(ffffff)", xasc[0],xasc[1],
        xasc[2],xasc[3],xasc[4],xasc[5],xdsc[0],xdsc[1],xdsc[2],xdsc[3],xdsc[4],
        xdsc[5],xper[0],xper[1],xper[2],xper[3],xper[4],xper[5],xaph[0],xaph[1],
        xaph[2],xaph[3],xaph[4],xaph[5]);
}

/* swisseph.sidtime */
static char pyswe_sidtime__doc__[] =
"Calculate sidereal time (UT).\n\n"
"Args: float julday\n"
"Return: float";

static PyObject * pyswe_sidtime FUNCARGS_KEYWDS
{
    double jd, ret;
    static char *kwlist[] = {"julday", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &jd))
        return NULL;
    ret = swe_sidtime(jd);
    return Py_BuildValue("f", ret);
}

/* swisseph.sidtime0 */
static char pyswe_sidtime0__doc__[] =
"Calculate sidereal time, given obliquity and nutation (UT).\n\n"
"Args: float julday, float obliquity, float nutation\n"
"Return: float";

static PyObject * pyswe_sidtime0 FUNCARGS_KEYWDS
{
    double jd, ret, obliquity, nutation;
    static char *kwlist[] = {"julday", "obliquity", "nutation", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ddd", kwlist,
        &jd, &obliquity, &nutation))
        return NULL;
    ret = swe_sidtime0(jd, obliquity, nutation);
    return Py_BuildValue("f", ret);
}

/* swisseph.houses */
static char pyswe_houses__doc__[] =
"Calculate houses cusps (UT).\n\n"
"Args: float julday, float lat, float lon, char hsys='P'\n"
"Return: 2 tuples of 12 and 8 float (cusps, ascmc) (except Gauquelin)";

static PyObject * pyswe_houses FUNCARGS_KEYWDS
{
    double jd, lat, lon, cusps[37], ascmc[10];
    int ret, hsys = 'P';
    static char *kwlist[] = {"julday", "lat", "lon", "hsys", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ddd|c", kwlist,
        &jd, &lat, &lon, &hsys))
        return NULL;
    ret = swe_houses(jd, lat, lon, hsys, cusps, ascmc);
    if (ret < 0)
    {
        PyErr_SetString(pyswe_Error, "swisseph.houses: error while computing");
        return NULL;
    }
    if (hsys == 71) /* Gauquelin houses */
    {
        return Py_BuildValue("(ffffffffffffffffffffffffffffffffffff)(ffffffff)",
        cusps[1],cusps[2],cusps[3],cusps[4],cusps[5],cusps[6],cusps[7],cusps[8],
        cusps[9],cusps[10],cusps[11],cusps[12],cusps[13],cusps[14],cusps[15],
        cusps[16],cusps[17],cusps[18],cusps[19],cusps[20],cusps[21],cusps[22],
        cusps[23],cusps[24],cusps[25],cusps[26],cusps[27],cusps[28],cusps[29],
        cusps[30],cusps[31],cusps[32],cusps[33],cusps[34],cusps[35],cusps[36],
        ascmc[0],ascmc[1],ascmc[2],ascmc[3],ascmc[4],ascmc[5],ascmc[6],ascmc[7]);
    }
    else
    {
        return Py_BuildValue("(ffffffffffff)(ffffffff)", cusps[1],cusps[2],
        cusps[3],cusps[4],cusps[5],cusps[6],cusps[7],cusps[8],cusps[9],cusps[10],
        cusps[11],cusps[12],ascmc[0],ascmc[1],ascmc[2],ascmc[3],ascmc[4],ascmc[5],
        ascmc[6],ascmc[7]);
    }
}

/* swisseph.houses_armc */
static char pyswe_houses_armc__doc__[] =
"Calculate houses cusps with ARMC.\n\n"
"Args: float armc, float lat, float obliquity, char hsys='P'\n"
"Return: 2 tuples of 12 and 8 float (cusps, ascmc) (except Gauquelin)";

static PyObject * pyswe_houses_armc FUNCARGS_KEYWDS
{
    double armc, lat, obl, cusps[37], ascmc[10];
    int ret, hsys = 'P';
    static char *kwlist[] = {"armc", "lat", "obliquity", "hsys", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ddd|c", kwlist,
        &armc, &lat, &obl, &hsys))
        return NULL;
    ret = swe_houses_armc(armc, lat, obl, hsys, cusps, ascmc);
    if (ret < 0)
    {
        PyErr_SetString(pyswe_Error, "swisseph.houses_armc: error while computing");
        return NULL;
    }
    if (hsys == 71) /* Gauquelin houses */
    {
        return Py_BuildValue("(ffffffffffffffffffffffffffffffffffff)(ffffffff)",
        cusps[1],cusps[2],cusps[3],cusps[4],cusps[5],cusps[6],cusps[7],cusps[8],
        cusps[9],cusps[10],cusps[11],cusps[12],cusps[13],cusps[14],cusps[15],
        cusps[16],cusps[17],cusps[18],cusps[19],cusps[20],cusps[21],cusps[22],
        cusps[23],cusps[24],cusps[25],cusps[26],cusps[27],cusps[28],cusps[29],
        cusps[30],cusps[31],cusps[32],cusps[33],cusps[34],cusps[35],cusps[36],
        ascmc[0],ascmc[1],ascmc[2],ascmc[3],ascmc[4],ascmc[5],ascmc[6],ascmc[7]);
    }
    else
    {
        return Py_BuildValue("(ffffffffffff)(ffffffff)", cusps[1],cusps[2],
        cusps[3],cusps[4],cusps[5],cusps[6],cusps[7],cusps[8],cusps[9],
        cusps[10],cusps[11],cusps[12],ascmc[0],ascmc[1],ascmc[2],ascmc[3],
        ascmc[4],ascmc[5],ascmc[6],ascmc[7]);
    }
}

/* swisseph.houses_ex */
static char pyswe_houses_ex__doc__[] =
"Calculate houses cusps (extended) (UT).\n\n"
"Args: float julday, float lat, float lon, char hsys='P', int flag=0\n"
"Return: 2 tuples of 12 and 8 float (cusps, ascmc) (except Gauquelin)";

static PyObject * pyswe_houses_ex FUNCARGS_KEYWDS
{
    double jd, lat, lon, cusps[37], ascmc[10];
    int ret, hsys = 'P', flag = 0;
    static char *kwlist[] = {"julday", "lat", "lon", "hsys", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ddd|ci", kwlist,
        &jd, &lat, &lon, &hsys, &flag))
        return NULL;
    ret = swe_houses_ex(jd, flag, lat, lon, hsys, cusps, ascmc);
    if (ret < 0)
    {
        PyErr_SetString(pyswe_Error, "swisseph.houses_ex: error while computing");
        return NULL;
    }
    if (hsys == 71) /* Gauquelin houses */
    {
        return Py_BuildValue("(ffffffffffffffffffffffffffffffffffff)(ffffffff)",
        cusps[1],cusps[2],cusps[3],cusps[4],cusps[5],cusps[6],cusps[7],cusps[8],
        cusps[9],cusps[10],cusps[11],cusps[12],cusps[13],cusps[14],cusps[15],
        cusps[16],cusps[17],cusps[18],cusps[19],cusps[20],cusps[21],cusps[22],
        cusps[23],cusps[24],cusps[25],cusps[26],cusps[27],cusps[28],cusps[29],
        cusps[30],cusps[31],cusps[32],cusps[33],cusps[34],cusps[35],cusps[36],
        ascmc[0],ascmc[1],ascmc[2],ascmc[3],ascmc[4],ascmc[5],ascmc[6],ascmc[7]);
    }
    else
    {
        return Py_BuildValue("(ffffffffffff)(ffffffff)", cusps[1],cusps[2],
        cusps[3],cusps[4],cusps[5],cusps[6],cusps[7],cusps[8],cusps[9],
        cusps[10],cusps[11],cusps[12],ascmc[0],ascmc[1],ascmc[2],ascmc[3],
        ascmc[4],ascmc[5],ascmc[6],ascmc[7]);
    }
}

/* swisseph.house_pos */
static char pyswe_house_pos__doc__[] =
"Calculate house position of a body.\n\n"
"Args: float armc, float geolat, float obliquity, float objlon,"
" float objlat=0.0, char hsys='P'\n"
"Return: float";

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
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("f", res);
}

/* swisseph.gauquelin_sector */
static char pyswe_gauquelin_sector__doc__[] =
"Calculate Gauquelin sector position of a body (UT).\n\n"
"Args: float julday, int or str body, float lon, float lat, float alt,"
" float press=0, float temp=0, int method=0, int flag=FLG_SWIEPH\n"
"Return: float";

static PyObject * pyswe_gauquelin_sector FUNCARGS_KEYWDS
{
    double jd, geopos[3], res, ret, press = 0.0, temp = 0.0;
    int plt, flag = SEFLG_SWIEPH, method = 0;
    char *star = "", err[256];
    PyObject *body;
    static char *kwlist[] = {"julday", "body", "lon", "lat", "alt", "press",
        "temp", "method", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dOddd|ddii", kwlist,
        &jd, &body, &geopos[0], &geopos[1], &geopos[2], &press, &temp, &method,
        &flag))
        return NULL;
    if (PyLong_CheckExact(body)) /* long -> planet */
    {
        plt = (int) PyLong_AsLong(body);
    }
#if PY_MAJOR_VERSION >= 3
    else if (PyUnicode_CheckExact(body)) /* unicode -> fixed star */
    {
        plt = 0;
        star = (char*) PyUnicode_AS_DATA(body);
    }
#elif PY_MAJOR_VERSION < 3
    else if (PyInt_CheckExact(body)) /* int -> planet */
    {
        plt = (int) PyInt_AsLong(body);
    }
    else if (PyString_CheckExact(body)) /* str -> fixed star */
    {
        plt = 0;
        star = PyString_AsString(body);
    }
#endif
    else
    {
        PyErr_SetString(pyswe_Error,
            "swisseph.gauquelin_sector: Invalid body type");
        return NULL;
    }
    res = swe_gauquelin_sector(jd, plt, star, flag, method, geopos, press,
        temp, &ret, err);
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("f", ret);
}

/* swisseph.house_name */
static char pyswe_house_name__doc__[] =
"Get the name of the house method.\n\n"
"Args: char hsys\n"
"Return: house system name";

static PyObject * pyswe_house_name FUNCARGS_KEYWDS
{
    char hsys;
    static char *kwlist[] = {"hsys", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "c", kwlist, &hsys))
        return NULL;
    return Py_BuildValue("s", swe_house_name(hsys));
}

/* swisseph.julday */
static char pyswe_julday__doc__[] =
"Calculate Julian day number.\n\n"
"Args: int year, int month, int day, float hour=12.0, int cal=GREG_CAL\n"
"Return: float";

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
    return Py_BuildValue("f", ret);
}

/* swisseph.date_conversion */
static char pyswe_date_conversion__doc__[] =
"Calculate Julian day number with check wether date is correct.\n\n"
"Args: int year, int month, int day, float hour=12.0, char cal='g'\n"
"Return: tuple (int result, float jd)";

static PyObject * pyswe_date_conversion FUNCARGS_KEYWDS
{
    int year, month, day, ret;
    double jd, hour = 12.0;
    char cal = 'g';
    static char *kwlist[] = {"year", "month", "day", "hour", "cal", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "iii|dc", kwlist,
        &year, &month, &day, &hour, &cal))
        return NULL;
    if (cal != 'g' && cal != 'j')
    {
        PyErr_SetString(pyswe_Error,
            "swisseph.date_conversion: Invalid calendar (g/j)");
        return NULL;
    }
    ret = swe_date_conversion(year, month, day, hour, cal, &jd);
    return Py_BuildValue("if", ret, jd);
}

/* swisseph.revjul */
static char pyswe_revjul__doc__[] =
"Calculate year, month, day, hour from Julian day number.\n\n"
"Args: float julday, int cal=GREG_CAL\n"
"Return: tuple of 3 int and 1 float";

static PyObject * pyswe_revjul FUNCARGS_KEYWDS
{
    int year, month, day, cal = SE_GREG_CAL;
    double hour, jd;
    static char *kwlist[] = {"julday", "cal", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d|i", kwlist,
        &jd, &cal))
        return NULL;
    swe_revjul(jd, cal, &year, &month, &day, &hour);
    return Py_BuildValue("(iiif)", year, month, day, hour);
}

/* swisseph.utc_to_jd */
static char pyswe_utc_to_jd__doc__ [] =
"Convert UTC to julian day.\n\n"
"Args: int year, int month, int day, int hour, int minutes, float seconds, int flag\n"
"Return: tuple (float et, float ut)";

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
    if (i < 0)
    {
        PyErr_SetString(pyswe_Error, serr);
        return NULL;
    }
    return Py_BuildValue("dd", dret[0], dret[1]);
}

/* swisseph.jdet_to_utc */
static char pyswe_jdet_to_utc__doc__ [] =
"Convert ET julian day number to UTC.\n\n"
"Args: float et, int flag\n"
"Return: tuple (int year, int month, int day, int hour, int minutes, float seconds)";

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
static char pyswe_jdut1_to_utc__doc__ [] =
"Convert UT julian day number to UTC.\n\n"
"Args: float ut, int flag\n"
"Return: tuple (int year, int month, int day, int hour, int minutes, float seconds)";

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

/* swisseph.utc_time_zone */
static char pyswe_utc_time_zone__doc__[] =
"Transform local time to UTC or UTC to local time.\n\n"
"Args: int year, int month, int day, int hour, int minutes, int seconds, float offset\n"
"Return: tuple (year, month, day, hour, minutes, seconds)";

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
    return Py_BuildValue("(iiiiii)", y2, m2, d2, h2, mi2, s2);
}

/* swisseph.deltat */
static char pyswe_deltat__doc__[] =
"Calculate value of delta T.\n\n"
"Args: float julday\n"
"Return: float";

static PyObject * pyswe_deltat FUNCARGS_KEYWDS
{
    double jd;
    static char *kwlist[] = {"julday", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &jd))
        return NULL;
    return Py_BuildValue("f", swe_deltat(jd));
}

/* swisseph.time_equ */
static char pyswe_time_equ__doc__[] =
"Calculate equation of time (ET).\n\n"
"Args: float julday\n"
"Return: float";

static PyObject * pyswe_time_equ FUNCARGS_KEYWDS
{
    int res;
    double jd, ret;
    char err[256];
    static char *kwlist[] = {"julday", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &jd))
        return NULL;
    res = swe_time_equ(jd, &ret, err);
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("f", ret);
}

/* swisseph.lmt_to_lat */
static char pyswe_lmt_to_lat__doc__[] =
"Translate local mean time (LMT) to local apparent time (LAT).\n\n"
"Args: float julday, float geolon\n"
"Return: float";

static PyObject * pyswe_lmt_to_lat FUNCARGS_KEYWDS
{
    int res;
    double jd, lon, ret;
    char err[256];
    static char *kwlist[] = {"julday", "geolon" , NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dd", kwlist, &jd, &lon))
        return NULL;
    res = swe_lmt_to_lat(jd, lon, &ret, err);
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("f", ret);
}

/* swisseph.lat_to_lmt */
static char pyswe_lat_to_lmt__doc__[] =
"Translate local apparent time (LAT) to local mean time (LMT).\n\n"
"Args: float julday, float geolon\n"
"Return: float";

static PyObject * pyswe_lat_to_lmt FUNCARGS_KEYWDS
{
    int res;
    double jd, lon, ret;
    char err[256];
    static char *kwlist[] = {"julday", "geolon" , NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dd", kwlist, &jd, &lon))
        return NULL;
    res = swe_lat_to_lmt(jd, lon, &ret, err);
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("f", ret);
}

/* swisseph.get_tid_acc */
static char pyswe_get_tid_acc__doc__[] =
"Get tidal acceleration.\n\n"
"Args: -\n"
"Return: float";

static PyObject * pyswe_get_tid_acc FUNCARGS_SELF
{
    return Py_BuildValue("f", swe_get_tid_acc());
}

/* swisseph.set_tid_acc */
static char pyswe_set_tid_acc__doc__[] =
"Set tidal acceleration.\n\n"
"Args: float acc\n"
"Return: None";

static PyObject * pyswe_set_tid_acc FUNCARGS_KEYWDS
{
    double acc;
    static char *kwlist[] = {"acc", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &acc))
        return NULL;
    swe_set_tid_acc(acc);
    Py_RETURN_NONE;
}

/* swisseph.sol_eclipse_when_loc */
static char pyswe_sol_eclipse_when_loc__doc__[] =
"Find the next solar eclipse for a given geographic position (UTC).\n\n"
"Args: float julday, float lon, float lat, float alt=0.0, bool backward=False,"
" int flag=FLG_SWIEPH\n"
"Return: tuples (retflag)(tret)(attr)";

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
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(i)(fffffff)(fffffffffff)", res,
        tret[0],tret[1],tret[2],tret[3],tret[4],tret[5],tret[6],
        attr[0],attr[1],attr[2],attr[3],attr[4],attr[5],attr[6],attr[7],attr[8],
        attr[9],attr[10]);
}

/* swisseph.lun_occult_when_loc */
static char pyswe_lun_occult_when_loc__doc__[] =
"Find next occultation of a body by the moon for a given geographic position (UTC).\n\n"
"Args: float julday, int or str body, float lon, float lat, float alt=0.0,"
" bool backward=False, int flag=FLG_SWIEPH\n"
"Return: tuple of results";

static PyObject * pyswe_lun_occult_when_loc FUNCARGS_KEYWDS
{
    double jd, tret[10], attr[20], geopos[3] = {0.0, 0.0, 0.0};
    int res, plt, backward = 0, flag = SEFLG_SWIEPH;
    char *star = "", err[256];
    PyObject *body;
    static char *kwlist[] = {"julday", "body", "lon", "lat", "alt", "backward", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dOdd|dii", kwlist,
        &jd, &body, &geopos[0], &geopos[1], &geopos[2], &backward, &flag))
        return NULL;
    if (PyLong_CheckExact(body)) /* long -> planet */
    {
        plt = (int) PyLong_AsLong(body);
    }
#if PY_MAJOR_VERSION >= 3
    else if (PyUnicode_CheckExact(body)) /* unicode -> fixed star */
    {
        plt = 0;
        star = (char*) PyUnicode_AS_DATA(body);
    }
#elif PY_MAJOR_VERSION < 3
    else if (PyInt_CheckExact(body)) /* int -> planet */
    {
        plt = (int) PyInt_AsLong(body);
    }
    else if (PyString_CheckExact(body)) /* str -> fixed star */
    {
        plt = 0;
        star = PyString_AsString(body);
    }
#endif
    else
    {
        PyErr_SetString(pyswe_Error, "swisseph.lun_occult_when_loc: Invalid body type");
        return NULL;
    }
    res = swe_lun_occult_when_loc(jd, plt, star, flag, geopos, tret, attr, backward, err);
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(i)(fffffff)(ffffffff)", res,tret[0],tret[1],
        tret[2],tret[3],tret[4],tret[5],tret[6],attr[0],attr[1],attr[2],
        attr[3],attr[4],attr[5],attr[6],attr[7]);
}

/* swisseph.sol_eclipse_when_glob */
static char pyswe_sol_eclipse_when_glob__doc__[] =
"Find the next solar eclipse globally (UTC).\n\n"
"Args: float jd_start, ecl_type=0, bool backward=False, int flag=FLG_SWIEPH\n"
"Return: tuples (retflag)(tret)";

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
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(i)(ffffffffff)", res,tret[0],tret[1],tret[2],tret[3],
        tret[4],tret[5],tret[6],tret[7],tret[8],tret[9]);
}

/* swisseph.lun_occult_when_glob */
static char pyswe_lun_occult_when_glob__doc__[] =
"Find the next occultation of a planet or star by the moon globally (UTC).\n\n"
"Args: float jd_start, int or str body, int ecl_type=0, bool backward=False,"
" int flag=FLG_SWIEPH\n"
"Return: tuple of results";

static PyObject * pyswe_lun_occult_when_glob FUNCARGS_KEYWDS
{
    double jd, tret[10];
    int res, plt, ecltype = 0, backward = 0, flag = SEFLG_SWIEPH;
    char *star = "", err[256];
    PyObject *body;
    static char *kwlist[] = {"jd_start", "body", "ecl_type", "backward", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dO|iii", kwlist,
        &jd, &body, &ecltype, &backward, &flag))
        return NULL;
    if (PyLong_CheckExact(body)) /* long -> planet */
    {
        plt = (int) PyLong_AsLong(body);
    }
#if PY_MAJOR_VERSION >= 3
    else if (PyUnicode_CheckExact(body)) /* unicode -> fixed star */
    {
        plt = 0;
        star = (char*) PyUnicode_AS_DATA(body);
    }
#elif PY_MAJOR_VERSION < 3
    else if (PyInt_CheckExact(body)) /* int -> planet */
    {
        plt = (int) PyInt_AsLong(body);
    }
    else if (PyString_CheckExact(body)) /* str -> fixed star */
    {
        plt = 0;
        star = PyString_AsString(body);
    }
#endif
    else
    {
        PyErr_SetString(pyswe_Error, "swisseph.lun_occult_when_glob: Invalid body type");
        return NULL;
    }
    res = swe_lun_occult_when_glob(jd, plt, star, flag, ecltype, tret, backward, err);
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(i)(ffffffffff)", res,tret[0],tret[1],tret[2],
        tret[3],tret[4],tret[5],tret[6],tret[7],tret[8],tret[9]);
}

/* swisseph.sol_eclipse_how */
static char pyswe_sol_eclipse_how__doc__[] =
"Calculate attributes of a solar eclipse.\n\n"
"Args: float julday, float lon, float lat, float alt=0.0, int flag=FLG_SWIEPH\n"
"Return: tuples (retflag)(attr)";

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
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(i)(fffffffffff)", res,attr[0],attr[1],attr[2],attr[3],
        attr[4],attr[5],attr[6],attr[7],attr[8],attr[9],attr[10]);
}

/* swisseph.sol_eclipse_where */
static char pyswe_sol_eclipse_where__doc__[] =
"Find where a solar eclipse is central or maximal (UTC).\n\n"
"Args: float julday, int flag=FLG_SWIEPH\n"
"Return: tuples (retval)(geopos)(attr)";

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
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(i)(ffffffffff)(fffffffffff)", res,geopos[0],geopos[1],
        geopos[2],geopos[3],geopos[4],geopos[5],geopos[6],geopos[7],geopos[8],
        geopos[9],attr[0],attr[1],attr[2],attr[3],attr[4],attr[5],attr[6],
        attr[7],attr[8],attr[9],attr[10]);
}

/* swisseph.lun_occult_where */
static char pyswe_lun_occult_where__doc__[] =
"Find where a lunar occultation is central or maximal (UTC).\n\n"
"Args: float julday, int or str body, int flag=FLG_SWIEPH\n"
"Return: tuples (retval)(geopos)(attr)";

static PyObject * pyswe_lun_occult_where FUNCARGS_KEYWDS
{
    double jd, geopos[10] = {0,0,0,0,0,0,0,0,0,0};
    double attr[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int res, plt, flag = SEFLG_SWIEPH;
    char *star = "", err[256];
    PyObject *body;
    static char *kwlist[] = {"julday", "body", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dO|i", kwlist,
        &jd, &body, &flag))
        return NULL;
    if (PyLong_CheckExact(body)) /* long -> planet */
    {
        plt = (int) PyLong_AsLong(body);
    }
#if PY_MAJOR_VERSION >= 3
    else if (PyUnicode_CheckExact(body)) /* unicode -> fixed star */
    {
        plt = 0;
        star = (char*) PyUnicode_AS_DATA(body);
    }
#elif PY_MAJOR_VERSION < 3
    else if (PyInt_CheckExact(body)) /* int -> planet */
    {
        plt = (int) PyInt_AsLong(body);
    }
    else if (PyString_CheckExact(body)) /* str -> fixed star */
    {
        plt = 0;
        star = PyString_AsString(body);
    }
#endif
    else
    {
        PyErr_SetString(pyswe_Error, "swisseph.lun_occult_where: Invalid body type");
        return NULL;
    }
    res = swe_lun_occult_where(jd, plt, star, flag, geopos, attr, err);
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(i)(ffffffffff)(ffffffff)", res,geopos[0],geopos[1],
        geopos[2],geopos[3],geopos[4],geopos[5],geopos[6],geopos[7],geopos[8],
        geopos[9],attr[0],attr[1],attr[2],attr[3],attr[4],attr[5],attr[6],attr[7]);
}

/* swisseph.lun_eclipse_how */
static char pyswe_lun_eclipse_how__doc__[] =
"Calculate attributes of a lunar eclipse (UTC).\n\n"
"Args: float julday, float lon, float lat, float alt=0.0, int flag=FLG_SWIEPH\n"
"Return: tuples (retflag)(attr)";

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
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(i)(fffffffffff)", res,attr[0],attr[1],attr[2],attr[3],
        attr[4],attr[5],attr[6],attr[7],attr[8],attr[9],attr[10]);
}

/* swisseph.lun_eclipse_when */
static char pyswe_lun_eclipse_when__doc__[] =
"Find the next lunar eclipse (UTC).\n\n"
"Args: float jd_start, int ecl_type=0, bool backward=False, int flag=FLG_SWIEPH\n"
"Return: tuples (retflag)(tret)";

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
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(i)(ffffffff)", res,tret[0],tret[1],tret[2],tret[3],
        tret[4],tret[5],tret[6],tret[7]);
}

/* swisseph.lun_eclipse_when_loc */
static char pyswe_lun_eclipse_when_loc__doc__[] =
"Find the next lunar eclipse observable from a given geographic position.\n\n"
"Args: float jd_start, float lon, float lat, float alt=0.0, bool backward=False,"
" int flag=FLG_SWIEPH\n"
"Return: 3 tuples (retflag, tret, attr)";

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
    if ( res < 0 )
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(i)(dddddddddd)(dddddddddd)", res,tret[0],tret[1],
        tret[2],tret[3],tret[4],tret[5],tret[6],tret[7],tret[8],tret[9],
        attr[0],attr[1],attr[2],attr[3],attr[4],attr[5],attr[6],attr[7],
        attr[8],attr[9]);
}

/* swisseph.rise_trans */
static char pyswe_rise_trans__doc__[] =
"Calculate times of rising, setting and meridian transits.\n\n"
"Args: float jd_start, int or str body, float lon, float lat, float alt=0.0,"
" float press=0.0, float temp=0.0, int rsmi=0, int flag=FLG_SWIEPH\n"
"Return: tuple of results";

static PyObject * pyswe_rise_trans FUNCARGS_KEYWDS
{
    double jd, tret[10], press = 0.0, temp = 0.0, geopos[3] = {0.0, 0.0, 0.0};
    int res, plt, rsmi = 0, flag = SEFLG_SWIEPH;
    char *star = "", err[256];
    PyObject *body;
    static char *kwlist[] = {"jd_start", "body", "lon", "lat", "alt", "press",
        "temp", "rsmi", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dOdd|dddii", kwlist,
        &jd, &body, &geopos[0], &geopos[1], &geopos[2], &press, &temp, &rsmi, &flag))
        return NULL;
    if (PyLong_CheckExact(body)) /* long -> planet */
    {
        plt = (int) PyLong_AsLong(body);
    }
#if PY_MAJOR_VERSION >= 3
    else if (PyUnicode_CheckExact(body)) /* unicode -> fixed star */
    {
        plt = 0;
        star = (char*) PyUnicode_AS_DATA(body);
    }
#elif PY_MAJOR_VERSION < 3
    else if (PyInt_CheckExact(body)) /* int -> planet */
    {
        plt = (int) PyInt_AsLong(body);
    }
    else if (PyString_CheckExact(body)) /* str -> fixed star */
    {
        plt = 0;
        star = PyString_AsString(body);
    }
#endif
    else
    {
        PyErr_SetString(pyswe_Error, "swisseph.rise_trans: Invalid body type");
        return NULL;
    }
    res = swe_rise_trans(jd, plt, star, flag, rsmi, geopos, press, temp, tret, err);
    if (res == -1)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(i)(ffffffffff)", res,tret[0],tret[1],tret[2],
        tret[3],tret[4],tret[5],tret[6],tret[7],tret[8],tret[9]);
}

/* swisseph.pheno */
static char pyswe_pheno__doc__[] =
"Calculate planetary phenomena (ET).\n\n"
"Args: float julday, int planet, int flag=FLG_SWIEPH\n"
"Return: tuple of results";

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
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(fffff)", attr[0],attr[1],attr[2],attr[3],attr[4]);
}

/* swisseph.pheno_ut */
static char pyswe_pheno_ut__doc__[] =
"Calculate planetary phenomena (UTC).\n\n"
"Args: float julday, int planet, int flag=FLG_SWIEPH\n"
"Return: tuple of results";

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
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(fffff)", attr[0],attr[1],attr[2],attr[3],attr[4]);
}

/* swisseph.refrac */
static char pyswe_refrac__doc__[] =
"Calculate either true altitude from apparent altitude, or apparent altitude"
" from true altitude.\n\n"
"Args: float alt, float press=0.0, float temp=0.0, int flag=TRUE_TO_APP\n"
"Return: float";

static PyObject * pyswe_refrac FUNCARGS_KEYWDS
{
    double alt, press = 0.0, temp = 0.0;
    int flag = SE_TRUE_TO_APP;
    static char *kwlist[] = {"alt", "press", "temp", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d|ddi", kwlist,
        &alt, &press, &temp, &flag))
        return NULL;
    return Py_BuildValue("f", swe_refrac(alt, press, temp, flag));
}

/* swisseph.refrac_extended */
static char pyswe_refrac_extended__doc__[] =
"Calculate either true altitude from apparent altitude, or apparent altitude"
" from true altitude, for geographical altitudes above sea level.\n\n"
"Args: float alt, float geoalt, float lrate, float press=0.0, float temp=0.0,"
" int flag=TRUE_TO_APP\n"
"Return: 2 tuples of 1 and 4 float";

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
    return Py_BuildValue("(f)(ffff)", ret, dret[0], dret[1], dret[2], dret[3]);
}

/* swisseph.set_lapse_rate */
static char pyswe_set_lapse_rate__doc__[] =
"Set lapse rate.\n\nArgs: float lrate\nReturn: None";

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

/* swisseph.azalt */
static char pyswe_azalt__doc__[] =
"Calculate horizontal coordinates (azimuth and altitude) of a planet or a star"
" from either ecliptical or equatorial coordinates (UTC).\n\n"
"Args: float julday, float lon, float lat, float hei, float x, float y,"
" float z=0.0, float press=0.0, float temp=0.0, int flag=ECL2HOR\n"
"Return: tuple of 3 float (azimuth, true altitude, apparent altitude)";

static PyObject * pyswe_azalt FUNCARGS_KEYWDS
{
    double jd, geo[3], xin[3], press = 0.0, temp = 0.0, xaz[3];
    int flag = SE_ECL2HOR;
    static char *kwlist[] = {"julday", "lon", "lat", "hei",
        "x", "y", "z", "press", "temp", "flag", NULL};
    xin[2] = 0.0;
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dddddd|dddi", kwlist,
        &jd, &geo[0], &geo[1], &geo[2], &xin[0], &xin[1], &xin[2], &press,
        &temp, &flag))
        return NULL;
    swe_azalt(jd, flag, geo, press, temp, xin, xaz);
    return Py_BuildValue("(fff)", xaz[0], xaz[1], xaz[2]);
};

/* swisseph.azalt_rev */
static char pyswe_azalt_rev__doc__[] =
"Calculate either ecliptical or equatorial coordinates from azimuth and true"
" altitude.\n\n"
"Args: float julday, float lon, float lat, float hei, double azim, double alt,"
" int flag=HOR2ECL\n"
"Return: tuple of 2 float";

static PyObject * pyswe_azalt_rev FUNCARGS_KEYWDS
{
    double jd, geo[3], xin[2], xout[2];
    int flag = SE_HOR2ECL;
    static char *kwlist[] = {"julday", "lon", "lat", "hei",
        "azim", "alt", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dddddd|i", kwlist,
        &jd, &geo[0], &geo[1], &geo[2], &xin[0], &xin[1], &flag))
        return NULL;
    swe_azalt_rev(jd, flag, geo, xin, xout);
    return Py_BuildValue("(ff)", xout[0], xout[1]);
}

/* *** Auxiliary functions *** */

/* swisseph.cotrans */
static char pyswe_cotrans__doc__[] =
"Coordinate transformation from ecliptic to equator or vice-versa.\n\n"
"Args: float lon, float lat, float dist, float obliquity\n"
"Return: tuple of 3 float (longitude, latitude, distance)";

static PyObject * pyswe_cotrans FUNCARGS_KEYWDS
{
    double xpo[3], xpn[3], eps;
    static char *kwlist[] = {"lon", "lat", "dist", "obliquity", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dddd", kwlist,
        &xpo[0], &xpo[1], &xpo[2], &eps))
        return NULL;
    swe_cotrans(xpo, xpn, eps);
    return Py_BuildValue("(fff)", xpn[0], xpn[1], xpn[2]);
}

/* swisseph.cotrans_sp */
static char pyswe_cotrans_sp__doc__[] =
"Coordinate transformation of position and speed, from ecliptic to equator"
" or vice-versa.\n\n"
"Args: float lon, float lat, float dist, float lonspeed, float latspeed,"
" float distspeed, float obliquity\n"
"Return: tuple of 6 float";

static PyObject * pyswe_cotrans_sp FUNCARGS_KEYWDS
{
    double xpo[6], xpn[6], eps;
    static char *kwlist[] = {"lon", "lat", "dist", "lonspeed",
        "latspeed", "distspeed", "obliquity", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ddddddd", kwlist,
        &xpo[0], &xpo[1], &xpo[2], &xpo[3], &xpo[4], &xpo[5], &eps))
        return NULL;
    swe_cotrans(xpo, xpn, eps);
    return Py_BuildValue("(ffffff)", xpn[0], xpn[1], xpn[2], xpn[3],
        xpn[4], xpn[5]);
}

/* swisseph.degnorm */
static char pyswe_degnorm__doc__[] =
"Normalization of any degree number to the range [0;360].\n\n"
"Args: float x\n"
"Return: float";

static PyObject * pyswe_degnorm FUNCARGS_KEYWDS
{
    double x;
    static char *kwlist[] = {"x", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &x))
        return NULL;
    return Py_BuildValue("f", swe_degnorm(x));
}

/* swisseph.csnorm */
static char pyswe_csnorm__doc__[] =
"Normalization of any centisecond number to the range [0;360].\n\n"
"Args: int x\n"
"Return: int";

static PyObject * pyswe_csnorm FUNCARGS_KEYWDS
{
    int x;
    static char *kwlist[] = {"x", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i", kwlist, &x))
        return NULL;
    return Py_BuildValue("i", swe_csnorm(x));
}

/* swisseph.radnorm */
static char pyswe_radnorm__doc__[] =
"Normalization of any radian number to the range [0;2*pi].\n\n"
"Args: float x\n"
"Return: float";

static PyObject * pyswe_radnorm FUNCARGS_KEYWDS
{
    double x;
    static char *kwlist[] = {"x", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &x))
        return NULL;
    return Py_BuildValue("f", swe_radnorm(x));
}

/* swisseph.rad_midp */
static char pyswe_rad_midp__doc__[] =
"Calculate midpoint (in radians).\n\n"
"Args: float x, float y\n"
"Return: float";

static PyObject * pyswe_rad_midp FUNCARGS_KEYWDS
{
    double x, y;
    static char *kwlist[] = {"x", "y", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dd", kwlist, &x, &y))
        return NULL;
    return Py_BuildValue("f", swe_rad_midp(x, y));
}

/* swisseph.deg_midp */
static char pyswe_deg_midp__doc__[] =
"Calculate midpoint (in degrees).\n\n"
"Args: float x, float y\n"
"Return: float";

static PyObject * pyswe_deg_midp FUNCARGS_KEYWDS
{
    double x, y;
    static char *kwlist[] = {"x", "y", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dd", kwlist, &x, &y))
        return NULL;
    return Py_BuildValue("f", swe_deg_midp(x, y));
}

/* swisseph.split_deg */
static char pyswe_split_deg__doc__[] =
"Split centiseconds in degrees, minutes, seconds, fraction of seconds, zodiac sign number.\n\n"
"Args: float ddeg, int roundflag\n"
"Return: tuple";

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

/* swisseph.difcsn */
static char pyswe_difcsn__doc__[] =
"Calculate distance in centisecs p1 - p2.\n\n"
"Args: int p1, int p2\n"
"Return: int";

static PyObject * pyswe_difcsn FUNCARGS_KEYWDS
{
    int p1, p2;
    static char *kwlist[] = {"p1", "p2", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ii", kwlist, &p1, &p2))
        return NULL;
    return Py_BuildValue("i", swe_difcsn(p1, p2));
}

/* swisseph.difdegn */
static char pyswe_difdegn__doc__[] =
"Calculate distance in degrees p1 - p2.\n\n"
"Args: float p1, float p2\n"
"Return: float";

static PyObject * pyswe_difdegn FUNCARGS_KEYWDS
{
    double p1, p2;
    static char *kwlist[] = {"p1", "p2", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dd", kwlist, &p1, &p2))
        return NULL;
    return Py_BuildValue("f", swe_difdegn(p1, p2));
}

/* swisseph.difcs2n */
static char pyswe_difcs2n__doc__[] =
"Calculate distance in centisecs p1 - p2 normalized to [-180;180].\n\n"
"Args: int p1, int p2\n"
"Return: int";

static PyObject * pyswe_difcs2n FUNCARGS_KEYWDS
{
    int p1, p2;
    static char *kwlist[] = {"p1", "p2", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ii", kwlist, &p1, &p2))
        return NULL;
    return Py_BuildValue("i", swe_difcs2n(p1, p2));
}

/* swisseph.difdeg2n */
static char pyswe_difdeg2n__doc__[] =
"Calculate distance in degrees p1 - p2 normalized to [-180;180].\n\n"
"Args: float p1, float p2\n"
"Return: float";

static PyObject * pyswe_difdeg2n FUNCARGS_KEYWDS
{
    double p1, p2;
    static char *kwlist[] = {"p1", "p2", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dd", kwlist, &p1, &p2))
        return NULL;
    return Py_BuildValue("f", swe_difdeg2n(p1, p2));
}

/* swisseph.difrad2n */
static char pyswe_difrad2n__doc__[] =
"Calculate distance in radians p1 - p2 normalized to [-180;180].\n\n"
"Args: float p1, float p2\n"
"Return: float";

static PyObject * pyswe_difrad2n FUNCARGS_KEYWDS
{
    double p1, p2;
    static char *kwlist[] = {"p1", "p2", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dd", kwlist, &p1, &p2))
        return NULL;
    return Py_BuildValue("f", swe_difrad2n(p1, p2));
}

/* swisseph.csroundsec */
static char pyswe_csroundsec__doc__[] =
"Round centiseconds, but at 29.5959 always down.\n\n"
"Args: int x\n"
"Return: int";

static PyObject * pyswe_csroundsec FUNCARGS_KEYWDS
{
    int x;
    static char *kwlist[] = {"x", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i", kwlist, &x))
        return NULL;
    return Py_BuildValue("i", swe_csroundsec(x));
}

/* swisseph.d2l */
static char pyswe_d2l__doc__[] =
"Double to integer with rounding, no overflow check.\n\n"
"Args: float x\n"
"Return: int";

static PyObject * pyswe_d2l FUNCARGS_KEYWDS
{
    double x;
    static char *kwlist[] = {"x", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &x))
        return NULL;
    return Py_BuildValue("i", swe_d2l(x));
}

/* swisseph.day_of_week */
static char pyswe_day_of_week__doc__[] =
"Calculate day of week number [0;6] from julian day number.\n\n"
"Args: float julday\n"
"Return: int";

static PyObject * pyswe_day_of_week FUNCARGS_KEYWDS
{
    double jd;
    static char *kwlist[] = {"julday", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &jd))
        return NULL;
    return Py_BuildValue("i", swe_day_of_week(jd));
}

/* swisseph.cs2timestr */
static char pyswe_cs2timestr__doc__[] =
"Get time string from centiseconds.\n\n"
"Args: int cs, char sep, bool suppresszero=True\n"
"Return: str";

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

/* swisseph.cs2lonlatstr */
static char pyswe_cs2lonlatstr__doc__[] =
"Get longitude or latitude string from centiseconds.\n\n"
"Args: int cs, char plus, char minus\n"
"Return: str";

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

/* swisseph.cs2degstr */
static char pyswe_cs2degstr__doc__[] =
"Get degrees string from centiseconds.\n\n"
"Args: int cs\n"
"Return: str";

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

/* swisseph.fixstar_mag */
static char pyswe_fixstar_mag__doc__ [] =
"Get fixed star magnitude.\n\n"
"Args: str star\n"
"Return: float";

static PyObject * pyswe_fixstar_mag FUNCARGS_KEYWDS
{
    char *star, st[41], err[256];
    int ret;
    double mag;
    static char *kwlist[] = {"star", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "s", kwlist, &star))
        return NULL;
    strcpy( st, star );
    ret = swe_fixstar_mag(st, &mag, err);
    if (ret < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("f", mag);
}

/* swisseph.heliacal_ut */
static char pyswe_heliacal_ut__doc__ [] =
"Find the Julian day of the next heliacal phenomenon after a given start date.\n"
"It works between geographic latitudes 60s - 60n.\n\n"
"Args: float jd_start, seq geopos, seq atmo, seq observer, str object,"
" int enventtype, int helflag\n"
"Return: tuple with 3 julian days";

static PyObject * pyswe_heliacal_ut FUNCARGS_KEYWDS
{
    double jdstart, geopos[3], atmo[4], observ[6], dret[3];
    char serr[255], *obj = 0; /* dummy assign */
    int i, evnt, flg;
    PyObject *o1=0, *o2=0, *o3=0, *o4, *o5, *o6, *o7, *o8, *o9;
    static char *kwlist[] = {"jd_start", "geopos", "atmo", "observer", "object",
        "eventtype", "helflag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dOOOsii", kwlist,
        &jdstart, o1, o2, o3, obj, &evnt, &flg))
        return NULL;

    if (!PySequence_Check(o1) || PySequence_Length(o1) != 3)
    {
        PyErr_SetString(pyswe_Error, "Invalid geopos sequence");
        return NULL;
    }
    else
    {
        o4 = PySequence_ITEM(o1, 0);
        o5 = PySequence_ITEM(o1, 1);
        o6 = PySequence_ITEM(o1, 2);
        if (!PyNumber_Check(o4) || !PyNumber_Check(o5) || !PyNumber_Check(o6))
        {
            PyErr_SetString(pyswe_Error, "Invalid geopos value type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
            return NULL;
        }

        /* checking longitude */
        if (PyFloat_Check(o4))
        {
            geopos[0] = PyFloat_AsDouble(o4);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
        {
            geopos[0] = (double) PyInt_AsLong(o4);
        }
#endif
        else if (PyLong_Check(o4))
        {
            geopos[0] = (double) PyLong_AsLong(o4);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid longitude type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
            return NULL;
        }

        /* checking latitude */
        if (PyFloat_Check(o5))
        {
            geopos[1] = PyFloat_AsDouble(o5);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
        {
            geopos[1] = (double) PyInt_AsLong(o5);
        }
#endif
        else if (PyLong_Check(o5))
        {
            geopos[1] = (double) PyLong_AsLong(o5);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid latitude type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
            return NULL;
        }

        /* checking altitude */
        if (PyFloat_Check(o6))
        {
            geopos[2] = PyFloat_AsDouble(o6);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
        {
            geopos[2] = (double) PyInt_AsLong(o6);
        }
#endif
        else if (PyLong_Check(o6))
        {
            geopos[2] = (double) PyLong_AsLong(o6);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid altitude type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
            return NULL;
        }

        Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
    }

    if (!PySequence_Check(o2) || PySequence_Length(o2) != 4)
    {
        PyErr_SetString(pyswe_Error, "Invalid atmospheric sequence");
        return NULL;
    }
    else
    {
        o4 = PySequence_ITEM(o2, 0);
        o5 = PySequence_ITEM(o2, 1);
        o6 = PySequence_ITEM(o2, 2);
        o7 = PySequence_ITEM(o2, 3);
        if (!PyNumber_Check(o4) || !PyNumber_Check(o5) || !PyNumber_Check(o6)
            || !PyNumber_Check(o7))
        {
            PyErr_SetString(pyswe_Error, "Invalid atmospheric value type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }

        /* atmospheric pressure */
        if (PyFloat_Check(o4))
        {
            atmo[0] = PyFloat_AsDouble(o4);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o4))
        {
            atmo[0] = (double) PyInt_AsLong(o4);
        }
#endif
        else if (PyLong_Check(o4))
        {
            atmo[0] = (double) PyLong_AsLong(o4);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid atmospheric pressure");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }

        /* atmospheric temperature */
        if (PyFloat_Check(o5))
        {
            atmo[1] = PyFloat_AsDouble(o5);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
        {
            atmo[1] = (double) PyInt_AsLong(o5);
        }
#endif
        else if (PyLong_Check(o5))
        {
            atmo[1] = (double) PyLong_AsLong(o5);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid atmospheric temperature");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }

        /* humidity */
        if (PyFloat_Check(o6))
        {
            atmo[2] = PyFloat_AsDouble(o6);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o6))
        {
            atmo[2] = (double) PyInt_AsLong(o6);
        }
#endif
        else if (PyLong_Check(o6))
        {
            atmo[2] = (double) PyLong_AsLong(o6);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid humidity");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }

        /* meteorological range */
        if (PyFloat_Check(o7))
        {
            atmo[3] = PyFloat_AsDouble(o7);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o7))
        {
            atmo[3] = (double) PyInt_AsLong(o7);
        }
#endif
        else if (PyLong_Check(o7))
        {
            atmo[3] = (double) PyLong_AsLong(o7);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid meteorological range");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }

        Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
    }

    if (!PySequence_Check(o3) || PySequence_Length(o3) != 6)
    {
        PyErr_SetString(pyswe_Error, "Invalid observer sequence");
        return NULL;
    }
    else
    {
        o4 = PySequence_ITEM(o3, 0);
        o5 = PySequence_ITEM(o3, 1);
        o6 = PySequence_ITEM(o3, 2);
        o7 = PySequence_ITEM(o3, 3);
        o8 = PySequence_ITEM(o3, 4);
        o9 = PySequence_ITEM(o3, 5);
        if (!PyNumber_Check(o4) || !PyNumber_Check(o5) || !PyNumber_Check(o6)
            || !PyNumber_Check(o7) || !PyNumber_Check(o8) || !PyNumber_Check(o9))
        {
            PyErr_SetString(pyswe_Error, "Invalid observer value type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }

        /* observer age */
        if (PyFloat_Check(o4))
        {
            observ[0] = PyFloat_AsDouble(o4);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o4))
        {
            observ[0] = (double) PyInt_AsLong(o4);
        }
#endif
        else if (PyLong_Check(o4))
        {
            observ[0] = (double) PyLong_AsLong(o4);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid observer age");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }

        /* snellen ratio */
        if (PyFloat_Check(o5))
        {
            observ[1] = PyFloat_AsDouble(o5);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
        {
            observ[1] = (double) PyInt_AsLong(o5);
        }
#endif
        else if (PyLong_Check(o5))
        {
            observ[1] = (double) PyLong_AsLong(o5);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid snellen ratio");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }

        /* mono/binocular */
        if (PyFloat_Check(o6))
        {
            observ[2] = PyFloat_AsDouble(o6);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o6))
        {
            observ[2] = (double) PyInt_AsLong(o6);
        }
#endif
        else if (PyLong_Check(o6))
        {
            observ[2] = (double) PyLong_AsLong(o6);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid telescope");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }

        /* telescope magnification */
        if (PyFloat_Check(o7))
        {
            observ[3] = PyFloat_AsDouble(o7);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o7))
        {
            observ[3] = (double) PyInt_AsLong(o7);
        }
#endif
        else if (PyLong_Check(o7))
        {
            observ[3] = (double) PyLong_AsLong(o7);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid telescope magnification");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }

        /* optical aperture */
        if (PyFloat_Check(o8))
        {
            observ[4] = PyFloat_AsDouble(o8);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o8))
        {
            observ[4] = (double) PyInt_AsLong(o8);
        }
#endif
        else if (PyLong_Check(o8))
        {
            observ[4] = (double) PyLong_AsLong(o8);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid telescope aperture");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }

        /* optical transmission */
        if (PyFloat_Check(o9))
        {
            observ[5] = PyFloat_AsDouble(o9);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o9))
        {
            observ[5] = (double) PyInt_AsLong(o9);
        }
#endif
        else if (PyLong_Check(o9))
        {
            observ[5] = (double) PyLong_AsLong(o9);
        }
        else
        {
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
    {
        return Py_BuildValue("ddd", dret[0], dret[1], dret[2]);
    }
    else
    {
        PyErr_SetString(pyswe_Error, serr);
        return NULL;
    }
}

/* swisseph.heliacal_pheno_ut */ /* TODO? this is 99% copy of above function */
static char pyswe_heliacal_pheno_ut__doc__ [] =
"Find the Julian day of the next heliacal phenomenon after a given start date.\n"
"It works between geographic latitudes 60s - 60n.\n\n"
"Args: float jd_start, seq geopos, seq atmo, seq observer, str object, int enventtype, int helflag\n"
"Return: tuple with 3 julian days";

static PyObject * pyswe_heliacal_pheno_ut FUNCARGS_KEYWDS
{
    double jdstart, geopos[3], atmo[4], observ[6], dret[3];
    char serr[255], *obj = 0; /* dummy assign */
    int i, evnt, flg;
    PyObject *o1=0, *o2=0, *o3=0, *o4, *o5, *o6, *o7, *o8, *o9;
    static char *kwlist[] = {"jd_start", "geopos", "atmo", "observer", "object",
        "eventtype", "helflag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dOOOsii", kwlist,
        &jdstart, o1, o2, o3, obj, &evnt, &flg))
        return NULL;

    if (!PySequence_Check(o1) || PySequence_Length(o1) != 3)
    {
        PyErr_SetString(pyswe_Error, "Invalid geopos sequence");
        return NULL;
    }
    else
    {
        o4 = PySequence_ITEM(o1, 0);
        o5 = PySequence_ITEM(o1, 1);
        o6 = PySequence_ITEM(o1, 2);
        if (!PyNumber_Check(o4) || !PyNumber_Check(o5) || !PyNumber_Check(o6))
        {
            PyErr_SetString(pyswe_Error, "Invalid geopos value type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
            return NULL;
        }

        /* checking longitude */
        if (PyFloat_Check(o4))
        {
            geopos[0] = PyFloat_AsDouble(o4);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
        {
            geopos[0] = (double) PyInt_AsLong(o4);
        }
#endif
        else if (PyLong_Check(o4))
        {
            geopos[0] = (double) PyLong_AsLong(o4);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid longitude type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
            return NULL;
        }

        /* checking latitude */
        if (PyFloat_Check(o5))
        {
            geopos[1] = PyFloat_AsDouble(o5);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
        {
            geopos[1] = (double) PyInt_AsLong(o5);
        }
#endif
        else if (PyLong_Check(o5))
        {
            geopos[1] = (double) PyLong_AsLong(o5);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid latitude type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
            return NULL;
        }

        /* checking altitude */
        if (PyFloat_Check(o6))
        {
            geopos[2] = PyFloat_AsDouble(o6);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
        {
            geopos[2] = (double) PyInt_AsLong(o6);
        }
#endif
        else if (PyLong_Check(o6))
        {
            geopos[2] = (double) PyLong_AsLong(o6);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid altitude type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
            return NULL;
        }

        Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
    }

    if (!PySequence_Check(o2) || PySequence_Length(o2) != 4)
    {
        PyErr_SetString(pyswe_Error, "Invalid atmospheric sequence");
        return NULL;
    }
    else
    {
        o4 = PySequence_ITEM(o2, 0);
        o5 = PySequence_ITEM(o2, 1);
        o6 = PySequence_ITEM(o2, 2);
        o7 = PySequence_ITEM(o2, 3);
        if (!PyNumber_Check(o4) || !PyNumber_Check(o5) || !PyNumber_Check(o6)
            || !PyNumber_Check(o7))
        {
            PyErr_SetString(pyswe_Error, "Invalid atmospheric value type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }

        /* atmospheric pressure */
        if (PyFloat_Check(o4))
        {
            atmo[0] = PyFloat_AsDouble(o4);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o4))
        {
            atmo[0] = (double) PyInt_AsLong(o4);
        }
#endif
        else if (PyLong_Check(o4))
        {
            atmo[0] = (double) PyLong_AsLong(o4);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid atmospheric pressure");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }

        /* atmospheric temperature */
        if (PyFloat_Check(o5))
        {
            atmo[1] = PyFloat_AsDouble(o5);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
        {
            atmo[1] = (double) PyInt_AsLong(o5);
        }
#endif
        else if (PyLong_Check(o5))
        {
            atmo[1] = (double) PyLong_AsLong(o5);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid atmospheric temperature");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }

        /* humidity */
        if (PyFloat_Check(o6))
        {
            atmo[2] = PyFloat_AsDouble(o6);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o6))
        {
            atmo[2] = (double) PyInt_AsLong(o6);
        }
#endif
        else if (PyLong_Check(o6))
        {
            atmo[2] = (double) PyLong_AsLong(o6);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid humidity");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }

        /* meteorological range */
        if (PyFloat_Check(o7))
        {
            atmo[3] = PyFloat_AsDouble(o7);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o7))
        {
            atmo[3] = (double) PyInt_AsLong(o7);
        }
#endif
        else if (PyLong_Check(o7))
        {
            atmo[3] = (double) PyLong_AsLong(o7);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid meteorological range");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }

        Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
    }

    if (!PySequence_Check(o3) || PySequence_Length(o3) != 6)
    {
        PyErr_SetString(pyswe_Error, "Invalid observer sequence");
        return NULL;
    }
    else
    {
        o4 = PySequence_ITEM(o3, 0);
        o5 = PySequence_ITEM(o3, 1);
        o6 = PySequence_ITEM(o3, 2);
        o7 = PySequence_ITEM(o3, 3);
        o8 = PySequence_ITEM(o3, 4);
        o9 = PySequence_ITEM(o3, 5);
        if (!PyNumber_Check(o4) || !PyNumber_Check(o5) || !PyNumber_Check(o6)
            || !PyNumber_Check(o7) || !PyNumber_Check(o8) || !PyNumber_Check(o9))
        {
            PyErr_SetString(pyswe_Error, "Invalid observer value type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }

        /* observer age */
        if (PyFloat_Check(o4))
        {
            observ[0] = PyFloat_AsDouble(o4);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o4))
        {
            observ[0] = (double) PyInt_AsLong(o4);
        }
#endif
        else if (PyLong_Check(o4))
        {
            observ[0] = (double) PyLong_AsLong(o4);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid observer age");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }

        /* snellen ratio */
        if (PyFloat_Check(o5))
        {
            observ[1] = PyFloat_AsDouble(o5);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
        {
            observ[1] = (double) PyInt_AsLong(o5);
        }
#endif
        else if (PyLong_Check(o5))
        {
            observ[1] = (double) PyLong_AsLong(o5);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid snellen ratio");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }

        /* mono/binocular */
        if (PyFloat_Check(o6))
        {
            observ[2] = PyFloat_AsDouble(o6);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o6))
        {
            observ[2] = (double) PyInt_AsLong(o6);
        }
#endif
        else if (PyLong_Check(o6))
        {
            observ[2] = (double) PyLong_AsLong(o6);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid telescope");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }

        /* telescope magnification */
        if (PyFloat_Check(o7))
        {
            observ[3] = PyFloat_AsDouble(o7);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o7))
        {
            observ[3] = (double) PyInt_AsLong(o7);
        }
#endif
        else if (PyLong_Check(o7))
        {
            observ[3] = (double) PyLong_AsLong(o7);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid telescope magnification");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }

        /* optical aperture */
        if (PyFloat_Check(o8))
        {
            observ[4] = PyFloat_AsDouble(o8);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o8))
        {
            observ[4] = (double) PyInt_AsLong(o8);
        }
#endif
        else if (PyLong_Check(o8))
        {
            observ[4] = (double) PyLong_AsLong(o8);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid telescope aperture");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }

        /* optical transmission */
        if (PyFloat_Check(o9))
        {
            observ[5] = PyFloat_AsDouble(o9);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o9))
        {
            observ[5] = (double) PyInt_AsLong(o9);
        }
#endif
        else if (PyLong_Check(o9))
        {
            observ[5] = (double) PyLong_AsLong(o9);
        }
        else
        {
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
    {
        return Py_BuildValue("ddd", dret[0], dret[1], dret[2]);
    }
    else
    {
        PyErr_SetString(pyswe_Error, serr);
        return NULL;
    }
}

/* swisseph.vis_limit_mag */
static char pyswe_vis_limit_mag__doc__ [] =
"Find the limiting visual magnitude in dark skies.\n\n"
"Args: float jd, seq geopos, seq atmo, seq observer, str object, int helflag\n"
"Return: tuple (float res, float magnitude)";

static PyObject * pyswe_vis_limit_mag FUNCARGS_KEYWDS
{
    double jd, geopos[3], atmo[4], observ[6], dres, dret;
    char serr[255], *obj = 0;
    int flg;
    PyObject *o1=0, *o2=0, *o3=0, *o4, *o5, *o6, *o7, *o8, *o9;
    static char *kwlist[] = {"jd", "geopos", "atmo", "observer", "object",
        "helflag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dOOOsi", kwlist,
        &jd, o1, o2, o3, obj, &flg))
        return NULL;

    if (!PySequence_Check(o1) || PySequence_Length(o1) != 3)
    {
        PyErr_SetString(pyswe_Error, "Invalid geopos sequence");
        return NULL;
    }
    else
    {
        o4 = PySequence_ITEM(o1, 0);
        o5 = PySequence_ITEM(o1, 1);
        o6 = PySequence_ITEM(o1, 2);
        if (!PyNumber_Check(o4) || !PyNumber_Check(o5) || !PyNumber_Check(o6))
        {
            PyErr_SetString(pyswe_Error, "Invalid geopos value type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
            return NULL;
        }

        /* checking longitude */
        if (PyFloat_Check(o4))
        {
            geopos[0] = PyFloat_AsDouble(o4);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
        {
            geopos[0] = (double) PyInt_AsLong(o4);
        }
#endif
        else if (PyLong_Check(o4))
        {
            geopos[0] = (double) PyLong_AsLong(o4);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid longitude type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
            return NULL;
        }

        /* checking latitude */
        if (PyFloat_Check(o5))
        {
            geopos[1] = PyFloat_AsDouble(o5);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
        {
            geopos[1] = (double) PyInt_AsLong(o5);
        }
#endif
        else if (PyLong_Check(o5))
        {
            geopos[1] = (double) PyLong_AsLong(o5);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid latitude type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
            return NULL;
        }

        /* checking altitude */
        if (PyFloat_Check(o6))
        {
            geopos[2] = PyFloat_AsDouble(o6);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
        {
            geopos[2] = (double) PyInt_AsLong(o6);
        }
#endif
        else if (PyLong_Check(o6))
        {
            geopos[2] = (double) PyLong_AsLong(o6);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid altitude type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
            return NULL;
        }

        Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6);
    }

    if (!PySequence_Check(o2) || PySequence_Length(o2) != 4)
    {
        PyErr_SetString(pyswe_Error, "Invalid atmospheric sequence");
        return NULL;
    }
    else
    {
        o4 = PySequence_ITEM(o2, 0);
        o5 = PySequence_ITEM(o2, 1);
        o6 = PySequence_ITEM(o2, 2);
        o7 = PySequence_ITEM(o2, 3);
        if (!PyNumber_Check(o4) || !PyNumber_Check(o5) || !PyNumber_Check(o6)
            || !PyNumber_Check(o7))
        {
            PyErr_SetString(pyswe_Error, "Invalid atmospheric value type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }

        /* atmospheric pressure */
        if (PyFloat_Check(o4))
        {
            atmo[0] = PyFloat_AsDouble(o4);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o4))
        {
            atmo[0] = (double) PyInt_AsLong(o4);
        }
#endif
        else if (PyLong_Check(o4))
        {
            atmo[0] = (double) PyLong_AsLong(o4);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid atmospheric pressure");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }

        /* atmospheric temperature */
        if (PyFloat_Check(o5))
        {
            atmo[1] = PyFloat_AsDouble(o5);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
        {
            atmo[1] = (double) PyInt_AsLong(o5);
        }
#endif
        else if (PyLong_Check(o5))
        {
            atmo[1] = (double) PyLong_AsLong(o5);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid atmospheric temperature");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }

        /* humidity */
        if (PyFloat_Check(o6))
        {
            atmo[2] = PyFloat_AsDouble(o6);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o6))
        {
            atmo[2] = (double) PyInt_AsLong(o6);
        }
#endif
        else if (PyLong_Check(o6))
        {
            atmo[2] = (double) PyLong_AsLong(o6);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid humidity");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }

        /* meteorological range */
        if (PyFloat_Check(o7))
        {
            atmo[3] = PyFloat_AsDouble(o7);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o7))
        {
            atmo[3] = (double) PyInt_AsLong(o7);
        }
#endif
        else if (PyLong_Check(o7))
        {
            atmo[3] = (double) PyLong_AsLong(o7);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid meteorological range");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            return NULL;
        }

        Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
    }

    if (!PySequence_Check(o3) || PySequence_Length(o3) != 6)
    {
        PyErr_SetString(pyswe_Error, "Invalid observer sequence");
        return NULL;
    }
    else
    {
        o4 = PySequence_ITEM(o3, 0);
        o5 = PySequence_ITEM(o3, 1);
        o6 = PySequence_ITEM(o3, 2);
        o7 = PySequence_ITEM(o3, 3);
        o8 = PySequence_ITEM(o3, 4);
        o9 = PySequence_ITEM(o3, 5);
        if (!PyNumber_Check(o4) || !PyNumber_Check(o5) || !PyNumber_Check(o6)
            || !PyNumber_Check(o7) || !PyNumber_Check(o8) || !PyNumber_Check(o9))
        {
            PyErr_SetString(pyswe_Error, "Invalid observer value type");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }

        /* observer age */
        if (PyFloat_Check(o4))
        {
            observ[0] = PyFloat_AsDouble(o4);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o4))
        {
            observ[0] = (double) PyInt_AsLong(o4);
        }
#endif
        else if (PyLong_Check(o4))
        {
            observ[0] = (double) PyLong_AsLong(o4);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid observer age");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }

        /* snellen ratio */
        if (PyFloat_Check(o5))
        {
            observ[1] = PyFloat_AsDouble(o5);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o5))
        {
            observ[1] = (double) PyInt_AsLong(o5);
        }
#endif
        else if (PyLong_Check(o5))
        {
            observ[1] = (double) PyLong_AsLong(o5);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid snellen ratio");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }

        /* mono/binocular */
        if (PyFloat_Check(o6))
        {
            observ[2] = PyFloat_AsDouble(o6);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o6))
        {
            observ[2] = (double) PyInt_AsLong(o6);
        }
#endif
        else if (PyLong_Check(o6))
        {
            observ[2] = (double) PyLong_AsLong(o6);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid telescope");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }

        /* telescope magnification */
        if (PyFloat_Check(o7))
        {
            observ[3] = PyFloat_AsDouble(o7);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o7))
        {
            observ[3] = (double) PyInt_AsLong(o7);
        }
#endif
        else if (PyLong_Check(o7))
        {
            observ[3] = (double) PyLong_AsLong(o7);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid telescope magnification");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }

        /* optical aperture */
        if (PyFloat_Check(o8))
        {
            observ[4] = PyFloat_AsDouble(o8);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o8))
        {
            observ[4] = (double) PyInt_AsLong(o8);
        }
#endif
        else if (PyLong_Check(o8))
        {
            observ[4] = (double) PyLong_AsLong(o8);
        }
        else
        {
            PyErr_SetString(pyswe_Error, "Invalid telescope aperture");
            Py_DECREF(o4); Py_DECREF(o5); Py_DECREF(o6); Py_DECREF(o7);
            Py_DECREF(o8); Py_DECREF(o9);
            return NULL;
        }

        /* optical transmission */
        if (PyFloat_Check(o9))
        {
            observ[5] = PyFloat_AsDouble(o9);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_Check(o9))
        {
            observ[5] = (double) PyInt_AsLong(o9);
        }
#endif
        else if (PyLong_Check(o9))
        {
            observ[5] = (double) PyLong_AsLong(o9);
        }
        else
        {
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
    {
        return Py_BuildValue("dd", dres, dret);
    }
    else
    {
        PyErr_SetString(pyswe_Error, serr);
        return NULL;
    }
}

#if PYSWE_USE_SWEPHELP
/* *** Specific pyswisseph functions. ***

All names begin with an underscore. They are not part of the original swisseph,
but provided here as helpers for the programmer.
There is no guarantee that these functions are accurate. Use at your own risks.

*/

/* swisseph._jdnow */
static char pyswe__jdnow__doc__[] =
"Get current Julian day number (Gregorian calendar, UTC).\n\n"
"Args: -\n"
"Return: float";

static PyObject * pyswe__jdnow FUNCARGS_SELF
{
    return Py_BuildValue("f", swh_jdnow());
}

/* swisseph._julday */
static char pyswe__julday__doc__[] =
"Get Julian day number (UTC), without having to calculate hour in decimal.\n\n"
"Args: int year, int month, int day, int hour=12, int minutes=0, int seconds=0,"
" int flag=GREG_FLAG\n"
"Return: float";

static PyObject * pyswe__julday FUNCARGS_KEYWDS
{
    int year, mon, day, hour=12, min=0, sec=0, flag=SE_GREG_CAL;
    static char *kwlist[] = {"year", "month", "day", "hour", "minutes",
        "seconds", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "iii|iiii", kwlist,
        &year, &mon, &day, &hour, &min, &sec, &flag))
        return NULL;
    return Py_BuildValue("f", swh_julday(year, mon, day, hour,
        min, sec, flag));
}

/* swisseph._revjul */
static char pyswe__revjul__doc__[] =
"Reverse Julian day to date & time (UTC).\n\n"
"Args: double julday, int flag=GREG_CAL\n"
"Return: tuple of 6 int";

static PyObject * pyswe__revjul FUNCARGS_KEYWDS
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

/* swisseph._degsplit */
static char pyswe__degsplit__doc__[] =
"Get degrees, sign number [0;11], minutes, seconds, from a longitude position in [0;360[.\n\n"
"Args: double pos\n"
"Return: tuple of 4 int (deg, sign, min, sec)";

static PyObject * pyswe__degsplit FUNCARGS_KEYWDS
{
    int ret[6];
    double pos;
    static char *kwlist[] = {"pos", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &pos))
        return NULL;
    swh_degsplit(pos, ret);
    return Py_BuildValue("(iiii)", ret[0], ret[1], ret[2], ret[3]);
}

/* swisseph._signtostr */
static char pyswe__signtostr__doc__[] =
"Get a 3-letters string representing the sign number [0;11].\n\n"
"Args: int sign\n"
"Return: str";

static PyObject * pyswe__signtostr FUNCARGS_KEYWDS
{
    int res, sign;
    char str[4];
    static char *kwlist[] = {"sign", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i", kwlist, &sign))
        return NULL;
    res = swh_signtostr(sign, str);
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, "swisseph._signtostr: invalid sign number");
        return NULL;
    }
    return Py_BuildValue("s", str);
}

/* swisseph._house_system_name */
static char pyswe__house_system_name__doc__[] =
"Get house system name.\n\n"
"Args: char hsys\n"
"Return: str";

static PyObject * pyswe__house_system_name FUNCARGS_KEYWDS
{
    int res;
    char hsys, str[25];
    static char *kwlist[] = {"hsys", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "c", kwlist, &hsys))
        return NULL;
    res = swh_house_system_name(hsys, str);
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, "swisseph._house_system_name: invalid house system");
        return NULL;
    }
    return Py_BuildValue("s", str);
}

/* swisseph._min_retro_time */
static char pyswe__min_retro_time__doc__[] =
"Get approximate minimum retrogradation time of a planet, in days.\n\n"
"Args: int planet\n"
"Return: int";

static PyObject * pyswe__min_retro_time FUNCARGS_KEYWDS
{
    int plnt, res;
    char err[64];
    static char *kwlist[] = {"planet", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i", kwlist, &plnt))
        return NULL;
    res = swh_min_retro_time(plnt, err);
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("i", res);
}

/* swisseph._max_retro_time */
static char pyswe__max_retro_time__doc__[] =
"Get approximate maximum retrogradation time of a planet, in days.\n\n"
"Args: int planet\n"
"Return: int";

static PyObject * pyswe__max_retro_time FUNCARGS_KEYWDS
{
    int plnt, res;
    char err[64];
    static char *kwlist[] = {"planet", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i", kwlist, &plnt))
        return NULL;
    res = swh_max_retro_time(plnt, err);
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("i", res);
}

/* swisseph._next_retro */
static char pyswe__next_retro__doc__[] =
"Find next direction changing of object.\n\n"
"If daystep=0, use predefined step.\n"
"Flag should include FLG_SPEED, and FLG_NOGDEFL to avoid bad surprises;"
" alternatively use true positions.\n"
"If dayspan != 0, can return None if limit has been reached.\n\n"
"Args: int planet, float jd_start, float daystep=0, bool backward=False,"
" float dayspan=0, int flag=FLG_SWIEPH+FLG_SPEED+FLG_NOGDEFL\n"
"Return: 2 tuples Julian day, positions (or None if time limit has been reached)";

static PyObject * pyswe__next_retro FUNCARGS_KEYWDS
{
    int res, plnt, backw=0, flag=SEFLG_SWIEPH+SEFLG_SPEED+SEFLG_NOGDEFL;
    double jd, step=0.0, trange=0, jdret, posret[6];
    char err[256];
    static char *kwlist[] = {"planet", "jd_start", "daystep", "backward",
        "dayspan", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "id|didi", kwlist,
        &plnt, &jd, &step, &backw, &trange, &flag))
        return NULL;
    res = swh_next_retro(plnt, jd, step, backw, trange, flag,
        &jdret, posret, err);
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    else if (res > 0) /* time limit reached */
    {
        return Py_BuildValue("(O)(OOOOOO)", Py_None, Py_None, Py_None, Py_None,
        Py_None, Py_None, Py_None);
    }
    else
    {
        return Py_BuildValue("(f)(ffffff)", jdret, posret[0], posret[1],
        posret[2], posret[3], posret[4], posret[5]);
    }
}

/* swisseph._go_past */
static char pyswe__go_past__doc__[] =
"Get Julian day number and positions when a celestial object has gone past a"
" fixed point expressed in longitude degrees.\n\n"
"If daystep=0, use a predefined step.\n"
"Same warning as in swe._next_retro.\n\n"
"Args: int planet, float fixedpt, float jd_start, float daystep=0,"
" bool backward=False, int flag=FLG_SWIEPH+FLG_SPEED+FLG_NOGDEFL\n"
"Return: 2 tuples Julian day, positions";

static PyObject * pyswe__go_past FUNCARGS_KEYWDS
{
    int plnt, backw=0, flag=SEFLG_SWIEPH+SEFLG_SPEED+SEFLG_NOGDEFL;
    double fix, jd, step=0, res, jdret, posret[6];
    char err[256];
    static char *kwlist[] = {"planet", "fixedpt", "jd_start", "daystep",
        "backward", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "idd|dii", kwlist,
        &plnt, &fix, &jd, &step, &backw, &flag))
        return NULL;
    res = swh_go_past(plnt, fix, jd, step, backw, flag, &jdret, posret, err);
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(f)(ffffff)", jdret, posret[0], posret[1], posret[2],
        posret[3], posret[4], posret[5]);
}

/* swisseph._next_aspect */
static char pyswe__next_aspect__doc__[] =
"Get Julian day number and positions when celestial object makes longitudinal"
" aspect to a fixed point expressed in longitude degrees.\n\n"
"Aspect in the range [0;360[.\n"
"If daystep=0, use a predefined step.\n"
"If dayspan != 0, can return None if limit has been reached.\n\n"
"Args: int planet, float aspect, float fixedpt, float jd_start, float daystep=0,"
" bool backward=False, float dayspan=0, int flag=FLG_SWIEPH+FLG_SPEED+FLG_NOGDEFL\n"
"Return: 2 tuples Julian day, positions (or None if limit has been reached)";

static PyObject * pyswe__next_aspect FUNCARGS_KEYWDS
{
    int plnt, backw=0, flag=SEFLG_SWIEPH+SEFLG_SPEED+SEFLG_NOGDEFL;
    double asp, fix, jd, step=0, trange=0, res, jdret, posret[6];
    char err[256];
    static char *kwlist[] = {"planet", "aspect", "fixedpt", "jd_start",
        "daystep", "backward", "dayspan", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "iddd|didi", kwlist,
        &plnt, &asp, &fix, &jd, &step, &backw, &trange, &flag))
        return NULL;
    res = swh_next_aspect(plnt, asp, fix, jd, step, backw, trange, flag,
        &jdret, posret, err);
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    else if (res > 0) /* time limit reached */
    {
        return Py_BuildValue("(O)(OOOOOO)", Py_None, Py_None, Py_None, Py_None,
        Py_None, Py_None, Py_None);
    }
    else
    {
        return Py_BuildValue("(f)(ffffff)", jdret, posret[0], posret[1],
        posret[2], posret[3], posret[4], posret[5]);
    }
}

/* swisseph._next_aspect2 */
static char pyswe__next_aspect2__doc__[] =
"Same as _next_aspect, but with aspect in range [0;180].\n\n"
"If aspect is not 0 or 180, it will try the two aspects in [0;360[, and return"
" the nearest from jd_start. It may then be faster to use _next_aspect several"
" times, especially when scanning long periods of time.\n\n"
"Args: int planet, float aspect, float fixedpt, float jd_start, float daystep=0,"
" bool backward=False, float dayspan=0, int flag=FLG_SWIEPH+FLG_SPEED+FLG_NOGDEFL\n"
"Return: 2 tuples Julian day, positions (or None if limit has been reached)";

static PyObject * pyswe__next_aspect2 FUNCARGS_KEYWDS
{
    int plnt, backw=0, flag=SEFLG_SWIEPH+SEFLG_SPEED+SEFLG_NOGDEFL;
    double asp, fix, jd, step=0, trange=0, res, jdret, posret[6];
    char err[256];
    static char *kwlist[] = {"planet", "aspect", "fixedpt", "jd_start",
        "daystep", "backward", "dayspan", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "iddd|didi", kwlist,
        &plnt, &asp, &fix, &jd, &step, &backw, &trange, &flag))
        return NULL;
    res = swh_next_aspect2(plnt, asp, fix, jd, step, backw, trange, flag,
        &jdret, posret, err);
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    else if (res > 0) /* time limit reached */
    {
        return Py_BuildValue("(O)(OOOOOO)", Py_None, Py_None, Py_None, Py_None,
        Py_None, Py_None, Py_None);
    }
    else
    {
        return Py_BuildValue("(f)(ffffff)", jdret, posret[0], posret[1],
        posret[2], posret[3], posret[4], posret[5]);
    }
}

/* swisseph._next_aspect_with */
static char pyswe__next_aspect_with__doc__[] =
"Get Julian day number and positions when celestial object makes longitudinal"
" aspect to another moving object.\n\n"
"Aspect in the range [0;360[.\n"
"Other object can be a fixed star.\n"
"If dayspan != 0, can return None if limit has been reached.\n\n"
"Args: int planet, float aspect, int or str other, float jd_start,"
" float daystep=10, bool backward=False, float dayspan=0, int flag=FLG_SWIEPH+FLG_SPEED\n"
"Return: 3 tuples Julian day, planet positions, other positions (or None if limit has been reached)";

static PyObject * pyswe__next_aspect_with FUNCARGS_KEYWDS
{
    int res, plnt, other, backw=0, flag=SEFLG_SWIEPH+SEFLG_SPEED;
    double asp, jd, step=10, trange=0, jdret, posret0[6], posret1[6];
    char err[256], *star="";
    PyObject *body;
    static char *kwlist[] = {"planet", "aspect", "other", "jd_start",
        "daystep", "backward", "dayspan", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "idOd|didi", kwlist,
        &plnt, &asp, &body, &jd, &step, &backw, &trange, &flag))
        return NULL;
    if (PyLong_CheckExact(body)) /* long -> planet */
    {
        other = (int) PyLong_AsLong(body);
    }
#if PY_MAJOR_VERSION >= 3
    else if (PyUnicode_CheckExact(body)) /* unicode -> fixed star */
    {
        other = 0;
        star = (char*) PyUnicode_AS_DATA(body);
    }
#elif PY_MAJOR_VERSION < 3
    else if (PyInt_CheckExact(body)) /* int -> planet */
    {
        other = (int) PyInt_AsLong(body);
    }
    else if (PyString_CheckExact(body)) /* str -> fixed star */
    {
        other = 0;
        star = PyString_AsString(body);
    }
#endif
    else
    {
        PyErr_SetString(pyswe_Error,
            "swisseph._next_aspect_with: Invalid body type");
        return NULL;
    }
    res = swh_next_aspect_with(plnt, asp, other, star, jd, step, backw, trange,
        flag, &jdret, posret0, posret1, err);
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    else if (res > 0) /* time limit reached */
    {
        return Py_BuildValue("(O)(OOOOOO)(OOOOOO)", Py_None, Py_None, Py_None,
        Py_None, Py_None, Py_None, Py_None, Py_None, Py_None, Py_None, Py_None,
        Py_None, Py_None);
    }
    else
    {
        return Py_BuildValue("(f)(ffffff)(ffffff)", jdret, posret0[0],
        posret0[1], posret0[2], posret0[3], posret0[4], posret0[5], posret1[0],
        posret1[1], posret1[2], posret1[3], posret1[4], posret1[5]);
    }
}

/* swisseph._next_aspect_with2 */
static char pyswe__next_aspect_with2__doc__[] =
"Same as _next_aspect_with, but aspect in range [0;180].\n\n"
"If aspect is not 0 or 180, it will try the two aspects in [0;360[, and return"
" the nearest from jd_start. It may then be faster to use _next_aspect_with"
" several times, especially when scanning long periods of time.\n\n"
"Args: int planet, float aspect, int or str other, float jd_start,"
" float daystep=10, bool backward=False, float dayspan=0, int flag=FLG_SWIEPH+FLG_SPEED\n"
"Return: 3 tuples Julian day, planet positions, other positions (or None if limit has been reached)";

static PyObject * pyswe__next_aspect_with2 FUNCARGS_KEYWDS
{
    int res, plnt, other, backw=0, flag=SEFLG_SWIEPH+SEFLG_SPEED;
    double asp, jd, step=10, trange=0, jdret, posret0[6], posret1[6];
    char err[256], *star="";
    PyObject *body;
    static char *kwlist[] = {"planet", "aspect", "other", "jd_start",
        "daystep", "backward", "dayspan", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "idOd|didi", kwlist,
        &plnt, &asp, &body, &jd, &step, &backw, &trange, &flag))
        return NULL;
    if (PyLong_CheckExact(body)) /* long -> planet */
    {
        other = (int) PyLong_AsLong(body);
    }
#if PY_MAJOR_VERSION >= 3
    else if (PyUnicode_CheckExact(body)) /* unicode -> fixed star */
    {
        other = 0;
        star = (char*) PyUnicode_AS_DATA(body);
    }
#elif PY_MAJOR_VERSION < 3
    else if (PyInt_CheckExact(body)) /* int -> planet */
    {
        other = (int) PyInt_AsLong(body);
    }
    else if (PyString_CheckExact(body)) /* str -> fixed star */
    {
        other = 0;
        star = PyString_AsString(body);
    }
#endif
    else
    {
        PyErr_SetString(pyswe_Error,
            "swisseph._next_aspect_with2: Invalid body type");
        return NULL;
    }
    res = swh_next_aspect_with2(plnt, asp, other, star, jd, step, backw, trange,
        flag, &jdret, posret0, posret1, err);
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    else if (res > 0) /* time limit reached */
    {
        return Py_BuildValue("(O)(OOOOOO)(OOOOOO)", Py_None, Py_None, Py_None,
        Py_None, Py_None, Py_None, Py_None, Py_None, Py_None, Py_None, Py_None,
        Py_None, Py_None);
    }
    else
    {
        return Py_BuildValue("(f)(ffffff)(ffffff)", jdret, posret0[0],
        posret0[1], posret0[2], posret0[3], posret0[4], posret0[5], posret1[0],
        posret1[1], posret1[2], posret1[3], posret1[4], posret1[5]);
    }
}

/* swisseph._next_aspect_cusp */
static char pyswe__next_aspect_cusp__doc__[] =
"Get Julian day number and positions, and houses cusps and ascmc, when celestial"
" object makes longitudinal aspect to a house cusp.\n\n"
"House cusp expressed as an integer in [1;12] or [1;36] for Gauquelin.\n"
"Aspect in the range [0;360[.\n"
"Body can be a fixed star.\n"
"For risings, settings, meridian transits, see rise_trans.\n\n"
"Args: int or str body, float aspect, int cusp, double jd_start, double lat,"
" double lon, char hsys='P', bool backward=False, int flag=FLG_SWIEPH+FLG_SPEED\n"
"Return: 4 tuples Julian day, body positions, cusps, ascmc";

static PyObject * pyswe__next_aspect_cusp FUNCARGS_KEYWDS
{
    int res, plnt, cusp, hsys='P', backw=0, flag=SEFLG_SWIEPH+SEFLG_SPEED;
    double asp, jd, lat, lon, step=0.2, jdret, posret[6], cusps[37], ascmc[10];
    char err[256], *star="";
    PyObject *body;
    static char *kwlist[] = {"body", "aspect", "cusp", "jd_start", "lat", "lon",
        "hsys", "backward", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "Odiddd|cii", kwlist,
        &body, &asp, &cusp, &jd, &lat, &lon, &hsys, &backw, &flag))
        return NULL;
    if (PyLong_CheckExact(body)) /* long -> planet */
    {
        plnt = (int) PyLong_AsLong(body);
    }
#if PY_MAJOR_VERSION >= 3
    else if (PyUnicode_CheckExact(body)) /* unicode -> fixed star */
    {
        plnt = 0;
        star = (char*) PyUnicode_AS_DATA(body);
    }
#elif PY_MAJOR_VERSION < 3
    else if (PyInt_CheckExact(body)) /* int -> planet */
    {
        plnt = (int) PyInt_AsLong(body);
    }
    else if (PyString_CheckExact(body)) /* str -> fixed star */
    {
        plnt = 0;
        star = PyString_AsString(body);
    }
#endif
    else
    {
        PyErr_SetString(pyswe_Error,
            "swisseph._next_aspect_cusp: Invalid body type");
        return NULL;
    }
    res = swh_next_aspect_cusp(plnt, star, asp, cusp, jd, lat, lon, hsys, step,
        backw, flag, &jdret, posret, cusps, ascmc, err);
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    if (hsys == 71) /* Gauquelin sectors */
    {
        return Py_BuildValue("(f)(ffffff)(ffffffffffffffffffffffffffffffffffff)(ffffffff)",
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
    }
    else
    {
        return Py_BuildValue("(f)(ffffff)(ffffffffffff)(ffffffff)", jdret,
        posret[0], posret[1], posret[2], posret[3], posret[4], posret[5],
        cusps[1], cusps[2], cusps[3], cusps[4], cusps[5], cusps[6], cusps[7],
        cusps[8], cusps[9], cusps[10], cusps[11], cusps[12],
        ascmc[0], ascmc[1], ascmc[2], ascmc[3], ascmc[4], ascmc[5], ascmc[6],
        ascmc[7]);
    }
}

/* swisseph._next_aspect_cusp2 */
static char pyswe__next_aspect_cusp2__doc__[] =
"Same as _next_aspect_cusp, but aspect in range[0;180].\n\n"
"If aspect is not 0 or 180, it will try the two aspects in [0;360[, and return"
" the nearest from jd_start. It may then be faster to use _next_aspect_cusp"
" several times, especially when scanning long periods of time.\n\n"
"Args: int or str body, float aspect, int cusp, double jd_start, double lat,"
" double lon, char hsys='P', bool backward=False, int flag=FLG_SWIEPH+FLG_SPEED\n"
"Return: 4 tuples Julian day, body positions, cusps, ascmc";

static PyObject * pyswe__next_aspect_cusp2 FUNCARGS_KEYWDS
{
    int res, plnt, cusp, hsys='P', backw=0, flag=SEFLG_SWIEPH+SEFLG_SPEED;
    double asp, jd, lat, lon, step=0.2, jdret, posret[6], cusps[37], ascmc[10];
    char err[256], *star="";
    PyObject *body;
    static char *kwlist[] = {"body", "aspect", "cusp", "jd_start", "lat", "lon",
        "hsys", "backward", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "Odiddd|cii", kwlist,
        &body, &asp, &cusp, &jd, &lat, &lon, &hsys, &backw, &flag))
        return NULL;
    if (PyLong_CheckExact(body)) /* long -> planet */
    {
        plnt = (int) PyLong_AsLong(body);
    }
#if PY_MAJOR_VERSION >= 3
    else if (PyUnicode_CheckExact(body)) /* unicode -> fixed star */
    {
        plnt = 0;
        star = (char*) PyUnicode_AS_DATA(body);
    }
#elif PY_MAJOR_VERSION < 3
    else if (PyInt_CheckExact(body)) /* int -> planet */
    {
        plnt = (int) PyInt_AsLong(body);
    }
    else if (PyString_CheckExact(body)) /* str -> fixed star */
    {
        plnt = 0;
        star = PyString_AsString(body);
    }
#endif
    else
    {
        PyErr_SetString(pyswe_Error,
            "swisseph._next_aspect_cusp2: Invalid body type");
        return NULL;
    }
    res = swh_next_aspect_cusp2(plnt, star, asp, cusp, jd, lat, lon, hsys, step,
        backw, flag, &jdret, posret, cusps, ascmc, err);
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    if (hsys == 71) /* Gauquelin sectors */
    {
        return Py_BuildValue("(f)(ffffff)(ffffffffffffffffffffffffffffffffffff)(ffffffff)",
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
    }
    else
    {
        return Py_BuildValue("(f)(ffffff)(ffffffffffff)(ffffffff)", jdret,
        posret[0], posret[1], posret[2], posret[3], posret[4], posret[5],
        cusps[1], cusps[2], cusps[3], cusps[4], cusps[5], cusps[6], cusps[7],
        cusps[8], cusps[9], cusps[10], cusps[11], cusps[12],
        ascmc[0], ascmc[1], ascmc[2], ascmc[3], ascmc[4], ascmc[5], ascmc[6],
        ascmc[7]);
    }
}

/* swisseph._match_aspect */
static char pyswe__match_aspect__doc__[] =
"Check if the two given positions match the aspect within the given orb.\n\n"
"If so return a tuple with difference, a value for application (True),"
" separation (False) or equal speeds (None), and an aspect strength factor;"
" else return three None.\n"
"Aspect in range [0;360[.\n\n"
"Args: float pos1, float speed1, float pos2, float speed2, float aspect,"
" float orb\nReturn: tuple (difference, application, factor)";

static PyObject * pyswe__match_aspect FUNCARGS_KEYWDS
{
    int applic;
    double res, pos0, pos1, sp0, sp1, asp, orb, ret, ftor;
    static char *kwlist[] = {"pos1", "speed1", "pos2", "speed2", "aspect",
        "orb", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dddddd", kwlist,
        &pos0, &sp0, &pos1, &sp1, &asp, &orb))
        return NULL;
    res = swh_match_aspect(pos0, sp0, pos1, sp1, asp, orb, &ret, &applic, &ftor);
    if (res < 0)
        return Py_BuildValue("(OOO)", Py_None, Py_None, Py_None);
    else if (applic == 1)
        return Py_BuildValue("(fOf)", ret, Py_False, ftor);
    else if (applic == -1)
        return Py_BuildValue("(fOf)", ret, Py_True, ftor);
    else
        return Py_BuildValue("(fOf)", ret, Py_None, ftor);
}

/* swisseph._match_aspect2 */
static char pyswe__match_aspect2__doc__[] =
"Same as _match_aspect, but with aspect in range [0;180].\n\n"
"Args: float pos1, float speed1, float pos2, float speed2, float aspect, float orb\n"
"Return: tuple (difference, application, factor)";

static PyObject * pyswe__match_aspect2 FUNCARGS_KEYWDS
{
    int applic;
    double res, pos0, pos1, sp0, sp1, asp, orb, ret, ftor;
    static char *kwlist[] = {"pos1", "speed1", "pos2", "speed2", "aspect",
        "orb", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dddddd", kwlist,
        &pos0, &sp0, &pos1, &sp1, &asp, &orb))
        return NULL;
    res = swh_match_aspect2(pos0, sp0, pos1, sp1, asp, orb, &ret, &applic, &ftor);
    if (res < 0)
        return Py_BuildValue("(OOO)", Py_None, Py_None, Py_None);
    else if (applic == 1)
        return Py_BuildValue("(fOf)", ret, Py_False, ftor);
    else if (applic == -1)
        return Py_BuildValue("(fOf)", ret, Py_True, ftor);
    else
        return Py_BuildValue("(fOf)", ret, Py_None, ftor);
}

/* swisseph._match_aspect3 */
static char pyswe__match_aspect3__doc__[] =
"Same as _match_aspect, but with specific orbs for applying/separating/stable aspects.\n\n"
"Args: float pos1, float speed1, float pos2, float speed2, float aspect, "
"float app_orb, float sep_orb, float sta_orb\n"
"Return: tuple (delta, applying, factor)";

static PyObject * pyswe__match_aspect3 FUNCARGS_KEYWDS
{
    int applic;
    double res, pos0, pos1, sp0, sp1, asp, app_orb, sep_orb, sta_orb, ret, ftor;
    static char *kwlist[] = {"pos1", "speed1", "pos2", "speed2", "aspect",
        "app_orb", "sep_orb", "sta_orb", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dddddddd", kwlist,
        &pos0, &sp0, &pos1, &sp1, &asp, &app_orb, &sep_orb, &sta_orb))
        return NULL;
    res = swh_match_aspect3(pos0, sp0, pos1, sp1, asp, app_orb, sep_orb, sta_orb,
        &ret, &applic, &ftor);
    if (res < 0)
        return Py_BuildValue("(OOO)", Py_None, Py_None, Py_None);
    else if (applic == 1)
        return Py_BuildValue("(fOf)", ret, Py_False, ftor);
    else if (applic == -1)
        return Py_BuildValue("(fOf)", ret, Py_True, ftor);
    else
        return Py_BuildValue("(fOf)", ret, Py_None, ftor);
}

/* swisseph._match_aspect4 */
static char pyswe__match_aspect4__doc__[] =
"Same as _match_aspect2, but with specific orbs for applying/separating/stable aspects.\n\n"
"Args: float pos1, float speed1, float pos2, float speed2, float aspect, "
"float app_orb, float sep_orb, float sta_orb\n"
"Return: tuple (delta, applying, factor)";

static PyObject * pyswe__match_aspect4 FUNCARGS_KEYWDS
{
    int applic;
    double res, pos0, pos1, sp0, sp1, asp, app_orb, sep_orb, sta_orb, ret, ftor;
    static char *kwlist[] = {"pos1", "speed1", "pos2", "speed2", "aspect",
        "app_orb", "sep_orb", "sta_orb", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dddddddd", kwlist,
        &pos0, &sp0, &pos1, &sp1, &asp, &app_orb, &sep_orb, &sta_orb))
        return NULL;
    res = swh_match_aspect4(pos0, sp0, pos1, sp1, asp, app_orb, sep_orb, sta_orb,
        &ret, &applic, &ftor);
    if (res < 0)
        return Py_BuildValue("(OOO)", Py_None, Py_None, Py_None);
    else if (applic == 1)
        return Py_BuildValue("(fOf)", ret, Py_False, ftor);
    else if (applic == -1)
        return Py_BuildValue("(fOf)", ret, Py_True, ftor);
    else
        return Py_BuildValue("(fOf)", ret, Py_None, ftor);
}

/* swisseph._years_diff */
static char pyswe__years_diff__doc__[] =
"Get number of 'astrological' years between two Julian days.\n\n"
"Args: float jd1, float jd2, int flag=FLG_SWIEPH\n"
"Return: float";

static PyObject * pyswe__years_diff FUNCARGS_KEYWDS
{
    double jd1, jd2, years;
    int flag = SEFLG_SWIEPH, res;
    char err[256];
    static char *kwlist[] = {"jd1", "jd2", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dd|i", kwlist,
        &jd1, &jd2, &flag))
        return NULL;
    res = swh_years_diff(jd1, jd2, flag, &years, err);
    if (res < 0)
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("f", years);
}

/* swisseph._geoc2d */
static char pyswe__geoc2d__doc__[] =
"Get float from given string meant as a geographical coordinates, examples:"
" \"022:W:25\", \"46:N:02:0\", \"6:E:55:00\".\n\n"
"Args: str coord\n"
"Return: float";

static PyObject * pyswe__geoc2d FUNCARGS_KEYWDS
{
    int res;
    double ret;
    char *coord;
    static char *kwlist[] = {"coord", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "s", kwlist, &coord))
        return NULL;
    res = swh_geoc2d(coord, &ret);
    if (res == -1)
    {
        PyErr_SetString(pyswe_Error, "swisseph._geoc2d: Invalid coord string");
        return NULL;
    }
    return Py_BuildValue("f", ret);
}

/* swisseph._geolat2c */
static char pyswe__geolat2c__doc__[] =
"Get formated string of given geographical latitude.\n\n"
"Args: float lat\n"
"Return: str";

static PyObject * pyswe__geolat2c FUNCARGS_KEYWDS
{
    int res;
    double lat;
    char ret[11];
    static char *kwlist[] = {"lat", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &lat))
        return NULL;
    res = swh_geolat2c(lat, ret);
    if (res == -1)
    {
        PyErr_SetString(pyswe_Error, "swisseph._geolat2c: Invalid latitude");
        return NULL;
    }
    return Py_BuildValue("s", ret);
}

/* swisseph._geolon2c */
static char pyswe__geolon2c__doc__[] =
"Get formated string of given geographical longitude.\n\n"
"Args: float lon\n"
"Return: str";

static PyObject * pyswe__geolon2c FUNCARGS_KEYWDS
{
    int res;
    double lon;
    char ret[12];
    static char *kwlist[] = {"lon", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &lon))
        return NULL;
    res = swh_geolon2c(lon, ret);
    if (res == -1)
    {
        PyErr_SetString(pyswe_Error, "swisseph._geolon2c: Invalid longitude");
        return NULL;
    }
    return Py_BuildValue("s", ret);
}

/* swisseph._raman_houses */
static char pyswe__raman_houses__doc__[] =
"Get Raman houses cusps (bhavamadhya the default, or arambhasandhi).\n\n"
"Args: float asc, float mc, bool sandhi=False\n"
"Return: tuple of 12 float";

static PyObject * pyswe__raman_houses FUNCARGS_KEYWDS
{
    int sdi = 0;
    double asc, mc, ret[12];
    static char *kwlist[] = {"asc", "mc", "sandhi", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dd|b", kwlist, &asc, &mc, &sdi))
        return NULL;
    swh_raman_houses(asc, mc, ret, sdi);
    return Py_BuildValue("ffffffffffff", ret[0],ret[1],ret[2],ret[3],ret[4],
        ret[5],ret[6],ret[7],ret[8],ret[9],ret[10],ret[11]);
}

/* swisseph._lord */
static char pyswe__lord__doc__[] =
"Get sign lord.\n\n"
"Args: int sign [0:11]\n"
"Return: int planet number";

static PyObject * pyswe__lord FUNCARGS_KEYWDS
{
    int sign, i;
    static char *kwlist[] = {"sign", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i", kwlist, &sign))
        return NULL;
    i = swh_lord(sign);
    if (i == -1)
    {
        PyErr_SetString(pyswe_Error, "swisseph._lord: Invalid sign number");
        return NULL;
    }
    return Py_BuildValue("i", i);
}

/* swisseph._long2rasi */
static char pyswe__long2rasi__doc__[] =
"Get rasi number from ecliptical longitude.\n\n"
"Args: float lon\n"
"Return: int";

static PyObject * pyswe__long2rasi FUNCARGS_KEYWDS
{
    double lon;
    static char *kwlist[] = {"lon", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &lon))
        return NULL;
    return Py_BuildValue("i", swh_long2rasi(lon));
}

/* swisseph._long2navamsa */
static char pyswe__long2navamsa__doc__[] =
"Get navamsa from ecliptical longitude.\n\n"
"Args: float lon\n"
"Return: int";

static PyObject * pyswe__long2navamsa FUNCARGS_KEYWDS
{
    double lon;
    static char *kwlist[] = {"lon", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &lon))
        return NULL;
    return Py_BuildValue("i", swh_long2navamsa(lon));
}

/* swisseph._long2nakshatra */
static char pyswe__long2nakshatra__doc__[] =
"Get nakshatra and pada from ecliptical longitude.\n\n"
"Args: float lon\n"
"Return: 2 int";

static PyObject * pyswe__long2nakshatra FUNCARGS_KEYWDS
{
    int ret[2];
    double lon;
    static char *kwlist[] = {"lon", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist, &lon))
        return NULL;
    swh_long2nakshatra(lon, ret);
    return Py_BuildValue("ii", ret[0], ret[1]);
}

/* swisseph._get_nakshatra_name */
static char pyswe__get_nakshatra_name__doc__[] =
"Get nakshatra name from nakshatra number [0:26].\n\n"
"Args: int nakshatra\n"
"Return: str";

static PyObject * pyswe__get_nakshatra_name FUNCARGS_KEYWDS
{
    char ret[15];
    int nak;
    static char *kwlist[] = {"nakshatra", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i", kwlist, &nak))
        return NULL;
    if (swh_get_nakshatra_name(nak, ret) == -1)
    {
        PyErr_SetString(pyswe_Error, "swisseph._get_nakshatra_name: Invalid nakshatra number");
        return NULL;
    }
    return Py_BuildValue("s", ret);
}

/* swisseph._rasinorm */
static char pyswe__rasinorm__doc__[] =
"Get a normalized rasi number between 0 and 11.\n\n"
"Args: int rasi\n"
"Return: int";

static PyObject * pyswe__rasinorm FUNCARGS_KEYWDS
{
    int rasi;
    static char *kwlist[] = {"rasi", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "i", kwlist, &rasi))
        return NULL;
    return Py_BuildValue("i", swh_rasinorm(rasi));
}

/* swisseph._rasi_dif */
static char pyswe__rasi_dif__doc__[] =
"Get number of rasi between two rasis, from 0 to 11.\n\n"
"Args: int r1, int r2\n"
"Return: int";

static PyObject * pyswe__rasi_dif FUNCARGS_KEYWDS
{
    int r1, r2;
    static char *kwlist[] = {"r1", "r2", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ii", kwlist, &r1, &r2))
        return NULL;
    return Py_BuildValue("i", swh_rasi_dif(r1, r2));
}

/* swisseph._rasi_dif2 */
static char pyswe__rasi_dif2__doc__[] =
"Get number of rasi between two rasis, from -5 to 6.\n\n"
"Args: int r1, int r2\n"
"Return: int";

static PyObject * pyswe__rasi_dif2 FUNCARGS_KEYWDS
{
    int r1, r2;
    static char *kwlist[] = {"r1", "r2", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ii", kwlist, &r1, &r2))
        return NULL;
    return Py_BuildValue("i", swh_rasi_dif2(r1, r2));
}

/* swisseph._tatkalika_relation */
static char pyswe__tatkalika_relation__doc__[] =
"Get the tatkalika relation between two planets, given their rasi numbers.\n\n"
"Args: int r1, int r2\n"
"Return: int 1 (Mitra) or -1 (Satru)";

static PyObject * pyswe__tatkalika_relation FUNCARGS_KEYWDS
{
    int r1, r2;
    static char *kwlist[] = {"r1", "r2", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ii", kwlist, &r1, &r2))
        return NULL;
    return Py_BuildValue("i", swh_tatkalika_relation(r1, r2));
}

/* swisseph._naisargika_relation */
static char pyswe__naisargika_relation__doc__[] =
"Get the naisargika relation between two planets.\n\n"
"Args: int gr1, int gr2\n"
"Return: int 1 (Mitra) 0 (Sama) or -1 (Satru)";

static PyObject * pyswe__naisargika_relation FUNCARGS_KEYWDS
{
    int gr1, gr2, i, ret;
    static char *kwlist[] = {"gr1", "gr2", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ii", kwlist, &gr1, &gr2))
        return NULL;
    i = swh_naisargika_relation(gr1, gr2, &ret);
    if (i == -1)
    {
        PyErr_SetString(pyswe_Error, "swisseph._naisargika_relation: Invalid planet");
        return NULL;
    }
    return Py_BuildValue("i", ret);
}

/* swisseph._residential_strength */
static char pyswe__residential_strength__doc__[] =
"Get the residential strength for a planet, given its longitude and bhavamadhya"
" longitudes in a 12 items sequence.\n\n"
"Args: int plon, seq bhavas\n"
"Return: float strength";

static PyObject * pyswe__residential_strength FUNCARGS_KEYWDS
{
    int i;
    double bh[12], ret, plon;
    PyObject *seq, *p;
    static char *kwlist[] = {"plon", "bhavas", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "dO", kwlist, &plon, &seq))
        return NULL;
    if ((PySequence_Check(seq) != 1) || (PySequence_Length(seq) < 12))
    {
        PyErr_SetString(pyswe_Error, "swisseph._residential_strength: Invalid bhavas");
        return NULL;
    }
    for (i = 0; i < 12; ++i) /* check sequence has 12 numbers */
    {
        p = PySequence_GetItem(seq, i);
        if (PyFloat_CheckExact(p))
        {
            bh[i] = PyFloat_AS_DOUBLE(p);
        }
        else if (PyLong_CheckExact(p))
        {
            bh[i] = PyLong_AsDouble(p);
        }
#if PY_MAJOR_VERSION < 3
        else if (PyInt_CheckExact(p))
        {
            bh[i] = PyInt_AS_LONG(p);
        }
#endif
        else
        {
            PyErr_SetString(pyswe_Error, "swisseph._residential_strength: Invalid bhavas type");
            return NULL;
        }
    }
    i = swh_residential_strength(plon, bh, &ret);
    if (i == -1) /* should not happen... */
    {
        PyErr_SetString(pyswe_Error, "swisseph._residential_strength: Invalid error");
        return NULL;
    }
    return Py_BuildValue("f", ret);
}

/* swisseph._ochchabala */
static char pyswe__ochchabala__doc__[] =
"Get the ochchabala for a planet.\n\n"
"Args: int pl, float longitude\n"
"Return: float shashtiamsa";

static PyObject * pyswe__ochchabala FUNCARGS_KEYWDS
{
    int ipl;
    double lon, d;
    static char *kwlist[] = {"pl", "longitude", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "id", kwlist, &ipl, &lon))
        return NULL;
    d = swh_ochchabala(ipl, lon);
    if (d == -1)
    {
        PyErr_SetString(pyswe_Error, "swisseph._ochchabala: Invalid planet");
        return NULL;
    }
    return Py_BuildValue("f", d);
}

/* swisseph._saturn_4_stars */
static char pyswe__saturn_4_stars__doc__[] =
"Compute Halbronn's 'Saturn 4 Stars' index.\n\n"
"Args: float jd, int flag=FLG_SWIEPH+FLG_SPEED\n"
"Return: tuple of 6 float (Sat, Ald, Reg, Ant, Fom, and index value)";

static PyObject * pyswe__saturn_4_stars FUNCARGS_KEYWDS
{
    double jd, ret[6] = {0,0,0,0,0,0};
    int res, flag = SEFLG_SWIEPH | SEFLG_SPEED;
    char err[256];
    static char *kwlist[] = {"jd", "flag", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d|i", kwlist, &jd, &flag))
        return NULL;
    res = swh_saturn_4_stars(jd, flag, ret, err);
    if ( res < 0 )
    {
        PyErr_SetString(pyswe_Error, err);
        return NULL;
    }
    return Py_BuildValue("(ffffff)", ret[0],ret[1],ret[2],ret[3],ret[4],ret[5]);
}

#if SWH_USE_THREADS

/* swisseph._lock */
static char pyswe__lock__doc__[] =
"Lock pyswisseph.\n\nArgs: -\nReturn: None";

static PyObject * pyswe__lock FUNCARGS_SELF
{
    swh_lock();
    Py_RETURN_NONE;
}

/* swisseph._unlock */
static char pyswe__unlock__doc__[] =
"Unlock pyswisseph.\n\nArgs: -\nReturn: None";

static PyObject * pyswe__unlock FUNCARGS_SELF
{
    swh_unlock();
    Py_RETURN_NONE;
}

/* swisseph._trylock */
static char pyswe__trylock__doc__[] =
"Try to lock pyswisseph.\n\nArgs: -\nReturn: bool";

static PyObject * pyswe__trylock FUNCARGS_SELF
{
    if (swh_trylock() == 0)
    {
        Py_RETURN_TRUE;
    }
    else
    {
        Py_RETURN_FALSE;
    }
}

#endif /* SWH_USE_THREADS */
#endif /* PYSWE_USE_SWEPHELP */

/* Methods */
static struct PyMethodDef pyswe_methods[] = {
    {"set_ephe_path", (PyCFunction) pyswe_set_ephe_path,
        METH_VARARGS|METH_KEYWORDS, pyswe_set_ephe_path__doc__},
    {"set_jpl_file", (PyCFunction) pyswe_set_jpl_file,
        METH_VARARGS|METH_KEYWORDS, pyswe_set_jpl_file__doc__},
    {"set_topo", (PyCFunction) pyswe_set_topo,
        METH_VARARGS|METH_KEYWORDS, pyswe_set_topo__doc__},
    {"set_sid_mode", (PyCFunction) pyswe_set_sid_mode,
        METH_VARARGS|METH_KEYWORDS, pyswe_set_sid_mode__doc__},
    {"get_ayanamsa", (PyCFunction) pyswe_get_ayanamsa,
        METH_VARARGS|METH_KEYWORDS, pyswe_get_ayanamsa__doc__},
    {"get_ayanamsa_ut", (PyCFunction) pyswe_get_ayanamsa_ut,
        METH_VARARGS|METH_KEYWORDS, pyswe_get_ayanamsa_ut__doc__},
    {"get_ayanamsa_name", (PyCFunction) pyswe_get_ayanamsa_name,
        METH_VARARGS|METH_KEYWORDS, pyswe_get_ayanamsa_name__doc__},
    {"close", (PyCFunction) pyswe_close,
        METH_NOARGS, pyswe_close__doc__},
    {"get_planet_name", (PyCFunction) pyswe_get_planet_name,
        METH_VARARGS|METH_KEYWORDS, pyswe_get_planet_name__doc__},
    {"calc", (PyCFunction) pyswe_calc,
        METH_VARARGS|METH_KEYWORDS, pyswe_calc__doc__},
    {"calc_ut", (PyCFunction) pyswe_calc_ut,
        METH_VARARGS|METH_KEYWORDS, pyswe_calc_ut__doc__},
    {"fixstar", (PyCFunction) pyswe_fixstar,
        METH_VARARGS|METH_KEYWORDS, pyswe_fixstar__doc__},
    {"fixstar_ut", (PyCFunction) pyswe_fixstar_ut,
        METH_VARARGS|METH_KEYWORDS, pyswe_fixstar_ut__doc__},
    {"nod_aps", (PyCFunction) pyswe_nod_aps,
        METH_VARARGS|METH_KEYWORDS, pyswe_nod_aps__doc__},
    {"nod_aps_ut", (PyCFunction) pyswe_nod_aps_ut,
        METH_VARARGS|METH_KEYWORDS, pyswe_nod_aps_ut__doc__},
    {"sidtime", (PyCFunction) pyswe_sidtime,
        METH_VARARGS|METH_KEYWORDS, pyswe_sidtime__doc__},
    {"sidtime0", (PyCFunction) pyswe_sidtime0,
        METH_VARARGS|METH_KEYWORDS, pyswe_sidtime0__doc__},
    {"houses_armc", (PyCFunction) pyswe_houses_armc,
        METH_VARARGS|METH_KEYWORDS, pyswe_houses_armc__doc__},
    {"houses_ex", (PyCFunction) pyswe_houses_ex,
        METH_VARARGS|METH_KEYWORDS, pyswe_houses_ex__doc__},
    {"house_pos", (PyCFunction) pyswe_house_pos,
        METH_VARARGS|METH_KEYWORDS, pyswe_house_pos__doc__},
    {"gauquelin_sector", (PyCFunction) pyswe_gauquelin_sector,
        METH_VARARGS|METH_KEYWORDS, pyswe_gauquelin_sector__doc__},
    {"house_name", (PyCFunction) pyswe_house_name,
        METH_VARARGS|METH_KEYWORDS, pyswe_house_name__doc__},
    {"julday", (PyCFunction) pyswe_julday,
        METH_VARARGS|METH_KEYWORDS, pyswe_julday__doc__},
    {"date_conversion", (PyCFunction) pyswe_date_conversion,
        METH_VARARGS|METH_KEYWORDS, pyswe_date_conversion__doc__},
    {"revjul", (PyCFunction) pyswe_revjul,
        METH_VARARGS|METH_KEYWORDS, pyswe_revjul__doc__},
    {"utc_to_jd", (PyCFunction) pyswe_utc_to_jd,
        METH_VARARGS|METH_KEYWORDS, pyswe_utc_to_jd__doc__},
    {"jdet_to_utc", (PyCFunction) pyswe_jdet_to_utc,
        METH_VARARGS|METH_KEYWORDS, pyswe_jdet_to_utc__doc__},
    {"jdut1_to_utc", (PyCFunction) pyswe_jdut1_to_utc,
        METH_VARARGS|METH_KEYWORDS, pyswe_jdut1_to_utc__doc__},
    {"utc_time_zone", (PyCFunction) pyswe_utc_time_zone,
        METH_VARARGS|METH_KEYWORDS, pyswe_utc_time_zone__doc__},
    {"deltat", (PyCFunction) pyswe_deltat,
        METH_VARARGS|METH_KEYWORDS, pyswe_deltat__doc__},
    {"get_tid_acc", (PyCFunction) pyswe_get_tid_acc,
        METH_NOARGS, pyswe_get_tid_acc__doc__},
    {"set_tid_acc", (PyCFunction) pyswe_set_tid_acc,
        METH_VARARGS|METH_KEYWORDS, pyswe_set_tid_acc__doc__},
    {"houses", (PyCFunction) pyswe_houses,
        METH_VARARGS|METH_KEYWORDS, pyswe_houses__doc__},
    {"time_equ", (PyCFunction) pyswe_time_equ,
        METH_VARARGS|METH_KEYWORDS, pyswe_time_equ__doc__},
    {"lmt_to_lat", (PyCFunction) pyswe_lmt_to_lat,
        METH_VARARGS|METH_KEYWORDS, pyswe_lmt_to_lat__doc__},
    {"lat_to_lmt", (PyCFunction) pyswe_lat_to_lmt,
        METH_VARARGS|METH_KEYWORDS, pyswe_lat_to_lmt__doc__},
    {"sol_eclipse_when_loc", (PyCFunction) pyswe_sol_eclipse_when_loc,
        METH_VARARGS|METH_KEYWORDS, pyswe_sol_eclipse_when_loc__doc__},
    {"lun_occult_when_loc", (PyCFunction) pyswe_lun_occult_when_loc,
        METH_VARARGS|METH_KEYWORDS, pyswe_lun_occult_when_loc__doc__},
    {"sol_eclipse_when_glob", (PyCFunction) pyswe_sol_eclipse_when_glob,
        METH_VARARGS|METH_KEYWORDS, pyswe_sol_eclipse_when_glob__doc__},
    {"sol_eclipse_how", (PyCFunction) pyswe_sol_eclipse_how,
        METH_VARARGS|METH_KEYWORDS, pyswe_sol_eclipse_how__doc__},
    {"sol_eclipse_where", (PyCFunction) pyswe_sol_eclipse_where,
        METH_VARARGS|METH_KEYWORDS, pyswe_sol_eclipse_where__doc__},
    {"lun_occult_when_glob", (PyCFunction) pyswe_lun_occult_when_glob,
        METH_VARARGS|METH_KEYWORDS, pyswe_lun_occult_when_glob__doc__},
    {"lun_occult_where", (PyCFunction) pyswe_lun_occult_where,
        METH_VARARGS|METH_KEYWORDS, pyswe_lun_occult_where__doc__},
    {"lun_eclipse_when", (PyCFunction) pyswe_lun_eclipse_when,
        METH_VARARGS|METH_KEYWORDS, pyswe_lun_eclipse_when__doc__},
    {"lun_eclipse_when_loc", (PyCFunction) pyswe_lun_eclipse_when_loc,
        METH_VARARGS|METH_KEYWORDS, pyswe_lun_eclipse_when_loc__doc__},
    {"lun_eclipse_how", (PyCFunction) pyswe_lun_eclipse_how,
        METH_VARARGS|METH_KEYWORDS, pyswe_lun_eclipse_how__doc__},
    {"rise_trans", (PyCFunction) pyswe_rise_trans,
        METH_VARARGS|METH_KEYWORDS, pyswe_rise_trans__doc__},
    {"pheno", (PyCFunction) pyswe_pheno,
        METH_VARARGS|METH_KEYWORDS, pyswe_pheno__doc__},
    {"pheno_ut", (PyCFunction) pyswe_pheno_ut,
        METH_VARARGS|METH_KEYWORDS, pyswe_pheno_ut__doc__},
    {"refrac", (PyCFunction) pyswe_refrac,
        METH_VARARGS|METH_KEYWORDS, pyswe_refrac__doc__},
    {"refrac_extended", (PyCFunction) pyswe_refrac_extended,
        METH_VARARGS|METH_KEYWORDS, pyswe_refrac_extended__doc__},
    {"set_lapse_rate", (PyCFunction) pyswe_set_lapse_rate,
        METH_VARARGS|METH_KEYWORDS, pyswe_set_lapse_rate__doc__},
    {"azalt", (PyCFunction) pyswe_azalt,
        METH_VARARGS|METH_KEYWORDS, pyswe_azalt__doc__},
    {"azalt_rev", (PyCFunction) pyswe_azalt_rev,
        METH_VARARGS|METH_KEYWORDS, pyswe_azalt_rev__doc__},
    {"cotrans", (PyCFunction) pyswe_cotrans,
        METH_VARARGS|METH_KEYWORDS, pyswe_cotrans__doc__},
    {"cotrans_sp", (PyCFunction) pyswe_cotrans_sp,
        METH_VARARGS|METH_KEYWORDS, pyswe_cotrans_sp__doc__},
    {"degnorm", (PyCFunction) pyswe_degnorm,
        METH_VARARGS|METH_KEYWORDS, pyswe_degnorm__doc__},
    {"csnorm", (PyCFunction) pyswe_csnorm,
        METH_VARARGS|METH_KEYWORDS, pyswe_csnorm__doc__},
    {"radnorm", (PyCFunction) pyswe_radnorm,
        METH_VARARGS|METH_KEYWORDS, pyswe_radnorm__doc__},
    {"rad_midp", (PyCFunction) pyswe_rad_midp,
        METH_VARARGS|METH_KEYWORDS, pyswe_rad_midp__doc__},
    {"deg_midp", (PyCFunction) pyswe_deg_midp,
        METH_VARARGS|METH_KEYWORDS, pyswe_deg_midp__doc__},
    {"split_deg", (PyCFunction) pyswe_split_deg,
        METH_VARARGS|METH_KEYWORDS, pyswe_split_deg__doc__},
    {"difcsn", (PyCFunction) pyswe_difcsn,
        METH_VARARGS|METH_KEYWORDS, pyswe_difcsn__doc__},
    {"difdegn", (PyCFunction) pyswe_difdegn,
        METH_VARARGS|METH_KEYWORDS, pyswe_difdegn__doc__},
    {"difcs2n", (PyCFunction) pyswe_difcs2n,
        METH_VARARGS|METH_KEYWORDS, pyswe_difcs2n__doc__},
    {"difdeg2n", (PyCFunction) pyswe_difdeg2n,
        METH_VARARGS|METH_KEYWORDS, pyswe_difdeg2n__doc__},
    {"difrad2n", (PyCFunction) pyswe_difrad2n,
        METH_VARARGS|METH_KEYWORDS, pyswe_difrad2n__doc__},
    {"csroundsec", (PyCFunction) pyswe_csroundsec,
        METH_VARARGS|METH_KEYWORDS, pyswe_csroundsec__doc__},
    {"d2l", (PyCFunction) pyswe_d2l,
        METH_VARARGS|METH_KEYWORDS, pyswe_d2l__doc__},
    {"day_of_week", (PyCFunction) pyswe_day_of_week,
        METH_VARARGS|METH_KEYWORDS, pyswe_day_of_week__doc__},
    {"cs2timestr", (PyCFunction) pyswe_cs2timestr,
        METH_VARARGS|METH_KEYWORDS, pyswe_cs2timestr__doc__},
    {"cs2lonlatstr", (PyCFunction) pyswe_cs2lonlatstr,
        METH_VARARGS|METH_KEYWORDS, pyswe_cs2lonlatstr__doc__},
    {"cs2degstr", (PyCFunction) pyswe_cs2degstr,
        METH_VARARGS|METH_KEYWORDS, pyswe_cs2degstr__doc__},
    {"fixstar_mag", (PyCFunction) pyswe_fixstar_mag,
        METH_VARARGS|METH_KEYWORDS, pyswe_fixstar_mag__doc__},
    {"heliacal_ut", (PyCFunction) pyswe_heliacal_ut,
        METH_VARARGS|METH_KEYWORDS, pyswe_heliacal_ut__doc__},
    {"heliacal_pheno_ut", (PyCFunction) pyswe_heliacal_pheno_ut,
        METH_VARARGS|METH_KEYWORDS, pyswe_heliacal_pheno_ut__doc__},
    {"vis_limit_mag", (PyCFunction) pyswe_vis_limit_mag,
        METH_VARARGS|METH_KEYWORDS, pyswe_vis_limit_mag__doc__},

#if PYSWE_USE_SWEPHELP
    /* pyswisseph/swephelp functions. */
    {"_jdnow", (PyCFunction) pyswe__jdnow,
        METH_NOARGS, pyswe__jdnow__doc__},
    {"_julday", (PyCFunction) pyswe__julday,
        METH_VARARGS|METH_KEYWORDS, pyswe__julday__doc__},
    {"_revjul", (PyCFunction) pyswe__revjul,
        METH_VARARGS|METH_KEYWORDS, pyswe__revjul__doc__},
    {"_degsplit", (PyCFunction) pyswe__degsplit,
        METH_VARARGS|METH_KEYWORDS, pyswe__degsplit__doc__},
    {"_signtostr", (PyCFunction) pyswe__signtostr,
        METH_VARARGS|METH_KEYWORDS, pyswe__signtostr__doc__},
    {"_house_system_name", (PyCFunction) pyswe__house_system_name,
        METH_VARARGS|METH_KEYWORDS, pyswe__house_system_name__doc__},
    {"_min_retro_time", (PyCFunction) pyswe__min_retro_time,
        METH_VARARGS|METH_KEYWORDS, pyswe__min_retro_time__doc__},
    {"_max_retro_time", (PyCFunction) pyswe__max_retro_time,
        METH_VARARGS|METH_KEYWORDS, pyswe__max_retro_time__doc__},
    {"_next_retro", (PyCFunction) pyswe__next_retro,
        METH_VARARGS|METH_KEYWORDS, pyswe__next_retro__doc__},
    {"_go_past", (PyCFunction) pyswe__go_past,
        METH_VARARGS|METH_KEYWORDS, pyswe__go_past__doc__},
    {"_next_aspect", (PyCFunction) pyswe__next_aspect,
        METH_VARARGS|METH_KEYWORDS, pyswe__next_aspect__doc__},
    {"_next_aspect2", (PyCFunction) pyswe__next_aspect2,
        METH_VARARGS|METH_KEYWORDS, pyswe__next_aspect2__doc__},
    {"_next_aspect_with", (PyCFunction) pyswe__next_aspect_with,
        METH_VARARGS|METH_KEYWORDS, pyswe__next_aspect_with__doc__},
    {"_next_aspect_with2", (PyCFunction) pyswe__next_aspect_with2,
        METH_VARARGS|METH_KEYWORDS, pyswe__next_aspect_with2__doc__},
    {"_next_aspect_cusp", (PyCFunction) pyswe__next_aspect_cusp,
        METH_VARARGS|METH_KEYWORDS, pyswe__next_aspect_cusp__doc__},
    {"_next_aspect_cusp2", (PyCFunction) pyswe__next_aspect_cusp2,
        METH_VARARGS|METH_KEYWORDS, pyswe__next_aspect_cusp2__doc__},
    {"_match_aspect", (PyCFunction) pyswe__match_aspect,
        METH_VARARGS|METH_KEYWORDS, pyswe__match_aspect__doc__},
    {"_match_aspect2", (PyCFunction) pyswe__match_aspect2,
        METH_VARARGS|METH_KEYWORDS, pyswe__match_aspect2__doc__},
    {"_match_aspect3", (PyCFunction) pyswe__match_aspect3,
        METH_VARARGS|METH_KEYWORDS, pyswe__match_aspect3__doc__},
    {"_match_aspect4", (PyCFunction) pyswe__match_aspect4,
        METH_VARARGS|METH_KEYWORDS, pyswe__match_aspect4__doc__},
    {"_years_diff", (PyCFunction) pyswe__years_diff,
        METH_VARARGS|METH_KEYWORDS, pyswe__years_diff__doc__},
    {"_geoc2d", (PyCFunction) pyswe__geoc2d,
        METH_VARARGS|METH_KEYWORDS, pyswe__geoc2d__doc__},
    {"_geolat2c", (PyCFunction) pyswe__geolat2c,
        METH_VARARGS|METH_KEYWORDS, pyswe__geolat2c__doc__},
    {"_geolon2c", (PyCFunction) pyswe__geolon2c,
        METH_VARARGS|METH_KEYWORDS, pyswe__geolon2c__doc__},
    {"_raman_houses", (PyCFunction) pyswe__raman_houses,
        METH_VARARGS|METH_KEYWORDS, pyswe__raman_houses__doc__},
    {"_lord", (PyCFunction) pyswe__lord,
        METH_VARARGS|METH_KEYWORDS, pyswe__lord__doc__},
    {"_long2rasi", (PyCFunction) pyswe__long2rasi,
        METH_VARARGS|METH_KEYWORDS, pyswe__long2rasi__doc__},
    {"_long2navamsa", (PyCFunction) pyswe__long2navamsa,
        METH_VARARGS|METH_KEYWORDS, pyswe__long2navamsa__doc__},
    {"_long2nakshatra", (PyCFunction) pyswe__long2nakshatra,
        METH_VARARGS|METH_KEYWORDS, pyswe__long2nakshatra__doc__},
    {"_get_nakshatra_name", (PyCFunction) pyswe__get_nakshatra_name,
        METH_VARARGS|METH_KEYWORDS, pyswe__get_nakshatra_name__doc__},
    {"_rasinorm", (PyCFunction) pyswe__rasinorm,
        METH_VARARGS|METH_KEYWORDS, pyswe__rasinorm__doc__},
    {"_rasi_dif", (PyCFunction) pyswe__rasi_dif,
        METH_VARARGS|METH_KEYWORDS, pyswe__rasi_dif__doc__},
    {"_rasi_dif2", (PyCFunction) pyswe__rasi_dif2,
        METH_VARARGS|METH_KEYWORDS, pyswe__rasi_dif2__doc__},
    {"_tatkalika_relation", (PyCFunction) pyswe__tatkalika_relation,
        METH_VARARGS|METH_KEYWORDS, pyswe__tatkalika_relation__doc__},
    {"_naisargika_relation", (PyCFunction) pyswe__naisargika_relation,
        METH_VARARGS|METH_KEYWORDS, pyswe__naisargika_relation__doc__},
    {"_residential_strength", (PyCFunction) pyswe__residential_strength,
        METH_VARARGS|METH_KEYWORDS, pyswe__residential_strength__doc__},
    {"_ochchabala", (PyCFunction) pyswe__ochchabala,
        METH_VARARGS|METH_KEYWORDS, pyswe__ochchabala__doc__},
    {"_saturn_4_stars", (PyCFunction) pyswe__saturn_4_stars,
        METH_VARARGS|METH_KEYWORDS, pyswe__saturn_4_stars__doc__},
#if SWH_USE_THREADS
    {"_lock", (PyCFunction) pyswe__lock,
        METH_VARARGS|METH_KEYWORDS, pyswe__lock__doc__},
    {"_unlock", (PyCFunction) pyswe__unlock,
        METH_VARARGS|METH_KEYWORDS, pyswe__unlock__doc__},
    {"_trylock", (PyCFunction) pyswe__trylock,
        METH_VARARGS|METH_KEYWORDS, pyswe__trylock__doc__},
#endif /* SWH_USE_THREADS */
#endif /* PYSWE_USE_SWEPHELP */
    {NULL, (PyCFunction) NULL, 0, NULL}
};

static char pyswe_module_documentation[] =
"Python extension to AstroDienst Swiss Ephemeris library.\n\n"
#if PYSWE_AUTO_SET_EPHE_PATH
"Import of this extension module does automagicaly set the ephemeris path"
" to \"" PYSWE_DEFAULT_EPHE_PATH "\".\n\n"
#endif
"Extended documentation can be found on AstroDienst website.\n\n"
"    Pyswisseph homepage: http://astrorigin.ch/pyswisseph/\n"
"    AstroDienst: http://www.astro.com/swisseph/\n"
"    PyPI: http://pypi.python.org/pypi/pyswisseph/";

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
    char buf[10];

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
    PyModule_AddIntConstant(m, "FLG_EQUATORIAL", SEFLG_EQUATORIAL);
    PyModule_AddIntConstant(m, "FLG_XYZ", SEFLG_XYZ);
    PyModule_AddIntConstant(m, "FLG_RADIANS", SEFLG_RADIANS);
    PyModule_AddIntConstant(m, "FLG_BARYCTR", SEFLG_BARYCTR);
    PyModule_AddIntConstant(m, "FLG_TOPOCTR", SEFLG_TOPOCTR);
    PyModule_AddIntConstant(m, "FLG_SIDEREAL", SEFLG_SIDEREAL);
    PyModule_AddIntConstant(m, "FLG_ICRS", SEFLG_ICRS);
    PyModule_AddIntConstant(m, "FLG_DPSIDEPS_1980", SEFLG_DPSIDEPS_1980);
    PyModule_AddIntConstant(m, "FLG_JPLHOR", SEFLG_JPLHOR);
    PyModule_AddIntConstant(m, "FLG_JPLHOR_APPROX", SEFLG_JPLHOR_APPROX);

    PyModule_AddIntConstant(m, "SIDBITS", SE_SIDBITS);
    PyModule_AddIntConstant(m, "SIDBIT_ECL_T0", SE_SIDBIT_ECL_T0);
    PyModule_AddIntConstant(m, "SIDBIT_SSY_PLANE", SE_SIDBIT_SSY_PLANE);

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
    PyModule_AddObject(m, "TJD_INVALID", Py_BuildValue("f", TJD_INVALID));
    PyModule_AddIntConstant(m, "SIMULATE_VICTORVB", SIMULATE_VICTORVB);

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

    PyModule_AddIntConstant(m, "PHOTOPIC_FLAG", SE_PHOTOPIC_FLAG);
    PyModule_AddIntConstant(m, "SCOTOPIC_FLAG", SE_SCOTOPIC_FLAG);
    PyModule_AddIntConstant(m, "MIXEDOPIC_FLAG", SE_MIXEDOPIC_FLAG);

#if PYSWE_USE_SWEPHELP
    /* *** Additional constants -- not swiss ephemeris ***/

    /* Aspects */
    PyModule_AddIntConstant(m, "CONJUNCTION", SWH_CONJUNCTION);
    PyModule_AddIntConstant(m, "SQUISEXTILE", SWH_SQUISEXTILE);
    PyModule_AddIntConstant(m, "SEMINOVILE", SWH_SEMINOVILE);
    PyModule_AddObject(m, "SQUISQUARE", Py_BuildValue("f", SWH_SQUISQUARE));
    PyModule_AddObject(m, "UNDECILE", Py_BuildValue("f", SWH_UNDECILE));
    PyModule_AddIntConstant(m, "SEMISEXTILE", SWH_SEMISEXTILE);
    PyModule_AddIntConstant(m, "SEMIQUINTILE", SWH_SEMIQUINTILE);
    PyModule_AddIntConstant(m, "NOVILE", SWH_NOVILE);
    PyModule_AddIntConstant(m, "SEMISQUARE", SWH_SEMISQUARE);
    PyModule_AddObject(m, "SEPTILE", Py_BuildValue("f", SWH_SEPTILE));
    PyModule_AddIntConstant(m, "SEXTILE", SWH_SEXTILE);
    PyModule_AddObject(m, "BIUNDECILE", Py_BuildValue("f", SWH_BIUNDECILE));
    PyModule_AddIntConstant(m, "QUINTILE", SWH_QUINTILE);
    PyModule_AddIntConstant(m, "BINOVILE", SWH_BINOVILE);
    PyModule_AddIntConstant(m, "SQUARE", SWH_SQUARE);
    PyModule_AddObject(m, "TRIUNDECILE", Py_BuildValue("f", SWH_TRIUNDECILE));
    PyModule_AddObject(m, "BISEPTILE", Py_BuildValue("f", SWH_BISEPTILE));
    PyModule_AddIntConstant(m, "TRINE", SWH_TRINE);
    PyModule_AddObject(m, "QUADUNDECILE", Py_BuildValue("f", SWH_QUADUNDECILE));
    PyModule_AddIntConstant(m, "SESQUISQUARE", SWH_SESQUISQUARE);
    PyModule_AddIntConstant(m, "BIQUINTILE", SWH_BIQUINTILE);
    PyModule_AddIntConstant(m, "QUINCUNX", SWH_QUINCUNX);
    PyModule_AddObject(m, "TRISEPTILE", Py_BuildValue("f", SWH_TRISEPTILE));
    PyModule_AddIntConstant(m, "QUATRONOVILE", SWH_QUATRONOVILE);
    PyModule_AddObject(m, "QUINUNDECILE", Py_BuildValue("f", SWH_QUINUNDECILE));
    PyModule_AddIntConstant(m, "OPPOSITION", SWH_OPPOSITION);

    /* Signs */
    PyModule_AddIntConstant(m, "ARIES", SWH_ARIES);
    PyModule_AddIntConstant(m, "TAURUS", SWH_TAURUS);
    PyModule_AddIntConstant(m, "GEMINI", SWH_GEMINI);
    PyModule_AddIntConstant(m, "CANCER", SWH_CANCER);
    PyModule_AddIntConstant(m, "LEO", SWH_LEO);
    PyModule_AddIntConstant(m, "VIRGO", SWH_VIRGO);
    PyModule_AddIntConstant(m, "LIBRA", SWH_LIBRA);
    PyModule_AddIntConstant(m, "SCORPIO", SWH_SCORPIO);
    PyModule_AddIntConstant(m, "SAGITTARIUS", SWH_SAGITTARIUS);
    PyModule_AddIntConstant(m, "CAPRICORN", SWH_CAPRICORN);
    PyModule_AddIntConstant(m, "AQUARIUS", SWH_AQUARIUS);
    PyModule_AddIntConstant(m, "PISCES", SWH_PISCES);

    PyModule_AddIntConstant(m, "MESHA", SWH_MESHA);
    PyModule_AddIntConstant(m, "VRISHABA", SWH_VRISHABA);
    PyModule_AddIntConstant(m, "MITHUNA", SWH_MITHUNA);
    PyModule_AddIntConstant(m, "KATAKA", SWH_KATAKA);
    PyModule_AddIntConstant(m, "SIMHA", SWH_SIMHA);
    PyModule_AddIntConstant(m, "KANYA", SWH_KANYA);
    PyModule_AddIntConstant(m, "THULA", SWH_THULA);
    PyModule_AddIntConstant(m, "VRISHIKA", SWH_VRISHIKA);
    PyModule_AddIntConstant(m, "DHANUS", SWH_DHANUS);
    PyModule_AddIntConstant(m, "MAKARA", SWH_MAKARA);
    PyModule_AddIntConstant(m, "KUMBHA", SWH_KUMBHA);
    PyModule_AddIntConstant(m, "MEENA", SWH_MEENA);

    /* Planets */
    PyModule_AddIntConstant(m, "RAVI", SWH_RAVI);
    PyModule_AddIntConstant(m, "CHANDRA", SWH_CHANDRA);
    PyModule_AddIntConstant(m, "BUDHA", SWH_BUDHA);
    PyModule_AddIntConstant(m, "SUKRA", SWH_SUKRA);
    PyModule_AddIntConstant(m, "KUJA", SWH_KUJA);
    PyModule_AddIntConstant(m, "GURU", SWH_GURU);
    PyModule_AddIntConstant(m, "SANI", SWH_SANI);
    PyModule_AddIntConstant(m, "RAHU", SWH_RAHU);
    PyModule_AddIntConstant(m, "KETU", SWH_KETU);

    PyModule_AddIntConstant(m, "SURYA", SWH_SURYA);
    PyModule_AddIntConstant(m, "SOMA", SWH_SOMA);
    PyModule_AddIntConstant(m, "SOUMYA", SWH_SOUMYA);
    PyModule_AddIntConstant(m, "BHARGAVA", SWH_BHARGAVA);
    PyModule_AddIntConstant(m, "ANGARAKA", SWH_ANGARAKA);
    PyModule_AddIntConstant(m, "BRIHASPATI", SWH_BRIHASPATI);
    PyModule_AddIntConstant(m, "MANDA", SWH_MANDA);
    PyModule_AddIntConstant(m, "THAMA", SWH_THAMA);
    PyModule_AddIntConstant(m, "SIKHI", SWH_SIKHI);

    /* Nakshatras */
    PyModule_AddIntConstant(m, "ASWINI", SWH_ASWINI);
    PyModule_AddIntConstant(m, "BHARANI", SWH_BHARANI);
    PyModule_AddIntConstant(m, "KRITIKHA", SWH_KRITHIKA);
    PyModule_AddIntConstant(m, "ROHINI", SWH_ROHINI);
    PyModule_AddIntConstant(m, "MRIGASIRA", SWH_MRIGASIRA);
    PyModule_AddIntConstant(m, "ARIDRA", SWH_ARIDRA);
    PyModule_AddIntConstant(m, "PUNARVASU", SWH_PUNARVASU);
    PyModule_AddIntConstant(m, "PUSHYAMI", SWH_PUSHYAMI);
    PyModule_AddIntConstant(m, "ASLESHA", SWH_ASLESHA);
    PyModule_AddIntConstant(m, "MAKHA", SWH_MAKHA);
    PyModule_AddIntConstant(m, "PUBBA", SWH_PUBBA);
    PyModule_AddIntConstant(m, "UTTARA", SWH_UTTARA);
    PyModule_AddIntConstant(m, "HASTA", SWH_HASTA);
    PyModule_AddIntConstant(m, "CHITTA", SWH_CHITTA);
    PyModule_AddIntConstant(m, "SWATHI", SWH_SWATHI);
    PyModule_AddIntConstant(m, "VISHAKA", SWH_VISHAKA);
    PyModule_AddIntConstant(m, "ANURADHA", SWH_ANURADHA);
    PyModule_AddIntConstant(m, "JYESTA", SWH_JYESTA);
    PyModule_AddIntConstant(m, "MOOLA", SWH_MOOLA);
    PyModule_AddIntConstant(m, "POORVASHADA", SWH_POORVASHADA);
    PyModule_AddIntConstant(m, "UTTARASHADA", SWH_UTTARASHADA);
    PyModule_AddIntConstant(m, "SRAVANA", SWH_SRAVANA);
    PyModule_AddIntConstant(m, "DHANISHTA", SWH_DHANISHTA);
    PyModule_AddIntConstant(m, "SATABISHA", SWH_SATABISHA);
    PyModule_AddIntConstant(m, "POORVABHADRA", SWH_POORVABHADRA);
    PyModule_AddIntConstant(m, "UTTARABHADRA", SWH_UTTARABHADRA);
    PyModule_AddIntConstant(m, "REVATHI", SWH_REVATHI);

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
