#include <iostream>
using namespace std;
#include <string>
#include <fstream>
#include <vector>

vector<double> loadData;


struct node {
    int classification;
    vector<double> features;
    
    node() {};
    node(int classType, int location) {
        classification = classType;
        location += 1;

        for (int i = location; i < loadData.size(); i++) {
            if (loadData.at(i) == 1 || loadData.at(i) == 2) {
                break;
            } else {
                features.push_back(loadData.at(i));
            }
        }
    }
};


int main() {
    vector<node> data;
    string fileName;
    ifstream inFile;
    double temp;

    cout << "Type in the name of the file you would like to test: ";
    //cin >> fileName;

    // 2 lines below for testing only
    cout << "For testing purposes, testing with small.txt." << endl;
    fileName = "small.txt";

    inFile.open(fileName);

    if (!inFile) {
        cout << "Unable to open file." << endl;
        exit(1);
    }

    while (inFile >> temp) {
        loadData.push_back(temp);
    }

    cout << "Populating classes." << endl;
    for (int i = 0; i < loadData.size(); i++) {
        if (loadData.at(i) == 1) {
            node newNode(1, i);
            data.push_back(newNode);
        } else if (loadData.at(i) == 2) {
            node newNode(2, i);
            data.push_back(newNode);
        }
    }

    // inFile >> test;
    // cout << setprecision(10) << test << endl;
    // inFile >> test;
    // cout << setprecision(10) << test << endl;

    inFile.close();
    return 0;
}