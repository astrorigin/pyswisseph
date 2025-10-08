==============================================
Heliacal Events of the Moon, Planets and Stars
==============================================

Introduction
============

From Swiss Ephemeris version 1.76 on, heliacal events have been included. The
heliacal rising and setting of planets and stars was very important for ancient
Babylonian and Greek astronomy and astrology. Also, first and last visibility
of the Moon can be calculated, which are important for many calendars, e.g. the
Islamic, Babylonian and ancient Jewish calendars.

The heliacal events that can be determined are:

- Inferior planets

  - Heliacal rising (morning first)
  - Heliacal setting (evening last)
  - Evening first
  - Morning last

- Superior planets and stars

  - Heliacal rising
  - Heliacal setting

- Moon

  - Evening first
  - Morning last

The acronychal risings and settings (also called cosmical settings) of superior
planets are a different matter. They will be added in a future version of the
Swiss Ephemeris.

The principles behind the calculation are based on the visibility criterion of
Schaefer [1993, 2000], which includes dependencies on aspects of:

- Position of celestial objects

like the position and magnitude of the Sun, Moon and the studied celestial
object,

- Location and optical properties observer

like his/her location (longitude, latitude, height), age, acuity and possible
magnification of optical instruments (like binoculars)

- Meteorological circumstances

mainly expressed in the astronomical extinction coefficient, which is
determined by temperature, air pressure, humidity, visibility range (air quality).

- Contrast between studied object and sky background

The observer's eye can on detect a certain amount of contract and this contract
threshold is the main body of the calculations

In the following sections above aspects will be discussed briefly and an idea
will be given what functions are available to calculate the heliacal events.
Lastly the future developments will be discussed.

Aspect determining visibility
=============================

The theory behind this visibility criterion is explained by Schaefer [1993,
2000] and the implemented by Reijs [2003] and Koch [2009]. The general ideas
behind this theory are explained in the following subsections.

1. Position of celestial objects

To determine the visibility of a celestial object it is important to know where
the studied celestial object is and what other light sources are in the sky.
Thus beside determining the position of the studied object and its magnitude,
it also involves calculating the position of the Sun (the main source of light)
and the Moon. This is common functions performed by Swiss Ephemeris.

2. Geographic location

The location of the observer determines the topocentric coordinates (incl.
influence of refraction) of the celestial object and his/her height (and
altitude of studied object) will have influence on the amount of airmass that
is in the path of celestial object's light.

3. Optical properties of observer

The observer's eyes will determine the resolution and the contrast differences
he/she can perceive (depending on age and acuity), furthermore the observer
might use optical instruments (like binocular or telescope).

4. Meteorological circumstances

The meteorological circumstances are very important for determining the
visibility of the celestial object. These circumstances influence the
transparency of the airmass (due to Rayleigh & aerosol scattering and ozone &
water absorption) between the celestial object and the observer's eye. This
result in the astronomical extinction coefficient (AEC: ktot). As this is a
complex environment, it is sometimes 'easier' to use a certain AEC, instead of
calculating it from the meteorological circumstances.

The parameters are stored in the datm (Pressure [mbar], Temperature [C],
Relative humidity [%], AEC [-]) array.

5. Contrast between object and sky background

All the above aspects influence the perceived brightness of the studied
celestial object and its background sky. The contrast threshold between the
studied object and the background will determine if the observer can detect the
studied object.

Functions to determine the heliacal events
==========================================

Two functions are seen as the spill of calculating the heliacal events:

1. Determining the contrast threshold (``swe.vis_limit_mag``)

Based on all the aspects mentioned earlier, the contrast threshold is determine
which decides if the studied object is visible by the observer or not.

2. Iterations to determine when the studied object is really visible
   (``swe.heliacal_ut``)

In general this procedure works in such a way that it finds (through
iterations) the day that conjunction/opposition between Sun and studied object
happens and then it determines, close to Sun's rise or set (depending on the
heliacal event), when the studied object is visible (by using the
``swe.vis_limit_mag`` function).

