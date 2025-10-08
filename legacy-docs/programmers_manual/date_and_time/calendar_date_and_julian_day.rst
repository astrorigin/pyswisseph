============================
Calendar date and Julian day
============================

These functions are needed to convert calendar dates to the astronomical time
scale which measures time in Julian days.

.. autofunction:: swisseph.julday

.. autofunction:: swisseph.date_conversion

.. autofunction:: swisseph.revjul

``julday()`` and ``date_conversion()`` compute a Julian day number from year,
month, day, and hour. ``date_conversion()`` checks in addition whether the date
is legal.

``revjul()`` is the reverse function of ``julday()``. It computes year, month,
day and hour from a Julian day number.

The Julian day number has nothing to do with Julius Cesar, who introduced the
Julian calendar, but was invented by the monk Julianus. The Julian day number
tells for a given date the number of days that have passed since the creation
of the world which was then considered to have happened on 1 Jan - 4712 at
noon. E.g. the 1.1.1900 corresponds to the Julian day number 2415020.5.

Midnight has always a JD with fraction 0.5, because traditionally the
astronomical day started at noon. This was practical because then there was no
change of date during a night at the telescope. From this comes also the fact
that noon ephemerides were printed before midnight ephemerides were introduced
early in the 20th century.

..
