/*
 *
 * State.h
 *
 * The header file of the example class State.
 * The purpose of this class is to show how to 
 * use heritage from State_Base class to find
 * the direction to the target block on a block
 * world.
 *
 * */

#ifndef STATE_H
#define STATE_H

#include "State_Base.h"

struct Location
	{ int x,y; };

enum {EMPTY=0,OBSTACLE,TOUCHED,START,TARGET};

/* Environment class is used to keep the map of the world, start and target
 * locations.
 * */
class Environment{
	private:
		int **map;				/* the map of the world */
		Location start, target;	/* the start and the destination */
		int size_x, size_y;		/* the size of the world. x is the horizontal axis */
	public:
		Environment(int **array, int sx, int sy, Location s, Location t);
		~Environment();
		void touch(Location);	/* used to mark a location as TOUCHED */
		void print();			/* prints the world as START (s), TARGET (t), TOUCHED (x), EMPTY (-) and OBSTACLE (O) */

		/* get functions */
		int ** get_map();
		Location get_target() const;
		int get_size_x() const;
		int get_size_y() const;
};

class State : public State_Base{
    private:
		static Environment *env;	/* Since the environment is unique, it is kept as static variable */
		Location coor;				/* The current location defines the state */
		typedef enum {START,UP,LEFT,DOWN,RIGHT} Direction;
		Direction last_movement;	/* the last movement is kept */
	public:
		State();

		/* this is the for the first state, and it config is initialized with initial_map and other variables */
		State(int **initial_map, int size_x, int size_y, int start_x, int start_y, int target_x, int target_y);

		/* operation denotes the direction of the movement */
		State(State & parent,Direction operation);

		~State();

		/* branch new states from the state */
		State_Base** Branch(int &nodes_n);

		/* print, calculate_g and calculate_h are pure virtual functions in the base class */
		/* Print the state configuration */
		void print();
	
		/* Number of displacements done so far */
		int calculate_g(State_Base *parent);

		/* Approximate number of displacements */
		int calculate_h(State_Base *parent);

		/* absolute value */
		int abs(int x);

		/* returns env */
		Environment* get_env();
};

#endif

