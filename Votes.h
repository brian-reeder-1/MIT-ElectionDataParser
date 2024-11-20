#pragma once
#include <string>
#include <iostream>

using namespace std;

// this class reads in the "entries" from the .txt files. the entries are sorted into the private members:
    // state, county, candidate, political party, and votes
// objects can be made under this type and stored in a vector. this allows the copying of a whole file and saving its
// data for menu functions. // the functions include: finding the total number of votes/entries, finding the winner of the popular vote,
    // tallying the votes for candidates, finding the percentage of votes a candidate earned, and finding
    // votes by county.
class Votes{

    public:
        // member function declarations
        Votes(void);

        void setState(string);
        string getState(void);

        void setCounty(string);
        string getCounty(void);

        void setCandidate(string);
        string getCandidate(void);

        void setParty(string);
        string getParty(void);

        void setVotes(string);
        string getVotes(void);

    private:
        string state;
        string county;
        string candidate;
        string politicalParty;
        string votes;
};

// default constructor
Votes::Votes(void){
    state = "";
    county = "";
    candidate = "";
    politicalParty = "";
    votes = "";
}

// setters and getters, pretty self explanatory
void Votes::setState(string stateFromMain){
    state = stateFromMain;
}
void Votes::setCounty(string countyFromMain){
    county = countyFromMain;
}
void Votes::setCandidate(string candFromMain){
    candidate = candFromMain;
}
void Votes::setParty(string partyFromMain){
    politicalParty = partyFromMain;
}
void Votes::setVotes(string votesFromMain){
    votes = votesFromMain;
}

string Votes::getState(){
    return state;
}
string Votes::getCounty(){
    return county;
}
string Votes::getCandidate(){
    return candidate;
}
string Votes::getParty(){
    return politicalParty;
}
string Votes::getVotes(){
    return votes;
}
