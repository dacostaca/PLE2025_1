# Makefile actualizado
CC = gcc
CFLAGS = -Wall -O2 -pthread
LDFLAGS = -ljpeg
TARGET = bin/motion_detector
TEST_TARGET = bin/motion_test

SRC_CORE = core/motion_engine.c core/capture.c core/gpio.c core/utils.c
SRC_APP = app/app.c app/main.c
SRC_TEST = tests/test_motion.c

INCLUDES = -Icore

.PHONY: all clean

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(SRC_CORE) $(SRC_APP)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)

$(TEST_TARGET): $(SRC_TEST) core/motion_engine.c core/utils.c core/capture.c
	@mkdir -p bin
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)

clean:
	rm -f bin/*
