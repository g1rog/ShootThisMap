
#include "Player/STMBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/STMCharacterMovementComponent.h"
#include "Components/STMHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"

ASTMBaseCharacter::ASTMBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USTMCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    
    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<USTMHealthComponent>("HealthComponent");
    
    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());
}

void ASTMBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

    check(SpringArmComponent);
    check(CameraComponent);
    check(HealthComponent);
    check(HealthTextComponent);
    check(GetCharacterMovement());

    OnHealthChanged(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &ASTMBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ASTMBaseCharacter::OnHealthChanged);
}

void ASTMBaseCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASTMBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);
    
    PlayerInputComponent->BindAxis("MoveForward", this, &ASTMBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASTMBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ASTMBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ASTMBaseCharacter::AddControllerYawInput);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTMBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTMBaseCharacter::OnStartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTMBaseCharacter::OnStopRunning);
}

FORCEINLINE void ASTMBaseCharacter::MoveForward(const float Amount)
{
    if (Amount == 0.0f) return;
    IsMovingForward = Amount > 0.0f;
    AddMovementInput(GetActorForwardVector(), Amount);
}

FORCEINLINE void ASTMBaseCharacter::MoveRight(const float Amount)
{
    AddMovementInput(GetActorRightVector(), Amount);
}

FORCEINLINE void ASTMBaseCharacter::OnStartRunning()
{
    WantsToRun = true;
}

FORCEINLINE void ASTMBaseCharacter::OnStopRunning()
{
    WantsToRun = false;
}

bool ASTMBaseCharacter::IsRunning() const
{
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero() ? true : false;
}

float ASTMBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero()) return 0.0f;
    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const auto Degrees =  FMath::RadiansToDegrees(AngleBetween);
    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ASTMBaseCharacter::OnDeath()
{
    PlayAnimMontage(DeathAnimMontage);
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(5.0f);
    if (Controller) Controller->ChangeState(NAME_Spectating);
}

void ASTMBaseCharacter::OnHealthChanged(const float Health) const
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}
