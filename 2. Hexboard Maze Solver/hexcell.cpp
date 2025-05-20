#include "hexcell.h"

/**
 * HexCell constructor. Initializes all walls to be true and path_dist_from_start to 0.
 * @param QR Axial coordinates of the hex cell
 */
HexCell::HexCell(std::pair<int, int> QR) {
    /**
     * @todo Your code here!
     */
    qr = QR;
    path_dist_from_start = 0;
    std::fill_n(walls, 6, true);
}

/**
 * Gets the side of a neighbour. Each side is represented with an int in [0,5].
 * See above for the definition of the sides
 * @param cell A neighbouring HexCell
 * @return The side of cell
 * REQUIRE: cell is a neighbour of this cell
 */
int HexCell::get_neighbour_side(const HexCell* cell) const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    if (cell->qr.first > qr.first) {
        if (cell->qr.second == qr.second) {
            return SE;
        } else {
            return NE;
        }
    } else if (cell->qr.first < qr.first) {
        if (cell->qr.second == qr.second) {
            return NW;
        } else {
            return SW;
        }
    } else {
        if (cell->qr.second > qr.second) {
            return S;
        } else {
            return N;
        }
    }
}