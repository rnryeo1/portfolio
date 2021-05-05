


<<<<<<< HEAD
ºí·¢¹Ú½º ·çÆ®Á¦ÀÛ ¾Ë°í¸®Áò ÇÙ½É ¼Ò½º ¹× ¼³¸í ¹× ½º·¹µå Á¤¸®
1.°æ·ÎÀÇ Ã³À½(µå¶óÀÌºê°æ·Î, A, B, Cµå¶óÀÌºêµî) m_bRootDir º¯¼ö·Î Ç¥ÇöÇÕ´Ï´Ù.
2.pdr, cdr, avi, µð·ºÅä¸® ÆÄÀÏ¸¸ º¸ÀÌ°Ô ÇÕ´Ï´Ù.
3. °æ·Î¸¦ Å¸¼­ µé¾î°¥ ¼ö·Ï m_CurrentDir ´Â °æ·Î ÀÌ¸§ÀÌ °è¼Ó ´õÇØÁý´Ï´Ù.±×¸®°í ÀÌÀü °æ·Î¸¦ ÀúÀåÇØµÓ´Ï´Ù.
4. ÇöÀç °æ·Î¿¡¼­ ³ª¿Ã°æ¿ì ÀÌÀü°æ·Î¸¦ ÀÌÀü¿¡ ÀúÀåÇß´ø °æ·Î·Î ¹Ù²ãÁÝ´Ï´Ù.±×¸®°í CString º¯¼öÀÎ ÇöÀç µð·ºÅÍ¸® º¯¼öµµ ""°ø¹é¹®ÀÚ·Î ¹Ù²ãÁÝ´Ï´Ù °æ·Î°¡ °è¼Ó ´õÇØÁú °æ¿ì path°¡ ³Ê¹« ±æ¾îÁö¸é CString º¯¼ö°¡ ±×¸¹Àº string µ¥ÀÌÅÍ¸¦ ÀúÀåÇÒ ¼ö ¾ø±â ‹š¹®¿¡ ¿À·ù°¡ ¹ß»ýÇÕ´Ï´Ù.
5. CWinThread * m_pThread; º¯¼ö¸¦ »ý¼º  m_pThread = AfxBeginThread(RunThread, this);
5 - 1. AfxBeginThread¿¡¼­ RunThread¶ó´Â ÆÄÀÏ ÀÐ±â ¾²·¹µå »ý¼ºÀ» ÇÑ ÈÄ ¹é±×¶ó¿îµå¿¡¼­ ½ÇÇà µÇ°Ô ÇÑ´Ù.ÀÛ¾÷ÀÚ ½º·¹µå¸¦ »ç¿ëÇÏ¿© ¸ÖÆ¼ ½º·¹µå È¯°æ¿¡¼­ µ¿ÀÛ ÇÏµµ·Ï ÇÑ´Ù.
6. CWinThread * m_pMakeTimeThread;
m_pMakeTimeThread = AfxBeginThread(RunMakeTimeThread, this);
RunMakeTimeThread ÇÔ¼ö´Â ÆÄÀÏÀÐ±â ÇÔ¼ö ÀÌ±â ¶§¹®¿¡ ¾²·¹µå·Î Ã³¸®ÇØ¾ß ÇÑ´Ù.
¿Ö³ÄÇÏ¸é ¸ÞÀÎ¾²·¹µå°¡ ¸ðµÎ Ã³¸®ÇÒ °æ¿ì ÀÐ±â ¼Óµµ°¡ ÇöÀúÈ÷ ´À·ÁÁö±â ¶§¹®ÀÌ´Ù.
¹é±×¶ó¿îµå ¿¡¼­ Ã³¸® ¼Ò½º
=======
 ë£¨íŠ¸ì œìž‘ ì•Œê³ ë¦¬ì¦˜ í•µì‹¬ ì†ŒìŠ¤ ë° ì„¤ëª… ë° ìŠ¤ë ˆë“œ ì •ë¦¬
