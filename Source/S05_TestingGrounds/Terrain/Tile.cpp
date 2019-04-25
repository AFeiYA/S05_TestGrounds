// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "MotionControllerComponent.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"
#include "NavigationSystem.h"




// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
TArray<TSubclassOf<AActor>> ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, float Radius, int MinSpawn, int MaxSpawn, float MinScale, float MaxScale)
{
    return RandomlyPlaceActors(ToSpawn, Radius, MinSpawn, MaxSpawn, MinScale, MaxScale);
}

TArray<TSubclassOf<APawn>> ATile::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, float Radius, int MinSpawn, int MaxSpawn)
{
	return RandomlyPlaceActors(ToSpawn, Radius,MinSpawn,MaxSpawn, 1, 1);
}


template<class T>
inline TArray<TSubclassOf<T>> ATile::RandomlyPlaceActors(TSubclassOf<T> ToSpawn, float Radius, int MinSpawn, int MaxSpawn, float MinScale, float MaxScale)
{
	int NumberToSpawn = FMath::FRandRange(MinSpawn, MaxSpawn);
	TArray<TSubclassOf<T>> SpawnedObjects;
	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FVector SpawnPoint;
		if (FindEmptyLocation(SpawnPoint, Radius)) {
			FSpawnInfo SpawnInfo;
			SpawnInfo.Location = SpawnPoint;
			SpawnInfo.Rotation = FMath::RandRange(-180.f, 180.f);
			SpawnInfo.Scale = FMath::RandRange(MinScale, MaxScale);
			PlaceActor(ToSpawn, SpawnInfo);
			if(ToSpawn != nullptr)
			{
				SpawnedObjects.Push(ToSpawn);
			}
			
			//UE_LOG(LogTemp, Warning, TEXT("Name:%s"), *ToSpawn->GetName());
		}
		//UE_LOG(LogTemp, Warning, TEXT("Random point position: %s"), *SpownPoint.ToCompactString());
	}
	return SpawnedObjects;

	
}



void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnInfo SpawnInfo)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	if (Spawned) 
	{
		Spawned->SetActorRelativeLocation(SpawnInfo.Location);
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		Spawned->SetActorRotation(FRotator(0, SpawnInfo.Rotation, 0));
		Spawned->SetActorScale3D(FVector(SpawnInfo.Scale));
	}

}

void ATile::PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnInfo SpawnInfo)
{
	APawn* Spawned = GetWorld()->SpawnActor<APawn>(ToSpawn);
	if (Spawned) 
	{
		Spawned->SetActorRelativeLocation(SpawnInfo.Location);
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		Spawned->SetActorRotation(FRotator(0, SpawnInfo.Rotation, 0));
		Spawned->SpawnDefaultController();
		Spawned->Tags.Add(FName("Enemy"));
	}
}




bool ATile::FindEmptyLocation(FVector& OutLocation, float Radius)
{
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);
	for (size_t i = 0; i < 100; i++)
	{
		FVector CandidatePoint = FMath::RandPointInBox(Bounds);
		if (IsAvailableToSpawn(CandidatePoint,Radius))
		{
			OutLocation = CandidatePoint;
			return true;
		}

	}
	return false;
}


// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();


}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Actors!= nullptr && Pool != nullptr) {
		Pool->Return(Actors);
		//UE_LOG(LogTemp, Warning, TEXT("End  play  Pool : %s"), *Actors->GetName());
	}
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ATile::IsAvailableToSpawn(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector WorldLocation = ActorToWorld().TransformPosition(Location);
	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult, WorldLocation, WorldLocation+FVector(0,0,1),FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));
	FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
	//DrawDebugCapsule(GetWorld(), WorldLocation, 0 , Radius, FQuat::Identity, ResultColor, true, 100);
	//DrawDebugSphere(GetWorld(), WorldLocation, Radius, 20, ResultColor, true, 100.f);
	return !HasHit;
}
void ATile::SetPool(UActorPool* InPool)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s  Pool : %s"), *(this->GetName()), *(InPool->GetName()));
	Pool = InPool;
	Actors = Pool->CheckOut();
	if (Actors == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] Not enough actors in pool."), *GetName());
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("%s check out : %s"), *(this->GetName()), *Actors->GetName());
	Actors->SetActorLocation(GetActorLocation() - FVector(2000,0,0));
	UNavigationSystemV1::GetNavigationSystem(GetWorld())->Build();
}
