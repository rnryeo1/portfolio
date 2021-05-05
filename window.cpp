


 루트제작 알고리즘 핵심 소스 및 설명 및 스레드 정리
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









루트제작 알고리즘 핵심 소스

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


=============================================================================================================================
com.google.maps.api.android.lib6.common.apiexception.c: Not on the main thread	
타이머로 했더니 에러 	Not on the main thread	 maps쓸때 메인으로해야되나봄 	
Timer timer = new Timer();
				TimerTask timertask = new TimerTask() {
					@Override
					public void run() {
						showCurrentLocation(m_Latitude, m_longitude);
					}
				};
				timer.schedule(timertask, 1000,1000);			
반면 핸들러는 잘된다 	개념다시보자.
final  Handler handler = new Handler();
				handler.postDelayed(new Runnable() {
					@Override
					public void run() {
						if (true) {
							Logger.e("showCurrentLocation postDelayed");
							m_longitude +=0.001;
							showCurrentLocation(m_Latitude, m_longitude);
							handler.postDelayed(this,1000);
						}
					}
				},1000);			
//물론 아래코드도 메인이니까 에러는 안난다 1000마다 불리지 않을뿐이지.	
final static Handler UpdateHandlerLocation = new Handler() {
		public void handleMessage(Message msg) {

			activity.showCurrentLocation(activity.m_Latitude,activity.m_longitude);
		}
	};	
	//안드로이드 
	[Handler()]
	Default constructor in android.os.Handler is deprecated 오류 : 
