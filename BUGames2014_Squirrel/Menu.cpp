#include "menu.h"
#include "windows.h"
const int Menu::MENU_ITEM_COUNT = 3;

Menu::Menu(SDL_Renderer* renderer, InputManager* input) 
{
	this->selectingPadId = -1;

	this->input = input;
	selectedIndex = 0;
	
	LoadImages(renderer);
}

Menu::~Menu() 
{

}

int Menu::Update() {
	//check for relevant keypresses
	if (input->WasKeyPressed(SDLK_DOWN))
		selectedIndex++;
	else if (input->WasKeyPressed(SDLK_UP))
		selectedIndex--;
	else if (input->WasKeyPressed(SDLK_RETURN)) {
		selectingPadId = -1;
		return selectedIndex;
	}

	//check for pads activity
	if (input->WasPadButtonPressedByAnyPad(SDL_CONTROLLER_BUTTON_DPAD_DOWN) != -1)
		selectedIndex++;
	else if (input->WasPadButtonPressedByAnyPad(SDL_CONTROLLER_BUTTON_DPAD_UP)  != -1)
		selectedIndex--; 
	else {
		selectingPadId = input->WasPadButtonPressedByAnyPad(SDL_CONTROLLER_BUTTON_START);
		if (selectingPadId != -1) {
			return selectedIndex;
		}
	}


	//keep selected index within bounds
	if (selectedIndex < 0) selectedIndex = MENU_ITEM_COUNT - 1;
	if (selectedIndex > MENU_ITEM_COUNT - 1) selectedIndex = 0;

	//if we get here then nothing has been selected
	return -1;
}

void Menu::DoSelection() {

	switch (selectedIndex) {
	case 0:
		std::cout << "New Game Selected\n";
		Beep( 1000, 100 );
		break;
	case 1:
		std::cout << "Credits\n";
		Beep( 4000, 100 );
		break;
	case 2:
		std::cout << "Exit \n";
		Beep( 5000, 100 );
		break;

	}

	//std::cout << "Menu - Item " << selectedIndex << " selected" << std::endl;
}

void Menu::Draw(SDL_Renderer* renderer) {
	int x = 100;
	int y = 100;
	
	for (int i = 0; i < MENU_ITEM_COUNT; i++) {
		if (i != selectedIndex)
			unselectedImages[i]->Draw(x, y, *renderer);
		else
			selectedImages[i]->Draw(x, y, *renderer);
		y += 75;
	}
}

void Menu::LoadImages(SDL_Renderer* renderer) {
	//load "unselected" images
	unselectedImages[0] = new Sprite("Content/MainMenu/menu1.png", renderer);
	//unselectedImages[1] = new Sprite("Content/MainMenu/menu2.png", renderer);
	//unselectedImages[2] = new Sprite("Content/MainMenu/menu3.png", renderer);
	unselectedImages[1] = new Sprite("Content/MainMenu/menu4.png", renderer);
	unselectedImages[2] = new Sprite("Content/MainMenu/menu5.png", renderer);

	//load "selected" images
	selectedImages[0] = new Sprite("Content/MainMenu/menu1_s.png", renderer);
	//selectedImages[1] = new Sprite("Content/MainMenu/menu2_s.png", renderer);
	//selectedImages[2] = new Sprite("Content/MainMenu/menu3_s.png", renderer);
	selectedImages[1] = new Sprite("Content/MainMenu/menu4_s.png", renderer);
	selectedImages[2] = new Sprite("Content/MainMenu/menu5_s.png", renderer);
}