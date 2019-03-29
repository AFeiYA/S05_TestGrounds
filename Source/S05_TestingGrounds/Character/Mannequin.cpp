// Fill out your copyright notice in the Description page of Project Settings.

#include "Mannequin.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "../Weapons/Gun.h"


// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Setup First Person Camera Component in the hierarchy.
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	//Setup First Person Mesh.
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonArms"));
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->SetupAttachment(FirstPersonCameraComponent);
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;
	FirstPersonMesh->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	FirstPersonMesh->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
	if (GunBlueprint == nullptr)
	{
		return;
	}
	Gun = GetWorld()-> SpawnActor<AGun>(GunBlueprint);
	if (IsPlayerControlled())
	{
		Gun->AttachToComponent(FirstPersonMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
	else {
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
	
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

