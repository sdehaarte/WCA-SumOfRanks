const express = require('express');
const { exec } = require('node:child_process');
const path = require('path');
const fs = require('fs').promises

const app = express();
app.use(express.static('../public'));
const port = 3000;

const buildPath = path.join(__dirname, '..', 'src', 'build');
process.chdir(buildPath);
const wcaSorPath = path.join(buildPath, 'WCA-SumOfRanks');
const ranksFilePath = path.join(__dirname, '..', 'src', 'output', 'ranks.json');
const compareFilePath = path.join(__dirname, '..', 'src', 'output', 'compare.json');

app.get('/api/rankings', async (req, res) => {
  const sort = req.query.sort || 'merge';
  try {
    const { stderr: execError } = await new Promise((resolve, reject) => {
      const cmd = `"${wcaSorPath}" --mode sort --sort ${sort}`;
      console.log("Running command: ", cmd);
      exec(cmd, (error, stdout, stderr) => {
        if (error) {
          reject({ error, stderr });
          return;
        }
        resolve({ stdout, stderr });
      });
    });
    if (execError) {
      console.error("Execution error: ", error);
      return res.status(500).send(stderr);
    }
    const ranksJSON = await fs.readFile(ranksFilePath, 'utf-8');
    const ranks = JSON.parse(ranksJSON);
    res.json(ranks);
  } catch (e) {
    console.error("Execution failed:", e.error);
    return res.status(500).send(e.stderr);
  }
});

app.get('/api/performance', async (req, res) => {
  try {
    const { stderr: execError } = await new Promise((resolve, reject) => {
      const cmd = `"${wcaSorPath}" --mode compare`;
      console.log("Running command: ", cmd);
      exec(cmd, (error, stdout, stderr) => {
        if (error) {
          reject({ error, stderr });
          return;
        }
        resolve({ stdout, stderr });
      });
    });
    if (execError) {
      console.error("Execution error: ", error);
      return res.status(500).send(stderr);
    }
    const compareJSON = await fs.readFile(compareFilePath, 'utf-8');
    const compare = JSON.parse(compareJSON);
    res.json(compare);
  } catch (e) {
    console.error("Execution failed:", e.error);
    return res.status(500).send(e.stderr);
  }
});

const server = app.listen(port, () => {
  console.log(`Running on: http://localhost:${port}`);
});

process.on('SIGTERM', () => {
  server.close(() => {
    console.log('Server closed');
    process.exit(0);
  });
});

process.on('SIGINT', () => {
  server.close(() => {
    console.log('Server closed');
    process.exit(0);
  });
});