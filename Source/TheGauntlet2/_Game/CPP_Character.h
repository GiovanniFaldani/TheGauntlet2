// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Interfaces/Interactable.h"
#include "Interfaces/Damageable.h"
#include "Components/CPP_InteractionComponent.h"
#include "CPP_Character.generated.h"

// Forward declarations for movement
class UInputMappingContext;
class UInputAction;
class UInputComponent;

// Delegate declarations
DECLARE_MULTICAST_DELEGATE(OnGameOver);
DECLARE_MULTICAST_DELEGATE(OnFallOutOFWorld);
DECLARE_MULTICAST_DELEGATE(OnLevelComplete);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, MaxHealth);

UCLASS()
class THEGAUNTLET2_API ACPP_Character : public ACharacter, public IDamageable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_Character();

	// Delegates
	OnGameOver onGameOver;
	OnFallOutOFWorld onFallOutOfWorld;
	OnLevelComplete onLevelComplete;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged onHealthChanged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Interaction)
	float InteractCooldown;

protected:
	// Damage and HP
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Player)
	float MaxHP;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Player)
	float HP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Player)
	float DamageDealt;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	// Move Input Actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> MoveAction;

	// Camera Input Actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> CameraAction;

	// Jump Input Actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> JumpAction;

	// Interact Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> InteractAction;

	// Camera
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<USpringArmComponent> Arm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	float CameraDistance;

	// Inventory
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
	bool bHasArtifact;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
	USceneComponent* ArtifactSocket;

	// Interaction
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Interaction)
	TObjectPtr<UCPP_InteractionComponent> InteractionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Interaction)
	bool CanInteract;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Interaction)
	float InteractTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Handles 2D Movement Input
	UFUNCTION()
	void Move(const FInputActionValue& Value);

	// Handles Camera movement
	UFUNCTION()
	void MoveCamera(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = Player)
	float GetMaxHP();

	UFUNCTION(BlueprintCallable, Category = Player)
	float GetCurrentHP();

	UFUNCTION(BlueprintCallable, Category = Player)
	float GetDamage();

	UFUNCTION(BlueprintCallable, Category = Player)
	void OnInteract();

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void SetKeyCollected(bool Value);

	virtual void ReceiveDamage_Implementation(float DamageReceived) override;

	UFUNCTION(BlueprintCallable, Category = "Input")
	UInputMappingContext* GetInputMappingContext() const { return InputMappingContext; }
};