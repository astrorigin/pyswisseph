==========================
House position of a planet
==========================

.. autofunction:: swisseph.house_pos

With Koch houses, the function sometimes returns 0, if the computation was not
possible. This happens most often in polar regions, but it can happen at
latitudes below 66°33' as well, e.g. if a body has a high declination and falls
within the circumpolar sky. With circumpolar fixed stars (or asteroids) a Koch
house position may be impossible at any geographic location except on the
equator.

The user must decide how to deal with this situation.

You can use the house positions returned by this function for house horoscopes
(or "mundane" positions). For this, you have to transform it into a value
between 0 and 360 degrees. Subtract 1 from the house number and multiply it
with 30, or ``mund_pos = (hpos – 1) * 30``.

You will realize that house positions computed like this, e.g. for the Koch
houses, will not agree exactly with the ones that you get applying the Huber
"hand calculation" method. If you want a better agreement, set the ecliptic
latitude ``objcoord[1] = 0``. Remaining differences result from the fact that
Huber's hand calculation is a simplification, whereas our computation is
geometrically accurate.

Currently, geometrically correct house positions are provided for the following
house methods:

``P`` Placidus, ``K`` Koch, ``C`` Campanus, ``R`` Regiomontanus,
``U`` Krusinski, ``A``/``E`` Equal, ``V`` Vehlow, ``W`` Whole Signs,
``D`` Equal/MC, ``N`` Equal/Zodiac, ``O`` Porphyry, ``B`` Alcabitius,
``X`` Meridian, ``F`` Carter, ``M`` Morinus, ``T`` Polich/Page, ``H`` Horizon,
``G`` Gauquelin.

A simplified house position (distance_from_cusp / house_size) is currently
provided for the following house methods:

``Y`` APC houses, ``L`` Pullen SD, ``Q`` Pullen SR, ``I`` Sunshine,
``S`` Sripati.

This function requires *tropical* positions in xpin. *Sidereal* house positions
are identical to tropical ones in the following cases:

- If the traditional method is used to compute sidereal planets (``sid_pos =
  trop_pos – ayanamsha``). Here the function ``house_pos()`` works for all
  house systems.
- If a non-traditional method (projection to the ecliptic of ``t0`` or to the
  solar system rotation plane) is used and the definition of the house system
  does not depend on the ecliptic. This is the case with Campanus,
  Regiomontanus, Placidus, Azimuth houses, axial rotation houses. This is not
  the case with equal houses, Porphyry and Koch houses. You have to compute
  equal and Porphyry house positions on your own. We recommend to avoid Koch
  houses here. Sidereal Koch houses make no sense with these sidereal
  algorithms.

Calculating the Gauquelin sector position of a planet
=====================================================

For general information on Gauquelin sectors, read chapter TODO

There are two functions that can be used to calculate Gauquelin sectors:

- ``house_pos()``. Full details about this function are presented in the
  previous section. To calculate Gauquelin sectors the parameter ``hsys`` must
  be set to ``G`` (Gauquelin sectors). This function will then return the
  sector position as a value between 1.0 and 36.9999999. Note that Gauquelin
  sectors are numbered in clockwise direction, unlike all other house systems.
- ``gauquelin_sector()`` - detailed below.

.. autofunction:: swisseph.gauquelin_sector

There are six methods of computing the Gauquelin sector position of a planet:

1. Sector positions from ecliptical longitude AND latitude:

   There are two ways of doing this:

   - Call ``house_pos()`` with ``hsys`` = ``b'G'``, ``objcoord[0]`` =
     ecliptical longitude of planet, and ``objcoord[1]`` = ecliptical
     latitude. This function returns the sector position as a value between
     1.0 and 36.9999999.
   - Call ``gauquelin_sector()`` with ``method`` = 0. This is less efficient
     than ``house_pos()`` because it recalculates the whole planet whereas
     ``house_pos()`` has an input array for ecliptical positions calculated
     before.

2. Sector positions computed from ecliptical longitudes without ecliptical
   latitudes:

   There are two ways of doing this:

   - Call ``house_pos()`` with ``hsys`` = ``b'G'``, ``objcoord[0]`` = ecl.
     longitude of planet, and ``objcoord[1]`` = 0. This function returns the
     sector position as a value between 1.0 and 36.9999999.
   - Call ``gauquelin_sector()`` with ``method`` = 1. Again this is less
     efficient than ``house_pos()``.

3. Sector positions of a planet from rising and setting times of planets.

   The rising and setting of the disk center is used:

   - Call ``gauquelin_sector()`` with ``method`` = 2.

4. Sector positions of a planet from rising and setting times of planets,
   taking into account atmospheric refraction.

   The rising and setting of the disk center is used:

   - Call ``gauquelin_sector()`` with ``method`` = 3.

5. Sector positions of a planet from rising and setting times of planets.

   The rising and setting of the disk edge is used:

   - Call ``gauquelin_sector()`` with ``method`` = 4.

6. Sector positions of a planet from rising and setting times of planets,
   taking into account atmospheric refraction.

   The rising and setting of the disk edge is used:

   - Call ``gauquelin_sector()`` with ``method`` = 5.

..
