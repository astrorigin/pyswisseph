================================================================================
Geocentric, topocentric, heliocentric, barycentric, and planetocentric positions
================================================================================

More precisely speaking, common ephemerides tell us the position where we would
see a planet if we stood in the center of the Earth and could see the sky. But
it has often been argued that a planet's position ought to be referred to the
geographic position of the observer (or the birth place). This can make a
difference of several arc seconds with the planets and even more than a degree
with the Moon! Such a position referred to the birth place is called the
topocentric planetary position. The observation of transits over the Moon might
help to find out whether or not this method works better.

For very precise topocentric calculations, the Swiss Ephemeris not only
requires the geographic position, but also its altitude above sea. An altitude
of 3000 m (e.g. Mexico City) may make a difference of more than 1 arc second
with the Moon. With other bodies, this effect is of the amount of a 0.01". The
altitudes are referred to the approximate Earth ellipsoid. Local irregularities
of the geoid have been neglected.

Our topocentric lunar positions differ from the NASA positions (s. the Horizons
Online Ephemeris System http://ssd.jpl.nasa.gov) by 0.2 - 0.3 arc sec. This
corresponds to a geographic displacement by a few 100 m and is about the best
accuracy possible. In the documentation of the Horizons System, it is written
that: "The Earth is assumed to be a rigid body. ... These Earth-model
approximations result in topocentric station location errors, with respect to
the reference ellipsoid, of less than 500 meters."

The Swiss ephemeris also allows the computation of apparent or true topocentric
positions.

With the lunar nodes and apogees, Swiss Ephemeris does not make a difference
between topocentric and geocentric positions. There are many ways to define
these points topocentrically. The simplest one is to understand them as axes
rather than points somewhere in space. In this case, the geocentric and the
topocentric positions are identical, because an axis is an infinite line that
always points to the same direction, not depending on the observer's position.

Moreover, the Swiss Ephemeris supports the calculation of heliocentric,
barycentric, and planetetocentric positions of the planets. Heliocentric
positions are positions as seen from the center of the Sun rather than from the
center of the Earth. Barycentric ones are positions as seen from the center of
the solar system, which is always close to but not identical to the center of
the Sun. And planetocentric positions are relative to the center of some other
object (planet, moon) of the solar system.

..
