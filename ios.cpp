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


 https://www.raywenderlich.com/
Ios 이론
 
스위프트의 옵셔널은 일종의 안전장치이다. 예상치 못한 곳에서 nil이 발생하여 프로그램이 예기치 않게 종료되는 것을 막기위해 사용한다. nil이 될 수 있는 인스턴스는 반드시 옵셔널타입으로 선언해야한다.
반대로, 옵셔널타입으로 선언되어있지 않은 인스턴스는 nil이 되지 못한다! (일반 자료형에 nil은 억지로 대입할 수도 없음)
 
if let에서 언래핑과정이 암묵적으로 수행되어 옵셔널의 값이 임시 상수로 지정된다.(theError)
var errorCodeString: String?
errorCodeString = "404"
 
if let theError = errorCodeString {
    print(theError)
}
 
 
?
옵셔널로 변수를 선언했고 그때 ?를 사용했다면 우리는 ‘노크’를 했다고 생각하면 된다.
이때 만약 값을 가지고 있다면 해당하는 값을 반환해주고 값이 없다면 nil을 반환하게 된다. 이때 nil 또한 메모리를 차지하고 있다.’
 
var someValue: Int? = 30
var Value = someValue
이때 위 코드에서 Value의 타입은 무엇일까? 바로 옵셔널이다.
즉, Value는 옵셔널 타입이며 Int데이터형을 가질 수 있는 변수를 의미한다. 이는 Int일수도 있고 Int가 아닐수도 있다.
 
 
 
 
var someValue: Int? = 30
var Value: Int = someValue
그런데 만약 위처럼 Value에 Int 타입을 지정해줬다고 해보자. 오류가 뜨게 될 것이다.
기본적으로 Int와 Int?는 다른 타입이다.
someValue는 옵셔널타입으로 값을 가질수도 있고 nil을 가질수도 있다. 그런데 Value에는 무조건 Int 타입만을 가질것이라고 선언을 해줬다.
그러니 당연히 Value는 someValue를 받아들이지 못할 것이다. 따라서 Int와 Int? 즉 옵셔널인 것과 옵셔널이 아닌것은 완전히 다른 타입을 의미하는 것을 알아야 한다.
 
 
!
!는 ?와 다르게 강제로 값을 빼내오는 것을 의미한다. 유명한 짤로 망치로 상자를 부수는 것이 떠오를 것이다.
이는 강제 언래핑(Unwrapping)이라고 하고 이 단어가 의미하는 것은 상자안에 값이 있든 없든 무조건 값을 가져오겠다는 것을 의미한다.
깨부순 상자안에는 값이 있을수도 있고 없을 수도 있을 것이다.
 
 
 
var someValue: Int? = 30
var Value: Int = someValue
위에서 본 예제를 다시 한번 봐보도록 하자. 오류가 났던 위 예제를 아래처럼 고쳐보도록 하자
var someValue: Int? = 30
var Value: Int = someValue!
 
 
 
 
 
자. 강제로 상자를 부쉈기때문에 에러는 발생하지 않았을 것이다. 그리고 다행히 상자 안에는 30이라는 값이 있었기 때문에 30이라는 숫자또한 값을 가지게 될 것이다. 그렇기 떄문에 옵셔널이
아닌 Int형의 Value라는 변수안에 데이터(30)이 들어갈 수 있게 될 것이다. 상자를 부수고, 값을 꺼내어 그 값을 Value안에 넣어준 코드이니 Value입장에서는 문제가 없을 것이다.
(Value는 Int형 데이터만을 받고 있는데 운이좋게 someValue에는 30이라는 Int형의 데이터가 있었기 때문이다)
그런데 만약 상자안에 값이 없다면? 생각해보자
 
var someValue: Int? = nil  // someValue는옵셔널타입으로 nil이들어갈수있다
var Value: Int = someValue!
 
