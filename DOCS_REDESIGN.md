# Documentation Redesign Plan

## Problem

While building [an astrology CLI](https://github.com/sailorfe/ephem) with pyswisseph, I constantly referenced [the C library docs](https://www.astro.com/swisseph/swephprg.htm) instead of the Python wrapper docs because:

1. **Broken and outdated**: The link on GitHub ([astrorigin.com/pyswisseph](https://astrorigin.com/pyswisseph)) goes nowhere. `docs/` was last updated 2021, while the C library's most recent copyright dates it 2022.
2. **No installation instructions**: Users must guess how to install the package.
3. **Wrong structure**: Mirrors C library organization instead of Python developer workflows.
4. **No entry point**: No quickstart or "calculate your first position" guide.
5. **Community acknowledgment**: C library maintainer opened [issue #85](https://github.com/astrorigin/pyswisseph/issues/85) about pyswisseph docs problems.

Current docs assume you already understand both astronomical concepts AND the C API. Directories like `heliacal_events_eclipses_occultations_etc/` are unwieldy. Content includes C-specific sections (DLLs, Delphi, Visual Basic) irrelevant to Python users.

## Solution

Rebuild docs around how Python developers actually use the library:

```
docs/
|-- index.md
|-- installation.md
|-- quickstart.md
|-- concepts/
|-- guides/
|-- api/
`-- c_to_python/
```

### Key improvements:
- Modern installation instructions with uv and pip
- Python-first organization (not C library mirror)
- Progressive disclosure: simple → intermediate → advanced
- Explicit C-to-Python translation guide
- MyST (Markdown) instead of reStructuredText
- Modern Python examples with type hints

## Migration strategy

**Keep:** Function descriptions, parameter docs, astronomical concepts
**Discard:** C-specific implementation (DLLs, pre-2.0 version history)
**Add:** Installation guide, quickstart, task-oriented guides, C-to-Python mapping

## Success metrics

- Users can install the library (currently impossible from docs)
- Calculate a planet position within 5 minutes
- Find Python equivalents of C functions immediately
- No C library knowledge required for common tasks

---

*Note: This is my first API documentation project (I've only done user docs). Starting fresh with modern patterns (Divio framework) rather than fixing the broken structure.*
