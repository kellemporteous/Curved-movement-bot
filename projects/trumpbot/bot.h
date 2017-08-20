#ifndef BOT_H
#define BOT_H
#include "bot_interface.h"
#include "kf/kf_random.h"

#ifdef BOT_EXPORTS
#define BOT_API __declspec(dllexport)
#else
#define BOT_API __declspec(dllimport)
#endif

class TrumpBot:public BotInterface27
{
public:
	// Example of finite state machine states.
	enum MovementState
	{
		MS_Random,
		MS_Lunge,
		MS_Freeze
	};

	TrumpBot();
	virtual ~TrumpBot();
	virtual void init(const BotInitialData &initialData, BotAttributes &attrib);
	virtual void update(const BotInput &input, BotOutput27 &output);
	virtual void result(bool won);
	virtual void bulletResult(bool hit);
	void pickRandomTarget();
	void drawCircle(BotOutput27 & output,kf::Vector2 centre, float radius, float r, float g, float b);

	kf::Xor128 m_rand;				// A random number generator.
	BotInitialData m_initialData;	// Initial bot data. This contains map data.
	kf::Vector2 aimDir;				// The direction the bot is aiming.
	kf::Vector2 target;				// The target for movement.
	kf::Vector2 enemyPos;			// Last known location of an enemy.
	int enemySpottedFrame;			// Frame number when the enemy was spotted (used to tell how old the enemyPos is)
	int frameNumber;				// Current frame number (incremented every update, each frame is 0.1s).
	MovementState currentMovementState;	// Movement state machine current state.
	MovementState lastMovementState;	// Movement state machine last state.
	int lastHealth;						// Health from the last frame. This is used to track damage to the bot.
};


#endif