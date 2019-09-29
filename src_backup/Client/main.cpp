//-----------------------------------------------------------------------------
//
// Assignment 2 - Networked game of tic-tac-toe
//
// Authors:
//  * David Jordan
//  * Garret Moran
//
//-----------------------------------------------------------------------------

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <RakNet/BitStream.h>
#include <RakNet/RakNetTypes.h>  // MessageID
#include <RakNet/RakPeerInterface.h>
#include <RakNet/MessageIdentifiers.h>

#include <SDL2/SDL.h>
#undef main

#include <GameLib/Application.h>
#include <GameLib/graphics/Graphics.h>
#include <Common/GameConfig.h>
#include "ClientApp.h"
#include "NewClientApp.h"

#define SERVER_PORT 60000

using namespace std;
using namespace RakNet;


//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

//#define EXPAND(x) x

// Accept any number of args >= N, but expand to just the Nth one. In this case,
// we have settled on 5 as N. We could pick a different number by adjusting
// the count of throwaway args before N. Note that this macro is preceded by
// an underscore--it's an implementation detail, not something we expect people
// to call directly.
//#define _GET_NTH_ARG(_1, _2, _3, _4, N, ...) N

// Count how many args are in a variadic macro. Only works for up to N-1 args.
//#define COUNT_VARARGS(...) EXPAND(_GET_NTH_ARG(__VA_ARGS__, 4, 3, 2, 1))

int main(int argc, char* argv[])
{
	//COUNT_VARARGS(1);
	//COUNT_VARARGS(6, 2);
	//std::cout << 9, 2, 3;
	//COUNT_VARARGS(9, 2, 3);
	//_GET_NTH_ARG(1, 2, 3,       4, 3, 2, 1)
	////printf("%d\n", COUNT_VARARGS());
	//printf("%d\n", COUNT_VARARGS(1));
	//printf("%d\n", COUNT_VARARGS(6, 2));
	//printf("%d\n", COUNT_VARARGS(9, 2, 3));
	////printf("%d\n", _GET_NTH_ARG(4, 3, 2, 1));
	//printf("%d\n", _GET_NTH_ARG(1, 4, 3, 2, 1));
	//printf("%d\n", _GET_NTH_ARG(6, 2, 4, 3, 2, 1));
	//printf("%d\n", _GET_NTH_ARG(9, 2, 3, 4, 3, 2, 1));
	//printf("%d\n", _GET_NTH_ARG(9, 2, 3, 7, 4, 3, 2, 1));
	//_LIST_PARAMETERS(_PRINT, int,x);
	//printf("\n");
	//_LIST_PARAMETERS(_PRINT, char,c, float,f);
	//printf("\n");
	//_LIST_PARAMETERS(_PRINT, char,c, float,f, int,i);
	//printf("\n");
	//_LIST_PARAMETERS(_PRINT, char,c, float,f, int,i, bool,b);
	//printf("\n");
	
	//Trigger trigger Trigger(
		//new events::Aftermath(),
		//new actions::Summon(1, tokenTentacles)
	//);

	Card* tokenTentacles = new Card();
	tokenTentacles->m_name = "Tentacles";
	tokenTentacles->m_power = 1;
	tokenTentacles->m_health = 1;
	tokenTentacles->m_tribe = nullptr;

	TriggerAction* action = new actions::Summon(
		1, tokenTentacles);

	//auto func = [&]()
	//{
	//	Context ctx;
	//	ctx.actions.Summon(
	//		ctx.functions.integer.Min(6, 4),
	//		tokenTentacles);
	//};
	
	auto effectTentacles = new Effect("Tentacles", new Trigger(
		new events::Aftermath(),
		new conditions::UnitIsAlive(new functions::unit::DyingUnit()),
		new actions::Summon(2, tokenTentacles))
	);
	auto effectNoxious = new Effect("Noxious", new Trigger(
		new events::AttackedByUnit(),
		new conditions::UnitIsDead(new functions::unit::AttackedUnit()),
		new actions::DamageAUnit(2, new functions::unit::AttackingUnit())
	));

	Game game;

	game.PrintCurrentState(std::cout);


	Context context;
	context.game = &game;
	context.opponent = game.GetPlayer(1);
	context.player = game.GetPlayer(0);
	action->Execute(&context);

	auto summonedUnit = game.GetPlayer(0)->GetPlayField()->m_cards[0];
	summonedUnit->AddEffect(effectTentacles);

	//TriggerEvent* event = new events::Aftermath();
	//auto e = new events::UnitDeath(summonedUnit);
	//cout << "Event Check: " << event->CheckEvent(&context, e) << endl;

	game.PrintCurrentState(std::cout);

	game.DamageUnit(summonedUnit, 5);

	game.PrintCurrentState(std::cout);
	
	system("pause");
	return 0;
	//BaseTest* asd = IntOrFloat(1.0f);
	//functions::integer::Max m;
	
	NewClientApp app;
	app.Initialize("Card Game", 750, 500);
	app.Run();
	return 0;

	/*
	RakPeerInterface *peer = RakPeerInterface::GetInstance();

	ClientApp app(peer);

	// Setup the client socket.
	SocketDescriptor sd;
	peer->Startup(1, &sd, 1);
	peer->SetOccasionalPing(true);

	// Prompt for the IP address to connect to.
	char str[512];
	printf("Enter server IP or hit enter for 127.0.0.1\n");
	gets_s(str, sizeof(str));
	if (str[0] == 0)
	{
		strcpy_s(str, "127.0.0.1");
	}

	// Connect to the server.
	printf("Starting the client.\n");
	peer->Connect(str, SERVER_PORT, 0, 0);

	RakNet::SystemAddress serverAddress;
	int connectionResult = 0;

	// Wait for connection handshake to pass.
	Packet *packet;
	while (connectionResult == 0 || connectionResult == 1)
	{
		for (packet = peer->Receive(); packet != NULL && connectionResult != 2;
			peer->DeallocatePacket(packet), packet = peer->Receive())
		{
			switch (packet->data[0])
			{
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				printf("Server is full!\n");
				connectionResult = -1;
				break;
			case ID_CONNECTION_REQUEST_ACCEPTED:
				printf("Connected successfully!\n");
				serverAddress = packet->systemAddress;
				connectionResult = 1;
				break;
			case PacketType::ACCEPT_CONNECTION:
				app.ReadConnectionAcceptedPacket(packet);
				connectionResult = 2;
				break;
			}
		}
	}

	// Run the client application.
	if (connectionResult == 2)
	{
		app.Initialize("Slime Volleyball", 750, 500);
		app.Run();
	}
	else
	{
		system("pause");
	}

	RakPeerInterface::DestroyInstance(peer);
	return 0;
	*/
}
