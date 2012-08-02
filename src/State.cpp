/*
 *
 * State.cpp
 *
 *
 * */

#include<iostream>
#include "../inc/State_Base.h"
#include "../inc/State.h"

using namespace std;

/* Initialization of the environment */
Environment::Environment(int **array, int sx, int sy, Location s, Location t){
	map = array;
	size_x  = sx;
	size_y  = sy;
	start = s;
	target = t;
}

void Environment::print(){
	for(int i=-1; i<=size_x; i++,cout << endl){
		if(-1==i || size_x==i){
			for(int j=-1; j<=size_y; j++)
				cout << '#';
		}
		else{
			cout << '#';
			for(int j=0; j<size_y; j++){
				switch(map[i][j]){
					case EMPTY: cout << '-'; break;
					case TOUCHED: cout << 'x'; break;
					case OBSTACLE: cout << 'O'; break;
					case START: cout << 's'; break;
					case TARGET: cout << 't'; break;
          case SOLVED: cout << '*'; break;
				}
			}
			cout << '#';
		}
	}
}

int** Environment::get_map(){ return map; }

Location Environment::get_target() const { return target; }

int Environment::get_size_x() const {return size_x;}
int Environment::get_size_y() const {return size_y;}

Environment::~Environment() {}

Environment* State::env = NULL;

State::State(){
	calculate_f(NULL);
	last_movement = START;
}

State::~State(){}

State::State(int **initial_map, int size_x, int size_y, int start_x, int start_y, int target_x, int target_y){
	Location start, target;
	start.x = start_x; start.y = start_y;
	target.x = target_x; target.y = target_y;
	env = new Environment(initial_map,size_x,size_y,start,target);
	coor = start;
	calculate_f(NULL);
	last_movement = START;
}

State::State(State& parent, Direction operation){
	*this = parent;
	switch(operation){
		case UP: --coor.x; break;
		case LEFT: --coor.y; break;
    case UPLEFT: --coor.x; --coor.y; break;
    case UPRIGHT: --coor.x; ++coor.y; break;
		case DOWN: ++coor.x; break;
		case RIGHT: ++coor.y; break;
    case DOWNLEFT: ++coor.x; --coor.y; break;
    case DOWNRIGHT: ++coor.x; ++coor.y; break;
		default: break;
	}

	last_movement = operation;

	//calculate_f(&parent);
  //has the same effectiveness
	calculate_f(this);
}

/* For each branch branched_nodes are initialized with a eight element array. The
 * members of the array with NULL are inappropriate nodes. These are not
 * taken into account in A_Star::solve()  */
State_Base** State::Branch(int &nodes_n){
	nodes_n = 8;
	State_Base **branched_nodes = new State_Base* [nodes_n];

	for(int i=0;i<nodes_n;i++)
		branched_nodes[i] = NULL;

	if(coor.x>0 && 
		(EMPTY==(env->get_map()[coor.x-1][coor.y])))
			branched_nodes[0] = new State(*this,UP);
	if(coor.x<env->get_size_x()-1 && 
		(EMPTY==(env->get_map()[coor.x+1][coor.y])))
			branched_nodes[1] = new State(*this,DOWN);
	if(coor.y>0 && 
		(EMPTY==(env->get_map()[coor.x][coor.y-1])))
			branched_nodes[2] = new State(*this,LEFT);
	if(coor.y<env->get_size_y()-1 && 
		(EMPTY==(env->get_map()[coor.x][coor.y+1])))
			branched_nodes[3] = new State(*this,RIGHT);
	if(coor.x>0 && coor.y > 0 &&
		(EMPTY==(env->get_map()[coor.x-1][coor.y-1])))
			branched_nodes[4] = new State(*this,UPLEFT);
	if(coor.x<env->get_size_x()-1 && coor.y > 0 &&
		(EMPTY==(env->get_map()[coor.x+1][coor.y-1])))
			branched_nodes[5] = new State(*this,DOWNLEFT);
	if(coor.x>0 && coor.y<env->get_size_y()-1 &&
		(EMPTY==(env->get_map()[coor.x-1][coor.y+1])))
			branched_nodes[6] = new State(*this,UPRIGHT);
	if(coor.x < env->get_size_x()-1 && coor.y<env->get_size_y()-1 &&
		(EMPTY==(env->get_map()[coor.x+1][coor.y+1])))
			branched_nodes[7] = new State(*this,DOWNRIGHT);

	return branched_nodes;
}

/* Prints the state information and the last operation is 
 * shown as the move of the appropriate neighboring block 
 * of the empty space */
void State::print(){
	cout << '(' << coor.x << ',' << coor.y << ')' << endl;
} 

/* Number of steps gone so far */
int State::calculate_g(State_Base *parent){
	if(!parent)
		return g=0;
  switch(dynamic_cast<State*>(parent)->last_movement){
    case UP:
    case LEFT:
    case DOWN:
    case RIGHT: g = parent->get_g()+10; break;
    case UPLEFT:
    case UPRIGHT:
    case DOWNLEFT:
    case DOWNRIGHT: g = parent->get_g()+14;break;
    default:break;
  }
	return (g);
}

int State::abs(int x){ return x<0?-x:x; }

/* Approximate number of displacements that will be taken to reach the goal.
 * This is the total of Mahalonobis distance of each block to its exact place
 * in the final state */
int State::calculate_h(State_Base *parent){
	if(!parent)
		return h=10;
	return h = abs(coor.x - env->get_target().x)*10 + abs(coor.y - env->get_target().y)*10;
}


string State::get_key()
{
  stringstream sstr;
  sstr << coor.x << ";" << coor.y;
  key = sstr.str();
  return key;
}

Location State::get_coor() { return coor; }
Environment* State::get_env() { return env; }

