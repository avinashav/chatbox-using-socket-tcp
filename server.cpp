/*
 *	SERVER PROGRAM
 *	---SOCKET PROGRAMMING---
 */

#include "headers.h"

int main(int argc , char *argv[])
{

	if( argc != 2 )
	{
		cout<<"Enter Port to connect! "<<endl;
		return 0;
	}

	//get the port number
	int port = atoi(argv[1]);

	//SOCKADDR_IN structure is used to specify a local or remote
	//endpoint address to which to connect a socket
	sockaddr_in servaddr , newaddr;

	//copy zeroes to servaddr string
	bzero((char*)&servaddr , sizeof(servaddr));

	servaddr.sin_family = AF_INET;			//IPv4 protocol
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);	//INADDR_ANY: not binding a socket to a specific IP
	servaddr.sin_port = htons(port);		//which port to bind

	// Creating socket file descriptor
	int sd = socket( AF_INET, SOCK_STREAM , 0);
	if (sd < 0)
	{
		cout<<"Failed to create Socket Descriptor"<<endl;
		return 0;
	}

	if( bind(sd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 )
	{
		cout<<"Error while binding socket-descriptor to local address"<<endl;
		return 0;
	}

	cout<<"Waiting... for client to connect"<<endl;
//server can serve upto 6 clients
	listen(sd, 6);

	socklen_t newaddrsize = sizeof(newaddr);
	int newsd = accept( sd, (struct sockaddr *) &newaddr, &newaddrsize);

	if(newsd < 0)
	{
		cout<<"Error while accepting client request\n"<<endl;
		return 0;
	}

	cout<<"Sucessfully accepted client connection request\n"<<endl;

	//keeping client session time
	struct timeval starttime, endtime;
	//get time
	if( gettimeofday(&starttime, NULL) < 0)
	{
		cout<<"Error Getting time\n"<<endl;
	}

	//storing bytes of data transferred & recieved
	int bytesread , byteswritten = 0;
	char buff[1024];
	while(1)
	{
		cout<<"\tWaiting for message ...\n\n";
		//clearing the message buffer
		memset(&buff , 0 , sizeof(buff));
		
		//message recieved and stored into buffer (buff)
		bytesread += recv(newsd, (char *)&buff , sizeof(buff) , 0);

		//checking for exit command from the client
		if(!strcmp(buff , "exit") || !strcmp(buff , "EXIT") || !strcmp(buff , "Exit"))
		{
				cout<<"Client wants to terminate the connection\n\n";
				break;
			}
		//communication continues
		cout<<">: "<<buff<<endl;
		cout<<"Reply: ";
		//cout<<"> ";
		string data;
        	getline(cin, data);
        	memset(&buff, 0, sizeof(buff)); //clear the buffer
        	strcpy(buff, data.c_str());
        	if(data == "exit")
        		{
            			//send to the client that server has closed the connection
            			send(newsd, (char*)&buff, strlen(buff), 0);
            			break;
        		}
		byteswritten += send(newsd, (char*)&buff, strlen(buff), 0);
	}
	gettimeofday(&endtime, NULL);
    close(newsd);
    close(sd);
    cout << "********Session Ends********" << endl;
    cout << "Bytes written: " << byteswritten << " Bytes read: " << bytesread << endl;
    cout << "Elapsed time: " << (endtime.tv_sec - starttime.tv_sec) 
        << " secs" << endl;
    cout << "Connection closed..." << endl;
    return 0;

}
