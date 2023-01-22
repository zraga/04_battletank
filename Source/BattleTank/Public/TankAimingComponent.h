// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for Aiming State

UENUM()
enum class EFiringState: uint8 {
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

// Forward declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

//holds barrel's properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void fire();

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetRoundsLeft() const;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Reloading;

private:

	// Sets default values for this component's properties
	UTankAimingComponent();

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	double LastFireTime = 0;

	virtual void BeginPlay()override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	FVector AimDirection;
	bool IsBarrelMoving();

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 RoundsLeft = 3;

};
