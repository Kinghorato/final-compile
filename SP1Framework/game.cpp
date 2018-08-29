// This is the main file for the game logic and function
#include "game.h"
#include "Framework\console.h"
#pragma comment (lib,"Winmm.lib")

//--------------------------------------------Global vars---------------------------------------------------------

double  g_dElapsedTime;
double  g_dDeltaTime;
bool g_abKeyPressed[K_COUNT];
EGAMESTATES g_eGameState = S_MENU;
SGameChar   g_sChar,
				//Doors and Switches
				g_sDoor1, g_sBatDoor, g_sBatDoor1, g_sBatDoor2, g_slever1,
					//Batteries
					g_sBatteries, g_sBatteries1, g_sBatteries2, g_sBatteries3, g_sBatteries4,
						//Generators
						g_sGenerator, g_sGenerator1,
							//Coins
	g_sCoin1, g_sCoin2, g_sCoin3, g_sCoin4, g_sCoin5, g_sCoin6, g_sCoin7, g_sCoin8, g_sCoin9;
// Gary Vars
double g_dEnemyTime1;
double g_dEnemyTime2;
double g_dEnemyTime3;
double g_dEnemyTime4;

double g_dTrapTime;
vector<string> map;

ROBOTS BOT[10];
TRAPS Trap[10];
COINS Coin[10];

int lifepoint = 100;
int startingpointx = 2;
int startingpointy = 14;

int checkpoint1X = 2;
int checkpoint1Y = 14;

int Botnumber = 0;
//

//Peng Yang Vars
double	barrelRollTime, S_Bullet;
bool	doorClosed, doorClosed1;
bool	isFired, barrels;
bool	B1, B2, B3, B4, ClearedPuz;
objects g_sDoors[6], g_sTrigPlate[2], g_sBlock[2], g_sBullet[2], g_sBarrel;
COORD	Shooter[3] = { { 83,11 },{ 102,8 },{ 132,2 } };			//first 2 = traps bullet. other is Barrel
COORD	puzTraps[4] = { { 84,14 },{ 84,7 },{ 102,7 },{ 102,10 } };
COORD	doorz[6] = { { 9,13 },{ 59,27 },{ 30,13 },{ 80,25 },{ 73,16 },{ 87,2 } };
COORD	plates[2] = { { 7,28 },{ 43,24 } };
COORD	puzzleSwitch[9] = { { 92,12 },{ 98,9 },{ 87,9 },{ 92,6 },{ 87,12 },{ 98,12 },{ 92,9 },{ 87,6 },{ 98,6 } }; // first 4 opens door(by sequence) other 5 reset buttons
//

//Sufyan Vars
bool	visibility = false;
bool	gameover = false;
int		coinScore = 0;
int		totalScore = 0;
int		coinAmt = 0;

vector<string> DeathScreen;
vector<string> WinScreen;
vector<string> scoreboard;
vector<string> ruleScreen;
vector<string> menuScreen;

//

// Choi Poh Vars
bool	g_Door1_Close;
bool	g_Bat_Door_Close;
bool	g_Bat_Door_Close1;
bool	g_GeneraStatus;
bool	g_GeneraStatus1;
bool	ifBattery1True;
bool	switchOn;

int Batteries;
double puzTraptimer;

COORD g_sTele[28] = { { 79, 30 },{ 91, 22 },{ 91, 30 },{ 89, 21 },{ 109, 26 }, //T0, T1, T2, T3, T4
{ 100, 30 },{ 89, 25 },{ 100, 22 },{ 111, 21 },{ 93, 29 }, //T5, T6, T7, T8, T9
{ 111, 25 },{ 100, 26 },{ 91, 26 },{ 98, 21 },{ 102, 29 }, //T10, T11, T12, T13, T14
{ 98, 25 },{ 109, 22 },{ 93, 25 },{ 98, 29 },{ 102, 25 }, //T15, T16, T17, T18, T19
{ 102, 21 },{ 107, 25 },{ 107, 21 },{ 93, 21 },{ 109, 30 }, //T20, T21, T22, T23, T24
{ 111, 29 },{ 92, 16 },{ 84, 2 } }; //T25, T26, T27

double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once
// Console object
Console g_Console(160, 50, "SP1 Framework");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------

//Gary
void init(void)
{
	// character position
	g_sChar.m_cLocation.X = 2;	//2, 9
	g_sChar.m_cLocation.Y = 14;	//14, 98
	g_sChar.m_bActive = true;

	// sets the initial state for the game
	g_eGameState = S_MENU;

	// Set precision for floating point output
	g_dElapsedTime = 0.0;
	g_dBounceTime = 0.0;
	// 

	//Sufyan init

	Coin[0] = { 8 , 9 };
	Coin[1] = { 10 , 7 };
	Coin[2] = { 8 , 5 };
	Coin[3] = { 43 , 15 }; 
	Coin[4] = { 110 , 3 };
	Coin[5] = { 113 , 10 };
	Coin[6] = { 15 , 22 };
	Coin[7] = { 52 , 26 };
	Coin[8] = { 91 ,29 };
	Coin[9] = { 65 , 7 };


	//

	//PengYang Init
	//bool for objects
	doorClosed = true;
	doorClosed1 = true;
	isFired = false;
	barrels = false;
	B1 = true;
	B2 = true;
	B3 = true;
	B4 = true;
	ClearedPuz = false;
	//timer
	barrelRollTime = 0.0;
	S_Bullet = 0.0;
	//location of character & objects*
	g_sBlock[0].Loc.X = 3;
	g_sBlock[0].Loc.Y = 21;
	g_sBlock[1].Loc.X = 38;
	g_sBlock[1].Loc.Y = 21;
	g_sBarrel.Loc = Shooter[2];

	for (int i = 0; i <= 6; i++)
	{
		g_sDoors[i].Loc.X = 0;
		g_sDoors[i].Loc.Y = 0;
	}
	for (int d = 0; d <= 6; d++)
	{
		g_sDoors[d].Loc = doorz[d];				//throw coords to doors object
	}
	for (int i = 0; i <= 1; i++)
	{
		g_sTrigPlate[i].Loc.X = 0;
		g_sTrigPlate[i].Loc.Y = 0;
	}
	for (int d = 0; d <= 1; d++)
	{
		g_sTrigPlate[d].Loc = plates[d];		//throw coords to trigger plates object
	}
	for (int d = 0; d <= 1; d++)
	{
		g_sBullet[d].Loc = Shooter[d];		//throw coords to shooting trap object
	}

	//For Levers
	g_slever1.m_cLocation.X = 5;
	g_slever1.m_cLocation.Y = 2;
	g_slever1.m_bActive = true;

	//Gary init
	g_dEnemyTime1 = 0.0;
	g_dEnemyTime2 = 0.0;
	g_dEnemyTime3 = 0.0;
	g_dEnemyTime4 = 0.0;

	g_dTrapTime = 0.0;

	//loads map
	loadMap();
	loadMenuScreen();
	loadDeathScreen();
	loadWinScreen();
	loadScoreboard();
	loadRuleScreen();
	//

	//music , uncomment to play , comment to mute
	PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_LOOP | SND_NOSTOP | SND_ASYNC);

	//BOT POS Struct array.
	// X , Y , Step , Dir , Range
	BOT[0] = { 2 , 5 , 0 , 1 , 14 };
	BOT[1] = { 16 , 7 , 0 , -1 , 14 };
	BOT[2] = { 30 , 27 , 0 , 1 , 28 };
	BOT[3] = { 58 , 27 , 0 , -1 , 28 };
	BOT[4] = { 84 , 30 , 0 , -1 , 11 };
	BOT[5] = { 2 , 9 , 0 , 1 ,14 };
	BOT[6] = { 104 , 18 , 0 , 1 , 0 };
	BOT[7] = { 121 , 18 , 0 , 1 , 0 };
	BOT[8] = { 121 , 2 , 0 , 1 , 0 };
	//

	//Traps

	Trap[0] = { 121 , 4 , 0 , 18 };
	Trap[1] = { 121 , 8 , 0 , 18 };
	Trap[2] = { 121 , 12 , 0 , 18 };
	Trap[3] = { 121 , 16 , 0 , 18 };
	//-------------------------------------Choi Poh Init----------------------------------------------------
	
	//Declarations
	Batteries = 0;
	
	//-----Objects Coord-----

	//Batteries
	g_sBatteries.m_cLocation.X = 40; // ice battery 40 7
	g_sBatteries.m_cLocation.Y = 7;
	g_sBatteries.m_bActive = true;

	g_sBatteries1.m_cLocation.X = 73; // toggle battery sight 73 1
	g_sBatteries1.m_cLocation.Y = 1;
	g_sBatteries1.m_bActive = true;

	g_sBatteries2.m_cLocation.X = 86; // 9 switch battery 86 1
	g_sBatteries2.m_cLocation.Y = 1;
	g_sBatteries2.m_bActive = true;

	g_sBatteries3.m_cLocation.X = 9; //moving block door battery 9 1
	g_sBatteries3.m_cLocation.Y = 1;
	g_sBatteries3.m_bActive = true;

	g_sBatteries4.m_cLocation.X = 63; //moving block door battery 63 26
	g_sBatteries4.m_cLocation.Y = 26;
	g_sBatteries4.m_bActive = true;

	//Doors
	g_sDoor1.m_cLocation.X = 59;
	g_sDoor1.m_cLocation.Y = 26;

	g_sBatDoor.m_cLocation.X = 63; 
	g_sBatDoor.m_cLocation.Y = 18;

	g_sBatDoor1.m_cLocation.X = 102;
	g_sBatDoor1.m_cLocation.Y = 3;

	g_sBatDoor2.m_cLocation.X = 101;
	g_sBatDoor2.m_cLocation.Y = 16;

	//For Generator
	g_sGenerator.m_cLocation.X = 49;
	g_sGenerator.m_cLocation.Y = 20;

	g_sGenerator1.m_cLocation.X = 53;
	g_sGenerator1.m_cLocation.Y = 20;

	//For Levers
	g_slever1.m_cLocation.X = 43;
	g_slever1.m_cLocation.Y = 21;

	//-----bActives-----

	//Batteries
	g_sBatteries.m_bActive = true;
	g_sBatteries1.m_bActive = true;
	g_sBatteries2.m_bActive = true;
	g_sBatteries3.m_bActive = true;
	g_sBatteries4.m_bActive = true;

	//Generators
	g_sGenerator.m_bActive = true;
	g_sGenerator1.m_bActive = true;
	
	//Doors
	g_sDoor1.m_bActive = true;
	g_sBatDoor.m_bActive = true;
	g_sBatDoor1.m_bActive = true;
	g_sBatDoor2.m_bActive = true;

	//Levers
	g_slever1.m_bActive = true;

	//-----Bool Function-----
	g_Door1_Close = true;		//door1 close
	g_Bat_Door_Close = true;	//battery door close
	g_Bat_Door_Close1 = true;	//battery door close
	g_GeneraStatus = true;		// Generator 1 off
	g_GeneraStatus1 = true;		// Generator 2 off
	switchOn = false;
	//

	//----------------------------------------------------------------

    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------

