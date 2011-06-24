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

/** @file swhutil.c
** @brief swephelp utilities
*/

#ifdef __cplusplus
extern "C"
{
#endif

#include "swhutil.h"
#include <string.h>
#include <swephexp.h>

#if SWH_USE_THREADS

#include <pthread.h>

static pthread_mutex_t swh_mutex = PTHREAD_MUTEX_INITIALIZER;

void swh_lock(void)
{
    pthread_mutex_lock(&swh_mutex);
}

void swh_unlock(void)
{
    pthread_mutex_unlock(&swh_mutex);
}

int swh_trylock(void)
{
    return pthread_mutex_trylock(&swh_mutex);
}

#endif /* SWH_USE_THREADS */

/** @brief
*/
int swh_set_globals(swh_Globals *glob)
{
    if (strlen(glob->ephe_path) != 0)
        swe_set_ephe_path(glob->ephe_path);
    if (strlen(glob->jpl_path) != 0)
        swe_set_jpl_file(glob->jpl_path);
    if (!(glob->topo_lon > 180 || glob->topo_lon < -180 ||
        glob->topo_lat > 90 || glob->topo_lat < -90 ||
        glob->topo_alt < 0))
        swe_set_topo(glob->topo_lon, glob->topo_lat, glob->topo_alt);
    if (glob->sidmode > -1 && glob->sidmode < 256)
        swe_set_sid_mode(glob->sidmode, glob->t0, glob->ayant0);
    return 0;
}

#ifdef __cplusplus
} /* extern "C" */
#endif
