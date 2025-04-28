// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSBasePawn.h"


// Sets default values
ARTSBasePawn::ARTSBasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARTSBasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARTSBasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARTSBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

