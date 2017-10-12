#include <iostream>
#include <string>
#include <cstdlib> //use for terminate calling process
#include <unistd.h> //use for getppid()
#include <sys/wait.h> //use of wait function
#include <sys/types.h> //create child process

using namespace std;

//function declaration
void Selection(); //Menu Selection
void SearchForIt(); //search for string
string BigStringyThing(); //Big String paragraph

string BigStringyThing(){//generated from randomtextgenerator.com
    string BigString = "Admiration stimulated cultivated reasonable be projection possession of. Real no near room ye bred sake if some. Is arranging furnished knowledge agreeable so. Fanny as smile up small. It vulgar chatty simple months turned oh at change of. Astonished set expression solicitude way admiration."
    "Your it to gave life whom as. Favourable dissimilar resolution led for and had. At play much to time four many. Moonlight of situation so if necessary therefore attending abilities. Calling looking enquire up me to in removal. Park fat she nor does play deal our. Procured sex material his offering humanity laughing moderate can. Unreserved had she nay dissimilar admiration interested. Departure performed exquisite rapturous so ye me resources."
    "Barton did feebly change man she afford square add. Want eyes by neat so just must. Past draw tall up face show rent oh mr. Required is debating extended wondered as do. New get described applauded incommode shameless out extremity but. Resembled at perpetual no believing is otherwise sportsman. Is do he dispatched cultivated travelling astonished. Melancholy am considered possession on collecting everything. "
    "At distant inhabit amongst by. Appetite welcomed interest the goodness boy not. Estimable education for disposing pronounce her. John size good gay plan sent old roof own. Inquietude saw understood his friendship frequently yet. Nature his marked ham wished. "
    "Greatest properly off ham exercise all. Unsatiable invitation its possession nor off. All difficulty estimating unreserved increasing the solicitude. Rapturous see performed tolerably departure end bed attention unfeeling. On unpleasing principles alteration of. Be at performed preferred determine collected. Him nay acuteness discourse listening estimable our law. Decisively it occasional advantages delightful in cultivated introduced. Like law mean form are sang loud lady put."
    "Ought these are balls place mrs their times add she. Taken no great widow spoke of it small. Genius use except son esteem merely her limits. Sons park by do make on. It do oh cottage offered cottage in written. Especially of dissimilar up attachment themselves by interested boisterous. Linen mrs seems men table. Jennings dashwood to quitting marriage bachelor in. On as conviction in of appearance apartments boisterous."
    "Seen you eyes son show. Far two unaffected one alteration apartments celebrated but middletons interested. Described deficient applauded consisted my me do. Passed edward two talent effect seemed engage six. On ye great do child sorry lived. Proceed cottage far letters ashamed get clothes day. Stairs regret at if matter to. On as needed almost at basket remain. By improved sensible servants children striking in surprise."
    "In no impression assistance contrasted. Manners she wishing justice hastily new anxious. At discovery discourse departure objection we. Few extensive add delighted tolerably sincerity her. Law ought him least enjoy decay one quick court. Expect warmly its tended garden him esteem had remove off. Effects dearest staying now sixteen nor improve."
    "Prepared do an dissuade be so whatever steepest. Yet her beyond looked either day wished nay. By doubtful disposed do juvenile an. Now curiosity you explained immediate why behaviour. An dispatched impossible of of melancholy favourable. Our quiet not heart along scale sense timed. Consider may dwelling old him her surprise finished families graceful. Gave led past poor met fine was new."
    "Demesne far hearted suppose venture excited see had has. Dependent on so extremely delivered by. Yet ﻿no jokes worse her why. Bed one supposing breakfast day fulfilled off depending questions. Whatever boy her exertion his extended. Ecstatic followed handsome drawings entirely mrs one yet outweigh. Of acceptance insipidity remarkably is invitation. ";
    return BigString;
}
void Selection(){
    char menuselection;
    bool loopMenu;
    do{
        cout << "\nMain Menu:" << endl;
        cout << "1. Search a string in text:" <<endl;
        cout << "2. Exit Program" << endl;
        cin >> menuselection;
        if(menuselection == '1'){
            SearchForIt(); //will make false if loopSearch is false
            loopMenu = false;
        }
        else if(menuselection == '2'){
            cout << "\nprogram exiting";
            loopMenu = false;
        }
        else if(menuselection != '1' || menuselection != '2'){
            cout << "your selection is wrong. Please try again."<< endl;
            loopMenu = true; // loop whole menu again
        }
        
    } while (loopMenu == true);
}
void SearchForIt(){
    string BigString = BigStringyThing(); //parse string to local variable
    bool loopSearch;
    string userInput;
    
    do{
        cout << "\nEnter a string to search. " << endl;
        cin >> userInput;
        if(userInput == "!wq"){
            cout << "You want to exit the program? Okay. That's cool." <<endl;
            loopSearch = false;
        }
        else{
            loopSearch = true;
            long ChildPID = fork(); //create a child process
            if (ChildPID == 0 ){
                int counter = 0;
                int stringIndex = 0;
                bool loopString = true;
                
                do{
                    stringIndex = BigString.find(userInput,stringIndex);
                    if(stringIndex > -1){
                        stringIndex++;
                        counter++;
                        loopString = true;
                    }
                    else if(stringIndex == -1 && counter == 0){
                        cout << ".";
                        stringIndex = 0;
                        loopString = true;
                    }
                    else if(stringIndex == -1 && counter > 0){
                        loopString = false;
                    }
                    
                }while(loopString == true);
                
                cout << "Parent Process ID: " << getppid()<< endl;
                cout << " Child Process ID: " << getpid() <<endl;
                cout << " string " << userInput << " appears " << counter << " times."<<endl;
                exit(0);
            }
            else if (ChildPID > 0){
                wait(0); // need to wait for child
            }
            else if(ChildPID < 0){
                cout << "Something is wrong. Child is not born." <<endl;
                exit(-1); //exit with error
            }
        }
    }while (loopSearch == true);
}
int main(){
    Selection();
    return 0;
}