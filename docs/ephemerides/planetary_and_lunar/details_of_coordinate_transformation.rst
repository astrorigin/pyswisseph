========================================
The details of coordinate transformation
========================================

The following conversions are applied to the coordinates after reading the raw
positions from the ephemeris files:

Correction for light-time
=========================

Since the planet's light needs time to reach the Earth, it is never seen where
it actually is, but where it was some time before. Light-time amounts to a few
minutes with the inner planets and a few hours with distant planets like
Uranus, Neptune and Pluto. For the Moon, the light-time correction is about one
second. With planets, light-time correction may be of the order of 20" in
position, with the Moon 0.5".

Conversion from the solar system barycenter to the geocenter
============================================================

Original JPL data are referred to the center of the gravity of the solar
system. Apparent planetary positions are referred to an imaginary observer in
the center of the Earth.

Light deflection by the gravity of the Sun
==========================================

In the gravitational fields of the Sun and the planets light rays are bent.
However, within the solar system only the Sun has enough mass to deflect
light significantly. Gravity deflection is greatest for distant planets and
stars, but never greater than 1.8". When a planet disappears behind the Sun,
the Explanatory Supplement recommends to set the deflection = 0. To avoid
discontinuities, we chose a different procedure. See Appendix A. TODO

"Annual" aberration of light
============================

The velocity of light is finite, and therefore the apparent direction of a
moving body from a moving observer is never the same as it would be if both the
planet and the observer stood still. For comparison: if you run through the
rain, the rain seems to come from ahead even though it actually comes from
above. Aberration may reach 20".

Frame Bias (ICRS to J2000)
==========================

JPL ephemerides since DE403/DE404 are referred to the International Celestial
Reference System, a time-independent, non-rotating reference system which was
introduced by the IAU in 1997. The planetary positions and speed vectors are
rotated to the J2000 system. This transformation makes a difference of only
about 0.0068 arc seconds in right ascension. (Implemented from Swiss Ephemeris
1.70 on)

Precession
==========

Precession is the motion of the vernal equinox on the ecliptic. It results from
the gravitational pull of the Sun, the Moon, and the planets on the equatorial
bulge of the Earth. Original JPL data are referred to the mean equinox of the
year 2000. Apparent planetary positions are referred to the equinox of date.
(From Swiss Ephemeris 1.78 on, we use the precession model
Vondrák/Capitaine/Wallace 2011.)

Nutation (true equinox of date)
===============================

A short-period oscillation of the vernal equinox. It results from the Moon’s
gravity which acts on the equatorial bulge of the Earth. The period of nutation
is identical to the period of a cycle of the lunar node, i.e. 18.6 years. The
difference between the true vernal point and the mean one is always below 17".
(From Swiss Ephemeris 2.00, we use the nutation model IAU 2006. Since 1.70,
we used nutation model IAU 2000. Older versions used the nutation model IAU
1980 (Wahr).)

Transformation from equatorial to ecliptic coordinates
======================================================

For precise speed of the planets and the Moon, we had to make a special effort,
because the Explanatory Supplement does not give algorithms that apply the
above-mentioned transformations to speed. Since this is not a trivial job, the
easiest way would have been to compute three positions in a small interval and
determine the speed from the derivation of the parabola going through them.
However, double float calculation does not guarantee a precision better than
0.1"/day. Depending on the time difference between the positions, speed is
either good near station or during fast motion. Derivation from more positions
and higher order polynomials would not help either.

Therefore we worked out a way to apply directly all the transformations to the
barycentric speeds that can be derived from JPL or Swiss Ephemeris. The
precision of daily motion is now better than 0.002" for all planets, and the
computation is even a lot faster than it would have been from three positions.
A position with speed takes in average only 1.66 times longer than one without
speed, if a JPL or a Swiss Ephemeris position is computed. With Moshier,
however, a computation with speed takes 2.5 times longer.

..
