=============
Sidereal time
=============

The sidereal time is computed inside the ``houses()`` function and returned via
the variable ``armc`` which measures sidereal time in degrees. To get sidereal
time in hours, divide ``armc`` by 15.

If the sidereal time is required separately from house calculation, two
functions are available. The second version requires obliquity and nutation to
be given in the function call, the first function computes them internally.
Both return sidereal time at the Greenwich Meridian, measured in hours.

.. autofunction:: swisseph.sidtime

.. autofunction:: swisseph.sidtime0

..
