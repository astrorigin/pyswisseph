============================
Suryasiddhanta and Aryabhata
============================

The explanations given above are mainly derived from the article by Mercier.
However, it is possible to derive ayanamshas from ancient Indian works
themselves.

The planetary theory of the main work of ancient Indian astronomy, the
Suryasiddhanta, uses the so-called Kaliyuga era as its zero point, i.e. the
18th February 3102 BCE, 0:00 local time at Ujjain, which is at geographic
longitude of 75.7684565 east (Mahakala temple). This era is henceforth called
"K0s". This is also the zero date for the planetary theory of the ancient
Indian astronomer Aryabhata, with the only difference that he reckons from
Sunrise of the same date instead of midnight. We call this Aryabhatan Kaliyuga
era "K0a".

Aryabhata mentioned that he was 23 years old when exactly 3600 years had
elapsed since the beginning of the Kaliyuga era. If 3600 years with a year
length as defined by the Aryabhata are counted from K0a, we arrive at the 21st
March, 499 CE, 6:56:55.57 UT. At this point of time the mean Sun is assumed to
have returned to the beginning of the sidereal zodiac, and we can try to derive
an ayanamsha from this information. There are two possible solutions, though:

1. We can find the place of the mean Sun at that time using modern astronomical
   algorithms and define this point as the beginning of the sidereal zodiac.

2. Since Aryabhata believed that the zodiac began at the vernal point, we can
   take the vernal point of this date as the zero point.

The same calculations can be done based on K0s and the year length of the
Suryasiddhanta. The resulting date of Kali 3600 is the same day but about half
an hour later: 7:30:31.57 UT.

Algorithms for the mean Sun were taken from: Simon et alii, "Numerical
expressions for precession formulae and mean elements for the Moon and the
planets", in: Astron. Astrophys. 282,663-683 (1994).

Suryasiddhanta/equinox ayanamshas with zero year 499 CE
=======================================================

:Sweph n°: ``SIDM_SURYASIDDHANTA`` (21)
:Ayanamsha: 0
:t0: March 21st 499, 7:30:31.57 UT = 12:33:36 LMT at Ujjain, 75.7684565 E
:Note: Based on Suryasiddhanta: ingress of mean Sun into Aries at point of mean
       equinox of date.

..

:Sweph n°: ``SIDM_SURYASIDDHANTA_MSUN`` (22)
:Ayanamsha: -0.21463395
:Note: Based on Suryasiddhanta again, but assuming ingress of mean Sun into
       Aries at true position of mean Sun at the same epoch.

Aryabhata/equinox ayanamshas with zero year 499 CE
==================================================

:Sweph n°: ``SIDM_ARYABHATA`` (23)
:Ayanamsha: 0
:t0: March 21st 499, 6:56:55.57 UT = 12 LMT, local noon at Ujjain, 75.7684565 E
:Note: Based on Aryabhata, ingress of mean Sun into Aries at point of mean
       equinox of date.

..

:Sweph n°: ``SIDM_ARYABHATA_MSUN`` (24)
:Ayanamsha: -0.23763238
:Note: Based on Aryabhata again, but assuming ingress of mean Sun into Aries at
       true position of mean Sun at the same epoch.

Aryabhata/equinox ayanamsha with zero year 522 CE
=================================================

According to Govindasvamin (850 n. Chr.), Aryabhata and his disciples taught
that the vernal point was at the beginning of sidereal Aries in the year 522 CE
(= Shaka 444). This tradition probably goes back to an erroneous interpretation
of Aryabhata's above-mentioned statement that he was 23 years old when 3600 had
elapsed after the beginning of the Kaliyuga. For the sake of completeness, we
therefore add the following ayanamsha:

:Sweph n°: ``SIDM_ARYABHATA_522`` (37)
:Ayanamsha: 0
:t0: March 21st 522, 5:46:44 UT

Ayanamsha having Revati/zeta Piscium at polar longitude 359°50' in 499 CE
=========================================================================

:Sweph n°: ``SIDM_SS_REVATI`` (25)
:Ayanamsha: -0.79167046
:t0: March 21st 499, 7:30:31.57 UT, noon at Ujjain, 75.7684565 E
:Note: Revati/zePsc at polar ecliptic longitude 359°50'.

True Revati ayanamsha
=====================

:Sweph n°: ``SIDM_TRUE_REVATI`` (28)
:Note: Revati/zePsc is always exactly at longitude 359°50' (not polar!)

(Note, this was incorrectly implemented in SE 2.00 – SE 2.04. The Position of
Revati was 0°. Only from SE 2.05 on, this ayanamsha is correct.)

Unfortunately, other star positions given in Suryasiddhanta are not compatible
with the one of Revati. In particular the star Spica/Citra, which is stated to
be at 180° exactly, has been used to create another bunch of ayanamshas (see
next chapter).

True Pushya paksha ayanamsha
============================

Siddhantas usually assume the star Pushya (delta Cancri = Asellus Australis) at
106°. PVR Narasimha Rao believes this star to be the best anchor point for a
sidereal zodiac. In the Kalapurusha theory, which assigns zodiac signs to parts
of the human body, the sign of Cancer is assigned to the heart, and according
to Vedic spiritual literature, the root of human existence is in the heart.
Mr. Narasimha Rao therefore proposed the following ayanamsha:

:Sweph n°: ``SIDM_TRUE_PUSHYA`` (29)
:Note: Pushya/deCnC is always exactly at longitude 106°

Sources
=======

 Surya-Siddhanta: A Text Book of Hindu Astronomy by Ebenezer Burgess, ed.
 Phanindralal Gangooly (1989/1997) with a 45-page commentary by P. C. Sengupta
 (1935).

 D. Pingree, "Precession and Trepidation in Indian Astronomy", in JHA iii
 (1972), pp. 28f.

..
