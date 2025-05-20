#include "qtvar.h"

/*
 * Returns true if the node's variance is less than tolerance.
 */
bool qtvar::prunable(Node* node, const int tol) const {
    /* Your code here! */
    return node->var <= tol;
}
