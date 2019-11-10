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

std::vector<Cube> CubeSystem::GetCoordinates(std::unordered_map<Cube, int, KeyHasher> map)
{
	std::vector<Cube> cubes;
	cubes.reserve(map.size());
	for (auto it : map)
	{
		cubes.push_back(it.first);
	}
	return cubes;
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

Chain CubeSystem::BoundaryOperator(Cube Q)
{
	int sign = 1;
	Chain c;

	for (int i = 0; i < Q.size(); ++i)
	{
		if (!Q[i].isDegenerate())
		{
			Cube R = Q;
			R[i].setLeft(Q[i].getLeft());
			R[i].setRight(Q[i].getLeft());
			c[R] = -sign;

			R[i].setLeft(Q[i].getRight());
			R[i].setRight(Q[i].getRight());
			c[R] = sign;

			sign = -sign;
		}
	}

	return c;
}

std::vector<IntMat> CubeSystem::BoundaryOperatorMatrix(std::vector<std::vector<Cube>> E)
{
	std::vector<IntMat> matrices;

	for (int k = 1; k < E.size(); ++k)
	{
		// bd: K_k --> K_{k-1}.
		int lastRow = E[k-1].size() - 1;
		int lastColumn = E[k].size() - 1;

		IntMat matrix(lastRow + 1, lastColumn + 1);

		// evaluate the boundary operator on each cube of E[k]:
		for (int j = 0; j < E[k].size(); ++j)
		{
			Chain c = BoundaryOperator(E[k][j]);
			std::vector<int> column = CanonicalCoordinates(c, E[k-1]);
			matrix.setColumn(j, column);
		}

		matrices.push_back(matrix);
	}

	return matrices;
}

void CubeSystem::Homology(CubicalSet K)
{
	// get the generators for C_k:
	std::vector<std::unordered_map<Cube, int, KeyHasher>> chainGroups = CubicalChainGroups(K);

	// convert the generators into coordinates:
	std::vector<std::vector<Cube>> E;
	for (int i = 0; i < chainGroups.size(); ++i)
	{
		E.push_back(GetCoordinates(chainGroups[i]));
	}

	// get the boundary operator matrices from the chains:
	std::vector<IntMat> D = BoundaryOperatorMatrix(E);

	// compute the homology groups:
	std::vector<Quotient> H = Homology::HomologyGroupOfChainComplex(D);

	// analyze the homology groups:
	Homology::AnalyzeHomology(H);
	
}

/*
void CubeSystem::Reduce(ChainComplex& E, BoundaryMap& bd, int i, Cube& a, Cube& b)
{
	for (Cube cube : E[i + 1])
	{
		bd[i+1][cube].erase(b);
	}

	for (Cube cube : E[i])
	{
		if (bd[i][cube].find(a) != bd[i][cube].end())
		{
			for (auto it : bd[i][b])
			{
				bd[i][cube][it.first] -= bd[i][cube][a] * bd[i][b][a] * bd[i][b][it.first];
			}
		}
	}

	RemoveElementFromVector(E[i], b);		
	RemoveElementFromVector(E[i - 1], a);		
	bd[i].erase(b);
	bd[i-1].erase(a);
}

void CubeSystem::RemoveElementFromVector(std::vector<Cube>& v, Cube& e)
{
	auto it = std::find(v.begin(), v.end(), e);

	// then the item has been found.
	if (it != v.end())
	{
		// swap the found element to the end of the vector and pop it off.
		std::swap(*it, v.back());
		v.pop_back();
	}
}

void CubeSystem::ReduceChainComplex(ChainComplex& E, BoundaryMap& bd)
{
	for (int i = E.size() - 1; i > 0; ++i)
	{
		bool found = false;
		while (!found)
		{
			for (Cube b : E[i])
			{
				for (Cube a : E[i-1])
				{
										
				}
			}
		}
	}
}

int CubeSystem::ScalarProduct(Chain& c1, Chain& c2)
{
	int product = 0;
	for (auto it : c1)
	{
		product += c2[it.first] * it.second;
	}
	return product;
}
*/
