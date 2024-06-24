#include <iostream>
#include <string>

using namespace std;

const int MAX_MOVIES = 25;

// Movie struct
struct Movie {
    string title= "Unknown";
    string genre= "Unknown";
    int year = 0;
};

// History stack using linked list
struct HistoryNode {
    Movie movie;
    HistoryNode* next = NULL;
};

// Add a new movie to the watchlist
void addMovie(Movie movies[], int& count) {
    if (count >= MAX_MOVIES) {
        cout << "Watchlist is full.\n";
        return;
    }

    Movie newMovie;
    cout << "Enter movie title: ";
    getline(cin, newMovie.title);
    cout << "Enter movie genre: ";
    getline(cin, newMovie.genre);
    cout << "Enter movie year: ";
    cin >> newMovie.year;
    cin.ignore(); // Ignore the newline character

    movies[count++] = newMovie;
    cout << "Movie added to the watchlist.\n";
}

// Display all movies in the watchlist
void displayMovies(const Movie movies[], int count) {
    if (count == 0) {
        cout << "Watchlist is empty.\n";
        return;
    }

    for (int i = 0; i < count; ++i) {
        cout << i + 1 << ". " << movies[i].title << " (" << movies[i].year << ") - " << movies[i].genre << "\n";
    }
}

// Update an existing movie in the watchlist
void updateMovie(Movie movies[], int count) {
    if (count == 0) {
        cout << "Watchlist is empty.\n";
        return;
    }

    int index;
    cout << "Enter the index of the movie to update (1 to " << count << "): ";
    cin >> index;
    cin.ignore(); // Ignore the newline character

    if (index < 1 || index > count) {
        cout << "Invalid index.\n";
        return;
    }

    Movie& movie = movies[index - 1];
    cout << "Enter new movie title (current: " << movie.title << "): ";
    getline(cin, movie.title);
    cout << "Enter new movie genre (current: " << movie.genre << "): ";
    getline(cin, movie.genre);
    cout << "Enter new movie year (current: " << movie.year << "): ";
    cin >> movie.year;
    cin.ignore(); // Ignore the newline character

    cout << "Movie updated.\n";
}

// Delete a movie from the watchlist
void deleteMovie(Movie movies[], int& count) {
    if (count == 0) {
        cout << "Watchlist is empty.\n";
        return;
    }

    int index;
    cout << "Enter the index of the movie to delete (1 to " << count << "): ";
    cin >> index;
    cin.ignore(); // Ignore the newline character

    if (index < 1 || index > count) {
        cout << "Invalid index.\n";
        return;
    }

    for (int i = index - 1; i < count - 1; ++i) {
        movies[i] = movies[i + 1];
    }
    --count;

    cout << "Movie deleted from the watchlist.\n";
}

// Search for a movie in the watchlist(sequential Search)
void searchMovie(const Movie movies[], int count) {
    if (count == 0) {
        cout << "Watchlist is empty.\n";
        return;
    }

    string searchTerm;
    cout << "Enter the movie title to search: ";
    getline(cin, searchTerm);

    bool found = false;
    for (int i = 0; i < count; ++i) {
        bool match = true;
        // Perform a simple sequential search
        if (movies[i].title.length() >= searchTerm.length()) {
            for (size_t j = 0; j < searchTerm.length(); ++j) {
                if (tolower(movies[i].title[j]) != tolower(searchTerm[j])) {
                    match = false;
                    break;
                }
            }
            if (match) {
                cout << i + 1 << ". " << movies[i].title << " (" << movies[i].year << ") - " << movies[i].genre << "\n";
                found = true;
            }
        }
    }

    if (!found) {
        cout << "No matching movies found.\n";
    }
}

// Sort the watchlist by year
void sortMovies(Movie movies[], int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (movies[j].year > movies[j + 1].year) {
                Movie temp = movies[j];
                movies[j] = movies[j + 1];
                movies[j + 1] = temp;
            }
        }
    }
    cout << "Watchlist sorted by year.\n";
}

// Watch a movie and add it to history
void watchMovie(Movie movies[], int& count, HistoryNode*& history) {
    if (count == 0) {
        cout << "Watchlist is empty.\n";
        return;
    }

    int index;
    cout << "Enter the index of the movie to watch (1 to " << count << "): ";
    cin >> index;
    cin.ignore(); // Ignore the newline character

    if (index < 1 || index > count) {
        cout << "Invalid index.\n";
        return;
    }

    // Add to history
    HistoryNode* newNode = new HistoryNode;
    newNode->movie = movies[index - 1];
    newNode->next = history;
    history = newNode;

    // Remove from watchlist
    deleteMovie(movies, count);
    cout << "Movie watched and added to history.\n";
}

// Display the history of watched movies
void displayHistory(HistoryNode* history) {
    if (history == nullptr) {
        cout << "No history available.\n";
        return;
    }

    HistoryNode* current = history;
    while (current != nullptr) {
        cout << current->movie.title << " (" << current->movie.year << ") - " << current->movie.genre << "\n";
        current = current->next;
    }
}

int main() {
    Movie watchlist[MAX_MOVIES];
    int movieCount = 0;
    HistoryNode* history = nullptr;

    int choice;

    do {
        cout << "\n Personal Watchlist App\n";
        cout << "=========================\n";
        cout << "1. Add Movie\n";
        cout << "2. Display Movies\n";
        cout << "3. Update Movie\n";
        cout << "4. Delete Movie\n";
        cout << "5. Search Movie\n";
        cout << "6. Sort Movies\n";
        cout << "7. Watch Movie\n";
        cout << "8. Display History\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore the newline character

        switch (choice) {
        case 1:
            addMovie(watchlist, movieCount);
            break;
        case 2:
            displayMovies(watchlist, movieCount);
            break;
        case 3:
            updateMovie(watchlist, movieCount);
            break;
        case 4:
            deleteMovie(watchlist, movieCount);
            break;
        case 5:
            searchMovie(watchlist, movieCount);
            break;
        case 6:
            sortMovies(watchlist, movieCount);
            break;
        case 7:
            watchMovie(watchlist, movieCount, history);
            break;
        case 8:
            displayHistory(history);
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}