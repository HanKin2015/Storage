VERSION   =
CC        = gcc
DEBUG     =
CFLAGS    = -Wall
AR        = ar
ARFLAGS   = rv
SOURCES   = $(wildcard *.c)
INCLUDES  = -I.
LIB_NAMES =
LIB_PATH  =
OBJ       = $(patsubst %.c, %.o, $(SOURCES))
TARGET    = libfun_a

#link
$(TARGET):$(OBJ)
		@mkdir -p output
		$(AR) $(ARFLAGS) output/$(TARGET)$(VERSION).a $(OBJ)
		@rm -rf $(OBJ)

#compile
%.o: %.c
		$(CC) $(INCLUDES) $(DEBUG) -c $(CFLAGS) $< -o $@
  
.PHONY:clean
clean:
		@echo "Remove linked and compiled files......"
		rm -rf $(OBJ) $(TARGET) output 