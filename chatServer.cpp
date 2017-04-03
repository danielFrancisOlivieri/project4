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
string receive_fifo = "Namerequest";
string send_fifo = "Namereply";
int count = 0;
/* Server main line,create name MAP, wait for and serve requests */
int main() {

string inMessage, outMessage = "", preventDuplicates;

vector <string> commentVector;

  // create the FIFOs for communication
  Fifo recfifo(receive_fifo);
  Fifo sendfifo(send_fifo);
  

  int fourFromEnd;
 
  // main while loop 
   while (1) {
inMessage = "";

string commentClass = "comment";


   recfifo.openread();// opens to read
	     inMessage = recfifo.recv(); // takes message in 
		 	sendfifo.openwrite(); // opens the write fifo 
		cout << inMessage << "   " << inMessage.size() << endl;
		int toSubstring = inMessage.size() - 4;
		inMessage = inMessage.substr(0, toSubstring);
	
		
		if (inMessage.find("***$") > 10)
			
			{
				cout << "pushback" << endl;				
				outMessage =  " <div class = " + commentClass + " > <b>" + inMessage + "</b> </div> <br>";
				commentVector.push_back(outMessage);
			}
			
			string toSendOut = "";
			cout << "before" << endl;
			
			sendfifo.send(outMessage);
			
			sendfifo.send("$END");
			cout << "END HAVING BEEN SENT" << endl;
		

	sendfifo.fifoclose();
	 recfifo.fifoclose();
  }
  
  
}
