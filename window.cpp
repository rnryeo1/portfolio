


<<<<<<< HEAD
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
=======
 猷⑦듃�젣�옉 �븣怨좊━利� �빑�떖 �냼�뒪 諛� �꽕紐� 諛� �뒪�젅�뱶 �젙由�
1.寃쎈줈�쓽 泥섏쓬(�뱶�씪�씠釉뚭꼍濡�, A, B, C�뱶�씪�씠釉뚮벑) m_bRootDir 蹂��닔濡� �몴�쁽�빀�땲�떎.
2.pdr, cdr, avi, �뵒�젆�넗由� �뙆�씪留� 蹂댁씠寃� �빀�땲�떎.
3. 寃쎈줈瑜� ����꽌 �뱾�뼱媛� �닔濡� m_CurrentDir �뒗 寃쎈줈 �씠由꾩씠 怨꾩냽 �뜑�빐吏묐땲�떎.洹몃━怨� �씠�쟾 寃쎈줈瑜� ����옣�빐�몼�땲�떎.
4. �쁽�옱 寃쎈줈�뿉�꽌 �굹�삱寃쎌슦 �씠�쟾寃쎈줈瑜� �씠�쟾�뿉 ����옣�뻽�뜕 寃쎈줈濡� 諛붽퓭以띾땲�떎.洹몃━怨� CString 蹂��닔�씤 �쁽�옱 �뵒�젆�꽣由� 蹂��닔�룄 ""怨듬갚臾몄옄濡� 諛붽퓭以띾땲�떎 寃쎈줈媛� 怨꾩냽 �뜑�빐吏� 寃쎌슦 path媛� �꼫臾� 湲몄뼱吏�硫� CString 蹂��닔媛� 洹몃쭖��� string �뜲�씠�꽣瑜� ����옣�븷 �닔 �뾾湲� �뻹臾몄뿉 �삤瑜섍�� 諛쒖깮�빀�땲�떎.
5. CWinThread * m_pThread; 蹂��닔瑜� �깮�꽦  m_pThread = AfxBeginThread(RunThread, this);
5 - 1. AfxBeginThread�뿉�꽌 RunThread�씪�뒗 �뙆�씪 �씫湲� �벐�젅�뱶 �깮�꽦�쓣 �븳 �썑 諛깃렇�씪�슫�뱶�뿉�꽌 �떎�뻾 �릺寃� �븳�떎.�옉�뾽�옄 �뒪�젅�뱶瑜� �궗�슜�븯�뿬 硫��떚 �뒪�젅�뱶 �솚寃쎌뿉�꽌 �룞�옉 �븯�룄濡� �븳�떎.
6. CWinThread * m_pMakeTimeThread;
m_pMakeTimeThread = AfxBeginThread(RunMakeTimeThread, this);
RunMakeTimeThread �븿�닔�뒗 �뙆�씪�씫湲� �븿�닔 �씠湲� �븣臾몄뿉 �벐�젅�뱶濡� 泥섎━�빐�빞 �븳�떎.
�솢�깘�븯硫� 硫붿씤�벐�젅�뱶媛� 紐⑤몢 泥섎━�븷 寃쎌슦 �씫湲� �냽�룄媛� �쁽����엳 �뒓�젮吏�湲� �븣臾몄씠�떎.
諛깃렇�씪�슫�뱶 �뿉�꽌 泥섎━ �냼�뒪
>>>>>>> e340c69db89f2133aada2c68ab0099feb755a92a
static UINT RunMakeTimeThread(LPVOID pParam);

UINT CMyDeanUIView::RunMakeTimeThread(LPVOID pParam)
{
	CMyDeanUIView* pView = (CMyDeanUIView*)pParam;

	pView->SendMessage(WM_READ_LIST_START);
<<<<<<< HEAD
	pView->GetFileList(); //파일 목록을 리스트에 넣어준다. (무거운작업)
=======
	pView->GetFileList(); //�뙆�씪 紐⑸줉�쓣 由ъ뒪�듃�뿉 �꽔�뼱以��떎. (臾닿굅�슫�옉�뾽)
>>>>>>> e340c69db89f2133aada2c68ab0099feb755a92a
	pView->SendMessage(WM_READ_LIST_DONE);
}









