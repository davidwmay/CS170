#include <iostream>
#include <string>
#include <vector>
using namespace std;

void custom_setup();

vector<int> startRow1;
vector<int> startRow2;
vector<int> startRow3;
int algChoice;

//void default_setup();

class node {
    public:
        vector<int> row1, row2, row3;


        node(vector<int>,vector<int>,vector<int>);
};

node::node(vector<int> row1, vector<int> row2, vector<int> row3) {
    this->row1 = row1;
    this->row2 = row2;
    this->row3 = row3;
}

void printCurr(node currNode) {
    for (int i = 0; i < currNode.row1.size(); i++) {
        cout << currNode.row1.at(i) << " ";
    }
    cout << endl;

    for (int i = 0; i < currNode.row2.size(); i++) {
        cout << currNode.row2.at(i) << " ";
    }
    cout << endl;

    for (int i = 0; i < currNode.row3.size(); i++) {
        cout << currNode.row3.at(i) << " ";
    }
    cout << endl;
}

void start() {

    int setupChoice;

    cout << "Welcome to the 8-puzzle solver!" << endl;
    cout << "Type '1' to use a default puzzle or '2' to enter your own: ";

    do { //ERROR IF ENTER NON-NUMBER INPUT
        cin >> setupChoice;
        if (setupChoice == 1) {
            //default_setup            
            break;
        } else if (setupChoice == 2) {
            custom_setup();
            break;
        }
        cout << setupChoice << " is invalid. Enter '1' or '2': ";
    } while (setupChoice != 1 && setupChoice != 2);
    
    cout << "Enter your choice of algorithm:<<"
    cout << "1. Uniform Cost Search" << endl << "2. A* with the Misplaced Tile Heuristic"
         << endl << "3. A* with the Manhattan Distance Heuristic" << endl;

    cin >> algChoice;
    if (algChoice == 1) {
        //set heuristic to 0
    }
}

void custom_setup() {
    int pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9;

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

    node start(startRow1, startRow2, startRow3);
    printCurr(start);
}

int main() {
    start();

}
