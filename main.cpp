#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;

// node custom_setup();
struct node;

int algChoice;
bool solutionFound = 0;
vector< vector<int> > closed;
vector< vector<int> > open;
priority_queue< node, vector<node>, greater<node> > pq; 

void printCurr(node); 


struct node {
    vector<int> state;
    int heuristic;
    int depth;
    node parent();

    node() {};
    node(vector<int> rows) {
        state = rows;
    }
    void setHeuristic(int algChoice, int parentHeur);
    void solve();
    void expand();
    int find0();
    void swap(int a, int b);
    int manhattanDistance();
};

struct manhattanVals {
    int val;
    int x;
    int y;

    manhattanVals(int val, int x, int y) {
        this->val = val;
        this->x = x;
        this->y = y;
    }

    int getVal() {
        return this->val;
    }
};

bool operator>( const node& lhs, const node& rhs ) {
  return lhs.heuristic > rhs.heuristic;
}

int node::manhattanDistance() {
    vector<manhattanVals> baseVals;
    vector<manhattanVals> currVals;
    int count = 0;

    baseVals.push_back(manhattanVals(1, 0, 0));
    baseVals.push_back(manhattanVals(2, 0, 1));
    baseVals.push_back(manhattanVals(3, 0, 2));
    baseVals.push_back(manhattanVals(4, 1, 0));
    baseVals.push_back(manhattanVals(5, 1, 1));
    baseVals.push_back(manhattanVals(6, 1, 2));
    baseVals.push_back(manhattanVals(7, 2, 0));
    baseVals.push_back(manhattanVals(8, 2, 1));
    baseVals.push_back(manhattanVals(0, 2, 2));
    
    currVals.push_back(manhattanVals(state.at(0), 0, 0));
    currVals.push_back(manhattanVals(state.at(1), 0, 1));
    currVals.push_back(manhattanVals(state.at(2), 0, 2));
    currVals.push_back(manhattanVals(state.at(3), 1, 0));
    currVals.push_back(manhattanVals(state.at(4), 1, 1));
    currVals.push_back(manhattanVals(state.at(5), 1, 2));
    currVals.push_back(manhattanVals(state.at(6), 2, 0));
    currVals.push_back(manhattanVals(state.at(7), 2, 1));
    currVals.push_back(manhattanVals(state.at(8), 2, 2));

    for (int i = 0; i < currVals.size(); i++) {
        for (int j = 0; j < baseVals.size(); j++) {
            if (currVals.at(i).val == baseVals.at(j).val && currVals.at(i).val != 0) {
                count += abs(currVals.at(i).x - baseVals.at(j).x) + abs(currVals.at(i).y - baseVals.at(j).y);
            }
        }
    }
    return count;
}

void node::setHeuristic(int algChoice, int parentHeur) {
    depth = parentHeur + 1;
    cout << "The best state to expand with a g(n) = " << parentHeur;
    if (algChoice == 1) { //use Uniform Cost Search (A*, h(n) = 0) basically BFS
        heuristic = parentHeur + 1;
        cout << " and a h(n) = 0 is..." << endl;
    } else if (algChoice == 2) { //use Misplaced Tile Heuristic
        int misplacedNum = 0;
        for (int i = 0; i < state.size(); i++) {
            if (state.at(i) != i + 1 && state.at(i) != 0) {
                misplacedNum++;
            }
        }
        cout << parentHeur + 1 << " and a h(n) = " << misplacedNum << " is..." << endl;
        heuristic = misplacedNum + parentHeur + 1;
    } else if (algChoice == 3) { //use Manhattan Distance
        heuristic = manhattanDistance() + parentHeur + 1;
        cout << " and a h(n) = " << manhattanDistance() << " is..." << endl;
    }
    printCurr(*this);
}

int node::find0() {
    for (int i = 0; i < state.size(); i++) {
        if (state.at(i) == 0) {
            return i;
        }
    }
    return -1;
}