<<<<<<< HEAD
블랙박스 루트제작 알고리즘 핵심 소스
=======
猷⑦듃�젣�옉 �븣怨좊━利� �빑�떖 �냼�뒪
>>>>>>> e340c69db89f2133aada2c68ab0099feb755a92a

void Computer::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{

<<<<<<< HEAD
	if (!m_bbloaded) //블랙박스 로딩이 아닌상태에서만 .
=======
	if (!m_bbloaded) //釉붾옓諛뺤뒪 濡쒕뵫�씠 �븘�땶�긽�깭�뿉�꽌留� .
>>>>>>> e340c69db89f2133aada2c68ab0099feb755a92a
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
<<<<<<< HEAD
		else
=======
		else 
>>>>>>> e340c69db89f2133aada2c68ab0099feb755a92a
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


<<<<<<< HEAD
			if (!strcmp(strSel, "..") && m_idirDepthCnt >= 1) //,,이아니고
=======
			if (!strcmp(strSel, "..") && m_idirDepthCnt >= 1) //,,�씠�븘�땲怨�
>>>>>>> e340c69db89f2133aada2c68ab0099feb755a92a
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
<<<<<<< HEAD
			else  //동영상 파일이 아닐때 
=======
			else  //�룞�쁺�긽 �뙆�씪�씠 �븘�땺�븣 
>>>>>>> e340c69db89f2133aada2c68ab0099feb755a92a
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


<<<<<<< HEAD
			int time = m_ListView1.GetItemData(i);				// 현재 저장하지 않음.
=======
			int time = m_ListView1.GetItemData(i);				// �쁽�옱 ����옣�븯吏� �븡�쓬.
>>>>>>> e340c69db89f2133aada2c68ab0099feb755a92a

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
<<<<<<< HEAD
		else if (m_idirDepthCnt >= 0 && !strcmp(strSel, "..")) //공백이아니고 ..
=======
		else if (m_idirDepthCnt >= 0 && !strcmp(strSel, "..")) //怨듬갚�씠�븘�땲怨� ..
>>>>>>> e340c69db89f2133aada2c68ab0099feb755a92a
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
<<<<<<< HEAD
				m_bDirChanged = false; //파일정리되기전 
=======
				m_bDirChanged = false; //�뙆�씪�젙由щ릺湲곗쟾 
>>>>>>> e340c69db89f2133aada2c68ab0099feb755a92a
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
<<<<<<< HEAD
				m_bDirChanged = false; //파일정리되기전 
=======
				m_bDirChanged = false; //�뙆�씪�젙由щ릺湲곗쟾 
>>>>>>> e340c69db89f2133aada2c68ab0099feb755a92a
				m_pThread = AfxBeginThread(RunThread, this);
				hThread = m_pThread->m_hThread;
				m_bRun = true;
				m_bPlayNextCom = true;
			}


		}

	}

