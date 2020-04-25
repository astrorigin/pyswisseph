# pyswisseph Makefile

PYTHON = python3

.DEFAULT_GOAL := void

.PHONY: build clean install sdist void

build:
	$(PYTHON) setup.py build

clean:
	rm -rf MANIFEST build dist

install:
	$(PYTHON) setup.py install

sdist:
	$(PYTHON) setup.py sdist --formats=xztar

void: ;

# vi: sw=4 ts=4 noet
