// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"

/**
 * 
 */
class AIRPLANEFLYINGAI_API Raycasting
{
	
public:
	static int nb;
	Raycasting(ACharacter *ToAttach);
	~Raycasting();
	void BuildLidar(float delta);
private:
	ACharacter *Attached;
};