<<<<<<< HEAD
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
=======
	MFC�뒗 �궗�슜�옄 �씤�꽣�럹�씠�뒪 �뒪�젅�뱶��� �옉�뾽�옄 �뒪�젅�뱶�씪�뒗 �몢 媛�吏� �쑀�삎�쓽 �뒪�젅�뱶瑜� 援щ텇�븳�떎.
		�궗�슜�옄 �씤�꽣�럹�씠�뒪 �뒪�젅�뱶 媛쒖껜�쓽 �삁濡쒕뒗 MFC�쓽 硫붿씤 �뒪�젅�뱶�씤 CWinApp媛� �엳�떎.
		�옉�뾽�옄 �뒪�젅�뱶�뒗 諛깃렇�씪�슫�뱶 �옉�뾽�씠�굹 �쑀吏� 愿�由� �옉�뾽�뿉 �쟻�빀�븯�떎.


		�옉�뾽�옄 �뒪�젅�뱶(Worker Thread)
		�듅�젙 �뿰�궛�씠�굹 �옉�뾽�쓣 �쐞�븳 �뒪�젅�뱶瑜� �씪而ル뒗�떎.
		吏곸젒 UI 而⑦듃濡ㅼ뿉 �젒洹쇳븯�뒗 寃껋쓣 沅뚯옣�븯吏� �븡�뒗�떎.
		UI �뒪�젅�뱶�뿉 硫붿떆吏�瑜� �쟾�떖�븯湲� �쐞�빐 PostMessage �삉�뒗 SendMessage瑜� �궗�슜�븳�떎.
		�궗�슜�옄 �씤�꽣�럹�씠�뒪 �뒪�젅�뱶(User - Interface Thread)
		�솕硫� 媛깆떊�씠�굹 洹몃젮吏��뒗 寃껋쿂�읆 '蹂댁씠�뒗 �옉�뾽'�쓣 泥섎━�븳�떎.
		而⑦듃濡ㅼ쓽 �씠踰ㅽ듃 泥섎━瑜� �떞�떦�븳�떎.


		�궗�슜�옄媛� 紐낅졊�뼱瑜� �엯�젰�븯硫� �꽣誘몃꼸�뿉�꽌 �옉�뾽�쓣 �엯�젰�븳 紐낅졊�쓣 �빐�꽍�븯�뿬 �떎�뻾�빀�땲�떎.洹몃━怨� 寃곌낵瑜� �솕硫댁뿉 異쒕젰�빀�땲�떎.洹몃윭硫� 異쒕젰�맂 寃곌낵 �솕硫댁쓣 蹂닿퀬 �떎�떆 紐낅졊�쓣 �엯�젰�븯�뒗 ����솕�떇 �옉�뾽�쓣 �닔�뻾�빀�땲�떎.�엯�젰�븳 紐낅졊�뼱 �떎�뻾�씠 寃곌낵媛� �굹�삱 �븣 源뚯�� 湲곕떎由щ뒗 諛⑹떇�씠 諛붾줈 �룷洹몃씪�슫�뱶 諛⑹떇 �엯�땲�떎.�룷洹몃씪�슫�뱶 �봽濡쒖꽭�뒪�씪怨� 留먰븯硫� �옉�뾽 �젣�뼱 痢〓㈃�뿉�꽌�뒗 �룷洹몃씪�슫�뱶 �옉�뾽�씠�씪怨� 留먰빀�땲�떎.
		�룷洹몃씪�슫�뱶 �옉�뾽��� �떎瑜� 紐낅졊�쓣 �엯�젰�븷 �닔 �뾾怨� 湲곕떎�젮�꽌 �엯�젰�빐�빞 �븳�떎.�씪諛섏쟻 紐낅졊�쓣 �떎�뻾 �엯�땲�떎.


		諛깃렇�씪�슫�뱶 湲곕뒫��� �봽濡쒖꽭�뒪媛� �떎�뻾�릺�뒗 �룞�븞 �떎瑜� �봽濡쒖꽭�뒪媛� �떎�뻾 媛��뒫�빀�땲�떎.�븯�굹�쓽 �돇�뿉�꽌 �뿬�윭 媛쒖쓽 �봽濡쒖꽭�뒪瑜� �룞�떆�뿉 �떎�뻾�븷 �닔 �엳�뒗 諛⑹떇�엯�땲�떎.
		諛깃렇�씪�슫�뱶 諛⑹떇�쑝濡� 紐낅졊�뼱瑜� �떎�뻾�븯硫� 怨㏓컮濡� �떎�쓬 紐낅졊�뼱瑜� �떎�뻾 媛��뒫�빀�땲�떎.�븘�슂�븳 �뿬�윭 �옉�뾽 �룞�떆�뿉 吏꾪뻾�븯硫댁꽌 �룷洹몃씪�슫�뱶 �옉�뾽�쓣 怨꾩냽 吏꾪뻾�븷 �닔 �엳�뒿�땲�떎.諛깃렇�씪�슫�뱶 �옉�뾽��� �빐�떦 紐낅졊�뼱 泥섎━媛� �삤�옒 嫄몃┫嫄� ���鍮꾪빐 諛깃렇�씪�슫�뱶瑜� �씠�슜�븯硫� �뿬�윭 �옉�뾽�쓣 �룞�떆�뿉 �닔�뻾�븷 �닔 �엳�떎.


		SendMessage & PostMessage �씠�빐�븯湲�
		SendMessage�뒗 �쐢�룄�슦 �봽濡쒖떆���(window procedure)瑜� 吏곸젒 �샇異쒗븯硫�, �봽濡쒖떆���媛� 硫붿떆吏�瑜� 泥섎━�븷 �븣 源뚯�� 諛섑솚�븯吏� �븡�뒿�땲�떎.利�, �븿�닔 �궡�뿉 �떎瑜� �븿�닔媛� �샇異쒕릺硫� 洹� �븿�닔媛� 諛섑솚�븷 �븣 源뚯�� 湲곕떎�젮�빞 �븯�벏�씠 �씪諛� �븿�닔 �샇異쒓낵 �룞�씪�븯寃� �룞�옉�빀�땲�떎.
		PostMessage�뒗 �샇異쒕맂 硫붿떆吏�媛� 硫붿떆吏� �걧�뿉 �뱾�뼱媛�硫�, �쐢�룄�슦 �봽濡쒖떆����뿉�꽌 �씠 硫붿떆吏�瑜� 泥섎━�븯寃� �맗�땲�떎.�씠寃껋씠 �쓽誘명븯�뒗 寃껋��, 硫붿떆吏�媛� 利됯컖 泥섎━�릺�뒗 寃껋씠 �븘�땲�씪 GetMessage()�뿉 �쓽�빐 �빐�꽍�맂 硫붿떆吏�媛� DispatchMessage()�뿉 �쓽�빐 �쐢�룄�슦 �봽濡쒖떆���濡� �쟾�떖�릺�뼱 泥섎━�맗�땲�떎.洹몃옒�꽌 PostMessage�뿉 �쓽�빐 �쟾�떖�맂 硫붿떆吏��뒗 �뼵�젣 泥섎━�맆 吏� �삁痢≫븯湲곌�� �뼱�졄�뒿�땲�떎.
		�몢 �븿�닔�쓽 李⑥씠瑜� �슂�빟�븯�옄硫� �떎�쓬怨� 媛숈뒿�땲�떎.


		SendMessage	PostMessage
		�쐢�룄�슦 �봽濡쒖떆���瑜� 吏곸젒 �샇異쒗븯硫�, �봽濡쒖떆���媛� 硫붿떆吏�瑜� 泥섎━�븷 �븣 源뚯�� 諛섑솚�븯吏� �븡�뒗�떎.硫붿떆吏� �걧�뿉 硫붿떆吏�媛� �궫�엯�릺硫�, �쐢�룄�슦 �봽濡쒖떆����뿉�꽌 硫붿떆吏�瑜� 泥섎━�븳�떎.�빐�떦 硫붿떆吏�媛� �뼵�젣 泥섎━�맆 吏� �삁痢≪씠 �뼱�졄�떎.
		�닚李⑥쟻�쑝濡� 泥섎━(sequentially)	鍮� �닚李⑥쟻�쑝濡� 泥섎━(not sequentially)
		�룞湲� 諛⑹떇(synchronous)	鍮꾨룞湲� 諛⑹떇(asynchronous)
>>>>>>> e340c69db89f2133aada2c68ab0099feb755a92a




<<<<<<< HEAD
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
=======
		�쐢�룄�슦 �뵒踰꾧퉭 紐⑤뱺 諛⑸쾿
		�뵒踰꾧렇 - callstack, 臾몄젣吏��젏�뿉�꽌 �떎�떆�떆�룄�쓣�슦湲�->breapoints, breapoints, error list, output, references
		1臾몄젣吏��젏�뿉�꽌 �떎�떆�떆�룄�쓣�슦湲�
		2breakpoints
		3callstack(諛묒뿉�꽌遺��꽣 �쐞濡쒕큵) 以묒슂
		4..�굹癒몄���벑�벑..�씠�슜
		________________________________________
		Call Stack(諛묒뿉�꽌遺��꽣 �쐞濡쒕큵)
		Ouput
		Breakpoints
		臾몄젣�긽�솴留뚮뱾怨� �떎�떆�떆�룄 �겢由�
>>>>>>> e340c69db89f2133aada2c68ab0099feb755a92a


