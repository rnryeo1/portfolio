


블랙박스 루트제작 알고리즘 핵심 소스 및 설명 및 스레드 정리
1.경로의 처음(드라이브경로, A, B, C드라이브등) m_bRootDir 변수로 표현합니다.
2.pdr, cdr, avi, 디렉토리 파일만 보이게 합니다.
3. 경로를 타서 들어갈 수록 m_CurrentDir 는 경로 이름이 계속 더해집니다.그리고 이전 경로를 저장해둡니다.
4. 현재 경로에서 나올경우 이전경로를 이전에 저장했던 경로로 바꿔줍니다.그리고 CString 변수인 현재 디렉터리 변수도 ""공백문자로 바꿔줍니다 경로가 계속 더해질 경우 path가 너무 길어지면 CString 변수가 그많은 string 데이터를 저장할 수 없기 떄문에 오류가 발생합니다.
5. CWinThread * m_pThread; 변수를 생성  m_pThread = AfxBeginThread(RunThread, this);
5 - 1. AfxBeginThread에서 RunThread라는 파일 읽기 쓰레드 생성을 한 후 백그라운드에서 실행 되게 한다.작업자 스레드를 사용하여 멀티 스레드 환경에서 동작 하도록 한다.
6. CWinThread * m_pMakeTimeThread;
m_pMakeTimeThread = AfxBeginThread(RunMakeTimeThread, this);
RunMakeTimeThread 함수는 파일읽기 함수 이기 때문에 쓰레드로 처리해야 한다.
왜냐하면 메인쓰레드가 모두 처리할 경우 읽기 속도가 현저히 느려지기 때문이다.
백그라운드 에서 처리 소스
static UINT RunMakeTimeThread(LPVOID pParam);

UINT CMyDeanUIView::RunMakeTimeThread(LPVOID pParam)
{
	CMyDeanUIView* pView = (CMyDeanUIView*)pParam;

	pView->SendMessage(WM_READ_LIST_START);
	pView->GetFileList(); //파일 목록을 리스트에 넣어준다. (무거운작업)
	pView->SendMessage(WM_READ_LIST_DONE);
}









블랙박스 루트제작 알고리즘 핵심 소스

void Computer::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{

	if (!m_bbloaded) //블랙박스 로딩이 아닌상태에서만 .
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
			else  //동영상 파일이 아닐때 
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


			int time = m_ListView1.GetItemData(i);				// 현재 저장하지 않음.

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
		else if (m_idirDepthCnt >= 0 && !strcmp(strSel, "..")) //공백이아니고 ..
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
				m_bDirChanged = false; //파일정리되기전 
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
				m_bDirChanged = false; //파일정리되기전 
				m_pThread = AfxBeginThread(RunThread, this);
				hThread = m_pThread->m_hThread;
				m_bRun = true;
				m_bPlayNextCom = true;
			}


		}

	}

	MFC는 사용자 인터페이스 스레드와 작업자 스레드라는 두 가지 유형의 스레드를 구분한다.
		사용자 인터페이스 스레드 개체의 예로는 MFC의 메인 스레드인 CWinApp가 있다.
		작업자 스레드는 백그라운드 작업이나 유지 관리 작업에 적합하다.


		작업자 스레드(Worker Thread)
		특정 연산이나 작업을 위한 스레드를 일컫는다.
		직접 UI 컨트롤에 접근하는 것을 권장하지 않는다.
		UI 스레드에 메시지를 전달하기 위해 PostMessage 또는 SendMessage를 사용한다.
		사용자 인터페이스 스레드(User - Interface Thread)
		화면 갱신이나 그려지는 것처럼 '보이는 작업'을 처리한다.
		컨트롤의 이벤트 처리를 담당한다.


		사용자가 명령어를 입력하면 터미널에서 작업을 입력한 명령을 해석하여 실행합니다.그리고 결과를 화면에 출력합니다.그러면 출력된 결과 화면을 보고 다시 명령을 입력하는 대화식 작업을 수행합니다.입력한 명령어 실행이 결과가 나올 때 까지 기다리는 방식이 바로 포그라운드 방식 입니다.포그라운드 프로세스라고 말하며 작업 제어 측면에서는 포그라운드 작업이라고 말합니다.
		포그라운드 작업은 다른 명령을 입력할 수 없고 기다려서 입력해야 한다.일반적 명령을 실행 입니다.


		백그라운드 기능은 프로세스가 실행되는 동안 다른 프로세스가 실행 가능합니다.하나의 쉘에서 여러 개의 프로세스를 동시에 실행할 수 있는 방식입니다.
		백그라운드 방식으로 명령어를 실행하면 곧바로 다음 명령어를 실행 가능합니다.필요한 여러 작업 동시에 진행하면서 포그라운드 작업을 계속 진행할 수 있습니다.백그라운드 작업은 해당 명령어 처리가 오래 걸릴걸 대비해 백그라운드를 이용하면 여러 작업을 동시에 수행할 수 있다.


		SendMessage & PostMessage 이해하기
		SendMessage는 윈도우 프로시저(window procedure)를 직접 호출하며, 프로시저가 메시지를 처리할 때 까지 반환하지 않습니다.즉, 함수 내에 다른 함수가 호출되면 그 함수가 반환할 때 까지 기다려야 하듯이 일반 함수 호출과 동일하게 동작합니다.
		PostMessage는 호출된 메시지가 메시지 큐에 들어가며, 윈도우 프로시저에서 이 메시지를 처리하게 됩니다.이것이 의미하는 것은, 메시지가 즉각 처리되는 것이 아니라 GetMessage()에 의해 해석된 메시지가 DispatchMessage()에 의해 윈도우 프로시저로 전달되어 처리됩니다.그래서 PostMessage에 의해 전달된 메시지는 언제 처리될 지 예측하기가 어렵습니다.
		두 함수의 차이를 요약하자면 다음과 같습니다.


		SendMessage	PostMessage
		윈도우 프로시저를 직접 호출하며, 프로시저가 메시지를 처리할 때 까지 반환하지 않는다.메시지 큐에 메시지가 삽입되며, 윈도우 프로시저에서 메시지를 처리한다.해당 메시지가 언제 처리될 지 예측이 어렵다.
		순차적으로 처리(sequentially)	비 순차적으로 처리(not sequentially)
		동기 방식(synchronous)	비동기 방식(asynchronous)




		윈도우 디버깅 모든 방법
		디버그 - callstack, 문제지점에서 다시시도띄우기->breapoints, breapoints, error list, output, references
		1문제지점에서 다시시도띄우기
		2breakpoints
		3callstack(밑에서부터 위로봄) 중요
		4..나머지등등..이용
		________________________________________
		Call Stack(밑에서부터 위로봄)
		Ouput
		Breakpoints
		문제상황만들고 다시시도 클릭


