#include <iostream>
#include <fstream>
#include <sstream>
#include "song.h"
#include <iomanip>
#include <chrono>
#include <string>
using namespace std;

void swap(vector<Song*> &songs, float j, float j_incr) {
    Song* temp = songs[j];
    songs[j] = songs[j_incr];
    songs[j_incr] = temp;
}

void InsertionSort(vector<Song*> &songs, int start, int incr, int n) {
    for (int i = start+incr; i < n; i += incr)
        for (int j = i; ((j >= incr) && (songs[j]->rating < songs[j-incr]->rating)); j -= incr)
            swap(songs, j, j-incr);
}

void ShellSort(vector<Song*> &songs, int n) {
    for (int i = n/2; i > 2; i /= 2)  // For each increment
        for (int j = 0; j < i; j++)  // Sort each sublist
            InsertionSort(songs, j, i, n);
    InsertionSort(songs, 0, 1, n);
}

vector<Song*> Merge(vector<Song*> songs1, vector<Song*> songs2) {
    vector<Song*> sorted;
    int count1 = 0;
    int count2 = 0;
    int size1 = songs1.size();
    int size2 = songs2.size();
    while (count1 < size1 || count2 < size2) {
        if (count1 == size1) {
            sorted.push_back(songs2[count2]);
            count2++;
        }
        else if (count2 == size2) {
            sorted.push_back(songs1[count1]);
            count1++;
        }
        else if (songs1[count1]->rating <= songs2[count2]->rating) {
            sorted.push_back(songs1[count1++]);
        }
        else
            sorted.push_back(songs2[count2++]);
    }
    return sorted;
}

vector<Song*> MergeSort(vector<Song*> inlist) {
    if (inlist.size() <= 1)
        return inlist;
    vector<Song*> list1;
    vector<Song*> list2;
    for (int i = 0; i < inlist.size(); i++) {
        if (i < inlist.size()/2)
            list1.push_back(inlist[i]);
        else
            list2.push_back(inlist[i]);
    }
    return Merge(MergeSort(list1), MergeSort(list2));
}

void PrintList(vector<Song*> list, int size) {
    for (int i = 0; i < size; i++)
        cout << fixed << setprecision(5) << list[i]->rating << " ";
}

void ReadCSV(Playlist& p, const string& opt, const string& adj, bool exp, int year, const string& artist){
    ifstream inFile;
    inFile.open("tracks_features.csv");
    string line;
    getline(inFile, line); // ignore header
    while(getline(inFile, line)) {
        if (!line.empty()){
            istringstream stream(line);
            Song* newSong = new Song;
            newSong->Deserialize(stream);
            p.Insert(newSong, opt, adj, exp, year, artist);
        }
    }
}

bool check_string(const string& str) {
    for (char i : str) {
        if (isalpha(i)) {
        }
        else if (isspace(i)) {
        }
        else {
            cout << str << " is not a valid entry, please type either Y or N." << endl;
            return false;
        }
    }
    return true;
}

