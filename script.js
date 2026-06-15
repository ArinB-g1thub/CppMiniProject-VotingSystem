// State management
let votes = {};
let voters = [];
let currentVoter = {
    voterId: '',
    constituency: '',
    candidate: ''
};

// Initialize votes structure
function initializeVotes() {
    electionData.constituencies.forEach(constituency => {
        votes[constituency.id] = {};
        constituency.candidates.forEach(candidate => {
            votes[constituency.id][candidate.name] = 0;
        });
    });
    loadFromLocalStorage();
}

// Page navigation
function goToPage(pageId) {
    document.querySelectorAll('.page').forEach(page => {
        page.classList.remove('active');
    });
    document.getElementById(pageId).classList.add('active');
}

// Start voting process
function startVoting() {
    // Check if already voted
    const voterId = prompt('Quick check: Have you registered your voter ID before? (Enter your voter ID to check, or press Cancel to continue)');
    if (voterId) {
        if (voters.includes(voterId)) {
            alert('✗ You have already voted! Each citizen can only vote once.');
            return;
        }
    }
    
    // Clear previous data
    currentVoter = { voterId: '', constituency: '', candidate: '' };
    document.getElementById('voterId').value = '';
    document.getElementById('constituencySelect').value = '';
    document.getElementById('voterError').textContent = '';
    document.getElementById('constituencyError').textContent = '';
    
    // Populate constituency dropdown
    const select = document.getElementById('constituencySelect');
    select.innerHTML = '<option value="">-- Choose --</option>';
    electionData.constituencies.forEach(constituency => {
        const option = document.createElement('option');
        option.value = constituency.id;
        option.textContent = constituency.name;
        select.appendChild(option);
    });
    
    goToPage('voterRegPage');
}

// Verify voter
function verifyVoter() {
    const voterId = document.getElementById('voterId').value.trim();
    const constituencyId = document.getElementById('constituencySelect').value;
    
    let isValid = true;
    
    if (voterId.length < 5) {
        document.getElementById('voterError').textContent = '✗ Voter ID must be at least 5 characters';
        isValid = false;
    } else {
        document.getElementById('voterError').textContent = '';
    }
    
    if (!constituencyId) {
        document.getElementById('constituencyError').textContent = '✗ Please select a constituency';
        isValid = false;
    } else {
        document.getElementById('constituencyError').textContent = '';
    }
    
    if (voters.includes(voterId)) {
        document.getElementById('voterError').textContent = '✗ You have already voted!';
        isValid = false;
    }
    
    if (!isValid) return;
    
    // Save current voter data
    currentVoter.voterId = voterId;
    currentVoter.constituency = constituencyId;
    
    // Show candidates for selected constituency
    const constituency = electionData.constituencies.find(c => c.id == constituencyId);
    document.getElementById('candidateTitle').textContent = `Select Your Candidate - ${constituency.name}`;
    document.getElementById('candidateSubtitle').textContent = 'Choose your preferred candidate';
    
    const container = document.getElementById('candidatesContainer');
    container.innerHTML = '';
    
    constituency.candidates.forEach(candidate => {
        const card = document.createElement('div');
        card.className = 'candidate-card';
        card.innerHTML = `
            <div class="candidate-name">${candidate.name}</div>
            <div class="candidate-party">🏛️ ${candidate.party}</div>
        `;
        card.onclick = () => selectCandidate(candidate.name, candidate.party, card);
        container.appendChild(card);
    });
    
    goToPage('candidatePage');
}

// Select candidate
function selectCandidate(candidateName, party, cardElement) {
    // Remove previous selection
    document.querySelectorAll('.candidate-card').forEach(card => {
        card.classList.remove('selected');
    });
    
    // Mark new selection
    cardElement.classList.add('selected');
    currentVoter.candidate = candidateName;
    currentVoter.party = party;
    
    // Auto proceed to confirmation
    setTimeout(() => {
        showConfirmation();
    }, 300);
}

// Show confirmation
function showConfirmation() {
    const constituency = electionData.constituencies.find(c => c.id == currentVoter.constituency);
    
    document.getElementById('confirmVoterId').textContent = currentVoter.voterId;
    document.getElementById('confirmConstituency').textContent = constituency.name;
    document.getElementById('confirmCandidate').textContent = currentVoter.candidate;
    document.getElementById('confirmParty').textContent = currentVoter.party;
    
    goToPage('confirmPage');
}

// Submit vote
function submitVote() {
    // Record vote
    const constituencyId = currentVoter.constituency;
    const candidateName = currentVoter.candidate;
    
    votes[constituencyId][candidateName]++;
    voters.push(currentVoter.voterId);
    
    // Save to localStorage
    saveToLocalStorage();
    
    // Show success
    goToPage('successPage');
}

