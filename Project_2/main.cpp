#include <iostream>
using namespace std;
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

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

void normalize(vector<node>& data) {
    vector<double> featureMin;
    vector<double> featureMax;

    cout << "Normalizing data... ";
    
    // Initializing vector to first value of each feature
    for (int i = 0; i < data.at(0).features.size(); i++) {
        featureMin.push_back(data.at(0).features.at(i));
        featureMax.push_back(data.at(0).features.at(i));
    }

    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data.at(0).features.size(); j++) {
            if (data.at(i).features.at(j) < featureMin.at(j)) {
                featureMin.at(j) = data.at(i).features.at(j);
            }
            if (data.at(i).features.at(j) > featureMax.at(j)) {
                featureMax.at(j) = data.at(i).features.at(j);
            }
        }
    }

    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data.at(0).features.size(); j++) {
            // cout << "data.at(i).features.at(j) = " << data.at(i).features.at(j) << endl;
            // cout << "featureMin.at(j) = " << featureMin.at(j) << endl;
            // cout << "featureMax.at(j) = " << featureMax.at(j) << endl;
            // cout << "Normalized value: " << (data.at(i).features.at(j) - featureMin.at(j)) / (featureMax.at(j) - featureMin.at(j)) << endl << endl;
            data.at(i).features.at(j) = (data.at(i).features.at(j) - featureMin.at(j)) / (featureMax.at(j) - featureMin.at(j));
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

                if (distance < bestSoFar) {
                    bestSoFar = distance;
                    bestSoFarLoc = j;
                }
            }
        }

        if (data.at(i).classification == data.at(bestSoFarLoc).classification) {
            numCorrect++;
        } 
    }
    accuracy = float(numCorrect) / data.size();
    return accuracy;
}

float leave_one_out_backward(vector<node> data, vector<int> featureSet, int featureToRemove) {
    int numCorrect = 0;
    float accuracy = 0;

    for (int i = 0; i < data.size(); i++) {
        double bestSoFar = INT_MAX;
        int bestSoFarLoc = 0;

        for (int j = 0; j < data.size(); j++) {
            double distance = 0;
            if (i != j) {

                for (int k = 0; k < featureSet.size(); k++) {
                    if (k != featureToRemove) {
                        distance += pow( data.at(i).features.at(featureSet.at(k)) - data.at(j).features.at(featureSet.at(k)), 2);
                    }
                }

                distance = sqrt(distance);

                if (distance < bestSoFar) {
                    bestSoFar = distance;
                    bestSoFarLoc = j;
                }
            }
        }

        if (data.at(i).classification == data.at(bestSoFarLoc).classification) {
            numCorrect++;
        } 
    }
    accuracy = float(numCorrect) / data.size();
    return accuracy;
}

void forward_selection(vector<node> data) {
    vector<int> featureSet;
    vector<int> bestFeatures;
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
                cout << "} accuracy is " << setprecision(3) << accuracy * 100 << "%\n";

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
            bestFeatures = featureSet;
        } else if (bestSoFar < overallBest && !decrease) {
            cout << "WARNING: Accuracy has decreased. Continuing search in case of local maxima.\n\n";
            decrease = 1;
        }

        cout << "Feature set {";
        for (int x = 0; x < featureSet.size() - 1; x++) {
            cout << featureSet.at(x) + 1 << ", ";
        }
        cout << featureSet.at(featureSet.size() - 1) + 1;
        cout << "} was best, accuracy is " << setprecision(3) << bestSoFar * 100 << "%\n\n";
    }

    cout << "Finished search. The best feature subset is {";
    for (int i = 0; i < bestFeatures.size() - 1; i++) {
        cout << bestFeatures.at(i) + 1 << ", ";
    }
    cout << bestFeatures.at(bestFeatures.size() - 1) + 1 << "}, which has an accuracy of " << setprecision(3) << overallBest * 100 << "%\n\n";
}

