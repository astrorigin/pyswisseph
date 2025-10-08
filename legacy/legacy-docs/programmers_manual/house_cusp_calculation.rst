======================
House cusp calculation
======================

The character codes of the most important house methods are:

=============== ===========================
Character       House method
=============== ===========================
``P``           Placidus
``K``           Koch
``O``           Porphyrius
``R``           Regiomontanus
``C``           Campanus
``A`` or ``E``  Equal (cusp 1 is Ascendant)
``W``           Whole sign
=============== ===========================

The complete list of house methods in alphabetical order is:

=============== ================================================
Character       House method
=============== ================================================
``B``           Alcabitus
``Y``           APC houses
``X``           Axial rotation system / Meridian system / Zariel
``H``           Azimuthal or horizontal system
``C``           Campanus
``F``           Carter "Poli-Equatorial"
``A`` or ``E``  Equal (cusp 1 is Ascendant)
``D``           Equal MC (cusp 10 is MC)
``N``           Equal/1=Aries
``G``           Gauquelin sector
--              Goelzer -> Krusinski
--              Horizontal system -> Azimuthal system
``I``           Sunshine (Makransky, solution Treindl)
``i``           Sunshine (Makransky, solution Makransky)
``K``           Koch
``U``           Krusinski-Pisa-Goelzer
--              Meridian system -> Axial rotation
``M``           Morinus
--              Neo-Porphyry -> Pullen SD
--              Pisa -> Krusinski
``P``           Placidus
--              Poli-Equatorial -> Carter
``T``           Polich/Page ("topocentric" system)
``O``           Porphyrius
``L``           Pullen SD (sinusoidal delta) – ex Neo-Porphyry
``Q``           Pullen SR (sinusoidal ratio)
``R``           Regiomontanus
``S``           Sripati
--              "Topocentric" system -> Polich/Page
``V``           Vehlow equal (Asc. in middle of house 1)
``W``           Whole sign
--              Zariel -> Axial rotation system
=============== ================================================

.. autofunction:: swisseph.house_name

.. autofunction:: swisseph.houses

.. autofunction:: swisseph.houses_armc

.. autofunction:: swisseph.houses_armc_ex2

.. autofunction:: swisseph.houses_ex

.. autofunction:: swisseph.houses_ex2

The extended house functions ``houses_ex()`` and ``houses_ex2()`` do exactly
the same calculations as ``houses()``. The difference is that the extended
functions have a parameter ``flags``, which can be set to ``FLG_SIDEREAL``, if
sidereal house positions are wanted. The house function returns data based on
the true equator and equinox of date. If the flag ``FLG_NONUT`` is set, then
the house cusps will be based on the mean equator and equinox of date. However,
we recommend to use the true equator and equinox. The function ``houses_ex2()``
also provides the speeds ("daily motions") of the house cusps and additional
points.

Before calling ``houses_ex()`` or ``houses_ex2()`` for sidereal house positions,
the sidereal mode can be set by calling the function ``set_sid_mode()``. If
this is not done, the default sidereal mode, i.e. the Fagan/Bradley ayanamsha,
will be used.

The function ``houses()``, ``houses_ex()``, and ``houses_ex2()`` are most
comfortable, as long as houses are to be calculated for a given date and
geographic position. Sometimes, however, one will need to compute houses from a
given ARMC, e.g. with the composite horoscope, which has no date, only a
composite ARMC which is computed from two natal ARMCs. In this case, the
function ``houses_armc()`` or ``houses_armc_ex2()``  can be used. Since these
functions require the ecliptic obliquity ``eps``, one will probably want to
calculate a composite value for this parameter also. To do this, one has to
call ``calc()`` with ``ECL_NUT`` for both birth dates and then calculate the
average of both ``eps``.

"Sunshine" or Makransky houses require a special handling with the function
``houses_armc()`` or ``houses_armc_ex2()``. The house system requires as a
parameter the declination of the Sun. The user has to calculate the declination
of the Sun and save it in the variable ``ascmc[9]``. For house cusps of a
composite chart, one has to calculate the composite declination of the Sun
(= average of the declinations of the natal Suns).

There is no extended function for ``houses_armc()``. Therefore, if one wants to
compute such exotic things as the house cusps of a sidereal composite chart,
the procedure will be more complicated:

.. code-block:: python

    # sidereal composite house computation
    # with true epsilon, but without nutation in longitude
    x1, rflags = swe.calc_ut(tjdut1, swe.ECL_NUT, 0)
    x2, rflags = swe.calc_ut(tjdut2, swe.ECL_NUT, 0)
    armc1 = swe.sidtime(tjdut1) * 15
    armc2 = swe.sidtime(tjdut2) * 15
    armc_comp = composite(armc1, armc2 ) # user defined function
    eps_comp = (x1[0] + x2[0]) / 2
    # ayanamsha for the middle of the two birth dates
    # the difference will be microscopic
    tjd_comp = (tjdut1 + tjdut2) / 2
    rflags, aya = swe.get_ayanamsa_ex_ut(tjd_comp, flags)
    cusps, ascmc = swe.houses_armc(armc_comp, geolat, eps_comp, hsys)
    for i in range(12):
        cusps[i] = swe.degnorm(cusps[i] - aya)
    for i in range(10):
        ascmc[i] = swe.degnorm(ascmc[i] - aya)

Or if you want to calculate sidereal progressions, do as follows:

- Calculate the tropical ``radix_armc``;
- ``radix_armc + direction_arc = directed_armc``
- Use ``houses_armc(directed_armc, ...)`` or ``houses_armc_ex2()`` for the
  house cusps
- Subtract ayanamsha (``get_ayanamsa_ex_ut()``) from the values.

.. note::

    In the array ``ascmc``, the function returns the following values:

    - ``ascmc[0]`` = Ascendant
    - ``ascmc[1]`` = MC
    - ``ascmc[2]`` = ARMC
    - ``ascmc[3]`` = Vertex
    - ``ascmc[4]`` = "equatorial ascendant"
    - ``ascmc[5]`` = "co-ascendant" (Walter Koch)
    - ``ascmc[6]`` = "co-ascendant" (Michael Munkasey)
    - ``ascmc[7]`` = "polar ascendant" (M. Munkasey)

    The following constants can be used to find these values:

    - ``ASC`` = 0
    - ``MC`` = 1
    - ``ARMC`` = 2
    - ``VERTEX`` = 3
    - ``EQUASC`` = 4
    - ``COASC1`` = 5
    - ``COASC2`` = 6
    - ``POLASC`` = 7
    - ``NASCMC`` = 8

..
