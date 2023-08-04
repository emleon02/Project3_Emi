#include <stdexcept>
#include "song.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void Playlist::Insert(Song* song, const string& option, const string& adj, bool exp, int year, const string& artist){
    if ((!exp && song->exp) || (artist != "any" && artist != song->artist)){
        delete song;
        return;
    }

    // Check if the songs year is within the decade inserted by user
    else if (option == "decade") {
        int lower = ((song->year % 100) / 10) * 10;
        int upper = lower + 10;
        if (year%100 >= lower && year%100 <= upper) {
            song->rating = song->tempo + song->dance + song->energy;
            songs.push_back(song);
        }
    }
    else if (year == 0 || year == song->year) {
        if (option == "mood") {
            if (adj == "happy" && song->tempo >= 120 && song->tempo <= 140 && song->dance >= 70 && song->energy >= 50 &&
                song->energy <= 90 && song->valence >= 70 && song->valence <= 90 && song->mode == 1 && song->loud >= -20) {
                song->rating = song->tempo + song->dance + song->energy;
                songs.push_back(song);
            } else if (adj == "sad" && song->tempo >= 50 && song->tempo <= 80 && song->energy <= 40 && song->dance <= 40 &&
                song->valence <= 40 && song->mode == 0 && song->loud <= -30) {
                song->rating = 180 - song->tempo + (100 - song->loud) + (100 - song->dance) + (100 - song->energy);
                songs.push_back(song);
            } else if (adj == "relaxed" && song->tempo >= 60 && song->tempo <= 90 && song->energy >= 10 && song->energy <= 50 &&
                song->dance <= 40 && song->loud >= -40 && song->loud <= -20 && song->valence >= 30 && song->valence <= 70 && song->mode == 0) {
                song->rating = 180 - song->tempo + (100 - song->loud) + (100 - song->dance) + (100 - song->energy);
                songs.push_back(song);
            } else if (adj == "victory" && song->tempo >= 120 && song->tempo <= 140 && song->valence >= 70 && song->energy >= 50 &&
                song->energy <= 90 && song->dance >= 70 && song->mode == 1 && song->loud >= -20) {
                song->rating = song->tempo + song->dance + song->energy;
                songs.push_back(song);
            } else if (adj == "angry" && song->tempo >= 130 && song->valence <= 60 && song->valence >= 30 && song->energy >= 50 &&
                song->energy >= 70 && song->dance >= 70 && song->loud >= -10) {
                song->rating = song->tempo + song->dance+ song->energy + song->loud;
                songs.push_back(song);
            } else if (adj == "sleepy" && song->tempo >= 40 && song->tempo <= 70 && song->dance <= 30 &&
                song->energy <= 30 && song->loud <= -30 && song->loud >= -60){
                song->rating = (180 - song->tempo) + (100 - song->dance) + (100 - song->energy);
                songs.push_back(song);
            }
        } else if (option == "event") {
            if (adj == "dinner" && song->tempo >= 50 && song->tempo <= 90 && song->dance <= 50 && song->energy >= 40 && song->loud >= -40 && song->loud <= -20) {
                    song->rating = 180 - song->tempo + (100 - song->loud) + (100 - song->dance) + (100 - song->energy);
                songs.push_back(song);
            } else if (adj == "party" && song->tempo >= 120 && song->energy >= 80 && song->dance >= 80 && song->valence >= 80 && song->loud >= -20 && song->mode == 1) {
                song->rating = song->tempo + song->dance + song->energy;
                songs.push_back(song);
            } else if (adj == "workout" && song->tempo >= 130 && song->tempo <= 150 && song->valence >= 50 && song->valence <= 90 &&
                song->energy >= 70 && song->dance >= 50 && song->dance <= 90 && song->loud >= -10 && song->mode == 1) {
                song->rating = song->tempo + song->dance + song->energy  + song->loud ;
                songs.push_back(song);
            } else if (adj == "after party" && song->tempo >= 90 && song->tempo <= 120 && song->dance >= 50 && song->dance <= 80 &&
                song->energy <= 80 && song->energy >= 40 && song->valence >= 30 && song->valence <= 80 && song->loud >= -20) {
                song->rating = song->tempo + song->dance + song->energy ;
                songs.push_back(song);
            }
            else if (adj == "studying" && song->tempo <= 100 && song->tempo >= 60 && song->dance <= 40 && song->dance >= 10 &&
                song->energy >= 10 && song->energy <= 50 && song->loud >= -40 && song->loud <= -20){
                song->rating = (180 - song->tempo) + (100 - song->dance) + (100 - song->energy);
                songs.push_back(song);
            }
        } else if (option == "artist") {
            song->rating = song->tempo;
            songs.push_back(song);
        }
    }

    else
        delete song;
}

