// VOTING SYSTEM v2.0 //

#include <iostream>
#include <string>
#include <limits>
using namespace std;
const int NUM_CANDIDATES = 4;

// array
string candidates[NUM_CANDIDATES] = {
    "KP Sharma Oli", 
    "Balen Shah", 
    "Ranjit Tamang", 
    "Mandira Chimaria"
};
int votes[NUM_CANDIDATES] = {0, 0, 0, 0};
int totalVotes = 0;

// Function to clear input buffer (bug fix for invalid input)
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function to get valid integer input
int getValidInput(int min, int max) {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail()) {
            clearInputBuffer();
            cout << "Invalid input! Please enter a number: ";
        } else if (input < min || input > max) {
            cout << "Please enter a number between " << min << " and " << max << ": ";
        } else {
            clearInputBuffer();
            return input;
        }
    }
}

// Function to display candidates
void displayCandidates() {
    cout << "\n =================================\n";
    cout << "      JHAPA-5 CONSTITUENCY         \n";
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        cout << "|  " << i + 1 << ". " << candidates[i];
        // Padding for alignment
        for (int j = candidates[i].length(); j < 25; j++) cout << " ";
        cout << "|\n";
    }
    cout << "====================================\n";
}

// Function to cast vote with confirmation
void castVote() {
    displayCandidates();
    
    cout << "\nEnter candidate number (1-" << NUM_CANDIDATES << "): ";
    int choice = getValidInput(1, NUM_CANDIDATES);
    
    // Confirmation
    char confirm;
    cout << "You selected: " << candidates[choice - 1] << endl;
    cout << "Confirm your vote? (Y/N): ";
    cin >> confirm;
    clearInputBuffer();
    
    if (confirm == 'Y' || confirm == 'y') {
        votes[choice - 1]++;
        totalVotes++;
        cout << "? Vote cast successfully!\n";
    } else {
        cout << "? Vote cancelled.\n";
    }
}

// Function to find winner
void findWinner() {
    int maxVotes = 0;
    int winnerIndex = 0;
    
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        if (votes[i] > maxVotes) {
            maxVotes = votes[i];
            winnerIndex = i;
        }
    }
    
    if (totalVotes > 0) {
        cout << "\n?? LEADING CANDIDATE: " << candidates[winnerIndex];
        cout << " with " << maxVotes << " votes\n";
    }
}

// Function to display results
void displayResults() {
    cout << "\n========================================\n";
    cout << "          VOTING RESULTS                \n";
    cout << "          JHAPA-5 CONSTITUENCY          \n";
    cout << "=========================================\n";
    
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        cout << "|  " << candidates[i];
        for (int j = candidates[i].length(); j < 22; j++) cout << " ";
        cout << ": " << votes[i] << " votes";
        if (votes[i] < 10) cout << " ";
        cout << "    |\n";
    }
    
    cout << "\n";
    cout << "Total Votes Cast: " << totalVotes;
    if (totalVotes < 10) cout << " ";
    cout << "     \n";
    cout << "=================================\n";
    
    findWinner();
}

int main() {
    cout << "==========================================\n";
    cout << "	SIMPLE VOTING SYSTEM v2.0         \n";
    cout << "==========================================\n";
    
    bool running = true;
    
    while (running) {
        cout << "\n========= MAIN MENU ========\n";
        cout << " 1. View Candidates      \n";
        cout << " 2. Cast Vote            \n";
        cout << " 3. View Results         \n";
        cout << " 4. Exit                 \n";
        cout << "============================\n";
        cout << "Enter choice: ";
        
        int option = getValidInput(1, 4);
        
        switch (option) {
            case 1:
                displayCandidates();
                break;
            case 2:
                castVote();
                break;
            case 3:
                displayResults();
                break;
            case 4:
                running = false;
                cout << "\nThank you for using the Voting System!\n";
                break;
        }
    }
    
    return 0;
}