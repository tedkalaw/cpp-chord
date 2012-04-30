// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "Node.h"
#include "Chord.h"
#include <math.h>
#include "sha1.h"
#include "log.hpp"
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
#include <utility>
#include <map>
#include <utility>
#include <boost/thread.hpp>

#define ME NULL
#define SUCCESSOR 0
#define NO_PREDECESSOR -1


// create a static logger, local to the current function, named with
// the function's name
#define INIT_LOCAL_LOGGER() \
    static log4cxx::LoggerPtr _local_logger = g_logger->getLogger(__func__)

// log using the current function's local logger (created by
// INIT_LOCAL_LOGGER)
#define LOGDEBUG(x) LOG4CXX_DEBUG(_local_logger, x)
#define LOGINFO(x) LOG4CXX_INFO(_local_logger, x)

using namespace std;
using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::mp2;

bool _debug = false;

void enter(int x, char* p){
  if(_debug)
    printf("%d entering %s\n", x, p);
}

void leave(int x, char* p){
  if(_debug)
    printf("%d leaving %s\n", x, p);
}
int seed;
/*
 *Constructor for the chord handler; resposnible for many of the functions of the server.
 *If this process is NOT the introducer, then it will connect to the introducer and ask it
 * for it's successor
 */
class ChordHandler : virtual public ChordIf {
 public:
  ChordHandler(int m = 5, int id = -1, int port = 9090, int introducer_port = -1,
      int s_interval = 2, int f_interval = 1) {
    this->m = m;
    this->introducer_port = introducer_port;
    this->id = id;
    this->port = port;
    this->pred.id = id;
    this->pred.port = port;
    this->stabilize_interval = s_interval;
    this->fix_interval = f_interval;
    //first element in table = successor
    this->finger_table = new vector<Node*>(m, NULL);
    int power = 1;
    power <<= m;
    this->power = power;
    this->gen_start_values();

    printf("constructor called with id: %d, port: %d, introducer: %d\n", id, port, introducer_port);

    /*
     *Asking for successor
     */
    if(id != 0){
      shared_ptr<TSocket> socket(new TSocket("localhost", introducer_port));
      shared_ptr<TTransport> transport(new TBufferedTransport(socket));
      shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
      this->introducer = new ChordClient(protocol);
      transport->open();
      successor returned;
      this->introducer->join_network(returned, this->id);
      transport->close();
      this->set_succ(returned.id, returned.port);
    }
    else{
      this->introducer = NULL;
    }

    pthread_mutex_init(&transport_mutex, NULL);
    this->start();
  }

  /*
   *Grab file data from a given node
   *Returns a populated key_and_node struct
   */
  void snatch_file(key_and_node& _return, const int32_t key){
    map<int, pair<string, string> >::iterator it = data_table.find(key);
    _return.key = key;
    _return.node_id = this->id;
    if(it == data_table.end()){
      _return.success = false;
    }
    else{
      _return.data = data_table[key].first;
      _return.success = true;
    }
  }

  /*
   *Generates the key table for a given node, and stores this string
   * _return
   */
  void gen_key_table(string& _return){
    stringstream s;
    map<int, pair<string, string> >::iterator it = data_table.begin();
    s << "keys table: \n";
    for(; it != data_table.end(); ++it){
      using std::setw;

      s<<"entry: k= " << setw(4) << it->first
        <<",  fname= " << setw(10) << (it->second).first
        <<",  fdata= " << (it->second).second
        << "\n";
    }
    _return = s.str();
  }

  /*
   * Generates the key table and finger table for a given pid. If the requested pid 
   * is equal to our own, we simply check it ourselves. Otherwise, we calculate
   * them and store them in _return.
   */
  void get_tables(string& _return, int32_t pid){
    string finger;
    string key;
    if(pid == this->id){
      gen_finger_table(finger);
      gen_key_table(key);
    }
    else{
      get_key_table(key, pid);
      get_finger_table(finger, pid);
    }
    _return = finger + key;
  }

