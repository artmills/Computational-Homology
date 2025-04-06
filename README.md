# TDA - Computational Cubical Homology
This project implements algorithms from Tomasz Kacynski's textbook Computational Homology.

Given a cubical set, the program computes the dimension of each of the homology groups of that set.
For example, if a 2D grid of squares is given, then the output will be the dimension of $$H_0$$ (number of connected components) and the dimension of $$H_1$$ (number of holes enclosed by activated squares).

This program uses the matrix-based methods suggested by Kacynski's textbook and is nowhere near state-of-the-art. 
The sizes of the matrices are huge (especially for higher-dimensional problems) and computation of the Smith normal form is extremely intensive.
The Smith normal form computations are now done using the open-source project LinBox, which greatly improves the computation time.

This project arose from the topology/geometry seminar at Oregon State University in 2019.
I worked with Danny Wentland and Chung-Ping Lai to introduce the seminar to topological data analysis, with the guidance of our advisor Dr. Christine Escher.
My contribution was to learn and implement the basic features of computational cubical homology, including homology computations on n-dimensional cubes and performing elementary reductions to make those computations more efficient.
Although this project is nowhere near performant enough for real applications, it was a great way to learn the foundational techniques in the field.
For an infinitely more robust cubical homology package, consider the project CHoMP. 
