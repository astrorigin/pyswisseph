======================
The full JPL Ephemeris
======================

This is the full precision state-of-the-art ephemeris. It provides the highest
precision and is the basis of the Astronomical Almanac. Time range:

==========  =============================   =============
Start date  9 Dec 13002 BCE (-13001) Jul.   JD -3027215.5
End date    11 Jan 17000 CE Greg.           JD 7930192.5
==========  =============================   =============

JPL is the Jet Propulsion Laboratory of NASA in Pasadena, CA, USA (see
http://www.jpl.nasa.gov). Since many years this institute, which is in charge
of the planetary missions of NASA, has been the source of the highest precision
planetary ephemerides. The currently newest version of JPL ephemeris is the
DE430/DE431.

There are several versions of the JPL Ephemeris. The version is indicated by
the DE-number. A higher number indicates a more recent version. Swisseph should
be able to read any JPL file from DE200 upwards.

Accuracy of JPL ephemerides DE403/404 (1996) and DE405/406 (1998)
=================================================================

According to a paper (see below) by Standish and others on DE403 (of which
DE406 is only a slight refinement), the accuracy of this ephemeris can be
partly estimated from its difference from DE200:

With the inner planets, Standish shows that within the period 1600 – 2160 there
is a maximum difference of 0.1 – 0.2" which is mainly due to a mean motion
error of DE200. This means that the absolute precision of DE406 is estimated
significantly better than 0.1" over that period. However, for the period
1980 – 2000 the deviations between DE200 and DE406 are below 0.01" for all
planets, and for this period the JPL integration has been fit to measurements
by radar and laser interferometry, which are extremely precise.

With the outer planets, Standish's diagrams show that there are large
differences of several " around 1600, and he says that these deviations are due
to the inherent uncertainty of extrapolating the orbits beyond the period of
accurate observational data. The uncertainty of Pluto exceeds 1" before 1910
and after 2010, and increases rapidly in more remote past or future.

With the Moon, there is an increasing difference of 0.9"/cty2 between 1750 and
2169. It is mainly caused by errors in LE200 (Lunar Ephemeris).

The differences between DE200 and DE403 (DE406) can be summarized as follows:

=========== =================== ==========
1980 – 2000 all planets         < 0.01"
1600 – 1980 Sun – Jupiter       a few 0.1"
1900 – 1980 Saturn – Neptune    a few 0.1"
1600 – 1900 Saturn – Neptune    a few "
1750 – 2169 Moon                a few "
=========== =================== ==========

(see: E.M. Standish, X.X. Newhall, J.G. Williams, and W.M. Folkner, JPL
Planetary and Lunar Ephemerides, DE403/LE403, JPL Interoffice Memorandum
IOM 314.10-127, May 22, 1995, pp. 7f.)

Comparison of JPL ephemerides DE406 (1998) with DE431 (2013)
============================================================

Differences DE431-DE406 for 3000 BCE to 3000 CE:

=================== ====================
Moon                < 7" (TT), < 2" (UT)
Sun, Mercury, Venus < 0.4"
Mars                < 2"
Jupiter             < 6"
Saturn              < 0.1"
Uranus              < 28"
Neptune             < 53"
Pluto               < 129"
=================== ====================

Moon, position (DE431) – position (DE406) in TT and UT:
(Delta T adjusted to tidal acceleration of lunar ephemeris)

======= ======= ======= ======= ======
Year    dL(TT)  dL(UT)  dB(TT)  dB(UT)
======= ======= ======= ======= ======
-2999   6.33"   -0.30"  -0.01"  0.05"
-2500   5.91"   -0.62"  -0.85"  -0.32"
-2000   3.39"   -1.21"  -0.59"  -0.20"
-1500   1.74"   -1.49"  -0.06"  -0.01"
-1000   1.06"   -1.50"  0.30"   0.12"
-500    0.63"   -1.40"  0.28"   0.09"
0       0.13"   -0.99"  0.11"   0.05"
500     -0.08"  -0.99"  -0.03"  0.05"
1000    -0.12"  -0.38"  -0.08"  -0.06"
1500    -0.08"  -0.15"  -0.03"  -0.02"
2000    0.00"   0.00"   0.00"   0.00"
2500    0.06"   0.06"   -0.02"  -0.02"
3000    0.10"   0.10"   -0.09"  -0.09"
======= ======= ======= ======= ======

Sun, position (DE431) – position (DE406) in TT and UT:

======= ======= ======
Year    dL(TT)  dL(UT)
======= ======= ======
2999    0.21"   -0.34"
-2500   0.11"   -0.33"
-2000   0.09"   -0.26"
-1500   0.04"   -0.22"
-1000   0.06"   -0.14"
-500    0.02"   -0.11"
0       0.02"   -0.06"
500     0.00"   -0.04"
1000    0.00"   -0.01"
1500    -0.00"  -0.01"
2000    -0.00"  -0.00"
2500    -0.00"  -0.00"
3000    -0.01"  -0.01"
======= ======= ======

Pluto, position (DE431) – position (DE406) in TT:

======= =======
Year    dL(TT)
======= =======
-2999   66.31"
-2500   82.93"
-2000   100.17"
-1500   115.19"
-1000   126.50"
-500    127.46"
0       115.31"
500     92.43"
1000    63.06"
1500    31.17"
2000    -0.02"
2500    -28.38"
3000    -53.38"
======= =======

The Swiss Ephemeris is based on the latest JPL file, and reproduces the full
JPL precision with better than 1/1000 of an arc second, while requiring only a
tenth storage. Therefore for most applications it makes little sense to get the
full JPL file. Precision comparison can be done at the Astrodienst web server.
The Swiss Ephemeris test page http://www.astro.com/swisseph/swetest.htm allows
to compute planetary positions for any date using the full JPL ephemerides
DE200, DE406, DE421, DE431, or the compressed Swiss Ephemeris or the Moshier
ephemeris.

..
