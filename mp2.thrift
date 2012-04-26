namespace cpp mp2

//need a structure to deal with nodes
struct node 
{
  //this may be all we need for now
  //may add something later for fingers to a node
  //may add something later for actual data... idk
  1: i32 my_m,
  2: i32 my_id,
  3: i32 my_port,
  4: i32 introducer_port

}


//service in which a node talks to a node
service Chord
{

	//this may be all we need so far
	//now to determine who does what
	void add_node(),
	void add_file(),
	void del_file(),
	void get_file(),
	void get_table(), 
        void test_method()

}





