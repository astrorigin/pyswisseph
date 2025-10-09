import os
import sys

sys.path.insert(0, os.path.abspath('..'))
autodoc_mock_imports = ['swisseph']

project = 'Pyswisseph'
copyright = '2007-2025, Pyswisseph authors and contributors'
author = 'Pyswisseph Authors and Documentation Contributors'
version = '2.10.02.0-dev'
release = '2.10.02.0-dev'

extensions = [
    'myst_parser',
    'sphinx.ext.autodoc',
    'sphinx.ext.napoleon',
    'sphinx_immaterial'
]

templates_path = ['_templates']

exclude_patterns = ['_build']

html_theme = 'sphinx_immaterial'

html_theme_options = {
    "icon": {
        "repo": "fontawesome/brands/github",
    },
    "palette": {
        "primary": "indigo",
        "accent": "light blue",
    },
    "repo_url": "https://github.com/sailorfe/pyswisseph/",
    "repo_name": "pyswisseph"
}