void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------

void getInput( void )
{    
	g_abKeyPressed[K_UP] = isKeyPressed(0x57);
	g_abKeyPressed[K_DOWN] = isKeyPressed(0x53);
	g_abKeyPressed[K_LEFT] = isKeyPressed(0x41);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(0x44);
	g_abKeyPressed[K_BACK] = isKeyPressed(0x42);

	g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);

	g_abKeyPressed[K_ResetBox] = isKeyPressed(0x52);
	g_abKeyPressed[K_PAUSE] = isKeyPressed(0x50);

	//Demo Checkpointer
	g_abKeyPressed[K_One] = isKeyPressed(0x31);
	g_abKeyPressed[K_Two] = isKeyPressed(0x32);
	g_abKeyPressed[K_Three] = isKeyPressed(0x33);
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------

void update(double dt) // every delta time run this 
{
    // get the delta time
	g_dElapsedTime += dt;
	g_dDeltaTime = dt;
	S_Bullet += dt;
	barrelRollTime += dt;

	//Choi Poh
	puzTraptimer += dt;

    switch (g_eGameState)
    {
	case S_MENU: whileMenuScreen(); // game logic for the splash screen
		break;
	case S_RULES: whileRuleScreen(); // game logic for the splash screen
		break;
	case S_GAME: gameplay(); // gameplay logic when we are in the game
		break;
	case S_DEATHSCREEN: whileDeathScreen(); // game logic for death screen
		break;
	case S_WINSCREEN: whileWinScreen(); // Inputs while in the win screen
		break;
	case S_SCOREBOARD: whileScoreboard(); // Inputs while in the scoreboard screen.
		break;
    }
}

//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------

void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
	case S_MENU: renderMenuScreen(); // Start of the game (menu Screen)
		break;
	case S_RULES: renderRuleScreen();; // When player looks at rule (Rule Screen)
		break;
	case S_GAME: renderGame(); // Loads up the main part of the game
		break;
	case S_DEATHSCREEN: renderDeathScreen(); // When the player dies and use up all 3 lives (Death Screen)
		break;
	case S_WINSCREEN: renderWinScreen(); // When player reaches the end of the level (Win Screen)
		break;
	case S_SCOREBOARD: renderScoreboard(); // When player checks their scores at the end of the game (Scoreboard)
		break;
    }

    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

//void splashScreenWait()    // waits for time to pass in splash screen
//{
//    if (g_dElapsedTime > 5.0) // wait for 5 seconds to switch to game mode, else do nothing
//        g_eGameState = S_MENU;
//}

void gameplay()            // gameplay logic
{
	//----for different instances of speed----
	g_dEnemyTime1 += g_dDeltaTime; 
	g_dEnemyTime2 += g_dDeltaTime;
	g_dEnemyTime3 += g_dDeltaTime; 
	g_dEnemyTime4 += g_dDeltaTime;

	g_dTrapTime += g_dDeltaTime;

	//----------------------------------------

    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
	
    //Sufyan gameplay
	floorCollision();
	coinCollision();
	//

	//Gary gameplay
	moveAIS();
	moveTraps();
	//

	//ChoiPoh gameplay
	Levers();			// Lever for Door
	Collision();		// In-game Objects Collision
	gameBatteries();	// Batteries
	Teleporter();		// Teleporter function
	Checkpointer();
	timerSwitch();
	timerSwitchBool();
	//

	//PengYang gameplay
	puzzswitch();
	doorCheck();
	blocksMovement();
	trapShoot();
	rollerBarrel();
	//
}

//Choi Poh
void timerSwitch()
{
	if (g_sChar.m_cLocation.X == g_slever1.m_cLocation.X && g_sChar.m_cLocation.Y == g_slever1.m_cLocation.Y)
	{
		if (switchOn == false)
		{
			switchOn = true;
			puzTraptimer = 0.0;
		}
	}
}

//Choi Poh
void timerSwitchBool()
{
	if (switchOn == true)
	{
		if (puzTraptimer <= 25.0)
		{
			g_Door1_Close = false;
		}
		else if (puzTraptimer > 25.0)
		{
			switchOn = false;
		}
	}
	else if (!switchOn)
	{
		g_Door1_Close = true;
	}
}

//PY
void doorCheck()
{
	int pairChecker = 0;
	doorClosed = true;
	doorClosed1 = true;
	for (int p = 0; p <= 1; p++)        //checking which plates the character triggered
	{
		pairChecker++;
		if (g_sChar.m_cLocation.X == g_sTrigPlate[p].Loc.X && g_sChar.m_cLocation.Y == g_sTrigPlate[p].Loc.Y ||
			g_sBlock[p].Loc.X == g_sTrigPlate[p].Loc.X && g_sBlock[p].Loc.Y == g_sTrigPlate[p].Loc.Y)
		{
			switch (pairChecker)
			{
			case 1:
				if (g_sDoors[0].Loc.Y != (char)32 && g_sDoors[0].Loc.X != (char)32) //
				{
					map[g_sDoors[0].Loc.Y][g_sDoors[0].Loc.X] = (char)32;
					//g_Console.writeToBuffer(doorz[0], (char)32, 6);
					doorClosed = false;
				}
				break;
			case 2:
				if (g_sDoors[2].Loc.Y != (char)32 && g_sDoors[2].Loc.X != (char)32) //
				{
					map[g_sDoors[2].Loc.Y][g_sDoors[2].Loc.X] = (char)32;
					//g_Console.writeToBuffer(doorz[2], (char)32, 6);
					doorClosed1 = false;
				}
				break;
			}
		}
	}
}

