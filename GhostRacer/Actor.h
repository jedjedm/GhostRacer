#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

// Class Prototypes
class StudentWorld;

// Constants
constexpr double PI = 3.141592643;
constexpr double LEFT_EDGE = ROAD_CENTER - static_cast<double>(ROAD_WIDTH) / 2; // the left side, NOT lane, of the road
constexpr double RIGHT_EDGE = ROAD_CENTER + static_cast<double>(ROAD_WIDTH) / 2; // the right side, NOT lane of the road
constexpr double LEFT_MIDDLE_LANE_BORDER = LEFT_EDGE + ROAD_WIDTH / 3; // x coordinate of the border between left and middle lane
constexpr double MIDDLE_RIGHT_LANE_BORDER = RIGHT_EDGE - ROAD_WIDTH / 3; // x coordinate of the border between middle and right lane
constexpr int MAX_DIRECTION = 120; // max direction of ghost racer
constexpr int MIN_DIRECTION = 60; // min direction of ghost racer
constexpr int UPWARD_DIRECTION = 90; // direction where actor is pointing upwards
constexpr int DOWNWARD_DIRECTION = 270; // direction where actor is pointing downwards
constexpr double LEFT_ROAD_CENTER = ROAD_CENTER - ROAD_WIDTH / 3; // the x coordinate of the center of the left lane
constexpr double RIGHT_ROAD_CENTER = ROAD_CENTER + ROAD_WIDTH / 3; // the x coordinate of the center of the right lane

// Damage Constants
constexpr int DAMAGE_ZOMBIE_CAB_TO_GHOST_RACER = 20; // damage a ZombieCab does to the GhostRacer
constexpr int DAMAGE_HOLY_WATER_PROJECTILE = 1; // damagae a HolyWaterProjectile does to every damagable actor

// Increase score constants
constexpr int SCORE_INCREASE_ZOMBIE_PED = 150; // score increase when killing a zombie ped
constexpr int SCORE_INCREASE_ZOMBIE_CAB = 200; // score increase when killing a zombie cab with projectile
constexpr int SCORE_INCREASE_HEALING_GOODIE = 250; // score increase when ghostRacer gets a healing goode
constexpr int SCORE_INCREASE_HOLY_WATER_GOODIE = 50; // score increase when ghostRacer gets a holy water goodie
constexpr int SCORE_INCREASE_SOUL_GOODIE = 100; // score increase when ghostRacer gets a soul goodie


//GhostRacer Constants
constexpr int GHOST_RACER_START_DIR = 90;
constexpr bool GHOST_RACER_START_IS_ALIVE = true;
constexpr double GHOST_RACER_START_X = 128;
constexpr double GHOST_RACER_START_Y = 32;
constexpr double GHOST_RACER_SIZE = 4.0;
constexpr int GHOST_RACER_DEPTH = 0;
constexpr double GHOST_RACER_START_VERT_SPEED = 0; // New "forward" speed
constexpr double GHOST_RACER_START_HORIZ_SPEED = 0;
constexpr int GHOST_RACER_HOLY_WATER_AMT = 10;
constexpr int GHOST_RACER_START_HP = 100;
constexpr int GHOST_RACER_DIR_CHANGE = 8; // everytime the ghost racer moves left or right, it changes by this constant
constexpr int GHOST_RACER_START_HOLY_WATER_GOODIES = 10;

// HumanPedestrian Constants
constexpr int HUMAN_PEDESTRIAN_START_DIR = 0;
constexpr double HUMAN_PEDESTRIAN_SIZE = 2.0;
constexpr int HUMAN_PEDESTRIAN_DEPTH = 0;
constexpr int HUMAN_PEDESTRIAN_MOVEMENT_PLAN_DISTANCE = 0;
constexpr double HUMAN_PEDESTRIAN_START_VERT_SPEED = -4;
constexpr double HUMAN_PEDESTRIAN_START_HORIZ_SPEED = 0;
constexpr int HUMAN_PEDESTRIAN_START_IS_ALIVE = true;
constexpr int HUMAN_PEDESTRIAN_START_HP = 2;

// ZombiePedestrian Constants
constexpr int ZOMBIE_PEDESTRIAN_START_DIR = 0;
constexpr double ZOMBIE_PEDESTRIAN_SIZE = 3.0;
constexpr int ZOMBIE_PEDESTRIAN_DEPTH = 0;
constexpr int ZOMBIE_PEDESTRIAN_MOVEMENT_PLAN_DISTANCE = 0;
constexpr double ZOMBIE_PEDESTRIAN_START_VERT_SPEED = -4;
constexpr double ZOMBIE_PEDESTRIAN_START_HORIZ_SPEED = 0;
constexpr int ZOMBIE_PEDESTRIAN_START_IS_ALIVE = true;
constexpr int ZOMBIE_PEDESTRIAN_START_HP = 2;
constexpr int ZOMBIE_PEDESTRIAN_START_TICKS_TO_GRUNTS = 0;

