서버와 데이터 주고받기.
ByteArrayOutputStream output = new ByteArrayOutputStream();
for (int i = 0; i < data.length; i++) {
    if (i > 3 && i < 12) {
        output.write(data[i]);
    }
}
byte[] result = output.toByteArray();
activity.strPlateNumber = new String(result);
activity.strPlateNumber_Save = activity.strPlateNumber;


activity.strPlateNumber = activity.strPlateNumber.substring(0, 6);
if (activity.strPlateNumber.compareTo("I530WF") == 0) {

    activity.strPlateNumber = "AB12345";
}
else
{
    activity.strPlateNumber = activity.strPlateNumber_Save;
}

Message msg = handler2.obtainMessage(); //핸들러로 UI 처리  
handler2.sendMessage(msg);

핸들러로 UI 처리
핸들러(Handler)는 스레드의 루퍼(Looper)와 연결된 메시지 큐로 메시지를 보내고 처리

final static Handler handler2 = new Handler(Looper.getMainLooper()){
    public void handleMessage(Message msg) {

       mEditTextPlateNumber.setText(activity.strPlateNumber.toUpperCase());
    }
};


===============================================================================================

    
    
===============================================================================================

스레드 통신에서 핸들러를 사용하여 데이터를 보내기 위해서는, 데이터 종류를 식별할 수 있는 식별자와 실질적인 데이터를 저장한 객체, 그리고 추가 정보를 전달할 객체가 필요합니다.즉, 
전달할 데이터를 한 곳에 저장하는 역할을 하는 클래스가 필요한데요, 이 역할을 하는 클래스가 바로 Message
하나의 데이터를 보내기 위해서는 한 개의 Message 인스턴스가 필요하며, 일단 데이터를 담은 Message 객체를 핸들러로 보내면 해당 객체는 핸들러와 연결된 메시지 큐(Message Queue)에
쌓이게 됩니다.

메시지 큐(Message Queue)는 이름 그대로 Message 객체를 큐(Queue) 형태로 관리하는 자료 구조를 말합니다.큐(Queue)라는 이름답게 FIFO(First In First Out) 방식으로 동작하기 때문에,
메시지는 큐에 들어온 순서에 따라 차례대로 저장됩니다. (First In).그리고 가장 먼저 들어온 Message 객체부터 순서대로 처리됩니다. (First Out).

안드로이드의 메시지 큐는 MessageQueue 클래스에 구현되어 있으며, 앱의 메인 스레드에서 기본적으로 사용되고 있습니다.하지만 개발자가 MessageQueue 객체를 직접 참조하여 메시지를 
전달하거나, 메시지를 가져와서 처리하지는 않습니다.메시지 전달은 메시지 큐에 연결된 핸들러(Handler)를 통해서, 그리고 메시지 큐로부터 메시지를 꺼내고 처리하는 역할은
루퍼(Looper)가 수행하기 때문입니다.

MessageQueue는 Message 객체 리스트를 관리하는 클래스일 뿐, 큐에 쌓인 메시지 처리를 위한 핸들러를 실행시키지는 않습니다.메시지 루프, 즉, 메시지 큐로부터 메시지를 꺼내온 다음,
해당 메시지와 연결된 핸들러를 호출하는 역할은 루퍼(Looper)가 담당합니다. "루퍼(Looper)"라는 이름에서 알 수 있듯이, 메시지 처리를 위한 메시지 루프(Message loop)를 실행하는 것이죠

안드로이드 앱의 메인 스레드에는 Looper 객체를 사용하여 메시지 루프를 실행하는 코드가 이미 구현되어 있고, 해당 루프 안에서 메시지 큐의 메시지를 꺼내어 처리하도록 
만들어져 있습니다.메인 스레드에서 메시지 루프와 관련된 코드를 개발자가 추가적으로 작성할 필요는 없는 것이죠.개발자가 할 일은, 메인 스레드로 전달할 Message 객체를 구성하고, 
스레드의 메시지 큐에 연결된 핸들러(Handler)를 통해 해당 메시지를 보내기만 하면 됩니다.

핸들러(Handler)는 스레드의 루퍼(Looper)와 연결된 메시지 큐로 메시지를 보내고 처리할 수 있게 만들어줍니다.메인 스레드의 메시지 처리 흐름에서, 
메시지 전달과 처리를 위해 개발자가 접근할 수 있는 창구 역할을 수행한다고 할 수 있죠

스레드와 연관된 핸들러를 얻기 위해서는, 간단하게 new 키워드를 사용하여 Handler 클래스 인스턴스를 생성하기만 하면 됩니다.그러면 새로운 Handler 인스턴스는
자동으로 해당 스레드와 메시지 큐에 연결(bound)되고, 그 시점부터 핸들러를 통해 메시지를 보내고 처리할 수 있게 됩니다.


핸들러는 생성과 동시에, 코드가 실행된 스레드에 연결(bind)됩니다.좀 더 정확히는, Handler 클래스 생성자에서 현재 스레드의 루퍼(Looper) 및 메시지 큐(MessageQueue)에 
대한 참조를 가지게 되는 것인데요, 이후 단계에서 메시지를 보낼 때 이 참조를 사용하여 메시지 큐에 메시지를 넣습니다.

핸들러를 생성하고 나서 다음 할 일은, 핸들러에서 수신한 메시지를 처리하기 위해 handleMessage 메서드를 오버라이드하는 것입니다.

handleMessage() 메서드는 메시지 루프를 통해 메시지 큐(MessageQueue)로부터 꺼낸 메시지를 처리할 수 있도록, 루퍼(Looper)에 의해 실행되는 메서드입니다
.당연히, 다른 스레드로부터 전달된 데이터는 msg 인스턴스에 담겨져 있으며, 일반적으로, 정수 타입인 what 변수의 값에 따라 if 또는 switch 등의 조건문으로 처리합니다.
    (위의 예제 코드 참고)

메시지를 보내는 곳에서는 먼저, 앞서 생성한 수신 스레드의 핸들러 객체 참조를 획득해야 합니다.메인 스레드인 경우, 액티비티의 클래스 변수로 핸들러 객체를 선언하고, 
액티비티 참조를 통해 핸들러 객체를 참조할 수 있습니다.액티비티 내에서 스레드를 생성했다면, 핸들러 객체를 바로 참조할 수 있습니다.

메시지 객체를 획득하기 위해서는 Handler의 obtainMessage() 메서드를 사용합니다.obtainMessage() 메서드는 글로벌 메시지 풀(Global Message Pool)로부터 메시지를 
가져오는데, 정적(static)으로 생성된 재사용(recycled) 객체로 관리되기 때문에 new 키워드로 새로운 Message 인스턴스를 만드는 것보다 효율적입니다.

obtainMessage() 메서드로 획득한 메시지 객체에 보내고자 하는 데이터를 채우고 나면, 마지막으로 할 일은 Handler.sendMessage() 메서드를 사용하여 메시지 객체를 
수신 스레드에 보내는 것입니다.


