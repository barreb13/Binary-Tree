//Brent Barrese
//Use Node Class!!

#pragma once

#include <ostream>
using namespace std;

template <class P>
class BinNode
{
private:
	P payload;
	BinNode * left;
	BinNode * right;

public:
	//Constructor
	BinNode(P newPayload, BinNode* newLeft, BinNode* newRight)
	{
		setPayload(newPayload);
		setLeft(newLeft);
		setRight(newRight);
	}

	//Accessors
	P getPayload() const
	{
		return (payload);
	}

	BinNode *getLeft() const
	{
		return left;
	}

	BinNode *getRight() const
	{
		return right;
	}

	//Mutators
	void setPayload(P newPayload)
	{
		payload = newPayload;
	}

	void setLeft(BinNode* newLeft)
	{
		left = newLeft;
	}

	void setRight(BinNode* newRight)
	{
		right = newRight;
	}

	//Overloaded Operators
	friend ostream& operator <<(ostream& outStream, const BinNode& binNode)
	{
		outStream << binNode.getPayload() << " ";
		return outStream;
	}

	//Deconstructor
	~BinNode()
	{

	}
};