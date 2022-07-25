#include<vector>
#include<utility>
#include<string>
#include<string.h>
using namespace std;

struct Transition
{
    string oldState;
    string newState;
    string oldSymbol;
    string newSymbol;
    string direction;
};

struct Tape
{
    string tape;
    int index_start;
    int index_end;
    int pointer;
};




class TuringMachine
{
private:
    vector<string> State;
    string startState;
    vector<string> inputSymbol;
    vector<string> tapeSymbol;
    string blankSymbol;
    vector<string> endState;
    int tapeCount;
    
    vector<Tape> setOfTape;

    vector<pair<string,vector<Transition>>> transFunc;
    bool isverbose;
    string currentState;
    bool successBuild;
    int stepCount;
public:
    TuringMachine(string setOfState,string setOfInput,string setOfTape,string startState,string blankSymbol,string setOfFinish,string numOfTape,vector<string> transfunc,bool isVerbose);
    string deleteExplanation(string str);
    void stringSplit(string str,int pos,string name);
    bool checkLegalTapeAndInput();
    bool checkStartstateAndFinishstateInState();
    bool isTM();
    void printState();
    void printTransitionFunc();
    bool checkinput(string inputString);
    void run(string inputString);
    Transition findNextMove();
    void moveToNext(Transition transition);
    void inVerboseMode();
    bool checktransition();
};