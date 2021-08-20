======================================
Mean solar time versus True solar time
======================================

Universal Time (UT or UTC) is based on Mean Solar Time, AKA Local Mean Time,
which is a uniform measure of time. A day has always the same length,
independent of the time of the year.

In the centuries before mechanical clocks where used, when the reckoning of
time was mostly based on sun dials, the True Solar Time was used, also called
Local Apparent Time.

The difference between Local Mean Time and Local Apparent Time is called the
equation of time. This difference can become as large as 20 minutes.

If a historical date was noted in Local Apparent Time, it must first be
converted to Local Mean Time by applying the equation of time, before it can be
used to compute Universal Time (for the houses) and finally Ephemeris Time (for
the planets).

This conversion can be done using the function ``lat_to_lmt()``. The reverse
function is ``lmt_to_lat()``. If required, the equation of time itself, i. e.
the value ``e = LAT - LMT``, can be calculated using the function
``time_equ()``.

.. autofunction:: swisseph.time_equ

.. autofunction:: swisseph.lmt_to_lat

.. autofunction:: swisseph.lat_to_lmt

..
