#include "Chord.h"
#include "Chord_Listener.h"
#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

//namespace specified
using namespace mp2; 

int introducer_port;

int starting_port = -1;
int attach_node = -1;
int m = -1;
int stabilize_interval = -1;
int fix_interval = -1;
string log_conf = "";

bool valid_flags(int argc, char **argv){
  if(argc < 2){
    std::cerr << "Needs at least --m flag" << endl;
    return false;
  }
  else{
    bool valid = false;
    for(int i=1; i<argc; i++){
      std::string arg = argv[i];
      if(arg == "-m"){
        valid = true;
        break;
      }
    }
    if(valid) return true;
    std::cerr << "Needs at --m flag" << endl;
    return false;
  }
}

void create_node(){
  switch(pid_t childPid = fork()){
    case -1: break;

    //child
    case 0: execv("./node", NULL);
            exit(1);

    //parent
    default: cout << "i am the parent" << endl;
             sleep(1);
             return;

  }

}

void set_args(int argc, char **argv, char**& arguments){
  string arg;
  bool valid = false;
  arguments = new char* [argc - 1];
  for(int i=1; i<argc; i+=2){
    arg = argv[i];
    if(arg == "--m"){
      m = atoi(argv[i+1]);
      valid = true;
      arguments[i-1] = new char [4];
      strncpy(arguments[i-1], "--m", 4);
    }
    else if(arg == "--startingPort"){
      starting_port = atoi(argv[i+1]);
      arguments[i-1] = new char[15];
      strncpy(arguments[i-1], "--startingPort", 15);
    }
    else if (arg == "--attachToNode"){
      attach_node = atoi(argv[i+1]);
      arguments[i-1] = new char[15];
      strncpy(arguments[i-1], "--attachToNode", 15);
    }
    else if(arg == "--stabilizeInterval"){
      stabilize_interval = atoi(argv[i+1]);
      arguments[i-1] = new char[20];
      strncpy(arguments[i-1], "--stabilizeInterval", 20);
    }
    else if(arg == "--fixInterval"){
      fix_interval = atoi(argv[i+1]);
      arguments[i-1] = new char[14];
      strncpy(arguments[i-1], "--fixInterval", 14);
    }
    else if(arg == "--logConf"){
      log_conf = atoi(argv[i+1]);
      arguments[i-1] = new char[10];
      strncpy(arguments[i-1], "--logConf", 10);
    }
    arguments[i] = new char [strlen(argv[i+1])];
    strncpy(arguments[i-1], argv[i+1]);
  }
}

void init_sockets(boost::shared_ptr<TSocket>& socket, boost::shared_ptr<TTransport>& transport,
    boost::shared_ptr<TProtocol>& protocol){

  socket = boost::shared_ptr<TSocket>(new TSocket("localhost", 9090));
  transport = boost::shared_ptr<TTransport> (new TBufferedTransport(socket));
  protocol = boost::shared_ptr<TProtocol> (new TBinaryProtocol(transport));
}


int main(int argc, char **argv) {

  /* server is listening on port 9090 */
  /*
  if(valid_flags(argc, argv)){
    ChordListener listener = parse_args(argc, argv);
  }
  else return 0;
  */

  //create_node();

  //we can change this later
  /* these next three lines are standard */

  char** args;
  set_args(argc, argv, args);

  return 0;
  bool valid = false;
  boost::shared_ptr<TSocket> socket;
  boost::shared_ptr<TTransport> transport;
  boost::shared_ptr<TProtocol> protocol;
  init_sockets(socket, transport, protocol);
  while(true){
    //create a client 
    try{
      transport->open();
      break;
    }
    catch(apache::thrift::transport::TTransportException& e){
      cout << e.what() << endl;
    }
  }

  ChordClient client(protocol);
  //want to add the original introducer node

  printf("Welcome to node listener\n");
  while(1){

	//40 should be enough, whatever we can change it 
	char input[40];
	fputs("Select an option...\n ", stdout);
	printf("ADD_NODE <node ID(s)> \n");
	printf("ADD_FILE <filename><data> \n");
	printf("DEL_FILE <filename>\n");
	printf("GET_FILE <filename>\n");
	printf("GET_TABLE <node ID>\n");
	fgets(input, sizeof input, stdin); 
        
	
	//we want to add a node
	if(strncmp(input, "ADD_NODE", 8) == 0){
		client.add_node();
	}

	//want to add a file 
	else if(strncmp(input, "ADD_FILE", 8) == 0){
		client.add_file();
	}

	//want to delete a file 
	else if(strncmp(input, "DEL_FILE", 8) == 0){
                client.del_file();
        }

	//want to get a file
	else if(strncmp(input, "GET_FILE", 8) ==0){
		client.get_file();
	}

	//want to get the table 
	else if(strncmp(input, "GET_TABLE", 9) == 0){
		client.get_table();
	}

	//exit 
	else if(strncmp(input, "EXIT", 4) == 0){
		break;
	}

	else{
		printf("Something went wrong\n");
	}

	//i go cray
	printf("\n\n\n\n\n");

  }
	
 
  transport->close();

  return 0;
}
