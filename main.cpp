/*
Election Data Parser

Author: Brian Reeder - [11/12/2024 - Present]
Contact: breed21@uic.edu - UIN: 651677051

Info: The goal of this project is to read in MIT .txt files that hold results from different recent elections.
the program takes in this info and organizes it into class objects. all of those objects are pushed into a
vector. a similar process is done to keep track of the candidates for a given election/file year.
a series of different options are given to the user which can be repeated.
*/

#include <iostream>
#include <iomanip>
#include <cctype>
#include <vector>
#include <fstream>
#include <string>
#include "Votes.h"      // includes the file with the Votes class mutators and accessors, constructors, etc..
#include "Candidates.h" // stores the class of type Candidates, which is used to store candidates (no repeats)
                        // their votes, and their party

using namespace std;

const string STATES[] = {"ALABAMA", "ALASKA", "ARIZONA", "ARKANSAS", "CALIFORNIA", "COLORADO",
                         "CONNECTICUT", "DELAWARE", "FLORIDA", "GEORGIA", "HAWAII", "IDAHO", "ILLINOIS",
                         "INDIANA", "IOWA", "KANSAS", "KENTUCKY", "LOUISIANA", "MAINE", "MARYLAND", "MASSACHUSETTS", "MICHIGAN",
                         "MINNESOTA", "MISSISSIPPI", "MISSOURI", "MONTANA", "NEBRASKA", "NEVADA", "NEW HAMPSHIRE", "NEW JERSEY",
                         "NEW MEXICO", "NEW YORK", "NORTH CAROLINA", "NORTH DAKOTA", "OHIO", "OKLAHOMA", "OREGON", "PENNSYLVANIA",
                         "RHODE ISLAND", "SOUTH CAROLINA", "SOUTH DAKOTA", "TENNESSEE", "TEXAS", "UTAH", "VERMONT", "VIRGINIA",
                         "WASHINGTON", "WASHINGTON DC", "WEST VIRGINIA", "WISCONSIN", "WYOMING"};
const int NUM_STATES = 51;

// prototypes for functions that appear below main, passed by reference so changes are reflected in main
void PushFileToVector(vector<Votes> &voteInfo);
void PushCandidatesToVector(vector<Votes> &voteInformation, vector<Candidates> &candidateList);

void DataOverview(vector<Votes> &voteInformation);
void NationalResults(vector<Votes> voteInformation, vector<Candidates> &candidateList);
void StateResults(vector<Votes> voteInformation, vector<Candidates> candidateList);
void CandidateResults(vector<Votes> voteInformation);
void CountyResults(vector<Votes> voteInformation);

void MainMenu(vector<Votes> &voteInformation, vector<Candidates> &candidateList);

int main()
{
    vector<Votes> voteInformation; // stores each separate entry from the entered file
    vector<Candidates> candidateList;

    PushFileToVector(voteInformation);                      // calls the function to read the file and store the entries
    PushCandidatesToVector(voteInformation, candidateList); // calls the function make a list of candidates

    MainMenu(voteInformation, candidateList); // calls the function that prompts the menu and calls all other functions
}

//----------------------[function space below]--------------------------------------------//

// this function is used to prompt the user for a menu input. it also calls all other functions based
// on user's choice. gets the two vectors from main by reference so they can be used in function calls.
// all changes made in the functions called here are reflected in this function, which is then reflected in main
void MainMenu(vector<Votes> &voteInformation, vector<Candidates> &candidateList)
{
    int choice = 1;

    // loop ends when the user input is 6
    do
    {
        cout << "\n\nSelect a menu option:" << endl;
        cout << "  1. Data overview" << endl;
        cout << "  2. National results" << endl;
        cout << "  3. State results" << endl;
        cout << "  4. Candidate results" << endl;
        cout << "  5. County search" << endl;
        cout << "  6. Exit" << endl;
        cout << "Your choice: ";

        // if input is invalid then the user is continously prompted
        do
        {
            cin >> choice;

            switch (choice)
            {
            case 1:
                DataOverview(voteInformation);
                break;
            case 2:
                NationalResults(voteInformation, candidateList);
                break;
            case 3:
                StateResults(voteInformation, candidateList);
                break;
            case 4:
                CandidateResults(voteInformation);
                break;
            case 5:
                CountyResults(voteInformation);
                break;
            case 6:
                break;
            default:
                break;
            }
        } while (choice > 6 || choice < 1);

    } while (choice != 6);
}

