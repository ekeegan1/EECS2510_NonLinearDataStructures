#include <iostream>
#include <string>
#include <stdexcept>
#include "HybridList.h"
#include "BoundedArray.cpp"
using namespace std;

HybridList::HybridList() {}

HybridList::HybridList(int blockSize) {
	if (blockSize <= 0)
		throw out_of_range("Invalid block size " + to_string(blockSize));
	this->blockSize = blockSize;
}

HybridList::~HybridList() {
	clear();
}

int HybridList::size() const {
	return numElements;
}

int HybridList::capacity() const {
	return numBlocks * blockSize;
}

int HybridList::block_size() const {
	return blockSize;
}

HybridListNode* HybridList::front() const {
	return head;
}

HybridListNode* HybridList::back() const {
	return tail;
}

double& HybridList::at(int index) const {
	HybridListNode* curNode = head;
	int elementsSearched = 0;

	if (index < 0 || index >= numElements)
		throw out_of_range("Invalid index " + to_string(index));

	// Iterate through all blocks to identify block containing the index
	while (curNode != nullptr) {
		if (index < elementsSearched + curNode->size()) {
			// Element is in this block so just return the correct element from
			// this block
			return curNode->at(index - elementsSearched);
		}
		// Element is not in this block so add the number of elements in the
		// block to the number of elements searched
		elementsSearched += curNode->size();
		curNode = curNode->next;
	}

	// Iterator went beyond last block so something went horribly wrong
	abort();
}

void HybridList::push_back(double value) {
	if (numBlocks == 0) {
		// Hybrid list is empty so creating a new node that will be both the head
		// and tail and append the element to it
		HybridListNode* newTail = new HybridListNode(blockSize);
		newTail->push_back(value);
		tail = newTail;
		head = newTail;
		numBlocks = 1;
	}
	else if (tail->size() == blockSize) {
		// Tail node is full so create a new tail node and copy the back half of
		// the old tail node to the new tail node
		HybridListNode* newTail = new HybridListNode(blockSize);

		// Copy just under half of elements from old tail to new tail
		for (int i = blockSize / 2 + 1; i < blockSize; i++)
			newTail->push_back(tail->at(i));
		tail->resize(blockSize / 2 + 1);
		//cout << tail->size() << endl;
		// Append new item to new tail
		newTail->push_back(value);
		tail->next = newTail;
		//cout << newTail->size() << endl;
		//cout << "Tail: " << tail << endl;
		//cout << "New tail: " << newTail << endl;
		tail = newTail;
		numBlocks++;
	}
	else
		tail->push_back(value);	// Tail isn't full so just append to tail

	numElements++;
}






//start of my code


HybridList& HybridList::operator=(const HybridList& h)
{
	blockSize = h.size();

	for (int j = 0; j < h.size(); j++)
		push_back(h.at(j));
	
	return *this;
}

void HybridList::pop_back()
{
	if (numBlocks == 0)
		throw std::out_of_range("Array is empty");

	//at the end of the tail remove the last element
	
	tail->pop_back();
	numElements--;

	//if this is the last element of the hybrid list
	//if numelements ==0, then reassign head and tail to nullptr
	if (numElements == 0)
	{
		delete head;
		head = tail = nullptr;
		numBlocks--;
	}

	//this is where the last element of tail is poped and needs to be deleted
	if(tail->size() == 0)
	{
		HybridListNode* currNode = head;
		while (currNode->next != tail)
			currNode = currNode->next;

		delete tail;
		tail = currNode;
		tail->next = nullptr;
		numBlocks--;
	}
}

//incomeplete
void HybridList::insert(int index, double value)
{
	if (index >= numElements || index < 0)
		throw std::out_of_range("Invalid index " + std::to_string(index));


	HybridListNode* currNode = head;
	int indicie = 0;

	while (currNode != nullptr)
	{
		for (int i = 0; i < currNode->size(); i++)
		{
			//cout << "index: " << indicie << " contains: " << currNode->at(i) << endl;

			//if the indicie is the desired index, then insert new value and move everything back
			if (indicie == index)
			{
				//this only handles the case of the value fitting in the index
				currNode->insert(index, value);

				//I couldn't get this code to work
				//my intention was to make a new node if the currNode was full, but i couldnt figure out how to check if the array was full
				/*
				//if the array is full insert in new node 
				if (currNode->capacity() >= currNode->size())
				{
					HybridListNode* newNode = nullptr;

					//if currNode is the tail node, reassign the tail
					if (currNode == tail)
					{
						currNode->next = newNode;	//new node goes after tail
						newNode = tail;				//assign tail to new node
						newNode->next = nullptr;	//nullptr is after new tail
					}

					//if anywhere else, squeeze in between currNode and currNode->next
					else
					{
						newNode->next = currNode->next;
						currNode->next = newNode;
					}

					//new block added and value insearted at first point
					newNode->insert(0, value);
					numBlocks++;
				}
				//if array is not full, insert it
				else
					currNode->insert(index, value);

				*/

				break;
				
			}

			indicie++;
			
				
		}
		currNode = currNode->next;
	}

	numElements++;	//value inserted

}


void HybridList::erase(int index)
{
	if (index >= numElements || index < 0)
		throw std::out_of_range("Invalid index " + std::to_string(index));

	HybridListNode* currNode = head;
	int indicie = 0;

	while (currNode != nullptr)
	{
		for (int i = 0; i < currNode->size(); i++)
		{
			//if the indicie is the desired index, then 'delete' it and move the numbers 
			if (indicie == index)
			{
				currNode->erase(index);
				break;
			}
				

			//cout << "index: " << indicie << " contains: " << currNode->at(i) << endl;
			indicie++;
		}
		currNode = currNode->next;
	}

	numElements--;	//element removed

	//delete current node if last value was erased
	if (currNode->size() == 0)
	{
		//this is the last element of the hybrid list
		//if numelements ==0, then reassign head and tail to nullptr
		if (numElements == 0)
		{
			delete head;
			head = tail = nullptr;
			numBlocks--;
		}

		//if currNode is tail, then reassign the tail since its empty
		else if (currNode == tail)
		{
			HybridListNode* tempNode = head;
			while (tempNode->next != tail)
				tempNode = tempNode->next;

			delete tail;
			tail = tempNode;
			tail->next = nullptr;
			numBlocks--;
		}

		//if currNode is head, then reassign the head since its empty
		else if (currNode == head)
		{
			delete head;
			head = currNode->next;
			currNode = currNode->next;
			head->next = currNode->next;
			numBlocks--;
		}

		//if neither are the case, this block is between and needs to be removed between
		else
		{
			HybridListNode* nextNode = currNode->next;
			HybridListNode* prevNode = head;

			while (prevNode != currNode)
				prevNode = prevNode->next;

			delete currNode;
			prevNode->next = nextNode;
			numBlocks--;
		}
		
	}
	
}


//end of my code






void HybridList::clear() {
	HybridListNode* curNode = head, * nextNode = nullptr;
	// Iterate through each node starting from the head and delete it
	while (curNode != nullptr) {
		nextNode = curNode->next;
		delete curNode;
		curNode = nextNode;
	}
	head = tail = nullptr;
	numElements = numBlocks = 0;
}

int main()
{
	/*
	HybridList test;
	test.push_back(1);
	test.push_back(2);
	//test.pop_back();
	//test.insert(1, 5);
	test.erase(0);
	double elem = test.at(1);

	cout << elem << endl;
	*/

	return 0;
}