void rollerBarrel()
{
	if (!barrels) {
		barrels = true;
	}

	if (barrels == true)
	{
		if (barrelRollTime >= 0.01 && g_sBarrel.Loc.Y == 2 && g_sBarrel.Loc.X > 124)
		{
			g_sBarrel.Loc.X--;
			barrelRollTime = 0.0;
		}
		else if (barrelRollTime >= 0.065 && g_sBarrel.Loc.Y < 5 && g_sBarrel.Loc.X == 124)
		{
			g_sBarrel.Loc.Y++;
			barrelRollTime = 0.0;
		}
		else if (barrelRollTime >= 0.065 && g_sBarrel.Loc.Y == 5 && g_sBarrel.Loc.X < 138)
		{
			g_sBarrel.Loc.X++;
			barrelRollTime = 0.0;
		}
		else if (barrelRollTime >= 0.065 && g_sBarrel.Loc.Y < 8 && g_sBarrel.Loc.X == 138)
		{
			g_sBarrel.Loc.Y++;
			barrelRollTime = 0.0;
		}
		else if (barrelRollTime >= 0.01 && g_sBarrel.Loc.Y == 8 && g_sBarrel.Loc.X > 123)
		{
			g_sBarrel.Loc.X--;
			barrelRollTime = 0.0;
		}
		else if (barrelRollTime >= 0.065 && g_sBarrel.Loc.Y < 11 && g_sBarrel.Loc.X == 123)
		{
			g_sBarrel.Loc.Y++;
			barrelRollTime = 0.0;
		}

		else if (barrelRollTime >= 0.065 && g_sBarrel.Loc.Y == 11 && g_sBarrel.Loc.X < 138)
		{
			g_sBarrel.Loc.X++;
			barrelRollTime = 0.0;
		}
		else if (barrelRollTime >= 0.065 && g_sBarrel.Loc.Y < 13 && g_sBarrel.Loc.X == 138)
		{
			g_sBarrel.Loc.Y++;
			barrelRollTime = 0.0;
		}
		else if (barrelRollTime >= 0.01 && g_sBarrel.Loc.Y == 13 && g_sBarrel.Loc.X > 123)
		{
			g_sBarrel.Loc.X--;
			barrelRollTime = 0.0;
		}
		else if (barrelRollTime >= 0.065 && g_sBarrel.Loc.Y < 15 && g_sBarrel.Loc.X == 123)
		{
			g_sBarrel.Loc.Y++;
			barrelRollTime = 0.0;
		}
		else if (barrelRollTime >= 0.065 && g_sBarrel.Loc.Y == 15 && g_sBarrel.Loc.X < 138)
		{
			g_sBarrel.Loc.X++;
			barrelRollTime = 0.0;
		}
		else if (barrelRollTime >= 0.065 && g_sBarrel.Loc.Y < 18 && g_sBarrel.Loc.X == 138)
		{
			g_sBarrel.Loc.Y++;
			barrelRollTime = 0.0;
		}
		else if (barrelRollTime >= 0.01 && g_sBarrel.Loc.Y == 18 && g_sBarrel.Loc.X > 124)
		{
			g_sBarrel.Loc.X--;
			barrelRollTime = 0.0;
		}
		else if (g_sBarrel.Loc.Y == 18 && g_sBarrel.Loc.X == 124) {
			g_sBarrel.Loc = { 132, 2 };
			barrels = false;
		}
	}
	if (g_sChar.m_cLocation.Y == g_sBarrel.Loc.Y && g_sChar.m_cLocation.X == g_sBarrel.Loc.X)
	{
		g_sChar.m_cLocation = { 123,18 };
		lifepoint--;
	}
}

void puzzswitch()
{
	if (!ClearedPuz)
	{
		if (g_sChar.m_cLocation.Y == (puzzleSwitch[0].Y + 1) && g_sChar.m_cLocation.X == puzzleSwitch[0].X)
		{
			if (g_abKeyPressed[K_SPACE])
			{
				B1 = false;
			}
		}
		if (!B1)
		{
			if (g_sChar.m_cLocation.Y == (puzzleSwitch[1].Y + 1) && g_sChar.m_cLocation.X == puzzleSwitch[1].X)
			{
				if (g_abKeyPressed[K_SPACE])
				{
					B2 = false;
				}
			}
		}
		if (!B2)
		{
			if (g_sChar.m_cLocation.Y == (puzzleSwitch[2].Y + 1) && g_sChar.m_cLocation.X == puzzleSwitch[2].X)
			{
				if (g_abKeyPressed[K_SPACE])
				{
					B3 = false;
				}
			}
		}
		if (!B3)
		{
			if (g_sChar.m_cLocation.Y == (puzzleSwitch[3].Y + 1) && g_sChar.m_cLocation.X == puzzleSwitch[3].X)
			{
				if (g_abKeyPressed[K_SPACE])
				{
					B4 = false;
					ClearedPuz = true;
				}
			}
		}

		for (int i = 4; i < 9; i++)
		{
			if (g_sChar.m_cLocation.Y == (puzzleSwitch[i].Y + 1) && g_sChar.m_cLocation.X == puzzleSwitch[i].X)
			{
				if (g_abKeyPressed[K_SPACE])
				{
					B1 = true;
					B2 = true;
					B3 = true;
					B4 = true;
				}
			}
		}
	}
}

void puzzTrigger()
{
	for (int s = 0; s < 9; s++) {
		g_Console.writeToBuffer(puzzleSwitch[s], (char)206, 7);
	}

	if (!B1) {
		g_Console.writeToBuffer(puzzleSwitch[0], (char)49, 5);
	}
	if (!B2) {
		g_Console.writeToBuffer(puzzleSwitch[1], (char)50, 5);
	}
	if (!B3) {
		g_Console.writeToBuffer(puzzleSwitch[2], (char)51, 5);
	}
	if (!B4) {
		g_Console.writeToBuffer(puzzleSwitch[3], (char)52, 5);
		map[doorz[5].Y][doorz[5].X] = (char)32;
		//g_Console.writeToBuffer(doorz[5], (char)32, 6);
	}

}

void trapShoot()	//trap shooter
{
	if (!isFired)
	{
		isFired = true;
	}
	if (isFired == true)		//move bullet
	{
		if (S_Bullet >= 0.111 && g_sBullet[0].Loc.X <= 102 && g_sBullet[1].Loc.X >= 84)
		{
			g_sBullet[0].Loc.X++;
			g_sBullet[1].Loc.X--;
			S_Bullet = 0.0;
			if (g_sBullet[0].Loc.X == 102 && g_sBullet[1].Loc.X == 83) //when bullet hits the end. reset
			{
				g_sBullet[0].Loc.X = 83;
				g_sBullet[1].Loc.X = 102;
				isFired = false;
			}
		}
	}

	for (int i = 0; i <= 1; i++)		//player take damage
	{
		if (g_sChar.m_cLocation.Y == g_sBullet[i].Loc.Y && g_sChar.m_cLocation.X == g_sBullet[i].Loc.X)
		{
			g_sChar.m_cLocation = { 92,14 };
			lifepoint--;
		}
	}
}

//sufyan -------- checking if the player steps off the wrong path in memory room ---------
void floorCollision()
{
	if (g_abKeyPressed[K_LEFT])
	{
		if (map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == (char)108)
		{
			g_sChar.m_cLocation.Y = 17;
			g_sChar.m_cLocation.X = 73;
			lifepoint -= 1;
		}
	}

	if (g_abKeyPressed[K_RIGHT])
	{
		if (map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == (char)108)
		{
			g_sChar.m_cLocation.Y = 17;
			g_sChar.m_cLocation.X = 73;
			lifepoint -= 1;
		}
	}

	if (g_abKeyPressed[K_DOWN])
	{
		if (map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == (char)108)
		{
			g_sChar.m_cLocation.Y = 17;
			g_sChar.m_cLocation.X = 73;
			lifepoint -= 1;
		}
	}

	if (g_abKeyPressed[K_UP])
	{
		if (map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == (char)108)
		{
			g_sChar.m_cLocation.Y = 17;
			g_sChar.m_cLocation.X = 73;
			lifepoint -= 1;
		}
	}
}

//sufyan -------- Death screen ( When the player uses up all 3 lives) --------
//
void renderDeathScreen()
{
	COORD a;
	COORD b;
	COORD c;

	int y = 0;
	int x = 0;
	for (int i = 0; i < DeathScreen.size(); i++)
	{
		a.X = x;
		a.Y = y;
		g_Console.writeToBuffer(a, DeathScreen[i], 12);
		y++;
	}

	b.X = 46;
	b.Y = 19;

	c.X = 50;
	c.Y = 21;

	g_Console.writeToBuffer(b, "How unlucky. Better luck next time.", 12);
	g_Console.writeToBuffer(c, "Press ESC to end the game");
}

void loadDeathScreen()
{
	//pushing text file into vector
	string line;
	ifstream deathscreenfile("deathscreen.txt");

	//storing text text file into vector string
	if (deathscreenfile.is_open())
	{
		while (getline(deathscreenfile, line))
		{
			DeathScreen.push_back(line);
		}
		deathscreenfile.close();
	}
}

void whileDeathScreen()
{
	processUserInput();
}
//

