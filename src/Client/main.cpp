//-----------------------------------------------------------------------------
//
// Assignment 2 - Networked game of tic-tac-toe
//
// Authors:
//  * David Jordan
//  * Garret Moran
//
//-----------------------------------------------------------------------------
//#include <stdio.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <Windows.h>


#include "ClientApp.h"

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>

#include <SDL2/SDL.h>
#undef main

#include <GameLib/Application.h>
#include <GameLib/graphics/Graphics.h>

#include "Enums.h"
#include "Entity.h"


#define SERVER_PORT 32764

using namespace std;
using namespace enums;


//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

void DoTest()
{
	//std::cout << EnumMap<GameTag>::MAP.at(GameTag::NAME) << std::endl;
	//std::cout << EnumMap<GameTag>::MAP.at(GameTag::CARD_ID) << std::endl;
	//std::cout << EnumMap<Tribe>::MAP.at(Tribe::AARD) << std::endl;
	//std::cout << EnumMap<Tribe>::MAP.at(Tribe::OCTOPI) << std::endl;
	

	auto typeInfo = GetTagTypeInfo(GameTag::TRIBE);

	std::cout << typeInfo->GetEnumName() << std::endl;
	std::cout << typeInfo->IntToName(6) << std::endl;
	std::cout << typeInfo->NameToInt("AARD") << std::endl;
	
	CardDatabase db;
	db.Initialize();

	//Tribe tribe = enums::ParseValue<GameTag>("aard");
	//std::cout << (int) tribe << " = " << enums::ValueName(tribe) << std::endl;


	return;
	//using namespace enums;
	//GameTag value = GameTag::AFTERMATH;
	//std::string name = ValueName<GameTag>(value);
	//printf("%s\n", EnumName<GameTag>().c_str());
	//printf("%d = %s\n", value, name.c_str());

	Tags tags;

	tags[GameTag::POWER] = 12345;
	tags[GameTag::NAME] = "Game";
	tags[GameTag::ZONE] = Zone::PLAY;
	tags[GameTag::STEP] = Step::DECLARE;

	int power = tags[GameTag::POWER];
	std::string name = tags[GameTag::NAME];
	cout << "Power = " << tags[GameTag::POWER].ValueName() << endl;
	cout << "Name = " << tags[GameTag::NAME].ValueName() << endl;
	cout << "Zone = " << tags[GameTag::ZONE].ValueName() << endl;
	cout << "Step = " << tags.Get(GameTag::STEP).ValueName() << endl;
	cout << "Text = " << tags.Get(GameTag::TEXT, "default") << endl;
	cout << "Health = " << tags.Get(GameTag::HEALTH, 16) << endl;

	cout << endl;
	cout << tags.Dump();
	cout << endl;
	cout << tags.ToJSON().dump();
	cout << endl;
	cout << Tags(tags.ToJSON()).Dump();
	cout << endl;
	cout << endl;

	Game game;
	game.Create();
	game.CreateEntity(4, CardType::UNIT, Tags::EMPTY);
	Player* player = (Player*) game.CreateEntity(4, CardType::PLAYER, Tags::EMPTY);
	player->SetTag(GameTag::NAME, "David Jordan");

	cout << "Player name = " << player->GetName() << endl;
}



int main(int argc, char* argv[])
{
	//DoTest(); system("pause"); return 0;

	ClientApp* client = new ClientApp();

	std::string address = "localhost";
	int port = 32764;

	client->Initialize("Card Game Client", 1000, 900);

	if (!client->Connect(address, port))
	{
		client->Quit();
		system("pause");
		return 1;
	}

	// Receive the welcome packet.
	json message;
	//client.Receive();
	//client.GetGame().PrintState();

	client->Run();
	//system("pause");
	return 0;
}
