#include <iostream>
using namespace std;
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

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

void normalize(vector<node>& dataVec) {
    vector<double> mins;

    cout << "Normalizing data... ";
    
    // Initializing vector to first value of each feature
    for (int i = 0; i < dataVec.at(0).features.size(); i++) {
        mins.push_back(dataVec.at(0).features.at(i));
    }

    for (int i = 0; i < dataVec.size(); i++) {
        for (int j = 0; j < dataVec.at(i).features.size(); j++) {
            if (dataVec.at(i).features.at(j) < mins.at(j)) {
                mins.at(j) = dataVec.at(i).features.at(j);
            }
        }
    }

    for (int i = 0; i < dataVec.size(); i++) {
        for (int j = 0; j < dataVec.at(i).features.size(); j++) {
            dataVec.at(i).features.at(j) = dataVec.at(i).features.at(j) - mins.at(j);
        }
    }

    cout << "Done!" << endl;

}



int main() {
    vector<node> data;
    string fileName;
    string algChoice;
    ifstream inFile;
    double temp;

    cout << "Type in the name of the file you would like to test: " << endl;
    //cin >> fileName;

    // 2 lines below for testing only
    fileName = "test.txt";
    cout << "For testing purposes, testing with " << fileName << endl;
    // cout << "Type the number of the algorithm you want to run: " << endl;
    // cout << "   1) Forward Selection" << endl;
    // cout << "   2) Backward Elimination" << endl;
    // cout << "   3) Custom Algorithm" << endl;
    // cin >> algChoice;

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

    normalize(data);

    cout << setprecision(10) << data.at(0).features.at(0) << endl;

    // inFile >> test;
    // cout << setprecision(10) << test << endl;
    // inFile >> test;
    // cout << setprecision(10) << test << endl;

    inFile.close();
    return 0;
}