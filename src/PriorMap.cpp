#include <iostream>
#include "PriorMap.h"
using namespace std;
/*
int main ()
{
  map<char,int> mymap;
  map<char,int>::iterator it;
  pair<char,int> highest;

  mymap['x']=1001;
  mymap['y']=2002;
  mymap['z']=3003;
  mymap['c']=3003;
  mymap['z']=5003;
  mymap['a']=3003;

  cout << "mymap contains:\n";

  highest=*mymap.rbegin();          // last element

  it=mymap.begin();

  //int max = 

  do {
    cout << (*it).first << " => " << (*it).second << endl;
  } while ( mymap.value_comp()(*it++, highest) );
  cout << endl;
  it=mymap.begin();
  for(; it != mymap.end(); ++it)
    cout << (*it).first << " => " << (*it).second << endl;
  return 0;
}*/

Tree_Element::Tree_Element() : parent(NULL) {}

Tree_Element::Tree_Element(State_Base *st, Tree_Element *prnt=NULL) {
	if(st!=NULL){
		set_state(*static_cast<State*>(st));
		set_parent(prnt);
	}
	else{
		cerr << "Error in Tree_Element::Tree_Element(State *st, Tree_Element *prnt=NULL)\n";
		//exit(1);
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
		//exit(1);
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
  //if((min_f_ele == NULL) || (ele->get_state().get_f() < min_f_ele->get_state().get_f())){
  //if((min_f_ele == NULL)){
  min_f_ele = ele;
  minKey = key;
  //}

  _map[key] = ele;
  return;
}

void PriorMap::add(string key, Tree_Element* ele){
  if(key == "" || ele == NULL)
    return;
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

  min_f_ele = NULL;
  minKey = "";

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

Tree_Element* PriorMap::getMinTreeElement(){
  return min_f_ele;
}
