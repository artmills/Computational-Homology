#include "cubesystem.hpp"


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
