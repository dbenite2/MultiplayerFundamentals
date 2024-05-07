// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "FunSwitch.generated.h"

class UPointLightComponent;

UCLASS()
class FUN_API AFunSwitch : public AActor, public IInteractable
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* Pivot{nullptr};

	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* Root{nullptr};

	UPROPERTY(EditDefaultsOnly)
	FRotator PivotRotationOn{};

	UPROPERTY(EditDefaultsOnly)
	FRotator PivotRotationOff{};

	UPROPERTY(EditDefaultsOnly)
	UPointLightComponent* Light{nullptr};
	
public:
	AFunSwitch();

	UPROPERTY(BlueprintReadWrite)
	bool bIsOn{false};

	UFUNCTION(BlueprintCallable)
	void Toggle();

	UFUNCTION(NetMulticast, Reliable)
	void Multi_Toggle();

	virtual void Interact_Implementation() override;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
