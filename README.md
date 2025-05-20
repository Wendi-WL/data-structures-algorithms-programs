# Programs with applications of Data Structures and Algorithms

## 1. Image Chain Transformation

PNG images are divided into evenly-sized blocks, then the blocks are connected in a chain using a linked list data structure.<br><br>
The program contains various methods that allow for the transformation and manipulation of the image's blocks (e.g., rotating, flipping) and the blocks' order in the chain (e.g., swapping, reversing).<br>

## 2. Hexboard Maze Solver

A hexboard is a board consisting of hexagonal cells (i.e., hexcells), with walls between some cells but not others to form a maze.<br><br>
Depth-first search (DFS), using a stack, is employed to generate the maze.<br>
The maze is solved using a similar DFS, with the program returning a solution of the path through the maze.<br><br>
This program also contains implementations of stack and queue data structures.

## 3. Image Resolution Pruning

PNG images are represented using a quadtree data structure. This is accomplished by dividing the image into 4 quadrants, and repeating the operation on each quadrant recursively, until the quadrant size is 1 pixel. The quadtree begins as a perfect tree, and is a full tree after pruning (each node has 0 or 4 children).<br><br>
Neighbouring quadrants with similar RGB values are pruned from the quadtree by combining the quadrants' 4 RGB values into 1 average RGB value. This decreases the image resolution in similar areas while preserving the areas of high contrast, to prevent loss in the image's content. The quadtree nodes are pruned according to a pruning strategy and value for tolerance. <br><br>
The program prunes images using two pruning strategies:
* By count (qtcount): prunes the 4 quadrants if the sum of their differences from the average colour is below a certain tolerance.
* By variance (qtvar): prunes the 4 quadrants if their variance is below a certain tolerance.