//sufyan -------- Score board ( shows the points for players at the end ) -------
//
void renderScoreboard()
{
	COORD a;
	COORD b;
	COORD c;
	COORD d;
	COORD e;
	COORD f;
	COORD g;
	COORD h;

	int y = 0;
	int x = 0;
	for (int i = 0; i < scoreboard.size(); i++)
	{
		a.X = x;
		a.Y = y;
		g_Console.writeToBuffer(a, scoreboard[i], 12);
		y++;
	}

	h.X = 32;
	h.Y = 17;

	b.X = 40;
	b.Y = 11;

	c.X = 40;
	c.Y = 12;

	d.X = 40;
	d.Y = 13;

	e.X = 40;
	e.Y = 14;

	f.X = 40;
	f.Y = 15;

	totalScore = coinScore;

	ostringstream str1;
	str1 << coinScore;
	string coinScore = str1.str();

	if (totalScore <= 4000)
	{
		g_Console.writeToBuffer(b, "1. Sufyan - 10000 ");
		g_Console.writeToBuffer(c, "2. Nelson - 8000 ");
		g_Console.writeToBuffer(d, "3. Choi Poh - 6000 ");
		g_Console.writeToBuffer(e, "4. Gary - 4000 ");
		g_Console.writeToBuffer(f, "5. You - ");
		g_Console.writeToBuffer(h, "You got last place. That is so very sad.");

		f.X += 9;

		for (int i = 0; i < coinScore.length(); i++)
		{
			g_Console.writeToBuffer(f, coinScore[i], 3);
			f.X++;
		}

	}

	else if (totalScore > 4000 && totalScore <= 6000)
	{
		f.X = 40;
		f.Y = 14;

		e.X = 40;
		e.Y = 15;

		h.X = 18;
		g_Console.writeToBuffer(b, "1. Sufyan - 10000 ");
		g_Console.writeToBuffer(c, "2. Nelson - 8000 ");
		g_Console.writeToBuffer(d, "3. Choi Poh - 6000 ");
		g_Console.writeToBuffer(f, "4. You - ");
		g_Console.writeToBuffer(e, "5. Gary - 4000 ");
		g_Console.writeToBuffer(h, "You got 4th place. Good job beating gary but bad job beating the rest.");

		f.X += 9;

		for (int i = 0; i < coinScore.length(); i++)
		{
			g_Console.writeToBuffer(f, coinScore[i], 3);
			f.X++;
		}

	}

	else if (totalScore > 6000 && totalScore <= 8000)
	{
		f.X = 40;
		f.Y = 13;

		d.X = 40;
		d.Y = 14;

		e.X = 40;
		e.Y = 15;

		h.X = 24;

		g_Console.writeToBuffer(b, "1. Sufyan - 10000 ");
		g_Console.writeToBuffer(c, "2. Nelson - 8000 ");
		g_Console.writeToBuffer(f, "3. You - ");
		g_Console.writeToBuffer(d, "4. Choi Poh - 6000 ");
		g_Console.writeToBuffer(e, "5. Gary - 4000 ");
		g_Console.writeToBuffer(h, "You got 3rd place! Its mediocre. Good job anyways.");

		f.X += 9;

		for (int i = 0; i < coinScore.length(); i++)
		{
			g_Console.writeToBuffer(f, coinScore[i], 3);
			f.X++;
		}
	}

	else if (totalScore > 8000 && totalScore <= 10000)
	{
		f.X = 40;
		f.Y = 12;

		c.X = 40;
		c.Y = 13;

		d.X = 40;
		d.Y = 14;

		e.X = 40;
		e.Y = 15;

		h.X = 16;

		g_Console.writeToBuffer(b, "1. Sufyan - 10000 ");
		g_Console.writeToBuffer(f, "2. You - ");
		g_Console.writeToBuffer(c, "3. Nelson - 8000 ");
		g_Console.writeToBuffer(d, "4. Choi Poh - 6000 ");
		g_Console.writeToBuffer(e, "5. Gary - 4000 ");
		g_Console.writeToBuffer(h, "You got 2nd place! You're amazing! But dare to challenge for a new high score?");

		f.X += 9;

		for (int i = 0; i < coinScore.length(); i++)
		{
			g_Console.writeToBuffer(f, coinScore[i], 3);
			f.X++;
		}
	}

	else if (totalScore > 10000)
	{
		f.X = 40;
		f.Y = 11;

		b.X = 40;
		b.Y = 12;

		c.X = 40;
		c.Y = 13;

		d.X = 40;
		d.Y = 14;

		e.X = 40;
		e.Y = 15;

		h.X = 27;

		g_Console.writeToBuffer(f, "1. You - ");
		g_Console.writeToBuffer(b, "2. Sufyan - 10000 ");
		g_Console.writeToBuffer(c, "3. Nelson - 8000 ");
		g_Console.writeToBuffer(d, "4. Choi Poh - 6000 ");
		g_Console.writeToBuffer(e, "5. Gary - 4000 ");
		g_Console.writeToBuffer(h, "You got 1st place! NEW HIGH SCORE! You're the best!");

		f.X += 9;

		for (int i = 0; i < coinScore.length(); i++)
		{
			g_Console.writeToBuffer(f, coinScore[i], 3);
			f.X++;
		}
	}
}

void loadScoreboard()
{
	string line;
	ifstream scoreboardfile("Scoreboard.txt");

	if (scoreboardfile.is_open())
	{
		while (getline(scoreboardfile, line))
		{
			scoreboard.push_back(line);
		}
		scoreboardfile.close();
	}
}

void whileScoreboard()
{
	processUserInput();
}
//

//sufyan --------------- Win Screen ( When player finishes the game )---------
void renderWinScreen()
{
	COORD a;
	COORD b;
	COORD c;

	int y = 0;
	int x = 0;
	for (int i = 0; i < WinScreen.size(); i++)
	{
		a.X = x;
		a.Y = y;
		g_Console.writeToBuffer(a, WinScreen[i], 12);
		y++;
	}

	b.X = 27;
	b.Y = 19;

	c.X = 30;
	c.Y = 21;

	g_Console.writeToBuffer(b, "Good job getting pass all that.");
	g_Console.writeToBuffer(c, " Let's see how you did!");

}

void loadWinScreen()
{
	string line;
	ifstream winscreenfile("winscreen.txt");

	if (winscreenfile.is_open())
	{
		while (getline(winscreenfile, line))
		{
			WinScreen.push_back(line);
		}
		winscreenfile.close();
	}
}

void whileWinScreen()
{
	processUserInput();

	if (g_abKeyPressed[K_SPACE])
	{
		g_eGameState = S_SCOREBOARD;
	}
}

// Sufyan ---------- Menu Screen ( Screen for Start of the game ) --------
//
void loadMenuScreen()
{
	string line;
	ifstream myfile("menu.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			menuScreen.push_back(line);
		}
		myfile.close();
	}
}

void renderMenuScreen()
{
	COORD a;

	int y = 0;
	int x = 0;
	for (int i = 0; i < menuScreen.size(); i++)
	{
		a.X = x;
		a.Y = y;
		g_Console.writeToBuffer(a, menuScreen[i], 12);
		y++;
	}
}

void whileMenuScreen()
{
	if (g_abKeyPressed[K_SPACE])
	{
		g_eGameState = S_GAME;
	}

	if (g_abKeyPressed[K_ESCAPE])
	{
		g_bQuitGame = true;
	}

	if (g_abKeyPressed[K_ResetBox])
	{
		g_eGameState = S_RULES;
	}
}
//

// Sufyan --------- Rule Screen ( Rules of the game for the players ) -----
//
void loadRuleScreen()
{
	string line;
	ifstream rulescreen("ruleScreen.txt");

	if (rulescreen.is_open())
	{
		while (getline(rulescreen, line))
		{
			ruleScreen.push_back(line);
		}
		rulescreen.close();
	}
}

void renderRuleScreen()
{
	COORD a;
	COORD b;

	int y = 0;
	int x = 0;

	for (int i = 0; i < ruleScreen.size(); i++)
	{
		a.X = x;
		a.Y = y;
		g_Console.writeToBuffer(a, ruleScreen[i], 12);
		y++;

	}

	b.X = 52;
	b.Y = 39;

	g_Console.writeToBuffer(b, "| Press B to return to the main menu |");
}

void whileRuleScreen()
{
	processUserInput();

	if (g_abKeyPressed[K_BACK])
	{
		g_eGameState = S_MENU;
	}

}
//

void doorCollision()
{
	if (g_abKeyPressed[K_UP])
	{
		if (map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == (char)68 || map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == (char)90)
		{
			g_sChar.m_cLocation.Y++;
		}
	}
	else if (g_abKeyPressed[K_LEFT])
	{
		if (map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == (char)68 || map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == (char)90)
		{
			g_sChar.m_cLocation.X++;
		}
	}
	else if (g_abKeyPressed[K_DOWN])
	{
		if (map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == (char)68 || map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == (char)90)
		{
			g_sChar.m_cLocation.Y--;
		}
	}
	else if (g_abKeyPressed[K_RIGHT])
	{
		if (map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == (char)68 || map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == (char)90)
		{
			g_sChar.m_cLocation.X--;
		}
	}
}

