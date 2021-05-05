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


스레드 통신에서 핸들러를 사용하여 데이터를 보내기 위해서는, 데이터 종류를 식별할 수 있는 식별자와 실질적인 데이터를 저장한 객체, 그리고 추가 정보를 전달할 객체가 필요합니다.즉, 전달할 데이터를 한 곳에 저장하는 역할을 하는 클래스가 필요한데요, 이 역할을 하는 클래스가 바로 Message
하나의 데이터를 보내기 위해서는 한 개의 Message 인스턴스가 필요하며, 일단 데이터를 담은 Message 객체를 핸들러로 보내면 해당 객체는 핸들러와 연결된 메시지 큐(Message Queue)에 쌓이게 됩니다.

메시지 큐(Message Queue)는 이름 그대로 Message 객체를 큐(Queue) 형태로 관리하는 자료 구조를 말합니다.큐(Queue)라는 이름답게 FIFO(First In First Out) 방식으로 동작하기 때문에, 메시지는 큐에 들어온 순서에 따라 차례대로 저장됩니다. (First In).그리고 가장 먼저 들어온 Message 객체부터 순서대로 처리됩니다. (First Out).

안드로이드의 메시지 큐는 MessageQueue 클래스에 구현되어 있으며, 앱의 메인 스레드에서 기본적으로 사용되고 있습니다.하지만 개발자가 MessageQueue 객체를 직접 참조하여 메시지를 전달하거나, 메시지를 가져와서 처리하지는 않습니다.메시지 전달은 메시지 큐에 연결된 핸들러(Handler)를 통해서, 그리고 메시지 큐로부터 메시지를 꺼내고 처리하는 역할은 루퍼(Looper)가 수행하기 때문입니다.

MessageQueue는 Message 객체 리스트를 관리하는 클래스일 뿐, 큐에 쌓인 메시지 처리를 위한 핸들러를 실행시키지는 않습니다.메시지 루프, 즉, 메시지 큐로부터 메시지를 꺼내온 다음, 해당 메시지와 연결된 핸들러를 호출하는 역할은 루퍼(Looper)가 담당합니다. "루퍼(Looper)"라는 이름에서 알 수 있듯이, 메시지 처리를 위한 메시지 루프(Message loop)를 실행하는 것이죠

안드로이드 앱의 메인 스레드에는 Looper 객체를 사용하여 메시지 루프를 실행하는 코드가 이미 구현되어 있고, 해당 루프 안에서 메시지 큐의 메시지를 꺼내어 처리하도록 만들어져 있습니다.메인 스레드에서 메시지 루프와 관련된 코드를 개발자가 추가적으로 작성할 필요는 없는 것이죠.개발자가 할 일은, 메인 스레드로 전달할 Message 객체를 구성하고, 스레드의 메시지 큐에 연결된 핸들러(Handler)를 통해 해당 메시지를 보내기만 하면 됩니다.

핸들러(Handler)는 스레드의 루퍼(Looper)와 연결된 메시지 큐로 메시지를 보내고 처리할 수 있게 만들어줍니다.메인 스레드의 메시지 처리 흐름에서, 메시지 전달과 처리를 위해 개발자가 접근할 수 있는 창구 역할을 수행한다고 할 수 있죠

스레드와 연관된 핸들러를 얻기 위해서는, 간단하게 new 키워드를 사용하여 Handler 클래스 인스턴스를 생성하기만 하면 됩니다.그러면 새로운 Handler 인스턴스는 자동으로 해당 스레드와 메시지 큐에 연결(bound)되고, 그 시점부터 핸들러를 통해 메시지를 보내고 처리할 수 있게 됩니다.


핸들러는 생성과 동시에, 코드가 실행된 스레드에 연결(bind)됩니다.좀 더 정확히는, Handler 클래스 생성자에서 현재 스레드의 루퍼(Looper) 및 메시지 큐(MessageQueue)에 대한 참조를 가지게 되는 것인데요, 이후 단계에서 메시지를 보낼 때 이 참조를 사용하여 메시지 큐에 메시지를 넣습니다.

핸들러를 생성하고 나서 다음 할 일은, 핸들러에서 수신한 메시지를 처리하기 위해 handleMessage 메서드를 오버라이드하는 것입니다.

handleMessage() 메서드는 메시지 루프를 통해 메시지 큐(MessageQueue)로부터 꺼낸 메시지를 처리할 수 있도록, 루퍼(Looper)에 의해 실행되는 메서드입니다.당연히, 다른 스레드로부터 전달된 데이터는 msg 인스턴스에 담겨져 있으며, 일반적으로, 정수 타입인 what 변수의 값에 따라 if 또는 switch 등의 조건문으로 처리합니다. (위의 예제 코드 참고)

메시지를 보내는 곳에서는 먼저, 앞서 생성한 수신 스레드의 핸들러 객체 참조를 획득해야 합니다.메인 스레드인 경우, 액티비티의 클래스 변수로 핸들러 객체를 선언하고, 액티비티 참조를 통해 핸들러 객체를 참조할 수 있습니다.액티비티 내에서 스레드를 생성했다면, 핸들러 객체를 바로 참조할 수 있습니다.

메시지 객체를 획득하기 위해서는 Handler의 obtainMessage() 메서드를 사용합니다.obtainMessage() 메서드는 글로벌 메시지 풀(Global Message Pool)로부터 메시지를 가져오는데, 정적(static)으로 생성된 재사용(recycled) 객체로 관리되기 때문에 new 키워드로 새로운 Message 인스턴스를 만드는 것보다 효율적입니다.

obtainMessage() 메서드로 획득한 메시지 객체에 보내고자 하는 데이터를 채우고 나면, 마지막으로 할 일은 Handler.sendMessage() 메서드를 사용하여 메시지 객체를 수신 스레드에 보내는 것입니다.


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