void node::swap(int a, int b) {
    bool add = 1;
    vector<int> goal;
    goal.push_back(1);
    goal.push_back(2);
    goal.push_back(3);
    goal.push_back(4);
    goal.push_back(5);
    goal.push_back(6);
    goal.push_back(7);
    goal.push_back(8);
    goal.push_back(0);

    node goalState(goal);

    vector<int> newVec;
    newVec = state;
    int temp;
    temp = newVec.at(a);
    newVec.at(a) = newVec.at(b);
    newVec.at(b) = temp;

    node newNode(newVec);
    if (newNode.state == goalState.state) {
        solutionFound = 1;
    }
    int heur = depth;
    newNode.setHeuristic(algChoice, heur);
    for (int i = 0; i < open.size(); i++) {
        if (open.at(i) == newNode.state) {
            add = 0;
        }
    }
    for (int i = 0; i < closed.size(); i++) {
        if (closed.at(i) == newNode.state) {
            add = 0;
        }
    }
    if (add) {
        pq.push(newNode);
        open.push_back(newNode.state);
    } else {
        closed.push_back(newNode.state);
    }
}

void node::expand() {
    if (find0() >= 0 && find0() <= 5 && !solutionFound) {
        swap(find0(), find0() + 3);
    } 
    if (find0() >= 3 && find0() <= 8 && !solutionFound) {
        swap(find0(), find0() - 3);
    } 
    if (find0() == 0 || find0() == 1 || find0() == 3 || find0() == 4 || find0() == 6 || find0() == 7) {
        if (!solutionFound) {
            swap(find0(), find0() + 1);
        }
    } 
    if (find0() == 1 || find0() == 2 || find0() == 4 || find0() == 5 || find0() == 7 || find0() == 8) {
        if (!solutionFound) {
            swap(find0(), find0() - 1);
        }
    }

    for (int i = 0; i < open.size(); i++) {
        if (open.at(i) == state) {
            closed.push_back(state);
            open.erase(open.begin() + i + 1);
        }
    }
}

void node::solve() {
    while(!pq.empty() && !solutionFound) {
        node expandNode = pq.top();
        pq.pop();
    //    cout << "Expanding: " << endl;
        // printCurr(expandNode);
        expandNode.expand();
    }
}

//void default_setup();

void printCurr(node currNode) {
    for (int i = 0; i < currNode.state.size(); i++) {
        if (i % 3 == 0) {
            cout << endl;
        }
        cout << currNode.state.at(i) << " ";
    }
    cout << endl << endl;
}

node custom_setup() {
    int pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9;
    vector<int> startRow;

    cout << "Enter the first row, use spaces or tabs between inputs: ";
    cin >> pos1 >> pos2 >> pos3;
    startRow.push_back(pos1);
    startRow.push_back(pos2);
    startRow.push_back(pos3);
    cout << "Enter the second row, use spaces or tabs between inputs: ";
    cin >> pos4 >> pos5 >> pos6;
    startRow.push_back(pos4);
    startRow.push_back(pos5);
    startRow.push_back(pos6);
    cout << "Enter the third row, use spaces or tabs between inputs: ";
    cin >> pos7 >> pos8 >> pos9;
    startRow.push_back(pos7);
    startRow.push_back(pos8);
    startRow.push_back(pos9);

    node startState(startRow);
    printCurr(startState);

    return startState;
}

void start() {

    int setupChoice;
    node starting;

    cout << "Welcome to the 8-puzzle solver!" << endl;
    cout << "Type '1' to use a default puzzle or '2' to enter your own: ";

    do {
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
    starting.setHeuristic(algChoice, 0);
    pq.push(starting);
    open.push_back(starting.state);
    starting.solve();

}

int main() {
    start();

    cout << "Number of nodes expanded: " << closed.size() << endl;
    cout << "Number of nodes discovered: " << open.size() << endl;
    return 0;
}