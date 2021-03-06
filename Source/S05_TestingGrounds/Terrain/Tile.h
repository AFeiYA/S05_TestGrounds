// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NavMeshBoundsVolume.h"
#include "Tile.generated.h"

USTRUCT()
struct FSpawnInfo
{
	GENERATED_USTRUCT_BODY()

	FVector Location;
	float Rotation;
	float Scale;
};


class UActorPool;

UCLASS()
class S05_TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	TArray<TSubclassOf<AActor>>  PlaceActors(TSubclassOf<AActor> ToSpawn, float Radius = 500, int MinSpawn = 1, int MaxSpawn = 1, float MinScale = 1, float MaxScale = 1);
	
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	TArray<TSubclassOf<APawn>>  PlaceAIPawns(TSubclassOf<APawn> ToSpawn, float Radius, int MinSpawn, int MaxSpawn);


protected:


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool* Pool);


private:

	bool FindEmptyLocation(FVector& OutLocation, float Radius );
	bool IsAvailableToSpawn(FVector Location, float Radius);
	
	template<class T>
	TArray<TSubclassOf<T>> RandomlyPlaceActors(TSubclassOf<T> ToSpawn, float Radius = 500, int MinSpawn = 1, int MaxSpawn = 1, float MinScale = 1, float MaxScale = 1);
	void PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnInfo SpawnInfo);
	void PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnInfo SpawnInfo);

	UActorPool* Pool;

	AActor* Actors;

	ANavMeshBoundsVolume* NavMeshBoundsVolumeInScene;

};

