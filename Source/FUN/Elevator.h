#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Elevator.generated.h"

class ATargetPoint;
class AElevatorSwitch;

UCLASS()
class FUN_API AElevator : public AActor
{
	GENERATED_BODY()

	UFUNCTION()
	void GoToFloor(int32 FloorIndex);

	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* Door{nullptr};

	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* Root{nullptr};

	UPROPERTY(EditAnywhere)
	TArray<ATargetPoint*> Floors{};

	UPROPERTY(EditDefaultsOnly)FRuntimeFloatCurve AnimationCurve;

	UPROPERTY(EditDefaultsOnly)
	FVector PosFrom = {};

	UPROPERTY(EditDefaultsOnly)
	FVector PosTo = {};
	
	UPROPERTY(EditDefaultsOnly)
	float Speed;

public:	
	AElevator();
	virtual void Tick(float DeltaTime) override;

private:
	virtual void BeginPlay() override;

	float Counter{0.f};
	bool Move{false};
	float Duration;

	FVector OpenDoor{0.f, 1.f, 0.9f};
	FVector CloseDoor{1.2f, 1.f, 0.9f};
};
