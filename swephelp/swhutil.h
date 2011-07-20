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

/** @file swhutil.h
** @brief swephelp utilities
*/

#ifndef SWHUTIL_H
#define SWHUTIL_H

#ifndef SWH_USE_THREADS
#define SWH_USE_THREADS     1
#endif

#ifndef SWH_USE_ALIASES
#define SWH_USE_ALIASES     1
#endif

#if SWH_USE_THREADS

#ifdef __cplusplus
extern "C"
{
#endif

void swh_lock(void);

void swh_unlock(void);

int swh_trylock(void);

typedef struct
{
    char    ephe_path[64]; /* swiss eph files path */
    char    jpl_path[64]; /* jpl file path */
    double  topo_lon; /* longitude. set to invalid value disables checking topo */
    double  topo_lat; /* latitude */
    int     topo_alt; /* altitude */
    int     sidmode; /* sidereal mode */
    double  t0; /* sidmode param */
    double  ayant0; /* sidmode param */
} swh_Globals;

void swh_globals_init(swh_Globals *glob);

int swh_set_globals(swh_Globals *glob);

#if SWH_USE_ALIASES

#define SWH_LOCK()      swh_lock()
#define SWH_UNLOCK()    swh_unlock()
#define SWH_TRYLOCK()   swh_trylock()

#endif /* SWH_USE_ALIASES */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SWH_USE_THREADS */
#endif /* SWHUTIL_H */
