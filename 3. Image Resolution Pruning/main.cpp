
// File:        main.cpp
// Author:      cheeren, zhangwil
// Date:        2023-03-23
// Description: Partial test of PA3 functionality
//              Reads Point data from external files
//              Produces PNG images of the point sets

#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include "qtcount.h"
#include "qtvar.h"
#include <iostream>

using namespace cs221util;
using namespace std;

int main() {
    // read in image
    PNG origIm1;
    origIm1.readFromFile("images/orig/KJVFbig.png");
    PNG origIm2;
    origIm2.readFromFile("images/orig/adasquare.png");
    PNG origIm3;
    origIm3.readFromFile("images/orig/stanley-totem-poles.png");

    // use it to build a quadtree
    qtcount t1(origIm1);
    qtcount tCopy1(t1);
    qtcount t2(origIm2);
    qtcount tCopy2(t2);
    qtcount t3(origIm3);
    qtcount tCopy3(t3);

    // prune the quadtree
    tCopy1.prune(10000);
    tCopy2.prune(10000);
    tCopy3.prune(3000);

    // render the quadtree
    PNG ppic1 = tCopy1.render();
    PNG ppic2 = tCopy2.render();
    PNG ppic3 = tCopy3.render();

    ppic1.writeToFile("images/out/output-prunedKJVFbig.png");
    ppic2.writeToFile("images/out/output-prunedadasquare.png");
    ppic3.writeToFile("images/out/output-prunedstanley-totem-poles.png");

    // use it to build a quadtree
    qtvar v1(origIm1);
    qtvar vCopy1(v1);
    qtvar v2(origIm2);
    qtvar vCopy2(v2);
    qtvar v3(origIm3);
    qtvar vCopy3(v3);

    // prune the quadtree
    vCopy1.prune(10000);
    vCopy2.prune(10000);
    vCopy3.prune(3000);

    // render the quadtree
    PNG vpic1 = vCopy1.render();
    PNG vpic2 = vCopy2.render();
    PNG vpic3 = vCopy3.render();

    vpic1.writeToFile("images/out/output-prunedKJVFbig-var.png");
    vpic2.writeToFile("images/out/output-prunedadasquare-var.png");
    vpic3.writeToFile("images/out/output-prunedstanley-totem-poles-var.png");

    // comparisons

    qtcount countcomp(origIm3);
    qtvar varcomp(origIm3);

    countcomp.prune(countcomp.idealPrune(10000));
    varcomp.prune(varcomp.idealPrune(10000));

    /*
    // I wrote two member functions to help me understand the different
    // compression strategies. I'm leaving this code here, so you
    // can explore similarly, if you like. The functions have been
    // removed from the given code, but you can add them if you want!!
        cout << "count: " << countcomp.count() << endl;
        cout << "count dim: " << countcomp.dimsum() << endl;
        cout << "var: " << varcomp.count() << endl;
        cout << "var dim: " << varcomp.dimsum() << endl;
    */

    PNG countpng = countcomp.render();
    PNG varpng = varcomp.render();

    countpng.writeToFile("images/out/output-comp-count-stanley.png");
    varpng.writeToFile("images/out/output-comp-var-stanley.png");

    // MY IMAGES
    // read in image
    PNG i1;
    i1.readFromFile("images/orig/rocks.png");
    PNG i2;
    i2.readFromFile("images/orig/bench.png");
    PNG i3;
    i3.readFromFile("images/orig/plane.png");

    // use it to build a quadtree
    qtcount c1(i1);
    qtcount c2(i2);
    qtcount c3(i3);
    qtvar var1(i1);
    qtvar var2(i2);
    qtvar var3(i3);
    
    // prune the quadtree
    c1.prune(c1.idealPrune(10000));
    c2.prune(c2.idealPrune(10000));
    c3.prune(c3.idealPrune(10000));
    var1.prune(var1.idealPrune(10000));
    var2.prune(var2.idealPrune(10000));
    var3.prune(var3.idealPrune(10000));

    // render the quadtree
    PNG cpng1 = c1.render();
    PNG cpng2 = c2.render();
    PNG cpng3 = c3.render();
    PNG vpng1 = var1.render();
    PNG vpng2 = var2.render();
    PNG vpng3 = var3.render();

    cpng1.writeToFile("images/out/output-qtcount-prunedrocks.png");
    cpng2.writeToFile("images/out/output-qtcount-prunedbench.png");
    cpng3.writeToFile("images/out/output-qtcount-prunedplane.png");
    vpng1.writeToFile("images/out/output-qtvar-prunedrocks.png");
    vpng2.writeToFile("images/out/output-qtvar-prunedbench.png");
    vpng3.writeToFile("images/out/output-qtvar-prunedplane.png");

    return 0;
}
