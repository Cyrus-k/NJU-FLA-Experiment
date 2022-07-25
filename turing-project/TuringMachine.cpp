#include<iostream>
#include"TuringMachine.h"
using namespace std;

string TuringMachine::deleteExplanation(string str){
    int length = str.length();
    int pos = length;
    for(int i = 0;i < length;i++){
        if(str[i] == ';'){
            pos = i;
            break;
        }
    }
    string result = str.substr(0,pos);
    return result;
}

void TuringMachine::printState(){
    for(int i=0;i<State.size();i++){
        cout<<State[i];
    }
    cout<<endl;
}

void TuringMachine::stringSplit(string str,int pos,string name){
    
    for(int i=0;i<str.length();i++){
        if(str[i] == '}'){
            str = str.substr(0,i);
            break;
        }
    }
    
    char* command =new char[str.length()+1];
    str.copy(command,str.length()-pos,pos);
    *(command + str.length()-pos) = '\0';
    /*for(int i=0;command[i]!='\0';i++){
        cout<<command[i];
    }
    cout<<endl;*/
    char*Partofcommand;
    Partofcommand = strtok(command,",");
    if (name == "setOfState"){
        while(Partofcommand != NULL){
            string temp = Partofcommand;
            //cout<<temp<<endl;
            if (temp[temp.length()-1] == '}'){
                temp = temp.substr(0,temp.length()-1);
            }
            State.push_back(temp);
            Partofcommand = strtok(NULL,",");
        }
    }
    else if(name == "setOfInput"){
        while(Partofcommand != NULL){
            string temp = Partofcommand;
            //cout<<temp<<endl;
            if (temp[temp.length()-1] == '}'){
                temp = temp.substr(0,temp.length()-1);
            }
            inputSymbol.push_back(temp);
            Partofcommand = strtok(NULL,",");
        }

    }
    else if(name == "setOfTape"){
        while(Partofcommand != NULL){
            string temp = Partofcommand;
            //cout<<temp<<endl;
            if (temp[temp.length()-1] == '}'){
                temp = temp.substr(0,temp.length()-1);
            }
            tapeSymbol.push_back(temp);
            Partofcommand = strtok(NULL,",");
        }
    }
    else if(name == "setOfFinish"){
        while(Partofcommand != NULL){
            string temp = Partofcommand;
            //cout<<temp<<endl;
            if (temp[temp.length()-1] == '}'){
                temp = temp.substr(0,temp.length()-1);
            }
            endState.push_back(temp);
            Partofcommand = strtok(NULL,",");
        }
    }
}

