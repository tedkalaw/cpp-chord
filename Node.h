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
    ChordClient* connection;
    Node(int, int);

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
  this->transport->open();
}

//how do destructors work again? haha
