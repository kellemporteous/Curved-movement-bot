#include "bot.h"
#include "time.h"

extern "C"
{
	BotInterface27 BOT_API *CreateBot27()
	{
		return new ThatGuy();
	}
}

ThatGuy::ThatGuy()
{
	m_rand(time(0)+(int)this);
}

ThatGuy::~ThatGuy()
{
}

void ThatGuy::init(const BotInitialData &initialData, BotAttributes &attrib)
{
	m_initialData = initialData;
	attrib.health=1.0;
	attrib.motor=1.0;
	attrib.weaponSpeed=1.0;
	attrib.weaponStrength=1.0;
	frameNumber = 0;
	//dir.set(m_rand.norm()*2.0 - 1.0, m_rand.norm()*2.0 - 1.0);
	aimDir.set(1, 0);
	//set the positon of target (Vector2)
	currentState = PlayerState::PS_NormalMovement;
	lastState = currentState;
	
	maxHealth = attrib.health;
	progress = 0;
	first = true;
}

void ThatGuy::update(const BotInput &_input, BotOutput27 &_output)
{	
	input = _input;
	output = &_output;

	if (first)
	{
		randomTarget();
		target = controlPoints[0];
		first = false;
	}


	output->motor = 1.0;
	//This is so we can update the bot logic
	botLogic();

	healthCheck();

	//set the position the bot will move
	//reset the position when target in within a certain distance
	kf::Vector2 delta = target - input.position;








	output->moveDirection = delta;
	if (delta.length() < 0.5)
	{
		progress += 0.05;
		if (progress > 1)
		{
			progress = 0;
			randomTarget();
		}

		kf::Vector2 temp11;
		kf::Vector2 temp12;
		kf::Vector2 temp13;
		temp11 = kf::lerp(controlPoints[0], controlPoints[1], progress);
		temp12 = kf::lerp(controlPoints[1], controlPoints[2], progress);
		temp13 = kf::lerp(controlPoints[2], controlPoints[3], progress);

		kf::Vector2 temp21;
		kf::Vector2 temp22;
		temp21 = kf::lerp(temp11, temp12, progress);
		temp22 = kf::lerp(temp12, temp13, progress);

		target = kf::lerp(temp21, temp22, progress);


	}


	//output.moveDirection.set(1, 0);
	//output.moveDirection.set(m_rand.norm()*2.0-1.0, m_rand.norm()*2.0-1.0);
	//output->lookDirection.set(0,1);
	//output->action = BotOutput::scan;
	//output.spriteFrame = (output.spriteFrame+1)%2;

	if (currentState != PlayerState::PS_RunBoi)
	{
		output->text.clear();
		char buf[100];
		sprintf(buf, "%d", input.health);
		output->text.push_back(TextMsg(buf, input.position - kf::Vector2(0.0f, 1.0f), 0.0f, 0.7f, 1.0f, 80));
	}
	//Print a line to say the bot movement
	output->lines.clear();
	Line l;
	l.start = input.position;
	l.end = target;
	l.r = 1.0f;
	output->lines.push_back(l);
	for (int i = 0;i < 3;i++)
	{
		l.start = controlPoints[i];
		l.end = controlPoints[i + 1];
		l.r = 1;
		l.g = 0;
		l.b = 1;
		output->lines.push_back(l);
	}
	kf::Vector2 temp = controlPoints[0];
	for (float p = 0;p < 1.0;p += 0.01)
	{
		kf::Vector2 temp11;
		kf::Vector2 temp12;
		kf::Vector2 temp13;
		temp11 = kf::lerp(controlPoints[0], controlPoints[1], p);
		temp12 = kf::lerp(controlPoints[1], controlPoints[2], p);
		temp13 = kf::lerp(controlPoints[2], controlPoints[3], p);

		kf::Vector2 temp21;
		kf::Vector2 temp22;
		temp21 = kf::lerp(temp11, temp12, p);
		temp22 = kf::lerp(temp12, temp13, p);

		l.end = kf::lerp(temp21, temp22, p);
		l.start = temp;
		l.r = 0;
		l.g = 1;
		l.b = 1;
		output->lines.push_back(l);
		temp = l.end;
	}
	frameNumber++;

}

void ThatGuy::result(bool won)
{
}

void ThatGuy::bulletResult(bool hit)
{

}

void ThatGuy::healthCheck()
{
	currentHealth = input.health;

	if (currentHealth <= maxHealth / 4)
	{
		currentState = PlayerState::PS_RunBoi;
	}
}

//This code is the logic that dictates the next point on the map the bot will move to
//Randomly picking a tile
//If selected tile is a wall, pick a new tile
void ThatGuy::randomTarget()
{
	controlPoints[0] = input.position;
	for (int i = 1; i < 4; i++)
	{
		int index;
		do
		{
			controlPoints[i].set(int(m_rand.norm() * (m_initialData.mapData.width - 3)) + 1.5, int(m_rand.norm() * (m_initialData.mapData.height - 3)) + 1.5);
			index = int(controlPoints[i].x) + int(controlPoints[i].y) * m_initialData.mapData.width;
		} while (m_initialData.mapData.data[index].wall);
	}

}

void ThatGuy::lookingForEnemy()
{
	for (int i = 0; i < input.scanResult.size(); ++i)
	{
		if (input.scanResult[i].type == VisibleThing::e_robot)
		{
			enemyPos = input.scanResult[i].position;
			frameSpotted = frameNumber;
			currentState = PlayerState::PS_Attacking;
		}
	}

	
	output->lookDirection = aimDir;
	if(output->action == BotOutput27::Action::scan)
		aimDir = aimDir.rotate(m_initialData.scanFOV * 2);
	output->action = BotOutput27::Action::scan;

}

void ThatGuy::botAttack()
{
	shootBoi();
	currentState = lastState;
}

void ThatGuy::botDefend()
{
	shootBoi();
	currentState = lastState;
}

void ThatGuy::runBoi()
{
	output->text.clear();
	output->text.push_back(TextMsg("OH SHIT RUN BOI", input.position - kf::Vector2(0.0f, 1.0f), 0.0f, 0.7f, 1.0f, 80));
}


void ThatGuy::shootBoi()
{
	output->lookDirection = enemyPos - input.position;
	aimDir = output->lookDirection;//.rotate(m_initialData.scanFOV * -2);
	output->action = BotOutput27::Action::shoot;
}

void ThatGuy::botLogic()
{
	switch (currentState)
	{
	case PlayerState::PS_NormalMovement:
		lookingForEnemy();
		break;
	case PlayerState::PS_Attacking:
		botAttack();
		break;
	case PlayerState::PS_Defending:
		break;
	case PlayerState::PS_RunBoi:
		runBoi();
		break;
	}
}
