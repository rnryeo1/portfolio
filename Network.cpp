서버 기본 지식 패킷 전송


// Winsock reset 
WSADATA wsa;
int retval;
if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) //2.2version
return 1;
//Socket
SOCKET tcp_sock = socket(AF_INET, SOCK_STREAM, 0); //socket creation
if (tcp_sock == INVALID_SOCKET) err_quit("socket()");
//connect
SOCKADDR_IN serveradddr;
ZeroMemory(&serveradddr, sizeof(serveradddr));
serveradddr.sin_family = AF_INET;
serveradddr.sin_addr.s_addr = inet_addr(SERVERIP); //convert ip address to text
serveradddr.sin_port = htons(SERVERPORT); //Conversion from host address to network address, port number (set communication path)
retval = connect(tcp_sock, (SOCKADDR*)&serveradddr, //connection with server address
sizeof(serveradddr)); //connect to server

if (retval == SOCKET_ERROR) err_quit("connect()");
// Variables to use for data communication
char buf[500 + 1];
int len;
WaitRoom* WaitRoom=newWaitRoom();///Generate structure information and replace values
waitroom->current_player = 1;
waitroom->max_player = 4;
waitroom->room_state = 3;
int roombuf = 0;
// server-to-data communication
int maxCnt = 1; // number of times sent
while (1) {
//// data input
//printf("\n[data to send]");
//if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
//break;
//// Remove the '\n' character.
//len = strlen(buf);
//if (buf[len - 1] == '\n')
//buf[len - 1] = '\0';
//if (strlen(buf) == 0)
//break;
// sending data
retrieve = send(tcp_sock, (char*)waitroom, sizeof(WaitRoom),0;//structure variables to the server. tcp connect
if (retval == SOCKET_ERROR) {
err_display("send()");
break;
}
if (maxCnt-- < 1)
{
break;
}

retval = bind(listen_sock, (SOCKADDR*) & serveraddr, sizeof(serveraddr)); //bind to tie the server address to the socket.
if (retval == SOCKET_ERROR) err_quit("bind()");
retrieve = listen(listen_sock, SOMAXCONN);//socket enters listen state.
if (retval == SOCKET_ERROR) err_quit("listen()");
// variable used for data communication
SOCKET client_sock;
SOCKADDR_IN clientaddr;
int addrlen;
HANDLE hThread;
while (1) {
// accept()
addrlen = sizeof(clientaddr);
client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);//accept the cloud connect. Note that another socket for communication is made at this time (accept).
if (client_sock == INVALID_SOCKET) {
err_display("accept()");
break;
}
// outputting connected client information
printf("\n[TCP Server]" client connection: IP address = %s, port number = %d\n",
inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
hThread = CreateThread (NULL, 0, ProcessClient, (LPVOID)client_sock, 0, NULL); /// Create a thread function named ProcessClient to run the thread.
if (hThread == NULL) { closesocket(client_sock); }
else { CloseHandle(hThread); }
}
// closesocket()
closesocket(listen_sock);
WSACleanup();
return 0;


====================================================================================================================================
07 db, sql, js 서버측 코드 서버측 분리 내용 이해 및 설명(서버측 분리 및 연결을 이해하는 과정)

App.post("name",function(req,res){
Dbconnect.getConnection(async function(connect){/dbConnection
Var sql = "Select cash,freecash,id, FROM userinfo WHERE userid
Var row = req['body']
Var params= row['user_id']
...
Var func = wait func2(conn...)//wait for synchronization.Of course, there are methods such as future and promise, but the content was obtained through direct search that await is easy to synchronize.
....
Reponsehelper.senddata(res,rows)//result is sent to the cla as a row.
Send data to //sql.
....
Reponsehelper.sendreturncode (res,1,0..., etc.) // When the server sends a signal that it has sent information,
// Receive the code from the client side and process it at the client.
//If the server side sends 1 as a success signal, the data is updated in sql before sending 1. After synchronization of update
// Get the updated data (sql value) value from the server side from the client.
====================================================================================================================================
 
