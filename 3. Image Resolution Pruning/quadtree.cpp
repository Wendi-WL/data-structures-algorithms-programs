
/**
 *
 * quadtree (pa3)
 * quadtree.cpp
 * This file will be used for grading.
 *
 */

#include "quadtree.h"
using namespace std;

#include <iostream>

// Node constructor, given.
quadtree::Node::Node(pair<int, int> ul, int d, RGBAPixel a, double v)
    : upLeft(ul), dim(d), avg(a), var(v), NW(nullptr), NE(nullptr), SE(nullptr), SW(nullptr) {}

// quadtree destructor, given.
quadtree::~quadtree() {
    clear();
}
// quadtree copy constructor, given.
quadtree::quadtree(const quadtree& other) {
    copy(other);
}
// quadtree assignment operator, given.
quadtree& quadtree::operator=(const quadtree& rhs) {
    if (this != &rhs) {
        clear();
        copy(rhs);
    }
    return *this;
}

quadtree::quadtree(PNG& imIn) {
    /* Your code here! */
    int resizedSide = pow(2, (int) log2(imIn.height()));
    imIn.resize(resizedSide, resizedSide);
    stats s = stats(imIn);
    pair<int, int> ul(0,0);
    edge = imIn.height();
    root = buildTree(s, ul, log2(edge));
}

quadtree::Node* quadtree::buildTree(stats& s, pair<int, int> ul, int dim) {
    /* Your code here! */
    Node* n = new Node(ul, dim, s.getAvg(ul, dim), s.getVar(ul, dim));
    if (dim == 0) {
        return n;
    }
    long side = pow(2, dim);
    int x = ul.first;
    int y = ul.second;
    pair<int, int> ulNW(x, y);
    pair<int, int> ulNE(x+side/2, y); 
    pair<int, int> ulSE(x+side/2, y+side/2); 
    pair<int, int> ulSW(x, y+side/2); 
    n->NW = buildTree(s, ulNW, dim-1);
    n->NE = buildTree(s, ulNE, dim-1);
    n->SW = buildTree(s, ulSW, dim-1);
    n->SE = buildTree(s, ulSE, dim-1);
    return n;
}

PNG quadtree::render() const {
    /* Your code here! */
    PNG img(edge, edge);
    renderHelper(img, root);
    return img;
}

void quadtree::renderHelper(PNG &img, Node* subroot) const {
    if (!subroot->NW) {
        int side = pow(2, subroot->dim);
        unsigned x = subroot->upLeft.first;
        unsigned y = subroot->upLeft.second;
        if (side == 1) {
            *img.getPixel(x, y) = subroot->avg;
            return;
        } 
        for (unsigned xi = x; xi < x + side; xi++) {
            for (unsigned yi = y; yi < y + side; yi++) {
                *img.getPixel(xi, yi) = subroot->avg;
            }
        }
        return;
    }
    renderHelper(img, subroot->NW);
    renderHelper(img, subroot->NE);
    renderHelper(img, subroot->SW);
    renderHelper(img, subroot->SE);
}

int quadtree::idealPrune(const int leaves) const {
    /* Your code here! */
    unsigned int min = 0;
    unsigned int max = 3*255*255;
    unsigned int tol;
    int tolLeaves;
    while (min < max) {
        tol = (max+min)/2;
        tolLeaves = pruneSize(tol);
        if (tolLeaves <= leaves) {
            max = tol;
        } else {
            min = tol+1;
        } 
    } 
    return max;
}

int quadtree::pruneSize(const int tol) const {
    /* Your code here! */
    return pow(4, root->dim) - pruneSizeHelper(tol, root);
}

int quadtree::pruneSizeHelper(const int tol, Node* subroot) const {
    if (!subroot) {
        return 0;
    }
    if (prunable(subroot, tol)) {
        return pow(4, subroot->dim) - 1;
    }

    return pruneSizeHelper(tol, subroot->NW) +
           pruneSizeHelper(tol, subroot->NE) +
           pruneSizeHelper(tol, subroot->SW) +
           pruneSizeHelper(tol, subroot->SE);
}

void quadtree::prune(const int tol) {
    /* Your code here! */
    pruneHelper(tol, root);
}

void quadtree::pruneHelper(const int tol, Node* subroot) {
    if (!subroot->NW) {
        return;
    }
    if (prunable(subroot, tol)) {
        clearHelper(subroot);
    } else {
        pruneHelper(tol, subroot->NW);
        pruneHelper(tol, subroot->NE);
        pruneHelper(tol, subroot->SW);
        pruneHelper(tol, subroot->SE);
    }
}

void quadtree::clear() {
    /* your code here */
    clearHelper(root);
    delete root;
    root = NULL;
}

void quadtree::clearHelper(Node* subroot) {
    if (!subroot->NW) {
        return;
    }
    clearHelper(subroot->NW);
    clearHelper(subroot->NE);
    clearHelper(subroot->SW);
    clearHelper(subroot->SE);
    delete subroot->NW;
    delete subroot->NE;
    delete subroot->SW;
    delete subroot->SE;
    subroot->NW = NULL;
    subroot->NE = NULL;
    subroot->SW = NULL;
    subroot->SE = NULL;
}

void quadtree::copy(const quadtree& other) {
    /* your code here */
    Node* otherRootCopy = other.root;
    root = new Node(otherRootCopy->upLeft, otherRootCopy->dim, otherRootCopy->avg, otherRootCopy->var);
    edge = other.edge;
    copyHelper(otherRootCopy, root);
}

void quadtree::copyHelper(Node*& other, Node* subroot) { 
    if (!other->NW) {
        return;
    }
    subroot->NW = new Node(other->NW->upLeft, other->NW->dim, other->NW->avg, other->NW->var);
    subroot->NE = new Node(other->NE->upLeft, other->NE->dim, other->NE->avg, other->NE->var);
    subroot->SW = new Node(other->SW->upLeft, other->SW->dim, other->SW->avg, other->SW->var);
    subroot->SE = new Node(other->SE->upLeft, other->SE->dim, other->SE->avg, other->SE->var);
    copyHelper(other->NW, subroot->NW);
    copyHelper(other->NE, subroot->NE);
    copyHelper(other->SW, subroot->SW);
    copyHelper(other->SE, subroot->SE);
}