// this function is used to request a file, read said file, and organize the entries into the vector of type votes
// this is all done by reference so changes are reflected in main and after the function call ends, the memory is freed since these blocks are limited to the stack
void PushFileToVector(vector<Votes> &voteInfo)
{
    ifstream fileInput; // declares ifstream object to read in a file
    Votes tempObject;   // creates a temp. object of type Votes, this is done so data can be stored then added to the vector of Votes objects
    string tempString;

    cout << "\n |-------------| Election Data Parser |-------------|\n";
    cout << "\n_________________________________________________________";
    cout << "\nThe goal of this project is to read formatted MIT .txt  |\nfiles containing results from different elections.      |"
            "\nThe program parses the data and analyzes it in various  |\nways based on the user's input.                         |"
            "\n\t\tYou will now be prompted for a file.            |"
            "\n________________________________________________________/"
            "\n\n(Current supported options include votes-2012.txt, -2016.txt, and -2020.txt)\n\n";

    // prompt for file
    cout << "Enter file to use: ";
    cin >> tempString;
    cin.ignore();

    string fileDirection = "/Users/brianreeder/CLionProjects/Election-Data-Analysis/" + tempString; // for macOS version of program
    fileInput.open(fileDirection);

    int x = 1;
    // runs till the file ends
    while (!fileInput.eof())
    {

        // getline reads each line of the file using the fileInput object, it ignores commas
        // each getline is for a different data piece we want to store.
        getline(fileInput, tempString, ',');

        // accounts for eof bug where eof is not detected.
        // breaks the loop if empty lines are taken in trough input from file.
        if (tempString.empty())
        {
            break;
        }
        tempObject.setState(tempString);

        getline(fileInput, tempString, ',');
        tempObject.setCounty(tempString);

        getline(fileInput, tempString, ',');
        tempObject.setCandidate(tempString);

        getline(fileInput, tempString, ',');
        tempObject.setParty(tempString);

        // fileInput acts like cin, so it takes the last input stopping at whitespace, but the new line is stored in the buffer
        // the last getline below clears the newline character from the buffer
        fileInput >> tempString;
        tempObject.setVotes(tempString);

        // adds each temp object to a vector storing all objects of type Votes
        voteInfo.push_back(tempObject);

        getline(fileInput, tempString);
    }

    fileInput.close(); // closes file, which is only ever open during the beginning of the program
}

