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

struct UserProfile {
  1: i32 uid,
  2: string name,
  3: string blurb
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
        successor join_network(1: i32 pid),
        predecessor current_pred(),
        void notify(1: i32 pid, 2: i32 new_port),
        successor find_successor(1: i32 pid),
        neighbor find_predecessor(1: i32 pid),
        neighbor closest_preceding_finger(1: i32 pid),
        neighbor get_info()


}





