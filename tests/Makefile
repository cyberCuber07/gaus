CC      := gcc
CCFLAGS := 
LDFLAGS :=

TARGETS:= main
MAINS  := $(addsuffix .o, $(TARGETS) )
OBJ    := main.o test_gen.o $(MAINS)
DEPS   := test_gen.h

.PHONY: all clean run

all: $(TARGETS)

clean:
	rm -f $(TARGETS) $(OBJ)

run:
	./$(TARGETS)

$(OBJ): %.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGETS): % : $(filter-out $(MAINS), $(OBJ)) %.o
	$(CC) -o $@ $(LIBS) $^ $(CCFLAGS) $(LDFLAGS)

