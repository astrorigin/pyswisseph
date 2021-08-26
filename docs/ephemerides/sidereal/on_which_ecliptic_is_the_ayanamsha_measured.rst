============================================
On which ecliptic is the ayanamsha measured?
============================================

1. The traditional algorithm (implemented in Swiss Ephemeris as default mode)
=============================================================================

As has been stated, sidereal planetary positions are computed from the
following equation: ``sidereal_position = tropical_position – ayanamsha``.

The ayanamsha of a given date t is computed from an initial value of the
ayanamsha at some initial date (e.g. t0 = 1 Jan 1900) and the speed of the
vernal point, the so-called precession rate:
``ayanamsha(t) = ayanamsha(t0) + precession(t-t0)``.

Unfortunately, this procedure is not really clean because the two formulae do
not operate on exactly the same plane. It may work sufficiently well in an
ordinary astrologer's practice. However, if very high accuracy is wanted over a
long period of time, then this approach is too simplistic.

The precession of the equinox is not only a matter of ecliptical longitude, but
a more complex phenomenon. It has two components:

a) The soli-lunar precession: The combined gravitational pull of the Sun and
the Moon on the equatorial bulge of the Earth causes the Earth axis to move
very slowly, in the way of a spinning top. As a result of this movement, the
vernal point moves around the ecliptic with a speed of about 50" per year. This
cycle has a period of roughly 26000 years.

b) The planetary precession: The Earth orbit itself is not fixed. The
gravitational influence from the planets causes it to slowly change its
orientation. As a result, the obliquity of the ecliptic currently decreases by
47" per century. This change also has some impact on the position of the vernal
point. (Note, however, that relative to the ecliptic of a fixed date, the
equator keeps an almost constant angle, with a change of only a couple of 0.06"
cty-2.)

Because the ecliptic plane is not fixed, it is not fully correct to subtract an
ayanamsha from the tropical position in order to get a sidereal position. Let
us take, e.g., the Fagan/Bradley ayanamsha, which can be defined by:

``ayanamsha = 24°02'31.36" + P(Je-Js)``,

where Js is the initial epoch or start date of the ayanamsha, in our case 1
Jan. 1950, and Je is the "end date" for which the ayanamsha is to be calculated.

24°02'31.36" is the value of the ayanamsha on the initial date Js = 1 Jan 1950.
It is obviously measured on the ecliptic of Js itself. P(Je-Js) is the distance
of the vernal point at the end epoch Je from the position of the vernal point
on the start epoch Js = 1 Jan 1950. Again, this distance is measured on the
ecliptic of Js.

Now, the value of ayanamsha is subtracted from a planetary position which is
referred to the ecliptic of the epoch Je, (not Js!). This approach is not
really correct. The error may be very small, but the ecliptic of Js and the
ecliptic of Je are not exactly in the same plane.

Precession polynomials found in astronomical literature are also relative to
Js. E.g. Indian Astronomical Ephemeris 1989 (IAE 1989), p. 525, gives the
following formula:

P\ :sub:`N`\  = ``(5029.0966 + 2.22226 * T-0.000042 * T2) * t + (1.11161 - 0.000127 * T) * t2 - 0.000113 * t3``

``t= (Je - Js) / 36525 ; T= (Js-2451545) / 36525``

If the start date Js is J2000 (i.e. 1 Jan. 2000, 12:00 TT), then the formula can also be written simpler:

P\ :sub:`N`\  = ``5029.0966 * t + 1.11161 *  t2 - 0.000113*t3``

According to IAE 1989, the resulting value P\ :sub:`N`\ is "referred to the
fixed ecliptic and equinox of Js". Thus, in a really correct calculation this
value should not be applied to a planetary or star position relative to the
ecliptic and equinox of Je. However, this is exactly what is done when sidereal
ephemerides are calculated from tropical ones.

As a result, an object that does not move relative to a fixed sidereal
reference frame, still has an apparent motion relative a sidereal zodiac. If we
compute its precise tropical position for several dates and then subtract the
Fagan/Bradley or Lahiri ayanamsha for the same dates in order to get its
sidereal position, then these positions will all be slightly different. This
difference can be considerable over long periods of time. Let us give two
examples to illustrate this phenomenon.

Long-term ephemeris of some fictitious star near the ecliptic that has no
proper motion (small change in longitude):