// ZombieCab Constants
constexpr int ZOMBIE_CAB_START_DIR = 90;
constexpr double ZOMBIE_CAB_SIZE = 4.0;
constexpr int ZOMBIE_CAB_DEPTH = 0;
constexpr double ZOMBIE_CAB_START_HORIZ_SPEED = 0;
constexpr double ZOMBIE_CAB_START_HP = 3;
constexpr bool ZOMBIE_CAB_START_IS_ALIVE = true;
constexpr int ZOMBIE_CAB_MOVEMENT_PLAN_DISTANCE = 0;
constexpr bool ZOMBIE_CAB_START_HAS_DAMAGED_GHOST_RACER = false;
constexpr double ZOMBIE_CAB_CLOSEST_DISTANCE = 96; // value that holds the closest distance a collision worthy actor should be from a ZombieCab in pixels
constexpr double ZOMBIE_CAB_CHANGE_VERT_SPEED = 0.5;

// BorderLine Constants
constexpr int BORDER_LINE_START_DIR = 0;
constexpr int BORDER_LINE_DEPTH = 2;
constexpr double BORDER_LINE_SIZE = 2.0;
constexpr double BORDER_LINE_VERT_SPEED = -4;
constexpr double BORDER_LINE_HORIZ_SPEED = 0;
constexpr bool BORDER_LINE_START_IS_ALIVE = true;

// HolyWaterProjectile Constants
constexpr int HOLY_WATER_PROJECTILE_MAX_TRAVEL_DISTANCE = 160;
constexpr double HOLY_WATER_PROJECTILE_SIZE = 1.0;
constexpr int HOLY_WATER_PROJECTILE_DEPTH = 1;
constexpr bool HOLY_WATER_PROJECTILE_START_IS_ALIVE = true;
constexpr double HOLY_WATER_PROJECTILE_VERT_SPEED = 0; // not needed, here just in case it does need to be initialized
constexpr double HOLY_WATER_PROJECTILE_HORIZ_SPEED = 0; // not needed, here just in case it does need to be initialized

// OilSlick Constants
constexpr int OIL_SLICK_START_DIR = 0;
constexpr int OIL_SLICK_DEPTH = 2;
constexpr double OIL_SLICK_START_HORIZ_SPEED = 0;
constexpr double OIL_SLICK_START_VERT_SPEED = -4;
constexpr bool OIL_SLICK_START_IS_ALIVE = true;

// HealingGoodie Constants
constexpr int HEALING_GOODIE_START_DIR = 0;
constexpr double HEALING_GOODIE_SIZE = 1.0;
constexpr int HEALING_GOODIE_DEPTH = 2;
constexpr double HEALING_GOODIE_HORIZ_SPEED = 0;
constexpr double HEALING_GOODIE_VERT_SPEED = -4;
constexpr bool HEALING_GOODIE_START_IS_ALIVE = true;
constexpr int HEALING_GOODIE_HEAL = 10; // heals GhostRacer by 10 points

// HolyWaterGoodie Constants
constexpr int HOLY_WATER_GOODIE_START_DIR = 90;
constexpr double HOLY_WATER_GOODIE_SIZE = 2.0;
constexpr int HOLY_WATER_GOODIE_DEPTH = 2;
constexpr double HOLY_WATER_GOODIE_HORIZ_SPEED = 0;
constexpr double HOLY_WATER_GOODIE_VERT_SPEED = -4;
constexpr bool HOLY_WATER_GOODIE_START_IS_ALIVE = true;
constexpr int HOLY_WATER_GOODIE_INCREASE_CHARGES = 10;

// SoulGoodie Constants
constexpr int SOUL_GOODIE_START_DIR = 0;
constexpr double SOUL_GOODIE_SIZE = 4.0;
constexpr int SOUL_GOODIE_DEPTH = 2;
constexpr double SOUL_GOODIE_HORIZ_SPEED = 0;
constexpr double SOUL_GOODIE_VERT_SPEED = -4;
constexpr bool SOUL_GOODIE_START_IS_ALIVE = true;

// Class Definitions
class Actor : public GraphObject
{
public:
	Actor(int imageID, double startX,
		double startY, int startDirection,
		double size, int depth,
		double horizSpeed, double vertSpeed,
		bool isAlive, StudentWorld* ptrToWorld);
	virtual ~Actor();
	virtual void doSomething() = 0; // each class has a doSomething function

