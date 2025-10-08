====================
Additional asteroids
====================

Body numbers of other asteroids are above ``AST_OFFSET`` (= 10000) and have to
be constructed as follows:

.. code-block:: python

    pl = swe.AST_OFFSET + minor_planet_catalogue_number

e.g. for asteroid Eros:

.. code-block:: python

    pl = swe.AST_OFFSET + 433

.. note::

    Asteroid names and catalog numbers are listed in the file ``seasnam.txt``.
    This file is in the ephemeris directory, and downloadable from
    `astro.com website`_.

.. _astro.com website: https://www.astro.com/swisseph

Examples are:

======= =========== ===================================================================
Number  Name        Comment
======= =========== ===================================================================
5       Astraea
6       Hebe
7       Iris
8       Flora
9       Metis
10      Hygiea
30      Urania
42      Isis        Not identical with "Isis-Transpluto"
153     Hilda       Has an own asteroid belt at 4 AU
227     Philosophia
251     Sophia
259     Aletheia
275     Sapientia
279     Thule       Asteroid close to Jupiter
375     Ursula
433     Eros
763     Cupido      Different from Witte's Cupido
944     Hidalgo
1181    Lilith      Not identical with Dark Moon 'Lilith'
1221    Amor
1387    Kama
1388    Aphrodite
1862    Apollo      Different from Witte's Apollon
3553    Damocles    Highly eccentric orbit between Mars and Uranus
3753    Cruithne    "Second moon" of Earth
4341    Poseidon    Greek Neptune, different from Witte's Poseidon
4464    Vulcano     Fire god, different from Witte's Vulkanus and intramercurian Vulcan
5731    Zeus        Greek Jupiter, different from Witte's Zeus
7066    Nessus      Third named Centaur, between Saturn and Pluto
======= =========== ===================================================================

There are two ephemeris files for each asteroid (except the main asteroids), a
long one and a short one, e.g:

=================== ===============================================================
``se09999.se1``     long-term ephemeris of asteroid number 9999, 3000 BCE – 3000 CE
``se09999s.se1``    short ephemeris of asteroid number 9999, 1500 – 2100 CE
=================== ===============================================================

The larger file is about 10 times the size of the short ephemeris. If the user
does not want an ephemeris for the time before 1500 he might prefer to work
with the short files. If so, just copy the files ending with "s.se1" to your
hard disk. ``calc()`` tries the long one and on failure automatically takes the
short one.

Asteroid ephemerides are looked for in the subdirectories ``ast0``, ``ast1``,
``ast2`` .. ``ast9`` etc. of the ephemeris directory and, if not found there,
in the ephemeris directory itself. Asteroids with numbers 0 – 999 are expected
in directory ``ast0``, those with numbers 1000 – 1999 in directory ``ast1`` etc.

Note that not all asteroids can be computed for the whole period of Swiss
Ephemeris. The orbits of some of them are extremely sensitive to perturbations
by major planets. E.g. Chiron, cannot be computed for the time before 650 CE
and after 4650 CE because of close encounters with Saturn. Outside this time
range, Swiss Ephemeris raises an exception. Be aware, that the user will have
to handle this case in his program. Computing Chiron transits for Jesus or
Alexander the Great will not work.

The same is true for Pholus before 3850 BCE, and for many other asteroids, as
e.g. 1862 Apollo. He becomes chaotic before the year 1870 CE, when he
approaches Venus very closely. Swiss Ephemeris does not provide positions of
Apollo for earlier centuries!

..
