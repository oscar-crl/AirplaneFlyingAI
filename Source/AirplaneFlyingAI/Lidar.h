// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"

/**
 * 
 */
class AIRPLANEFLYINGAI_API Lidar
{
	
public:
	Lidar(ACharacter *ToAttach);
	~Lidar();
	void ApplyLidar(float Delta, std::function<void(float, FHitResult)> OnHit);
	void SetLidarFrequency(float NewFrequency);
	UStaticMeshComponent *GetBaseMesh();

private:
	ACharacter *Attached;
	float Frequency;
	float LoadedFrequency;
};

