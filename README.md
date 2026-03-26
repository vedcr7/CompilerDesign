# Compiler Project — Phase 1 & Phase 2
### Lexical Analyser + Parser with AST Generation
---

## Project Structure

```
compiler/
├── Makefile          ← builds both phases
├── sample.c          ← example C input to test with
│
├── phase1/
│   └── lexer.l       ← Flex lexical analyser (Phase 1)
│
└── phase2/
    ├── ast.h         ← AST node definitions (shared header)
    ├── lexer.l       ← Flex lexer that feeds tokens to Bison
    └── parser.y      ← Bison parser + AST builder (Phase 2)
```

---

## Requirements

| Tool  | Version  | Install (Ubuntu/Debian)          |
|-------|----------|----------------------------------|
| Flex  | 2.6+     | `sudo apt install flex`          |
| Bison | 3.0+     | `sudo apt install bison`         |
| GCC   | any      | `sudo apt install gcc`           |

**macOS:**
```bash
brew install flex bison gcc
# Add bison to PATH (Homebrew bison takes priority over system bison):
export PATH="$(brew --prefix bison)/bin:$PATH"
```

**Windows:**
Use WSL (Windows Subsystem for Linux) or MSYS2. Inside WSL/MSYS2:
```bash
sudo apt install flex bison gcc    # WSL
pacman -S flex bison gcc           # MSYS2
```

---

## Build

```bash
# Build both phases at once
make

# Or build individually
make phase1       # produces phase1/lexer
make phase2       # produces phase2/parser
```

---

## Run

### Phase 1 — Lexical Analysis
```bash
./phase1/lexer sample.c
./phase1/lexer your_program.c
```

**Output:** A formatted table showing every token found:
- Line number
- Token type  (KEYWORD, IDENTIFIER, INT_NUMBER, OP_ARITH, etc.)
- Token value
- Lexical errors (unclosed strings, invalid characters) printed to stderr

### Phase 2 — Parsing + AST
```bash
./phase2/parser sample.c
./phase2/parser your_program.c
```

**Output:**
1. Syntax error messages (if any) — to stderr
2. A coloured tree diagram of the Abstract Syntax Tree (AST)

---

## Test Both at Once

```bash
make test         # runs both phases on sample.c
```

---

## AST Node Types

| Node         | Meaning                                      |
|--------------|----------------------------------------------|
| PROGRAM      | Root of the tree                             |
| FUNC_DEF     | Function definition                          |
| BLOCK        | Compound statement `{ … }`                   |
| DECL         | Variable declaration `int x;`                |
| DECL_INIT    | Declaration with initialiser `int x = 5;`    |
| ASSIGN       | Assignment `x = expr` or `x += expr`         |
| IF           | If statement (with optional else)            |
| WHILE        | While loop                                   |
| DO_WHILE     | Do-while loop                                |
| FOR          | For loop                                     |
| RETURN       | Return statement                             |
| BREAK        | Break statement                              |
| CONTINUE     | Continue statement                           |
| BINOP        | Binary operation (`+`, `-`, `*`, `==`, …)   |
| UNOP         | Unary operation (`!`, `~`, `pre++`, …)       |
| CALL         | Function call `f(args)`                      |
| INDEX        | Array index `a[i]`                           |
| MEMBER       | Struct member `.field` or `->field`          |
| TERNARY      | Ternary `cond ? a : b`                       |
| CAST         | Type cast `(int) x`                          |
| IDENT        | Identifier leaf                              |
| INT_LIT      | Integer literal leaf                         |
| FLOAT_LIT    | Float literal leaf                           |
| STRING_LIT   | String literal leaf                          |
| CHAR_LIT     | Character literal leaf                       |
| TYPE         | Type specifier (`int`, `char`, …)            |
| PARAM        | Function parameter                           |

---

## How It Works

### Phase 1 — Lex flow
```
source.c  →  [Flex rules]  →  token table on stdout
```
Flex reads the file character-by-character. Rules are matched
longest-first. Start conditions (`%x`) handle multi-line
block comments and string literals safely.

### Phase 2 — Lex + Bison flow
```
source.c
  → [Flex lexer]  returns token IDs + values (yylval)
  → [Bison parser] matches grammar rules, executes actions
  → [AST builder]  allocates ASTNode structs, links children
  → ast_print()    walks tree recursively, prints with colour
```
The grammar follows standard C operator precedence using
Bison's `%left` / `%right` declarations and an explicit
precedence-climbing hierarchy in the grammar rules.

---

## Colour Legend (terminal output)

| Colour       | Meaning (Phase 1)     | Meaning (Phase 2 AST)  |
|--------------|-----------------------|------------------------|
| Bold blue    | Keywords              | —                      |
| White        | Identifiers           | —                      |
| Green        | Numbers               | —                      |
| Yellow       | Strings / chars       | Node value             |
| Magenta      | Operators             | —                      |
| Cyan         | Symbols               | Node kind name         |
| Dark grey    | Comments              | Line number / tree     |
| Bold red     | Errors                | Errors                 |
| Bold green   | —                     | AST root label         |

---

## Clean Up

```bash
make clean        # removes all generated C files and binaries
```
