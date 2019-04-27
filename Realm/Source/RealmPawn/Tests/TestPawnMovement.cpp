#include "TestPawnMovement.h"
PRAGMA_DISABLE_OPTIMIZATION

// Configuration
bool ATestPawnMovement::IsConfigured()
{
    return IsPawnValid() && IsTargetPointValid();
}

void ATestPawnMovement::OnConstruction(const FTransform& Transform)
{
// Case - Variables aren't set on the instance, so it can't be tested
// Cause - This test will not appear in the session list
// Example - Tests level to not show in sessions list
#if WITH_EDITOR
	bIsEnabled = IsConfigured();
#endif

    Super::OnConstruction(Transform);
}

// Functional Test
void ATestPawnMovement::PrepareTest()
{
    if(AssertTrue(IsValid(), TEXT("Configuration"), this))
    {
        GetPawnAIController()->ReceiveMoveCompleted.AddDynamic(this, &ATestPawnMovement::PawnMoveCompleted);
    }
    Super::PrepareTest();
}

void ATestPawnMovement::StartTest()
{
    Super::StartTest();

    AAIController* AIController = GetPawnAIController();
    // XXX: This should be caught by the prepare, necessary?
    if(nullptr == AIController){ return; }

    FPathFollowingRequestResult PathRequest = AIController->MoveTo(FAIMoveRequest(TargetPoint));
}

// Validity
bool ATestPawnMovement::IsValid()
{
    return IsPawnValid() && IsPawnMoveable() && IsTargetPointValid();
}

void ATestPawnMovement::ValidateMovement()
{
    float Distance = Pawn->GetDistanceTo(TargetPoint);
    AssertEqual_Bool(Distance < DistancePercision, ExpectedResult, FString::Printf(TEXT("Pawn is distance %.2f from target"), Distance));

    FinishTest(EFunctionalTestResult::Succeeded, TEXT("Success"));
}

// Pawn
AAIController* ATestPawnMovement::GetPawnAIController()
{
    if(nullptr == GetPawn()){ return nullptr; }

    return Pawn->GetController<AAIController>();
}

PRAGMA_ENABLE_OPTIMIZATION
