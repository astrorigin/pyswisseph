# pyswisseph makefile for unixes

CD = cd
PY = python
RM = rm -rf
PYDOC = epydoc
RST = rst2html.py


all: libswe.a build

libswe.a:
	$(CD) src; make $@

build: libswe.a
	$(PY) setup.py build

install:
	$(PY) setup.py install

clean:
	$(RM) build dist pydoc swisseph.html index.html README.html MANIFEST

cleanswe:
	$(RM) src/*.o src/*.a

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

# end.
