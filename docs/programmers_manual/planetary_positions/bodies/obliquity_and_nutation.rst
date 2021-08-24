======================
Obliquity and nutation
======================

A special body number ``ECL_NUT`` is provided to compute the obliquity of
the ecliptic and the nutation. Of course nutation is already added internally
to the planetary coordinates by ``calc()`` but sometimes it will be
needed as a separate value.

.. code-block:: python

    xx, retflags = swe.calc(tjd_et, swe.ECL_NUT, 0)

``xx`` is a tuple of 6 floats as usual. It will be filled as follows:

=========== ==================================================
``xx[0]``   true obliquity of the Ecliptic (includes nutation)
``xx[1]``   mean obliquity of the Ecliptic
``xx[2]``   nutation in longitude
``xx[3]``   nutation in obliquity
``xx[4]``   0
``xx[5]``   0
=========== ==================================================

..
