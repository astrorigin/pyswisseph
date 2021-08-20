===========================================
Specialities (going beyond common interest)
===========================================

True or apparent positions
==========================

Common ephemerides supply apparent geocentric positions. Since the journey of
the light from a planet to the Earth takes some time, the planets are never
seen where they actually are, but where they were a few minutes or hours
before. Astrology uses to work with the positions we see. (More precisely: with
the positions we would see, if we stood at the center of the Earth and could
see the sky. Actually, the geographical position of the observer could be of
importance as well and topocentric positions could be computed, but this is
usually not taken into account in astrology.). The geocentric position for the
Earth (``EARTH``) is returned as zero.

To compute the true geometrical position of a planet, disregarding light-time,
you have to add the flag ``FLG_TRUEPOS``.

Topocentric positions
=====================

To compute topocentric positions, i.e. positions referred to the place of the
observer (the birth place) rather than to the center of the Earth, do as
follows:

First call ``set_topo()``. Then add the flag ``FLG_TOPOCTR`` for the
call to ``calc()``.

.. autofunction:: swisseph.set_topo
    :noindex:

For example:

.. code-block:: python

    swe.set_topo(8.58, 47.33, 473) # Zollikon, ch
    flags = swe.FLG_SWIEPH | swe.FLG_SPEED | swe.FLG_TOPOCTR
    xx, retflags = swe.calc_ut(jdut, swe.SUN, flags)

Heliocentric positions
======================

To compute a heliocentric position, add ``FLG_HELCTR``.

A heliocentric position can be computed for all planets including the moon.
For the sun, lunar nodes and lunar apogees the coordinates are returned as
zero; no error message appears.

Barycentric positions
=====================

``FLG_BARYCTR`` yields coordinates as referred to the solar system
barycenter. However, this option is not completely implemented. It was used for
program tests during development. It works only with the JPL and the Swiss
Ephemeris, not with the Moshier ephemeris; and only with physical bodies, but
not with the nodes and the apogees.

Moreover, the barycentric Sun of Swiss Ephemeris has "only" a precision of
0.1". Higher accuracy would have taken a lot of storage, on the other hand it
is not needed for precise geocentric and heliocentric positions. For more
precise barycentric positions the JPL ephemeris file should be used.

A barycentric position can be computed for all planets including the sun and
moon. For the lunar nodes and lunar apogees the coordinates are returned as
zero; no error message appears.

Astrometric positions
=====================

For astrometric positions, which are sometimes given in the Astronomical
Almanac, the light-time correction is computed, but annual aberration and the
light-deflection by the sun neglected. This can be done with
``FLG_NOABERR`` and ``FLG_NOGDEFL``. For positions related to the mean
equinox of 2000, you must set ``FLG_J2000`` and ``FLG_NONUT``, as well.

True or mean equinox of date
============================

``calc()`` usually computes the positions as referred to the true equinox
of the date (i.e. with nutation). If you want the mean equinox, you can turn
nutation off, using the flag bit ``FLG_NONUT``.

J2000 positions and positions referred to other equinoxes
=========================================================

``calc()`` usually computes the positions as referred to the equinox of
date. ``FLG_J2000`` yields data referred to the equinox J2000. For
positions referred to other equinoxes, ``FLG_SIDEREAL`` has to be set and
the equinox specified by ``set_sid_mode()``. For more information, refer to
chapter TODO

Sidereal positions
==================

To compute sidereal positions, set bit ``FLG_SIDEREAL`` and use the
function ``set_sid_mode()`` in order to define the ayanamsha you want.
For more information, read to chapter TODO

JPL Horizons positions
======================

For apparent positions of the planets, JPL Horizons follows a different
approach from Astronomical Almanac and from the IERS Conventions 2003 and 2010.
It uses the old precession models IAU 1976 (Lieske) and nutation IAU 1980
(Wahr) and corrects the resulting positions by adding daily-measured celestial
pole offsets (delta_psi and delta_epsilon) to nutation. (IERS Conventions 1996,
p. 22) While this approach is more accurate in some respect, it is not referred
to the same reference frame. For more details see the chapter
:ref:`Swiss Ephemeris and JPL Horizons System of NASA`.

Apparent positions of JPL Horizons can be reproduced with about 0.001 arcsec
precision using the flag ``FLG_JPLHOR``. For best accuracy, the daily Earth
orientation parameters (EOP) delta_psi and delta_eps relative to the IAU 1980
precession/nutation model must be downloaded and saved in the ephemeris path
defined by ``set_ephe_path()``. The EOP files are found on the IERS
website: http://www.iers.org/IERS/EN/DataProducts/EarthOrientationData/eop.html

The following files are required:

1. EOP 08 C04 (IAU1980) - one file (1962-now)

   http://datacenter.iers.org/eop/-/somos/5Rgv/document/tx14iers.0z9/eopc04_08.62-now

   Put this file into your ephemeris path and rename it as
   ``eop_1962_today.txt``.

2. finals.data (IAU1980)

   http://datacenter.iers.org/eop/-/somos/5Rgv/document/tx14iers.0q0/finals.data

   Put this file into your ephemeris path, too, and rename it as
   ``eop_finals.txt``.

If the Swiss Ephemeris does not find these files, it defaults to
``FLG_JPLHORA``, which is a very good approximation of Horizons, at least
for 1962 to present.

``FLG_JPLHORA`` can be used independently for the whole time range of the
Swiss Ephemeris.

Note, the Horizons mode works only with planets and fixed stars. With lunar
nodes and apsides, we use our standard methods.

..
