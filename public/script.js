const ranksPerPage = 10;
let currentPage = 1;
let rankingsData = [];

const fetchResults = async () => {
    const sort = document.getElementById('sort').value;
    const topN = document.getElementById('topN').value;
    const response = await fetch(`/api/rankings?sort=${sort}&topN=${topN}`);
    const data = await response.json();
    rankingsData = data;
    currentPage = 1;
    displayRankingsPage(1);
}

const fetchPerformance = async () => {
    const performanceDiv = document.getElementById('performance')
    const response = await fetch('/api/performance');
    const data = await response.json();
    performanceDiv.innerHTML = '';

    const msRow = document.createElement('tr');
    msRow.innerHTML = `
        <td>MergeSort Time</td>
        <td>${data.mergeSort} seconds</td>`;

    const qsRow = document.createElement('tr');
    qsRow.innerHTML = `
        <td>QuickSort Time</td>
        <td>${data.quickSort} seconds</td>`;

    let message = "";
    let percentFaster = 0;
    if (data.mergeSort < data.quickSort) {
        message = "MergeSort was faster than QuickSort by ";
        percentFaster = ((data.quickSort - data.mergeSort) / data.mergeSort) * 100;
    } else {
        message = "QuickSort was faster than MergeSort by ";
        percentFaster = ((data.mergeSort - data.quickSort) / data.quickSort) * 100;
    }
    const fasterRow = document.createElement('tr');
    fasterRow.innerHTML = `
        <td>${message}</td>
        <td>${percentFaster.toFixed(2)}%</td>`;
    
    performanceDiv.appendChild(msRow);
    performanceDiv.appendChild(qsRow);
    performanceDiv.appendChild(fasterRow);

}

function displayRankingsPage(page) {
    const rankingsDiv = document.getElementById('rankings');
    const pageSelectorDiv = document.getElementById('pageSelector');

    if (!rankingsDiv) {
        console.error("Results not found");
        return;
    }
    rankingsDiv.innerHTML = '';
    const currentPageRankings = rankingsData.ranks.slice((currentPage - 1) * ranksPerPage, currentPage * ranksPerPage)

    const table = document.createElement('table');
    table.classList.add('rankings-table');

    if (rankingsDiv.querySelector('table') === null) {
        const headers = ['Rank', 'Name', 'WCA ID', 'Sum of Ranks'];
        const thead = document.createElement('thead'); 
        const headerRow = document.createElement('tr');
        headers.forEach(header => {
            const th = document.createElement('th');
            th.textContent = header;
            headerRow.appendChild(th);
        });
        thead.appendChild(headerRow);
        table.appendChild(thead);
        rankingsDiv.appendChild(table);
    }

    const keys = ['rank', 'name', 'wcaId', 'sumOfRanks']
    const tbody = document.createElement('tbody');
    currentPageRankings.forEach(cuber => {
        const row = document.createElement('tr');
        keys.forEach(key => {
            const td = document.createElement('td');
            td.textContent = cuber[key];
            row.appendChild(td);
        });
        tbody.appendChild(row);
    });
    table.appendChild(tbody);
    rankingsDiv.replaceChild(table, rankingsDiv.querySelector('table'));

    if (rankingsDiv.innerHTML.trim() !== '') {
        pageSelectorDiv.style.display = 'block';
    }
}

function goToRankingsPage() {
    const selectElement = document.getElementById("rankingsPageNumber");
    const selectedPage = parseInt(selectElement.value);
    if (!isNaN(selectedPage) && selectedPage >= 1) {
      currentPage = selectedPage;
      displayRankingsPage(currentPage);
    }
}


const searchIdInput = document.querySelector('.search-container input[type="text"]');
searchIdInput.addEventListener('input', handleSearch);

function handleSearch(event) {
    const searchId = event.target.value.trim().toLowerCase();
    const rankingsDiv = document.getElementById('rankings');
    pageSelectorDiv = document.getElementById('pageSelector');
    rankingsDiv.innerHTML = '';
    pageSelectorDiv.style.display = 'none';
    if (searchId === '') {
        currentPage = 1;
        displayRankingsPage(1);
        return;
    }
    const foundCuber = rankingsData.ranks.find(cuber => cuber.wcaId.toLowerCase().includes(searchId));
    if (foundCuber) {
        const table = document.createElement('table');
        table.classList.add('rankings-table');
        const headers = ['Rank', 'Name', 'WCA ID', 'Sum of Ranks'];
        const thead = document.createElement('thead'); 
        const headerRow = document.createElement('tr');
        headers.forEach(header => {
            const th = document.createElement('th');
            th.textContent = header;
            headerRow.appendChild(th);
        });
        thead.appendChild(headerRow);
        table.appendChild(thead);
        rankings.appendChild(table);

        const keys = ['rank', 'name', 'wcaId', 'sumOfRanks']
        const tbody = document.createElement('tbody');
        const row = document.createElement('tr');
        keys.forEach(key => {
            const td = document.createElement('td');
            td.textContent = foundCuber[key];
            row.appendChild(td);
        });
        tbody.appendChild(row);
        table.appendChild(tbody);
        rankingsDiv.appendChild(table);
    }
}

