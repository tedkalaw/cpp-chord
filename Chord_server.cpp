// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "Node.h"
#include "Chord.h"
#include "sha1.h"
#include "Chord_Listener.h"
#include <string>
#include <protocol/TBinaryProtocol.h>
#include <server/TSimpleServer.h>
#include <server/TThreadedServer.h>
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
int _x;
bool debugging = false;;


class ChordHandler : virtual public ChordIf {
 public:
  ChordHandler(int m = 5, int id = -1, int port = 9090, int introducer_port = -1,
      int s_interval = 2, int f_interval = 1) {
    _x = 0;
    this->m = m;
    this->introducer_port = introducer_port;
    this->id = id;
    this->port = port;
    this->pred.id = id;
    this->pred.port = -1;
    this->stabilize_interval = s_interval;
    this->fix_interval = f_interval;
    //first element in table = successor
    this->finger_table = new vector<Node*>(m, NULL);
    int pow = 1;
    pow <<= m;
    this->pow = pow;
    this->gen_start_values();

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

    pthread_mutex_init(&m_mutex, NULL);
    pthread_mutex_init(&transport_mutex, NULL);
    this->start();
  }

  void add_node() {
    // Your implementation goes here
    printf("RPC\n");
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

  void current_pred(predecessor& _return){
    printf("Telling someone that my pred's id is %d\n", pred.id);
    _return.id = this->pred.id;
    _return.port = this->pred.port;
  }

  void notify(const int32_t pid, const int32_t new_port) {
    ////printf("Process %d claims to be my predecessor.\n", pid);
    if(pid != this->id && (pred.id == this->id || in_range(pred.id, this->id, pid))){
    printf("I am %d and %d is trying to be my predecessor\n", this->id, pid);
      if(pred.id != pid){
        pred.id = pid;
    printf("Pred.port is changing from %d to %d\n", pred.port, new_port);
        pred.port = new_port;
        printf("Changing my predecessor to %d\n", pred.id);
      }
    }
    else{
      printf("No change to predecessor\n");
    }
  }

  //tell the introducer that we are joining
  //we can assume that add_node won't be called with an id that has alreayd 
  //been used
  void join_network(successor& _return, const int32_t pid){
    printf("*************\n");
    printf("*************\n");
    printf("Node %d just connected.\n", pid);
    printf("*************\n");
    printf("*************\n");
    this->find_successor(_return, pid);
  }

  void find_successor(successor& _return, const int32_t pid) {
    printf("%d is trying to find %d's successor\n", this->id, pid);
    neighbor returned;
    this->find_predecessor(returned, pid);
    _return.id = returned.succ_id;
    _return.port = returned.succ_port;
  }

  //this function isn't necessary right now, but we'll keep it
  //so that the code is consistent with the white paper
  void find_predecessor(neighbor& _return, const int32_t pid) {
    printf("%d is trying to find %d's predecessor\n", this->id, pid);
    this->closest_preceding_finger(_return, pid);
  }

  bool in_range(int left, int right, int t){
    bool returned;
    if(left > right){
      if(t >= left){
        return (t == left) || (t <= pow);
      }
      else if (t <= right){
        return (t==right) || (t>= 0);
      }
    }
    else{
      returned = (t >= left) && (t <= right);
    }

    printf("%d: Checking if %d is on (%d, %d): %d\n", _x, t, left, right, returned);
    _x++;
    return returned;
  }

  void closest_preceding_finger(neighbor& _return, const int32_t pid){
    int i = this->m-1;
    Node* entry;
    printf("In closest preceding finger\n");
    while(i>=0){
      entry = this->finger_table->at(i);
      if(entry == NULL && pid == this->id) break;
      if(entry != NULL && (this->in_range(this->id, pid, entry->id))){
        //pass to next node
        pthread_mutex_lock(&transport_mutex);
        entry->open_connection();
        entry->connection->closest_preceding_finger(_return, pid);
        entry->close_connection();
        pthread_mutex_unlock(&transport_mutex);
        return;
      }
      i--;
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
  
  void set_finger(int new_id, int new_port, int i){
    pthread_mutex_lock(&m_mutex);
    Node* curr = this->finger_table->at(i);
    if(curr != NULL){
      printf("Old value: %d\n", curr->id);
      if(curr->id == new_id){
        pthread_mutex_unlock(&m_mutex);
        return;
      }
      else
        delete curr;
    }
    if(new_id == this->id){
      printf("My id\n");
      (*(this->finger_table))[i] = NULL;
    }
    else{
      printf("Changing");
      (*(this->finger_table))[i] = new Node(new_id, new_port);
    }

    pthread_mutex_unlock(&m_mutex);
  }


  //manage connection here?
  void set_succ(int id, int port){
    pthread_mutex_lock(&m_mutex);
    Node* curr = this->finger_table->at(0);
    //no successor - either new node or the only node in the system!
    if(curr == NULL){
      //printf("making new node that points to %d::%d\n", id, port);
      (*(this->finger_table))[0] = new Node(id, port);
    }
    else{
      //only do this stuff if it's a new node!
      if(curr->id != id){
        delete curr;
        (*(this->finger_table))[0] = new Node(id, port);

        //printf("Telling %d that it is my successor\n", id);
        curr = this->finger_table->at(0);
        pthread_mutex_lock(&transport_mutex);
        curr->notify(this->id, this->port);
        pthread_mutex_lock(&transport_mutex);
      }
    }
    pthread_mutex_unlock(&m_mutex);
  }


  void start(){
    pthread_create(&stabilize_thread, NULL, start_stabilize, this);
    pthread_create(&fix_thread, NULL, start_fix, this);
  }

  ChordClient* introducer;
  vector<Node*>* finger_table;
  int pow;
  predecessor pred;

  //verify current node's successor
  //
  void gen_start_values(){
    start_values = new vector<int>(m+1, this->id);
    for(int i=0; i<=m; i++){
      (*(start_values))[i] = (this->id + (1 << (i))) % pow;
    }
  }

  vector<int>* atomic_get_finger_table(){
    pthread_mutex_lock(&m_mutex);
    pthread_mutex_unlock(&m_mutex);
  }

  vector<int>* atomic_write_finger_table(int i){

  }

  Node* atomic_get_node(int i){
    Node* returned;
    pthread_mutex_lock(&m_mutex);
    returned = this->finger_table->at(i);
    pthread_mutex_unlock(&m_mutex);
    return returned;
  }


 private:
  int m;
  int id;
  int introducer_port;
  int port;
  int stabilize_interval;
  int fix_interval;
  pthread_t stabilize_thread;
  pthread_t fix_thread;
  pthread_mutex_t m_mutex;
  pthread_mutex_t transport_mutex;
  vector<int>* start_values;

  void stabilize(){
    Node* successor;
    predecessor next;
    while(true){
      sleep(this->stabilize_interval);
      printf("My predecessor: %d\n", this->pred.id);
      successor = atomic_get_node(SUCCESSOR);
      if(successor != NULL){
        printf("Successor's id: %d\n", successor->id);
        pthread_mutex_lock(&transport_mutex);
        successor->current_pred(next);
        pthread_mutex_unlock(&transport_mutex);
        //if our successor has no predecessor
        if(next.id != this->id && in_range(this->id, successor->id, next.id)){
          this->set_succ(next.id, next.port);
          successor = this->finger_table->at(SUCCESSOR);
        }
        //printf("about to notify my successor from stab; %d::%d\n", successor->id, this->id);
        pthread_mutex_lock(&transport_mutex);
        successor->notify(this->id, this->port);
        pthread_mutex_unlock(&transport_mutex);
      }
      else{
        //printf("Successor is empty\n");
        if(pred.id != this->id){
          //printf("Pred: %d::%d\n", pred.id, pred.port);
          this->set_succ(pred.id, pred.port);
        }
      }
    }
  }

  void print_fingers(){
    printf("**** Fingers ****\n");
    Node* curr;
    for(int i=0; i<m; i++){
      curr = this->finger_table->at(i);
      if(curr != NULL)
        printf("%d -> %d\n", i, curr->id);
      else
        printf("%d -> SELF\n", i);
    }
    printf("*****************\n");

  }

  void fix_fingers(){
    successor next;
    srand(time(NULL));
    int pick, curr_start;
    while(true){
      sleep(this->fix_interval);
      pick = rand() % (m-1) + 1;
      printf("Fixing fingers by looking at %dth start\n", pick);
      curr_start = this->start_values->at(pick);
      printf("Start value at %d = %d\n", pick, curr_start);
      find_successor(next, curr_start);
      printf("New finger is id: %d, port: %d at %d\n", next.id, next.port, pick);
      set_finger(next.id, next.port, pick);
      //print_fingers();
    }
  }

  static void* start_stabilize(void* arg) {
    ChordHandler* h = reinterpret_cast<ChordHandler*>(arg);
    h->stabilize();
    pthread_exit(0);
  }

  static void* start_fix(void* arg){
    ChordHandler* h = reinterpret_cast<ChordHandler*>(arg);
    h->fix_fingers();
    pthread_exit(0);
  }

};

ChordHandler* init_node(int argc, char** argv){
  int id = -1;
  int port = -1;
  int m = -1;
  int introducer_port = -1;
  int num;
  int stabilize_interval = 2;
  int fix_interval = 1;

  cout << argc << endl;
  for(int i=0; i<argc; i++){
    printf("%s\n", argv[i]);
  }

  for(int i=1; i<argc; i+=2){
    num = atoi(argv[i+1]);
    string arg = argv[i];
    if(arg == "--m"){
      printf("M: %d\n", num);
      m = num;
    }
    else if(arg == "--id"){
      printf("My id: %d\n", num);
      id = num;
    }
    else if(arg == "--port"){
      printf("My port: %d\n", num);
      port = num;
    }
    else if (arg== "--introducerPort"){
      printf("Intro port: %d\n", num);
      introducer_port = num;
    }
    else if (arg == "--stabilizeInterval"){
      printf("Stab interval: %d\n", num);
      stabilize_interval = num;
    }
  }

  if(id != 0 && introducer_port == -1){
    std::cerr << "Need to include introducer port. Shutting down now." << endl;
    exit(1);
  }

  cout << "Successfully listening" << endl;
  return (new ChordHandler(m, id, port, introducer_port, stabilize_interval, fix_interval));
}

int main(int argc, char **argv) {
  cout << "HI MANG\n" << endl;;
  ChordHandler* nodeh = init_node(argc, argv);
  shared_ptr<ChordHandler> handler(nodeh);
  shared_ptr<TProcessor> processor(new ChordProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(nodeh->get_port()));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TThreadedServer server(processor, serverTransport, transportFactory, protocolFactory);
  printf("Starting session on port %d\n", nodeh->get_port());

  //spawn thread to take care of stabilization stuff
  
  server.serve();
  return 0;
}
