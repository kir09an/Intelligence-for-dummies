
/*
======================================================
Project: Intelligence for Dummies - Quiz Game
Course: Programming Fundamentals Lab
Section: BSCS-1A
Group Members:
    Merub Awan (25F-0534)
    Kiran Shahid (25F-0601)
    M. Ehsan Danish (25F-0754)
Submission Date: December 09, 2025

DESCRIPTION:
This program is an interactive quiz game with multiple features:
1. Multiple categories (Science, Computer, Sports, History, IQ/Logic)
2. Three difficulty levels (Easy, Medium, Hard)
3. Four lifelines (50-50, Skip, Replace, +10 seconds)
4. Timer-based questions with penalties
5. Score tracking with streak bonuses
6. High score leaderboard
7. Review of incorrect answers
8. Detailed logging system

FEATURES IMPLEMENTED:
- File I/O for questions and scores
- Time management with countdown timer
- Input validation
- Random question shuffling
- Score calculation with penalties
- Game state management
======================================================
*/


#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <limits>
using namespace std;

// ======================================================
// GLOBAL CONSTANTS
// ======================================================
const int MAX_QUESTIONS = 100;  // Maximum number of questions that can be loaded

// ======================================================
// STRUCTURE: Question
// PURPOSE: Stores a single quiz question with all details
// MEMBERS:
//   question - The question text
//   options[4] - Array of 4 answer choices
//   correct - Index (1-4) of correct answer
//   difficulty - Difficulty level (Easy/Medium/Hard)
// ======================================================
struct Question {
    string question;
    string options[4];
    int correct;
    string difficulty;
};

// ======================================================
// STRUCTURE: Player
// PURPOSE: Tracks player's game statistics and progress
// MEMBERS:
//   name - Player's name
//   score - Current score
//   correct - Number of correct answers
//   wrong - Number of wrong answers
//   life_50, life_skip, life_replace, life_time - Lifeline status
//   streak - Consecutive correct answers
//   category, difficulty - Game settings
//   wrongQuestions[10] - Stores indices of wrong answers
//   wrongCount - Number of wrong answers
// ======================================================
struct Player {
    string name;
    int score;
    int correct;
    int wrong;
    bool life_50;
    bool life_skip;
    bool life_replace;
    bool life_time;
    int streak;
    string category;
    string difficulty;
    int wrongQuestions[10];
    int wrongCount;
};

// ======================================================
// GLOBAL VARIABLES
// ======================================================
Question questions[MAX_QUESTIONS];  // Array to store loaded questions
int totalQuestions = 0;             // Actual number of questions loaded

// ======================================================
// FUNCTION PROTOTYPES
// ======================================================
string getCurrentDateTime();
void clearScreen();
void pressEnterToContinue();
void loadQuestions(string filename, string difficulty);
void startQuiz();
void viewHighScores();
void saveHighScore(Player& player);
void saveQuizLog(Player& player);
void displayQuestion(Question& q, int qNum, int timeLeft, Player& player);
void shuffleQuestions();
int getValidInput(int min, int max);
void use5050(Question& q, Player& player);
void selectCategory(string& filename, string& categoryName);
void selectDifficulty(string& diff);
void reviewIncorrectAnswers(Player& player);
void playAgainPrompt();

// ======================================================
// FUNCTION: main
// PURPOSE: Entry point of the program, displays main menu
// FLOW:
//   1. Seeds random number generator
//   2. Displays main menu in a loop
//   3. Calls appropriate functions based on user choice
//   4. Exits when user selects option 3
// ======================================================
int main() {
    // Seed random number generator for shuffling questions
    srand(static_cast<unsigned int>(time(0)));
    int choice;

    // Main program loop
    while (true) {
        clearScreen();
        cout << ".............................................._." << endl;
        cout << "    Welcome To Intelligence for Dummies! :D    " << endl;
        cout << ".............................................._." << endl;
        cout << "  1. Start New Quiz (Ready to impress us?)" << endl;
        cout << "  2. View High Scores (See the legends!)" << endl;
        cout << "  3. Exit Game (Already giving up? :P)" << endl;
        cout << "What's your move, genius?: ";

        choice = getValidInput(1, 3);

        // Handle menu choice
        switch (choice) {
        case 1:
            startQuiz();
            break;
        case 2:
            viewHighScores();
            break;
        case 3:
            cout << "................................................_." << endl;
            cout << "   Hope your brain cells multiplied today! :)" << endl;
            cout << "        Thanks for playing, champ!" << endl;
            cout << "................................................_." << endl << endl;
            return 0;
        }
    }
    return 0;
}

