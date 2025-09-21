#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <map>

using namespace std;
using namespace chrono;

struct Question {
    string question;
    vector<string> options;
    int correctAnswer;
    string category;
};

struct Player {
    string name;
    int score;
    string category;
    int timeSpent;
    string date;
    
    Player(string n, int s, string c, int t, string d) 
        : name(n), score(s), category(c), timeSpent(t), date(d) {}
};

class QuizApp {
private:
    vector<Question> questions;
    vector<Player> leaderboard;
    string leaderboardFile = "leaderboard.txt";
    
public:
    QuizApp() {
        initializeQuestions();
        loadLeaderboard();
    }
    
    void initializeQuestions() {
        questions.push_back({
            "What is the chemical symbol for gold?",
            {"A) Go", "B) Gd", "C) Au", "D) Ag"},
            2, "Science"
        });
        
        questions.push_back({
            "Which planet is known as the Red Planet?",
            {"A) Venus", "B) Mars", "C) Jupiter", "D) Saturn"},
            1, "Science"
        });
        
        questions.push_back({
            "What is the speed of light in vacuum?",
            {"A) 300,000 km/s", "B) 299,792,458 m/s", "C) 186,000 mph", "D) All of the above"},
            3, "Science"
        });
        
        questions.push_back({
            "What is the smallest unit of matter?",
            {"A) Molecule", "B) Atom", "C) Proton", "D) Quark"},
            3, "Science"
        });
        
        questions.push_back({
            "Which gas makes up about 78% of Earth's atmosphere?",
            {"A) Oxygen", "B) Carbon Dioxide", "C) Nitrogen", "D) Hydrogen"},
            2, "Science"
        });
        
        questions.push_back({
            "In which year did World War II end?",
            {"A) 1944", "B) 1945", "C) 1946", "D) 1947"},
            1, "History"
        });
        
        questions.push_back({
            "Who was the first person to walk on the moon?",
            {"A) Buzz Aldrin", "B) Neil Armstrong", "C) John Glenn", "D) Alan Shepard"},
            1, "History"
        });
        
        questions.push_back({
            "Which ancient wonder of the world was located in Alexandria?",
            {"A) Hanging Gardens", "B) Colossus of Rhodes", "C) Lighthouse", "D) Statue of Zeus"},
            2, "History"
        });
        
        questions.push_back({
            "The Berlin Wall fell in which year?",
            {"A) 1987", "B) 1989", "C) 1991", "D) 1993"},
            1, "History"
        });
        
        questions.push_back({
            "Who painted the ceiling of the Sistine Chapel?",
            {"A) Leonardo da Vinci", "B) Raphael", "C) Michelangelo", "D) Donatello"},
            2, "History"
        });
        
        questions.push_back({
            "What is the capital of Australia?",
            {"A) Sydney", "B) Melbourne", "C) Canberra", "D) Perth"},
            2, "Geography"
        });
        
        questions.push_back({
            "Which is the longest river in the world?",
            {"A) Amazon", "B) Nile", "C) Mississippi", "D) Yangtze"},
            1, "Geography"
        });
        
        questions.push_back({
            "Mount Everest is located in which mountain range?",
            {"A) Andes", "B) Alps", "C) Himalayas", "D) Rocky Mountains"},
            2, "Geography"
        });
        
        questions.push_back({
            "Which country has the most time zones?",
            {"A) Russia", "B) United States", "C) China", "D) France"},
            3, "Geography"
        });
        
        questions.push_back({
            "What is the smallest country in the world?",
            {"A) Monaco", "B) San Marino", "C) Vatican City", "D) Liechtenstein"},
            2, "Geography"
        });
        
        questions.push_back({
            "How many players are on a basketball team on the court at one time?",
            {"A) 4", "B) 5", "C) 6", "D) 7"},
            1, "Sports"
        });
        
        questions.push_back({
            "In which sport would you perform a slam dunk?",
            {"A) Volleyball", "B) Tennis", "C) Basketball", "D) Football"},
            2, "Sports"
        });
        
        questions.push_back({
            "How often are the Summer Olympics held?",
            {"A) Every 2 years", "B) Every 3 years", "C) Every 4 years", "D) Every 5 years"},
            2, "Sports"
        });
        
        questions.push_back({
            "What is the maximum score possible in ten-pin bowling?",
            {"A) 200", "B) 250", "C) 300", "D) 350"},
            2, "Sports"
        });
        
        questions.push_back({
            "Which country won the FIFA World Cup in 2018?",
            {"A) Germany", "B) Brazil", "C) France", "D) Argentina"},
            2, "Sports"
        });
    }
    
