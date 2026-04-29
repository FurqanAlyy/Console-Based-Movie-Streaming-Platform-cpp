#include <iostream>
#include <string>
#include "movie.h"
#include "user.h"
using namespace std;

class StreamingPlatform
{
private:
    MovieManager movieManager;
    TrendingHeap trendingHeap;
    UserManager userManager;

public:
    void loadData()
    {
        movieManager.loadFromFile("movies.txt");
        movieManager.buildTrending(trendingHeap);
        userManager.loadAll("users.txt");
    }

    void saveData()
    {
        movieManager.saveToFile("movies.txt");
        userManager.saveAll("users.txt");
    }

    void mainMenu()
    {
        loadData();
        int choice;
        do
        {
            cout << "\n=== Streaming Platform ===\n";
            cout << "1. Sign Up\n";
            cout << "2. Log In\n";
            cout << "3. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore();

            if (choice == 1)
                handleSignUp();
            else if (choice == 2)
                handleLogin();
        } while (choice != 3);

        saveData();
        cout << "Goodbye!\n";
    }

    void handleSignUp()
    {
        string uname, pass;
        cout << "Choose a username: ";
        getline(cin, uname);
        cout << "Choose a password: ";
        getline(cin, pass);
        userManager.signUp(uname, pass);
    }

    void handleLogin()
    {
        string uname, pass;
        cout << "Enter username: ";
        getline(cin, uname);
        cout << "Enter password: ";
        getline(cin, pass);
        if (userManager.login(uname, pass))
        {
            userDashboard();
            userManager.logout();
        }
    }

    void userDashboard()
    {
        int choice;
        do
        {
            cout << "\n--- User Dashboard ---\n";
            cout << "1. Search Movie by Title\n";
            cout << "2. Watch Movie\n";
            cout << "3. Undo Last Watched\n";
            cout << "4. Show Watch History\n";
            cout << "5. Add to Watchlist\n";
            cout << "6. Show Watchlist\n";
            cout << "7. Remove from Watchlist\n";
            cout << "8. Show Trending\n";
            cout << "9. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice)
            {
            case 1:
                
                searchMovie();
                break;
            case 2:
                watchMovie();
                break;
            case 3:
                undoWatch();
                break;
            case 4:
                showHistory();
                break;
            case 5:
                addToWatchlist();
                break;
            case 6:
                showWatchlist();
                break;
            case 7:
                removeFromWatchlist();
                break;
            case 8:
                showTrending();
                break;
            case 9:
                return;
            default:
                cout << "Invalid option!\n";
            }
        } while (true);
    }

    void searchMovie()
    {   
        string title;
        cout << "Enter movie title: ";
        getline(cin, title);
        Movie* m = movieManager.searchByTitle(title);
        if (m)
        {
            cout << "\nMovie found:\n";
            m->display();
        }
        else
        {
            cout << "Movie not found.\n";
        }
    }

    void watchMovie()
    {
        movieManager.showMovieList();
        User* u = userManager.getCurrentUser();
        if (!u)
            return;

        string title;
        cout << "Enter movie title to watch: ";
        getline(cin, title);
        Movie* m = movieManager.searchByTitle(title);
        if (m)
        {
            m->views++;
            u->watchMovie(title);
            movieManager.buildTrending(trendingHeap);
        }
        else
        {
            cout << "Movie not found.\n";
        }
    }

    void undoWatch()
    {
        User* u = userManager.getCurrentUser();
        if (u)
            u->undoWatch();
    }

    void showHistory()
    {
        User* u = userManager.getCurrentUser();
        if (u)
            u->showHistory();
    }

    void addToWatchlist()
    {
        movieManager.showMovieList();
        User* u = userManager.getCurrentUser();
        if (!u)
            return;
        string title;
        cout << "Enter movie title to add to watchlist: ";
        getline(cin, title);
        Movie* m = movieManager.searchByTitle(title);
        if (m)
            u->addToWatchlist(title);
        else
            cout << "Movie not found.\n";
    }

    void removeFromWatchlist()
    {
        User* u = userManager.getCurrentUser();
        if (!u)
            return;

        string title;
        cout << "Enter movie title to remove from watchlist: ";
        getline(cin, title);
        u->removeFromWatchlist(title);
    }

    void showWatchlist()
    {
        User* u = userManager.getCurrentUser();
        if (u)
            u->showWatchlist();
    }

    void showTrending()
    {
        trendingHeap.showTopN(5);
    }
};
