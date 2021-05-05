3) ios async, platenum, send, recv, 이론정리등.
IOS Data 주고받기 및 IOS의 UI Update 방법(async)을 정리

func parseGetPlateNumber(_ data : [UInt8] ) {
    print("\(WHAT_CLASS):\(#function):\(#line)")
        let simple = CNSPlateNumberSetting.init(bytes: data)
        if simple.resultbyte < 0 {
            print("\(WHAT_CLASS):\(#function):\(#line) set wifi password failed")
                showPopup(NSLocalizedString("NOTIFY", comment: "안내"), NSLocalizedString("PN_CHANGE_ERROR", comment: "Wi-Fi 비밀번호 변경을 실패했습니다."))
        }
        else {
            isPassError = true
                //m_plateName
                //showPopup(MsgDefs.PN_CHANGE_TITLE, MsgDefs.PN_CHANGE_PROGRESS)
                print("parseGetPlateNumber else ")
                var databuf : [UInt8] = [0, 0, 0, 0, 0, 0, 0, 0]
                var cnt : Int = 0
                for index in 0.. < data.count - 1
                {
                    if (index > 3 || index < 12)
                    {
                        databuf[cnt] = data[index]
                            if (index > 3 && index < 11)
                            {
                                cnt += 1;
                            }
                    }
                    print("\(String(format: "data[index] data = % 2X ", data[index])) ")
                        print("\(String(format: "parseGetPlateNumber data = % 2X ", databuf[cnt])) ")

                }
            if let _string_ = String(bytes: databuf, encoding : .utf8)
            {
                print("_string_: {" + _string_ + "}")
                    m_plateName = _string_.uppercased()
                    if m_plateName.contains("I530WF") {
                        labelTitle2.text = "AB12345"
                            print(m_plateName)
                    }
                    else {
                        labelTitle2.text = m_plateName
                            print(m_plateName)
                    }

            }
            else
            {
                print("not a valid utf-8 sequence");
            }

        }

}

선언
protocol DReceiveDelegate{
    func onDReceive(_ res : Int)
}

func onReceive(_ cmd : UInt16, _ size : Int, _ data : [UInt8] , _ ext : UInt8, _ crc : UInt8) -> Int {
    print("\(WHAT_CLASS):\(#function):\(#line): size: \(size)")

        if size <= 0 {
            stopLoading()
                return -1
        }

    switch cmd{
    case NetDefs.NAT_CMD_SET_PLATENUMBER_RESP:
        parseSetPlateNumber(data)
        break
    case NetDefs.NAT_CMD_GET_PLATENUMBER_RESP:
        parseGetPlateNumber(data)
        break
    default:
        break
    }

        return 0
}

//데이터받아서 셋.
func parseSetPlateNumber(_ data : [UInt8] ) {
    print("\(WHAT_CLASS):\(#function):\(#line)")
        let simple = CNSPlateNumberSetting.init(bytes: data)

        if simple.resultbyte < 0 {
            print("\(WHAT_CLASS):\(#function):\(#line) set wifi password failed")
                showPopup(NSLocalizedString("NOTIFY", comment: "안내"), NSLocalizedString("PN_CHANGE_ERROR", comment: "Wi-Fi 비밀번호 변경을 실패했습니다."))

        }
        else {
            print("\(String(format: "parseSetPlateNumber data.count = % d", data.count)) ")//13

                for index in 0.. < data.count - 1
                {

                    print("\(String(format: "parseSetPlateNumber data[index] data = % 2X ", data[index])) ")

                }
            isPassError = true
                //showPopup(MsgDefs.PN_CHANGE_TITLE, MsgDefs.PN_CHANGE_PROGRESS)
        }
}

private var recDelegate : ReceiveDelegate ? = nil

func setRecDelegate(_ delegate: ReceiveDelegate ? ) {
    self.recDelegate = delegate
}

let appDelegate = UIApplication.shared.delegate as!AppDelegate //Shared 변수 
var tcpclient : TCPC = TCPC() //서버통신 
appDelegate.tcpclient.send(NetDefs.NAT_CMD_FACTORY_RESET, nil, 10)