서비스와 수신자
Broadcast Receiver(브로드캐스트 수신자)
여러 객체에게 메세지를 전달하고 싶을 때 브로드캐스팅을 사용한다.
예를들어, 단말에서 발생한 SMS 수신 이벤트를 다른 앱에서 사용해야하는 경우가 있을 것이다.
이렇게 발생한 브로드캐스팅 메세지는 BroadcastReceiver를 이용해 받을 수 있다.
받고 싶은 메세지의 종류를 manifest에 등록하면 그 메세지가 해당 애플리케이션에 전달되는 방식이다.메세지는 Intent 객체로 만들어져 전달된다.

서버에 데이터 요청하고 응답받기
안드로이드 소켓 연결 등을 시도하거나 응답을 받아 처리할 때 스레드를 사용해야 한다


메인 스레드(Main Thread)
스레드의 관점에서 메시지 큐(Message Queue)는 시스템 이벤트를 발생 순서대로 전달받아 처리하기 위해 사용하는 구조
시스템(또는 프로세스)에서 발생한 새로운 메시지가 메시지 큐(Message Queue)에 수신되면, 메시지가 담고 있는 내용에 따라 적절한 핸들러(Handler)
메서드가 호출됩니다.하지만 일반적인 응용 프로그램이, 시스템에서 발생 가능한 모든 이벤트를 처리할 필요는 없기 때문에,
보통, 자신이 관심을 가지는 이벤트에 대한 메시지를 핸들러로 등록하고 호출되도록 만듭니다.
안드로이드의 핸들러(Handler)는, 이름 그대로, Handler 클래스가 담당합니다.그런데 통상적인 개념에서 핸들러(Handler)는
메시지 수신 시 그 처리를 담당하는 역할만 수행하는데, 안드로이드에서 Handler는 메시지를 보내는 역할까지 포함합니다.
안드로이드의 Handler는 Looper가 가진 메시지 큐(Message Queue)를 다룰 수 있기 때문에,
새로운 메시지를 보내거나, 수신된 메시지에 대한 처리를 담당하는 주체가 되는 것입니다.
프레임워크의 "그리기 기능"은 반드시 메인 UI 스레드에서만 실행
UI를 제대로 표시하기 위해서는 각 요소를 그리는 순서가 절대적으로 중요하기 때문에
반드시 하나의 스레드, 즉, 메인 UI 스레드에서 순차적으로 그리도록 만들어야 하는 것입니다.


기본 생성자를 통해 Handler를 생성하면, 생성되는 Handler는 해당 Handler를 호출한 스레드의 MessageQueue와 Looper에 자동 연결된다.
이런 식으로 메인 스레드에서 Handler를 생성하면 해당 Handler는 호출한 스레드의 메시지큐와 루퍼에 자동 연결 되므로 다른
스레드에서 Handler를 통해 메시지를 전달하면 메인 스레드(UI 스레드)에서 UI 작업을 가능하게 하는 것입니다.
앞서 설명드렸듯이 안드로이드에선 메인스레드와 서브스레드 간에 Handler를 통해 메시지를 전달하여 메시지 큐에 저장하는 방식의 통신을 사용합니다.
메시지 큐는 FIFO(First In First OUT) 방식으로 먼저 전달 받은 메시지를 먼저 처리하게되죠.Handler의 메시지 전달 함수는 아래의 두 가지가 있습니다.
    

=================================================================================================================================================
  안드로이드 핸들러  
  
    ui동기화작업예방 -> 스레드는 핸들러(메시지전달한다)를 사용 -> 워커스레드에서 핸들러는 메인 스레드로 메시지를 전달한다-> 메인 스레드에서 다시 처리한다.
핸들러는 핸들러 객체를 만든 스레드와 해당 스레드의 Message Queue에 바인딩된다. 
Message Queue는 핸들러가 전달하는 Message를 보관하는 FIFO방식의 큐이다.
다른 스레드에게 메세지를 전달하려면 수신 대상 스레드에서 생성한 핸들러의 post나 sendMessage 등의 함수를 사용해야 한다.
그래야 수신 대상 스레드의 Message Queue에 message가 저장되기 때문이다.
Message Queue에 저장된 message나 runnable은 Looper가 차례로 꺼내서 핸들러로 전달한다.
핸들러가 힘들게 넣은 것을 다시 핸들러에게 전달하는 이유는 해당 message나 runnable을 처리하기 위해서이다.

Handler.sendMessage(Message msg)
Message 객체를 message queue에 전달하는 함수

Handler.sendEmptyMessage(int what)
Message의 what필드를 전달하는 함수

Handler.post(new Runnable())
Runnable 객체를 message queue에 전달하는 함수

post를 통해서 전달된 Runnable객체는 해당 핸들러가 연결된 스레드에서 실행된다. 따라서 UI작업을 처리하기 위해서는
핸들러를 메인 스레드에서 생성하여 핸들러와 메인 스레드가 연결되어 있어야 한다.
(SendMessage()를 통해서 Message를 전달하는 것과 다를 게 없다. 어차피 대상 스레드의 Message Queue에 전달되는 것이기 때문이다)
워커 스레드 내부에서 핸들러를 생성하면 결국 워커 스레드에서 UI처리를 시도하는 것과 다를 바 없다 
워커 스레드 내부에서 핸들러를 생성하였다. 따라서 해당 핸들러를 통해 post()로 전달된 Runnable객체는 워커 스레드의 message queue에 저장된다.
그러면 워커스레드의 Looper가 Runnable객체를 꺼내서 run()을 실행한다. run()에서 시도하는 작업이 ui처리라면 에러가 발생한다.
워커 스레드 내부에서 메인 스레드 핸들러를 통해서 Runnable객체를 전달한다. 따라서 메인 스레드의 Message queue에 Runnable객체가 저장된다.
그러면 메인 스레드의 Looper가 Runnable객체를 꺼내서 Run()을 실행한다. 메인스레드에서 처리되는 ui작업이기 때문에 정상적으로 실행된다.

기본 생성자를 통해 Handler를 생성하면, 생성되는 Handler는 해당 Handler를 호출한 스레드의 MessageQueue와 Looper에 자동 연결된다.
 이런 식으로 메인 스레드에서 Handler를 생성하면 해당 Handler는 호출한 스레드의 메시지큐와 루퍼에 자동 연결 되므로 다른
 스레드에서 Handler를 통해 메시지를 전달하면 메인 스레드(UI 스레드)에서 UI 작업을 가능하게 하는 것입니다.
 앞서 설명드렸듯이 안드로이드에선 메인스레드와 서브스레드 간에 Handler를 통해 메시지를 전달하여 메시지 큐에 저장하는 방식의 통신을 사용합니다. 
 메시지 큐는 FIFO(First In First OUT) 방식으로 먼저 전달 받은 메시지를 먼저 처리하게되죠. Handler의 메시지 전달 함수는 아래의 두 가지가 있습니다.
Handler.sendEmptyMessage(int what)
Message what(ID) 를 사용할 경우 사용하는 메서드

