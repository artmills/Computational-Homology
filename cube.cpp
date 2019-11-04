#include "cube.hpp"

Cube::Interval::Interval(int left, int right)
{
	setLeft(left);
	setRight(right);
}
Cube::Interval::~Interval()
int Interval::getLeft()
{
	return endpoints.at(Endpoint::Left);
}
int Interval::getRight()
{
	return endpoints.at(Endpoint::Right);
}
void Interval::setLeft(int data)
{
	endpoints.erase(Endpoint::Left);
	endpoints.insert(std::pair<Endpoint, int>(Endpoint::Left, data));
}
void Interval::setRight(int data)
{
	endpoints.erase(Endpoint::Right);
	endpoints.insert(std::pair<Endpoint, int>(Endpoint::Right, data));
}
bool Interval::isDegenerate(){}
