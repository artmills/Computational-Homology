#pragma once

#include <unordered_map>

namespace Cube
{

// to keep track of orientation, endpoints of elementary intervals need
// to know whether they are left or right endpoints.
enum class Endpoint {Left, Right};

// elementary intervals are hash maps of endpoints.
struct Interval
{
	public:
	
		Interval(int left, int right);
		~Interval();

		void setLeft(int data);
		void setRight(int data);
		int getLeft();
		int getRight();
		bool isDegenerate();

	private:

		std::unordered_map<Endpoint, int> endpoints;
};






}
