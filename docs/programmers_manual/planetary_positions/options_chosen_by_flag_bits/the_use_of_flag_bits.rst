====================
The use of flag bits
====================

If no bits are set, i.e. if ``flags == 0``, the function ``calc()`` computes
what common astrological ephemerides (as available in book shops) supply, i.e.
an apparent body position in geocentric ecliptic polar coordinates (longitude,
latitude, and distance) relative to the true equinox of the date.

If the speed of the body is required, set ``flags = swe.FLG_SPEED``.

For mathematical points as the mean lunar node and the mean apogee, there is no
apparent position. ``calc()`` returns true positions for these points.

If you need another kind of computation, use the flags explained in the
following paragraphs. Their names begin with ``FLG_``. To combine them, you
have to concatenate them (inclusive-or) as in the following example:

.. code-block:: python

    flags = swe.FLG_SPEED | swe.FLG_TRUEPOS

With this value of ``flags``, ``calc()`` will compute true positions (i.e. not
accounted for light-time) with speed.

The flag bits are:

======================= ========================================================================================================================
Constant name           Usage
======================= ========================================================================================================================
swe.FLG_JPLEPH          Use JPL ephemeris
swe.FLG_SWIEPH          Use SwissEph ephemeris
swe.FLG_MOSEPH          Use Moshier ephemeris
swe.FLG_HELCTR	        Heliocentric position
swe.FLG_TRUEPOS	        True/geometric position, not apparent position
swe.FLG_J2000	        No precession, i.e. give J2000 equinox
swe.FLG_NONUT	        No nutation, i.e. mean equinox of date
swe.FLG_SPEED3	        Speed from 3 positions (do not use it, FLG_SPEED is faster and more precise)
swe.FLG_SPEED	        High precision speed
swe.FLG_NOGDEFL	        Turn off gravitational deflection
swe.FLG_NOABERR	        Turn off 'annual' aberration of light
swe.FLG_ASTROMETRIC     Astrometric position, i.e. with light-time, but without aberration and light deflection. Equals (FLG_NOABERR|FLG_NOGDEFL)
swe.FLG_EQUATORIAL      Equatorial positions are wanted
swe.FLG_XYZ	            Cartesian, not polar, coordinates
swe.FLG_RADIANS	        Coordinates in radians, not degrees
swe.FLG_BARYCTR	        Barycentric position
swe.FLG_TOPOCTR	        Topocentric position
swe.FLG_ORBEL_AA        Used for Astronomical Almanac mode in calculation of Kepler elipses. Equals FLG_TOPOCTR
swe.FLG_TROPICAL	    Tropical position (default)
swe.FLG_SIDEREAL	    Sidereal position
swe.FLG_ICRS	        ICRS (DE406 reference frame)
swe.FLG_DPSIDEPS_1980	Reproduce JPL Horizons 1962 - today to 0.002 arcsec
swe.FLG_JPLHOR	        Equals SEFLG_DPSIDEPS_1980
swe.FLG_JPLHOR_APPROX	Approximate JPL Horizons 1962 - today
swe.FLG_CENTER_BODY     Calculate position of center of body (COB) of planet, not barycenter of its system
swe.FLG_TEST_PLMOON     Test raw data in files sepm9*. Equals (2*1024*1024|FLG_J2000|FLG_ICRS|FLG_HELCTR|FLG_TRUEPOS)
======================= ========================================================================================================================

.. note::

    Center of body can be calculated either:

    .. code-block:: python

        # with a flag
        ipl = swe.JUPITER
        flags |= swe.FLG_CENTER_BODY

    or, without any additional flags:

    .. code-block:: python

        ipl = swe.PLMOON_OFFSET + swe.JUPITER * 100 + 99
        xx, retflags = swe.calc_ut(jd, ipl, flags)

    See
    :doc:`/programmers_manual/planetary_positions/bodies/planetary_moons_and_body_centers`

..
