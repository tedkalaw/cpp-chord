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

struct neighbor
{
  1: i32 id,
  2: i32 port,
  3: i32 succ_id,
  4: i32 succ_port,
}

struct successor
{
  1: i32 id,
  2: i32 port
}

struct predecessor
{
  1: i32 id,
  2: i32 port
}

struct key_and_node{
  1: i32 key,
  2: i32 node_id,
  3: bool success,
  4: string data
}

struct UserProfile {
  1: i32 uid,
  2: string name,
  3: string blurb
}

struct previous_try{
  1: i32 left,
  2: i32 right,
  3: i32 t
}



//service in which a node talks to a node
service Chord
{

	//this may be all we need so far
	//now to determine who does what
	void add_node(),
	key_and_node add_file(1: string filename, 2: string data),
	key_and_node del_file(1: string filename),
	void get_table(),
        void transfer_file(1: i32 key, 2: string data),
        key_and_node snatch_file(1: i32 key),
        key_and_node get_file(1: string filename),
        key_and_node remove_file(1: i32 key),
        successor get_successor(),
        successor join_network(1: i32 pid),
        predecessor current_pred(),
        void notify(1: i32 pid, 2: i32 new_port),
        successor find_successor(1: i32 pid),
        neighbor find_predecessor(1: i32 pid),
        neighbor closest_preceding_finger(1: i32 pid)
}