1.ê²½ë¡œì˜ ì²˜ìŒ(ë“œë¼ì´ë¸Œê²½ë¡œ, A, B, Cë“œë¼ì´ë¸Œë“±) m_bRootDir ë³€ìˆ˜ë¡œ í‘œí˜„í•©ë‹ˆë‹¤.
2.pdr, cdr, avi, ë””ë ‰í† ë¦¬ íŒŒì¼ë§Œ ë³´ì´ê²Œ í•©ë‹ˆë‹¤.
3. ê²½ë¡œë¥¼ íƒ€ì„œ ë“¤ì–´ê°ˆ ìˆ˜ë¡ m_CurrentDir ëŠ” ê²½ë¡œ ì´ë¦„ì´ ê³„ì† ë”í•´ì§‘ë‹ˆë‹¤.ê·¸ë¦¬ê³  ì´ì „ ê²½ë¡œë¥¼ ì €ìž¥í•´ë‘¡ë‹ˆë‹¤.
4. í˜„ìž¬ ê²½ë¡œì—ì„œ ë‚˜ì˜¬ê²½ìš° ì´ì „ê²½ë¡œë¥¼ ì´ì „ì— ì €ìž¥í–ˆë˜ ê²½ë¡œë¡œ ë°”ê¿”ì¤ë‹ˆë‹¤.ê·¸ë¦¬ê³  CString ë³€ìˆ˜ì¸ í˜„ìž¬ ë””ë ‰í„°ë¦¬ ë³€ìˆ˜ë„ ""ê³µë°±ë¬¸ìžë¡œ ë°”ê¿”ì¤ë‹ˆë‹¤ ê²½ë¡œê°€ ê³„ì† ë”í•´ì§ˆ ê²½ìš° pathê°€ ë„ˆë¬´ ê¸¸ì–´ì§€ë©´ CString ë³€ìˆ˜ê°€ ê·¸ë§Žì€ string ë°ì´í„°ë¥¼ ì €ìž¥í•  ìˆ˜ ì—†ê¸° ë–„ë¬¸ì— ì˜¤ë¥˜ê°€ ë°œìƒí•©ë‹ˆë‹¤.
5. CWinThread * m_pThread; ë³€ìˆ˜ë¥¼ ìƒì„±  m_pThread = AfxBeginThread(RunThread, this);
5 - 1. AfxBeginThreadì—ì„œ RunThreadë¼ëŠ” íŒŒì¼ ì½ê¸° ì“°ë ˆë“œ ìƒì„±ì„ í•œ í›„ ë°±ê·¸ë¼ìš´ë“œì—ì„œ ì‹¤í–‰ ë˜ê²Œ í•œë‹¤.ìž‘ì—…ìž ìŠ¤ë ˆë“œë¥¼ ì‚¬ìš©í•˜ì—¬ ë©€í‹° ìŠ¤ë ˆë“œ í™˜ê²½ì—ì„œ ë™ìž‘ í•˜ë„ë¡ í•œë‹¤.
6. CWinThread * m_pMakeTimeThread;
m_pMakeTimeThread = AfxBeginThread(RunMakeTimeThread, this);
RunMakeTimeThread í•¨ìˆ˜ëŠ” íŒŒì¼ì½ê¸° í•¨ìˆ˜ ì´ê¸° ë•Œë¬¸ì— ì“°ë ˆë“œë¡œ ì²˜ë¦¬í•´ì•¼ í•œë‹¤.
ì™œëƒí•˜ë©´ ë©”ì¸ì“°ë ˆë“œê°€ ëª¨ë‘ ì²˜ë¦¬í•  ê²½ìš° ì½ê¸° ì†ë„ê°€ í˜„ì €ížˆ ëŠë ¤ì§€ê¸° ë•Œë¬¸ì´ë‹¤.
ë°±ê·¸ë¼ìš´ë“œ ì—ì„œ ì²˜ë¦¬ ì†ŒìŠ¤
>>>>>>> e340c69db89f2133aada2c68ab0099feb755a92a
static UINT RunMakeTimeThread(LPVOID pParam);

UINT CMyDeanUIView::RunMakeTimeThread(LPVOID pParam)
{
	CMyDeanUIView* pView = (CMyDeanUIView*)pParam;

	pView->SendMessage(WM_READ_LIST_START);
<<<<<<< HEAD
	pView->GetFileList(); //ÆÄÀÏ ¸ñ·ÏÀ» ¸®½ºÆ®¿¡ ³Ö¾îÁØ´Ù. (¹«°Å¿îÀÛ¾÷)
=======
	pView->GetFileList(); //íŒŒì¼ ëª©ë¡ì„ ë¦¬ìŠ¤íŠ¸ì— ë„£ì–´ì¤€ë‹¤. (ë¬´ê±°ìš´ìž‘ì—…)
>>>>>>> e340c69db89f2133aada2c68ab0099feb755a92a
	pView->SendMessage(WM_READ_LIST_DONE);
}