  /*
   * Generates key table for a given pid. Same as above.
   */
  void get_key_table(string& _return, int32_t pid){
    successor next;
    find_successor(next, pid - 1);
    Node* temp = new Node(next.id, next.port);
    pthread_mutex_lock(&transport_mutex);
    temp->open_connection();
    temp->connection->gen_key_table(_return);
    temp->close_connection();
    pthread_mutex_unlock(&transport_mutex);
    delete temp;
  }

  /*
   *  Generates finger table for a given node and stores it 
   *  in _return. Creates formatted string.
   */
  void gen_finger_table(string& _return){
    stringstream s;
    for(int i=1; i <= this->m; i++){
      s << "entry: i= " << setw(2) << i << ", interval=["
        << setw(4) << calc_start(i)
        << ",  "
        << setw(4) << calc_start(i+1)
        << "),  node= "
        << setw(4) ;
        if(this->finger_table->at(i-1) != NULL)
          s << this->finger_table->at(i-1)->id;
        else
          s << this->id;
        s << "\n";

    }
    _return = s.str();
  }

  /*
   * Grabs finger table for a given pid and stores it in _return. 
   * Does not do the computation - is meant to be used as an RPC call.
   */
  void get_finger_table(string& _return, int32_t pid){
    successor next;
    find_successor(next, pid - 1);
    Node* temp = new Node(next.id, next.port);
    enter(this->id, "gft");
    pthread_mutex_lock(&transport_mutex);
    temp->open_connection();
    temp->connection->gen_finger_table(_return);
    temp->close_connection();
    pthread_mutex_unlock(&transport_mutex);
    enter(this->id, "gft");
    delete temp;
  }


  void add_node() {
    // Your implementation goes here
  }


  /*
   *
   *Adds file to the system. If the current node is the only node in the system
   *then we go ahead and store it there. 
   *
   */
  void add_file(key_and_node& _return, const std::string& filename, const std::string& data) {
    int key = generate_sha1(filename);
    //if we're the only node in the system,
    if(this->finger_table->at(SUCCESSOR) == NULL){
      data_table[key] = pair<string, string>(data, filename);
      _return.node_id = this->id;
    }
    else{
      successor succ;
      find_successor(succ, key);
      if(succ.id == this->id){
        data_table[key] = pair<string, string>(data, filename);
        _return.node_id = this->id;
      }
      else{
        Node* temp = new Node(succ.id, succ.port);
        pthread_mutex_lock(&transport_mutex);
        temp->open_connection();
        temp->connection->transfer_file(key, data, filename);
        temp->close_connection();
        pthread_mutex_unlock(&transport_mutex);
        _return.node_id = succ.id;
        delete temp;
      }
    }
    _return.key = key;
  }


  /*
   * Deletes files from the system. Searches for the file. Stores results in a key_and_node struct,
   * and if it doesn't exist, the success field is false.
   */
  void del_file(key_and_node& _return, const std::string& filename) {
    int key = generate_sha1(filename);
    map<int, pair<string, string> >::iterator it = data_table.find(key);
    if(it != data_table.end()){
      //success
      if(this->finger_table->at(SUCCESSOR) == NULL){
        data_table.erase(it);
        _return.key = key;
        _return.node_id = this->id;
        _return.success = true;
      }
      else{
        if(this->finger_table->at(SUCCESSOR) == NULL){
          _return.key = key;
          _return.node_id = this->id;
          _return.success = false;
        }
      }
    }
    else{
      successor succ;
      find_successor(succ, key);
      if(succ.id == this->id){
        remove_file(_return, key);
      }
      else{
      Node* temp = new Node(succ.id, succ.port);
      pthread_mutex_lock(&transport_mutex);
      temp->open_connection();
      temp->connection->remove_file(_return, key);
      temp->close_connection();
      pthread_mutex_unlock(&transport_mutex);
      }
    }
  }

