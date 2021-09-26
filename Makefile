# pyswisseph Makefile

PYTHON = python3

.DEFAULT_GOAL := void

.PHONY: build clean html install sdist void

build:
	$(PYTHON) setup.py build

clean:
	rm -rf MANIFEST build dist .eggs *.egg-info *.so docs/_build/*

html:
	cd docs && make html

install:
	$(PYTHON) setup.py install

sdist:
	$(PYTHON) setup.py sdist --formats=gztar,xztar,zip

void: ;

# vi: sw=4 ts=4 noet
