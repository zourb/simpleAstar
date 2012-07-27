#include <iostream>
#include "State.h"
#include "A_Star.h"

using namespace std;

State* A_Star::solve(State* initial_state, int& solution_n){
	a_star_state = NOT_FOUND;
	solution_n = 0;
	solution_leaf = NULL;
	solution = NULL;
	root = new Tree_Element(initial_state);
  open_list.set(root->get_state().get_key(), root);

  Tree_Element* t_tmp = NULL;
  while((t_tmp = open_list.min_pop()) != NULL)
  {
    close_list.insert(pair<string, Tree_Element*>(t_tmp->get_state().get_key(), t_tmp));
		/* The solution is found */
    if(t_tmp->get_state().get_h() == 0)
    {
			a_star_state = FOUND;
			Tree_Element *solution_leaf = t_tmp;
			Tree_Element *t_ele = solution_leaf;
			int step_n = 0;

			while(t_ele){
				++step_n;
				t_ele = t_ele->get_parent();
			}
			solution_n = step_n;

			solution = new State [step_n];
			t_ele = solution_leaf;
			for(int i=step_n-1;i>=0;i--){
				solution[i] = t_ele->get_state();
				t_ele = t_ele->get_parent();
			}

			return solution;
    }
		int new_states_n;
		State_Base** branched_states = (((t_tmp->get_state()).Branch(new_states_n)));

		for(int i=0; i<new_states_n; i++){
			if(branched_states[i] != NULL)
      {
        string str = dynamic_cast<State *>(branched_states[i])->get_key();
        if(close_list.count(str) <= 0)
        {
          Tree_Element *tmp = NULL;
          Tree_Element *cur = NULL;
          if(open_list.isExist(str))
          {
            cur = open_list.get(str); 
            if(branched_states[i]->get_f() < cur->get_state().get_f())
            {
              tmp = new Tree_Element(branched_states[i], t_tmp);
              open_list.set(str, tmp);
              delete(cur);
            }
            else
              delete(branched_states[i]);
          }
          else
          {
            tmp = new Tree_Element(branched_states[i], t_tmp);
            open_list.add(str, tmp);
          }
        }
        else
        {
          //do some delete
          delete(branched_states[i]);
        }
     }
	  }
	}

  //close_list memory reclaimation, open_list reclaim its' by itself
  if(close_list.size() > 0)
  {
     map<string,Tree_Element*>::iterator it;
     for(it = close_list.begin(); it != close_list.end(); it++)
     {
       Tree_Element * ptr = (*it).second;
       if(ptr != NULL)
         delete(ptr);
     }
  }
	if(NOT_FOUND==a_star_state){
		cerr << "The Solution does not exist\n";
		return NULL;
	}
  return NULL;
}

void A_Star::print(){
	for(int i=0; i<solution_n; i++)
		solution->print();
}

