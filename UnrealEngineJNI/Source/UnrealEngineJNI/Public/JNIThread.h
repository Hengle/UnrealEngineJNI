// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "UnrealEngineJNI.h"
#include "JNIThread.generated.h"


class FJNIRunnable : public FRunnable
{
private:
	JNIEnv *AttachedJNIEnv;
	JavaVM *Vm;
	FRunnableThread* Thread;

protected:
	jclass JNIClass;
	jobject JNIObject;
	jmethodID JNIMethodID;

	jclass JThreadClass;
	jobject JCurrentThread;
	jmethodID JThreadInterrupt;

public:
	FJNIRunnable(jobject JObject, jmethodID JMethodID);
	FJNIRunnable(jclass JClass, jmethodID JMethodID);
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
};

/**
 * 
 */
UCLASS(BlueprintType)
class UNREALENGINEJNI_API UJNIThread : public UObject
{
	GENERATED_BODY()
	
private:
	FJNIRunnable *JNIRunnable;
	
public:
	void StartJNIThread(jobject JObject, jmethodID JMethodID);
	void StartJNIThread(jclass JClass, jmethodID JMethodID);
	~UJNIThread();
};
