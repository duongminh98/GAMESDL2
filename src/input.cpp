#include "common.h"
extern Game game;
void doKeyUp(SDL_KeyboardEvent *event)
{
    if (event->repeat == 0 and event->keysym.scancode < KEYBOARD)
    {
        game.keyboard[event->keysym.scancode] = 0;
    }
}
void doKeyDown(SDL_KeyboardEvent *event)
{
    if (event->repeat == 0 and event->keysym.scancode < KEYBOARD)
    {
        game.keyboard[event->keysym.scancode] = 1;
    }
}
void doInput()
{
	SDL_Event event;
	memset(game.inputText, '\0', MAX_LINE_LENGTH);
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_KEYDOWN:
                doKeyDown(&event.key);
                break;
            case SDL_KEYUP:
                doKeyUp(&event.key);
                break;
           	case SDL_TEXTINPUT:
				STRNCPY(game.inputText, event.text.text, MAX_LINE_LENGTH);
				break;
			case SDL_MOUSEBUTTONDOWN:
			{
				if(event.button.button==SDL_BUTTON_LEFT)
					game.mouse[0]=1;
				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				if(event.button.button==SDL_BUTTON_LEFT)
					game.mouse[0]=0;
				break;
			}
			default:
				break;
		}
	}
}
