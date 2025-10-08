===============
Ephemeris flags
===============

The flags to choose an ephemeris are:

=============== =====================
``FLG_JPLEPH``  Use JPL ephemeris
``FLG_SWIEPH``  Use Swiss Ephemeris
``FLG_MOSEPH``  Use Moshier ephemeris
=============== =====================

If none of this flags is specified, ``calc()`` tries to compute the default
ephemeris. The default ephemeris is defined as ``FLG_DEFAULTEPH`` and equals
``FLG_SWIEPH``. In this case the default ephemeris is Swiss Ephemeris. If you
have not specified an ephemeris in ``flags``, ``calc()`` tries to compute a
Swiss Ephemeris position. If it does not find the required Swiss Ephemeris file
either, it computes a Moshier position.

..
