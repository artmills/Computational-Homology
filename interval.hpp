#pragma once

#include <iostream>

struct Interval
{
public:

	Interval(int left);
	Interval(int left, int right);
	~Interval();

	int getLeft() const;
	int getRight() const;
	void setLeft(int data);
	void setRight(int data);
	bool isDegenerate() const;
	bool isDegenerate();

	void Print() const;


private:

	int left;
	int right;

};

bool operator==(const Interval& left, const Interval& right);
bool operator!=(const Interval& left, const Interval& right);
