=========================================
The Swiss Ephemeris compression mechanism
=========================================

The idea behind our mechanism of ephemeris compression was developed by Dr.
Peter Kammeyer of the U.S. Naval Observatory in 1987.

This is how it works: The ephemerides of the Moon and the inner planets require
by far the greatest part of the storage. A more sophisticated mechanism is
required for these than for the outer planets. Instead of the positions we
store the differences between JPL and the mean orbits of the analytical theory
VSOP87. These differences are a lot smaller than the position values, wherefore
they require less storage. They are stored in Chebyshew polynomials covering a
period of an anomalistic cycle each. (By the way, this is the reason, why the
Swiss Ephemeris does not cover the time range of the full JPL ephemeris. The
first ephemeris file begins on the date on which the last of the inner planets
(including Mars) passes its first perihelion after the start date of the JPL
ephemeris.)

With the outer planets from Jupiter through Pluto we use a simpler mechanism.
We rotate the positions provided by the JPL ephemeris to the mean plane of the
planet. This has the advantage that only two coordinates have high values,
whereas the third one becomes very small. The data are stored in Chebyshew
polynomials that cover a period of 4000 days each. (This is the reason, why
Swiss Ephemeris stops before the end date of the JPL ephemeris.)

..
