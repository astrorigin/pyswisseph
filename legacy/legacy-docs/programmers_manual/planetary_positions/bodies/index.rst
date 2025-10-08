======
Bodies
======

To tell ``calc()`` which celestial body or factor should be computed, a fixed
set of body numbers is used. The body numbers are module integer constants:

=============== ======= ==================================
Constant name   Value   Comment
=============== ======= ==================================
``ECL_NUT``     -1      Obliquity of ecliptic and nutation
``SUN``         0
``MOON``        1
``MERCURY``     2
``VENUS``       3
``MARS``        4
``JUPITER``     5
``SATURN``      6
``URANUS``      7
``NEPTUNE``     8
``PLUTO``       9
``MEAN_NODE``   10      Mean lunar node
``TRUE_NODE``   11      True lunar node
``MEAN_APOG``   12      Mean lunar apogee
``OSCU_APOG``   13      Osculating lunar apogee
``EARTH``       14
``CHIRON``      15
``PHOLUS``      16
``CERES``       17
``PALLAS``      18
``JUNO``        19
``VESTA``       20
``INTP_APOG``   21      Interpolated lunar apogee
``INTP_PERG``   22      Interpolated lunar perigee
=============== ======= ==================================

Some other related constants:

=================== ======= =============================
Constant name       Value   Comment
=================== ======= =============================
``NPLANETS``        23      Number of "planets"
``FICT_OFFSET``     40      Offset for fictitious objects
``NFICT_ELEM``      15      Number of fictitious objects
``PLMOON_OFFSET``   9000    Offset for planetary moons
``AST_OFFSET``      10000   Offset for asteroids
=================== ======= =============================

Hamburger or Uranian "planets":

=============== =====
Constant name   Value
=============== =====
``CUPIDO``      40
``HADES``       41
``ZEUS``        42
``KRONOS``      43
``APOLLON``     44
``ADMETOS``     45
``VULKANUS``    46
``POSEIDON``    47
=============== =====

Other fictitious bodies:

======================= =====
Constant name           Value
======================= =====
``ISIS``                48
``NIBIRU``              49
``HARRINGTON``          50
``NEPTUNE_LEVERRIER``   51
``NEPTUNE_ADAMS``       52
``PLUTO_LOWELL``        53
``PLUTO_PICKERING``     54
======================= =====

.. toctree::
    :caption: See also:
    :maxdepth: 3

    additional_asteroids
    planetary_moons_and_body_centers
    fictitious_planets
    obliquity_and_nutation

..
