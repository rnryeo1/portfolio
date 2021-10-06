
 

Black box route making algorithm core source and description and thread arrangement
1. The beginning of the path (drive path, A, B, C drive, etc.) is expressed by the m_bRootDir variable.
2.pdr,cdr,avi,directory Only files are visible.
3. As you enter the path, m_CurrentDir continues to be appended to the path name. And save the old path.
4. When exiting from the current path, the previous path is replaced with the previously saved path. And the current directory variable, which is a CString variable, is also replaced with a "" space character. If the path continues to be added
If the path becomes too long, an error occurs because the CString variable cannot store that much string data.
5. CWinThread* m_pThread; Create a variable m_pThread = AfxBeginThread(RunThread, this);
5-1. AfxBeginThread creates a file reading thread called RunThread and runs it in the background. It uses worker threads to operate in a multi-threaded environment.
6. CWinThread* m_pMakeTimeThread;
 m_pMakeTimeThread = AfxBeginThread(RunMakeTimeThread, this);
Because RunMakeTimeThread function is a file reading function, it should be processed as a thread.
This is because when the main thread processes everything, the read speed becomes significantly slower.
processing source in the background

static UINT RunMakeTimeThread(LPVOID pParam);

UINT CMyDeanUIView::RunMakeTimeThread(LPVOID pParam)
{
	CMyDeanUIView* pView = (CMyDeanUIView*)pParam;

	pView->SendMessage(WM_READ_LIST_START);
	pView->GetFileList(); //Adds a list of files to the list. (heavy work)
	pView->SendMessage(WM_READ_LIST_DONE);
}









Black box route making algorithm core source

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


When the user enters a command, the terminal interprets and executes the entered command. And print the result to the screen. Then look at the output screen
Re-entering the command is an interactive operation. In the foreground method, the input command execution waits for the result to appear.
It is said to be a foreground process, and in terms of job control, it is said to be a foreground job.
Foreground tasks cannot enter other commands and must wait. A common command is to run .


A background function allows other processes to run while the process is running. This is how you can run multiple processes simultaneously in one shell.
If a command is executed in the background method, the next command can be executed immediately. You can continue working in the foreground while running multiple tasks as needed at the same time.
Background tasks can perform multiple tasks at the same time by using the background in case the processing of the corresponding command takes a long time.


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

