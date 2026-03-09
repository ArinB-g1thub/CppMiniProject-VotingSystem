// VOTING SYSTEM v3.0 //

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;e
const int NUM_AREAS = 3;
const int MAX_CANDIDATES = 4;

// Area names
string areas[NUM_AREAS] = {"Jhapa-5", "Kathmandu-1", "Chitwan-2"};

// 2D array for candidates [area][candidate]
string candidates[NUM_AREAS][MAX_CANDIDATES] = {
    {"KP Sharma Oli", "Balen Shah", "Sher Bahadur Deuba", "Pushpa Kamal Dahal"},
    {"Balen Shah", "Rabi Lamichhane", "Gagan Thapa", "Prakash Man Singh"},
    {"Pushpa Kamal Dahal", "Bishnu Poudel", "Ram Chandra Poudel", "Narayan Kaji Shrestha"}
};

// 2D array for votes [area][candidate]
int votes[NUM_AREAS][MAX_CANDIDATES] = {{0}};

// Total votes per area
int totalVotesPerArea[NUM_AREAS] = {0};

// Function declarations
void clearInputBuffer();
int getValidInput(int min, int max);
void displayAreas();
void displayCandidates(int areaIndex);
void castVote();
void displayAreaResults(int areaIndex);
void displayAllResults();
void findWinner(int areaIndex);

// Clear input buffer
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Get valid integer input
int getValidInput(int min, int max) {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail()) {
            clearInputBuffer();
            cout << "Invalid! Enter a number: ";
        } else if (input < min || input > max) {
            cout << "Enter between " << min << "-" << max << ": ";
        } else {
            clearInputBuffer();
            return input;
        }
    }
}

// Display all areas
void displayAreas() {
    cout << "\n╔═══════════════════════════════╗\n";
    cout << "║      SELECT CONSTITUENCY      ║\n";
    cout << "╠═══════════════════════════════╣\n";
    for (int i = 0; i < NUM_AREAS; i++) {
        cout << "║  " << i + 1 << ". " << areas[i];
        for (int j = areas[i].length(); j < 23; j++) cout << " ";
        cout << "║\n";
    }
    cout << "╚═══════════════════════════════╝\n";
}

// Display candidates for specific area
void displayCandidates(int areaIndex) {
    cout << "\n┌─────────────────────────────────┐\n";
    cout << "│  " << areas[areaIndex] << " CANDIDATES";
    for (int j = areas[areaIndex].length(); j < 17; j++) cout << " ";
    cout << "│\n";
    cout << "├─────────────────────────────────┤\n";
    
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        cout << "│  " << i + 1 << ". " << candidates[areaIndex][i];
        for (int j = candidates[areaIndex][i].length(); j < 25; j++) cout << " ";
        cout << "│\n";
    }
    cout << "└─────────────────────────────────┘\n";
}

// Cast vote
void castVote() {
    displayAreas();
    cout << "Select constituency (1-" << NUM_AREAS << "): ";
    int areaChoice = getValidInput(1, NUM_AREAS) - 1;
    
    displayCandidates(areaChoice);
    cout << "Select candidate (1-" << MAX_CANDIDATES << "): ";
    int candChoice = getValidInput(1, MAX_CANDIDATES) - 1;
    
    // Confirmation
    cout << "\n┌─────────────────────────────────┐\n";
    cout << "│  VOTE CONFIRMATION              │\n";
    cout << "├─────────────────────────────────┤\n";
    cout << "│  Area: " << areas[areaChoice] << endl;
    cout << "│  Candidate: " << candidates[areaChoice][candChoice] << endl;
    cout << "└─────────────────────────────────┘\n";
    
    char confirm;
    cout << "Confirm vote? (Y/N): ";
    cin >> confirm;
    clearInputBuffer();
    
    if (confirm == 'Y' || confirm == 'y') {
        votes[areaChoice][candChoice]++;
        totalVotesPerArea[areaChoice]++;
        cout << "✓ Vote recorded successfully!\n";
    } else {
        cout << "✗ Vote cancelled.\n";
    }
}

