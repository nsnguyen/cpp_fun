/*Sender 3 - Divisible by 257*/

#include <iostream>
#include <cstdlib> // use of rand()
#include <ctime> //use of time()
#include <sys/msg.h> // use of msgget(), msgsnd(), msgrcv()
#include <sys/ipc.h>
#include <unistd.h> // use of getpid()

using namespace std;

struct Struct_message{
    long mtype; //message type
    int rnumber; //store random number
    int borderline; //store divisiblity
    bool exitQueue; //tells sender to exit queue
};


int main(){
    //initialize random number generator using argument passed as seed.
     srand(time(NULL));
    
    //initalizing message queue
    int queue_id = msgget(ftok(".",'u'),0);
    //0 is to wait until object is inserted to queue successfully
    
    //initialize structure
    Struct_message mymsg; //create new structure object
    
    //determine size of message
    int size = sizeof(mymsg) - sizeof(long);
    
    //determine if the loop will continue or not
    bool keepLooping = true;
    
    //variable for exit receiver 2
    bool exitloop_b = false;
   
    
    //varaible for random number
    int randnumber;
    
    //loop keeps on looping until told otherwise
    while(keepLooping == true){
        randnumber = rand();
        cout << "\nRandom Number: " << randnumber;

        if (exitloop_b == false){
            if(randnumber % 257 == 0){
                cout << "Divisible by 257 " << endl;
                
                //storing data into mymsg struct
                mymsg.rnumber = randnumber;
                mymsg.exitQueue = false;
                mymsg.borderline = 257;
                mymsg.mtype = 256;
                //send message to queue so receiver 2 can pick up
                msgsnd(queue_id, (struct msgbuf*)&mymsg, size, 0);
                //receive message from receiver 2 to check if should exit loop
                msgrcv(queue_id,(struct msgbuf*)&mymsg, size, 112,0);
                exitloop_b = mymsg.exitQueue;
                
            }
        }
        else if(exitloop_b == true){
            //exit loop
            keepLooping = false;
        }
    }
    
    exit(0);
    return 0;
}