==========================
Astrological House Systems
==========================

The following house methods have been implemented so far:

Placidus
========

This system is named after the Italian monk Placidus de Titis (1590-1668). The
cusps are defined by divisions of semidiurnal and seminocturnal arcs. The 11th
cusp is the point on the ecliptic that has completed 2/3 of its semidiurnal
arc, the 12th cusp the point that has completed 1/3 of it. The 2nd cusp has
completed 2/3 of its seminocturnal arc, and the 3rd cusp 1/3.

Koch/GOH
========

This system is called after the German astrologer Walter Koch (1895-1970).
Actually it was invented by Fiedrich Zanzinger and Heinz Specht, but it was
made known by Walter Koch. In German-speaking countries, it is also called the
"Geburtsorthäusersystem" (GOHS), i.e. the "Birth place house system". Walter
Koch thought that this system was more related to the birth place than other
systems, because all house cusps are computed with the "polar height of the
birth place", which has the same value as the geographic latitude.

This argumentation shows actually a poor understanding of celestial geometry.
With the Koch system, the house cusps are actually defined by horizon lines at
different times. To calculate the cusps 11 and 12, one can take the time it
took the MC degree to move from the horizon to the culmination, divide this
time into three and see what ecliptic degree was on the horizon at the thirds.
There is no reason why this procedure should be more related to the birth place
than other house methods.

Regiomontanus
=============

Named after the Johannes Müller (called "Regiomontanus", because he stemmed
from Königsberg) (1436-1476).

The equator is divided into 12 equal parts and great circles are drawn through
these divisions and the north and south points on the horizon. The intersection
points of these circles with the ecliptic are the house cusps.

Campanus
========

Named after Giovanni di Campani (1233-1296).

The vertical great circle from east to west is divided into 12 equal parts and
great circles are drawn through these divisions and the north and south points
on the horizon. The intersection points of these circles with the ecliptic are
the house cusps.

Equal Systems
=============

1. Equal houses from Ascendant
------------------------------

The zodiac is divided into 12 houses of 30 degrees each starting from the
Ascendant.

2. Equal houses from Midheaven
------------------------------

The zodiac is divided into 12 houses of 30 degrees each starting from MC + 90
degrees.

3. Vehlow-equal system
----------------------

Equal houses with the Ascendant positioned in the middle of the first house.

4. Whole Sign houses
--------------------

The first house starts at the beginning of the zodiac sign in which the
ascendant is. Each house covers a complete sign. This method was used in
Hellenistic astrology and is still used in Hindu astrology.

5. Whole Sign houses starting at 0° Aries
-----------------------------------------

The first house starts at the beginning of Aries.

Porphyry Houses and Related House Systems
=========================================

1. Porphyry Houses
------------------

Each quadrants is trisected in three equal parts on the ecliptic.

2. Sripati Houses
-----------------

This is a traditional Indian house system. In a first step, Porphyry houses are
calculated. The cusps of each new house will be the midpoint between the last
and the current. So house 1 will be equal to:

H1' = (H1 - H12) / 2 + H12

H2' = (H2 - H1) / 2 + H1

And so on.

3. Pullen SD (Sinusoidal Delta, also known as "Neo-Porphyry")
-------------------------------------------------------------

This house system was invented in 1994 by Walter Pullen, the author of the
astrology software Astrolog. Like the Porphyry house system, this house system
is based on the idea that the division of the houses must be relative to the
ecliptic sections of the quadrants only, not relative to the equator or diurnal
arcs. For this reason, Pullen originally called it "Neo-Porphyry". However, the
sizes of the houses of a quadrant are not equal. Pullen describes it as follows:

"Like Porphyry except instead of simply trisecting quadrants, fit the house
widths to a sine wave such that the 2nd/5th/8th/11th houses are expanded or
compressed more based on the relative size of their quadrants."

In practice, an ideal house size of 30° each is assumed, then half of the
deviation of the quadrant from 90° is added to the middle house of the
quadrant. The remaining half is bisected again into quarters, and a quarter is
added to each of the remaining houses. Pullen himself puts it as follows:

