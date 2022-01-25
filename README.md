# Computational_Homology
Implementing algorithms from Kaczynski's Computational Homology

# NOTE: Currently inactive!
This project was part of an effort by the Oregon State University mathematics topology seminar in Fall 2019 to introduce the field of topological data analysis to the seminar.
My contribution was to learn and implement the basic features of computational cubical homology, including homology computations on n-dimensional cubes and performing elementary reductions to make those computations more efficient.
Although this project is nowhere near-performant enough for real applications, it was a great way to learn the foundational techniques in the field.
For an infinitely more robust cubical homology package, take a look at CHoMP. 

To-Do List:
* Find a better alternative to the Smith Normal form algorithm. This is by far the slowest part of the program, since it performs naive row-reduction algorithms on the enormous incidence matrices. Which leads me to:
* Sparse matrices. The boundary operators for computing the homology are incidence matrices, which are incredibly sparse. A significant performance gain can be made by using more intelligent data structures.
* CHoMP: Try playing with CHoMP! See just how much faster CHoMP is than this naive implementation, and try it out on some real data. I bet there's something fun I could do analyzing chunks in Minecraft with this.
