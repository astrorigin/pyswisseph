=========================================================
The sign of geographical longitudes in Swisseph functions
=========================================================

There is a disagreement between American and European programmers whether
eastern or western geographical longitudes ought to be considered positive.
Americans prefer to have West longitudes positive, Europeans prefer the older
tradition that considers East longitudes as positive and West longitudes as
negative.

The Astronomical Almanac still follows the European pattern. It gives the
geographical coordinates of observatories in "East longitude".

The Swiss Ephemeris also follows the European style. All Swiss Ephemeris
functions that use geographical coordinates consider positive geographical
longitudes as East and negative ones as West.

E.g. 87w39 = -87.65° (Chicago IL/USA) and 8e33 = +8.55° (Zurich, Switzerland).

There is no such controversy about northern and southern geographical
latitudes. North is always positive and south is negative.

Geographic versus geocentric latitude
=====================================

There is some confusion among astrologers whether they should use geographic
latitude (also called geodetic latitude, which is a synonym) or geocentric
latitude for house calculations, topocentric positions of planets, eclipses,
etc.

Where latitude is an input parameter (or output parameter) in Swiss Ephemeris
functions, it is always geographic latitude. This is the latitude found in
Atlases and Google Earth.

If internally in a function a conversion to geocentric latitude is required
(because the 3-d point on the oblate Earth is needed), this is done
automatically.

For such conversions, however, the Swiss Ephemeris only uses an ellipsoid for
the form of the Earth. It does not use the irregular geoid. This can result in
an altitude error of up to 500 meters, or error of the topocentric Moon of up
to 0.3 arc seconds.

Astrologers who claim that for computing the ascendant or houses one needs
geocentric latitude are wrong. The flattening of the Earth does not play a part
in house calculations. Geographic latitude should always be used with house
calculations.

..
