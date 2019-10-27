# Project: Simplify a 3D polyedric mesh

Given a big (in size), precise 3D polyedric mesh representation of an object, I had to implement a way of simplifying it in order to make it smaller (in size).

# Ressources

The detailed project's subject is [sujet-canard.pdf](sujet-canard.pdf).

# Given files

- `mesh.h`                   : file with definitions of this project objects
- `list.h`, `list.o`         : precompiled list module
- `test-list.c`              : test and demo of list module
- `collapse.h`, `collapse.o` : precompiled module which contracts vertices

# Implemented files

- `coherence.c|h`			 : module which checks whether a mesh is correct
- `main.c`					 
- `offio.c|h`				 : module which reads and writes a mesh in a file
- `print_mesh.c|h`			 : modue which prints mesh information in order to debug
