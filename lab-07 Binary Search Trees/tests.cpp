/*
  Copyright (c) 2021
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, S. Caplan, A. Danner, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2021
  CPSC 035: Data Structures and Algorithms
*/

#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include <UnitTest++/UnitTest++.h>

#include "adts/BST.h"
#include "adts/list.h"
#include "linkedBST.h"
#include "linkedBSTNode.h"

using namespace std;

/**
 * This helper function will build a small BST on which we can perform
 * experiments.  We can call the methods of the BST
 * in a specific order to make sure it puts the nodes where we want them
 * (assuming, of course, that the insert and get functions work correctly).
 * Our tree will look like this:
 * @verbatim
 *         6
 *        / \
 *       /   \
 *      2     7
 *     / \     \
 *    1   4     9
 *       /
 *      3
 * @endverbatim
 * @return An example BST.  The caller is responsible for deleting this BST.
 */
LinkedBST<int, string>* makeExampleBST() {
    LinkedBST<int, string>* bst = new LinkedBST<int, string>();
    bst->insert(6, "6");
    bst->insert(2, "2");
    bst->insert(7, "7");
    bst->insert(1, "1");
    bst->insert(4, "4");
    bst->insert(9, "9");
    bst->insert(3, "3");
    bst->checkInvariants();
    return bst;
}


TEST(emptyBST) {
    LinkedBST<int, string>* bst = new LinkedBST<int, string>();
    CHECK_EQUAL(0, bst->getSize());
    CHECK(bst->isEmpty());
    bst->checkInvariants();
    delete bst;
}


TEST(exampleBST) {
    // Since we have to respect the BST interface -- we can't look
    // directly at the BST nodes -- we have to test the example BST to
    // make sure that it behaves like we'd think.  If this test fails,
    // then either the insert or the get method is broken and it's
    // hard to tell which.  The upside is that we test both the insert
    // and get functions with this test.
    LinkedBST<int, string>* bst = makeExampleBST();
    for (int i = 1; i <= 9; i++) {
        if (i != 5 && i != 8) {
            CHECK_EQUAL(to_string(i), bst->get(i));
        }
    }
    delete bst;
}

TEST(exampleBSTSize) {
    LinkedBST<int, string>* bst = makeExampleBST();
    CHECK_EQUAL(7, bst->getSize());
    CHECK(!bst->isEmpty());
    delete bst;
}

// NOTE: Be sure to make frequent use of the checkInvariants method
// which verifies that your BST contains the correct number of nodes
// and has properly implemented the BST property.

//test LinkedBST<K,V>::update
TEST(updateBST) {
    LinkedBST<int, string>* bst = makeExampleBST();
    bst->update(9, "10");
    bst->update(1, "0");
    CHECK_EQUAL("10", bst->get(9));
    CHECK_EQUAL("0", bst->get(1));
    CHECK(!bst->isEmpty());
    bst->checkInvariants();
    delete bst;
}

//test LinkedBST<K,V>::contains
TEST(containsBST) {
    LinkedBST<int, string>* bst = makeExampleBST();
    CHECK(bst->contains(1));
    CHECK(bst->contains(2));
    CHECK(bst->contains(9));
    CHECK(!bst->contains(5));
    delete bst;
}

//test LinkedBST<K,V>::remove
TEST(removeBST) {
    LinkedBST<int, string>* bst = makeExampleBST();
    bst->remove(9);
    CHECK_EQUAL(6, bst->getSize());
    bst->remove(1);
    CHECK_EQUAL(5, bst->getSize());
    bst->checkInvariants();
    delete bst;
}

//test LinkedBST<K,V>::getKeys
TEST(getKeysBST) {
    LinkedBST<int, string>* bst = makeExampleBST();
    vector<int> vector1 = bst->getKeys();
    CHECK_EQUAL(6, vector1[0]);
    CHECK_EQUAL(9, vector1[6]);
    CHECK_EQUAL(1, vector1[2]);
    CHECK_EQUAL(4, vector1[3]);
    bst->checkInvariants();
    delete bst;
}

//test LinkedBST<K,V>::getItems
TEST(getItemsBST) {
    LinkedBST<int, string>* bst = makeExampleBST();
    vector<pair<int, string>> vector1 = bst->getItems();
    CHECK_EQUAL(6, vector1[0].first);
    CHECK_EQUAL(9, vector1[6].first);
    CHECK_EQUAL(1, vector1[2].first);
    CHECK_EQUAL(4, vector1[3].first);
    bst->checkInvariants();
    delete bst;
}

//test LinkedBST<K,V>::getHeight
TEST(getHeightBST) {
    LinkedBST<int, string>* bst = makeExampleBST();
    CHECK_EQUAL(3, bst->getHeight());
    bst->remove(3);
    CHECK_EQUAL(2, bst->getHeight());
    bst->checkInvariants();
    delete bst;
    
    bst = new LinkedBST<int, string>();
    CHECK_EQUAL(-1, bst->getHeight());
    delete bst;
}

