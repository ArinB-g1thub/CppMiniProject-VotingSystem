// VOTING SYSTEM v1.0//

#include <iostream>
#include <string>
using namespace std;

// arrays for candidates and votes
string candidates[4] = {"KP Sharma Oli", "Balen Shah", "Ranjit Tamang", "Mandira Chimaria"};
int votes[4] = {0, 0, 0, 0};

// display candidates
void displayCandidates() 
{
    cout << "\n===== JHAPA-5 CONSTITUENCY =====\n";
    cout << "Candidates:\n";
    for (int i = 0; i < 4; i++) 
	{
        cout << i + 1 << ". " << candidates[i] << endl;
    }
    cout << "================================\n";
}

// Cast Vote
void castVote() 
{
    int choice;
    cout << "\nEnter candidate number (1-4): ";
    cin >> choice;
    
    if (choice >= 1 && choice <= 4) 
	{
        votes[choice - 1]++;
        cout << "Vote cast successfully!\n";
    } 
	else {
        cout << "Invalid choice!\n";
    }
}

// display results
void displayResults() 
{
    cout << "\n======= VOTING RESULTS =======\n";
    cout << "JHAPA-5 CONSTITUENCY\n";
    cout << "------------------------------\n";
    for (int i = 0; i < 4; i++) {
        cout << candidates[i] << ": " << votes[i] << " votes\n";
    }
    cout << "==============================\n";
}

int main() {
    int option;
    bool running = true;
    
    cout << "\n";
    cout << "SIMPLE VOTING SYSTEM v1.0 \n";
    
    while (running) {
        cout << "\n--- MAIN MENU ---\n";
        cout << "1. View Candidates\n";
        cout << "2. Cast Vote\n";
        cout << "3. View Results\n";
        cout << "4. Exit\n";
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
                cout << "Thank you for using the Voting System!\n";
                break;
            default:
                cout << "Invalid option!\n";
        }
    }
    
    return 0;
}