Handler.sendMessage(Message msg)
Message what, arg1, obj 등 ID와 정보 등을 같이 사용하는 메서드

 애플리케이션을 위해 프로게스가 만들어 지면 메인스레드는 최상위에서 관리되는 애플리케이션 객체인 애티비티, 
 
 브로드캐스트 수신자 등과 새로만들어지는 위도우를 관리하기 위한 메시지 큐를 실행하게 됩니다. 

 이 메시지 큐를 이용해 순차적으로 코드를 수행할 수 있으며 이 메시지 큐를 이용해 메인 스레드에서 처리할 메시지를 전달하는 

 역할을 담당하는 것이 핸들러 클래스 입니다.

 Thead 와 핸들러수행순서

 1. 핸들러가 관리하는 메시지 큐에서 처리할 수 있는 메시지 객체 하나를 참조한다.
 2. obtainMessage() 를 이용해 호출의결과로 메시지 객체를 리턴받는다.
 3. 메세지 객체에 정보를 넣는다.
 4. sendMessage() 메소드를 이용해 메시지 큐에 넣는다.
 5. handleMessage() 메소드에 정의된 기능이 수행된다.

핸들러는 안드로이드에서 비동기적인 메시지를 처리하기 위해 사용되며 스레드간 통신을 
할 수 있는 방법을 제공한다. 핸들러 인스턴스를 생성할때 핸들러 인스턴스는 현재 쓰레드에 소속되어 있는 루퍼의
레퍼런스를 알고 있다.

핸들러가 처리하는 대상은 메세지와 러너블 객체이며 단일 쓰레드에 단하나의 루퍼와 메세지큐가 존재하지만 
핸들러는 다수 존재 가능하다

//방법1
1.Handler 의 생성
Class A extends Handler{
 @override 
 public void handleMessage(Message msg)
 {
 //메시지 처리
 }
}
//방법2
class B extends Activity
{
 Handler mHandler = new Handler()
 {
 @override
 public void handleMessage(Message msg)
 {
 //메시지 처리
 }
 };
}

Handler 클래스는 다양한 Handler 생성자를 제공한다. 다음은 Handler 생성자중 가장 기본적인 생성자에 대한 설명이다

1Handler의 생성자

public Handler()
{
 mLooper = Looper.myLooper();
 if(mLooper == null)
 {
 throw new RunTimeException("Can`t create handler inside thread that has not called Looper.prepare()");
 }
 mQueue= mLooper.mQueue;
 mCallback = null;
}
위 코드처럼 쓰레드와 연관된 루퍼가 존재하지 않다면 핸들러 또한 메시지를 처리할 수 없으므로 런타임 예외사항이 발생한다.
루퍼 객체를 획득하였다면 루퍼와 연관된 메시지 큐의 획득이 가능하다. 이때 획득한 메시지 큐에 메시지를 삽입하여 다른 핸드러와 메시지 통신이 가능하다.

2메시지 획득
핸들러는 메시지 풀로부터 메세지를 얻을 수 있는 방법을 제공한다. 쓰레드 간의 통신을 위해서 메시지가 필요하다면 핸들러의 obtainMessage()메서드를 사용 할 수 있다.
obtainMessage()메서드는 각 메서드에 따라 what, arg1, arg2, obj등을 초기화 할 수 있는 기능을 제공한다.

Handler 클래스의 obtainMessage() 메서드
public final Message obtainMessage();
public final Message obtainMessage(int what);
public final Message obtainMessage(int what, Object obj);
public final Message obtainMessage(int what, int arg1, int arg2);
public final Message obtainMessage(int what, int arg1, int arg2,Object obj);

3메시지의 전송
핸들러는 원하는 핸들러로 메세지를 보낼 수 있도록 메세지 전송 메서드를 제공한다. Handler 클래스의 메시지 전송 메서드인 sendMessage() 메서드를 실행하면
핸들러는 가지고 있는 루퍼와 연관된 메시지 큐에 메세지를 삽입한다.

Handler 클래스의 메세지 전송 메서드
public final boolean sendMessage(Message msg);
public final boolean sendEmptyMessage(int what);
public final boolean sendEmptyMessageDelayed(int what, long delayMillis);
public final boolean sendEmptyMessageAtTime(int what, long uptimeMillis);
public final boolean sendMessageDelayed(Message msg, long delayMillis);
public boolean sendMessageAtTime(Message msg, long uptimeMillis);
public final boolean sendMessageAtFrontOfQueue(Message msg);


4러너블의 전송
러너블 인터페이스는 쓰레드에 의해서 실행되길 원하는 인스턴스를 구현할 수 있도록 한다.
post()메서드는 메시지(Message)대신 Runnable 객체를 메세지 큐에 전달할 수 있다.

public final boolean post(Runnable r);
public final boolean postAtTime(Runnable r, long upTimeMillis);
public final boolean postDelayed(Runnable r, long delayMillis);

post()메서드가 Runnable객체를 메세지 큐에 전달하는 방법은 Runnable 객체를 메세지의 callback 멤버 변수로 저장후 그메세지를 sendMessageDelayed()
메서드를 통해 루퍼의 메세지 큐에 전송하는 것이다. 메시지큐에 도착한 메세지는 루퍼에 의해서 스케줄링 된후 연관된 핸들러에 의해 메세지에 포함된 Runnable 객체가
실행된다. getPostMessage()메서드는 Runnable 객체를 메세지화 하는 역할을 담당한다.

Handler 클래스의 post()메서드
Runnable 객체는 실제 실행해야하는 코드를 run()메서드에 구현한 뒤 메세지를 통해 루퍼의 메세지 큐에 전달할 수있다.

5.메세지의 처리
루퍼는 메세지 큐로부터 Runnable 객체와 메세지 객체를 디스패치하여 해당 핸들러에 전달한다.

Handler 클래스의 메세지 디스패치
public void dispatchMessage(Message msg)
{
 if(msg.callback != null)
 //Runnable 객체 실행되길 
 handleCallback(msg);
 else
 {
 if(mCallback != null)
 {
 if(mCallback.handleMessage(msg))
 {
 return;
 
 }
 }
 handleMessage(msg);

 }
}

private final void handleCallback(Message message)
{
 message.callback.run();
}

위 코드에서 처럼 handleCallback() 메서드는 메세지를 통해 전달된 Runnable객체를 실행하는 역할을 한다.
Runnable객체가 아닌 메세지가 전달되면 handleMessage()메서드를 호출하여 메세지를 처리한다.
Handler에서는 Message의 What필드를 참고하여 어떠한 처리가 필요한 이벤트인지 인지하고 처리할 코드를 결정한다.
---
    
    

=================================================================================================================================================    
    
    
Android 비동기 처리에 대한 정리

Service & IntentService
■ Service

장점
Activity에 의존하지 않고 장시간 백그라운드 처리에 적합하다.
Context를 가지고 있다
단점
메인 스레드에서 동작하기 때문에 작업을 수행하면 화면의 응답이 늦어지거나 앱이 종료된다.
※ Service의 우월성

Service는 Activity와 동일한 스레드에서 동작하고 있기 때문에 Service를 사용하지 않고 Acitivty에서 스레드를 생성하면 될 것이라 생각 할 수도 있지만 Service는 
Context를 보유하고 있다.
Activity에서도 스레드 생성 처리를 할 수 있지만, Activity가 종료되면 Activity에 관련된 Context를 사용 할 수가 없기 때문에 Context를 이용한 백그라운드 작업은 
Service에서 처리해야한다.
■ IntentService

장점
Activity에 의존하지 않고 비동기 처리에 적합하다.
내부에 HandlerThread을 가지고 있기 때문에, 메인 스레드는 다른 스레드 형태로 순처 처리를 한다.

