const express = require('express');
const { exec } = require('node:child_process');

const app = express();
const port = 3000;

app.use(express.static('../frontend'));
app.get('/api/rankings', (req, res) => {
  const sort = req.query.sort || 'merge';
  exec(`../src/build/wca_sor --mode sort --sort ${sort}`, (error, stdout, stderr) => {
    if (error) {
      console.error(`exec error: ${error}`);
      return res.status(500).send(stderr);
    }
    res.json(JSON.parse(stdout));
  });
});

app.listen(port, () => {
    console.log(`Running on: http://localhost:${port}`)
});