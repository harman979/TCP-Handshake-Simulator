# ─────────────────────────────────────────────────────────────────────────────
#  Makefile — TCP Three-Way Handshake Simulator
#  Platform : Linux / WSL Ubuntu
#  Compiler : gcc
# ─────────────────────────────────────────────────────────────────────────────

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -Isrc
TARGET  = tcp_sim
SRCDIR  = src

# Collect every .c file inside src/
SRCS    = $(wildcard $(SRCDIR)/*.c)

# Replace src/foo.c → src/foo.o
OBJS    = $(SRCS:.c=.o)

# ── Default target ────────────────────────────────────────────────────────────
all: $(TARGET)

# ── Link ──────────────────────────────────────────────────────────────────────
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo ""
	@echo "  Build successful → ./$(TARGET)"
	@echo ""

# ── Compile each .c → .o ──────────────────────────────────────────────────────
$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# ── Run ───────────────────────────────────────────────────────────────────────
run: $(TARGET)
	./$(TARGET)

# ── Clean ─────────────────────────────────────────────────────────────────────
clean:
	rm -f $(SRCDIR)/*.o $(TARGET)
	@echo "  Cleaned build artifacts."

.PHONY: all run clean
