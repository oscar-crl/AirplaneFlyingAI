// Fill out your copyright notice in the Description page of Project Settings.


#include "Raycasting.h"

#include <array>

#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"


#include "Engine/World.h"

int Raycasting::nb = 0;

Raycasting::Raycasting(ACharacter *ToAttach)
{
	this->Attached = ToAttach;
}

Raycasting::~Raycasting()
{
	
}

void Raycasting::BuildLidar(float delta)
{
	FHitResult Result;
	FVector Start = this->Attached->GetCapsuleComponent()->GetComponentLocation();
	const std::array<FVector, 4> VectorArray = { FVector(1000.0f, 0.0f, 0.0f), {-1000, 200, 200}, {200, 1000, 200}, {200, -1000, 200}};
	const std::array<ECollisionChannel, 2> ChannelArray= {ECC_WorldDynamic, ECC_WorldStatic};

	Start = {Start.X + 200.0f, Start.Y, Start.Z};
	int i = 0;
	for (const auto Vector : VectorArray)
	{
		
		const FVector End = {Start.X + Vector.X, Start.Y + Vector.Y, Start.Z + Vector.Z};
		for (const auto Channel : ChannelArray)
		{
			auto Query = FCollisionQueryParams();
				
			//Query.


			//params.AddIgnoredActor(this->Attached);
			FCollisionObjectQueryParams QueryParams;
			
			QueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
			auto mdr = this->Attached->GetWorld()->LineTraceSingleByObjectType(Result, Start, End, QueryParams, {});
			//auto mdr = this->Attached->ActorLineTraceSingle(Result, Start, End, Channel, params);
			DrawDebugLine(this->Attached->GetWorld(), Start, End, FColor::Green, false, delta * 2, 5);
			if (GEngine)	
			{
				if (mdr == true)
				{
					UE_LOG(LogTemp, Warning, TEXT("Distance %s"), ToCStr((Start - Result.ImpactPoint).ToString())); 
		
					//Result.GetActor()->Destroy();
				} else
				{
					UE_LOG(LogTemp, Warning, TEXT("TOUCHLOL! %s - Touch: %d"), ToCStr(Result.ToString()), mdr);
				}
			}
		}
		return;
	}
}