// ======================================================
// FUNCTION: clearScreen
// PURPOSE: Clears the console screen for better user interface
// NOTE: Uses system("cls") which is Windows-specific
// ======================================================
void clearScreen() {
    system("cls");
}

// ======================================================
// FUNCTION: pressEnterToContinue
// PURPOSE: Pauses program execution until user presses Enter
// CLEARS: Input buffer to prevent leftover characters
// ======================================================
void pressEnterToContinue() {
    cout << "Press Enter to continue";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// ======================================================
// FUNCTION: getValidInput
// PURPOSE: Validates and returns user input within specified range
// PARAMETERS:
//   min - Minimum acceptable integer value
//   max - Maximum acceptable integer value
// RETURNS: Valid integer between min and max
// ERROR HANDLING: Re-prompts user for valid input on invalid entry
// ======================================================
int getValidInput(int min, int max) {
    int input;
    while (true) {
        cin >> input;

        // Check if input is valid
        if (cin.fail() || input < min || input > max) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Hmm, that doesn't work. Try a number between " << min << " and " << max << ": ";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return input;
        }
    }
}

// ======================================================
// FUNCTION: selectCategory
// PURPOSE: Displays category menu and sets selected category
// PARAMETERS:
//   filename - Reference to store selected filename
//   categoryName - Reference to store category display name
// DISPLAYS: Menu of 5 categories with descriptions
// ======================================================
void selectCategory(string& filename, string& categoryName) {
    clearScreen();

    cout << "..............................................._." << endl;
    cout << "    PICK YOUR BATTLEGROUND (Category Time!)" << endl;
    cout << "..............................................._." << endl << endl;
    cout << "  1.  Science (For the curious nerds!)" << endl;
    cout << "  2.  Computer (Beep boop! Tech time!)" << endl;
    cout << "  3.  Sports (Athletic geniuses only!)" << endl;
    cout << "  4.  History (Time travelers welcome!)" << endl;
    cout << "  5.  IQ/Logic (Big brain stuff!)" << endl;
    cout << "Choose your destiny (1-5): ";

    int choice = getValidInput(1, 5);

    // Map choice to actual filename and category name
    switch (choice) {
    case 1:
        filename = "science.txt";
        categoryName = "Science";
        break;
    case 2:
        filename = "computer.txt";
        categoryName = "Computer";
        break;
    case 3:
        filename = "sports.txt";
        categoryName = "Sports";
        break;
    case 4:
        filename = "history.txt";
        categoryName = "History";
        break;
    case 5:
        filename = "iq.txt";
        categoryName = "IQ/Logic";
        break;
    }
}

// ======================================================
// FUNCTION: selectDifficulty
// PURPOSE: Displays difficulty menu and sets selected difficulty
// PARAMETERS:
//   diff - Reference to store selected difficulty level
// DISPLAYS: Menu of 3 difficulty levels with penalty information
// ======================================================
void selectDifficulty(string& diff) {
    clearScreen();

    cout << "............................................_." << endl;
    cout << "    HOW BRAVE ARE YOU? (Difficulty Time!)" << endl;
    cout << "............................................_." << endl << endl;
    cout << "  1.  Easy   (Nice and chill, -2 for mistakes)" << endl;
    cout << "  2.  Medium (Getting spicy! -3 penalty)" << endl;
    cout << "  3.  Hard   (Only for the fearless! -5 ouch!)" << endl;
    cout << "How tough do ya want it? (1-3): ";

    int choice = getValidInput(1, 3);

    // Set difficulty based on choice
    switch (choice) {
    case 1:
        diff = "Easy";
        break;
    case 2:
        diff = "Medium";
        break;
    case 3:
        diff = "Hard";
        break;
    }
}

