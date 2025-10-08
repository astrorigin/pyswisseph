================================
Planetary moons and body centers
================================

Ephemerides of planetary moons and centers of body (COB) were introduced with
Swiss Ephemeris version 2.10.

Their Swiss Ephemeris body numbers are between ``PLMOON_OFFSET`` (= 9000) and
``AST_OFFSET`` (= 10000) and are constructed as follows:

.. code-block:: python

    pl = swe.PLMOON_OFFSET + planet_number * 100 + moon_number_in_JPL_Horizons

E.g., Jupiter moon Io:

.. code-block:: python

    pl = swe.PLMOON_OFFSET + swe.JUPITER * 100 + 1 # 9000 + 5 * 100 + 1 = 9501

Centers of body (COB) are calculated the same way, i.e. like a planetary moon
but with the "moon number" 99 e.g. Jupiter center of body:

.. code-block:: python

    pl = swe.PLMOON_OFFSET + swe.JUPITER * 100 + 99 # = 9599

=========== =============== ====
Planet      Moon numbers    COB
=========== =============== ====
Mars        9401 – 9402
Jupiter     9501 – 95xx     9599
Saturn      9601 – 96xx     9699
Uranus      9701 – 97xx     9799
Neptune     9801 – 98xx     9899
Pluto       9901 – 99xx     9999
=========== =============== ====

A full list of existing planetary moons is found here:
https://en.wikipedia.org/wiki/List_of_natural_satellites

The ephemeris files of the planetary moons and COB are in the subdirectory
``sat``. Like the subdirectories of asteroids, the directory sat must be
created in the path which is defined using the function ``set_ephe_path()``.

The ephemeris files can be downloaded from here:
https://www.astro.com/ftp/swisseph/ephe/sat/

The list of objects available in the Swiss Ephemeris is:

======= =================
Number  Object
======= =================
9401    Phobos/Mars
9402    Deimos/Mars
9501    Io/Jupiter
9502    Europa/Jupiter
9503    Ganymede/Jupiter
9504    Callisto/Jupiter
9599    Jupiter/COB
9601    Mimas/Saturn
9602    Enceladus/Saturn
9603    Tethys/Saturn
9604    Dione/Saturn
9605    Rhea/Saturn
9606    Titan/Saturn
9607    Hyperion/Saturn
9608    Iapetus/Saturn
9699    Saturn/COB
9701    Ariel/Uranus
9702    Umbriel/Uranus
9703    Titania/Uranus
9704    Oberon/Uranus
9705    Miranda/Uranus
9799    Uranus/COB
9801    Triton/Neptune
9802    Nereid/Neptune
9808    Proteus/Neptune
9899    Neptune/COB
9901    Charon/Pluto
9902    Nix/Pluto
9903    Hydra/Pluto
9904    Kerberos/Pluto
9905    Styx/Pluto
9999    Pluto/COB
======= =================

The maximum differences between barycenter and center of body (COB) are
(from one-day-step calculations over 150 years):

=========== ============================
Mars        (0.2 m, irrelevant to us)
Jupiter     0.075  arcsec (jd 2468233.5)
Saturn      0.053  arcsec (jd 2463601.5)
Uranus      0.0032 arcsec (jd 2446650.5)
Neptune     0.0036 arcsec (jd 2449131.5)
Pluto       0.088  arcsec (jd 2437372.5)
=========== ============================

If you prefer using COB rather than barycenters, you should understand that:

- The performance is not as good for COB as for barycenters. With transit
  calculations you could run into troubles.
- The ephemerides are limited to the time range 1900 to 2047.

..