//byte데이터 받음.
if self.recDelegate != nil{
                    if self.recDelegate!.onReceive(unCmd, nSize, byteData, byteEXT, byteCRC) < 0 {
                    }
}





// IOS UI Update
DispatchQueue.main.async{
    self.progressBarViewController.progressCur.doubleValue = Double(frameCntCur)
    self.progressBarViewController.progressAll.doubleValue = Double(frameCntAll)
    self.progressBarViewController.labelProcessing2._string_Value = "\(NSLocalizedString("PROCESSING", comment: "진행 중")).. 
        \(processPer)% (\(fileCntCurRef.pointee)/\(fileCntMax))"
}

DispatchQueue.main.async{
                    self.present(_alert_, animated: false, completion : nil)
}
 

====================================================================================================================
main()함수는 UIAppliationMain()함수를 호출하는데 이함수가 이벤트 루프를 처리하는 앱의핵심 컨트롤러이다
실행되면 모든 기본적인 일은 UiKit 프레임워크가 처리하는데, 이 프레임워크가 UI를 보여주고 , 메인이벤트 루프를 시작한다.
이루프를 도는동안 UIKit은 터치에 대한 노티피케이션 및 디바이스의 방향 변경등의 이벤트를 객체에게 보내서 처리하며,
앱에서 요청한 명령들을 처리해준다. 홈버튼눌러서 종료할때 UIKit이 앱에게 통지하고 종료 처리한다.

앱 델리게이트는 앱의 핵심 클래스로서메인 이벤트 루프로부터 메시지를 받는다. 그리고 아이폰 OS가 보내는 
중요한 시스템 메시지들을 처리하는 책임을 가지고 있다.
모든 아이폰 앱은 앱델리게이트 객체를 갖고있어야한다. 
뷰 컨트롤러 클래스는 하나 또는 여러뷰를 생성하고 화면에 보여준다.
이클래스는 또한 표준 시스템이벤트(예를 들어 디바이스의 방향이 바뀌는 등)에 대해서 앱이 처리해야할 일들을 수행하는
델리게이트의 역할도 한다.

@interface로 클래스 선언한다.
@implementation 으로 클래스 정의한다. @end로 끝난다.
@synthesize 키워드를 사용하여 클래스 인터페이스에서 선언한 프로퍼티 메소드들을 구현한다.

객체형(Type) : id형은 Generic Type이다.
@property 키워드를 사용해서 프로퍼티를 선언하면, 인스턴스 변수를 접근하기 위해서
접근자 메소드를 일일이 선언하고 구현하는 지루한 반복작업을 하지 않아도 된다.

메소드 이름앞의 뺄셈기호(-)는 메소드가 인스턴스 메소드라는 것을 나타낸다.
클래스 메소드 앞에는(+) 기호가 사용된다.

자동해제 풀 : 1.메인 이벤트 루프가 시작되기전에 기본 자동해제 풀을 생성한다.
 2. 메인 이벤트 루프가 끝나면 자동해제 풀이 제거된다.
 
alloc, retain, copy ,release 주기
레퍼런스 카운팅 기반의 메모리 관리 : alloc, retain ,release 메소드 호출로 인한 리테인 카운트 변화를 고려해야하며
자신의 소유가 아닌 객체는 해제하면 안된다. 
객체를 소유한다는 것은 alloc 또는 copy 메소드로 객체를 생성하거나 retain을 호출하여 객체의 
리테인 카운트를 증가시킨 경우를 말한다. 
객체를 해제할 때에는 release 메시지 또는 autorelease 메시지를 보낼 수 있다.
[anObject release]; //리테인 카운트가 하나 감소된다. 리테인 카운트가 0이되면 dealloc 메소드가 호출되고 객체가 메모리에서 제거된다.
[anObject autorelease]; //객체가 자동해제 풀에들어가 현재의 이벤트 사이클이 끝날때 release 메시지를 받음.
	
