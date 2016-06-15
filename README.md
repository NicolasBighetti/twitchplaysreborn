#Twitch Play API

Projet twitch plays pnsinnov 2016


TwitchPlay is a Plug in for Unreal Engine it allows developper to quickly link their pawns and actors to a Twitch Channel.
We offers:

* binding Keywords to your pawn's method from your c++ code
* implementation of the different chat parsing strategies (democratie, anarchy and basic)
* use of custom TwitchEvent like Spamming and CloudWord to interact with your viewers
* dynamic management of camps, your viewers can join the different side based of the number of Pawn you dropped in your game

### Getting Started

Download te latest version from github
Launch Unreal Engine

Create a new C++ Basic Code project, call it TwitchTest
It's very important to call it TwitchTest cause all the file belongs to this module

![start](https://github.com/Paltoquet/UnrealTutoRessource/blob/master/Start1.PNG)

Go to your Source folder (UnrealProjects/TwitchPlaysProject/Source)
Insert the content of Source/TwitchTest/private and Source/TwitchTest/classes you get from the git repository in to your Source folder
(Classes got all the .h files, private all the .cpp the files from root are just samples)

Add the TwitchPlaysAPI.conf and bannedWords.txt in your Config folder (UnrealProjects/TwitchPlaysProject/Config)
Open the TwitchPlaysAPI.conf from notepad supply it with the appropriate info
channel: the channel you wish to connect
botNickname: the pseudo of a valid Twitch acount
oAuth : a crypted key you got from http://www.twitchapps.com/tmi/ linked to your account
strategy: basic (each word one command), anarchy (a random command during laps time), democracy (an elected command during a lap time)
tick: lap time for anarchy or democracy in second

```
oAuth : xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
botNickname : mybot
channel	: #mybot
strategy : basic
tick : 1
bannedWordsFile : Config/bannedWords.txt
```

Open Visual Studio if not opened (File/Open Visual Studio)
Open TwitchTestGameMode.h
make inherit your class from ATwitchGameMode and add the appropriate include

```
#include "TwitchPlaysAPI.h"
#include "TwitchGameMode.h"
#include "TwitchTestGameMode.generated.h"

#pragma once

UCLASS()
class TWITCHTEST_API ATwitchTestGameMode : public ATwitchGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	
};

```

your TwitchTestGameMoede.cpp shoul look like that

```
#include "TwitchTestGameMode.h"

void ATwitchTestGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ATwitchTestGameMode::BeginDestroy()
{
	Super::BeginDestroy();
}

```

ATwitchGameMode connect to the IRC chat supplied in the config file
It will bind each of your TwitchPawnActor to a different camp and notify them when a command has arrived



###Create a custom Pawn

go to the Unreal Editor and create a new Pawn, call it MyTwitchPawn
![Pawn](https://github.com/Paltoquet/UnrealTutoRessource/blob/master/Pawn.PNG)


go to MyTwitchPawn.h
make it inherit ATwitchPawn, include the file too.
add a mesheComponent with a uproperty tag to make it editable from editor

```
#pragma once

#include "TwitchPlaysAPI.h"
#include "GameFramework/Pawn.h"
#include "TwitchPawn.h"
#include "MyTwitchPawn.generated.h"

UCLASS()
class TWITCHTEST_API AMyTwitchPawn : public ATwitchPawn
{
	GENERATED_BODY()



public:

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* OurVisibleComponent;
	// Sets default values for this pawn's properties
	AMyTwitchPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UStaticMeshComponent* GetOurVisibleComponent() { return OurVisibleComponent; }

	
	
};

```

the cpp file
we add a camera to our component and we enable physics

```
#include "TwitchPlaysAPI.h"
#include "MyTwitchPawn.h"


// Sets default values
AMyTwitchPawn::AMyTwitchPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Create a camera and a visible object
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	OurCamera->AttachTo(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	OurVisibleComponent->AttachTo(RootComponent);
	OurVisibleComponent->SetSimulatePhysics(true);

}

// Called when the game starts or when spawned
void AMyTwitchPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyTwitchPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AMyTwitchPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

```

now click build solution on visual studio or compile form the game editor
if everything is fine you should be able to drag and drop a MyTwitchPawn in to the world and set its mesh and material
![custom](https://github.com/Paltoquet/UnrealTutoRessource/blob/master/TwitchPawn.PNG)

###Bind action to the Pawn

Go to the Edit and click on add new c++ class and then none parent class
Call it MyTwitchPawnCommand

![start](https://github.com/Paltoquet/UnrealTutoRessource/blob/master/PawnCommand.PNG)

We will create a super class  MyTwitchPawnCommand and also all the different Command we want for our Pawn.
Our class will inherit FCommand which allows to bind the keyword to our parsing method, it will keep a pointer to the MyTwitchPawn as an attribute, it's a kind of a c++ delegate.
All of the subclass will inherit from the one we created and define a execute method wich will be called when the keyword is taped in chat. The Fcommand constructor taks a FString it's what will have to type in the chat to execute the appropriate method

MyTwitchPawnCommand.h

```
#pragma once


#include "TwitchPlaysAPI.h"
#include "Command.h"
#include "MyTwitchPawn.h"
/**
 * the super class for all of our command
 */
class MyTwitchPawnCommand : public FCommand
{
protected:
	AMyTwitchPawn* Pawn;
public:
//name correspond to what we will have to type
	MyTwitchPawnCommand(FString _name, AMyTwitchPawn* _pawn) : FCommand(_name), Pawn(_pawn) {}
};

class FPawnFrontCommand : public MyTwitchPawnCommand
{
public:
//type front
	FPawnFrontCommand(AMyTwitchPawn* _pawn) : MyTwitchPawnCommand(TEXT("front"), _pawn) {}
	virtual void Execute(FCommandParser parser);
};

class FPawnBackCommand : public MyTwitchPawnCommand
{
public:
//type back
	FPawnBackCommand(AMyTwitchPawn* _pawn) : MyTwitchPawnCommand(TEXT("back"), _pawn) {}
	virtual void Execute(FCommandParser parser);
};
```
now we will define the execute method for both our command back and front in the MyTwitchPawnCommand.cpp file

```
#include "TwitchPlaysAPI.h"
#include "MyTwitchPawnCommand.h"


// Move ball Forward
void FPawnFrontCommand::Execute(FCommandParser parser)
{
	
	//speed
	int32 val = 4;
	const FVector Torque = FVector(0.f, -1.f * val * 500000.0f, 0.f);
	(Pawn->GetOurVisibleComponent())->AddTorque(Torque);
}

// Move ball Backward
void FPawnBackCommand::Execute(FCommandParser parser)
{

	//speed
	int32 val = 4;
	const FVector Torque = FVector(0.f, 1.f * val * 500000.0f, 0.f);
	(Pawn->GetOurVisibleComponent())->AddTorque(Torque);
}
```

We have our class Command know we need to instanciate them in the MyTwitchPawn constructor.
AMyTwitchPawn inherit from ATwitchPawn a attribute called CommandsRegistry.
we will register the new instance of our command in it.
It's used to call the appropriate method when our Actor receive a Message from our differents Threads.

go to MyTwitchPawn.cpp
the constructor know should like this, don't forget to add the new include "MyTwitchPawnCommand.h"

```
#include "TwitchPlaysAPI.h"
#include "MyTwitchPawnCommand.h"
#include "MyTwitchPawn.h"


// Sets default values
AMyTwitchPawn::AMyTwitchPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Create a camera and a visible object
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	OurCamera->AttachTo(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	OurVisibleComponent->AttachTo(RootComponent);
	OurVisibleComponent->SetSimulatePhysics(true);

	//bind the command to the registry with a pointer to the actor
	CommandsRegistry.Register(new FPawnFrontCommand(this));
	CommandsRegistry.Register(new FPawnBackCommand(this));
}
```

compile again
And run 
You should be able to move your Pawn from the chat after  "Bot activated !" have been prompt in the chat
See the output log for more detail (window/developer tool/outputlog).

![nic](https://github.com/Paltoquet/UnrealTutoRessource/blob/master/movement.PNG)


You have full access to the source files.
Check TwitchGameMode.cpp for more information or a TwitchPawn.
You can try to move your ball left and right by adding commands too.


###Create Custom Event

Not fill for the moment go see TwitchGameMode constructor
and ActorTwitchEventListener for the implementation of the listener

You need to implement TwitchEventListener on one of your class (actor,gamemode,everything you want)
Then bind it to your event at creation, care you need to notify the TwitchMessageReceiver with the setEvent method.


```

	AActorTwitchEventListener* ActorListener = NULL;
	for (TActorIterator<AActorTwitchEventListener> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		UE_LOG(LogTemp, Warning, TEXT("finding actor"));
		ActorListener = *ActorItr;
	}
	if(ActorListener != NULL){
		//events = new SpamEvent(5, Context, ActorListener, GetWorld(), TEXT("Kappa"));
		events = new CloudWordEvent(15, Context, ActorListener, GetWorld(), 4);
		((FTwitchMessageReceiver*)TwitchRunnable)->setEvent(events);
	}
```

2 Events are at your disposals SpamEvent and CloudWordEvent
SpamEvent take as parameter the FString you want to follow in the chat and return the winning team with the number of spams.
CloudWord returns the n words more used (4 in this sample) in the chat (words not phrases).





