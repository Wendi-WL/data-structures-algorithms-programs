#include <sys/stat.h>

#include <iostream>
#include <vector>

#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include "cs221util/catch.hpp"
#include "qtcount.h"
#include "qtvar.h"
#include "quadtree.h"
#include "stats.h"

using namespace std;
using namespace cs221util;

TEST_CASE("stats::basic rectArea", "[weight=1][part=stats]") {
    PNG data;
    data.resize(2, 2);
    stats s(data);
    long result = s.rectArea(1);

    REQUIRE(result == 4);
}

TEST_CASE("stats::basic getAvg", "[weight=1][part=stats]") {
    PNG data;
    data.resize(2, 2);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            RGBAPixel* p = data.getPixel(i, j);
            p->r = 20 * i + 3 * j;
            p->g = 3 * i + 20 * j;
            p->b = 23 * i + 23 * j;
            p->a = 1.0;
        }
    }
    stats s(data);
    pair<int, int> ul(0, 0);
    RGBAPixel result = s.getAvg(ul, 1);
    RGBAPixel expected(11, 11, 23);

    REQUIRE(result == expected);
}

TEST_CASE("stats::basic variance", "[weight=1][part=stats]") {
    PNG data;
    data.resize(2, 2);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            RGBAPixel* p = data.getPixel(i, j);
            p->r = 20 * i + 3 * j;
            p->g = 3 * i + 20 * j;
            p->b = 23 * i + 23 * j;
            p->a = 1.0;
        }
    }
    stats s(data);
    pair<int, int> ul(0, 0);
    long result = s.getVar(ul, 1);

    REQUIRE(result == 1876);
}

TEST_CASE("qtcount::basic ctor render", "[weight=1][part=qtcount]") {
    PNG img;
    img.readFromFile("images/orig/geo.png");

    qtcount t1(img);

    PNG out = t1.render();

    REQUIRE(out == img);
}

TEST_CASE("qtcount::basic copy", "[weight=1][part=qtcount]") {
    PNG img;
    img.readFromFile("images/orig/geo.png");

    qtcount t1(img);
    qtcount t1copy(t1);

    PNG out = t1copy.render();

    REQUIRE(out == img);
}

TEST_CASE("qtcount::basic prune", "[weight=1][part=qtcount]") {
    PNG img;
    img.readFromFile("images/orig/adasquare.png");
    
    qtcount t1(img);
    t1.prune(3000);
    PNG result = t1.render();

    result.writeToFile("images/my-adaPrune-count.png");

    PNG expected;
    expected.readFromFile("images/soln/given-adaPrune-count.png");

    REQUIRE(result == expected);
}

TEST_CASE("qtcount::basic pruneSize", "[weight=1][part=qtcount]") {
    PNG img;
    img.readFromFile("images/orig/adasquare.png");

    qtcount t1(img);
    int result = t1.pruneSize(3000);

    int expected = 9394;

    REQUIRE(result == expected);
}

TEST_CASE("qtcount::basic idealPrune", "[weight=1][part=qtcount]") {
    PNG img;
    img.readFromFile("images/orig/adasquare.png");

    qtcount t1(img);
    int result = t1.idealPrune(13904);

    int expected = 1366;

    REQUIRE(result == expected);

}

TEST_CASE("qtcount prune then size", "[weight=1][part=qtcount]") {
    PNG img;
    img.readFromFile("images/orig/adasquare.png");

    qtcount t1(img);
        
    REQUIRE(t1.pruneSize(1366) == 13903);
}

TEST_CASE("qtvar::basic prune", "[weight=1][part=qtvar]") {
    PNG img;
    img.readFromFile("images/orig/adasquare.png");

    qtvar t1(img);
    t1.prune(3000);
    PNG result = t1.render();

    // result.writeToFile("images/soln/given-adaPrune-var.png");

    PNG expected;
    expected.readFromFile("images/soln/given-adaPrune-var.png");

    REQUIRE(result == expected);
}