@interface AnObject: UIViewController<UITableViewDataSource, UITableViewDelegate>
{
	...
}
위의 AnObject 클래스는 UIViewController 클래스로부터 상속받았으며, 테이블 뷰에게 데이터를 제공하며
 테이블 뷰가 생성하는 이벤트에 대한 처리를 수행할 수 있다고 선언하는 것이다. 다시말하면 
 이클래스는 UITableViewDataSource, UITableViewDelegate 프로토콜을 구현한다는 뜻이다.
 
먼저 클래스란?
클래스는 하나의 주제로 묶여 있는 속성과 기능 입니다. 여기서 주제를 '클래스명' ,속성은 '인스턴스 변수' ,기능은 '메소드'라 칭합니다. 
이러한 클래스를 가지고 객체를 생성해서 사용합니다. 

클래스 구조
클래스는 다음과 같은 구조로 '@interface' 와 '@implementation' 를 통해 사용할 수 있습니다

@interface 클래스명:슈퍼클래스명{
인스턴스 변수 선언;
}
메소드 선언;
@end

@implementation 클래스명
-(반환타입) 메소드명{
메소드 정의;
}
@end


먼저 '@interface'를 통해 클래스에 대해 정의합니다.
'@interface' 지시자와 '@end' 지시자로 감싸져 있는 부분이 'Car' 클래스에 대한 인스턴스 변수 와 메소드에대한 정의입니다.
그리고 보통의 클래스는 정의할 경우 루트 클래스인 NSObject를 상속합니다.
@interface Car:NSObject{
 int maxSpeed;
 NSString *color;
}
-(void) drive;
-(void) stop;
@end


다음은 '@implementation'를 통해 정의한 클래스에대해 실질적 기능등을 구현합니다.
'@implementation' 지시자와 '@end' 지시자로 감싸져 있어, '@interface'를 통해 정의한 부분을 상세 구현합니다.
@implementation Car
-(void) drive{
 NSLog(@"운행시작");
}
-(void) stop{
 NSLog(@"운행멈춤");
}
@end


그리고 실질적으로 객체화 시켜서 사용합니다.
int main(int argc, const char * argv[]) {
 @autoreleasepool {
 // insert code here...
 Car *car=[[Car alloc]init];
 car.drive;
 car.stop;
 }
 return 0;
}



8.1.1. 루트 클래스의 역할
런타임 시스템은 Objective-C 용 운영체제 같은 것으로, 객체 생성, 해제에 따른 메모리 영역 관리와 송신된 메시지에 대응하는 메서드 검색 등을 한다.
보통은 프로그램에서 런타임 시스템 기능을 직접 사용하지 않는다.
이런 기본 기능은 루트 클래스인 NSObject 에 있는 메서드로 제공된다.
다시 말해 루트 클래스는 런타임 시스템에 대한 인터페이스 역할이라고 할 수 있다.

* 8.1.2. 클래스와 인스턴스
NSObject 의 인스턴스 변수는 오직 하나뿐이다.
바로 Class 형 변수인 isa 이다.
모든 인스턴스 객체는 isa 에 따라 자신이 속한 클래스 객체를 참조한다.
isa 는 인스턴스와 클래스의 관계를 결정하는 무척 중요한 변수이므로, 서브 클래스에서 값을 변경해서는 안 된다.
인스턴스에 속한 클래스를 조사하려면 isa 를 참조하는 것이 아니라 인스턴스 메서드 class 를 사용해야 한다.


NSObject 메서드는 NSObject 자체에서 사용되기보다는 서브 클래스인 각종 클래스 및 인스턴스에서 공통으로 사용된다.


-(Class) class
 리시버가 속한 클래스의 클래스 객체를 돌려준다.
+(Class) class
 클래스 객체를 돌려준다.
-(id) self
 리시버 자체를 돌려준다.
-(BOOL) isMemberOfClass: (Class) aClass
 리시버가 인수 클래스 인스턴스인가 조사한다.
