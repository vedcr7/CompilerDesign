# Phase 3 Runtime Guide (Optimization + TCG)

## Folder

`/home/ved/updated/phase 3`

## Build and Run

```bash
cd "/home/ved/updated/phase 3"
make clean
make phase2
./build/parser ./test/demo2.c
```

This test file is semantically clean and reaches:
- Phase 4 (ICG)
- Phase 5 (Optimization)
- Phase 6 (Target Code Generation)

## Show Target Code (Assembly)

```bash
cd "/home/ved/updated/phase 3"
sed -n '1,220p' output.s
```

## Execute Generated Assembly

```bash
cd "/home/ved/updated/phase 3"
gcc -no-pie output.s -o output
./output
```

## Open Showcase Website

```bash
cd "/home/ved/updated/phase 3"
python3 -m http.server 8080
```

Then open:

`http://localhost:8080/project_showcase.html`

## Full Web App (Backend + Frontend)

This mode lets you paste any C code in browser and see 3 project phases:
- Phase 1: Lexical analysis
- Phase 2: AST + semantic analysis
- Phase 3: Optimization + target code generation

### 1) Start backend API in WSL

```bash
cd "/home/ved/updated/phase 3"
make phaseweb
python3 web_backend.py
```

Backend runs on:

`http://localhost:9000`

### 2) Start frontend page in another WSL terminal

```bash
cd "/home/ved/updated/phase 3"
python3 -m http.server 8080
```

Open:

`http://localhost:8080/project_showcase.html`