<<<<<<< HEAD
ºí·¢¹Ú½º ·çÆ®Á¦ÀÛ ¾Ë°í¸®Áò ÇÙ½É ¼Ò½º
=======
ë£¨íŠ¸ì œìž‘ ì•Œê³ ë¦¬ì¦˜ í•µì‹¬ ì†ŒìŠ¤
>>>>>>> e340c69db89f2133aada2c68ab0099feb755a92a

void Computer::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{

<<<<<<< HEAD
	if (!m_bbloaded) //ºí·¢¹Ú½º ·ÎµùÀÌ ¾Æ´Ñ»óÅÂ¿¡¼­¸¸ .
=======
	if (!m_bbloaded) //ë¸”ëž™ë°•ìŠ¤ ë¡œë”©ì´ ì•„ë‹Œìƒíƒœì—ì„œë§Œ .
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
			if (!strcmp(strSel, "..") && m_idirDepthCnt >= 1) //,,ÀÌ¾Æ´Ï°í
=======
			if (!strcmp(strSel, "..") && m_idirDepthCnt >= 1) //,,ì´ì•„ë‹ˆê³ 
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
			else  //µ¿¿µ»ó ÆÄÀÏÀÌ ¾Æ´Ò¶§ 
=======
			else  //ë™ì˜ìƒ íŒŒì¼ì´ ì•„ë‹ë•Œ 
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
			int time = m_ListView1.GetItemData(i);				// ÇöÀç ÀúÀåÇÏÁö ¾ÊÀ½.
=======
			int time = m_ListView1.GetItemData(i);				// í˜„ìž¬ ì €ìž¥í•˜ì§€ ì•ŠìŒ.
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
		else if (m_idirDepthCnt >= 0 && !strcmp(strSel, "..")) //°ø¹éÀÌ¾Æ´Ï°í ..
=======
		else if (m_idirDepthCnt >= 0 && !strcmp(strSel, "..")) //ê³µë°±ì´ì•„ë‹ˆê³  ..
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
				m_bDirChanged = false; //ÆÄÀÏÁ¤¸®µÇ±âÀü 
=======
				m_bDirChanged = false; //íŒŒì¼ì •ë¦¬ë˜ê¸°ì „ 
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
				m_bDirChanged = false; //ÆÄÀÏÁ¤¸®µÇ±âÀü 
=======
				m_bDirChanged = false; //íŒŒì¼ì •ë¦¬ë˜ê¸°ì „ 
>>>>>>> e340c69db89f2133aada2c68ab0099feb755a92a
				m_pThread = AfxBeginThread(RunThread, this);
				hThread = m_pThread->m_hThread;
				m_bRun = true;
				m_bPlayNextCom = true;
			}


		}

	}

