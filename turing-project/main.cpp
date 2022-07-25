#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<vector>
#include"TuringMachine.h"
using namespace std;

bool isverbose = false;
bool ishelp = false;

void splitCommand(string str,string* turmachine, string* inputstring)
{
    bool islegalinput = false;
    bool isturing = false;
    //bool ishelp = false;

    string turingmachine;
    string input;
    char* command =new char[str.length()+1];
    str.copy(command,str.length(),0);
    *(command + str.length()) = '\0';
    
    char* PartOfCommand;
    PartOfCommand = strtok(command," ");
    if (strcmp(PartOfCommand,"./turing")==0 && PartOfCommand != NULL){
        isturing = true;
    }
    else{
        islegalinput = false;
    }
    if (isturing){
        PartOfCommand = strtok(NULL," ");
        if(PartOfCommand != NULL && (strcmp(PartOfCommand,"-v")==0 || strcmp(PartOfCommand,"--verbose")==0)){
            isverbose = true;
            PartOfCommand = strtok(NULL," ");
            if(PartOfCommand == NULL)
            {
                //cout<<"no tm"<<endl;
            }
            else{
                string tempstring = PartOfCommand;
                int length = tempstring.length();
                if(length < 4){
                    islegalinput = false;
                }
                else{
                    string lastthree = tempstring.substr(length-3,3);
                    //cout<<lastthree<<endl;
                    if (lastthree == ".tm"){
                        turingmachine = tempstring;
                        PartOfCommand = strtok(NULL," ");
                        if(PartOfCommand ==NULL){
                            //cout<<"no input"<<endl;
                            input = "";
                        }
                        else{
                            input = PartOfCommand;
                            while(PartOfCommand!=NULL){
                                PartOfCommand = strtok(NULL," ");
                                if(PartOfCommand==NULL) break;
                                string temp1 = PartOfCommand;
                                input = input + " " + temp1;
                            }
                        }
                        islegalinput =true;
                    }
                    else{
                        islegalinput = false;
                    }
                }
            }
        }
        else if(PartOfCommand!=NULL && (strcmp(PartOfCommand,"-h")==0 || strcmp(PartOfCommand,"--help")==0)){
            ishelp = true;
            PartOfCommand = strtok(NULL," ");
            if(PartOfCommand == NULL)
            {
                islegalinput =true;
                cout<<"usage: turing [-v|--verbose] [-h|--help] <tm> <input>\n";
                ishelp = true;
            }
            
        }
        else if (PartOfCommand!=NULL){
            string tempstring = PartOfCommand;
            /*for(int j = 0;PartOfCommand[j]!='\0';j++){
                cout<<PartOfCommand[j];
            }*/
            //cout<<tempstring<<endl;
            //string m = tempstring;
            int length = tempstring.length();
            if(length < 4){
                islegalinput = false;
            }
            else{
                string lastthree = tempstring.substr(length-3,3);
                
                //cout<<lastthree<<endl;
                if (lastthree == ".tm"){
                    turingmachine = tempstring;
                    PartOfCommand = strtok(NULL," ");
                    if(PartOfCommand ==NULL){
                        //cout<<"no input"<<endl;
                        input = "";
                    }
                    else{
                        //cout<<"time\n";
                        input = PartOfCommand;
                        while(PartOfCommand!=NULL){
                                PartOfCommand = strtok(NULL," ");
                                if(PartOfCommand==NULL) break;
                                string temp1 = PartOfCommand;
                                input = input + " " + temp1;
                            }
                    }
                    islegalinput =true;
                }
                else{
                    islegalinput = false;
                }
            }
        }
        else{
            islegalinput = false;
        }
    }
    if (!islegalinput){
        //cout<<"no good\n";
        fprintf(stderr,"illegal command");
        cout<<endl;
        exit(-1);
    }
    //cout<<turingmachine<< " "<<input<<endl;
    *turmachine = turingmachine;
    *inputstring = input;
}

TuringMachine get_TuringMachine(string turingmachine,bool isVerbose)
{
    ifstream in(turingmachine);
    vector<string> turingText;
    string setOfState,setOfInput,setOfTape,startState,blankSymbol,setOfFinish,numOfTape;
    vector<string> transfunc;
    if(in.is_open()){
        while(!in.eof())
        {
            string temp;
            getline(in,temp);
            turingText.push_back(temp);
        }
    }
    else{
        cout<<"syntax error\n";
        exit(-1);
    }
    //cout<<"copy right\n";
    int alltext = turingText.size();
    for (int i = 0;i < alltext;i++){
        string temp = turingText[i];
        if(temp.length()==0){
            //konghang
        }
        else{
            int length = temp.length();
            if (temp[0] == ';'){
                //zhushi
            }
            else if(temp[0] == '#'){
                if (length == 1){
                    cout<<"syntax error\n";
                    exit(-1);//wrong line
                }
                else{
                    if(temp[1] == 'Q'){
                        setOfState = temp;
                        //cout<<setOfState<<endl;
                    }
                    else if (temp[1] == 'S'){
                        setOfInput = temp;
                    }
                    else if(temp[1] == 'G'){
                        setOfTape = temp;
                    }
                    else if(temp[1] == 'B'){
                        blankSymbol = temp;
                    }
                    else if(temp[1] == 'F'){
                        setOfFinish = temp;
                    }
                    else if(temp[1] == 'N'){
                        numOfTape = temp;
                    }
                    else{
                        if(length < 3){
                            cout<<"syntax error\n";
                            exit(-1);
                        }
                        else{
                            startState = temp;
                        }
                    }
                }
            }//qigezhuangtai
            else{
                string temp1 =temp;
                transfunc.push_back(temp1);
            }//transition func
        }
    }
    TuringMachine TM = TuringMachine(setOfState,setOfInput,setOfTape,startState,blankSymbol,setOfFinish,numOfTape,transfunc,isVerbose);
    if (!TM.isTM()){
        //cout<<"wrong tm\n";
        cout<<"syntax error";
        cout<<endl;
        exit(-1);
    }
    else{
        //cout<<"correct tm\n";
        return TM;
    }
}

int main(int argc, char* argv[])
{
    string str;
    string turingMachine,Input;
    for (int i = 0;i<argc;i++){
        string temp = argv[i];
        temp.push_back(' ');
        str+=temp;
    }
    //cout<<str<<endl;
    //cout<<"bad\n";
    splitCommand(str,&turingMachine,&Input);

    //cout<<"good\n";
    //cout<<"turingmachine = "<<turingMachine<<" input = "<<Input<<endl;
    if(!ishelp){
        TuringMachine TM = get_TuringMachine(turingMachine,isverbose);
        if(TM.checkinput(Input)){
            TM.run(Input);
        }
        else{
            exit(-1);
        }
    }
    return 0;
}


