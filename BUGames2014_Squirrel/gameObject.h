#ifndef gameObject_h
#define gameObject_h

#include"baseObjects.h"
#include"sprite.h"
#include<vector>

class gameObject :public baseObjects{
protected:
	sprite* displaySprite;	
	bool	alive;
	bool	active;
	int		state;
public:
	gameObject();
	~gameObject();

	virtual void	draw(SDL_Surface* screen);
	virtual void	update(SDL_Surface* screen);
	virtual void	handleInput(SDL_Event evt)=0;

	void			setDisplaySprite(sprite* spr);
	void			setActive(bool ta);
	void			setAlive(bool ta);
	void			setState(int ts);
	bool			getActive();
	bool			getAlive();
	int				getState();
};

#endif