// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "EngineUtils.h"



void AInfiniteTerrainGameMode::PopulateActors()
{
  auto ActorIterator = TActorIterator<AActor>(GetWorld());
  while (ActorIterator)
  {
	  UE_LOG(LogTemp, Warning, TEXT("Actor : %s"), *ActorIterator->GetName())
	  ++ActorIterator;
  }
}
