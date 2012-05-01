namespace cpp mp2

//First struct we made;
//Not actually used
struct node 
{
  1: i32 my_m,
  2: i32 my_id,
  3: i32 my_port,
  4: i32 introducer_port

}

//Stores information about a given node
//Used in find_predecessor so we can use both its information
//And the information about its successor for the comparison
struct neighbor
{
  1: i32 id,
  2: i32 port,
  3: i32 succ_id,
  4: i32 succ_port,
}

//Stores id and port of successor
struct successor
{
  1: i32 id,
  2: i32 port
}

//Stores id and port of predecessor; no difference from above, just used
//For readability purposes
struct predecessor
{
  1: i32 id,
  2: i32 port
}

//Stores information about a add/del/get/etc operation.
//Has all of the information needed to print back.
struct key_and_node{
  1: i32 key,
  2: i32 node_id,
  3: bool success,
  4: string data
}

//Service in which a node talks to a node
service Chord
{

	void add_node(),
	key_and_node add_file(1: string filename, 2: string data),
	key_and_node del_file(1: string filename),
	void get_table(),
        void transfer_file(1: i32 key, 2: string data, 3: string filename),
        key_and_node snatch_file(1: i32 key),
        key_and_node get_file(1: string filename),
        key_and_node remove_file(1: i32 key),
        successor get_successor(),
        successor join_network(1: i32 pid),
        predecessor current_pred(),
        void notify(1: i32 pid, 2: i32 new_port),
        successor find_successor(1: i32 pid),
        neighbor find_predecessor(1: i32 pid),
        neighbor closest_preceding_finger(1: i32 pid),
        string gen_key_table(),
        string gen_finger_table(),
        string get_key_table(1: i32 pid),
        string get_finger_table(1: i32 pid),
        string get_tables(1:i32 pid)

        
}