// Find winner of an area
void findWinner(int areaIndex) {
    if (totalVotesPerArea[areaIndex] == 0) {
        cout << "No votes cast yet.\n";
        return;
    }
    
    int maxVotes = 0;
    int winnerIndex = 0;
    
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        if (votes[areaIndex][i] > maxVotes) {
            maxVotes = votes[areaIndex][i];
            winnerIndex = i;
        }
    }
    
    cout << "🏆 Leader: " << candidates[areaIndex][winnerIndex];
    cout << " (" << maxVotes << " votes)\n";
}

// Display results for specific area
void displayAreaResults(int areaIndex) {
    cout << "\n╔═══════════════════════════════════════════╗\n";
    cout << "║  RESULTS: " << areas[areaIndex];
    for (int j = areas[areaIndex].length(); j < 30; j++) cout << " ";
    cout << "║\n";
    cout << "╠═══════════════════════════════════════════╣\n";
    
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        float percentage = 0;
        if (totalVotesPerArea[areaIndex] > 0) {
            percentage = (float)votes[areaIndex][i] / totalVotesPerArea[areaIndex] * 100;
        }
        
        cout << "║  " << candidates[areaIndex][i];
        for (int j = candidates[areaIndex][i].length(); j < 22; j++) cout << " ";
        cout << ": " << setw(3) << votes[areaIndex][i] << " (";
        cout << fixed << setprecision(1) << setw(5) << percentage << "%) ║\n";
    }
    
    cout << "╠═══════════════════════════════════════════╣\n";
    cout << "║  Total Votes: " << setw(3) << totalVotesPerArea[areaIndex];
    cout << "                         ║\n";
    cout << "╚═══════════════════════════════════════════╝\n";
    
    findWinner(areaIndex);
}

// Display all results
void displayAllResults() {
    cout << "\n";
    for (int i = 0; i < NUM_AREAS; i++) {
        displayAreaResults(i);
    }
}

// View results menu
void viewResults() {
    cout << "\n┌─────────────────────────┐\n";
    cout << "│    VIEW RESULTS         │\n";
    cout << "├─────────────────────────┤\n";
    cout << "│ 1. Specific Area        │\n";
    cout << "│ 2. All Areas            │\n";
    cout << "└─────────────────────────┘\n";
    cout << "Choice: ";
    
    int choice = getValidInput(1, 2);
    
    if (choice == 1) {
        displayAreas();
        cout << "Select area: ";
        int area = getValidInput(1, NUM_AREAS) - 1;
        displayAreaResults(area);
    } else {
        displayAllResults();
    }
}

int main() {
    cout << "╔════════════════════════════════════════════╗\n";
    cout << "║        VOTING SYSTEM v3.0                  ║\n";
    cout << "║     Multiple Constituencies                ║\n";
    cout << "╚════════════════════════════════════════════╝\n";
    
    bool running = true;
    
    while (running) {
        cout << "\n┌─────────── MAIN MENU ───────────┐\n";
        cout << "│ 1. View Constituencies          │\n";
        cout << "│ 2. View Candidates              │\n";
        cout << "│ 3. Cast Vote                    │\n";
        cout << "│ 4. View Results                 │\n";
        cout << "│ 5. Exit                         │\n";
        cout << "└─────────────────────────────────┘\n";
        cout << "Enter choice: ";
        
        int option = getValidInput(1, 5);
        
        switch (option) {
            case 1:
                displayAreas();
                break;
            case 2:
                displayAreas();
                cout << "Select area: ";
                displayCandidates(getValidInput(1, NUM_AREAS) - 1);
                break;
            case 3:
                castVote();
                break;
            case 4:
                viewResults();
                break;
            case 5:
                running = false;
                cout << "\nThank you for using the Voting System!\n";
                break;
        }
    }
    
    return 0;
}