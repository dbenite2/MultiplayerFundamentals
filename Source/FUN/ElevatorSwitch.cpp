#include "ElevatorSwitch.h"

#include "Net/UnrealNetwork.h"


AElevatorSwitch::AElevatorSwitch()
{

	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Root"));
	Root->SetupAttachment(RootComponent);
	SetRootComponent(Root);
	
	Pivot = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Pivot"));
	Pivot->SetupAttachment(Root);

}


void AElevatorSwitch::BeginPlay()
{
	Super::BeginPlay();
	
}

void AElevatorSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsOn) {
		Counter += DeltaTime;

		const auto Value = Counter/TimePressed;

		const auto Eval = AnimationCurve.ExternalCurve
			? AnimationCurve.ExternalCurve->GetFloatValue(Value)
			: AnimationCurve.EditorCurveData.Eval(Value);

		const auto Pos = FMath::Lerp(PivotPositionOff,PivotPositionOn, Eval);

		Pivot ->SetRelativeLocation(Pos);
	}

}

void AElevatorSwitch::Interact_Implementation() {
	Press();
}

void AElevatorSwitch::Press() {
	if(IsOn) return;
	auto* World = GetWorld();

	if(!World) return;
	
	IsOn = true;

	OnElevatorSwitchPressed.Broadcast(TargetFloor);

	FTimerHandle Handle = {};
	World->GetTimerManager().SetTimer(Handle,this, &AElevatorSwitch::Reset,TimePressed,false);
}

void AElevatorSwitch::Reset() {
	IsOn = false;
	Counter = 0.f;
}

void AElevatorSwitch::OnRep_IsOn(bool OldValue) {
	if(!IsOn) {
		Reset();
	}
	// PrimaryActorTick.bCanEverTick = IsOn;
	UE_LOG(LogTemp, Log, TEXT("IsOn value: {%hs} Old IsOn value: {%hs}"), IsOn ? "true" : "false", OldValue ? "true" : "false");
}

void AElevatorSwitch::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AElevatorSwitch, IsOn);
}
