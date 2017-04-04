
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

   recfifo.openread();// opens to read
	     inMessage = recfifo.recv(); // takes message in 
		 	sendfifo.openwrite(); // opens the write fifo 
		
		// cuts of the trailing $END 
		int toSubstring = inMessage.size() - 4; 
		inMessage = inMessage.substr(0, toSubstring);
	
		
		if (inMessage.find("***$") > 10) // determines whether or not it's a request 
			
			{
				// allows the message to be ready to immediatly be put into the HTML 
				outMessage =  " <div class = " + commentClass + " > <b>" + inMessage + "</b> </div> <br>"; 

			}
					
			
			sendfifo.send(outMessage); // sends the outMessage to the cgi 
			
			sendfifo.send("$END");// send the End message 
			
		
// closes fifos 
	sendfifo.fifoclose();
	 recfifo.fifoclose();
  }
  
  
}

