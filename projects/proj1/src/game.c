#include "game.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "snake_utils.h"

/* Helper function definitions */
static void set_board_at(game_t *game, unsigned int row, unsigned int col,
                         char ch);
static bool is_tail(char c);
static bool is_head(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static char head_to_body(char c);
static unsigned int get_next_row(unsigned int cur_row, char c);
static unsigned int get_next_col(unsigned int cur_col, char c);
static void find_head(game_t *game, unsigned int snum);
static char next_square(game_t *game, unsigned int snum);
static void update_tail(game_t *game, unsigned int snum);
static void update_head(game_t *game, unsigned int snum);

/**
  @task: Task 1
  @state: pass
*/

game_t *create_default_game() {
  game_t *game = (game_t *)malloc(sizeof(game_t));
  if (game == NULL) {
    fprintf(stderr, "allocate game fail\n");
  }

  game->snakes = (snake_t *)malloc(sizeof(snake_t));

  snake_t snake = {2, 2, 2, 4, true};
  game->num_rows = 18;
  game->num_snakes = 1;
  game->snakes[0] = snake;

  game->board = (char **)malloc(sizeof(char *) * 18);
  for (int i = 0; i < 18; i++)
    game->board[i] = (char *)malloc(sizeof(char) * 22);
  for (int i = 0; i < 18; i++) {
    if (i == 0 || i == 17)
      strcpy(game->board[i], "####################\n");
    else if (i == 2)
      strcpy(game->board[i], "# d>D    *         #\n");
    else
      strcpy(game->board[i], "#                  #\n");
  }
  return game;
}

/**
  @task: Task 2
  @state: pass
*/
void free_game(game_t *game) {
  for (int i = 0; i < game->num_rows; i++)
    free(game->board[i]);
  free(game->board);
  free(game->snakes);
  free(game);
  return;
}

/**
  @task: Task 3
  @state: pass
*/
void print_board(game_t *game, FILE *fp) {
  for (int i = 0; i < game->num_rows; i++)
    fprintf(fp, "%s", game->board[i]);
  return;
}

/*
  Saves the current game into filename. Does not modify the game object.
  (already implemented for you).
*/
void save_board(game_t *game, char *filename) {
  FILE *f = fopen(filename, "w");
  print_board(game, f);
  fclose(f);
}

/* Task 4.1 */

/*
  Helper function to get a character from the board
  (already implemented for you).
*/
char get_board_at(game_t *game, unsigned int row, unsigned int col) {
  return game->board[row][col];
}

/*
  Helper function to set a character on the board
  (already implemented for you).
*/
static void set_board_at(game_t *game, unsigned int row, unsigned int col,
                         char ch) {
  game->board[row][col] = ch;
}

/*
  Returns true if c is part of the snake's tail.
  The snake consists of these characters: "wasd"
  Returns false otherwise.
*/
static bool is_tail(char c) {
  return c == 'w' || c == 'a' || c == 's' || c == 'd';
}

/*
  Returns true if c is part of the snake's head.
  The snake consists of these characters: "WASDx"
  Returns false otherwise.
*/
static bool is_head(char c) {
  return c == 'W' || c == 'A' || c == 'S' || c == 'D' || c == 'x';
}

/*
  Returns true if c is part of the snake.
  The snake consists of these characters: "wasd^<v>WASDx"
*/
static bool is_snake(char c) {
  char *snake = "wasd^<v>WASDx";
  if (strchr(snake, c) == NULL)
    return false;
  return true;
}

/*
  Converts a character in the snake's body ("^<v>")
  to the matching character representing the snake's
  tail ("wasd").
*/
static char body_to_tail(char c) {
  switch (c) {
  case '^':
    return 'w';
  case '<':
    return 'a';
  case 'v':
    return 's';
  case '>':
    return 'd';
  default:
    return '?';
  }
}

/*
Converts a character in the snake's head ("WASD")
to the matching character representing the snake's
body ("^<v>").
*/
static char head_to_body(char c) {
  switch (c) {
  case 'W':
    return '^';
  case 'A':
    return '<';
  case 'D':
    return '>';
  case 'S':
    return 'v';
  default:
    return '?';
  }
}

/*
  Returns cur_row + 1 if c is 'v' or 's' or 'S'.
  Returns cur_row - 1 if c is '^' or 'w' or 'W'.
  Returns cur_row otherwise.
*/
static unsigned int get_next_row(unsigned int cur_row, char c) {
  if (c == 'v' || c == 's' || c == 'S')
    return cur_row + 1;
  else if (c == '^' || c == 'w' || c == 'W')
    return cur_row - 1;
  else
    return cur_row;
}

/*
Returns cur_col + 1 if c is '>' or 'd' or 'D'.
Returns cur_col - 1 if c is '<' or 'a' or 'A'.
Returns cur_col otherwise.
*/
static unsigned int get_next_col(unsigned int cur_col, char c) {
  if (c == '>' || c == 'd' || c == 'D')
    return cur_col + 1;
  else if (c == '<' || c == 'a' || c == 'A')
    return cur_col - 1;
  else
    return cur_col;
}

/*
  Task 4.2

  Helper function for update_game. Return the character in the cell the snake is
  moving into.

  This function should not modify anything.
*/
static char next_square(game_t *game, unsigned int snum) {
  unsigned int row = game->snakes[snum].head_row;
  unsigned int col = game->snakes[snum].head_col;
  char head = get_board_at(game, row, col);
  char direction = head_to_body(head);
  unsigned int next_row = get_next_row(row, direction);
  unsigned int next_col = get_next_col(col, direction);

  return get_board_at(game, next_row, next_col);
}

/*
  Task 4.3

  Helper function for update_game. Update the head...

  ...on the board: add a character where the snake is moving

  ...in the snake struct: update the row and col of the head

  Note that this function ignores food, walls, and snake bodies when moving the
  head.
*/
static void update_head(game_t *game, unsigned int snum) {
  unsigned int row = game->snakes[snum].head_row;
  unsigned int col = game->snakes[snum].head_col;

  char head = get_board_at(game, row, col);
  char body = head_to_body(head);

  unsigned int next_row = get_next_row(row, body);
  unsigned int next_col = get_next_col(col, body);

  set_board_at(game, next_row, next_col, head);
  set_board_at(game, row, col, body);

  game->snakes[snum].head_row = next_row;
  game->snakes[snum].head_col = next_col;
  return;
}

/*
  Task 4.4

  Helper function for update_game. Update the tail...

  ...on the board: blank out the current tail, and change the new
  tail from a body character (^<v>) into a tail character (wasd)

  ...in the snake struct: update the row and col of the tail
*/
static void update_tail(game_t *game, unsigned int snum) {
  unsigned int row = game->snakes[snum].tail_row;
  unsigned int col = game->snakes[snum].tail_col;

  char tail = get_board_at(game, row, col);

  unsigned int next_row = get_next_row(row, tail);
  unsigned int next_col = get_next_col(col, tail);

  char body = get_board_at(game, next_row, next_col);
  char new_tail = body_to_tail(body);

  set_board_at(game, row, col, ' ');
  set_board_at(game, next_row, next_col, new_tail);

  game->snakes[snum].tail_row = next_row;
  game->snakes[snum].tail_col = next_col;
  return;
}

/* Task 4.5 */
void update_game(game_t *game, int (*add_food)(game_t *game)) {
  for (unsigned int i = 0; i < game->num_snakes; i++) {
    char ch = next_square(game, i);
    if (ch == '#' || is_snake(ch)) {
      unsigned int row = game->snakes[i].head_row;
      unsigned int col = game->snakes[i].head_col;
      set_board_at(game, row, col, 'x');
      game->snakes[i].live = false;
    } else if (ch == '*') {
      update_head(game, i);
      add_food(game);
    } else {
      update_head(game, i);
      update_tail(game, i);
    }
  }
  return;
}

/* Task 5.1 */
char *read_line(FILE *fp) {
  size_t BUFSIZE = 16;
  size_t length = 0;
  char *buf = malloc(sizeof(char) * BUFSIZE);

  while (fgets(buf + length, (int)(BUFSIZE - length), fp)) {
    if (strchr(buf + length, '\n')) {
      return buf;
    }

    length += strlen(buf + length);
    BUFSIZE *= 2;
    buf = realloc(buf, BUFSIZE);
  }

  if (length == 0) {
    free(buf);
  }

  // buf = realloc(buf, strlen(buf) + 1);

  return NULL;
}

/* Task 5.2 */
game_t *load_board(FILE *fp) {
  game_t *game = (game_t *)malloc(sizeof(game_t));
  game->num_rows = 0;
  game->snakes = NULL;
  game->num_snakes = 0;
  game->board = NULL;

  char *line = NULL;
  while ((line = read_line(fp))) {
    char **temp =
        (char **)realloc(game->board, (game->num_rows + 1) * sizeof(char *));

    if (temp == NULL) {
      free(temp);
      free(game->board);
      free(game);
      return NULL;
    }

    temp[game->num_rows] = line;
    game->board = temp;
    (game->num_rows)++;
  }

  return game;
}

/*
  Task 6.1

  Helper function for initialize_snakes.
  Given a snake struct with the tail row and col filled in,
  trace through the board to find the head row and col, and
  fill in the head row and col in the struct.
*/
static void find_head(game_t *game, unsigned int snum) {
  unsigned int row = game->snakes[snum].tail_row;
  unsigned int col = game->snakes[snum].tail_col;
  char cur_ch = get_board_at(game, row, col);

  // fflush(stdout);
  // printf("Snake %u Starts at: row=%u, col=%u\n", snum, row, col);

  while (!is_head(cur_ch)) {
    row = get_next_row(row, cur_ch);
    col = get_next_col(col, cur_ch);

    cur_ch = get_board_at(game, row, col);
    // printf("Stepping on: '%c' at row=%u, col=%u\n", cur_ch, row, col);
  }

  game->snakes[snum].head_row = row;
  game->snakes[snum].head_col = col;
  return;
}

/* Task 6.2 */
game_t *initialize_snakes(game_t *game) {
  unsigned int snakes = 0;
  for (unsigned int i = 0; i < game->num_rows; i++) {
    for (unsigned int j = 0; j < strlen(game->board[i]); j++) {
      char ch = get_board_at(game, i, j);
      if (is_tail(ch))
        snakes++;
    }
  }

  game->snakes = (snake_t *)malloc(sizeof(snake_t) * snakes);
  game->num_snakes = snakes;

  snakes = 0;
  for (unsigned int i = 0; i < game->num_rows; i++) {
    for (unsigned int j = 0; j < strlen(game->board[i]); j++) {
      char ch = get_board_at(game, i, j);
      if (is_tail(ch)) {
        game->snakes[snakes].tail_row = i;
        game->snakes[snakes].tail_col = j;
        game->snakes[snakes].live = true;

        find_head(game, snakes);
        snakes++;
      }
    }
  }
  return game;
}
