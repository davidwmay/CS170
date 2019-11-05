#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

// node custom_setup();
struct node;

int algChoice;
vector<node> closed;
vector<node> open;
priority_queue<node, vector<node>, greater<int> > my_min_heap;


struct node {
    vector< vector<int> > state;
    int heuristic;
    node* parent;

    node() {};
    node(vector<int>,vector<int>,vector<int>);
    void setHeuristic(int algChoice);
    void solve();
    void expand();
    void validOps();
    void up();
    int find0();
};

node::node(vector<int> row1, vector<int> row2, vector<int> row3) {
    state.push_back(row1);
    state.push_back(row2);
    state.push_back(row3);
}

void node::setHeuristic(int algChoice) {
    if (algChoice == 1) { //use Uniform Cost Search (A*, h(n) = 0) basically BFS
        this->heuristic = 1;
    } else if (algChoice == 2) { //use Misplaced Tile Heuristic
        
    } else if (algChoice == 3) { //use Manhattan Distance

    }
}

int node::find0() {
    if (state.at(0).at(0) == 0) {
        return 1;
    } else if (state.at(0).at(1) == 0) {
        return 2;
    } else if (state.at(0).at(2) == 0) {
        return 3;
    } else if (state.at(1).at(0) == 0) {
        return 4;
    } else if (state.at(1).at(1) == 0) {
        return 5;
    } else if (state.at(1).at(2) == 0) {
        return 6;
    } else if (state.at(2).at(0) == 0) {
        return 7;
    } else if (state.at(2).at(1) == 0) {
        return 8;
    } else if (state.at(2).at(2) == 0) {
        return 9;
    }
    return -1;
}

void node::expand() {
    node newNode;
    cout << "IN EXPAND" << endl;
    if (find0() >= 1 && find0() <= 6) {
        cout << "can shift down" << endl;
        
    } 
    if (find0() >= 4 && find0() <= 9) {
        cout << "can shift up" << endl;
        //up
    } 
    if (find0() == 1 || find0() == 2 || find0() == 4 || find0() == 5 || find0() == 7 || find0() == 8) {
        cout << "can shift right" << endl;
        //right
    } 
    if (find0() == 2 || find0() == 3 || find0() == 5 || find0() == 6 || find0() == 8 || find0() == 9) {
        cout << "can shift left" << endl;
        //left
    }
}

void node::validOps() {

}

void node::solve() {
    this->expand();
}



//void default_setup();

void printCurr(node currNode) {
    for (int i = 0; i < currNode.state.size(); i++) {
        for (int j = 0; j < currNode.state.at(i).size(); j++) {
            cout << currNode.state.at(i).at(j) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

node custom_setup() {
    int pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9;
    vector< vector<int> > startNode;
    vector<int> startRow1;
    vector<int> startRow2;
    vector<int> startRow3;

    cout << "Enter the first row, use spaces or tabs between inputs: ";
    cin >> pos1 >> pos2 >> pos3;
    startRow1.push_back(pos1);
    startRow1.push_back(pos2);
    startRow1.push_back(pos3);
    cout << "Enter the second row, use spaces or tabs between inputs: ";
    cin >> pos4 >> pos5 >> pos6;
    startRow2.push_back(pos4);
    startRow2.push_back(pos5);
    startRow2.push_back(pos6);
    cout << "Enter the third row, use spaces or tabs between inputs: ";
    cin >> pos7 >> pos8 >> pos9;
    startRow3.push_back(pos7);
    startRow3.push_back(pos8);
    startRow3.push_back(pos9);

    startNode.push_back(startRow1);
    startNode.push_back(startRow2);
    startNode.push_back(startRow3);
    node startState(startRow1, startRow2, startRow3);
    printCurr(startState);

    vector<int> goalRow1;
    vector<int> goalRow2;
    vector<int> goalRow3;
    goalRow1.push_back(1);
    goalRow1.push_back(2);
    goalRow1.push_back(3);
    goalRow2.push_back(4);
    goalRow2.push_back(5);
    goalRow2.push_back(6);
    goalRow3.push_back(7);
    goalRow3.push_back(8);
    goalRow3.push_back(0);

    node goalState(goalRow1, goalRow2, goalRow3);
    printCurr(goalState);

    return startState;
}

void start() {

    int setupChoice;
    node starting;

    cout << "Welcome to the 8-puzzle solver!" << endl;
    cout << "Type '1' to use a default puzzle or '2' to enter your own: ";

    do { //ERROR IF ENTER NON-NUMBER INPUT
        cin >> setupChoice;
        if (setupChoice == 1) {
            //default_setup            
            break;
        } else if (setupChoice == 2) {
            starting = custom_setup();
            break;
        }
        cout << setupChoice << " is invalid. Enter '1' or '2': ";
    } while (setupChoice != 1 && setupChoice != 2);
    
    cout << "Enter your choice of algorithm:" << endl;
    cout << "1. Uniform Cost Search" << endl << "2. A* with the Misplaced Tile Heuristic"
         << endl << "3. A* with the Manhattan Distance Heuristic" << endl;

    cin >> algChoice;
    starting.setHeuristic(algChoice);
    starting.solve();
}

int main() {
    start();
    return 0;
}