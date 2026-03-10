// VOTING SYSTEM v5.0 //

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits> 
using namespace std;

// Constants
const int NUM_AREAS = 7;
const int MAX_CANDIDATES = 4;
const int MAX_VOTERS = 1000;
const string ADMIN_PASSWORD = "admin123";
const string VOTES_FILE = "election_votes.txt";
const string VOTERS_FILE = "registered_voters.txt";

// Global Data

// Area names
string areas[NUM_AREAS] = {
    "Jhapa-5",
    "Kathmandu-1",
    "Chitwan-2",
    "Pokhara-3",
    "Biratnagar-4",
    "Sarlahi-4",
    "Bhaktapur-2"
};

// 2D array for candidates
string candidates[NUM_AREAS][MAX_CANDIDATES] = {

    {"KP Sharma Oli", "Balen Shah", "Keshav Prasad Budhathoki", "Rajendra Lingden"},
    {"Ranju Darshana Neupane", "Mohan Raj Regmi", "Prabal Thapa", "Rabindra Mishra"},
    {"Rabi Lamichhane", "Surya Prasad Adhikari", "Umesh Shrestha", "Vikram Pandey"},
    {"Dhan Raj Gurung", "Krishna Thapa", "Guru Raj Baral", "Deepak Bahadur Singh"},
    {"Nagarik Shah", "Lal Babu Pandit", "Amrit Aryal", "Rajendra Lingden"},
    {"Amresh Kumar Singh", "Amanish Kumar Yadav", "Gagan Kumar Thapa", "Pradeep Kumar Jha"},
    {"Rajiv Khatri", "Mahesh Basnet", "Kabir Rana", "Bikram Thapa"}
};

// Party affiliations
string parties[NUM_AREAS][MAX_CANDIDATES] = {
    {"UML", "Independent", "Congress", "Maoist"},
    {"Independent", "RSP", "Congress", "Congress"},
    {"Maoist", "UML", "Congress", "UML"},
    {"RSP", "Congress", "UML", "Congress"},
    {"Congress", "JSP", "Loktantrik", "Janamat"}
};

// 2D array for votes
int votes[NUM_AREAS][MAX_CANDIDATES] = {{0}};
int totalVotesPerArea[NUM_AREAS] = {0};

// Voter registration (1D array)
string registeredVoters[MAX_VOTERS];
int voterCount = 0;

// Election state
bool electionActive = true;


// Utility Functions

// Print a line of characters
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

// Get valid integer input with range
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

// Print visual bar for votes
void printBar(int value, int maxValue, int width) 
{
    int filled = 0;
    if (maxValue > 0) {
        filled = (value * width) / maxValue;
    }
    cout << "[";
    for (int i = 0; i < width; i++) {
        if (i < filled) {
            cout << "#";
        } else {
            cout << "-";
        }
    }
    cout << "]";
}

// File Handling 

// Save votes to file
void saveVotesToFile() {
    ofstream outFile(VOTES_FILE);
    
    if (!outFile) {
        cout << "[ERROR] Could not save votes!" << endl;
        return;
    }
    
    for (int i = 0; i < NUM_AREAS; i++) {
        for (int j = 0; j < MAX_CANDIDATES; j++) {
            outFile << votes[i][j] << " ";
        }
        outFile << endl;
    }
    
    outFile.close();
}

