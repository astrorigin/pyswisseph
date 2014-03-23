#!/usr/bin/env python
# -*- coding: utf-8 -*-

#   This file is part of Pyswisseph.
#
#   Copyright (c) 2007-2014 Stanislas Marquis <smarquis@astrorigin.ch>
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

# This docstring is published at the PyPI
# and is used as Distutils long description:
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

# Pyswisseph version string
# Our version string gets the version of the swisseph library (x.xx.xx)
# and our increment as suffix (-x).
VERSION = '2.00.00-2'

# Corresponding swisseph version string
swe_version = '2.00.00'

# libswe-dev detection
# Set to True to find libswe in system.
# Set to False to use internal libswe.
swe_detection = True

# Additional functions and constants
use_swephelp = True

# Compile flags
cflags = ['-std=gnu99']

# Link flags
ldflags = []

# Don't modify below

import os.path, sys
from distutils.core import setup, Extension

# Test for pkg-config
has_pkgconfig = False
if swe_detection:
    print('Searching system libswe...')
    try:
        import subprocess
        subprocess.check_output(['pkg-config'], stderr=subprocess.STDOUT)
    except subprocess.CalledProcessError:
        has_pkgconfig = True
        print('Found pkg-config')
    except OSError:
        print('pkg-config not found')
        pass
    except ImportError: # Python < 2.4
        pass
    #

# Find libswe-dev
libswe_found = False
if has_pkgconfig:
    try:
        swe_includes = subprocess.check_output(
            ['pkg-config', '--cflags', 'libswe-'+swe_version],
            stderr=subprocess.STDOUT)
        swe_libs = subprocess.check_output(
            ['pkg-config', '--libs', 'libswe-'+swe_version],
            stderr=subprocess.STDOUT)
        swe_sources = []
        swe_depends = []
        swe_defines = [('PYSWE_DEFAULT_EPHE_PATH',
            '"/usr/share/libswe/ephe2:/usr/share/libswe/ephe"')]
        libswe_found = True
        print('pkg-config found libswe-'+swe_version)
    except subprocess.CalledProcessError:
        pass
    #

# Another attempt at finding libswe-dev -- without pkg-config
# (pkg-config may be uninstalled but pc file should be in place)
# (and assuming there is only one version installed...)
if ( swe_detection and not libswe_found
    and os.path.isfile( '/usr/lib/pkgconfig/libswe-'+swe_version+'.pc' )):
    swe_includes = ['/usr/include']
    swe_sources = []
    swe_depends = []
    swe_libs = ['swe']
    swe_defines = [('PYSWE_DEFAULT_EPHE_PATH',
        '"/usr/share/libswe/ephe2:/usr/share/libswe/ephe"')]
    print('Found system libswe')
else: # using internal libswe
    swe_includes = ['libswe']
    swe_sources = [
        'libswe/swecl.c',
        'libswe/swedate.c',
        'libswe/swehel.c',
        'libswe/swehouse.c',
        'libswe/swejpl.c',
        'libswe/swemmoon.c',
        'libswe/swemplan.c',
        #libswe/swemptab.c # included c file goes in depends
        'libswe/swepcalc.c',
        'libswe/sweph.c',
        'libswe/swephlib.c']
    swe_depends = [
        'libswe/swedate.h',
        'libswe/swehouse.h',
        'libswe/swemptab.c',
        'libswe/swenut2000a.h',
        'libswe/swepcalc.h',
        'libswe/sweph.h',
        #'libswe/swedll.h',
        'libswe/swejpl.h',
        'libswe/sweodef.h',
        'libswe/swephexp.h',
        'libswe/swephlib.h']
    swe_libs = []
    swe_defines = []
    print('Using internal libswe')

# Includes
includes = swe_includes
if use_swephelp:
    includes += ['swephelp']

# Sources
sources = ['pyswisseph.c'] + swe_sources
if use_swephelp:
    sources += [
        'swephelp/swhdatetime.c',
        'swephelp/swhformat.c',
        'swephelp/swhgeo.c',
        'swephelp/swhmisc.c',
        'swephelp/swhraman.c',
        'swephelp/swhsearch.c',
        'swephelp/swhutil.c'
        ]
    #

# Depends
depends = swe_depends
if use_swephelp:
    depends += [
        'swephelp/swephelp.h',
        'swephelp/swhdef.h',
        'swephelp/swhgeo.h',
        'swephelp/swhraman.h',
        'swephelp/swhutil.h',
        'swephelp/swhdatetime.h',
        'swephelp/swhformat.h',
        'swephelp/swhmisc.h',
        'swephelp/swhsearch.h',
        'swephelp/swhwin.h'
        ]
    #

# Pyswisseph extension
swemodule = Extension(
    'swisseph',
    define_macros = swe_defines,
    depends = depends,
    extra_compile_args = cflags,
    extra_link_args = ldflags,
    include_dirs = includes,
    libraries = swe_libs,
    sources = sources 
    )

setup(
    name = 'pyswisseph',
    version = VERSION,
    description = 'Python extension to the Swiss Ephemeris',
    long_description = __doc__,
    author = 'Stanislas Marquis',
    author_email = 'smarquis@astrorigin.ch',
    url = 'http://astrorigin.ch/pyswisseph',
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

# vi: set fenc=utf-8 ff=unix et sw=4 ts=4 sts=4 :
