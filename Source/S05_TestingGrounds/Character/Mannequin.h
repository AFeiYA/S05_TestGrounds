// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mannequin.generated.h"

UCLASS()
class S05_TESTINGGROUNDS_API AMannequin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMannequin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//virtual void UnPossessed() override;
	virtual void UnPossessed() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	class TSubclassOf<class ATile>  TileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	class TSubclassOf<class AGun>  GunBlueprint;

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire();

private:
	//create a first camera component.
	UPROPERTY(VisibleAnywhere,  Category = Camera)
	class UCameraComponent* FirstPersonCameraComponent;
	//create a SK_Mesh for first person player.
	UPROPERTY(VisibleAnywhere,  Category = Mesh)
	class USkeletalMeshComponent*  FirstPersonMesh;

	AGun* Gun;

};
