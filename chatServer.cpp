/***************************************************************************
* copyright : (C) 2009 by Jim Skon
***************************************************************************/
//File Name: chatServer.cpp
//Team Members: Daniel Oliveri, Juviand Rivera, & Aidan Murphy
//Email Addresses: olivierid@kenyon.edu, riveraj@kenyon.edu murphy1@kenyon.edu
//Project Number: 4
//Description: The server for a multi-user chat program.
//Last Changed: March 1st, 2017
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <string>
#include <vector>
#include <ostream>
#include "fifo.h"

using namespace std;


  /* Fifo names */
string receive_fifo = "Chatrequest";
string send_fifo = "Chatreply";
int count = 0;
/* Server main line,create name MAP, wait for and serve requests */
int main() {

string inMessage, outMessage = ""; // global variables that are needed 

  // create the FIFOs for communication
  Fifo recfifo(receive_fifo);
  Fifo sendfifo(send_fifo);
  
  // main while loop 
   while (1) {
inMessage = "";

string commentClass = "comment";
cout << "testing 1" << endl;
   recfifo.openread();// opens to read
   cout << "testing 1.1" << endl;
	     inMessage = recfifo.recv(); // takes message in 
		 cout << "testing 1.2" << endl;
		 	sendfifo.openwrite(); // opens the write fifo 
			cout << "testing 1.3" << endl;
		
		// cuts of the trailing $END 
		int toSubstring = inMessage.size() - 4; 
		inMessage = inMessage.substr(0, toSubstring);
	cout << "testing 2 inMessage: " << inMessage << endl;
		
		if (inMessage.find("***$") > 10) // determines whether or not it's a request 
			
			{ // if it's not a request 
				
				// allows the message to be ready to immediatly be put into the HTML 
				outMessage =  " <div class = " + commentClass + " > <b>" + inMessage + "</b> </div> <br>"; 
				cout << "testing outMessage: " << outMessage << endl;
					sendfifo.send(outMessage); // sends the outMessage to the cgi 
			
			sendfifo.send("$END");// send the End message 

			}
	else{
								if ( outMessage.size() > 2)
								{
										cout << "70: " << outMessage << endl;
				sendfifo.send(outMessage + "$END"); // sends the outMessage to the cgi 
			cout << "72" << endl;	
			
								}
								else
								{
								cout << "line 81: " << outMessage << endl;
								sendfifo.send("Nothing $END");
								cout << "line 83" << endl;
								}
			
				}	
			
			
		cout << "before the fifos" << endl;
		
// closes fifos 
	sendfifo.fifoclose();
	 recfifo.fifoclose();
	 cout << "after the fifos" << endl;
  }
  
  
}
