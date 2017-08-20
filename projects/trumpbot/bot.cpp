#include "bot.h"
#include "time.h"

extern "C"
{
	BotInterface27 BOT_API *CreateBot27()
	{
		return new TrumpBot();
	}
}

TrumpBot::TrumpBot()
{
	m_rand(time(0)+(int)this);
}

TrumpBot::~TrumpBot()
{
}

void TrumpBot::init(const BotInitialData &initialData, BotAttributes &attrib)
{
	m_initialData = initialData;
	attrib.health=1.0;
	attrib.motor=1.0;
	attrib.weaponSpeed=1.0;
	attrib.weaponStrength=1.0;
	aimDir.set(1, 0);
	pickRandomTarget();
	frameNumber = 0;
	currentMovementState = MovementState::MS_Random;
	lastMovementState = currentMovementState;
	lastHealth = 0;
}

void TrumpBot::update(const BotInput &input, BotOutput27 &output)
{
	output.motor = 1.0;
	
	kf::Vector2 delta = target - input.position;

// Movement

	// Example finite state machine:
	//
	//switch (currentMovementState)
	//{
	//	case MovementState::MS_Freeze:
	//		output.moveDirection.set(0, 0);
	//		break;
	//	case MovementState::MS_Lunge:
	//		break;
	//	case MovementState::MS_Random:
	//	{
	//		output.moveDirection = delta;
	//		if (delta.length() < 0.8)
	//		{
	//			pickRandomTarget();
	//		}
	//		if (frameNumber > 100)
	//		{
	//			lastMovementState = currentMovementState;
	//			currentMovementState = MovementState::MS_Freeze;
	//		}
	//	}
	//		break;
	//}

	output.moveDirection = delta;
	if (delta.length() < 0.8)
	{
		pickRandomTarget();
	}


// Scanning
	bool spotted = false;
	for (int i = 0; i < input.scanResult.size(); ++i)
	{
		if (input.scanResult[i].type == VisibleThing::e_robot)
		{
			enemyPos = input.scanResult[i].position;
			enemySpottedFrame = frameNumber;
			spotted = true;
		}
	}

	if (spotted)
	{
		if (currentMovementState == MovementState::MS_Random)
		{
			output.lookDirection = enemyPos - input.position;
			aimDir = output.lookDirection.rotate(m_initialData.scanFOV * -2);
			output.action = BotOutput27::Action::shoot;
			target = enemyPos;
		}
	}
	else
	{
		output.action = BotOutput27::Action::scan;
		 aimDir = aimDir.rotate(m_initialData.scanFOV * 2);
		 output.lookDirection = aimDir;
	}

// Sprite animation
	if (input.health < lastHealth)
	{
		//tput.spriteFrame = 1;
	}
	else
	{
		output.spriteFrame = 0;
	}

// Debug
	// output.text.clear();
	// char buf[100];
	// sprintf(buf, "%d", input.health);
	// output.text.push_back(TextMsg(buf, input.position - kf::Vector2(0.0f, 1.0f), 0.0f, 0.7f, 1.0f,80));

	output.lines.clear();
	Line l;
	l.start = input.position;
	l.end = target;
	l.r = 1.0f;
	l.g = 0;
	l.b = 1.0f;
	output.lines.push_back(l);
	
	drawCircle(output, input.position, 0.35, 1, 1, 0);

	frameNumber++;	// increment the frame number.
	lastHealth = input.health;
}

void TrumpBot::result(bool won)
{
}

void TrumpBot::bulletResult(bool hit)
{

}

// Look for a tile that doesn't contain a wall and make it the movement target.
void TrumpBot::pickRandomTarget()
{
	int index;
	do
	{
		target.set(int(m_rand.norm() * (m_initialData.mapData.width - 3)) + 1.5, int(m_rand.norm() * (m_initialData.mapData.height - 3)) + 1.5);
		index = int(target.x) + int(target.y) * m_initialData.mapData.width;
	} while (m_initialData.mapData.data[index].wall);
}

void TrumpBot::drawCircle(BotOutput27 & output, kf::Vector2 centre, float radius, float r, float g, float b)
{
	float angle = (3.14159265*2.0) / 32;
	for (float i = 0; i<3.14159265*2.0;i+=angle)
	{
		kf::Vector2 p1(cos(i)*radius, sin(i)*radius);
		kf::Vector2 p2(cos(i+angle)*radius, sin(i + angle)*radius);
		Line l;
		l.start = p1+ centre;
		l.end = p2+ centre;
		l.r = r;
		l.g = g;
		l.b = b;
		output.lines.push_back(l);
	}
}