# Social Network Analysis

A C++ application for modeling and analyzing a social network using graph algorithms. This console-based project enables users to create a network of people, connect them through friendships, and analyze relationships using **Breadth-First Search (BFS)** and **Depth-First Search (DFS)**. Data is stored persistently via text file serialization.

---

## 🧠 Features

- 🧍 **Person Management**: Add individuals with names and interests
- 🤝 **Mutual Friendships**: Connect people in two-way relationships
- 🧭 **Shortest Path Detection**: Find connection paths using BFS
- 🎯 **Interest-Based Grouping**: Identify groups sharing common interests via DFS
- 💾 **Persistent Storage**: Save and load data from a `.txt` file
- 🖥️ **Console Menu Interface**: Simple and interactive navigation

---

## 🗃️ Data File Structure

- First line: Number of people
- For each person:
  - ID
  - Name
  - Number of interests
  - List of interests
  - Number of friends
  - List of friend IDs

Saved to: `social_network_data.txt`

---

## 🧱 Class Structure

### `Person` Struct

- `id`: Unique identifier
- `name`: Full name
- `interests`: List of interests
- `friends`: List of friend IDs

### `SocialNetwork` Class

Manages the graph and interactions.

#### Key Members:
- `people`: `map<int, Person>`
- `next_id`: For generating unique IDs
- `datafile`: File used for saving/loading

#### Core Methods:
- `addPerson()`
- `addFriendship()`
- `findPath()` – Uses **BFS**
- `findGroup()` – Uses **DFS**
- `listPeople()`
- `saveData()` and `loadData()`

---

## 🛠️ How to Run

1. Compile the project using any C++ compiler:
   ```bash
   g++ main.cpp -o social_network
   ./social_network
