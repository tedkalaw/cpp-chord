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
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

//namespace specified
using namespace mp2; 

int new_port;

ChordClient* introducer;

boost::shared_ptr<TSocket> _socket;
boost::shared_ptr<TTransport> _transport;
boost::shared_ptr<TProtocol> _protocol;

int attached = -1;
int starting_port = -1;
string attach_node = "";
string m = "";
string stabilize_interval = "";
string fix_interval = "";
string log_conf = "";
int num_arguments = 0;

//Stores the formatted arguments that will be used in the exec call
//when we make a new node.
char** args;
int introductor_port = 0;

/*
 * Initializes a connection given three references to the required files.
 */
void init_sockets(boost::shared_ptr<TSocket>& socket, boost::shared_ptr<TTransport>& transport,
    boost::shared_ptr<TProtocol>& protocol, int port){

  socket = boost::shared_ptr<TSocket>(new TSocket("localhost", port));
  transport = boost::shared_ptr<TTransport> (new TBufferedTransport(socket));
  protocol = boost::shared_ptr<TProtocol> (new TBinaryProtocol(transport));
}

/*
 * Inserts id, port, and intro_port into their proper places in the argumetns
 * array that will be sent to ./node
 *
 * id: --id arg
 * port: --port arg
 * intro_port: --introducerPort flag
 */
void insert_args(int id, int port, int intro_port){
  string a;
  a = boost::lexical_cast<string>(id);
  int len;

  len = a.length() + 1;
  args[4] = new char[len];
  strncpy(args[4], a.c_str(), len);

  a = boost::lexical_cast<string>(port);
  len = a.length() + 1;
  args[6] = new char[len];
  strncpy(args[6], a.c_str(), len);

  a = boost::lexical_cast<string>(intro_port);
  len = a.length() + 1;
  args[8] = new char[len];
  strncpy(args[8], a.c_str(), len);
}

/*
 * Creates new node. Execs and then waits a little to give the 
 * node a chance to start; after one second, it attempts to connect.
 * If the connection is successful (and the node is not the introducer) 
 * the connection is closed. If the node is the introducer, then the
 * connection stays open.
 *
 * If the connection is not made, then we know that the node can't have been
 * created properly, so we pick a random number and pick a new one.
 *
 * new_id: id of new node to add
 * is_introducer: true if node is introducer
 *
 */
void create_node(int new_id, bool is_introducer){
  bool done = false;
  pid_t child;
  if(!is_introducer)
    new_port = rand() % 8000 + 1999;
  while(!done){
    switch(child = fork()){
      case 0: insert_args(new_id, new_port, introductor_port);
              execv("./node", args);

      default: usleep(10000);
    }

    if(child != 0){
      init_sockets(_socket, _transport, _protocol, new_port);
      try{
        sleep(1);
        _transport->open();
        done = true;
      }
      catch(apache::thrift::transport::TTransportException& e){
        new_port = rand() % 8000 + 1999;
      }
    }
  }

  if(is_introducer){
    introductor_port = new_port;
  }
  else
    _transport->close();

}

/*
 * Creates the array that will be fed to ./node on the commandline.
 * Just puts them in the right places, allocates memory, and whatnot.
 */
void initialize_args(){
  int num = 10 + 2 * num_arguments;
  int end = num - 1;
  args = new char* [num];
  int len;
  len = strlen("./listener") + 1;
  args[0] = new char[len];
  strncpy(args[0], "./listener", len);

  len = strlen("--m") + 1;
  args[1] = new char[len];
  strncpy(args[1], "--m", len);

  len = m.length() + 1;
  args[2] = new char[len];
  strncpy(args[2], m.c_str(), len);

  len = strlen("--id") + 1;
  args[3] = new char[len];
  strncpy(args[3], "--id", len);

  len = strlen("--port") + 1;
  args[5] = new char[len];
  strncpy(args[5], "--port", len);

  len = strlen("--introducerPort") + 1;
  args[7] = new char[len];
  strncpy(args[7], "--introducerPort", len);

  int next_pos = 9;
  if(stabilize_interval != ""){
    len = strlen("--stabilizeInterval") + 1;
    args[next_pos] = new char[len];
    strncpy(args[next_pos], "--stabilizeInterval", len);

    len = stabilize_interval.length() + 1;
    args[next_pos+1] = new char[len];
    strncpy(args[next_pos+1], stabilize_interval.c_str(), len);
    next_pos += 2;
  }

  if(fix_interval != ""){
    len = strlen("--fixInterval") + 1;
    args[next_pos] = new char[len];
    strncpy(args[next_pos], "--fixInterval", len);

    len = fix_interval.length() + 1;
    args[next_pos+1] = new char[len];
    strncpy(args[next_pos+1], fix_interval.c_str(), len);
    next_pos += 2;
  }

  if(log_conf != ""){
    len = strlen("--logConf") + 1;
    args[next_pos] = new char[len];
    strncpy(args[next_pos], "--logConf", len);

    len = log_conf.length() + 1;
    args[next_pos+1] = new char[len];
    strncpy(args[next_pos+1], log_conf.c_str(), len);
    next_pos += 2;
  }

  args[next_pos] = NULL;

}

