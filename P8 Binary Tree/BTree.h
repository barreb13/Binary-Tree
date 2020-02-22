//Brent Barrese
//Use Stack Class!!

#pragma once
#include "BinNode.h"
#include "Queue.h"
#include <ostream>
#include <cassert>

using namespace std;

//Set Class TraverseType
enum class TraverseType { INORDER, PREORDER, POSTORDER, BREADTHORDER };

template <class P>
class BTree
{
private:
	BinNode<P> *head;
	int numNodes;
	TraverseType traverseOrder;

public:
	//Constructor
	BTree()
	{
		head = nullptr;
		//numNodes = 0;
		traverseOrder = TraverseType::INORDER;
	}

	//Copy Constructor
	BTree(const BTree& fromTree)
	{

		traverseOrder = fromTree.traverseOrder;
		//this->numNodes= 0;
		head = nullptr;
		head=copyHelper(fromTree.head);
	}

	//Accessors
	BinNode<P>* getHead() const
	{
		return head;
	}

	//Mutators
	void setHead(BinNode<P>* node)
	{
		head = node;
	}

	//Copy Helper Preorder Traversal
	BinNode<P>* copyHelper(BinNode<P>* current) 
	{
		BinNode<P> *temp = nullptr;
		if (current != nullptr)
		{
			//Testing
			temp = new BinNode<P>(current->getPayload(),copyHelper(current->getLeft()),copyHelper(current->getRight()));
		}
		return temp;
	}

	//Clear Tree
	void clearTree(BinNode<P>* current)
	{
		if (current != nullptr)
		{
			clearTree(current->getLeft());
			clearTree(current->getRight());
			delete current;
		}
	}

	//Pre-order Print Helper ** This Works
	void preOrderPrint(ostream& outStream, BinNode<P>* current)
	{
		if (current != nullptr)
		{
			outStream << current->getPayload() << " ";
			preOrderPrint(outStream, current->getLeft());
			preOrderPrint(outStream, current->getRight());
		}
	}

	//In-order Print Helper ** This Works
	void inOrderPrint(ostream& outStream, BinNode<P>* current)
	{
		if (current != nullptr)
		{
			inOrderPrint(outStream, current->getLeft());
			outStream << current->getPayload()<< " ";
			inOrderPrint(outStream, current->getRight());
		}
	}

	//Post-order Print Helper ** This Works
	void postOrderPrint(ostream& outStream, BinNode<P>* current)
	{
		if (current != nullptr)
		{
			postOrderPrint(outStream, current->getLeft());
			postOrderPrint(outStream, current->getRight());
			outStream << current->getPayload() << " ";
		}
	}

	//Breadth-order Print Helper ** This Works
	void breadthOrderPrint(ostream& outStream, BinNode<P>* current)
	{
		Queue<BinNode<P>*> tempQueue;

		if (current != nullptr)
		{
			tempQueue.enqueue(current);

			while (!tempQueue.isEmpty())
			{
				outStream << *tempQueue.getFront();
				if (current->getLeft() != nullptr)
				{
					tempQueue.enqueue(current->getLeft());
				}
				if (current->getRight() != nullptr)
				{
					tempQueue.enqueue(current->getRight());
				}
				
				tempQueue.dequeue();

				if (!tempQueue.isEmpty())	// Only getting Front if queue is not empty
				{
					current = tempQueue.getFront();
				}
			}
		}
	}

	//Set Traverse Type Order
	void setTraverseOrder(TraverseType order)
	{
		traverseOrder = order;
	}

	//Overloaded Operators
	//friend << overload // Need an if statement to determine traversal type
	friend ostream& operator <<(ostream& outStream, BTree& tree)
	{
		switch (tree.traverseOrder)		//ostream does not know about tree
		{
		case TraverseType::INORDER:
			tree.inOrderPrint(outStream, tree.head);
			break;
		case TraverseType::PREORDER:
			tree.preOrderPrint(outStream, tree.head);
			break;
		case TraverseType::POSTORDER:
			tree.postOrderPrint(outStream, tree.head);
			break;
		case TraverseType::BREADTHORDER:
			tree.breadthOrderPrint(outStream, tree.head);
			break;
		}
		return (outStream);
	}

	//Overload Assignment Operator =
	BTree& operator =(BTree& fromTree)
	{
		if (this != &fromTree)
		{
			traverseOrder = fromTree.traverseOrder;
			clearTree(this->head); 
			head = copyHelper(fromTree.head);
		}
		return *this;
	}

	//Deconstructor
	~BTree()
	{
		clearTree(head);
	}
};