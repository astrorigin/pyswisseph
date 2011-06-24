Pyswisseph Readme
-----------------

This directory contains the source of Python extension to the Swiss Ephemeris,
along with the swisseph source itself, created by AstroDienst.

  - Homepage: http://pyswisseph.chaosorigin.com/
  - Python Package Index: http://pypi.python.org/pypi/pyswisseph/
  - AstroDienst: http://www.astro.com/swisseph/

For python version 2.x or 3.x
-----------------------------

  - To install in sites-packages: « python setup.py install »
  - To build extension only: « python setup.py build »

64 bits platforms
-----------------

Compilation on 64 bits platform will not work with the original swisseph
makefiles, unless you add -fPIC to the compilation flags.

The swisseph shipped with this package has an updated Makefile that should
work.

Licensing
---------
Either GNU Public License v2 or later, or Swiss Ephemeris Professional License.

The choice must be made before the software developer distributes software
containing parts of Swiss Ephemeris to others, and before any public service
using the developed software is activated.

If the developer choses the GNU GPL software license, he or she must fulfill
the conditions of that license, which includes the obligation to place his or
her whole software project under the GNU GPL or a compatible license.
See http://www.gnu.org/licenses/old-licenses/gpl-2.0.html

If the developer choses the Swiss Ephemeris Professional license, he must
follow the instructions below and purchase the Swiss Ephemeris Professional
Edition from Astrodienst and sign the corresponding license contract.

For more information about licensing see AstroDienst website:
http://www.astro.com/swisseph/

Contact
-------
Any feedback about pyswisseph is welcome:
Stanislas Marquis <stnsls@gmail.com>

..
