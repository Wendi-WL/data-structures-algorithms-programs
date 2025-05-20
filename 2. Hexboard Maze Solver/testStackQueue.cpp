#define CATCH_CONFIG_MAIN
#include "cs221util/catch.hpp"

#include <iostream>

#include "queue.h"
#include "stack.h"



using namespace std;

TEST_CASE("stack::basic functions", "[weight=1][part=stack]") {
    // cout << "Testing Stack..." << endl;
    Stack<int> intStack;
    vector<int> result;
    vector<int> expected;
    for (int i = 10; i > 0; i--) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intStack.push(i);
    }
    while (!intStack.is_empty()) {
        result.push_back(intStack.pop());
    }
    REQUIRE(result == expected);
}

TEST_CASE("queue::basic functions", "[weight=1][part=queue]") {
    Queue<int> intQueue;
    vector<int> result;
    vector<int> expected;
    for (int i = 1; i <= 10; i++) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intQueue.enqueue(i);
    }
    while (!intQueue.is_empty()) {
        result.push_back(intQueue.dequeue());
    }
    REQUIRE(result == expected);
}

TEST_CASE("stack::peek", "[weight=1][part=stack]") {
    Stack<int> s;
    for (int i = 1; i <= 10; i++) {
        s.push(i);
    }
    REQUIRE(s.peek() == 10);
}

TEST_CASE("queue::peek", "[weight=1][part=queue]") {
    Queue<int> q;
    for (int i = 1; i <= 10; i++) {
        q.enqueue(i);
    }
    REQUIRE(q.peek() == 1);
}

TEST_CASE("quack::pop_right pop_left no resize", "[weight=1][part=quack]") {
    Quack<int> quack;
    for (int i = 1; i <= 10; i++) {
        quack.push_right(i);
    }
    for (int i = 0; i < 5; i++) {
        quack.pop_right();
    }
    quack.pop_left();
    quack.pop_left(); //just twice
    REQUIRE(quack.peekL() == 3);
    REQUIRE(quack.peekR() == 5);
}

