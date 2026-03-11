// VOTING SYSTEM v5.0 //

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>
#include <cstdlib>
using namespace std;

// Constants
const int NUM_AREAS = 7;
const int MAX_CANDIDATES = 4;
const int MAX_VOTERS = 1000;
const string ADMIN_PASSWORD = "admin123";
const string VOTES_FILE = "election_votes_v5.txt";
const string VOTERS_FILE = "registered_voters_v5.txt";

// Structs

// Struct for Candidate
struct Candidate {
    string name;
    string party;
    int votes;
};

// Struct for Constituency/Area
struct Constituency {
    string name;
    Candidate candidates[MAX_CANDIDATES];
    int totalVotes;
};

// Struct for Voter
struct Voter {
    string voterID;
};

// Struct for Voter Registry
struct VoterRegistry {
    Voter voters[MAX_VOTERS];
    int count;
};

// Struct for Election Data
struct ElectionData {
    Constituency areas[NUM_AREAS];
    int totalConstituencies;
    bool isActive;
};

// Struct for Statistics
struct Statistics {
    int totalVotes;
    int totalVoters;
    int mostActiveAreaIndex;
    int leastActiveAreaIndex;
    float averageVotesPerArea;
};

// Global Data
ElectionData election;
VoterRegistry voterRegistry;

// Utility Functions

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