컴파일 오류도 일어나지 않을 것이며 build success도 되겠지만 금방 런타임에러가 발생하게 될 것이다.
 
 
!를 사용해 값이 존재하지 않는 옵셔널 값에 접근하려 시도하면 런타임 에러가 발생한다. 
느낌표를 사용해 강제 언랩핑을 하기 전에는 항상 옵셔널값이 nil이 아님을 확실히 해야한다.
즉, nil이 아니라는 것이 확실하지도 않은 상태에서 !를 남용하면 에러가 날 확률도 높아질 것이다. 그리고 !도 옵셔널이기 때문에 초기화할 때
갑을 요구하지 ㅇ낳는다. 초기화해주징낳으면 ?와 마찬가지로 nil값이 들어가게 될 것이다. 잊지말자
그러면 이제 옵셔널 타입의 변수값을 가져오는 방법에 대해 생각해 보자
 
옵셔널 바인딩(Optional Bounding)
옵셔널 바인딩은 주로 if let(if var)구문과 같이 사용된다. 즉 먼저 체크해준다 를 생각하면 이해하기 쉽다.
이 값이 nil인지, 값이 있는지 경우에 따라 결과를 달리하고 싶을때 옵셔널 바인딩을 사용해 겁사해주면 된다.
func printName(_name:String) {
  print(_name)
}
 
var myName: String? = nil
if let name = myName {
  printName(_name: name)
}
 
실행해보면 콘솔창에는 아무것도 나오지 않을 것이고(myName은 nil값으로 초기화되어있기 때문) 이는 if let구문이 myName이라는 상자에
노크해보고 값이 있으면 name에 넣어주고 조건문을 실행해 라는 것을 의미한다는 것을 알 수 있을 것이다. 이때 값이 있는 경우에만 값이 바인딩 되기 때문에 콘솔창에는 아무것도 실행되지 않아 비어져있을 것이다.
 
 
옵셔널 체이닝(Optional Channing)
옵셔널 체이닝은 하위 프로퍼티에 옵셔널값이 있는지 없는지를 연속적으로 확인하면서 중간에 하나라도 nil이 존재함다면 nil이 반환되는 형식을 의미한다.
 
let roomCount = zehye.residence?.numberOfRoomes
 
위처럼 진행하는 방식이 옵셔널 체이닝이다. 이때 zehye의 residence가 nil이 아니라면 다음으로 넘어가 residence의 numberOfRoomes를
확인하게 될 것이다. 만약 zehye의 residence가 nil이라면 뒤의 else문을 수행하게 될 것이다. 그런데 이때 residence 뒤에 왜 ?가 붙을까?
그 이유는 residence가 nil을 반환할 수도 있고 아닐수도 있기 때문이다.
 
즉 하위 프로퍼티에 옵셔널 값이 있는지 연속적으로 확인하면서 중간에 하나라도 nil이 발견된다면 nil을 반환하는 것을 옵셔널체이닝 방식이라고 한다.
그러면 이때 roomCount의 타입은 무엇일까? 당연히 옵셔널 타입일 것이다. 즉 우리가 특별히 지정해주지 않았음에도 불구하고 roomCount의 타입은 옵셔널임을 알 수 있다.
 
그 이유는 zehye.residence?.numberOfRoomes가 nil을 반환할 수도 있고 아닐수도 있기 때문이다.
 
 
 
그러면 도대체 !를 왜 쓰는 것일까? 일단 우선적으로 !는 최대한 적게 사용하는 것이 좋다. 그러나 유용하게 쓸 수 있는 구석은 있다.
!는 언제 사용할까?
때로는 프로그램의 구조상 옵셔널 값을 먼저 설정한 후 그 값이 항상 있는 것이 명백한 경우가 있다.
즉 변수에 값이 있다는 것을 확신할 수 있는 경우를 의미한다. 그런때에 우리가 옵셔널 바인딩과 체이닝을 사용해 조건문을 사용할 이유가 있을까?
없다고 생각한다! 이런 종류의 옵셔널을 implicitly unwrapped optionals이라고 정의한다. 직역을 하자면 암시적으로 언랩핑된 옵셔널? 이라고 할 수 있을 것이다.
이는 주로 클래스 초기화 과정에서 사용된다고 한다.
 
class ViewContrller: UIViewController {
  @IBOutlet weak var leftButton: UIButton!
}
이렇게 IBOutlet같은 변수는 연결했다는 것을 확실히 할수 있기 때문에 !를 붙힐 수 있는 것이다.
근데 이렇게 IBOutlet을 선언했음에도 이 버튼을 사용할수도 안사용할수도 있을 텐데 그럴때는 ?를 사용하면 된다. 만약 ? 혹은 ! 둘다 붙이지 않는다면 에러가 뜨게 될
것이다 > UIButton타입은 non-optional일 수 없는 프로퍼티라는 의미의 에러일 것이다.
 
 
 
지금까지의 실습에서 나는 무조건 IBOutlet 뒤에는 무조건 !를 썼지만 사실 이런 사용법도 좋은 방법이 아니라고 한다. 무조건적으로 !의
사용은 줄이는 것이 좋다고 한다. 지금에야 확실히 이 버튼을 사용한다는 확신이 있지만 연결이 되지 않은 경우도 생길 수 있기 때문이다. 즉 만약을 대비하여
UIButton?을 사용하는 것이 훨씬 좋은 방법이라고 한다! 앞으로의 코드는 ?를 사용하도록 해야지
즉 정리하면 !는 옵셔널 바인딩, 체이닝으로 매번 값을 추출하기 귀찮거나 로직상으로 nil이 할당되지 않을 것 같다는 확신이 들때 사용하면 될 것같다.
 
옵셔널은 왜 사용하는 것일까?
swift는 일반적으로 아래와 같은 언어이다
1. Safe
2. Fast
3. Expressive
옵셔널을 통해 swift의 안정성을 제공한다.
그리고 더 나아가 프로그래머들간의 원활한 커뮤니케이션을 위해 사용한다고 생각한다.
코드만으로도 변수들이 어떤 타입을 가질지 명확하게 보여주며 함수의 파라미터 부분만 봐도 여기에 어떠한 값들이 들어올 수 있는지 추측이 가능하기 때문이다.
 
 
 
 
iOS GCD에 대해서 알아보기 (DispathQueue)
안녕하세요. 마기입니다.
이번 포스팅에서는 멀티스레딩을 위한 API를 알아보겠습니다.
쉽고 편한 멀티 스레딩 처리를 위해 애플은 두가지의 API를 제공하고 있습니다.
GCD(Grand Central Dispatch)라는 C기반의 저수준 API와
NSOperation이라는 Obj-C 기반으로 만들어진 고수준 API가 있습니다.
NSOperation은 GCD보다 약간의 오버헤드가 더 발생되고 느리지만
GCD에서는 직접 처리해야 하는 작업들을 지원 하고 있기 때문에
(KVO관찰, 작업취소 등등) 그정도는 감수하고 사용할만 합니다.
이번 포스팅에서는 부담없이 사용할수 있는 GCD에 대해서 알아보도록 하겠습니다.
 
DispatchQueue
GCD를 사용하기전에 먼저 알아야 할 클래스가 있습니다.
바로 DispatchQueue라는 클래스인데요.
실제로 해야할 Task를 담아두면 선택된 스레드에서 실행을 해주는 역할을 합니다.
DispatchQueue는 2가지로 종류로 나눌수 있습니다.
Serial Dispatch Queue와 Concurrent Dispatch Queue입니다.
- Serial Dispatch Queue
  
   Serial Queue는 등록된 작업을 한번에 하나씩 차례대로 처리 합니다.
  
  처리중인 작업이 완료되면 다음 작업을 처리합니다.
- Concurrent Dispatch Queue
  
   Concurrent Queue는 등록된 작업을 한번에 하나씩 처리 하지 않고
  
  여러 작업들을 동시에 처리합니다.
let serialQueue = DispatchQueue(label: "magi82.serial")
print(serialQueue) // Serial Dispatch Queue
 
let concurrentQueue = DispatchQueue(label: "magi82.concurrent",
                                    attributes: .concurrent)
print(concurrentQueue) // Concurrent Dispatch Queue
앱 실행시 시스템에서 기본적으로 2개의 Queue를 만들어 줍니다.
Main Queue와 Global Queue 입니다.
- Main Queue
  
  메인 스레드(UI 스레드)에서 사용 되는 Serial Queue 입니다.
  
  모든 UI 처리는 메인 스레드에서 처리를 해야 합니다.
