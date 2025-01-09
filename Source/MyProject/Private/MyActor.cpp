#include "MyActor.h"
#include "./MyProject/MyProjectCharacter.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyActor::AMyActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
    Super::BeginPlay();

    PlayerCharacter = Cast<AMyProjectCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        InputComponent = NewObject<UInputComponent>(this);
        InputComponent->RegisterComponent();
        EnableInput(PlayerController);

        InputComponent->BindAction("TeleportPlayer", IE_Pressed, this, &AMyActor::HandleInput);
    }
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // 함수 호출 확인을 위한 디버그 메시지 

    if (true == m_bMove)
        m_fAccTime += DeltaTime;

    if (m_fAccTime > 0.5f)
    {
        m_fAccTime = 0.f;
        m_iMoveCount++;

        if (FMath::FRand() < 0.5f)
            Move();
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed Call Move"));
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Failed Call Move\n")));
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Event Count : %d/10"), m_iMoveCount + 1));
        }

        if (m_iMoveCount >= 9)
        {
            m_bMove = false;
            m_iMoveCount = 0;
        }
    }
}

void AMyActor::HandleInput()
{
    if (nullptr != PlayerCharacter)
    {
        UE_LOG(LogTemp, Warning, TEXT("HandleInput call"));
        m_fAccTime = 0.f;
        m_bMove = true;
        m_iMoveCount = 0;

        Move();
    }
}

void AMyActor::Move()
{
    FVector RandomOffset = FVector(FMath::FRandRange(-20.0f, 20.0f), FMath::FRandRange(-20.0f, 20.0f), 0);
    FVector PreLocation = PlayerCharacter->GetActorLocation();
    FVector NewLocation = PreLocation + RandomOffset;

    float totDist = RandomOffset.Size(); 

    UE_LOG(LogTemp, Warning, TEXT("Move call Move Distance : %f"), totDist); 
    if (GEngine) 
    { 
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Move Distance : %f\n"), totDist));
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("After x : %f , y : %f"), NewLocation.X, NewLocation.Y));
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Before x : %f , y : %f"), PreLocation.X, PreLocation.Y));
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Event Count : %d/10"), m_iMoveCount + 1));
    }

    PlayerCharacter->SetActorLocation(NewLocation);
}
