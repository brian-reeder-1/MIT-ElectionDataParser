#pragma once
#include <string>
#include <iostream>

// this class is used to creat objects that store candidate info. the objects can be pushed into a vector and
// used for functions as well. this class is used for searching for candidates and counting state votes
class Candidates{
    public:
        Candidates(void);
        bool operator<(Candidates rhs); //overloaded operator

        void setName(string nameFromMain);
        void setParty(string partyFromMain);
        void setVotesNat(unsigned int nationalVotesFromMain);
        void addVotesNat(unsigned int nationalVotesFromMain);
        void setVotesState(unsigned int stateVotesFromMain);
        void addVotesState(unsigned int stateVotesFromMain); //used to sum votes


        string getName();
        string getParty();
        unsigned int getVotesNat();
        unsigned int getVotesState();

    private:
        string name;
        string party;
        unsigned int nationalVotes;
        unsigned int stateVotes;
};

// default constructor
Candidates::Candidates(void){
    name = "";
    party = "";
    nationalVotes = 0;
    stateVotes = 0;
}

/* overloaded operator for <, allows the use of sort with the class type Candidate to order number of votes
bool Candidates::operator<(Candidates rhs){
    if(nationalVotes < rhs.nationalVotes)
        return false;
    else
        return true;
}*/

void Candidates::setName(string nameFromMain){
    name = nameFromMain;
}
void Candidates::setParty(string partyFromMain){
    party = partyFromMain;
}

void Candidates::setVotesNat(unsigned int nationalVotesFromMain){
    nationalVotes = nationalVotesFromMain;
}
void Candidates::addVotesNat(unsigned int nationalVotesFromMain){
    nationalVotes += nationalVotesFromMain;
}

void Candidates::setVotesState(unsigned int stateVotesFromMain){
    stateVotes = stateVotesFromMain;
}
void Candidates::addVotesState(unsigned int stateVotesFromMain){
    stateVotes += stateVotesFromMain;
}

string Candidates::getName(){
    return name;
}
string Candidates::getParty(){
    return party;
}
unsigned int Candidates::getVotesNat(){
    return nationalVotes;
}
unsigned int Candidates::getVotesState(){
    return stateVotes;
}