// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ControllerPawn.generated.h"

//This is a forward declaration section
class UInputAction;
class UCapsuleComponent;
class UCameraComponent;
class USpringArmComponent;
struct FInputActionValue;
class UFloatingPawnMovement;

UCLASS()
class RTSUTILLS_API AControllerPawn : public APawn
{
	GENERATED_BODY()

	private:
	//Capsule component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true")) // meta = (AllowPrivateAccess = "true")) this makes Blueprints able to see this
	UCapsuleComponent* CapsuleComponent;

	//Camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	//Spring arm component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	//Adding input Action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	//Add a floating pawn movement component
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UFloatingPawnMovement* FloatingPawnMovement;
	
public:
	// Sets default values for this pawn's properties
	AControllerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Called for move input
	void Move(const FInputActionValue& Value);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
