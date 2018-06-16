#include "headers.h"

int main(int argc , char *argv[])
{
	if( argc != 3 )
        	{
                 cout<<"Enter Server-Ip and Port to connect! "<<endl;
                 return 0;
        	}
	
	//get the server-Ip address
	char *servip = argv[1];

        //get the port number
        int port = atoi(argv[2]);

	//gethostbyname function retrieves host information 
	//corresponding to a host name from a host database.
	struct hostent* host = gethostbyname(servip);


	//SOCKADDR_IN structure is used to specify a local or remote
        //endpoint address to which to connect a socket
	sockaddr_in sendToSockAddr;
	
	//initialize to all zeroes first
	bzero((char*)&sendToSockAddr, sizeof(sendToSockAddr));

	
	sendToSockAddr.sin_family = AF_INET;	//using IPv4 protocol

	/* 
	  *inet_addr converts the standard IPv4 dotted decimal notation to an integer value suitable for use as an Internet address
	 
	  *inet_ntoa convert the Internet host address to a string in the Internet standard dot notation.
	  
	  *h_addr_list is a Null-terminated array of in_addr structs
	  */
	sendToSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
	  
	sendToSockAddr.sin_port = htons(port);
	  
	  // Creating client's  socket file descriptor
	int clientSd = socket(AF_INET, SOCK_STREAM, 0);

	if(clientSd < 0)
	  {
		  cout<<"Failed to create Client's socket descriptor\n";
		  return 0;
	  }

	int conReq;
	  
	if( (conReq = connect(clientSd , (struct sockaddr*) &sendToSockAddr , sizeof(sendToSockAddr)) ) < 0)
	 {
		 cout<<"some problem in establishing connection to server\n";
		 return 0;
	 }

	 cout << "Connected to the User !" << endl;
	 
	 int bytesRead, bytesWritten = 0;
	 
	 //keeping client session time
	 struct timeval startTime, endTime;
	 
	 //start session timer 
	 gettimeofday(&startTime, NULL);
	 
	 char msg[1024];

	 while(1)
	 {
		 cout << ">";
		 
		 //get user's input and initiate the communication with the server
		 string data;
		 getline(cin, data);    //take input from user
		 
		 //clear the buffer
		 memset(&msg, 0, sizeof(msg));

		 //c_str member function returns a pointer to the beginning of a null-terminated string.
		 strcpy(msg, data.c_str());     //copy typed message to msg buffer
		 
		 //if user wants to end the chat, if he'll type exit to terminate the communication
		 if(data == "exit" || data == "EXIT" || data =="Exit")
		 {
			 send(clientSd, (char*)&msg, strlen(msg), 0);
			 break;		//breaks the while loop
		 }
		 
		 bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);
		 

		 cout<<endl<<"\tWaiting for message..." << endl;
		 memset(&msg, 0, sizeof(msg));	//clear the buffer for server's reply
		 
		 bytesRead += recv(clientSd, (char*)&msg, sizeof(msg), 0);
		 
		 //check whether fellow user wants to terminate the chat
		 if(!strcmp(msg, "exit") || !strcmp(msg, "Exit") || !strcmp(msg, "Exit") )
		 {
			 cout <<"Fellow User Terminated the session"<< endl;
			 break;		//break the while loop
		 }
		 
		 cout <<"Reply: "<<msg<<endl;
	 }

	 //store the session end-time
	 gettimeofday(&endTime, NULL);
	 
	 close(clientSd);
	 
	 
	 cout << "********Session Details********" << endl;
	 cout << "Bytes written: " << bytesWritten <<" Bytes read: " << bytesRead << endl;
	 
	 cout << "Elapsed time: " << (endTime.tv_sec- startTime.tv_sec)<< " secs" << endl;
	 
	 cout << "Connection Terminated !!" << endl;
	 
	 return 0;
}
