


���ڽ� ��Ʈ���� �˰��� �ٽ� �ҽ� �� ���� �� ������ ����
1.����� ó��(����̺���, A, B, C����̺��) m_bRootDir ������ ǥ���մϴ�.
2.pdr, cdr, avi, ���丮 ���ϸ� ���̰� �մϴ�.
3. ��θ� Ÿ�� �� ���� m_CurrentDir �� ��� �̸��� ��� �������ϴ�.�׸��� ���� ��θ� �����صӴϴ�.
4. ���� ��ο��� ���ð�� ������θ� ������ �����ߴ� ��η� �ٲ��ݴϴ�.�׸��� CString ������ ���� ���͸� ������ ""���鹮�ڷ� �ٲ��ݴϴ� ��ΰ� ��� ������ ��� path�� �ʹ� ������� CString ������ �׸��� string �����͸� ������ �� ���� ������ ������ �߻��մϴ�.
5. CWinThread * m_pThread; ������ ����  m_pThread = AfxBeginThread(RunThread, this);
5 - 1. AfxBeginThread���� RunThread��� ���� �б� ������ ������ �� �� ��׶��忡�� ���� �ǰ� �Ѵ�.�۾��� �����带 ����Ͽ� ��Ƽ ������ ȯ�濡�� ���� �ϵ��� �Ѵ�.
6. CWinThread * m_pMakeTimeThread;
m_pMakeTimeThread = AfxBeginThread(RunMakeTimeThread, this);
RunMakeTimeThread �Լ��� �����б� �Լ� �̱� ������ ������� ó���ؾ� �Ѵ�.
�ֳ��ϸ� ���ξ����尡 ��� ó���� ��� �б� �ӵ��� ������ �������� �����̴�.
��׶��� ���� ó�� �ҽ�
static UINT RunMakeTimeThread(LPVOID pParam);

UINT CMyDeanUIView::RunMakeTimeThread(LPVOID pParam)
{
	CMyDeanUIView* pView = (CMyDeanUIView*)pParam;

	pView->SendMessage(WM_READ_LIST_START);
	pView->GetFileList(); //���� ����� ����Ʈ�� �־��ش�. (���ſ��۾�)
	pView->SendMessage(WM_READ_LIST_DONE);
}









���ڽ� ��Ʈ���� �˰��� �ٽ� �ҽ�

