const fetchResults = async () => {
    const sort = document.getElementById('sort').value;
    const response = await fetch(`/api/rankings?${sort}`);
    const data = await response.json();
    document.getElementById('results').innerHTML = JSON.stringify(data, null, 2);
}