// ======================================================
// FUNCTION: loadQuestions
// PURPOSE: Loads questions from file, filtering by difficulty
// PARAMETERS:
//   filename - Name of the question file to load
//   difficulty - Difficulty level to filter questions
// FILE FORMAT: Each question block contains:
//   1. Question text
//   2. 4 answer options
//   3. Correct answer number
//   4. Difficulty level
//   5. Blank line separator
// ======================================================
void loadQuestions(string filename, string difficulty) {
    ifstream file(filename);
    totalQuestions = 0;
    string line;

    // Read file line by line
    while (getline(file, line) && totalQuestions < MAX_QUESTIONS) {
        if (line.empty()) continue;  // Skip empty lines

        Question tempQ;
        tempQ.question = line;

        // Read the 4 answer options
        for (int i = 0; i < 4; i++) {
            getline(file, tempQ.options[i]);
        }

        // Read correct answer and difficulty
        getline(file, line);
        tempQ.correct = stoi(line);
        getline(file, tempQ.difficulty);

        // Clean up whitespace from difficulty string
        tempQ.difficulty.erase(0, tempQ.difficulty.find_first_not_of(" \t\r\n"));
        tempQ.difficulty.erase(tempQ.difficulty.find_last_not_of(" \t\r\n") + 1);

        // Only add questions that match the selected difficulty
        if (tempQ.difficulty == difficulty) {
            questions[totalQuestions] = tempQ;
            totalQuestions++;
        }

        getline(file, line);  // Skip the blank line between questions
    }

    file.close();
}

// ======================================================
// FUNCTION: shuffleQuestions
// PURPOSE: Randomly shuffles the questions array
// ALGORITHM: Fisher-Yates shuffle algorithm
// PROCESS: Iterates through array, swapping each element with random element
// ======================================================
void shuffleQuestions() {
    for (int i = totalQuestions - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Question temp = questions[i];
        questions[i] = questions[j];
        questions[j] = temp;
    }
}

// ======================================================
// FUNCTION: displayQuestion
// PURPOSE: Shows a question with all game info (score, time, lifelines)
// PARAMETERS:
//   q - Reference to the current question
//   qNum - Current question number (1-10)
//   timeLeft - Time remaining in seconds
//   player - Reference to player's current stats
// DISPLAYS: Question, options, score, timer, and lifelines
// ======================================================
void displayQuestion(Question& q, int qNum, int timeLeft, Player& player) {
    clearScreen();

    // Header with game stats
    cout << "......................._." << endl;
    cout << "Question: " << qNum << "/10" << endl;
    cout << "Score: " << player.score << endl;
    cout << "Time: " << timeLeft << "s" << endl;
    cout << "......................._." << endl << endl;

    // Player stats
    cout << "Streak: " << player.streak << endl;
    cout << "Correct: " << player.correct << endl;
    cout << "Wrong: " << player.wrong << endl;

    // The actual question
    cout << " " << q.question << endl << endl;

    // Display answer options
    for (int i = 0; i < 4; i++) {
        cout << "  " << (i + 1) << ". " << q.options[i] << endl;
    }

    // Footer with available lifelines
    cout << "......................._." << endl;
    cout << " LIFELINES: ";
    if (player.life_50) cout << "[5] 50-50   ";
    if (player.life_skip) cout << "[6] Skip   ";
    if (player.life_replace) cout << "[7] Replace   ";
    if (player.life_time) cout << "[8] +10s   ";
    cout << endl;
    cout << "......................._." << endl;
}