Service와 IntentService의 차이점
아래에 Service를 사용한 처리 및 IntentService를 사용한 예제 코드를 작성한다. Activity에서 Intent를 사용하여 Service·IntentService를 호출한다.


Activity
public class MainAcitivty extends AppCompatActivity implements View.OnClickListener {
 @Override
 protected void onCreate (Bundle savedInstanceState) {
 super.onCreate (savedInstanceState);
 setContentView (R.layout.activity_main);

 findViewById(R.id.button_service).setOnClickListener(this);
 findViewById(R.id.button_intentservice).setOnClickListener(this);
 }

 @Override
 public void onClick(View v) {
 switch (v.getId()) {
 case R.id.button_service:
 Intent intent = new Intent(this, MyService.class);
 intent.setAction("show");
 startService(intent);
 break;
 case R.id.button_intentservice:
 Intent intent = new Intent(this, MyIntentService.class);
 intent.setAction("show");
 startService(intent);
 break;
 }
 }
}
Service(무한 for문을 실행)
public class MyService extends Service {
 @Override
 public int onStartCommand(Intent intent, int flags, int startId) {
 // 무한 for문을 실행
 return START_NOT_STICKY;
 }
}
→ 앱이 종료된다.

IntentService(무한 for문을 실행)
public class MyIntentService extends IntentService {
 @Override
 protected void onHandleIntent (Intent intent) {
 // 무한 for문을 실행
 }
}
→ UI(메인 스레드)에 영향을 주지 않기 때문에 앱이 종료되지 않는다.


HandleThread
HandleThread는 내부에 Looper를 가지고 Handler에 의해 보내진 메시지를 순차적으로 처리하는 구조다.

Looper & Handler
■ Looper

내부에 Message Queue를 가지고 순서대로 Queue에서 꺼낸 메시지를 처리하는 방법
Android의 기본적인 구조로 되어 Activity와 Service등이 Looper에서 동작하고 있음
Activity와 Service는 메인 루퍼(메인 스레드)에서 동작하며 화면에 대한 위젯 변경등은 메인 루퍼에서 해야함
■ Handler

Looper에 Message를 전달하기 위한 메신저


Handler와 HandlerThread의 차이점
Handler는 메인 스레드에서 작업이 진행된다. 하지만 HandlerThread는 새로운 Thread를 생성하고, 거기서 작업을 처리한다.

public class HandlerDefault extends AppCompatActivity {
 @Override
 protected void onCreate(Bundle savedInstanceState) {
 super.onCreate(savedInstanceState);
 setContentView(R.layout.activity_handler_default);

 Handler handler = new Handler();
 handler.post (new Runnable() {
 @Override
 public void run() {
 // 코스트 높은 작업을 수행
 final String currentThread = Thread.currentThread().getName();
 }
 });
 }

}
→ currentThread는 main 메인 스레드에서 코스트가 높은 작업을 수행하면 앱이 종료

public class HandlerThreadDefault extends AppCompatActivity {
 @Override
 protected void onCreat (Bundle savedInstanceState) {
 super.onCreate(savedInstanceState);
 setContentView(R.layout.activity_handler_thread_default);

 // other 스레드 생성 -> 시작
 HandlerThread handlerThread = new HandlerThread("other");
 handlerThread.start();

 // other 스레드의 Looper를 Handler에 할당
 Handler handler = new Handler(handlerThread.getLooper());
 handler.post(new Runnable() {
 @Override
 public void run() {
 // 코스트 높은 작업을 수행
 final String currentThread = Thread.currentThread().getName();
 }
 });
 }
}
→ currentThread는 other 다른 스레드를 생성했기 때문에 코스트가 높은 작업을 수행하도 UI에 영향을 미치는 것이 아니라 앱이 종료될 염려는 없다.







---

=================================================================================================================================================
    aos 비동기 처리
[안드로이드 비동기 처리] AsyncTask

3년 전 by PEACE PEACE-

안녕하세요 PEACE-에요.
안드로이드 스터디 [열 번째]글이네요.

오늘은 비동기 처리를 위한 AsyncTask에 대해 포스팅하겠습니다.




1. 메인쓰레드(UI Thread)와 비동기 처리

우리가 사용하는 안드로이드 어플리케이션에서 UI(버튼, 리스트, 텍스트뷰 등등..)는 UI쓰레드라고 불리는 메인쓰레드가 관여하고 처리한다. 
    그렇다면 우리가 만든 버튼을 통해 어떠한 작업을 수행한다면 메인쓰레드는 어떻게 처리할까? 우선 하나의 상황을 통해 설명하려한다. 
    '777APP'이라는 어플리케이션에 '다운로드'와 '페이지 닫기'라는 두 개의 버튼이 구성되어있다. 그리고 다운로드 버튼을 클릭해 해당 파일을 다운로드 하려한다.
    이때 메인쓰레드가 수행하도록 코드를 구성했다면 버튼에 대한 처리는 메인쓰레드가 할 것이며, 다운로드하는 처리도 메인쓰레드가 할 것이다. 
    또한 다운로드 받는 동안 타 UI와의 교류가 비활성화 될 것이다. 쉽게말해 '다운로드' 버튼과 '페이지 닫기' 버튼이 먹통이 될 것이다. 그렇다면 어떻게 해야할까?
    기다려야할까? 아니다. 사용자는 그것을 원치 않을 것이다. 이때 우리는 메인쓰레드와 별개로 작업을 수행하고 그 결과를 UI에 나타낼 수 있도록 처리해야한다. 
    '비동기 처리'라고 하며, 이를 위해 AsyncTask에 대해 알아 볼 것이다.



2. AsyncTask란?


AsyncTask가 메인쓰레드에서 수행될 작업을 수행해주는 비동기적 처리 방법 중 하나라고 했다. 아래 사진은 AsyncTask에 대한 이해를 돕기 위해 안드로이드 
디벨로퍼스의 AsyncTask Guide를 발췌해온 글이다.

위 내용은 구글 번역기에 이용해 확인할 수 있다. 그래서 나는 중요 포인트만 짚고 넘어가려한다. 우선 AsyncTask는 메인쓰레드를 작업을 좀 더 효율적이게
해줄 수 있는 백그라운드 처리 기법이다.  AsyncTask는 작업 수행 시간이 수 초간 진행될 때 유용하며, 오랜 시간 작업을 해야하는 경우에는 
AsyncTask가 아닌 다른 방법을 권장한다. 예를들면 java.util.concurrent패키지에서 제공하는 Executor, ThreadPoolExecutor 및 FutureTask가 있다.



3. AsyncTask에는 무엇이 있을까?




[그림 1] AsyncTask의 Override 메서드

[그림 1]은 AsyncTask에서 지원하는 메서드들과 그에 대한 쓰임을 나타낸 것이다. 이제 쉽게 다룰 수 있을 것이며, 사용법과 주의점만 파악한다면
좀 더 퀄리티있는 소스 코딩이 가능할 것이다.



4. AsyncTask 사용 방법



[그림 2] AsyncTask 사용 방법

[그림 2]에서 보면 execute()를 통해 작업을 수행하며 인자의 자료형은 doInBackground()의 매개변수의 자료형과 같다. 또한 이 자료형의 변수는 
가변인자이며 단일 변수나 배열과 같은 형태의 변수를 사용할 수 있다. doInBackground()에서 가변 형태인 매개변수 사용 시에는 변수명[0]과 같이 배열의 형태로 사용한다.

