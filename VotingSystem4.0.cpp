// VOTING SYSTEM v4.0 //

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>
#include <cstdlib>
using namespace std;

// Constants
const int NUM_AREAS = 4;
const int MAX_CANDIDATES = 4;
const string ADMIN_PASSWORD = "admin123";
const string DATA_FILE = "votes_v4.txt";

// Structs

// Struct for Candidate
struct Candidate {
    string name;
    int votes;
};

// Struct for Constituency/Area
struct Constituency {
    string name;
    Candidate candidates[MAX_CANDIDATES];
    int totalVotes;
};

// Struct for Election Data
struct ElectionData {
    Constituency areas[NUM_AREAS];
    int totalConstituencies;
};

// Global data
ElectionData election;

// Utility Function

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.get();
}

void printLine(char ch, int len) {
    for (int i = 0; i < len; i++) {
        cout << ch;
    }
    cout << endl;
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getValidInput(int min, int max) {
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

// Initialization

void initializeElection() {
    election.totalConstituencies = NUM_AREAS;
    
    // Area names
    string areaNames[NUM_AREAS] = {
        "Jhapa-5", 
        "Kathmandu-1", 
        "Chitwan-2", 
        "Pokhara-3"
    };
    
    // Candidate names for each area
    string candidateNames[NUM_AREAS][MAX_CANDIDATES] = {
    {"KP Sharma Oli", "Balen Shah",  "Mandhara Chimariya", "Samir Tamang"},    
    {"Ranju Neupane", "Prakash Man Shrestha", "Rabindra Mishra", "Kiran Pokharel"},
    {"Rabi Lamichhane", "Mina Kumari Kharel", "Krishna Bhakta Pokharel", "Reena Gurud"},
    {"Arjun Khanal", "Yogesh Bhattarai", "Ramji Prasad Baral"}
    
};
        
    
    // Initialize each constituency
    for (int i = 0; i < NUM_AREAS; i++) {
        election.areas[i].name = areaNames[i];
        election.areas[i].totalVotes = 0;
        
        // Initialize each candidate in this constituency
        for (int j = 0; j < MAX_CANDIDATES; j++) {
            election.areas[i].candidates[j].name = candidateNames[i][j];
            election.areas[i].candidates[j].votes = 0;
        }
    }
}

// File Handling

void saveVotesToFile() {
    ofstream outFile(DATA_FILE);
    
    if (!outFile) {
        cout << "[ERROR] Could not save data!" << endl;
        return;
    }
    
    // Save votes for each constituency and candidate
    for (int i = 0; i < NUM_AREAS; i++) {
        for (int j = 0; j < MAX_CANDIDATES; j++) {
            outFile << election.areas[i].candidates[j].votes << " ";
        }
        outFile << endl;
    }
    
    outFile.close();
    cout << "[OK] Data saved successfully!" << endl;
}

void loadVotesFromFile() {
    ifstream inFile(DATA_FILE);
    
    if (!inFile) {
        cout << "[INFO] No previous data found. Starting fresh." << endl;
        return;
    }
    
    // Load votes for each constituency and candidate
    for (int i = 0; i < NUM_AREAS; i++) {
        election.areas[i].totalVotes = 0;
        
        for (int j = 0; j < MAX_CANDIDATES; j++) {
            inFile >> election.areas[i].candidates[j].votes;
            election.areas[i].totalVotes += election.areas[i].candidates[j].votes;
        }
    }
    
    inFile.close();
    cout << "[OK] Previous data loaded successfully!" << endl;
}

// Display Function

void displayAreas() {
    cout << endl;
    printLine('-', 50);
    cout << "        AVAILABLE CONSTITUENCIES" << endl;
    printLine('-', 50);
    cout << " " << left << setw(5) << "No.";
    cout << setw(20) << "Constituency";
    cout << "Votes Cast" << endl;
    printLine('-', 50);
    
    for (int i = 0; i < NUM_AREAS; i++) {
        cout << " " << left << setw(5) << i + 1;
        cout << setw(20) << election.areas[i].name;
        cout << election.areas[i].totalVotes << endl;
    }
    printLine('-', 50);
}

void displayCandidates(int areaIndex) {
    cout << endl;
    printLine('-', 45);
    cout << " " << election.areas[areaIndex].name << " - CANDIDATES" << endl;
    printLine('-', 45);
    cout << " " << left << setw(5) << "No.";
    cout << "Candidate Name" << endl;
    printLine('-', 45);
    
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        cout << " " << left << setw(5) << i + 1;
        cout << election.areas[areaIndex].candidates[i].name << endl;
    }
    printLine('-', 45);
}

// Function to find winner using struct
Candidate findWinner(int areaIndex) {
    Candidate winner;
    winner.name = "No votes yet";
    winner.votes = 0;
    
    if (election.areas[areaIndex].totalVotes == 0) {
        return winner;
    }
    
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        if (election.areas[areaIndex].candidates[i].votes > winner.votes) {
            winner = election.areas[areaIndex].candidates[i];
        }
    }
    
    return winner;
}

