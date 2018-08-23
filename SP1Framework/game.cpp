// This is the main file for the game logic and function
#include "game.h"
#include "Framework\console.h"
#pragma comment (lib,"Winmm.lib")

//--------------------------------------------Global vars---------------------------------------------------------

double  g_dElapsedTime;
double  g_dDeltaTime;
bool g_abKeyPressed[K_COUNT];
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
SGameChar   g_sChar, g_sDoor1, g_slever1, g_sBatteries, g_sBatteries1, g_sBatteries2, g_sBatteries3 , g_sBatteries4 , g_sBatDoor, g_sGenerator , g_sCoin1, g_sCoin2, g_sCoin3;
// Gary Vars
double g_dEnemyTime1;
double g_dEnemyTime2;
double g_dEnemyTime3;

vector<string> map;
vector<string> loading;

ROBOTS BOT[10];

int lifepoint = 3;
int startingpointx = 2;
int startingpointy = 14;

int checkpoint1X = 2;
int checkpoint1Y = 14;

int Botnumber = 0;
//

//Peng Yang Vars
bool	doorClosed;
bool	switchOn;
bool	B1, B2, B3, B4, ClearedPuz;
objects g_sDoors[8], g_sTrigPlate[2], g_sBlock[2];
COORD doorz[6] = { { 9,13 },{ 63,27 },{ 30,13 },{ 80,25 },{ 73,16 },{ 87,2 } };
COORD plates[2] = { { 5,28 },{ 63,24 } };
COORD puzzleSwitch[9] = { { 92,12 },{ 98,9 },{ 87,9 },{ 92,6 },{ 87,12 },{ 98,12 },{ 92,9 },{ 87,6 },{ 98,6 } }; // first 4 opens door(by sequence) other 5 reset buttons
//

//Sufyan Vars
int		coinAmt = 0;
bool	visibility = false;
//

// Choi Poh Vars
bool	g_Door1_Close;
bool	g_Bat_Door_Close;
bool	g_GeneraStatus;
int Batteries;
bool ifBattery1True;

COORD g_sTele[28] = { { 79, 30 },{ 91, 22 },{ 91, 30 },{ 89, 21 },{ 109, 26 }, //T0, T1, T2, T3, T4
{ 100, 30 },{ 89, 25 },{ 100, 22 },{ 111, 21 },{ 93, 29 }, //T5, T6, T7, T8, T9
{ 111, 25 },{ 100, 26 },{ 91, 26 },{ 98, 21 },{ 102, 29 }, //T10, T11, T12, T13, T14
{ 98, 25 },{ 109, 22 },{ 93, 25 },{ 98, 29 },{ 102, 25 }, //T15, T16, T17, T18, T19
{ 102, 21 },{ 107, 25 },{ 107, 21 },{ 93, 21 },{ 109, 30 }, //T20, T21, T22, T23, T24
{ 111, 29 },{ 92, 16 },{ 84, 2 } }; //T25, T26, T27



double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once
// Console object
Console g_Console(160, 40, "SP1 Framework");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------

