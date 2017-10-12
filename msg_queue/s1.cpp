/*Sender 1*/
#include <iostream>
#include <cstdlib> // use of rand()
#include <ctime> //use of time()
#include <sys/msg.h> // use of msgget(), msgsnd(), msgrcv()
#include <sys/ipc.h>
#include <unistd.h> // use of getpid()

using namespace std;

struct Struct_message{
    long mtype; //message type
    int rnumber;
    int borderline;
    bool exitQueue;
    bool deleteQueue;
};


int main(){
    //initialize random number generator using argument passed as seed.
    srand(time(NULL));
    
    //initalizing message queue
    int queue_id = msgget(ftok(".",'u'),0); //0 is to wait until object is inserted to queue successfully
    
    //initialize structure
    Struct_message mymsg; //create new structure object
    
    //determine size of message
    int size = sizeof(mymsg) - sizeof(long);
    
    //determine if the loop will continue or not
    bool keepLooping = true;
    
    //variable for exit program
    bool exitloop_g1 = false;
    
    //varaible for random number
    int randnumber;
    
    while(keepLooping == true){
        randnumber = rand();
        cout << "\nRandom Number: " << randnumber;
        
        if(randnumber >= 100){
            if(randnumber % 255 == 0){
                cout << "Divisible by 256 " << endl;
                //storing data
                mymsg.rnumber = randnumber;
                mymsg.exitQueue = false;
                mymsg.borderline = 255;
                mymsg.mtype = 255;
                //send message to queue so receiver 1 can pick up
                msgsnd(queue_id, (struct msgbuf*)&mymsg, size, 0);
                //receive message from receiver 1 to check if should exit loop
                msgrcv(queue_id,(struct msgbuf*)&mymsg, size, 111,0);
                
                
            }
            
        }
        else if(randnumber < 100){
            keepLooping = false;
        }
        
    }
    
    mymsg.exitQueue = true;
    mymsg.mtype = 255;
    //send final message to receiver 1 to tell that it ends before exiting
    msgsnd(queue_id, (struct msgbuf*)&mymsg, size, 0);
    exit(0);
    
    
    return 0;
}