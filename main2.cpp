#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <sstream> // Add this line to include the stringstream header

using namespace std;

struct User {
    string username;
    string password;
    double weight;
    double height;
};

// Struct to represent a workout entry
struct Workout {
    string username;
    string date;
    string time;
    string activity;
    double duration;
    double calories1;
};

// Struct to represent a food entry
struct Food {
    string username;
    string date;
    string time;
    string item;
    double calories;
};

string getCurrentDateTime() {
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &ltm);
    return string(buffer);
}

bool authenticateUser(const string &username, const string &password) {
    ifstream file("users.txt");
    string u, p;
    double w;

    while (file >> u >> p >> w) {
        if (u == username && p == password) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void logWorkout(const string &username) {
    ofstream file("workouts.txt", ios::app);
    Workout workout;
    workout.username = username;
    workout.date = getCurrentDateTime();
    
    cin.ignore();
    cout << "Enter Activity: ";
    getline(cin, workout.activity);
    cout << "Enter Duration (in minutes): ";
    cin >> workout.duration;
    cout << "Enter the Calories burned: ";
    cin >> workout.calories1;

    file << workout.username << " " << workout.date << " " << workout.activity << " " << workout.duration << " " << workout.calories1 << endl;
    file.close();

    cout << "Workout logged successfully!" << endl;
}

void logFood(const string &username) {
    ofstream file("foods.txt", ios::app);
    Food food;
    food.username = username;
    food.date = getCurrentDateTime();

    cin.ignore();
    cout << "Enter Food Item: ";
    getline(cin, food.item);
    cout << "Enter Calories: ";
    cin >> food.calories;

    file << food.username << " " << food.date << " " << food.item << " " << food.calories << endl;
    file.close();

    cout << "Food logged successfully!" << endl;
}

void updateWeight(const string &username) {
    ifstream inFile("users.txt");
    ofstream outFile("temp.txt");

    string u, p;
    double w;
    double newWeight;
    while (inFile >> u >> p >> w) {
        if (u == username) {
            cout << "Enter New Weight (in kg): ";
            cin >> newWeight;
            outFile << u << " " << p << " " << newWeight << endl;
        } else {
            outFile << u << " " << p << " " << w << endl;
        }
    }

    inFile.close();
    outFile.close();

    remove("users.txt");
    rename("temp.txt", "users.txt");

    cout << "Weight updated successfully!" << endl;
}

void showRecentDetails(const string &username) {
    ifstream workoutFile("workouts.txt");
    ifstream foodFile("foods.txt");
    string line;
    bool workoutFound = false;
    bool foodFound = false;

    cout << "\n--- Recent Details ---\n";

    // Display recent workouts for the user
    while (getline(workoutFile, line)) {
        istringstream iss(line);
        Workout workout;
        iss >> workout.username >> workout.date >> workout.time >> workout.activity >> workout.duration >> workout.calories1;
        if (workout.username == username) {
            cout << "Last Workout:\n";
            cout << "Date: " << workout.date << "\n";
            cout << "Activity: " << workout.activity << "\n";
            cout << "Duration: " << workout.duration << " minutes\n";
            cout << "Calories Burned: " << workout.calories1 << "\n";
            workoutFound = true;
            break;  // Display only the most recent workout
        }
    }
    workoutFile.close();

    // Display recent food intake for the user
    while (getline(foodFile, line)) {
        istringstream iss(line);
        Food food;
        iss >> food.username >> food.date >> food.time >> food.item >> food.calories;
        if (food.username == username) {
            cout << "\nLast Food Intake:\n";
            cout << "Date: " << food.date << "\n";
            cout << "Food Item: " << food.item << "\n";
            cout << "Calories: " << food.calories << "\n";
            foodFound = true;
            break;  // Display only the most recent food entry
        }
    }
    foodFile.close();

    if (!workoutFound) {
        cout << "No workouts logged yet.\n";
    }

    if (!foodFound) {
        cout << "No foods logged yet.\n";
    }

    cout << "-----------------------\n\n";
}

void exportUserDetails(const string &username) {
    ofstream exportFile(username + "_details.txt");
    ifstream workoutFile("workouts.txt");
    ifstream foodFile("foods.txt");
    string line;

    exportFile << "=== User Details for " << username << " ===\n\n";

    // Export workout details
    exportFile << "=== Workout Details ===\n";
    while (getline(workoutFile, line)) {
        istringstream iss(line);
        Workout workout;
        iss >> workout.username >> workout.date >> workout.time >> workout.activity >> workout.duration >> workout.calories1;
        if (workout.username == username) {
            exportFile << "Date: " << workout.date << "\n";
            exportFile << "Time: " << workout.time << "\n";
            exportFile << "Activity: " << workout.activity << "\n";
            exportFile << "Duration: " << workout.duration << " minutes\n";
            exportFile << "Calories Burned: " << workout.calories1 << "\n\n";
        }
    }
    exportFile << "\n";

    // Export food details
    exportFile << "=== Food Details ===\n";
    while (getline(foodFile, line)) {
        istringstream iss(line);
        Food food;
        iss >> food.username >> food.date >> food.time >> food.item >> food.calories;
        if (food.username == username) {
            exportFile << "Date: " << food.date << "\n";
            exportFile << "Time: " << food.time << "\n";
            exportFile << "Food Item: " << food.item << "\n";
            exportFile << "Calories: " << food.calories << "\n\n";
        }
    }

    exportFile.close();
    cout << "User details exported successfully to " << username << "_details.txt\n";
}

void userDashboard(const string &username) {
    int choice;

    while (true) {
        cout << "=== " << username << "'s Dashboard ===" << endl;
        cout << "1. Log Workout" << endl;
        cout << "2. Log Food" << endl;
        cout << "3. Update Weight" << endl;
        cout << "4. Show Recent Workout and Food Details" << endl;
        cout << "5. Export Details" << endl;
        cout << "6. Logout" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                logWorkout(username);
                break;
            case 2:
                logFood(username);
                break;
            case 3:
                updateWeight(username);
                break;
            case 4:
                showRecentDetails(username);
                break;
            case 5:
                exportUserDetails(username); // Call the exportUserDetails function
                break;
            case 6:
                return;  // Logout and return to the main menu
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}

void registerUser() {
    string username, password;
    double weight;

    cout << "Enter Username: ";
    cin >> username;

    cout << "Enter Password: ";
    cin >> password;

    cout << "Enter Weight (in kg): ";
    cin >> weight;

    ofstream file("users.txt", ios::app);
    file << username << " " << password << " " << weight << endl;
    file.close();

    cout << "Registration successful!" << endl;
}

void loginUser() {
    string username, password;

    cout << "Enter Username: ";
    cin >> username;

    cout << "Enter Password: ";
    cin >> password;

    if (authenticateUser(username, password)) {
        cout << "Login successful!" << endl;
        userDashboard(username);
    } else {
        cout << "Invalid username or password. Try again." << endl;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "=== Main Menu ===" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                return 0;  // Exit the program
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}