#!/usr/bin/env python
# -*- coding: utf-8 -*-

#   This file is part of Pyswisseph.
#
#   Copyright (c) 2007-2022 Stanislas Marquis <stan@astrorigin.com>
#
#   Pyswisseph is free software: you can redistribute it and/or modify
#   it under the terms of the GNU Affero General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   Pyswisseph is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU Affero General Public License for more details.
#
#   You should have received a copy of the GNU Affero General Public License
#   along with Pyswisseph.  If not, see <https://www.gnu.org/licenses/>.

# This docstring is published at the PyPI
# and is used as Distutils long description:
"""Python extension to AstroDienst Swiss Ephemeris library.

The Swiss Ephemeris is the de-facto standard library for astrological
calculations. It is a high-precision ephemeris, based upon the DE431
ephemerides from NASA's JPL, and covering the time range 13201 BC to AD 17191.

::

    >>> import swisseph as swe
    >>> # first set path to ephemeris files
    >>> swe.set_ephe_path('/usr/share/sweph/ephe')
    >>> # find time of next lunar eclipse
    >>> jd = swe.julday(2007, 3, 3) # julian day
    >>> res = swe.lun_eclipse_when(jd)
    >>> ecltime = swe.revjul(res[1][0])
    >>> print(ecltime)
    (2007, 3, 3, 23.347926892340183)
    >>> # get ecliptic position of asteroid 13681 "Monty Python"
    >>> jd = swe.julday(2008, 3, 21)
    >>> xx, rflags = swe.calc_ut(jd, swe.AST_OFFSET+13681)
    >>> # print longitude
    >>> print(xx[0])
    0.09843983166646618

:Documentation: https://astrorigin.com/pyswisseph
:Repository: https://github.com/astrorigin/pyswisseph

"""

import os.path, sys
from setuptools import setup, Extension
from glob import glob

# Pyswisseph version string
# Our version string gets the version of the swisseph library (X.XX.XX)
# and our increment as suffix (.X), plus an eventual pre-release tag (.devX).
#
# Note about Github Actions:
# Each push tagged with vX.XX.XX.X triggers a stable release on PyPI.
# Each push tagged with vX.XX.XX.X.devX triggers a pre-release on PyPI.
# Do not forget to: increment version string right here, and modify file
# pyswisseph.c (PYSWISSEPH_VERSION).
VERSION = '2.10.03.1'

# Corresponding swisseph version string (normalized for pkg-config)
swe_version = '2.10.3'

# Debian libswe-dev detection
# Set to True to try and find libswe in system.
# Set to False to use bundled libswe.
swe_detection = True

# Include additional functions and constants (contrib submodule)
use_swephelp = True

# Sqlite3 detection
# Set to True to try and find libsqlite3-dev in system.
# Set to False to use bundled sqlite3.
# This is relevant only for the contrib submodule.
sqlite3_detection = True

# Compile flags
cflags = []
if sys.platform in ['win32', 'win_amd64']: # Windows
    cflags.append('-D_CRT_SECURE_NO_WARNINGS')
elif sys.platform == 'darwin': # OSX
    cflags.append('-Wno-error=unused-command-line-argument-hard-error-in-future')
else: # Linux etc
    pass

# Link flags
ldflags = []

# Should not modify below...

# Test for pkg-config
has_pkgconfig = False
if swe_detection or (use_swephelp and sqlite3_detection):
    print('Searching for pkg-config...')
    try:
        import subprocess
        try:
            subprocess.check_output(['pkg-config'], stderr=subprocess.STDOUT)
        except AttributeError: # Python < 2.7
            print('Python < 2.7, skipping pkg-config')
    except subprocess.CalledProcessError:
        has_pkgconfig = True
        print('Found pkg-config')
    except OSError:
        print('pkg-config not found')
    except ImportError: # Python < 2.4
        print('Python < 2.4, skipping pkg-config')
    #

# Find libswe-dev
libswe_found = False
if has_pkgconfig and swe_detection:
    print('Searching for libswe-dev...')
    try:
        out = subprocess.check_output(
            ['pkg-config', '--modversion', 'swe'],
            stderr=subprocess.STDOUT).decode().strip()
        if out != swe_version:
            raise ValueError
        out = subprocess.check_output(
            ['pkg-config', '--cflags-only-I', 'swe'],
            stderr=subprocess.STDOUT).decode().strip().split(' ')
        swe_includes = [x[2:] for x in out if x != '']
        out = subprocess.check_output(
            ['pkg-config', '--libs-only-l', 'swe'],
            stderr=subprocess.STDOUT).decode().strip().split(' ')
        swe_libs = [x[2:] for x in out if x != '']
        swe_sources = []
        swe_depends = []
        swe_defines = [('PYSWE_DEFAULT_EPHE_PATH',
            '"/usr/share/libswe:/usr/local/share/libswe"')]
        libswe_found = True
        print('pkg-config found libswe-dev '+swe_version)
    except subprocess.CalledProcessError:
        print('pkg-config has not found libswe-dev '+swe_version)
    except ValueError:
        print('pkg-config found version '+out+', but not '+swe_version)
    #

