#include "chain.h"
#include "chain_given.cpp"
#include <cmath>
#include <iostream>

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain()
{
    clear();
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block &ndata)
{
    Node* last = walk(head_, size());
    last->next = new Node(ndata);
    last->next->next = head_;
    length_++;
}


/**
 * Swaps the two nodes at the indexes "node1" and "node2".
 * The indexes of the nodes are 1 based.
 * assumes i and j are valid (in {1,length_} inclusive)
 * 
 */
void Chain::swap(int i, int j)
{
    Node* iNodePrev = walk(head_, i-1);
    Node* iNode = walk(head_, i);
    Node* iNodeNext = walk(head_, i+1);
    Node* jNodePrev = walk(head_, j-1);
    Node* jNode = walk(head_, j);

    iNodePrev->next = jNode;
    jNodePrev->next = iNode;
    iNode->next = jNode->next;
    jNode->next = iNodeNext;
}

/**
 * Reverses the chain
 */
void Chain::reverse()
{
    int currPos = size();
    Node* last = walk(head_, currPos);
    while (currPos > 0) {
        Node* currNode = walk(head_, currPos);
        Node* prevNode = walk(head_, currPos - 1);
        currNode->next = prevNode;
        currPos--;
    }
    head_->next = last;
}

/*
* Modifies the current chain by "rotating" every k nodes by one position.
* In every k node sub-chain, remove the first node, and place it in the last 
* position of the sub-chain. If the last sub-chain has length less than k,
* then don't change it at all. 
* Some examples with the chain a b c d e:
*   k = 1: a b c d e
*   k = 2: b a d c e
*   k = 3: b c a d e
*   k = 4: b c d a e
*/
void Chain::rotate(int k)
{
    if (k == 1) return;
    int subchainStart = 1;
    int subchainEnd = k;
    while (subchainEnd <= size()) {
        Node* prev = walk(head_, subchainStart - 1);
        Node* toLast = walk(head_, subchainStart);
        Node* toSecondLast = walk(head_, subchainEnd);
        prev->next = toLast->next;
        toLast->next = toSecondLast->next;
        toSecondLast->next = toLast;
        subchainStart += k;
        subchainEnd += k;
    }
}

/**
 * Destroys ALL dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear()
{
    while (!empty()) {
        Node* last = walk(head_, size());
        delete last;
        length_--;
    }
    delete head_;
}

/* makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other)
{
    width_ = other.width_;
    height_ = other.height_;
    length_ = 0;

    head_ = new Node();
    Node* toCopy = other.head_;
    while (this->size() < other.size()) {
        insertBack(toCopy->next->data);
        toCopy = toCopy->next;
    }
    Node* last = walk(head_, size());
    last->next = head_;
}
