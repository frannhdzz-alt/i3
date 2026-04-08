/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Rodrigo and Mario
 * @version 2.0
 * @date 12-03-2026
 * @copyright GNU Public License
 */

#include "graphic_engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"
#include "player.h"
#include "object.h"
#include "character.h"

#define WIDTH_MAP 62 
#define WIDTH_DES 45
#define WIDTH_BAN 25
#define HEIGHT_MAP 24 
#define HEIGHT_BAN 1
#define HEIGHT_HLP 2
#define HEIGHT_FDB 3

struct _Graphic_engine {
  Area *map, *descript, *banner, *help, *feedback;
};

void _get_space_objects_str(Game *game, Id space_id, char *out_str);
void _get_character_sym(Game *game, Id space_id, char *out_sym);

void _get_space_objects_str(Game *game, Id space_id, char *out_str) {
  int i;
  char temp[255] = "";
  out_str[0] = '\0';
  if (space_id == NO_ID) return;
  
  for (i = 1; i <= MAX_OBJECTS; i++) {
    if (game_get_object_location(game, i) == space_id) {
      if (strlen(temp) > 0) strcat(temp, ",");
      strcat(temp, object_get_name(game_get_object(game, i)));
    }
  }
  
  strncpy(out_str, temp, 15);
  out_str[15] = '\0';
}

void _get_character_sym(Game *game, Id space_id, char *out_sym) {
  Id char_id;
  Character *c;
  strcpy(out_sym, "      "); 
  if (space_id == NO_ID) return;
  
  char_id = space_get_character(game_get_space(game, space_id));
  if (char_id != NO_ID) {
    c = game_get_character(game, char_id);
    if (c) {
      strncpy(out_sym, character_get_gdesc(c), 6);
      out_sym[6] = '\0';
    }
  }
}

Graphic_engine *graphic_engine_create() {
  static Graphic_engine *ge = NULL;

  if (ge) return ge;

  screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + 3);
  ge = (Graphic_engine *)calloc(1, sizeof(Graphic_engine));
  if (ge == NULL) return NULL;

  ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
  ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
  ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
  ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
  ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

  return ge;
}