// this function is used to sift the stored entries and compile a list of candidates
// by reference so changes are reflected in main, (this saves memory as well!)
// this function also tallies the national votes and sorts the candidates based on those votes
void PushCandidatesToVector(vector<Votes> &voteInformation, vector<Candidates> &candidateList)
{
    unsigned int i;
    unsigned int j;

    Candidates tempObject;

    // the object is intialized with the first candidate from the first object stored in the vector of type Votes
    // the outer loop increments through every entry stored in the vector, each outer loop resets the count to 0
    // if the current Votes entry name is found in the vector of candidates, (using getName()), then the count is incremented
    // this keeps track of if a candidate is already in the list. else, the name and party are appended to the vector.
    tempObject.setName((voteInformation.at(0)).getCandidate());
    tempObject.setParty((voteInformation.at(0)).getParty());
    candidateList.push_back(tempObject);

    for (i = 0; i < voteInformation.size(); i++)
    {
        int count = 0;

        // compares the current entry at i with all the candidates stored in the type Candidates vector
        // if the candidate was already added then count is incremented- indicating the name and party should not be added again
        for (j = 0; j < candidateList.size(); j++)
        {
            if (((voteInformation.at(i)).getCandidate()) == (candidateList.at(j)).getName())
                count++;
        }

        // if count == 0 then the current entries' name and party are added to the temporary object
        // the object is then appended to the vector of type Candidates
        if (count == 0)
        {
            tempObject.setName((voteInformation.at(i)).getCandidate());
            tempObject.setParty((voteInformation.at(i)).getParty());
            candidateList.push_back(tempObject);
        }
    }

    // adds all votes from every entry into each candidates private members based on which name is detected
    // if the current iterated entry matches, then those votes are added to the data member with the same name
    for (i = 0; i < voteInformation.size(); i++)
    {
        for (j = 0; j < candidateList.size(); j++)
        {
            if ((voteInformation.at(i)).getCandidate() == (candidateList.at(j)).getName())
            {
                unsigned int votesFromEntry = stoi((voteInformation.at(i)).getVotes());
                (candidateList.at(j)).addVotesNat(votesFromEntry);
            }
        }
    }

    // bubble sort to swap the candidates and sort by most state votes, will implement as overloaded operator soon
    for (i = 0; i < candidateList.size() - 1; i++)
    {
        // Candidates tempObject;

        for (j = 0; j < (candidateList.size() - 1); j++)
        {
            if ((candidateList.at(j)).getVotesNat() < (candidateList.at(j + 1)).getVotesNat())
            {
                tempObject.setName((candidateList.at(j + 1)).getName());
                tempObject.setParty((candidateList.at(j + 1)).getParty());
                tempObject.setVotesNat((candidateList.at(j + 1)).getVotesNat());
                tempObject.setVotesState((candidateList.at(j + 1)).getVotesState());

                (candidateList.at(j + 1)).setName((candidateList.at(j)).getName());
                (candidateList.at(j + 1)).setParty((candidateList.at(j)).getParty());
                (candidateList.at(j + 1)).setVotesNat((candidateList.at(j)).getVotesNat());
                (candidateList.at(j + 1)).setVotesState((candidateList.at(j)).getVotesState());

                (candidateList.at(j)).setName(tempObject.getName());
                (candidateList.at(j)).setParty(tempObject.getParty());
                (candidateList.at(j)).setVotesNat(tempObject.getVotesNat());
                (candidateList.at(j)).setVotesState(tempObject.getVotesState());
            }
        }
    }
}

// this function is used to add up the votes from every entry for the grand total
void DataOverview(vector<Votes> &voteInformation)
{
    unsigned int totalVotes = 0;
    string temp;

    // increments through every entry, then takes the votes, turns it into a integer, and totals the votes
    for (unsigned int i = 0; i < voteInformation.size(); i++)
    {
        temp = (voteInformation.at(i)).getVotes();
        totalVotes += stoi(temp);
    }

    cout << "\n|=-=-=-=-=-=-=[ National Overview ]=-=-=-=-=-=-=|";
    cout << "\n Number of election records: " << voteInformation.size() << "\n Total number of votes recorded: " << totalVotes << endl;
    cout << "\n|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=|" << endl;
}

// prints out a formatted output of the national votes collected during the pushCandidateToVector function
// candidates are pre sorted
void NationalResults(vector<Votes> voteInformation, vector<Candidates> &candidateList)
{

    cout << "\n|=-=-=-=-=-=-=[ Popular Votes ]=-=-=-=-=-=-=|" << endl;
    for (int i = 0; i < candidateList.size(); i++)
    {
        cout << left << setw(20) << ((candidateList.at(i)).getName());
        cout << left << setw(15) << ((candidateList.at(i)).getParty());
        cout << right << setw(10) << ((candidateList.at(i)).getVotesNat());
        cout << endl;
    }
    cout << "\n|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=|" << endl;
}