<<<<<<< HEAD
	MFC´Â »ç¿ëÀÚ ÀÎÅÍÆäÀÌ½º ½º·¹µå¿Í ÀÛ¾÷ÀÚ ½º·¹µå¶ó´Â µÎ °¡Áö À¯ÇüÀÇ ½º·¹µå¸¦ ±¸ºÐÇÑ´Ù.
		»ç¿ëÀÚ ÀÎÅÍÆäÀÌ½º ½º·¹µå °³Ã¼ÀÇ ¿¹·Î´Â MFCÀÇ ¸ÞÀÎ ½º·¹µåÀÎ CWinApp°¡ ÀÖ´Ù.
		ÀÛ¾÷ÀÚ ½º·¹µå´Â ¹é±×¶ó¿îµå ÀÛ¾÷ÀÌ³ª À¯Áö °ü¸® ÀÛ¾÷¿¡ ÀûÇÕÇÏ´Ù.


		ÀÛ¾÷ÀÚ ½º·¹µå(Worker Thread)
		Æ¯Á¤ ¿¬»êÀÌ³ª ÀÛ¾÷À» À§ÇÑ ½º·¹µå¸¦ ÀÏÄÂ´Â´Ù.
		Á÷Á¢ UI ÄÁÆ®·Ñ¿¡ Á¢±ÙÇÏ´Â °ÍÀ» ±ÇÀåÇÏÁö ¾Ê´Â´Ù.
		UI ½º·¹µå¿¡ ¸Þ½ÃÁö¸¦ Àü´ÞÇÏ±â À§ÇØ PostMessage ¶Ç´Â SendMessage¸¦ »ç¿ëÇÑ´Ù.
		»ç¿ëÀÚ ÀÎÅÍÆäÀÌ½º ½º·¹µå(User - Interface Thread)
		È­¸é °»½ÅÀÌ³ª ±×·ÁÁö´Â °ÍÃ³·³ 'º¸ÀÌ´Â ÀÛ¾÷'À» Ã³¸®ÇÑ´Ù.
		ÄÁÆ®·ÑÀÇ ÀÌº¥Æ® Ã³¸®¸¦ ´ã´çÇÑ´Ù.


		»ç¿ëÀÚ°¡ ¸í·É¾î¸¦ ÀÔ·ÂÇÏ¸é ÅÍ¹Ì³Î¿¡¼­ ÀÛ¾÷À» ÀÔ·ÂÇÑ ¸í·ÉÀ» ÇØ¼®ÇÏ¿© ½ÇÇàÇÕ´Ï´Ù.±×¸®°í °á°ú¸¦ È­¸é¿¡ Ãâ·ÂÇÕ´Ï´Ù.±×·¯¸é Ãâ·ÂµÈ °á°ú È­¸éÀ» º¸°í ´Ù½Ã ¸í·ÉÀ» ÀÔ·ÂÇÏ´Â ´ëÈ­½Ä ÀÛ¾÷À» ¼öÇàÇÕ´Ï´Ù.ÀÔ·ÂÇÑ ¸í·É¾î ½ÇÇàÀÌ °á°ú°¡ ³ª¿Ã ¶§ ±îÁö ±â´Ù¸®´Â ¹æ½ÄÀÌ ¹Ù·Î Æ÷±×¶ó¿îµå ¹æ½Ä ÀÔ´Ï´Ù.Æ÷±×¶ó¿îµå ÇÁ·Î¼¼½º¶ó°í ¸»ÇÏ¸ç ÀÛ¾÷ Á¦¾î Ãø¸é¿¡¼­´Â Æ÷±×¶ó¿îµå ÀÛ¾÷ÀÌ¶ó°í ¸»ÇÕ´Ï´Ù.
		Æ÷±×¶ó¿îµå ÀÛ¾÷Àº ´Ù¸¥ ¸í·ÉÀ» ÀÔ·ÂÇÒ ¼ö ¾ø°í ±â´Ù·Á¼­ ÀÔ·ÂÇØ¾ß ÇÑ´Ù.ÀÏ¹ÝÀû ¸í·ÉÀ» ½ÇÇà ÀÔ´Ï´Ù.


		¹é±×¶ó¿îµå ±â´ÉÀº ÇÁ·Î¼¼½º°¡ ½ÇÇàµÇ´Â µ¿¾È ´Ù¸¥ ÇÁ·Î¼¼½º°¡ ½ÇÇà °¡´ÉÇÕ´Ï´Ù.ÇÏ³ªÀÇ ½©¿¡¼­ ¿©·¯ °³ÀÇ ÇÁ·Î¼¼½º¸¦ µ¿½Ã¿¡ ½ÇÇàÇÒ ¼ö ÀÖ´Â ¹æ½ÄÀÔ´Ï´Ù.
		¹é±×¶ó¿îµå ¹æ½ÄÀ¸·Î ¸í·É¾î¸¦ ½ÇÇàÇÏ¸é °ð¹Ù·Î ´ÙÀ½ ¸í·É¾î¸¦ ½ÇÇà °¡´ÉÇÕ´Ï´Ù.ÇÊ¿äÇÑ ¿©·¯ ÀÛ¾÷ µ¿½Ã¿¡ ÁøÇàÇÏ¸é¼­ Æ÷±×¶ó¿îµå ÀÛ¾÷À» °è¼Ó ÁøÇàÇÒ ¼ö ÀÖ½À´Ï´Ù.¹é±×¶ó¿îµå ÀÛ¾÷Àº ÇØ´ç ¸í·É¾î Ã³¸®°¡ ¿À·¡ °É¸±°É ´ëºñÇØ ¹é±×¶ó¿îµå¸¦ ÀÌ¿ëÇÏ¸é ¿©·¯ ÀÛ¾÷À» µ¿½Ã¿¡ ¼öÇàÇÒ ¼ö ÀÖ´Ù.


		SendMessage & PostMessage ÀÌÇØÇÏ±â
		SendMessage´Â À©µµ¿ì ÇÁ·Î½ÃÀú(window procedure)¸¦ Á÷Á¢ È£ÃâÇÏ¸ç, ÇÁ·Î½ÃÀú°¡ ¸Þ½ÃÁö¸¦ Ã³¸®ÇÒ ¶§ ±îÁö ¹ÝÈ¯ÇÏÁö ¾Ê½À´Ï´Ù.Áï, ÇÔ¼ö ³»¿¡ ´Ù¸¥ ÇÔ¼ö°¡ È£ÃâµÇ¸é ±× ÇÔ¼ö°¡ ¹ÝÈ¯ÇÒ ¶§ ±îÁö ±â´Ù·Á¾ß ÇÏµíÀÌ ÀÏ¹Ý ÇÔ¼ö È£Ãâ°ú µ¿ÀÏÇÏ°Ô µ¿ÀÛÇÕ´Ï´Ù.
		PostMessage´Â È£ÃâµÈ ¸Þ½ÃÁö°¡ ¸Þ½ÃÁö Å¥¿¡ µé¾î°¡¸ç, À©µµ¿ì ÇÁ·Î½ÃÀú¿¡¼­ ÀÌ ¸Þ½ÃÁö¸¦ Ã³¸®ÇÏ°Ô µË´Ï´Ù.ÀÌ°ÍÀÌ ÀÇ¹ÌÇÏ´Â °ÍÀº, ¸Þ½ÃÁö°¡ Áï°¢ Ã³¸®µÇ´Â °ÍÀÌ ¾Æ´Ï¶ó GetMessage()¿¡ ÀÇÇØ ÇØ¼®µÈ ¸Þ½ÃÁö°¡ DispatchMessage()¿¡ ÀÇÇØ À©µµ¿ì ÇÁ·Î½ÃÀú·Î Àü´ÞµÇ¾î Ã³¸®µË´Ï´Ù.±×·¡¼­ PostMessage¿¡ ÀÇÇØ Àü´ÞµÈ ¸Þ½ÃÁö´Â ¾ðÁ¦ Ã³¸®µÉ Áö ¿¹ÃøÇÏ±â°¡ ¾î·Æ½À´Ï´Ù.
		µÎ ÇÔ¼öÀÇ Â÷ÀÌ¸¦ ¿ä¾àÇÏÀÚ¸é ´ÙÀ½°ú °°½À´Ï´Ù.


		SendMessage	PostMessage
		À©µµ¿ì ÇÁ·Î½ÃÀú¸¦ Á÷Á¢ È£ÃâÇÏ¸ç, ÇÁ·Î½ÃÀú°¡ ¸Þ½ÃÁö¸¦ Ã³¸®ÇÒ ¶§ ±îÁö ¹ÝÈ¯ÇÏÁö ¾Ê´Â´Ù.¸Þ½ÃÁö Å¥¿¡ ¸Þ½ÃÁö°¡ »ðÀÔµÇ¸ç, À©µµ¿ì ÇÁ·Î½ÃÀú¿¡¼­ ¸Þ½ÃÁö¸¦ Ã³¸®ÇÑ´Ù.ÇØ´ç ¸Þ½ÃÁö°¡ ¾ðÁ¦ Ã³¸®µÉ Áö ¿¹ÃøÀÌ ¾î·Æ´Ù.
		¼øÂ÷ÀûÀ¸·Î Ã³¸®(sequentially)	ºñ ¼øÂ÷ÀûÀ¸·Î Ã³¸®(not sequentially)
		µ¿±â ¹æ½Ä(synchronous)	ºñµ¿±â ¹æ½Ä(asynchronous)