-(BOOL) isKindOfClass: (Class) aClass
 리시버가 인수 클래스 인스턴스인지, 혹은 그 클래스의 서브 클래스 인스턴스인지를 조사한다.
+(BOOL) isSubclassOfClass: (Class) aClass
 isKindOfClass: 와 같은 형태이나 class method 이다.
-(Class) superclass
 리시버가 속한 클래스의 슈퍼 클래스의 클래스 객체를 return
+(Class) superclass
 위와 동일한 녀석, but class method.
* 8.1.3. 인스턴스 생성과 해제
+(id) alloc
 리시버로 지정된 클래스 인스턴스를 생성한다.
 생성된 인스턴스 초기화를 완전히 하기 위해 늘 init 또는 init으로 시작하는 메서드 또는 초기자와 조합해서 사용해야 한다.
 서브 클래스에서 alloc 을 재정의해서는 안 된다.

-(void) dealloc
 인스턴스를 해제한다.
 release 결과로 호출된다.
 서브 클래스로 dealloc 를 재정의할 때 빼고는 프로그램에서 직접 호출해서는 안 된다.

-(oneway void) release
-(id) retain
-(id) autorelease
-(NSUInteger) retainCount
-(void) finalize
dealloc 에서 retainCount 까지는 수동 카운터 관리 방식으로 메모리 관리를 할 때 유효하고, ARC 에서는 사용할 수 없다.
finalize 는 가비지 컬렉션을 사용할 때 유효하다.

-(id) init
 alloc 으로 생성된 인스턴스를 초기화한다.

+(void) initialize
 클래스 초기화.
 클래스 안에서 공통으로 쓰는 변수 초기 설정 등을 할 때 사용한다.
 이 메서드는 그 클래스에 처음으로 온 메시지보다 먼저 자동으로 실행된다.
 직접 호출해서는 안 된다.

+(id) new
 일반적으로 alloc 과 init 을 조합한 것이다.

-(BOOL) isEqual: (id) anObject
-(NSUInteger) hash

8.2.1. 셀렉터와 SEL 형
# 셀렉터(Selector) - 함수를 직접 지정하는 기능을 가진 일종의 함수 선택자
Selector는 본래 Objecive-C에서 클래스 메소드의 이름을 가르키는 데 사용되는 참조 타입입니다.
동적 호출 등의 목적으로 @selector() 어트리뷰트 메소드 이름을 인자값으로 넣어 전달하면 이를 내부적으로 정수값으로 매핑해서 처리하는 형태입니다.
 이것이 Swift로 넘어오면서 구조체 형식으로 정의되고, #selector()구문을 사용하여 해당 타입의 값을 생성할 수 있게 되었습니다. 

Swift4부터는 Selector 타입으로 전달할 메소드를 작성할 때 반드시 @objc 어트리뷰트를 붙여주어야 합니다. 
이는 Objective-C와의 호환성을 위한 것으로,
 Swift에서 정의한 메소드를 Objective-C에서도 인식할 수 있게 해 줍니다.

셀렉터의 자료형이 SEL 이다.
셀렉터 표기로 SEL 형 데이터를 프로그램에서 얻을 수 있는 컴파일러 지시자 @selector() 가 있다.

SEL 형의 변수가 유효한 셀렉터를 값으로 가지고 있지 않다는 것을 나타내고 싶을 때 전통적인 NULL 을 사용할 때가 많다.
혹은 (SEL)0 이라는 표현을 쓰기도 한다.


EL 형 값을 사용해서 메시지 송신이 가능하다.
(id) performSelector: (SEL) aSelector
(id) performSelector: (SEL) aSelector withObject: (id) anObject

함수 포인터는 그 함수가 존재하는 메모리 주소를 나타낸다.
그 포인터에 대응하는 함수가 무엇인가를 컴파일 할 때 결정하게 되므로 지정하지 않은 함수는 실행되지 않는다.
SEL 형은 메서드명에 상당하는 것으로 리시버가 되는 객체가 무엇인지에 따라 메서드가 실행될 대 정해진다.




8.2.2. 메시지 탐색