void printBar(int value, int maxValue, int width) {
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

// Initialization

void initializeElection() {
    election.totalConstituencies = NUM_AREAS;
    election.isActive = true;
    
    // Area names
    string areaNames[NUM_AREAS] = {
        "Jhapa-5",
        "Kathmandu-1",
        "Chitwan-2",
        "Pokhara-3",
        "Biratnagar-4",
        "Sarlahi-4",
        "Bhaktapur-2"
    };
    
    // Candidate names for each area
    string candidateNames[NUM_AREAS][MAX_CANDIDATES] = {
        {"KP Sharma Oli", "Balen Shah", "Keshav Prasad Budhathoki", "Rajendra Lingden"},
        {"Ranju Darshana Neupane", "Mohan Raj Regmi", "Prabal Thapa", "Rabindra Mishra"},
        {"Rabi Lamichhane", "Surya Prasad Adhikari", "Umesh Shrestha", "Vikram Pandey"},
        {"Dhan Raj Gurung", "Krishna Thapa", "Guru Raj Baral", "Deepak Bahadur Singh"},
        {"Nagarik Shah", "Lal Babu Pandit", "Amrit Aryal", "Rajendra Lingden"},
        {"Amresh Kumar Singh", "Amanish Kumar Yadav", "Gagan Kumar Thapa", "Pradeep Kumar Jha"},
        {"Rajiv Khatri", "Mahesh Basnet", "Kabir Rana", "Bikram Thapa"}
    };

    // Party names for each candidate
    string partyNames[NUM_AREAS][MAX_CANDIDATES] = {
        {"UML", "Independent", "Congress", "RPP"},
        {"Bibeksheel", "RSP", "Congress", "RPP"},
        {"RSP", "UML", "Congress", "RPP"},
        {"Congress", "UML", "UML", "Congress"},
        {"Independent", "UML", "Congress", "RPP"},
        {"Congress", "Janamat", "Congress", "Loktantrik"},
        {"Congress", "UML", "Independent", "RSP"}
    };
    
    // Initialize each constituency
    for (int i = 0; i < NUM_AREAS; i++) {
        election.areas[i].name = areaNames[i];
        election.areas[i].totalVotes = 0;
        
        // Initialize each candidate
        for (int j = 0; j < MAX_CANDIDATES; j++) {
            election.areas[i].candidates[j].name = candidateNames[i][j];
            election.areas[i].candidates[j].party = partyNames[i][j];
            election.areas[i].candidates[j].votes = 0;
        }
    }
    
    // Initialize voter registry
    voterRegistry.count = 0;
}

// File Handling

void saveVotesToFile() {
    ofstream outFile(VOTES_FILE);
    
    if (!outFile) {
        cout << "[ERROR] Could not save votes!" << endl;
        return;
    }
    
    // Save election status
    outFile << election.isActive << endl;
    
    // Save votes for each constituency and candidate
    for (int i = 0; i < NUM_AREAS; i++) {
        for (int j = 0; j < MAX_CANDIDATES; j++) {
            outFile << election.areas[i].candidates[j].votes << " ";
        }
        outFile << endl;
    }
    
    outFile.close();
}

void loadVotesFromFile() {
    ifstream inFile(VOTES_FILE);
    
    if (!inFile) {
        cout << "[INFO] No previous vote data found." << endl;
        return;
    }
    
    // Load election status
    inFile >> election.isActive;
    
    // Load votes for each constituency and candidate
    for (int i = 0; i < NUM_AREAS; i++) {
        election.areas[i].totalVotes = 0;
        
        for (int j = 0; j < MAX_CANDIDATES; j++) {
            inFile >> election.areas[i].candidates[j].votes;
            election.areas[i].totalVotes += election.areas[i].candidates[j].votes;
        }
    }
    
    inFile.close();
    cout << "[OK] Vote data loaded successfully!" << endl;
}

void saveVotersToFile() {
    ofstream outFile(VOTERS_FILE);
    
    if (!outFile) {
        cout << "[ERROR] Could not save voter data!" << endl;
        return;
    }
    
    outFile << voterRegistry.count << endl;
    for (int i = 0; i < voterRegistry.count; i++) {
        outFile << voterRegistry.voters[i].voterID << endl;
    }
    
    outFile.close();
}

// FIXED: Changed voterId to voterID
void loadVotersFromFile() {
    ifstream inFile(VOTERS_FILE);
    
    if (!inFile) {
        return;
    }
    
    inFile >> voterRegistry.count;
    inFile.ignore();
    
    for (int i = 0; i < voterRegistry.count && i < MAX_VOTERS; i++) {
        getline(inFile, voterRegistry.voters[i].voterID);
    }
    
    inFile.close();
    cout << "[OK] Voter registry loaded (" << voterRegistry.count << " voters)" << endl;
}

// Voter Functions

bool hasVoted(string voterID) {
    for (int i = 0; i < voterRegistry.count; i++) {
        if (voterRegistry.voters[i].voterID == voterID) {
            return true;
        }
    }
    return false;
}

bool registerVoter(string voterID) {
    if (voterRegistry.count >= MAX_VOTERS) {
        cout << "[!] Voter registry is full!" << endl;
        return false;
    }
    
    voterRegistry.voters[voterRegistry.count].voterID = voterID;
    voterRegistry.count++;
    saveVotersToFile();
    return true;
}

// Display Functions

void displayWelcome() {
    cout << endl;
    printLine('=', 55);
    cout << "        ELECTRONIC VOTING SYSTEM v5.0" << endl;
    cout << "         Final Version with Structs" << endl;
    printLine('=', 55);
    cout << endl;
}

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
        cout << setw(20) << election.areas[i].name;
        cout << election.areas[i].totalVotes << endl;
    }
    printLine('-', 55);
}

void displayCandidates(int areaIndex) {
    Constituency area = election.areas[areaIndex];
    
    cout << endl;
    printLine('-', 60);
    cout << " " << area.name << " - CANDIDATES" << endl;
    printLine('-', 60);
    cout << " " << left << setw(5) << "No.";
    cout << setw(28) << "Candidate Name";
    cout << "Party" << endl;
    printLine('-', 60);
    
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        cout << " " << left << setw(5) << i + 1;
        cout << setw(28) << area.candidates[i].name;
        cout << area.candidates[i].party << endl;
    }
    printLine('-', 60);
}

// Results Functions

