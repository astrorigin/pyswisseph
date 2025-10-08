=======================================================================
The Swiss Ephemeris Compared with Astronomical Almanac and JPL Horizons
=======================================================================

Swiss Ephemeris and the Astronomical Almanac
============================================

The original JPL ephemeris provides barycentric equatorial Cartesian positions
relative to the equinox 2000/ICRS. Moshier provides heliocentric positions.
The conversions to apparent geocentric ecliptical positions were done using the
algorithms and constants of the Astronomical Almanac as described in the
"Explanatory Supplement to the Astronomical Almanac". Using the DE200 data
file, it is possible to reproduce the positions given by the Astronomical
Almanac 1984, 1995, 1996, and 1997 (on p. B37-38 in all editions) to the last
digit. Editions of other years have not been checked. DE200 was used by
Astronomical Almanac from 1984 to 2002. The sample positions given in the
mentioned editions of Astronomical Almanac can also be reproduced using a
recent version of the Swiss Ephemeris and a recent JPL ephemeris. The number of
digits given in AA do not allow to see a difference. The Swiss Ephemeris has
used DE405/DE406 since its beginning in 1997.

From 2003 to 2015, the Astronomical Almanac has been using JPL ephemeris DE405,
and since Astronomical Almanac 2006 all relevant resolutions of the
International Astronomical Union (IAU) have been implemented. Versions 1.70 and
higher of the Swiss Ephemeris also follow these resolutions and reproduce the
sample calculation given by AA2006 (p. B61-B63), AA2011 and AA2013
(both p. B68-B70) to the last digit, i.e. to better than 0.001 arc second.
(To avoid confusion when checking AA2006, it may be useful to know that the JD
given on page B62 does not have enough digits in order to produce the correct
final result. With later AA2011 and AA2013, there is no such problem.)

The Swiss Ephemeris uses JPL Ephemeris DE431 since version 2.0 (2014). The
Astronomical Almanac uses JPL Ephemeris DE430 since 2016. The Swiss Ephemeris
and the Astronomical Almanac still perfectly agree.

Detailed instructions how to compare planetary positions as given by the Swiss
Ephemeris with those of Astronomical Almanac are given in Appendix D at the end
of this documentation. (TODO)

.. _Swiss Ephemeris and JPL Horizons System of NASA:

Swiss Ephemeris and JPL Horizons System of NASA
===============================================

The Swiss Ephemeris, from version 1.70 on, reproduces astrometric planetary
positions of the JPL Horizons System precisely. However, there have been small
differences of about 53 mas (milli-arcseconds) with apparent positions. The
same deviations also occur if Horizons is compared with the example
calculations given in the Astronomical Almanac.

With ephemerides relative to the equinox of date, Horizons uses a different
reference ecliptic than Astronomical Almanac and Swiss Ephemeris. It follows
IERS Conventions 1996 (p. 22), which is based on the old precession models IAU
1976 (Lieske) and nutation IAU 1980 (Wahr). On the other hand, the Astronomical
Almanac and the Swiss Ephemeris follow IERS Conventions 2003 and 2010 with more
recent precession and nutation models. As a result of the different reference
ecliptics used, there is a constant offset of 53 mas in RA between Horizons and
the Swiss Ephemeris.

It should be understood that these differences in apparent ephemerides are not
the result of an error on the side of the Swiss Ephemeris and much less on the
side of Horizons. Both systems are valid. According to private communication
with Jon Giorgini (5 April 2021), there are also (low-priority) plans to
implement the more recent conventions in Horizons as an option. With this
option, the 53 mas-difference should disappear and the remaining error of about
1 mas will be due to free core nutation, which is considered by Horizons, but
not by the Swiss Ephemeris.

Swiss Ephemeris versions 2.00 and higher contain code to reproduce positions of
Horizons with a precision of about 1 mas for 1799 CE – today. From version 2.07
on, Horizons can be reproduced with a similar precision for its whole time
range.

For best agreement with Horizons, current data files with Earth orientation
parameters (EOP) must be downloaded from the IERS website and put into the
ephemeris path. If they are not available, the Swiss Ephemeris uses an
approximation which reproduces Horizons still with an accuracy of about 2 mas
between 1962 and present.

It must be noted that correct values for Earth orientation delta_psi and
delta_epsilon are only available between 1962 and present. For all calculations
before that, Horizons uses the first values of the EOP data, and for all
calculations in the future, it uses the last values of the existing data. The
resulting positions before 1962 thus do not have the same precision, but the
ephemeris is at least continuous.

More information on this and technical details are found in the programmer's
documentation and in the source code, file swephlib.h.

IERS Conventions 1996, 2003, and 2010 can be read or downloaded from here:
http://www.iers.org/IERS/EN/DataProducts/Conventions/conventions.html

Detailed instructions how to compare planetary positions as given by the Swiss
Ephemeris with those of JPL are given in Appendix C at the end of this
documentation. (TODO)

Many thanks to Jon Giorgini, developer of the Horizons System, for explaining
us the methods used at JPL.

Differences between Swiss Ephemeris 1.70 and older versions
===========================================================

TODO

Differences between Swiss Ephemeris 1.78 and 1.77
=================================================

TODO

Differences between Swiss Ephemeris 2.00 and 1.80
=================================================

TODO

Differences between Swiss Ephemeris 2.05.01 and 2.06
====================================================

TODO

..
