# C Compiler Front-End
### Lexical Analysis · Syntax Parsing · AST Generation · Semantic Analysis
**Compiler Design Project — Graphic Era University**

---

## What This Project Does

This project implements a **compiler front-end for a subset of the C programming language**, built from scratch using industry-standard tools — Flex (for lexical analysis) and Bison (for parsing). It is structured in three phases that mirror how a real-world compiler processes source code, from raw characters all the way to a structured, analysed program representation.

When you run a C program through this compiler front-end, it does the following:

1. **Reads your source code** character by character and breaks it into meaningful tokens (Phase 1)
2. **Checks that those tokens follow valid C grammar rules** and builds a tree structure representing the program (Phase 2)
3. **Walks that tree and detects logical errors** — undeclared variables, wrong argument counts, array out-of-bounds access, division by zero, type mismatches, and more (Phase 3)

This is exactly what the front-end of compilers like GCC and Clang do before generating machine code.

---

## Project Phases

### Phase 1 — Lexical Analysis
> *"Breaking source code into tokens"*

The lexer reads the raw `.c` file and converts it into a stream of classified tokens. Every keyword, identifier, number, operator, symbol, string, and comment is recognised and labelled. Lexical errors — such as unclosed strings, unclosed block comments, and invalid characters — are detected and reported with the exact line number.

**Input:** Any `.c` source file  
**Output:** A colour-coded token table showing line number, token type, category, and value

**Example output for `int x = 10;`:**
```
LINE  TOKEN TYPE              CATEGORY        VALUE
──────────────────────────────────────────────────
1     KEYWORD                 keyword         int
1     IDENTIFIER              identifier      x
1     OP_ASSIGN               operator        =
1     INTEGER                 literal         10
1     SEMICOLON               symbol          ;
```

---

### Phase 2 — Syntax Analysis & AST Construction
> *"Checking grammar and building a program tree"*

The parser takes the token stream from Phase 1 and checks it against the grammar rules of C. If the syntax is valid, it builds an **Abstract Syntax Tree (AST)** — a tree where every node represents a construct in the program (a function, a loop, an expression, an assignment). The tree structure makes the program's logic visible and navigable.

**Input:** Token stream from Phase 1  
**Output:** A colour-coded, indented AST printed to the terminal

**Example — what `int add(int x, int y) { return x + y; }` looks like as an AST:**
```
└── FUNC_DEF  (add)  [line 1]
    ├── TYPE  (int)  [line 1]
    ├── PARAM_LIST  [line 1]
    │   ├── PARAM  (x)  [line 1]
    │   │   └── TYPE  (int)  [line 1]
    │   └── PARAM  (y)  [line 1]
    │       └── TYPE  (int)  [line 1]
    └── BLOCK  [line 1]
        └── RETURN  (return)  [line 1]
            └── BINOP  (+)  [line 1]
                ├── IDENT  (x)  [line 1]
                └── IDENT  (y)  [line 1]
```

---

### Phase 3 — Semantic Analysis
> *"Finding the logical bugs a compiler would catch"*

Once the AST is built, the semantic analyser walks it and applies a set of semantic rules that go beyond grammar. It maintains a **symbol table** — a record of every variable, function, and array declared — and uses it to verify the program's meaning, not just its structure.

**What the semantic analyser detects:**

| Check | Example | Severity |
|---|---|---|
| Undeclared variable | Using `x` without `int x;` | Error |
| Undeclared function | Calling `foo()` with no definition | Error |
| Duplicate declaration | Declaring `int x;` twice in same scope | Error |
| Wrong argument count | `add(1, 2, 3)` when `add` takes 2 params | Error |
| Array out-of-bounds | `arr[10]` on a declared `int arr[5]` | Error |
| Division by zero | `result / 0` with a literal zero | Error |
| Type mismatch | Assigning a string to an `int` variable | Error |
| Use before initialisation | Reading `x` before it has been assigned | Warning |
| Unused variable | Declaring `int score;` and never using it | Warning |
| Float → int data loss | `int x = 3.14;` truncates silently | Warning |
| Missing return statement | Non-void function with no `return` | Warning |

**Example semantic output:**
```
  [ERROR  ] line 34    Array 'arr[5]': index 10 is out of bounds (size=5).
             → Hint: Array indices must be 0 to size-1.

  [ERROR  ] line 37    Function 'add' expects 2 argument(s) but called with 3.
             → Hint: Check the function signature and provide the correct number of arguments.

  [WARNING] line 29    Variable 'score' declared at line 29 but never used.
             → Hint: Remove 'score' or use it — unused variables waste memory.

  [WARNING] line 42    Assigning float to int variable 'approx' — possible data loss.
             → Hint: Cast explicitly: (int)expr, or change the variable type to float.
```

---

## Project Structure

```
compiler_project/
│
├── phase_1/
│   └── lexer.l          ← Flex rules for lexical analysis (Phase 1)
│
└── phase_2/
    ├── ast.h            ← AST node definitions, symbol table, semantic analyser
    ├── lexer.l          ← Flex lexer that feeds tokens to Bison (Phase 2+3)
    ├── parser.y         ← Bison grammar rules + AST builder + main driver
    └── demo.c           ← Sample C input that demonstrates all error detection
```

---

## Requirements

| Tool | Version | Install |
|---|---|---|
| Flex | 2.6+ | `sudo apt install flex` |
| Bison | 3.0+ | `sudo apt install bison` |
| GCC | any | `sudo apt install gcc` |
| Make | any | `sudo apt install make` |

Install all at once:
```bash
sudo apt update && sudo apt install flex bison gcc make -y
```

