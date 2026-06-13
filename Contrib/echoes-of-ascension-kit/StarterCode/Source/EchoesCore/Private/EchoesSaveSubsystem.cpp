// Echoes of Ascension - starter scaffold.

#include "EchoesSaveSubsystem.h"
#include "EchoesSaveGame.h"
#include "Kismet/GameplayStatics.h"

const FString UEchoesSaveSubsystem::ProfileSlot = TEXT("Profile");

FString UEchoesSaveSubsystem::RunSlotForSeed(int32 Seed)
{
	return FString::Printf(TEXT("Run_%d"), Seed);
}

UEchoesProfileSaveGame* UEchoesSaveSubsystem::GetProfile()
{
	if (!CachedProfile)
	{
		CachedProfile = Cast<UEchoesProfileSaveGame>(
			UGameplayStatics::CreateSaveGameObject(UEchoesProfileSaveGame::StaticClass()));
	}
	return CachedProfile;
}

UEchoesRunSaveGame* UEchoesSaveSubsystem::GetRun()
{
	if (!CachedRun)
	{
		CachedRun = Cast<UEchoesRunSaveGame>(
			UGameplayStatics::CreateSaveGameObject(UEchoesRunSaveGame::StaticClass()));
	}
	return CachedRun;
}

void UEchoesSaveSubsystem::SaveProfile()
{
	FAsyncSaveGameToSlotDelegate Done;
	Done.BindUObject(this, &UEchoesSaveSubsystem::HandleSaveCompleted);
	UGameplayStatics::AsyncSaveGameToSlot(GetProfile(), ProfileSlot, 0, Done);
}

void UEchoesSaveSubsystem::SaveRun()
{
	UEchoesRunSaveGame* Run = GetRun();
	FAsyncSaveGameToSlotDelegate Done;
	Done.BindUObject(this, &UEchoesSaveSubsystem::HandleSaveCompleted);
	UGameplayStatics::AsyncSaveGameToSlot(Run, RunSlotForSeed(Run->TowerSeed), 0, Done);
}

void UEchoesSaveSubsystem::LoadProfile()
{
	if (UGameplayStatics::DoesSaveGameExist(ProfileSlot, 0))
	{
		FAsyncLoadGameFromSlotDelegate Done;
		Done.BindUObject(this, &UEchoesSaveSubsystem::HandleProfileLoaded);
		UGameplayStatics::AsyncLoadGameFromSlot(ProfileSlot, 0, Done);
	}
}

void UEchoesSaveSubsystem::LoadRun(int32 TowerSeed)
{
	const FString Slot = RunSlotForSeed(TowerSeed);
	if (UGameplayStatics::DoesSaveGameExist(Slot, 0))
	{
		FAsyncLoadGameFromSlotDelegate Done;
		Done.BindUObject(this, &UEchoesSaveSubsystem::HandleRunLoaded);
		UGameplayStatics::AsyncLoadGameFromSlot(Slot, 0, Done);
	}
}

bool UEchoesSaveSubsystem::DoesRunExist(int32 TowerSeed) const
{
	return UGameplayStatics::DoesSaveGameExist(RunSlotForSeed(TowerSeed), 0);
}

void UEchoesSaveSubsystem::DeleteRun(int32 TowerSeed)
{
	UGameplayStatics::DeleteGameInSlot(RunSlotForSeed(TowerSeed), 0);
	CachedRun = nullptr;
}

void UEchoesSaveSubsystem::HandleSaveCompleted(const FString& SlotName, int32 UserIndex, bool bSuccess)
{
	UE_LOG(LogTemp, Log, TEXT("[EchoesSave] Save to '%s' %s"), *SlotName, bSuccess ? TEXT("OK") : TEXT("FAILED"));
}

void UEchoesSaveSubsystem::HandleProfileLoaded(const FString& SlotName, int32 UserIndex, USaveGame* Loaded)
{
	if (UEchoesProfileSaveGame* P = Cast<UEchoesProfileSaveGame>(Loaded))
	{
		// TODO: if (P->SaveVersion < CurrentVersion) migrate before caching.
		CachedProfile = P;
	}
}

void UEchoesSaveSubsystem::HandleRunLoaded(const FString& SlotName, int32 UserIndex, USaveGame* Loaded)
{
	if (UEchoesRunSaveGame* R = Cast<UEchoesRunSaveGame>(Loaded))
	{
		CachedRun = R;
	}
}
