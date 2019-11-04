#include <iostream>
#include <string>
#include <vector>
using namespace std;

void custom_setup();

vector<int> row1;
vector<int> row2;
vector<int> row3;
//void default_setup();

void printCurr() {
    for (int i = 0; i < row1.size(); i++) {
        cout << row1.at(i) << " ";
    }
    cout << endl;

    for (int i = 0; i < row2.size(); i++) {
        cout << row2.at(i) << " ";
    }
    cout << endl;

    for (int i = 0; i < row3.size(); i++) {
        cout << row3.at(i) << " ";
    }
    cout << endl;
}

void start() {

    int choice;

    cout << "Welcome to the 8-puzzle solver!" << endl;
    cout << "Type '1' to use a default puzzle or '2' to enter your own: ";

    do { //ERROR IF ENTER NON-NUMBER INPUT
        cin >> choice;
        if (choice == 1) {
            //default_setup            
            break;
        } else if (choice == 2) {
            custom_setup();
            break;
        }
        cout << choice << " is invalid. Enter '1' or '2': ";
    } while (choice != 1 && choice != 2);
    
}

void custom_setup() {
    int pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9;

    cout << "Enter the first row, use spaces or tabs between inputs: ";
    cin >> pos1 >> pos2 >> pos3;
    row1.push_back(pos1);
    row1.push_back(pos2);
    row1.push_back(pos3);
    cout << "Enter the second row, use spaces or tabs between inputs: ";
    cin >> pos4 >> pos5 >> pos6;
    row2.push_back(pos4);
    row2.push_back(pos5);
    row2.push_back(pos6);
    cout << "Enter the third row, use spaces or tabs between inputs: ";
    cin >> pos7 >> pos8 >> pos9;
    row3.push_back(pos7);
    row3.push_back(pos8);
    row3.push_back(pos9);

    printCurr();
}

int main() {
    start();
}

