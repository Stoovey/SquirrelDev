#include"level.h"

level::level(){
	platformBlocks = new std::vector<Sprite*>;
	goalLocations  = new std::vector<Vector2D*>;

	goalLocations->push_back(new Vector2D(300, 120));
	goalLocations->push_back(new Vector2D(920, 120));
	goalLocations->push_back(new Vector2D(920, 440));
	goalLocations->push_back(new Vector2D(300, 440));

	srand((unsigned int)time(NULL));
}

void level::init(SDL_Renderer* render){
	grass = new Sprite("Resources/block.png",render);
	PopulateBlocksVector(render);
}

level::~level(){
	delete grass;

	//get rid of platform block sprites
	for (unsigned int i = 0; i < platformBlocks->size(); i++)
		delete platformBlocks->at(i);
	delete platformBlocks;

	//get rid of platform block sprites
	for (unsigned int i = 0; i < goalLocations->size(); i++)
		delete goalLocations->at(i);
	delete goalLocations;
}

void level::PopulateBlocksVector(SDL_Renderer* render) {
	//HARDCODE THE LEVEL DESIGN
	std::string grassBlock = "Resources/block.png";
	
	std::string Block1 = "Assets/block_1.png";
	std::string Block2 = "Assets/block_2.png";
	std::string Block3 = "Assets/block_3.png";
	std::string Block4 = "Assets/block_4.png";
	std::string Block5 = "Assets/block_5.png";
	std::string BlockL = "Assets/block_end_left.png";
	std::string BlockR = "Assets/block_end_right.png";

	//FLOOR
	platformBlocks->push_back(new Sprite(BlockL, 64*6+32,720-32,32,32,*render));
	platformBlocks->push_back(new Sprite(Block1, 64*6+32*2,720-32,32,32,*render));
	platformBlocks->push_back(new Sprite(Block3, 64*6+32*3,720-32,32,32,*render));
	platformBlocks->push_back(new Sprite(Block2, 64*6+32*4,720-32,32,32,*render));
	platformBlocks->push_back(new Sprite(Block5, 64*6+32*5,720-32,32,32,*render));
	platformBlocks->push_back(new Sprite(Block4, 64*6+32*6,720-32,32,32,*render));
	platformBlocks->push_back(new Sprite(Block1, 64*6+32*7,720-32,32,32,*render));
	platformBlocks->push_back(new Sprite(Block2, 64*6+32*8,720-32,32,32,*render));
	platformBlocks->push_back(new Sprite(Block4, 64*6+32*9,720-32,32,32,*render));
	platformBlocks->push_back(new Sprite(Block3, 64*6+32*10,720-32,32,32,*render));
	platformBlocks->push_back(new Sprite(Block5, 64*6+32*11,720-32,32,32,*render));
	platformBlocks->push_back(new Sprite(Block2, 64*6+32*12,720-32,32,32,*render));
	platformBlocks->push_back(new Sprite(Block5, 64*6+32*13,720-32,32,32,*render));
	platformBlocks->push_back(new Sprite(Block4, 64*6+32*14,720-32,32,32,*render));
	platformBlocks->push_back(new Sprite(BlockR, 64*6+32*15,720-32,32,32,*render));
	
	//BOTTOM
	platformBlocks->push_back(new Sprite(BlockL, 64*3,720-32*6,32,32,*render));
	platformBlocks->push_back(new Sprite(Block1, 64*3+32,720-32*6,32,32,*render));
	platformBlocks->push_back(new Sprite(Block2, 64*3+32*2,720-32*6,32,32,*render));
	platformBlocks->push_back(new Sprite(Block3, 64*3+32*3,720-32*6,32,32,*render));
	platformBlocks->push_back(new Sprite(Block4, 64*3+32*4,720-32*6,32,32,*render));
	platformBlocks->push_back(new Sprite(Block5, 64*3+32*5,720-32*6,32,32,*render));
	platformBlocks->push_back(new Sprite(Block3, 64*3+32*6,720-32*6,32,32,*render));
	platformBlocks->push_back(new Sprite(Block2, 64*3+32*7,720-32*6,32,32,*render));
	platformBlocks->push_back(new Sprite(BlockR, 64*3+32*8,720-32*6,32,32,*render));

	platformBlocks->push_back(new Sprite(BlockL, 1280-64*3-(32*8),720-32*6,32,32,*render));
	platformBlocks->push_back(new Sprite(Block3, 1280-64*3-(32*7),720-32*6,32,32,*render));
	platformBlocks->push_back(new Sprite(Block2, 1280-64*3-(32*6),720-32*6,32,32,*render));
	platformBlocks->push_back(new Sprite(Block1, 1280-64*3-(32*5),720-32*6,32,32,*render));
	platformBlocks->push_back(new Sprite(Block4, 1280-64*3-(32*4),720-32*6,32,32,*render));
	platformBlocks->push_back(new Sprite(Block5, 1280-64*3-(32*3),720-32*6,32,32,*render));
	platformBlocks->push_back(new Sprite(Block1, 1280-64*3-(32*2),720-32*6,32,32,*render));
	platformBlocks->push_back(new Sprite(Block2, 1280-64*3-(32*1),720-32*6,32,32,*render));
	platformBlocks->push_back(new Sprite(BlockR, 1280-64*3-32,720-32*6,32,32,*render));

	//MID
	platformBlocks->push_back(new Sprite(BlockL, 0,720-32*11,32,32,*render));
	platformBlocks->push_back(new Sprite(Block3, 0+32,720-32*11,32,32,*render));
	platformBlocks->push_back(new Sprite(Block2, 0+32*2,720-32*11,32,32,*render));
	platformBlocks->push_back(new Sprite(Block5, 0+32*3,720-32*11,32,32,*render));
	platformBlocks->push_back(new Sprite(Block4, 0+32*4,720-32*11,32,32,*render));
	platformBlocks->push_back(new Sprite(BlockR, 0+32*5,720-32*11,32,32,*render));

	platformBlocks->push_back(new Sprite(BlockR, 1280/2+(32*4),720-32*11,32,32,*render));
	platformBlocks->push_back(new Sprite(Block3, 1280/2+(32*3),720-32*11,32,32,*render));
	platformBlocks->push_back(new Sprite(Block4, 1280/2+(32*2),720-32*11,32,32,*render));
	platformBlocks->push_back(new Sprite(Block3, 1280/2+32,720-32*11,32,32,*render));
	platformBlocks->push_back(new Sprite(Block1, 1280/2,720-32*11,32,32,*render));
	platformBlocks->push_back(new Sprite(BlockL, 1280/2-(32*4),720-32*11,32,32,*render));
	platformBlocks->push_back(new Sprite(Block4, 1280/2-(32*3),720-32*11,32,32,*render));
	platformBlocks->push_back(new Sprite(Block3, 1280/2-(32*2),720-32*11,32,32,*render));
	platformBlocks->push_back(new Sprite(Block1, 1280/2-32,720-32*11,32,32,*render));


	platformBlocks->push_back(new Sprite(BlockL, 1280-(32*6),720-32*11,32,32,*render));
	platformBlocks->push_back(new Sprite(Block1, 1280-(32*5),720-32*11,32,32,*render));
	platformBlocks->push_back(new Sprite(Block4, 1280-(32*4),720-32*11,32,32,*render));
	platformBlocks->push_back(new Sprite(Block2, 1280-(32*3),720-32*11,32,32,*render));
	platformBlocks->push_back(new Sprite(Block5, 1280-(32*2),720-32*11,32,32,*render));
	platformBlocks->push_back(new Sprite(BlockR, 1280-32,720-32*11,32,32,*render));
	
	//TOP
	platformBlocks->push_back(new Sprite(BlockL, 64*3,720-32*16,32,32,*render));
	platformBlocks->push_back(new Sprite(Block4, 64*3+32,720-32*16,32,32,*render));
	platformBlocks->push_back(new Sprite(Block1, 64*3+32*2,720-32*16,32,32,*render));
	platformBlocks->push_back(new Sprite(Block2, 64*3+32*3,720-32*16,32,32,*render));
	platformBlocks->push_back(new Sprite(Block3, 64*3+32*4,720-32*16,32,32,*render));
	platformBlocks->push_back(new Sprite(Block5, 64*3+32*5,720-32*16,32,32,*render));
	platformBlocks->push_back(new Sprite(Block4, 64*3+32*6,720-32*16,32,32,*render));
	platformBlocks->push_back(new Sprite(Block1, 64*3+32*7,720-32*16,32,32,*render));
	platformBlocks->push_back(new Sprite(BlockR, 64*3+32*8,720-32*16,32,32,*render));

	platformBlocks->push_back(new Sprite(BlockL, 1280-64*3-(32*8),720-32*16,32,32,*render));
	platformBlocks->push_back(new Sprite(Block4, 1280-64*3-(32*7),720-32*16,32,32,*render));
	platformBlocks->push_back(new Sprite(Block3, 1280-64*3-(32*6),720-32*16,32,32,*render));
	platformBlocks->push_back(new Sprite(Block1, 1280-64*3-(32*5),720-32*16,32,32,*render));
	platformBlocks->push_back(new Sprite(Block2, 1280-64*3-(32*4),720-32*16,32,32,*render));
	platformBlocks->push_back(new Sprite(Block5, 1280-64*3-(32*3),720-32*16,32,32,*render));
	platformBlocks->push_back(new Sprite(Block3, 1280-64*3-(32*2),720-32*16,32,32,*render));
	platformBlocks->push_back(new Sprite(Block2, 1280-64*3-(32*1),720-32*16,32,32,*render));
	platformBlocks->push_back(new Sprite(BlockR, 1280-64*3-32,720-32*16,32,32,*render));
}

void level::drawLevel(SDL_Renderer* render) {
		
	for (unsigned int i = 0; i < platformBlocks->size(); i++)
		platformBlocks->at(i)->Draw(*render);
}
	
std::vector<Sprite*>* level::GetPlatformBlocks() {
	return platformBlocks;
}

Vector2D* level::GetAGoalLocation() {
	int random = rand(); 
	int index = random % (int)goalLocations->size();

	return goalLocations->at(index); 
}