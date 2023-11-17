#include <string>
#include <cmath>

class UserProfile {
private:
    string name;
    int age;
    char gender; // 'M' for male, 'F' for female, 'O' for others
    float height; // in meters
    float weight; // in kilograms

public:
    // Constructors
    UserProfile() : name(""), age(0), gender('O'), height(0.0), weight(0.0) {}
    UserProfile(const string& n, int a, char g, float h, float w)
        : name(n), age(a), gender(g), height(h), weight(w) {}

    // Getters
    string getName() const { return name; }
    int getAge() const { return age; }
    char getGender() const { return gender; }
    float getHeight() const { return height; }
    float getWeight() const { return weight; }

    // Setters
    void setName(const string& n) { name = n; }
    void setAge(int a) { age = a; }
    void setGender(char g) { gender = g; }
    void setHeight(float h) { height = h; }
    void setWeight(float w) { weight = w; }

    // Calculate BMI
    float calculateBMI() const {
        if (height == 0.0) return 0.0; // To avoid division by zero
        return weight / (height * height);
    }
};