3. Geographic limitations of ``swe.heliacal_ut`` and strange behavior of planets
   in high geographic latitudes

This function is limited to geographic latitudes between 60S and 60N. Beyond
that the heliacal phenomena of the planets become erratic. We found cases of
strange planetary behavior even at 55N.

An example:

At 0E, 55N, with an extinction coefficient 0.2, Mars had a heliacal rising on
25 Nov. 1957. But during the following weeks and months Mars did not constantly
increase its height above the horizon before Sunrise. In contrary, it
disappeared again, i.e. it did a "morning last" on 18 Feb. 1958. Three months
later, on 14 May 1958, it did a second morning first (heliacal rising). The
heliacal setting or evening last took place on 14 June 1959.

Currently, this special case is not handled by ``swe.heliacal_ut()``. The function
cannot detect "morning lasts" of Mars and following "second heliacal risings".
The function only provides the heliacal rising of 25 Nov. 1957 and the next
ordinary heliacal rising in its ordinary synodic cycle which took place on 11
June 1960.

However, we may find a solution for such problems in future releases of the
Swiss Ephemeris and even extend the geographic range of ``swe.heliacal_ut()`` to
beyond +/- 60.

4. Visibility of Venus and the Moon during day

For the Moon, ``swe.heliacal_ut()`` calculates the evening first and the morning
last. For each event, the function returns the optimum visibility and a time of
visibility start and visibility end. Note, that on the day of its morning last
or evening first, the Moon is often visible for almost the whole day. It even
happens that the crescent first becomes visible in the morning after its
rising, then disappears, and again reappears during culmination, because the
observation conditions are better as the Moon stands high above the horizon.
The function ``swe.heliacal_ut()`` does not handle this in detail. Even if the Moon
is visible after Sunrise, the function assumes that the end time of observation
is at Sunrise. The evening fist is handled in the same way.

With Venus, we have a similar situation. Venus is often accessible to naked eye
observation during day, and sometimes even during inferior conjunction, but
usually only at a high altitude above the horizon. This means that it may be
visible in the morning at its heliacal rising, then disappear and reappear
during culmination. (Whoever does not believe me, please read the article by
H.B. Curtis listed under "References".) The function ``swe.heliacal_ut()`` does not
handle this case. If binoculars or a telescope is used, Venus may be even
observable during most of the day on which it first appears in the east.

Future developments
===================

The section of the Swiss Ephemeris software is still under development. The
acronychal events of superior planets and stars will be added. And comparing
other visibility criterions will be included; like Schoch's criterion [1928],
Hoffman's overview [2005] and Caldwall & Laney criterion [2005].

References
==========

 Caldwell, J.A.R., Laney, C.D., First visibility of the lunar crescent,
 http://www.saao.ac.za/public-info/Sun-Moon-stars/Moon-index/lunar-crescent-visibility/first-visibility-of-lunar-crescent/,
 2005, viewed March, 30th, 2009

 H.B. Curtis, Venus Visible at inferior conjunction, in : Popular Astronomy
 vol. 18 (1936), p. 44; online at
 http://articles.adsabs.harvard.edu/cgi-bin/nph-iarticle_query?1936PA.....44...18C&data_type=PDF_HIGH&whole_paper=YES&type=PRINTER&filetype=.pdf

 Hoffman, R.E., Rational design of lunar-visibility criteria, The observatory,
 Vol. 125, June 2005, No. 1186, pp 156-168.

 Reijs, V.M.M., Extinction angle and heliacal events,
 http://www.iol.ie/~geniet/eng/extinction.htm, 2003, viewed March, 30th, 2009

 Schaefer, B., Astronomy and the limit of vision, Vistas in astronomy, 36:311,
 1993

 Schaefer, B., New methods and techniques for historical astronomy and
 archeoastronomy, Archeoastronomy, Vol. XV, 2000, page 121-136

 Schoch, K., Astronomical and calendrical tables in Langdon. S., Fotheringham,
 K.J., The Venus tables of Amninzaduga: A solution of Babylonian chronology by
 means of Venus observations of the first dynasty, Oxford, 1928.

..
