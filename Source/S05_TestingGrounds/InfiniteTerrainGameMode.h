// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "S05_TestingGroundsGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"



UCLASS()
class S05_TESTINGGROUNDS_API AInfiniteTerrainGameMode : public AS05_TestingGroundsGameMode
{
	GENERATED_BODY()

public:
	AInfiniteTerrainGameMode();

	UFUNCTION(BlueprintCallable, Category = "Actors")
	void PopulateActors();

	//UFUNCTION(BlueprintCallable, Category = "Nav Mesh Bounds Volume")
	//void PopulateNavMeshBoundsVolume();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pool")
	class UActorPool* Actors;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NavMeshPool")
	TArray<AActor*>  NavMeshBoundsVolume;

private:
	void AddToPool(AActor* ActorToAdd);
	//void AddToNavMeshVolume(AActor* VolumeToAdd);
};