  /*
   *Removes file from a given node; meant to be used as an RPC call.
   * Stores results in a key_and_node struct.
   */
  void remove_file(key_and_node& _return, const int32_t key){
    map<int, pair<string, string> >::iterator it = data_table.find(key);
    _return.key = key;
    _return.node_id = this->id;
    if(it == data_table.end()){
      _return.success = false;
    }
    else{
      data_table.erase(it);
      _return.success = true;
    }
  }

  /*
   * Gets file that corresponds to a given filename. Hashes it to SHA1 and
   * find the node that it belongs to.
   */
  void get_file(key_and_node& _return, const string& filename){
    int key = generate_sha1(filename);
    map<int, pair<string, string> >::iterator it;
    if(this->finger_table->at(SUCCESSOR) == NULL){
      it = data_table.find(key);
      if(it != data_table.end()){
        _return.data = data_table[key].first;
        _return.key = key;
        _return.node_id = this->id;
        _return.success = true;
      }
      else{
        _return.key = key;
        _return.node_id = this->id;
        _return.success = false;
      }
    }
    else{
      successor succ;
      find_successor(succ, key);
      if(succ.id == this->id){
        snatch_file(_return, key);
      }
      Node* temp = new Node(succ.id, succ.port);
      pthread_mutex_lock(&transport_mutex);
      temp->open_connection();
      temp->connection->snatch_file(_return, key);
      temp->close_connection();
      pthread_mutex_unlock(&transport_mutex);
    }
  }

  /*
   * Transfers file to the node called with it. Used as an RPC call. Also used in
   * notify to migrate keys.
   */
  void transfer_file(const int32_t key, const string& data, const string& filename) {
    data_table[key] = pair<string, string>(data, filename);
  }

  void get_table() {
    // Your implementation goes here
  }

  /*
   * Returns predecessor of the current node.
   */
  void current_pred(predecessor& _return){
    _return.id = this->pred.id;
    _return.port = this->pred.port;
  }

  /*
   * Tells node that node pid at port new_port believes it is its successor.
   * If its the case, this node will try to transfer keys.
   */
  void notify(const int32_t pid, const int32_t new_port) {
    if(pid != this->id && (pred.id == this->id || in_range(pred.id, this->id, pid))){
      if(pred.id != pid){
        pred.id = pid;
        pred.port = new_port;
        Node* new_node = new Node(pid, new_port);
        int val;

        map<int, pair<string, string> >::iterator it;
        for(it = data_table.begin(); it != data_table.end(); ++it){
          val = it->first;
          if(val <= pid){
            enter(this->id, "notify");
            pthread_mutex_lock(&transport_mutex);
            new_node->open_connection();
            pair<string, string> _data = it->second;
            new_node->connection->transfer_file(val, _data.first, _data.second);
            new_node->close_connection();
            pthread_mutex_unlock(&transport_mutex);
            leave(this->id, "notify");
            data_table.erase(it);
          }
        }
      }
    }
  }

  //tell the introducer that we are joining
  //we can assume that add_node won't be called with an id that has alreayd 
  //been used
  void join_network(successor& _return, const int32_t pid){
    printf("%d reporting for duty\n", pid);
    this->find_successor(_return, pid);
  }

  void get_successor(successor& _return){
    _return.id = this->finger_table->at(0)->id;
    _return.port = this->finger_table->at(0)->port;
  }
  void find_successor(successor& _return, const int32_t pid) {
    neighbor returned;
    this->find_predecessor(returned, pid);
    _return.id = returned.succ_id;
    _return.port = returned.succ_port;
  }