// ======================================================
// FUNCTION: use5050
// PURPOSE: Implements 50-50 lifeline by removing two wrong answers
// PARAMETERS:
//   q - Reference to current question (modified in-place)
//   player - Reference to player (lifeline status updated)
// PROCESS:
//   1. Checks if lifeline is available
//   2. Finds indices of wrong answers
//   3. Randomly removes 2 wrong options
//   4. Marks lifeline as used
// ======================================================
void use5050(Question& q, Player& player) {
    if (!player.life_50) {
        cout << "You already used this one, smarty! ;)" << endl;
        return;
    }

    player.life_50 = false;  // Mark lifeline as used

    // Find indices of wrong answers
    int wrongIndices[3];
    int wrongCount = 0;

    for (int i = 0; i < 4; i++) {
        if (i + 1 != q.correct) {
            wrongIndices[wrongCount] = i;
            wrongCount++;
        }
    }

    // Remove 2 wrong options
    int removedCount = 0;
    while (removedCount < 2 && wrongCount > 0) {
        int randomIndex = rand() % wrongCount;
        int optionToRemove = wrongIndices[randomIndex];
        q.options[optionToRemove] = " [REMOVED]";

        // Shift remaining indices
        for (int i = randomIndex; i < wrongCount - 1; i++) {
            wrongIndices[i] = wrongIndices[i + 1];
        }
        wrongCount--;
        removedCount++;
    }

    cout << "50-50 activated! Poof! Two wrong answers gone! :D" << endl;
}

// ======================================================
// FUNCTION: getCurrentDateTime
// PURPOSE: Gets current date and time as formatted string
// FORMAT: YYYY-MM-DD HH:MM:SS
// RETURNS: String containing current date and time
// ======================================================
string getCurrentDateTime() {
    time_t now = time(0);
    struct tm timeinfo;
    localtime_s(&timeinfo, &now);

    stringstream ss;
    ss << (timeinfo.tm_year + 1900) << "-"
        << setfill('0') << setw(2) << (timeinfo.tm_mon + 1) << "-"
        << setfill('0') << setw(2) << timeinfo.tm_mday << " "
        << setfill('0') << setw(2) << timeinfo.tm_hour << ":"
        << setfill('0') << setw(2) << timeinfo.tm_min << ":"
        << setfill('0') << setw(2) << timeinfo.tm_sec;

    return ss.str();
}

