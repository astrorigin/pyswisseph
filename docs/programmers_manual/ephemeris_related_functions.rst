====================================
The Ephemeris file related functions
====================================

.. _The ephemeris path:

The ephemeris path
==================

This is the first function that should be called before any other function of
the Swiss Ephemeris. Even if you don't want to set an ephemeris path and use
the Moshier ephemeris, it is nevertheless recommended to call
``set_ephe_path(None)``, because this function makes important initializations.
If you don't do that, the Swiss Ephemeris may work, but the results may be not
100% consistent.

If the environment variable ``SE_EPHE_PATH`` exists in the environment where
Swiss Ephemeris is used, its content is used to find the ephemeris files. The
variable can contain a directory name, or a list of directory names separated
by ``;`` (semicolon) on Windows or ``:`` (colon) on Unix.

.. note::

   In Python, depending on how the extension was built, the ``path`` argument
   of the function has a special default value.

.. autofunction:: swisseph.set_ephe_path

Usually an application will want to set its own ephemeris, e.g. as follows:

.. code-block:: python

    swe.set_ephe_path("/usr/share/sweph/ephe")

The argument can be a single directory name or a list of directories, which are
then searched in sequence. The argument of this call is ignored if the
environment variable ``SE_EPHE_PATH`` exists and is not empty.
If you want to make sure that your program overrides any environment variable
setting, you can use ``os.putenv("SE_EPHE_PATH", "")`` to set it to an empty
string.

If the path is longer than 256 bytes, ``set_ephe_path()`` sets the path to a
predefined default value instead:

=========== ==================================
Platform    Default SE_EPHE_PATH
=========== ==================================
Windows     ``"\\sweph\\ephe"``
Mac         ``":ephe:"``
Unixes      ``".:/users/ephe2/:/users/ephe/"``
=========== ==================================

If no environment variable exists and ``set_ephe_path()`` is never called, the
built-in ephemeris path is used.

Asteroid ephemerides are looked for in the subdirectories ``ast0``, ``ast1``,
``ast2`` .. ``ast9`` of the ephemeris directory and, if not found there, in the
ephemeris directory itself. Asteroids with numbers 0 -- 999 are expected in
directory ``ast0``, those with numbers 1000 -- 1999 in directory ``ast1`` etc.

The environment variable ``SE_EPHE_PATH`` is most convenient when a user has
several applications installed which all use the Swiss Ephemeris but would
normally expect the ephemeris files in different application-specific
directories. The use can override this by setting the environment variable,
which forces all the different applications to use the same ephemeris
directory. This allows him to use only one set of installed ephemeris files for
all different applications. A developer should accept this override feature and
allow the sophisticated users to exploit it.

Release memory
==============

.. autofunction:: swisseph.close

The JPL files
=============

.. autofunction:: swisseph.set_jpl_file

.. note::

    If the file name is longer than 256 bytes, ``set_jpl_file()`` cuts the file
    name to a length of 256 bytes. The error will become visible after the
    first call of ``calc()``, when it will raise an exception.

Library version
===============

This string constant is the version number of the Swiss Ephemeris library being
used.

.. code-block:: python

   se_version_major, se_version_minor, se_version_patch = swe.version.split('.')

Library path
============

.. autofunction:: swisseph.get_library_path

Inspect ephemeris files
=======================

.. autofunction:: swisseph.get_current_file_data

..