void Playlist::PrintAll(){
    if (songs.empty()){
        cout << "Sorry! No applicable songs :(" << endl << endl;
        return;
    }
    cout << "Your playlist has " << songs.size() << " songs!" << endl << endl;
    for (const auto& i : songs){
        cout << "Title: " << i->name << endl;
        cout << "Artist: " << i->artist << endl;
        cout << "Album: " << i->album << endl << endl;
    }

}

void Playlist::PrintN(int n){
    if (songs.empty()){
        cout << "Sorry! No applicable songs :(" << endl << endl;
        return;
    }
    if (n > songs.size()){
        cout << "Your playlist has " << songs.size() << " songs!" << endl;

        for (int i = songs.size() - 1; i > 0; i--) {
            cout << "Title: " << songs[i]->name << endl;
            cout << "Artist: " << songs[i]->artist << endl;
            cout << "Album: " << songs[i]->album << endl << endl;
        }
    }
    else{
        cout << "Your playlist has " << n << " songs!" << endl;

        for (int i = n - 1; i > 0; i--){
            cout << "Title: " << songs[i]->name << endl;
            cout << "Artist: " << songs[i]->artist << endl;
            cout << "Album: " << songs[i]->album << endl << endl;

        }
    }

}

void Song::Deserialize(istringstream& stream) {
    string token;
    getline(stream, token, ','); // ignore id

    getline(stream, this->name, ',');
    while (name[0] == '\"' && name[name.size() - 1] != '\"'){
        getline(stream, token, ',');
        name += token;
    }
    name.erase(0, 1);
    name.erase(name.size() - 2, 1);

    getline(stream, this->album, ',');
    while (album[0] == '\"' && album[album.size() - 1] != '\"'){
        getline(stream, token, ',');
        album += token;
    }
    album.erase(0, 1);
    album.erase(album.size() - 2, 1);

    getline(stream, token, ','); // ignore album id

    getline(stream, token, ',');
    try{
        this->artist = token;
        while (this->artist[artist.size() - 1] != ']'){
            getline(stream, token, ',');
            this->artist += token;
        }
        artist.erase(0, 2);
        artist.erase(artist.size() - 3, 2);
    }
    catch (out_of_range&){
        this->artist = "null";
    }
    getline(stream, token, ','); // ignore artist id

    getline(stream, token, ','); // ignore track num

    getline(stream, token, ','); // ignore disk num

    getline(stream, token, ',');

    if (token.size() == 4){
        this->exp = true;
    }
    else
        this->exp = false;

    getline(stream, token, ',');

    try{
        this->dance = int(stod(token) * 100);
    }
    catch (invalid_argument&){
        this->dance = 0;
    }

    getline(stream, token, ','); // ignore artist id

    try{
        this->energy = int(stod(token) * 100);
    }
    catch (invalid_argument&){
        this->energy = 0;
    }

    getline(stream, token, ',');

    try{
        this->key = stoi(token);
    }
    catch (invalid_argument&){
        this->key = 0;
    }

    getline(stream, token, ',');

    try{
        this->loud = stoi(token);
    }
    catch (invalid_argument&){
        this->loud = 0;
    }

    getline(stream, token, ',');
    try{
        this->mode = stoi(token);
    }
    catch (invalid_argument&){
        this->mode = -1;
    }

    getline(stream, token, ',');
    // ignore speece

    getline(stream, token, ',');

    getline(stream, token, ',');

    getline(stream, token, ',');

    getline(stream, token, ',');

    try{
        this->valence = int(stod(token) * 100);
    }
    catch (invalid_argument&){
        this->valence = 0;
    }

    getline(stream, token, ',');
    try{
        this->tempo = stoi(token);
    }
    catch (invalid_argument&){
        this->tempo = 0;
    }


    getline(stream, token, ',');
    // ignore duration

    getline(stream, token, ',');

    getline(stream, token, ',');
    try{
        this->year = stoi(token);
    }
    catch (invalid_argument&){
        this->year = 0;
    }

    getline(stream, token, ',');
}

Playlist::~Playlist(){
    for (auto& i : songs){
        delete i;
    }

}