// ======================================================
// FUNCTION: startQuiz
// PURPOSE: Main game loop controlling the entire quiz experience
// FLOW:
//   1. Initializes player stats
//   2. Gets player name
//   3. Selects category and difficulty
//   4. Loads and shuffles questions
//   5. Runs 10-question loop with timer
//   6. Handles lifelines and scoring
//   7. Displays results and saves scores
//   8. Offers review and play again options
// ======================================================
void startQuiz() {
    Player player;
    string filename, categoryName;

    // Initialize player stats - fresh start!
    player.score = 0;
    player.correct = 0;
    player.wrong = 0;
    player.life_50 = true;
    player.life_skip = true;
    player.life_replace = true;
    player.life_time = true;
    player.streak = 0;
    player.wrongCount = 0;

    // Get player's name
    clearScreen();
    cout << " What should we call you? : ";
    getline(cin, player.name);

    // Let player choose category and difficulty
    selectCategory(filename, categoryName);
    player.category = categoryName;
    string difficulty;
    selectDifficulty(difficulty);
    player.difficulty = difficulty;

    // Load and shuffle questions
    clearScreen();
    cout << "Loading some brain-busting questions..." << endl;
    loadQuestions(filename, difficulty);
    shuffleQuestions();
    cout << " Questions all shuffled up! Let's do this! :D" << endl;
    pressEnterToContinue();

    // QUIZ LOOP - 10 QUESTIONS
    for (int i = 0; i < 10; i++) {
        int timeLeft = 10;
        bool answered = false;
        bool skipped = false;
        time_t startTime = time(0);

        // Loop for each question until answered or skipped
        while (!answered && !skipped) {
            int secondsPassed = difftime(time(0), startTime);
            timeLeft = 10 - secondsPassed;

            // TIME'S UP!
            if (timeLeft <= 0) {
                cout << "TIME'S UP! Too slow, friend! :P" << endl;
                int penalty = 5;
                player.score -= penalty;
                player.wrong++;
                player.streak = 0;

                // Remember this wrong question for later review
                player.wrongQuestions[player.wrongCount] = i;
                player.wrongCount++;

                cout << " Penalty: -" << penalty << " points for taking too long!" << endl;
                answered = true;
                pressEnterToContinue();
                break;
            }

            // Display the current question
            displayQuestion(questions[i], i + 1, timeLeft, player);
            cout << "Your answer (1-4) or lifeline (5-8): ";
            int answer = getValidInput(1, 8);

            // HANDLE LIFELINES
            if (answer == 5 && player.life_50) {
                use5050(questions[i], player);
                pressEnterToContinue();
                continue;
            }
            else if (answer == 6 && player.life_skip) {
                cout << "Skipping this one! No worries, no penalty :)" << endl;
                player.life_skip = false;
                skipped = true;
                pressEnterToContinue();
                break;
            }
            else if (answer == 7 && player.life_replace) {
                cout << "Getting you a fresh question instead!" << endl;
                player.life_replace = false;
                skipped = true;
                pressEnterToContinue();
                break;
            }
            else if (answer == 8 && player.life_time) {
                cout << "+10 seconds! Use 'em wisely! ;)" << endl;
                startTime -= 10;  // Add time by moving start time back
                player.life_time = false;
                pressEnterToContinue();
                continue;
            }
            else if (answer > 4) {
                cout << "That lifeline's already gone or doesn't exist!" << endl;
                pressEnterToContinue();
                continue;
            }

            // CHECK IF ANSWER IS CORRECT
            if (answer == questions[i].correct) {
                cout << "......................._." << endl;
                cout << "  CORRECT! Nice one! :D" << endl;
                cout << "  +10 points to your score!" << endl;
                player.score += 10;
                player.correct++;
                player.streak++;

                // STREAK BONUSES - Rewards for consecutive correct answers
                if (player.streak == 3) {
                    cout << "  3-STREAK BONUS! +5 points! You're on fire!" << endl;
                    player.score += 5;
                }
                if (player.streak == 5) {
                    cout << "  5-STREAK BONUS! +15 points! UNSTOPPABLE! XD" << endl;
                    player.score += 15;
                }
                cout << "......................._." << endl;
            }
            else {
                // WRONG ANSWER
                cout << "......................._." << endl;
                cout << "  Oops, not quite! :(" << endl;
                cout << "  The answer was: " << questions[i].correct << ". " << questions[i].options[questions[i].correct - 1] << endl;
                player.wrong++;
                player.streak = 0;

                // Save for review
                player.wrongQuestions[player.wrongCount] = i;
                player.wrongCount++;

                // Apply penalty based on difficulty
                int penalty = 0;
                if (difficulty == "Easy") penalty = 2;
                else if (difficulty == "Medium") penalty = 3;
                else penalty = 5;

                player.score -= penalty;
                cout << "  Penalty: -" << penalty << " points! Ouch!" << endl;
                cout << "......................._." << endl;
            }

            answered = true;
            pressEnterToContinue();
        }
    }

    // SHOW RESULTS
    clearScreen();
    cout << "......................._." << endl;
    cout << "        QUIZ COMPLETE! Good job! :)" << endl;
    cout << "......................._." << endl << endl;
    cout << "Player: " << player.name << endl;
    cout << "Category: " << player.category << endl;
    cout << "Difficulty: " << player.difficulty << endl;
    cout << "Final Score: " << player.score << " points" << endl;
    cout << "Correct: " << player.correct << endl;
    cout << "Wrong: " << player.wrong << endl;
    cout << "......................._." << endl;

    // Save the results
    saveHighScore(player);
    saveQuizLog(player);
    cout << "Your score's been saved to the hall of fame!" << endl;
    pressEnterToContinue();

    // Offer to review mistakes
    reviewIncorrectAnswers(player);

    // Ask if they want to play again
    playAgainPrompt();
}

// ======================================================
// FUNCTION: saveHighScore
// PURPOSE: Saves player's score to the high scores file
// FILE FORMAT: Each line contains player data separated by newlines
// SAVES: Name, Score, Category, Difficulty, Date/Time
// MODE: Append mode to preserve existing scores
// ======================================================
void saveHighScore(Player& player) {
    ofstream file("high_scores.txt", ios::app);
    if (!file.is_open()) {
        cout << "Couldn't save your score, file issues :/" << endl;
        return;
    }
    // FIXED: Using pipe separators instead of newlines
    file << player.name << "|" << player.score << "|" << player.category << "|" << player.difficulty << "|" << getCurrentDateTime() << endl;
    file.close();
}
// ======================================================
// FUNCTION: saveQuizLog
// PURPOSE: Saves detailed quiz log for record keeping
// FILE FORMAT: Formatted log with separators and all game details
// SAVES: Complete game session information for debugging/analysis
// ======================================================
void saveQuizLog(Player& player) {
    ofstream file("quiz_logs.txt", ios::app);
    if (!file.is_open()) return;

    file << "......................._." << endl;
    file << "Player: " << player.name << endl;
    file << "Date: " << getCurrentDateTime() << endl;
    file << "Category: " << player.category << endl;
    file << "Difficulty: " << player.difficulty << endl;
    file << "Score: " << player.score << endl;
    file << "Correct: " << player.correct << endl;
    file << "Wrong: " << player.wrong << endl;
    file << "......................._." << endl << endl;

    file.close();
}

