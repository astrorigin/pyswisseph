=================
Pyswisseph README
=================

This package contains the Python extension to the Swiss Ephemeris
(or Pyswisseph, or python-swisseph as you wish), along with the
SwissEph source code itself, created by AstroDienst.

  - Pyswisseph Homepage:    http://astrorigin.ch/pyswisseph
  - Downloads source:       http://pypi.python.org/pypi/pyswisseph
  - Fork me on GitHub:      https://github.com/astrorigin/pyswisseph
  - AstroDienst:            http://www.astro.com/swisseph


Linux & Unix-like systems with GCC
==================================

To install in sites-packages, just the usual way:

    « python setup.py install »
  
To build the extension only:
    
    « python setup.py build »


Windows
=======

With Windows, it is recommended to use MSVC 201x or MinGW, with help of
the CMake build system.

    -> CMake website: http://cmake.org/

Please note:

MinGW: directory separator of PYSWE_DEFAULT_EPHE_PATH must be entered as a
triple backslash: "\\\".   Eg: C:\\\swisseph\\\ephe

MSVC: directory separator of PYSWE_DEFAULT_EPHE_PATH must be entered as a
double backslash: "\\".   Eg: C:\\swisseph\\ephe


Licensing
=========

The Pyswisseph package adopts the GNU Public License version 2 (or later).
See the COPYING file.


Contact
=======

Any feedback about Pyswisseph is welcome:
Stanislas Marquis <smarquis@astrorigin.ch>

..
