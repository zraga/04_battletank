// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"// must be the last include

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

//forward declartions
class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	

	virtual void BeginPlay()override;
	virtual void Tick(float DeltaTime) override;
	

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

	UFUNCTION()
	void OnPossedTankDeath();

private:

	//Start the tank moving the barrel so that a shot would hit where the cross hair intersects the world
	void AimTowardsCrosshair();

	//Return an out parameter, true if hit land scape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;

	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.33333;

	UPROPERTY(EditAnyWhere)
		float LineTraceRange = 1000000;

	virtual void SetPawn(APawn* InPawn) override;
};