void blocksMovement() {
	//detect if player collide with block
	for (int b = 0; b < 2; b++) {
		if (g_sBlock[b].Loc.Y == g_sChar.m_cLocation.Y && g_sBlock[b].Loc.X == g_sChar.m_cLocation.X)
		{
			//check if which movement key is pressed then check if block is touching wall. if no, player push block. if yes, player cannot push
			if (g_abKeyPressed[K_UP])
			{
				if (map[g_sBlock[b].Loc.Y - 1][g_sBlock[b].Loc.X] != (char)219)
				{
					g_sBlock[b].Loc.Y--;
				}
				else
				{
					g_sChar.m_cLocation.Y++;
				}
			}
			else if (g_abKeyPressed[K_LEFT])
			{
				if (map[g_sBlock[b].Loc.Y][g_sBlock[b].Loc.X - 1] != (char)219)
				{
					g_sBlock[b].Loc.X--;
				}
				else
				{
					g_sChar.m_cLocation.X++;
				}
			}
			else if (g_abKeyPressed[K_DOWN])
			{
				if (map[g_sBlock[b].Loc.Y + 1][g_sBlock[b].Loc.X] != (char)219)
				{
					g_sBlock[b].Loc.Y++;
				}
				else
				{
					g_sChar.m_cLocation.Y--;
				}
			}
			else if (g_abKeyPressed[K_RIGHT])
			{
				if (map[g_sBlock[b].Loc.Y][g_sBlock[b].Loc.X + 1] != (char)219)
				{
					g_sBlock[b].Loc.X++;
				}
				else
				{
					g_sChar.m_cLocation.X--;
				}
			}
		}
	}
}

//sufyan -------- check if player collides with coins ---------
void coinCollision()
{
	COORD a;
	for (int i = 0; i < 10; i++)
	{
		a.X = Coin[i].xpos;
		a.Y = Coin[i].ypos;

		if (g_sChar.m_cLocation.X == Coin[i].xpos && g_sChar.m_cLocation.Y == Coin[i].ypos)
		{
			g_Console.writeToBuffer(a , (char)32, 0);
			Coin[i].xpos = 1;
			Coin[i].ypos = 0;
			coinAmt += 1;
		}
	}
	// Final coinScore
	coinScore = coinAmt * 1500;
}

void moveCharacter()
{
	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	//Testing for death against Traps [red !!]
	if ((map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == (char)30))
	{
		lifepoint -= 1;
		g_sChar.m_cLocation.X = startingpointx;
		g_sChar.m_cLocation.Y = startingpointy;
	}

	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character

	if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0)
	{
		//Checking for slipping motion.
		while (true)
		{
			if (map[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == (char)8)
			{
				g_sChar.m_cLocation.Y--;
			}
			else break;
		}
		//Collision against wall.
		if (map[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != (char)219)
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;
		}
	}

	if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0)
	{
		//Checking for slipping motion.
		while (true)
		{
			if (map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] == (char)8)
			{
				g_sChar.m_cLocation.X--;
			}
			else break;
		}

		//Collision against wall.
		if (map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != (char)219)
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.X--;
			bSomethingHappened = true;
		}
	}

	if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		//Checking for slipping motion.
		while (true)
		{
			if (map[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] == (char)8)
			{
				g_sChar.m_cLocation.Y++;
			}
			else break;
		}
		//Collision against wall.
		if (map[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != (char)219)
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.Y++;
			bSomethingHappened = true;
		}
	}

	if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		//Checking for slipping motion.
		while (true)
		{
			if (map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] == (char)8)	//----------check if character next pos not wall & not door then move----------
			{
				g_sChar.m_cLocation.X++;
			}
			else break;
		}
		//Collision against wall.
		if (map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != (char)219)
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.X++;
			bSomethingHappened = true;
		}
	}

	if (g_abKeyPressed[K_SPACE])
	{
		g_sChar.m_bActive = !g_sChar.m_bActive;
		bSomethingHappened = true;
	}

	if (g_abKeyPressed[K_PAUSE])
	{
		getch();
	}

	if (bSomethingHappened) //after something happens
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}

	if (g_abKeyPressed[K_ResetBox])
	{
		g_sBlock[0].Loc.X = 4;
		g_sBlock[0].Loc.Y = 25;
		g_sBlock[1].Loc.X = 38;
		g_sBlock[1].Loc.Y = 21;

		bSomethingHappened = true;
	}
}

