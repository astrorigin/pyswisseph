README.TXT   24-Dec-1998 by Alois Treindl
	     last update 7-may-2014  zip files were updated

=======================================================================
This directory contains the binary ephemeris files of SWISS EPHEMERIS.
=======================================================================


LICENSE.TXT
	The Swiss Ephemeris is published under GPL and alternatively
	a commercial license (for paying customers).
	You must read and accept the license before you download any files.


sepl*.se1	SwissEph ephemeris files for main planets, 600 years per file
semo*.se1	SwissEph ephemeris files for Moon, 600 years per file
seas*.se1	SwissEph ephemeris files with asteroids Ceres, Pallas, Vesta,
		Juno, Chiron and Pholus, 600 years per file
		BE AWARE that the same files are also in the archive files
		below. It is faster to download them in archived format.

		These files cover the time range 13200 BC to 16200 AD.

		Download problems with ephemeris files: With some browsers 
		for download, you may have observe
		that the binary ephemeris files appear as garbage on your
		screen instead of a file save dialog being offered.
		You need to define a proper MIME type for the file suffix se1.
		It is simpler however, to go to the archive directory and
		to download the zip or gz archives containing the same
		ephemeris files.

fixstars.cat	list of fixed stars with elements
		Attention, this file is different from a file with the
		same name in the Placalc directory. The Placalc fixstar
		list does not work with Swiss Ephemeris.

archive_zip
	Directory containing compressed archives of the ephemeris
	files for easier download. Archives are provides in ZIP
	format for Windows.
	Each archive covers 600 years and has a file size of about 2 Mbyte.
	The same files exist in Unix-gzip format in directory archive_gzip.

	sweph_00.zip	contains sepl_00.se1, semo_00.se1, seas_00.se1
			ephemeris files for   01 BC -  600 AD

	sweph_06.zip	contains sepl_06.se1, semo_06.se1, seas_06.se1
			ephemeris files for  600 AD - 1200 AD

	sweph_12.zip	contains sepl_12.se1, semo_12.se1, seas_12.se1
			ephemeris files for 1200 AD - 1800 AD

	sweph_18.zip	contains sepl_18.se1, semo_18.se1, seas_18.se1
			ephemeris files for 1800 AD - 2400 AD
	THIS FILE SHOULD BE DOWNLOADED FOR THE CURRENT EPHEMERIS.

	sweph_24.zip	contains sepl_24.se1, semo_24.se1, seas_24.se1
			ephemeris files for 2400 AD - 3000 AD

	sweph_30.zip	contains sepl_30.se1, semo_30.se1, seas_30.se1
			ephemeris files for 3000 AD - 3600 AD

	sweph_36.zip	contains sepl_36.se1, semo_36.se1, seas_36.se1
			ephemeris files for 3600 AD - 4200 AD

	sweph_42.zip	contains sepl_42.se1, semo_42.se1, seas_42.se1
			ephemeris files for 4200 AD - 4800 AD

	sweph_48.zip	contains sepl_48.se1, semo_48.se1, seas_48.se1
			ephemeris files for 4800 AD - 5400 AD

	swephm06.zip	contains seplm06.se1, semom06.se1, seasm06.se1
			ephemeris files for  601 BC -   02 BC

	swephm12.zip	contains seplm12.se1, semom12.se1, seasm12.se1
			ephemeris files for 1201 BC -  602 BC

	swephm18.zip	contains seplm18.se1, semom18.se1, seasm18.se1
			ephemeris files for 1801 BC - 1202 BC

	swephm24.zip	contains seplm24.se1, semom24.se1, seasm24.se1
			ephemeris files for 2401 BC - 1802 BC

	swephm30.zip	contains seplm30.se1, semom30.se1, seasm30.se1
			ephemeris files for 3001 BC - 2402 BC

	swephm36.zip	contains seplm36.se1, semom36.se1, seasm36.se1
			ephemeris files for 3601 BC - 3002 BC

	swephm42.zip	contains seplm42.se1, semom42.se1, seasm42.se1
			ephemeris files for 4201 BC - 3602 BC

	swephm48.zip	contains seplm48.se1, semom48.se1, seasm48.se1
			ephemeris files for 4801 BC - 4202 BC

	swephm54.zip	contains seplm54.se1, semom54.se1, seasm54.se1
			ephemeris files for 5401 BC - 4802 BC


Asteroid files:
===============
Astrodienst performs numerical integration
for all known and numbered asteroids.
Our software computes about 200 asteroids per day.
The number of officially numbered asteroids continues to grow at a
very fast pace now.
On May 2014 2008 the number of 385'000 asteroids was reached.

For each asteroid there is a short file, e.g. se03045s.se1 covering the years
1500 - 2100, and a long file se03045.seq for the years -3000 .. 3000.
The short 600-year files are published here in this download area.
The long 6000-year files are available in the directory longfiles.

The asteroid files are organized in directories ast0 .. ast9 by their minor
planet numbers. Asteroids with number below 1000 are in ast0,
asteroids 1000 - 1999 in ast1,
etc, with 1000 files per directory.

DO NOT DOWNLOAD ALL THESE FILES, IT DOES NOT MAKE SENSE!
Just pick the few asteroids you might be interested in, e.g. asteroid #3045
which goes under the name 'Alois'. 

The six most interesting asteroids Ceres, Pallas, Vesta, Juno, Chiron and Pholus
are packed together in the Swiss Ephemeris standard files, seas*.se1, and need
no to be picked separately out of the asteroid collection. 
You will notice that there are no asteroid files for the numbers 1,2,3 and 4
in directory ast0, for this reason.

Long asteroid files:
The files for 6000 years are in the sub directory longfiles.

Asteroid collections available on CDROM:
========================================
We do not offer CDROMS now. Download is the only option. All parts
of Swiss Ephemeris are found in the download area.

JPL files
=========
In directory 'jplfiles' you find binary ephemeris files.
Some of them (de200, de405, de406, de431) are copies of binary files
as distributed by JPL.

JPL ephemeris files with DE-number > 406 can only be used with Swiss
Ephemeris release 1.75 or later.

Legal restrictions
==================
Read LICENSE.TXT
