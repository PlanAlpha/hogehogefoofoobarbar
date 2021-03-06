/*********************************************
 
 　　　　　　　　　　　 i!
 　　　　　　　　＿＿＿ﾉ;}
 　　　　　 ,　 ´: : : : : ｀ヽ、,_ _
 　　　　／: : : : : :: : : : : : ＼:ヽ
 　　　/: : : l: : | : : : : ﾄ、 : ヽ :ヽ
 　　/: : : :  : 八 : :: :./:.ヽ_ : ヽ: |
 　 ,: :: : : !: : :ﾉ 　ヽl＼/　　ヽ:ノ: |
 　 l: :: :|  / TT　　　 　TT 　:i: |: :j
 　 \:\ :: :|　　Ｕ　 　　　Ｕ 　 |: | :,'
 　　 ＼: ::i 　 , ,　　　　, , :l::八丿
 　　　　ヽ :|_ 　　　　＿,　　ｨ~
 　　　　　ヽrｹ､=‐-t------r-ァ:イ/
 　 　 　 　 ｀　., '｀iヽヽ//､::i|:;
 　　　　　　　/　 ,'个-｀_8:、｀､
 　　　　　　 /　 ,'::;;:;:;: 、ヽ
 　　　　　 /((┃))＿＿＿＿_＿i　|　 キュッキュッ
 　　　　  /ヽ,,⌒) ￣￣￣￣￣（,,ノ ＼
 　　　   /＿＿＿＿＿＿＿＿＿＿ヽ.. 　  ＼

 
 
 　　　　　　　　　　　 i!
 　　　　　　　　＿＿＿ﾉ;}
 　　　　　 ,　 ´: : : : : ｀ヽ、,_ _
 　　　　／: : : : : :: : : : : : ＼:ヽ
 　　　/: : : l: : | : : : : ﾄ、 : ヽ :ヽ
 　　/: : : :  : 八 : :: :./:.ヽ_ : ヽ: |
 　 ,: :: : : !: : :ﾉ 　ヽl＼/　　ヽ:ノ: |
 　 l: :: :|  / TT　　　 　TT 　:i: |: :j
 　 \:\ :: :|　　Ｕ　 　　　Ｕ 　 |: | :,'
 　　 ＼: ::i 　 , ,　　　　, , :l::八丿
 　　　　ヽ :|_ 　　　　＿,　　ｨ~
 　　　　　ヽrｹ､=‐-t------r-ァ:イ/
 　 　 　 　 ｀　., '｀iヽヽ//､::i|:;
 　　　　　　　/　 ,'个-｀_8:、｀､
 　　　　　　 /　 ,'::;;:;:;: 、ヽ
 　　　　　  |￣￣￣￣￣￣￣￣￣￣￣|　　ﾄﾝ
 　　 　（,,)　　　　　　　　　　(,,）_
 　 　  ／.　|   PlanAlpha.h    |＼
   　 ／　　.|＿＿＿＿＿＿＿＿＿＿.|　 ＼
 
**********************************************/

#ifndef __PlanAlpha__
#define __PlanAlpha__

#include "Robot_APIs/PASpeaker.h"
#include "Robot_APIs/GCADJD.h"
#include "Robot_APIs/GC6050.h"
#include "Robot_APIs/PAL3G4200D.h"
#include "Robot_APIs/PALineSensor.h"
#include "Robot_APIs/PAThreeLineSensors.h"
#include "Robot_APIs/GCMotor.h"
#include "Core_APIs/DigitalIn.h"

namespace PlanAlpha {
    extern PASpeaker<4>       speaker1;
	extern PASpeaker<9>		  speaker2;
    extern GCADJD             leftColorSensor;
    extern GCADJD             rightColorSensor;
    extern GC6050             gyroAcceleroSensor;
    extern PAL3G4200D         gyroSensor;
    extern PALineSensor       forwardLeftLineSensor;
    extern PALineSensor       forwardCenterLineSensor;
    extern PALineSensor       forwardRightLineSensor;
    extern PALineSensor       middleLeftLineSensor;
    extern PALineSensor       middleRightLineSensor;
    extern PAThreeLineSensors forwardLineSensors;
    extern GCMotor            leftMotor;
    extern GCMotor            rightMotor;
    extern DigitalIn          powerSwitch;
}

#endif
