# 🎬 C++ Console Streaming Platform

A console-based movie streaming platform built in C++ that simulates core features of a real streaming service — user accounts, movie browsing, watch history, watchlists, and trending charts.

---

## 📁 Project Structure

```
├── source.cpp       # Entry point
├── platform.h       # StreamingPlatform class (main controller)
├── movies.h         # Movie, MovieManager, TrendingHeap classes
├── user.h           # User and UserManager classes
├── movies.txt       # Movie data (auto-generated)
└── users.txt        # User data (auto-generated)
```

---

## ✨ Features

### 👤 User System
- **Sign Up** — Create a new account with a username and password
- **Log In / Log Out** — Secure session management
- Data is **persisted to disk** (`users.txt`) between runs

### 🎥 Movie Browsing
- Browse the full movie catalogue loaded from `movies.txt`
- **Search by title** using a hash map for O(1) lookup
- Each movie stores: title, genre, actor, rating, and view count

### ▶️ Watch History (Stack)
- Watch a movie to add it to your history
- **Undo last watched** — removes the most recently watched movie (stack-based)
- View your full watch history in reverse chronological order

### 📋 Watchlist (Array)
- Add movies to a personal watchlist
- Remove movies from the watchlist
- View all saved titles

### 🔥 Trending (Max-Heap)
- View the **Top 5 Trending Movies** ranked by view count
- Trending list updates automatically every time a movie is watched
- Implemented using a custom max-heap

---

## 🗂️ Data Structures Used

| Feature | Data Structure |
|---|---|
| Movie search by title | `unordered_map` (Hash Map) |
| Trending movies | Max-Heap (custom array-based) |
| Watch history & undo | Stack (array-based) |
| Watchlist | Dynamic array |
| User storage | `unordered_map` |

---

## 🚀 Getting Started

### Prerequisites
- A C++ compiler (g++, MSVC, Clang)
- C++11 or later

### Compilation

```bash
g++ source.cpp -o streamflix
```

### Run

```bash
./streamflix
```

---

## 📄 Data Files

The program reads and writes two plain-text files automatically:

- **`movies.txt`** — Stores all movie records (title, genre, actor, rating, views)
- **`users.txt`** — Stores all user accounts along with their watchlists and watch history

> If these files don't exist on first run, the platform starts with an empty catalogue. You can manually populate `movies.txt` using the format below.

### `movies.txt` Format
```
Movie Title
Genre
Actor Name
<rating> <views>
```

**Example:**
```
Inception
Sci-Fi
Leonardo DiCaprio
8.8 150000
The Dark Knight
Action
Christian Bale
9.0 200000
```

---

## 🔮 Possible Improvements

- Add admin panel to add/remove movies from within the app
- Implement genre and actor-based search
- Add movie ratings by users
- Replace file storage with a proper database
- Build a GUI frontend

---

## 👨‍💻 Author
# Furqan Ali

Built as a Data Structures course project in C++.
