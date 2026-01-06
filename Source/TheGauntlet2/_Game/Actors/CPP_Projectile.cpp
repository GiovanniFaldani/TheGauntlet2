// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Actors/CPP_Projectile.h"
#include "../Subsystems/CPP_ObjectPoolSubsystem.h"
#include "../Interfaces/Damageable.h"

// Sets default values
ACPP_Projectile::ACPP_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = Collision;

	// collision delegate binding
	Collision->OnComponentHit.AddDynamic(this, &ACPP_Projectile::OnHit);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bRotationFollowsVelocity = true;

	// start inactive
	ProjectileMovement->StopMovementImmediately();
	ProjectileMovement->ProjectileGravityScale = 0.0f;

}

// Called when the game starts or when spawned
void ACPP_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
	// start hidden
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void ACPP_Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// get actor hit, if IDamamgeable, apply damage
	if (IsValid(OtherActor) && OtherActor->GetClass()->ImplementsInterface(UDamageable::StaticClass()))
	{
		IDamageable::Execute_ReceiveDamage(OtherActor, DamageDealt);
	}

	// deactivate and return to object pool
	ReturnToPool();
}

void ACPP_Projectile::ReturnToPool()
{
	if (UCPP_ObjectPoolSubsystem* Subsystem = GetWorld()->GetSubsystem<UCPP_ObjectPoolSubsystem>())
	{
		// build interface ref for this instance
		TScriptInterface<IObjectPoolInterface> InterfaceRef;
		InterfaceRef.SetObject(this);
		InterfaceRef.SetInterface(Cast<IObjectPoolInterface>(this));

		Subsystem->ReturnObjectToPool(this->GetClass(), InterfaceRef);
	}
}

// Called every frame
void ACPP_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_Projectile::Activate_Implementation(FObjectPoolActivationData ObjectPoolData)
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);

	// Start movement
	ProjectileMovement->SetUpdatedComponent(RootComponent);
	ProjectileMovement->ResetInterpolation();
	ProjectileMovement->InitialSpeed = ProjectileSpeed;
	ProjectileMovement->MaxSpeed = ProjectileSpeed;
	ProjectileMovement->Velocity = GetActorForwardVector() * ProjectileMovement->InitialSpeed;
	ProjectileMovement->Activate();

	GetWorld()->GetTimerManager().SetTimer(LifeSpanTimerHandle, this, &ACPP_Projectile::ReturnToPool, LifeSpanSeconds, false);
}

void ACPP_Projectile::Deactivate_Implementation()
{
	// clear timer to avoid memory leaks
	GetWorld()->GetTimerManager().ClearTimer(LifeSpanTimerHandle);

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	ProjectileMovement->StopMovementImmediately();
}

