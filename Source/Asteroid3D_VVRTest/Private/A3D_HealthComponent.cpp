#include "A3D_HealthComponent.h"

#include "A3D_GameModeBase.h"
#include "ChaosInterfaceWrapperCore.h"
#include "GameFramework/GameModeBase.h"
#include "Net/UnrealNetwork.h"

class AA3D_GameModeBase;
// Sets default values for this component's properties
UA3D_HealthComponent::UA3D_HealthComponent() {
    Health = MaxHealth;
    bIsDead = false;
}

// Called when the game starts
void UA3D_HealthComponent::BeginPlay() {
    Super::BeginPlay();
    AActor* MyOwner = GetOwner();
    if( MyOwner ) {
        MyOwner->OnTakeAnyDamage.AddDynamic( this, &UA3D_HealthComponent::HandleTakeAnyDamage );
    }
}

void UA3D_HealthComponent::HandleTakeAnyDamage( AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                             AController* InstigatedBy, AActor* DamageCauser ) {
    

    if( Damage <= 0.0f || bIsDead ||  GetOwner()->GetWorldTimerManager().IsTimerActive(TimerHandle_Immunity)) {
        return;
    }

    //Update Health clamped
    Health = FMath::Clamp( Health - Damage, 0.0f, MaxHealth );

    UE_LOG( LogTemp, Log, TEXT("Health Changed: %s"), *FString::SanitizeFloat( Health ) );

    printf( "Health Changed: %ls", *FString::SanitizeFloat( Health ) );

    bIsDead = Health <= 0.0f;

    OnHealthChanged.Broadcast( this, Health, Damage, DamageType, InstigatedBy, DamageCauser );

    if( bIsDead ) {
        
         AA3D_GameModeBase* GM = Cast<AA3D_GameModeBase>( GetWorld()->GetAuthGameMode() );
         if( GM ) {
             //TODO handle death
             // GM->OnActorKilled.Broadcast( GetOwner(), DamageCauser, InstigatedBy );
         }
    }

}


float UA3D_HealthComponent::GetHealth() const {
    return Health;
}


void UA3D_HealthComponent::Heal( float HealAmount ) {
    if( HealAmount <= 0.0f || Health <= 0.0f ) {
        return;
    }
    Health = FMath::Clamp( Health + HealAmount, 0.0f, MaxHealth );

    UE_LOG( LogTemp, Log, TEXT( "Healed: %s (+ %s)" ), *FString::SanitizeFloat( Health ),
            *FString::SanitizeFloat( HealAmount ) );

    OnHealthChanged.Broadcast( this, Health, -HealAmount, nullptr, nullptr, nullptr );


}



void UA3D_HealthComponent::SetMaxHealth(float max) {
    MaxHealth = max;
    Health = MaxHealth;
}

void UA3D_HealthComponent::SetImmunity() {
    GetOwner()->GetWorldTimerManager().SetTimer(TimerHandle_Immunity, ImmunityDelay, false);
}
