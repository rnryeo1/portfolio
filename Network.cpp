
서버 기본지식 패킷 보내는 것 정리

// 윈속 초기화
WSADATA  wsa;
int retval;
if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)	//2.2버전
return 1;
//Socket
SOCKET tcp_sock = socket(AF_INET, SOCK_STREAM, 0); //소켓생성
if (tcp_sock == INVALID_SOCKET) err_quit("socket()");
//connect 
SOCKADDR_IN serveradddr;
ZeroMemory(&serveradddr, sizeof(serveradddr));
serveradddr.sin_family = AF_INET;
serveradddr.sin_addr.s_addr = inet_addr(SERVERIP);	//ip주소를 문자로변환
serveradddr.sin_port = htons(SERVERPORT);	//호스트 주소에서 네트워크 주소로 변환 ,포트번호(통신경로 설정)
retval = connect(tcp_sock, (SOCKADDR*)&serveradddr,  //서버주소와 연결
	sizeof(serveradddr)); //서버에  연결

if (retval == SOCKET_ERROR) err_quit("connect()");
// 데이터 통신에 사용할 변수 
char buf[500 + 1];
int len;
WaitRoom* waitroom = new WaitRoom(); //구조체정보를 생성하고 값대입
waitroom->current_player = 1;
waitroom->max_player = 4;
waitroom->room_state = 3;
int roombuf = 0;
// 서버와 데이터 통신
int maxCnt = 1; //보내는회수
while (1) {
	//// 데이터 입력
	//printf("\n[보낼 데이터] ");
	//if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
	//break;
	//// '\n' 문자 제거
	//len = strlen(buf);
	//if (buf[len - 1] == '\n')
	//buf[len - 1] = '\0';
	//if (strlen(buf) == 0)
	//break;
	// 데이터 보내기
	retval = send(tcp_sock, (char*)waitroom, sizeof(WaitRoom), 0);  //구조체변수를 서버에 보낸다. tcp connect
	if (retval == SOCKET_ERROR) {
		err_display("send()");
		break;
	}
	if (maxCnt-- < 1)
	{
		break;
	}

	retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));	//bind 로 server address를  소켓과 묶어준다.
	if (retval == SOCKET_ERROR) err_quit("bind()");
	retval = listen(listen_sock, SOMAXCONN);	 //소켓이 listen 상태로 들어간다.
	if (retval == SOCKET_ERROR) err_quit("listen()");
	// 데이터 통신에 사용할 변수
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	HANDLE hThread;
	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen); // 클라의 connect 를 accept 해준다. 이때(accept) 통신용 소켓이 하나더 만들어진다는 점에 주의한다.
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}
		//접속한 클라이언트 정보 출력
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
		hThread = CreateThread(NULL, 0, ProcessClient, (LPVOID)client_sock, 0, NULL); ///ProcessClient 라는 이름의 쓰레드 함수를 만들어 쓰레드를 돌린다.
		if (hThread == NULL) { closesocket(client_sock); }
		else { CloseHandle(hThread); }
	}
	// closesocket()
	closesocket(listen_sock);
	WSACleanup();
	return 0;


====================================================================================================================================
07 db,sql,js 서버쪽 코드 서버 클라 분리내용 이해및  설명부분 (서버 클라 분리 연결 이해과정)	
	
	App.post(”name”,function(req,res){
Dbconnect.getConnection(async function (conn){ //db연결
	Var sql = “Select cash,freecash,id, FROM userinfo WHERE userid
	Var row = req[’body’]
	Var params= row[’user_id’]
	...
	Var func = await func2(conn...)//동기화를 위해 await를 한다.물론 future,promise등의 방법이 있으나 await이 동기화가 편하다라고 직접 서치를통해 얻은내용이다.
	....
	Responsehelper.senddata(res,rows)//result를 row로 클라에 보내준다.
	//sql에 데이터를 보낸다.
	 ....
Responsehelper.sendreturncode(res,1,0등등...)//정보를 보냈다는 신호를 서버가 보내면 
//클라이언트단에서 코드를 받고 클라이언트에서 처리를 하면된다.
//만약 서버단에서 1을 성공신호로 보낸다면 1을 보내기전 sql에서 데이터를 갱신한다. 갱신동기화가 된후에
//클라이언트에서 서버측에서 갱신된data(sql의값)값을 받아온다. 

====================================================================================================================================	
	
	
		
		
		
		
		
		
		
		
		
		
		
		
		
		