AsyncTask 작업을 수행하기 위해서는 객체를 생성해 execute()메서드와 executeOnExecutor()메서드를 호출하는 방법이 있다.
  **execute() 메서드 호출을 통한 작업 수행
      : 일반적인 사용하는 수행 방법이며 여러 AsyncTask 객체를 만들어 다수의 작업을 수행할 때 execute()가 호출된 순서대로 처리.
  **executeOnExecutor() 메서드 호출을 통한 작업 수행
      : 병렬처리를 위한 수행 방법이며 여러 AsyncTask 객체를 만들어 다수의 작업을 수행할 때 executeOnExecutor()가 호출된 순서에
        상관 없이 동시처리한다.



5. AsyncTask 주의점

AsyncTask 수행을 위해 생성된 객체는 execute()를 통해 단 한번만 실행 가능(1)하며, 재 실행시 예외 상황이 발생한다. 또한 AsyncTask는 
메인쓰레드에서만 실행되고 호출되어야한다(2). AsyncTask는 백그라운드에서 수행되며, 그 결과를 메인쓰레드에 전달해 사용자에게 제공한다.
          그렇다면 AsyncTask에 백그라운드 작업을 요청한 메인쓰레드, 즉 AsyncTask를 호출한 Activity가 destroy된다면 어떻게될까? 여기서부터 문제가 발생한다. 
          일반적으로 특별한 처리를 해두지 않았다면 AsyncTask는가 참조하고있던 UI가 사라져도 AsyncTask는 백그라운드에서 작업을 수행한다. 
          그리고 개발자의 코드에 의해 그 결과를 사라진 메인쓰레드에 넘겨주려 할 것이며, 이 과정에서 사라진 UI를 참조하게된다. 
          하지만 자신이 참조하는 UI는 이미 destroy되었으며 예외 상황이 발생하게된다. 또한 가비지컬렉터는 AsyncTask가 참조하고 있는
          이전 Activity를 컬렉트할 수 없어 메모리릭이 발생할 수 있다. 또한 화면 회전에 의해 Activity가 destroy되고 새 인스턴스로 Activity를 생성할때도
          이와같은 상황이 발생할 수 있다. 이를 위한 대비를 해야하며, cancel()을 통해 doInBackground() 실행 완료 후, onPostExcute() 호출을 막고 onCancelled를
          호출하도록 해야한다(3). 마지막으로 AsyncTask를 여러 개 실행하면 이는 순차적으로 수행이 이뤄진다. ATask.execute()와 BTask.execute()를 
          순서대로 호출하면 ATask에 대한 작업이 끝나야 BTask에 대한 작업이 수행된다는 뜻이다. 그렇다면 동시에 처리하려면 어떻게해야할까? 이를 위해 
          execute() 메서드 대신 executeOnExecutor()라는 메서드가 제공되며 이를 사용해 병렬처리가 가능하다.


---




1. 앱 실행 (액티비티 호출) : onCreate() -> onStart() -> onResume()
2. 액티비비1에서 인텐트로 액티비티2를 띄웠을 때
액티비티1 관점 : onPause() -> onStop()
액티비티2 관점 : onCreate() -> onStart() -> onResume()
3. 액티비티2를 종료하고 1으로 돌아왔을 때 : onRestart() -> onStart() -> onResume()
4. 홈키를 눌러 앱이 백그라운드로 전환됐을 때 : onPuase() -> onStop()
5. 다시 돌아왔을 때 : onRestart() -> onStart() -> onResume()
6. 앱을 종료할 때 : onPuase() -> onStop() -> onDestroy()


서비스는 타 컴포넌트(클라이언트)와 연결되며 여러 클라이언트를 가질 수 있다. 또한 클라이언트는 특정 작업을 통해 서비스에게 데이터를 요청(서비스 객체, 멤버에 접근)할 수 있다.

안드로이드에서 Activity는 Background에서 작업을 수행할 수 없다. 이를 위해 우리는 Service를 사용한다. 예를 들면 노래를 켜고 웹 서핑을 하는 상황이 있다. 
우리가 음악을 듣는 어플을 사용할때 보통 어플에 들어가 노래를 켜고 다른 화면으로 가거나 화면을 끄거나 다른 어플리케이션을 사용한다. 그럼에도 불구하고 노래를 들을 수 있는건 
백그라운드에서 노래를 틀어주는 작업을 수행하고 있기 때문이다. 그럼 이제 머리속에 Service라는 컴포넌트에 대한 스케치가 됐을 것이다.

Service 사용에 있어서 기억해야할 내용은 다음과 같다.

 * 서비스 라이프사이클(Service Life Cycle)

 * 단순 Service에 대한 수행 처리 과정

 * 서비스바운딩에 의한 Service 수행 처리 과정

 * 동시 수행 처리 과정
 
4. 서비스의 수행과 처리

서비스는 타 컴포넌트(클라이언트)와 연결되며 여러 클라이언트를 가질 수 있다. 또한 클라이언트는 특정 작업을 통해 서비스에게 데이터를 요청(서비스 객체, 멤버에 접근)할 수 있다.


액티비티1'에서 startService() 호출 후 '액티비티2'에서 bindService()를 호출한 경우, '액티비티2'에서는 서비스바운딩을 통해 현재 실행 중인 서비스 객체에 접근할 수 있다. 
'액티비티1'에서도 startService() 호출 후 서비스 객체에 접근하기 위해 bindService()를 호출할 수 있다. 이렇게 하나의 서비스에 대해 여러 서비스바운딩이 이뤄진 경우 서비스가
 종료되는 시점에 대해 어려움을 가질 수 있다. [그림 3]에서 처럼 startService() 만 호출만 경우에는 stopService()를 통해 서비스를 종료할 수 있지만, 
 어딘가에서 서비스바운딩이 일어났을때는 바운딩이 끊어져야 서비스 종료가 가능해진다. 즉, 서비스바운딩 중에 stopService()를 호출해도 바운딩이 끊어질때까지 기다리며 서비스바운딩
 중인 액티비티에서 바운딩이 끊어져야 비로소 서비스에서 onDestroy()가 호출되며 서비스 수행이 종료된다. 또한 startService() 호출 없이 bindService()만 호출해서
 서비스를 시작할 수 있으며 unbindService()를 호출하면 onDestroy()가 호출됨과 동시에 서비스 수행이 종료된다.





1) 메인 액티비티 생성.

2) 메인 레이아웃 구성.

3) 서비스 상속 클래스 생성.

4) AndroidManifest.xml에 서비스 목록 추가.



MainActicity에서는 Intent를 startActivity()가 아닌 startActivityForResult()메서드를 사용해 Activity의 새 인스턴스를 생성했다.
 startActivityForResult()메서드의 첫번째 인자는 Intent가 들어가며 두번째 인자에는 결과를 요청할때 확인할 요청코드를 보낸다. 
요청코드는 1과 같이 임의의 코드를 보낸다. 또한 새 인스턴스로 부터 결과를 받아오기 위해 onActivityResult()를 Overriding해야한다.


