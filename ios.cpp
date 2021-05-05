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
    self.progressBarViewController.labelProcessing2._string_Value = "\(NSLocalizedString("PROCESSING", comment: "진행 중")).. \(processPer)% (\(fileCntCurRef.pointee)/\(fileCntMax))"
}

DispatchQueue.main.async{
                    self.present(_alert_, animated: false, completion : nil)
}
 

