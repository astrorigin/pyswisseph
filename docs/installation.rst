============
Installation
============

Installation from PyPI
----------------------

Pyswisseph packages are published on the
`Python Package Index <https://pypi.org/project/pyswisseph/>`_.
The preferred tool for installing packages from PyPI is **pip**. This tool is
provided with all modern versions of Python.

Open your terminal and run the following command.

::

    pip install -U pyswisseph

Installation from *PyPI* also allows you to install the latest development
release. To do this, use the ``--pre`` flag.

::

    pip install -U --pre pyswisseph

Installation from source
------------------------

You can install Pyswisseph directly from a clone of the `Git repository`_.

Clone and build using **pip** with the following commands.

::

    git clone --recurse-submodules https://github.com/astrorigin/pyswisseph
    cd pyswisseph
    pip install .

.. _Git repository: https://github.com/astrorigin/pyswisseph

Build using CMake
-----------------

It is possible to build the extension with `CMake`_. This is especially useful
for development, or if you want more flexibility.

.. _CMake: https://cmake.org/

Here is a list of interesting **cmake** options:

 - ``CMAKE_BUILD_TYPE``: Release, Debug
 - ``PYSWE_AUTO_SET_EPHE_PATH``: set ephemeris path on module import (on or off)
 - ``PYSWE_DEFAULT_EPHE_PATH``: path to directory containing ephemeris files
 - ``PYSWE_USE_SWEPHELP``: build the ``swisseph.contrib`` submodule (on or off)

..
