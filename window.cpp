
 

블랙박스 경로 작성 알고리즘 핵심 소스 및 설명 및 스레드 배열
1. 경로의 시작(드라이브 경로, A, B, C 드라이브 등)은 m_bRootDir 변수로 표현됩니다.
2.pdr,cdr,avi,directory 파일만 보입니다.
3. 경로를 입력하면 m_CurrentDir이 경로 이름에 계속 추가됩니다. 그리고 이전 경로를 저장합니다.
4. 현재 경로에서 나갈 때 이전 경로는 이전에 저장한 경로로 대체됩니다. 그리고 CString 변수인 현재 디렉토리 변수도 "" 공백 문자로 대체됩니다. 경로가 계속 추가되면
경로가 너무 길어지면 CString 변수가 그만큼의 문자열 데이터를 저장할 수 없기 때문에 오류가 발생합니다.
5. CWinThread* m_pThread; 변수 만들기 m_pThread = AfxBeginThread(RunThread, this);
5-1. AfxBeginThread는 RunThread라는 파일 읽기 스레드를 만들고 백그라운드에서 실행합니다. 작업자 스레드를 사용하여 다중 스레드 환경에서 작동합니다.
6. CWinThread* m_pMakeTimeThread;
 m_pMakeTimeThread = AfxBeginThread(RunMakeTimeThread, this);
RunMakeTimeThread 함수는 파일 읽기 함수이므로 스레드로 처리해야 합니다.
메인 스레드가 모든 것을 처리할 때 읽기 속도가 현저히 느려지기 때문입니다.
백그라운드에서 소스 처리
static UINT RunMakeTimeThread(LPVOID pParam);

UINT CMyDeanUIView::RunMakeTimeThread(LPVOID pParam)
{
	CMyDeanUIView* pView = (CMyDeanUIView*)pParam;

	pView->SendMessage(WM_READ_LIST_START);
	pView->GetFileList(); //Adds a list of files to the list. (heavy work)
	pView->SendMessage(WM_READ_LIST_DONE);
}






 



블랙박스 경로 생성 알고리즘 핵심 소스