// Load votes from file
void loadVotesFromFile() {
    ifstream inFile(VOTES_FILE);
    
    if (!inFile) {
        cout << "[INFO] No previous vote data found." << endl;
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
    cout << "[OK] Vote data loaded successfully!" << endl;
}

// Save voters to file
void saveVotersToFile() {
    ofstream outFile(VOTERS_FILE);
    
    if (!outFile) {
        cout << "[ERROR] Could not save voter data!" << endl;
        return;
    }
    
    outFile << voterCount << endl;
    for (int i = 0; i < voterCount; i++) {
        outFile << registeredVoters[i] << endl;
    }
    
    outFile.close();
}

// Load voters from file
void loadVotersFromFile() {
    ifstream inFile(VOTERS_FILE);
    
    if (!inFile) {
        return;
    }
    
    inFile >> voterCount;
    inFile.ignore();
    
    for (int i = 0; i < voterCount && i < MAX_VOTERS; i++) {
        getline(inFile, registeredVoters[i]);
    }
    
    inFile.close();
    cout << "[OK] Voter registry loaded (" << voterCount << " voters)" << endl;
}

// Voter Functions

// Check if voter has already voted
bool hasVoted(string voterId) {
    for (int i = 0; i < voterCount; i++) {
        if (registeredVoters[i] == voterId) {
            return true;
        }
    }
    return false;
}

// Register voter after voting
bool registerVoter(string voterId) {
    if (voterCount >= MAX_VOTERS) {
        cout << "[!] Voter registry is full!" << endl;
        return false;
    }
    
    registeredVoters[voterCount] = voterId;
    voterCount++;
    saveVotersToFile();
    return true;
}


// Display Functions

// Display welcome screen
void displayWelcome() {
    cout << endl;
    printLine('=', 55);
    cout << "        ELECTRONIC VOTING SYSTEM v5.0" << endl;
    cout << "              Final Version" << endl;
    printLine('=', 55);
    cout << endl;
}

// Display all areas
void displayAreas() {
    cout << endl;
    printLine('-', 55);
    cout << "            AVAILABLE CONSTITUENCIES" << endl;
    printLine('-', 55);
    cout << " " << left << setw(5) << "No.";
    cout << setw(20) << "Constituency";
    cout << "Votes Cast" << endl;
    printLine('-', 55);
    
    for (int i = 0; i < NUM_AREAS; i++) {
        cout << " " << left << setw(5) << i + 1;
        cout << setw(20) << areas[i];
        cout << totalVotesPerArea[i] << endl;
    }
    printLine('-', 55);
}

// Display candidates for specific area
void displayCandidates(int areaIndex) {
    cout << endl;
    printLine('-', 60);
    cout << " " << areas[areaIndex] << " - CANDIDATES" << endl;
    printLine('-', 60);
    cout << " " << left << setw(5) << "No.";
    cout << setw(28) << "Candidate Name";
    cout << "Party" << endl;
    printLine('-', 60);
    
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        cout << " " << left << setw(5) << i + 1;
        cout << setw(28) << candidates[areaIndex][i];
        cout << parties[areaIndex][i] << endl;
    }
    printLine('-', 60);
}


// Voting Functions

// Cast vote - main voting function
void castVote() {
    // Check if election is active
    if (!electionActive) {
        cout << "\n[!] Election has been closed by administrator!" << endl;
        return;
    }
    
    // Get voter ID
    string voterId;
    cout << endl;
    printLine('-', 45);
    cout << "         VOTER VERIFICATION" << endl;
    printLine('-', 45);
    cout << "Enter your Voter ID (Citizenship No.): ";
    getline(cin, voterId);
    
    // Validate voter ID length
    if (voterId.empty() || voterId.length() < 5) {
        cout << "[!] Invalid Voter ID! Must be at least 5 characters." << endl;
        return;
    }
    
    // Check if already voted
    if (hasVoted(voterId)) {
        cout << endl;
        printLine('=', 50);
        cout << " [ERROR] You have already voted!" << endl;
        cout << " Each citizen can only vote once." << endl;
        printLine('=', 50);
        return;
    }
    
    // Select constituency
    displayAreas();
    cout << "Select your constituency (1-" << NUM_AREAS << ") or 0 to cancel: ";
    int areaChoice = getValidInput(0, NUM_AREAS);
    
    if (areaChoice == 0) {
        cout << "[X] Voting cancelled." << endl;
        return;
    }
    areaChoice--;
    
    // Select candidate
    displayCandidates(areaChoice);
    cout << "Select your candidate (1-" << MAX_CANDIDATES << ") or 0 to cancel: ";
    int candChoice = getValidInput(0, MAX_CANDIDATES);
    
    if (candChoice == 0) {
        cout << "[X] Voting cancelled." << endl;
        return;
    }
    candChoice--;
    
    // Show confirmation
    cout << endl;
    printLine('=', 55);
    cout << "            VOTE CONFIRMATION" << endl;
    printLine('=', 55);
    cout << " Voter ID    : " << voterId << endl;
    cout << " Constituency: " << areas[areaChoice] << endl;
    cout << " Candidate   : " << candidates[areaChoice][candChoice] << endl;
    cout << " Party       : " << parties[areaChoice][candChoice] << endl;
    printLine('=', 55);
    
    // Final confirmation
    char confirm;
    cout << "\n[!] Once confirmed, your vote cannot be changed!" << endl;
    cout << "Confirm your vote? (Y/N): ";
    cin >> confirm;
    clearInputBuffer();
    
    if (confirm == 'Y' || confirm == 'y') {
        // Record vote
        votes[areaChoice][candChoice]++;
        totalVotesPerArea[areaChoice]++;
        
        // Register voter to prevent duplicate voting
        registerVoter(voterId);
        
        // Save data to file
        saveVotesToFile();
        
        cout << endl;
        printLine('=', 55);
        cout << "    [OK] YOUR VOTE HAS BEEN RECORDED!" << endl;
        cout << "         Thank you for voting!" << endl;
        printLine('=', 55);
    } else {
        cout << "[X] Vote cancelled." << endl;
    }
}