TuringMachine::TuringMachine(string setOfState,string setOfInput,string setOfTape,string StartState,string BlankSymbol,string setOfFinish,string numOfTape,vector<string> transfunc,bool isVerbose){
    successBuild = true;
    isverbose = isVerbose;
    setOfState = deleteExplanation(setOfState);
    setOfInput = deleteExplanation(setOfInput);
    setOfTape = deleteExplanation(setOfTape);
    setOfFinish = deleteExplanation(setOfFinish);
    StartState = deleteExplanation(StartState);
    BlankSymbol = deleteExplanation(BlankSymbol);
    numOfTape = deleteExplanation(numOfTape);
    int length = transfunc.size();
    //cout<<setOfState<<endl;
    //cout<<setOfInput<<endl;
    string lineBeginning;
    if (setOfState.length()>=6){
        lineBeginning = setOfState.substr(0,6);
        if(lineBeginning == "#Q = {"){
            string name = "setOfState";
            stringSplit(setOfState,6,name);
        }
        else{
            successBuild = false;
        }
    }
    else{
        successBuild = false;
    }
    //printState();

    if (setOfInput.length()>=6){
        lineBeginning = setOfInput.substr(0,6);
        if(lineBeginning == "#S = {"){
            string name = "setOfInput";
            stringSplit(setOfInput,6,name);
        }
        else{
            successBuild = false;
        }
    }
    else{
        successBuild = false;
    }
    /*for(int i=0;i<inputSymbol.size();i++){
        cout<<inputSymbol[i]<<endl;
    }*/

    if (setOfTape.length()>=6){
        lineBeginning = setOfTape.substr(0,6);
        if(lineBeginning == "#G = {"){
            string name = "setOfTape";
            stringSplit(setOfTape,6,name);
        }
        else{
            successBuild = false;
        }
    }
    else{
        successBuild = false;
    }

    if (setOfFinish.length()>=6){
        lineBeginning = setOfFinish.substr(0,6);
        if(lineBeginning == "#F = {"){
            string name = "setOfFinish";
            stringSplit(setOfFinish,6,name);
        }
        else{
            successBuild = false;
        }
    }
    else{
        successBuild = false;
    }

    if (StartState.length()>=7){
        lineBeginning = StartState.substr(0,6);
        if(lineBeginning == "#q0 = "){
            startState = StartState.substr(6,StartState.length()-6);
            int pos = startState.length();
            for(int j=0;j<startState.length();j++){
                if(startState[j]==' '){
                    pos = j;
                    break;
                }
            }
            startState = startState.substr(0,pos);
            //cout<<startState<<endl;
            currentState = startState;
        }
        else{
            successBuild = false;
        }
    }
    else{
        successBuild = false;
    
    }

    if (BlankSymbol.length()>=6){
        lineBeginning = BlankSymbol.substr(0,5);
        if(lineBeginning == "#B = "){
            blankSymbol = BlankSymbol.substr(5,BlankSymbol.length()-5);
            //cout<<blankSymbol<<endl;
            if(blankSymbol != "_"){
                successBuild = false;
            }
        }
        else{
            successBuild = false;
        }
    }
    else{
        successBuild = false;
    }
    
    if (numOfTape.length()>=6){
        lineBeginning = numOfTape.substr(0,5);
        if(lineBeginning == "#N = "){
            tapeCount = 0;
            
            string num = numOfTape.substr(5,numOfTape.length()-5);
            int pos = num.length();
            for(int j=0;j<num.length();j++){
                if(num[j]==' '){
                    pos = j;
                    break;
                }
            }
            num = num.substr(0,pos);

            for(int i = 0;i<num.length();i++){
                tapeCount = tapeCount*10 + (num[i]-'0');
            }
        }
        else{
            successBuild = false;
        }
    }
    else{
        successBuild = false;
    }
    //cout<<tapeCount<<endl;

    int numofstate = State.size();
    pair<string,vector<Transition>>* group = new pair<string,vector<Transition>> [numofstate];
    for (int i =0;i<numofstate;i++){
        group[i].first = State[i];
        //cout<<group[i].first<<endl;
    }

    for(int i=0;i<transfunc.size();i++){
        string temp = deleteExplanation(transfunc[i]);
        Transition func;
        char* command =new char[temp.length()+1];
        temp.copy(command,temp.length(),0);
        *(command + temp.length()) = '\0';
        command = strtok(command," ");
        if(command!=NULL){
            func.oldState = command;
            command = strtok(NULL," ");
            if(command!=NULL){
                func.oldSymbol = command;
                command = strtok(NULL," ");
                if(command!=NULL){
                    func.newSymbol = command;
                    command = strtok(NULL," ");
                    if(command!=NULL){
                        func.direction = command;
                        command = strtok(NULL," ");
                        if(command!=NULL){
                            func.newState= command;
                            command = strtok(NULL," ");
                            if(command!=NULL){
                                successBuild = false;
                                break;
                            }
                            else{
                                bool istransitionfunc = false;
                                for(int j =0;j<numofstate;j++){
                                    if(group[j].first == func.oldState){
                                        group[j].second.push_back(func);
                                        istransitionfunc = true;
                                        break;
                                    }
                                }
                                if(!istransitionfunc){
                                    successBuild = false;
                                    break;
                                }
                            }
                        }
                        else{
                            successBuild = false;
                            break;
                        }
                    }
                    else{
                        successBuild = false;
                        break;
                    }
                }
                else{
                    successBuild = false;
                    break;
                }
            }
            else{
                successBuild = false;
                break;
            }
        }
        else{
            successBuild = false;
            break;
        }
    }
    for(int i=0;i<numofstate;i++){
        transFunc.push_back(group[i]);
    }
    if (!checkStartstateAndFinishstateInState()||!checkLegalTapeAndInput()||!checktransition()){
        successBuild = false;
    }
    //printTransitionFunc();
}

