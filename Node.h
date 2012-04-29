#include "Chord.h"
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

using namespace std;
using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::mp2;

class Node {
  public:
    int id;
    int port;
    int start;
    ChordClient* connection;
    Node(int, int);
    ~Node();
    void notify(int,int);
    void current_pred(predecessor&);
    void open_connection();
    void close_connection();
    pthread_mutex_t* m_mutex;

  private:
    shared_ptr<TSocket> socket;
    shared_ptr<TTransport> transport;
    shared_ptr<TProtocol> protocol;
};

Node::Node(int id, int port){
  this->id = id;
  this->port = port;
  this->socket = shared_ptr<TSocket>(new TSocket("localhost", port));
  this->transport = shared_ptr<TTransport>(new TBufferedTransport(socket));
  this->protocol = shared_ptr<TProtocol>(new TBinaryProtocol(transport));
  this->connection = new ChordClient(protocol);
}

void Node::notify(int new_id, int new_port){
  open_connection();
  this->connection->notify(new_id, new_port);
  close_connection();
}

void Node::current_pred(predecessor& _return){
  open_connection();
  this->connection->current_pred(_return);
  close_connection();
}

void Node::open_connection(){
  this->transport->open();
}

void Node::close_connection(){
  this->transport->close();
}

//how do destructors work again? haha
Node::~Node(){
  delete this->connection;
}
