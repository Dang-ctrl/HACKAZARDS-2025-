#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <map>
#include <fstream>
#include <cstdlib> // for random number generation
#include <cmath> // for calculating streaks

using namespace std;

// Helper function to get current date as string
string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", ltm);
    return string(buf);
}

// Helper function for generating random motivational quotes
string getMotivationalQuote() {
    const string quotes[] = {
        "You are capable of amazing things!",
        "Consistency is the key to success!",
        "Small steps every day add up to big results.",
        "Believe in yourself and all that you are.",
        "Stay focused and never give up!"
    };
    return quotes[rand() % 5];
}

class Habit {
private:
    string name;
    string category;
    string frequency;
    int streak;
    vector<string> completionDates;
    int goal;  // For personalized goal setting
    bool isCompletedToday; // Prevent duplicate completion on the same day

public:
    Habit(string n, string cat, string freq, int g = 0) : name(n), category(cat), frequency(freq), streak(0), goal(g), isCompletedToday(false) {}

    // Mark habit as done and update streak
    void markDone() {
        string today = getCurrentDate();
        if (!isCompletedToday) {
            if (completionDates.empty() || completionDates.back() != today) {
                completionDates.push_back(today);
                streak++;
                isCompletedToday = true;
                cout << "Great job! You've completed this habit today!\n";
            }
        } else {
            cout << "You have already completed this habit today.\n";
        }
    }

    void resetStreak() { streak = 0; }

    int getStreak() const { return streak; }
    string getName() const { return name; }

    bool isGoalAchieved() const {
        return goal != 0 && streak >= goal;
    }

    // Display habit details including goal status
    void showDetails() const {
        cout << "Habit: " << name << " | Category: " << category << " | Frequency: " << frequency
             << " | Streak: " << streak << " days";
        if (isGoalAchieved()) {
            cout << " | Goal achieved!";
        }
        cout << endl;
    }

    int getGoal() const { return goal; }
    void setGoal(int g) { goal = g; }
};

class User {
private:
    string name;
    vector<Habit> habits;
    int rewardPoints;

public:
    User(string uname) : name(uname), rewardPoints(0) {}

    void addHabit() {
        string hname, hcat, hfreq;
        int goal = 0;

        cout << "Enter habit name: ";
        cin.ignore(); getline(cin, hname);
        cout << "Enter category (Health/Productivity/etc.): "; getline(cin, hcat);
        cout << "Enter frequency (daily/weekly): "; getline(cin, hfreq);
        cout << "Enter goal (0 for no goal, or a target streak): ";
        cin >> goal;

        habits.push_back(Habit(hname, hcat, hfreq, goal));
    }

    void markHabitDone() {
        showHabits();
        cout << "Select habit index to mark as done: ";
        int idx; cin >> idx;
        if (idx >= 0 && idx < habits.size()) {
            habits[idx].markDone();
            cout << "Habit marked as done!\n";

            // Reward system based on streak
            if (habits[idx].getStreak() % 5 == 0) { // Milestone reward
                rewardPoints += 10;
                cout << "Congrats! You've earned 10 reward points for a 5-day streak.\n";
            }
            if (habits[idx].isGoalAchieved()) {
                rewardPoints += 20; // Goal completion reward
                cout << "Awesome! You've achieved your goal and earned 20 reward points.\n";
            }
        } else {
            cout << "Invalid index!\n";
        }
    }

    void showHabits() const {
        if (habits.empty()) {
            cout << "No habits yet. Add one!\n";
            return;
        }
        for (int i = 0; i < habits.size(); ++i) {
            cout << i << ". ";
            habits[i].showDetails();
        }
    }

    void showStats() const {
        cout << "--- Habit Stats for " << name << " ---\n";
        showHabits();
        cout << "Total Reward Points: " << rewardPoints << endl;
    }

    void viewMotivation() const {
        cout << getMotivationalQuote() << endl;
    }

    string getName() const { return name; }
    int getRewardPoints() const { return rewardPoints; }
};

class HabitSphereApp {
private:
    vector<User> users;

public:
    void run() {
        cout << "Welcome to HabitSphere!\n";
        cout << "Enter your name: ";
        string uname;
        cin >> uname;

        User currentUser(uname);
        bool running = true;

        while (running) {
            int choice;
            cout << "\n1. Add Habit\n2. Mark Habit as Done\n3. View Stats\n4. View Motivation\n5. Exit\nChoose an option: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    currentUser.addHabit();
                    break;
                case 2:
                    currentUser.markHabitDone();
                    break;
                case 3:
                    currentUser.showStats();
                    break;
                case 4:
                    currentUser.viewMotivation();
                    break;
                case 5:
                    running = false;
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        }
        cout << "Goodbye! Keep up the great work!\n";
    }
};

int main() {
    HabitSphereApp app;
    app.run();
    return 0;
}
