#include "cubesystem.hpp"


std::vector<int> CubeSystem::CanonicalCoordinates(Chain c, std::vector<Cube> cubes)
{
	std::vector<int> v;

	// go through the array of cubes and evalute the chain
	// on them. collect the coefficients and put them in the 
	// vector.
	for (int i = 0; i < cubes.size(); ++i)
	{
		auto it = c.find(cubes[i]);
		if (it == c.end())
		{
			v.push_back(0);	
		}
		else
		{
			v.push_back(it->second);
		}
	}

	return v;
}

Chain CubeSystem::ChainFromCanonicalCoordinates(std::vector<int> v, std::vector<Cube> cubes)
{
	Chain c;
	for (int i = 0; i < cubes.size(); ++i)
	{
		if (v[i] != 0)
		{
			c[cubes[i]] = v[i];	
		}
	}
	return c;
}


std::unordered_map<Cube, int, KeyHasher> CubeSystem::PrimaryFaces(Cube Q)
{
	std::unordered_map<Cube, int, KeyHasher> faces;

	for (int i = 0; i < Q.EmbeddingNumber(); ++i)
	{
		if (!(Q[i].isDegenerate()))
		{
			Cube R = Q;

			R[i].setLeft(Q[i].getLeft());
			R[i].setRight(Q[i].getLeft());
			//R.Print();
			faces[R] = R.Dimension();

			R[i].setLeft(Q[i].getRight());
			R[i].setRight(Q[i].getRight());
			//R.Print();
			faces[R] = R.Dimension();
		}
	}

	return faces;
}

std::vector<std::unordered_map<Cube, int, KeyHasher>> CubeSystem::CubicalChainGroups(CubicalSet K)
{
	//std::cout << "Dimension of the cubical set K: " << K.Dimension() << std::endl;
	std::vector<std::unordered_map<Cube, int, KeyHasher>> E(K.Dimension() + 1);	

	//std::cout << "Number of chain groups to consider: " << E.size() << std::endl;
	
	while (!K.isEmpty())
	{
		// test:
		//std::cout << "Size of K: " << K.cubes.size() << std::endl;

		Cube Q = K.Pop();

		/*
		std::cout << "The current cube being considered in K is: " << std::endl;
		Q.Print();
		std::cout << "with dimension: " << Q.Dimension() << std::endl;
		*/


		int k = Q.Dimension();
		if (k > 0)
		{
			std::unordered_map<Cube, int, KeyHasher> L = PrimaryFaces(Q);

			// union of K and L:
			K.cubes.insert(L.begin(), L.end());

			// L gives (k-1)-dimension cubes. so they go in
			// E[k-1]:
			E[k-1].insert(L.begin(), L.end());
		}

		// Q is k-dimensional so it goes in E[k]:
		E[k].insert(std::pair<Cube, int>(Q, Q.Dimension()));

	}

	return E;
}


