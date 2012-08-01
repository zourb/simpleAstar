/*
 *
 * Main function
 *
 * */

#include<iostream>
#include<fstream>
#include "../inc/State.h"
#include "../inc/A_Star.h"
using namespace std;

/* global variable for map */
int** array = NULL;
int size_x;
int size_y;

/* reading the input from file with the name specified in filename */
extern "C" int load_map(const char *filename){
//int load_map(const char *filename){
	ifstream fin;
  if(filename == NULL)
    filename = "../inp/map";
	//if(!fin.open(filename))
  //  return 1;
  fin.open(filename);
	fin >> size_x >> size_y;
	array = new int* [size_x];
	for(int i=0; i<size_x; i++)
		array[i] = new int[size_y];
	
	for(int i=0; i<size_x; i++)
		for(int j=0; j<size_y; j++)
			fin >> array[i][j];
	fin.close();
	return 0;
}

extern "C" int destroy_map()
//int destroy_map()
{
  if(array == NULL)
    return 0;
  for(int i = 0; i < size_x; i++)
    if(array[i] != NULL)
      delete[](array[i]);
  delete[](array);
  return 0;
}

void usage(){ cerr << "Usage: something\n"; }
extern "C" int simpleAstar(int start_x, int start_y, int target_x, int target_y)
{
  if(array == NULL)
    return 1;
  for(int i = 0; i < size_x; i++)
    if(array[i] == NULL)
      return 1;
/*int main(int argc, char *argv[])
{
  int start_x = 1, start_y = 1, target_x = 2, target_y = 5;
  //char* file = "../inp/map";
  load_map(NULL);
  if(array == NULL)
    return 1;
  for(int i = 0; i < size_x; i++)
    if(array[i] == NULL)
      return 1;
*/
	/* the initial state (the root of the a-star tree) */
	State *x = new State(array, size_x, size_y, start_x, start_y, target_x, target_y);
  Environment* globalEnv = x->get_env();
  if(globalEnv != NULL)
    globalEnv->print();

	A_Star as;
	int number_of_states;
	State *sol = as.solve(x,number_of_states);

  if(sol != NULL)
  {
	  cout << "\nThe path followed:\n";
    for(int i=0;i<number_of_states;i++)
      sol[i].print();
    delete[] sol;
  }
  /* object cleanup on heap */
  if(x != NULL)
    delete(x);
  //if(sol != NULL)
  //  delete(sol);
  if(globalEnv != NULL)
    delete(globalEnv);
	return 0;
}

