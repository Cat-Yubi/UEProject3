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

    // Get reference to player character
    PlayerCharacter = Cast<AMyProjectCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    // Bind input action
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
}

// Function to handle input
void AMyActor::HandleInput()
{
    if (PlayerCharacter)
    {
        // Generate a random location around the player within a distance of 2 units
        FVector RandomOffset = FVector(FMath::FRandRange(-20.0f, 20.0f), FMath::FRandRange(-20.0f, 20.0f), 0);
        FVector NewLocation = PlayerCharacter->GetActorLocation() + RandomOffset;

        // Teleport player to the new location
        PlayerCharacter->SetActorLocation(NewLocation);
    }
}