//Gary
void init( void )
{
	// character position
	g_sChar.m_cLocation.X = 2;	//2, 9
	g_sChar.m_cLocation.Y = 14;	//14, 98
	g_sChar.m_bActive = true;

	// sets the initial state for the game
	g_eGameState = S_SPLASHSCREEN;

    // Set precision for floating point output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;
	// 

	//Sufyan init

	//For Coins
	g_sCoin1.m_cLocation.X = 10;
	g_sCoin1.m_cLocation.Y = 18;

	g_sCoin2.m_cLocation.X = 76;
	g_sCoin2.m_cLocation.Y = 18;

	g_sCoin3.m_cLocation.X = 75;
	g_sCoin3.m_cLocation.Y = 18;
	//

	//PengYang Init
	//bool door & switch
	doorClosed = true;
	switchOn = false;
	B1 = true;
	B2 = true;
	B3 = true;
	B4 = true;
	ClearedPuz = false;

	//character & object
	g_sChar.m_bActive = true;
	g_sDoor1.m_bActive = true;

	//location of character & objects*
	g_sBlock[0].Loc.X = 4;
	g_sBlock[0].Loc.Y = 25;
	g_sBlock[1].Loc.X = 38;
	g_sBlock[1].Loc.Y = 21;

	for (int i = 0; i <= 6; i++)
	{
		g_sDoors[i].Loc.X = 0;
		g_sDoors[i].Loc.Y = 0;
	}
	for (int d = 0; d <= 6; d++)
	{
		g_sDoors[d].Loc = doorz[d];				//throw coords to object
	}
	for (int i = 0; i <= 1; i++)
	{
		g_sTrigPlate[i].Loc.X = 0;
		g_sTrigPlate[i].Loc.Y = 0;
	}
	for (int d = 0; d <= 1; d++)
	{
		g_sTrigPlate[d].Loc = plates[d];		//throw coords to object
	}

	//For Levers
	g_slever1.m_cLocation.X = 5;
	g_slever1.m_cLocation.Y = 2;
	g_slever1.m_bActive = true;

	//

	//Gary init
	g_dEnemyTime1 = 0.0;
	g_dEnemyTime2 = 0.0;
	g_dEnemyTime3 = 0.0;

	//loads map
	loadMap();
	loadTextScreen();

	//music , uncomment to play , comment to mute
	//PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_LOOP | SND_NOSTOP | SND_ASYNC);

	//BOT POS Struct array.
	BOT[0] = { 3 , 7 , 0 , 1 , 13};
	BOT[1] = { 16 , 9 , 0 , -1 , 13 };
	BOT[2] = { 30 , 27 , 0 , 1 , 39};
	BOT[3] = { 69 , 27 , 0 , -1 , 39};
	BOT[4] = { 84 , 30 , 0 , -1 , 11};
	BOT[5] = { 3 , 11 , 0 , 1 ,13 };
	//
	
	//Choi Poh Init
	//For Batteries
	g_sBatteries.m_cLocation.X = 4;
	g_sBatteries.m_cLocation.Y = 4;
	g_sBatteries.m_bActive = true;

	g_sBatteries1.m_cLocation.X = 9;
	g_sBatteries1.m_cLocation.Y = 9;
	g_sBatteries1.m_bActive = true;

	g_sBatteries2.m_cLocation.X = 11;
	g_sBatteries2.m_cLocation.Y = 11;
	g_sBatteries2.m_bActive = true;

	g_sBatteries3.m_cLocation.X = 8;
	g_sBatteries3.m_cLocation.Y = 8;
	g_sBatteries3.m_bActive = true;

	g_sBatteries4.m_cLocation.X = 13;
	g_sBatteries4.m_cLocation.Y = 11;
	g_sBatteries4.m_bActive = true;

	Batteries == 0;

	//For Generator
	g_sGenerator.m_cLocation.X = 54;
	g_sGenerator.m_cLocation.Y = 21;
	g_sGenerator.m_bActive = true;

	//For Doors
	g_sDoor1.m_cLocation.X = 9;
	g_sDoor1.m_cLocation.Y = 4;
	g_sDoor1.m_bActive = true;

	g_sBatDoor.m_cLocation.X = 9;
	g_sBatDoor.m_cLocation.Y = 12;
	g_sBatDoor.m_bActive = true;
	//

	//Bool Function
	g_Door1_Close = true;		//door1 close
	g_Bat_Door_Close = true;	//battery door close
	g_GeneraStatus = true;		// Generator off

								//For Levers
	g_slever1.m_cLocation.X = 13;
	g_slever1.m_cLocation.Y = 2;
	g_slever1.m_bActive = true;
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
	g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
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

    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;

        case S_GAME: gameplay(); // gameplay logic when we are in the game
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
        case S_SPLASHSCREEN: renderSplashScreen();
            break;
        case S_GAME: renderGame();
            break;
    }

    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime > 0.5) // wait for 5 seconds to switch to game mode, else do nothing
        g_eGameState = S_GAME;
}

