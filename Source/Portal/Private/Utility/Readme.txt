* 1. 
Source/Private가 존재한다면 그곳에 만드시면 됩니다. Blueprint에선 사용할 수 없습니다.
Utility/DebugHelper.h 만 include 하시면 사용 가능합니다.
아래에 자주 쓰이는 매크로만 따로 정리해두었습니다. 함수도 물론 쓸 수 있습니다.
혹시 등록이 안된다면 에디터 켜시고 ` Tool-Refresh {IDE} ... ` 을 누르시면 됩니다.

* 2. 
컴파일 타임이 조금 늘어납니다.
` Source/{MyProjectName}/{MyProjectName}.h ` 에 추가하면 미리 컴파일된 헤더(pch)로서 사용 가능합니다.
한번만 컴파일 하면 해당 컴퓨터에서는 크게 걱정할 정도로는 오래 안걸립니다.

* 3.
Debug 장소를 기억했다가 게임이 끝날 때 노란색 로그로 보여줍니다.
추후 발표용 혹은 배포때는 해당 기록을 보고 지워주시면 됩니다. (pch 등록을 안하셨다면 include 도 지워주세요
게임을 종료하면(정지 버튼 누르면) 테이블 다 초기화됩니다.
이 외에는 런타임에 영향을 주지 않습니다.


/* API
*	Useful Macro. You can **" Copy And Paste these with Double-Click "**
*	**" Write  `debughelper` "** Makes Auto Word Completions

* Log
DEBUG_HELPER_LOG(Msg)
DEBUG_HELPER_WARNING(Msg)
DEBUG_HELPER_LOG_THIS_LINE
DEBUG_HELPER_WARNING_THIS_LINE
DEBUG_HELPER_LOG_THIS_INSTANCE(Instance)


* Print On Screen
* () : Can Use Without ((Argument))
* This : Send To Argument "this" in your instance
* In : Send To Argument "your value" in your class
* Key : If `equal key` is inserted, one Message Cover the other.
* if Key is empty, Use SelfHashing (Fast, not to worry)

DEBUG_HELPER_PRINT_SCREEN(Msg (, Key))

DEBUG_HELPER_PRINT_LINE((Key))						// if empty args, Print "current line"
DEBUG_HELPER_PRINT_INSTANCE((instance||this, Key))		// if empty args, Print "current this"

DEBUG_HELPER_PRINT_BOOL(InBool (, Key))
DEBUG_HELPER_PRINT_INT(InInt (, Key))
DEBUG_HELPER_PRINT_FLOAT(InFloat (, Key))
DEBUG_HELPER_PRINT_VECTOR(InVec (, Key))
DEBUG_HELPER_PRINT_ROTATOR(InRot (, Key))
DEBUG_HELPER_PRINT_QUAT(InQuat (, Key))

*/