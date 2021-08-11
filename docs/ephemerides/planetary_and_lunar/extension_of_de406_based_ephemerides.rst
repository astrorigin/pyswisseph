========================================================
The extension of DE406-based ephemerides to 10.800 years
========================================================

This Chapter is only relevant to those who use pre-2014, DE406-based ephemeris
files of the Swiss Ephemeris.

The JPL ephemeris DE406 covers the time range from 3000 BCE to 3000 CE. While
this is an excellent range covering all precisely known historical events,
there are some types of ancient astrology and archeoastronomical research which
would require a longer time range.

In December 1998 we have made an effort to extend the time range using our own
numerical integration. The exact physical model used by Standish et. al. for
the numerical integration of the DE406 ephemeris is not fully documented (at
least we do not understand some details), so that we cannot use the same
integration program as had been used at JPL for the creation of the original
ephemeris.

The previous JPL ephemeris DE200, however, has been reproduced by Steve Moshier
over a very long-time range with his numerical integrator, which was available
to us. We used this software with start vectors taken at the end points of the
DE406 time range. To test our numerical integrator, we ran it upwards from 3000
BCE to 600 BCE for a period of 2400 years and compared its results with the
DE406 ephemeris itself. The agreement is excellent for all planets except the
Moon (see table below). The lunar orbit creates a problem because the physical
model for the Moon's libration and the effect of the tides on lunar motion is
quite different in the DE406 from the model in the DE200. We varied the tidal
coupling parameter (love number) and the longitudinal libration phase at the
start epoch until we found the best agreement over a 2400-year test range
between our integration and the JPL data. We could reproduce the Moon's motion
over a 2400-time range with a maximum error of 12 arcseconds. For most of this
time range the agreement is better than 5 arcsec.

With these modified parameters we ran the integration backward in time from
3000 BCE to 5400 BCE. It is reasonable to assume that the integration errors in
the backward integration are not significantly different from the integration
errors in the upward integration.

=========== =================== ===================
Planet      max. error (arcsec) avg. error (arcsec)
=========== =================== ===================
Mercury     1.67                0.61
Venus       0.14                0.03
Earth       1.00                0.42
Mars        0.21                0.06
Jupiter     0.85                0.38
Saturn      0.59                0.24
Uranus      0.20                0.09
Neptune     0.12                0.06
Pluto       0.12                0.04
Moon        12.2                2.53
Sun bary.   6.3                 0.39
=========== =================== ===================

The same procedure was applied at the upper end of the DE406 range, to cover an
extension period from 3000 CE to 5400 CE. The maximum integration errors as
determined in the test run 3000 CE down to 600 CE are given in the table below.

=========== =================== ===================
Planet      max. error (arcsec) avg. error (arcsec)
=========== =================== ===================
Mercury     2.01                0.69
Venus       0.06                0.02
Earth       0.33                0.14
Mars        1.69                0.82
Jupiter     0.09                0.05
Saturn      0.05                0.02
Uranus      0.16                0.07
Neptune     0.06                0.03
Pluto       0.11                0.04
Moon        8.89                3.43
Sun bary.   0.61                0.05
=========== =================== ===================

Deviations in heliocentric longitude from new JPL ephemeris DE431 (2013),
time range 5400 BCE to 3000 BCE:

======================= ======
Moon (geocentric)       < 40"
Earth, Mercury, Venus   < 1.4"
Mars                    < 4"
Jupiter                 < 9"
Saturn                  < 1.2"
Uranus                  < 36"
Neptune                 < 76"
Pluto                   < 120"
======================= ======

..