// Function to find winner
Candidate findWinner(int areaIndex) {
    Candidate winner;
    winner.name = "No votes yet";
    winner.party = "";
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
    
    // Find max votes for bar scaling
    int maxVotes = 0;
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        if (area.candidates[i].votes > maxVotes) {
            maxVotes = area.candidates[i].votes;
        }
    }
    
    cout << endl;
    printLine('=', 70);
    cout << " RESULTS: " << area.name << endl;
    printLine('=', 70);
    
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        Candidate cand = area.candidates[i];
        float percentage = 0;
        
        if (area.totalVotes > 0) {
            percentage = (float)cand.votes / area.totalVotes * 100;
        }
        
        cout << " " << left << setw(24) << cand.name << " ";
        printBar(cand.votes, (maxVotes > 0 ? maxVotes : 1), 15);
        cout << " " << right << setw(4) << cand.votes;
        cout << " (" << fixed << setprecision(1) << setw(5) << percentage << "%)" << endl;
    }
    
    printLine('-', 70);
    cout << " Total Votes: " << area.totalVotes;
    
    Candidate winner = findWinner(areaIndex);
    cout << "   |   ** LEADING: " << winner.name << " (" << winner.votes << " votes) **" << endl;
    printLine('=', 70);
}

void displayAllResults() {
    for (int i = 0; i < NUM_AREAS; i++) {
        displayAreaResults(i);
    }
}

void displayWinnersSummary() {
    cout << endl;
    printLine('=', 65);
    cout << "               WINNERS SUMMARY" << endl;
    printLine('=', 65);
    cout << " " << left << setw(18) << "Constituency";
    cout << setw(25) << "Leading Candidate";
    cout << setw(12) << "Party";
    cout << "Votes" << endl;
    printLine('-', 65);
    
    for (int i = 0; i < NUM_AREAS; i++) {
        Candidate winner = findWinner(i);
        cout << " " << left << setw(18) << election.areas[i].name;
        cout << setw(25) << winner.name;
        cout << setw(12) << winner.party;
        cout << winner.votes << endl;
    }
    printLine('=', 65);
}

void viewResults() {
    clearScreen();
    
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
            clearScreen();
            displayAreas();
            cout << "Select constituency: ";
            {
                int area = getValidInput(1, NUM_AREAS) - 1;
                clearScreen();
                displayAreaResults(area);
            }
            pauseScreen();
            break;
        case 2:
            clearScreen();
            displayAllResults();
            pauseScreen();
            break;
        case 3:
            clearScreen();
            displayWinnersSummary();
            pauseScreen();
            break;
        case 4:
            break;
    }
}

// Voting Function

