// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"

#include "ElevatorSwitch.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

AElevator::AElevator()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->SetupAttachment(RootComponent);
	SetRootComponent(Root);

	Door = CreateDefaultSubobject<USceneComponent>(TEXT("Door"));
	Door->SetupAttachment(Root);
}

void AElevator::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AElevatorSwitch::StaticClass(), FoundActors);

	for (auto* Actor: FoundActors) {
		if (AElevatorSwitch* Switch = Cast<AElevatorSwitch>(Actor)) {
			if (!Switch->OnElevatorSwitchPressed.IsAlreadyBound(this, &AElevator::AElevator::GoToFloor)) {
				Switch->OnElevatorSwitchPressed.AddDynamic(this, &AElevator::GoToFloor);
			}
		}
	}
}

void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Move) {
		Door->SetRelativeScale3D(CloseDoor);
		Counter += DeltaTime;
		auto Value = Counter/Duration;

		if (Value > 1.f) {
			Move = false;
			Value = 1.f;
			Door->SetRelativeScale3D(OpenDoor);
		}

		const auto Eval = AnimationCurve.ExternalCurve ? AnimationCurve.ExternalCurve->GetFloatValue(Value) :
		AnimationCurve.EditorCurveData.Eval(Value);

		const auto Pos = FMath::Lerp(PosFrom, PosTo, Eval);
		SetActorLocation(Pos);
	}
}

void AElevator::GoToFloor(int32 FloorIndex) {
	UE_LOG(LogTemp, Log, TEXT("Going to Floor: %d"), FloorIndex);

	if (Move) return;
	if (!Floors.IsValidIndex(FloorIndex)) return;
	
	auto* Target = Floors[FloorIndex];
	PosTo = Target->GetActorLocation();
	PosFrom = GetActorLocation();
	Counter = 0.f;
	Duration = (PosTo - PosFrom).Length() / Speed;
	Move = true;
}