void Computer::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{

	if (!m_bbloaded) //���ڽ� �ε��� �ƴѻ��¿����� .
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


			if (!strcmp(strSel, "..") && m_idirDepthCnt >= 1) //,,�̾ƴϰ�
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
			else  //������ ������ �ƴҶ� 
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


			int time = m_ListView1.GetItemData(i);				// ���� �������� ����.

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
		else if (m_idirDepthCnt >= 0 && !strcmp(strSel, "..")) //�����̾ƴϰ� ..
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
				m_bDirChanged = false; //���������Ǳ��� 
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
				m_bDirChanged = false; //���������Ǳ��� 
				m_pThread = AfxBeginThread(RunThread, this);
				hThread = m_pThread->m_hThread;
				m_bRun = true;
				m_bPlayNextCom = true;
			}


		}

	}

	MFC�� ����� �������̽� ������� �۾��� �������� �� ���� ������ �����带 �����Ѵ�.
		����� �������̽� ������ ��ü�� ���δ� MFC�� ���� �������� CWinApp�� �ִ�.
		�۾��� ������� ��׶��� �۾��̳� ���� ���� �۾��� �����ϴ�.


		�۾��� ������(Worker Thread)
		Ư�� �����̳� �۾��� ���� �����带 ���´´�.
		���� UI ��Ʈ�ѿ� �����ϴ� ���� �������� �ʴ´�.
		UI �����忡 �޽����� �����ϱ� ���� PostMessage �Ǵ� SendMessage�� ����Ѵ�.
		����� �������̽� ������(User - Interface Thread)
		ȭ�� �����̳� �׷����� ��ó�� '���̴� �۾�'�� ó���Ѵ�.
		��Ʈ���� �̺�Ʈ ó���� ����Ѵ�.


		����ڰ� ��ɾ �Է��ϸ� �͹̳ο��� �۾��� �Է��� ����� �ؼ��Ͽ� �����մϴ�.�׸��� ����� ȭ�鿡 ����մϴ�.�׷��� ��µ� ��� ȭ���� ���� �ٽ� ����� �Է��ϴ� ��ȭ�� �۾��� �����մϴ�.�Է��� ��ɾ� ������ ����� ���� �� ���� ��ٸ��� ����� �ٷ� ���׶��� ��� �Դϴ�.���׶��� ���μ������ ���ϸ� �۾� ���� ���鿡���� ���׶��� �۾��̶�� ���մϴ�.
		���׶��� �۾��� �ٸ� ����� �Է��� �� ���� ��ٷ��� �Է��ؾ� �Ѵ�.�Ϲ��� ����� ���� �Դϴ�.


		��׶��� ����� ���μ����� ����Ǵ� ���� �ٸ� ���μ����� ���� �����մϴ�.�ϳ��� ������ ���� ���� ���μ����� ���ÿ� ������ �� �ִ� ����Դϴ�.
		��׶��� ������� ��ɾ �����ϸ� ��ٷ� ���� ��ɾ ���� �����մϴ�.�ʿ��� ���� �۾� ���ÿ� �����ϸ鼭 ���׶��� �۾��� ��� ������ �� �ֽ��ϴ�.��׶��� �۾��� �ش� ��ɾ� ó���� ���� �ɸ��� ����� ��׶��带 �̿��ϸ� ���� �۾��� ���ÿ� ������ �� �ִ�.


		SendMessage & PostMessage �����ϱ�
		SendMessage�� ������ ���ν���(window procedure)�� ���� ȣ���ϸ�, ���ν����� �޽����� ó���� �� ���� ��ȯ���� �ʽ��ϴ�.��, �Լ� ���� �ٸ� �Լ��� ȣ��Ǹ� �� �Լ��� ��ȯ�� �� ���� ��ٷ��� �ϵ��� �Ϲ� �Լ� ȣ��� �����ϰ� �����մϴ�.
		PostMessage�� ȣ��� �޽����� �޽��� ť�� ����, ������ ���ν������� �� �޽����� ó���ϰ� �˴ϴ�.�̰��� �ǹ��ϴ� ����, �޽����� �ﰢ ó���Ǵ� ���� �ƴ϶� GetMessage()�� ���� �ؼ��� �޽����� DispatchMessage()�� ���� ������ ���ν����� ���޵Ǿ� ó���˴ϴ�.�׷��� PostMessage�� ���� ���޵� �޽����� ���� ó���� �� �����ϱⰡ ��ƽ��ϴ�.
		�� �Լ��� ���̸� ������ڸ� ������ �����ϴ�.


		SendMessage	PostMessage
		������ ���ν����� ���� ȣ���ϸ�, ���ν����� �޽����� ó���� �� ���� ��ȯ���� �ʴ´�.�޽��� ť�� �޽����� ���ԵǸ�, ������ ���ν������� �޽����� ó���Ѵ�.�ش� �޽����� ���� ó���� �� ������ ��ƴ�.
		���������� ó��(sequentially)	�� ���������� ó��(not sequentially)
		���� ���(synchronous)	�񵿱� ���(asynchronous)




		������ ����� ��� ���
		����� - callstack, ������������ �ٽýõ�����->breapoints, breapoints, error list, output, references
		1������������ �ٽýõ�����
		2breakpoints
		3callstack(�ؿ������� ���κ�) �߿�
		4..���������..�̿�
		________________________________________
		Call Stack(�ؿ������� ���κ�)
		Ouput
		Breakpoints
		������Ȳ����� �ٽýõ� Ŭ��


