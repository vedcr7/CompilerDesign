# ============================================================
#  Makefile — Compiler Design Project (Phase 1-5)
#  Install : sudo apt install flex bison gcc make
#  Usage   : make              → build everything
#            make test FILE=demo2.c → test on specific file
#            make clean          → remove generated files
# ============================================================

CC    = gcc
CFLAGS = -Wall -Wno-unused-function -g
FLEX  = flex
BISON = bison
FLEXLIB = $(shell uname -s | grep -q Darwin && echo "" || echo "-lfl")
INCLUDE = -Iinclude

SRC_DIR = synthesis
BUILD_DIR = build
TEST_DIR = test

# Phase 1 targets
PHASE1 = $(BUILD_DIR)/lexer

# Phase 2-5 targets
PHASE2 = $(BUILD_DIR)/parser
LEXER_DUMP = $(BUILD_DIR)/lexer_dump

# Default test file
FILE ?= demo2.c

.PHONY: all phase1 phase2 phaseweb test test-verbose clean

all: phase1 phase2

phaseweb: phase2 $(LEXER_DUMP)

# ── Phase 1 (parser includes lexer) ──────────────────────────
phase1: phase2

# ── Phase 2 + 3 + 4 + 5 ──────────────────────────────────────
phase2: $(PHASE2)

$(BUILD_DIR)/parser.tab.c $(BUILD_DIR)/parser.tab.h: $(SRC_DIR)/parser.y
	@mkdir -p $(BUILD_DIR)
	$(BISON) -d -o $(BUILD_DIR)/parser.tab.c $<

$(BUILD_DIR)/lex.yy.c: $(SRC_DIR)/lexer.l $(BUILD_DIR)/parser.tab.h
	$(FLEX) -o $@ $<

$(PHASE2): $(BUILD_DIR)/parser.tab.c $(BUILD_DIR)/lex.yy.c $(SRC_DIR)/icg.c $(SRC_DIR)/tcg.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ \
	    $(BUILD_DIR)/parser.tab.c $(BUILD_DIR)/lex.yy.c $(SRC_DIR)/icg.c $(SRC_DIR)/tcg.c $(FLEXLIB)

$(LEXER_DUMP): $(BUILD_DIR)/parser.tab.h $(BUILD_DIR)/lex.yy.c $(SRC_DIR)/lexer_driver.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ \
	    $(SRC_DIR)/lexer_driver.c $(BUILD_DIR)/lex.yy.c $(FLEXLIB)

# ── Test ─────────────────────────────────────────────────────
test: all
	@echo ""
	@echo "============================================================"
	@echo "  RUNNING COMPILER ON: $(FILE)"
	@echo "============================================================"
	@echo ""
	@echo "PHASE 1-5 — LEXER + PARSER + AST + SEMANTIC + ICG + OPTIMIZATION"
	@echo "────────────────────────────────────────────────────────────"
	$(PHASE2) $(TEST_DIR)/$(FILE)

# ── Clean ────────────────────────────────────────────────────
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(BUILD_DIR)/parser.output

.PHONY: help
help:
	@echo ""
	@echo "Compiler Design Project — Makefile Targets"
	@echo "==========================================="
	@echo ""
	@echo "make all              — Build all phases"
	@echo "make phase1           — Build Phase 1 (Lexer) only"
	@echo "make phase2           — Build Phase 2-5 (Parser+) only"
	@echo "make test             — Run compiler on test/demo2.c"
	@echo "make test FILE=X.c    — Run compiler on test/X.c"
	@echo "make clean            — Remove build artifacts"
	@echo "make help             — Show this help message"
	@echo ""
	@echo "Example:"
	@echo "  make test FILE=demo.c"
	@echo "  make test FILE=test_trivial.c"
	@echo ""
