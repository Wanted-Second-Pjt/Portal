#include "DebugHelperTable.h"
#include "DebugHelperVVV.h"

bool UDebugHelperVVV::bCleaningData = false;

bool UDebugHelperVVV::PreventGetter()
{
	return bCleaningData;
}

void UDebugHelperVVV::SetInitTiming()
{
	FWorldDelegates::OnPostWorldCreation.AddStatic(&UDebugHelperVVV::InitData);
}

void UDebugHelperVVV::SetCleanupTiming()
{
	FWorldDelegates::OnWorldCleanup.AddStatic(&UDebugHelperVVV::CleanupData);
}

void UDebugHelperVVV::InitData(UWorld* World)
{
	DEBUG_HELPER_VVV::Log("InitData");
	bCleaningData = false;
}

void UDebugHelperVVV::CleanupData(UWorld* World, bool bSessionEnded, bool bCleanUpResources)
{
	DEBUG_HELPER_VVV::Log("CleanData");
	bCleaningData = true;
}
