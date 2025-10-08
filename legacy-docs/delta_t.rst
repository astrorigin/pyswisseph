============
ΔT (Delta T)
============

Ephemerides of planets are calculated using so called Terrestrial Time (which
replaces former Ephemeris Time (ET)). Terrestrial time is a perfectly uniform
time measure based on atomic clocks (SI seconds). Computations of sidereal time
and houses, on the other hand, are calculated using Universal Time (UT).
Universal Time is based on the rotational period of the Earth (the day), which
is not perfectly uniform. The difference between TT (ET) and UT is called ΔT
("Delta T"), and is defined as ΔT = TT – UT.

The Earth's rotation decreases slowly, currently at the rate of roughly 0.5 –
1 second per year, but in an irregular and unpredictable way. The value of ΔT
cannot be calculated with accuracy for the future or the remote past. Future
values of ΔT can only be determined in hindsight from astronomical
observations. Observations of solar and lunar eclipses made by ancient
Babylonians, Chinese, Greeks, Arabs, and scholars of the European Renaissance
and early Modern Era can be used to determine the approximate value of ΔT for
historical epochs after 720 BCE. For the remoter past or the future,
estimations must be made. Numerous occultations of stars by the Moon have
provided more exact values for ΔT for epochs after 1700. Since 1962, ΔT has
been determined from extremely accurate measurements of the Earth rotation by
the International Earth Rotation and Reference Systems Service (IERS).

Swiss Ephemeris Version 2.06 and later use the ΔT algorithms published in:

- Stephenson, F.R., Morrison, L.V., and Hohenkerk, C.Y., "Measurement of the
  Earth's Rotation: 720 BCE to CE 2015", Royal Society Proceedings A, 7 Dec
  2016,
  http://rspa.royalsocietypublishing.org/lookup/doi/10.1098/rspa.2016.0404

These algorithms are used for epochs before 1 January 1955. From 1955 on we use
the values provided by the Astronomical Almanac, pp. K8-9 (since AA 1986). From
1974 on we use values calculated from data of the Earth Orientation Department
of the US Naval Observatory:

- (TAI-UTC) from: ftp://maia.usno.navy.mil/ser7/tai-utc.dat;
- (UT1-UTC) from: ftp://ftp.iers.org/products/eop/rapid/standard/finals.data;
  or
- ftp://maia.usno.navy.mil/ser7/finals.all;
  file description in: ftp://maia.usno.navy.mil/ser7/readme.finals.

``Delta T = TAI-UT1 + 32.184 sec = (TAI-UTC) - (UT1-UTC) + 32.184 sec``

For epochs before 1955, the ΔT function adjusts for a value of secular tidal
acceleration ndot that is consistent with the ephemeris used (LE431 has ndot =
-25.80 arcsec/cty2, LE405/406 has ndot = -25.826 arcsec/cty2, ELP2000 and DE200
ndot = -23.8946 arcsec/cty2). The ΔT values of Astronomical Almanac are
consistent with ndot = -26 arcsec/cty2, those of Stephenson & alii 2016 with
ndot = -25.85 arcsec/cty2.

For the time after the last tabulated value, we use the formula of Stephenson
(1997; p. 507), with a modification that avoids a discontinuity at the end of
the tabulated period. A linear term is added that makes a slow transition from
the table to the formula over a period of 100 years.

The ΔT algorithms have been changed with the Swiss Ephemeris releases 1.64
(Stephenson 1997), 1.72 (Morrison/Stephenson 2004), 1.77 (Espenak & Meeus) and
2.06 (Stephenson/Morrison/Hohenkerk). These updates have caused changes in
ephemerides that are based on Universal Time.

Until version 2.05.01, the Swiss Ephemeris has used the ΔT values provided by
Astronomical Almanac K8-9 starting from the year 1633. Before 1600, polynomials
published by Espenak and Meeus (2006, see further below) were used. These
formulae include the long-term formula by Morrison/Stephenson (2004, p. 332),
which is used for epochs before -500. Between the value of 1600 and the value
of 1633, a linear interpolation was made.

**Differences in ΔT, SE 2.06 – SE 2.05 (new – old)**

(with resulting differences for lunar and solar ephemerides calculated in UT)

=========== =========== =========================== =========== =======
Year        ΔT sec      Difference in ΔT (new-old)  L (Moon)    L (Sun)
=========== =========== =========================== =========== =======
-3000       75051       1174                        644"        48"
-2500       60203       865                         475"        36"
-2000       46979       588                         323"        24"
-1500       35377       342                         188"        14"
-1000       25398       129                         71"         5"
-900        23596       90                          49"         4"
-800        21860       52                          29"         2"
-700        20142       -31                         -17"        -1"
-600        18373       -229                        -126"       -9"
-500        16769       -325                        -179"       -13"
-400        15311       -119                        -65"        -5"
-300        13981       -5                          -3"         -0"
-200        12758       50                          27"         2"
-100        11623       62                          34"         3"
0           10557       43                          24"         2"
100         9540        6                           3"          0"
200         8554        -31                         -17"        -1"
300         7578        -53                         -29"        -2"
400         6593        -62                         -34"        -3"
500         5590        -81                         -45"        -3"
600         4596        -110                        -60"        -5"
700         3649        -135                        -74"        -6"
800         2786        -145                        -80"        -6"
900         2045        -135                        -74"        -6"
1000        1464        -94                         -52"        -4"
1100        1063        -13                         -7"         -1"
1200        802         76                          42"         3"
1300        625         141                         77"         6"
1400        473         157                         86"         6"
1500        292         97                          53"         4"
1600        89          -29                         -16"        -1.2"
1700        14          6.5                         3.6"        0.27"
1800        19          5.3                         2.9"        0.22"
1900        -2.0        0.78                        0.43"       0.03"
1920        22          0.47                        0.26"       0.02"
1940        24          0.10                        0.05"       0.00"
1960        33          0.00                        0.00"       0.00"
1970        40          0.00                        0.00"       0.00"
1980        51          0.00                        0.00"       0.00"
1990        57          0.00                        0.00"       0.00"
2000        64          0.00                        0.00"       0.00"
2010        66          0.00                        0.00"       0.00"
2020        70          0.00                        0.00"       0.00"
2030        74          -5.9                        -3.3"       -0.24"
2040        76          -21                         -12"        -0.87"
2050        78          -37                         -20"        -1.5"
2100        94          -119                        -65"        -4.9"
2200        163         -265                        -145"       -11"
2300        297         -397                        -218"       -16"
2400        520         -503                        -276"       -21"
2500        855         -558                        -307"       -23"
3000        3292        -1004                       -551"       -41"
=========== =========== =========================== =========== =======