---

## Build & Run

### Phase 1 — Lexical Analyser

```bash
cd ~/compiler_project/phase_1

# Step 1: Generate C code from Flex rules
flex lexer.l

# Step 2: Compile
gcc lex.yy.c -lfl -o lexer

# Step 3: Run on any C file
./lexer ../phase_2/demo.c
```

### Phase 2 + 3 — Parser, AST, and Semantic Analysis

```bash
cd ~/compiler_project/phase_2

# Step 1: Generate parser from Bison grammar
bison -d parser.y

# Step 2: Generate lexer C code
flex lexer.l

# Step 3: Compile everything together
gcc parser.tab.c lex.yy.c -lfl -o parser

# Step 4: Run on any C file
./parser demo.c
```

---

## How the Tools Work Together

```
Your C source file
        │
        ▼
┌───────────────┐
│  Flex Lexer   │  Reads characters, matches patterns using regular
│  (lexer.l)    │  expressions, returns token IDs and values to Bison
└───────┬───────┘
        │  token stream (ID, type, value)
        ▼
┌───────────────┐
│ Bison Parser  │  Matches tokens against grammar rules, builds the
│  (parser.y)   │  Abstract Syntax Tree node by node
└───────┬───────┘
        │  AST (tree of ASTNode structs)
        ▼
┌───────────────┐
│  Semantic     │  Walks the AST, maintains a symbol table, checks
│  Analyser     │  types, scopes, declarations, and usage patterns
│   (ast.h)     │
└───────┬───────┘
        │
        ▼
  Symbol Table + Issue Report + AST printout
```

Flex and Bison communicate through the `yylval` union — the lexer sets a value (like the identifier name or number literal) and returns a token ID, which Bison uses to match grammar rules and trigger AST-building actions.

---

## AST Node Reference

| Node | What it represents |
|---|---|
| `PROGRAM` | Root of the entire tree |
| `FUNC_DEF` | A function definition with return type, parameters, and body |
| `BLOCK` | A compound statement enclosed in `{ }` |
| `DECL` | A variable declaration — `int x;` |
| `DECL_INIT` | A declaration with initialiser — `int x = 5;` |
| `ARRAY_DECL` | An array declaration — `int arr[10];` |
| `ASSIGN` | An assignment — `x = expr` or `x += expr` |
| `IF` | An if statement, with optional else branch |
| `WHILE` | A while loop |
| `DO_WHILE` | A do-while loop |
| `FOR` | A for loop with init, condition, update, and body |
| `RETURN` | A return statement |
| `BREAK` | A break statement |
| `CONTINUE` | A continue statement |
| `BINOP` | A binary operation — `+`, `-`, `*`, `/`, `==`, `&&`, etc. |
| `UNOP` | A unary operation — `!`, `~`, `pre++`, `post--`, `sizeof` |
| `CALL` | A function call — `f(arg1, arg2)` |
| `INDEX` | An array index expression — `arr[i]` |
| `TERNARY` | A ternary expression — `cond ? a : b` |
| `IDENT` | An identifier leaf node |
| `INT_LIT` | An integer literal leaf node |
| `FLOAT_LIT` | A floating-point literal leaf node |
| `STRING_LIT` | A string literal leaf node |
| `CHAR_LIT` | A character literal leaf node |
| `TYPE` | A type specifier — `int`, `float`, `char`, etc. |
| `PARAM` | A function parameter |
| `PARAM_LIST` | The list of parameters in a function signature |
| `ARG_LIST` | The list of arguments in a function call |

---

## Colour Guide (Terminal Output)

### Phase 1 — Lexer
| Colour | Token category |
|---|---|
| Bold blue | Keywords (`int`, `if`, `while`, …) |
| White | Identifiers (variable and function names) |
| Green | Numeric literals (integers, floats, hex) |
| Yellow | String and character literals |
| Magenta | Operators (`+`, `==`, `&&`, `<<=`, …) |
| Cyan | Symbols (`;`, `{`, `[`, …) |
| Light blue | Preprocessor directives (`#include`, `#define`) |
| Dark grey | Comments |
| Bold red | Lexical errors |

### Phase 2+3 — AST & Semantic Report
| Colour | Meaning |
|---|---|
| Cyan bold | AST node kind name |
| Yellow | Node value (operator, identifier, literal) |
| Dark grey | Line numbers and tree branch lines |
| Blue | Type nodes |
| Magenta | Assignment and binary operation nodes |
| Orange | Control flow nodes (if, while, for) |
| Bold green | AST root label |
| Bold red | Semantic errors |
| Yellow | Semantic warnings |

---

## Clean Build Files

To remove all generated files and start fresh:

```bash
# Phase 1
cd ~/compiler_project/phase_1
rm -f lex.yy.c lexer

# Phase 2
cd ~/compiler_project/phase_2
rm -f lex.yy.c parser.tab.c parser.tab.h parser parser.output
```

---

## Why This Project Matters

Every modern compiler — GCC, Clang, MSVC — has a front-end that does exactly these three things. This project demonstrates a working implementation of that front-end pipeline:

- **Flex** implements the same DFA-based lexical analysis technique used in production compilers
- **Bison** implements LALR(1) parsing, the same algorithm used by GCC's early parser
- **The semantic analyser** demonstrates the kind of static analysis that catches real bugs before runtime — the same class of checks performed by tools like `cppcheck` and compiler warning flags like `-Wall`

The project shows not just that these phases can be implemented, but how they connect — the lexer feeds the parser, the parser builds the AST, and the semantic analyser uses the AST to reason about program correctness.

---

*Graphic Era University — Compiler Design Project*
