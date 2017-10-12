/**Receiver 2*/
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
    int queue_id = msgget(ftok(".",'u'),IPC_EXCL|IPC_CREAT|0600);
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
    
    while(keepLooping == true){
        if(exitloop == false && messageCounter < 5000){
            msgrcv(queue_id,(struct msgbuf*)&mymsg, size, 256,0);
            exitloop = mymsg.exitQueue;
            
            //wait until object in queue to pull the object off queue
            cout << "\nBorderline:" << mymsg.borderline;
            cout << "\tNumber: " << mymsg.rnumber;
            
            //message counter
            messageCounter = messageCounter + 1;
            
            cout << "\tCounter: " << messageCounter;
            mymsg.exitQueue = false;
            mymsg.mtype = 112;
            //send back to senders to keep looping
            msgsnd(queue_id, (struct msgbuf*)&mymsg, size, 0);
        }
        else if(exitloop == true || messageCounter >=5000){
            //exit loop when Counter exeeds 5000
            keepLooping = false;
        }//end else if
    }//end while
    
    mymsg.exitQueue = true;
    mymsg.mtype = 112;
    //send each sender 2 and sender 3 to get out loop and exit
    msgsnd(queue_id, (struct msgbuf*)&mymsg, size, 0);
    msgsnd(queue_id, (struct msgbuf*)&mymsg, size, 0);
    
    exit(0);
    return 0;
}