GEN_SRC := Chord.cpp mp2_constants.cpp mp2_types.cpp
GEN_OBJ := $(patsubst %.cpp,%.o, $(GEN_SRC))
CXX += -DHAVE_NETINET_IN_H -g -lpthread -lm
THRIFT_DIR := /class/ece428/libs/include/thrift
BOOST_DIR := /usr/local/include
LOG4CXX_DIR := /class/ece428/libs/include

INC += -I$(THRIFT_DIR) -I$(BOOST_DIR) -I$(LOG4CXX_DIR)

LINK += -L/class/ece428/libs/lib -Wl,-rpath,/class/ece428/libs/lib

#BOOSTIP = -I/usr/local/include

.PHONY: all clean

all: node  listener

%.o: %.cpp
	$(CXX) -Wall $(INC) -c $< -o $@

node: log.o sha1.o Chord_server.o $(GEN_OBJ)
	$(CXX) $(INC) $(LINK) -llog4cxx -lthrift $^ -o $@

listener: sha1.o Chord_client.o $(GEN_OBJ)
	$(CXX) $(LINK) -lthrift $^ -o $@

sha1.o: sha1.c
	$(CXX) $(LINK) -c sha1.c

log.o: log.cpp
	$(CXX) $(INC) $(LINK) -c log.cpp

clean:
	$(RM) *.o Chord_server Chord_client