/*
 * Takes in information about a DEL action and returns the formatted string as specified.
 *
 * fname: name of file
 * key: value of key
 * nodeID: id of node that did the DEL
 * success: true if the file was found and deleted
 *
 */
string get_DEL_FILE_result_as_string(const char* fname, const int32_t key, const int32_t nodeID, bool success){
  std::stringstream s;
  s << "fname =" << fname << "\n";
  s << "key= " << key << "\n";
  if(success){
    s << "was stored at node= " << nodeID << "\n";
    s << "deleted\n";
  }
  else{
    s << "file not found\n";
  }
  return s.str();
}

/*
 * Takes in information about a ADD action and returns the formatted
 * string as specified.
 *
 * fname: name of file
 * key: value of key
 * nodeID: id of node that did the ADD
 * success: true if the file was found and added
 */
string get_ADD_FILE_result_as_string(const char* fname, const int32_t key,
    const int32_t nodeID){
  std::stringstream s;
  s << "fname= " << fname << "\n";
  s << "key= " << key << "\n";
  s << "added to node= " << nodeID << "\n";
  return s.str();
}

/*
 * Takes in information about a GET action and returns the formatted
 * string as specified.
 *
 * fname: name of file
 * key: value of key
 * nodeID: id of node that did the GET
 * success: true if the file was found and added
 * fdata: data stored at location
 */
string get_GET_FILE_result_as_string(const char *fname,
    const int32_t key,
    const bool found,
    const int32_t nodeId,
    const char *fdata)
{
  std::stringstream s;
  s << "fname= " << fname << "\n";
  s << "key= " << key << "\n";
  if (found) {

    s << "stored at node= " << nodeId << "\n";
    s << "fdata= " << fdata << "\n";
  }
  else {

    s << "file not found\n";
  }
  return s.str();
}

/*
 * Builds the argument  array to give to the exec call.
 * Uses the global "arg" to store all of the variables.
 *
 * argc: argc passed in from commandline
 * argv: argv passed in from commandline
 */
void set_args(int argc, char **argv){
  string arg;
  bool intro = false;
  for(int i=1; i<argc; i+=2){
    arg = argv[i];
    if(arg == "--m"){
      arg = argv[i+1];
      m = arg;
    }
    else if(arg == "--startingPort"){
      new_port = atoi(argv[i+1]);;
      intro = true;
    }
    else if (arg == "--attachToNode"){
      arg = argv[i+1];
      attach_node = arg;
    }
    else if(arg == "--stabilizeInterval"){
      arg = argv[i+1];
      stabilize_interval = arg;
      num_arguments++;
    }
    else if(arg == "--fixInterval"){
      arg = argv[i+1];
      fix_interval = arg;
      num_arguments++;
    }
    else if(arg == "--logConf"){
      arg = argv[i+1];
      log_conf = arg;
      num_arguments++;
    }
  }

  if(!intro){
    new_port = rand() % 8000 + 1999;
  }
}

/*
 * Starts repl for user
 */
int main(int argc, char **argv) {

  srand(time(NULL));

  set_args(argc, argv);
  initialize_args();
  if(attach_node == ""){
    create_node(0, true);
  }
  else{
    int new_port = boost::lexical_cast<int>(attached);
    init_sockets(_socket, _transport, _protocol, new_port);
    _transport -> open();
    introductor_port = new_port;
  }


  ChordClient client(_protocol);
  //want to add the original introducer node

  printf("Chord active.\n");
  while(1){

	//40 should be enough, whatever we can change it 
        string input;
        getline(cin, input);
        std::vector<std::string> strs;
        boost::split(strs, input, boost::is_any_of(" "));
	
        string output;
        key_and_node text;

        if(strs[0] == "ADD_FILE"){
          client.add_file(text, strs[1], strs[2]);
          output = get_ADD_FILE_result_as_string(strs[1].c_str(), text.key, text.node_id);
          cout << output << endl;
        }
        else if(strs[0] == "DEL_FILE"){
          client.del_file(text, strs[1]);
          output = get_DEL_FILE_result_as_string(strs[1].c_str(), text.key, text.node_id, 
              text.success);
          cout << output << endl;
        } else if(strs[0] == "ADD_NODE"){
          for(int i=1; i<strs.size(); i++){
            create_node(boost::lexical_cast<int>(strs[i]), false);
          }
        }
        else if(strs[0] == "GET_FILE"){
          client.get_file(text, strs[1]);
          output = get_GET_FILE_result_as_string(strs[1].c_str(), text.key, 
              text.success, text.node_id, text.data.c_str());
          cout << output << endl;
        }
        else if(strs[0] == "GET_TABLE"){
          client.get_tables(output, boost::lexical_cast<int>(strs[1].c_str()));
          cout << output << endl;
        }else if (strs[0] == "x"){
          _transport->close();
          exit(0);
        }

  }

  _transport->close();

  return 0;
}