=======
	MFCëŠ” ì‚¬ìš©ìž ì¸í„°íŽ˜ì´ìŠ¤ ìŠ¤ë ˆë“œì™€ ìž‘ì—…ìž ìŠ¤ë ˆë“œë¼ëŠ” ë‘ ê°€ì§€ ìœ í˜•ì˜ ìŠ¤ë ˆë“œë¥¼ êµ¬ë¶„í•œë‹¤.
		ì‚¬ìš©ìž ì¸í„°íŽ˜ì´ìŠ¤ ìŠ¤ë ˆë“œ ê°œì²´ì˜ ì˜ˆë¡œëŠ” MFCì˜ ë©”ì¸ ìŠ¤ë ˆë“œì¸ CWinAppê°€ ìžˆë‹¤.
		ìž‘ì—…ìž ìŠ¤ë ˆë“œëŠ” ë°±ê·¸ë¼ìš´ë“œ ìž‘ì—…ì´ë‚˜ ìœ ì§€ ê´€ë¦¬ ìž‘ì—…ì— ì í•©í•˜ë‹¤.


		ìž‘ì—…ìž ìŠ¤ë ˆë“œ(Worker Thread)
		íŠ¹ì • ì—°ì‚°ì´ë‚˜ ìž‘ì—…ì„ ìœ„í•œ ìŠ¤ë ˆë“œë¥¼ ì¼ì»«ëŠ”ë‹¤.
		ì§ì ‘ UI ì»¨íŠ¸ë¡¤ì— ì ‘ê·¼í•˜ëŠ” ê²ƒì„ ê¶Œìž¥í•˜ì§€ ì•ŠëŠ”ë‹¤.
		UI ìŠ¤ë ˆë“œì— ë©”ì‹œì§€ë¥¼ ì „ë‹¬í•˜ê¸° ìœ„í•´ PostMessage ë˜ëŠ” SendMessageë¥¼ ì‚¬ìš©í•œë‹¤.
		ì‚¬ìš©ìž ì¸í„°íŽ˜ì´ìŠ¤ ìŠ¤ë ˆë“œ(User - Interface Thread)
		í™”ë©´ ê°±ì‹ ì´ë‚˜ ê·¸ë ¤ì§€ëŠ” ê²ƒì²˜ëŸ¼ 'ë³´ì´ëŠ” ìž‘ì—…'ì„ ì²˜ë¦¬í•œë‹¤.
		ì»¨íŠ¸ë¡¤ì˜ ì´ë²¤íŠ¸ ì²˜ë¦¬ë¥¼ ë‹´ë‹¹í•œë‹¤.


		ì‚¬ìš©ìžê°€ ëª…ë ¹ì–´ë¥¼ ìž…ë ¥í•˜ë©´ í„°ë¯¸ë„ì—ì„œ ìž‘ì—…ì„ ìž…ë ¥í•œ ëª…ë ¹ì„ í•´ì„í•˜ì—¬ ì‹¤í–‰í•©ë‹ˆë‹¤.ê·¸ë¦¬ê³  ê²°ê³¼ë¥¼ í™”ë©´ì— ì¶œë ¥í•©ë‹ˆë‹¤.ê·¸ëŸ¬ë©´ ì¶œë ¥ëœ ê²°ê³¼ í™”ë©´ì„ ë³´ê³  ë‹¤ì‹œ ëª…ë ¹ì„ ìž…ë ¥í•˜ëŠ” ëŒ€í™”ì‹ ìž‘ì—…ì„ ìˆ˜í–‰í•©ë‹ˆë‹¤.ìž…ë ¥í•œ ëª…ë ¹ì–´ ì‹¤í–‰ì´ ê²°ê³¼ê°€ ë‚˜ì˜¬ ë•Œ ê¹Œì§€ ê¸°ë‹¤ë¦¬ëŠ” ë°©ì‹ì´ ë°”ë¡œ í¬ê·¸ë¼ìš´ë“œ ë°©ì‹ ìž…ë‹ˆë‹¤.í¬ê·¸ë¼ìš´ë“œ í”„ë¡œì„¸ìŠ¤ë¼ê³  ë§í•˜ë©° ìž‘ì—… ì œì–´ ì¸¡ë©´ì—ì„œëŠ” í¬ê·¸ë¼ìš´ë“œ ìž‘ì—…ì´ë¼ê³  ë§í•©ë‹ˆë‹¤.
		í¬ê·¸ë¼ìš´ë“œ ìž‘ì—…ì€ ë‹¤ë¥¸ ëª…ë ¹ì„ ìž…ë ¥í•  ìˆ˜ ì—†ê³  ê¸°ë‹¤ë ¤ì„œ ìž…ë ¥í•´ì•¼ í•œë‹¤.ì¼ë°˜ì  ëª…ë ¹ì„ ì‹¤í–‰ ìž…ë‹ˆë‹¤.


		ë°±ê·¸ë¼ìš´ë“œ ê¸°ëŠ¥ì€ í”„ë¡œì„¸ìŠ¤ê°€ ì‹¤í–‰ë˜ëŠ” ë™ì•ˆ ë‹¤ë¥¸ í”„ë¡œì„¸ìŠ¤ê°€ ì‹¤í–‰ ê°€ëŠ¥í•©ë‹ˆë‹¤.í•˜ë‚˜ì˜ ì‰˜ì—ì„œ ì—¬ëŸ¬ ê°œì˜ í”„ë¡œì„¸ìŠ¤ë¥¼ ë™ì‹œì— ì‹¤í–‰í•  ìˆ˜ ìžˆëŠ” ë°©ì‹ìž…ë‹ˆë‹¤.
		ë°±ê·¸ë¼ìš´ë“œ ë°©ì‹ìœ¼ë¡œ ëª…ë ¹ì–´ë¥¼ ì‹¤í–‰í•˜ë©´ ê³§ë°”ë¡œ ë‹¤ìŒ ëª…ë ¹ì–´ë¥¼ ì‹¤í–‰ ê°€ëŠ¥í•©ë‹ˆë‹¤.í•„ìš”í•œ ì—¬ëŸ¬ ìž‘ì—… ë™ì‹œì— ì§„í–‰í•˜ë©´ì„œ í¬ê·¸ë¼ìš´ë“œ ìž‘ì—…ì„ ê³„ì† ì§„í–‰í•  ìˆ˜ ìžˆìŠµë‹ˆë‹¤.ë°±ê·¸ë¼ìš´ë“œ ìž‘ì—…ì€ í•´ë‹¹ ëª…ë ¹ì–´ ì²˜ë¦¬ê°€ ì˜¤ëž˜ ê±¸ë¦´ê±¸ ëŒ€ë¹„í•´ ë°±ê·¸ë¼ìš´ë“œë¥¼ ì´ìš©í•˜ë©´ ì—¬ëŸ¬ ìž‘ì—…ì„ ë™ì‹œì— ìˆ˜í–‰í•  ìˆ˜ ìžˆë‹¤.


		SendMessage & PostMessage ì´í•´í•˜ê¸°
		SendMessageëŠ” ìœˆë„ìš° í”„ë¡œì‹œì €(window procedure)ë¥¼ ì§ì ‘ í˜¸ì¶œí•˜ë©°, í”„ë¡œì‹œì €ê°€ ë©”ì‹œì§€ë¥¼ ì²˜ë¦¬í•  ë•Œ ê¹Œì§€ ë°˜í™˜í•˜ì§€ ì•ŠìŠµë‹ˆë‹¤.ì¦‰, í•¨ìˆ˜ ë‚´ì— ë‹¤ë¥¸ í•¨ìˆ˜ê°€ í˜¸ì¶œë˜ë©´ ê·¸ í•¨ìˆ˜ê°€ ë°˜í™˜í•  ë•Œ ê¹Œì§€ ê¸°ë‹¤ë ¤ì•¼ í•˜ë“¯ì´ ì¼ë°˜ í•¨ìˆ˜ í˜¸ì¶œê³¼ ë™ì¼í•˜ê²Œ ë™ìž‘í•©ë‹ˆë‹¤.
		PostMessageëŠ” í˜¸ì¶œëœ ë©”ì‹œì§€ê°€ ë©”ì‹œì§€ íì— ë“¤ì–´ê°€ë©°, ìœˆë„ìš° í”„ë¡œì‹œì €ì—ì„œ ì´ ë©”ì‹œì§€ë¥¼ ì²˜ë¦¬í•˜ê²Œ ë©ë‹ˆë‹¤.ì´ê²ƒì´ ì˜ë¯¸í•˜ëŠ” ê²ƒì€, ë©”ì‹œì§€ê°€ ì¦‰ê° ì²˜ë¦¬ë˜ëŠ” ê²ƒì´ ì•„ë‹ˆë¼ GetMessage()ì— ì˜í•´ í•´ì„ëœ ë©”ì‹œì§€ê°€ DispatchMessage()ì— ì˜í•´ ìœˆë„ìš° í”„ë¡œì‹œì €ë¡œ ì „ë‹¬ë˜ì–´ ì²˜ë¦¬ë©ë‹ˆë‹¤.ê·¸ëž˜ì„œ PostMessageì— ì˜í•´ ì „ë‹¬ëœ ë©”ì‹œì§€ëŠ” ì–¸ì œ ì²˜ë¦¬ë  ì§€ ì˜ˆì¸¡í•˜ê¸°ê°€ ì–´ë µìŠµë‹ˆë‹¤.
		ë‘ í•¨ìˆ˜ì˜ ì°¨ì´ë¥¼ ìš”ì•½í•˜ìžë©´ ë‹¤ìŒê³¼ ê°™ìŠµë‹ˆë‹¤.


		SendMessage	PostMessage
		ìœˆë„ìš° í”„ë¡œì‹œì €ë¥¼ ì§ì ‘ í˜¸ì¶œí•˜ë©°, í”„ë¡œì‹œì €ê°€ ë©”ì‹œì§€ë¥¼ ì²˜ë¦¬í•  ë•Œ ê¹Œì§€ ë°˜í™˜í•˜ì§€ ì•ŠëŠ”ë‹¤.ë©”ì‹œì§€ íì— ë©”ì‹œì§€ê°€ ì‚½ìž…ë˜ë©°, ìœˆë„ìš° í”„ë¡œì‹œì €ì—ì„œ ë©”ì‹œì§€ë¥¼ ì²˜ë¦¬í•œë‹¤.í•´ë‹¹ ë©”ì‹œì§€ê°€ ì–¸ì œ ì²˜ë¦¬ë  ì§€ ì˜ˆì¸¡ì´ ì–´ë µë‹¤.
		ìˆœì°¨ì ìœ¼ë¡œ ì²˜ë¦¬(sequentially)	ë¹„ ìˆœì°¨ì ìœ¼ë¡œ ì²˜ë¦¬(not sequentially)
		ë™ê¸° ë°©ì‹(synchronous)	ë¹„ë™ê¸° ë°©ì‹(asynchronous)
