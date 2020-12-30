CC = gcc
SPECK_FILES = speck/speck.c speck/speck.h
SPECK_BIN = speck/bin/speck

SHA_FILES = sha3/sha3.c sha3/sha3.h
SHA_BIN = sha3/bin/sha3

run: run_speck run_sha3

build: build_speck build_sha3
	@echo "Built all."

run_speck: build_speck ${SPECK_FILES}
	./${SPECK_BIN}
	@echo

run_sha3: build_sha3 ${SHA_FILES}
	./${SHA_BIN}
	@echo

build_speck: ${SPECK_FILES}
	@echo "Building SPECK."
	@${CC} speck/speck.c -o ${SPECK_BIN}

build_sha3: ${SHA_FILES}
	@echo "Building SHA."
	@${CC} sha3/sha3.c -o ${SHA_BIN}