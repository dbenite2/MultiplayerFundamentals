// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FunSwitch.generated.h"

UCLASS()
class FUN_API AFunSwitch : public AActor
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
	
public:
	AFunSwitch();

	UPROPERTY(BlueprintReadWrite)
	bool bIsOn{false};

	UFUNCTION(BlueprintCallable)
	void Toggle();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
