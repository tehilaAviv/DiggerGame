#include "Collision.h"
#include <iostream>
#include "Digger.h"
#include "RegularMonster.h"
#include "SpecialMonster.h"
#include "Diamond.h"
#include "Stone.h"
#include <utility> 


HitFunctionPtr Collision::lookup(const std::string& class1, const std::string& class2)//מימוש הפונקציה אשר מחפשת את הפונקציה להפעלה
{
	static HitMap collisionMap(initializeCollisionMap());//האתחול מבוצע פעם אחת בלבד אודות לאובייקט הסטטי
	HitMap::iterator mapEntry = collisionMap.find(std::make_pair(class1, class2));
	if (mapEntry == collisionMap.end())
		return 0;
	return (*mapEntry).second;
}

HitMap Collision::initializeCollisionMap()//איתחול של מפת ההתנגשות
{
	HitMap phm;
	phm[std::make_pair(typeid(Digger).name(), typeid(RegularMonster).name())]= &DiggerRegularMonster;
	phm[std::make_pair(typeid(RegularMonster).name(), typeid(Digger).name())] = &RegularMonsterDigger;

	phm[std::make_pair(typeid(Digger).name(), typeid(SpecialMonster).name())] = &DiggerSpecialMonster;
	phm[std::make_pair(typeid(SpecialMonster).name(), typeid( Digger).name())] = &SpecialMonsterDigger;

	phm[std::make_pair(typeid(Digger).name(), typeid(Diamond).name())] = &DiggerDiamond;
	phm[std::make_pair(typeid(Diamond).name(), typeid( Digger).name())] = &DiamondDigger;

	phm[std::make_pair(typeid(Digger).name(), typeid(Stone).name())] = &DiggerStone;
	phm[std::make_pair(typeid(Stone).name(), typeid( Digger).name())] = &StoneDigger;

	phm[std::make_pair(typeid(Digger).name(), typeid(Gift).name())] = &DiggerGift;
	phm[std::make_pair(typeid(Gift).name(), typeid( Digger).name())] = &GiftDigger;

	phm[std::make_pair(typeid(RegularMonster).name(), typeid(Wall).name())] = &RegularMonsterWall;
	phm[std::make_pair(typeid(Wall).name(), typeid(RegularMonster).name())] = &WallRegularMonster;

	phm[std::make_pair(typeid(SpecialMonster).name(), typeid(Wall).name())] = &SpecialMonsterWall;
	phm[std::make_pair(typeid(Wall).name(), typeid(SpecialMonster).name())] = &WallSpecialMonster;

	phm[std::make_pair(typeid(SpecialMonster).name(), typeid(Stone).name())] = &SpecialMonsterStone;
	phm[std::make_pair(typeid(Stone).name(), typeid(SpecialMonster).name())] = &StoneSpecialMonster;

	phm[std::make_pair(typeid(RegularMonster).name(), typeid(Stone).name())] = &RegularMonsterStone;
	phm[std::make_pair(typeid(Stone).name(), typeid(RegularMonster).name())] = &StoneRegularMonster;

	return phm;
}

//1-------------------------------------------------------------------
void SpecialMonsterWall(Object& specialMonster, Object& wall) //פונקציה הבודקת התנגשות בין מפלצת מיוחדת לקיר
{
	SpecialMonster& m = dynamic_cast<SpecialMonster&>(specialMonster);
	m.setcanMove();//עצירת תזוזת המפלצת המיוחדת בגלל התנגשות בקיר
	m.setDirection();//שינוי התזוזה לכיוון הנגדי
}


void WallSpecialMonster(Object& wall, Object& specialMonster) //פונקציה הבודקת התנגשות בין קיר למפלצת מיוחדת
{
	SpecialMonsterWall(specialMonster, wall);
}
//2-------------------------------------------------------------------

void SpecialMonsterStone(Object& specialMonster, Object& stone) //פונקציה הבודקת התנגשות בין מפלצת מיוחדת לאבן
{
	SpecialMonster& m = dynamic_cast<SpecialMonster&>(specialMonster);
	m.setcanMove();//עצירת תזוזת המפלצת המיוחדת בגלל התנגשות באבן
	m.setDirection();//שינוי התזוזה לכיוון הנגדי
}

void StoneSpecialMonster(Object& stone, Object& specialMonster)//פונקציה הבודקת התנגשות בין אבן למפלצת מיוחדת
{
	SpecialMonsterStone(specialMonster, stone);
}

//3-------------------------------------------------------------------

void RegularMonsterStone(Object& regularMonster, Object& stone)//פונקציה הבודקת התנגשות בין מפלצת רגילה לאבן
{
	RegularMonster& m = dynamic_cast<RegularMonster&>(regularMonster);
	m.setcanMove();//עצירת תזוזת המפלצת בגלל התנגשות באבן
	m.setDirection();//שינוי התזוזה לכיוון הנגדי
}
void StoneRegularMonster(Object& stone, Object& regularMonster)//פונקציה הבודקת התנגשות בין אבן למפלצת רגילה
{
	RegularMonsterStone(regularMonster, stone);
}

