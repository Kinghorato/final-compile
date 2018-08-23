#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include "AI.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

// Enumeration to store the control keys that your game will have
enum EKEYS
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
    K_SPACE,
    K_COUNT
};

// Enumeration for the different screen states
enum EGAMESTATES
{
    S_SPLASHSCREEN,
    S_GAME,
    S_COUNT
};

// struct for the game character
struct SGameChar
{
    COORD m_cLocation;
    bool  m_bActive;
};

struct objects {
	COORD Loc;
	//bool SandD;

};

// struct for the AI in the game.
struct ROBOTS
{
	int xpos;
	int ypos;
	int step;
	int dir;
	int range;
};


void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory

void splashScreenWait();    // waits for time to pass in splash screen
void gameplay();            // gameplay logic

void moveCharacter();       // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 

void moveAIS();

void renderSplashScreen();  // renders the splash screen
void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderAIS();
void renderlives();

//Choi Poh
void Teleporter();
void renderDoor();			// renders the door into the buffer
void renderBatDoor();
void renderText();
void renderLever();
void renderBatteries();
void gameBatteries();
void Levers();
void Collision();
void renderGenerator();
void BatGenerator();
//

//PY
void doorCollision();		// collision of door
void doorCheck();			// check which door character or block is hitting
void blocksMovement();		// moving blocks
void puzzswitch();			// puzzle with 9 switch
void puzzTrigger();			// render puzzle wall
							// will be doing timer switch

//Sufyan
void renderVisibility();
void floorCollision();
void coinCollision();

//

void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void loadMap();
void loadTextScreen();

#endif // _GAME_H