// ======================================================
// FUNCTION: viewHighScores
// PURPOSE: Shows the top 5 high scores from the leaderboard
// DISPLAYS: Formatted leaderboard with player info and scores
// HANDLES: Empty file case gracefully
// FORMAT: Rank. Name - Score pts [Category-Difficulty] Date
// ======================================================
void viewHighScores() {
    clearScreen();

    cout << "......................._." << endl;
    cout << "      HALL OF FAME - TOP 5 LEGENDS :D" << endl;
    cout << "......................._." << endl << endl;

    ifstream file("high_scores.txt");
    if (!file.is_open()) {
        cout << " No scores yet! Be the first to make history! :)" << endl;
        pressEnterToContinue();
        return;
    }

    string line;
    int count = 0;

    // Read and display up to 5 high scores
    // Read and display up to 5 high scores
    while (getline(file, line) && count < 5) {
        stringstream ss(line);
        string name, category, difficulty, date;
        int score;

        getline(ss, name, '|');
        ss >> score;
        ss.ignore();
        getline(ss, category, '|');
        getline(ss, difficulty, '|');
        getline(ss, date);

        cout << " " << (count + 1) << ". " << name << " - " << score << " pts [" << category << "-" << difficulty << "] " << date << endl;
        count++;
    }

    if (count == 0)
        cout << " Empty leaderboard! Time to make your mark!" << endl;

    file.close();
    pressEnterToContinue();
}

// ======================================================
// FUNCTION: reviewIncorrectAnswers
// PURPOSE: Shows the questions the player got wrong (for learning)
// DISPLAYS: Up to 5 wrong questions with correct answers
// HANDLES: Perfect score case (no wrong answers)
// FEATURE: Learning tool to improve performance
// ======================================================
void reviewIncorrectAnswers(Player& player) {
    if (player.wrongCount == 0) {
        cout << "PERFECT SCORE! You didn't miss any! You're a genius! :D" << endl;
        pressEnterToContinue();
        return;
    }

    cout << "......................._." << endl;
    cout << "    LET'S REVIEW YOUR MISTAKES" << endl;
    cout << "......................._." << endl;
    cout << "You missed " << player.wrongCount << " question(s):" << endl;

    // Show up to 5 wrong questions with correct answers
    for (int i = 0; i < player.wrongCount && i < 5; i++) {
        int qIndex = player.wrongQuestions[i];
        cout << "\n" << (i + 1) << ". " << questions[qIndex].question << endl;
        cout << "    Right answer: " << questions[qIndex].correct << ". " << questions[qIndex].options[questions[qIndex].correct - 1] << endl;
    }

    cout << "\n Learn from these and come back stronger! :)" << endl;
    pressEnterToContinue();
}

// ======================================================
// FUNCTION: playAgainPrompt
// PURPOSE: Asks player if they want to play another round
// OPTIONS:
//   1. Play Again - Restarts the quiz game
//   2. Back to Menu - Returns to main menu
// ======================================================
void playAgainPrompt() {
    cout << "......................._." << endl;
    cout << "    WHAT'S NEXT, BRAINIAC?" << endl;
    cout << "......................._." << endl;
    cout << "   1.  Play Again (One more round!)" << endl;
    cout << "   2.  Back to Main Menu" << endl;
    cout << "......................._." << endl;
    cout << " Your choice: ";

    int choice = getValidInput(1, 2);
    if (choice == 1) {
        startQuiz();  // Start fresh quiz
    }
    // Choice 2 just returns to main menu naturally
}