안드로이드는 서버와 통신하기 위한 방법으로는 HTTP통신과 Soket통신이 있다. 오늘 다룰 내용은 HTTP통신으로 URL 접속을 통해 데이터를 읽어오는 방법이다.
 우리는 주로 DB에 존재하는 데이터를 가져오기 위해 서버 통신을 한다. 
하지만 안드로이드의 특성상 외부 DB에 직접 접근할 수 가 없도록 되어있어 중간 매체인 WEB을 활용해야한다. 이해를 위해 그림으로 쉽게 표현했다. 


안드로이드 통신은 보통 위와 같이 이뤄지며 본 포스팅에서는 'ANDROID-WEB'의 통신 방법에 대해 다룰 것이다. 
우선 막연하게 WEB이라고만 하면 정확히 어떤 것을 말하는 것인지 헷갈릴 수 있다. 여기서 말하는 WEB은 HTML, JSP, PHP, SERVLET 등이 있다.
 자신의 DB와 WEB에서 데이터를 가져오기 위해선 호스팅이나 개인서버를 구축한 후,
 자신이 만든 WEB문서가 포함된 로컬호스트 주소에 접속해서 데이터를 얻어와야한다.


이전에 '비동기 처리를 위한 AsyncTask'라는 제목으로 포스팅을 했다. 안드로이드 어플리케이션 구현에 있어서 아주 중요한 부분인데 HttpURLConnection을
 직접 구현하고 싶다면 저 포스팅을 보고 오길 강력 추천한다. 일단 간단히 설명하자면 안드로이드의 UI관련 처리는 메인쓰레드가 담당한다. 메인쓰레드는 UI쓰레드라고도 하며,
 우리가 특정 명령으로 수행시키지 않아도 자동으로 수행된다. 조금 더 구체적으로 말하자면 액티비티를 띄우고 액티비티 내에서 일어나는 모든 처리는 메인쓰레드가 담당한다고 보면된다.
 즉 onCreate()에서의 코드 수행도 메인쓰레드가 처리하며 혼자서 처리하다보니 동시 작업에 무리가 있다. 즉 현재 띄워진 액티비티 내에서 다운로드와 같은 오랜시간 동안 수행하는
 작업을 메인쓰레드가 하게되면 다른 UI가 먹통이 된다. 모두 메인쓰레드가 처리하기 때문에 다운로드가 끝나기 전엔 다른 작업을 수행할 수 없는 것이다. 이를 해결하기 위해 비동기
 처리를 해야하며 안드로이드 제공하는 AsyncTask라는 별도의 쓰레드를 이용한다. AsyncTask를 사용하면 메인쓰레드와 별개로 작업이 수행되며 수행 후 결과만 메인쓰레드에
 넘겨주어 효율적인 작업이 이뤄질 수 있다. "아 귀찮아. 그냥 난 메인쓰레드에서 돌릴거야!"라고 생각하시는 분들도 계실텐데.. 실제로 돌려보면 Runtime Exception과 
 함께 다음과 같은 예외 상황이 발생한다.
 
android.os.NetworkOnMainThreadException !!
따라서 AsyncTask를 사용하길 적극 권장한다.

우선 첫번째로 'INTERNET'에 대한 권한을 주어야한다.
두번째로 별도의 클래스(RequestHttpURLConnection)를 만들어 HttpURLConnection을 수행하는 기능 구현한다.
세번째로 MainActivity에서의 위젯을 처리하고 Network Processing에 대해서 비동기 처리하기 위해 AsyncTask를 구현한다.

3.1 동기(Synchronous) 실행 vs 비동기 (Asynchronous) 실행.
프로그래밍 분야에서, 동기(Synchronous) 실행이 의미하는 것은, 프로그램 실행 중 하나의 기능 또는 함수를 실행했을 때, 
그것을 실행한 측(Caller)에서 기능이나 함수의 모든 동작이 완료될 때까지 대기하는 방식을 의미합니다.
 그리고 비동기(Asynchronous) 실행은, 기능 또는 함수의 동작이 끝나길 기다리지 않고 바로 그 다음 코드를 실행하는 방식을 말하죠.


메인 액티비티의 onCreate() 메서드에서 readFileData() 메서드를 호출하는데요. 이 때 onCreate() 
메서드는 readFileData() 메서드를 호출하고 난 뒤 파일의 데이터가 모두 읽히기를 기다립니다. 그리고 readFileData()
 메서드의 실행이 완료되면 그 다음 코드인 showFileData()를 실행합니다. 이러한 실행 흐름이 바로 동기(Synchronous) 실행 입니다.

자, 그런데 여기서, 한 가지 좋지 않은 상황을 가정해보겠습니다. 읽고자 하는 파일의 크기가 매우 큰 경우 말이죠. 만약 파일의 크기가 
아주 커서 파일의 내용을 읽는데 몇 초, 몇 십초 이상의 시간이 소요된다면, 분명 심각한 문제가 발생할 것입니다. 왜냐하면 readFileData()에서
 파일을 읽을 동안 readFileData()를 호출한 메인 스레드가 다른 이벤트들을 처리하지 못하게 될 것이고, 최악의 경우,
 ANR(Application Not Responding)이 발생하면서 시스템에 의해 앱의 실행이 중지되는 상황이 생길 수도 있습니다. 이는 
 [안드로이드 스레드 예제. 스레드로 고민해보기. (Android Thread UseCase)] 주제에서 여러 번 강조한,
 "안드로이드 앱의 메인 스레드에서는 무한 루프나 실행 시간이 긴 작업, 또는 과도한 대기(sleep) 등의 작업이 실행되어서는 안된다"는 원칙을 명백히 위반하는 것이죠.


이런 경우 개발자가 선택할 수 있는 방법은, 파일을 읽는 코드를 별도의 스레드에서 실행되도록 만들어 메인 스레드의 실행에 영향이 가지 않게 하는 만드는 것입니다. 
즉, readFileData() 메서드 내부에서는 파일을 복사하는 새로운 스레드를 실행하기만 하고 바로 리턴되게 만드는 것이죠. 
그러면 onCreate()에서 readFileData()를 호출하더라도 메인 스레드가 대기할 필요 없이 바로 다음 코드를 실행할 수 있습니다. 그리고 파일 복사 스레드에서 파일을 다 읽고나면, 
메인 스레드에 메시지(Message)를 전달하여 메인 스레드에서 파일의 내용을 화면에 표시하게 만들면 됩니다. 이것이 바로 비동기(Asynchronous) 실행입니다.


단순히 파일을 읽는 경우를 예로 들어 비동기(Asynchronous) 실행을 설명했는데요, 사실, 앱의 기능을 구현하는데 있어
 "비동기(Asynchronous) 실행"은 훨씬 다양한 상황에 적용 가능합니다. 크기가 큰 파일 복사,
 데이터베이스 쿼리, HTTP 서버 API 요청, FTP 파일 다운로드 등, 비동기(Asynchronou) 실행이 필요한 경우를 찾는 것은 그리 어렵지 않죠.

요약하자면, 동기(Synchronous) 실행과 비동기(Asynchronous) 실행은, 어떤 기능을 실행한 다음, 그 기능의 실행이 완료될 때까지 대기할 것인지 여부에 따라 구분됩니다. 
실행이 모두 완료될 때까지 기다리면 "동기(Synchronous) 실행", 실행이 완료되기를 기다리지 않고 바로 다음 코드를 실행하는 것은 "비동기(Asynchronous) 실행" 입니다.

