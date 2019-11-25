#include "cubesystem.hpp"


std::vector<int> CubeSystem::CanonicalCoordinates(Chain& c, std::vector<Cube>& cubes)
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

Chain CubeSystem::ChainFromCanonicalCoordinates(std::vector<int>& v, std::vector<Cube>& cubes)
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


std::unordered_map<Cube, int, KeyHasher> CubeSystem::PrimaryFaces(Cube& Q)
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

std::vector<Cube> CubeSystem::GetCoordinates(std::unordered_map<Cube, int, KeyHasher>& map)
{
	std::vector<Cube> cubes;
	cubes.reserve(map.size());
	for (auto it : map)
	{
		cubes.push_back(it.first);
	}
	return cubes;
}

std::vector<std::unordered_map<Cube, int, KeyHasher>> CubeSystem::CubicalChainGroups(CubicalSet& K)
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

Chain CubeSystem::BoundaryOperator(Cube& Q)
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

BoundaryMap CubeSystem::Boundaries(ChainComplex& E)
{
	// bd is an arrray where bd[k] is the boundary map from k+1 to k,
	// since we are skipping zero.
	BoundaryMap bd(E.size() - 1);

	for (int k = 1; k < E.size(); ++k)
	{
		// evaluate the boundary operator on each cube of E[k]:
		for (int j = 0; j < E[k].size(); ++j)
		{
			Cube& e = E[k][j];
			Chain c = BoundaryOperator(e);

			bd[k-1][e] = c;
		}
	}

	return bd;
}

std::vector<IntMat> CubeSystem::BoundaryOperatorMatrix(std::vector<std::vector<Cube>>& E, BoundaryMap& bd)
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
			Cube& e = E[k][j];
			Chain c = bd[k-1][e];
			std::vector<int> column = CanonicalCoordinates(c, E[k-1]);
			matrix.setColumn(j, column);
		}

		matrices.push_back(matrix);
	}

	return matrices;
}
std::vector<IntMat> CubeSystem::BoundaryOperatorMatrix(std::vector<std::vector<Cube>>& E)
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


void CubeSystem::Homology(CubicalSet& K, bool CCR)
{
	// get the generators for C_k:
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	std::vector<std::unordered_map<Cube, int, KeyHasher>> chainGroups = CubicalChainGroups(K);
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Time to create chain groups: " << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() / 1000000.0 << " seconds." << std::endl;


	
	// convert the generators into coordinates:
	begin = std::chrono::steady_clock::now();
	std::vector<std::vector<Cube>> E;
	for (int i = 0; i < chainGroups.size(); ++i)
	{
		E.push_back(GetCoordinates(chainGroups[i]));
	}
	end = std::chrono::steady_clock::now();
	std::cout << "Time to convert chains to coordinates: " << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() / 1000000.0 << " seconds." << std::endl;

	std::vector<IntMat> D;
	if (CCR)
	{
		// get the boundary operators:
		begin = std::chrono::steady_clock::now();
		BoundaryMap bd = Boundaries(E);
		end = std::chrono::steady_clock::now();
		std::cout << "Time to create boundary maps: " << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() / 1000000.0 << " seconds." << std::endl;

		// apply the CCR algorithm:
		begin = std::chrono::steady_clock::now();
		ReduceChainComplex(E, bd);		
		end = std::chrono::steady_clock::now();
		std::cout << "Time to do CCR: " << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() / 1000000.0 << " seconds." << std::endl;

	
		// get the boundary operator matrices from the chains:
		begin = std::chrono::steady_clock::now();
		D = BoundaryOperatorMatrix(E, bd);
		end = std::chrono::steady_clock::now();
		std::cout << "Time to get boundary matrices: " << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() / 1000000.0 << " seconds." << std::endl;
		std::cout << "Sizes of the matrices: " << std::endl;
		for (int i = 0; i < D.size(); ++i)
		{
			std::cout << D[i].getRows() << " x " << D[i].getColumns() << std::endl;
		}
	}
	else
	{
		// get the boundary operator matrices from the chains:
		begin = std::chrono::steady_clock::now();
		D = BoundaryOperatorMatrix(E);
		end = std::chrono::steady_clock::now();
		std::cout << "Time to get boundary matrices: " << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() / 1000000.0 << " seconds." << std::endl;
		std::cout << "Sizes of the matrices: " << std::endl;
		for (int i = 0; i < D.size(); ++i)
		{
			std::cout << D[i].getRows() << " x " << D[i].getColumns() << std::endl;
		}
	}

	// compute the homology groups:
	//begin = std::chrono::steady_clock::now();
	std::vector<std::vector<int>> hom = Homology::GetHomology(D);
	Homology::AnalyzeHomology(hom);
	//end = std::chrono::steady_clock::now();
	//std::cout << "Time to compute homology: " << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() / 1000000.0 << " seconds." << std::endl;




	//std::vector<Quotient> H = Homology::HomologyGroupOfChainComplex(D);

	// analyze the homology groups:
	//Homology::AnalyzeHomology(H);
}


void CubeSystem::Reduce(ChainComplex& E, BoundaryMap& bd, int i, Cube& a, Cube& b)
{
	//std::cout << "i = " << i << std::endl;
	for (Cube cube : E[i])
	{
		bd[i-1][cube].erase(b);
	}

	for (Cube cube : E[i-1])
	{
		if (bd[i-2][cube].find(a) != bd[i-2][cube].end())
		{
			for (auto it : bd[i-1][b])
			{
				bd[i-1][cube][it.first] -= bd[i-1][cube][a] * bd[i-1][b][a] * bd[i-1][b][it.first];
			}
		}
	}

	RemoveElementFromVector(E[i], b);		
	RemoveElementFromVector(E[i - 1], a);		
	bd[i-1].erase(b);
	bd[i-2].erase(a);
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
	for (int i = E.size() - 1; i > 1; --i)
	{
		bool found = false;
		while (!found)
		{
			//std::cout << "i = " << i << std::endl;
			for (Cube b : E[i])
			{
				for (Cube a : E[i-1])
				{
					if (bd[i-1].find(b) != bd[i-1].end())
					{
						if (bd[i-1][b].find(a) != bd[i-1][b].end())
						{
							if (std::abs(bd[i-1][b][a] == 1))
							{
								/*
								std::cout << "Reducing: " << std::endl;
								a.Print();
								b.Print();
								*/

								Reduce(E, bd, i, a, b);
								found = true;
								break;
							}
						}
					}
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


CubicalSet CubeSystem::GetCubicalSet(Grid& grid)
{
	std::vector<Cube> cubes;

	// go through the grid and create a cube for each activated square.
	// the grid coordinates (x, y) will refer to the bottom left corner
	// of the elementary cube. so each cube will have two intervals:
	// (x, x+1) and (y, y+1).
	
	for (int x = 0; x < grid.getRows(); x++)
	{
		for (int y = 0; y < grid.getColumns(); y++)
		{
			if (grid.getElement(x, y))
			{
				Cube c; 
				c.addInterval(Interval(x));
				c.addInterval(Interval(y));
				cubes.push_back(c);
			}
		}
	}

	return CubicalSet(cubes);
}
