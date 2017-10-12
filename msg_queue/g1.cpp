/*Receiver 1*/
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
    //initalizing message queue
    int queue_id = msgget(ftok(".",'u'),0600);
    //0 is to wait until object is inserted to queue successfully
    
    //initialize structure
    Struct_message mymsg; //create new structure object
    
    //determine size of message
    int size = sizeof(mymsg) - sizeof(long);
    
    //determine if the loop will continue or not
    bool keepLooping = true;
    
    //variable for exit program
    bool exitloop = false;
    
    //variable to count messages
    int messageCounter = 0;
    
    //variable to determine if all senders exited (counter 0= no sender exited, 1=1 sender exited, 2= 2 sender exited)
    int exitcounter = 0;

    
    
    while(keepLooping == true){
        //counter to determine if both senders are done
        //this receiver only terminates if both senderes are done
        if(exitcounter != 2){
            if(exitloop == false){
                msgrcv(queue_id,(struct msgbuf*)&mymsg, size, 255,0);
                exitloop = mymsg.exitQueue;
                
                //wait until object in queue to pull the object off queue
                cout << "\nBorderline:" << mymsg.borderline;
                cout << "\tNumber: " << mymsg.rnumber;
                messageCounter = messageCounter + 1;
                cout << "\tCounter: " << messageCounter;
                mymsg.exitQueue = false;
                mymsg.mtype = 111;
                msgsnd(queue_id, (struct msgbuf*)&mymsg, size, 0);
                
            }//end if
            else if(exitloop == true){
                //if one sender is done, exitcounter increment by one
                ++exitcounter;
                //but does not exit yet
                exitloop = false;
                cout << "\nExit Counter: " <<exitcounter;
            }//end else if
        }
        else if(exitcounter == 2){
            //if two senders are done, exit loop
            keepLooping = false;
        }//end else if
    }//end while
    msgctl(queue_id, IPC_RMID,NULL); //safe to delete queue
    
    exit(0);
    return 0;
}