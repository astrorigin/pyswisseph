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

/** @file swephelp.h
** @brief swephelp export header file
**
** Main swephelp header, imports all swephelp functions and defines.
*/

#ifndef SWEPHELP_H
#define SWEPHELP_H

/* pollute namespace with fancy aliases */
#ifndef SWH_USE_ALIASES
#define SWH_USE_ALIASES     1
#endif

/* use a global mutex to protect swisseph data */
#ifndef SWH_USE_THREADS
#define SWH_USE_THREADS     1
#endif

/* include swisseph functions */
#include <swephexp.h>

/* swephelp headers */
#include "swhdatetime.h"
#include "swhdef.h"
#include "swhformat.h"
#include "swhgeo.h"
#include "swhmisc.h"
#include "swhraman.h"
#include "swhsearch.h"
#include "swhutil.h"

#endif /* SWEPHELP_H */
/* vi: set fenc=utf-8 ff=unix et sw=4 ts=4 sts=4 : */