void graphic_engine_destroy(Graphic_engine *ge) {
  if (!ge) return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, p_obj = NO_ID;
  Id id_west = NO_ID, id_east = NO_ID, char_id = NO_ID;
  Space *space_act = NULL, *space_back = NULL, *space_next = NULL;
  Space *space_west = NULL, *space_east = NULL;
  Object *po = NULL;
  Character *c = NULL;
  Player *player = game_get_player(game);
  
  char str[255];
  char left_str[60], center_str[60], right_str[60];
  char west_link[3], east_link[3];
  
  char p_sym[4] = "   ";
  char c_sym_back[7], c_sym_act[7], c_sym_next[7], c_sym_west[7], c_sym_east[7];
  char obj_back[16], obj_act[16], obj_next[16], obj_west[16], obj_east[16];
  
  int i;
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  
  if (player_get_gdesc(player) && strlen(player_get_gdesc(player)) > 0) {
    strncpy(p_sym, player_get_gdesc(player), 3);
    p_sym[3] = '\0';
  }

  /* Map Area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID) {
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);
    id_west = space_get_west(space_act);
    id_east = space_get_east(space_act);

    if (id_west != NO_ID) space_west = game_get_space(game, id_west);
    if (id_east != NO_ID) space_east = game_get_space(game, id_east);

    _get_character_sym(game, id_back, c_sym_back);
    _get_character_sym(game, id_act, c_sym_act);
    _get_character_sym(game, id_next, c_sym_next);
    _get_character_sym(game, id_west, c_sym_west);
    _get_character_sym(game, id_east, c_sym_east);

    _get_space_objects_str(game, id_back, obj_back);
    _get_space_objects_str(game, id_act, obj_act);
    _get_space_objects_str(game, id_next, obj_next);
    _get_space_objects_str(game, id_west, obj_west);
    _get_space_objects_str(game, id_east, obj_east);

    if (id_back != NO_ID) {
      space_back = game_get_space(game, id_back);
      sprintf(str, "                     +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                     | %-3s %-6s  %2d|", "   ", c_sym_back, (int)id_back);
      screen_area_puts(ge->map, str);
      for (i = 0; i < 5; i++) {
          sprintf(str, "                     |   %-9s   |", space_get_gdesc(space_back, i));
          screen_area_puts(ge->map, str);
      }
      sprintf(str, "                     |%-15.15s|", obj_back);
      screen_area_puts(ge->map, str);
      sprintf(str, "                     +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                             ^");
      screen_area_puts(ge->map, str);
    }

    if (id_west != NO_ID) sprintf(left_str, "  +---------------+");
    else sprintf(left_str, "                   ");
    sprintf(center_str, "  +---------------+  ");
    if (id_east != NO_ID) sprintf(right_str, "+---------------+");
    else sprintf(right_str, "                 ");
    sprintf(str, "%s%s%s", left_str, center_str, right_str);
    screen_area_puts(ge->map, str);

    if (id_west != NO_ID) sprintf(left_str, "  | %-3s %-6s  %2d|", "   ", c_sym_west, (int)id_west);
    else sprintf(left_str, "                   ");
    sprintf(center_str, "  | %-3s %-6s  %2d|  ", p_sym, c_sym_act, (int)id_act);
    if (id_east != NO_ID) sprintf(right_str, "| %-3s %-6s  %2d|", "   ", c_sym_east, (int)id_east);
    else sprintf(right_str, "                 ");
    sprintf(str, "%s%s%s", left_str, center_str, right_str);
    screen_area_puts(ge->map, str);

    for (i = 0; i < 5; i++) {
        if (id_west != NO_ID) sprintf(left_str, "  |   %-9s   |", space_get_gdesc(space_west, i));
        else sprintf(left_str, "                   ");
        
        strcpy(west_link, "  ");
        strcpy(east_link, "  ");
        if (i == 2) {
            if (id_west != NO_ID) strcpy(west_link, "<-");
            if (id_east != NO_ID) strcpy(east_link, "->");
        }
        
        sprintf(center_str, "%s|   %-9s   |%s", west_link, space_get_gdesc(space_act, i), east_link);
        
        if (id_east != NO_ID) sprintf(right_str, "|   %-9s   |", space_get_gdesc(space_east, i));
        else sprintf(right_str, "                 ");
        
        sprintf(str, "%s%s%s", left_str, center_str, right_str);
        screen_area_puts(ge->map, str);
    }

    if (id_west != NO_ID) sprintf(left_str, "  |%-15.15s|", obj_west);
    else sprintf(left_str, "                   ");
    sprintf(center_str, "  |%-15.15s|  ", obj_act);
    if (id_east != NO_ID) sprintf(right_str, "|%-15.15s|", obj_east);
    else sprintf(right_str, "                 ");
    sprintf(str, "%s%s%s", left_str, center_str, right_str);
    screen_area_puts(ge->map, str);

    if (id_west != NO_ID) sprintf(left_str, "  +---------------+");
    else sprintf(left_str, "                   ");
    sprintf(center_str, "  +---------------+  ");
    if (id_east != NO_ID) sprintf(right_str, "+---------------+");
    else sprintf(right_str, "                 ");
    sprintf(str, "%s%s%s", left_str, center_str, right_str);
    screen_area_puts(ge->map, str);

    if (id_next != NO_ID) {
      space_next = game_get_space(game, id_next);
      sprintf(str, "                             v");
      screen_area_puts(ge->map, str);
      sprintf(str, "                     +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                     | %-3s %-6s  %2d|", "   ", c_sym_next, (int)id_next);
      screen_area_puts(ge->map, str);
      for (i = 0; i < 5; i++) {
          sprintf(str, "                     |   %-9s   |", space_get_gdesc(space_next, i));
          screen_area_puts(ge->map, str);
      }
      sprintf(str, "                     |%-15.15s|", obj_next);
      screen_area_puts(ge->map, str);
      sprintf(str, "                     +---------------+");
      screen_area_puts(ge->map, str);
    }
  }

  /* Description Area */
  screen_area_clear(ge->descript);
  
  sprintf(str, "  Objects Location:");
  screen_area_puts(ge->descript, str);
  for (i = 1; i <= MAX_OBJECTS; i++) {
      Object *o = game_get_object(game, i);
      if (o) {
          Id o_loc = game_get_object_location(game, i);
          if (o_loc != NO_ID) {
              sprintf(str, "  %-12s:%ld", object_get_name(o), o_loc);
              screen_area_puts(ge->descript, str);
          }
      }
  }

  screen_area_puts(ge->descript, " ");
  sprintf(str, "  Characters:");
  screen_area_puts(ge->descript, str);
  for (i = 1; i <= MAX_CHARACTERS; i++) {
      c = game_get_character(game, i);
      if (c) {
          Id c_loc = game_get_character_location(game, i);
          sprintf(str, "  %-6s:%ld (%d pts)", character_get_gdesc(c), c_loc, character_get_health(c));
          screen_area_puts(ge->descript, str);
      }
  }

screen_area_puts(ge->descript, " ");
Inventory *inv;
Set *objs;
int i;

inv = player_get_inventory(player);
objs = inventory_get_objects(inv);
Set *objs = inventory_get_objects(inv);

if (set_get_n_ids(objs) > 0)
  p_obj = set_get_id_at(objs, 0);
else
  p_obj = NO_ID;

  sprintf(str, "  Player loc :%ld (%d pts)", game_get_player_location(game), player_get_health(player));
  screen_area_puts(ge->descript, str);
  if (p_obj != NO_ID) {
      po = game_get_object(game, p_obj);
      sprintf(str, "  Player has object: %s", po ? object_get_name(po) : "Unknown");
  } else {
      sprintf(str, "  Player has no objects");
  }
  screen_area_puts(ge->descript, str);

 /* Chat System */
if (last_cmd == INSPECT) {
  const char *arg_name = command_get_arg(game_get_last_command(game));
  Object *o = NULL;
  Id space_id = game_get_player_location(game);
  int found = 0;
  
  screen_area_puts(ge->descript, " ");
  
  if (arg_name && arg_name[0] != '\0') {
    for (i = 1; i <= MAX_OBJECTS; i++) {
      o = game_get_object(game, i);
      if (o && strcasecmp(object_get_name(o), arg_name) == 0) {

      
        if (player_has_object(player, object_get_id(o)) == TRUE ||
            space_has_object(game_get_space(game, space_id), object_get_id(o)) == TRUE) {

          sprintf(str, "  Inspect: %s", object_get_description(o));
          screen_area_puts(ge->descript, str);
          found = 1;
          break;
        }
      }
    }

    if (!found) {
      screen_area_puts(ge->descript, "  Inspect: You can't inspect that here.");
    }
  }
}

  last_cmd = command_get_code(game_get_last_command(game));
  if (last_cmd == CHAT) {
      screen_area_puts(ge->descript, " "); 
      
      if (space_act != NULL && (char_id = space_get_character(space_act)) != NO_ID) {
          c = game_get_character(game, char_id);
          if (c != NULL) {
              if (character_get_friendly(c) == TRUE) {
                  sprintf(str, "  Chat: %s", character_get_message(c));
              } else {
                  sprintf(str, "  Chat: The %s is hostile! No talking.", character_get_name(c));
              }
              screen_area_puts(ge->descript, str);
          }
      } else {
          screen_area_puts(ge->descript, "  Chat: There is no one here to talk to.");
      }
  }

  /* Banner and Help Areas */
  screen_area_puts(ge->banner, " The haunted castle game ");
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, " next(n), back(b), left(l), right(r), take(t) [obj], drop(d), attack(a), chat(c), exit(e)");
  screen_area_puts(ge->help, str);

  /* Feedback Area */
  sprintf(str, " %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  screen_area_puts(ge->feedback, str);

  /* Dump to terminal */
  screen_paint();
  printf("prompt:> ");
}