=========== =============== =============
Date        Longitude       Latitude
=========== =============== =============
-12000      335°16'55.2211  0°55'48.9448
-11000      335°16'54.9139  0°47'55.3635
-10000      335°16'46.5976  0°40'31.4551
-9000       335°16'32.6822  0°33'40.6511
-8000       335°16'16.2249  0°27'23.8494
-7000       335°16'00.1841  0°21'41.0200
-6000       335°15'46.8390  0°16'32.9298
-5000       335°15'37.4554  0°12'01.7396
-4000       335°15'32.2252  0°08'10.3657
-3000       335°15'30.4535  0°05'01.3407
-2000       335°15'30.9235  0°02'35.9871
-1000       335°15'32.3268  0°00'54.2786
0           335°15'33.6425  -0°00'04.7450
1000        335°15'34.3645  -0°00'22.4060
2000        335°15'34.5249  -0°00'00.0196
3000        335°15'34.5216  0°01'01.1573
=========== =============== =============

Long-term ephemeris of some fictitious star with high ecliptic latitude and no
proper motion (bigger change in longitude value):

=========== =============== =============
Date        Longitude       Latitude
=========== =============== =============
-12000      25°48'34.9812   58°55'17.4484
-11000      25°33'30.5709   58°53'56.6536
-10000      25°18'18.1058   58°53'20.5302
-9000       25°03'09.2517   58°53'26.8693
-8000       24°48'12.6320   58°54'12.3747
-7000       24°33'33.6267   58°55'34.7330
-6000       24°19'16.3325   58°57'33.3978
-5000       24°05'25.4844   59°00'08.8842
-4000       23°52'06.9457   59°03'21.4346
-3000       23°39'26.8689   59°07'10.0515
-2000       23°27'30.5098   59°11'32.3495
-1000       23°16'21.6081   59°16'25.0618
0           23°06'02.6324   59°21'44.7241
1000        22°56'35.5649   59°27'28.1195
2000        22°48'02.6254   59°33'32.3371
3000        22°40'26.4786   59°39'54.5816
=========== =============== =============

Exactly the same kind of thing happens to sidereal planetary positions if one
calculates them in the traditional way. They are actually given relative to a
moving reference frame. The "fixed zodiac" is not really fixed. When observed
over long periods of time in quick motion, it seems to wobble.

The wobbling of the ecliptic plane also influences ayanamshas that are referred
to the nodes of the galactic equator with the ecliptic.

=========== =========
Year        Diff in "
=========== =========
-3000       -9.633
-2500       -8.472
-2000       -7.049
-1500       -5.528
-1000       -4.052
-500        -2.735
0           -1.656
500         -0.854
1000        -0.334
1500        -0.067
1600        -0.040
1700        -0.020
1800        -0.007
1900        -0.001
1920        -0.000
1940        0.000
1960        0.000
1980        0.000
2000        -0.000
2020        -0.001
2040        -0.002
2060        -0.003
2080        -0.004
2100        -0.005
2200        -0.015
2300        -0.029
2400        -0.046
2500        -0.066
3000        -0.190
3500        -0.304
4000        -0.357
=========== =========

Note that the differences are around a millisecond of arc or below for current
decades, but greater than an arc second 2000 years ago.

However, if the reference epoch is in the remote past, e.g. when ayanamsha is
calculated from a zero ayanamsha epoch on the equinox 285 CE, then the
differences are near zero only near that epoch, but amount to 0.65" in 2020:

=========== =========
Year        Diff in "
=========== =========
-3000       -4.209
-2500       -3.250
-2000       -2.279
-1500       -1.408
-1000       -0.720
-500        -0.258
0           -0.032
500         -0.016
1000        -0.161
1500        -0.395
1600        -0.446
1700        -0.496
1800        -0.546
1900        -0.595
1920        -0.604
1940        -0.614
1960        -0.623
1980        -0.633
2000        -0.642
2020        -0.651
2040        -0.660
2060        -0.669
2080        -0.677
2100        -0.686
2200        -0.727
2300        -0.765
2400        -0.799
2500        -0.828
3000        -0.895
3500        -0.810
4000        -0.572
=========== =========

3. Projection onto the ecliptic of t0 (implemented in Swiss Ephemeris as an option)
===================================================================================

The opposite solution, which would also be consistent, would be to project the
planetary positions of end date Je onto the ecliptic of the start date of the
ayanamsha JS using a correct coordinate transformation. E.g., for the
Fagan/Bradley ayanamsha, this would be the mean ecliptic of 1950; for the
Lahiri ayanamsha, the mean ecliptic of 21 March 1956.

