#include "qtcount.h"

/*
 * Return true if all of the leaves in the node's subtree have colour-distance within tolerance of its average. 
 * Distances between colours are computed as the sum, over each colour channel, of the pixel value differences, squared.
 */
bool qtcount::prunable(Node* node, const int tol) const {
    /* Your code here */
    // return false;
    return prunableHelper(node, tol, node->avg);
}

/*
 * Helper function for prunable. 
 */
bool qtcount::prunableHelper(Node* subroot, const int tol, const RGBAPixel avg) const {
    if (!subroot->NW) {
        return (pow((subroot->avg.r - avg.r), 2) 
        + pow((subroot->avg.g - avg.g), 2) 
        + pow((subroot->avg.b - avg.b), 2) 
        <= tol); 
    }
    return prunableHelper(subroot->NW, tol, avg)
    && prunableHelper(subroot->NE, tol, avg)
    && prunableHelper(subroot->SW, tol, avg)
    && prunableHelper(subroot->SE, tol, avg);
}
