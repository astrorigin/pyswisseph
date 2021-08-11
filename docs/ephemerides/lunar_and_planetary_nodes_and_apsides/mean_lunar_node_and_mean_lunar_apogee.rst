=======================================================================
Mean Lunar Node and Mean Lunar Apogee (Lilith, Black Moon in astrology)
=======================================================================

JPL ephemerides do not include a mean lunar node or mean lunar apsis
(perigee/apogee). We therefore have to derive them from different sources.

Our mean node and mean apogee are computed from Moshier's lunar routine, which
is an adjustment of the ELP2000-85 lunar theory to the JPL ephemeris on the
interval from 3000 BCE to 3000 CE. Its deviation from the mean node of
ELP2000-85 is 0 for J2000 and remains below 20 arc seconds for the whole
period. With the apogee, the deviation reaches 3 arc minutes at 3000 BCE.

In order to cover the whole time range of DE431, we had to add some corrections
to Moshier's mean node and apsis, which we derived from the true node and apsis
that result from the DE431 lunar ephemeris. Estimated precision is 1 arcsec,
relative to DE431.

Notes for astrologers
=====================

Astrological Lilith or the Dark Moon is either the apogee ("aphelion") of the
lunar orbital ellipse or, according to some, its empty focal point. As seen
from the geocenter, this makes no difference. Both of them are located in
exactly the same direction. But the definition makes a difference for
topocentric ephemerides.

The opposite point, the lunar perigee or orbital point closest to the Earth, is
also known as Priapus. However, if Lilith is understood as the second focal
point, an opposite point makes no sense, of course.

Originally, the term "Dark Moon" stood for a hypothetical second body that was
believed to move around the Earth. There are still ephemerides circulating for
such a body, but modern celestial mechanics clearly exclude the possibility of
such an object. Later the term "Dark Moon" was used for the lunar apogee.

The Swiss Ephemeris apogee differs from the ephemeris given by Joëlle de
Gravelaine in her book "Lilith, der schwarze Mond" (Astrodata 1990). The
difference reaches several arc minutes. The mean apogee (or perigee) moves
along the mean lunar orbit which has an inclination of 5 degrees. Therefore it
has to be projected on the ecliptic. With de Gravelaine's ephemeris, this was
not taken into account. As a result of this projection, we also provide an
ecliptic latitude of the apogee, which will be of importance if declinations
are used.

There may be still another problem. The 'first' focal point does not coincide
with the geocenter but with the barycenter of the Earth-Moon-system. The
difference is about 4700 km. If one took this into account, it would result in
a monthly oscillation of the Black Moon. If one defines the Black Moon as the
apogee, this oscillation would be about +/- 40 arc minutes. If one defines it
as the second focus, the effect is a lot greater: +/- 6 degrees. However, we
have neglected this effect.

[added by Alois 7-feb-2005, arising out of a discussion with Juan Revilla] The
concept of 'mean lunar orbit' means that short term. e.g. monthly, fluctuations
must not be taken into account. In the temporal average, the EMB coincides with
the geocenter. Therefore, when mean elements are computed, it is correct only
to consider the geocenter, not the Earth-Moon Barycenter.

Computing topocentric positions of mean elements is also meaningless and should
not be done.

..