Handler 생성 중에 암시 적으로 Looper를 선택하면 작업이 자동으로 손실 (Handler가 새 작업을 예상하지 않고 종료되는 경우), 
충돌 (Looper가 활성화되지 않은 스레드에서 처리기가 생성되는 경우) 또는 경쟁 조건이 발생하는 버그가 발생할 수 있습니다.
 핸들러가 연관된 스레드가 작성자가 예상 한 것과 다른 경우. 대신, {link android.view.View # getHandler} 
 등을 Executor사용하여 루퍼를 명시 적으로 사용하거나 지정하세요 Looper#getMainLooper. 암시 적 스레드
 로컬 동작이 호환성 new Handler(Looper.myLooper())을 위해 필요한 경우을 사용 하여 독자에게 명확하게하십시오.


라고 명시되어있습니다. 그래서 생성자로 Looper를 넣어서 사용하도록 합시다.

Handler(Looper.getMainLooper())
////////////////////////////////////////////////////////////////////////////////////////////////////
 public void getMapAsync(OnMapReadyCallback var1) {
        Preconditions.checkMainThread("getMapAsync must be called on the main thread.");
        this.zzch.getMapAsync(var1);
    }
현재 돌아가고 있는 activity 가 main 	인데 onCreate 이함수가 main 인것같음.
개념다시 정리


//extends Activity -> extends Fragment

FileListActivity 를 fragment 로 만드는 과정
결과 소스 : http://www.mediafire.com/?3gf1n19v3o0z6c2
결과 소스에 before/after 가 있으니 compare tool 을 사용해서 확인하면 더욱 이해하기 편할 것이다.

아래 2개의 소스를 fragment 로 변형할 것이다.
FileListActivity.java
activity_filelist.xml

방법
복사 : FileListActivity.java / activity_filelist.xml 를 복사한다.
이름 변경 : FileListActivity.java 를 FileListFragment.java 로 이름을 바꾼다.
이름 변경 : activity_filelist.xml 를 fragment_filelist.xml 로 이름을 바꾼다.
결과 파일
FileListActivity.java
FileListFragment
activity_filelist.xml
fragment_filelist.xml

FileListActivity.java
FragmentActivity 로 변경: extends Activity -> extends FragmentActivity
fragment tag 추가 : activity_filelist.xml 에 <fragment name="package.FileListFragment" .../> 를 추가하자.

FileListFragment.java
Fragment 로 변경 : extends Activity -> extends Fragment
onStart()로 변경 :
onCreate() 을 onStart() 로 바꾸고,
super.onCreate() 을 super.onStart() 로 바꾼다.
setContentView() 삭제
getActivity() 로 변경 : this 는 getActivity() 로 바꾼다.
getView() 추가 : findViewById() 앞에는 getView() 를 넣어서 getView().findViewById() 로 만든다.(getView() 는 onCreateView() 에서 inflate 되는 fragment이다.)
onCreateView() 추가 :
@Override
public View onCreateView(LayoutInflater inflater, ViewGroup container,
  Bundle savedInstanceState) {
 return inflater.inflate(R.layout.fragment_filelist, container, false);
}

onCreateView() 에선 Fragment 를 초기화하는 데 필요한 요소를 넣으면 된다. UI를 inflate 하거나, Fragment 에서 사용할 Service 나 Timer 등을 여기서 만들면 된다.

onStart() 에 넣을 수 있다면, onStart() 가 좋을 수도 있다. onCreateView() 에 넣으면, 다 그려지기 전까지는 화면에 보이지 않을 수도 있다.(확인필요)

그러므로 화면이 바뀌어서 다시 돌아오게 되면 onCreateView() 부터 시작하게 된다. 화면이 바뀌게 되면, 이 화면을 다시 그려야 하기 때문에 inflate 를 해줘야 한다.
 그러니 이부분에는 화면을 inflate 하는 부분을 넣어줘야 한다.

근데, 만약에 Activity에 관련있는 값을 필요로 할 때는 onActivityCreated() 에서 처리해야 한다. onActivityCreated() 
handler 는 Activity 의 초기화, UI 생성이 다 된 후에 호출되는 녀석이기 때문이다. 

Fragment 와 Activity
Fragment 가 inflated 되고 나면, Fragment 가 Activity 안에 들어가게 된다.(Activity의 View hiearchy 의 일부가 된다.) 
그러므로 Activity.findViewById()를 이용해서 찾을 수 있다.


getActivity()
getActivity()를 통해서 Fragment 가 속해있는 Activity(host Activity)의 reference 를 얻을 수 있다. 그래서 아래와 같은 것들에 이용할 수 있다.

Context 찾을 때
다른 fragmentManager 를 이용해서 다른 fragment 를 찾을 때
Activity's View hierarchy 안에 있는 View 들을 찾을 때

////////////////////////////////////////////////////////////////////////////////////////////////////	
TabHost 해결과정 논리 ㄷㄱㄹ 어떻게하면 더 시간절약을 할 수 있었을까 ? 모든해결방안 정리
원래 소스에 맞는 코드를 찾고 -> tab특성도 맞는 코드를 찾음->계속찾고 최대한 현코드에맞는 쉬운방법으로 ->삽질->계속찾기 반복할수밖에없다
////////////////////////////////////////////////////////////////////////////////////////////////////
 public void getMapAsync(OnMapReadyCallback var1) {
        Preconditions.checkMainThread("getMapAsync must be called on the main thread.");
        this.zzch.getMapAsync(var1);
    }	
	//MainFileFreeView의 onCreate 에서 UI 바꾸는 작업을 할경우 오류 가 안나는가?
	//MainFileFreeView의 onCreate 에서 getMapAsync 는 되는데 
	//메인쓰레드가 MainFileFreeView로 것인가?
안드로이드 프레임워크 내부 클래스인 android.app.ActivityThread가 애플리케이션 메인 클래스이고, ActivityThread의 main()메서드가 애플리케이션의 시작 지점이다.

ActivityThread는 Activity만 관련되어 있는것이 아니라 모든 컴포넌트들이 다 관련되어 있다. (Thread를 상속 받은 class가 아니다.)

public static void main(String[] args){
  SamplingProfilerIntegration.start();

  ClosedGuard.setEnabled(false);

  Environment.initForCurrentUser();

  EventLogger.setReporter(new EventLoggingReporter());

  Process.setArgV0("<pre-initialized>");

  Looper.prepareMainLooper(); // main Looper를 준비한다.

  ActivityThread thread = new ActivityThread();
     thread.attach(false);

  if(sMainThreadHandler == null){
      sMainThreadHandler = thread.getHandler();
      }

   AsyncTask.init();

   Looper.loop(); // UI Message 처리한다. Looper.loop() 메서드에 무한 반복문이 있어 main() 메서드는 프로세스가 종료될 때 까지 끝나지 않는다.

   throw new RuntimeException("Main thread loop unexpectedly exited");
}

Looper는 TLS(Thread Local Storage)에 저장되고 꺼내진다.
ThreadLocal set() 메서드로 새로운 Looper을 추가, get() 메서드로 Looper를 가져올때 스레드별로 다른 Looper가 반환된다.
Looper.prepare() 에서 스레드별로 Looper를 생성한다.
스레드의 메인 Looper는 Looper.prepareMainLooper()를 호출하여 생성, Looper.getMainLooper()를 사용하면 어디서든 메인 Looper를 가져올 수 있다.

Looper는 각각의 MessageQueue를 가진다. 특히 메인 스레드에서는 이 Message Queue를 통해서 UI 작업에서 경합 상태를 해결한다.

quit() : 아직 처리되지 않은 Message를 모두 제거한다.
quitSafely() : sendMessageDelayed() 등을 써서 실행 타임스탬프를 뒤로 미룬 지연 Message를 처리, quickSafely()
 메서드를 실행하는 시점에 현재 시간보다 타임스탬프가
 뒤에 있는 Message를 제거 앞에 있는 Message는 계속해서 처리


MessageQueue는 Message를 담는 자료구조
MessageQueue에는 Message가 실행 타임스탬프순으로 삽입되고 링크로 연결되어, 실행 시간이 빠른 것부터 순차적으로 꺼내어진다.


Message를 보낼때 변수에다가 값을 넣어서 보낸다.

android.os 패키지 아래에 Looper, Message, MessageQueue, Handler는 클래스에서 Message의 패키지 private 변수에 직접 접근한다.

Handler 접근 메소드 : target, callback
postXxx(), sendXxx() 메서드를 호출할때 Message에 담겨서 MessageQueue에 들어간다.
postXxx(), sendXxx() 메서드에서 실행 시간 (when)이 전달되고, 나중에 호출한 것이라도 타임스탬프가 앞서면 큐 중간에 삽입된다. 이것이 삽입이 쉬운 링크 구조를 사용한 이유이다.

obtain() 메서드를 통한 Message 생성
Message를 생성할 떄는 오브젝트 풀(object pool)에서 가져온는 Message.obtain() 메소드나 Handler의 obtainMessage() 메서드 사용을 권장
오브젝트 풀은 Message에 정적 변수로 있고 Message를 최대 50개까지 저장한다.
Looper.loop() 메서드에서 Message를 처리하고 나서 recycleUncChecked() 메서드를 통해서 Message를 초기화해서 재사용한다.
오브젝트 풀이 최대 개수에 도달하지 않았다면 오브젝트 풀에 Message를 추가한다.
new Message()와 같이 기본 생성자로 생성해서 값을 채워도 동작에는 문제가 없어보이지만 Message 처리가 끝나면 불필요하게 풀에 Message 처리가 끝나면
 불필요하게 풀에 Message를 추가하면서 금방 풀의 최대 개수에 이른다.

안드로이드 프레임워크 내부에서 쓰이는 Handler
안드로이드 프레임워크에서도 내부적으로 Handler를 많이 사용한다. 메인 스레드에서 실행해야 하는 작업들이, Handler를 
사용해서 메인 Looper의 MessageQueue를 거쳐서 순차적으로 실행된다.
ActivityThread의 내부 클래스인 H는 Handler를 상속한다. 컴포넌트 생명주기 Message는 모두 H를 거친다.
 Message 의 what 변수에 들어가는 int 상수에는 LAUNCH_ACTIVITY, RESUME_ACTIVITY, PAUSE_ACTIVITY, 
 DESTROY_ACTIVITY, CREATE_SERVICE, STOP_SERVICE, RECEIVER, BIND_APPLICATION, EXIT_APPLICATION등이 있다.
ActivityThread.class
ViewRootImpl 클래스에서 Handler를 이용해서 터치(touch)나 그리기(invalidate)등 이벤트를 처리한다.(MSG_INVALIDATE, 
MSG_RESIZED, MSG_DISPATCH_INPUT_EVENT, MSG_CHECK_FOCUS, MESSAGE_DISPACH_DRAG_EVENT 등).
 ViewRootImpl은 ICS까지는 Handler를 직접 상속했지만, 젤리빈부터는 내부 클래스인 ViewRootHandler가 Handler를 상속한다.
 ViewRootImpl에서 처음 그릴 때나 다시 그릴 때(invalidate()호출, 레이아웃 변경, Visibility 변경 등) 화면에 그리라는
 Message를 Choreographer에 위임하는데, Choreographer에서도 내부적으로 Handler를 상속한 FrameHandler를 사용한다.
Acvitiy는 멤버 변수에 Handler가 있고 runOnUiThread() 메서도에서만 사용된다.
View에는 ViewRootImpl에서 전달된 ViewRootHandler를 post() 와 postDelayed() 메서드에서 사용한다.
Activity는 멤버 변수에 Handleer가 있고 runOnUiThread() 메서드에서만 사용된다.
View에는 ViewRootImpl에서 전달된 ViewRootHandler를 post()와 postDelayed()메서드에서 사용한다.
Handler의 타이밍 이슈
원하는 동작 시점과 실제 동작 시점에서 차이가 생기는데, 이런 타이밍 이슈는 메인 스레드와 Handler를 사용해서 해결할 수 있다.
Activity의 onCreate() 메서드에서 Handler의 post() 메서드를 실행하면 Runnable이 실행되는 시점은 메인 스레드에서는 한 
번에 하나의 작업밖에 하지 못하고, 여러 작업이 서로 엉키지 않기 위해서 메인 Looper의 MessageQueue에서 Message를 하나씩 꺼내서
 처리 하며 MessageQueue에서 Message를 하나 꺼내오면 onCreate()에서 onResume()까지 쭉 실행되므로 onResume()이후에 실행이된다.
지연 Message는 처리 시점을 보장할 수 없음
Handler에서 -Delayed()나 -AtTime() 메서드에 전달된 지연 Message는 지연시간(delay time)을 정확하게 보장하지는 않는다.
 MessageQueue에서 먼저 꺼낸 Message 처리가 오래 걸린다면 실행이 느려진다.
Handler handler = new Handler();
handler.postDelayed(new Runnalbe(){
  @Override
  public void run(){
      Log.d(TAG, "200 delay");
  }
}, 200);
handler.post(new Runnable(){
  @Override
  public void run(){
      Log.d(TAG, "just");
      SystemClock.sleep(500);
  }
});
첫 번째 handler에서 Message를 보내지만 200ms 이후에 작업되는 2번째 handler에서 Message는 즉시 실행되지만 sleep시간을 포함해서 500ms가 거리는 작업이다. 
단일 스레드의 규칙 때문에 앞의 작업을 다 끝내야만, 뒤의 것을 처리할 수 있다. 따라서 '200 delay'라는 로그는 200ms가 아닌 최소 500ms 이후에 남게 된다.
////////////////////////////////////////////////////////////////////////////////////////////////////
	onCreateView 는 계속 불리고 Oncreate 는 한번 불림.
	그런데 Oncreate에서 한번 부른거를 onCreateView에서 계속부르고 있었음. 그래서 onCreateView에서 한번처리해줌 플래그로
	디버그해서 몇번부르나 확인해서  코드가하는 역할을 잘파악하는 수밖에 
	디버그 처음단에서 발생한걸 100%  확신후 거기서 고쳐야되는데 약간의 아닌가? 하는 의심이 있었음. head가 너무안돌아감.
	그냥 계속불리는 것은 onCreateView 에서 override만 불리고  한번불리는 것은 oncreate에서 1번인데 oncreateView에서 Oncreate부르고있으니
	1번처리해줘야됨. 계속만들고있으니.
////////////////////////////////////////////////////////////////////////////////////////////////////	
indicator color 해결과정	
천천히 침착하게 영어 검색하는 수밖에 없다 1.침착하고 2.천천히 영어 읽음.. 
tabwidget underline color 검색 -> 힌트찾고 selector 쪽이라는 힌트를 찾음 ->  android selector indicator 검색 -> 결과 찾기 완료
잘찾아야한다 생각하면서 일부만 답이 있는 곳도 있다 
특히 기존회사 코드가 적용이되는 코드인지 회사코드인것을 위주로 채택해서 적용한다

////////////////////////////////////////////////////////////////////////////////////////////////////
	  public void run ()
If this thread was constructed using a separate Runnable run object, then that Runnable object's 
run method is called; otherwise, this method does nothing and returns.
	run()
When an object implementing interface Runnable is used to create a thread, starting 
the thread causes the object's run method to be called in that separately executing thread.
////////////////////////////////////////////////////////////////////////////////////////////////////	
"getMapAsync must be called on the main thread.");	
처음main thread->환경설정으로 갔다면 메인쓰레드가 옮겨간것이다라고 생각 일단 일단맞다고함.
////////////////////////////////////////////////////////////////////////////////////////////////////	
피곤하다고 걍 대충 로그 찾아서 안보고 집중 못하지 말고 검색해서 로그 찾자 ...
	 Logger.d("MainFreeView# Receive error = " + e); 내용 ..
