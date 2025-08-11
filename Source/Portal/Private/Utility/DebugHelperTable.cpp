#include "DebugHelperTable.h"
#include "DebugHelperVVV.h"

bool UDebugHelperTable::bStopData = false;
TMap<uint32, FString> UDebugHelperTable::DebuggingLocationMap = TMap<uint32, FString>();

void UDebugHelperTable::RememberLocation(const uint32& Key, const FString& Location)
{
	DebuggingLocationMap.Add(Key, Location);
}

void UDebugHelperTable::RememberLocation(const FString& Location)
{
	DebuggingLocationMap.Add(FCrc::StrCrc32(GetData(Location)), Location);
}

bool UDebugHelperTable::PreventGetter()
{
	return bStopData;
}

void UDebugHelperTable::SetReStartTiming()
{
	//FWorldDelegates::OnPostWorldCreation.AddStatic(&UDebugHelperVVV::InitData);
}

void UDebugHelperTable::SetStopTiming()
{
	//FWorldDelegates::OnWorldCleanup.AddStatic(&UDebugHelperVVV::ReStartData);
}

void UDebugHelperTable::SetDestroyTiming()
{
	FEditorDelegates::PrePIEEnded.AddStatic(&UDebugHelperTable::DestroyData);
}

void UDebugHelperTable::InitData(UWorld* World)
{
	bStopData = false;
}

void UDebugHelperTable::StopData(UWorld* World, bool bSessionEnded, bool bCleanUpResources)
{
	bStopData = true;
}

void UDebugHelperTable::DestroyData(bool bIsSimulating)
{
	for (const TPair<uint32, FString>& It : DebuggingLocationMap)
	{
		UE_LOG(LogPath, Type::Warning, TEXT("%s"), *It.Value);
	}
	
	DebuggingLocationMap.Empty();
}
