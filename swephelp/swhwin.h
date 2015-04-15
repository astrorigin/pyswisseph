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

/** @file swhwin.h
** @brief swephelp windowz specific header
*/

/* define WIN32 for MSVC compilers */
#ifdef _WIN32
#define WIN32
#endif

#ifndef SWHWIN_H
#define SWHWIN_H

#ifdef WIN32

#define lround(num) \
        ((long)(num > 0 ? num + 0.5 : ceil(num - 0.5)))

#endif /* WIN32 */
#endif /* SWHWIN_H */
/* vi: set fenc=utf8 ff=unix et sw=4 ts=4 sts=4 : */
