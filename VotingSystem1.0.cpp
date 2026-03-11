// VOTING SYSTEM v1.0 //

#include <iostream>
#include <string>
using namespace std;

// array for candidates and votes
string candidates[4] = {"KP Sharma Oli", "Balen Shah", "Ranjit Tamang", "Mandira Chimaria"};
int votes[4] = {0, 0, 0, 0};

// Function to display candidates
void displayCandidates() {
    cout << "\n==============================" << endl;
    cout << "     JHAPA-5 CONSTITUENCY     " << endl;
    cout << "==============================" << endl;
    cout << "Candidates:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << i + 1 << ". " << candidates[i] << endl;
    }
    cout << "==============================" << endl;
}

// Function to cast vote
void castVote() {
    int choice;
    cout << "\nEnter candidate number (1-4): ";
    cin >> choice;
    
    if (choice >= 1 && choice <= 4) {
        votes[choice - 1]++;
        cout << "Vote cast successfully!" << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }
}

// Function to display result
void displayResults() {
    cout << "\n==============================" << endl;
    cout << "       VOTING RESULTS         " << endl;
    cout << "     JHAPA-5 CONSTITUENCY     " << endl;
    cout << "------------------------------" << endl;
    for (int i = 0; i < 4; i++) {
        cout << candidates[i] << ": " << votes[i] << " votes" << endl;
    }
    cout << "==============================" << endl;
}

int main() {
    int option;
    bool running = true;
    
    cout << "****************************************" << endl;
    cout << "*     SIMPLE VOTING SYSTEM v1.0        *" << endl;
    cout << "****************************************" << endl;
    
    while (running) {
        cout << "\n--- MAIN MENU ---" << endl;
        cout << "1. View Candidates" << endl;
        cout << "2. Cast Vote" << endl;
        cout << "3. View Results" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> option;
        
        switch (option) {
            case 1:
                displayCandidates();
                break;
            case 2:
                displayCandidates();
                castVote();
                break;
            case 3:
                displayResults();
                break;
            case 4:
                running = false;
                cout << "Thank you for using the Voting System!" << endl;
                break;
            default:
                cout << "Invalid option!" << endl;
        }
    }
    
    return 0;
}