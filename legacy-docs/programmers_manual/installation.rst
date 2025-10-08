============
Installation
============

Installation from PyPI
======================

Pyswisseph packages are published on the
`Python Package Index <https://pypi.org/project/pyswisseph/>`_.
The preferred tool for installing packages from PyPI is **pip**. This tool is
provided with all modern versions of Python.

Open your terminal and run the following command.

::

    pip install -U pyswisseph

Installation from *PyPI* also allows you to install the latest development
release (if it exists). To do this, use the ``--pre`` flag.

::

    pip install -U --pre pyswisseph

Installation from source
========================

You can install Pyswisseph directly from a clone of the `Git repository`_.
That if you want the latest "unstable" development version.

Clone and build using **pip** with the following commands.

::

    git clone --recurse-submodules https://github.com/astrorigin/pyswisseph
    cd pyswisseph
    pip install .

The usual ``python setup.py install`` procedure works fine, too.

.. _Git repository: https://github.com/astrorigin/pyswisseph

Build using CMake
=================

It is possible to build the extension with `CMake`_. This is especially useful
for development, or if you want more flexibility.

.. _CMake: https://cmake.org/

Here is a list of interesting **cmake** options:

 - ``CMAKE_BUILD_TYPE``: Release, Debug
 - ``PYSWE_AUTO_SET_EPHE_PATH``: set ephemeris path on module import (on or off)
 - ``PYSWE_DEFAULT_EPHE_PATH``: path to directory containing ephemeris files
 - ``PYSWE_USE_SWEPHELP``: build the ``swisseph.contrib`` submodule (on or off)

CMake on Linux
--------------

Here is an example using **ccmake**, an application with a terminal
user-interface. You can use **cmake-gui** if you prefer, or the regular
**cmake**.

.. code-block:: bash

    git clone --recurse-submodules https://github.com/astrorigin/pyswisseph
    cd pyswisseph
    mkdir build
    cd build
    ccmake ..
    # 'configure' and select your options, 'configure' again
    # until you can 'generate' and exit
    # with the regular cmake, it looks like this:
    #cmake -D CMAKE_BUILD_TYPE=Release -D PYSWE_USE_SWEPHELP=0 ..
    make
    # put the resulting file 'swisseph.so' in your sys.path

CMake on Windows
----------------

What's needed:

- Visual Studio (tools for development with C++)
  from https://visualstudio.microsoft.com
- Python, CMake and Git, to clone the repository.
- Use CMake to create a "solution":

  1. Browse to the source code directory
  2. Browse to an empty directory where you want to build
  3. Click *Configure*, select your version of Visual Studio in the menu
  4. Lines in red are newly found options, leave untouched in doubt
  5. Click *Configure* again, lines become white, click *Generate*
  6. With Visual Studio, open the "solution" located in your build directory
  7. Select *Release* build type instead of *Debug*, click *Build Solution*

.. image:: cmake01.png
    :align: center

The file ``swisseph.pyd`` is found in your build directory, under ``Release``.
Put this file in your ``sys.path``.

Ephemeris files
===============

Where to go from here?

One probably wants a few ephemeris files to work with. They can be found there:
https://www.astro.com/ftp/swisseph/ephe/

For description of the main ephemeris files, see chapter
:doc:`/ephemerides/planetary_and_lunar/three_ephemerides/swiss_ephemeris`.
About asteroids, see chapter
:doc:`/ephemerides/asteroids/asteroid_ephemeris_files`.

Details about where to install your files (and why) and the "ephemeris path",
see chapter :ref:`The ephemeris path`.

..
