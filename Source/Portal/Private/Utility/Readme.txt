1. 
DebugHelper / DebugMacro
DebugHelper.h 만 include 하시면 사용 가능합니다.

2. 
컴파일 타임이 조금 늘어납니다.
[MyProjectName].h 에 추가하면 미리 컴파일된 헤더로서 사용 가능합니다.
한번만 컴파일 하면 해당 컴퓨터에서는 크게 걱정할 정도로는 오래 안걸립니다.

3.
Hashing이 런타임에 NameTable을 이빠이 만들 수 있습니다.
그래도 생각보다 타이트 하진 않습니다. (FName 을 써서 그렇습니다)
게임을 종료하면(정지 버튼 누르면) FName 테이블 다 초기화됩니다.
이 외에는 런타임에 영향을 주지 않습니다.

/* API
*	Useful Macro. You can **" Copy And Paste these with Double-Click "**
*	**" Write  `debughelper` "** Makes Auto Word Completions

* Log
DEBUG_HELPER_LOG_THIS_LINE
DEBUG_HELPER_WARNING_THIS_LINE
DEBUG_HELPER_LOG_THIS_INSTANCE(this)

* Print On Screen
* () : Can Use Without ((Argument))
* This : Send To Argument "this" in your instance
* In : Send To Argument "your value" in your class
* Key : If `equal key` is inserted, one Message Cover the other.
* if Key is empty, Use SelfHashing (Fast, not to worry)


DEBUG_HELPER_PRINT_LINE((Key))						// if empty args, Print "current line"
DEBUG_HELPER_PRINT_INSTANCE((instance||this, Key))		// if empty args, Print "current this"

DEBUG_HELPER_PRINT_BOOL(InBool (, Key))
DEBUG_HELPER_PRINT_INT(InInt (, Key))
DEBUG_HELPER_PRINT_FLOAT(InFloat (, Key))
DEBUG_HELPER_PRINT_VECTOR(InVec (, Key))
DEBUG_HELPER_PRINT_ROTATOR(InRot (, Key))
DEBUG_HELPER_PRINT_QUAT(InQuat (, Key))

*/