void Computer::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{

	if (!m_bbloaded) //Only when the black box is not loaded.
	{
		LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
		// TODO: Add your control notification handler code here
		CString strSel;
		LockWindowUpdate();
		m_ListView1.LockWindowUpdate();
		int i = m_ListView1.GetNextItem(-1, LVNI_SELECTED);
		if (i >= 0)
			strSel = m_ListView1.GetItemText(i, 0);

		if (m_bRootDir)
		{
			m_CurrentDir += strSel;
			m_idirDepthCnt += 1;   //
			m_CurrentDirBefore = m_CurrentDir; //first before 
		}
		else
		{

			if (m_idirDepthCnt >= 1) //c, c://blackbox
			{
				m_CurrentDirBefore = "";
				m_CurrentDirBefore = m_CurrentDir; //before dir
			}
			if (strstr(strSel, ".CDR") != NULL || strstr(strSel, ".cdr") != NULL ||
				strstr(strSel, ".PDR") != NULL || strstr(strSel, ".pdr") != NULL ||
				strstr(strSel, ".AVI") != NULL || strstr(strSel, ".avi") != NULL)
			{

			}
			else
			{
				m_CurrentDir += _T("\\") + strSel;
				if (strstr(strSel, ".CDR") == NULL || strstr(strSel, ".cdr") == NULL ||
					strstr(strSel, ".PDR") == NULL || strstr(strSel, ".pdr") == NULL ||
					strstr(strSel, ".AVI") == NULL || strstr(strSel, ".avi") == NULL)
				{
					TRACE("560line:%d\n", m_idirDepthCnt);
					TRACE("560line:%s strsel\n", strSel);
					//if(!strcmp(strSel,".."))
					m_idirDepthCnt++;
					if (!strcmp(strSel, ".."))
					{

						m_idirDepthCnt--;
						TRACE("566line:%d\n", m_idirDepthCnt);

						m_CurrentDir = "";
						CString temp = (LPTSTR)(LPCTSTR)m_CurrentDirBefore; //temp(before before)

						int nLen = temp.ReverseFind('\\');
						int nLen2 = nLen;
						if (nLen2 > 0)
							temp = temp.Left(nLen2);

						m_CurrentDir = temp;
					}
				}
				else
				{
					int a = 0;
				}


			}


			if (!strcmp(strSel, "..") && m_idirDepthCnt >= 1) //,,이아니고
			{
				TRACE("586:%d\n", m_idirDepthCnt);
				m_idirDepthCnt -= 1;
			}
			else if (strstr(strSel, ".CDR") == NULL || strstr(strSel, ".cdr") == NULL ||
				strstr(strSel, ".PDR") == NULL || strstr(strSel, ".pdr") == NULL ||
				strstr(strSel, ".AVI") == NULL || strstr(strSel, ".avi") == NULL)
			{
				int a = 0;
			}
			else  //When it is not a video file
			{
				//m_idirDepthCnt += 1;
				TRACE("what?\n");
			}
		}
		m_bRootDir = false;

		//if itemtext is pdr, cdr ,avi
		if (strstr(strSel, ".CDR") != NULL || strstr(strSel, ".cdr") != NULL ||
			strstr(strSel, ".PDR") != NULL || strstr(strSel, ".pdr") != NULL ||
			strstr(strSel, ".AVI") != NULL || strstr(strSel, ".avi") != NULL)
		{
			
			
				int time = m_ListView1.GetItemData(i);				// Currently not saving.

				TRACE("i = %d time = %d\n", i, time);
				TRACE("play_at_computer: %d\n", i);
				m_pWndView->PostMessage(WM_PLAY_AT_COMPUTER, i, time);
				m_bFileClicked = true;
				m_bPlayNextCom = false;
			
			m_PlayList.RemoveAll();
			for (i = 0; i < m_ListView1.GetItemCount(); i++) {
				CLIST clist;
				clist.type = m_ListView1.GetItemData(i);
				clist.path = m_CurrentDirBefore + _T("\\") + m_ListView1.GetItemText(i, 0);
				m_PlayList.Add(clist);
			}
	
			
			TRACE("%s %d strSel: %s\n", __FUNCTION__, __LINE__, strSel);
		}
		else if (m_idirDepthCnt >= 0 && !strcmp(strSel, "..")) //is not a blank ..
		{
			if (m_idirDepthCnt == 0)
			{
				m_CurrentDir = "";
				m_bRootDir = true;
			}

			TCHAR* changeDir = (TCHAR*)(LPCTSTR)m_CurrentDir;
			SetCurrentDirectory(changeDir);
			videoCount = 0;
			if (m_ListView1.DeleteAllItems()) {
				m_bDirChanged = false; //before the file is cleaned
				m_pThread = AfxBeginThread(RunThread, this);
				hThread = m_pThread->m_hThread;
				m_bRun = true;
				m_bPlayNextCom = true;
			}

			TRACE("646:strSel:%s\n", strSel);
			TRACE("646m_idirDepthCnt:%d\n", m_idirDepthCnt);
			TRACE("646 m_CurrentDir = {%s}\n", m_CurrentDir);
			
		}
		else if ((m_idirDepthCnt >= 1 && strcmp(strSel, "..") && strcmp(strSel, "")))
		{
			TRACE("637:strSel:%s\n", strSel);
			TRACE("637m_idirDepthCnt:%d\n", m_idirDepthCnt);
			TRACE("637 m_CurrentDir = {%s}\n", m_CurrentDir);
			TCHAR* changeDir = (TCHAR*)(LPCTSTR)m_CurrentDir;
			SetCurrentDirectory(changeDir);
			videoCount = 0;
			if (m_ListView1.DeleteAllItems()) {
				m_bDirChanged = false; //before the file is cleaned
				m_pThread = AfxBeginThread(RunThread, this);
				hThread = m_pThread->m_hThread;
				m_bRun = true;
				m_bPlayNextCom = true;
			}

			
		}

}

	
	
	

	
UINT Computer::RunThread(LPVOID pParam)
{
	Computer* g_pDlg = (Computer*)pParam;

	CFileFind finder;

	TCHAR currentDir[256];

	int ch, drive, curdrive;
	static char path[_MAX_PATH];

	BOOL bWorking = finder.FindFile(g_pDlg->m_CurrentDir + _T("\\*.*"));

	CString fileName;

	LVITEM item;

	int i1 = 0;
	int j1 = 0;
	int k1 = 1;

	int nDrive = 0;
	int index;
	bool bAscending = true;

	CString strSel;
	int i = g_pDlg->m_ListView1.GetNextItem(-1, LVNI_SELECTED);
	if(i >= 0)
		strSel = g_pDlg->m_ListView1.GetItemText(i, 0);

	g_pDlg->m_ListView1.DeleteAllItems();
	g_pDlg->m_PlayList.RemoveAll();
	g_pDlg->m_DirList.RemoveAll();

	

	if (!g_pDlg->m_bRootDir) {

		// If it is not root, ".." is added unconditionally.
		item.iImage = 1;									//DIROUT
		item.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;
		item.iItem = 0;
		item.iSubItem = 0;
		item.pszText = _T("..");
		index = g_pDlg->m_ListView1.InsertItem(&item);
		g_pDlg->m_ListView1.SetItemData(index, 1);

		BOOL bWorking = finder.FindFile(g_pDlg->m_CurrentDir + _T("\\*.*"));

		while (bWorking) {

			bWorking = finder.FindNextFile();

			TRACE("%d, %d, %d, %d, %d, %d, %d, %d, {%s}\n",
				finder.IsNormal(), finder.IsArchived(), finder.IsSystem(), finder.IsHidden(), finder.IsCompressed(), finder.IsTemporary(), finder.IsReadOnly(), finder.IsDirectory(),
				finder.GetFileName());

			fileName = finder.GetFileName();

			if (finder.IsDots()) {	// "." 과 ".."은 무시
				continue;
			}
			else if (finder.IsArchived()) {

				if (strstr(fileName, ".CDR") != NULL || strstr(fileName, ".cdr") != NULL ||
					strstr(fileName, ".PDR") != NULL || strstr(fileName, ".pdr") != NULL ||
					strstr(fileName, ".AVI") != NULL || strstr(fileName, ".avi") != NULL) {

					item.iImage = 2;
					item.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;
					item.iItem = 0;
					item.iSubItem = 0;
					item.pszText = fileName.GetBuffer(0);
					index = g_pDlg->m_ListView1.InsertItem(&item);
					g_pDlg->m_ListView1.SetItemData(index, 2);

					CLIST clist;
					clist.type = 2;
					clist.path = fileName.GetBuffer(0);
					if (clist.type == 2)
						g_pDlg->m_PlayList.Add(clist);

					g_pDlg->videoCount++;
				}
			}

			//현상태 && finder.IsDirectory() 제거 및 !!finder.IsReadOnly() 제거
			else if (!finder.IsSystem() && !finder.IsHidden() && !finder.IsCompressed() && !finder.IsTemporary()
				 /*&& !finder.IsReadOnly()*//* && finder.IsDirectory()*/
				&& !finder.IsNormal() && !finder.IsSerializable()) {
				item.iImage = 1;
				item.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;
				item.iItem = 0;
				item.iSubItem = 0;
				item.pszText = fileName.GetBuffer(0);
				index = g_pDlg->m_ListView1.InsertItem(&item);

				g_pDlg->m_ListView1.SetItemData(index, 1);

				CLIST clist;
				clist.type = 1;
				clist.path = fileName.GetBuffer(0);
				if (clist.type == 1)
					g_pDlg->m_DirList.Add(clist);
			}
		}

		qsort((void*)g_pDlg->m_PlayList.GetData(), g_pDlg->m_PlayList.GetSize(), sizeof(CLIST), g_pDlg->Compare);
		qsort((void*)g_pDlg->m_DirList.GetData(), g_pDlg->m_DirList.GetSize(), sizeof(CLIST), g_pDlg->Compare);
		g_pDlg->m_ListView1.DeleteAllItems();

		item.iImage = 1;
		item.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;
		item.iItem = 0;
		item.iSubItem = 0;
		item.pszText = LPSTR(LPCTSTR(".."));
		*item.pszText;
		item.pszText;
		g_pDlg->m_ListView1.InsertItem(&item);

		for (int b = 0; b < g_pDlg->m_DirList.GetCount(); b++)
		{
			item.iImage = 1; //dirout

			item.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;
			item.iItem = b + 1; //0;
			item.iSubItem = 0;
			item.pszText = LPSTR(LPCTSTR(g_pDlg->m_DirList.GetAt(b).path));
			*item.pszText;
			item.pszText;
			index = g_pDlg->m_ListView1.InsertItem(&item);
			g_pDlg->m_ListView1.SetItemData(index, 1);
			//g_pDlg->m_ListView1.InsertItem(&item);
			k1++;
		}
		for (int a = 0; a < g_pDlg->m_PlayList.GetCount(); a++)
		{
			item.iImage = 2; //cdr
			item.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;
			item.iItem = k1 + 1 + a; //0;
			item.iSubItem = 0;
			item.pszText = LPSTR(LPCTSTR(g_pDlg->m_PlayList.GetAt(a).path));
			*item.pszText;
			item.pszText;
			index = g_pDlg->m_ListView1.InsertItem(&item);
			g_pDlg->m_ListView1.SetItemData(index, 2);
			//g_pDlg->m_ListView1.InsertItem(&item);

		}
	}
	else {
		if (g_pDlg->m_idirDepthCnt == 0) {
			CFileFind finder;

			char szDriveBuf[256] = { 0, };
			UINT nCount = GetLogicalDriveStrings(256, szDriveBuf);
			char* pBufIndex = szDriveBuf;
			CString localcurrentDriveDir;
			LVITEM item;
			for (int i = 0; i < nCount / 4; i++)
			{
				CString cBufIndex = (LPCSTR)(LPSTR)pBufIndex;
				BOOL bWorking = finder.FindFile(cBufIndex + _T("*.*"));
				BOOL finded = false;

				while (bWorking) {
					bWorking = finder.FindNextFile();

					if (finder.IsArchived() || finder.IsDirectory()) {
						g_pDlg->DriveStringArr[i] = pBufIndex;
						finded = true;
					}
				}
				if (finded)
				{
					item.iImage = 5; //Drive
					item.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;
					item.iItem = i; //0;
					item.iSubItem = 0;
					item.pszText = LPSTR(LPCTSTR(g_pDlg->DriveStringArr[i]));
					index = g_pDlg->m_ListView1.InsertItem(&item);
					g_pDlg->m_ListView1.SetItemData(index, 0);
					finded = false;
				}
				pBufIndex += 4;
			}

			g_pDlg->m_idirDepthCnt = 0;
		}
	}

	g_pDlg->m_bRun = false;
	g_pDlg->m_pThread = NULL;
	g_pDlg->m_bFileClicked = true;
	Sleep(250); //만약 오류생길경우 on_play에서..
	g_pDlg->m_bDirChanged = true;  //파일정리된 후 

	return 0;
}
	
	
	
	
MFC distinguishes between two types of threads: user interface threads and worker threads.
An example of a user interface thread object is CWinApp, MFC's main thread.
Worker threads are suitable for background work or maintenance tasks.


Worker Thread
A thread for a specific operation or task.
Direct access to UI controls is discouraged.
Use PostMessage or SendMessage to deliver a message to the UI thread.
User-Interface Thread
Handles 'visible tasks' such as updating the screen or being drawn.
Responsible for event handling of the control.
MFC는 사용자 인터페이스 스레드와 작업자 스레드의 두 가지 유형의 스레드를 구분합니다.
사용자 인터페이스 스레드 개체의 예는 MFC의 주 스레드인 CWinApp입니다.
작업자 스레드는 백그라운드 작업 또는 유지 관리 작업에 적합합니다.


작업자 스레드
특정 작업이나 작업에 대한 스레드입니다.
UI 컨트롤에 직접 액세스하는 것은 권장되지 않습니다.
PostMessage 또는 SendMessage를 사용하여 UI 스레드에 메시지를 전달합니다.
사용자 인터페이스 스레드
화면 업데이트 또는 그리기와 같은 '보이는 작업'을 처리합니다.
컨트롤의 이벤트 처리를 담당합니다.
	


When the user enters a command, the terminal interprets and executes the entered command. And print the result to the screen. Then look at the output screen
Re-entering the command is an interactive operation. In the foreground method, the input command execution waits for the result to appear.
It is said to be a foreground process, and in terms of job control, it is said to be a foreground job.
Foreground tasks cannot enter other commands and must wait. A common command is to run .


A background function allows other processes to run while the process is running. This is how you can run multiple processes simultaneously in one shell.
If a command is executed in the background method, the next command can be executed immediately. You can continue working in the foreground while running multiple tasks as needed at the same time.
Background tasks can perform multiple tasks at the same time by using the background in case the processing of the corresponding command takes a long time.

사용자가 명령을 입력하면 단말은 입력된 명령을 해석하여 실행합니다. 그리고 결과를 화면에 출력합니다. 그런 다음 출력 화면을보십시오
명령을 다시 입력하는 것은 대화식 작업입니다. 포그라운드 방식에서 입력 명령 실행은 결과가 나타날 때까지 기다립니다.
포그라운드 프로세스라고 하며, 작업 제어 측면에서 포그라운드 작업이라고 합니다.
포그라운드 작업은 다른 명령을 입력할 수 없으며 기다려야 합니다. 일반적인 명령은 실행하는 것입니다.


백그라운드 기능을 사용하면 프로세스가 실행되는 동안 다른 프로세스를 실행할 수 있습니다. 이것은 하나의 쉘에서 동시에 여러 프로세스를 실행할 수 있는 방법입니다.
백그라운드 방식으로 명령어를 실행하면 바로 다음 명령어를 실행할 수 있다. 동시에 필요에 따라 여러 작업을 실행하면서 포그라운드에서 계속 작업할 수 있습니다.
백그라운드 작업은 해당 명령의 처리 시간이 오래 걸리는 경우 백그라운드를 사용하여 동시에 여러 작업을 수행할 수 있습니다.
	

Understanding SendMessage & PostMessage
SendMessage directly calls a window procedure and does not return until the procedure processes the message. That is, when another function is called within a function,
It behaves the same as a normal function call, as if it had to wait for the function to return.
In PostMessage, the called message is put into the message queue, and the window procedure handles this message. What this means is that the message is not processed immediately.
The message interpreted by GetMessage() is passed to the window procedure by DispatchMessage() for processing. So the message delivered by PostMessage is
It is difficult to predict when it will be processed.
To summarize the differences between the two functions:

 SendMessage	PostMessage

Calls the window procedure directly, and does not return until the procedure processes the message. A message is inserted into the message queue, and the message is processed in a window procedure.
It is difficult to predict when the message will be processed.
 process sequentially process not sequentially
 synchronous Asynchronous

SendMessage 및 PostMessage 이해하기
SendMessage는 창 프로시저를 직접 호출하고 프로시저가 메시지를 처리할 때까지 반환하지 않습니다. 즉, 함수 내에서 다른 함수가 호출될 때,
함수가 반환될 때까지 기다려야 하는 것처럼 일반 함수 호출과 동일하게 작동합니다.
PostMessage에서 호출된 메시지는 메시지 큐에 넣고 창 프로시저는 이 메시지를 처리합니다. 이것이 의미하는 바는 메시지가 즉시 처리되지 않는다는 것입니다.
GetMessage()에 의해 해석된 메시지는 처리를 위해 DispatchMessage()에 의해 창 프로시저에 전달됩니다. 따라서 PostMessage가 전달하는 메시지는
언제 처리될지 예측하기 어렵습니다.
두 함수의 차이점을 요약하면 다음과 같습니다.

 SendMessage 포스트메시지

창 프로시저를 직접 호출하고 프로시저가 메시지를 처리할 때까지 반환하지 않습니다. 메시지는 메시지 큐에 삽입되고 메시지는 창 프로시저에서 처리됩니다.
메시지가 처리될 시기를 예측하기 어렵습니다.
 순차적으로 처리 순차적으로 처리하지 않음
 동기 비동기


Windows Debugging All Methods
Debug-callstack, retry at problem point->breapoints,breapoints,error list ,output , references
1 Retry at the problem point
2 breakpoints
3callstack (view from bottom to top)
4. Use the rest, etc.
________________________________________
Call Stack (view from bottom to top)
Ouput
Breakpoints
Create a problem and click try again

모든 방법을 디버깅하는 Windows
디버그 호출 스택, 문제 지점에서 재시도->중점, 중단점, 오류 목록, 출력, 참조
1 문제 지점에서 재시도
2개의 중단점
3callstack(아래에서 위로 보기)
4. 나머지 등을 활용한다.
__________________________________________________________
호출 스택(아래에서 위로 보기)
출력
중단점
문제를 만들고 다시 시도를 클릭하세요.
