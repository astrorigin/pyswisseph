==================
UTC and Julian day
==================

The following functions, which were introduced with Swiss Ephemeris version
1.76, do a similar job as the functions described before. The difference is
that input and output times are Coordinated Universal Time (UTC). For
transformations between wall clock (or arm wrist) time and Julian Day numbers,
these functions are more correct. The difference is below 1 second, though.

Use these functions to convert:

- local time to UTC and UTC to local time;
- UTC to a Julian day number, and
- a Julian day number to UTC.

Past leap seconds are hard coded in the Swiss Ephemeris. Future leap seconds
can be specified in the file ``seleapsec.txt``.
See :doc:`` TODO.

.. note::

    In case of leap seconds, the input or output time may be 60.9999 seconds.
    Input or output forms have to allow for this.

.. autofunction:: swisseph.utc_time_zone

.. autofunction:: swisseph.utc_to_jd

.. autofunction:: swisseph.jdet_to_utc

.. autofunction:: swisseph.jdut1_to_utc

Get correct planetary positions from date and time
==================================================

.. literalinclude:: datetime_example1.py
    :language: python

Get date and time from Julian day number
========================================

Depending on whether you have ``tjd_et`` (Julian day as ET (TT)) or ``tjd_ut``
(Julian day as UT (UT1)), use one of the two functions ``jdet_to_utc()`` or
``jdut1_to_utc()``.

.. literalinclude:: datetime_example2.py
    :language: python

..