void displayAreaResults(int areaIndex) {
    Constituency area = election.areas[areaIndex];
    
    cout << endl;
    printLine('=', 55);
    cout << " RESULTS: " << area.name << endl;
    printLine('=', 55);
    
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        float percentage = 0;
        if (area.totalVotes > 0) {
            percentage = (float)area.candidates[i].votes / area.totalVotes * 100;
        }
        
        cout << " " << left << setw(26) << area.candidates[i].name;
        cout << ": " << right << setw(4) << area.candidates[i].votes;
        cout << " (" << fixed << setprecision(1) << setw(5) << percentage << "%)" << endl;
    }
    
    printLine('-', 55);
    cout << " Total Votes: " << area.totalVotes << endl;
    
    Candidate winner = findWinner(areaIndex);
    cout << " ** LEADING: " << winner.name << " (" << winner.votes << " votes) **" << endl;
    printLine('=', 55);
}

void displayAllResults() {
    for (int i = 0; i < NUM_AREAS; i++) {
        displayAreaResults(i);
    }
}

// Voting Function

void castVote() {
    clearScreen();
    
    displayAreas();
    cout << "Select constituency (1-" << NUM_AREAS << ") or 0 to cancel: ";
    int areaChoice = getValidInput(0, NUM_AREAS);
    
    if (areaChoice == 0) {
        cout << "[X] Vote cancelled." << endl;
        pauseScreen();
        return;
    }
    areaChoice--;
    
    clearScreen();
    
    displayCandidates(areaChoice);
    cout << "Select candidate (1-" << MAX_CANDIDATES << ") or 0 to cancel: ";
    int candChoice = getValidInput(0, MAX_CANDIDATES);
    
    if (candChoice == 0) {
        cout << "[X] Vote cancelled." << endl;
        pauseScreen();
        return;
    }
    candChoice--;
    
    clearScreen();
    
    // Show confirmation using struct data
    cout << endl;
    printLine('-', 50);
    cout << "         VOTE CONFIRMATION" << endl;
    printLine('-', 50);
    cout << " Constituency: " << election.areas[areaChoice].name << endl;
    cout << " Candidate   : " << election.areas[areaChoice].candidates[candChoice].name << endl;
    printLine('-', 50);
    
    char confirm;
    cout << "Confirm your vote? (Y/N): ";
    cin >> confirm;
    clearInputBuffer();
    
    if (confirm == 'Y' || confirm == 'y') {
        // Update votes using struct
        election.areas[areaChoice].candidates[candChoice].votes++;
        election.areas[areaChoice].totalVotes++;
        
        saveVotesToFile();
        cout << "\n[OK] Vote recorded and saved successfully!" << endl;
    } else {
        cout << "[X] Vote cancelled." << endl;
    }
    
    pauseScreen();
}

// ==================== VIEW RESULTS ====================

