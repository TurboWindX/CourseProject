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
    vector<string> prereqs;

public:
    Course();
    virtual ~Course();
    void setNumber(string inputCourseNumber);
    void setTitle(string inputCourseTitle);
    void addPrereq(string prereq);
    string getNumber();
    string getTitle();
    vector<string> getPrereqs();
};

// Course Class constructor
Course::Course() {
    courseNumber = "";
    courseTitle = "";
    prereqs = vector<string>();
}

Course::~Course() {
    //free(this);
}

// Course Class setters
void Course::setNumber(string CourseNumber) {
    courseNumber = CourseNumber;
}

void Course::setTitle(string CourseTitle) {
    courseTitle = CourseTitle;
}

void Course::addPrereq(string prereq) {
    prereqs.push_back(prereq);
}

// Course Class getters
string Course::getNumber() {
    return courseNumber;
}

string Course::getTitle() {
    return courseTitle;
}

vector<string> Course::getPrereqs() {
    return prereqs;
}

class BinarySearchTree {

private:

    // Internal structure for tree node
    struct Node {
        Course course;
        // create the key for the given course
        unsigned key;
        Node* left = nullptr;
        Node* right = nullptr;

        unsigned int Hash(int key) {
            unsigned bucketIndex;
            bucketIndex = key % 10;
            return bucketIndex;
        }

        Node(Course aCourse) {
            course = aCourse;
            string prekey = course.getNumber().c_str();
            prekey = prekey.substr(prekey.length() - 3);
            key = Hash(atoi(prekey.c_str()));
        }
    };
    Node* root;
    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);

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
    string prekey = courseNumber.substr(courseNumber.length() - 3);
    unsigned key = atoi(prekey.c_str()) % 10;

    while (curNode != nullptr) {
        if (curNode->key == key) {
            if (curNode->course.getNumber() == courseNumber) {
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
        
        cout << node->key << ", " << node->course.getNumber() << ", " << node->course.getTitle();
        vector<string> prereqs = node->course.getPrereqs();
        for (int i = 0; i < prereqs.size(); i++) {
            cout << " => " << prereqs[i];
        }
        cout << endl;
        inOrder(node->right);
    }
}
void BinarySearchTree::postOrder(Node* node) {
    // FixMe (10): Post order root
    if (node != nullptr) {
        postOrder(node->left);
        postOrder(node->right);
        cout << node->key << ", " << node->course.getNumber() << ", " << node->course.getTitle() << ", "
            << node->course.getPrereqs().at(0) << ", " << node->course.getPrereqs().at(1) << " ==> " << endl;
    }
}

void BinarySearchTree::preOrder(Node* node) {
    // FixMe (11): Pre order root
    if (node != nullptr) {
        cout << node->key << ", " << node->course.getNumber() << ", " << node->course.getTitle() << ", "
            << node->course.getPrereqs().at(0) << ", " << node->course.getPrereqs().at(1) << " ==> " << endl;
        preOrder(node->left);
        preOrder(node->right);
    }
}

void loadLines(string csvPath, BinarySearchTree* bst) {
    
    ifstream csv(csvPath);
    if (csv.is_open()) {
        string line;
        while (getline(csv, line)) {
            vector<string> csvline;
            Course theCourse;
            printf(line.c_str());
            stringstream ss(line.c_str());
            while (ss.good()) {
                string substr;
                getline(ss, substr, ',');
                csvline.push_back(substr);
            }
            theCourse.setNumber(csvline[0]);
            theCourse.setTitle(csvline[1]);
            if (csvline.size() >= 3) {
                for (int i = 2; i < csvline.size(); i++) {
                    theCourse.addPrereq(csvline[i]);
                }
            }
            
            bst->Insert(theCourse);
            
        }
        csv.close();
    }

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
        case 3:
            bst->Search(aCourseNumber);
            break;

        }
        

    }
    return 0;
}