	// Getters and Setters for private variables
	double getHorizSpeed() const; // getter for m_horizSpeed
	void setHorizSpeed(double horizSpeed); // setter for m_horizSpeed;
	double getVertSpeed() const; // getter for m_vertSpeed
	void setVertSpeed(double vertSpeed); // setter for m_vertSpeed;
	bool getIsAlive() const; // getter for m_isAlive
	void setIsAlive(bool isAlive); // setter for m_isAlive
	StudentWorld* getWorld() const; // getter for m_ptrToWorld private variable
	
	// Helper functions
	int getLane() const; // returns which lane an Actor is on (left lane is lane = 1, middle lane is in lane = 2, right lane is line = 3, no lane is -1)
	bool isOverlapping(Actor* other) const; // returns true if this Actor and other Actor are overlapping
										    // returns false otherwise

	// identifier functions
	virtual bool isCollisionAvoidant() = 0; // returns true if an object is collision avoidant
											// returns false otherwise
	virtual bool getBlessed(); // returns true if an actor can be blessed/interacted with by holy water, false otherwise
						       // handles what happens if a projectile hits an Actor that can be interacted with by. won't do anything if projetile hits anything else

	// Common Functionality functions
protected:
	virtual bool move(); // moves Actor, returns true if an Actor is still alive after moving, false if actor is not alive after moving

	// Play sound function, implement with every thing // check what has sounds
	// make a unique "destructor" method that should be used when an actor needs to be removed // not needed duh
	// damageRacer(Actor* other, int amount)

private:
	double m_horizSpeed; // for x direction (columns)
					  // can be negative
	double m_vertSpeed; // for y direction (rows)
					 // can be negative
	bool m_isAlive; // stores "alive state"
				  // true if Actor is alive
				  // false if Actor is not alive/off screen
	StudentWorld* m_ptrToWorld; // ptr to StudentWorld class object
};

class CollisionAvoidant : public Actor
{
public:
	CollisionAvoidant(int imageID, double startX,
		double startY, int startDirection,
		double size, int depth,
		double horizSpeed, double vertSpeed,
		bool isAlive, int hitpoints, StudentWorld* ptrToWorld);
	virtual ~CollisionAvoidant();
	virtual bool isCollisionAvoidant();
	int getHitPoints() const; // getter for m_hitpoints
	void setHitPoints(int hitpoints); // setter for m_hitpoints

	// Identifier functions
private:
	int m_hitpoints;
};

class GhostRacer : public CollisionAvoidant
{
public:
	GhostRacer(StudentWorld* ptrToWorld);
	virtual ~GhostRacer();
	virtual void doSomething();
	int getNumHolyWaterGoodies() const; // getter for m_numOfHolyWaterGoodies
	void setNumHolyWaterGoodies(int numHolyWaterGoodies); // setter for m_numOfHolyWaterGoodies
	void increaseHitPoints(int hitpoints);

protected:
	virtual bool move(); //movement algorithm for ghost racer, differs from every other Actor
	
private:
	int m_numOfHolyWaterGoodies; // stores number of holy water goodies the ghost racer has current level
	
};

class MobileActors : public CollisionAvoidant
{
public:
	MobileActors(int imageID, double startX,
		double startY, int startDirection,
		double size, int depth,
		double horizSpeed, double vertSpeed,
		bool isAlive, int hitpoints, StudentWorld* ptrToWorld, int movementPlanDistance);
	virtual ~MobileActors();
protected:
	int getMovementPlanDistance() const; // getter for m_movementPlanDistance
	void setMovementPlanDistance(int movementPlanDistance); // setter for m_movementPlanDistance
private:
	int m_movementPlanDistance;	
};

class ZombieCab : public MobileActors
{
public:
	ZombieCab(StudentWorld* ptrToWorld, double startX, double startY, double vertSpeed);
	virtual ~ZombieCab();
	virtual void doSomething();
	virtual bool getBlessed();
protected:
	bool getHasDamagedGhostRacer() const; // getter for m_hasDamagedGhostRacer
	void setHasDamagedGhostRacer(bool hasDamagedGhostRacer); // setter for m_hasDamagedGhostRacer
private:
	bool m_hasDamagedGhostRacer;
};

