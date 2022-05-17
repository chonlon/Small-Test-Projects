export LD_PRELOAD=/usr/lib/faketime/libfaketime.so.1 
export FAKETIME=-1y

build:
	ninja

run:
	./converter ${ARGS}

all: build run

.DEFAULT_GOAL := all
