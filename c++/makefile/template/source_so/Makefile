VERSION   =
CC        = gcc
DEBUG     =
CFLAGS    = -fPIC -shared 
LFLAGS    = -fPIC -shared 
SOURCES   = $(wildcard *.c)
INCLUDES  = -I.
LIB_NAMES =
LIB_PATH  =
OBJ       = $(patsubst %.c, %.o, $(SOURCES))
TARGET    = libfun_so

#link
$(TARGET):$(OBJ)
		@mkdir -p output
		$(CC) $(OBJ) $(LIB_PATH) $(LIB_NAMES) $(LFLAGS) -o output/$(TARGET)$(VERSION).so
		@rm -rf $(OBJ)
 
#compile
%.o: %.c
		$(CC) $(INCLUDES) $(DEBUG) -c $(CFLAGS) $< -o $@

.PHONY:clean
clean:
		@echo "Remove linked and compiled files......"
		rm -rf $(OBJ) $(TARGET) output 