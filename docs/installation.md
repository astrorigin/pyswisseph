# Installation

pyswisseph is published to [PyPI](https://pypi.org/project/pyswisseph).

## Using `uv` (recommended)

If you're adding pyswisseph to a project:
```bash
uv add pyswisseph
```

Or installing in a virtual environment:
```bash
uv venv
source .venv/bin/activate   # On Windows: .venv\Scripts\activate
uv pip instasll pyswisseph
```

## Using `pip`

```bash
python3 -m venv .venv
source .venv/bin/activate   # On Windows: .venv\Scripts\Activate
pip install pyswisseph
```

## Verify installation

```py
import swisseph as swe
print(swe.version)
```

It should print `2.10.03`.

## Next steps

- [Quickstart](quickstart.md) – Calculate your first planetary position
