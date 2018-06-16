I've created a simple server-side script and a client-side script for communication between two processes(IPC mechanism).

Used Socket Programming module **<sys/socket.h>**
and other supporting modules **<netinet/in.h>**, **<arpa/inet.h>** etc

Since sockets can be used to serve multiple clients, here 6 clients can be connected to the server at once(it can be increased or decreased based on requirements).

Server should be up-running prior to clients getting connected.
On running the server and multiple clients, you can now see that each message (sent by client) is being received by the server.


______________________________________
Steps to follow to run the setup.
    Step1: Download the File to desired location in pc.
    Step2: Open two terminals with the location of the file saved.
    Step3: In First Terminal, Compile **server.cpp** file by giving command as **gcc -o server server.cpp**
    Step4: Choose an available free port-no (say 5000) and run the server object file i.e. **./server 5000**
    Step5: In Second Terminal, Compile **client.cpp** file by giving command as **gcc -o client client.cpp**
    Step6: Connect client program to the server by giving command as **./server 127.0.0.1 5000** , i.e. using the localhost address and port to connect to server.
    Step7: Now Client can Initiate the communication by sending first message to server.
    
To Terminate the process, a simple **exit** message is sufficient.
______________________________________

NOTE: The program is designed to send and recieve one message at a time, with limited number of characters(1024 characters).

**Screenshots**
For Better Understanding attaching Screenshots with a client connected to server.
More terminals can be created and clients can be connected similarly as done.

![Setting-up-connection](https://github.com/avinashav/chatbox-using-sockets-cpp/blob/master/screens/establish.png)

![communication](https://github.com/avinashav/chatbox-using-sockets-cpp/blob/master/screens/communication.png)

![Terminating-connection](https://github.com/avinashav/chatbox-using-sockets-cpp/blob/master/screens/session.png)

After each session of communication, total bytes sent, bytes recieved and total session time can be seen after exit.

Thanks,
Avinash Kumar