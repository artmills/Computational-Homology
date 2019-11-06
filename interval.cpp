#include "interval.hpp"

Interval::Interval(int left)
{
	this->left = left;
	this->right = left + 1;
}
Interval::Interval(int left, int right)
{
	this->left = left;
	this->right = right;
}
Interval::~Interval(){}
int Interval::getLeft() const
{
	return left;
}
int Interval::getRight() const
{
	return right;
}
void Interval::setLeft(int data)
{
	left = data;
}
void Interval::setRight(int data)
{
	right = data;
}
bool Interval::isDegenerate()
{
	if (left == right)
	{
		return true;
	}
	return false;
}

bool operator==(const Interval& left, const Interval& right)
{
	if (left.getLeft() == right.getLeft() && left.getRight() == right.getRight())
	{
		return true;
	}
	else
	{
		return false;
	}
}
