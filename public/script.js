const ranksPerPage = 10;
let currentPage = 1;
let rankingsData = [];

const fetchResults = async () => {
    const sort = document.getElementById('sort').value;
    const response = await fetch(`/api/rankings?sort=${sort}`);
    const data = await response.json();
    // document.getElementById('rankings').innerHTML = JSON.stringify(data, null, 2);
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
        <td>${data.mergeSort}</td>`;

    const qsRow = document.createElement('tr');
    qsRow.innerHTML = `
        <td>QuickSort Time</td>
        <td>${data.quickSort}</td>`;
        
    performanceDiv.appendChild(msRow);
    performanceDiv.appendChild(qsRow);
}


function displayRankingsPage(page) {
    const rankings = document.getElementById('rankings');
    if (!rankings) {
        console.error("Results not found");
        return;
    }
    rankings.innerHTML = '';
    const currentPageRankings = rankingsData.ranks.slice((currentPage - 1) * ranksPerPage, currentPage * ranksPerPage)

    const table = document.createElement('table');
    table.classList.add('rankings-table');

    if (rankings.querySelector('table') === null) {
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
    rankings.replaceChild(table, rankings.querySelector('table'));
}

function goToRankingsPage() {
    const selectElement = document.getElementById("rankingsPageNumber");
    const selectedPage = parseInt(selectElement.value);
    if (!isNaN(selectedPage) && selectedPage >= 1) {
      currentPage = selectedPage;
      displayRankingsPage(currentPage);
    }
  }