void castVote() {
    clearScreen();
    
    if (!election.isActive) {
        cout << "\n[!] Election has been closed by administrator!" << endl;
        pauseScreen();
        return;
    }
    
    string voterID; 
    cout << endl;
    printLine('-', 45);
    cout << "         VOTER VERIFICATION" << endl;
    printLine('-', 45);
    cout << "Enter your Voter ID (Citizenship No.): ";
    getline(cin, voterID); 
    
    if (voterID.empty() || voterID.length() < 5) { 
        cout << "[!] Invalid Voter ID! Must be at least 5 characters." << endl;
        pauseScreen();
        return;
    }
    
    if (hasVoted(voterID)) { 
        clearScreen();
        cout << endl;
        printLine('=', 50);
        cout << " [ERROR] You have already voted!" << endl;
        cout << " Each citizen can only vote once." << endl;
        printLine('=', 50);
        pauseScreen();
        return;
    }
    
    clearScreen();
    
    displayAreas();
    cout << "Select your constituency (1-" << NUM_AREAS << ") or 0 to cancel: ";
    int areaChoice = getValidInput(0, NUM_AREAS);
    
    if (areaChoice == 0) {
        cout << "[X] Voting cancelled." << endl;
        pauseScreen();
        return;
    }
    areaChoice--;
    
    clearScreen();
    
    displayCandidates(areaChoice);
    cout << "Select your candidate (1-" << MAX_CANDIDATES << ") or 0 to cancel: ";
    int candChoice = getValidInput(0, MAX_CANDIDATES);
    
    if (candChoice == 0) {
        cout << "[X] Voting cancelled." << endl;
        pauseScreen();
        return;
    }
    candChoice--;
    
    clearScreen();
    
    // Get selected constituency and candidate using structs
    Constituency selectedArea = election.areas[areaChoice];
    Candidate selectedCandidate = selectedArea.candidates[candChoice];
    
    cout << endl;
    printLine('=', 55);
    cout << "            VOTE CONFIRMATION" << endl;
    printLine('=', 55);
    cout << " Voter ID    : " << voterID << endl;
    cout << " Constituency: " << selectedArea.name << endl;
    cout << " Candidate   : " << selectedCandidate.name << endl;
    cout << " Party       : " << selectedCandidate.party << endl;
    printLine('=', 55);
    
    char confirm;
    cout << "\n[!] Once confirmed, your vote cannot be changed!" << endl;
    cout << "Confirm your vote? (Y/N): ";
    cin >> confirm;
    clearInputBuffer();
    
    if (confirm == 'Y' || confirm == 'y') {
        // Update votes using struct reference
        election.areas[areaChoice].candidates[candChoice].votes++;
        election.areas[areaChoice].totalVotes++;
        
        registerVoter(voterID);
        saveVotesToFile();
        
        clearScreen();
        cout << endl;
        printLine('=', 55);
        cout << "    [OK] YOUR VOTE HAS BEEN RECORDED!" << endl;
        cout << "         Thank you for voting!" << endl;
        printLine('=', 55);
    } else {
        cout << "[X] Vote cancelled." << endl;
    }
    
    pauseScreen();
}

// Statistics Functions

// Function that returns Statistics struct
Statistics calculateStatistics() {
    Statistics stats;
    stats.totalVotes = 0;
    stats.totalVoters = voterRegistry.count;
    stats.mostActiveAreaIndex = 0;
    stats.leastActiveAreaIndex = 0;
    
    int highestVotes = 0;
    int lowestVotes = 999999;
    
    for (int i = 0; i < NUM_AREAS; i++) {
        stats.totalVotes += election.areas[i].totalVotes;
        
        if (election.areas[i].totalVotes > highestVotes) {
            highestVotes = election.areas[i].totalVotes;
            stats.mostActiveAreaIndex = i;
        }
        if (election.areas[i].totalVotes < lowestVotes) {
            lowestVotes = election.areas[i].totalVotes;
            stats.leastActiveAreaIndex = i;
        }
    }
    
    stats.averageVotesPerArea = (NUM_AREAS > 0) ? (float)stats.totalVotes / NUM_AREAS : 0;
    
    return stats;
}

void displayStatistics() {
    // Get statistics using struct
    Statistics stats = calculateStatistics();
    
    cout << endl;
    printLine('=', 55);
    cout << "            ELECTION STATISTICS" << endl;
    printLine('=', 55);
    cout << " Total Votes Cast          : " << stats.totalVotes << endl;
    cout << " Registered Voters         : " << stats.totalVoters << endl;
    cout << " Total Constituencies      : " << election.totalConstituencies << endl;
    cout << " Total Candidates          : " << NUM_AREAS * MAX_CANDIDATES << endl;
    cout << " Average Votes/Constituency: " << fixed << setprecision(1) << stats.averageVotesPerArea << endl;
    printLine('-', 55);
    cout << " Most Active   : " << election.areas[stats.mostActiveAreaIndex].name;
    cout << " (" << election.areas[stats.mostActiveAreaIndex].totalVotes << " votes)" << endl;
    cout << " Least Active  : " << election.areas[stats.leastActiveAreaIndex].name;
    cout << " (" << election.areas[stats.leastActiveAreaIndex].totalVotes << " votes)" << endl;
    cout << " Election Status: ";
    if (election.isActive) {
        cout << "ACTIVE" << endl;
    } else {
        cout << "CLOSED" << endl;
    }
    printLine('=', 55);
}

