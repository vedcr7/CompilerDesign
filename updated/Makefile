# ============================================================
#  Makefile — Compiler Design Project (Phase 1, 2, 3)
#  Install : sudo apt install flex bison gcc make
#  Usage   : make          → build everything
#            make test     → run both phases on demo.c
#            make clean    → remove generated files
# ============================================================

CC    = gcc
CFLAGS = -Wall -Wno-unused-function -g
FLEX  = flex
BISON = bison
FLEXLIB = $(shell uname -s | grep -q Darwin && echo "" || echo "-lfl")

P1_DIR = p1
P2_DIR = p2

.PHONY: all phase1 phase2 test clean

all: phase1 phase2

# ── Phase 1 ──────────────────────────────────────────────────
phase1: $(P1_DIR)/lexer

$(P1_DIR)/lex.yy.c: $(P1_DIR)/lexer.l
	$(FLEX) -o $@ $<

$(P1_DIR)/lexer: $(P1_DIR)/lex.yy.c
	$(CC) $(CFLAGS) -o $@ $< $(FLEXLIB)

# ── Phase 2 + 3 ──────────────────────────────────────────────
phase2: $(P2_DIR)/parser

$(P2_DIR)/parser.tab.c $(P2_DIR)/parser.tab.h: $(P2_DIR)/parser.y
	$(BISON) -d -o $(P2_DIR)/parser.tab.c $<

$(P2_DIR)/lex.yy.c: $(P2_DIR)/lexer.l $(P2_DIR)/parser.tab.h
	$(FLEX) -o $@ $<

$(P2_DIR)/parser: $(P2_DIR)/parser.tab.c $(P2_DIR)/lex.yy.c $(P2_DIR)/icg.c
	$(CC) $(CFLAGS) -I$(P2_DIR) -o $@ \
	    $(P2_DIR)/parser.tab.c $(P2_DIR)/lex.yy.c $(P2_DIR)/icg.c $(FLEXLIB)

# ── Test ─────────────────────────────────────────────────────
test: all
	@echo ""
	@echo "============================================================"
	@echo "  PHASE 1 — LEXICAL ANALYSIS on demo.c"
	@echo "============================================================"
	./$(P1_DIR)/lexer $(P2_DIR)/demo.c
	@echo ""
	@echo "============================================================"
	@echo "  PHASE 2+3 — PARSER + AST + SEMANTIC ANALYSIS on demo.c"
	@echo "============================================================"
	./$(P2_DIR)/parser $(P2_DIR)/demo.c

# ── Clean ────────────────────────────────────────────────────
clean:
	rm -f $(P1_DIR)/lex.yy.c $(P1_DIR)/lexer
	rm -f $(P2_DIR)/lex.yy.c $(P2_DIR)/parser.tab.c \
	      $(P2_DIR)/parser.tab.h $(P2_DIR)/parser \
	      $(P2_DIR)/parser.output