bool TuringMachine::checktransition(){
    for(int i=0;i<transFunc.size();i++){
        for(int j=0;j<transFunc[i].second.size();j++){
            bool checkoldstate = false;
            bool checknewstate = false;
            for(int k=0;k<State.size();k++){
                if(transFunc[i].second[j].oldState == State[k]){
                    checkoldstate = true;
                }
                if(transFunc[i].second[j].newState == State[k]){
                    checknewstate = true;
                }
            }
            if((!checknewstate)||(!checkoldstate)){
                return false;
            }
            else{
                bool checkdirection = false;
                string Direction = transFunc[i].second[j].direction;
                for(int n=0;n<Direction.length();n++){
                    if((Direction[n] == 'l')||(Direction[n] == 'r')||(Direction[n] == '*')){
                        checkdirection = true;
                    }
                    else{
                        checkdirection = false;
                        break;
                    }
                }
                if(checkdirection){
                    //bool checknewsym = false;
                    string newsym = transFunc[i].second[j].newSymbol;
                    for(int t=0;t<newsym.length();t++){
                        bool isintape = false;
                        for(int m = 0;m<tapeSymbol.size();m++){
                            if(newsym[t]==tapeSymbol[m][0]){
                                isintape = true;
                            }
                        }
                        if(!isintape){
                            return false;
                        }
                    }

                }
                else{
                    return false;
                }
            }
        }
    }
    return true;
}

bool TuringMachine::isTM(){
    return successBuild;
}

void TuringMachine::printTransitionFunc(){
    cout<<"good\n";
    for(int i=0;i<transFunc.size();i++){
        cout<<transFunc[i].first<<endl;
        for(int j = 0;j<transFunc[i].second.size();j++){
            cout<<transFunc[i].second[j].oldState<<" "<<transFunc[i].second[j].oldSymbol<<" "<<transFunc[i].second[j].newSymbol<<" "<<transFunc[i].second[j].direction<<" "<<transFunc[i].second[j].newState<<endl;

        }
    }
}

bool TuringMachine::checkLegalTapeAndInput(){
    for(int i=0;i<tapeSymbol.size();i++){
        for(int j=0;j<tapeSymbol[i].length();j++){
            if((tapeSymbol[i][j]==' ')||(tapeSymbol[i][j]==',')||(tapeSymbol[i][j]==';')||(tapeSymbol[i][j]=='{')||(tapeSymbol[i][j]=='}')||(tapeSymbol[i][j]=='*')){
                return false;
            }
        }
    }
    for(int i=0;i<inputSymbol.size();i++){
        bool ischeck = false;
        for(int j=0;j<tapeSymbol.size();j++){
            if(inputSymbol[i] == tapeSymbol[j]){
                ischeck = true;
                
            }
        }
        if(!ischeck){
            return false;
        }
    }
    return true;
}

bool TuringMachine::checkStartstateAndFinishstateInState(){
    bool startstatein = false;
    for (int i=0;i<State.size();i++){
        if(startState == State[i]){
            startstatein = true;
            break;
        }
    }
    if(!startstatein){
        return false;
    }
    for(int i=0;i<endState.size();i++){
        bool finishin = false;
        for(int j=0;j<State.size();j++){
            if(endState[i]==State[j]){
                finishin = true;
            }
        }
        if(!finishin){
            return false;
        }
    }
    return true;
}

bool TuringMachine::checkinput(string InputString){
    int pos=-1;
    for(int i=0;i<InputString.length();i++){
        bool notinInput = false;
        for(int j=0;j<inputSymbol.size();j++){
            if(InputString[i] == inputSymbol[j][0]){
                notinInput = true;
            }
        }
        if(!notinInput){
            pos = i;
            break;
        }
    }
    if(pos<0){
        if(isverbose){
            string res = "Input: ";
            res = res + InputString;
            cout<<res<<endl;
            cout<<"==================== RUN ====================\n";
        }
        return true;
    }
    else{
        if(isverbose){
            string res = "Input: ";
            res = res + InputString;
            cout<<res<<endl;
            cout<<"==================== ERR ====================\n";
            string err = "error: '";
            err.push_back(InputString[pos]);
            err = err + "' was not declared in the set of input symbols";
            cout<<err<<endl;
            cout<<res<<endl;
            string blank = "       ";
            for(int i=0;i<pos;i++){
                blank.push_back(' ');
            }
            blank.push_back('^');
            cout<<blank<<endl;
            cout<<"==================== END ====================\n";
        }
        else{
            cout<<"illegal input\n";
        }
        return false;
    }
}

