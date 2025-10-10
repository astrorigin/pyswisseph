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

# modern documentaiton

.PHONY: docs clean-docs live

BUILD_DIR := docs/_build
SPHINX_SOURCE_DIR := docs/

docs: clean-docs
	@echo "Building documentation with Sphinx..."
	uv run sphinx-build -b html $(SPHINX_SOURCE_DIR) $(BUILD_DIR)

clean-docs:
	@echo "Cleaning up documentation build directory ($(BUILD_DIR))..."
	rm -rf $(BUILD_DIR)

live:
	@echo "Starting live documentation server..."
	uv run sphinx-autobuild --host 0.0.0.0 $(SPHINX_SOURCE_DIR) $(BUILD_DIR) --watch $(SPHINX_SOURCE_DIR)