MainFreeView# Receive error = android.view.ViewRootImpl$CalledFromWrongThreadException: 
Only the original thread that created a view hierarchy can touch its views.	
////////////////////////////////////////////////////////////////////////////////////////////////////	
<shape android:shape="rectangle"
                    xmlns:android="http://schemas.android.com/apk/res/android">
//rectangle 만 하지말고 xmlns:android="http://schemas.android.com/apk/res/android" 도 붙여준다.
////////////////////////////////////////////////////////////////////////////////////////////////////
- 어플리케이션이 실행 중이지 않을 때도 작업해야하는 경우 서비스를 사용.
    (어플리케이션이 실행 중일 때만 작업해야하는 경우 스레드권장)
	- startService

startService() 함수를 호출해서 서비스를 시작하면, 시작타입의 서비스가 실행된다. 시작타입의 서비스는 한 번 시작되면,
 백그라운드에서 무한정 실행되지만, 보통의 경우는 일처리를 다 완료하면 서비스가 종료된다.
 시작타입의 서비스는 호출한 곳에 결과값을 반환하지 않고 계속해서 서비스한다. (음악재생,파일다운로드 등)

하나의 프로세스안에서 동작하며, 패키지내 컴포넌트들과 유기적으로 통신하는 역할

- boundService

bindService() 함수를 통해서 서비스하면, 연결타입의 서비스가 실행된다. 연결타입의 서비스는 서버-클라이언트 형식의
 구조를 취하기 때문에 호출자(액티비티)에서 서비스에게 어떤것을 요청하고 서비스는 그 요청을 처리한 후 결과값을 반환한다.
 이러한 구조때문에 액티비티가 사라지면, 서비스도 자동적으로 destroy되면서 없어진다. 또 하나의 서비스에 여러개의 액티비티가 붙을 수 있다. 

