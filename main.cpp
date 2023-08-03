#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include "song.h"
#include "SortAlgorithms"
#include <chrono>
#include <sstream>
#include <string>
using namespace std;

void ReadCSV(Playlist& p, const string& opt, const string& adj, bool exp, int year, const string& artist){
    ifstream inFile;

    inFile.open("tracks_features.csv");

    string line;
    getline(inFile, line); // ignore header
    while (getline(inFile, line)){
        if (!line.empty()){
            istringstream stream(line);
            Song* newSong = new Song;
            newSong->Deserialize(stream);
            p.Insert(newSong, opt, adj, exp, year, artist);
        }
    }
}

int main() {
    Playlist p;
    Playlist p2;

    bool on = true;

    while(on){
        cout << "How would you like to design your playlist?" << endl;
        cout << "1. Decade" << endl;
        cout << "2. Mood" << endl;
        cout << "3. Event" << endl;
        cout << "4. Artist" << endl;
        cout << "0. End" << endl;

        int result;
        string artist;
        cin >> result;
        char exp;
        bool exp_cont;
        int year;
        string num;

        if (result == 0)
            break;

            // Decade
        else if (result == 1){
            cout << "Enter Decade (ex. 1950): " << endl;
            cin >> result;

            cout << "Family Friendly? (Y/N): " << endl;
            cin >> exp;

            if (exp == 'Y')
                exp_cont = false;
            else
                exp_cont = true;

            cout << "How many songs? (10 - 50): " << endl;
            cin >> num;

            ReadCSV(p, "decade", "any", exp_cont, result, "any");

            auto start = chrono::high_resolution_clock::now();
            p2.songs = MergeSort(p.songs);
            auto stop = chrono::high_resolution_clock::now();
            auto timeMerge = chrono::duration_cast<chrono::microseconds>(stop - start);

            start = chrono::high_resolution_clock::now();
            ShellSort(p.songs, p.songs.size());
            stop = chrono::high_resolution_clock::now();
            auto timeShell = chrono::duration_cast<chrono::microseconds>(stop - start);

            cout << endl;
            if (num != "all"){
                p2.PrintN(stoi(num));
            }
            else
                p.PrintAll();
            p.songs.clear();
            result = 0;

            cout << "Merge Sort time: " << timeMerge.count() << " microseconds" << endl;
            cout << "Shell Sort time: " << timeShell.count() << " microseconds" << endl;
            cout << endl;
        }

            // mood
        else if (result == 2){
            cout << "Select Mood: " << endl;
            cout << "1. Happy " << endl; // high energy A major, Bb major c major
            cout << "2. Sad " << endl; // low energy f minor G minor ab major/minor Bb minor b mino (50 - 80 ) C sharp minor
            cout << "3. Relaxed " << endl; // mid-energy ~ 60 bpm lots of instrumental low loud
            cout << "4. Victorious" << endl; // D major high energy high tempo
            cout << "5. Angry" << endl; // f major b major very loud high tempo
            cout << "6. Sleepy" << endl;
            cout << "0. to stop the program" << endl;

            cin >> result;

            cout << "Family Friendly? (Y/N): " << endl;
            cin >> exp;
            if (exp == 'Y')
                exp_cont = false;
            else
                exp_cont = true;
            cout << "Insert year: (\"0\" if all): " << endl;
            cin >> year;

            cout << "How many songs? (10 - 50): " << endl;
            cin >> num;


            if (result == 1)
                ReadCSV(p, "mood", "happy", exp_cont, year, "any");
            else if (result == 2)
                ReadCSV(p, "mood", "sad", exp_cont, year, "any");
            else if (result == 3)
                ReadCSV(p, "mood", "relaxed", exp_cont, year, "any");
            else if (result == 4)
                ReadCSV(p, "mood", "victory", exp_cont, year, "any");
            else if (result == 5)
                ReadCSV(p, "mood","angry", exp_cont, year, "any");
            else if (result == 6)
                ReadCSV(p, "mood", "sleepy", exp_cont, year, "any");
            else
                break;

            auto start = chrono::high_resolution_clock::now();
            p2.songs = MergeSort(p.songs);
            auto stop = chrono::high_resolution_clock::now();
            auto timeMerge = chrono::duration_cast<chrono::microseconds>(stop - start);

            start = chrono::high_resolution_clock::now();
            ShellSort(p.songs, p.songs.size());
            stop = chrono::high_resolution_clock::now();
            auto timeShell = chrono::duration_cast<chrono::microseconds>(stop - start);

            cout << endl;
            if (num != "all")
                p2.PrintN(stoi(num));
            else
                p.PrintAll();

            p.songs.clear();
            result = 0;

            cout << "Merge Sort time: " << timeMerge.count() << " microseconds" << endl;
            cout << "Shell Sort time: " << timeShell.count() << " microseconds" << endl;
            cout << endl;
        }

            // Event
        else if (result == 3){
            cout << "Enter Event: " << endl;
            cout << "1. Dinner Party" << endl;  // low dance + fam friendly
            cout << "2. Party" << endl; // high dance
            cout << "3. Workout" << endl; // high energy + high dance + high tempo
            cout << "4. After party" << endl; // mid energy + mid tempo
            cout << "5. Studying" << endl;
            cin >> result;


            cout << "Family Friendly? (Y/N): " << endl;
            cin >> exp;
            if (exp == 'Y')
                exp_cont = false;
            else
                exp_cont = true;
            cout << "Insert year: (\"0\" if all): " << endl;
            cin >> year;

            cout << "How many songs? (10 - 50): " << endl;
            cin >> num;

            if (result == 1)
                ReadCSV(p, "event", "dinner", exp_cont, year, "any");
            else if (result == 2)
                ReadCSV(p, "event", "party", exp_cont, year, "any");
            else if (result == 3)
                ReadCSV(p, "event", "workout", exp_cont, year, "any");
            else if (result == 4)
                ReadCSV(p, "event", "after party", exp_cont, year, "any");
            else if (result == 5)
                ReadCSV(p, "event", "studying", exp_cont, year, "any");
            else {
                break;
            }

            auto start = chrono::high_resolution_clock::now();
            p2.songs = MergeSort(p.songs);
            auto stop = chrono::high_resolution_clock::now();
            auto timeMerge = chrono::duration_cast<chrono::microseconds>(stop - start);

            start = chrono::high_resolution_clock::now();
            ShellSort(p.songs, p.songs.size());
            stop = chrono::high_resolution_clock::now();
            auto timeShell = chrono::duration_cast<chrono::microseconds>(stop - start);

            cout << endl;
            if (num != "all")
                p.PrintN(stoi(num));
            else
                p.PrintAll();

            p.songs.clear();
            result = 0;

            cout << "Merge Sort time: " << timeMerge.count() << " microseconds" << endl;
            cout << "Shell Sort time: " << timeShell.count() << " microseconds" << endl;
            cout << endl;
        }

            // Artist
        else if (result == 4){
            cout << "Enter Artist: " << endl;
            cin.ignore();
            getline(cin, artist);

            cout << "Family Friendly? (Y/N): " << endl;
            cin >> exp;
            if (exp == 'Y')
                exp_cont = false;
            else
                exp_cont = true;

            cout << "Insert year: (\"0\" if all): " << endl;
            cin >> year;

            cout << "How many songs? (10 - 50): " << endl;
            cin >> num;

            ReadCSV(p, "artist", "any", exp_cont, year, artist);

            auto start = chrono::high_resolution_clock::now();
            p2.songs = MergeSort(p.songs);
            auto stop = chrono::high_resolution_clock::now();
            auto timeMerge = chrono::duration_cast<chrono::microseconds>(stop - start);

            start = chrono::high_resolution_clock::now();
            ShellSort(p.songs, p.songs.size());
            stop = chrono::high_resolution_clock::now();
            auto timeShell = chrono::duration_cast<chrono::microseconds>(stop - start);

            cout << endl;
            if (num != "all")
                p.PrintN(stoi(num));
            else
                p.PrintAll();

            p.songs.clear();
            result = 0;

            cout << "Merge Sort time: " << timeMerge.count() << " microseconds" << endl;
            cout << "Shell Sort time: " << timeShell.count() << " microseconds" << endl;
            cout << endl;
        }
    }
}