  //this function isn't necessary right now, but we'll keep it
  //so that the code is consistent with the white paper
  void find_predecessor(neighbor& _return, const int32_t pid) {
    Node* cur;
    _return.id = this->id;
    _return.port = this->port;
    if(this->finger_table->at(0) != NULL){
    _return.succ_id = this->finger_table->at(0)->id;
    _return.succ_port = this->finger_table->at(0)->port;
    }
    else{
      _return.succ_id = this->id;
      _return.succ_port = this->port;
    }
    while(!in_range(_return.id, _return.succ_id, pid)){
      if(_return.id != this->id){
        cur = new Node(_return.id, _return.port);
        enter(this->id, "find_p");
        pthread_mutex_lock(&transport_mutex);
        cur->open_connection();
        cur->connection->closest_preceding_finger(_return, pid);
        cur->close_connection();
        pthread_mutex_unlock(&transport_mutex);
        leave(this->id, "find_p");
      }
      else{
        closest_preceding_finger(_return, pid);
      }
    }
  }

  /*
   * Function to check if a number is between two numbers on an arc.
   * This function is used extensively in the paper.
   */
  bool in_range(int left, int right, int t){
    bool returned;
    if(left > right){
      if(t >= left){
        return (t == left) || (t <= power);
      }
      else if (t <= right){
        return (t==right) || (t>= 0);
      }
    }
    else{
      returned = (t >= left) && (t <= right);
    }
    if(left == right) returned = true;

    return returned;
  }