bool check_num_str(const string& str, int num) {
    if (str == "all") {
        return true;
    }
    for (char i : str) {
        if (isdigit(i)) {
        }
        else {
            switch (num) {
                case 0:
                    cout << str << " is not a valid option from the menu, please try again." << endl << endl;
                    break;
                case 1:
                    cout << str << " is not a valid decade, please enter a new decade." << endl << endl;
                    break;
                case 2:
                    cout << str << " is not a valid number, please enter a numerical value." << endl << endl;
                    break;
                case 3:
                    cout << str << " is not a valid option from the menu, please try again." << endl << endl;
                    break;
            }
            return false;
        }
    }
    switch (num) {
        // Checking menu option
        case 0:
            if (stoi(str) > 4 || stoi(str) < 0) {
                cout << str << " is not a valid option from the menu, please try again." << endl << endl;
                return false;
            }
            break;
            // Checking decade option
        case 1:
            if (stoi(str) > 2029 || stoi(str) < 1900) {
                cout << str << " is out of range, please enter a decade between 1900 and 2020." << endl << endl;
                return false;
            }
            break;
            // Checking playlist size option
        case 2:
            if (stoi(str) < 0) {
                cout << "Your playlist needs at least 1 song..." << endl << endl;
                return false;
            }
            break;
            // Checking mood option
        case 3:
            if (stoi(str) > 5 || stoi(str) < 0) {
                cout << str << " is not a valid option from the menu, please try again." << endl << endl;
                return false;
            }
            break;
            // Checking year option
        case 4:
            if (stoi(str) == 0) {
                return true;
            }
            else if (stoi(str) > 2020 || stoi(str) < 1900) {
                cout << str << " is not a valid year option, please enter a year between 1900 and 2020." << endl << endl;
                return false;
            }
            break;
        case 5:
            // Checking event option
            if (stoi(str) > 4 || stoi(str) < 0) {
                cout << str << " is not a valid option from the event menu, please try again." << endl << endl;
            }
            break;
        default:
            break;
    }
    return true;
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

        bool result_bool = true;
        string option_result;
        int result;
        int counter = 1;
        while (result_bool) {
            getline(cin,option_result);
            if (check_num_str(option_result, 0)) {
                result_bool = false;
                result = stoi(option_result);
            }
            else
                counter++;
            if (counter % 3 == 0 && result_bool) {
                cout << "How would you like to design your playlist?" << endl;
                cout << "1. Decade" << endl;
                cout << "2. Mood" << endl;
                cout << "3. Event" << endl;
                cout << "4. Artist" << endl;
                cout << "0. End" << endl;
            }

        }

        string artist;

        bool exp_cont;
        int year;
        bool decade_bool = true;
        bool explicit_bool = true;
        bool num_songs_bool = true;
        bool year_bool = true;
        string decade_option;
        string exp_option;
        string num_songs_option;
        string mood_option;
        string year_option;
        string event_option;
        int decade;
        int num_songs;

        // If the user wanted to exit the program.
        if (result == 0) {
            cout << "Thanks for tuning in, Goodbye!" << endl << endl;
            on = false;
        }

            // Decade
        else if (result == 1){
            cout << "Enter Decade (ex. 1950): " << endl;
            counter = 1;
            while (decade_bool) {
                cin >> decade_option;
                if (check_num_str(decade_option, 1)) {
                    decade_bool = false;
                    decade = stoi(decade_option);
                }
                else
                    counter++;
                if (counter % 3 == 0 && decade_bool) {
                    cout << "Enter Decade (ex. 1950): " << endl;
                }
            }

            cout << "Family Friendly? (Y/N): " << endl;
            counter = 0;
            while (explicit_bool) {
                getline(cin,exp_option);
                if (check_string(exp_option)) {
                    if (exp_option == "Y") {
                        explicit_bool = false;
                        exp_cont = false;
                    }
                    else if (exp_option == "N") {
                        explicit_bool = false;
                        exp_cont = true;
                    }
                    else if(counter == 1) {
                        cout << "Please enter either Y or N." << endl;
                    }
                }
                counter = 1;
            }

            counter = 1;
            cout << "How many songs? (10 - 50): " << endl;
            while (num_songs_bool) {
                cin >> num_songs_option;
                if (check_num_str(num_songs_option, 2)) {
                    num_songs = stoi(num_songs_option);
                    num_songs_bool = false;
                }
                else
                    counter++;
                if (counter % 3 == 0 && num_songs_bool) {
                    cout << "How many songs? (10 - 50): " << endl;
                }
            }

            ReadCSV(p, "decade", "any", exp_cont, decade, "any");

            auto start = chrono::high_resolution_clock::now();
            p2.songs = MergeSort(p.songs);
            auto stop = chrono::high_resolution_clock::now();
            auto timeMerge = chrono::duration_cast<chrono::microseconds>(stop - start);

            start = chrono::high_resolution_clock::now();
            ShellSort(p.songs, p.songs.size());
            stop = chrono::high_resolution_clock::now();
            auto timeShell = chrono::duration_cast<chrono::microseconds>(stop - start);

            cout << endl;
            if (num_songs_option != "all"){
                p2.PrintN(num_songs);
            }
            else
                p.PrintAll();
            p.songs.clear();
            result = 0;

            cout << "Merge Sort time: " << setprecision(3) << float(timeMerge.count())/1000.0 << " milliseconds" << endl;
            cout << "Shell Sort time: " << setprecision(3) << float(timeShell.count())/1000.0 << " milliseconds" << endl;

            cout << endl;
        }

            // mood
        else if (result == 2){
            result_bool = true;
            cout << "Select Mood: " << endl;
            cout << "1. Happy " << endl; // high energy A major, Bb major c major
            cout << "2. Sad " << endl; // low energy f minor G minor ab major/minor Bb minor b mino (50 - 80 ) C sharp minor
            cout << "3. Relaxed " << endl; // mid-energy ~ 60 bpm lots of instrumental low loud
            cout << "4. Victorious" << endl; // D major high energy high tempo
            cout << "5. Angry" << endl; // f major b major very loud high tempo
            cout << "0. to stop the program" << endl;

            counter = 1;
            while (result_bool) {
                getline(cin,option_result);
                if (check_num_str(option_result, 3)) {
                    result_bool = false;
                    result = stoi(option_result);
                }
                else
                    counter++;
                if (counter % 3 == 0 && result_bool) {
                    cout << "Select Mood: " << endl;
                    cout << "1. Happy " << endl; // high energy A major, Bb major c major
                    cout << "2. Sad " << endl; // low energy f minor G minor ab major/minor Bb minor b mino (50 - 80 ) C sharp minor
                    cout << "3. Relaxed " << endl; // mid-energy ~ 60 bpm lots of instrumental low loud
                    cout << "4. Victorious" << endl; // D major high energy high tempo
                    cout << "5. Angry" << endl; // f major b major very loud high tempo
                    cout << "0. to stop the program" << endl;
                }
            }

            cout << "Family Friendly? (Y/N): " << endl;
            counter = 0;
            while (explicit_bool) {
                getline(cin,exp_option);
                if (check_string(exp_option)) {
                    if (exp_option == "Y") {
                        explicit_bool = false;
                        exp_cont = false;
                    }
                    else if (exp_option == "N") {
                        explicit_bool = false;
                        exp_cont = true;
                    }
                    else if(counter == 1) {
                        cout << "Please enter either Y or N." << endl;
                    }
                }
                counter = 1;
            }

            counter = 1;
            cout << "Insert year: (or \"0\" if all): " << endl;
            while (year_bool) {
                cin >> year_option;
                if (check_num_str(year_option, 4)) {
                    year_bool = false;
                    year = stoi(year_option);
                }
                else
                    counter++;
                if (counter % 3 == 0 && year_bool) {
                    cout << "Insert year: (or \"0\" if all): " << endl;
                }
            }

            counter = 1;
            cout << "How many songs? (10 - 50): " << endl;
            while (num_songs_bool) {
                cin >> num_songs_option;
                if (check_num_str(num_songs_option, 2)) {
                    num_songs = stoi(num_songs_option);
                    num_songs_bool = false;
                }
                else
                    counter++;
                if (counter % 3 == 0 && num_songs_bool) {
                    cout << "How many songs? (10 - 50): " << endl;
                }
            }

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
            if (num_songs_option != "all"){
                p2.PrintN(num_songs);
            }
            else
                p.PrintAll();
            p.songs.clear();
            result = 0;

            cout << "Merge Sort time: " << setprecision(3) << float(timeMerge.count())/1000.0 << " milliseconds" << endl;
            cout << "Shell Sort time: " << setprecision(3) << float(timeShell.count())/1000.0 << " milliseconds" << endl;

            cout << endl;
        }

            // Event
        else if (result == 3) {
            result_bool = true;
            cout << "Enter Event: " << endl;
            cout << "1. Dinner Party" << endl;  // low dance + fam friendly
            cout << "2. Party" << endl; // high dance
            cout << "3. Workout" << endl; // high energy + high dance + high tempo
            cout << "4. After party" << endl; // mid energy + mid tempo
            cout << "0. to stop the program" << endl;

            counter = 1;
            while (result_bool) {
                getline(cin,event_option);
                if (check_num_str(event_option, 5)) {
                    result_bool = false;
                    result = stoi(event_option);
                }
                else
                    counter++;
                if (counter % 3 == 0 && result_bool) {
                    cout << "Enter Event: " << endl;
                    cout << "1. Dinner Party" << endl;  // low dance + fam friendly
                    cout << "2. Party" << endl; // high dance
                    cout << "3. Workout" << endl; // high energy + high dance + high tempo
                    cout << "4. After party" << endl; // mid energy + mid tempo
                    cout << "0. to stop the program" << endl;
                }
            }

            cout << "Family Friendly? (Y/N): " << endl;
            counter = 0;
            while (explicit_bool) {
                getline(cin,exp_option);
                if (check_string(exp_option)) {
                    if (exp_option == "Y") {
                        explicit_bool = false;
                        exp_cont = false;
                    }
                    else if (exp_option == "N") {
                        explicit_bool = false;
                        exp_cont = true;
                    }
                    else if(counter == 1) {
                        cout << "Please enter either Y or N." << endl;
                    }
                }
                counter = 1;
            }

            counter = 1;
            cout << "Insert year: (or \"0\" if all): " << endl;
            while (year_bool) {
                cin >> year_option;
                if (check_num_str(year_option, 4)) {
                    year_bool = false;
                    year = stoi(year_option);
                }
                else
                    counter++;
                if (counter % 3 == 0 && year_bool) {
                    cout << "Insert year: (or \"0\" if all): " << endl;
                }
            }

            counter = 1;
            cout << "How many songs? (10 - 50): " << endl;
            while (num_songs_bool) {
                cin >> num_songs_option;
                if (check_num_str(num_songs_option, 2)) {
                    num_songs = stoi(num_songs_option);
                    num_songs_bool = false;
                }
                else
                    counter++;
                if (counter % 3 == 0 && num_songs_bool) {
                    cout << "How many songs? (10 - 50): " << endl;
                }
            }

            if (result == 1)
                ReadCSV(p, "event", "dinner", exp_cont, year, "any");
            else if (result == 2)
                ReadCSV(p, "event", "party", exp_cont, year, "any");
            else if (result == 3)
                ReadCSV(p, "event", "workout", exp_cont, year, "any");
            else if (result == 4)
                ReadCSV(p, "event", "after party", exp_cont, year, "any");
            else {
                break;
            }

            auto start = chrono::high_resolution_clock::now();
            ShellSort(p.songs, p.songs.size());
            auto stop = chrono::high_resolution_clock::now();
            auto timeShell = chrono::duration_cast<chrono::microseconds>(stop - start);

            start = chrono::high_resolution_clock::now();
            p2.songs = MergeSort(p.songs);
            stop = chrono::high_resolution_clock::now();
            auto timeMerge = chrono::duration_cast<chrono::microseconds>(stop - start);

            cout << endl;
            if (num_songs_option != "all"){
                p2.PrintN(num_songs);
            }
            else
                p.PrintAll();
            p.songs.clear();
            result = 0;

            cout << "Merge Sort time: " << setprecision(3) << float(timeMerge.count())/1000.0 << " milliseconds" << endl;
            cout << "Shell Sort time: " << setprecision(3) << float(timeShell.count())/1000.0 << " milliseconds" << endl;

            cout << endl;
        }

            // Artist
        else if (result == 4){
            cout << "Enter Artist: " << endl;
            cin.ignore();
            getline(cin, artist);

            cout << "Family Friendly? (Y/N): " << endl;
            counter = 0;
            while (explicit_bool) {
                getline(cin,exp_option);
                if (check_string(exp_option)) {
                    if (exp_option == "Y") {
                        explicit_bool = false;
                        exp_cont = false;
                    }
                    else if (exp_option == "N") {
                        explicit_bool = false;
                        exp_cont = true;
                    }
                    else if(counter == 1) {
                        cout << "Please enter either Y or N." << endl;
                    }
                }
                counter = 1;
            }

            counter = 1;
            cout << "Insert year: (or \"0\" if all): " << endl;
            while (year_bool) {
                cin >> year_option;
                if (check_num_str(year_option, 4)) {
                    year_bool = false;
                    year = stoi(year_option);
                }
                else
                    counter++;
                if (counter % 3 == 0 && year_bool) {
                    cout << "Insert year: (or \"0\" if all): " << endl;
                }
            }

            counter = 1;
            cout << "How many songs? (10 - 50): " << endl;
            while (num_songs_bool) {
                cin >> num_songs_option;
                if (check_num_str(num_songs_option, 2)) {
                    num_songs = stoi(num_songs_option);
                    num_songs_bool = false;
                }
                else
                    counter++;
                if (counter % 3 == 0 && num_songs_bool) {
                    cout << "How many songs? (10 - 50): " << endl;
                }
            }

            ReadCSV(p, "artist", "any", exp_cont, year, artist);

            auto start = chrono::high_resolution_clock::now();
            ShellSort(p.songs, p.songs.size());
            auto stop = chrono::high_resolution_clock::now();
            auto timeShell = chrono::duration_cast<chrono::microseconds>(stop - start);

            start = chrono::high_resolution_clock::now();
            p2.songs = MergeSort(p.songs);
            stop = chrono::high_resolution_clock::now();
            auto timeMerge = chrono::duration_cast<chrono::microseconds>(stop - start);

            cout << endl;
            if (num_songs_option != "all"){
                p2.PrintN(num_songs);
            }
            else
                p.PrintAll();
            p.songs.clear();
            result = 0;

            cout << "Merge Sort time: " << setprecision(3) << float(timeMerge.count())/1000.0 << " milliseconds" << endl;
            cout << "Shell Sort time: " << setprecision(3) << float(timeShell.count())/1000.0 << " milliseconds" << endl;

            cout << endl;
        }
        cin.ignore();
    }
}
