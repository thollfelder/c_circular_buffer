IDIR =../src

CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = queue.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = robust_queue.o queue.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 



# Defining constants
#CC=gcc
#INC_DIR = src
#SRC_DIR = test/robustness
#OBJ_DIR = obj
#CFLAGS  = -c -Wall -I.
#SRCS = $(SRC_DIR)/test_queue.c 
#OBJS = $(OBJ_DIR)/test_queue.o
# Note: The above will soon get unwieldy.
# The wildcard and patsubt commands will come to your rescue.
#DEPS = $(INC_DIR)/queue.h
# Note: The above will soon get unwieldy.
# You will soon want to use an automatic dependency generator.
#all: $(OBJS)
#
#$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
#	$(CC) $(CFLAGS) -c $< -o $@
#
#$(OBJ_DIR)/Trace.o: $(DEPS)