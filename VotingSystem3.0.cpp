// VOTING SYSTEM v3.0 //

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

// Constants
const int NUM_AREAS = 4;
const int MAX_CANDIDATES = 4;

// Area names
string areas[NUM_AREAS] = {"Jhapa-5", "Kathmandu-1", "Chitwan-2", "Pokhara-3"};

// 2D array for candidates
string candidates[NUM_AREAS][MAX_CANDIDATES] = {
    {"KP Sharma Oli", "Balen Shah",  "Mandhara Chimariya", "Samir Tamang"},    
    {"Ranju Neupane", "Prakash Man Shrestha", "Rabindra Mishra", "Kiran Pokharel"},
    {"Rabi Lamichhane", "Mina Kumari Kharel", "Krishna Bhakta Pokharel", "Reena Gurud"},
};

// 2D array for votes
int votes[NUM_AREAS][MAX_CANDIDATES] = {{0}};

// Total votes per area
int totalVotesPerArea[NUM_AREAS] = {0};

// Function declaration
void clearInputBuffer();
int getValidInput(int min, int max);
void displayAreas();
void displayCandidates(int areaIndex);
void castVote();
void displayAreaResults(int areaIndex);
void displayAllResults();
void findWinner(int areaIndex);

// Clear input buffer
void clearInputBuffer() 
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Get valid integer input
int getValidInput(int min, int max) 
{
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

// Displaying all areas
void displayAreas() 
{
    cout << "\n+-------------------------------+" << endl;
    cout << "|      SELECT CONSTITUENCY      |" << endl;
    cout << "+-------------------------------+" << endl;
    for (int i = 0; i < NUM_AREAS; i++) {
        cout << "| " << i + 1 << ". " << areas[i] << endl;
    }
    cout << "+-------------------------------+" << endl;
}

// Display candidates for specific area
void displayCandidates(int areaIndex) 
{
    cout << "\n+---------------------------------+" << endl;
    cout << "| " << areas[areaIndex] << " CANDIDATES" << endl;
    cout << "+---------------------------------+" << endl;
    
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        cout << "| " << i + 1 << ". " << candidates[areaIndex][i] << endl;
    }
    cout << "+---------------------------------+" << endl;
}

// Cast vote
void castVote() 
{
    displayAreas();
    cout << "Select constituency (1-" << NUM_AREAS << "): ";
    int areaChoice = getValidInput(1, NUM_AREAS) - 1;
    
    displayCandidates(areaChoice);
    cout << "Select candidate (1-" << MAX_CANDIDATES << "): ";
    int candChoice = getValidInput(1, MAX_CANDIDATES) - 1;
    
    // Confirmation
    cout << "\n+---------------------------------+" << endl;
    cout << "|  VOTE CONFIRMATION              |" << endl;
    cout << "+---------------------------------+" << endl;
    cout << "| Area: " << areas[areaChoice] << endl;
    cout << "| Candidate: " << candidates[areaChoice][candChoice] << endl;
    cout << "+---------------------------------+" << endl;
    
    char confirm;
    cout << "Confirm vote? (Y/N): ";
    cin >> confirm;
    clearInputBuffer();
    
    if (confirm == 'Y' || confirm == 'y') {
        votes[areaChoice][candChoice]++;
        totalVotesPerArea[areaChoice]++;
        cout << "[OK] Vote recorded successfully!" << endl;
    } else {
        cout << "[X] Vote cancelled." << endl;
    }
}

// Find winner of an area
void findWinner(int areaIndex) 
{
    if (totalVotesPerArea[areaIndex] == 0) {
        cout << "No votes cast yet." << endl;
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
    
    cout << "** Leader: " << candidates[areaIndex][winnerIndex];
    cout << " (" << maxVotes << " votes) **" << endl;
}

// Display results for specific area
void displayAreaResults(int areaIndex) {
    cout << "\n+-------------------------------------------+" << endl;
    cout << "| RESULTS: " << areas[areaIndex] << endl;
    cout << "+-------------------------------------------+" << endl;
    
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        float percentage = 0;
        if (totalVotesPerArea[areaIndex] > 0) {
            percentage = (float)votes[areaIndex][i] / totalVotesPerArea[areaIndex] * 100;
        }
        
        cout << "| " << candidates[areaIndex][i] << ": ";
        cout << votes[areaIndex][i] << " votes (";
        cout << fixed << setprecision(1) << percentage << "%)" << endl;
    }
    
    cout << "+-------------------------------------------+" << endl;
    cout << "| Total Votes: " << totalVotesPerArea[areaIndex] << endl;
    cout << "+-------------------------------------------+" << endl;
    
    findWinner(areaIndex);
}

// Display all results
void displayAllResults() 
{
    cout << "\n";
    for (int i = 0; i < NUM_AREAS; i++) {
        displayAreaResults(i);
    }
}

// View results menu
void viewResults() 
{
    cout << "\n+-------------------------+" << endl;
    cout << "|    VIEW RESULTS         |" << endl;
    cout << "+-------------------------+" << endl;
    cout << "| 1. Specific Area        |" << endl;
    cout << "| 2. All Areas            |" << endl;
    cout << "+-------------------------+" << endl;
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

int main() 
{
    cout << "+================================+" << endl;
    cout << "|       VOTING SYSTEM v3.0       |" << endl;
    cout << "+================================+" << endl;
    
    bool running = true;
    
    while (running) {
        cout << "\n+--------------------------------+" << endl;
        cout << "|          MAIN MENU             |" << endl;
        cout << "+--------------------------------+" << endl;
        cout << "| 1. View Constituencies         |" << endl;
        cout << "| 2. View Candidates             |" << endl;
        cout << "| 3. Cast Vote                   |" << endl;
        cout << "| 4. View Results                |" << endl;
        cout << "| 5. Exit                        |" << endl;
        cout << "+--------------------------------+" << endl;
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
                cout << "\nThank you for using the Voting System!" << endl;
                break;
        }
    }
    
    return 0;
}