=================
Pyswisseph README
=================

This is the Python extension to the Swiss Ephemeris by AstroDienst.

The Swiss Ephemeris is the de-facto standard library for astrological
calculations.

  - Pyswisseph Homepage:    https://astrorigin.com/pyswisseph
  - Clone with command:     git clone --recurse-submodules https://github.com/astrorigin/pyswisseph
  - Launchpad PPA:          https://launchpad.net/~astrorigin/+archive/ubuntu/python-swisseph
  - Python Package Index:   https://pypi.org/project/pyswisseph
  - AstroDienst:            https://www.astro.com/swisseph

Licensing
=========

The Pyswisseph package adopts the GNU Affero General Public License version 3.
See the ``LICENSE.txt`` file.

The original swisseph library is distributed under a dual licensing system:
GNU Affero General Public License, or Swiss Ephemeris Professional License.
For more information, see file ``libswe/LICENSE``.

Test Suite
==========

For now, the tests can be run with the standard ``python3 setup.py test``
command. For them to pass successfully, you need a basic set of ephemerides
files installed somewhere on your system:

 - ``seas_18.se1``
 - ``sefstars.txt``
 - ``semo_18.se1``
 - ``sepl_18.se1``

All downloadable from https://www.astro.com/ftp/swisseph/ephe/

The path to the directory containing those files must be indicated in the
environment variable ``SE_EPHE_PATH``.

For example, on a system with the ``env`` command, you can do::

    env SE_EPHE_PATH="/usr/share/sweph/ephe" python3 setup.py test

Credits
=======

Author: Stanislas Marquis <stan(at)astrorigin.com>

PyPI maintainer (branch pypi): Jonathan de Jong <jonathan(at)automatia.nl>

..
