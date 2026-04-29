# Compiler Pipeline Studio

A web-based compiler visualizer for a Compiler Design project. It lets users paste C code and inspect the project pipeline from lexical analysis to AST/semantic analysis, optimization, target code generation, and generated x86-64 assembly.

## Features

- Professional dashboard UI for explaining the compiler project
- C source editor with synchronized line gutter
- Phase 1 lexical token table
- Phase 2 interactive AST tree with source-line jumping
- Semantic analysis report
- Phase 3 optimization and target code generation output
- Generated assembly viewer
- Sample program storage in browser local storage
- Export buttons for report JSON, assembly, and full compiler log

## Project Structure

```text
.
├── project_showcase.html        # Main web frontend
├── frontend/
│   └── compiler_frontend.html   # Same frontend under the original filename
├── web_backend.py               # Local API server used by the frontend
├── Makefile                     # Builds lexer/parser web targets
├── include/                     # Compiler headers
├── synthesis/                   # Flex, Bison, ICG, optimizer, TCG sources
├── test/                        # Sample C programs
├── scripts/
│   ├── run_backend.sh
│   └── run_frontend.sh
└── RUN_PHASE3.md                # Original runtime notes
```

## Requirements

Install these inside WSL/Linux:

```bash
sudo apt update
sudo apt install flex bison gcc make python3
```

## Run The Website

Open two terminals from the project folder.

Terminal 1:

```bash
./scripts/run_backend.sh
```

Terminal 2:

```bash
./scripts/run_frontend.sh
```

Then open:

```text
http://localhost:8080/project_showcase.html
```

The frontend sends requests to:

```text
http://localhost:9000/api/analyze
```

## Manual Commands

Backend:

```bash
make phaseweb
python3 web_backend.py
```

Frontend:

```bash
python3 -m http.server 8080
```

## Test The Compiler Without The Website

```bash
make phaseweb
./build/parser ./test/demo2.c
```

Generated assembly is written to:

```text
output.s
```

## Notes For GitHub Upload

This folder intentionally excludes generated build files, Python caches, temporary web files, and local virtual environments. After cloning, run `make phaseweb` to regenerate the compiler binaries.
