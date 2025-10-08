========================================================
The Babylonian tradition and the Fagan/Bradley ayanamsha
========================================================

There have been several attempts to calculate the zero point of the Babylonian
ecliptic from cuneiform lunar and planetary tablets. Positions were given
relative to some siderealy fixed reference point. The main problem in fixing
the zero point is the inaccuracy of ancient observations.

Kugler ayanamshas
=================

Around 1900 F.X. Kugler found that the Babylonian star positions fell into
three groups:

1.

:Sweph n°: ``SIDM_BABYL_KUGLER1`` (9)
:Ayanamsha: -5°40'
:t0: -100

2.

:Sweph n°: ``SIDM_BABYL_KUGLER2`` (10)
:Ayanamhsa: -4°16'
:t0: -100
:Note: Spica at 29°Vir26'

3.

:Sweph n°: ``SIDM_BABYL_KUGLER3`` (11)
:Ayanamsah: -3°25'
:t0: -100

.. note::

    The "Sweph n°" refers to an integer constant of the API.
    See chapter :doc:`/programmers_manual/sidereal_mode`.

Huber ayanamsha
===============

In 1958, Peter Huber reviewed the topic in the light of new material and found:

:Sweph n°: ``SIDM_BABYL_HUBER`` (12)
:Ayanamsha: -4°28' +/- 20'
:t0: –100
:Note: Spica at 29°Vir07'59"

The standard deviation was 1°08'.

(Note, this ayanamsha was corrected with SE version 2.05. A wrong value of
-4°34' had been taken over from Mercier, "Studies on the Transmission of
Medieval Mathematical Astronomy", IIb, p. 49.)

Eta Piscium ayanamsha
=====================

In 1977 Raymond Mercier noted that the zero point might have been defined as
the ecliptic point that culminated simultaneously with the star eta Piscium
(Al Pherg). For this possibility, we compute:

:Sweph n°: ``SIDM_BABYL_ETPSC`` (13)
:Ayanamsha: -5°04'46"
:t0: –129
:Note: Spica at 29°Vir21'

Fagan/Bradley ayanamsha
=======================

Around 1950, Cyril Fagan, the founder of the modern western sidereal astrology,
reintroduced the old Babylonian zodiac into astrology, placing the fixed star
Spica near 29°00 Virgo. As a result of "rigorous statistical investigation"
(astrological!) of solar and lunar ingress charts, Donald Bradley decided that
the sidereal longitude of the vernal point must be computed from Spica at
29°Vir06'05" disregarding its proper motion. Fagan and Bradley defined their
"synetic vernal point" as:

:Sweph n°: ``SIDM_FAGAN_BRADLEY`` (0)
:Ayanamsha: 24°02'31.36"
:t0: Jan. 1st, 1950
:Note: Spica at 29°Vir06'05" (without aberration)

(For the year –100, this ayanamsha places Spica at 29°Vir07'32".)

The difference between P. Huber's zodiac and the Fagan/Bradley ayanamsha is
smaller than 1'.

Aldebaran-Antares ayanamsha
===========================

According to a text by Fagan (found on the internet), Bradley "once opined in
print prior to "New Tool" that it made more sense to consider Aldebaran and
Antares, at 15 degrees of their respective signs, as prime fiducials than it
did to use Spica at 29 Virgo". Such statements raise the question if the
sidereal zodiac ought to be tied up to one of those stars.

For this possibility, Swiss Ephemeris gives an Aldebaran ayanamsha:

:Sweph n°: ``SIDM_ALDEBARAN_15TAU`` (14)
:t0: around -100
:Note: Aldebaran at 15°Tau00'00" and Antares at 15°Sco00'17"

The difference between this ayanamsha and the Fagan/Bradley one is 1'06".

Britton ayanamsha
=================

In 2010, the astronomy historian John P. Britton made another investigation in
cuneiform astronomical tablets and corrected Huber's by a 7 arc minutes.

:Sweph n°: ``SIDM_BABYL_BRITTON`` (38)
:Ayanamsha: -3.2° +- 0.09° (5'24")
:t0: Jan. 1st, 0
:Note: Spica at 29°Vir14'58"

(For the year -100, this ayanamsha places Spica at 29Vir15'02".)

This ayanamsha deviates from the Fagan/Bradley aynamsa by 7 arc min.

Sources
=======

 Raymond Mercier, "Studies in the Medieval Conception of Precession", in
 'Archives Internationales d'Histoire des Sciences', (1976) 26:197-220
 (part I), and (1977) 27:33-71 (part II);

 Cyril Fagan and Brigadier R.C. Firebrace, -Primer of Sidereal Astrology,
 Isabella, MO, USA 1971;

 P. Huber, "Über den Nullpunkt der babylonischen Ekliptik", in: Centaurus
 1958, 5, pp. 192-208;

 John P. Britton, "Studies in Babylonian lunar theory: part III. The
 introduction of the uniform zodiac", in Arch. Hist. Exact. Sci.
 (2010)64:617-663, p. 630.

Vettius Valens ayanamsha
========================

:Sweph n°: ``SIDM_SIDM_VALENS_MOON`` (42)

The ayanamsha used by Greek astrologers in late antiquity does not have a
clear-cut definition. However, from extant charts it is known that the
ayanamsha was about -3° in the year 150 CE. The following ayanamsha is derived
from Vettius Valens' (2nd century CE) lunar positions, according to:
James H. Holden, "The Classical Zodiac", in: AFA Journal of Research, vol. 7,
no. 2 1995, p. 12.

..
