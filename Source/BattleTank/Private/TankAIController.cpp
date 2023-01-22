// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAIController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h" //so we can impliment on death
#include "Engine/World.h"


void ATankAIController::BeginPlay() {

	Super::BeginPlay();

}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		
		auto PossedTank = Cast<ATank>(InPawn);
		if (!ensure(PossedTank)) {
			return;
		}

		// Subscribe our local method to the tank's death event
		PossedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);

	}
}

void ATankAIController::OnPossedTankDeath()
{
	if (!GetPawn()) {
		return;
	}

	GetPawn()->DetachFromControllerPendingDestroy();
}


void ATankAIController::Tick(float DeltaTime) {
	
	Super::Tick(DeltaTime);
	
	auto PlayerTank= GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();


	if (!ensure(PlayerTank && ControlledTank)) {
		return;
	}

		//Move Towards player
		MoveToActor(PlayerTank, AcceptanceRadius); //check radius in cm
		
	    //aim towards player
		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
	   

		if (AimingComponent->GetFiringState() == EFiringState::Locked) {
			AimingComponent->fire();// TODO limit firing rate
		}
}


