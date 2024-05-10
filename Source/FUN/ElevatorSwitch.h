// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "ElevatorSwitch.generated.h"

class AElevator;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnElevatorSwitchPressed, int, floor);

UCLASS()
class FUN_API AElevatorSwitch : public AActor, public IInteractable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	USceneComponent *Pivot = nullptr;

	UPROPERTY(EditAnywhere)
	USceneComponent *Root= nullptr;

	UPROPERTY(EditDefaultsOnly)
	FVector PivotPositionOn = {};

	UPROPERTY(EditDefaultsOnly)
	FVector PivotPositionOff = {};
	
	UPROPERTY(ReplicatedUsing=OnRep_IsOn)
	bool IsOn = false;

	UPROPERTY(EditDefaultsOnly)
	float TimePressed = 1.f;

	UPROPERTY(EditDefaultsOnly)
	AElevator* Elevator{nullptr};

	float Counter = 0.f;

	UPROPERTY(EditDefaultsOnly)FRuntimeFloatCurve AnimationCurve;

	UPROPERTY(EditInstanceOnly)
	int TargetFloor{0};
	
public:	
	// Sets default values for this actor's properties
	AElevatorSwitch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation() override;

	void Press();
	void Reset();

	UFUNCTION()
	void OnRep_IsOn(bool OldValue);

	UPROPERTY()
	FOnElevatorSwitchPressed OnElevatorSwitchPressed;
};
