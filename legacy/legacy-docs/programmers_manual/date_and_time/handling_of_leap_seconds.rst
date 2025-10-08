========================
Handling of leap seconds
========================

The insertion of leap seconds is not known in advance. We will update the Swiss
Ephemeris whenever the IERS announces that a leap second will be inserted.
However, if the user does not want to wait for our update or does not want to
download a new version of the Swiss Ephemeris, he can create a file
``seleapsec.txt`` in the ephemeris directory. The file looks as follows
(lines with ``#`` are only comments):

.. literalinclude:: seleapsec.txt
    :language: text

Before 1972, ``utc_to_jd()`` treats its input time as UT1.

.. note::

    UTC was introduced in 1961. From 1961 - 1971, the length of the UTC second
    was regularly changed, so that UTC remained very close to UT1.

From 1972 on, input time is treated as UTC.

If ``delta_t - nleap - 32.184 > 1``, the input time is treated as UT1.

.. note::

    Like this we avoid errors greater than 1 second in case that the leap
    seconds table (or the Swiss Ephemeris version) is not updated for a long
    time.

..