class Pedestrian : public MobileActors
{
public:
	Pedestrian(int imageID, int startDirection,
		double size, int depth,
		double horizSpeed, double vertSpeed,
		bool isAlive, int hitpoints, StudentWorld* ptrToWorld, int movementPlanDistance);
	virtual ~Pedestrian();
	virtual void doSomething();
protected:
	virtual void overlapWithGhostRacer() = 0; // For what ZombiePedestrian and HumanPedestrian do when overlapping with GhostRacer
	virtual void doDifferentiatedStuffBeforeMoving() = 0; // For what ZombiePedestrian and HumanPedestrian do BEFORE moving
	virtual void doDifferentiatedStuffAfterMoving() = 0; // For what ZombiePedestrian and HumanPedestrian do AFTER moving
private:
};

class HumanPedestrian : public Pedestrian
{
public:
	HumanPedestrian(StudentWorld* ptrToWorld);
	virtual ~HumanPedestrian();
	//virtual void doSomething();
	virtual bool getBlessed();
protected:
	virtual void overlapWithGhostRacer();
	virtual void doDifferentiatedStuffBeforeMoving();
	virtual void doDifferentiatedStuffAfterMoving();
private:
};

class ZombiePedestrian : public Pedestrian
{
public:
	ZombiePedestrian(StudentWorld* ptrToWorld);
	virtual ~ZombiePedestrian();
	//virtual void doSomething();
	double getTicksToGrunt() const; // getter for m_ticksToGrunt
	void setTicksToGrunt(double ticksToGrunt); // setter for m_ticksToGrunt
	virtual bool getBlessed();
protected:
	virtual void overlapWithGhostRacer();
	virtual void doDifferentiatedStuffBeforeMoving();
	virtual void doDifferentiatedStuffAfterMoving();
private:
	double m_ticksToGrunt;
};

class NonCollisionAvoidant : public Actor
{
public:
	NonCollisionAvoidant(int imageID, double startX,
		double startY, int startDirection,
		double size, int depth,
		double horizSpeed, double vertSpeed,
		bool isAlive, StudentWorld* ptrToWorld);
	virtual ~NonCollisionAvoidant();
	virtual bool isCollisionAvoidant();
private:
};

class OilSlick : public NonCollisionAvoidant
{
public:
	OilSlick(StudentWorld* ptrToWorld);
	OilSlick(StudentWorld* ptrToWorld, double startX, double StartY); // for when adding an OilSlick if a zombie cab dies
	virtual ~OilSlick();
	virtual void doSomething();
private:
};

class HolyWaterProjectile : public NonCollisionAvoidant
{
public:
	HolyWaterProjectile(StudentWorld* ptrToWorld, double startX, double startY, int startDir);
	virtual ~HolyWaterProjectile();
	virtual void doSomething();
	virtual bool move();

protected:
	//double getStartX() const; // getter for m_startX
	//double getStartY() const; // getter for m_startY
	//double getMaxTravelDistance() const; // getter for m_maxTravelDistance
private:
	double m_startX;
	double m_startY;
	double m_maxTravelDistance;
	int m_startDir;
};

class BorderLine : public NonCollisionAvoidant
{
public:
	BorderLine(StudentWorld* ptrToWorld, int imageID, double startX, double startY);
	virtual ~BorderLine();
	virtual void doSomething();
private:
};

class Goodie : public NonCollisionAvoidant
{
public:
	Goodie(int imageID, double startX,
		double startY, int startDirection,
		double size, int depth,
		double horizSpeed, double vertSpeed,
		bool isAlive, StudentWorld* ptrToWorld);
	virtual void doSomething(); // every goodie has a similar doSomething()
	virtual ~Goodie();
protected:
	virtual void overlapWithGhostRacer() = 0; // every Goodie has a specific set of instructions on what to do when a Goodie overlaps with GhostRacer
	virtual void doDifferentiatedStuff();
private:
};

class HealingGoodie : public Goodie
{
public:
	HealingGoodie(StudentWorld* ptrToWorld, double startX, double startY);
	virtual ~HealingGoodie();
	//virtual void doSomething();
	virtual bool getBlessed();
protected:
	virtual void overlapWithGhostRacer();
private:
};

class SoulGoodie : public Goodie
{
public:
	SoulGoodie(StudentWorld* ptrToWorld);
	virtual ~SoulGoodie();
	//virtual void doSomething();
protected:
	virtual void overlapWithGhostRacer();
	virtual void doDifferentiatedStuff();
private:
};

class HolyWaterGoodie : public Goodie
{
public:
	HolyWaterGoodie(StudentWorld* ptrToWorld);
	virtual ~HolyWaterGoodie();
	//virtual void doSomething();
	virtual bool getBlessed();
protected:
	virtual void overlapWithGhostRacer();
private:
};
#endif // ACTOR_H_