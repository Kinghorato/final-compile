#include "AI.h"

void MovingAI(struct ROBOTS *BOT, int BotNumber)
{
	//Horizontal AI
	if (BotNumber != 4)
	{
		BOT[BotNumber].xpos += BOT[BotNumber].dir * 1;
		BOT[BotNumber].step++;

		if (BOT[BotNumber].step >= BOT[BotNumber].range)
		{
			BOT[BotNumber].dir *= -1;
			BOT[BotNumber].step = 0;
		}
	}
	//Vert AI
	else
	{
		BOT[BotNumber].ypos += BOT[BotNumber].dir * 1;
		BOT[BotNumber].step++;


		if (BOT[BotNumber].step >= 11)
		{
			BOT[BotNumber].dir *= -1;
			BOT[BotNumber].step = 0;
		}
	}



}