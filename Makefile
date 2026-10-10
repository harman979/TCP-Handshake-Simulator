# ─────────────────────────────────────────────────────────────────────────────
#  Makefile — TCP Three-Way Handshake Simulator (Pure C)
#  Platform : Linux / WSL Ubuntu / Windows (MinGW)
#  Compiler : gcc
# ─────────────────────────────────────────────────────────────────────────────

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -Isrc
TARGET  = tcp_sim
TESTBIN = test_unit
SRCDIR  = src
TESTDIR = tests

# Simulator source and object files
SRCS    = $(wildcard $(SRCDIR)/*.c)
OBJS    = $(SRCS:.c=.o)

# OS-specific settings for clean and executable extensions
ifeq ($(OS),Windows_NT)
    EXE_EXT     = .exe
    RM_OBJS     = if exist src\*.o del /Q /F src\*.o
    RM_TARGET   = if exist $(TARGET) del /Q /F $(TARGET) & if exist $(TARGET).exe del /Q /F $(TARGET).exe
    RM_TEST_BIN = if exist $(TESTBIN) del /Q /F $(TESTBIN) & if exist $(TESTBIN).exe del /Q /F $(TESTBIN).exe
else
    EXE_EXT     =
    RM_OBJS     = rm -f $(SRCDIR)/*.o
    RM_TARGET   = rm -f $(TARGET)
    RM_TEST_BIN = rm -f $(TESTBIN) $(TESTBIN).exe
endif

# ── Default target: Build simulator executable ────────────────────────────────
all: $(TARGET)

# ── Link simulator ────────────────────────────────────────────────────────────
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo ""
	@echo "  Build successful -> ./$(TARGET)$(EXE_EXT)"
	@echo ""

# ── Compile each .c -> .o ──────────────────────────────────────────────────────
$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# ── Run Interactive Simulator ─────────────────────────────────────────────────
run: $(TARGET)
	./$(TARGET)$(EXE_EXT)

# ── Build & Run C Test Suite ──────────────────────────────────────────────────
test: $(TESTBIN)
	@echo ""
	@echo "==> Running C Test Suite..."
	./$(TESTBIN)$(EXE_EXT)

$(TESTBIN): $(SRCDIR)/tcp_state.c $(SRCDIR)/message.c $(TESTDIR)/test_unit.c
	$(CC) $(CFLAGS) $(SRCDIR)/tcp_state.c $(SRCDIR)/message.c $(TESTDIR)/test_unit.c -o $(TESTBIN)$(EXE_EXT)

# ── Clean Build Artifacts ─────────────────────────────────────────────────────
clean:
	@$(RM_OBJS)
	@$(RM_TARGET)
	@$(RM_TEST_BIN)
	@echo "  Cleaned build artifacts."

.PHONY: all run test clean
