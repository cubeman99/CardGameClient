#ifndef _NEW_CLIENT_APP_H_
#define _NEW_CLIENT_APP_H_

#include <map>
#include <vector>
#include <GameLib/Application.h>
#include <GameLib/graphics/Graphics.h>
#include <GameLib/math/Rect2f.h>
#include <GameLib/math/Vector2f.h>
#include "Card.h"
#include "GameRules.h"
#include "triggers/Trigger.h"
#include "Game.h"


class AttackMove
{
public:
	CardInstance* m_subject;
	CardInstance* m_target;
};


// Application class that runs the client.
class NewClientApp : public Application
{
public:
	NewClientApp();
	~NewClientApp();

	float GetTimeStamp();

	void FlipCard(CardInstance* card);
	void UnflipCard(CardInstance* card);
	void DeclareAttack(const AttackMove& attack);
	void DeclareAttack(CardInstance* subject, CardInstance* target);
	void UndeclareAttack(AttackMove* attack);
	void UndeclareAttack(CardInstance* card);
	AttackMove* GetAttack(CardInstance* card);

	void UnflipAllCards(Player* player);

	void ResolveCombat();
	void ResolveNextAttack();
	void ResolveAttack(AttackMove* attack);
	void ResolveDeath(CardInstance* unit);



	void DrawCard(Graphics& g, CardInstance* card, const Vector2f& position);
	void DrawField(Graphics& g, Player* player, const Vector2f& center);
	void DrawHand(Graphics& g, Player* player, const Vector2f& center);

protected:
	void OnInitialize() override;
	void OnUpdate(float timeDelta) override;
	void OnRender() override;
	void OnQuit() override;

private:
	CardDatabase m_cardDatabase;
	CardManager m_cardManager;

	CardInstance* m_selectedCard;
	CardInstance* m_mousedOverCard;

	std::vector<AttackMove*> m_attackMoves;

	Tribe* m_tribeSlug;
	Player* m_players[2];

	// Resources
	Texture*	m_testTexture;
	Font*		m_fontScore;
	Font*		m_fontSmall;
};


#endif // _NEW_CLIENT_APP_H_