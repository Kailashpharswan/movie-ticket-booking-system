// Movie: title, language, duration — nothing else
#include <string>
using namespace std;

class Movie {
private:
    int id;
    string title;
    string language;
    int durationMinutes;

public:
    Movie(int id, string title, string language, int durationMinutes) {
        // this keyword used to distinguish member variables from parameters
        this->id = id;
        this->title = title;
        this->language = language;
        this->durationMinutes = durationMinutes;
    }

    int getId() { return id; }
    string getTitle() { return title; }
    string getLanguage() { return language; }
    int getDurationMinutes() { return durationMinutes; }
};   // <-- don't forget this semicolon after the closing brace, it's required in C++