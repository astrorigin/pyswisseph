import os
import sys

sys.path.insert(0, os.path.abspath('..'))

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


autodoc_default_options = {
    'members': True,
    'undoc-members': True,
    'show-inheritance': True,
    'no-inherited-members': True,
}

toc_object_entries = False

html_theme_options = {
    "icon": {
        "logo": "material/orbit",
        "repo": "fontawesome/brands/github",
    },
    "repo_url": "https://github.com/sailorfe/pyswisseph/",
    "repo_name": "pyswisseph",
    "toc_title": "On this page",
    "toc_title_is_page_title": False,
    "palette": [
        {
            "media": "(prefers-color-scheme)",
            "scheme": "default",
            "primary": "deep-purple",
            "accent": "purple",
            "toggle": {
                "icon": "material/toggle-switch",
                "name": "Switch to light mode",
            }
        },
        {
            "media": "(prefers-color-scheme: light)",
            "scheme": "default",
            "primary": "deep-purple",
            "accent": "purple",
            "toggle": {
                "icon": "material/toggle-switch",
                "name": "Switch to dark mode",
            }
        },
        {
            "media": "(prefers-color-scheme: dark)",
            "scheme": "slate",
            "primary": "deep-purple",
            "accent": "purple",
            "toggle": {
                "icon": "material/toggle-switch-off-outline",
                "name": "Switch to system preference",
            }
        }
    ]
}
