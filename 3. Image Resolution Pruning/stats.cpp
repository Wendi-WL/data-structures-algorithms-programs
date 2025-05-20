
#include "stats.h"

long stats::square(long num) {
    return num * num;
}

stats::stats(PNG& im) {
    /* Your code here!! */
    vector<long> red0 {im.getPixel(0, 0)->r};
    vector<long> green0 {im.getPixel(0, 0)->g};
    vector<long> blue0 {im.getPixel(0, 0)->b};
    vector<long> sqRed0 {square(im.getPixel(0, 0)->r)};
    vector<long> sqGreen0 {square(im.getPixel(0, 0)->g)};
    vector<long> sqBlue0 {square(im.getPixel(0, 0)->b)};
    for (unsigned y = 1; y < im.height(); y++) {
        red0.push_back(red0[y-1] + im.getPixel(0, y)->r);
        green0.push_back(green0[y-1] + im.getPixel(0, y)->g);
        blue0.push_back(blue0[y-1] + im.getPixel(0, y)->b);
        sqRed0.push_back(sqRed0[y-1] + square(im.getPixel(0, y)->r));
        sqGreen0.push_back(sqGreen0[y-1] + square(im.getPixel(0, y)->g));
        sqBlue0.push_back(sqBlue0[y-1] + square(im.getPixel(0, y)->b));
    }
    sumRed.push_back(red0);
    sumGreen.push_back(green0);
    sumBlue.push_back(blue0);
    sumsqRed.push_back(sqRed0);
    sumsqGreen.push_back(sqGreen0);
    sumsqBlue.push_back(sqBlue0);
    for (unsigned x = 1; x < im.width(); x++) {
        vector<long> xRed {sumRed[x-1][0] + im.getPixel(x, 0)->r};
        vector<long> xGreen {sumGreen[x-1][0] + im.getPixel(x, 0)->g};
        vector<long> xBlue {sumBlue[x-1][0] + im.getPixel(x, 0)->b};
        vector<long> xsqRed {sumsqRed[x-1][0] + square(im.getPixel(x, 0)->r)};
        vector<long> xsqGreen {sumsqGreen[x-1][0] + square(im.getPixel(x, 0)->g)};
        vector<long> xsqBlue {sumsqBlue[x-1][0] + square(im.getPixel(x, 0)->b)};
        for (unsigned y = 1; y < im.height(); y++) {
            xRed.push_back(sumRed[x-1][y] + xRed[y-1] - sumRed[x-1][y-1] + im.getPixel(x, y)->r);
            xGreen.push_back(sumGreen[x-1][y] + xGreen[y-1] - sumGreen[x-1][y-1]+ im.getPixel(x, y)->g);
            xBlue.push_back(sumBlue[x-1][y] + xBlue[y-1] - sumBlue[x-1][y-1] + im.getPixel(x, y)->b);
            xsqRed.push_back(sumsqRed[x-1][y] + xsqRed[y-1] - sumsqRed[x-1][y-1] + square(im.getPixel(x, y)->r));
            xsqGreen.push_back(sumsqGreen[x-1][y] + xsqGreen[y-1] - sumsqGreen[x-1][y-1] + square(im.getPixel(x, y)->g));
            xsqBlue.push_back(sumsqBlue[x-1][y] + xsqBlue[y-1] - sumsqBlue[x-1][y-1] + square(im.getPixel(x, y)->b));
        }
        sumRed.push_back(xRed);
        sumGreen.push_back(xGreen);
        sumBlue.push_back(xBlue);
        sumsqRed.push_back(xsqRed);
        sumsqGreen.push_back(xsqGreen);
        sumsqBlue.push_back(xsqBlue);       
    }
}

long stats::getSum(char channel, pair<int, int> ul, int dim) {
    /* Your code here!! */
    int x = ul.first;
    int y = ul.second;
    long side = pow(2, dim);
    long toSubtract = 0;
    vector<vector<long>>* channelVector;
    switch (channel) {        
        case 'r': channelVector = &sumRed; break;
        case 'g': channelVector = &sumGreen; break;
        case 'b': channelVector = &sumBlue; break;
    }
    if (x != 0) {
        toSubtract += (*channelVector)[x-1][y+side-1];
    }
    if (y != 0) {
        toSubtract += (*channelVector)[x+side-1][y-1];
    }
    if (x != 0 && y != 0) {
        toSubtract -= (*channelVector)[x-1][y-1];
    } 
    return (*channelVector)[x+side-1][y+side-1] - toSubtract;
}

long stats::getSumSq(char channel, pair<int, int> ul, int dim) {
    /* Your code here!! */
    int x = ul.first;
    int y = ul.second;
    long side = pow(2, dim);
    long toSubtract = 0;
    vector<vector<long>>* channelVector;
    switch (channel) {        
        case 'r': channelVector = &sumsqRed; break;
        case 'g': channelVector = &sumsqGreen; break;
        case 'b': channelVector = &sumsqBlue; break;
    }
    if (x != 0) {
        toSubtract += (*channelVector)[x-1][y+side-1];
    }
    if (y != 0) {
        toSubtract += (*channelVector)[x+side-1][y-1];
    }
    if (x != 0 && y != 0) {
        toSubtract -= (*channelVector)[x-1][y-1];
    } 
    return (*channelVector)[x+side-1][y+side-1] - toSubtract;
}

long stats::rectArea(int dim) {
    /* Your code here!! */
    long side = pow(2, dim);
    return square(side);
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int, int> ul, int dim) {
    /* Your code here!! */
    double varR = getSumSq('r', ul, dim) - (square(getSum('r', ul, dim)) / rectArea(dim));
    double varG = getSumSq('g', ul, dim) - (square(getSum('g', ul, dim)) / rectArea(dim));
    double varB = getSumSq('b', ul, dim) - (square(getSum('b', ul, dim)) / rectArea(dim));
    return varR + varG + varB;
}

RGBAPixel stats::getAvg(pair<int, int> ul, int dim) {
    /* Your code here!! */
    unsigned char r = getSum('r', ul, dim)/rectArea(dim);
    unsigned char g = getSum('g', ul, dim)/rectArea(dim);
    unsigned char b = getSum('b', ul, dim)/rectArea(dim);
    return RGBAPixel(r, g, b);
}
