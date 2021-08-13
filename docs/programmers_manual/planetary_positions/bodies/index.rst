======
Bodies
======

To tell ``calc()`` which celestial body or factor should be computed, a fixed
set of body numbers is used. The body numbers are module integer constants:

=============== ======= ==================================
Constant name   Value   Comment
=============== ======= ==================================
swe.ECL_NUT     -1      Obliquity of ecliptic and nutation
swe.SUN         0
swe.MOON        1
swe.MERCURY     2
swe.VENUS       3
swe.MARS        4
swe.JUPITER     5
swe.SATURN      6
swe.URANUS      7
swe.NEPTUNE     8
swe.PLUTO       9
swe.MEAN_NODE   10      Mean lunar node
swe.TRUE_NODE   11      True lunar node
swe.MEAN_APOG   12      Mean lunar apogee
swe.OSCU_APOG   13      Osculating lunar apogee
swe.EARTH       14
swe.CHIRON      15
swe.PHOLUS      16
swe.CERES       17
swe.PALLAS      18
swe.JUNO        19
swe.VESTA       20
swe.INTP_APOG   21      Interpolated lunar apogee
swe.INTP_PERG   22      Interpolated lunar perigee
=============== ======= ==================================

Some other related constants:

=================== ======= =============================
Constant name       Value   Comment
=================== ======= =============================
swe.NPLANETS        23      Number of "planets"
swe.FICT_OFFSET     40      Offset for fictitious objects
swe.NFICT_ELEM      15      Number of fictitious objects
swe.PLMOON_OFFSET   9000    Offset for planetary moons
swe.AST_OFFSET      10000   Offset for asteroids
=================== ======= =============================

Hamburger or Uranian "planets":

=============== =====
Constant name   Value
=============== =====
swe.CUPIDO      40
swe.HADES       41
swe.ZEUS        42
swe.KRONOS      43
swe.APOLLON     44
swe.ADMETOS     45
swe.VULKANUS    46
swe.POSEIDON    47
=============== =====

Other fictitious bodies:

======================= =====
Constant name           Value
======================= =====
swe.ISIS                48
swe.NIBIRU              49
swe.HARRINGTON          50
swe.NEPTUNE_LEVERRIER   51
swe.NEPTUNE_ADAMS       52
swe.PLUTO_LOWELL        53
swe.PLUTO_PICKERING     54
======================= =====

.. toctree::
    :caption: See also:
    :maxdepth: 3

    additional_asteroids
    planetary_moons_and_body_centers
    fictitious_planets
    obliquity_and_nutation

..
