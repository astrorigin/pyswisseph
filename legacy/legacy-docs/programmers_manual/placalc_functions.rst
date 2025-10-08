=================
Placalc functions
=================

Placalc, the predecessor of SwissEph, had included several functions that we do
not need for anymore. Nevertheless we include them again in our DLL, because
some users of our software may have taken them over and use them in their
applications. However, we gave them new names that were more consistent with
SwissEph..

Placalc used angular measurements in centiseconds a lot; a centisecond is
1/100 of an arc second. The C type CSEC or centisec is a 32-bit integer. CSEC
was used because calculation with integer variables was considerably faster
than floating point calculation on most CPUs in 1988, when Placalc was written.

In the Swiss Ephemeris we have dropped the use of centiseconds and use double
(64-bit floating point) for all angular measurements.

.. autofunction:: swisseph.csnorm

.. autofunction:: swisseph.difcsn

.. autofunction:: swisseph.difdegn

.. autofunction:: swisseph.difcs2n

.. autofunction:: swisseph.difdeg2n

.. autofunction:: swisseph.csroundsec

.. autofunction:: swisseph.d2l

.. autofunction:: swisseph.day_of_week

.. autofunction:: swisseph.cs2timestr

.. autofunction:: swisseph.cs2lonlatstr

.. autofunction:: swisseph.cs2degstr

..
