/* MISC.C
 All KINDS of assorted crap :) Has most of the in-game dialog boxes
 such as the status box etc.

 Also like I said there's all kinds of assorted crap in here.
 That's why it's called "misc.c" (get it? :))
 */

#include "keen.h"
#include <SDL.h>
#include "sdl/CInput.h"
#include "sdl/CVideoDriver.h"
#include "sdl/sound/CSound.h"

#include "game.h"
#include "fileio/CSavedGame.h"
#include "CLogFile.h"
#include "graphics/CGfxEngine.h"
#include "StringUtils.h"
#include "FindFile.h"

#include "fileio/CExeFile.h"

#include "dialog/CTextViewer.h"

#include <fstream>
#include <cstdlib>

void banner(void)
{
	char buf[80];

	sprintf(buf, "%s  *Unknown* build check banner()", REVISION);
#ifdef TARGET_WIN32
    sprintf(buf, "%s  Windows build", REVISION);
#endif
#ifdef TARGET_LNX
    sprintf(buf, "%s  Linux build", REVISION);
#endif
	printf("%s", buf);
	printf(" (%d bit)", static_cast<int> (sizeof(int*)*8));

	printf("\nby The CloneKeenPlus Team 2009\n");
	printf("\n");
	printf("BY A FAN, FOR FANS. ALL \"COMMANDER KEEN\" GRAPHICS,\n");
	printf("SOUND, AND LEVEL FILES ARE THE PROPERTY OF ID SOFTWARE.\n");
	printf("\n");
}

void AllPlayersInvisible(void)
{
	/*int i;

	 for(i=0;i<MAX_PLAYERS;i++)
	 {
	 if (player[i].isPlaying)
	 {
	 objects[player[i].useObject].onscreen = 0;
	 player[i].hideplayer = 1;
	 }
	 }*/
}


void usage(void)
{
	// TODO: Many options has to be changed. For now it is disabled
	/*
	 printf("Usage: keen [lvlnum] [-*player] [-nopk] [-ep*] [-dtm] [-nocheat] [-rec] -[eseq]<br>\n");
	 printf("lvlnum          specify a level number (such as 2) to go directly to that level<br>");
	 printf("-*player        select number of players (1-4); defaults to 1<br>");
	 printf("-nopk           do not allow players to kill each other in multiplayer games<br>");
	 printf("-game*            select game of data base; if not given, start menu is opened<br>");
	 printf("-dtm            go directly to the world map, bypassing intro and title screen<br>");
	 printf("-mean           increase game difficulty<br>");
	 printf("-cheat          enable function key cheat/debug codes<br>");
	 printf("-rec            record player actions to demo.dat for making a demo<br>");
	 printf("-eseq           for the impatient--cut directly to the ending sequence<br>");
	 #ifdef BUILD_SDL
	 printf("-fs             use fullscreen mode<br>");
	 printf("-dbl            zoom image 2x<br>");
	 printf("-ogl            hardware acceleration<br>");
	 printf("-showfps        show FPS in upper-right of screen<br>");
	 #endif

	 printf("<br>");
	 printf("Examples:<br>");
	 printf("  keen 3 -ep2                play ep 2, level 3 in 1-player mode<br>");
	 printf("  keen -ep3 -dtm -2player    play ep3, skip title&intro, 2-player mode<br>");
	 printf("  keen -ep3                  play a normal game of ep3<br>");
	 */
}

unsigned int rnd(void)
{
	return std::rand();
}

