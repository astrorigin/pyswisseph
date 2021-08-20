==========
Refraction
==========

The refraction depends on the atmospheric pressure and temperature at the
location of the observer.

.. autofunction:: swisseph.refrac

.. autofunction:: swisseph.refrac_extended

This function was created thanks to and with the help of the archaeoastronomer
Victor Reijs.

It is more correct and more skilled than the old function ``refrac()``.

It allows correct calculation of refraction for altitudes above sea > 0, where
the ideal horizon and planets that are visible may have a negative height.
(for ``refrac()``, negative apparent heights do not exist!)

It allows to manipulate the refraction constant.

If ``atpress`` is given the value 0, the function estimates the pressure from
the geographical altitude given in ``geoalt`` and ``attemp``. If ``geoalt`` is
0, ``atpress`` will be estimated for sea level.

Function returns:

- case 1, conversion from true altitude to apparent altitude:

  - apparent altitude, if body is observable above ideal horizon
  - true altitude (the input value); otherwise "ideal horizon" is the
    horizon as seen above an ideal sphere (as seen from a plane over the
    ocean with a clear sky)

- case 2, conversion from apparent altitude to true altitude:

  - the true altitude resulting from the input apparent altitude, if this
    value is a plausible apparent altitude, i.e. if it is a position above
    the ideal horizon
  - the input altitude; otherwise in addition the array dret returns the
    following values:

   - ``dret[0]`` true altitude, if possible; otherwise input value;
   - ``dret[1]`` apparent altitude, if possible; otherwise input value;
   - ``dret[2]`` refraction;
   - ``dret[3]`` dip of the horizon.

The body is above the horizon if the ``dret[0]`` != ``dret[1]``.

..
