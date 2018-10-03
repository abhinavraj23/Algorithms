#include <iostream>
#include <vector>

using namespace std;

vector<string> findPatternBranchOne(vector<char> data) {
    vector<string> patternOne;

    for(int i = 0; i < data.size(); i++) {
        if(data[i] == '1')
            patternOne.emplace_back("T");
        else
            patternOne.emplace_back("N");
    }

    return patternOne;
}

vector<string> findPatternBranchTwo(vector<char> data) {
    vector<string> patternOne = findPatternBranchOne(data);
    vector<string> patternTwo;

    for(int i = 0; i < data.size(); i++) {
        if(patternOne[i] != "T") {
            if(data[i] == '1' || data[i] == '0')
                patternTwo.emplace_back("T");
            else
                patternTwo.emplace_back("N");
        }
    }

    return patternTwo;
}

vector<string> findPatternBranchThree(vector<char> data) {
    vector<string> patternOne;

    for(int i = 0; i < data.size(); i++) {
            patternOne.emplace_back("T");
    }

    return patternOne;
}

int main() {

    cout<<"\nEnter the pattern that is loaded from the memory (only once): ";
    string s;
    cin>>s;
    vector<char> data;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '-') {
            data.emplace_back('2');
            i++;
        }
        else {
            data.emplace_back(s[i]);
        }
    }

    // Options
    vector<string> options;
    options.emplace_back("1 bit predictor");
    options.emplace_back("2 bits history predictor");

    cout<<"\n\nOptions:"<<endl;
    for(int i = 0; i < options.size(); i++) {
        cout<<i+1<<". "<<options[i]<<endl;
    }

    cout<<"\nEnter option: ";
    int option;
    cin>>option;

    // Find patterns for different branches
    vector<string> patternOne = findPatternBranchOne(data);
    cout<<"\nBranch 1: ";
    for(int i = 0; i < patternOne.size(); i++) {
        cout<<patternOne[i];
    }
    vector<string> patternTwo = findPatternBranchTwo(data);
    cout<<"\nBranch 2: ";
    for(int i = 0; i < patternTwo.size(); i++) {
        cout<<patternTwo[i];
    }
    vector<string> patternThree = findPatternBranchThree(data);
    cout<<"\nBranch 3: ";
    for(int i = 0; i < patternThree.size(); i++) {
        cout<<patternThree[i];
    }

    bool predictionBit = false;
    int branchOneHits = 0, branchTwoHits = 0, branchThreeHits = 0;
    int branchOneMisses = 0, branchTwoMisses = 0, branchThreeMisses = 0;

    // Patterns Available - TT, TN, NT, NN
    bool historyTable[] = {false,false,false,false};

    int size1,size2,counter2 = 2;

    switch(option) {
        case 1:
           // Aliasing in branches 1 and 3

           // Removing initial starting error
            for(int i = 0; i < data.size(); i++) {
                bool temp;

                temp = patternOne[i] == "T";
                if(temp ^ predictionBit) {
                    predictionBit = !predictionBit;
                }

                temp = patternThree[i] == "T";
                if(temp ^ predictionBit) {
                    predictionBit = !predictionBit;
                }
            }

            // Finding actual accuracy
            for(int i = 0; i < data.size(); i++) {
                bool temp;

                temp = patternOne[i] == "T";
                if(temp ^ predictionBit) {
                    predictionBit = !predictionBit;
                    branchOneMisses++;
                }
                else
                    branchOneHits++;

                temp = patternThree[i] == "T";
                if(temp ^ predictionBit) {
                    predictionBit = !predictionBit;
                    branchThreeMisses++;
                }
                else
                    branchThreeHits++;
            }

            // Finding accuracy for branch 2
            predictionBit = false;

            for(int i = 0; i < patternTwo.size(); i++) {
                bool temp;

                temp = patternTwo[i] == "T";
                if(temp ^ predictionBit) {
                    predictionBit = !predictionBit;
                }
            }

            for(int i = 0; i < patternTwo.size(); i++) {
                bool temp;

                temp = patternTwo[i] == "T";
                if(temp ^ predictionBit) {
                    predictionBit = !predictionBit;
                    branchTwoMisses++;
                }
                else
                    branchTwoHits++;
            }
            break;

        case 2:

            size1 = patternOne.size();
            size2 = patternTwo.size();

            for(int i = 0; i < size1; i++) {
                patternOne.emplace_back(patternOne[i]);
                patternThree.emplace_back(patternThree[i]);
            }
            for(int i = 0; i < size1; i++) {
                patternOne.emplace_back(patternOne[i]);
                patternThree.emplace_back(patternThree[i]);
            }

            for(int i = 0; i < size2; i++) {
                patternTwo.emplace_back(patternTwo[i]);
            }
            for(int i = 0; i < size2; i++) {
                patternTwo.emplace_back(patternTwo[i]);
            }

            for(int i = 2; i < 2*size1; i++) {

                // For branch 1
                bool check;
                string s = patternOne[i-2]+patternOne[i-1];
                check = patternOne[i] == "T";
                if(s == "TT") {
                    if(check ^ historyTable[0]) {
                        historyTable[0] = !historyTable[0];
                    }
                }
                else if(s == "TN") {
                    if(check ^ historyTable[1]) {
                        historyTable[1] = !historyTable[1];
                    }
                }
                else if(s == "NT") {
                    if(check ^ historyTable[2]) {
                        historyTable[2] = !historyTable[2];
                    }
                }
                else if(s == "NN") {
                    if(check ^ historyTable[3]) {
                        historyTable[3] = !historyTable[3];
                    }
                }

                // For branch 3
                check = true;
                if(check ^ historyTable[0])
                    historyTable[0] = true;

                // For branch 2
                if(patternOne[i] == "N") {
                    s = patternTwo[counter2-2] + patternTwo[counter2-1];
                    check = patternTwo[counter2] == "T";
                    if(s == "TT") {
                        if(check ^ historyTable[0]) {
                            historyTable[0] = !historyTable[0];
                        }
                    }
                    else if(s == "TN") {
                        if(check ^ historyTable[1]) {
                            historyTable[1] = !historyTable[1];
                        }
                    }
                    else if(s == "NT") {
                        if(check ^ historyTable[2]) {
                            historyTable[2] = !historyTable[2];
                        }
                    }
                    else if(s == "NN") {
                        if(check ^ historyTable[3]) {
                            historyTable[3] = !historyTable[3];
                        }
                    }
                    counter2++;
                }

            }

            counter2-=2;

            for(int i = 2*size1; i < patternOne.size(); i++) {
                // For branch 1
                bool check;
                string s = patternOne[i-2]+patternOne[i-1];
                check = patternOne[i] == "T";
                if(s == "TT") {
                    if(check ^ historyTable[0]) {
                        historyTable[0] = !historyTable[0];
                        branchOneMisses++;
                    }
                    else
                        branchOneHits++;
                }
                else if(s == "TN") {
                    if(check ^ historyTable[1]) {
                        historyTable[1] = !historyTable[1];
                        branchOneMisses++;
                    }
                    else
                        branchOneHits++;
                }
                else if(s == "NT") {
                    if(check ^ historyTable[2]) {
                        historyTable[2] = !historyTable[2];
                        branchOneMisses++;
                    }
                    else
                        branchOneHits++;
                }
                else if(s == "NN") {
                    if(check ^ historyTable[3]) {
                        historyTable[3] = !historyTable[3];
                        branchOneMisses++;
                    }
                    else
                        branchOneHits++;
                }

                // For branch 3
                check = true;
                if(check ^ historyTable[0]) {
                    historyTable[0] = true;
                    branchThreeMisses++;
                }
                else
                    branchThreeHits++;

                // For branch 2
                if(patternOne[i] == "N") {
                    s = patternTwo[counter2-2] + patternTwo[counter2-1];
                    check = patternTwo[counter2] == "T";
                    if(s == "TT") {
                        if(check ^ historyTable[0]) {
                            historyTable[0] = !historyTable[0];
                            branchTwoMisses++;
                        }
                        else
                            branchTwoHits++;
                    }
                    else if(s == "TN") {
                        if(check ^ historyTable[1]) {
                            historyTable[1] = !historyTable[1];
                            branchTwoMisses++;
                        }
                        else
                            branchTwoHits++;
                    }
                    else if(s == "NT") {
                        if(check ^ historyTable[2]) {
                            historyTable[2] = !historyTable[2];
                            branchTwoMisses++;
                        }
                        branchTwoHits++;
                    }
                    else if(s == "NN") {
                        if(check ^ historyTable[3]) {
                            historyTable[3] = !historyTable[3];
                            branchTwoMisses++;
                        }
                        else
                            branchTwoHits++;
                    }
                    counter2++;
                }

            }

            break;
        default:
            break;
    }

    cout<<"\n\nAccuracy:"<<endl;
    cout<<"Branch 1 - "<<(branchOneHits*100.0)/(branchOneHits+branchOneMisses)<<"%"<<endl;
    cout<<"Branch 2 - "<<(branchTwoHits*100.0)/(branchTwoHits+branchTwoMisses)<<"%"<<endl;
    cout<<"Branch 3 - "<<(branchThreeHits*100.0)/(branchThreeHits+branchThreeMisses)<<"%"<<endl;
    return 0;
}