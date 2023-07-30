#include <iostream>
#include <vector>
using namespace std;
struct Song {
    // class variables
    string name;
    string album;
    string artist;
    bool exp;
    int dance;
    int key;
    int energy;
    int loud;
    int year;
    int tempo;
    int valence;
    int rating;
public:
    void Deserialize(istringstream& stream);
};

class Playlist{
public:
    Song* s;
    vector<Song*> songs;
    Playlist() : songs(){}
    void Insert(Song* song, const string& option, const string& adj, bool exp, int year, const string& artist);
    vector<int> Ratings();
    void PrintAll();
    void PrintN(int n);
    ~Playlist();
};
