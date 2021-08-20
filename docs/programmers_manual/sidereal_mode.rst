=======================
Sidereal mode functions
=======================

The predefined sidereal modes are:

=================================== ============================
Name                                Constant
=================================== ============================
Fagan/Bradley                       ``SIDM_FAGAN_BRADLEY``
De Luce                             ``SIDM_DELUCE``
Raman                               ``SIDM_RAMAN``
Usha/Shashi                         ``SIDM_USHASHASHI``
Krishnamurti                        ``SIDM_KRISHNAMURTI``
Djwhal Khul                         ``SIDM_DJWHAL_KHUL``
Yukteshwar                          ``SIDM_YUKTESHWAR``
J.N. Bhasin                         ``SIDM_JN_BHASIN``
Babylonian/Kugler 1                 ``SIDM_BABYL_KUGLER1``
Babylonian/Kugler 2                 ``SIDM_BABYL_KUGLER2``
Babylonian/Kugler 3                 ``SIDM_BABYL_KUGLER3``
Babylonian/Huber                    ``SIDM_BABYL_HUBER``
Babylonian/Eta Piscium              ``SIDM_BABYL_ETPSC``
Babylonian/Aldebaran = 15 Tau       ``SIDM_ALDEBARAN_15TAU``
Hipparchos                          ``SIDM_HIPPARCHOS``
Sassanian                           ``SIDM_SASSANIAN``
Galact. Center = 0 Sag              ``SIDM_GALCENT_0SAG``
J2000                               ``SIDM_J2000``
J1900                               ``SIDM_J1900``
B1950                               ``SIDM_B1950``
Suryasiddhanta                      ``SIDM_SURYASIDDHANTA``
Suryasiddhanta, mean Sun            ``SIDM_SURYASIDDHANTA_MSUN``
Aryabhata                           ``SIDM_ARYABHATA``
Aryabhata, mean Sun                 ``SIDM_ARYABHATA_MSUN``
SS Revati                           ``SIDM_SS_REVATI``
SS Citra                            ``SIDM_SS_CITRA``
True Citra                          ``SIDM_TRUE_CITRA``
True Revati                         ``SIDM_TRUE_REVATI``
True Pushya (PVRN Rao)              ``SIDM_TRUE_PUSHYA``
Galactic Center (Gil Brand)         ``SIDM_GALCENT_RGBRAND``
Galactic Equator (IAU1958)          ``SIDM_GALEQU_IAU1958``
Galactic Equator                    ``SIDM_GALEQU_TRUE``
Galactic Equator mid-Mula           ``SIDM_GALEQU_MULA``
Skydram (Mardyks)                   ``SIDM_GALALIGN_MARDYKS``
True Mula (Chandra Hari)            ``SIDM_TRUE_MULA``
Dhruva/Gal.Center/Mula (Wilhelm)    ``SIDM_GALCENT_MULA_WILHELM``
Aryabhata 522                       ``SIDM_ARYABHATA_522``
Babylonian/Britton                  ``SIDM_BABYL_BRITTON``
"Vedic"/Sheoran                     ``SIDM_TRUE_SHEORAN``
Cochrane (Gal.Center = 0 Cap)"      ``SIDM_ALCENT_COCHRANE``
Galactic Equator (Fiorenza)         ``SIDM_GALEQU_FIORENZA``
Vettius Valens                      ``SIDM_VALENS_MOON``
Lahiri 1940                         ``SIDM_LAHIRI_1940``
Lahiri VP285                        ``SIDM_LAHIRI_VP285``
Krishnamurti-Senthilathiban         ``SIDM_KRISHNAMURTI_VP291``
Lahiri ICRC                         ``SIDM_LAHIRI_ICRC``
=================================== ============================

.. autofunction:: swisseph.get_ayanamsa_name

.. autofunction:: swisseph.set_sid_mode

.. note::

    the parameters set by ``set_sid_mode()`` survive calls of the function
    ``close()``.

To define your own sidereal mode, use ``SIDM_USER`` and set the reference date
(``t0``) and the initial value of the ayanamsha (``ayan_t0``)::

    ayan_t0 = tropical_position_t0 – sidereal_position_t0

Without additional specifications, the traditional method is used. The
ayanamsha measured on the ecliptic of ``t0`` is subtracted from tropical
positions referred to the ecliptic of date.

.. note::

    This method will not provide accurate results if you want coordinates
    referred to the ecliptic of one of the following equinoxes:

     - ``SIDM_J2000``, ``SIDM_J1900``, ``SIDM_B1950``

Instead, you have to use a correct coordinate transformation as described in
the following.

User-defined ayanamsha with t0 in UT
====================================

If a user-defined ayanamsha is set using ``SIDM_USER``, then the ``t0`` is
usually considered to be TT (ET). However, ``t0`` can be provided as UT if
``SIDM_USER`` is combined with ``SIDBIT_USER_UT``.

Example:

.. code-block:: python

    swe.set_sid_mode(swe.SIDM_USER|swe.SIDBIT_USER_UT, 1720935.589444445, 0)
    flags |= swe.FLG_SIDERAL
    xx, retflags = swe.calc_ut(tjdut, pl, flags)

Transformation of ecliptic coordinates to the ecliptic of a particular date
===========================================================================

To understand these options, please study them in the chapter TODO.

If a transformation to the ecliptic of ``t0`` is required the following bit
can be added ('ored') to the value of the variable ``sidmode``:
``SIDBIT_ECL_T0``.

Example:

.. code-block:: python

    swe.set_sid_mode(swe.SIDM_J2000|swe.SIDBIT_ECL_T0, 0, 0)
    flags |= swe.FLG_SIDEREAL
    xx, retflags = swe.calc_ut(tjdut, pl, flags)

This procedure is required for the following sidereal modes, i.e. for
transformation to the ecliptic of one of the standard equinoxes:

 - ``SIDM_J2000``, ``SIDM_J1900``, ``SIDM_B1950``

If a transformation to the ecliptic of date is required the following bit can
be added ('ored') to the value of the variable ``sidmode``: ``SIDBIT_ECL_DATE``.

Example:

.. code-block:: python

    swe.set_sid_mode(swe.SIDM_J2000|swe.SIDBIT_ECL_DATE, 0, 0)
    flags |= swe.FLG_SIDEREAL
    xx, retflags = swe.calc_ut(tjdut, pl, flags)

Calculating precession-corrected transits
=========================================

The function ``set_sid_mode()`` can also be used for calculating
"precession-corrected transits". There are two methods, of which you have to
choose the one that is more appropriate for you.

1. If you already have tropical positions of a natal chart, you can proceed as
   follows:

   .. code-block:: python

       xx, retflags = swe.calc(tjdet_natal, swe.ECL_NUT, 0)
       nut_long_natal = xx[2]
       swe.set_sid_mode(swe.SIDBIT_USER|swe.SIDBIT_ECL_T0, tjdet, nut_long_natal)

   Where ``tjdet_natal`` is the Julian day of the natal chart (Ephemeris Time).

   After this, calculate the transits, using ``calc()`` with the sidereal bit:

   .. code-block:: python

       flags |= swe.FLG_SIDEREAL
       xx, retflags = swe.calc(tjdet_transit, pl, flags)

2. If you do not have tropical natal positions yet, if you do not need them
   and are just interested in transit times, you can have it simpler:

   .. code-block:: python

       swe.set_sid_mode(swe.SIDBIT_USER|swe.SIDBIT_ECL_T0, tjdet, 0)
       flags |= swe.FLG_SIDEREAL
       xx, retflags = swe.calc(tjdet_natal, pl_natal, flags)
       xx, retflags = swe.calc(tjdet_transit, pl_transit, flags)

   In this case, the natal positions will be tropical but without nutation.
   Note that you should not use them for other purposes.

Solar system rotation plane
===========================

For sidereal positions referred to the solar system rotation plane, use the
flag ``SIDBIT_SSY_PLANE``.

Ayanamsha
=========

These functions compute the ayanamsha, i.e. the distance of the tropical
vernal point from the sidereal zero point of the zodiac. The ayanamsha is
used to compute sidereal planetary positions from tropical ones::

    pos_sid = pos_trop – ayanamsha

Important information concerning the values returned:

- The functions ``get_ayanamsa()`` and ``get_ayanamsa_ut()`` provide the
  ayanamsha without nutation.
- The functions ``get_ayanamsa_ex()`` and ``get_ayanamsa_ex_ut()`` provide the
  ayanamsha with or without nutation depending on the parameter ``flags``.
  If ``flags`` contains ``FLG_NONUT`` the ayanamsha value is calculated
  without nutation, otherwise it is calculated including nutation.

It is not recommended to use the ayanamsha functions for calculating sidereal
planetary positions from tropical positions, since this could lead to
complicated confusions. For sidereal planets, please use ``calc_ut()`` and
``calc()`` with the flag ``FLG_SIDEREAL``.

Use the ayanamsha function only for "academical" purposes, e.g. if you want to
indicate the value of the ayanamsha on a horoscope chart. In this case, it is
recommended to indicate the ayanamsha including nutation.

Ayanamsha without nutation may be useful in historical research, where the
focus usually is on the mere precessional component of the ayanamsha.

Special case of "true" ayanamshas such as "True Chitrapaksha" etc.: The flags
``FLG_TRUEPOS``, ``FLG_NOABERR`` and ``FLG_NOGDEFL`` can be used here, but
users should not do that unless they really understand what they are doing. It
means that the same flags are internally used for the calculation of the
reference star (e.g. Citra/Spica). Slightly different ayanamsha values will
result depending on these flags.

Before calling one of these functions, you have to set the sidereal mode with
``set_sid_mode()``, unless you want the default sidereal mode, which is the
Fagan/Bradley ayanamsha.

.. autofunction:: swisseph.get_ayanamsa_ex_ut

.. autofunction:: swisseph.get_ayanamsa_ex

.. autofunction:: swisseph.get_ayanamsa_ut

.. autofunction:: swisseph.get_ayanamsa

The functions ``get_ayanamsa_ex_ut()`` and ``get_ayanamsa_ex()`` were
introduced with Swiss Ephemeris version 2.02, the former expecting input time
as UT, the latter as ET/TT. These functions are better than the older functions
``get_ayanamsa_ut()`` and ``get_ayanamsa()``.

The function ``get_ayanamsa_ex_ut()`` uses a Delta T consistent with the
``flags`` specified.

The function ``get_ayanamsa_ex()`` does not depend on Delta T; however with
fixed-star-based ayanamshas like True Chitrapaksha or True Revati, the fixed
star position also depends on the solar ephemeris (annual aberration of the
star), which can be calculated with any of the three ephemeris flags.

The differences between the values provided by the new and old functions are
very small and possibly only relevant for precision fanatics.

The function ``get_ayanamsa_ut()`` was introduced with Swisseph Version 1.60
and expects Universal Time instead of Ephemeris Time.

..
