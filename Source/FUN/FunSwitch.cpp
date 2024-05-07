// Fill out your copyright notice in the Description page of Project Settings.


#include "FunSwitch.h"

#include "Interactable.h"
#include "Components/PointLightComponent.h"

AFunSwitch::AFunSwitch()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->SetupAttachment(RootComponent);
	SetRootComponent(Root);
	
	Pivot = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));
	Pivot->SetupAttachment(Root);

	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	Light->SetupAttachment(Root);

}

void AFunSwitch::Toggle() {
	Multi_Toggle();
}

void AFunSwitch::Multi_Toggle_Implementation() {
	bIsOn = !bIsOn;
	
	Pivot->SetRelativeRotation(bIsOn ? PivotRotationOn : PivotRotationOff);
	
	Light->SetIntensity(bIsOn ? 5000.f : 0.f);
	Light->SetLightColor(bIsOn ? FLinearColor::White : FLinearColor::Black);
}

void AFunSwitch::Interact_Implementation() {
	IInteractable::Interact_Implementation();
	Toggle();
}

void AFunSwitch::BeginPlay()
{
	Super::BeginPlay();
	Pivot->SetRelativeRotation(PivotRotationOff);
	Light->SetIntensity(0.f);
	Light->SetLightColor(FLinearColor::Black);
	
}

void AFunSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
