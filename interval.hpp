#pragma once

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
		bool isDegenerate();


	private:

		int left;
		int right;

};

bool operator==(const Interval& left, const Interval& right);