- Global Queue
  
  편의상 사용할수 있게 만들어 놓은 Concurrent Queue 입니다.
  
   Global Queue는 처리 우선 순위를 위한 qos(Quality of service)
  
  파라메터를 제공합니다.
  
  병렬적으로 동시에 처리를 하기때문에 작업 완료의 순서는 정할수 없지만
  
  우선적으로 일을 처리하게 할수 있습니다.
let mainQueue = DispatchQueue.main
print(mainQueue) // Main Queue
let globalQueue = DispatchQueue.global(qos: .background)
print(globalQueue) // Global Queue
QOS 우선순위는 아래와 같습니다.
1. userInteractive
2. userInitiated
3. default
4. utility
5. background
6. unspecified
 
sync / async
Dispatch Queue는 sync와 async라는 메소드를 가지고 있습니다.
동기, 비동기라는 말을 많이 들어 보셨을 겁니다.
sync는 동기 처리 메소드 입니다.
해당 작업을 처리하는 동안 다음으로 진행되지 않고
계속 머물러 있습니다.
 
 
DispatchQueue.main.sync {
  print("value: 1")
}
print("value: 2")
 
// 결과
/*
  value: 1
  value: 2
*/
 
 
async는 비동기 처리 메소드 입니다. 
sync와는 다르게 처리를 하라고 지시후 다음으로 넘어가 버립니다. 
이번에는 시스템에서 제공하는 Global Queue로 테스트를 해보겠습니다.
let globalQueue = DispatchQueue.global(qos: .background)
globalQueue.async {
  print("value: 1")
}
print("value: 2")
 
// 결과
/*
  value: 2
  value: 1
*/
 
보통 스레드 처리를 하는 작업들은 시간이 꽤나 걸리는 큰 작업이거나
언제 끝날지 알수 없는 작업에 사용 되는데 (ex: 네트워크, 파일로딩)
작업이 처리 되는동안 아무것도 하지 못하고 멈춰 있으면
앱이 렉이 걸리거나 아무 반응이 없는거처럼 보입니다.
그래서 보통 동기 처리 메소드인 sync는 잘 사용하지 않습니다.
간혹가다가오해하는분들이계신데
Serial / Concurrent와 sync / async 는별개입니다. 
직렬인데비동기일수도있고, 병렬인데동기일수도있습니다. 
직렬과병렬은한번에하나만처리하느냐동시에여러개처리하느냐고
동기와비동기는처리가끝날때까지기다리느냐
지시만하고다른처리를하느냐입니다.
 
 
NotificationCenter에등록된 Event가발생하면해당 Event들에대한행동을취하는것.
앱내에서아무데서나메시지를던지면앱내의아무데서나이메시지를받을수있게해주는것이 NSNotificationCenter의역활.
 
 
post
post는 전송 하는 notification입니다.
myNoti를 Observer에게 전달할 값을 전달해주는 부분 입니다.
1
NotificationCenter.default.post(name:"myNoti",   object:" 전달할 값")
 
 
Observer 등록
옵저버란 말그대로 계속 탐지하는거라고 보시면 되는데, 뭘 탐지하느냐!
name이라는 키 값을 탐지하는겁니다.
어떤 객체가 "myNoti"라는 name으로 notification을 전송 했는데 옵저버에서 탐지 하고있다가 "myNoti"가 오면 수행 하는 녀석 입니다!
1
2
3
4
NotificationCenter.default.addObserver(observer:Any,   selector:Selector, name: NSNotification.Name?, object:Any?)
 
