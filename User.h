
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;

const int MAX_USERS = 100;
const int MAX_WATCHLIST = 100;
const int MAX_HISTORY = 100;

class Movie;

class User
{
private:
    string username;
    string password;

    string watchlist[MAX_WATCHLIST];
    int watchlistCount;

    string history[MAX_HISTORY];
    int top;

public:
    User()
    {
        username = "";
        password = "";
        watchlistCount = 0;
        top = -1;
    }

    User(string u, string p)
    {
        username = u;
        password = p;
        watchlistCount = 0;
        top = -1;
    }

    string getUsername() const
    {
        return username;
    }

    bool checkPassword(string pass) const
    {
        return password == pass;
    }

    void watchMovie(string title)  
    {  
       if (top < MAX_HISTORY - 1)  
       {  
           history[++top] = title;  
           cout << "You watched: " << title << endl;  
       }  
       else  
       {  
           cout << "History is full. Cannot add more movies.\n";  
       }  
    }

    void undoWatch()
    {
        if (top >= 0)
        {
            cout << "Undo last watched movie: " << history[top--] << endl;
        }
        else
        {
            cout << "No history to undo.\n";
        }
    }

    void showHistory() const
    {
        if (top != 0) {
            cout << "\nWatch History:\n";
            for (int i = top; i >= 0; --i)
            {
                cout << history[i] << endl;
            }
        }
        else
            cout << "No Movies in history." << endl;
    }

    void addToWatchlist(string title)
    {
        if (watchlistCount < MAX_WATCHLIST)
        {
            watchlist[watchlistCount++] = title;
            cout << "Added to watchlist: " << title << endl;
        }
    }

    void removeFromWatchlist(string title)
    {
        int index = -1;
        for (int i = 0; i < watchlistCount; ++i)
        {
            if (watchlist[i] == title)
            {
                index = i;
                break;
            }
        }
        if (index != -1)
        {
            for (int i = index; i < watchlistCount - 1; ++i)
            {
                watchlist[i] = watchlist[i + 1];
            }
            watchlistCount--;
            cout << "Removed from watchlist: " << title << endl;
        }
        else
        {
            cout << "Movie not found in watchlist.\n";
        }
    }

    void showWatchlist() const
    {
        cout << "\nYour Watchlist:\n";
        if (watchlistCount != 0) {
            for (int i = 0; i < watchlistCount; ++i)
            {
                cout << i + 1 << ". " << watchlist[i] << endl;
            }
        }
        else
            cout << "You have not added any movie to Watchlist." << endl;
    }

    void saveToFile(ofstream& fout)
    {
        fout << username << "\n"
            << password << "\n";

        fout << watchlistCount << "\n";
        for (int i = 0; i < watchlistCount; ++i)
            fout << watchlist[i] << "\n";

        fout << top + 1 << "\n";
        for (int i = 0; i <= top; ++i)
            fout << history[i] << "\n";
    }

    void loadFromFile(ifstream& fin)
    {
        getline(fin, username);
        getline(fin, password);

        fin >> watchlistCount;
        fin.ignore();
        for (int i = 0; i < watchlistCount; ++i)
            getline(fin, watchlist[i]);

        fin >> top;
        fin.ignore();
        for (int i = 0; i <= top; ++i)
            getline(fin, history[i]);
    }
};

class UserManager
{
private:
    unordered_map<string, User> users;
    User* currentUser;

public:
    UserManager()
    {
        currentUser = nullptr;
    }

    bool signUp(string uname, string pass)
    {
        if (users.find(uname) != users.end())
        {
            cout << "Username already exists.\n";
            return false;
        }
        users[uname] = User(uname, pass);
        cout << "Signup successful!\n";
        return true;
    }

    bool login(string uname, string pass)
    {
        if (users.find(uname) != users.end() && users[uname].checkPassword(pass))
        {
            currentUser = &users[uname];
            cout << "Login successful!\n";
            return true;
        }
        cout << "Invalid credentials.\n";
        return false;
    }

    User* getCurrentUser()
    {
        return currentUser;
    }

    void logout()
    {
        currentUser = nullptr;
    }

    void saveAll(const string& filename)
    {
        ofstream fout(filename);
        fout << users.size() << "\n";
        for (auto& pair : users)
        {
            pair.second.saveToFile(fout);
        }
        fout.close();
    }

    void loadAll(const string& filename)
    {
        ifstream fin(filename);
        if (!fin.is_open())
            return;
        int total;
        fin >> total;
        fin.ignore();
        for (int i = 0; i < total; ++i)
        {
            User u;
            u.loadFromFile(fin);
            users[u.getUsername()] = u;
        }
        fin.close();
    }
};
