=============
Sidereal Time
=============

Swiss Ephemeris versions until 1.80 used the IAU 1976 formula for Sidereal
time. Since version 2.00 it uses sidereal time based on the IAU2006/2000
precession/nutation model.

As this solution is not good for the whole time range of JPL Ephemeris DE431,
we only use it between 1850 and 2050. Outside this period, we use a solution
based on the long term precession model Vondrak 2011, nutation IAU2000 and the
mean motion of the Earth according to Simon & alii 1994. To make the function
continuous we add some constant values to our long-term function before 1850
and after 2050.

 Vondrak/Capitaine/Wallace, "New precession expressions, valid for long time
 intervals", in A&A 534, A22(2011).

 Simon & alii, "Precession formulae and mean elements for the Moon and the
 Planets", A&A 282 (1994), p. 675/678.

..
