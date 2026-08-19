MAKEFLAGS += -r

CC := gcc
CFLAGS = -Iinclude -Wall -Wextra -I./iup/include $(shell pkg-config --cflags gtk+-3.0)
LDFLAGS = -L./iup -Wl,-rpath=./iup
LDLIBS = -liup $(shell pkg-config --libs gtk+-3.0) -lX11 -lm

SRC := $(shell find . -name "*.c")
OBJS := $(patsubst %.c,%.o,$(SRC))

# test:
# 	echo $(SRC)
# 	echo $(OBJS)

app: $(OBJS)
	$(CC) $(OBJS) -o $(@) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

%.o:%.c
	$(CC) $(CFLAGS) -c $(<) -o $(@)

clean:
	rm -rf $(OBJS)
	rm app