If we follow this method, the wobbling effect described above under (1)
(traditional ayanamsha method) will not occur, and an object that has no proper
motion will keep its position forever.

The differences from the traditional method look quite similar to method 2
above, where the calculation is consistently done relative to the ecliptic of
date:

=========== =========
Year        Diff in "
=========== =========
-3000       -9.522
-2500       -9.089
-2000       -7.970
-1500       -6.402
-1000       -4.763
-500        -3.207
0           -1.897
500         -0.939
1000        -0.337
1500        -0.058
1600        -0.033
1700        -0.016
1800        -0.005
1900        -0.000
1920        -0.000
1940        0.000
1960        0.000
1980        0.000
2000        -0.000
2020        -0.001
2040        -0.001
2060        -0.002
2080        -0.003
2100        -0.004
2200        -0.008
2300        -0.014
2400        -0.019
2500        -0.024
3000        0.030
3500        0.318
4000        0.967
=========== =========

A comparison of the two consistent methods 2 and 3 provides the following
differences, which are considerably smaller:

=========== =========
Year        Diff in "
=========== =========
-3000       -0.111
-2500       0.617
-2000       0.921
-1500       0.874
-1000       0.711
-500        0.472
0           0.241
500         0.084
1000        0.003
1500        -0.009
1600        -0.006
1700        -0.004
1800        -0.002
1900        -0.000
1920        0.000
1940        0.000
1960        0.000
1980        0.000
2000        0.000
2020        -0.000
2040        -0.001
2060        -0.001
2080        -0.001
2100        -0.002
2200        -0.006
2300        -0.015
2400        -0.027
2500        -0.042
3000        -0.219
3500        -0.621
4000        -1.324
=========== =========

A philosophical side note: This method is geometrically more correct than the
traditional one, but still has a problem. For, if we want to refer everything
to the ecliptic of some initial date t0, we will have to choose that date very
carefully. Its ecliptic ought to be of "cosmic" importance. The ecliptic of
1950 or the one of 1900 or 1956 (Lahiri) are obviously meaningless and not
suitable as a reference plane. So, how about some historical date on which the
tropical and the sidereal zero point coincided? Although this may be considered
as a kind of cosmic anniversary (the ancient Indians and Sassanians did so),
the ecliptic plane of that time does not have an "eternal" value. E.g., it is
different from the ecliptic plane of the previous annivesary around the year
26000 BCE, and it is also different from the ecliptic plane of the next cosmic
anniversary around the year 26000 CE.

Thus, it may be wiser to use method 2, i.e. a consistent ayanamsha calculation
on the ecliptic of date.

Method 3 can also be used for computations of the following kind:

c) Astronomers may want to calculate positions referred to a standard equinox
like J2000, B1950, or B1900, or to any other equinox.

d) Astrologers may be interested in the calculation of precession-corrected
transits. See explanations in the next chapter.

e) The algorithm can be applied to any user-defined sidereal mode, if the
ecliptic of its reference date is considered to be astrologically significant.

