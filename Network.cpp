// ���� �ʱ�ȭ
WSADATA  wsa;
int retval;
if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)	//2.2����
return 1;
//Socket
SOCKET tcp_sock = socket(AF_INET, SOCK_STREAM, 0); //���ϻ���
if (tcp_sock == INVALID_SOCKET) err_quit("socket()");
//connect 
SOCKADDR_IN serveradddr;
ZeroMemory(&serveradddr, sizeof(serveradddr));
serveradddr.sin_family = AF_INET;
serveradddr.sin_addr.s_addr = inet_addr(SERVERIP);	//ip�ּҸ� ���ڷκ�ȯ
serveradddr.sin_port = htons(SERVERPORT);	//ȣ��Ʈ �ּҿ��� ��Ʈ��ũ �ּҷ� ��ȯ ,��Ʈ��ȣ(��Ű�� ����)
retval = connect(tcp_sock, (SOCKADDR*)&serveradddr,  //�����ּҿ� ����
	sizeof(serveradddr)); //������  ����

if (retval == SOCKET_ERROR) err_quit("connect()");
// ������ ��ſ� ����� ���� 
char buf[500 + 1];
int len;
WaitRoom* waitroom = new WaitRoom(); //����ü������ �����ϰ� ������
waitroom->current_player = 1;
waitroom->max_player = 4;
waitroom->room_state = 3;
int roombuf = 0;
// ������ ������ ���
int maxCnt = 1; //������ȸ��
while (1) {
	//// ������ �Է�
	//printf("\n[���� ������] ");
	//if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
	//break;
	//// '\n' ���� ����
	//len = strlen(buf);
	//if (buf[len - 1] == '\n')
	//buf[len - 1] = '\0';
	//if (strlen(buf) == 0)
	//break;
	// ������ ������
	retval = send(tcp_sock, (char*)waitroom, sizeof(WaitRoom), 0);  //����ü������ ������ ������. tcp connect
	if (retval == SOCKET_ERROR) {
		err_display("send()");
		break;
	}
	if (maxCnt-- < 1)
	{
		break;
	}

	retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));	//bind �� server address��  ���ϰ� �����ش�.
	if (retval == SOCKET_ERROR) err_quit("bind()");
	retval = listen(listen_sock, SOMAXCONN);	 //������ listen ���·� ����.
	if (retval == SOCKET_ERROR) err_quit("listen()");
	// ������ ��ſ� ����� ����
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	HANDLE hThread;
	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen); // Ŭ���� connect �� accept ���ش�. �̶�(accept) ��ſ� ������ �ϳ��� ��������ٴ� ���� �����Ѵ�.
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
			break;
		}
		//������ Ŭ���̾�Ʈ ���� ���
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
		hThread = CreateThread(NULL, 0, ProcessClient, (LPVOID)client_sock, 0, NULL); ///ProcessClient ��� �̸��� ������ �Լ��� ����� �����带 ������.
		if (hThread == NULL) { closesocket(client_sock); }
		else { CloseHandle(hThread); }
	}
	// closesocket()
	closesocket(listen_sock);
	WSACleanup();
	return 0;


