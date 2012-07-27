/*
 *
 * State.h
 *
 * The header file of the example class State.
 * The purpose of this class is to show how to 
 * use heritage from State_Base class to solve
 * the 8-puzzle problem.
 *
 * */

#ifndef STATE_H
#define STATE_H

#include "State_Base.h"

class State : public State_Base{
    private:
        struct Empty_Place{ int x,y; } emp_place;			/* empty place (0) location, x and y are the horizontal and vertical
															 * coordinates respectively */
        int config[3][3];									/* This is the configuration of the board, unique numbers in
															 * each place from 0 to 8, where 0 denotes the empty place */
        typedef enum {START=-1,UP, LEFT, DOWN, RIGHT} Direction; /* Direction type to keep the last operation */
		Direction last_operation;							/* the last direction in which the empty place is moved is kept */
	public:
		State();

		/* this is the for the first state, and it config is initialized with array */
		State(int array[3][3]);

		/* operation denotes the direction of the empty place */
		State(State & parent,Direction operation);

		~State();

		/* branch new states from the state */
		State_Base** Branch(int &nodes_n);

		/*print, calculate_g and calculate_h are pure virtual functions in the base class */
		/* Print the state configuration */
		void print();
	
		/* Number of displacements done so far */
		int calculate_g(State_Base *parent);

		/* Approximate number of displacements */
		int calculate_h(State_Base *parent);
};

#endif