// View results - FIXED: Now actually calculates and displays votes
function viewResults() {
    const resultsContainer = document.getElementById('resultsContainer');
    resultsContainer.innerHTML = '';
    
    let totalVotes = 0;
    
    electionData.constituencies.forEach(constituency => {
        const constituencyVotes = votes[constituency.id];
        let maxVotes = Math.max(...Object.values(constituencyVotes));
        
        const resultDiv = document.createElement('div');
        resultDiv.className = 'constituency-result';
        
        let html = `<h3>${constituency.name}</h3>`;
        
        constituency.candidates.forEach(candidate => {
            const voteCount = constituencyVotes[candidate.name] || 0;
            totalVotes += voteCount;
            const percentage = maxVotes > 0 ? ((voteCount / maxVotes) * 100) : 0;
            
            html += `
                <div class="vote-bar">
                    <div class="vote-label">
                        <span>${candidate.name} (${candidate.party})</span>
                        <span>${voteCount} votes</span>
                    </div>
                    <div class="bar">
                        <div class="bar-fill" style="width: ${percentage}%"></div>
                    </div>
                </div>
            `;
        });
        
        resultDiv.innerHTML = html;
        resultsContainer.appendChild(resultDiv);
    });
    
    document.getElementById('totalVotes').textContent = totalVotes;
    document.getElementById('totalVoters').textContent = voters.length;
    
    goToPage('resultsPage');
}

// Admin login
function adminLogin() {
    const password = document.getElementById('adminPassword').value;
    
    if (password === electionData.adminPassword) {
        document.getElementById('adminError').textContent = '';
        document.getElementById('adminPassword').value = '';
        showAdminDashboard();
    } else {
        document.getElementById('adminError').textContent = '✗ Incorrect password';
    }
}

// Show admin dashboard
function showAdminDashboard() {
    const statsContainer = document.getElementById('adminStatsContainer');
    
    let totalVotes = 0;
    let mostActiveConstituency = '';
    let mostActiveVotes = 0;
    
    electionData.constituencies.forEach(constituency => {
        const constituencyTotal = Object.values(votes[constituency.id]).reduce((a, b) => a + b, 0);
        totalVotes += constituencyTotal;
        
        if (constituencyTotal > mostActiveVotes) {
            mostActiveVotes = constituencyTotal;
            mostActiveConstituency = constituency.name;
        }
    });
    
    const avgVotes = electionData.constituencies.length > 0 ? (totalVotes / electionData.constituencies.length).toFixed(1) : 0;
    
    statsContainer.innerHTML = `
        <p><strong>📊 Total Votes Cast:</strong> ${totalVotes}</p>
        <p><strong>👥 Registered Voters:</strong> ${voters.length}</p>
        <p><strong>🏆 Most Active Constituency:</strong> ${mostActiveConstituency || 'N/A'} (${mostActiveVotes} votes)</p>
        <p><strong>📈 Average Votes per Constituency:</strong> ${avgVotes}</p>
        <p><strong>🗳️ Total Constituencies:</strong> ${electionData.constituencies.length}</p>
        <p><strong>👨‍⚖️ Total Candidates:</strong> ${electionData.constituencies.length * 4}</p>
    `;
    
    goToPage('adminDashboard');
}

// Reset all data
function resetAllData() {
    const confirm = prompt('Type "RESET" to confirm resetting all data:');
    if (confirm === 'RESET') {
        votes = {};
        voters = [];
        initializeVotes();
        alert('✓ All data has been reset!');
        goToPage('welcomePage');
    }
}

// Export data as JSON
function exportData() {
    const dataToExport = {
        timestamp: new Date().toLocaleString(),
        totalVotes: Object.values(votes).reduce((sum, constituency) => 
            sum + Object.values(constituency).reduce((a, b) => a + b, 0), 0),
        totalVoters: voters.length,
        votes: votes,
        voterCount: voters.length
    };
    
    const dataStr = JSON.stringify(dataToExport, null, 2);
    const dataBlob = new Blob([dataStr], { type: 'application/json' });
    const url = URL.createObjectURL(dataBlob);
    const link = document.createElement('a');
    link.href = url;
    link.download = `election-data-${Date.now()}.json`;
    link.click();
    
    alert('✓ Data exported successfully!');
}

// LocalStorage functions
function saveToLocalStorage() {
    localStorage.setItem('votingSystemVotes', JSON.stringify(votes));
    localStorage.setItem('votingSystemVoters', JSON.stringify(voters));
}

function loadFromLocalStorage() {
    const savedVotes = localStorage.getItem('votingSystemVotes');
    const savedVoters = localStorage.getItem('votingSystemVoters');
    
    if (savedVotes) votes = JSON.parse(savedVotes);
    if (savedVoters) voters = JSON.parse(savedVoters);
}

// Initialize on page load
window.addEventListener('DOMContentLoaded', () => {
    initializeVotes();
    goToPage('welcomePage');
});