모든 인스턴스에는 isa 라는 Class 형 인스턴스 변수가 있는데, 이것이 클래스 객체를 나타낸다.
우선 런타임 시스템은 메시지와 같은 셀렉터를 가진 메서드가 클래스에 있는지 확인한다.
있으면 그 메서드를 실행하지만, 없으면 클래스 객체 안에 슈퍼 클래스를 나타내는 포인터가 있으므로 그것을 따라가서 슈퍼 클래스에 메서드가 있는지 확인한다.
최종적으로 루트 클래스까지 가서 찾아봐도 해당 메서드가 발견되지 않으면 실행 에러가 발생한다.

메시지를 보낼 때마다 해당하는 메서드를 탐색하면 호출 처리가 무척 무거워진다.
따라서 런타임 시스템은 어떤 클래스가 어떤 셀렉터에 대응하는 메서드를 가지고 있고, 그 정의 장소가 어디인지 같은 정보를 캐시에 넣어둔다.
그래서 다음에 같은 메시지가 오면 다시 탐색하지 않고 캐시 정보를 이용할 수 있게 한다.

어떤 객체가 지정한 셀렉터에 대응하는 메서드를 구현했는지 어떤지는 동적으로 확인할 수 있다.
-(BOOL) respondsToSelector: (SEL) aSelector
+(BOOL) instancesRespondToSelector: (SEL) aSelector

* 8.2.3. 메시지 함수 구현
메시지 송신이 함수 호출에 비해 조금 느리다는 건 사실이지만 객체지향의 유연성을 포기하면서까지 속도를 올릴 만한 가치는 없다.
메시지 송신은 충분히 빠르다.
어떤 객체의 메서드에 대응하는 함수를 가리키는 포인터를 얻을 땐 그 객체에 대해 다음 메서드를 사용한다.

-(IMP) methodForSelector: (SEL) aSelector
 인수로 지정한 셀렉터에 대응하는 메서드를 확인해서 그 구현이 있는 함수 포인터를 돌려준다.
 이 메서드는 인스턴스 객체에서도, 클래스 객체에서도 사용할 수 있다.
 인스턴스 객체에 대해 사용하면 인스턴스 메서드에 대응하는 함수가 반환되고,
 클래스 객체에 대해 사용하면 클래스 메서드에 대응하는 함수가 반환된다.

+(IMP) instanceMethodForSelector: (SEL) aSelector

 인수로 지정한 셀렉터에 대응하는 인스턴스 메서드를 조사해서 그 구현이 있는 함수 포인터를 돌려준다.

IMP 형은 다음 정의와 같은 형식으로 메서드에 대응하는 함수 포인터를 나타낸다

typdef id (*IMP)(id, SEL, …);


cf) 함수 포인터
함수의 포인터가 나타내는 건 그 함수 실행 코드의 첫 주소라고 생각해도 된다.
함수 포인터는 변수나 배열에 대입하거나 다른 함수에 인수로 넘길 수 있다.
구조체 멤버에 넣어 구조체를 객체처럼 다룰 수도 있다.
int funcA(double x, int *err); // 함수 signature
int (*p) (double, int *); // 함수 포인터
typedef int (*t_func) (double, int *); // t_func 라는 이름의 함수 포인터

t_func fptr = funcA;
x = (*fptr) ( 1.4142, &error ); // 함수 포인터를 강조하기 위해 보통 사용되는 방법
x = fptr( 1.4142, &error ); // 이렇게 쓸 수도 있지만 그냥 함수같아서 위의 방법으로 주로 사용


IMP funcp = [foo methodForSelector:@selector(setBox:title:)];
xyz = (*funcp)(foo, @selector(setBox:title:), param1, param2);
메서드에 대응하는 함수는 메서드에서 선언한 인수 말고도 반드시 리시버가 되는 객체와 메시지 셀렉터를 인수로 받는다.
명시되진 않았지만 이들은 메서드 속에서 참조가 가능해 숨은 인수(hidden arguments)라고 부른다.
첫 번째 인수인 리시버는 실제로는 self, 두번째 인수인 셀렉터는 _cmd 라는 변수명으로 참조가 가능하다.


