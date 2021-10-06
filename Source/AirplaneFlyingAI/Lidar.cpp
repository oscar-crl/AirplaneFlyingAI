// Fill out your copyright notice in the Description page of Project Settings.


#include "Lidar.h"

#include <array>

#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"


#include "Engine/World.h"


Lidar::Lidar(ACharacter* ToAttach)
{
	this->Attached = ToAttach;
	this->Frequency = 0.0;
	this->LoadedFrequency = 0.0;
}

Lidar::~Lidar()
{
}

UStaticMeshComponent* Lidar::GetBaseMesh()
{
	UActorComponent* Base = nullptr;

	for (auto ok : this->Attached->GetComponents())
	{
		if (ok->GetName() == "Plane")
		{
			Base = ok;
		}
	}
	if (Base == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("FAILED TO FIND ACTOR"));
		return {};
	}
	return Cast<UStaticMeshComponent>(Base);
}


void Lidar::ApplyLidar(float Delta, std::function<void(float, FHitResult)> OnHit)
{
	FHitResult Result;
	UStaticMeshComponent* BaseMesh = this->GetBaseMesh();
	FVector Start = BaseMesh->GetComponentLocation();
	FRotator Rotation = BaseMesh->GetComponentRotation();
	const std::array<FVector, 9> VectorArray = {
		FVector(500, 0, 0), {500, 250, 0}, {500, -250, 0}, /* LIDAR in front of the plane*/
		{500.0f, -500.0f, 0.0f}, {500, -750, 0}, {500, -1000, 0} /* LIDAR at the left side of the plane*/,
		{500.0f, 500.0f, 0.0f}, {500, 750, 0}, {500, 1000, 0} /* LIDAR at the right side of the plane*/
	};

	this->LoadedFrequency += Delta;
	if (this->LoadedFrequency < Frequency)
		return;
	this->LoadedFrequency = 0.0;
	for (auto Vector : VectorArray)
	{
		Vector = Rotation.RotateVector(Vector);
		const FVector End = {Start.X + Vector.X, Start.Y + Vector.Y, Start.Z + Vector.Z};
		auto Query = FCollisionQueryParams();
		auto DidHit = false;
		FCollisionObjectQueryParams QueryParams;

		QueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		DrawDebugLine(this->Attached->GetWorld(), Start, End, FColor::Green, false, Delta * 2, 5);
		DidHit = this->Attached->GetWorld()->LineTraceSingleByObjectType(Result, Start, End, QueryParams, {});
		if (DidHit)
		{
			OnHit(Delta, Result);
		}
	}
}

void Lidar::SetLidarFrequency(float NewFrequency)
{
	this->Frequency = NewFrequency;
}
