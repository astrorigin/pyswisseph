# Installation

## System requirements (C build tools)

pyswisseph is a Python wrapper for a C library and requires a C compiler and development headers to be installed on your system.

| OS                    | Command                                                                                   |
| --------------------- | ----------------------------------------------------------------------------------------- |
| Linux (Debian/Ubuntu) | `sudo apt-get install build-essential pkg-config`                                         |
| Linux (Fedora/RHEL)   | `sudo dnf install @development-tools`                                                     |
| macOS                 | Install **XCode Command Line Tools** (`xcode-select --install`)                           |
| Windows               | Install **Build Tools for Visual Studio** (with the "Desktop development with C++" workload)  |


## PyPI installation

pyswisseph is published to [PyPI](https://pypi.org/project/pyswisseph).

### Using `uv` (recommended)

If you're adding pyswisseph to a project:
```bash
uv add pyswisseph
```

Or installing in a virtual environment:
```bash
uv venv
source .venv/bin/activate   # On Windows: .venv\Scripts\activate
uv pip install pyswisseph
```

### Using `pip`

```bash
python3 -m venv .venv
source .venv/bin/activate   # On Windows: .venv\Scripts\Activate
pip install pyswisseph
```

## Configuration: Using extended ephemeris data

To go beyond the bundled data range (e.g., 13000 BCE - 4000 CE) or use extended data (e.g., asteroids), you must download the official Swiss Ephemeris `.se1,` `.se2`, etc., data files and point the library to them.

1. **Download** the desired ephemerides from [aloistr/swisseph](https://github.com/aloistr/swisseph/tree/master/ephe).
2. **Set the path** in your Python code before any calculation:
```python
import swisseph as swe
swe.set_ephe_path("/path/to/your/ephemeris/data")
```

## Verify installation

```py
import swisseph as swe
print(swe.version)
```

It should print `2.10.03`.

## Next steps

- [Quickstart](quickstart.md) – Calculate your first planetary position
