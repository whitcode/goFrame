#include"goframe.h"
#include<stdio.h>
#include<stdlib.h>
/* possibly modify for empty points and possiblly add no color */
#define     playerColor(x)       ( x == GO_PLAYER_BLACK ? GO_COLOR_BLACK : GO_COLOR_WHITE )
#define     pointColor(x)        ( x == GO_POINT_BLACK ? GO_COLOR_BLACK : GO_COLOR_WHITE )
#define     playerPoint(x)       ( x == GO_PLAYER_BLACK ? GO_POINT_BLACK : GO_POINT_WHITE )

inline int board_map(int x, int y, int size) {
   return x*size + y;
}
inline int board_pos(goGame *gm, int x, int y) {
   return gm->board[x*gm->size + y];
}
inline int is_out_of_bounds(goGame *gm, int x, int y) {
   if( x < 0 || x >= gm->size || 
       y < 0 || y >= gm->size ) {
      return 0;
   }
   return 1;
}

struct game * init_game( short size ) {
   int i;
   struct game *rt = malloc( sizeof(goGame) );

   if( rt == NULL ) {
      return NULL;
   }
   /* history is empty */
   rt->first = NULL;
   rt->last = NULL;

   /* create new board */
   rt->board = malloc( sizeof(goPoint) * size * size );
   if( rt->board == NULL ) {
      return NULL;
   }
   /* empty the new board */
   for( i = 0 i < size*size; i++ ) {
      rt->board[i] = GO_POINT_EMPTY;
   }

   /* init the captures */
   rt->white_captures = 0;
   rt->black_captures = 0;

   return rt;
}
/* move procedure 
 *
 * check move legality
 * if illegal return
 * else play move
 *
 * remove game marks
 * 
 * remove killed stones
 *
 * stones_captured = 0
 * foreach neighbor
 *    if same color
 *       next
 *    else if empty
 *       next
 *    else if liberties == 0
 *       remove group and mark
 *       stones_captures += removed stones
 *
 * remove game marks unless one stone removed
 *
 * if stones_captured != 1
 *    remove marks
 * add captures to game totals
 */

short play( goGame *gm, short x, short y) {
   goPlayer pl = whosturn(gm);

   if( ! valid_move(gm,x,y,pl) ) {
      return 0;
   }

   /* setup game move */
   goMove mv;
   mv.x = x;
   mv.y = y;
   mv.player = pl;
   mv.is_pass = 0;

   /* add game move to history */
   goHistory *hist = malloc(sizeof(goHistory));
   if( hist == NULL ) {
      return -1;
   }
   hist->move = mv;
   hist->prev = gm->last;
   hist->next = NULL;
   if( gm->first == NULL ) { // this is the first move 
      gm->first = hist;
      gm->last = hist;
   } else { // link to last move
      gm->last->next = hist;
      gm->last = hist;
   }
   /* remove board marks - there last purpose was move legality */
   unmark_board(gm);

   /* place stone */
   board[board_map(x,y,gm->size)] = playerPoint(pl);

   /* remove killed stones */
   /* if captured != 1 remove marks */
   /* updated captures */

   // update board
   return 1;
}
short save( struct game *gm, char *filename) {
   //open file
   //print each history item into it
}

short load( struct game *gm, char *filename) {
   //open file
   //parse history items
   //play each item
   //return
   return -1;
}

short undo( struct game *gm) {
   //remove last history item
   //replay history
   returen -1;
}

short pass( struct game *gm) {
   // if last history item was pass
   // game over
   // score and return
   return -1;
}

goPlayer whosturn( goGame *gm ) {
   if( go->last ) {
      return gm->last->move.player == GO_PLAYER_BLACK ? GO_PLAYER_WHITE : GO_PLAYER_BLACK;
   } else {
      return GO_PLAYER_BLACK;
   }
}

short white_captures( struct game *gm ) {
   return gm->white_captures;
}

short black_captures( struct game *gm ) {
   return gm->black_captures;
}