//test LinkedBST<K,V>::getMax
TEST(getMaxBST) {
    LinkedBST<int, string>* bst = makeExampleBST();
    CHECK_EQUAL(9, bst->getMaxKey());
    bst->remove(9);
    CHECK_EQUAL(7, bst->getMaxKey());
    bst->checkInvariants();
    delete bst;
}

//test LinkedBST<K,V>::getMin
TEST(getMinBST) {
    LinkedBST<int, string>* bst = makeExampleBST();
    CHECK_EQUAL(1, bst->getMinKey());
    bst->remove(1);
    CHECK_EQUAL(2, bst->getMinKey());
    bst->checkInvariants();
    delete bst;
}

//test LinkedBST<K,V>::getPreOrder
TEST(examplePreOrderTraversal) {
    LinkedBST<int, string>* bst = makeExampleBST();
    vector<pair<int, string>> traversal = bst->traversePreOrder();

    // build vector containing what the ordering should be
    vector<pair<int, string>> expected;
    expected.push_back(pair<int, string>(6, "6"));
    expected.push_back(pair<int, string>(2, "2"));
    expected.push_back(pair<int, string>(1, "1"));
    expected.push_back(pair<int, string>(4, "4"));
    expected.push_back(pair<int, string>(3, "3"));
    expected.push_back(pair<int, string>(7, "7"));
    expected.push_back(pair<int, string>(9, "9"));
    REQUIRE CHECK_EQUAL(expected.size(), traversal.size());
    for (int i = 0; i < expected.size(); i++) {
        CHECK_EQUAL(expected[i].first, traversal[i].first);
        CHECK_EQUAL(expected[i].second, traversal[i].second);
    }
    delete bst;
}

//test LinkedBST<K,V>::getInOrder
TEST(exampleInOrderTraversal) {
    LinkedBST<int, string>* bst = makeExampleBST();
    vector<pair<int, string>> traversal = bst->traverseInOrder();

    // build vector containing what the ordering should be
    vector<pair<int, string>> expected;
    expected.push_back(pair<int, string>(1, "1"));
    expected.push_back(pair<int, string>(2, "2"));
    expected.push_back(pair<int, string>(3, "3"));
    expected.push_back(pair<int, string>(4, "4"));
    expected.push_back(pair<int, string>(6, "6"));
    expected.push_back(pair<int, string>(7, "7"));
    expected.push_back(pair<int, string>(9, "9"));
    REQUIRE CHECK_EQUAL(expected.size(), traversal.size());
    for (int i = 0; i < expected.size(); i++) {
        CHECK_EQUAL(expected[i].first, traversal[i].first);
        CHECK_EQUAL(expected[i].second, traversal[i].second);
    }
    delete bst;
}

//LinkedBST<K,V>::getPostOrder
TEST(examplePostOrderTraversal) {
    LinkedBST<int, string>* bst = makeExampleBST();
    vector<pair<int, string>> traversal = bst->traversePostOrder();

    // build vector containing what the ordering should be
    vector<pair<int, string>> expected;
    expected.push_back(pair<int, string>(1, "1"));
    expected.push_back(pair<int, string>(3, "3"));
    expected.push_back(pair<int, string>(4, "4"));
    expected.push_back(pair<int, string>(2, "2"));
    expected.push_back(pair<int, string>(9, "9"));
    expected.push_back(pair<int, string>(7, "7"));
    expected.push_back(pair<int, string>(6, "6"));
    REQUIRE CHECK_EQUAL(expected.size(), traversal.size());
    for (int i = 0; i < expected.size(); i++) {
        CHECK_EQUAL(expected[i].first, traversal[i].first);
        CHECK_EQUAL(expected[i].second, traversal[i].second);
    }
    delete bst;
}

//test LinkedBST<K,V>::getLevelOrder
TEST(exampleLevelOrderTraversal) {
    LinkedBST<int, string>* bst = makeExampleBST();
    vector<pair<int, string>> traversal = bst->traverseLevelOrder();

    // build vector containing what the ordering should be
    vector<pair<int, string>> expected;
    expected.push_back(pair<int, string>(6, "6"));
    expected.push_back(pair<int, string>(2, "2"));
    expected.push_back(pair<int, string>(7, "7"));
    expected.push_back(pair<int, string>(1, "1"));
    expected.push_back(pair<int, string>(4, "4"));
    expected.push_back(pair<int, string>(9, "9"));
    expected.push_back(pair<int, string>(3, "3"));
    REQUIRE CHECK_EQUAL(expected.size(), traversal.size());
    for (int i = 0; i < expected.size(); i++) {
        CHECK_EQUAL(expected[i].first, traversal[i].first);
        CHECK_EQUAL(expected[i].second, traversal[i].second);
    }
    delete bst;
}


int main() {
    return UnitTest::RunAllTests();
}
