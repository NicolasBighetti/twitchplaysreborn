// Fill out your copyright notice in the Description page of Project Settings.

#include "TwitchTest.h"
#include "Strategy.h"


Strategy::Strategy(BlockingQueue<FString>* q) {

	queue = q;
}

void Strategy::Receive() {
}

void Strategy::OnTick() {

}