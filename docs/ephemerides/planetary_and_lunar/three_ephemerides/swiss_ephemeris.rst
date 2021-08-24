The Swiss Ephemeris
===================

The core part of Swiss Ephemeris is a compression of the JPL-Ephemeris DE431,
which covers roughly the time range 13.000 BCE to 17.000 CE. Using a
sophisticated mechanism, we succeeded in reducing JPL's 2.8 GB storage to only
99 MB. The compressed version agrees with the JPL Ephemeris to 1
milli-arcsecond (0.001"). Since the inherent uncertainty of the JPL ephemeris
for most of its time range is a lot greater, the Swiss Ephemeris should be
completely satisfying even for computations demanding very high accuracy.

Before 2014, the Swiss Ephemeris was based on JPL Ephemeris DE406. Its 200 MB
were compressed to 18 MB. The time range of the DE406 was 3000 BCE to 3000 CE
or 6000 years. We had extended this time range to 10.800 years, from 2 Jan 5401
BCE to 31 Dec 5399 CE. The details of this extension are described below.
To make sure that you work with current data, please check the date of the
ephemeris files. They must be 2014 or later.

Each Swiss Ephemeris file covers a period of 600 years; there are 50 planetary
files, 50 Moon files for the whole time range of almost 30.000 years and 18
main-asteroid files for the time range of 10.800 years.

The file names are as follows:

=================== ================ ================== ============================
Planetary file      Moon file        Main-asteroid file Time range
=================== ================ ================== ============================
``seplm132.se1``    ``semom132.se1``                    11 Aug 13000 BCE – 12602 BCE
``seplm126.se1``    ``semom126.se1``                    12601 BCE – 12002 BCE
``seplm120.se1``    ``semom120.se1``                    12001 BCE – 11402 BCE
``seplm114.se1``    ``semom114.se1``                    11401 BCE – 10802 BCE
``seplm108.se1``    ``semom108.se1``                    10801 BCE – 10202 BCE
``seplm102.se1``    ``semom102.se1``                    10201 BCE – 9602 BCE
``seplm96.se1``     ``semom96.se1``                     9601 BCE – 9002 BCE
``seplm90.se1``     ``semom90.se1``                     9001 BCE – 8402 BCE
``seplm84.se1``     ``semom84.se1``                     8401 BCE – 7802 BCE
``seplm78.se1``     ``semom78.se1``                     7801 BCE – 7202 BCE
``seplm72.se1``     ``semom72.se1``                     7201 BCE – 6602 BCE
``seplm66.se1``     ``semom66.se1``                     6601 BCE – 6002 BCE
``seplm60.se1``     ``semom60.se1``                     6001 BCE – 5402 BCE
``seplm54.se1``     ``semom54.se1``  ``seasm54.se1``    5401 BCE – 4802 BCE
``seplm48.se1``     ``semom48.se1``  ``seasm48.se1``    4801 BCE – 4202 BCE
``seplm42.se1``     ``semom42.se1``  ``seasm42.se1``    4201 BCE – 3602 BCE
``seplm36.se1``     ``semom36.se1``  ``seasm36.se1``    3601 BCE – 3002 BCE
``seplm30.se1``     ``semom30.se1``  ``seasm30.se1``    3001 BCE – 2402 BCE
``seplm24.se1``     ``semom24.se1``  ``seasm24.se1``    2401 BCE – 1802 BCE
``seplm18.se1``     ``semom18.se1``  ``seasm18.se1``    1801 BCE – 1202 BCE
``seplm12.se1``     ``semom12.se1``  ``seasm12.se1``    1201 BCE – 602 BCE
``seplm06.se1``     ``semom06.se1``  ``seasm06.se1``    601 BCE – 2 BCE
``sepl_00.se1``     ``semo_00.se1``  ``seas_00.se1``    1 BCE – 599 CE
``sepl_06.se1``     ``semo_06.se1``  ``seas_06.se1``    600 CE – 1199 CE
``sepl_12.se1``     ``semo_12.se1``  ``seas_12.se1``    1200 CE – 1799 CE
``sepl_18.se1``     ``semo_18.se1``  ``seas_18.se1``    1800 CE – 2399 CE
``sepl_24.se1``     ``semo_24.se1``  ``seas_24.se1``    2400 CE – 2999 CE
``sepl_30.se1``     ``semo_30.se1``  ``seas_30.se1``    3000 CE – 3599 CE
``sepl_36.se1``     ``semo_36.se1``  ``seas_36.se1``    3600 CE – 4199 CE
``sepl_42.se1``     ``semo_42.se1``  ``seas_42.se1``    4200 CE – 4799 CE
``sepl_48.se1``     ``semo_48.se1``  ``seas_48.se1``    4800 CE – 5399 CE
``sepl_54.se1``     ``semo_54.se1``                     5400 CE – 5999 CE
``sepl_60.se1``     ``semo_60.se1``                     6000 CE – 6599 CE
``sepl_66.se1``     ``semo_66.se1``                     6600 CE – 7199 CE
``sepl_72.se1``     ``semo_72.se1``                     7200 CE – 7799 CE
``sepl_78.se1``     ``semo_78.se1``                     7800 CE – 8399 CE
``sepl_84.se1``     ``semo_84.se1``                     8400 CE – 8999 CE
``sepl_90.se1``     ``semo_90.se1``                     9000 CE – 9599 CE
``sepl_96.se1``     ``semo_96.se1``                     9600 CE – 10199 CE
``sepl_102.se1``    ``semo_102.se1``                    10200 CE – 10799 CE
``sepl_108.se1``    ``semo_108.se1``                    10800 CE – 11399 CE
``sepl_114.se1``    ``semo_114.se1``                    11400 CE – 11999 CE
``sepl_120.se1``    ``semo_120.se1``                    12000 CE – 12599 CE
``sepl_126.se1``    ``semo_126.se1``                    12600 CE – 13199 CE
``sepl_132.se1``    ``semo_132.se1``                    13200 CE – 13799 CE
``sepl_138.se1``    ``semo_138.se1``                    13800 CE – 14399 CE
``sepl_144.se1``    ``semo_144.se1``                    14400 CE – 14999 CE
``sepl_150.se1``    ``semo_150.se1``                    15000 CE – 15599 CE
``sepl_156.se1``    ``semo_156.se1``                    15600 CE – 16199 CE
``sepl_162.se1``    ``semo_162.se1``                    16200 CE – 7 Jan 16800 CE
=================== ================ ================== ============================

All Swiss Ephemeris files have the file suffix ``.se1``. A planetary file is
about 500 kb, a lunar file 1300 kb. Swiss Ephemeris files are available for
download from `Astrodienst's web server`_.

.. _Astrodienst's web server: https://www.astro.com/ftp/swisseph/ephe/

The time range of the Swiss Ephemeris
+++++++++++++++++++++++++++++++++++++

Versions until 1.80, which were based on JPL Ephemeris DE406 and some extension
created by Astrodienst, work for the following time range:

=========== =============================== ============
Start date  2 Jan 5401 BCE (-5400) Jul.     JD -251291.5
End date    31 Dec 5399 CE (Greg. Cal.)     JD 3693368.5
=========== =============================== ============

Versions since 2.00, which are based on JPL Ephemeris DE431, work for the
following time range:

=========== =============================== =============
Start date  11 Aug 13000 BCE (-12999) Jul.  JD -3026604.5
End date    7 Jan 16800 CE Greg.            JD 7857139.5
=========== =============================== =============

Please note that versions prior to 2.00 are not able to correctly handle the
JPL ephemeris DE431.

A note on year numbering
++++++++++++++++++++++++

There are two numbering systems for years before the year 1 CE. The historical
numbering system (indicated with BCE) has no year zero. Year 1 BCE is followed
directly by year 1 CE.

The astronomical year numbering system does have a year zero; years before the
common era are indicated by negative year numbers. The sequence is year -1,
year 0, year 1 CE.

 - the historical year 1 BCE corresponds to astronomical year 0,
 - the historical year 2 BCE corresponds to astronomical year -1, etc.

In this and other documents related to the Swiss Ephemeris we use both systems
of year numbering. When we write a negative year number, it is astronomical
style; when we write BCE, it is historical style.

..