f) The algorithm makes the problems of the traditional method visible. It shows
the dimensions of the inherent inaccuracy of the traditional method. (Calculate
some star position using the traditional method and compare it to the same
star's position if calculated using this method.)

For the planets and for centuries close to t0, the difference from the
traditional procedure will be only a few arc seconds in longitude. Note that
the Sun will have an ecliptical latitude of several arc minutes after a few
centuries.

For the lunar nodes, the procedure is as follows:

Because the lunar nodes have to do with eclipses, they are actually points on
the ecliptic of date, i.e. on the tropical zodiac. Therefore, we first compute
the nodes as points on the ecliptic of date and then project them onto the
sidereal zodiac. This procedure is very close to the traditional method of
computing sidereal positions (a matter of arc seconds). However, the nodes will
have a latitude of a couple of arc minutes.

For the axes and houses, we compute the points where the horizon or the house
lines intersect with the sidereal plane of the zodiac, not with the ecliptic of
date. Here, there are greater deviations from the traditional procedure. If t
is 2000 years from t0, the difference between the ascendant positions might
well be 1/2 degree.

4. Fixed-star-bound ecliptic (implemented in Swiss Ephemeris for some selected stars)
=====================================================================================

One can use a stellar object as an anchor for the sidereal zodiac and make sure
that a particular stellar object is always at a certain position on the
ecliptic of date. E.g. one might want to have Spica always at 0 Libra or the
Galactic Center always at 0 Sagittarius. There is nothing against this method
from a geometrical point of view. But it must be noted that this system is not
really fixed either, because it is still based on the true ecliptic of date,
which is actually moving. Moreover, the fixed stars that are used as anchor
stars have a small proper motion, as well. Thus, if Spica is assumed as a fixed
point, then its proper motion, its aberration, its gravitational deflection,
and its parallax will necessarily affect the position and motion of all other
stars (in addition to their own proper motion, aberration, etc.). Note, the
Galactic Centre (Sgr A*) is not really fixed either, but has a small apparent
motion that reflects the motion of the Sun around it.

This solution has been implemented for the following stars and fixed positions:

- Spica/Citra at 180° ("True Chitra Paksha Ayanamsha")
- Revati (zeta Piscium) at 359°50'
- Pushya (Asellus Australis) at 106° (PVR Narasimha Rao)
- Mula (lambda Scorpionis) at 240° (Chandra Hari)
- Galactic centre at 0° Sagittarius
- Galactic centre at 0° Capricorn (David Cochrane)
- Galactic centre at golden section between 0° Sco and 0° Aqu (R. Gil Brand)
- Polar longitude of galactic centre in the middle of nakshatra Mula (E. Wilhelm)

With Swiss Ephemeris versions before 2.05, the apparent position of the star
relative to the mean ecliptic plane of date was used as the reference point of
the zodiac. E.g. with the True Chitra ayanamsha, the star Chitra/Spica had the
apparent position 180° exactly. However, the true position was slightly
different. Since version 2.05, the star is always exactly at 180°, not only its
apparent, but also its true position.

5. Galactic-equator-based ayanamshas (implemented in Swiss Ephemeris)
=====================================================================

Some ayanamshas are based on the galactic node, i.e. the intersection of the
galactic equator with the mean ecliptic of date. These ayanamshas include:

- Galactic equator (IAU 1958)
- Galactic equator true/modern
- Galactic equator in middle of Mula

(Note, the Mardyks ayanamsha, although derived from the galactic equator, does
not work like this. It is calculated using the method described above under 1).)

The galactic node is calculated from the true position of the galactic pole,
not the apparent one. As a result, if the position of the galactic pole is
calculated using the ayanamsha that has the galactic node at 0° Sagittarius,
then the true position of the pole is exactly at sidereal 150°, but its
apparent position is slightly different from that.

Here again, it must be stated that the ecliptic plane used is the true ecliptic
of date, which is moving, with the only difference that the initial point is
defined by the intersection of the ecliptic with the galactic equator.

6. The long-term mean Earth-Sun plane (not implemented in Swiss Ephemeris)
==========================================================================

To avoid the problem of choice of a reference ecliptic, one could use a kind of
"average ecliptic". The mechanism of the planetary precession mentioned above
works in a similar way as the mechanism of the luni-solar precession. The
motion of the Earth orbit can be compared to a spinning top, with the Earth
mass equally distributed around the whole orbit. The other planets, especially
Venus and Jupiter, cause it to move around an average position. But
unfortunately, this "long-term mean Earth-Sun plane" is not really stable
either, and therefore not suitable as a fixed reference frame.

The period of this cycle is about 75000 years. The angle between the long-term
mean plane and the ecliptic of date is currently about 1°33', but it varies
considerably. (This cycle must not be confused with the period between two
maxima of the ecliptic obliquity, which is about 40000 years and often
mentioned in the context of planetary precession. This is the time it takes the
vernal point to return to the node of the ecliptic (its rotation point), and
therefore the oscillation period of the ecliptic obliquity.)

7. The solar system rotation plane (implemented in Swiss Ephemeris as an option)
================================================================================

The solar system as a whole has a rotation axis, too, and its equator is quite
close to the ecliptic, with an inclination of 1°34'44" against the ecliptic of
the year 2000. This plane is extremely stable and perhaps the only convincing
candidate for a fixed zodiac plane.

This method avoids the problem of method 3). No particular ecliptic has to be
chosen as a reference plane. The only remaining problem is the choice of the
zero point.

It does not make much sense to use this algorithm for predefined sidereal
modes. One can use it for user-defined ayanamshas.

..