short liberty_count( goGame *gm, short x, short y, goColor color, char *board) {
   int sum = 0;
   int i;
   int is_first = 0;

   // if board == NULL then this is the first call
   if( board == NULL ) {
      board = malloc(sizeof(char) * gm->size * gm->size);
      // oppsy return invalid count -1
      if( board == NULL ) {
         return -1;
      }
      // initialize marker board to 0
      for( i = 0; i < gm->size * gm->size; i++) {
         board[i] = 0;
      }
      // flag so we now to free board at the end
      is_first = 1;
      color = board_pos(gm,x,y);
   }
   // if off the board  add no liberties
   if(is_out_bounds(gm,x,y) ) {
         return 0;
   }
   // add nothing if we were already here
   if( board[board_map(x,y,gm->size)] == 1 ) {
      return 0;
   }
   // mark this location
   board[board_map(x,y,gm->size)] = 1;
   //if empty then we found a liberty
   if( board_pos(gm,x,y) == GO_POINT_EMPTY ||
       board_pos(gm,x,y) == GO_POINT_MARKED ) {// a marked point is still empty
      return 1;
   }
   //if not the color we are looking at return
   if( pointColor( board_pos(gm,x,y) ) != color ) {
      return 0;
   }
   // check our neighbors
   sum += liberty_count(gm,x-1,y,color,board);
   sum += liberty_count(gm,x+1,y,color,board);
   sum += liberty_count(gm,x,y-1,color,board);
   sum += liberty_count(gm,x,y+1,color,board);

   // freeing up board if we allocated it
   if( is_first ) free(board);

   //returning the sum
   return sum;
}
short remove_around_if_dead(gm *gm, short x, short y) {
   goPoint pt = board_pos(gm,x,y);
   goColor cl;
   int cnt;
   if( pt == GO_POINT_EMPTY ) {
      return 0;
   }
   /* for each direction */
      /* count liberties */
      /* if 0 remove them */

   cl = pointColor(board_pos(gm,x - 1,y));
   cnt = liberty_count(gm,x - 1, y, cl);
   if( cnt == 0 ) {
      remove_group(gm,x - 1,y,cl);
   }

   cl = pointColor(board_pos(gm,x + 1,y));
   cnt = liberty_count(gm,x + 1, y, cl);
   if( cnt == 0 ) {
      remove_group(gm,x + 1,y,cl);
   }

   cl = pointColor(board_pos(gm,x,y - 1));
   cnt = liberty_count(gm,x, y - 1, cl);
   if( cnt == 0 ) {
      remove_group(gm,x,y - 1,cl);
   }

   cl = pointColor(board_pos(gm,x,y + 1));
   cnt = liberty_count(gm,x, y + 1, cl);
   if( cnt == 0 ) {
      remove_group(gm,x,y + 1,cl);
   }
}
/* returns the number of stones removed the empty spaces will be set to GO_MARKED*/
short remove_group(gm *gm, short x, short y, goColor color) {
   int sum = 0;

   /* stop if off the board */
   if( is_out_bounds(gm,x,y) ) {
      return 0;
   }

   /* stop  if not the color we are looking for */
   if( pointColor(board_pos(gm,x,y)) != color ) {
      return 0;
   }

   /* set to marked */
   gm->board[board_map(x,y,sm->size)] = GO_POINT_MARKED;

   /* check neighbors and add their results up */
   sum += remove_group(gm, x - 1, y, color);
   sum += remove_group(gm, x + 1, y, color);
   sum += remove_group(gm, x, y - 1, color);
   sum += remove_group(gm, x, y + 1, color);

   return sum;
}

/* sets all GO_MARKED to GO_EMPTY */
void unmark_board(goGame *gm) {
   int i = 0;
   for( i = 0; i < gm->size * gm->size; i++ ) {
      if( board_pos(gm,x,y) == GO_POINT_MARKED ) {
         gm->board[board_map(x,y,gm->size)] = GO_POINT_EMPTY;
      }
   }
   return;
}

short is_sucide(goGame *gm, short x, short y, goPoint color) {
   /* checks for a non-empty point */
   if( board_pos(gm,x,y) != GO_EMPTY ) {
      return -1;
   }

   /* check neighbers if they are empty*/
   if( board_pos(gm, x - 1, y) == GO_EMPTY ||
       board_pos(gm, x + 1, y) == GO_EMPTY ||
       board_pos(gm, x, y - 1) == GO_EMPTY ||
       board_pos(gm, x, y + 1) == GO_EMPTY ) {
      return 0; 
   }
   int lib;

   lib = liberty_count(gm,x - 1,y, 0, NULL);
   if( board_pos(gm, x - 1, y) == color && lib > 1 )  return 0; 
   if( board_pos(gm, x - 1, y) != color && lib == 1 ) return 0;

   lib = liberty_count(gm,x + 1,y, 0, NULL);
   if( board_pos(gm, x + 1, y) == color && lib > 1 )  return 0; 
   if( board_pos(gm, x + 1, y) != color && lib == 1 ) return 0;

   lib = liberty_count(gm,x,y - 1, 0, NULL);
   if( board_pos(gm, x, y - 1) == color && lib > 1 )  return 0; 
   if( board_pos(gm, x, y - 1) != color && lib == 1 ) return 0;

   lib = liberty_count(gm,x,y + 1, 0, NULL);
   if( board_pos(gm, x, y + 1) == color && lib > 1 )  return 0; 
   if( board_pos(gm, x, y + 1) != color && lib == 1 ) return 0;

   return 1;
}

// ko handling if capured 1 stone
// then that becomes the new ko point
// this does not handle superko

short is_invalid_move(goGame *gm, short x, short y, goPoint color) {
   /* You can not play ontop of another piece
    *
    * since kos will be the only spots with GO_MARKED
    * this also checks for ko
    */
   if( board_pos(gm,x,y) != GO_EMPTY ) {
      return 0;
   }
   //checks for sucide
   return is_sucide(gm,x,y, color);
}
