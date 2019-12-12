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

    cout << "Done!\n\n";

}

float leave_one_out(vector<node> data, vector<int> featureSet, int featureToAdd) {
    int numCorrect = 0;
    float accuracy = 0;

    for (int i = 0; i < data.size(); i++) {
        double bestSoFar = INT_MAX;
        int bestSoFarLoc = 0;

        for (int j = 0; j < data.size(); j++) {
            double distance = 0;
            if (i != j) {

                    for (int k = 0; k < featureSet.size(); k++) {
                        distance += pow( data.at(i).features.at(featureSet.at(k)) - data.at(j).features.at(featureSet.at(k)), 2);
                    }

                    distance += pow( data.at(i).features.at(featureToAdd) - data.at(j).features.at(featureToAdd), 2);

                distance = sqrt(distance);
                // cout << "Distance: " << setprecision(10) << distance << endl;

                if (distance < bestSoFar) {
                    bestSoFar = distance;
                    bestSoFarLoc = j;
                }
            }
        }

        // cout << "For exemplar " << i << " I think its nearest neighbor is " << bestSoFarLoc << endl << endl;
        if (data.at(i).classification == data.at(bestSoFarLoc).classification) {
            // cout << "I got exemplar " << i << " correct.\n\n";
            numCorrect++;
        } else {
            // cout << "I did NOT get exemplar " << i << " correct.\n\n";
        }
    }
    // cout << "float(numCorrect) = " << float(numCorrect) << endl;
    // cout << "(data.size() - 1) = " << data.size() << endl;
    accuracy = float(numCorrect) / data.size();
    // cout << "The accuracy of this test was " << setprecision(10) << accuracy * 100 << "%" << endl << endl;
    return accuracy;
}

void forward_selection(vector<node> data) {
    vector<int> featureSet;
    float overallBest = 0;
    bool decrease = 0;
    cout << "Beginning search.\n\n";

    for (int i = 0; i < data.at(0).features.size(); i++) {
        int featureToAdd = 0;
        float bestSoFar = 0;

        for (int j = 0; j < data.at(0).features.size(); j++) {
            if (find(featureSet.begin(), featureSet.end(), j) == featureSet.end()) {
                float accuracy = leave_one_out(data, featureSet, j);
                cout << "   Using feature(s) {";

                for (int x = 0; x < featureSet.size(); x++) {
                    cout << featureSet.at(x) + 1 << ", ";
                }
                cout << j + 1;
                cout << "} accuracy is " << accuracy * 100 << "%\n";

                if (accuracy > bestSoFar) {
                    bestSoFar = accuracy;
                    featureToAdd = j;
                }
            }
        }

        cout << "\n";
        featureSet.push_back(featureToAdd);
        if (bestSoFar > overallBest) {
            overallBest = bestSoFar;
        } else if (bestSoFar < overallBest && !decrease) {
            cout << "WARNING: Accuracy has decreased. Continuing search in case of local maxima.\n\n";
            decrease = 1;
        }

        cout << "Feature set {";
        for (int x = 0; x < featureSet.size(); x++) {
            cout << featureSet.at(x) + 1 << ", ";
        }
        cout << "} was best, accuracy is " << setprecision(10) << bestSoFar * 100 << "%\n\n";
    }
}

int main() {
    vector<node> data;
    string fileName;
    string algChoice;
    ifstream inFile;
    double temp;

    // cout << "Type in the name of the file you would like to test: " << endl;
    //cin >> fileName;

    // 2 lines below for testing only
    fileName = "SMALL70.txt";
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

    for (int i = 0; i < loadData.size(); i++) {
        if (loadData.at(i) == 1) {
            node newNode(1, i);
            data.push_back(newNode);
        } else if (loadData.at(i) == 2) {
            node newNode(2, i);
            data.push_back(newNode);
        }
    }

    // normalize(data);
    forward_selection(data);
    //vector below for testing
    // vector<int> featureTest;
    // featureTest.push_back(4);
    // featureTest.push_back(6);
    // leave_one_out(data, featureTest, 2);

    inFile.close();
    return 0;
}