다른 프로세스들 간에서도 통신이 유기적으로 가능.



- intentService

일반 Service와 다르게 요청이 끝나면, 자동으로 서비스가 종료, 또 다른 서비스들과 다르게 onHandleIntent()함수 하나만을 통해 작업을 처리할 수 있다.
안드로이드는 리눅스 기반이기 때문에 프레임워크단에는 리눅스로 구현되어있다.

메모리관리 또한 리눅스 정책을 따른다. 즉 리눅스 커널에 의해서 관리된다.

결국 여러 프로세스들을 커널에서 관리한다고 짐작할 수 있다. 또 하나의 프로세스안에는 어플리케이션, 4대 컴포넌트, 스레드등을 구성하고있다.
	 이 말은 4대컴포넌트의 운명 또한 리눅스 커널에게 달려있다는 소리다.



만약 메모리부족이나, 과부하 등과 같은 현상이 발생했을 때 리눅스 커널이 프로세스를 강제로 종료시킬 수 있다.

안드로이드 어플리케이션적으로 설명하자면, 안드로이드 ui관련 처리는 메인스레드(UI스레드)라는 녀석이 처리하는데 

서비스를 그냥 생성하면, 기본적으로 이 메인스레드에게 붙는다. 만약 서비스에게 많은 일을 할당하면, 메인스레드에게 부담이 된다. 



