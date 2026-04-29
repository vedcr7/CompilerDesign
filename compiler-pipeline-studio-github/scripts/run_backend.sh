#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")/.."

make phaseweb
python3 web_backend.py
