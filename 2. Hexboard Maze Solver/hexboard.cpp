#include "hexboard.h"

#include <iostream>

#include "queue.h"
#include "stack.h"

/**
 * Constructor. Creates a board with given radius, creating new HexCells and inserting them into this->cells by calling createBoard(). The default start_coord and end_coord are (0, 0).
 * @note There is no maze yet! The board is just a beehive for now.
 * @param rad The radius of the board
 */
HexBoard::HexBoard(int rad) {
    /**
     * @todo Your code here!
     */
    radius = rad;
    start_coord = {0, 0};
    end_coord = {0, 0};
    longest_path_dist = 0;
    create_board();
    std::cout << "done" << std::endl;
}

// Frees all dynamically allocated memory associated with the board.
HexBoard::~HexBoard() {
    /**
     * @todo Your code here!
     */
    for (auto coord_hc : cells) {
        delete coord_hc.second;
    }
}

/**
 * Creates all neccessary HexCells up to the given radius and insert them into this->cells.
 */
void HexBoard::create_board() {
    /**
     * @todo Your code here!
     */
    for (int q = -radius; q <= radius; q++) {
        if (q < 0) {
            for (int r = -radius-q; r <= radius; r++) {
                cells[{q, r}] = new HexCell({q, r});
            }
        }
        else {
            for (int r = -radius; r <= radius-q; r++) {
                cells[{q, r}] = new HexCell({q, r});
            }
        }
    }
}

/**
 * Gets the coordinates of the six neighbours of coord, in the sides order specified in HexCell.h.
 * @param coord The input coordinate.
 */
vector<pair<int, int>> HexBoard::get_neigh_coords(const pair<int, int>& coord) const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    int q = coord.first;
    int r = coord.second;
    return {{q, r-1}, {q+1, r-1}, {q+1, r}, {q, r+1}, {q-1, r+1}, {q-1, r}};
}

/**
 * Link two cells at the given coordinates by setting each cell's wall to false in the other cell's direction.
 * @param coord1 A coordinate of a HexCell to be linked.
 * @param coord2 A coordinate of a HexCell to be linked.
 * @note remember to link both directions!
 * REQUIRE: the two coords are neighbours
 */
void HexBoard::link(const pair<int, int>& coord1, const pair<int, int>& coord2) const {
    /**
     * @todo Your code here!
     */
    HexCell* cell1 = cells.find(coord1)->second;
    HexCell* cell2 = cells.find(coord2)->second;
    cell1->walls[cell1->get_neighbour_side(cell2)] = false;
    cell2->walls[cell2->get_neighbour_side(cell1)] = false;
}

/**
 * @param coord1 A coordinate of a HexCell
 * @param coord2 A coordinate of a HexCell
 * @return The cell distance (ignoring walls) between coord1 and coord2.
 */
int HexBoard::distance(const pair<int, int>& coord1, const pair<int, int>& coord2) const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    int dq = coord2.first - coord1.first;
    int dr = coord2.second - coord1.second;
    if ((dq > 0 && dr > 0) || (dq < 0 && dr < 0)) {
        return abs(dq+dr);
    } else {
        return std::max(abs(dq), abs(dr));
    }
}

/**
 * @return true if coord is at the edge of the board, false otherwise.
 */
bool HexBoard::is_edge(const pair<int, int>& coord) const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    return distance({0, 0}, coord) == radius;
}

