# pyswisseph Makefile

CD = cd
PY = python
RM = rm -rf
CP = cp -f
MKDIR = mkdir -p
CMAKE = cmake-gui
PYDOC = epydoc
RST = rst2html


all: libswe.a build

libswe.a:
	$(CD) src; make $@

build: libswe.a
	$(PY) setup.py build

install:
	$(PY) setup.py install

clean:
	$(RM) build dist pydoc swisseph.html index.html README.html MANIFEST CMakeLists.txt

cleanswe:
	$(RM) src/*.o src/*.a src/swetest src/CMakeLists.txt src/build*

mrproper: clean cleanswe

doc: build
	$(PYDOC) --config epydoc.cfg

rst:
	$(RST) --config docutils.cfg index.txt index.html

rpm:
	$(PY) setup.py bdist_rpm --use-bzip2

dist: doc rst cleanswe
	$(PY) setup.py sdist --formats=bztar

upload: doc rst cleanswe
	$(PY) setup.py sdist --formats=bztar upload

cmakebuild: mrproper
	$(CP) cmake/pysweCMakeLists.txt CMakeLists.txt;\
	$(CP) cmake/sweCMakeLists.txt src/CMakeLists.txt;\
	$(MKDIR) build; $(CD) build;\
	$(CMAKE) ..

.PHONY: all libswe.a build install clean cleanswe mrproper\
	doc rst rpm upload cmakebuild

# end.