"Sinusoidal Delta" (formerly "Neo-Porphyry") houses::

 Asc        12th        11th        MC          9th         8th         7th
 |          |           |           |           |           |           |
 +----------+-----------+-----------+-----------+-----------+-----------+
 angle      angle       angle       angle       angle       angle
 x+n        x           x+n         x+3n        x+4n        x+3n

In January 2016, in a discussion in the Swiss Ephemeris Yahoo Group, Alois
Treindl criticized that Pullen's code only worked as long as the quadrants were
greater than 30°, whereas negative house sizes resulted for the middle house of
quadrants smaller than 30°. It was agreed upon that in such cases the size of
the house had to be set to 0.

 https://groups.yahoo.com/neo/groups/swisseph/conversations/topics/5579

 https://groups.yahoo.com/neo/groups/swisseph/conversations/topics/5606

4. Pullen SR (Sinusoidal Ratio)
-------------------------------

On 24 Jan. 2016, during the above-mentioned discussion in the Swiss Ephemeris
Yahoo Group, Walter Pullen proposed a better solution of a sinusoidal division
of the quadrants, which does not suffer from the same problem. He wrote:

"It's possible to do other than simply add sine wave offsets to houses (the
"Sinusoidal Delta" house system above). Instead, let's proportion or ratio the
entire house sizes themselves to each other based on the sine wave constants,
or multiply instead of add. That results in using a "sinusoidal ratio" instead
of a "sinusoidal delta", so this alternate method could be called "Sinusoidal
Ratio houses". As before, let "x" be the smallest house in the compressed
quadrant. There's a ratio "r" multiplied by it to get the slightly larger 10th
and 12th houses. The value "r" starts out at 1.0 for 90 degree quadrants, and
gradually increases as quadrant sizes differ. Houses in the large quadrant have
"r" multiplied to "x" 3 times (or 4 times for the largest quadrant). That
results in the (0r, 1r, 3r, 4r) distribution from the sine wave above. This is
summarized in the chart below:"

"Sinusoidal Ratio" houses::

 Asc        12th        11th        MC          9th         8th         7th
 |          |           |           |           |           |           |
 +----------+-----------+-----------+-----------+-----------+-----------+
 angle      angle       angle       angle       angle       angle
 rx         x           rx          r^3x        r^4x        r^3x

"The unique values for "r" and "x" can be computed based on the quadrant size
"q", given the equations rx + x + rx = q, r\ :sup:`3`\ x + r\ :sup:`4`\ x +
r\ :sup:`3`\ x = 180 - q."

 https://groups.yahoo.com/neo/groups/swisseph/conversations/topics/5579

Axial rotation systems
======================

1. Meridian system
------------------

The equator is partitioned into 12 equal parts starting from the ARMC. Then the
ecliptic points are computed that have these divisions as their right
ascension. Note: The ascendant is different from the 1st house cusp.

2. Carter's poli-equatorial houses
----------------------------------

The equator is partitioned into 12 equal parts starting from the right
ascension of the ascendant. Then the ecliptic points are computed that have
these divisions as their right ascension. Note: The MC is different from the
10th house cusp.

The prefix "poli-" might stand for "polar". (Speculation by DK.)

Carter's own words:

"...the houses are demarcated by circles passing through the celestial poles and dividing the equator into twelve equal arcs, the cusp of the 1st house passing through the ascendant. This system, therefore, agrees with the natural rotation of the heavens and also produces, as the Ptolemaic (equal) does not, distinctive cusps for each house ..."

 Charles Carter (1947, 2nd ed. 1978) Essays on the Foundations of Astrology.
 Theosophical Publishing House, London. p. 158-159.

 http://www.exeterastrologygroup.org.uk/2014/12/charles-carters-forgotten-house-system.html

The Morinus system
==================

The equator is divided into 12 equal parts starting from the ARMC. The
resulting 12 points on the equator are transformed into ecliptic coordinates.
Note: The Ascendant is different from the 1st cusp, and the MC is different
from the 10th cusp.

