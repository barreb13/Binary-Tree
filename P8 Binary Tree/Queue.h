// File Name:  Queue.h
// Author:  Cliff Snyder (csnyder@everett.edu)
// Description:  Declarations for the class Queue 

#pragma once
#include <iostream>
#define NDEBUG // allow exceptions to fire
#include <cassert>
#include "Node.h"
using namespace std;

template <class P>
class Queue
{
private:	// Private attributes
	Node<P>      *front;    // Pointer to the front of the queue
	Node<P>      *rear;     // Pointer to the rear of the queue
	unsigned int numNodes;  // Number of payloads in the queue

	void clearQueue()
	{
		while (front != nullptr)
		{
			dequeue();
		}
	}

	void copyNodes(const Node<P> *nodePtr)
	{
		// Copy each item in the queue.
		while (nodePtr != nullptr)
		{
			enqueue(nodePtr->getPayload());
			nodePtr = nodePtr->getNext();
		}
	}

public:
	// Constructors
	Queue()
	{
		front = nullptr;
		rear = nullptr;
		numNodes = 0;
	}

	Queue(const Queue& fromQueue)
	{
		front = nullptr;
		rear = nullptr;
		numNodes = 0;
		this->copyNodes(fromQueue.front);  // Deep copy of the Nodes
	}

	// Enqueue/Dequeue methods
	bool enqueue(P newPayload)
	{
		bool returnVal(true);
		try // new throws exceptions
		{
			// Get a new node, store the new payload, and set its next pointer to null.  
			Node<P> *newNode = new Node<P>(newPayload, nullptr);
			// If this is the first node in the queue, set both front and rear to the new node.
			if (numNodes == 0)
			{
				assert(front == nullptr);
				assert(rear == nullptr);
				front = newNode;
				rear = newNode;
			}
			else // Just add the new node to the linked list and reset the rear pointer
			{
				assert(rear != nullptr);
				rear->setNext(newNode);
				rear = newNode;
			}
			numNodes++; // increment the number of nodes in the queue
		}
		catch (...)
		{
			returnVal = false;
		}
		return returnVal;
	}

	P dequeue()
	{
		// Return the payload of the front node, delete it, and reset the front pointer.
		// Throw an exception if the queue is empty
		assert(numNodes > 0);
		if (numNodes <= 0)
		{
			throw runtime_error("Illegal dequeue");
		}

		// Store the payload and next pointer;
		P returnVal = front->getPayload();
		Node<P> *temp = front->getNext();

		// Delete the node; decrement the number of nodes
		delete front;
		numNodes--;

		// Set the front of the queue to the next node
		front = temp;
		if (numNodes == 0)
		{
			assert(front == nullptr);
			rear = nullptr;
		}

		// Return the first element in the queue
		return(returnVal);
	}

	// Front accessor
	P getFront() const
	{
		// Return the payload of the front node.
		// Throw an exception if the queue is empty
		assert(numNodes > 0);
		if (numNodes <= 0)
		{
			throw runtime_error("Illegal readFront");
		}
		return(front->getPayload());
	}

	// Num Nodes accessor
	unsigned int getNumNodes() const
	{
		return(numNodes);
	}

	// isEmpty method
	bool isEmpty() const
	{
		return (numNodes == 0);
	}

	// Overloaded operators
	Queue& operator=(const Queue& fromQueue)
	{
		// If the passed objects are different, delete the nodes from the to stack and copy the nodes from the from stack
		if (this != &fromQueue) // handle queue1 = queue1;
		{
			this->clearQueue();
			this->copyNodes(fromQueue.front);
		}
		return (*this);
	}

	bool operator==(const Queue& rhs) const
	{
		bool retVal = true;

		// If the number of nodes is different, the queues are different.
		if (rhs.numNodes != this->numNodes)
		{
			retVal = false;
		}
		// Else, compare each node and look for differences
		else
		{
			Node<P> *rhsTemp = rhs.front;
			Node<P> *lhsTemp = this->front;

			while (lhsTemp != nullptr && retVal)
			{
				if (lhsTemp->getPayload() != rhsTemp->getPayload())
				{
					retVal = false;
				}
				lhsTemp = lhsTemp->getNext();
				rhsTemp = rhsTemp->getNext();
			}
		}
		return retVal;
	}

	friend ostream& operator <<(ostream& outputStream, const Queue& queue)
	{
		Node<P> *nodePtr = queue.front;
		while (nodePtr != nullptr)
		{
			outputStream << *nodePtr << " ";
			nodePtr = nodePtr->getNext();
		}
		return(outputStream);
	}

	// Destructor
	~Queue()
	{
		clearQueue();
	}
};