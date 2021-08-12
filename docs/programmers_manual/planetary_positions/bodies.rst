======
Bodies
======

To tell ``calc()`` which celestial body or factor should be computed, a fixed
set of body numbers is used. The body numbers are module integer constants:

======================= ======= ==================================
Constant name           Value   Comment
======================= ======= ==================================
swisseph.ECL_NUT        -1      Obliquity of ecliptic and nutation
swisseph.SUN            0
swisseph.MOON           1
swisseph.MERCURY        2
swisseph.VENUS          3
swisseph.MARS           4
swisseph.JUPITER        5
swisseph.SATURN         6
swisseph.URANUS         7
swisseph.NEPTUNE        8
swisseph.PLUTO          9
swisseph.MEAN_NODE      10      Mean lunar node
swisseph.TRUE_NODE      11      True lunar node
swisseph.MEAN_APOG      12      Mean lunar apogee
swisseph.OSCU_APOG      13      Osculating lunar apogee
swisseph.EARTH          14
swisseph.CHIRON         15
swisseph.PHOLUS         16
swisseph.CERES          17
swisseph.PALLAS         18
swisseph.JUNO           19
swisseph.VESTA          20
swisseph.INTP_APOG      21      Interpolated lunar apogee
swisseph.INTP_PERG      22      Interpolated lunar perigee
======================= ======= ==================================

Some other related constants:

======================= ======  =============================
Constant name           Value   Comment
======================= ======  =============================
swisseph.NPLANETS       23      Number of "planets"
swisseph.FICT_OFFSET    40      Offset for fictitious objects
swisseph.NFICT_ELEM     15      Number of fictitious objects
swisseph.PLMOON_OFFSET  9000    Offset for planetary moons
swisseph.AST_OFFSET     10000   Offset for asteroids
======================= ======  =============================

Hamburger or Uranian "planets":

=================== =====
Constant name       Value
=================== =====
swisseph.CUPIDO     40
swisseph.HADES      41
swisseph.ZEUS       42
swisseph.KRONOS     43
swisseph.APOLLON    44
swisseph.ADMETOS    45
swisseph.VULKANUS   46
swisseph.POSEIDON   47
=================== =====

Other fictitious bodies:

=========================== =====
Constant name               Value
=========================== =====
swisseph.ISIS               48
swisseph.NIBIRU             49
swisseph.HARRINGTON         50
swisseph.NEPTUNE_LEVERRIER  51
swisseph.NEPTUNE_ADAMS      52
swisseph.PLUTO_LOWELL       53
swisseph.PLUTO_PICKERING    54
=========================== =====

..
