// VOTING SYSTEM v4.0 //

#include <iostream>
#include <fstream>
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
    {"Arjun Khanal", "Yogesh Bhattarai", "Ramji Prasad Baral}
};

// 2D array for votes
int votes[NUM_AREAS][MAX_CANDIDATES] = {{0}};
int totalVotesPerArea[NUM_AREAS] = {0};

// Function to print a line
void printLine(char ch, int len) 
{
    for (int i = 0; i < len; i++) {
        cout << ch;
    }
    cout << endl;
}

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
            cout << "[!] Invalid! Enter a number: ";
        } else if (input < min || input > max) {
            cout << "[!] Enter between " << min << "-" << max << ": ";
        } else {
            clearInputBuffer();
            return input;
        }
    }
}

// Save votes to file
void saveVotesToFile() 
{
    ofstream outFile(DATA_FILE);
    
    if (!outFile) {
        cout << "[ERROR] Could not save data!" << endl;
        return;
    }
    
    for (int i = 0; i < NUM_AREAS; i++) {
        for (int j = 0; j < MAX_CANDIDATES; j++) {
            outFile << votes[i][j] << " ";
        }
        outFile << endl;
    }
    
    outFile.close();
    cout << "[OK] Data saved successfully!" << endl;
}

// Load votes from file
void loadVotesFromFile() 
{
    ifstream inFile(DATA_FILE);
    
    if (!inFile) {
        cout << "[INFO] No previous data found. Starting fresh." << endl;
        return;
    }
    
    for (int i = 0; i < NUM_AREAS; i++) {
        totalVotesPerArea[i] = 0;
        for (int j = 0; j < MAX_CANDIDATES; j++) {
            inFile >> votes[i][j];
            totalVotesPerArea[i] += votes[i][j];
        }
    }
    
    inFile.close();
    cout << "[OK] Previous data loaded successfully!" << endl;
}

// Display all areas
void displayAreas() 
{
    cout << endl;
    printLine('-', 45);
    cout << "        AVAILABLE CONSTITUENCIES" << endl;
    printLine('-', 45);
    
    for (int i = 0; i < NUM_AREAS; i++) {
        cout << " " << i + 1 << ". " << left << setw(15) << areas[i];
        cout << " (" << totalVotesPerArea[i] << " votes cast)" << endl;
    }
    printLine('-', 45);
}

// Display candidates for specific area
void displayCandidates(int areaIndex) 
{
    cout << endl;
    printLine('-', 40);
    cout << " " << areas[areaIndex] << " - CANDIDATES" << endl;
    printLine('-', 40);
    
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        cout << " " << i + 1 << ". " << candidates[areaIndex][i] << endl;
    }
    printLine('-', 40);
}

// Find winner of an area
void findWinner(int areaIndex) 
{
    if (totalVotesPerArea[areaIndex] == 0) {
        cout << " No votes cast yet." << endl;
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
    
    cout << " ** LEADING: " << candidates[areaIndex][winnerIndex];
    cout << " (" << maxVotes << " votes) **" << endl;
}

// Display results for specific area
void displayAreaResults(int areaIndex) 
{
    cout << endl;
    printLine('=', 50);
    cout << " RESULTS: " << areas[areaIndex] << endl;
    printLine('=', 50);
    
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        float percentage = 0;
        if (totalVotesPerArea[areaIndex] > 0) {
            percentage = (float)votes[areaIndex][i] / totalVotesPerArea[areaIndex] * 100;
        }
        
        cout << " " << left << setw(24) << candidates[areaIndex][i];
        cout << ": " << right << setw(4) << votes[areaIndex][i];
        cout << " (" << fixed << setprecision(1) << setw(5) << percentage << "%)" << endl;
    }
    
    printLine('-', 50);
    cout << " Total Votes: " << totalVotesPerArea[areaIndex] << endl;
    findWinner(areaIndex);
    printLine('=', 50);
}

// Display all results
void displayAllResults() 
{
    for (int i = 0; i < NUM_AREAS; i++) {
        displayAreaResults(i);
    }
}

// Cast vote
void castVote() 
{
    displayAreas();
    cout << "Select constituency (1-" << NUM_AREAS << ") or 0 to cancel: ";
    int areaChoice = getValidInput(0, NUM_AREAS);
    
    if (areaChoice == 0) {
        cout << "[X] Vote cancelled." << endl;
        return;
    }
    areaChoice--;
    
    displayCandidates(areaChoice);
    cout << "Select candidate (1-" << MAX_CANDIDATES << ") or 0 to cancel: ";
    int candChoice = getValidInput(0, MAX_CANDIDATES);
    
    if (candChoice == 0) {
        cout << "[X] Vote cancelled." << endl;
        return;
    }
    candChoice--;
    
    // Confirmation
    cout << endl;
    printLine('-', 45);
    cout << "         VOTE CONFIRMATION" << endl;
    printLine('-', 45);
    cout << " Constituency: " << areas[areaChoice] << endl;
    cout << " Candidate   : " << candidates[areaChoice][candChoice] << endl;
    printLine('-', 45);
    
    char confirm;
    cout << "Confirm your vote? (Y/N): ";
    cin >> confirm;
    clearInputBuffer();
    
    if (confirm == 'Y' || confirm == 'y') {
        votes[areaChoice][candChoice]++;
        totalVotesPerArea[areaChoice]++;
        saveVotesToFile();
        cout << "\n[OK] Vote recorded and saved successfully!" << endl;
    } else {
        cout << "[X] Vote cancelled." << endl;
    }
}