>>>>>>> e340c69db89f2133aada2c68ab0099feb755a92a




<<<<<<< HEAD
		À©µµ¿ì µð¹ö±ë ¸ðµç ¹æ¹ý
		µð¹ö±× - callstack, ¹®Á¦ÁöÁ¡¿¡¼­ ´Ù½Ã½Ãµµ¶ç¿ì±â->breapoints, breapoints, error list, output, references
		1¹®Á¦ÁöÁ¡¿¡¼­ ´Ù½Ã½Ãµµ¶ç¿ì±â
		2breakpoints
		3callstack(¹Ø¿¡¼­ºÎÅÍ À§·Îº½) Áß¿ä
		4..³ª¸ÓÁöµîµî..ÀÌ¿ë
		________________________________________
		Call Stack(¹Ø¿¡¼­ºÎÅÍ À§·Îº½)
		Ouput
		Breakpoints
		¹®Á¦»óÈ²¸¸µé°í ´Ù½Ã½Ãµµ Å¬¸¯
=======
		ìœˆë„ìš° ë””ë²„ê¹… ëª¨ë“  ë°©ë²•
		ë””ë²„ê·¸ - callstack, ë¬¸ì œì§€ì ì—ì„œ ë‹¤ì‹œì‹œë„ë„ìš°ê¸°->breapoints, breapoints, error list, output, references
		1ë¬¸ì œì§€ì ì—ì„œ ë‹¤ì‹œì‹œë„ë„ìš°ê¸°
		2breakpoints
		3callstack(ë°‘ì—ì„œë¶€í„° ìœ„ë¡œë´„) ì¤‘ìš”
		4..ë‚˜ë¨¸ì§€ë“±ë“±..ì´ìš©
		________________________________________
		Call Stack(ë°‘ì—ì„œë¶€í„° ìœ„ë¡œë´„)
		Ouput
		Breakpoints
		ë¬¸ì œìƒí™©ë§Œë“¤ê³  ë‹¤ì‹œì‹œë„ í´ë¦­
>>>>>>> e340c69db89f2133aada2c68ab0099feb755a92a