Transition TuringMachine::findNextMove(){
    string currentSymbol="";
    for(int i=0;i<tapeCount;i++){
        currentSymbol.push_back(setOfTape[i].tape[setOfTape[i].pointer-setOfTape[i].index_start]);
    }
    //cout<<currentState<< "   "<<currentSymbol<<"   \n";
    Transition temp;
    temp.oldState = "notfound";
    for(int i=0;i<transFunc.size();i++){
        if(transFunc[i].first == currentState){
            for(int j=0;j<transFunc[i].second.size();j++){
                if(transFunc[i].second[j].oldSymbol == currentSymbol){
                    temp = transFunc[i].second[j];
                    break;
                }
            }
        }
    }
    return temp;

}

void TuringMachine::moveToNext(Transition transition){
    currentState = transition.newState;
    string newsymbol = transition.newSymbol;
    string direction = transition.direction;
    for(int i=0;i<tapeCount;i++){
        setOfTape[i].tape[setOfTape[i].pointer-setOfTape[i].index_start] = newsymbol[i];
        int oldpointer = setOfTape[i].pointer;
        if(direction[i] == 'l'){
            setOfTape[i].pointer--;
        }
        else if(direction[i]=='r'){
            setOfTape[i].pointer++;
        }
        else if(direction[i]=='*'){
            ;
        }
        if(setOfTape[i].pointer > setOfTape[i].index_end){
            setOfTape[i].tape.push_back('_');
            setOfTape[i].index_end = setOfTape[i].pointer;
        }
        if(setOfTape[i].pointer < setOfTape[i].index_start){
            string newb = "_";
            newb = newb + setOfTape[i].tape;
            setOfTape[i].tape = newb;
            setOfTape[i].index_start = setOfTape[i].pointer;
        }
        if((setOfTape[i].pointer>=setOfTape[i].index_start)&&(setOfTape[i].pointer<=setOfTape[i].index_end)){
            if(setOfTape[i].pointer==setOfTape[i].index_start){
                int pos = -1;
                bool findblank = false;
                for(int j=1;j<setOfTape[i].tape.length();j++){
                    if(setOfTape[i].tape[j]=='_'){
                        findblank = true;
                        pos = j;
                    }
                    else{
                        findblank = false;
                        pos = -1;
                    }
                }
                if(findblank){
                    setOfTape[i].index_end = setOfTape[i].index_start + pos-1;
                    setOfTape[i].tape = setOfTape[i].tape.substr(0,setOfTape[i].index_end-setOfTape[i].index_start+1);
                }
            }
            else if(setOfTape[i].pointer==setOfTape[i].index_end){
                int pos = -1;
                bool findblank = false;
                for(int j=setOfTape[i].tape.length()-2;j>=0;j--){
                    if(setOfTape[i].tape[j]=='_'){
                        findblank = true;
                        pos = j;
                    }
                    else{
                        findblank = false;
                        pos = -1;
                    }
                }
                if(findblank){//leng= leng-pos-1 end-start = leng-1 start =end-leng+1
                    setOfTape[i].index_start = setOfTape[i].index_end + pos + 2 - setOfTape[i].tape.length();
                    setOfTape[i].tape = setOfTape[i].tape.substr(pos+1,setOfTape[i].index_end-setOfTape[i].index_start+1);
                }
            }
            else{
                int pos = -1;
                bool findblank = false;
                for(int j=setOfTape[i].pointer-setOfTape[i].index_start+1;j<setOfTape[i].tape.length();j++){
                    if(setOfTape[i].tape[j]=='_'){
                        findblank = true;
                        pos = j;
                    }
                    else{
                        findblank = false;
                        pos = -1;
                    }
                }
                if(findblank){
                    setOfTape[i].index_end = setOfTape[i].index_start + pos-1;
                    setOfTape[i].tape = setOfTape[i].tape.substr(0,setOfTape[i].index_end-setOfTape[i].index_start+1);
                }
                for(int j=setOfTape[i].pointer-setOfTape[i].index_start-1;j>=0;j--){
                    if(setOfTape[i].tape[j]=='_'){
                        findblank = true;
                        pos = j;
                    }
                    else{
                        findblank = false;
                        pos = -1;
                    }
                }
                if(findblank){//leng= leng-pos-1 end-start = leng-1 start =end-leng+1
                    setOfTape[i].index_start = setOfTape[i].index_end + pos + 2 - setOfTape[i].tape.length();
                    setOfTape[i].tape = setOfTape[i].tape.substr(pos+1,setOfTape[i].index_end-setOfTape[i].index_start+1);
                }
            }
        }
    }

}

