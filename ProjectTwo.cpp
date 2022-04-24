#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Course {
private:
    string courseNumber;
    string courseTitle;
    string prereq1, prereq2, prereq3, prereq4;

public:
    Course();
    virtual ~Course();
    void setCourseNumber(string inputCourseNumber);
    void setCourseTitle(string inputCourseTitle);
    void setPrereq1(string inputPrereq1);
    void setPrereq2(string inputPrereq2);
    string getCourseNumber();
    string getCourseTitle();
    string getPrereq1();
    string getPrereq2();
};

// Course Class constructor
Course::Course() {
    courseNumber = "";
    courseTitle = "";
    prereq1 = "";
    prereq2 = "";
    prereq3 = "";
    prereq4 = "";
}

// Course Class destructor
Course::~Course() {
    // ******************************************************    <--------
}

// Course Class setters
void Course::setCourseNumber(string inputCourseNumber) {
    courseNumber = inputCourseNumber;
}

void Course::setCourseTitle(string inputCourseTitle) {
    courseTitle = inputCourseTitle;
}

void Course::setPrereq1(string inputPrereq1) {
    prereq1 = inputPrereq1;
}

void Course::setPrereq2(string inputPrereq2) {
    prereq2 = inputPrereq2;
}

// Course Class getters
string Course::getCourseNumber() {
    return courseNumber;
}

string Course::getCourseTitle() {
    return courseTitle;
}

string Course::getPrereq1() {
    return prereq1;
}

string Course::getPrereq2() {
    return prereq2;
}

class BinarySearchTree {

private:

    // Internal structure for tree node
    struct Node {
        Course course;
        // create the key for the given course
        unsigned key;

        Node* parent = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;

        unsigned int Hash(int key) {
            unsigned bucketIndex;
            bucketIndex = key % 10;
            return bucketIndex;
        }

        Node(Course aCourse) {
            course = aCourse;
            key = Hash(atoi(course.getCourseNumber().c_str()));
        }
    };
    Node* root;
    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    vector<string> loadLines(string csvPath, BinarySearchTree* bst);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Course course);
    Course Search(string courseNumber);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    //root is equal to nullptr
    this->root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    // Case that tree is already empty
    // ******************************************************    <--------
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    preOrder(root);
}

/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course course) {
    Node* theNode = new Node(course);

    if (root == nullptr) {
        root = theNode;
    }

    else {
        addNode(root, course);
    }
}

/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseNumber) {
    // FIXME (7) Implement searching the tree for a course
    Node* curNode = root;
    Course course;
    unsigned key = atoi(courseNumber.c_str()) % 10;

    while (curNode != nullptr) {
        if (curNode->key == key) {
            if (curNode->course.getCourseNumber() == courseNumber) {
                return curNode->course;
            }
            return curNode->course;
        }

        if (curNode->key <= key) {
            curNode = curNode->left;
        }

        else {
            curNode = curNode->right;
        }
    }

    return course;
}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param course Course to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // FIXME (8) Implement inserting a course into the tree
    Node* nodeToInsert = new Node(course);
    nodeToInsert->parent = node;

    if (nodeToInsert->key <= node->key) {
        if (node->left == nullptr) {
            node->left = nodeToInsert;
        }
        else {
            addNode(node->left, course);
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = nodeToInsert;
        }
        else {
            addNode(node->right, course);
        }
    }
}
void BinarySearchTree::inOrder(Node* node) {
    // FixMe (9): Pre order root
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->key << ", " << node->course.getCourseNumber() << ", " << node->course.getCourseTitle() << ", "
            << node->course.getPrereq1() << ", " << node->course.getPrereq2() << " ==> " << endl;
        inOrder(node->right);
    }
}
void BinarySearchTree::postOrder(Node* node) {
    // FixMe (10): Post order root
    if (node != nullptr) {
        postOrder(node->left);
        postOrder(node->right);
        cout << node->key << ", " << node->course.getCourseNumber() << ", " << node->course.getCourseTitle() << ", "
            << node->course.getPrereq1() << ", " << node->course.getPrereq2() << " ==> " << endl;
    }
}

void BinarySearchTree::preOrder(Node* node) {
    // FixMe (11): Pre order root
    if (node != nullptr) {
        cout << node->key << ", " << node->course.getCourseNumber() << ", " << node->course.getCourseTitle() << ", "
            << node->course.getPrereq1() << ", " << node->course.getPrereq2() << " ==> " << endl;
        preOrder(node->left);
        preOrder(node->right);
    }
}

void loadLines(string csvPath, BinarySearchTree* bst) {
    vector<string> theVector;
    Course theCourse;
    ifstream csv(csvPath);

    vector<string> result;
    string line, unused;

    stringstream lineStream(line);
    string cell;

    getline(csv, line);
    int numRows = 1;

    while (getline(csv, unused)) {
        ++numRows;
    }

    while (getline(csv, line)) {
        for (int i = 0; i < numRows; i++) {
            while (getline(lineStream, cell, ',')) {
                result.push_back(cell);
            }
            if (!lineStream && cell.empty()) {
                result.push_back("");
            }
        }
    }

    if (theVector.size() == 2) {
        theCourse.setCourseNumber(theVector[0]);
        theCourse.setCourseTitle(theVector[1]);
    }

    if (theVector.size() == 3) {
        theCourse.setCourseNumber(theVector[0]);
        theCourse.setCourseTitle(theVector[1]);
        theCourse.setPrereq1(theVector[2]);
    }

    if (theVector.size() == 4) {
        theCourse.setCourseNumber(theVector[0]);
        theCourse.setCourseTitle(theVector[1]);
        theCourse.setPrereq1(theVector[2]);
        theCourse.setPrereq2(theVector[3]);
    }
    bst->Insert(theCourse);
}

Course vectorToCourse(vector<string> courseVector, BinarySearchTree* bst) {
    Course theCourse;

    
    return theCourse;
}

int main(int argc, char* argv[]) {
    string csvPath, aCourseNumber;

    switch (argc) {
    case 2:
        csvPath = argv[1];
        aCourseNumber = "CSCI400";
        break;

    case 3:
        csvPath = argv[1];
        aCourseNumber = argv[2];
        break;

    default:
        csvPath = "res/ABCU_Advising_Program_Input.txt";
        aCourseNumber = "CSCI400";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst = nullptr;

    Course aCourse;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "1. Load Courses into the Binary Search Tree." << endl;
        cout << "2. Print Entire Course List." << endl;
        cout << "3. Print Specific Course." << endl;
        cout << "9. Exit." << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            bst = new BinarySearchTree();

            ticks = clock();

            loadLines(csvPath, bst);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 2:
            bst->InOrder();
            break;
        }
    }
    return 0;
}