if not libswe_found: # using internal libswe
    print('Using internal libswe')
    swe_includes = ['libswe']
    swe_sources = [
        'libswe/swecl.c',
        'libswe/swedate.c',
        'libswe/swehel.c',
        'libswe/swehouse.c',
        'libswe/swejpl.c',
        'libswe/swemmoon.c',
        'libswe/swemplan.c',
        'libswe/sweph.c',
        'libswe/swephlib.c']
    swe_depends = [
        'libswe/swedate.h',
        'libswe/swehouse.h',
        'libswe/swemptab.h',
        'libswe/swenut2000a.h',
        'libswe/sweph.h',
        #'libswe/swedll.h',
        'libswe/swejpl.h',
        'libswe/sweodef.h',
        'libswe/swephexp.h',
        'libswe/swephlib.h']
    swe_libs = []
    swe_defines = []

# Find sqlite3
sqlite3_found = False
if has_pkgconfig and use_swephelp and sqlite3_detection:
    print('Searching for libsqlite3-dev')
    try:
        out = subprocess.check_output(
            ['pkg-config', '--cflags-only-I', 'sqlite3'],
            stderr=subprocess.STDOUT).decode().strip().split(' ')
        sqlite3_includes = [x[2:] for x in out if x != '']
        out = subprocess.check_output(
            ['pkg-config', '--libs-only-l', 'sqlite3'],
            stderr=subprocess.STDOUT).decode().strip().split(' ')
        sqlite3_libs = [x[2:] for x in out if x != '']
        sqlite3_defines = []
        sqlite3_sources = []
        sqlite3_depends = []
        sqlite3_found = True
        print('pkg-config has found libsqlite3-dev')
    except subprocess.CalledProcessError:
        print('pkg-config has not found libsqlite3-dev')
    #

if use_swephelp and not sqlite3_found: # using internal sqlite3
    print('Using internal sqlite3')
    sqlite3_defines = [
        ('SQLITE_DEFAULT_AUTOVACUUM', 1),
        ('SQLITE_DEFAULT_FOREIGN_KEYS', 1),
        ('SQLITE_DEFAULT_MEMSTATUS', 0),
        ('SQLITE_DEFAULT_WAL_SYNCHRONOUS', 1),
        ('SQLITE_DOESNT_MATCH_BLOBS', 1),
        ('SQLITE_DQS', 0),
        ('SQLITE_ENABLE_COLUMN_METADATA', 1),
        ('SQLITE_ENABLE_FTS4', 1),
        ('SQLITE_MAX_EXPR_DEPTH', 0),
        ('SQLITE_OMIT_DEPRECATED', 1),
        ('SQLITE_OMIT_SHARED_CACHE', 1),
        ('SQLITE_SECURE_DELETE', 1),
        ('SQLITE_THREADSAFE', 1)
    ]
    sqlite3_includes = ['swephelp/sqlite3']
    sqlite3_sources = ['swephelp/sqlite3/sqlite3.c']
    sqlite3_depends = ['swephelp/sqlite3/sqlite3.h']
    sqlite3_libs = []

# Defines
defines = swe_defines
if use_swephelp:
    defines += sqlite3_defines

# Include paths
includes = swe_includes
if use_swephelp:
    includes += ['swephelp']
    includes += sqlite3_includes

# Sources
sources = ['pyswisseph.c'] + swe_sources
if use_swephelp:
    sources += glob('swephelp/*.c')
    sources += glob('swephelp/*.cpp')
    sources += sqlite3_sources

# Depends
depends = swe_depends
if use_swephelp:
    depends += glob('swephelp/*.h')
    depends += glob('swephelp/*.hpp')
    depends += sqlite3_depends

# Libraries
libraries = swe_libs
if use_swephelp:
    libraries += sqlite3_libs

# Pyswisseph extension
swemodule = Extension(
    'swisseph',
    define_macros = defines,
    depends = depends,
    extra_compile_args = cflags,
    extra_link_args = ldflags,
    include_dirs = includes,
    libraries = libraries,
    sources = sources
    )

setup(
    name = 'pyswisseph',
    version = VERSION,
    description = 'Python extension to the Swiss Ephemeris',
    long_description = __doc__,
    long_description_content_type = 'text/x-rst',
    author = 'Stanislas Marquis',
    author_email = 'stan@astrorigin.com',
    url = 'https://astrorigin.com/pyswisseph',
    download_url = 'https://pypi.org/project/pyswisseph',
    classifiers = [
        'Development Status :: 3 - Alpha',
        'Intended Audience :: Developers',
        'Intended Audience :: Religion',
        'License :: OSI Approved :: GNU Affero General Public License v3',
        'Programming Language :: C',
        'Programming Language :: Python',
        'Programming Language :: Python :: 2',
        'Programming Language :: Python :: 3',
        'Topic :: Religion',
        'Topic :: Scientific/Engineering :: Astronomy',
        'Topic :: Software Development :: Libraries :: Python Modules'
        ],
    keywords = 'Astrology Ephemeris Swisseph',
    ext_modules = [swemodule],
    setup_requires = ['wheel'],
    python_requires = '>=3.5',
    test_suite = 'tests'
    )

# vi: set fenc=utf-8 ff=unix et sw=4 ts=4 sts=4 :
