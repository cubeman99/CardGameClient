#ifndef _CLIENT_APP_H_
#define _CLIENT_APP_H_

#include "NetworkManager.h"
#include <map>
#include <vector>
#include <GameLib/Application.h>
#include <GameLib/graphics/Graphics.h>
#include <GameLib/math/Rect2f.h>
#include <GameLib/math/Vector2f.h>
#include "Entity.h"
#include <mutex>


struct CardGraphics
{
	Rect2f		nameBox;
	Rect2f		textBox;
	Vector2f	size;
};


// Application class that runs the client.
class ClientApp : public Application, ReceiveCallback
{
public:
	ClientApp();
	~ClientApp();

	inline NetworkManager& GetNetworkManager() { return m_network; }
	inline Game& GetGame() { return m_game; }

	bool Connect(const std::string& address, int port);
	bool Receive();

	void Receive(const json& message) override;
	bool IsReceiving() override;

	Player* GetPlayer() { return (Player*) m_game.GetEntity(m_playerId); }

	float GetTimeStamp();

	//void FlipCard(CardInstance* card);
	//void UnflipCard(CardInstance* card);
	//void DeclareAttack(const AttackMove& attack);
	//void DeclareAttack(CardInstance* subject, CardInstance* target);
	//void UndeclareAttack(AttackMove* attack);
	//void UndeclareAttack(CardInstance* card);
	//AttackMove* GetAttack(CardInstance* card);

	//void UnflipAllCards(Player* player);

	//void ResolveCombat();
	//void ResolveNextAttack();
	//void ResolveAttack(AttackMove* attack);
	//void ResolveDeath(CardInstance* unit);



	void DrawTextInBox(Graphics& g, Font* font, std::string text, const Rect2f& box, const Color& color);
	void DrawCard(Graphics& g, Card* card, const Vector2f& position);
	void DrawField(Graphics& g, Player* player, const Vector2f& center);
	void DrawHand(Graphics& g, Player* player, const Vector2f& center);

protected:
	void OnInitialize() override;
	void OnUpdate(float timeDelta) override;
	void OnRender() override;
	void OnQuit() override;

private:
	Game m_game;
	NetworkManager m_network;
	int m_playerId;
	std::mutex m_mutex;

	Option m_targetingOption;
	bool m_targeting;
	std::vector<Card*> m_targets;

	Card* m_selectedCard;
	Card* m_mousedOverCard;

	CardGraphics m_cardGraphics;

	// Resources
	Texture*	m_testTexture;
	Font*		m_fontScore;
	Font*		m_fontSmall;
};


#endif // _CLIENT_APP_H_