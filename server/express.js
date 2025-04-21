const express = require('express');
const { exec } = require('node:child_process');
const path = require('path');
const fs = require('fs').promises

const app = express();
const port = 3000;

const buildPath = path.join(__dirname, '..', 'src', 'build');
process.chdir(buildPath);
const wcaSorPath = path.join(buildPath, 'wca_sor');
const ranksFilePath = path.join(__dirname, '..', 'src', 'output', 'ranks.json');
const compareFilePath = path.join(__dirname, '..', 'src', 'output', 'compare.json');

app.use(express.static('../public'));

app.get('/api/rankings', (req, res) => {
  const sort = req.query.sort || 'merge';
  exec(`"${wcaSorPath}" --mode sort --sort ${sort}`, async (error, stderr) => {
    if (error) {
      console.error("Execution error: ", error);
      return res.status(500).send(stderr);
    }
    try {
      const ranksJSON = await fs.readFile(ranksFilePath, 'utf-8');
      const ranks = JSON.parse(ranksJSON);
      res.json(ranks);
    } catch (e) {
      console.error("Error reading ranks.json:", e);
      return res.status(500).send("Error reading ranks.json");
    }
  });
});

app.get('/api/performance', (req, res) => {
  exec(`"${wcaSorPath}" --mode compare`, async (error, stderr) => {
    if (error) {
      console.error("Execution error: ", error);
      return res.status(500).send(stderr);
    }
    try {
      const comparisonJSON = await fs.readFile(compareFilePath, 'utf-8');
      const comparison = JSON.parse(comparisonJSON);
      res.json(comparison);
    } catch (e) {
      console.error("Error reading comparison.json", e);
      return res.status(500).send("Error reading comparison.json");
    }
  });
});

app.listen(port, () => {
    console.log(`Running on: http://localhost:${port}`)
});