void gameplay()            // gameplay logic
{
	//----for different instances of speed----
	g_dEnemyTime1 += g_dDeltaTime; 
	g_dEnemyTime2 += g_dDeltaTime;
	g_dEnemyTime3 += g_dDeltaTime; 

	//----------------------------------------

    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
	
    //Sufyan gameplay
	floorCollision();
	coinCollision();
	//

	//Gary gameplay
	moveAIS();
	//

	//ChoiPoh gameplay
	Levers();			// Lever for Door
	Collision();		// In-game Objects Collision
	gameBatteries();	// Batteries
	BatGenerator();		// Generator
	Teleporter();		// Teleporter function
	//

	//PengYang gameplay
	puzzswitch();
	doorCheck();
	blocksMovement();
	//
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
		g_Console.writeToBuffer(puzzleSwitch[s], (char)206, 4);
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


//PY
void doorCheck()
{
	int pairChecker = 0;
	doorClosed = true;
	for (int p = 0; p <= 1; p++)		//checking which plates the character triggered
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
					doorClosed = false;
				}
				break;
			}
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
	if (g_sCoin1.m_cLocation.X == g_sChar.m_cLocation.X && g_sCoin1.m_cLocation.Y == g_sChar.m_cLocation.Y)
	{
		g_Console.writeToBuffer(g_sCoin1.m_cLocation, (char)32, 0);
		g_sCoin1.m_cLocation.X = 1;
		g_sCoin1.m_cLocation.Y = 0;
		coinAmt += 1;
	}

	if (g_sCoin2.m_cLocation.X == g_sChar.m_cLocation.X && g_sCoin2.m_cLocation.Y == g_sChar.m_cLocation.Y)
	{
		g_Console.writeToBuffer(g_sCoin1.m_cLocation, (char)32, 0);
		g_sCoin2.m_cLocation.X = 1;
		g_sCoin2.m_cLocation.Y = 0;
		coinAmt += 1;
	}

	if (g_sCoin3.m_cLocation.X == g_sChar.m_cLocation.X && g_sCoin3.m_cLocation.Y == g_sChar.m_cLocation.Y)
	{
		g_Console.writeToBuffer(g_sCoin1.m_cLocation, (char)32, 0);
		g_sCoin3.m_cLocation.X = 1;
		g_sCoin3.m_cLocation.Y = 0;
		coinAmt += 1;
	}
}


void moveCharacter()
{
    bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;

	//Testing for death against Traps [red !!]
	if ((map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == (char)19))
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
			if (map[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == (char)8 )
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
		if (map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X -1] != (char)219) 
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
    if (bSomethingHappened) //after something happens
    {
        // set the bounce time to some time in the future to prevent accidental triggers
        g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
    }
}

void BatGenerator()
{
	if (Batteries == 3)
	{
		if (g_sChar.m_cLocation.X == g_sBatDoor.m_cLocation.X + 1 && g_sChar.m_cLocation.Y == g_sBatDoor.m_cLocation.Y)
		{
			g_Bat_Door_Close = false;
		}
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
	}

	if (g_GeneraStatus == false)
	{
		Batteries - 3 ;
	}
}

void Levers()
{
	if (g_sChar.m_cLocation.X == g_slever1.m_cLocation.X && g_sChar.m_cLocation.Y == g_slever1.m_cLocation.Y)
	{
		g_Door1_Close = false;
	}
}