//구현
NotificationCenter.default.addObserver(self, selector:   #selector(handleNoti(_:)), name: myNoti, object: nil)
 
 
 
 
위의 소스를 보면, myNoti라는 name의 notification이 오면 selector를 실행하라 라는 뜻입니다.
1
2
3
4
@objc func handleNoti(_ noti: Notification) {
    print(noti)
    print("handleNoti")
}
 
 
 
 
 
selector의 handleNoti를 실행하면 파라미터로 post가 넘긴 name = myNoti, object = Optional(전달할 값), userInfo = nil 값이 넘어오게 됩니다.
 
Remove Observer
NotificationCenter 는 싱글턴 인스턴스라서 여러 오브젝트에서 공유합니다. 그래서 옵저버를 등록한 오브젝트가 메모리에서 해제되면 NSNotificationCenter에서도 옵저버를 없앴다고 알려줘야 됩니다.
1
2
3
4
5
//  self에 등록된 옵저버 전체 제거
notiCenter.removeObserver(self)
 
//옵저버 하나 제거(등록된 특정 노티를 제거하기   위해 사용)
notiCenter.removeObserver(self, name:   NSNotification.Name.UIKeyboardDidShow, object: nil)
보통은 Counterpart되는곳에 맞춰서 해제 시켜줍니다.
viewWillAppear < - > viewWillDisappear
viewdidload() < - > deinit() : 1번씩만 호출되니까
 
전체 코드 확인
 
ViewController

81
class ViewController: UIViewController {
 
    let notiCenter = NotificationCenter.default
    
    var observer: NSObjectProtocol? //   addObserver에 반환값이 있는 메서드를 사용할때 해제 해주어야 할 프로퍼티
    
    override func viewDidLoad() {
        super.viewDidLoad()
 
        //object는 어떤객체를 전달할지 queue는 스레드 using은 수행할 로직.
          //NSNotification.Name.UIKeyboardWillShow 키보드가 나타나기 직전에 알려줘라
        // .을 사용하면 여러가지 설정이 있다.
        // 시스템에서 어떤 일이 일어났을때 캐치를   하고싶을때 컨트롤하고싶을때 notification을 사용해서 알 수 있다.
          notiCenter.addObserver(forName: NSNotification.Name.UIKeyboardWillShow,   object: nil, queue: .main) { (noti) in
            print(noti)
              print("UIKeyboardWillShow")
        }
        
        
        /***************************************
         # 노티피케이션을 이용해서 클로저로   반환을 하면은
         NSObjectProtocol라는   타입이 있기 때문에
         
         이런식으로 NSObjectProtocol를 해제해주어야된다.
           notiCenter.removeObserver(observer)
           ****************************************/
        observer =   notiCenter.addObserver(forName:   NSNotification.Name.UIApplicationDidBecomeActive, object: nil, queue: .main)   { (noti) in
            print(noti)
              print("UIApplicationDidBecomeActive")
        }
 
        //Device가 회전했는지 체크
          //notiCenter.addObserver(forName:   NSNotification.Name.UIDeviceOrientationDidChange, object: nil, queue: .main)   { (noti) in
            //print(noti)
              //print("UIDeviceOrientationDidChange")
        //}
        
        
        notiCenter.addObserver(self,   selector: #selector(deviceOrientationDidChange(_:)), name:   NSNotification.Name.UIDeviceOrientationDidChange, object: nil)
        //똑같은   Notification이 등록되면 중복되서 날라간다.
          //notiCenter.addObserver(self, selector: #selector(deviceOrientationDidChange(_:)),   name: NSNotification.Name.UIDeviceOrientationDidChange, object: nil)
        
        
    }
 
    @objc func deviceOrientationDidChange(_   noti: Notification) {
        print(noti)
        print("deviceOrientationDidChange")
    }
    
    // 매칭되는곳에 맞춰서 해제 시켜줘야된다.viewWillAppear <-> viewWillDisappear
    // viewdidload() <-> deinit() : 1번씩만   호출되니까
    override func viewWillAppear(_ animated:   Bool) {
          super.viewWillAppear(animated)
    }
    
    //NotificatioCenter는 싱글턴이여서 메모리가 계속 상주하기   때문에 해제를 시켜줘야된다.
    override func viewWillDisappear(_ animated:   Bool) {
          super.viewWillDisappear(animated)
        
          notiCenter.removeObserver(self) //  self에 등록된 옵저버 전체 제거
        notiCenter.removeObserver(self,   name: NSNotification.Name.UIKeyboardDidShow, object: nil) //옵저버 하나 제거(등록된 특정 노티를 제거하기 위해 사용)
    }
    
    @IBAction func postButton(_ sender:   UIButton) {
        
        //AnotherVC에 있는 myNoti에 송출하기 위해 사용.
        NotificationCenter.default.post(name:   myNoti, object: "김승진")
    }
    
    
    deinit {
        print("deinit")
    }
    
    override func didReceiveMemoryWarning() {
          super.didReceiveMemoryWarning()
        // Dispose of any resources   that can be recreated.
    }
 
}
AnotherViewController

import UIKit
 
let myNoti = Notification.Name.init("myNoti")   // 외부에서 접근 가능하도록 하기위해 클래스 위에 선언한것.
 
//NotiName을 설정하는 방법의 또다른 방식.
extension Notification.Name {
    static let myNoti2 =   Notification.Name.init("kMyNoti2")
}
 
class AnotherViewController: UIViewController {
 
    override func viewDidLoad() {
        super.viewDidLoad()
 
          NotificationCenter.default.addObserver(self, selector:   #selector(handleNoti(_:)), name: myNoti, object: nil)
        NotificationCenter.default.addObserver(self,   selector: #selector(handleNoti(_:)), name: Notification.Name.myNoti2, object:   nil)
    }
 
    //myNoti라 Name이라는   것을 받으면 작동하는 메서드
    @objc func handleNoti(_ noti: Notification)   {
        print(noti)
        print("handleNoti")
    }
    
    override func didReceiveMemoryWarning() {
          super.didReceiveMemoryWarning()
        // Dispose of any resources   that can be recreated.
    }
}
 
 
 
- Selector란?
  
   Selector는 Objective-C에서 사용하던 개념으로, Objective-C의 객체의 메소드를 문자열을 통해 지정하고 호출하는 방법입니다. KVC의 메소드 버전이라고 생각하시면 됩니다.
- 실제로는 해당 메소드가 존재하는 메모리의 포인터 값이며, 이를 이용해서 Objective-C 런타임은 실제 호출할 함수를 동적으로 결정하게 됩니다. 동적으로 결정하게 된다는 것은
- 컴파일 타임에는 어떤 메소드를 호출할지 알 수 없고, 실행 시점에서야 실제 호출할 메소드를 결정한다는 의미입니다. 이 때 이전 포스트에서 다룬 message dispatch가 사용됩니다.
  
   Swift2 이전에는 셀렉터를 만들 때 문자열 리터럴을 그대로 이용했지만 Swift3 이후로는 #selector() 문법을 이용해서 셀렉터 객체를 만들 수 있도록 하였습니다. 
	본질은 달라지지 않았지만,
- 이렇게 하면 컴파일러가 셀렉터의 유효성을 알 수 있어서 빠르게 에러를 잡아내고, 자동완성 등의 편리한 기능등을 제공해 줄 수 있게 되었다는 것은 큰 장점입니다.
 
 
 
1. Selector
변수 선언 : SEL 변수 = @selector(함수이름); 
셀렉터를 이용하여 함수 사용 : [클래스 변수 performSelector:@selector(함수이름)];
[a performSelector:@selector(go:) withObject:(id)10];
[a performSelector:@selector(go:speed:) withObject:(id)10 withObject:(id)10];
withObject는 2개까지 지원
 
2. Selector는 함수 포인터다?
제목에서 알 수 있듯이 잘못됌
다른 클래스에 같은 이름의 함수가 있을경우 함수포인터라면 다른 주소를 가져야함
근데 @selector를 만들때 클래스를 구분할 수 없다.
그래서 selector를 가져와 보면 동일한 selector를 가짐
따라서 함수포인터가 아니다.
클래스가 다르더라도 함수이름이 동일하면 셀렉터는 동일
 
3. 동작 원리
클래스의 객체 생성 시 주소가 100이라면 포인터가 주소 100번지를 가짐
내부적으로 함수테이블 만듬 (가상함수 테이블, 모든 함수의 주소를 가지는 테이블, 문자열/주소를 가짐, 함수테이블때문에 부하가 있다.)
 
셀렉터 생성하면 함수 문자열 생성 selector는 그 시작 주소를 가리킴(따라서 함수 이름만 아는거)
따라서 @selector(함수명) 는 const char*s1 = “함수명”; 와 같은 의미
 
따라서 없는 함수 foo를 셀렉터로 만들어 실행해보면 selector를 만들때
SEL s = @selector(foo);
[a performSelector:s];
둘다 컴파일 에러는 나지 않는다.
왜냐하면 단지 함수 테이블에서 없는 foo라는 문자열을 찾아서 그 주소를 따라가라는 뜻이기 때문에
 
하지만 실제로 클래스에는 해당 함수가 없기 때문에 런타임 에러가 난다.
 
Swift - 'as!' 오퍼레이터 살펴보기
 
as is compile time cast
as? and as! are runtime casts
- as? will cast, if cast not possible will return Optional(nil)
- as! will cast, if cast not possible will crash with runtime error 🔫
Example:
class Music { }
class Pop: Music { }
class Rock: Music { }
 
Pop() as Music // OK, some might disagree but Music *is* a super class of Pop
Pop() as Rock  // Compile error: 'Pop' is not convertable to 'Rock'
 
let pop: AnyObject = Pop()
 
pop as Music // Compile error: 'AnyObject' is not convertible to 'Music'
 
pop as? Pop // Pop
pop as! Pop // Pop
pop as? Music // Pop
pop as! Music // Pop
 
pop as? Rock // nil
pop as! Rock // Runtime error signal SIGABRT
 
 
 
 
 
 
AnyObject를 "모든 클래스가 암시적으로 준수하는 프로토콜"이라고 정의해놓았네요. 
그리고 OverView의 마지막줄을 보시면,
 
"AnyObject can be used as the concrete type for an instance of any class, class type, or class-only protocol. "
AnyObject는 클래스, 클래스 타입 또는 클래스 전용 프로토콜의 인스턴스에 대한 구체적인 타입으로 사용될 수 있습니다.
 
라고 하네요. 
그러니까!!위에서 에러가 난 이유는 배열 안에 있는 값들이 클래스타입이 아니기때문이죠.
















https://docs.swift.org/swift-book/LanguageGuide/Protocols.html  //swift 가이드문서 . 



Question
저는 그동안 UI 관련 동작을 수행하기 위해 DispatchQueue.main.async 를 계속 사용해왔습니다.

Swift는 DispatchQueue.main.async 와 DispatchQueue.main.sync 를 제공해주며 둘 다 main queue 에서 수행됩니다.

두 개의 차이가 무엇인지, 언제 무엇을 사용해야 하는지 알려주실 분이 계신가요?

DispatchQueue.main.async {
    self.imageView.image = imageView
    self.lbltitle.text = ""

}

DispatchQueue.main.sync {
    self.imageView.image = imageView
    self.lbltitle.text = ""
}
Answer
왜 동시성이 필요할까?
데이터 로딩 같은 무거운 작업을 실행하는 순간 어플리케이션의 UI는 느려지거나 멈추게 됩니다.
 동시성(Concurrency)은 2개 이상의 일(task)를 "동시에" 수행할 수 있도록 해줍니다. 동시성의 단점으로는 thread safety 이슈가 있습니다. 
 예를 들면 서로 다른 쓰레드에서 동일한 변수를 변경하려고 시도하거나, 이미 다른 쓰레드에 의해 블럭되어 있는 리소스에 접근하려 시도하는 등의 문제입니다.

우리가 알아야 할 몇 가지 추상적인 개념들이 있습니다.

Queues
동기/비동기처리의 퍼포먼스
Priorities
자주 발생하는 문제들
Queues
Queue 는 다음 두 가지 중 하나의 처리 방식을 가집니다.

serial (순차적으로 처리)
concurrent (동시에 처리)
또한 Queue 는 다음 두 가지 중 하나의 접근 범위를 가집니다.

global
private
(global serial queue, global concurrent queue, private serial queue, private concurrent queue 모두 가능하다는 말입니다.)

Serial queue 에서는 task 가 하나씩 수행되고 종료됩니다. 반면 concurrent queue 의 경우에는 여러 task 가
 동시에 수행되며 그 중 어느 것이 먼저 종료될지 알 수 없습니다. 같은 task 그룹을 수행한다면 당연히 concurrent queue 보다 serial queue 에서 더 많은 시간이 걸릴 것입니다.

Private queue 를 직접 생성하여 사용할 수도 있고 (serial 과 concurrent 모두 가능) 이미 제공되는 global 
(system) queue 들을 사용할 수도 있습니다. Main queue 는 global queue 중 유일한 serial queue 입니다.

UI와 관련없는 무거운 작업들, 예를 들어 네트워크에서 데이터를 받아오는 등의 작업은 main queue 대신 다른 queue 에서 돌리는 것이 권장됩니다.
 UI가 뻗지 않고 계속 유저 액션을 받을 수 있도록 말입니다. 그러나 UI 업데이트를 다른 queue 에서 하게 되면 예상했던 것과 
 다른 타이밍/속도로 반영될 위험이 있습니다. 몇몇 UI 요소는 필요한 시점 이전이나 이후에 그려질 수도 있습니다. 이것은 UI의 붕괴를 초래합니다. 
 Global queue 에 대해서도 염두에 두어야 할 사항이 있습니다. Global queue 는 system queue 이기 때문에 system 에 의한 다른 task 들이 돌아갈 수 있다는 사실입니다.

Quality of Service / Priority
Queue 에는 qos (Quality of Service) 를 설정할 수 있습니다. 이것에 따라 작업 수행에 대한 priority(우선순위)가 결정됩니다.
 우선순위가 높은 것부터 나열해보았습니다.
.userInteractive - main queue
.userInitiated - 유저가 시작한 작업이며, 유저가 응답을 기다리고 있음
.utility - 다소 시간이 걸리며 즉각적인 응답이 필요하지 않은 경우 (ex: 데이터 처리 작업)
.background - 눈에 보이지 않는 부분의 작업이고 완료 시간이 중요하지 않음

그리고 물론 이런 qos도 있습니다.

.default - qos를 딱히 설정하지 않은 경우. 이 경우 .userInitiated 와 .utility 사이가 된다.


작업은 동기적으로(synchronously) 수행되거나 비동기적으로(asynchronously) 수행됩니다.

Synchronous 함수는 작업이 다 끝난 다음에만 현재의 queue에게 컨트롤을 넘깁니다. 
그 전까지 현재의 queue 는 block 되어 작업이 끝날 때까지 기다려야 합니다.
Asynchronous 함수는 작업을 수행할 다른 큐에게 작업을 넘기자마자 현재의 queue에게 컨트롤을 돌려줍니다.
 작업이 끝나기 전까지 기다릴 필요가 없으며 현재의 queue 도 block 되지 않습니다.
자주 발생하는 문제들
프로그래머가 가장 많이 겪는 동시성 문제에는 다음과 같은 것들이 있습니다.

Race condition
Priority inversion
Deadlock
절대로 sync 함수를 main queue 에서 부르지 마십시오.
만약 main queue 에서 sync 함수를 부른다면 main queue 만이 아니라 작업이 완료되는 것을 기다리고 있는 queue 까지 block 될 것입니다.
 그러나 작업은 절대로 끝나지 않습니다. Queue 가 이미 block 상태이기 때문에 시작조차 할 수 없기 때문입니다. 이것을 데드락이라고 합니다.
(역주: 설명이 친절하지 않아 덧붙입니다. 정확히 말하면, 메인 쓰레드에서 main queue + sync 를 부르지 마십시오. 
Sync 함수의 특성 상, main queue 에 넣은 task 가 완료되기 전까지 메인 쓰레드는 blocking waiting 상태가 됩니다. 
그런데 이 ‘task’는 메인 스레드에서 serial 하게 실행이 되는 main queue에 들어가 있지요. 
따라서 이미 block 상태로 빠진 메인 쓰레드에서 작업은 영영 시작되지 않습니다. 이렇게 무한대기 상태로 빠지기 때문에 데드락이라고 하는 것입니다.)

언제 sync 를 사용하는가? 작업이 끝나는 것을 기다려야 할 때 사용하세요. 예를 들면 어떤 함수/메소드가 중복으로 불리지 않는 것을 보장해야 할 때 사용하세요.
 또 다른 예로는 하나의 동기화 작업을 진행하는 도중 이 동기화 작업을 중복으로 시도하지 않기 위해 사용하세요. 이것에 대한 코드는 여기서 볼 수 있습니다

GCD 중요 밑에 GCD 원문.
 https://www.raywenderlich.com/5370-grand-central-dispatch-tutorial-for-swift-4-part-1-2


===================================================================================================================

