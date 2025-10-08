================================================================================
The Interpolated or Natural Apogee and Perigee (astrological Lilith and Priapus)
================================================================================

As has been said above, the osculating lunar apogee (so-called 'true Lilith')
is a mathematical construct which assumes that the motion of the Moon is a
two-body problem. This solution is obviously too simplistic. Although Kepler
ellipses are a good means to describe planetary orbits, they fail with the
orbit of the Moon, which is strongly perturbed by the gravitational pull of the
Sun. This solar perturbation results in gigantic monthly oscillations in the
ephemeris of the osculating apsides (the amplitude is 30 degrees). These
oscillations have to be considered an artifact of the insufficient model, they
do not really show a motion of the apsides.

A more sensible solution seems to be an interpolation between the real
passages of the Moon through its apogees and perigees. It turns out that the
motions of the lunar perigee and apogee form curves of different quality and
the two points are usually not in opposition to each other. They are more or
less opposite points only at times when the Sun is in conjunction with one of
them or at an angle of 90° from them. The amplitude of their oscillation about
the mean position is 5 degrees for the apogee and 25 degrees for the perigee.

This solution has been called the "interpolated" or "realistic" apogee and
perigee by Dieter Koch in his publications. Juan Revilla prefers to call them
the "natural" apogee and perigee. Today, Dieter Koch would prefer the
designation "natural". The designation "interpolated" is a bit misleading,
because it associates something that astrologers used to do every day in old
days, when they still used to work with printed ephemerides and house tables.

*Note on implementation (from Swiss Ephemeris Version 1.70 on)*

Conventional interpolation algorithms do not work well in the case of the lunar
apsides. The supporting points are too far away from each other in order to
provide a good interpolation, the error estimation is greater than 1 degree for
the perigee. Therefore, Dieter chose a different solution. He derived an
"interpolation method" from the analytical lunar theory which we have in the
form of Moshier's lunar ephemeris. This "interpolation method" has not only the
advantage that it probably makes more sense, but also that the curve and its
derivation are both continuous.

Literature (in German):

- Dieter Koch, "Was ist Lilith und welche Ephemeride ist richtig", Meridian 1/95
- Dieter Koch and Bernhard Rindgen, "Lilith und Priapus", Frankfurt/Main, 2000.
- (http://www.vdhb.de/Lilith_und_Priapus/lilith_und_priapus.html)
- Juan Revilla, "The Astronomical Variants of the Lunar Apogee - Black Moon".
- http://www.expreso.co.cr/centaurs/blackMoon/barycentric.html

..
