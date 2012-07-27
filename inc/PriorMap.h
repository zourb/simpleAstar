#ifndef PRIORMAP_H
#define PRIORMAP_H

#include <iostream>
#include <string>
#include <map>
#include "State.h"
using namespace std;

class Tree_Element{
	private:
		Tree_Element *parent;
		State state;
	public:
		Tree_Element();
		Tree_Element(State_Base*);
		Tree_Element(State_Base*, Tree_Element*);
		~Tree_Element();

		void set_parent(Tree_Element *prnt);	
		void set_state(State &st);
		Tree_Element* get_parent() const;
		State get_state() const;
};

class PriorMap{
  private:
    map<string, Tree_Element *> _map;
    Tree_Element * min_f_ele;
    string minKey;

  public:
    PriorMap();
    ~PriorMap();

    //update a pair and set the minkey and min_f_ele
    void set(string key, Tree_Element* ele);
    
    //add a pair
    void add(string key, Tree_Element* ele);

    //get the TreeElement specified by the key
    Tree_Element* get(string key);
    
    //whether the pair indicated by the key is existing
    bool isExist(string key);

    //pop the TreeElement which is the min f() from the map, 
    //re-calculate the minState and minKey
    Tree_Element* min_pop();
};
#endif