// this function produces the state-wide results for every candidate in the form of tallies. one tally = 150,000 votes
// the votes are totaled, then divided by 150,000. int-division gives the total times 150,000 was counted in integers, and the
// decimal place indicates the leftover votes that are already divided by 150,000. comparing this leftover decimal
// to the decimal formed from dividing 80,000/150,000 allows us to see when the remainder is above 80,000 votes (out of 150,000)
void StateResults(vector<Votes> voteInformation, vector<Candidates> candidateList)
{
    string choice = "";
    unsigned int i;
    unsigned int j;
    const double roundingPoint = 80'000.0 / 150'000.0; // rounding point is used to deterimine if the remainder falls above 80,000

    cout << "Enter state: ";
    cin.ignore();
    getline(cin, choice);

    for (i = 0; i < choice.size(); i++)
    {
        choice.at(i) = toupper(choice.at(i));
    }

    // this for loop goes through all entries in the vote info vector. if the state at an entry is the same as
    // user input, then we carry on with the conditons. since it has been determined that the input is at
    // the entry, next we need to find the respective candidate at the entry, and add to their state-wide votes
    for (i = 0; i < voteInformation.size(); i++)
    {
        if (((voteInformation.at(i).getState() == choice)))
        {
            for (j = 0; j < candidateList.size(); j++)
            {
                if ((voteInformation.at(i)).getCandidate() == (candidateList.at(j)).getName())
                {
                    unsigned int stateVotesFromEntry = stoi((voteInformation.at(i)).getVotes());
                    (candidateList.at(j)).addVotesState(stateVotesFromEntry);
                }
            }
        }
    }

    // bubble sort to swap the candidates and sort by most state votes, will implement as overloaded operator soon
    for (i = 0; i < candidateList.size() - 1; i++)
    {
        Candidates tempObject;

        for (j = 0; j < (candidateList.size() - 1); j++)
        {
            if ((candidateList.at(j)).getVotesState() < (candidateList.at(j + 1)).getVotesState())
            {
                tempObject.setName((candidateList.at(j + 1)).getName());
                tempObject.setParty((candidateList.at(j + 1)).getParty());
                tempObject.setVotesNat((candidateList.at(j + 1)).getVotesNat());
                tempObject.setVotesState((candidateList.at(j + 1)).getVotesState());

                (candidateList.at(j + 1)).setName((candidateList.at(j)).getName());
                (candidateList.at(j + 1)).setParty((candidateList.at(j)).getParty());
                (candidateList.at(j + 1)).setVotesNat((candidateList.at(j)).getVotesNat());
                (candidateList.at(j + 1)).setVotesState((candidateList.at(j)).getVotesState());

                (candidateList.at(j)).setName(tempObject.getName());
                (candidateList.at(j)).setParty(tempObject.getParty());
                (candidateList.at(j)).setVotesNat(tempObject.getVotesNat());
                (candidateList.at(j)).setVotesState(tempObject.getVotesState());
            }
        }
    }

    cout << "\n|=-=-=-=-=-=-=[ State Votes in 150,000's ]=-=-=-=-=-=-=|" << endl;
    // prints out the sorted tallies based on amounts of 150,000
    for (i = 0; i < candidateList.size(); i++)
    {
        int votesFromState = (candidateList.at(i)).getVotesState();         // stores value of total state votes for specific candidate
        int tallyAmount = votesFromState / 150000;                          // gets tally amount with int division ("full" values of 150,000)
        double tallyRemainder = (votesFromState / 150'000.0) - tallyAmount; // finds the remainder by subtracting the full amount from version containing the remainder in decimal format

        cout << left << setw(20) << ((candidateList.at(i)).getName());

        for (j = 0; j < tallyAmount; j++)
        {
            cout << "|";
        }
        // if the remainder >= .5333, AKA "roundingPoint", then the remainder is more than 80,000 votes and can be rounded up
        if (tallyRemainder >= roundingPoint)
            cout << "|";

        cout << endl;
    }
    cout << "\n|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|" << endl;
}

// this function is used to calculate the candidate's results from every state. the name input is found and
// all votes in the state relating to that name are counted. all general state votes are also counted. at the end
// of the loop, the percetange of votes received out of total state votes is computed in the form of a percent
// the best percent overall is kept track of and output at the end of the function call
void CandidateResults(vector<Votes> voteInformation)
{
    string name;
    string bestState;
    double bestPercent = 0.0;

    cout << "Enter candidate: ";
    cin.ignore();
    getline(cin, name);

    for (int i = 0; i < name.size(); i++)
    {
        name.at(i) = toupper(name.at(i));
    }

    // uses .find() function to search for the user's input. first time it detects, the loop is broken to ease run time
    // stores the candidates name in the .txt file's format for easy searching below
    for (int i = 0; i < voteInformation.size(); i++)
    {
        string fullName = (voteInformation.at(i)).getCandidate();

        if (fullName.find(name) != string::npos)
        {
            // cout << "\nname: " << (voteInformation.at(i)).getCandidate() << " | state: " << (voteInformation.at(i)).getState();
            name = fullName;
            cout << endl;
            break;
        }
    }

    cout << "\n|=-=-=-=-=-=-=[ Candidate Results ]=-=-=-=-=-=-=|" << endl;
    // this loop increments through all the states. the total votes, candidate votes, and percentage are found and output
    for (int i = 0; i < NUM_STATES; i++)
    {

        int candidateVotes = 0;
        int totalVotes = 0;
        double percent;

        for (int j = 0; j < voteInformation.size(); j++)
        {
            if (STATES[i] == (voteInformation.at(j)).getState())
            {
                totalVotes += stoi((voteInformation.at(j)).getVotes());

                if (name == (voteInformation.at(j)).getCandidate())
                    candidateVotes += stoi((voteInformation.at(j)).getVotes());
            }
        }
        percent = 100.0 * (static_cast<double>(candidateVotes) / totalVotes);

        if (percent >= bestPercent)
        {
            bestPercent = percent;
            bestState = STATES[i];
        }

        cout << left << setw(20) << STATES[i];
        cout << right << setw(10) << candidateVotes << right << setw(10) << totalVotes;
        cout << right << setw(7) << fixed << setprecision(1) << percent << "%";

        cout << endl;
    }
    cout << "\nThe best state for " << name << " is " << bestState << endl;
    cout << "\n|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=|" << endl;
}

// this function acts similarly to the previous one. a county is entered and the input is saved. the entries vector
// is then scanned and if the county is found in the file, it is grabbed, then its votes and candidate are output as well
void CountyResults(vector<Votes> voteInformation)
{
    string county;
    cout << "Enter county: ";
    cin.ignore();
    getline(cin, county);

    for (int i = 0; i < county.size(); i++)
    {
        county.at(i) = toupper(county.at(i));
    }

    cout << "\n|=-=-=-=-=-=-=-=-=-=-=-=-=[ County Results ]=-=-=-=-=-=-=-=-=-=-=-=-=|" << endl;
    // this for loop simply stores each entries values for outputting and concatenation of the location strings
    for (int i = 0; i < voteInformation.size(); i++)
    {
        string fullCounty = (voteInformation.at(i)).getCounty();
        string state = (voteInformation.at(i)).getState();
        string candidate = (voteInformation.at(i)).getCandidate();
        string votes = (voteInformation.at(i)).getVotes();
        string location = fullCounty + ", " + state;

        if (fullCounty.find(county) != string::npos)
        {
            cout << left << setw(40) << location;
            cout << left << setw(20) << candidate;
            cout << right << setw(10) << votes << endl;
        }
    }
    cout << "\n|=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=|" << endl;
}
