====================================================================================================
More benefits from our new sidereal algorithms: standard equinoxes and precession-corrected transits
====================================================================================================

Method no. 3, the transformation to the ecliptic of t0, opens two more
possibilities:

You can compute positions referred to any equinox, 2000, 1950, 1900, or
whatever you want. This is sometimes useful when Swiss Ephemeris data ought to
be compared with astronomical data, which are often referred to a standard
equinox.

There are predefined sidereal modes for these standard equinoxes:

- ``SIDM_J2000`` (18) J2000
- ``SIDM_J1900`` (19) J1900
- ``SIDM_B1950`` (20) B1950

Moreover, it is possible to compute precession-corrected transits or synastries
with very high precision. An astrological transit is defined as the passage of
a planet over the position in your birth chart. Usually, astrologers assume
that tropical positions on the ecliptic of the transit time has to be compared
with the positions on the tropical ecliptic of the birth date. But it has been
argued by some people that a transit would have to be referred to the ecliptic
of the birth date. With the new Swiss Ephemeris algorithm (method no. 3) it is
possible to compute the positions of the transit planets referred to the
ecliptic of the birth date, i.e. the so-called precession-corrected transits.
This is more precise than just correcting for the precession in longitude (see
details in the programmer's documentation swephprg.doc, Ch. 8.1). TODO

..
