SRCS = types.c \
       git.c \
       menu.c \
       log.c \
       main.c
TARGET = cnsc
CFLAGS = -Wall -O3
LDFLAGS =

OBJ = $(SRCS:.c=.o)

all: $(TARGET)

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: all clean
