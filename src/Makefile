# Makefile
# Generates the ccorgi binary

# Variables
TARGETS = ccorgi

# Housekeeping
all : $(TARGETS)
clean :
	rm -f ../build/*

# Other targets
ccorgi : ccorgi.c
	gcc ccorgi.c -lncurses -o ../build/ccorgi
