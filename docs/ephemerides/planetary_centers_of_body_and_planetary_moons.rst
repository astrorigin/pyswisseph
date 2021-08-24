===================================================
Planetary Centers of Body (COB) and Planetary Moons
===================================================

Although nobody ever finds it worth mentioning and hardly anybody is aware of
it, all hitherto ephemerides and astrology softwares provide only the
barycenter of the Jupiter system, i.e. the center of mass of Jupiter together
with all his moons, not the center of Jupiter's body or the real planet. And
the same holds for all the other planets that have moons, except the earth. We
call the center of the real planets the centers of body (COB).

The difference between the barycenters and the COBs are small. The maximum
geocentric angular distances are as follows:

=========== ============================
Mars        (0.2 m, irrelevant to us)
Jupiter     0.075  arcsec (jd 2468233.5)
Saturn      0.053  arcsec (jd 2463601.5)
Uranus      0.0032 arcsec (jd 2446650.5)
Neptune     0.0036 arcsec (jd 2449131.5)
Pluto       0.088  arcsec (jd 2437372.5)
=========== ============================

(from one-day-step calculations over 150 years)

Swiss Ephemeris versions 2.10 and higher can provide positions of the centers
of body of the planets as well as some planetary moons, thanks to a joint
effort by Walter Pullen and Dieter Koch.

The ephemerides were downloaded from JPL Horizons and then compressed using the
Astrodienst software ``chopt``, the same software that is also used to generate
asteroid ephemeris files.

Currently, not all planetary moons are available to Swiss Ephemeris users.

Software developers who want to implement COB have to know that the performance
of this calculation is not as good as with the barycenters. Moreover, the time
range is currently limited to the years 1900 to 2047.

..
