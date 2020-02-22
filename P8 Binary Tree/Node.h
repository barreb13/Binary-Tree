// Brent Barrese

#pragma once

#include <ostream>

using namespace std;

template <class P>
class Node
{
private:
	P payload;
	Node *next;

public:
	//Constructors
	Node(P newPayload, Node* newNext)
	{
		setPayload(newPayload);
		setNext(newNext);
	}

	//Accessors
	P getPayload() const
	{
		return (payload);
	}
	Node* getNext() const
	{
		return next;
	}

	//Mutators
	void setPayload(P newPayload)
	{
		payload = newPayload;
	}
	void setNext(Node *newNext)
	{
		next = newNext;
	}

	// Overloaded Operators
	friend ostream& operator <<(ostream& outStream, const Node& node)
	{
		outStream << node.getPayload() << " ";
		return (outStream);
	}

	//Deconstructor
	~Node()
	{

	}
};
