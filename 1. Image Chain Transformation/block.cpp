#include "block.h"
#include <cmath>
#include <iostream>

int Block::width() const
{
    if (data.size() > 0) {
        return data[0].size();
    } else {
        return 0;
    }
}
int Block::height() const
{
    return data.size();
}

void Block::render(PNG &im, int column, int row) const
{
    RGBAPixel* pixel;
    for (int x = column; x < column + this->width(); x++) {
        for (int y = row; y < row + this->height(); y++) {
            pixel = im.getPixel(x, y);
            *pixel = data[y - row][x - column];
        }
    }
}

void Block::build(PNG &im, int column, int row, int width, int height)
{
    data.clear();
    RGBAPixel* pixel;
    for (int r = row; r < row + height; r++) {
        vector<RGBAPixel> row_vector;
        for (int c = column; c < column + width; c++) {
            pixel = im.getPixel(c, r);
            row_vector.push_back(*pixel);
        }
        data.push_back(row_vector);
    }
}

void Block::flipVert()
{
    for (int r = 0; r < this->height() / 2; r++) {
        vector<RGBAPixel> temp = data[r];
        data[r] = data[this->height() - 1 - r];
        data[this->height() - 1 - r] = temp;
    }
}

void Block::flipHoriz()
{
    for (int r = 0; r < this->height(); r++) {
        for (int c = 0; c < this->width() / 2; c++) {
            RGBAPixel temp = data[r][c];
            data[r][c] = data[r][this->width() - 1 - c];
            data[r][this->width() - 1 - c] = temp;
        }
    }
}

void Block::rotateRight()
{
    vector<vector<RGBAPixel>> old = data;
    for (int r = 0; r < this->height(); r++) {
        for (int c = 0; c < this->width(); c++) {
            data[c][this->height() - 1 - r] = old[r][c];
        }
    }
}
