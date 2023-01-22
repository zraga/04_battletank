// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank is used to set maximum driving force and to move the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable,Category = "Input")
	void SetThrottle(float Throttle);
	
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 40000; //Assuming 40 tonne tank, and 1g acceleration

private:

	UTankTrack();
	//virtual void BeginPlay() override;
	//void ApplySidewaysForce();

	//UFUNCTION()
    //void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	void DriveTrack(float CurrentThrottle);
	//float CurrentThrottle = 0;

	TArray<class ASprungWheel*>GetWheels()const;
};
