#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class User {
public:
    string username;
    string password;
};

class Workout {
public:
    string date;
    string type;
    float duration;
    float caloriesBurned;
};

class Food {
public:
    string date;
    string foodName;
    float calories;
};

vector<User> users;
vector<Workout> workouts;
vector<Food> foods;

void saveUsersToFile() {
    ofstream userFile("users.txt");
    if (userFile.is_open()) {
        for (const User& user : users) {
            userFile << user.username << " " << user.password << endl;
        }
        userFile.close();
    }
}

void loadUsersFromFile() {
    ifstream userFile("users.txt");
    if (userFile.is_open()) {
        users.clear();
        string username, password;
        while (userFile >> username >> password) {
            User user;
            user.username = username;
            user.password = password;
            users.push_back(user);
        }
        userFile.close();
    }
}

void saveWorkoutsToFile() {
    ofstream workoutFile("workouts.txt");
    if (workoutFile.is_open()) {
        for (const Workout& workout : workouts) {
            workoutFile << workout.date << " " << workout.type << " " << workout.duration << " " << workout.caloriesBurned << endl;
        }
        workoutFile.close();
    }
}

void loadWorkoutsFromFile() {
    ifstream workoutFile("workouts.txt");
    if (workoutFile.is_open()) {
        workouts.clear();
        string date, type;
        float duration, caloriesBurned;
        while (workoutFile >> date >> type >> duration >> caloriesBurned) {
            Workout workout;
            workout.date = date;
            workout.type = type;
            workout.duration = duration;
            workout.caloriesBurned = caloriesBurned;
            workouts.push_back(workout);
        }
        workoutFile.close();
    }
}

void saveFoodsToFile() {
    ofstream foodFile("foods.txt");
    if (foodFile.is_open()) {
        for (const Food& food : foods) {
            foodFile << food.date << " " << food.foodName << " " << food.calories << endl;
        }
        foodFile.close();
    }
}

void loadFoodsFromFile() {
    ifstream foodFile("foods.txt");
    if (foodFile.is_open()) {
        foods.clear();
        string date, foodName;
        float calories;
        while (foodFile >> date >> foodName >> calories) {
            Food food;
            food.date = date;
            food.foodName = foodName;
            food.calories = calories;
            foods.push_back(food);
        }
        foodFile.close();
    }
}

bool isUserRegistered(const string& username) {
    for (const User& user : users) {
        if (user.username == username) {
            return true;
        }
    }
    return false;
}

bool loginUser(const string& username, const string& password) {
    for (const User& user : users) {
        if (user.username == username && user.password == password) {
            return true;
        }
    }
    return false;
}

void registerUser() {
    string username, password;
    cout << "Enter a username: ";
    cin >> username;

    if (isUserRegistered(username)) {
        cout << "Username already exists. Please choose another one.\n";
        return;
    }

    cout << "Enter a password: ";
    cin >> password;

    User user;
    user.username = username;
    user.password = password;

    users.push_back(user);
    saveUsersToFile();

    cout << "User registered successfully!\n";
}

void logWorkout(const string& username) {
    Workout workout;
    workout.date = getCurrentDate();
    cout << "Enter workout type: ";
    cin.ignore();
    getline(cin, workout.type);
    cout << "Enter duration (minutes): ";
    cin >> workout.duration;
    cout << "Enter calories burned: ";
    cin >> workout.caloriesBurned;

    workouts.push_back(workout);
    saveWorkoutsToFile();

    cout << "Workout logged successfully!\n";
}

void logFood(const string& username) {
    Food food;
    food.date = getCurrentDate();
    cout << "Enter food name: ";
    cin.ignore();
    getline(cin, food.foodName);
    cout << "Enter calories: ";
    cin >> food.calories;

    foods.push_back(food);
    saveFoodsToFile();

    cout << "Food intake logged successfully!\n";
}

string getCurrentDate() {
    time_t currentTime = time(nullptr);
    tm* localTime = localtime(&currentTime);
    char dateStr[11];
    strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", localTime);
    return dateStr;
}

int main() {
    loadUsersFromFile();
    loadWorkoutsFromFile();
    loadFoodsFromFile();

    int choice;
    string username, password;

    while (true) {
        cout << "Welcome to HealthLogix!\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                if (loginUser(username, password)) {
                    cout << "Login successful!\n";
                    while (true) {
                        cout << "1. Log Workout\n";
                        cout << "2. Log Food Intake\n";
                        cout << "3. Logout\n";
                        cout << "Enter your choice: ";
                        cin >> choice;
                        if (choice == 1) {
                            logWorkout(username);
                        } else if (choice == 2) {
                            logFood(username);
                        } else if (choice == 3) {
                            cout << "Logout successful!\n";
                            break;
                        } else {
                            cout << "Invalid choice. Try again.\n";
                        }
                    }
                } else {
                    cout << "Login failed. Invalid username or password.\n";
                }
                break;
            case 3:
                cout << "Exiting HealthLogix. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