//RESULTS FUNCTIONS

// Find winner of an area
string findWinner(int areaIndex, int &winnerVotes) {
    if (totalVotesPerArea[areaIndex] == 0) {
        winnerVotes = 0;
        return "No votes yet";
    }
    
    int maxVotes = 0;
    int winnerIndex = 0;
    
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        if (votes[areaIndex][i] > maxVotes) {
            maxVotes = votes[areaIndex][i];
            winnerIndex = i;
        }
    }
    
    winnerVotes = maxVotes;
    return candidates[areaIndex][winnerIndex];
}

// Display results for specific area with visual bars
void displayAreaResults(int areaIndex) 
{
    // Find max votes for bar scaling
    int maxVotes = 0;
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        if (votes[areaIndex][i] > maxVotes) {
            maxVotes = votes[areaIndex][i];
        }
    }
    
    cout << endl;
    printLine('=', 70);
    cout << " RESULTS: " << areas[areaIndex] << endl;
    printLine('=', 70);
    
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        float percentage = 0;
        if (totalVotesPerArea[areaIndex] > 0) {
            percentage = (float)votes[areaIndex][i] / totalVotesPerArea[areaIndex] * 100;
        }
        
        cout << " " << left << setw(24) << candidates[areaIndex][i] << " ";
        printBar(votes[areaIndex][i], (maxVotes > 0 ? maxVotes : 1), 15);
        cout << " " << right << setw(4) << votes[areaIndex][i];
        cout << " (" << fixed << setprecision(1) << setw(5) << percentage << "%)" << endl;
    }
    
    printLine('-', 70);
    cout << " Total Votes: " << totalVotesPerArea[areaIndex];
    
    int winnerVotes;
    string winner = findWinner(areaIndex, winnerVotes);
    cout << "   |   ** LEADING: " << winner << " (" << winnerVotes << " votes) **" << endl;
    printLine('=', 70);
}

// Display all results
void displayAllResults() {
    for (int i = 0; i < NUM_AREAS; i++) {
        displayAreaResults(i);
    }
}

// Display winners summary
void displayWinnersSummary() {
    cout << endl;
    printLine('=', 60);
    cout << "               WINNERS SUMMARY" << endl;
    printLine('=', 60);
    cout << " " << left << setw(18) << "Constituency";
    cout << setw(28) << "Leading Candidate";
    cout << "Votes" << endl;
    printLine('-', 60);
    
    for (int i = 0; i < NUM_AREAS; i++) {
        int winnerVotes;
        string winner = findWinner(i, winnerVotes);
        cout << " " << left << setw(18) << areas[i];
        cout << setw(28) << winner;
        cout << winnerVotes << endl;
    }
    printLine('=', 60);
}

// View results menu
void viewResults() {
    cout << endl;
    printLine('-', 35);
    cout << "         VIEW RESULTS" << endl;
    printLine('-', 35);
    cout << " 1. Specific Constituency" << endl;
    cout << " 2. All Constituencies" << endl;
    cout << " 3. Winners Summary" << endl;
    cout << " 4. Go Back" << endl;
    printLine('-', 35);
    cout << "Choice: ";
    
    int choice = getValidInput(1, 4);
    
    switch (choice) {
        case 1:
            displayAreas();
            cout << "Select constituency: ";
            displayAreaResults(getValidInput(1, NUM_AREAS) - 1);
            break;
        case 2:
            displayAllResults();
            break;
        case 3:
            displayWinnersSummary();
            break;
        case 4:
            break;
    }
}