void backward_elimination(vector<node> data) {
    vector<int> featureSet;
    vector<int> bestFeatures;
    float overallBest = 0;
    bool decrease = 0;
    bool outputCheck = 0;
    cout << "Beginning search.\n\n";

    for (int i = 0; i < data.at(0).features.size(); i++) {
        featureSet.push_back(i);
    }

    cout << "Starting feature set: ";
    for (int i = 0; i < featureSet.size(); i++) {
        cout << featureSet.at(i) + 1 << " ";
    }
    cout << "\n\n";

    for (int i = 0; i < data.at(0).features.size(); i++) {
        int featureToRemove = 0;
        float bestSoFar = 0;

        for (int j = 0; j < data.at(0).features.size(); j++) {
            if (find(featureSet.begin(), featureSet.end(), j) != featureSet.end() && featureSet.size() > 1) {
                float accuracy = leave_one_out_backward(data, featureSet, j);
                cout << "   Using feature(s) {";

                for (int x = 0; x < featureSet.size() - 2; x++) {
                    if (featureSet.at(x) != j) {
                        cout << featureSet.at(x) + 1 << ", ";
                    }
                }
                if (featureSet.at(featureSet.size() - 2) == j) {
                    cout << featureSet.at(featureSet.size() - 1) + 1;
                } else if (featureSet.at(featureSet.size() - 1) == j) {
                    cout << featureSet.at(featureSet.size() - 2) + 1;
                } else {
                    cout << featureSet.at(featureSet.size() - 2) + 1 << ", ";
                    cout << featureSet.at(featureSet.size() - 1) + 1;
                }
                // if (featureSet.at(featureSet.size() - 1 != j)) {
                //     cout << featureSet.at(featureSet.size() - 1) + 1;
                // } 
                cout << "} accuracy is " << setprecision(3) << accuracy * 100 << "%\n";

                if (accuracy > bestSoFar) {
                    bestSoFar = accuracy;
                    featureToRemove = j;
                }
            }
        }

        cout << "\n";

        for (int i = 0; i < featureSet.size(); i++) {
            if (featureSet.at(i) == featureToRemove) {
                featureSet.erase(featureSet.begin() + i);
                break;
            }
        }

        if (bestSoFar > overallBest) {
            overallBest = bestSoFar;
            bestFeatures = featureSet;
        } else if (bestSoFar < overallBest && !decrease) {
            cout << "WARNING: Accuracy has decreased. Continuing search in case of local maxima.\n\n";
            decrease = 1;
        }

        if (featureSet.size() != 1 || (featureSet.size() == 1 && !outputCheck)) {
            if (featureSet.size() == 1) {
                outputCheck = 1;
            }
            cout << "Feature set {";
            for (int x = 0; x < featureSet.size() - 1; x++) {
                cout << featureSet.at(x) + 1 << ", ";
            }
            cout << featureSet.at(featureSet.size() - 1) + 1;
            cout << "} was best, accuracy is " << setprecision(10) << bestSoFar * 100 << "%\n\n";
        }

    }

    cout << "Finished search. The best feature subset is {";
    for (int i = 0; i < bestFeatures.size() - 1; i++) {
        cout << bestFeatures.at(i) + 1 << ", ";
    }
    cout << bestFeatures.at(bestFeatures.size() - 1) + 1 << "} which has an accuracy of " << overallBest * 100 << "%\n\n";

}

int main() {
    vector<node> data;
    string fileName;
    int algChoice;
    ifstream inFile;
    double temp;

    // cout << "Type in the name of the file you would like to test: " << endl;
    //cin >> fileName;

    // 2 lines below for testing only
    fileName = "SMALL70.txt";
    cout << "Type the number of the algorithm you want to run: " << endl;
    cout << "   1) Forward Selection" << endl;
    cout << "   2) Backward Elimination" << endl;
    cout << "   3) Custom Algorithm" << endl;
    cin >> algChoice;

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

    normalize(data);
    
    if (algChoice == 1) {
        forward_selection(data);
    } else if (algChoice == 2) {
        backward_elimination(data);
    } else {
        // custom algorithm
    }
    //vector below for testing
    // vector<int> featureTest;
    // featureTest.push_back(4);
    // featureTest.push_back(6);
    // leave_one_out(data, featureTest, 6);

    inFile.close();
    return 0;
}