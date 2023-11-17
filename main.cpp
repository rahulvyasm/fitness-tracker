#include <iostream>
#include <fstream> 
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;

class HealthLogixApp {
private:
    void displayMainMenu() {
        cout << "===== HealthLogix =====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
    }

    void displayUserMenu() {
        cout << "===== User Dashboard =====\n";
        cout << "1. Add Workout\n";
        cout << "2. Add Food\n";
        cout << "3. View Weight History\n";
        cout << "4. Logout\n";
        cout << "Enter your choice: ";
    }

    void registerUser() {
        string username, password;
        int age;
        string gender;
        float height, weight;

        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        cout << "Enter age: ";
        cin >> age;
        cout << "Enter gender (Male/Female/Other): ";
        cin >> gender;
        cout << "Enter height (in cm): ";
        cin >> height;
        cout << "Enter weight (in kg): ";
        cin >> weight;

        ofstream file("users.txt", ios::app);  // Open the file in append mode
        if (file.is_open()) {
            // Write user details to the file
            file << username << " " << password << " " << age << " " << gender << " " << height << " " << weight << endl;
            file.close();
            cout << "Registration successful!\n";
        } else {
            cout << "Failed to open the user file.\n";
        }

        // After registration, give the option to go back to the main menu
        cout << "Press 'B' to go back to the main menu or any other key to continue registering: ";
        char choice;
        cin >> choice;
        if (choice == 'B' || choice == 'b') {
            return; // User chose to go back to the main menu
        }
    }


    void loginUser() {
        string username, password;

        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        ifstream file("users.txt");
        if (file.is_open()) {
            string storedUsername, storedPassword;
            while (file >> storedUsername >> storedPassword) {
                if (storedUsername == username && storedPassword == password) {
                    cout << "Login successful!\n";
                    file.close();
                    userDashboard();
                    return;
                }
            }
            file.close();
        }
    
        cout << "Login failed. Check your credentials.\n";
    }


    void userDashboard() {
        int choice;
        do {
            displayUserMenu();
            cin >> choice;

            switch (choice) {
                case 1:
                    // Add workout logic
                    break;
                case 2:
                    // Add food logic
                    break;
                case 3:
                    // View weight history logic
                    break;
                case 4:
                    cout << "Logged out successfully!\n";
                    return;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        } while (true);
    }

public:
    void run() {
        int choice;
        do {
            displayMainMenu();
            cin >> choice;

            switch (choice) {
                case 1:
                    registerUser();
                    break;
                case 2:
                    loginUser();
                    break;
                case 3:
                    cout << "Exiting...\n";
                    return;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        } while (true);
    }
};

int main() {
    HealthLogixApp app;
    app.run();
    return 0;
}
