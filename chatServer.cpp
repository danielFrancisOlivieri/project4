/***************************************************************************
* copyright : (C) 2009 by Jim Skon
***************************************************************************/
//File Name: chatServer.cpp
//Team Members: Daniel Oliveri, Juviand Rivera, & Aidan Murphy
//Email Addresses: olivierid@kenyon.edu, riveraj@kenyon.edu murphy1@kenyon.edu
//Project Number: 3
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
vector <string> testVector;//A test vector, designed to insure the functionality of sending vectors of strings.

testVector.push_back("Gastby");
testVector.push_back("believed in the green");
testVector.push_back("light the future that year by ");
testVector.push_back("year receds before us");
testVector.push_back("it eludes us then but it is no matter");
testVector.push_back("tomorrow we'll run faster, stretch out our arms farther.");

  // create the FIFOs for communication
  Fifo recfifo(receive_fifo);
  Fifo sendfifo(send_fifo);
  
 // int previousVectorSize = 0;
  int fourFromEnd;
 
  // main while loop 
   while (1) {
inMessage = "";

string commentClass = "comment";
//cout << "start" << endl;

   recfifo.openread();// opens to read
	     inMessage = recfifo.recv(); // takes message in 
		 	sendfifo.openwrite(); // opens the write fifo 
		cout << inMessage << "   " << inMessage.size() << endl;
		int toSubstring = inMessage.size() - 4;
		inMessage = inMessage.substr(0, toSubstring);
		//inMessage.replace("", inMessage.size() - 4)
		
		if (inMessage.find("***$") > 10)
			
			{
				cout << "pushback" << endl;				
				outMessage =  " <div class = " + commentClass + " > <b>" + inMessage + "</b> </div> ";
				commentVector.push_back(outMessage);
			}
			
			string toSendOut = "";
			cout << "before" << endl;
			
			sendfifo.send(outMessage);
			
			/*
			for (int i = 0; i < commentVector.size(); i++)
			{
				
				//toSendOut += commentVector[i];
				outMessage = commentVector[i];
				sendfifo.send(outMessage);
				//sendfifo.send("$END");
				
				cout << "SENDING: " << outMessage << " i: " << i <<  endl;
			}
			*/
			sendfifo.send("$END");
			cout << "END HAVING BEEN SENT" << endl;
		
		//" <div class = " + commentClass + " > <b>" + fromCGI + "</b> </div>"
		
		// if (outMessage.size() > 0)
		// {
			// cout << "SENDING: " << toSendOut <<  endl;
			// // int i = 0;
			// // while (i < commentVector.size())
			// // {
				// //cout << "SENDING: " << commentVector[i] <<  endl;
				// //sendfifo.send("<div> <b> SPUCKLE </b> </div>");
				
				// // i++;
			// // }
				
		// }
				

/*

	    recfifo.openread();// opens to read
	     inMessage = recfifo.recv(); // takes message in 
		 	sendfifo.openwrite(); // opens the write fifo 
			cout << "&&&&&&&&&&&&& " << inMessage << endl;
			cout << inMessage.find("***$") << endl;
			if (inMessage.find("***$") > 10) // makes sure it's not a request 
		{
			cout << "******************************" << endl;
			commentVector.push_back(inMessage);
		
	 string toSendToWeb;
			for (int i = 0; i < commentVector.size(); i++)
			{
				cout << i << ": " << commentVector[i] << endl;
				
				toSendToWeb += commentVector[i];
			}
	
		if (inMessage.size() > 2)
			{
				
				// testVector.push_back(inMessage);
					//toSendToWeb	+= inMessage;
				//	cout << "to send " << toSendToWeb << endl;
				//for (int i = 0; i < testVector.size(); i++){
					
					cout << " ^^^^^ " << commentVector[0] << endl;
					sendfifo.send("THIS IS IA TEST");
				
				
			}
			}
		*/
	/*
		if (inMessage.find("***$") == string::npos) // makes sure it's not a request 
		{
			cout << "comment to be added to list: " << inMessage << endl;
		 string stringToProcess;
		 stringToProcess = inMessage.substr(0, fourFromEnd);
		commentVector.push_back(stringToProcess);
		inMessage = "";

		}
		else
		{ // runs if it is a request
			cout << "request: " << inMessage << endl;
				 	
				for (int i = 0; i < commentVector.size(); i++)
	{
		cout << "8 working: " << commentVector[i] << "vector size: " << commentVector.size() << endl << endl;
		 
		 sendfifo.send(commentVector[i]);
		
		 cout << " message has been sent " << commentVector[i] << " " << i<< endl;
	}
	 
	 sendfifo.send("$END");
	cout << "END HAS BEEN SENT"  << endl << endl;
	 
		}
	    
	
	 
	  cout << "end" << endl;
	  
	  */

	sendfifo.fifoclose();
	 recfifo.fifoclose();
  }
  
  
}
