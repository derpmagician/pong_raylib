#ifndef MENU_H
#define MENU_H

#include <game_state.h>

enum MenuOption {
    MENU_PLAY = 0,
    MENU_SETTINGS = 1,
    MENU_QUIT = 2,
    MENU_OPTION_COUNT = 3
};

void LoadMenuSounds();
void UnloadMenuSounds();

void UpdateMenu(Game* game, bool* shouldExit);
void DrawMenu();

void UpdateSettings(Game* game);
void DrawSettings(Game* game);

#endif
