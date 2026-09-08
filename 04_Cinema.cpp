// Cinema: the theatre — its name; owns its screens
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Cinema {
private:
    string name;
    vector<Screen> screens;   // Composition — screens die with the cinema
    vector<Movie> movies;     // movie catalogue
    vector<Show*> shows;      // shows scheduled here

public:
    Cinema(string name) {
        this->name = name;
    }

    string getName() { return name; }

    void addScreen(Screen screen) { screens.push_back(screen); }
    void addMovie(Movie movie) { movies.push_back(movie); }
    void addShow(Show *show) { shows.push_back(show); }

    vector<Screen>& getScreens() { return screens; }
    vector<Movie>& getMovies() { return movies; }
    vector<Show*>& getShows() { return shows; }

    // F1: list all movies currently playing
    void listMovies() {
        cout << "\n  [1] Movies currently playing:\n";
        for (size_t i = 0; i < movies.size(); i++) {
            cout << "   [" << (i + 1) << "] " << movies[i].getTitle()
                 << "\t" << movies[i].getLanguage()
                 << "\t" << movies[i].getDurationMinutes() << " min\n";
        }
    }
};