void TuringMachine::inVerboseMode(){
    cout<<"Step   : "<<stepCount<<endl;
    for (int i=0;i<tapeCount;i++){
        string index = "Index";
        string TaPe = "Tape";
        string Head = "Head";
        int t = i/10;
        if(t==0){
            index.push_back((char)(i+'0'));
            index.push_back(' ');
            index.push_back(':');
            index.push_back(' ');
            TaPe.push_back((char)(i+'0'));
            TaPe = TaPe + "  : ";
            Head.push_back((char)(i+'0'));
            Head = Head + "  : ";
        }
        else{
            index.push_back((char)(t+'0'));
            index.push_back((char)(i%10+'0'));
            index.push_back(':');
            index.push_back(' ');
            TaPe.push_back((char)(t+'0'));
            TaPe.push_back((char)(i%10+'0'));
            TaPe = TaPe + " : ";
            Head.push_back((char)(t+'0'));
            Head.push_back((char)(i%10+'0'));
            Head = Head + " : ";
        }
        cout<<index;
        for(int j=setOfTape[i].index_start;j<=setOfTape[i].index_end;j++){
            if(j<0){
                cout<<0-j;
            }
            else{
                cout<<j;
            }
            //if(j!=setOfTape[i].index_end){
                cout<<" ";
            //}
        }
        cout<<endl;
        cout<<TaPe;
        for(int j=0;j<setOfTape[i].tape.length();j++){
            cout<<setOfTape[i].tape[j];
            if((setOfTape[i].index_start+j<10)&&(setOfTape[i].index_start+j>-10)){
                cout<<" ";
            }
            else if(((setOfTape[i].index_start+j>=10)&&(setOfTape[i].index_start+j<100))||((setOfTape[i].index_start+j>-100)&&(setOfTape[i].index_start+j<=-10))){
                cout<<"  ";
            }
            else {
                cout<<"   ";
            }
        }
        cout<<endl;
        cout<<Head;
        int pointpos = setOfTape[i].pointer - setOfTape[i].index_start;
        for(int j=0;j<pointpos;j++){
            cout<<" ";
            if((setOfTape[i].index_start+j<10)&&(setOfTape[i].index_start+j>-10)){
                cout<<" ";
            }
            else if(((setOfTape[i].index_start+j>=10)&&(setOfTape[i].index_start+j<100))||((setOfTape[i].index_start+j>-100)&&(setOfTape[i].index_start+j<=-10))){
                cout<<"  ";
            }
            else {
                cout<<"   ";
            }
        }
        cout<<"^"<<endl;
        
    }
    cout<<"State  : "<<currentState<<endl;
    cout<<"---------------------------------------------\n";
}

void TuringMachine::run(string InputString){
    stepCount = 0;
    for(int i=0;i<tapeCount;i++){
        Tape temptape;
        if(i == 0){
            temptape.tape = InputString;
            if(InputString == ""){
                temptape.tape = "_";
            }
            temptape.index_start = 0;
            temptape.index_end = temptape.tape.length()-1;
            temptape.pointer = 0;
        }
        else{
            temptape.tape = "_";
            temptape.index_start = 0;
            temptape.index_end = 0;
            temptape.pointer = 0;
        }
        setOfTape.push_back(temptape);
    }
    while(true){
        if(isverbose){
            inVerboseMode();
        }
        Transition nextTransition = findNextMove();
        if (nextTransition.oldState == "notfound"){
            //cout<<"end\n";
            break;
        }
        else{
            moveToNext(nextTransition);
            stepCount++;
        }
        //if(stepCount == 14) break;
    }
    if(isverbose){
        cout<<"Result: "<<setOfTape[0].tape<<endl;
        cout<<"==================== END ====================\n";
    }
    else{
        cout<<setOfTape[0].tape<<endl;
    }
}