TEST_CASE("qtvar::basic pruneSize", "[weight=1][part=qtvar]") {
    PNG img;
    img.readFromFile("images/orig/adasquare.png");

    qtvar t1(img);
    int result = t1.pruneSize(3000);

    int expected = 15547;

    REQUIRE(result == expected);
}

TEST_CASE("qtvar::basic idealPrune", "[weight=1][part=qtvar]") {
    PNG img;
    img.readFromFile("images/orig/adasquare.png");

    qtvar t1(img);
    int result = t1.idealPrune(13904);

    int expected = 3865;

    REQUIRE(result == expected);
}

TEST_CASE("qtvar prune then size", "[weight=1][part=qtvar]") {
    PNG img;
    img.readFromFile("images/orig/adasquare.png");

    qtvar t1(img);

    REQUIRE(t1.pruneSize(3865) == 13903);
}

// TEST_CASE("comp prune", "[weight=1][part=mytest]") {
//     PNG origIm3;
//     origIm3.readFromFile("images/orig/stanley-totem-poles.png");
//     // qtcount t3(origIm3);
//     // qtcount tCopy3(t3);
//     // tCopy3.prune(3000);
//     // PNG ppic3 = tCopy3.render();
//     // ppic3.writeToFile("images/out/output-prunedstanley-totem-poles.png");
//     // PNG pexpected;
//     // pexpected.readFromFile("images/soln/given-prunedstanley-totem-poles.png");
//     // REQUIRE(ppic3 == pexpected);
    
//     // qtvar v3(origIm3);
//     // qtvar vCopy3(v3);
//     // vCopy3.prune(3000);
//     // PNG vpic3 = vCopy3.render();
//     // vpic3.writeToFile("images/out/output-prunedstanley-totem-poles-var.png");
//     // PNG vexpected;
//     // vexpected.readFromFile("images/soln/given-prunedstanley-totem-poles-var.png");
//     // REQUIRE(vpic3 == vexpected);
    
//     // comparisons

//     qtcount countcomp(origIm3);
//     qtvar varcomp(origIm3);

//     // cout << origIm3.height() << endl;
//     // cout << countcomp.pruneSize(3000) << endl;
//     // cout << varcomp.pruneSize(3000) << endl;
//     // cout << countcomp.idealPrune(countcomp.pruneSize(3000)) << endl;
//     // cout << varcomp.idealPrune(varcomp.pruneSize(3000)) << endl;
//     // cout << countcomp.idealPrune(10000) << endl;
//     // cout << varcomp.idealPrune(10000) << endl;
//     // cout << countcomp.pruneSize(countcomp.idealPrune(10000)) << endl;
//     // cout << varcomp.pruneSize(varcomp.idealPrune(10000)) << endl;

//     countcomp.prune(countcomp.idealPrune(10000));
//     varcomp.prune(varcomp.idealPrune(10000));

//     /*
//     // I wrote two member functions to help me understand the different
//     // compression strategies. I'm leaving this code here, so you
//     // can explore similarly, if you like. The functions have been
//     // removed from the given code, but you can add them if you want!!
//         cout << "count: " << countcomp.count() << endl;
//         cout << "count dim: " << countcomp.dimsum() << endl;
//         cout << "var: " << varcomp.count() << endl;
//         cout << "var dim: " << varcomp.dimsum() << endl;
//     */

//     PNG countpng = countcomp.render();
//     PNG varpng = varcomp.render();

//     countpng.writeToFile("images/out/output-comp-count-stanley.png");
//     varpng.writeToFile("images/out/output-comp-var-stanley.png");

//     PNG cexp;
//     cexp.readFromFile("images/soln/given-comp-count-stanley.png");
//     REQUIRE(countpng == cexp);
//     PNG vexp;
//     vexp.readFromFile("images/soln/given-comp-var-stanley.png");
//     REQUIRE(varpng == vexp);
// }
