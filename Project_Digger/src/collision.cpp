#include "Collision.h"
#include <iostream>
#include "Digger.h"
#include "RegularMonster.h"
#include "SpecialMonster.h"
#include "Diamond.h"
#include "Stone.h"
#include <utility> 


HitFunctionPtr Collision::lookup(const std::string& class1, const std::string& class2)//����� �������� ��� ����� �� �������� ������
{
	static HitMap collisionMap(initializeCollisionMap());//������ ����� ��� ��� ���� ����� �������� �����
	HitMap::iterator mapEntry = collisionMap.find(std::make_pair(class1, class2));
	if (mapEntry == collisionMap.end())
		return 0;
	return (*mapEntry).second;
}

HitMap Collision::initializeCollisionMap()//������ �� ��� ��������
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
void SpecialMonsterWall(Object& specialMonster, Object& wall) //������� ������ ������� ��� ����� ������ ����
{
	SpecialMonster& m = dynamic_cast<SpecialMonster&>(specialMonster);
	m.setcanMove();//����� ����� ������ ������� ���� ������� ����
	m.setDirection();//����� ������ ������ �����
}


void WallSpecialMonster(Object& wall, Object& specialMonster) //������� ������ ������� ��� ��� ������ ������
{
	SpecialMonsterWall(specialMonster, wall);
}
//2-------------------------------------------------------------------

void SpecialMonsterStone(Object& specialMonster, Object& stone) //������� ������ ������� ��� ����� ������ ����
{
	SpecialMonster& m = dynamic_cast<SpecialMonster&>(specialMonster);
	m.setcanMove();//����� ����� ������ ������� ���� ������� ����
	m.setDirection();//����� ������ ������ �����
}

void StoneSpecialMonster(Object& stone, Object& specialMonster)//������� ������ ������� ��� ��� ������ ������
{
	SpecialMonsterStone(specialMonster, stone);
}

//3-------------------------------------------------------------------

void RegularMonsterStone(Object& regularMonster, Object& stone)//������� ������ ������� ��� ����� ����� ����
{
	RegularMonster& m = dynamic_cast<RegularMonster&>(regularMonster);
	m.setcanMove();//����� ����� ������ ���� ������� ����
	m.setDirection();//����� ������ ������ �����
}
void StoneRegularMonster(Object& stone, Object& regularMonster)//������� ������ ������� ��� ��� ������ �����
{
	RegularMonsterStone(regularMonster, stone);
}

//4-------------------------------------------------------------------
void RegularMonsterWall(Object& regularMonste, Object& wall) //������� ������ ������� ��� ����� ����� ����
{
	RegularMonster& m = dynamic_cast<RegularMonster&>(regularMonste);
	m.setcanMove();//����� ����� ������ ���� ������� ����
	m.setDirection();//����� ������ ������ �����
}

void WallRegularMonster(Object& wall, Object& regularMonste)//������� ������ ������� ��� ��� ������ ����� 
{
	RegularMonsterWall(regularMonste, wall);
}
//5-------------------------------------------------------------------
void DiggerRegularMonster(Object& digger, Object& regularMonster) //������� ������ ������� ��� ���� ������ �����
{
	Digger& d = dynamic_cast<Digger&>(digger);
	d.decreasLives();//��� ������� �� ���� �� ����� ����� ���� 
	d.setNeedToSetBoard(true);//����� �� ���� ����
}

void RegularMonsterDigger(Object& regularMonster, Object& digger)//������� ������ ������� ��� ����� ����� �����
{
	DiggerRegularMonster(digger, regularMonster);
}

//6-------------------------------------------------------------------
void DiggerSpecialMonster(Object& digger, Object& specialMonster) //������� ������ ������� ��� ���� ������ ������
{
	Digger& d = dynamic_cast<Digger&>(digger);
	d.decreasLives();//��� ������� �� ���� �� ����� ������ ����� ����
	d.setNeedToSetBoard(true);//����� �� ���� ����
}

void SpecialMonsterDigger(Object& specialMonster, Object& digger)  //������� ������ ������� ��� ����� ������ �����
{
	DiggerSpecialMonster(digger, specialMonster);
}

//7-------------------------------------------------------------------
void DiggerDiamond(Object& digger, Object& diamond) //������� ������ ������� ��� ���� ������
{
	Digger& d = dynamic_cast<Digger&>(digger);
	Diamond& diamond1 = dynamic_cast<Diamond&>(diamond);
	d.setNumScores(15);//��� ������� �� ���� �� ����� ����� 15 ������  
	diamond1.clean(' ');//���� ������ �����
	d.decreaseDiamond();
}

void DiamondDigger(Object& diamond, Object& digger)//������� ������ ������� ��� ����� �����
{
	DiggerDiamond(digger, diamond);
}

//-------------------------------------------------------------------
void DiggerStone(Object& digger, Object& stone) //������� ������ ������� ��� ���� ����
{
	Digger& d = dynamic_cast<Digger&>(digger);
	Stone& s = dynamic_cast<Stone&>(stone);
	if (d.getNumStones() > 0)//�� ��� ���� ������ ���� ���� 
	{
		d.decreasnumOfStones();//��� ������� �� ���� �� ��� ����� �� �� ���� ������ ������� ����
		s.clean(' ');//����� ���� �����
	}
	else
		d.setCanMove(false);//�� ����� �� ���� ������ ������� �� ����� ��� �� ���� ����� �� ���� ���� 
}


void StoneDigger(Object& stone, Object& digger)//������� ������ ������� ��� ��� �����
{
	DiggerStone(digger, stone);
}
//8-------------------------------------------------------------------

void DiggerGift(Object& digger, Object& gift)//������� ������ ������� ��� ���� ������
{
	Digger& d = dynamic_cast<Digger&>(digger);
	Gift& g = dynamic_cast<Gift&>(gift);
	int SpecialKey = g.getSpecialKey();//����� �������� ����� ���� ���� �����
	switch (SpecialKey)
	{
	case 0: d.setNumScores(15);//���� ����� ����� �15
		g.clean(' ');
		break;
	case 1:d.setAddingTime();// ���� ����� ��� �30 �����
		g.clean(' ');
		break;
	case 2:d.setNumStonesGift();//���� ����� �� ���� ������ ������ ���� �����
		g.clean(' ');
		break;
	default:
		break;
	}
}

void GiftDigger(Object& gift, Object& digger) //������� ������ ������� ��� ����� �����
{
	DiggerGift(digger, gift);
}