    void loadLeaderboard() {
        ifstream file(leaderboardFile);
        if (!file.is_open()) return;
        
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, category, date;
            int score, timeSpent;
            
            if (getline(ss, name, ',') &&
                ss >> score && ss.ignore() &&
                getline(ss, category, ',') &&
                ss >> timeSpent && ss.ignore() &&
                getline(ss, date)) {
                leaderboard.emplace_back(name, score, category, timeSpent, date);
            }
        }
        file.close();
    }
    
    void saveLeaderboard() {
        ofstream file(leaderboardFile);
        if (!file.is_open()) {
            cout << "Error: Could not save leaderboard!\n";
            return;
        }
        
        for (const auto& player : leaderboard) {
            file << player.name << "," << player.score << "," 
                 << player.category << "," << player.timeSpent << "," 
                 << player.date << "\n";
        }
        file.close();
    }
    
    string getCurrentDate() {
        auto now = system_clock::now();
        auto time_t = system_clock::to_time_t(now);
        stringstream ss;
        ss << put_time(localtime(&time_t), "%Y-%m-%d");
        return ss.str();
    }
    
    vector<Question> getQuestionsByCategory(const string& category) {
        vector<Question> categoryQuestions;
        for (const auto& q : questions) {
            if (q.category == category) {
                categoryQuestions.push_back(q);
            }
        }
        return categoryQuestions;
    }
    
    void shuffleQuestions(vector<Question>& qs) {
        random_device rd;
        mt19937 g(rd());
        shuffle(qs.begin(), qs.end(), g);
    }
    
    void displayQuestion(const Question& q, int questionNum, int totalQuestions) {
        cout << "\n" << string(50, '=') << "\n";
        cout << "Question " << questionNum << "/" << totalQuestions << "\n";
        cout << string(50, '=') << "\n";
        cout << q.question << "\n\n";
        
        for (const auto& option : q.options) {
            cout << option << "\n";
        }
        cout << "\nYour answer (A/B/C/D): ";
    }
    
    char getValidAnswer() {
        char answer;
        while (true) {
            cin >> answer;
            answer = toupper(answer);
            if (answer >= 'A' && answer <= 'D') {
                return answer;
            }
            cout << "Invalid input! Please enter A, B, C, or D: ";
        }
    }
    
    void playQuiz() {
        cout << "\n" << string(60, '=') << "\n";
        cout << "                    QUIZ CATEGORIES" << "\n";
        cout << string(60, '=') << "\n";
        cout << "1. Science\n";
        cout << "2. History\n";
        cout << "3. Geography\n";
        cout << "4. Sports\n";
        cout << "5. Mixed (All Categories)\n";
        cout << string(60, '=') << "\n";
        cout << "Choose a category (1-5): ";
        
        int choice;
        while (!(cin >> choice) || choice < 1 || choice > 5) {
            cout << "Invalid choice! Please enter 1-5: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        
        string category;
        vector<Question> quizQuestions;
        
        switch (choice) {
            case 1: category = "Science"; break;
            case 2: category = "History"; break;
            case 3: category = "Geography"; break;
            case 4: category = "Sports"; break;
            case 5: category = "Mixed"; break;
        }
        
        if (category == "Mixed") {
            quizQuestions = questions;
        } else {
            quizQuestions = getQuestionsByCategory(category);
        }
        
        shuffleQuestions(quizQuestions);
        
        int numQuestions = min(5, (int)quizQuestions.size());
        quizQuestions.resize(numQuestions);
        
        cout << "\nEnter your name: ";
        cin.ignore();
        string playerName;
        getline(cin, playerName);
        
        cout << "\n" << string(60, '=') << "\n";
        cout << "Welcome " << playerName << "! Quiz starting...\n";
        cout << "Category: " << category << "\n";
        cout << "Questions: " << numQuestions << "\n";
        cout << "Time limit: 30 seconds per question\n";
        cout << string(60, '=') << "\n";
        cout << "\nPress Enter to start...";
        cin.get();
        
        int score = 0;
        auto quizStart = high_resolution_clock::now();
        
        for (int i = 0; i < numQuestions; i++) {
            auto questionStart = high_resolution_clock::now();
            
            displayQuestion(quizQuestions[i], i + 1, numQuestions);
            
            char answer = getValidAnswer();
            
            auto questionEnd = high_resolution_clock::now();
            auto questionTime = duration_cast<seconds>(questionEnd - questionStart).count();
            
            if (questionTime > 30) {
                cout << "\nTime's up! Moving to next question...\n";
            } else if (answer - 'A' == quizQuestions[i].correctAnswer) {
                score++;
                cout << "Correct! ✓\n";
            } else {
                cout << "Incorrect! ✗ The correct answer was " 
                     << char('A' + quizQuestions[i].correctAnswer) << "\n";
            }
            
            if (i < numQuestions - 1) {
                cout << "\nPress Enter for next question...";
                cin.ignore();
                cin.get();
            }
        }
        
        auto quizEnd = high_resolution_clock::now();
        int totalTime = duration_cast<seconds>(quizEnd - quizStart).count();
        
        
        cout << "\n" << string(60, '=') << "\n";
        cout << "                    QUIZ COMPLETED!" << "\n";
        cout << string(60, '=') << "\n";
        cout << "Player: " << playerName << "\n";
        cout << "Category: " << category << "\n";
        cout << "Score: " << score << "/" << numQuestions << " (" 
             << (score * 100 / numQuestions) << "%)\n";
        cout << "Time taken: " << totalTime << " seconds\n";
        cout << string(60, '=') << "\n";
    
        leaderboard.emplace_back(playerName, score, category, totalTime, getCurrentDate());
        saveLeaderboard();
        
        cout << "\nYour score has been added to the leaderboard!\n";
    }
    
    void displayLeaderboard() {
        if (leaderboard.empty()) {
            cout << "\nNo scores recorded yet. Play a quiz to get started!\n";
            return;
        }
        
        cout << "\n" << string(80, '=') << "\n";
        cout << "                              LEADERBOARD" << "\n";
        cout << string(80, '=') << "\n";
        
        
        vector<Player> sortedBoard = leaderboard;
        sort(sortedBoard.begin(), sortedBoard.end(), 
             [](const Player& a, const Player& b) {
                 if (a.score != b.score) return a.score > b.score;
                 return a.timeSpent < b.timeSpent;
             });
        
        cout << left << setw(4) << "Rank" << setw(20) << "Name" 
             << setw(10) << "Score" << setw(12) << "Category" 
             << setw(8) << "Time" << setw(12) << "Date" << "\n";
        cout << string(80, '-') << "\n";
        
        for (int i = 0; i < min(10, (int)sortedBoard.size()); i++) {
            const auto& player = sortedBoard[i];
            cout << left << setw(4) << (i + 1) 
                 << setw(20) << player.name.substr(0, 19)
                 << setw(10) << (to_string(player.score) + "/5")
                 << setw(12) << player.category.substr(0, 11)
                 << setw(8) << (to_string(player.timeSpent) + "s")
                 << setw(12) << player.date << "\n";
        }
        cout << string(80, '=') << "\n";
        
        
        cout << "\nCATEGORY CHAMPIONS:\n";
        cout << string(40, '-') << "\n";
        
        vector<string> categories = {"Science", "History", "Geography", "Sports", "Mixed"};
        for (const string& cat : categories) {
            auto best = max_element(sortedBoard.begin(), sortedBoard.end(),
                [&cat](const Player& a, const Player& b) {
                    if (a.category != cat && b.category != cat) return false;
                    if (a.category != cat) return true;
                    if (b.category != cat) return false;
                    if (a.score != b.score) return a.score < b.score;
                    return a.timeSpent > b.timeSpent;
                });
            
            if (best != sortedBoard.end() && best->category == cat) {
                cout << left << setw(12) << cat << ": " 
                     << best->name << " (" << best->score << "/5)\n";
            }
        }
    }
    
    void showStatistics() {
        cout << "\n" << string(60, '=') << "\n";
        cout << "                    QUIZ STATISTICS" << "\n";
        cout << string(60, '=') << "\n";
        
        if (leaderboard.empty()) {
            cout << "No data available. Play some quizzes first!\n";
            return;
        }
        
        int totalQuizzes = leaderboard.size();
        int totalScore = 0;
        int totalTime = 0;
        
        map<string, int> categoryCount;
        map<string, int> categoryScore;
        
        for (const auto& player : leaderboard) {
            totalScore += player.score;
            totalTime += player.timeSpent;
            categoryCount[player.category]++;
            categoryScore[player.category] += player.score;
        }
        
        cout << "Total quizzes played: " << totalQuizzes << "\n";
        cout << "Average score: " << fixed << setprecision(1) 
             << (double)totalScore / totalQuizzes << "/5\n";
        cout << "Average time per quiz: " << totalTime / totalQuizzes << " seconds\n\n";
        
        cout << "CATEGORY BREAKDOWN:\n";
        cout << string(30, '-') << "\n";
        for (const auto& cat : categoryCount) {
            cout << left << setw(12) << cat.first << ": " 
                 << cat.second << " quizzes, avg score: "
                 << fixed << setprecision(1) 
                 << (double)categoryScore[cat.first] / cat.second << "/5\n";
        }
        
        auto bestPlayer = max_element(leaderboard.begin(), leaderboard.end(),
            [](const Player& a, const Player& b) {
                if (a.score != b.score) return a.score < b.score;
                return a.timeSpent > b.timeSpent;
            });
        
        cout << "\nBest performance: " << bestPlayer->name 
             << " (" << bestPlayer->score << "/5 in " 
             << bestPlayer->timeSpent << "s)\n";
        cout << string(60, '=') << "\n";
    }
    
    void displayMenu() {
        cout << "\n" << string(60, '=') << "\n";
        cout << "                    QUIZ APPLICATION" << "\n";
        cout << string(60, '=') << "\n";
        cout << "1. Play Quiz\n";
        cout << "2. View Leaderboard\n";
        cout << "3. View Statistics\n";
        cout << "4. Exit\n";
        cout << string(60, '=') << "\n";
        cout << "Enter your choice (1-4): ";
    }
    
    void run() {
        cout << "Welcome to the Ultimate Quiz App!\n";
        
        while (true) {
            displayMenu();
            
            int choice;
            while (!(cin >> choice) || choice < 1 || choice > 4) {
                cout << "Invalid choice! Please enter 1-4: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            
            switch (choice) {
                case 1:
                    playQuiz();
                    break;
                case 2:
                    displayLeaderboard();
                    break;
                case 3:
                    showStatistics();
                    break;
                case 4:
                    cout << "\nThanks for playing! Goodbye!\n";
                    return;
            }
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    }
};

int main() {
    QuizApp app;
    app.run();
    return 0;
}
