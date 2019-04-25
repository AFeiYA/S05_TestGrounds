// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "Engine.h"
#include "EngineUtils.h"
#include "ActorPool.h"
#include "NavMeshBoundsVolume.h"




AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	Actors = CreateDefaultSubobject<UActorPool>(FName("Actors Pool"));
}

void AInfiniteTerrainGameMode::PopulateActors()
{
  auto ActorIterator = TActorIterator<AActor>(GetWorld());
  while (ActorIterator)
  {
	  FString Type = *ActorIterator->GetActorLabel();
	  if (Type.StartsWith("NavMeshBounds"))
	  {
		  /*AddToNavMeshVolume(*ActorIterator);*/
		  AddToPool(*ActorIterator);
		  UE_LOG(LogTemp, Warning, TEXT("ActorName:%s, Type:%s "), *ActorIterator->GetName(), *ActorIterator->GetActorLabel());
	  }	 
	  ++ActorIterator;

  }
}

//void AInfiniteTerrainGameMode::PopulateNavMeshBoundsVolume()
//{
//	auto ActorIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
//	while (ActorIterator)
//	{
//
//		AddToPool(*ActorIterator);
//		++ActorIterator;
//	}
//}



void AInfiniteTerrainGameMode::AddToPool(AActor * ActorToAdd)
{
	Actors->Add(ActorToAdd);
	NavMeshBoundsVolume.Push(ActorToAdd);
	if (NavMeshBoundsVolume.Num() == 0) 
	{
		UE_LOG(LogTemp, Warning, TEXT("nav mesh num:%s "), NavMeshBoundsVolume.Num());
	}
	if (Actors == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actors:%s "), *Actors->GetName());
	}
}

//void AInfiniteTerrainGameMode::AddToNavMeshVolume(AActor * VolumeToAdd)
//{
//	UE_LOG(LogTemp, Warning, TEXT("ActorName:%s, Type:%s "), *VolumeToAdd->GetName(), *VolumeToAdd->GetActorLabel());
//}
