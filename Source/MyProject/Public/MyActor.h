#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class MYPROJECT_API AMyActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AMyActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    void HandleInput();

    void Move();

    class AMyProjectCharacter* PlayerCharacter;

    int m_iMoveCount = { 0 };
    bool m_bMove = { false };
    float m_fAccTime = { 0.f };
};
