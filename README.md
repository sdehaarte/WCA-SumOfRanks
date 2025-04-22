# WCA-Sum-Of-Ranks

Project 3 for COP3530. This project seeks to create a metric for measuring the strength of competitive cubers while demonstrating use of two algorithms.

### Tools used
C++ / Express.js / Javascript / HTML / CSS 

## Clone the repository:
To get started, clone the repository to your local machine:
```bash
git clone https://github.com/sdehaarte/WCA-SumOfRanks/
cd WCA-SumOfRanks
```

## Instructions to Run Website Locally

1. Ensure [Node.js](https://nodejs.org/en/download) package manager is installed.
3. Run `cd server` to enter server directory
4. Run `npm i` to install packages.
5. Run `node express.js` to start the server.
6. The application should now be running at `http://localhost:3000`.

## Instructions to Build C++ Backend (not necessary)
1. Run `cd src` from the root to enter src directory
2. Ensure `g++` and `cmake` are installed
3. To create build files run:
```bash
cmake --build ./build --config Debug --target all -j 10 --
```
4. Finally, run `./build/WCA-SumOfRanks`.