IMP 형은 메서드 인수 형식을 명시하지 않으므로 실제 프로그래밍에서는 인수 형식이 구체적으로 정해진 함수 포인터에 캐스트해서 사용하는 게 안전하다.

AnyObject
모든 클래스 타입을 지칭하는 프로토콜
클래스와 프로토콜에 대한 설명은 차후에 합니다
class SomeClass {}
var someAnyObject: AnyObject = SomeClass()


Not Running(Terminated) : App이 아직 실행되지 않았거나 시스템에 의해 완전히 종료된 상태입니다.
Inactive(Foreground) : App이 실행 중이지만 이벤트를 받지 않는 상태입니다. Active 상태로 넘어가기 전에 앱은 반드시 이 상태를 거칩니다. 
미리알림 같은 특정 알림창이 화면을 덮어서 앱이 실질적으로 event를 받지 못하는 상태 등이 여기에 해당됩니다.
Active(Foreground) : App이 실행 중이고 이벤트를 받고 있는 상태입니다. Foreground 상태에 있는 app들은 평소에 이 상태에 머물러 있습니다.
Background : App이 다른 앱으로 전환되거나 홈 화면으로 나갔을 때 실질적인 동작을 하고 있는 상태입니다. 백그라운드에서 동작하는 코드를 추가하면 
suspended 상태로 넘어가지 않고 백그라운드 상태를 유지하게 됩니다. 처음부터 background 상태로 실행되는 app은 inactive 
대신 background 상태로 진입합니다. 음악을 실행하고 홈 화면으로 나가도 음악이 나오는 상태가 이 경우에 해당됩니다.
Suspended : App이 background 상태에서 추가적인 작업을 하지 않으면 곧바로 suspended 상태로 진입합니다.
 앱을 다시 실행할 경우 빠른 실행을 위해 메모리에만 올라가 있습니다. 메모리가 부족한 상황이 되면 iOS는 suspended 상태에 있는 앱들을 메모리에서 해제시켜서 메모리를 확보합니다.


Life Cycle in States
AppDelegate에 구현된 UIApplicationDelegate protocol의 method들을 사용하여 생명 주기 사이에 커스텀 코드를 실행시킬 수 있습니다.

UIApplication
App을 실행하면 main에서 UIApplicationMain() 함수가 호출되면서 UIApplication 객체를 생성합니다. 
UIApplication은 app의 main run loop을 관리하는 객체로, 앱이 실행되면 info.plist의 값들을 바탕으로 app에 필요한 데이터와 객체들을 로드합니다.
 UIApplication 객체는 프로젝트를 생성할 때 기본으로 생성되는 AppDelegate 클래스에 app의 상태변화, 푸시 알림 등 이벤트를 전달하여 app의 상태에 따라 
 custom code를 실행시킵니다. AppDelegate 클래스는 UIApplicationDelegate protocol을 채택하여 custom code를 실행시킬 수 있는 delegate method를 구현합니다.