자, "비동기(Asynchronous) 실행"에 대한 개념을 설명했으니, 이제, 실질적인 구현 방법에 대해 알아볼텐데요.
 그런데 사실, "비동기(Asynchronous) 실행" 이라고 해서, 
앞서 정리한 [개발자를 위한 레시피 - THREAD]를 벗어나는 내용은 없습니다. 오히려, 앞서 다른 글에서 설명한 
스레드와 스레드 간 통신에 대한 내용에 정확히 들어 있다고 할 수 있죠. "메인 스레드의 실행에 영향을 줄 수 있는 기능을 새로운 스레드에서 실행하고, 
기능이 완료되면 메인 스레드 핸들러로 메시지를 전달한다."는 것, 명확하지 않습니까?

그런데 안드로이드에서의 "비동기(Asynchronous) 실행"을 위한 스레드 처리 과정을 가만히 살펴보면,
공통된 패턴이 존재하는 것을 발견할 수 있습니다. 바로, 스레드에서 실행되는 작업이 완료되면 더 이상 스레드를 유지하지 않아도 되는
 "단발성 실행"이라는 것과 스레드 실행 중간 상태 또는 최종 결과를 "메인 스레드로 전달"한다는 사실입니다.

실행(execute) : 비동기(Asynchronous) 작업 준비 및 시작.
백그라운드 작업(doInBackground) : 백그라운드 스레드에서 비동기(Asynchronous) 작업 실행.
진행 상황 업데이트(onProgressUpdate) : 백그라운드 스레드 진행 상황을 메인스레드로 전달.
비동기 실행 완료 후 처리(onPostExecute) : 백그라운드 스레드 완료 후 메인스레드에 완료 상태 전달.

execute -> doInBackground -> onProgressUpdate -> onPostExecute


AsyncTask는 그 이름에서도 알 수 있듯이, 비동기(Asynchronous)적으로 실행될 필요가 있는 작업(Task)을 위해 사용하는 클래스입니다. 
특히 Thread, Handler, Message, Runnable 등을 직접 다루지 않아도, 메인 스레드와 별개로 "비동기(Asynchronous) 실행"이 필요한 작업에 사용할 수 있습니다.

AsyncTask로 비동기 작업을 구현하기 위해서는 먼저 아래의 몇 가지 사항에 대해 알아두어야 합니다.

추상 클래스 : abstract class AsyncTask.
제네릭 타입 : AsyncTask<Params, Progress, Result>
가변 인자 : (Params ...), (Progress ...)
실행 단계 : onPreExecute, doInBackground, onProgressUpdate, onPostExecute

추상 클래스. (abstract class AsyncTask)
AsyncTask는 추상 클래스(abstract class)입니다. 이 말은, AsyncTask를 사용하기 위해서는 반드시 AsyncTask를
 상속(extends)한 클래스를 생성해야 한다는 것을 의미합니다. "추상 클래스"는 해당 클래스에 대한 인스턴스를 바로 생성할 수 없기 때문이죠.

public abstract class AsyncTask<Params, Progress, Result> {

}

좋습니다. abstract 키워드를 확인했으니, 구현할 때 AsyncTask를 상속한 클래스를 만들면 되겠군요.
 그런데 AsyncTask가 제네릭 타입으로 선언된 것을 확인할 수 있는데요, "<Params, Progress, Result>"는 각각 무엇을 의미할까요?

 제네릭 타입. (AsyncTask<Params, Progress, Result>)
AsyncTask는 "비동기(Asynchronous) 실행" 작업을 위해 사용하는 클래스입니다. 
그리고 일반적으로 "비동기(Asynchronous) 실행" 작업은 "작업 시작", "작업 실행", "상태 갱신", "결과 확인"이라는 공통된 단계를 거치게 됩니다. 이러한 단계들은, 
뒤에서 조금 더 자세히 설명하겠지만, 추상 클래스인 AsyncTask를 상속할 때 반드시 오버라이드해야 하는 메서드들에 매핑됩니다.



그런데 여기서 갑자기 의문이 생기네요. AsyncTask를 통해 구현하고자 하는 기능은 상황에 따라 다를테고 또
 관리해야하는 데이터의 종류 또한 제각각일텐데, AsyncTask에서 구현해야 하는 메서드에서는 상황에 따라 변하는 타입의 데이터를 어떻게 전달하고 관리할 수 있을까요? 
 AsyncTask 실행에 필요한 파라미터(예. 파일 경로, URL, DB 파일 경로 등)라던가, 현재 작업 진행 정보를 나타내는 상태 값
 (예. 크기 또는 개수를 나타내는 정수 값, 진행율을 위한 실수 값 등),
 그리고 작업의 실행이 완료된 후의 최종 결과(예. 성공 또는 실패, 처리된 내용의 크기 또는 개수 등) 등이 상황에 따라 다르게 정의될 것은 명확한데 말이죠.

자, 그러면 이러한 상황, 즉, 구현하고자 하는 기능에 따라 클래스 내부에서 다른 타입의 데이터를 적용되게 만들어야 하는 상황에 대처하는 방법을 찾아야 하는데요,
 공통된 코드를 다양한 타입에 재사용할 수 있게 만드는 방법, 바로 제네릭(Generics) 입니다.

AsyncTask는 제네릭(Generics) 클래스로 선언되어, 각 메서드에서 사용할 데이터 타입을 AsyncTask를 상속할 때 결정할 수 있도록 만들어 놓았습니다. 
Params, Progress, Result가 그것들이죠.

AsyncTask 제네릭 파라미터 타입
public abstract class AsyncTask<Params, Progress, Result>
세 개의 제네릭 파라미터 타입은 이름이 가진 의미 그대로 AsyncTask에 전달될 파라미터(Params), 현재 작업 진행 상태 값(Progress), 작업 완료 최종 결과(Result)를 나타냅니다.

Params : AsyncTask 실행에 필요한 파라미터.
Progress : 현재 작업 진행 정보를 나타내는 상태 값.
Result : 작업의 실행이 완료된 후의 최종 결과.

제네릭 파라미터 타입을 어떻게 사용해야 하는지 선뜻 이해되시나요? 
지금 당장 이해가 되지 않는다고해서 너무 걱정하실 필요는 없습니다. 아래 예제 코드를 살펴보시면, 충분히 이해되실 거라 생각합니다.
그런데 여기서 잠깐, 또 한 가지 궁금한 것이 생겼습니다. 제네릭 파라미터 타입을 결정하고나서 데이터를 전달할 때 만약 두 개 이상의 값을 사용하려면 어떻게 해야 할까요? 
예를 들어 파일 복사 작업의 현재 진행 상태를 표시할 때, 복사된 파일 개수를 나타내는 Count 값과 복사된 바이트 수를 나타내는 TotalBytes를 Progress를 통해 전달해야 한다면,
 두 멤버를 가지는 새로운 클래스를 만들어야 하나요? 아니면 배열 또는 컬렉션(Collections) 객체를 사용해야 하는 건가요?