Horizontal system
=================

The house cusps are defined by division of the horizon into 12 directions. The
first house cusp is not identical with the Ascendant but is located precisely
in the east.

The Polich-Page ("topocentric") system
======================================

This system was introduced in 1961 by Wendel Polich and A.P. Nelson Page. Its
construction is rather abstract: The tangens of the polar height of the 11th
house is the tangens of the geo. latitude divided by 3. (2/3 of it are taken
for the 12th house cusp.) The philosophical reasons for this algorithm are
obscure. Nor is this house system more "topocentric" (i.e. birth-place-related)
than any other house system. (c.f. the misunderstanding with the "birth place
system".) The "topocentric" house cusps are close to Placidus house cusps
except for high geographical latitudes. It also works for latitudes beyond the
polar circles, wherefore some consider it to be an improvement of the Placidus
system. However, the striking philosophical idea behind Placidus, i.e. the
division of diurnal and nocturnal arcs of points of the zodiac, is completely
abandoned.

Alcabitus system
================

A method of house division which first appears with the Hellenistic astrologer
Rhetorius (500 A.D.) but is named after Alcabitius, an Arabic astrologer, who
lived in the 10th century A.D. This is the system used in a few remaining
examples of ancient Greek horoscopes.

The MC and ASC are the 10th- and 1st- house cusps. The remaining cusps are
determined by the trisection of the semidiurnal and seminocturnal arcs of the
ascendant, measured on the celestial equator. The houses are formed by great
circles that pass through these trisection points and the celestial north and
south poles.

Gauquelin sectors
=================

This is the "house" system used by the Gauquelin and their epigones and critics
in statistical investigations in Astrology. Basically, it is identical with the
Placidus house system, i.e. diurnal and nocturnal arcs of ecliptic points or
planets are subdivided. There are a couple of differences, though.

- Up to 36 "sectors" (or house cusps) are used instead of 12 houses.
- The sectors are counted in clockwise direction.
- There are so-called plus (+) and minus (–) zones. The plus zones are the
  sectors that turned out to be significant in statistical investigations, e.g.
  many top sportsmen turned out to have their Mars in a plus zone. The plus
  sectors are the sectors 36 – 3, 9 – 12, 19 – 21, 28 – 30.
- More sophisticated algorithms are used to calculate the exact house position
  of a planet (see chapters 6.4 and 6.5 on house positions and Gauquelin sector
  positions of planets). TODO

Krusinski/Pisa/Goelzer system
=============================

This house system was first published in 1994/1995 by three different authors
independently of each other:

- by Bogdan Krusinski (Poland).
- by Milan Pisa (Czech Republic) under the name "Amphora house system".
- by Georg Goelzer (Switzerland) under the name "Ich-Kreis-Häusersystem"
  ("I-Circle house system").

Krusinski defines the house system as "... based on the great circle passing
through ascendant and zenith. This circle is divided into 12 equal parts (1st
cusp is ascendant, 10th cusp is zenith), then the resulting points are
projected onto the ecliptic through meridian circles. The house cusps in space
are half-circles perpendicular to the equator and running from the north to the
south celestial pole through the resulting cusp points on the house circle.
The points where they cross the ecliptic mark the ecliptic house cusps."
(Krusinski, e-mail to Dieter Koch)

It may seem hard to believe that three persons could have discovered the same
house system at almost the same time. But apparently this is what happened.
Some more details are given here, in order to refute wrong accusations from the
Czech side against Krusinski of having "stolen" the house system.

Out of the documents that Milan Pisa sent to Dieter Koch, the following are to
be mentioned: Private correspondence from 1994 and 1995 on the house system
between Pisa and German astrologers Böer and Schubert-Weller, two type-written
(apparently unpublished) treatises in German on the house system dated from
1994. A printed booklet of 16 pages in Czech from 1997 on the theory of the
house system ("Algoritmy noveho systemu astrologickych domu"). House tables
computed by Michael Cifka for the geographical latitude of Prague, copyrighted
from 1996. The house system was included in the Czech astrology software
Astrolog v. 3.2 (APAS) in 1998. Pisa's first publication on the house system
happened in spring 1997 in "Konstelace" No. 22, the periodical of the Czech
Astrological Society.

Bogdan Krusinski first published the house system at an astrological congress
in Poland, the ""XIV Szkola Astrologii Humanistycznej" held by Dr Leszek Weres,
which took place between 15.08.1995 and 28.08.1995 in Pogorzelica at coast of
the Baltic Sea." Since then Krusinski has distributed printed house tables for
the Polish geographical latitudes 49-55° and floppy disks with house tables for
latitudes 0-90°. In 1996, he offered his program code to Astrodienst for
implementation of this house system into Astrodienst's then astronomical
software Placalc. (At that time, however, Astrodienst was not interested in
it.) In May 1997, Krusinski put the data on the web at:

http://www.ci.uw.edu.pl/~bogdan/astrol.htm (now at http://www.astrologia.pl/main/domy.html).

In February 2006 he sent Swiss-Ephemeris-compatible program code in C for this
house system to Astrodienst. This code was included into Swiss Ephemeris
Version 1.70 and released on 8 March 2006.

Georg Goelzer describes the same house system in his book "Der Ich-Kosmos",
which appeared in July 1995 at Dornach, Switzerland (Goetheanum). The book has
a second volume with house tables according to the house method under
discussion. The house tables were created by Ulrich Leyde. Goelzer also uses a
house calculation programme which has the time stamp "9 April 1993" and
produces the same house cusps.

By March 2006, when the house system was included in the Swiss Ephemeris under
the name of "Krusinski houses", neither Krusinski nor Astrodienst knew about
the works of Pisa and Goelzer. Goelzer heard of his co-discoverers only in 2012
and then contacted Astrodienst.

Conclusion: It seems that the house system was first "discovered" and published
by Goelzer, but that Pisa and Krusinski also "discovered" it independently. We
do not consider this a great miracle because the number of possible house
constructions is quite limited.

APC house system
================

This house system was introduced by the Dutch astrologer L. Knegt and is used
by the Dutch Werkgemeenschap van Astrologen (WvA, also known as "Ram school").

The parallel of declination that goes through the ascendant is divided in six
equal parts both above and below the horizon. Position circles through the
north and the south point on the horizon are drawn through the division points.
The house cusps are where the position circles intersect the ecliptic.

Note, the house cusps 11, 12, 2, and 3 are not exactly opposite the cusps 5, 6,
8, and 9.

Sunshine house system
=====================

This house system was invented by Bob Makransky and published in 1988 in his
book Primary Directions. A Primer of Calculation (free download:
http://www.dearbrutus.com/buyprimarydirections.html).

The diurnal and nocturnal arcs of the Sun are trisected, and great circles are
drawn through these trisection points and the north and the south point on the
horizon. The intersection points of these great circles with the ecliptic are
the house cusps. Note that the cusps 11, 12, 2, and 3 are not in exact
opposition to the cusps 5, 6, 8, and 9.

For the polar region and during times where the Sun does not rise or set, the
diurnal and nocturnal arc are assumed to be either 180° or 0°. If the diurnal
arc is 0°, the house cusps 8 – 12 coincide with the meridian. If the nocturnal
arc is 0°, the cusps 2 – 6 coincide with the meridian. As with the closely
related Regiomontanus system, an MC below the horizon and IC above the horizon
are exchanged.

Vertex, Antivertex, East Point and Equatorial Ascendant etc
===========================================================

The Vertex is the point of the ecliptic that is located precisely in western
direction. The Antivertex is the opposition point and indicates the precise
east in the horoscope. It is identical to the 1st house cusp in the horizon
house system.

There is a lot of confusion about this, because there is also another point
which is called the "East Point" but is usually not located in the east. In
celestial geometry, the expression "East Point" means the point on the horizon
which is in precise eastern direction. The equator goes through this point as
well, at a right ascension which is equal to ARMC + 90 degrees. On the other
hand, what some astrologers call the "East Point" is the point on the ecliptic
whose right ascension is equal to ARMC + 90 (i.e. the right ascension of the
horizontal East Point). This point can deviate from eastern direction by 23.45
degrees, the amount of the ecliptic obliquity. For this reason, the term
"East Point" is not very well-chosen for this ecliptic point, and some
astrologers (M. Munkasey) prefer to call it the Equatorial Ascendant, because
it is identical to the Ascendant at a geographical latitude 0.

The Equatorial Ascendant is identical to the first house cusp of the axial
rotation system.

.. note::

    If a projection of the horizontal East Point on the ecliptic is wanted, it
    might seem more reasonable to use a projection rectangular to the ecliptic,
    not rectangular to the equator as is done by the users of the "East Point".
    The planets, as well, are not projected on the ecliptic in a right angle to
    the ecliptic.

The Swiss Ephemeris supports three more points connected with the house and
angle calculation. They are part of Michael Munkasey's system of the 8 Personal
Sensitive Points (PSP). The PSP include the Ascendant, the MC, the Vertex, the
Equatorial Ascendant, the Aries Point, the Lunar Node, and the "Co-Ascendant"
and the "Polar Ascendant".

The term "Co-Ascendant" seems to have been invented twice by two different
people, and it can mean two different things. The one "Co-Ascendant" was
invented by Walter Koch. To calculate it, one has to take the ARIC as an ARMC
and compute the corresponding Ascendant for the birth place. The "Co-Ascendant"
is then the opposition to this point.

The second "Co-Ascendant" stems from Michael Munkasey. It is the Ascendant
computed for the natal ARMC and a latitude which has the value 90° -
birth_latitude.

The "Polar Ascendant" finally was introduced by Michael Munkasey. It is the
opposition point of Walter Koch's version of the "Co-Ascendant". However, the
"Polar Ascendant" is not the same as an Ascendant computed for the birth time
and one of the geographic poles of the Earth. At the geographic poles, the
Ascendant is always 0 Aries or 0 Libra. This is not the case for Munkasey's
"Polar Ascendant".

House cusps beyond the polar circle
===================================

Beyond the polar circle, we proceed as follows:

1. We make sure that the ascendant is always in the eastern hemisphere.
2. Placidus and Koch house cusps sometimes can, sometimes cannot be computed
   beyond the polar circles. Even the MC doesn't exist always, if one defines
   it in the Placidus manner. Our function therefore automatically switches to
   Porphyry houses (each quadrant is divided into three equal parts) and
   returns a warning.

3. Beyond the polar circles, the MC is sometimes below the horizon. The
   geometrical definition of the Campanus and Regiomontanus systems requires in
   such cases that the MC and the IC are swapped. The whole house system is
   then oriented in clockwise direction.

There are similar problems with the Vertex and the horizon house system for
birth places in the tropics. The Vertex is defined as the point on the ecliptic
that is located in precise western direction. The ecliptic east point is the
opposition point and is called the Antivertex. Our program code makes sure that
the Vertex (and the cusps 11, 12, 1, 2, 3 of the horizon house system) is
always located in the western hemisphere. Note that for birthplaces on the
equator the Vertex is always 0 Aries or 0 Libra.

Of course, there are no problems in the calculation of the Equatorial Ascendant
for any place on Earth.

Implementation in other calculation modules
===========================================

1. PLACALC
----------

Placalc is the predecessor of Swiss Ephemeris; it is a calculation module
created by Astrodienst in 1988 and distributed as C source code. Beyond the
polar circles, Placalc's house calculation did switch to Porphyry houses for
all unequal house systems. Swiss Ephemeris still does so with the Placidus and
Koch method, which are not defined in such cases. However, the computation of
the MC and Ascendant was replaced by a different model in some cases: Swiss
Ephemeris gives priority to the Ascendant, choosing it always as the eastern
rising point of the ecliptic and accepting an MC below the horizon, whereas
Placalc gave priority to the MC. The MC was always chosen as the intersection
of the meridian with the ecliptic above the horizon. To keep the quadrants in
the correct order, i.e. have an Ascendant in the left side of the chart, the
Ascendant was switched by 180 degrees if necessary.

In the discussions between Alois Treindl and Dieter Koch during the development
of the Swiss Ephemeris it was recognized that this model is more unnatural than
the new model implemented in Swiss Ephemeris.

Placalc also made no difference between Placidus/Koch on one hand and
Regiomontanus/Campanus on the other as Swiss Ephemeris does. In Swiss
Ephemeris, the geometrical definition of Regiomontanus/Campanus is strictly
followed, even for the price of getting the houses in "wrong" order.
(see above, Chapter 4.1.) TODO

2. ASTROLOG program as written by Walter Pullen
-----------------------------------------------

While the freeware program Astrolog contains the planetary routines of Placalc,
it uses its own house calculation module by Walter Pullen. Various releases of
Astrolog contain different approaches to this problem.

3. ASTROLOG on our website
--------------------------

ASTROLOG is also used on Astrodienst's website for displaying free charts. This
version of Astrolog used on our website however is different from the Astrolog
program as distributed on the Internet. Our webserver version of Astrolog
contains calls to Swiss Ephemeris for planetary positions. For Ascendant, MC
and houses it still uses Walter Pullen's code. This will change in due time
because we intend to replace ASTROLOG on the website with our own charting
software.

4. Other astrology programs
---------------------------

Because most astrology programs still use the Placalc module, they follow the
Placalc method for houses inside the polar circles. They give priority to keep
the MC above the horizon and switch the Ascendant by 180 degrees if necessary
to keep the quadrants in order.

House position of a planet
==========================

The Swiss Ephemeris DLL also provides a function to compute the house position
of a given body, i.e. in which house it is. This function can be used either to
determine the house number of a planet or to compute its position in a house
horoscope. (A house horoscope is a chart in which all houses are stretched or
shortened to a size of 30 degrees. For unequal house systems, the zodiac is
distorted so that one sign of the zodiac does not measure 30 house degrees)

Note that the actual house position of a planet is not always the one that it
seems to be in an ordinary chart drawing. Because the planets are not always
exactly located on the ecliptic but have a latitude, they can seemingly be
located in the first house, but are actually visible above the horizon. In
such a case, our program function will place the body in the 12th (or 11th or
10th) house, whatever celestial geometry requires. However, it is possible to
get a house position in the "traditional" way, if one sets the ecliptic
latitude to zero.

Although it is not possible to compute Placidus house cusps beyond the polar
circle, this function will also provide Placidus house positions for polar
regions. The situation is as follows:

The Placidus method works with the semidiurnal and seminocturnal arcs of the
planets. Because in higher geographic latitudes some celestial bodies (the ones
within the circumpolar circle) never rise or set, such arcs do not exist. To
avoid this problem it has been proposed in such cases to start the diurnal
motion of a circumpolar body at its "midnight" culmination and its nocturnal
motion at its midday culmination. This procedure seems to have been proposed by
Otto Ludwig in 1930. It allows to define a planet's house position even if it
is within the circumpolar region, and even if you are born in the northernmost
settlement of Greenland. However, this does not mean that it be possible to
compute ecliptical house cusps for such locations. If one tried that, it would
turn out that e.g. an 11th house cusp did not exist, but there were two 12th
house cusps.

Note however, that circumpolar bodies may jump from the 7th house directly into
the 12th one or from the 1st one directly into the 6th one.

The Koch method, on the other hand, cannot be helped even with this method. For
some bodies it may work even beyond the polar circle, but for some it may fail
even for latitudes beyond 60 degrees. With fixed stars, it may even fail in
central Europe or USA. (Dieter Koch regrets the connection of his name with
such a badly defined house system)

Note that Koch planets do strange jumps when they cross the meridian. This is
not a computation error but an effect of the awkward definition of this house
system. A planet can be east of the meridian but be located in the 9th house,
or west of the meridian and in the 10th house. It is possible to avoid this
problem or to make Koch house positions agree better with the Huber "hand
calculation" method, if one sets the ecliptic latitude of the planets to zero.
But this is not more correct from a geometrical point of view.

Gauquelin sector position of a planet
=====================================

The calculation of the Gauquelin sector position of a planet is based on the
same idea as the Placidus house system, i.e. diurnal and nocturnal arcs of
ecliptic points or planets are subdivided.

Three different algorithms have been used by Gauquelin and others to determine
the sector position of a planet.

1. We can take the ecliptic point of the planet (ecliptical latitude ignored)
   and calculate the fraction of its diurnal or nocturnal arc it has completed
2. We can take the true planetary position (taking into account ecliptical
   latitude) for the same calculation.
3. We can use the exact times for rise and set of the planet to determine the
   ratio between the time the planet has already spent above (or below) the
   horizon and its diurnal (or nocturnal) arc. Times of rise and set are
   defined by the appearance or disappearance of the center of the planet's
   disks.

All three methods are supported by the Swiss Ephemeris.

Methods 1 and 2 also work for polar regions. The Placidus algorithm is used,
and the Otto Ludwig method applied with circumpolar bodies. I.e. if a planet
does not have a rise and set, the "midnight" and "midday" culminations are used
to define its semidiurnal and seminocturnal arcs.

With method 3, we don't try to do similar. Because planets do not culminate
exactly in the north or south, a planet can actually rise on the western part
of the horizon in high geographic latitudes. Therefore, it does not seem
appropriate to use meridian transits as culmination times. On the other hand,
true culmination times are not always available. E.g. close to the geographic
poles, the Sun culminates only twice a year.

Improvement of the Placidus house calculation in SE 2.09
========================================================

Before Swiss Ephemeris 2.09, our calculation of Placidus house positions did
not provide greatest possible precision with high geographic latitudes (noticed
by D. Senthilathiban). The Placidus house cusps were calculated with only two
iterations. This resulted in an accuracy of 1 arcsec until about the geographic
latitude 56°. On higher latitudes, the error was greater for some cusps and for
some time of the day. For latitudes extremely close to the polar circle the
error could even become greater than a degree.

This problem has been fixed by using a variable number of iterations, which
stops when the cusp converges, with n = 100 as maximum number of iterations.
If the iteration does not converge with this maximum of iterations, we switch
to Porphyry cusps and return a warning.

Example:

*Old calculation with SE 2.08:*

::

    sweph2.08/swetest -b26.1.2000 -ut8:08 -house30,66.562,P -p

    date (dmy) 26.1.2000 greg.   8:08:00 UT         version 2.08
    UT:  2451569.838888889     delta t: 63.849300 sec
    TT:  2451569.839627885
    geo. long 30.000000, lat 66.562000, alt 0.000000
    Epsilon (t/m)     23°26'16.2121   23°26'21.3741
    house  1          93°10'50.7734
    house  2          93°35'32.4962
    house  3          94°45' 1.3614
    house  4          96°22'19.2129
    house  5          99°30'38.8122
    house  6         107°41'47.9654

*New calculation with SE 2.09:*

::

    swetest -b26.1.2000 -ut8:08 -house30,66.562,P -p

    date (dmy) 26.1.2000 greg.   8:08:00 UT         version 2.08.00a
    UT:  2451569.838888889     delta t: 63.849300 sec
    TT:  2451569.839627885
    geo. long 30.000000, lat 66.562000, alt 0.000000
    Epsilon (t/m)     23°26'16.2121   23°26'21.3741
    Nutation          -0° 0'13.1306   -0° 0' 5.1621
    Houses system P (Placidus) for long=  30° 0' 0.0000, lat=  66°33'43.2000
    house  1          93°10'50.7734
    house  2          93°35'32.4962
    house  3          94°45' 1.3614
    house  4          96°22'19.2129
    house  5          99°34' 5.9429
    house  6         109°14' 4.4696

..