  void closest_preceding_finger(neighbor& _return, const int32_t pid){
    int i = this->m-1;
    Node* entry;
    while(i>=0){
      entry = this->finger_table->at(i);
      if(entry == NULL && pid == this->id) break;
      if(entry != NULL && (this->in_range(this->id, pid, entry->id))){
        _return.id = entry->id;
        _return.port = entry->port;
        successor succ;
        enter(this->id, "cpf");
        pthread_mutex_lock(&transport_mutex);
        entry->open_connection();
        entry->connection->get_successor(succ);
        entry->close_connection();
        pthread_mutex_unlock(&transport_mutex);
        leave(this->id, "cpf");
        _return.succ_id = succ.id;
        _return.succ_port = succ.port;
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

  //class functions
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
  
  /*
   * Set's current node's ith finger to be id new_id Set's current node's ith finger to be id new_id
   */
  void set_finger(int new_id, int new_port, int i){
    pthread_mutex_lock(&transport_mutex);
    Node* curr = this->finger_table->at(i);
    if(curr != NULL){
      if(curr->id == new_id){
        pthread_mutex_unlock(&transport_mutex);
        return;
      }
      else{

      }
    }
    if(new_id == this->id){
      (*(this->finger_table))[i] = NULL;
    }
    else{
      (*(this->finger_table))[i] = new Node(new_id, new_port);
    }

    pthread_mutex_unlock(&transport_mutex);
  }


  //manage connection here?
  void set_succ(int id, int port){
    Node* curr = this->finger_table->at(0);
    //no successor - either new node or the only node in the system!
    if(curr == NULL){
      pthread_mutex_lock(&transport_mutex);
      (*(this->finger_table))[0] = new Node(id, port);
      pthread_mutex_unlock(&transport_mutex);
    }
    else{
      //only do this stuff if it's a new node!
      if(curr->id != id){
        pthread_mutex_lock(&transport_mutex);
        (*(this->finger_table))[0] = new Node(id, port);
        pthread_mutex_unlock(&transport_mutex);

        curr = this->finger_table->at(0);
        pthread_mutex_lock(&transport_mutex);
        curr->notify(this->id, this->port);
        pthread_mutex_unlock(&transport_mutex);
      }
    }
  }


  void start(){
    pthread_create(&stabilize_thread, NULL, start_stabilize, this);
    pthread_create(&fix_thread, NULL, start_fix, this);
  }

  ChordClient* introducer;
  vector<Node*>* finger_table;
  int power;
  predecessor pred;
  //****
  map<int, pair<string,string> > data_table;

  //verify current node's successor
  //
  void gen_start_values(){
    start_values = new vector<int>(m+1, this->id);
    for(int i=0; i<=m; i++){
      (*(start_values))[i] = (this->id + (1 << (i))) % power;
    }
  }

  int generate_sha1(const string& input){
    SHA1Context sha;
    SHA1Reset(&sha);
    SHA1Input(&sha, (unsigned char*)input.c_str(), input.length());
    SHA1Result(&sha);
    int key_id = sha.Message_Digest[4]%(1<<m);
    return key_id;
  }

  vector<int>* start_values;

  int id;
 private:
  int m;
  int introducer_port;
  int port;
  int stabilize_interval;
  int fix_interval;
  pthread_t stabilize_thread;
  pthread_t fix_thread;
  pthread_mutex_t transport_mutex;

  void stabilize(){
    Node* successor;
    predecessor next;
    while(true){
      sleep(this->stabilize_interval);
      successor = this->finger_table->at(SUCCESSOR);
      if(successor != NULL){
        pthread_mutex_lock(&transport_mutex);
        successor->current_pred(next);
        pthread_mutex_unlock(&transport_mutex);
        //if our successor has no predecessor
        if(next.id != this->id && in_range(this->id, successor->id, next.id)){
          this->set_succ(next.id, next.port);
          successor = this->finger_table->at(SUCCESSOR);
        }
        pthread_mutex_lock(&transport_mutex);
        successor->notify(this->id, this->port);
        pthread_mutex_unlock(&transport_mutex);
      }
      else{
        if(pred.id != this->id){
          this->set_succ(pred.id, pred.port);
        }
      }
    }
  }

  void print_fingers(){
    Node* curr;
    for(int i=0; i<m; i++){
      curr = this->finger_table->at(i);
    }

  }

  int calc_start(int i){
    return (this->id + (1 << (i-1))) % this->power;
  }

  /*
   * Method used by finger thread to keep updating fingers. 
   *  Sleeps "fix_interval" seconds before each poke.
   */
  void fix_fingers(){
    successor next;
    srand(seed);
    int pick, curr_start;
    while(true){
      sleep(this->fix_interval);
      for(int i=1; i<=this->m; i++){
        find_successor(next, calc_start(i));
        set_finger(next.id, next.port, i-1);
      }
    }
  }

  /*
   * Starts stabilization thread, using some weird method I found online.
   * This is necessary for pthreads it seems.
   */
  static void* start_stabilize(void* arg) {
    ChordHandler* h = reinterpret_cast<ChordHandler*>(arg);
    h->stabilize();
    pthread_exit(0);
  }

  /*
   * Starts finger fixing thread, using some weird method I found online.
   * This is necessary for pthread it seems, because it requires :642
   */
  static void* start_fix(void* arg){
    ChordHandler* h = reinterpret_cast<ChordHandler*>(arg);
    h->fix_fingers();
    pthread_exit(0);
  }

};

/*
 * Parses command line arguments sent in by listener, and then creates a new
 * ChordHandler object.
 */
ChordHandler* init_node(int argc, char** argv){
  int id = -1;
  int port = -1;
  int m = -1;
  int introducer_port = -1;
  int num;
  int stabilize_interval = 1;
  int fix_interval = 1;
  string new_log = "";

  //cout << argc << endl;
  for(int i=0; i<argc; i++){
  }

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
    else if (arg == "--stabilizeInterval"){
      stabilize_interval = num;
    }
    else if (arg == "--logConf"){
      new_log = argv[i+1];
    }
    else if (arg == "--seed"){
      seed = num;
    }
  }

  if(id != 0 && introducer_port == -1){
    std::cerr << "Need to include introducer port. Shutting down now." << endl;
    exit(1);
  }

  if(new_log != "")
    configureLogging(new_log.c_str());
  else
    configureLogging(NULL);


  //cout << "Successfully listening" << endl;
  return (new ChordHandler(m, id, port, introducer_port, stabilize_interval, fix_interval));
}

int main(int argc, char **argv) {
  ChordHandler* nodeh = init_node(argc, argv);
  shared_ptr<ChordHandler> handler(nodeh);
  shared_ptr<TProcessor> processor(new ChordProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(nodeh->get_port()));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TThreadedServer server(processor, serverTransport, transportFactory, protocolFactory);

  //spawn thread to take care of stabilization stuff
  
    server.serve();
  return 0;
}