아닙니다. 반드시 그렇게 할 필요는 없습니다. 왜냐하면 Params와 Progress는 doInBackground()와 onProgressUpdate() 메서드에서
 각각 가변 인자(Varargs)로 전달되기 때문입니다.

가변 인자. (Varargs)
가변 인자(Varargs)는 이름 그대로, 메서드에 전달되는 파라미터의 개수가 가변적이라는 의미입니다. 
메서드에 전달할 파라미터의 개수가 일정하지 않을 때 사용하는 방법인데요. 파라미터의 타입에 "..."를 추가하여 메서드에 
전달되는 파라미터가 가변 인자라는 것을 명시할 수 있습니다.


 가변 인자. (Varargs)
가변 인자(Varargs)는 이름 그대로, 메서드에 전달되는 파라미터의 개수가 가변적이라는 의미입니다. 
메서드에 전달할 파라미터의 개수가 일정하지 않을 때 사용하는 방법인데요. 파라미터의 타입에 "..."를 추가하여 메서드에 전달되는 파라미터가 가변 인자라는 것을 명시할 수 있습니다.

AsyncTask의 doInBackground()와 onProgressUpdate() 메서드는 위와 같이 Params, Progress 
제네릭 타입에 대한 가변 인자를 전달하도록 선언되어 있기 때문에, 다른 객체를 사용하지 않아도 두 개 이상의 값을 전달할 수 있습니다.

public abstract class AsyncTask<Params, Progress, Result> {

 protected abstract Result doInBackground(Params... params);
 protected void onProgressUpdate(Progress... values) {}
}

실행 단계. (onPreExecute, doInBackground, onProgressUpdate, onPostExecute)
일단 AsyncTask를 통해 "비동기(Asynchronous) 실행"이 시작되면, AsyncTask는 "작업 시작", "작업 수행", "상태 갱신", "결과 확인"의 네 단계를 거쳐 실행됩니다.
 그리고 각 단계는 onPreExecute(), doInBackground(), onProgressUpdate(), onPostExecute()라는 메서드로 매핑됩니다.




onPreExecute(). 작업이 실행되기 직전에 UI 스레드에 의해 호출됩니다. 일반적으로 UI 초기화와 같이, "비동기(Asynchronous) 실행" 작업에 대한 초기화 과정을 수행하는 메서드입니다.

doInBackground(Params...). onPreExecute()가 호출된 뒤, 
곧 바로 백그라운드 스레드에서 호출됩니다. AsyncTask가 수행할 실질적인 작업 실행 코드가 작성되는 메서드입니다.
 AsyncTask의 첫 번째 제네릭 파라미터 타입(Params)이 이 메서드의 파라미터 타입으로 매핑되고, 
 마지막 제네릭 파라미터 타입(Result)이 doInBackground()의 리턴 타입으로 매핑됩니다.
그리고 doInBackground() 실행 중 상태 업데이트가 필요한 경우, publishProgress(Progress...) 
메서드를 호출하여 메인 스레드에서 onProgressUpdate(Progress...)가 호출되게 만들 수 있습니다.

onProgressUpdate(Progress...). 백그라운드 스레드에서 동작하는 doInBackground()에서 
publishProgress(Progress...)를 호출하면, UI 스레드에서 호출되는 메서드입니다. 보통 현재 작업 진행 상태를 화면에 갱신하는 역할을 수행합니다.

onPostExecute(Result). 백그라운드 스레드의 모든 실행이 완료되면 UI 스레드에서 호출되는 메서드입니다. 
onPostExecute()의 파라미터(Result)는 doInBackground()에서 리턴되는 값입니다.


5. AsyncTask 예제
그럼 이제 예제를 작성하면서, AsyncTask를 사용하는 방법에 대해 알아보도록 하겠습니다.

예제에서 구현하는 기능은 간단합니다. 먼저 앱의 에셋(Assets) 폴더에 파일을 하나 추가합니다. 
그리고 화면의 버튼을 클릭하면 애셋(Assets)에 저장된 파일을 앱의 로컬 디렉토리에 복사하도록 만듭니다. 주로,
 미리 만들어진 형식의 파일(DB, XML, JSON 등)을 앱 릴리즈 시점에 같이 배포한 다음, 앱의 로컬 디렉토리에서 읽고 쓸 수 있게 만들 때 사용하는 방법이죠.

워크플로우.
AsyncTask예제 작성 절차
1-Asset에 파일추가
2-메인액티비티 레이아웃 작성
3-화면 구성 뷰에 대한 참조 획득
4-AsyncTask 상속(extends AsyncTask)
5-onPreExecute() 작성
6-doInBackground() 작성
7-onProgressUpdate() 작성
8-OnPostExecute() 작성
9-AsyncTask 실행 (AsyncTask.execute())


AsyncTask 클래스 상속.
onPreExecute() 메서드 오버라이드.
AsyncTask 기능 구현의 첫 번째 단계는 onPreExecute() 메서드를 오버라이드하는 것입니다.
앞서 설명했듯이, onPreExecute() 메서드는 AsyncTask의 백그라운드 스레드가 실행되기 전, 메인 스레드에 의해 호출되는 메서드입니다. 
주로 UI 초기화 작업이 이루어지는 메서드죠. 예제에서도 화면 각 요소 값의 초기화를 onPreExecute()에서 수행합니다.

doInBackground() 메서드 오버라이드.
이제 실질적인 비동기 작업이 실행되는 doInBackground() 메서드를 오버라이드합니다.
앞에서도 강조했듯이, doInBackground() 메서드는 메인스레드가 아닌, 백그라운드 스레드에서 실행되는 코드입니다. 
그러므로 doInBackground() 메서드 내에서 UI를 직접 제어하면 안됩니다.
대신, publishProgress() 메서드를 사용하여 화면에 표시될 데이터를 전달하고, onProgressUpdate() 메서드에서 UI 화면을 갱신할 수 있습니다.

onProgressUpdate() 메서드 오버라이드.
doInBackground() 메서드에서 publishProgress() 메서드를 호출했을 때, 메인 UI 스레드에서 실행할 onProgressUpdate() 메서드를 구현합니다.

private class CopyDatabaseAsyncTask extends AsyncTask<String, Long, Boolean> {
 /// ... 코드 계속

 @Override
 protected void onProgressUpdate(Long... values) {
 long fileSize = values[0] ;
 long copySize = values[1] ;
 int percent = (int)((copySize * 100) / fileSize) ;

 mTextMessage.setText(percent + " %") ;
 mProgressCopy.setProgress(percent) ;
 }

 /// 코드 계속 ...
 }
	
onPostExecute() 메서드 오버라이드.
마지막으로 doInBackground() 메서드 실행이 완료되어 리턴되었을 때 호출되는 onPostExecute() 메서드를 구현합니다.

private class CopyDatabaseAsyncTask extends AsyncTask<String, Long, Boolean> {
 /// ... 코드 계속

 @Override
 protected void onPostExecute(Boolean result) {
 mTextMessage.setText("Copy completed.") ;
 }

 /// 코드 계속 ...
 }


AsyncTask 실행.

이제 AsyncTask에서 구현해야 할 메서드는 모두 작성하였으므로, 메인액티비티에서 앞서 작성한 AsyncTask를 실행하기 위해 execute() 메서드를 호출하는 코드를 작성합니다.


















































    
    
    
