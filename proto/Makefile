PROTOC = ../tools/generator-bin/protoc --nanopb_out=.
PROTO_FILES := $(wildcard *.proto)

all: proto move

proto: $(PROTO_FILES)
	$(PROTOC) $(PROTO_FILES)

move: proto
	@echo Move
	mv *.pb.c ../src
	mv *.pb.h ../include

.PHONY: proto

