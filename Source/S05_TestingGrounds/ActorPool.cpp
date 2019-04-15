// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorPool.h"
#include "GameFramework/Actor.h"
//#include "Runtime/NavigationSystem/Public/NavMesh/NavMeshBoundsVolume.h"
//#include "NavMeshBoundsVolume.h"

// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AActor* UActorPool::CheckOut()
{
	if (Pool.Num() == 0)
	{
		return nullptr;
	}
	return Pool.Pop();
}
void UActorPool::Return(AActor* ActorToReturn)
{
	if (ActorToReturn!=nullptr) 
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Return:%s"), *GetName(),*ActorToReturn->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Return called"), *GetName());
		return;
	}
}
void UActorPool::Add(AActor* ActorToAdd)
{
	if (ActorToAdd==nullptr)
	{
		return;
	}
	Pool.Push(ActorToAdd);
}