// View results menu
void viewResults() 
{
    cout << endl;
    printLine('-', 30);
    cout << "      VIEW RESULTS" << endl;
    printLine('-', 30);
    cout << " 1. Specific Constituency" << endl;
    cout << " 2. All Constituencies" << endl;
    cout << " 3. Go Back" << endl;
    printLine('-', 30);
    cout << "Choice: ";
    
    int choice = getValidInput(1, 3);
    
    if (choice == 1) {
        displayAreas();
        cout << "Select area: ";
        int area = getValidInput(1, NUM_AREAS) - 1;
        displayAreaResults(area);
    } else if (choice == 2) {
        displayAllResults();
    }
}

// Admin login
bool adminLogin() 
{
    string password;
    int attempts = 3;
    
    cout << endl;
    printLine('-', 35);
    cout << "     ADMIN AUTHENTICATION" << endl;
    printLine('-', 35);
    
    while (attempts > 0) {
        cout << "Enter password (" << attempts << " attempts left): ";
        cin >> password;
        clearInputBuffer();
        
        if (password == ADMIN_PASSWORD) {
            cout << "[OK] Login successful!" << endl;
            return true;
        } else {
            attempts--;
            cout << "[X] Incorrect password!" << endl;
        }
    }
    
    cout << "[!] Access denied. Too many failed attempts." << endl;
    return false;
}

// Reset all votes
void resetVotes() 
{
    char confirm;
    cout << "\n[WARNING] This will delete ALL votes!" << endl;
    cout << "Are you sure? (Y/N): ";
    cin >> confirm;
    clearInputBuffer();
    
    if (confirm == 'Y' || confirm == 'y') {
        for (int i = 0; i < NUM_AREAS; i++) {
            totalVotesPerArea[i] = 0;
            for (int j = 0; j < MAX_CANDIDATES; j++) {
                votes[i][j] = 0;
            }
        }
        saveVotesToFile();
        cout << "[OK] All votes have been reset!" << endl;
    } else {
        cout << "[X] Reset cancelled." << endl;
    }
}

// Display statistics
void displayStatistics() 
{
    int totalVotes = 0;
    int highestAreaVotes = 0;
    int highestAreaIndex = 0;
    
    for (int i = 0; i < NUM_AREAS; i++) {
        totalVotes += totalVotesPerArea[i];
        if (totalVotesPerArea[i] > highestAreaVotes) {
            highestAreaVotes = totalVotesPerArea[i];
            highestAreaIndex = i;
        }
    }
    
    cout << endl;
    printLine('=', 45);
    cout << "         VOTING STATISTICS" << endl;
    printLine('=', 45);
    cout << " Total Votes (All Areas): " << totalVotes << endl;
    cout << " Total Constituencies   : " << NUM_AREAS << endl;
    cout << " Most Active Area       : " << areas[highestAreaIndex] << endl;
    printLine('=', 45);
}

// Admin panel
void adminPanel() 
{
    if (!adminLogin()) return;
    
    bool inAdmin = true;
    
    while (inAdmin) {
        cout << endl;
        printLine('-', 35);
        cout << "         ADMIN PANEL" << endl;
        printLine('-', 35);
        cout << " 1. View All Results" << endl;
        cout << " 2. View Statistics" << endl;
        cout << " 3. Reset All Votes" << endl;
        cout << " 4. Save Data" << endl;
        cout << " 5. Load Data" << endl;
        cout << " 6. Exit Admin Panel" << endl;
        printLine('-', 35);
        cout << "Choice: ";
        
        int choice = getValidInput(1, 6);
        
        switch (choice) {
            case 1:
                displayAllResults();
                break;
            case 2:
                displayStatistics();
                break;
            case 3:
                resetVotes();
                break;
            case 4:
                saveVotesToFile();
                break;
            case 5:
                loadVotesFromFile();
                break;
            case 6:
                inAdmin = false;
                cout << "Exiting admin panel..." << endl;
                break;
        }
    }
}

int main() 
{
    cout << endl;
    printLine('=', 50);
    cout << "         VOTING SYSTEM v4.0" << endl;
    cout << "    With File Handling & Admin Panel" << endl;
    printLine('=', 50);
    
    // Load previous data
    loadVotesFromFile();
    
    bool running = true;
    
    while (running) {
        cout << endl;
        printLine('-', 40);
        cout << "            MAIN MENU" << endl;
        printLine('-', 40);
        cout << " 1. View Constituencies" << endl;
        cout << " 2. View Candidates" << endl;
        cout << " 3. Cast Vote" << endl;
        cout << " 4. View Results" << endl;
        cout << " 5. Admin Panel" << endl;
        cout << " 6. Exit" << endl;
        printLine('-', 40);
        cout << "Enter choice: ";
        
        int option = getValidInput(1, 6);
        
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
                adminPanel();
                break;
            case 6:
                saveVotesToFile();
                running = false;
                cout << "\nThank you for using the Voting System!" << endl;
                break;
        }
    }
    
    return 0;
}