#ifndef __GOFRAME_H__
#define __GOFRAME_H__   1

/* type definitions */


typedef enum { 
   GO_POINT_EMPTY,
   GO_POINT_BLACK,
   GO_POINT_WHITE,
   GO_POINT_MARKED
} goPoint;

typedef enum { 
   GO_PLAYER_BLACK,
   GO_PLAYER_WHITE,
} goPlayer;

typedef enum { 
   GO_COLOR_BLACK,
   GO_COLOR_WHITE,
} goColor;

typedef struct goMove {
   unsigned short x;
   unsigned short y;
   char is_pass;
   goPlayer player;
} goMove;

typedef struct goHistory {
   goMove move;
   struct history *next;
   struct history *prev;
} goHistory;

typedef struct game {
   unsigned short size; // board size is size**2
   goPoint * board;
   // goPlayer whosTurn; // Redundant check history
   unsigned short white_captures;
   unsigned short black_captures;
   goHistory * first;
   goHistory * last;
} goGame;

/* Game initialization */

goGame * init_game( short size );

/* Game Manipulation */

short play( goGame *gm, unsigned short x, unsigned short y ); // makes a move as the next player
short undo( goGame *gm );
short pass( goGame *gm );
short setPoint( goGame *gm, unsigned short x, unsigned short y, goPoint state );

/* Game filehandling */

short save( goGame *gm, char *filename );
short load( goGame *gm, char *filename );

/* Game Information */

short whosturn( goGame *gm );
short white_captures( goGame *gm );
short black_captures( goGame *gm );


/* Game Utilities */

#endif
