// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "Node.h"
#include "Chord.h"
#include "sha1.h"
#include "Chord_Listener.h"
#include <string>
#include <protocol/TBinaryProtocol.h>
#include <server/TSimpleServer.h>
#include <transport/TServerSocket.h>
#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <utility>
#include <boost/thread.hpp>

#define ME NULL
#define SUCCESSOR 0
#define NO_PREDECESSOR -1

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
    this->predecessor = -1;
    //first element in table = successor
    this->finger_table = new vector<Node*>(m, NULL);
    int pow = 1;
    pow <<= m;
    this->pow = pow;

    if(id != 0){
      shared_ptr<TSocket> socket(new TSocket("localhost", introducer_port));
      shared_ptr<TTransport> transport(new TBufferedTransport(socket));
      shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
      this->introducer = new ChordClient(protocol);
      transport->open();
      successor returned;
      this->introducer->join_network(returned, this->id);
      printf("Introducer told me that my successor is %d on port %d\n", returned.id,
          returned.port);
      transport->close();
      this->set_succ(returned.id, returned.port);
    }
    else{
      this->introducer = NULL;
    }


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

  void notify(const int32_t pid) {
    printf("Process %d claims to be my predecessor.\n", pid);
    if(this->predecessor == NO_PREDECESSOR || in_range(predecessor, this->id, pid)){
      predecessor = pid;
      printf("Changing my predecessor to %d\n", predecessor);
    }
    else{
      printf("No change to predecessor\n");
    }
  }

  //tell the introducer that we are joining
  //we can assume that add_node won't be called with an id that has alreayd 
  //been used
  void join_network(successor& _return, const int32_t pid){
    printf("Node %d just connected.\n", pid);
    this->find_successor(_return, pid);
  }

  void find_successor(successor& _return, const int32_t pid) {
    // Your implementation goes here
    printf("%d is trying to find %d's successor\n", this->id, pid);
    neighbor returned;
    this->find_predecessor(returned, pid);
    _return.id = returned.succ_id;
    _return.port = returned.succ_port;
  }

  //this function isn't necessary right now, but we'll keep it
  //so that the code is consistent with the white paper
  void find_predecessor(neighbor& _return, const int32_t pid) {
    // Your implementation goes here
    printf("%d is trying to find %d's predecessor\n", this->id, pid);
    this->closest_preceding_finger(_return, pid);
  }

  bool in_range(int start, int end, int test){
    return ((test > start) && (test < this->pow)) || ((test < end) && (test > 0));
  }

  void closest_preceding_finger(neighbor& _return, const int32_t pid){
    printf("%d is trying to find %d's closest preceding finger\n", this->id, pid);
    int i = this->m;
    Node* entry;
    while(--i){
      entry = this->finger_table->at(i);
      if(entry == NULL) continue;
      if(this->in_range(this->id, pid, entry->id)){
        //pass to next node
        entry->connection->closest_preceding_finger(_return, pid);
        return;
      }
    }
    //current node is closest
    _return.id = this->get_id();
    _return.port = this->get_port();
    Node* curr = this->finger_table->at(SUCCESSOR);
    //case for first node - this node is its own successor
    if(curr == NULL){
      _return.succ_id = this->get_id();
      _return.succ_port = this->get_port();
    }
    else{
      _return.succ_id = curr->id;
      _return.succ_port = curr->port;
    }
  }

  void get_info(neighbor& _return){

  }

  //class functions
  bool is_introducer(){
    return (this->introducer_port != -1);
  } 
  int get_port(){
    return this->port;
  }

  int get_id(){
    return this->id;
  }

  //we'll make this just return the first element in our finger table
  int get_succ(){
    return 0;
  }
  
  //manage connection here?
  void set_succ(int id, int port){
    Node* curr = this->finger_table->at(0);
    //no successor - either new node or the only node in the system!
    if(curr == NULL){
      printf("making new node that points to %d::%d\n", id, port);
      (*(this->finger_table))[0] = new Node(id, port);
    }
    else{
      //only do this stuff if it's a new node!
      if(curr->id != id){
        delete curr;
        (*(this->finger_table))[0] = new Node(id, port);
      }
    }

    printf("Telling %d that it is my successor\n", id);
    curr = this->finger_table->at(0);
    curr->notify(this->id);
  }

  int get_pred(){
    return this->predecessor;
  }

  void* test_func(void* input){

  }

  void go(){
    pthread_t test;

  }

  void set_pred(int port){
    this->predecessor = port;
  }

  void stabilize(){
    sleep(1);
    printf("Boom\n");

  }

  ChordClient* introducer;
  vector<Node*>* finger_table;
  int pow;

  //verify current node's successor

 private:
  int m;
  int id;
  int introducer_port;
  int port;
  int predecessor;
  pthread_t mthread;

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
  ChordHandler* nodeh = init_node(argc, argv);
  shared_ptr<ChordHandler> handler(nodeh);
  shared_ptr<TProcessor> processor(new ChordProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(nodeh->get_port()));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  printf("Starting session on port %d\n", nodeh->get_port());

  //spawn thread to take care of stabilization stuff
  
  server.serve();
  return 0;
}

