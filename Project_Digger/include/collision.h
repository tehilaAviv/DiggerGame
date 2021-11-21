#pragma once
#include <map>
#include"Object.h"

class Level;
//פונקציה כללית שמוצאת במפה את האוביקטים שמתנגשים ומטפלת בהתנגשותם
typedef void(*HitFunctionPtr)(Object&, Object&);
typedef std::map< std::pair<std::string, std::string>, HitFunctionPtr > HitMap;
class Collision
{
public:
	Collision() = default;
	HitFunctionPtr lookup(const std::string & , const std::string&);// מחפש את הפונקציה להפעלה
	~Collision() = default;

private:
	HitMap initializeCollisionMap();
};

void DiggerRegularMonster(Object& , Object& );
void RegularMonsterDigger(Object& , Object& );
void DiggerSpecialMonster(Object&, Object&);
void SpecialMonsterDigger(Object&, Object&);
void DiggerDiamond(Object&, Object&);
void DiamondDigger(Object&, Object&);
void DiggerStone(Object&, Object&);
void StoneDigger(Object&, Object&);
void DiggerGift(Object&, Object&);
void GiftDigger(Object&, Object&);
void RegularMonsterWall(Object&, Object&);
void WallRegularMonster(Object&, Object&);
void SpecialMonsterWall(Object&, Object&);
void WallSpecialMonster(Object&, Object&);
void SpecialMonsterStone(Object&, Object&);
void StoneSpecialMonster(Object&, Object&);
void RegularMonsterStone(Object&, Object&);
void StoneRegularMonster(Object&, Object&);