// Admin Functions

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
        // Reset all votes using structs
        for (int i = 0; i < NUM_AREAS; i++) {
            election.areas[i].totalVotes = 0;
            for (int j = 0; j < MAX_CANDIDATES; j++) {
                election.areas[i].candidates[j].votes = 0;
            }
        }
        
        // Reset voter registry
        voterRegistry.count = 0;
        for (int i = 0; i < MAX_VOTERS; i++) {
            voterRegistry.voters[i].voterID = "";
        }
        
        saveVotesToFile();
        saveVotersToFile();
        
        cout << "\n[OK] All data has been reset!" << endl;
    } else {
        cout << "[X] Reset cancelled." << endl;
    }
}

void toggleElection() {
    election.isActive = !election.isActive;
    saveVotesToFile();
    
    if (election.isActive) {
        cout << "[OK] Election has been OPENED. Voting is now allowed." << endl;
    } else {
        cout << "[OK] Election has been CLOSED. No more votes will be accepted." << endl;
    }
}

void adminPanel() {
    clearScreen();
    
    if (!adminLogin()) return;
    
    bool inAdmin = true;
    
    while (inAdmin) {
        clearScreen();
        
        cout << endl;
        printLine('-', 45);
        cout << "             ADMIN PANEL" << endl;
        printLine('-', 45);
        cout << " 1. View All Results" << endl;
        cout << " 2. View Statistics" << endl;
        if (election.isActive) {
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
                clearScreen();
                displayAllResults();
                pauseScreen();
                break;
            case 2:
                clearScreen();
                displayStatistics();
                pauseScreen();
                break;
            case 3:
                toggleElection();
                pauseScreen();
                break;
            case 4:
                clearScreen();
                resetVotes();
                pauseScreen();
                break;
            case 5:
                saveVotesToFile();
                saveVotersToFile();
                cout << "[OK] All data saved!" << endl;
                pauseScreen();
                break;
            case 6:
                loadVotesFromFile();
                loadVotersFromFile();
                pauseScreen();
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
    clearScreen();
    
    cout << endl;
    printLine('=', 60);
    cout << "         ELECTRONIC VOTING SYSTEM v5.0" << endl;
    printLine('=', 60);
    cout << endl;
    cout << " Structs Used:" << endl;
    cout << "   - Candidate  : name, party, votes" << endl;
    cout << "   - Constituency: name, candidates[], totalVotes" << endl;
    cout << "   - Voter      : voterID" << endl;
    cout << "   - VoterRegistry: voters[], count" << endl;
    cout << "   - ElectionData: areas[], totalConstituencies, isActive" << endl;
    cout << "   - Statistics : totalVotes, averageVotes, etc." << endl;
    cout << endl;
    cout << " Features:" << endl;
    cout << "   [+] 7 Constituencies with 4 candidates each" << endl;
    cout << "   [+] Voter registration to prevent duplicate voting" << endl;
    cout << "   [+] File-based data persistence" << endl;
    cout << "   [+] Secure admin panel with authentication" << endl;
    cout << "   [+] Comprehensive statistics and reporting" << endl;
    cout << "   [+] Visual vote representation" << endl;
    cout << endl;
    cout << " Built with: C++ (with Structs)" << endl;
    printLine('=', 60);
    
    pauseScreen();
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
    // Initialize election data using structs
    initializeElection();
    
    clearScreen();
    displayWelcome();
    
    cout << "Loading system data..." << endl;
    loadVotesFromFile();
    loadVotersFromFile();
    
    pauseScreen();
    
    bool running = true;
    
    while (running) {
        clearScreen();
        displayMainMenu();
        
        int option = getValidInput(1, 7);
        
        switch (option) {
            case 1:
                clearScreen();
                displayAreas();
                pauseScreen();
                break;
                
            case 2:
                clearScreen();
                displayAreas();
                cout << "Select constituency: ";
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
                displayAbout();
                break;
                
            case 7:
                clearScreen();
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