void viewResults() {
    clearScreen();
    
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
        clearScreen();
        displayAreas();
        cout << "Select area: ";
        int area = getValidInput(1, NUM_AREAS) - 1;
        clearScreen();
        displayAreaResults(area);
        pauseScreen();
    } else if (choice == 2) {
        clearScreen();
        displayAllResults();
        pauseScreen();
    }
}

// ==================== ADMIN FUNCTIONS ====================

bool adminLogin() {
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
            pauseScreen();
            return true;
        } else {
            attempts--;
            cout << "[X] Incorrect password!" << endl;
        }
    }
    
    cout << "[!] Access denied. Too many failed attempts." << endl;
    pauseScreen();
    return false;
}

void resetVotes() {
    char confirm;
    cout << "\n[WARNING] This will delete ALL votes!" << endl;
    cout << "Are you sure? (Y/N): ";
    cin >> confirm;
    clearInputBuffer();
    
    if (confirm == 'Y' || confirm == 'y') {
        // Reset using struct
        for (int i = 0; i < NUM_AREAS; i++) {
            election.areas[i].totalVotes = 0;
            for (int j = 0; j < MAX_CANDIDATES; j++) {
                election.areas[i].candidates[j].votes = 0;
            }
        }
        saveVotesToFile();
        cout << "[OK] All votes have been reset!" << endl;
    } else {
        cout << "[X] Reset cancelled." << endl;
    }
    pauseScreen();
}

void displayStatistics() {
    int totalVotes = 0;
    int highestAreaVotes = 0;
    int highestAreaIndex = 0;
    
    // Calculate statistics using struct
    for (int i = 0; i < NUM_AREAS; i++) {
        totalVotes += election.areas[i].totalVotes;
        if (election.areas[i].totalVotes > highestAreaVotes) {
            highestAreaVotes = election.areas[i].totalVotes;
            highestAreaIndex = i;
        }
    }
    
    cout << endl;
    printLine('=', 50);
    cout << "         VOTING STATISTICS" << endl;
    printLine('=', 50);
    cout << " Total Votes (All Areas): " << totalVotes << endl;
    cout << " Total Constituencies   : " << election.totalConstituencies << endl;
    cout << " Most Active Area       : " << election.areas[highestAreaIndex].name << endl;
    printLine('=', 50);
    
    pauseScreen();
}

void adminPanel() {
    clearScreen();
    
    if (!adminLogin()) return;
    
    bool inAdmin = true;
    
    while (inAdmin) {
        clearScreen();
        
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
                clearScreen();
                displayAllResults();
                pauseScreen();
                break;
            case 2:
                clearScreen();
                displayStatistics();
                break;
            case 3:
                clearScreen();
                resetVotes();
                break;
            case 4:
                saveVotesToFile();
                pauseScreen();
                break;
            case 5:
                loadVotesFromFile();
                pauseScreen();
                break;
            case 6:
                inAdmin = false;
                cout << "Exiting admin panel..." << endl;
                break;
        }
    }
}

// Main Function

int main() {
    // Initialize election data using struct
    initializeElection();
    
    clearScreen();
    
    cout << endl;
    printLine('=', 55);
    cout << "           VOTING SYSTEM v4.0" << endl;
    cout << "    With Structs, File Handling & Admin Panel" << endl;
    printLine('=', 55);
    
    // Load previous data
    loadVotesFromFile();
    pauseScreen();
    
    bool running = true;
    
    while (running) {
        clearScreen();
        
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
                clearScreen();
                displayAreas();
                pauseScreen();
                break;
            case 2:
                clearScreen();
                displayAreas();
                cout << "Select area: ";
                {
                    int area = getValidInput(1, NUM_AREAS) - 1;
                    clearScreen();
                    displayCandidates(area);
                }
                pauseScreen();
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
                clearScreen();
                saveVotesToFile();
                running = false;
                cout << "\nThank you for using the Voting System!" << endl;
                break;
        }
    }
    
    return 0;
}