# 🧠 Intelligence for Dummies

**A feature-rich, console-based quiz game built in C++**

What started as a simple quiz app for a semester project grew into a full game system — timed questions, lifelines, streak bonuses, and a persistent high-score leaderboard, all built with core C++ and no external libraries.

`C++` `Console Application` `Visual Studio`

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Concepts Demonstrated](#concepts-demonstrated)
- [Built With](#built-with)
- [How to Run](#how-to-run)
- [How to Play](#how-to-play)
- [Project Structure](#project-structure)
- [What This Project Taught Us](#what-this-project-taught-us)
- [Team](#team)

## Overview

Intelligence for Dummies is a console-based quiz game built as a semester project for Programming Fundamentals Lab. Players pick a category and difficulty, then race against a 10-second countdown to answer 10 questions — wrong answers cost points scaled by difficulty, correct streaks earn bonus points, and four lifelines are available when things get tough. Scores are saved to a persistent leaderboard, and players can review exactly which questions they missed at the end of each round.

The project was built entirely with core C++ — no external libraries — as practice for structs, file I/O, arrays, and modular function design.

## Features

**Gameplay**
- 5 categories — Science, Computer, Sports, History, IQ/Logic
- 3 difficulty levels — Easy, Medium, Hard — each with a different wrong-answer penalty (−2 / −3 / −5)
- 10-second countdown timer per question, with a time-out penalty if you don't answer in time
- 4 lifelines, each usable once per game — 50-50, Skip, Replace Question, +10 Seconds
- Streak bonuses — +5 points at a 3-answer streak, +15 points at a 5-answer streak
- Randomized question order via a Fisher-Yates shuffle, so no two playthroughs feel the same
- Robust input validation — invalid input is re-prompted, never crashes the game

**Persistence & Review**
- Persistent high-score leaderboard, saved to file, top 5 scores shown on request
- Detailed session logging — every quiz run is logged with full stats for later review
- Post-quiz review screen — see exactly which questions you got wrong and what the correct answers were

## Concepts Demonstrated

| Concept | Where It Lives | What It Looks Like |
|---|---|---|
| **Structs** | `struct Player`, `struct Question` | Bundling related state (score, streak, lifelines) into one unit |
| **File I/O** | Question loading, leaderboard, and session logs | `fstream` reads category files, writes `high_scores.txt` and `quiz_logs.txt` |
| **Arrays** | Question pools per category, lifeline tracking | Fixed-size storage for loaded questions and used lifelines |
| **Modular Function Design** | Quiz flow split into distinct functions (load, ask, score, save) | Each function has a single, clear responsibility |
| **String Manipulation** | Parsing question files, formatting leaderboard output | Splitting raw file lines into question/answer/options |
| **Timing** | Per-question 10-second countdown | Time-based logic without any external timing library |
| **Input Validation** | Every menu and answer prompt | Re-prompts on invalid input instead of crashing |

## Built With

- **Language:** C++
- **Core techniques:** Structs, File I/O (`fstream`), arrays, string manipulation, timing, modular function design
- **IDE:** Visual Studio

## How to Run

1. Clone or download this repository
2. Make sure the question files (`science.txt`, `computer.txt`, `sports.txt`, `history.txt`, `iq.txt`) are in the same directory as the executable
3. Compile `quizgame.cpp` with any C++ compiler:
   ```
   g++ quizgame.cpp -o quizgame
   ./quizgame
   ```
   Or open and build it directly in Visual Studio.
4. Follow the on-screen menu to start a quiz or view the leaderboard

> **Note:** This project was built and tested on Windows (uses `system("cls")` and `localtime_s`). To run on Linux/macOS, swap `system("cls")` for `system("clear")`, and `localtime_s` for the thread-safe `localtime_r` equivalent.

## How to Play

1. Choose a category — Science, Computer, Sports, History, or IQ/Logic
2. Choose a difficulty — Easy, Medium, or Hard (affects wrong-answer penalty)
3. Answer 10 questions, each with a 10-second timer
4. Use lifelines (50-50, Skip, Replace Question, +10 Seconds) when you need help — each works only once per game
5. Build streaks of correct answers for bonus points
6. Review your missed questions and see your final score
7. Check the leaderboard to see how you rank against previous games

## Project Structure

```
Intelligence-for-dummies/
│
├── 📜 quizgame.cpp         # Main program source code
│
├── 📄 science.txt           # Science category questions
├── 📄 computer.txt          # Computer category questions
├── 📄 sports.txt            # Sports category questions
├── 📄 history.txt           # History category questions
├── 📄 iq.txt                # IQ/Logic category questions
│
├── 📄 high_scores.txt       # Generated leaderboard (created on first run)
├── 📄 quiz_logs.txt         # Generated session logs (created on first run)
│
└── 📜 README.md
```

## What This Project Taught Us

This was our first real C++ project beyond classroom exercises. It pushed us to think about program structure and state management (via `struct Player` and `struct Question`), practice file-based persistence, and handle edge cases like invalid input, timers, and empty leaderboards gracefully. It's rough around the edges in places, but it's ours — built from scratch in our first semester.

## Team

Built as a group project for Programming Fundamentals Lab (BSCS-1A):
- Merub Awan
- Kiran Shahid
- M. Ehsan Danish
