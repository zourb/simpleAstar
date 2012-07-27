/*
 * A_Star.h
 *
 * This header file contains declerations of four classes
 *
 * 1) Tree_Element: A-star search tree is kept as a tree where
 *    each node has a pointer to its parent. This class is the 
 *    node class of the search three.
 *
 * 2) PriorMap: Wrapped map which has the minKey and min_f_ele 
 *    (the Tree_Element which has min f value) , is using for open_list in a* algo.
 *
 * 3) A_Star: This class keeps a pointer to the A-star search tree, an instant
 *    of PriorMap. The only thing that is necessary
 *    to do is to call the function "solve". If solution exists, the function
 *    returns the solution size (solution_n) and a solution_n-sized array
 *    of State array that is the solution. The first state is kept in the
 *    0-th index of the array. If a solution does not exist, this function
 *    returns NULL. The function "print" can be called after the function "solve"
 *    is called. It iteratively calls "print" function of State instances of the
 *    solution.
 *
 * */

#ifndef A_STAR_H
#define A_STAR_H

#include "State.h"
#include "PriorMap.h"
#include <queue>
#include <vector>

using namespace std;

class A_Star{
	private:
    PriorMap open_list;
    map<string,Tree_Element *> close_list;
		Tree_Element *root;			/* root of the A-star tree */
		Tree_Element *solution_leaf;/* keeps the solution leaf after solve is called */
		State *solution;			/* This array is allocated when solve is called */
		int solution_n;				/* the size of the solution after solve is called */
		enum {NOT_FOUND,FOUND} a_star_state;	/* keeps if a solution exists after solve is called */
	public:
		State* solve(State* initial_state, int &solution_n);
		void print();
};

#endif

