=====================
The Moshier Ephemeris
=====================

This is a semi-analytical approximation of the JPL planetary and lunar
ephemerides DE404, developed by Steve Moshier. Its deviation from JPL is below
1 arc second with the planets and a few arc seconds with the Moon. No data
files are required for this ephemeris, as all data are linked into the program
code already.

This may be sufficient accuracy for most purposes, since the Moon moves 1 arc
second in 2 time seconds and the Sun 2.5 arc seconds in one minute.

The advantage of the Moshier mode of the Swiss Ephemeris is that it needs no
disk storage. Its disadvantage, besides the limited precision, is reduced
speed: it is about 10 times slower than JPL mode and the compressed JPL mode.

The Moshier Ephemeris covers the interval from 3000 BCE to 3000 CE. However,
Moshier notes that "the adjustment for the inner planets is strictly valid only
from 1350 B.C. to 3000 A.D., but may be used to 3000 B.C. with some loss of
precision". And: "The Moon's position is calculated by a modified version of
the lunar theory of Chapront-Touze' and Chapront. This has a precision of 0.5
arc second relative to DE404 for all dates between 1369 B.C. and 3000 A.D."
(Moshier, http://www.moshier.net/aadoc.html).

..