// Admin Functions

// Admin login with password protection
bool adminLogin() {
    string password;
    int attempts = 3;
    
    cout << endl;
    printLine('-', 40);
    cout << "        ADMIN AUTHENTICATION" << endl;
    printLine('-', 40);
    
    while (attempts > 0) {
        cout << "Password (" << attempts << " attempts remaining): ";
        cin >> password;
        clearInputBuffer();
        
        if (password == ADMIN_PASSWORD) {
            cout << "[OK] Authentication successful!" << endl;
            return true;
        } else {
            attempts--;
            cout << "[X] Incorrect password!" << endl;
        }
    }
    
    cout << "[!] Access denied. Too many failed attempts." << endl;
    return false;
}

// Display comprehensive statistics
void displayStatistics() {
    int totalVotes = 0;
    int highestAreaVotes = 0;
    int lowestAreaVotes = 999999;
    int highestAreaIndex = 0;
    int lowestAreaIndex = 0;
    
    // Calculate statistics
    for (int i = 0; i < NUM_AREAS; i++) {
        totalVotes += totalVotesPerArea[i];
        if (totalVotesPerArea[i] > highestAreaVotes) {
            highestAreaVotes = totalVotesPerArea[i];
            highestAreaIndex = i;
        }
        if (totalVotesPerArea[i] < lowestAreaVotes) {
            lowestAreaVotes = totalVotesPerArea[i];
            lowestAreaIndex = i;
        }
    }
    
    float avgVotes = 0;
    if (NUM_AREAS > 0) {
        avgVotes = (float)totalVotes / NUM_AREAS;
    }
    
    cout << endl;
    printLine('=', 55);
    cout << "            ELECTION STATISTICS" << endl;
    printLine('=', 55);
    cout << " Total Votes Cast          : " << totalVotes << endl;
    cout << " Registered Voters         : " << voterCount << endl;
    cout << " Total Constituencies      : " << NUM_AREAS << endl;
    cout << " Total Candidates          : " << NUM_AREAS * MAX_CANDIDATES << endl;
    cout << " Average Votes/Constituency: " << fixed << setprecision(1) << avgVotes << endl;
    printLine('-', 55);
    cout << " Most Active   : " << areas[highestAreaIndex];
    cout << " (" << highestAreaVotes << " votes)" << endl;
    cout << " Least Active  : " << areas[lowestAreaIndex];
    cout << " (" << lowestAreaVotes << " votes)" << endl;
    cout << " Election Status: ";
    if (electionActive) {
        cout << "ACTIVE" << endl;
    } else {
        cout << "CLOSED" << endl;
    }
    printLine('=', 55);
}

// Reset all votes and voter registrations
void resetVotes() {
    cout << endl;
    printLine('=', 55);
    cout << " [WARNING] This action will:" << endl;
    cout << "   - Delete ALL recorded votes" << endl;
    cout << "   - Clear ALL voter registrations" << endl;
    cout << "   - This action CANNOT be undone!" << endl;
    printLine('=', 55);
    
    cout << "Type 'RESET' to confirm: ";
    string confirmation;
    getline(cin, confirmation);
    
    if (confirmation == "RESET") {
        // Reset all votes
        for (int i = 0; i < NUM_AREAS; i++) {
            totalVotesPerArea[i] = 0;
            for (int j = 0; j < MAX_CANDIDATES; j++) {
                votes[i][j] = 0;
            }
        }
        
        // Reset all voters
        voterCount = 0;
        for (int i = 0; i < MAX_VOTERS; i++) {
            registeredVoters[i] = "";
        }
        
        // Save empty data to files
        saveVotesToFile();
        saveVotersToFile();
        
        cout << "\n[OK] All data has been reset!" << endl;
    } else {
        cout << "[X] Reset cancelled." << endl;
    }
}