void Teleporter()
{
	for (int i = 0; i < 28; i++)
	{
		if (g_sChar.m_cLocation.X == g_sTele[i].X && g_sChar.m_cLocation.Y == g_sTele[i].Y)
		{
			g_sChar.m_cLocation.X = g_sTele[i + 1].X;
			g_sChar.m_cLocation.Y = g_sTele[i + 1].Y -1;
		}
	}

	if (g_sChar.m_cLocation.X == g_sTele[28].X && g_sChar.m_cLocation.X == g_sTele[28].X)
	{
		g_sChar.m_cLocation.X = g_sTele[0].X + 1;
		g_sChar.m_cLocation.Y = g_sTele[0].Y;
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------

void gameBatteries()
{
	//Bat 1
	if (g_sChar.m_cLocation.X == g_sBatteries.m_cLocation.X  && g_sChar.m_cLocation.Y == g_sBatteries.m_cLocation.Y + 1)
	{
		Batteries++;
		g_sBatteries.m_cLocation.Y = 100;
	}
	//Bat 2
	if (g_sChar.m_cLocation.X == g_sBatteries1.m_cLocation.X && g_sChar.m_cLocation.Y == g_sBatteries1.m_cLocation.Y + 1)
	{
		Batteries++;
		g_sBatteries1.m_cLocation.Y = 100;
	}
	//Bat 3
	if (g_sChar.m_cLocation.X == g_sBatteries2.m_cLocation.X && g_sChar.m_cLocation.Y == g_sBatteries2.m_cLocation.Y + 1)
	{
		Batteries++;
		g_sBatteries2.m_cLocation.Y = 100;
	}
	//Bat 4
	if (g_sChar.m_cLocation.X == g_sBatteries3.m_cLocation.X && g_sChar.m_cLocation.Y == g_sBatteries3.m_cLocation.Y + 1)
	{
		Batteries++;
		g_sBatteries3.m_cLocation.Y = 100;
	}
	//Bat 5
	if (g_sChar.m_cLocation.X == g_sBatteries4.m_cLocation.X && g_sChar.m_cLocation.Y == g_sBatteries4.m_cLocation.Y + 1)
	{
		Batteries++;
		g_sBatteries4.m_cLocation.Y = 100;
		puzTraptimer = 0.0;
	}

}

//Choi Poh
void Levers()
{
	if (g_sChar.m_cLocation.X == g_slever1.m_cLocation.X && g_sChar.m_cLocation.Y == g_slever1.m_cLocation.Y)
	{
		g_Door1_Close = false;
	}
}

//Choi Poh
void Collision()
{
	if (g_Door1_Close == true)
	{
		if (g_sChar.m_cLocation.Y == g_sDoor1.m_cLocation.Y + 1 && g_sChar.m_cLocation.X == g_sDoor1.m_cLocation.X)
		{
			if (g_abKeyPressed[K_UP])
			{
				if (map[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != (char)68)
				{
					g_sChar.m_cLocation.Y++;
				}
			}
			else if (g_abKeyPressed[K_LEFT])
			{
				if (map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != (char)68)
				{
					g_sChar.m_cLocation.X++;
				}

			}
			else if (g_abKeyPressed[K_DOWN])
			{
				if (map[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != (char)68)
				{
					g_sChar.m_cLocation.Y--;
				}
			}
			else if (g_abKeyPressed[K_RIGHT])
			{
				if (map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != (char)68)
				{
					g_sChar.m_cLocation.X--;
				}
			}
		}
	}

	if (g_Bat_Door_Close == true || g_Bat_Door_Close1 == true)
	{
		if (g_sChar.m_cLocation.Y == g_sBatDoor.m_cLocation.Y && g_sChar.m_cLocation.X == g_sBatDoor.m_cLocation.X || g_sChar.m_cLocation.Y == g_sBatDoor1.m_cLocation.Y && g_sChar.m_cLocation.X == g_sBatDoor1.m_cLocation.X || g_sChar.m_cLocation.Y == g_sBatDoor2.m_cLocation.Y && g_sChar.m_cLocation.X == g_sBatDoor2.m_cLocation.X)
		{
			if (g_abKeyPressed[K_UP])
			{
				if (map[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != (char)69)
				{
					g_sChar.m_cLocation.Y++;
				}
			}
			else if (g_abKeyPressed[K_LEFT])
			{
				if (map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != (char)69)
				{
					g_sChar.m_cLocation.X++;
				}

			}
			else if (g_abKeyPressed[K_DOWN])
			{
				if (map[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != (char)69)
				{
					g_sChar.m_cLocation.Y--;
				}
			}
			else if (g_abKeyPressed[K_RIGHT])
			{
				if (map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != (char)69)
				{
					g_sChar.m_cLocation.X--;
				}
			}
		}
	}

	if (g_GeneraStatus == false || g_GeneraStatus1 == false || g_GeneraStatus == true || g_GeneraStatus1 == true)
	{
		if (g_sChar.m_cLocation.Y == g_sGenerator.m_cLocation.Y && g_sChar.m_cLocation.X == g_sGenerator.m_cLocation.X || g_sChar.m_cLocation.Y == g_sGenerator1.m_cLocation.Y && g_sChar.m_cLocation.X == g_sGenerator1.m_cLocation.X)
		{
			if (g_abKeyPressed[K_UP])
			{
				if (map[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] != (char)158)
				{
					g_sChar.m_cLocation.Y++;
				}
			}
			else if (g_abKeyPressed[K_LEFT])
			{
				if (map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X - 1] != (char)158)
				{
					g_sChar.m_cLocation.X++;
				}

			}
			else if (g_abKeyPressed[K_DOWN])
			{
				if (map[g_sChar.m_cLocation.Y + 1][g_sChar.m_cLocation.X] != (char)158)
				{
					g_sChar.m_cLocation.Y--;
				}
			}
			else if (g_abKeyPressed[K_RIGHT])
			{
				if (map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X + 1] != (char)158)
				{
					g_sChar.m_cLocation.X--;
				}
			}
		}
	}
}

//Gary
void moveAIS() // movement of AI
{
	//-------------------------------Bot 1 , 2 & 6 movement------------------------------------------

	for (int i = 0; i < 10; i++)
	{
		if (g_sChar.m_cLocation.X == BOT[i].xpos && g_sChar.m_cLocation.Y == BOT[i].ypos)
		{
			if (i == 6 || i == 7 || i == 8)
			{
				g_sChar.m_cLocation.X = 103; //setting player spawnpoint set to 1
				g_sChar.m_cLocation.Y = 3;
				lifepoint -= 1;
			}
			else if (i != 4 && i != 6 && i != 7)
			{
				g_sChar.m_cLocation.X = checkpoint1X; //setting player spawnpoint set to 1
				g_sChar.m_cLocation.Y = checkpoint1Y;
				lifepoint -= 1;
			}
			
			else
			{
				g_sChar.m_cLocation.X = 84; //setting player spawnpoint set to 1
				g_sChar.m_cLocation.Y = 17;
				lifepoint -= 1;
			}
		}
	}

	//Tracking AI for bot 6 ,7  & 8

	if (g_sChar.m_cLocation.X > 103 && g_sChar.m_cLocation.X < 122) // X range for AI
	{
		if (g_sChar.m_cLocation.Y > 1 && g_sChar.m_cLocation.Y < 20) // Y range for AI
		{
			if (g_dEnemyTime4 >= 0.18) //Speed
			{
				for (int i = 0; i < 10; i++) // loop
				{
					if (i == 6 || i == 7 || i == 8) // AI's that are tracking 
					{
						if (BOT[i].xpos < g_sChar.m_cLocation.X)
						{
							BOT[i].xpos += 1;
						}
						else if (BOT[i].xpos > g_sChar.m_cLocation.X)
						{
							BOT[i].xpos -= 1;
						}
						else if (BOT[i].ypos < g_sChar.m_cLocation.Y)
						{
							BOT[i].ypos += 1;
						}
						else if (BOT[i].ypos > g_sChar.m_cLocation.Y)
						{
							BOT[i].ypos -= 1;
						}
						g_dEnemyTime4 = 0.0;
					}
				}
			}
		}
	}
	else //Reseting AI position
	{
		BOT[6] = { 104 , 18 , 0 , 1 , 0 };
		BOT[7] = { 121 , 18 , 0 , 1 , 0 };
		BOT[8] = { 121 , 2 , 0 , 1 , 0 };
	}

	// Throw structure and bot number into the function , MovingAI.
	if (g_dEnemyTime1 >= 0.03)  // how fast the enemy moves
	{
		MovingAI(BOT, 0);
		MovingAI(BOT, 1);
		MovingAI(BOT, 5);
		g_dEnemyTime1 = 0;
	}

	//----------------------------------------Bot 3 & 4 movemement--------------------------------------------------
	if (g_dEnemyTime2 >= 0.035)  // how fast the enemy moves
	{
		MovingAI(BOT, 2);
		MovingAI(BOT, 3);
		g_dEnemyTime2 = 0.0;
	}

	//----------------------------------------Bot 5 movement [vertical] ---------------------------------------------------
	if (g_dEnemyTime3 >= 0.05)
	{
		g_dEnemyTime3 = 0.0;
		MovingAI(BOT, 4);
	}
}

void moveTraps()
{
	//Collision test for traps
	for (int i = 0; i < 10; i++)
	{
		//if player Y  = Trap Y and Player x is more than trap xpos - step
		if (g_sChar.m_cLocation.Y == Trap[i].ypos && (g_sChar.m_cLocation.X >= Trap[i].xpos - Trap[i].step && g_sChar.m_cLocation.X <= Trap[i].xpos)) // if player location == y location of trap 
		{
			lifepoint -= 1;
			g_sChar.m_cLocation.X = 103;
			g_sChar.m_cLocation.Y = 3;
		}
	}

	if (g_dTrapTime >= 0.1)
	{
		for (int i = 0; i < 10; i++)
		{
			Trap[i].step++; //increasing step everytime it loops through
			g_dTrapTime = 0.0;

			if (Trap[i].step >= Trap[i].range)
			{
				Trap[i].step = 0;
			}
		}
	}
}

void processUserInput()
{
	// quits the game if player hits the escape key
	if (g_abKeyPressed[K_ESCAPE])
	{
		g_bQuitGame = true;
	}
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x00);
}

void loadTextScreen()
{
	//pushing text file into vector
	string line;
	ifstream myfile("loading.txt");

	//storing text text file into vector string
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			menuScreen.push_back(line);
		}
		myfile.close();
	}
}

// Sufyan ------ Pathway for invisible room
void renderVisibility()
{
	COORD a;

	a.X = 78;
	a.Y = 34;

	// if the player steps on the 's' switch, the path will render in the rendermap function.
	if (map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == '!')
	{
		visibility = true;
	}
	else
	{
		visibility = false;
	}

	// text for invisble room
	if (g_sChar.m_cLocation.X == 71 && g_sChar.m_cLocation.Y == 17)
	{
		g_Console.writeToBuffer(a, "This is a the invisible room. The '!' will light up the path", 15);
		a.Y += 1;
		g_Console.writeToBuffer(a, "   To activate them, simply move your character towards it.", 15);
		a.Y += 1;
		g_Console.writeToBuffer(a, "     Should you touch the red path, you will lose 1 life.", 15);
	}
}

//sufyan ----- Draw the coins
void renderCoins()
{
	COORD a;
	for (int i = 0; i < 10; i++)
	{
		a.X = Coin[i].xpos;
		a.Y = Coin[i].ypos;
		g_Console.writeToBuffer(a , '*', 3);
	}
}

void renderAIS() //All the AIS
{
	COORD a; // bot 1

	for (int i = 0; i < 9; i++)
	{
		a.X = BOT[i].xpos;
		a.Y = BOT[i].ypos;
		g_Console.writeToBuffer(a, 197, 12);
	}
}

void renderTraps()
{
	COORD a;

	for (int j = 0; j < 10; j++)
	{
		a.X = Trap[j].xpos;
		a.Y = Trap[j].ypos;

		for (int i = 0; i <= Trap[0].step; i++) // loops for how many steps
		{
			g_Console.writeToBuffer(a, 174, 12);
			a.X--;
		}
	}
}

//Choi Poh
void Checkpointer(void)
{
	if (g_abKeyPressed[K_One])
	{
		g_sChar.m_cLocation.X = 2;
		g_sChar.m_cLocation.Y = 14;
	}

	if (g_abKeyPressed[K_Two])
	{
		g_sChar.m_cLocation.X = 51;
		g_sChar.m_cLocation.Y = 14;
	}

	if (g_abKeyPressed[K_Three])
	{
		g_sChar.m_cLocation.X = 84;
		g_sChar.m_cLocation.Y = 18;
	}
}

void renderGame()
{
    renderMap();        // gary
	renderAIS();        //gary
	renderTraps();
	renderlives();      //gary

	//Choi poh
	renderLever();
	renderDoor();		
	renderBatDoor();
	renderText();		
	renderBatteries();	
	renderGenerator();
	//

	//PengYang
	doorCollision();	
	puzzTrigger();		
	overwriteDoor();
	renderbullet();
	//

	//Sufyan
	renderVisibility(); 
	renderCoins();	
	//
	renderCharacter(); 
}

void loadMap()
{
	//pushing text file into vector
	string line;
	ifstream myfile("map.txt");

	//storing text text file into vector string
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (int i = 0; i < line.length(); i++)
			{
				if (line[i] == '#')
				{
					line[i] = 219;
				}
				if (line[i] == 's')
				{
					line[i] = 8;
				}
				if (line[i] == 'z')
				{
					line[i] = 30;
				}
			}
			map.push_back(line);
		}
		myfile.close();
	}
}