Process Life Cycle
application(_:willFinishLaunchingWithOptions:)
App에 필요한 주요 객체들을 생성하고 run loop를 생성하는 등 app의 실행 준비가 끝나기 직전에 호출됩니다.
App State : Launch Time(Not Running)
application(_:didFinishLaunchingWithOptions:)
App 실행을 위한 모든 준비가 끝난 후 화면이 사용자에게 보여지기 직전에 호출됩니다. 주로 최종 초기화 코드를 작성합니다.
App State : Launch Time(Not Running)
applicationWillTerminate(_:)
- App이 종료되기 직전에 호출출되며 App이 곧 종료될 것임을 알려줍니다.
사용자가 직접 앱을 종료할 때만 호출됩니다. 다음 경우에는 호출되지 않습니다.
메모리 확보를 위해 Suspended 상태에 있는 app이 종료될 때
Background 상태에서 사용자에 의해 종료될 때
오류로 인해 app이 종료될 때
Deivce를 재부팅할 때
App State : Active -> Terminate
UI Life Cycle
applicationWillEnterForeground(_:)
App이 Background 또는 Not-Running 상태에서 Foreground로 들어가기 직전에 호출됩니다.
App State : Background or Not Running -> In-Active -> Active
applicationDidBecomeActive(_:)
App이 active 상태로 진입하고 난 직후 호출됩니다. App이 실제로 사용되기 전에 마지막으로 준비할 수 있는 코드를 작성할 수 있습니다.
App State : Active
applicationWillResignActive(_:)
App이 Active에서 In-Active 상태로 진입하기 직전에 호출됩니다. 주로 App이 quiescent(조용한) 상태로 변환될 때의 작업을 진행합니다.
App State : Active -> In-Active -> Background
applicationDidEnterBackground(_:)
App이 background 상태에 진입한 직후 호출됩니다. App이 Suspended 상태로 진입하기 전에 중요한 데이터를 저장하거나
 점유하고 있는 공유 자원을 해제하는 등 종료되기 전에 필요한 준비 작업을 진행합니다.
특별한 처리가 없으면 background 상태에서 곧바로 suspended 상태로 전환됩니다.
App이 종료된 이후 다시 실행될 때 직전 상태를 복구할 수 있는 정보를 저장할 수 있습니다.
App State : Background

위처럼 변수의 타입의 뒤에 ?를 붙여주면 해당 변수는 Optional이 됩니다. 
Swift에서는 기본적으로 변수 선언시 nil 값이 들어가는 것을 허용하지 않습니다. 런타임 에러를 뿜는 것이 아니라, 아예 컴파일 에러를 내버립니다. 
그러므로 아래에서 첫 번째 줄의 코드는 에러이고, 두 번째 줄은 Optional type(String?)으로 선언했으므로 에러가 아닙니다.

Forced Unwrapping
앞선 예제에서처럼 출력 결과가 Optional(“Hello”)처럼 나오는 것은 대부분의 경우 원하는 출력값이 아닙니다. 
이 때 올바른 출력을 위해 사용하는 것이 !(exclamation mark), 즉 느낌표입니다. 즉, optional로 선언했지만, 
무조건 변수가 있는 상황이 보장된 경우 느낌표(!)를 쓰면 우리가 원하는 Hello을 출력할 수 있습니다.


Optional Binding은 Optional 타입으로 선언된 변수에 값이 있는지 없는지를 확인할 수 있도록 해주는 기능입니다. 
Optional Binding을 사용하면 느낌표 없이 Optional
 타입의 변수 값을 출력할 수 있어서 좀 더 안전한 형태로 값을 얻을 수 있습니다. 기본적인 형태는 다음과 같습니다.
 if let 변수명 = Optional 변수 {
 // 임시 변수에 Optional 변수의 value값이 할당됩니다.
}

?.는 존재하지 않아도 괜찮은 대상에만 사용해야 합니다.

옵셔널 체이닝의 등장
?.은 ?.'앞’의 평가 대상이 undefined나 null이면 평가를 멈추고 undefined를 반환합니다.

user?.address로 주소를 읽으면 아래와 같이 user 객체가 존재하지 않더라도 에러가 발생하지 않습니다.


NOTE

Swift’s nil isn’t the same as nil in Objective-C. In Objective-C, nil is a pointer to a nonexistent object.
 In Swift, nil isn’t a pointer—it’s the absence of a value of a certain type. 
 Optionals of any type can be set to nil, not just object types.


Once you’re sure that the optional does contain a value, you can access its underlying value by adding an exclamation point (!)
 to the end of the optional’s name. The exclamation point effectively says, 
“I know that this optional definitely has a value; please use it.” 
This is known as forced unwrapping of the optional’s value:


NOTE
Trying to use ! to access a nonexistent optional value triggers a runtime error. 
Always make sure that an optional contains a non-nil value before using ! to force-unwrap its value.

Info.plist 

<key>UIUserInterfaceStyle</key>
<string>Light</string>


====================================================================================================================







