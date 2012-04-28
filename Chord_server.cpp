// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "Chord.h"
#include <string>
#include <protocol/TBinaryProtocol.h>
#include <server/TSimpleServer.h>
#include <transport/TServerSocket.h>
#include <transport/TBufferTransports.h>
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;
using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::mp2;

class ChordHandler : virtual public ChordIf {
 public:
  ChordHandler(int m = 5, int id = -1, int port = 9090, int introducer_port = -1) {
    this->m = m;
    this->introducer_port = introducer_port;
    this->id = id;
    this->port = port;
    // Your initialization goes here
  }

  void add_node() {
    // Your implementation goes here
    printf("%d\n", this->m);
  }

  void add_file() {
    // Your implementation goes here
    printf("add_file\n");
  }

  void del_file() {
    // Your implementation goes here
    printf("del_file\n");
  }

  void get_file() {
    // Your implementation goes here
    printf("get_file\n");
  }

  void get_table() {
    // Your implementation goes here
    printf("get_table\n");
  }


  bool is_introducer(){
    return (this->introducer_port != -1);
  }

  int get_port(){
    return this->port;
  }

 private:
  int m;
  int id;
  int introducer_port;
  int port;

};

ChordHandler* init_node(int argc, char** argv){
  int id = -1;
  int port = -1;
  int m = -1;
  int introducer_port = -1;
  int num;

  for(int i=1; i<argc; i+=2){
    num = atoi(argv[i+1]);
    string arg = argv[i];
    if(arg == "--m"){
      m = num;
    }
    else if(arg == "--id"){
      id = num;
    }
    else if(arg == "--port"){
      port = num;
    }
    else if (arg== "--introducerPort"){
      introducer_port = num;
    }
  }

  if(id != 0 && introducer_port == -1){
    std::cerr << "Need to include introducer port. Shutting down now." << endl;
    exit(1);
  }

  cout << "Successfully listening" << endl;
  return (new ChordHandler(m, id, port, introducer_port));
}

int main(int argc, char **argv) {
  printf("Starting up\n");
  ChordHandler* nodeh = init_node(argc, argv);
  shared_ptr<ChordHandler> handler(nodeh);
  shared_ptr<TProcessor> processor(new ChordProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(nodeh->get_port()));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