void renderMap()
{
	COORD d;
	
	COORD k;
	// render 
	for (int j = 0; j < map.size(); j++) //y axis
	{
		for (int i = 0; i < map[j].size(); i++)  //x axis
		{

			if ((map[j])[i] == ((char)219)) // if character is a wall
			{
				g_Console.writeToBuffer({(SHORT) i, (SHORT)j }, 219 , 14);  //print out walls
			}
			
			else if ((map[j])[i] == ((char)8)) // if character is ice
			{
				g_Console.writeToBuffer({ (SHORT)i, (SHORT)j }, 8, 3);      //print out ice 
			}

			else if ((map[j])[i] == ((char)30)) // if character is trap       
			{
				g_Console.writeToBuffer({ (SHORT)i, (SHORT)j }, 30, 4);     // printing trap
			}

			else if ((map[j])[i] == ((char)84)) //if teleporter      
			{
				g_Console.writeToBuffer({ (SHORT)i, (SHORT)j }, 64, 10);     // printing teleporter
			}
			
			else if ((map[j])[i] == ((char)48)) // if character is stopper       
			{
				g_Console.writeToBuffer({ (SHORT)i, (SHORT)j }, 48, 6);     // printing stopper [prevent slipping on ice]
			}
			else if ((map[j])[i] == ((char)120)) // if character is stopper       
			{
				g_Console.writeToBuffer({ (SHORT)i, (SHORT)j }, 219 , 7);     // printing instructions
			}

			else if ((map[j])[i] == 'D') // Door
			{
				g_Console.writeToBuffer({ (SHORT)i, (SHORT)j }, 178, 6);
			}

			else if ((map[j])[i] == ((char)88)) // plates
			{
				g_Console.writeToBuffer({ (SHORT)i, (SHORT)j }, 202, 11);
			}

			else if ((map[j])[i] == ((char)108)) // if character is 108
			{
				if (visibility == true)
				{
					g_Console.writeToBuffer({ (SHORT)i, (SHORT)j }, 108, 12);
				}
				else if (visibility == false)
				{
					g_Console.writeToBuffer({ (SHORT)i, (SHORT)j }, 108, 0);
				}
			}

			else 
			{                                                                 
				g_Console.writeToBuffer({ (SHORT)i, (SHORT)j }, (map[j][i]), 10); //printing anything else that hasnt been mentioned as the following
			}
		}
	}

	//-----------------------------------------------------Legend area---------------------------------------------------
	//legend monster

	//legend door
	d.X = 120;
	d.Y = 20;

	g_Console.writeToBuffer(d, 234, 15);
	d.X += 1;
	g_Console.writeToBuffer(d, " = Battery", 15);

	d.X = 120;
	d.Y = 22;

	g_Console.writeToBuffer(d, 158, 15);
	d.X += 1;
	g_Console.writeToBuffer(d, " = Generator", 15);

	d.X = 120;
	d.Y = 24;

	g_Console.writeToBuffer(d, 64, 10);
	d.X += 1;
	g_Console.writeToBuffer(d, " = Teleporter", 10);

	d.X = 120;
	d.Y = 26;

	g_Console.writeToBuffer(d, 178, 6);
	d.X += 1;
	g_Console.writeToBuffer(d, " = Door", 6);

	//legend switch

	d.X = 120;
	d.Y = 28;

	g_Console.writeToBuffer(d, 202, 11);
	d.X += 1;

	g_Console.writeToBuffer(d, " = switch", 11);

	//legend movable block

	d.X = 120;
	d.Y = 30;

	g_Console.writeToBuffer(d, 254, 8);
	d.X += 1;

	g_Console.writeToBuffer(d, " = moving block", 8);


	d.X = 2;
	d.Y = 34;
	g_Console.writeToBuffer(d, "Press 'P' To pause the game and any other key to resume", 7);
	d.Y += 1;
	g_Console.writeToBuffer(d, "Anything red kills you", 12);

	string cordx;
	string cordy;

	//coin indicator
	k.X = 2;
	k.Y = 37;

	g_Console.writeToBuffer(k, 42, 3);
	k.X += 2;
	g_Console.writeToBuffer(k, " , Coins Collected : ", 3);
	k.X += 21;

	ostringstream str1;
	str1 << coinAmt;
	string coinstr = str1.str();

	for (int i = 0; i < coinstr.length(); i++)
	{
		g_Console.writeToBuffer(k, coinstr[i], 3);
		k.X++;
	}

}

void renderLever()
{
	WORD LeverColor = 0x0F;
	COORD a;

	a.X = g_slever1.m_cLocation.X;
	a.Y = g_slever1.m_cLocation.Y;

	g_Console.writeToBuffer(a, (char)79, LeverColor);
}

void renderCharacter() //printing characters every frame
{
	COORD c , d;

	//Draw moveable blocks
	WORD blockColor = 0x08;
	c.X = g_sBlock[0].Loc.X;
	c.Y = g_sBlock[0].Loc.Y;
	d.X = g_sBlock[1].Loc.X;
	d.Y = g_sBlock[1].Loc.Y;
	g_Console.writeToBuffer(c, (char)254, blockColor);
	g_Console.writeToBuffer(d, (char)254, blockColor);

	c.X = g_sChar.m_cLocation.X;
	c.Y = g_sChar.m_cLocation.Y ;
	
    g_Console.writeToBuffer(c, 12, 15);

	//sufyan ---- Check if player reaches the end of the maze
	if (g_sChar.m_cLocation.X == 139 && g_sChar.m_cLocation.Y == 2)
	{
		g_sChar.m_cLocation.X = 0;
		g_sChar.m_cLocation.Y = 0;
		g_eGameState = S_WINSCREEN;
	}
}

void renderbullet()
{
	g_Console.writeToBuffer(g_sBarrel.Loc, (char)233, 4);
	g_Console.writeToBuffer(g_sBullet[0].Loc, (char)45, 4);
	g_Console.writeToBuffer(g_sBullet[1].Loc, (char)45, 4);
}

//-----Choi Poh-----
void renderDoor()
{
	WORD doorColor = 0x0F;

	COORD c;

	//Door for Switches
	c.X = g_sDoor1.m_cLocation.X;
	c.Y = g_sDoor1.m_cLocation.Y + 1;

	if (g_Door1_Close == true)
	{
		g_Console.writeToBuffer(c, (char)68, doorColor);
	}
	else
	{
		g_Console.writeToBuffer(c, (char)32);
	}
}

void renderBatDoor()
{
	WORD doorColor = 0x0F;

	COORD a, b, c;

	a.X = g_sBatDoor.m_cLocation.X;
	a.Y = g_sBatDoor.m_cLocation.Y;

	b.X = g_sBatDoor1.m_cLocation.X;
	b.Y = g_sBatDoor1.m_cLocation.Y;

	c.X = g_sBatDoor2.m_cLocation.X;
	c.Y = g_sBatDoor2.m_cLocation.Y;

	if (g_Bat_Door_Close == true)
	{
		g_Console.writeToBuffer(a, (char)69, doorColor);
	}
	else
	{
		g_Console.writeToBuffer(a, (char)32, doorColor);
		g_sBatDoor.m_cLocation.X = 1;
		g_sBatDoor.m_cLocation.Y = 100;

	}

	if (g_Bat_Door_Close1 == true)
	{
		g_Console.writeToBuffer(b, (char)69, doorColor);
		g_Console.writeToBuffer(c, (char)69, doorColor);
	}
	else
	{
		g_Console.writeToBuffer(b, (char)32, doorColor);
		g_Console.writeToBuffer(c, (char)32, doorColor);
	}
}

void renderBatteries()
{
	WORD BatteriesColor = 0x0F;


	//Declaration for Batteries
	COORD a , b , c , d ,e;
	
	a.X = g_sBatteries.m_cLocation.X;
	a.Y = g_sBatteries.m_cLocation.Y + 1;

	b.X = g_sBatteries1.m_cLocation.X;
	b.Y = g_sBatteries1.m_cLocation.Y + 1;

	c.X = g_sBatteries2.m_cLocation.X;
	c.Y = g_sBatteries2.m_cLocation.Y + 1;

	d.X = g_sBatteries3.m_cLocation.X;
	d.Y = g_sBatteries3.m_cLocation.Y + 1;

	e.X = g_sBatteries4.m_cLocation.X;
	e.Y = g_sBatteries4.m_cLocation.Y + 1;

	g_Console.writeToBuffer(a, (char)234, BatteriesColor);

	g_Console.writeToBuffer(b, (char)234, BatteriesColor);

	g_Console.writeToBuffer(c, (char)234, BatteriesColor);

	g_Console.writeToBuffer(d, (char)234, BatteriesColor);

	g_Console.writeToBuffer(e, (char)234, BatteriesColor);
}

void renderText()
{
	std::ostringstream ss;
	COORD c = g_Console.getConsoleSize();
	c.Y = 35;
	c.X = 99;

	//Switch Texts
	if (g_sChar.m_cLocation.X == g_slever1.m_cLocation.X && g_sChar.m_cLocation.Y == g_slever1.m_cLocation.Y)
	{
		g_Console.writeToBuffer(c, "You have Opened a Door", 15);
	}
	
	if (puzTraptimer < 25.0 && switchOn == true)
	{
		ss.str("");
		ss << "Door Time : " << puzTraptimer;
		c.Y = 38;
		c.X = 2;
		g_Console.writeToBuffer(c, ss.str(), 15);
	}
	else
	{

	}

	c.Y = 34;
	c.X = 82;
	
	if (g_sChar.m_cLocation.X == 92 && g_sChar.m_cLocation.Y == 15)
	{
		g_Console.writeToBuffer(c, "  This is a key room. Press spacebar at the crosses", 15);
		c.Y += 1;
		g_Console.writeToBuffer(c, " To activate them. Activating 4 in the correct order", 15);
		c.Y += 1;
		g_Console.writeToBuffer(c, "Opens the door above you. Getting it wrong resets them", 15);
	} 

	//-----------------------------------Batteries Text----------------------------------------- 
	COORD d = g_Console.getConsoleSize();
	d.Y = 36;
	d.X = 2;

	//Battery Text
	if (Batteries == 0)
	{
		g_Console.writeToBuffer(d, "Batteries : 0", 0x03);
	}
	else if (Batteries == 1)
	{
		g_Console.writeToBuffer(d, "Batteries : 1", 0x03);
	}
	else if (Batteries == 2)
	{
		g_Console.writeToBuffer(d, "Batteries : 2", 0x03);
	}
	else if (Batteries == 3)
	{
		g_Console.writeToBuffer(d, "Batteries : 3", 0x03);
	}
	else if (Batteries == 4)
	{
		g_Console.writeToBuffer(d, "Batteries : 4", 0x03);
	}
	else if (Batteries == 5)
	{
		g_Console.writeToBuffer(d, "Batteries : 5", 0x03);
	}
	else
	{
		g_Console.writeToBuffer(d, "Batteries : 0", 0x03);
	}

	//Generator 1 text
	COORD e;
	e.Y = 35;
	e.X = 90;

	COORD f;
	f.Y = 36;
	f.X = 94;

	//Generator 2 text

	COORD g;
	g.Y = 36;
	g.X = 92;

	COORD h;
	h.Y = 36;
	h.X = 92;

	if (g_sChar.m_cLocation.X == g_sGenerator.m_cLocation.X && g_sChar.m_cLocation.Y == g_sGenerator.m_cLocation.Y - 1 ||
		g_sChar.m_cLocation.X == g_sGenerator.m_cLocation.X && g_sChar.m_cLocation.Y == g_sGenerator.m_cLocation.Y + 1 ||
		g_sChar.m_cLocation.X == g_sGenerator.m_cLocation.X + 1 && g_sChar.m_cLocation.Y == g_sGenerator.m_cLocation.Y ||
		g_sChar.m_cLocation.X == g_sGenerator.m_cLocation.X - 1 && g_sChar.m_cLocation.Y == g_sGenerator.m_cLocation.Y)
	{
		if (g_GeneraStatus != false)
		{
			if (Batteries == 0)
			{
				g_Console.writeToBuffer(e, "Need 3 Batteries to power to Generator", 0x03);
			}
			else if (Batteries == 1)
			{
				g_Console.writeToBuffer(e, "Need 2 Batteries to power to Generator", 0x03);
			}
			else if (Batteries == 2)
			{
				g_Console.writeToBuffer(e, "Need 1 Batteries to power to Generator", 0x03);
			}
			else if (Batteries == 3)
			{
				g_GeneraStatus = false;
				Batteries -= 3;
			}
		}
		else
		{
			g_Console.writeToBuffer(e, "Generator 1 is on", 0x03);
			g_Console.writeToBuffer(f, "-Door is Open-", 0x03);
		}
	}

	if (g_sChar.m_cLocation.X == g_sGenerator1.m_cLocation.X && g_sChar.m_cLocation.Y == g_sGenerator1.m_cLocation.Y - 1 ||
		g_sChar.m_cLocation.X == g_sGenerator1.m_cLocation.X && g_sChar.m_cLocation.Y == g_sGenerator1.m_cLocation.Y + 1 ||
		g_sChar.m_cLocation.X == g_sGenerator1.m_cLocation.X + 1 && g_sChar.m_cLocation.Y == g_sGenerator1.m_cLocation.Y ||
		g_sChar.m_cLocation.X == g_sGenerator1.m_cLocation.X - 1 && g_sChar.m_cLocation.Y == g_sGenerator1.m_cLocation.Y)
	{
		if (g_GeneraStatus == false)
		{
			if (g_GeneraStatus1 != false)
			{
				if (Batteries == 0)
				{
					g_Console.writeToBuffer(e, "Need 2 Batteries to power to Generator", 0x03);
				}
				else if (Batteries == 1)
				{
					g_Console.writeToBuffer(e, "Need 1 Batteries to power to Generator", 0x03);
				}
				else if (Batteries == 2)
				{
					g_GeneraStatus1 = false;
					Batteries -= 2;
				}
			}
			else
			{
				g_Console.writeToBuffer(e, "Generator 2 is on", 0x03);
				g_Console.writeToBuffer(f, "-Door is Open-", 0x03);
			}
		}
		else
		{
			g_Console.writeToBuffer(e, "I think i have to activate the first generator first!", 0x03);
		}
	}

}

//----------------------------------Render da Generator------------------------------------
void renderGenerator()
{
	WORD GeneratorColor = 0x0F;
	
	COORD a, b;

	a.X = g_sGenerator.m_cLocation.X;
	a.Y = g_sGenerator.m_cLocation.Y;

	b.X = g_sGenerator1.m_cLocation.X;
	b.Y = g_sGenerator1.m_cLocation.Y;

	if (g_GeneraStatus == false)
	{
		g_Bat_Door_Close = false;
	}

	if (g_GeneraStatus1 == false)
	{
		g_Bat_Door_Close1 = false;
	}

	g_Console.writeToBuffer(a, (char)158, GeneratorColor);

	g_Console.writeToBuffer(b, (char)158, GeneratorColor);
}

//Gary ---------------------------------Life Points---------------------------------
void renderlives()
{
	COORD c;

	c.X = 2;
	c.Y = 32;

	for (int i = 0; i < lifepoint; i++)
	{
		g_Console.writeToBuffer(c, 3 , 13);
		c.X++;
	}

	c.X = 2;
	c.Y += 1;

	if (lifepoint == 3)
	{
		g_Console.writeToBuffer(c , "You Have 3 lives left ATM you can do this !" , 13);
	}

	if (lifepoint == 2)
	{
		g_Console.writeToBuffer(c, "You Have 2 lives left :o surely you can complete the game right $_$ ", 13);
	}

	if (lifepoint == 1)
	{
		g_Console.writeToBuffer(c, "You Have 1 life left :o you are really bad at this /._./ ", 13);
	}

	// Check if player dies to load up death screen
	if (lifepoint == 0)
	{
		g_eGameState = S_DEATHSCREEN;
	}
}

void overwriteDoor()
{
	if (doorClosed == true)
	{
		map[g_sDoors[0].Loc.Y][g_sDoors[0].Loc.X] = (char)68;
		g_Console.writeToBuffer(doorz[0], (char)178, 6);
	}
	if (doorClosed1 == true)
	{
		map[g_sDoors[2].Loc.Y][g_sDoors[2].Loc.X] = (char)68;
		g_Console.writeToBuffer(doorz[2], (char)178, 6);
	}
}

void renderFramerate()
{
	COORD c;
	// displays the framerate
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(3);
	ss << 1.0 / g_dDeltaTime << "fps";
	c.X = g_Console.getConsoleSize().X - 9;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str());

	// displays the elapsed time
	ss.str("");
	ss << g_dElapsedTime << "secs";
	c.X = 0;
	c.Y = 0;
	g_Console.writeToBuffer(c, ss.str(), 15);

	ss.str("");
	ss << "X = " << g_sChar.m_cLocation.X;
	c.X = g_Console.getConsoleSize().X - 8;
	c.Y = 1;
	g_Console.writeToBuffer(c, ss.str(), 15);

	ss.str("");
	ss << "Y = " << g_sChar.m_cLocation.Y;
	c.Y += 1;
	g_Console.writeToBuffer(c, ss.str(), 15);
	//g_sChar.m_cLocation.Y = 14;
}

void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}