/**
 * Traverses the board via dfs to generate the maze, updating and keeping track of:
 * A. The largest path distance from start to an edge cell so far (this is not longest_path_dist!)

 * The algorithm goes as follows:
 * 0. Set the start_coord member variable
 * 1. Seed this->rng with seed
 * 2. Add the start_coord to a stack, and mark it as visited
 * 3. While the stack is not empty:

 *   a. Peek the top of the stack (call it curr_coord)
 *   b. Use choose_neighbour to choose the neighbour to visit
 *   c. If the neighbour exists, for that neighbour (call it neigh_cell) do:

 *     i. Link curr_coord with neigh_coord
 *     ii. Push neigh_coord into the stack, and mark it as visited
 *     iii. Update the neigh_cell's path distance to start
 *     iv. If necessary, update length of longest path so far (longest_path_dist)
 *     v. Update the end coordinate only if its path distance to start is strictly greater than the largest path distance from start to an edge cell so far.

 *   d. Otherwise (if choose_neighbour returns nullptr), pop the stack.

 * @param start The {q, r} coordinate of the start of the maze.
 * @param branch_prob Specifies how often it should "branch out" when choosing neighbours.
 *                    A small branch_prob means neighbours of the same dist from the start_coord are preferred
 *                    A large branch_prob means neighbours of a different dist from the start_coord are preferred
 * @param seed The seed used for the rng
 * REQUIRE: create_board() is already called
 */
void HexBoard::generate_maze(pair<int, int> start, double branch_prob, int seed) {
    /**
     * @todo Your code here!
     */
    std::cout << "in genmaze" << std::endl;
    start_coord = start;
    rng.seed(seed);
    Stack<pair<int, int>> stack;
    set<pair<int, int>> visited;
    stack.push(start_coord);
    visited.insert(start_coord);
    int path_dist_so_far = 0;
    while (!stack.is_empty()) {
        
        std::cout << "stack nonempty" << std::endl;
        pair<int, int> curr_coord = stack.peek();
        HexCell* neigh_cell = choose_neighbour(curr_coord, visited, branch_prob);
        if (neigh_cell) {
            pair<int, int> neigh_coord = neigh_cell->qr;
            path_dist_so_far++;
            if (visited.find(neigh_coord) == visited.end()) {
                link(curr_coord, neigh_coord);
                stack.push(neigh_coord);
                visited.insert(neigh_coord);
                neigh_cell->path_dist_from_start = path_dist_so_far;        
                if (path_dist_so_far > longest_path_dist) {
                    longest_path_dist = path_dist_so_far;
                }
                if (is_edge(neigh_coord)) {
                    if (path_dist_so_far > cells.find(end_coord)->second->path_dist_from_start) {
                        end_coord = neigh_coord;
                    }
                }
            }
        } else {
            stack.pop();
            path_dist_so_far--;
        }
    }
    
    std::cout << "done genmaze" << std::endl;
}

/**
 * Populate (member variable) solution as a list of coordinates from start_coord to end_coord, represented as {q, r} pairs.

 * REQUIRE: generate_maze must be called already
 */
void HexBoard::solve_maze() {
    /**
     * @todo Your code here!
     */
    
    std::cout << "in solvemaze" << std::endl;
    vector<pair<int, int>> path;
    Stack<pair<int, int>> stack;
    set<pair<int, int>> visited;
    stack.push(start_coord);
    while (!stack.is_empty()) {
        
        std::cout << "stack nonempty sm" << std::endl;
        pair<int, int> curr_coord = stack.peek();
        path.push_back(curr_coord);
        if (curr_coord == end_coord) {   
            solution = path;
            break;
        }
        stack.pop();    
        visited.insert(curr_coord);   
        HexCell* curr_cell = cells.find(curr_coord)->second;
        for (int side = 0; side < 6; side++) {
            if (!curr_cell->walls[side]) {
                pair<int, int> neigh_coord = get_neigh_coords(curr_coord)[side];
                if (visited.find(neigh_coord) == visited.end()) {
                    stack.push(neigh_coord);
                }
            }
        }
        int backtrack_dist = 1 + cells.find(curr_coord)->second->path_dist_from_start - cells.find(stack.peek())->second->path_dist_from_start;
        while (backtrack_dist > 0) {
            path.pop_back();
            backtrack_dist--;
        }
    }
    
    std::cout << "solved" << std::endl;
}