void Collision()
{
	if (g_Door1_Close == true)
	{
		if (g_sChar.m_cLocation.Y == g_sDoor1.m_cLocation.Y && g_sChar.m_cLocation.X == g_sDoor1.m_cLocation.X)
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

	if (g_Bat_Door_Close == true)
	{
		if (g_sChar.m_cLocation.Y == g_sBatDoor.m_cLocation.Y && g_sChar.m_cLocation.X == g_sBatDoor.m_cLocation.X)
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

	if (g_GeneraStatus == false || g_GeneraStatus == true)
	{
		if (g_sChar.m_cLocation.Y == g_sGenerator.m_cLocation.Y && g_sChar.m_cLocation.X == g_sGenerator.m_cLocation.X)
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
	//---------------------- if location of player is BOTposition -------------------------------
	//-------------------------------moving horizontally-----------------------------------------
	COORD targetDest1 = { (BOT[0].xpos + (BOT[0].dir * 1)) , (BOT[0].ypos) };
	COORD targetDest6 = { (BOT[5].xpos + (BOT[5].dir * 1)) , (BOT[5].ypos) };
	COORD targetDest2 = { (BOT[1].xpos + (BOT[1].dir * 1)) , (BOT[1].ypos) };
	COORD targetDest3 = { (BOT[2].xpos + (BOT[2].dir * 1)) , (BOT[2].ypos) };
	COORD targetDest4 = { (BOT[3].xpos + (BOT[3].dir * 1)) , (BOT[3].ypos) };

	//-------------------------------moving up and down------------------------------------------ 
	COORD targetDest5 = { (BOT[4].xpos) , (BOT[4].ypos + (BOT[4].dir * 1)) };

	//-------------------------------AI movement begin-------------------------------------------

	//-------------------------------Bot 1 , 2 & 6 movement------------------------------------------

	if (g_dEnemyTime1 >= 0.03)  // how fast the enemy moves
	{
		//Bot 1
		if (g_sChar.m_cLocation.X == targetDest1.X && g_sChar.m_cLocation.Y == targetDest1.Y)
		{
			g_sChar.m_cLocation.X = checkpoint1X; 
			g_sChar.m_cLocation.Y = checkpoint1Y;
		}
		else
		{
			g_dEnemyTime1 = 0;
			MovingAI(BOT, 0);
		}
	
		//Bot 2 Start
		if (g_sChar.m_cLocation.X == targetDest2.X && g_sChar.m_cLocation.Y == targetDest2.Y)
		{
			g_sChar.m_cLocation.X = checkpoint1X; 
			g_sChar.m_cLocation.Y = checkpoint1Y;
			lifepoint -= 1;
		}
		else
		{
			g_dEnemyTime1 = 0;
			MovingAI(BOT , 1);
		}

		//Bot 6 begin
		if (g_sChar.m_cLocation.X == targetDest6.X && g_sChar.m_cLocation.Y == targetDest6.Y)
		{
			g_sChar.m_cLocation.X = checkpoint1X; //setting player spawnpoint set to 1
			g_sChar.m_cLocation.Y = checkpoint1Y;
			lifepoint -= 1;
		}
		else
		{
			g_dEnemyTime1 = 0;
			MovingAI(BOT , 5);
		}
	}

	//----------------------------------------Bot 3 & 4 movemement--------------------------------------------------
	if (g_dEnemyTime2 >= 0.035)  // how fast the enemy moves
	{
		//Bot 3
		if (g_sChar.m_cLocation.X == targetDest3.X && g_sChar.m_cLocation.Y == targetDest3.Y)
		{
			g_sChar.m_cLocation.X = checkpoint1X; //setting player spawnpoint set to 1
			g_sChar.m_cLocation.Y = checkpoint1Y;
			lifepoint -= 1;
		}
		else
		{
			g_dEnemyTime2 = 0.0;
			MovingAI(BOT , 2);
		}

		//Bot 4
		if (g_sChar.m_cLocation.X == targetDest4.X && g_sChar.m_cLocation.Y == targetDest4.Y)
		{
			g_sChar.m_cLocation.X = checkpoint1X; //setting player spawnpoint set to 1
			g_sChar.m_cLocation.Y = checkpoint1Y;
			lifepoint -= 1;
		}
		else
		{
			g_dEnemyTime2 = 0.0;
			MovingAI(BOT , 3);
		}
	}

	//----------------------------------------Bot 5 movement [vertical] ---------------------------------------------------
	if (g_dEnemyTime3 >= 0.05)
	{
		if (g_sChar.m_cLocation.X == targetDest5.X && g_sChar.m_cLocation.Y == targetDest5.Y)
		{
			g_sChar.m_cLocation.X = 84; //setting player spawnpoint set to 1
			g_sChar.m_cLocation.Y = 18;
			lifepoint -= 1;
		}
		else
		{
			g_dEnemyTime3 = 0.0;
			MovingAI(BOT, 4);
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
			loading.push_back(line);
		}
		myfile.close();
	}
}

void renderVisibility()
{
	// if the player steps on the 's' switch, the path will render in the rendermap function.
	if (map[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'S')
	{
		visibility = true;
	}
	else
	{
		visibility = false;
	}
}

//sufyan
void renderCoins()
{
	g_Console.writeToBuffer(g_sCoin1.m_cLocation, '*', 3);
	g_Console.writeToBuffer(g_sCoin2.m_cLocation, '*', 3);
	g_Console.writeToBuffer(g_sCoin3.m_cLocation, '*', 3);
}

//Gary
void renderSplashScreen()  // renders the splash screen
{
	COORD c;
	COORD d;
	COORD e;

    int pos = 0;
	int xpos = 0;
	for (int i = 0; i < loading.size(); i++) //keep printing each line as long as vector != 0
	{
		c.X = xpos;
		c.Y = pos + 1;
		g_Console.writeToBuffer(c, loading[i], 12);
		pos++;
	}

	// General Text On Screen
	d.X = 64;
	d.Y = 20;
	g_Console.writeToBuffer(d, "Game starting in 5 seconds ..." , 12);
	
	e.X = 54;
	e.Y = 22;

	g_Console.writeToBuffer(e, 12, 15);
	e.X += 2;
	g_Console.writeToBuffer(e, " Is You , The Character. Get To The Exit To Win.", 15);
	e.Y += 2;
	e.X -= 8;
	g_Console.writeToBuffer(e, " Anything in RED is hostile . Touch and you lose a life point. " , 12);
}

void renderAIS() //All the AIS
{
	COORD a; // bot 1
	COORD b; // bot 2  
	COORD c; // bot 3
	COORD d; // bot 4
	COORD e; // bot 5
	COORD f; // bot 6

	a.X = BOT[0].xpos;
	a.Y = BOT[0].ypos;

	g_Console.writeToBuffer(a , 197 , 12);
	 
	b.X = BOT[1].xpos;
	b.Y = BOT[1].ypos;

	g_Console.writeToBuffer(b , 197 , 12);

	c.X = BOT[2].xpos;
	c.Y = BOT[2].ypos;

	g_Console.writeToBuffer(c, 197, 12);

	d.X = BOT[3].xpos;
	d.Y = BOT[3].ypos;

	g_Console.writeToBuffer(d, 197, 12);

	e.X = BOT[4].xpos;
	e.Y = BOT[4].ypos;

	g_Console.writeToBuffer(e, 197, 12);

	f.X = BOT[5].xpos;
	f.Y = BOT[5].ypos;

	g_Console.writeToBuffer(f, 197, 12);
}

void renderGame()
{
    renderMap();        // gary
	renderAIS();        //gary
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
	//

	//Sufyan
	renderVisibility(); 
	renderCoins();	
	//

	renderCharacter(); 
}

void renderText()
{
	COORD c = g_Console.getConsoleSize();
	c.Y = 35;
	c.X = 46;

	//Switch Texts
	if (g_sChar.m_cLocation.X == g_slever1.m_cLocation.X && g_sChar.m_cLocation.Y == g_slever1.m_cLocation.Y)
	{
		g_Console.writeToBuffer(c, "You have Opened a Door", 0x03);
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

	//Generator text
	COORD e;
	e.Y = 36;
	e.X = 25;

	COORD f;
	f.Y = 37;
	f.X = 25;

	if (g_sChar.m_cLocation.X == g_sGenerator.m_cLocation.X && g_sChar.m_cLocation.Y == g_sGenerator.m_cLocation.Y + 1 || g_sChar.m_cLocation.X == g_sGenerator.m_cLocation.X + 1 && g_sChar.m_cLocation.Y == g_sGenerator.m_cLocation.Y)
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
		else
		{
			g_Console.writeToBuffer(e, "Generator is on", 0x03);
			g_Console.writeToBuffer(f, "-Door is Open-", 0x03);
			g_GeneraStatus = false;
		}
	}
}

void loadMap() // level 1
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
					line[i] = 19;
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
	COORD e;
	COORD f;
	COORD g;
	COORD h;
	COORD i;
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

			else if ((map[j])[i] == ((char)19)) // if character is trap       
			{
				g_Console.writeToBuffer({ (SHORT)i, (SHORT)j }, 19, 12);     // printing trap
			}
			
			else if ((map[j])[i] == ((char)48)) // if character is stopper       
			{
				g_Console.writeToBuffer({ (SHORT)i, (SHORT)j }, 48, 6);     // printing stopper [prevent slipping on ice]
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

	d.X = 120;
	d.Y = 22;

	g_Console.writeToBuffer(d, 197 , 12);
	d.X += 1;
	g_Console.writeToBuffer(d, " = MONSTER", 12);

	//legend door

	e.X = 120;
	e.Y = 24;

	g_Console.writeToBuffer(e, 178, 5);
	e.X += 1;
	g_Console.writeToBuffer(e, " = Door", 3);

	//legend switch

	f.X = 120;
	f.Y = 26;

	g_Console.writeToBuffer(f, 33, 2);
	f.X += 1;

	g_Console.writeToBuffer(f, " = switch", 2);

	//legend movable block

	g.X = 120;
	g.Y = 28;

	g_Console.writeToBuffer(g, 254 , 8);
	g.X += 1;

	g_Console.writeToBuffer(g, " = moving block", 8);

	h.X = 120;
	h.Y = 29;

	i.X = 120;
	i.Y = 30;

	string cordx;
	string cordy;

	int x = g_sChar.m_cLocation.X;
	g_Console.writeToBuffer(h, x , 6); // x cord of player
	g_Console.writeToBuffer(i, g_sChar.m_cLocation.Y, 6); // y cord of player

	
	//coin indicator
	k.X = 2;
	k.Y = 33;

	g_Console.writeToBuffer(k, "Coins Collected : ", 3);
	k.X += 18;

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

//Gary
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
}

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

	COORD a;

	a.X = g_sBatDoor.m_cLocation.X;
	a.Y = g_sBatDoor.m_cLocation.Y + 1;

	if (g_Bat_Door_Close == true)
	{
		g_Console.writeToBuffer(a, (char)68, doorColor);
	}
	else
	{
		g_Console.writeToBuffer(a, (char)32, doorColor);
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

//----------------------------------Render da Generatorto------------------------------------
void renderGenerator()
{
	WORD GeneratorColor = 0x0F;

	COORD a;

	a.X = g_sGenerator.m_cLocation.X;
	a.Y = g_sGenerator.m_cLocation.Y + 1;

	if (g_GeneraStatus == false)
	{
		g_Bat_Door_Close = false;
	}

	g_Console.writeToBuffer(a, (char)158, GeneratorColor);
}

//Gary ---------------------------------Life Points---------------------------------
void renderlives()
{
	COORD c;
	COORD end;

	COORD death;
	
	end.X = 55;
	end.Y = 15;

	c.X = 2;
	c.Y = 32;
	
	death.X = 2;
	death.Y = 34;

	for (int i = 0; i < lifepoint; i++)
	{
		g_Console.writeToBuffer(c, 3 , 13);
		c.X++;
	}

	if (lifepoint == 3)
	{
		g_Console.writeToBuffer(death , "You Have 3 lives left ATM you can do this !" , 13);
	}

	if (lifepoint == 2)
	{
		g_Console.writeToBuffer(death, "You Have 2 lives left :o surely you can complete the game right $_$ ", 13);
	}

	if (lifepoint == 1)
	{
		g_Console.writeToBuffer(death, "You Have 1 life left :o you are really bad at this /._./ ", 13);
	}


	
	if (lifepoint == 0) //if life points are 0
	{
		g_Console.clearBuffer();
		g_Console.writeToBuffer(end, "Game Over !!! Nice Try . Hit ESC to exit. ", 006);
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
    g_Console.writeToBuffer(c, ss.str(), 0x59);
}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}