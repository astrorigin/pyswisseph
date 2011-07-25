#!/usr/bin/env python
# -*- coding: utf-8 -*-

#   This file is part of Pyswisseph.
#
#   Copyright (c) 2007-2011 Stanislas Marquis <stnsls@gmail.com>
#
#   Pyswisseph is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   Pyswisseph is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with Pyswisseph.  If not, see <http://www.gnu.org/licenses/>.

"""Python extension to AstroDienst Swiss Ephemeris library.

Swiss Ephemeris homepage: http://www.astro.com/swisseph/

Compatible with Python 2.x and 3.x.

Usage example:

>>> import swisseph as swe
>>> swe.set_ephe_path('/usr/share/ephe') # set path to ephemeris files
>>> now = swe.julday(2007,3,3) # get Julian day number
>>> res = swe.lun_eclipse_when(now) # find next lunar eclipse (from now on)
>>> ecltime = swe.revjul(res[1][0]) # get date UTC
>>> ecltime
(2007, 3, 3, 23.347975596785545)
>>> jd = swe.julday(2008,3,21)
>>> swe.calc_ut(jd, swe.AST_OFFSET+13681)[0] # asteroid Monty Python
0.098474291148756998
>>> help(swe)

Standard installation (unixes): ``# python setup.py install``

"""

import os.path, sys
from distutils.core import setup, Extension

# Pyswisseph version
VERSION = '1.77.00-0'

# This builds libswe
if 'build' in sys.argv or 'install' in sys.argv:
    instdir = os.path.dirname(os.path.abspath(__file__))
    os.chdir(os.path.join(instdir, 'src'))
    os.system('make clean')
    os.system('make libswe.a')
    os.chdir(instdir)

# Extension
swemodule = Extension(
    'swisseph',
    include_dirs = ['src', 'swephelp'],
    libraries = ['swe'],
    library_dirs = ['src'],
    extra_compile_args= ['-std=gnu99'],
    sources = [
        'pyswisseph.c',
        'swephelp/swhdatetime.c',
        'swephelp/swhformat.c',
        'swephelp/swhsearch.c',
        'swephelp/swhraman.c',
        'swephelp/swhgeo.c',
        'swephelp/swhutil.c'
        ]
    )

setup(
    name = 'pyswisseph',
    version = VERSION,
    description = 'Python extension to the Swiss Ephemeris',
    long_description = __doc__,
    author = 'S.Marquis',
    author_email = 'stnsls@gmail.com',
    url = 'http://pyswisseph.chaosorigin.com/',
    download_url = 'http://pypi.python.org/pypi/pyswisseph',
    classifiers = [
        'Development Status :: 5 - Production/Stable',
        'Intended Audience :: Developers',
        'Intended Audience :: Religion',
        'License :: OSI Approved :: GNU General Public License (GPL)',
        'Programming Language :: C',
        'Programming Language :: Python',
        'Programming Language :: Python :: 3',
        'Topic :: Religion',
        'Topic :: Scientific/Engineering :: Astronomy',
        'Topic :: Software Development :: Libraries :: Python Modules'
        ],
    keywords = 'Astrology Ephemeris Swisseph',
    ext_modules = [swemodule]
    )

# vi: set ai et sw=4:

