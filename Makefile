GEN_SRC := Chord.cpp mp2_constants.cpp mp2_types.cpp
GEN_OBJ := $(patsubst %.cpp,%.o, $(GEN_SRC))
CXX += -DHAVE_NETINET_IN_H -g -lpthread -lm
THRIFT_DIR := /class/ece428/libs/include/thrift
BOOST_DIR := /usr/local/include

INC += -I$(THRIFT_DIR) -I$(BOOST_DIR)

LINK += -L/class/ece428/libs/lib -Wl,-rpath,/class/ece428/libs/lib

#BOOSTIP = -I/usr/local/include

.PHONY: all clean

all: node  listener

%.o: %.cpp
	$(CXX) -Wall $(INC) -c $< -o $@

node: sha1.o Chord_server.o $(GEN_OBJ)
	$(CXX) $(LINK) -lthrift $^ -o $@

listener: sha1.o Chord_client.o $(GEN_OBJ)
	$(CXX) $(LINK) -lthrift $^ -o $@

sha1.o: sha1.c
	$(CXX) $(LINK) -c sha1.c

clean:
	$(RM) *.o Chord_server Chord_client
