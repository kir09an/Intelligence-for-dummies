# Intelligence-for-dummies

A feature-rich, console-based quiz game built in C++ as a semester project for Programming Fundamentals Lab. What started as a simple quiz app grew into a full game system — timed questions, lifelines, streak bonuses, and a persistent high-score leaderboard.


📋 Overview

Players pick a category and a difficulty level, then race against a 10-second countdown to answer 10 questions. Wrong answers cost points (scaled by difficulty), correct streaks earn bonus points, and four lifelines are available to help out when things get tough. Scores are saved to a leaderboard, and players can review the questions they missed at the end of each round.

Built entirely with core C++ — no external libraries — to practice structures, file I/O, arrays, and modular function design.


✨ Features


5 Categories — Science, Computer, Sports, History, IQ/Logic
3 Difficulty Levels — Easy, Medium, Hard (each with a different wrong-answer penalty: -2 / -3 / -5)
10-second countdown timer per question, with a time-out penalty if you don't answer in time
4 Lifelines — 50-50, Skip, Replace Question, +10 Seconds (each usable once per game)
Streak bonuses — +5 points at a 3-streak, +15 points at a 5-streak
Persistent high-score leaderboard — saved to file, top 5 scores shown on request
Detailed session logging — every quiz run is logged with full stats for review
Post-quiz review — see exactly which questions you got wrong and what the correct answers were
Randomized question order — Fisher-Yates shuffle so no two playthroughs feel the same
Robust input validation — the game never crashes on bad input, it just asks again



🛠️ Built With


Language: C++
Concepts used: Structs, File I/O (fstream), arrays, string manipulation, <ctime> for timing, modular function design
IDE: Visual Studio



🚀 How to Run


Clone or download this repository
Make sure the question files (science.txt, computer.txt, sports.txt, history.txt, iq.txt) are in the same directory as the executable
Compile quizgame.cpp with any C++ compiler (Visual Studio, g++, etc.)


   g++ quizgame.cpp -o quizgame
   ./quizgame


Follow the on-screen menu to start a quiz or view the leaderboard



Note: This project was built and tested on Windows (uses system("cls") and localtime_s). To run on Linux/macOS, swap system("cls") for system("clear") and localtime_s for the thread-safe localtime_r equivalent.




📁 File Structure

quiz-game-cpp/
│
├── quizgame.cpp        # Main program source code
├── science.txt          # Science category questions
├── computer.txt         # Computer category questions
├── sports.txt            # Sports category questions
├── history.txt           # History category questions
├── iq.txt                    # IQ/Logic category questions
├── high_scores.txt    # Generated leaderboard (created on first run)
├── quiz_logs.txt         # Generated session logs (created on first run)
└── README.md


👥 Team

Built as a group project for Programming Fundamentals Lab (BSCS-1A):


Merub Awan
Kiran Shahid
M. Ehsan Danish



📚 What This Project Taught Us

This was our first real C++ project beyond classroom exercises — it pushed us to think about program structure and state management (via struct Player and struct Question), practice file-based persistence, and handle edge cases like invalid input, timers, and empty leaderboards gracefully. It's rough around the edges in places, but it's ours, built from scratch in our first semester.