// Toggle election status (open/close)
void toggleElection() {
    electionActive = !electionActive;
    if (electionActive) {
        cout << "[OK] Election has been OPENED. Voting is now allowed." << endl;
    } else {
        cout << "[OK] Election has been CLOSED. No more votes will be accepted." << endl;
    }
}

// Admin panel
void adminPanel() {
    if (!adminLogin()) return;
    
    bool inAdmin = true;
    
    while (inAdmin) {
        cout << endl;
        printLine('-', 45);
        cout << "             ADMIN PANEL" << endl;
        printLine('-', 45);
        cout << " 1. View All Results" << endl;
        cout << " 2. View Statistics" << endl;
        if (electionActive) {
            cout << " 3. Close Election" << endl;
        } else {
            cout << " 3. Open Election" << endl;
        }
        cout << " 4. Reset All Data" << endl;
        cout << " 5. Save All Data" << endl;
        cout << " 6. Reload Data from Files" << endl;
        cout << " 7. Exit Admin Panel" << endl;
        printLine('-', 45);
        cout << "Choice: ";
        
        int choice = getValidInput(1, 7);
        
        switch (choice) {
            case 1:
                displayAllResults();
                break;
            case 2:
                displayStatistics();
                break;
            case 3:
                toggleElection();
                break;
            case 4:
                resetVotes();
                break;
            case 5:
                saveVotesToFile();
                saveVotersToFile();
                cout << "[OK] All data saved!" << endl;
                break;
            case 6:
                loadVotesFromFile();
                loadVotersFromFile();
                break;
            case 7:
                inAdmin = false;
                cout << "Exiting admin panel..." << endl;
                break;
        }
    }
}

// About

void displayAbout() {
    cout << endl;
    printLine('=', 60);
    cout << "         ELECTRONIC VOTING SYSTEM v5.0" << endl;
    printLine('=', 60);
    cout << " A comprehensive voting system featuring:" << endl;
    cout << endl;
    cout << " [+] 5 Constituencies with 4 candidates each" << endl;
    cout << " [+] Voter registration to prevent duplicate voting" << endl;
    cout << " [+] File-based data persistence" << endl;
    cout << " [+] Secure admin panel with authentication" << endl;
    cout << " [+] Comprehensive statistics and reporting" << endl;
    cout << " [+] Visual vote representation" << endl;
    cout << endl;
    cout << " Built with: C++" << endl;
    cout << " Features Used:" << endl;
    cout << "   - Control Structures (if-else, switch, loops)" << endl;
    cout << "   - Functions (20+ user-defined)" << endl;
    cout << "   - Arrays (1D and 2D)" << endl;
    cout << "   - File Handling (read/write)" << endl;
    cout << "   - Input Validation and Error Handling" << endl;
    printLine('=', 60);
}

// Main Menu

void displayMainMenu() {
    cout << endl;
    printLine('-', 45);
    cout << "              MAIN MENU" << endl;
    printLine('-', 45);
    cout << " 1. View Constituencies" << endl;
    cout << " 2. View Candidates" << endl;
    cout << " 3. Cast Your Vote" << endl;
    cout << " 4. View Results" << endl;
    cout << " 5. Admin Panel" << endl;
    cout << " 6. About" << endl;
    cout << " 7. Exit" << endl;
    printLine('-', 45);
    cout << "Enter your choice: ";
}

// Main Functions

int main() {
    // Display welcome screen
    displayWelcome();
    
    // Load existing data from files
    cout << "Loading system data..." << endl;
    loadVotesFromFile();
    loadVotersFromFile();
    
    bool running = true;
    
    // Main program loop
    while (running) {
        displayMainMenu();
        int option = getValidInput(1, 7);
        
        switch (option) {
            case 1:
                displayAreas();
                break;
                
            case 2:
                displayAreas();
                cout << "Select constituency: ";
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
                displayAbout();
                break;
                
            case 7:
                // Save data before exit
                saveVotesToFile();
                saveVotersToFile();
                running = false;
                
                cout << endl;
                printLine('=', 55);
                cout << "    Thank you for using the Voting System!" << endl;
                cout << "          Your data has been saved." << endl;
                printLine('=', 55);
                break;
        }
    }
    
    return 0;
}