#pragma once

// Core, Engine
#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"

// FunctionalTesting
#include "FunctionalTest.h"

// AIModule
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"

#include "TestPawnMovement.generated.h"


UCLASS()
class REALMPAWN_API ATestPawnMovement : public AFunctionalTest
{
    GENERATED_BODY()

// Configuration
public:
    bool IsConfigured();

    virtual void OnConstruction(const FTransform& Transform) override;

// Functional Test
protected:
    virtual void PrepareTest() override;

    virtual void StartTest() override;

// Validity
public:
    bool IsValid();

private:
    void ValidateMovement();

    UPROPERTY(EditAnywhere, Category = Configuration)
    float DistancePercision = 100.0f;

    UPROPERTY(EditAnywhere, Category = Configuration)
    bool ExpectedResult = true;

// Pawn
public:
    APawn* GetPawn(){ return Pawn.IsValid() ? Pawn.Get() : nullptr; }

    bool IsPawnValid(){ return nullptr != GetPawn(); }

    bool IsPawnMoveable(){ return nullptr != GetPawnAIController(); }

    AAIController* GetPawnAIController();

private:
    UPROPERTY(EditInstanceOnly, Category = Configuration)
	TSoftObjectPtr<APawn> Pawn;

    UFUNCTION()
    void PawnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type MovementResult){ ValidateMovement(); }

// Target
public:
    bool IsTargetPointValid(){ return nullptr != TargetPoint; }

private:
    UPROPERTY(EditInstanceOnly, Category = Configuration)
    ATargetPoint* TargetPoint;
};