//4-------------------------------------------------------------------
void RegularMonsterWall(Object& regularMonste, Object& wall) //פונקציה הבודקת התנגשות בין מפלצת רגילה לקיר
{
	RegularMonster& m = dynamic_cast<RegularMonster&>(regularMonste);
	m.setcanMove();//עצירת תזוזת המפלצת בגלל התנגשות בקיר
	m.setDirection();//שינוי התזוזה לכיוון הנגדי
}

void WallRegularMonster(Object& wall, Object& regularMonste)//פונקציה הבודקת התנגשות בין קיר למפלצת רגילה 
{
	RegularMonsterWall(regularMonste, wall);
}
//5-------------------------------------------------------------------
void DiggerRegularMonster(Object& digger, Object& regularMonster) //פונקציה הבודקת התנגשות בין שחקן למפלצת רגילה
{
	Digger& d = dynamic_cast<Digger&>(digger);
	d.decreasLives();//בעת התנגשות של שחקן עם מפלצת נוריד חיים 
	d.setNeedToSetBoard(true);//מתחיל את השלב מחדש
}

void RegularMonsterDigger(Object& regularMonster, Object& digger)//פונקציה הבודקת התנגשות בין מפלצת רגילה לשחקן
{
	DiggerRegularMonster(digger, regularMonster);
}

//6-------------------------------------------------------------------
void DiggerSpecialMonster(Object& digger, Object& specialMonster) //פונקציה הבודקת התנגשות בין שחקן למפלצת מיוחדת
{
	Digger& d = dynamic_cast<Digger&>(digger);
	d.decreasLives();//בעת התנגשות של שחקן עם מפלצת מיוחדת נוריד חיים
	d.setNeedToSetBoard(true);//מתחיל את השלב מחדש
}

void SpecialMonsterDigger(Object& specialMonster, Object& digger)  //פונקציה הבודקת התנגשות בין מפלצת מיוחדת לשחקן
{
	DiggerSpecialMonster(digger, specialMonster);
}

//7-------------------------------------------------------------------
void DiggerDiamond(Object& digger, Object& diamond) //פונקציה הבודקת התנגשות בין שחקן ליהלום
{
	Digger& d = dynamic_cast<Digger&>(digger);
	Diamond& diamond1 = dynamic_cast<Diamond&>(diamond);
	d.setNumScores(15);//בעת התנגשות של שחקן עם יהלום נוסיף 15 נקודות  
	diamond1.clean(' ');//הסרת היהלום מהלוח
	d.decreaseDiamond();
}

void DiamondDigger(Object& diamond, Object& digger)//פונקציה הבודקת התנגשות בין יהלום לשחקן
{
	DiggerDiamond(digger, diamond);
}

//-------------------------------------------------------------------
void DiggerStone(Object& digger, Object& stone) //פונקציה הבודקת התנגשות בין שחקן לאבן
{
	Digger& d = dynamic_cast<Digger&>(digger);
	Stone& s = dynamic_cast<Stone&>(stone);
	if (d.getNumStones() > 0)//כל עוד מספר האבנים גדול מאפס 
	{
		d.decreasnumOfStones();//בעת התנגשות של שחקן עם אבן נוריד לו את כמות האבנים המותרות באחד
		s.clean(' ');//מחיקת האבן מהלוח
	}
	else
		d.setCanMove(false);//אם נגמרו לו כמות האבנים שמותרות לו לאכול הוא לא יכול לאכול את האבן שרצה 
}


void StoneDigger(Object& stone, Object& digger)//פונקציה הבודקת התנגשות בין אבן לשחקן
{
	DiggerStone(digger, stone);
}
//8-------------------------------------------------------------------

void DiggerGift(Object& digger, Object& gift)//פונקציה הבודקת התנגשות בין שחקן למתנות
{
	Digger& d = dynamic_cast<Digger&>(digger);
	Gift& g = dynamic_cast<Gift&>(gift);
	int SpecialKey = g.getSpecialKey();//קריאה לפונקציה שמזהה איזה מתנה נבחרה
	switch (SpecialKey)
	{
	case 0: d.setNumScores(15);//מתנה המעלה ניקוד ב15
		g.clean(' ');
		break;
	case 1:d.setAddingTime();// מתנה המעלה זמן ב30 שניות
		g.clean(' ');
		break;
	case 2:d.setNumStonesGift();//מתנה המעלה את כמות האבנים שהשחקן יכול לאכול
		g.clean(' ');
		break;
	default:
		break;
	}
}

void GiftDigger(Object& gift, Object& digger) //פונקציה הבודקת התנגשות בין מתנות לשחקן
{
	DiggerGift(digger, gift);
}


