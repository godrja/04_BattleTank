// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankProjectileMovementComponent.h"
#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankProjectileMovementComponent = CreateDefaultSubobject<UTankProjectileMovementComponent>(FName("Projectile Movement Component"));
	TankProjectileMovementComponent->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate ScriptDelegate;
	ScriptDelegate.BindUFunction(this, FName("OnHit"));
	CollisionMesh->OnComponentHit.Add(ScriptDelegate);
}

void AProjectile::Launch(float Speed)
{
	TankProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	TankProjectileMovementComponent->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();
	
	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	FTimerHandle TimerHandle; // throwaway
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectile::OnTimer, DestroyDelay);
}

void AProjectile::OnTimer()
{
	ensure(Destroy());
}
