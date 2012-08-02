#include <iostream>
#include "../inc/PriorMap.h"
using namespace std;

Tree_Element::Tree_Element() : parent(NULL) {}

Tree_Element::Tree_Element(State_Base *st, Tree_Element *prnt=NULL) {
	if(st!=NULL){
		set_state(*static_cast<State*>(st));
		set_parent(prnt);
	}
	else{
		cerr << "Error in Tree_Element::Tree_Element(State *st, Tree_Element *prnt=NULL)\n";
    return;
	}
}

Tree_Element::Tree_Element(State_Base *st) {
	if(st!=NULL){
		set_state(*static_cast<State*>(st));
		set_parent(NULL);
	}
	else{
		cerr << "Error in Tree_Element::Tree_Element(State *st)\n";
    return;
	}
}

Tree_Element::~Tree_Element() {}

void Tree_Element::set_parent(Tree_Element *prnt){ parent = prnt; }
void Tree_Element::set_state(State &st){ state = st; }

Tree_Element* Tree_Element::get_parent() const {return parent;}
State Tree_Element::get_state() const {return state;}


PriorMap::PriorMap()
{
  min_f_ele = NULL;
  minKey = "";
}

PriorMap::~PriorMap(){
  if(_map.size() > 0)
  {
     map<string,Tree_Element*>::iterator it;
     for(it = _map.begin(); it != _map.end(); it++)
     {
       Tree_Element * ptr = (*it).second;
       if(ptr != NULL)
         delete(ptr);
     }
  }
  return;
}

void PriorMap::set(string key, Tree_Element* ele){
  if(key == "" || ele == NULL)
    return;
  /* pair added to map needs setting min_f_ele and minKey 
   * including the first pair or the pair has min_f*/
  min_f_ele = ele;
  minKey = key;

  _map[key] = ele;
  return;
}

void PriorMap::add(string key, Tree_Element* ele){
  if(key == "" || ele == NULL)
    return;
  /* if the _map.size() equals 0, then adding pair 
   * should re-initialize min_f_ele and minKey */
  if(minKey == "" || min_f_ele == NULL)
  {
    minKey = key;
    min_f_ele = ele;
  }
  _map[key] = ele;
  return;
}

Tree_Element* PriorMap::get(string key){
  return _map.find(key)->second;
}

bool PriorMap::isExist(string key)
{
  return _map.count(key) > 0;
}

Tree_Element* PriorMap::min_pop()
{
  Tree_Element *res = NULL;
  if(min_f_ele != NULL)
  {
    res = min_f_ele;
    _map.erase(minKey);
  }
  //cout << minKey << endl;

  min_f_ele = NULL;
  minKey = "";

  /* re-calculate the minKey and min_f_ele */
  if(_map.size() > 0)
  {
     map<string,Tree_Element*>::iterator it;
     for(it = _map.begin(), minKey = (*it).first, min_f_ele = (*it).second; it != _map.end(); it++)
     {
       if((*it).second->get_state().get_f() < min_f_ele->get_state().get_f())
       {
         minKey = (*it).first;
         min_f_ele = (*it).second;
       }
     }
  }
  return res;
}

