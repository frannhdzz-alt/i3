/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Rodrigo and Mario
 * @version 3.0
 * @date 05-04-2026
 * @copyright GNU Public License
 */

#include "graphic_engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

typedef struct {
    Id id;
    char gdesc[5][10];
    char obj_list[20];
    char c_sym[7];
    char p_sym[4];
    Bool discovered;
} SpaceView;

void _get_space_objects_str(Game *game, Id space_id, char *out_str);
void _get_character_sym(Game *game, Id space_id, char *out_sym);
void _prepare_space_view(Game *game, Space *s, Id p_loc, SpaceView *view);

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

void _prepare_space_view(Game *game, Space *s, Id p_loc, SpaceView *view) {
    int i;
    Player *player = game_get_player(game);

    if (!s) {
        view->id = NO_ID;
        return;
    }

    view->id = space_get_id(s);
    view->discovered = space_get_discovered(s);
    
    strcpy(view->p_sym, "   ");
    if (p_loc == view->id && player_get_gdesc(player)) {
        strncpy(view->p_sym, player_get_gdesc(player), 3);
        view->p_sym[3] = '\0';
    }

    if (view->discovered == TRUE) {
     
        for (i = 0; i < 5; i++) {
            strcpy(view->gdesc[i], space_get_gdesc(s, i));
        }
        _get_space_objects_str(game, view->id, view->obj_list);
        _get_character_sym(game, view->id, view->c_sym);
    } else {
    
        for (i = 0; i < 5; i++) strcpy(view->gdesc[i], "         ");
        strcpy(view->gdesc[2], "  ???    ");
        strcpy(view->obj_list, "");
        strcpy(view->c_sym, "      ");
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

  Id p_loc = NO_ID;
  Space *space_act = NULL, *space_back = NULL, *space_next = NULL;
  Player *player = NULL;
  
  char str[512]; 
  int i;
  
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  
  SpaceView view_act, view_back, view_next;

  Object *o = NULL;
  Character *c = NULL;
  Id char_id = NO_ID;

  if (!game) return;

  player = game_get_player(game);
  p_loc = game_get_player_location(game);

  /* Map Area */
  screen_area_clear(ge->map);
  if (p_loc != NO_ID) {
    space_act = game_get_space(game, p_loc);
    space_back = game_get_space(game, game_get_connection(game, space_get_id(space_act), N)); 
    space_next = game_get_space(game, game_get_connection(game, space_get_id(space_act), S)); 

    _prepare_space_view(game, space_back, p_loc, &view_back);
    _prepare_space_view(game, space_act, p_loc, &view_act);
    _prepare_space_view(game, space_next, p_loc, &view_next);

    if (view_back.id != NO_ID) {
      sprintf(str, "                     +---------------+");
      screen_area_puts(ge->map, str);
      if (view_back.discovered) {
        sprintf(str, "                     | %-3s %-6s  %2d|", view_back.p_sym, view_back.c_sym, (int)view_back.id);
        screen_area_puts(ge->map, str);
        for (i = 0; i < 5; i++) {
          sprintf(str, "                     |   %-9s   |", view_back.gdesc[i]);
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "                     |%-15.15s|", view_back.obj_list);
        screen_area_puts(ge->map, str);
      } else {
        sprintf(str, "                     | %-3s %-6s  %2d|", "   ", "      ", (int)view_back.id);
        screen_area_puts(ge->map, str);
        for (i = 0; i < 5; i++) {
          sprintf(str, "                     |   %-9s   |", view_back.gdesc[i]);
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "                     |%-15.15s|", "");
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "                     +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                             ^");
      screen_area_puts(ge->map, str);
    }

    sprintf(str, "                     +---------------+");
    screen_area_puts(ge->map, str);
    sprintf(str, "                     | %-3s %-6s  %2d|", view_act.p_sym, view_act.c_sym, (int)view_act.id);
    screen_area_puts(ge->map, str);
    for (i = 0; i < 5; i++) {
        char w_link[3] = "  ", e_link[3] = "  ";
        if (i == 2) {
            if (game_get_connection(game, space_get_id(space_act), W) != NO_ID) strcpy(w_link, "<-");
            if (game_get_connection(game, space_get_id(space_act), E) != NO_ID) strcpy(e_link, "->");
        }
        sprintf(str, "                   %s|   %-9s   |%s", w_link, view_act.gdesc[i], e_link);
        screen_area_puts(ge->map, str);
    }
    sprintf(str, "                     |%-15.15s|", view_act.obj_list);
    screen_area_puts(ge->map, str);
    sprintf(str, "                     +---------------+");
    screen_area_puts(ge->map, str);

    if (view_next.id != NO_ID) {
      sprintf(str, "                             v");
      screen_area_puts(ge->map, str);
      sprintf(str, "                     +---------------+");
      screen_area_puts(ge->map, str);
      if (view_next.discovered) {
        sprintf(str, "                     | %-3s %-6s  %2d|", view_next.p_sym, view_next.c_sym, (int)view_next.id);
        screen_area_puts(ge->map, str);
        for (i = 0; i < 5; i++) {
          sprintf(str, "                     |   %-9s   |", view_next.gdesc[i]);
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "                     |%-15.15s|", view_next.obj_list);
        screen_area_puts(ge->map, str);
      } else {
        sprintf(str, "                     | %-3s %-6s  %2d|", "   ", "      ", (int)view_next.id);
        screen_area_puts(ge->map, str);
        for (i = 0; i < 5; i++) {
          sprintf(str, "                     |   %-9s   |", view_next.gdesc[i]);
          screen_area_puts(ge->map, str);
        }
        sprintf(str, "                     |%-15.15s|", "");
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "                     +---------------+");
      screen_area_puts(ge->map, str);
    }
  }


  screen_area_clear(ge->descript);
  

  screen_area_puts(ge->descript, "  =========================================");
  sprintf(str, "    PLAYER %ld STATUS   |   HEALTH: %d pts", player_get_id(player), player_get_health(player));
  screen_area_puts(ge->descript, str);
  screen_area_puts(ge->descript, "  =========================================");
  
  sprintf(str, "  > Current Location : %ld", game_get_player_location(game));
  screen_area_puts(ge->descript, str);
  

  {
      char player_objs[255] = ""; 
      Object *po_inv = NULL;
      for (i = 1; i <= MAX_OBJECTS; i++) {
          po_inv = game_get_object(game, i);
          if (po_inv != NULL && player_has_object(player, object_get_id(po_inv)) == TRUE) {
              if (strlen(player_objs) > 0) strcat(player_objs, ", ");
              strcat(player_objs, object_get_name(po_inv));
          }
      }
      if (strlen(player_objs) > 0) {
          sprintf(str, "  > Backpack       : %s", player_objs);
      } else {
          sprintf(str, "  > Backpack       : [EMPTY]");
      }
      screen_area_puts(ge->descript, str);
  }

  screen_area_puts(ge->descript, "  -----------------------------------------");
  screen_area_puts(ge->descript, "  VISIBLE ENTITIES (Discovered Spaces):");


  for (i = 1; i <= MAX_OBJECTS; i++) {
      o = game_get_object(game, i);
      if (o) {
          Id o_loc = game_get_object_location(game, i);
          Space *o_space = game_get_space(game, o_loc);
          if (o_space && space_get_discovered(o_space) == TRUE) {
              sprintf(str, "   [Obj] %-10s at Space %ld", object_get_name(o), o_loc);
              screen_area_puts(ge->descript, str);
          }
      }
  }

  for (i = 1; i <= MAX_CHARACTERS; i++) {
      c = game_get_character(game, i);
      if (c) {
          Id c_loc = game_get_character_location(game, i);
          Space *c_space = game_get_space(game, c_loc);
          if (c_space && space_get_discovered(c_space) == TRUE) {
            sprintf(str, "   [Chr] %-6s at Space %ld (HP:%d)", character_get_gdesc(c), c_loc, character_get_health(c));
            screen_area_puts(ge->descript, str);
          }
      }
  }

  screen_area_puts(ge->descript, "  -----------------------------------------");


  last_cmd = command_get_code(game_get_last_command(game));
  
  if (last_cmd == INSPECT) {
    const char *arg_name = command_get_arg(game_get_last_command(game));
    int found = 0;
    if (arg_name && arg_name[0] != '\0') {
      for (i = 1; i <= MAX_OBJECTS; i++) {
        o = game_get_object(game, i);
        if (o && strcasecmp(object_get_name(o), arg_name) == 0) {
          if (player_has_object(player, object_get_id(o)) == TRUE || 
              space_has_object(game_get_space(game, p_loc), object_get_id(o)) == TRUE) {
            sprintf(str, "  [INSPECT] %s", object_get_description(o));
            screen_area_puts(ge->descript, str);
            found = 1;
            break;
          }
        }
      }
      if (!found) screen_area_puts(ge->descript, "  [INSPECT] You can't inspect that here.");
    }
  }

  if (last_cmd == CHAT) {
      if (space_act != NULL && (char_id = space_get_character(space_act)) != NO_ID) {
          c = game_get_character(game, char_id);
          if (c != NULL) {
              if (character_get_friendly(c) == TRUE) sprintf(str, "  [CHAT] %s: \"%s\"", character_get_name(c), character_get_message(c));
              else sprintf(str, "  [CHAT] The %s is hostile!", character_get_name(c));
              screen_area_puts(ge->descript, str);
          }
      } else {
          screen_area_puts(ge->descript, "  [CHAT] Nobody is here.");
      }
  }


  sprintf(str, "   THE HAUNTED CASTLE");
  screen_area_puts(ge->banner, str);
  
  screen_area_clear(ge->help);
  screen_area_puts(ge->help, " Commands:");
  sprintf(str, " m [dir] | t/d [obj] | a | i [obj] | c | u [obj] | o [lnk] with [obj] | e");
  screen_area_puts(ge->help, str);

  sprintf(str, " %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  screen_area_puts(ge->feedback, str);


  if (player_get_id(player) == 1) screen_paint(CYAN);
  else if (player_get_id(player) == 2) screen_paint(GREEN);
  else screen_paint(WHITE);
  
  printf("prompt:> ");
}