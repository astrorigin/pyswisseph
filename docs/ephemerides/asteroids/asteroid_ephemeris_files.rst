========================
Asteroid ephemeris files
========================

The standard distribution of SwissEph includes the main asteroids Ceres,
Pallas, Juno, Vesta, as well as 2060 Chiron, and 5145 Pholus. To compute them,
one must have the main-asteroid ephemeris files in the ephemeris directory.

The names of these files are of the following form:

    ``seas_18.se1`` (main asteroids for 600 years from 1800 - 2400)

The size of such a file is about 200 kb.

All other asteroids are available in separate files. The names of additional
asteroid files look like:

    ``se00433.se1`` (the file of asteroid no. 433 (= Eros))

These files cover the period 3000 BCE - 3000 CE.

A short version for the years 1500 – 2100 CE has the file name with an ``s``
embedded, ``se00433s.se1``.

The numerical integration of the all numbered asteroids is an ongoing effort.
In December 1998, 8000 asteroids were numbered, and their orbits computed by
the developers of Swiss Ephemeris. In January 2001, the list of numbered
asteroids reached 20957, in January 2014 more than 380.000, and it is still
growing very fast.

Any asteroid can be called either with the JPL, the Swiss, or the Moshier
ephemeris flag, and the results will be slightly different. The reason is that
the solar position (which is needed for geocentric positions) will be taken
from the ephemeris that has been specified.

Availability of asteroid files
------------------------------

All short files (over 200000) are available for free download at our ftp server
ftp://ftp.astro.ch/pub/swisseph. (and https://www.astro.com/ftp/swisseph/ephe/)

The purpose of providing this large number of files for download is that the
user can pick those few asteroids he/she is interested in.

For all named asteroids also a long (6000 years) file is available in the
download area.

..