따라서 서비스에게 많은 일을 해야하는 경우가 발생하면, 서비스의 일은 곧 메인스레드이고, 메인스레드는 그일을 처리하느냐 UI업데이트를 신경쓰지 
못하고 사용자는 멈춰있는 어플리케이션을 마주하게된다. 구글은 사용자가 어플리케이션 UI업데이트를 오랫동안 기다려야하고 늦은 응답에 대해 무한정 
기다려주는 정책을 펼치지 않는다. 이 때 ANR이라는 것을 발동시켜 강제로 프로세스를 죽여버린다. 



그렇다면, ANR을 방지하기 위해... 만약 많은 일을 서비스가 처리해야한다면, 별도의 WorksThread를(백그라운드 스레드) 만들어 처리해야한다.



HandlerThread 는 Thread 를 상속하고, 내부에서 Looper.prepare()와 Looper.loop()을 실행하는 Looper 스레드이다.
즉, 내부에 무한루프를 도는 Looper를 가진 백그라운드 스레드이며, Handler에서 편리하게 사용하기 위한 스레드 클래스이다.
아래와 같이 간단한 구현으로 백그라운드 작업을 수행할 수 있다.
private HandlerThread handlerThread;
public void init(){
    handlerThread = new HandlerThread("Test");
    handlerThread.start();
}
public void start(){
    new Handler(handlerThread.getLooper()).post(new Runnable() {
        @Override
        public void run(){
              ...
        }
    }
}


각 스레드는 [스레드] 실행 중에 메서드 로컬 변수와 매개 변수를 저장하는데 주로 사용되는 독립용 메모리 영역을 할당합니다.
 독립용 메모리 영역은 스레드가 생성될 때 할당되고, 스레드가 종료되면 할당이 해제됩니다.”



BroadCastReceiver 는 4대 컴포넌트 중에 하나이다. 

BroadCastReceiver 의 역할은 단말기 안에서 이루어지는 수많은 일들을 대신해서 알려준다.

예를들어 배터리부족,SMS문자메시지,전화가온다거나 하는 일들을 방송알림 해준다.



	3개 전부다 시도합시다. 파고들어서~ 3가지 방법 있습니다~
		public TabSpec setIndicator(CharSequence label, Drawable icon) {
					mIndicatorStrategy = new LabelAndIconIndicatorStrategy(label, icon);
					return this;
				}

        /**
         * Specify a view as the tab indicator.
         */
        public TabSpec setIndicator(View view) {
            mIndicatorStrategy = new ViewIndicatorStrategy(view);
            return this;
        }

        /**
         * Specify the id of the view that should be used as the content
         * of the tab.
         */
        public TabSpec setContent(int viewId) {
            mContentStrategy = new ViewIdContentStrategy(viewId);
            return this;
        }		
		
