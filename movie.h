
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;

const int MAX_MOVIES = 1000;

class Movie
{
public:
    string title;
    string genre;
    string actor;
    float rating;
    int views;

    Movie()
    {
        title = genre = actor = "";
        rating = 0.0;
        views = 0;
    }

    Movie(string t, string g, string a, float r, int v)
    {
        title = t;
        genre = g;
        actor = a;
        rating = r;
        views = v;
    }

    void display() const
    {
        cout << "Title: " << title << "\nGenre: " << genre
            << "\nActor: " << actor << "\nRating: " << rating
            << "\nViews: " << views << "\n\n";
    }
};

class TrendingHeap
{
private:
    Movie heap[MAX_MOVIES];
    int size;

    void swap(Movie& a, Movie& b)
    {
        Movie temp = a;
        a = b;
        b = temp;
    }

    void heapifyDown(int i)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && heap[left].views > heap[largest].views)
            largest = left;
        if (right < size && heap[right].views > heap[largest].views)
            largest = right;

        if (largest != i)
        {
            swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }

    void heapifyUp(int i)
    {
        if (i && heap[(i - 1) / 2].views < heap[i].views)
        {
            swap(heap[i], heap[(i - 1) / 2]);
            heapifyUp((i - 1) / 2);
        }
    }

public:
    TrendingHeap()
    {
        size = 0;
    }

    void insert(Movie m)
    {
        if (size >= MAX_MOVIES)
            return;
        heap[size] = m;
        heapifyUp(size);
        size++;
    }

    void showTopN(int n)
    {
        cout << "\nTop " << n << " Trending Movies:\n";
        for (int i = 0; i < min(n, size); ++i)
            cout << i + 1 << ". " << heap[i].title << " (Views: " << heap[i].views << ")\n";
        cout << endl;
    }

    void reset()
    {
        size = 0;
    }
};

class MovieManager
{
public:
    Movie movies[MAX_MOVIES];
    int count;

    unordered_map<string, Movie*> titleMap;
    unordered_map<string, Movie*> genreMap[MAX_MOVIES];
    unordered_map<string, Movie*> actorMap[MAX_MOVIES];

    MovieManager()
    {
        count = 0;
    }

    void addMovie(Movie m)
    {
        if (count >= MAX_MOVIES)
            return;
        movies[count] = m;
        titleMap[m.title] = &movies[count];
        count++;
    }

    Movie* searchByTitle(const string& title)
    {
        if (titleMap.find(title) != titleMap.end())
            return titleMap[title];
        return nullptr;
    }

    void loadFromFile(const string& filename)
    {
        ifstream fin(filename);
        if (!fin.is_open())
            return;
        string t, g, a;
        float r;
        int v;
        while (getline(fin, t))
        {
            getline(fin, g);
            getline(fin, a);
            fin >> r >> v;
            fin.ignore();
            addMovie(Movie(t, g, a, r, v));
        }
        fin.close();
    }

    void saveToFile(const string& filename)
    {
        ofstream fout(filename);
        for (int i = 0; i < count; ++i)
        {
            fout << movies[i].title << "\n"
                << movies[i].genre << "\n"
                << movies[i].actor << "\n"
                << movies[i].rating << " " << movies[i].views << "\n";
        }
        fout.close();
    }

    void buildTrending(TrendingHeap& heap)
    {
        heap.reset();
        for (int i = 0; i < count; ++i)
            heap.insert(movies[i]);
    }

    void showMovieList() {
            ifstream file("movies.txt");

            if (!file.is_open()) {
                cout << "Failed to open file." << endl;
                return;
            }

            string name, genre, writer;
            float rating;
            int views;

            cout << "Movies List:\n";
            cout << "-----------------------------\n";

            while (getline(file, name)) {
                getline(file, genre);
                getline(file, writer);
                file >> rating;
                file >> views;
                file.ignore(); 

                cout << "Name   : " << name << endl;
                cout << "Genre  : " << genre << endl;
                cout << "Writer : " << writer << endl;
                cout << "Rating : " << rating << endl;
                cout << "Views  : " << views << endl;
                cout << "-----------------------------\n";
            }

            file.close();
        }

};
