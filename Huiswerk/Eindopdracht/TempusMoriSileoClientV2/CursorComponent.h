#pragma once
class CursorComponent : public Component
{
public:
	CursorComponent(bool isRighthand): isRightHand(isRighthand){};
	~CursorComponent(){};	
	virtual void update(Entity& entity);
	virtual void render(Entity& entity){};
private:
	bool isRightHand;
};

