#include "Chord.h"
#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>
#include <vector>
#include <vector>
#include <string>
#include <stdio.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

//namespace specified
using namespace mp2; 

int main(int argc, char **argv) {
  /* server is listening on port 9090 */

  /* these next three lines are standard */
  boost::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));
  boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

  //create a client 
  ChordClient client(protocol);
  transport->open();

  //want to add the original introducer node
  client.add_node();

  printf("Welcome to node listener\n");
  //user interface type shit
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
