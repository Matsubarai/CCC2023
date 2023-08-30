
CXX 	   := g++
TARGETS    := generate_data sticker
SRC_FILES  := $(addsuffix .cpp, $(TARGETS))

all: $(TARGETS)
	./generate_data

$(TARGETS): $(SRC_FILES)
	@g++ -o $@ $@.cpp

clean: 
	rm ./*.txt; \
	rm $(TARGETS)

