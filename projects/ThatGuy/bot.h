#ifndef BOT_H
#define BOT_H
#include "bot_interface.h"
#include "kf/kf_random.h"

#ifdef BOT_EXPORTS
#define BOT_API __declspec(dllexport)
#else
#define BOT_API __declspec(dllimport)
#endif

class ThatGuy:public BotInterface27
{
public:
	enum PlayerState
	{
		PS_NormalMovement,
		PS_Attacking,
		PS_Defending,
		PS_RunBoi
	};
	ThatGuy();
	virtual ~ThatGuy();
	virtual void init(const BotInitialData &initialData, BotAttributes &attrib);
	virtual void update(const BotInput &_input, BotOutput27 &_output);
	virtual void result(bool won);
	virtual void bulletResult(bool hit);
	void healthCheck();
	void randomTarget();
	void lookingForEnemy();
	void botLogic();
	void botAttack();
	void botDefend();
	void runBoi();
	void shootBoi();



	kf::Xor128 m_rand;
	BotInitialData m_initialData;
	kf::Vector2 aimDir;
	kf::Vector2 controlPoints[4];
	kf::Vector2 target;
	kf::Vector2 enemyPos;
	PlayerState currentState;
	PlayerState lastState;
	BotInput input;
	BotOutput27 *output;
	int frameSpotted;
	int frameNumber;
	float currentHealth;
	float maxHealth;
	float progress;
	bool first;
};


#endif