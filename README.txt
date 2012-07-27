 README: A-Star Search Class
-----------------------------

This project is aimed to be used as a generic A-star class.
In order to make use of it, the programmer has to define
a State class which has to be derived from State_Base class.
During this process, programmer has to code State.h (to be
put in inc/), State.cpp and main.cpp (to be put in src/).

There are two examples: ex1 and ex2. The related files can be
found in the folders with the same name of the examples in inc/
and src/. In order to comple one of it. The header files and 
the source files must be copied to inc/ and src/ folders, respectively.

 Examples
----------

In example-1, how to solve 8-puzzle problem from a given initial state 
with A-star class is shown.

In example-2, finding the shortest path from a starting point to
the target point in a grid world is demonstrated.

 For a Specific Problem
------------------------

For a specific problem, the programmer has to write State class
with the public derivation:

class State : public State_Base

in which, the functions with the following prototypes must be.

1) int calculate_g(State_Base *parent);
2) int calculate_h(State_Base *parent);
3) void print();

In the main file (main.cpp), an instance of A_Star has to be
created. Then, solve member function has to be called
with a State pointer which points to the initial state.

 Compilation
-------------

In order to compile a user defined program with A-star. State.h
has to be in inc/ and State.cpp and main.cpp has to be in src/.
After this, `make` command can be called. To clean, `make clean`
and `make cleanall` can be used.

In order to compile an example, before `make` command, the example 
header files and source files has to be copied to inc/ and src/ respectively.

 Bug Reporting - Author Info
-----------------------------
For any comment and bug reports do not hasitate to contact the author:

Cuneyt Mertayak - cuneyt.mertayak@gmail.com

