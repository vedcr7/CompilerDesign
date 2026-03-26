# ============================================================
#  Makefile  —  Compiler Project (Phase 1 & Phase 2)
#
#  Requirements : flex, bison, gcc (any modern version)
#  Ubuntu/Debian: sudo apt install flex bison gcc
#  macOS        : brew install flex bison gcc
#  Windows      : use MSYS2/MinGW or WSL
#
#  Usage:
#    make           → builds both phases
#    make phase1    → builds lexer only
#    make phase2    → builds parser + AST only
#    make test      → runs both on sample.c
#    make clean     → removes all generated files
# ============================================================

CC      = gcc
CFLAGS  = -Wall -Wno-unused-function -g
FLEX    = flex
BISON   = bison

# ── Phase 1 ──────────────────────────────────────────────────
P1_DIR  = phase1
P1_SRC  = $(P1_DIR)/lexer.l
P1_GEN  = $(P1_DIR)/lex.yy.c
P1_BIN  = $(P1_DIR)/lexer

# ── Phase 2 ──────────────────────────────────────────────────
P2_DIR  = phase2
P2_LSRC = $(P2_DIR)/lexer.l
P2_YSRC = $(P2_DIR)/parser.y
P2_LGEN = $(P2_DIR)/lex.yy.c
P2_YGEN = $(P2_DIR)/parser.tab.c
P2_YHDR = $(P2_DIR)/parser.tab.h
P2_BIN  = $(P2_DIR)/parser

.PHONY: all phase1 phase2 test clean

all: phase1 phase2

# ── Phase 1: Lex → C → binary ────────────────────────────────
phase1: $(P1_BIN)

$(P1_GEN): $(P1_SRC)
	$(FLEX) -o $@ $<

$(P1_BIN): $(P1_GEN)
	$(CC) $(CFLAGS) -o $@ $< -lfl

# ── Phase 2: Bison + Lex → C → binary ───────────────────────
phase2: $(P2_BIN)

$(P2_YGEN) $(P2_YHDR): $(P2_YSRC)
	$(BISON) -d -o $(P2_YGEN) $<

$(P2_LGEN): $(P2_LSRC) $(P2_YHDR)
	$(FLEX) -o $@ $<

$(P2_BIN): $(P2_YGEN) $(P2_LGEN)
	$(CC) $(CFLAGS) -I$(P2_DIR) -o $@ $(P2_YGEN) $(P2_LGEN) -lfl

# ── Test both phases on sample.c ─────────────────────────────
test: all
	@echo ""
	@echo "══════════════════════════════════════════════"
	@echo "  PHASE 1 — Lexical Analysis"
	@echo "══════════════════════════════════════════════"
	./$(P1_BIN) sample.c
	@echo ""
	@echo "══════════════════════════════════════════════"
	@echo "  PHASE 2 — Parsing + AST Generation"
	@echo "══════════════════════════════════════════════"
	./$(P2_BIN) sample.c

# ── Clean ────────────────────────────────────────────────────
clean:
	rm -f $(P1_GEN) $(P1_BIN)
	rm -f $(P2_LGEN) $(P2_YGEN) $(P2_YHDR) $(P2_BIN)
	rm -f $(P2_DIR)/parser.output