**Differences in ΔT, SE 1.77 – SE 1.76**

=============== =================================
Year            Difference in seconds (new - old)
=============== =================================
-3000           3
-2000           2
-1100           1
-1001           29
-900            -45
-800            -57
-700            -696            (is a maximum!)
-500            -14
until -200      3 > diff > -25
until 100       3 > diff > -15
until 500       3 > diff > -03
until 1600      4 > diff > -16
until 1630      1 > diff > -30
until 1700      0.1             | diff |
until 1900      0.01
until 2100      0.001
=============== =================================

The differences for –1000 to +1630 are explained as follows:

Espenak & Meeus ignore Morrison & Stephenson's values for -700 and -600,
whereas the former Swiss Ephemeris versions used them. For -500 to +1600
Espenak & Meeus use polynomials whereas the former Swiss Ephemeris versions
used a linear interpolation between Morrison / Stephenson's tabulated values.

**Differences in ΔT, SE 1.72 – SE 1.71**

=========== =================================
Year        Difference in seconds (new - old)
=========== =================================
-3000       -4127
-2000       -2130
-1000       -760
0           -20
1000        -30
1600        10
1619        0.5
1620        0
=========== =================================

**Differences in ΔT, SE 1.64 – SE 1.63**

=========== =================================
Year        Difference in seconds (new - old)
=========== =================================
-3000       2900
0           1200
1600        29
1619        60
1620        -0.6
1700        -0.4
1800        -0.1
1900        -0.02
1940        -0.001
1950        0
2000        0
2020        2
2100        23
3000        -400
=========== =================================

In 1620, where the ΔT table of the Astronomical Almanac starts, there was a
discontinuity of a whole minute in the old algorithms. This has been fixed with
SE 1.64.

The smaller differences for the period 1620-1955 are due to a correction in the
tidal acceleration of the Moon, which now has the same value as is also used by
JPL for their T calculations.

References
==========

 Borkowski, K. M., "ELP2000-85 and the Dynamical Time - Universal Time
 relation," Astronomy and Astrophysics 205, L8-L10 (1988)

 Chapront-Touze, Michelle, and Jean Chapront, Lunar Tables and Programs from
 4000 B.C. to A.D. 8000, Willmann-Bell 1991

 Espenak, Fred, and Jean Meeus, "Five-millennium Catalog of Lunar Eclipses
 –1900 to +3000", 2009, p. 18ff.,
 http://eclipse.gsfc.nasa.gov/5MCSE/TP2009-214174.pdf.

 Explanatory Supplement of the Astronomical Almanac, University Science Books,
 1992, Mill Valley, CA, p. 265ff.

 Morrison, L. V. and F. R. Stephenson, Sun and Planetary System, vol 96,73 eds.
 W. Fricke, G. Teleki, Reidel, Dordrecht (1982)

 Morrison, L. V., and F.R. Stephenson, "Historical Values of the Earth's Clock
 Error T and the Calculation of Eclipses", JHA xxxv (2004), pp.327-336

 Stephenson, F. R., and L. V. Morrison, "Long-term changes in the rotation of
 the Earth: 700 BCE to CE 1980", Philosophical Transactions of the Royal
 Society of London, Series A 313, 47-70 (1984)

 Stephenson, F. R., and M. A. Houlden, Atlas of Historical Eclipse Maps,
 Cambridge U. Press (1986)

 Stephenson, F.R. & Morrison, L.V., "Long-Term Fluctuations in the Earth's
 Rotation: 700 BCE to CE 1990", in: Philosophical Transactions of the Royal
 Society of London, Ser. A, 351 (1995), 165-202.

 Stephenson, F. Richard, Historical Eclipses and Earth's Rotation, Cambridge U.
 Press (1997)

 Stephenson, F.R., Morrison, L.V., and Hohenkerk, C.Y., "Measurement of the
 Earth's Rotation: 720 BCE to CE 2015", Royal Society Proceedings A, 7 Dec
 2016, http://rspa.royalsocietypublishing.org/lookup/doi/10.1098/rspa.2016.0404

 For a comprehensive collection of publications and formulae, see R.H. van
 Gent at
 http://www.phys.uu.nl/~vgent/astro/deltatime.htm.

..
