CC = gcc
CFLAGS = -Wall -Wextra

all: gpio_led_user

gpio_led_user: gpio_led_user.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f gpio_led_user
