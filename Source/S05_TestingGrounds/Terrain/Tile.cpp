// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "MotionControllerComponent.h"
#include "DrawDebugHelpers.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, float Radius, int MinSpawn, int MaxSpawn, float MinScale, float MaxScale)
{

	int NumberToSpawn = FMath::FRandRange(MinSpawn, MaxSpawn);
	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FVector SpawnPoint;
		if (FindEmptyLocation(SpawnPoint, Radius)) {
			PlaceActor(ToSpawn, SpawnPoint, FMath::RandRange(-180.f, 180.f), FMath::RandRange(MinScale, MaxScale));
		}
		//UE_LOG(LogTemp, Warning, TEXT("Random point position: %s"), *SpownPoint.ToCompactString());
	}

}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPosition, float Rotation , float Scale)
{

	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPosition);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0, Rotation, 0));
	Spawned->SetActorScale3D(FVector(Scale));
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

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
bool ATile::IsAvailableToSpawn(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector WorldLocation = ActorToWorld().TransformPosition(Location);
	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult, WorldLocation, WorldLocation,FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));
	//FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
	//DrawDebugCapsule(GetWorld(), WorldLocation, 20 , Radius, FQuat::Identity, ResultColor, true, 100);
	return !HasHit;
}

