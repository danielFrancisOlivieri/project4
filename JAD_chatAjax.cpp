//File Name: JAD_chatAjax.cpp
//Team Members: Daniel Oliveri, Juviand Rivera, & Aidan Murphy
//Email Addresses: olivierid@kenyon.edu, riveraj@kenyon.edu murphy1@kenyon.edu
//Project Number: 3
//Description: An ajax program that functions as the CGI for communication between a web page and a server for a chat room program.
//Last Changed: Febuary 27th, 2017
#include <iostream>
// Stuff for AJAX
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

//Stuff for pipes
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include "fifo.h"

using namespace std;
using namespace cgicc; // Needed for AJAX functions.

//Indeed, myString needs to be a copy of the original string
std::string StringToUpper(std::string myString)//A program to turn a string into uppercase.
{
  const int length = myString.length();
  for(int i=0; i!=length ; ++i)
    {
      myString[i] = std::toupper(myString[i]);
    }
  return myString;
}


// fifo for communication
string receive_fifo = "Chatreply";
string send_fifo = "Chatrequest";

int main() {
  Cgicc cgi;    // Ajax object
  char *cstr;
  
  // Create AJAX objects to recieve information from web page.
  form_iterator message = cgi.getElement("message");
  string inMessage, outMessage;

  cout << "Content-Type: text/plain\n\n"; 
  
  // create the FIFOs for communication
  Fifo recfifo(receive_fifo);
  Fifo sendfifo(send_fifo);
  
  // Call server to get results
  inMessage = **message;
  inMessage = StringToUpper(inMessage);
	//The inputted message is put in the uppercase
  
  string color = "#f44336";
  


  while(1)
	
	{
		
	// open sendfifo to send word to server
 sendfifo.openwrite();
  sendfifo.send(inMessage);
  

 // return 0;
  /* Get a message from a server */
  recfifo.openread();
	//return 0;	
	outMessage = recfifo.recv(); // puts the results from the server into the results variable 
	  outMessage = StringToUpper(outMessage);
	 // cout << outMessage << endl;
	 // this if statement looks for the $END in order to break the loop once all the lines have been outputted 
	 if (outMessage.find("$END") != string:: npos)
	 {
		 return 0;
		 break;
	 }



	cout <<  outMessage;
	  //print the message
		return 0;
	}

}
