#include "Actor.h"
#include "StudentWorld.h"
#include <cmath> // cos() and std::abs
#include <iostream>
using namespace std;

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

// Actor Class Function Implementations
Actor::Actor(int imageID, double startX, double startY, int startDirection, double size, int depth, double horizSpeed, double vertSpeed, bool isAlive, StudentWorld * ptrToWorld)
	: GraphObject(imageID, startX, startY, startDirection, size, depth)
{
	m_horizSpeed = horizSpeed;
	m_vertSpeed = vertSpeed;
	m_isAlive = isAlive;
	m_ptrToWorld = ptrToWorld;
}

Actor::~Actor()
{
	// todo
}

StudentWorld* Actor::getWorld() const
{
	return m_ptrToWorld;
}

double Actor::getHorizSpeed() const
{
	return m_horizSpeed;
}

void Actor::setHorizSpeed(double horizSpeed)
{
	m_horizSpeed = horizSpeed;
}

double Actor::getVertSpeed() const
{
	return m_vertSpeed;
}

void Actor::setVertSpeed(double vertSpeed)
{
	m_vertSpeed = vertSpeed;
}

bool Actor::getIsAlive() const
{
	return m_isAlive;
}

void Actor::setIsAlive(bool isAlive)
{
	m_isAlive = isAlive;
}

bool Actor::isOverlapping(Actor* other) const
{
	double delta_x = abs(getX() - other->getX()); // find absolute value of distance between x coordinate
	double delta_y = abs(getY() - other->getY()); // find absolute value of distance between y coordinate
	double radiusSum = getRadius() + other->getRadius();
	return ((delta_x < (radiusSum * 0.25)) && (delta_y < (radiusSum * 0.6))); // if this statement is true, objects overlap
																			  // if this statement is false, objects DO NOT overlap
}

bool Actor::move()
{
	double vert_speed = getVertSpeed() - getWorld()->getGhostRacerVertSpeed();
	double horiz_speed = getHorizSpeed();
	moveTo(getX() + horiz_speed, getY() + vert_speed); // move Actor to new coords
	if (getX() < 0 || getY() < 0 || getX() > VIEW_WIDTH || getY() > VIEW_HEIGHT) // if the Actor is out of bounds, set isAlive is false
	{
		setIsAlive(false);
		return false;
	}
	return true;
}

int Actor::getLane() const
{
	// check if inequalities are right!!!!

	if ((LEFT_EDGE <= getX() && getX() < LEFT_MIDDLE_LANE_BORDER)) // if Actor is in left lane
	{
		return 1; 
	}
	else if (LEFT_MIDDLE_LANE_BORDER <= getX() && getX() < MIDDLE_RIGHT_LANE_BORDER) // if Actor is in middle lane
	{
		return 2;
	}
	else if (MIDDLE_RIGHT_LANE_BORDER <= getX() && getX() < RIGHT_EDGE) // if Actor is in the right lane
	{
		return 3;
	}
	else // if Actor is in no lanes
	{
		return -1;
	}
}

bool Actor::getBlessed()
{
	return false;
}

// Collision Class Avoidant Implementations
CollisionAvoidant::CollisionAvoidant(int imageID, double startX, double startY, int startDirection, double size, int depth, double horizSpeed, double vertSpeed, bool isAlive, int hitpoints, StudentWorld* ptrToWorld)
	: Actor(imageID, startX, startY, startDirection, size, depth, horizSpeed, vertSpeed, isAlive, ptrToWorld)
{
	m_hitpoints = hitpoints;
}

CollisionAvoidant::~CollisionAvoidant()
{
	// todo
}

bool CollisionAvoidant::isCollisionAvoidant()
{
	return true;
}

int CollisionAvoidant::getHitPoints() const
{
	return m_hitpoints;
}

void CollisionAvoidant::setHitPoints(int hitpoints)
{
	m_hitpoints = hitpoints;
}

// GhostRace Class Implementations
GhostRacer::GhostRacer(StudentWorld* ptrToWorld)
	:CollisionAvoidant(IID_GHOST_RACER, GHOST_RACER_START_X, GHOST_RACER_START_Y, GHOST_RACER_START_DIR, GHOST_RACER_SIZE, GHOST_RACER_DEPTH, GHOST_RACER_START_HORIZ_SPEED, GHOST_RACER_START_VERT_SPEED, GHOST_RACER_START_IS_ALIVE, GHOST_RACER_START_HP, ptrToWorld)
{
	m_numOfHolyWaterGoodies = GHOST_RACER_START_HOLY_WATER_GOODIES;
}

void GhostRacer::doSomething()
{
	if (!getIsAlive()) // the ghost racer is dead, don't do anything
	{
		return;
	}

	int ch; // variable for storing key press

	// Check GhostRacer is off the left side of the road
	if (getX() < LEFT_EDGE)
	{
		if (getDirection() > UPWARD_DIRECTION) // facing left
		{
			setHitPoints(getHitPoints() - 10); // damage GhostRacer
			setDirection(82); // set direction pointing away from left side of the road
			getWorld()->playSound(SOUND_VEHICLE_CRASH);
		}
	}
	// Check if GhostRacer is off the right side of the road
	else if (getX() > RIGHT_EDGE)
	{
		if (getDirection() < UPWARD_DIRECTION) // facing right
		{
			setHitPoints(getHitPoints() - 10); // damage GhostRacer
			setDirection(98); // set direction pointing away from right side of the road
			getWorld()->playSound(SOUND_VEHICLE_CRASH);
		}
	}
	// Check if a key is pressed
	else if (getWorld()->getKey(ch))
	{
		switch (ch)
		{
			// Check if key press space is hit first
			// If spacebar, send out a holy water projectile
			case KEY_PRESS_SPACE:
				if (m_numOfHolyWaterGoodies > 0)
				{
					m_numOfHolyWaterGoodies--; // decrement holy water goodies
					getWorld()->launchProjectile();
				}
				break;
			case KEY_PRESS_LEFT:
				if(getDirection() < 114)
					setDirection(getDirection() + GHOST_RACER_DIR_CHANGE);
				break;
			case KEY_PRESS_RIGHT:
				if(getDirection() > 66)
					setDirection(getDirection() - GHOST_RACER_DIR_CHANGE);
				break;
			case KEY_PRESS_UP:
				if (getVertSpeed() < 5)
					setVertSpeed(getVertSpeed() + 1);
				break;
			case KEY_PRESS_DOWN:
				if (getVertSpeed() > -1)
					setVertSpeed(getVertSpeed() - 1);
				break;
		}
	}
	
	if (move() == false) // Move ghost racer. if after moving, ghost racer is not alive, immediately return
	{
		return;
	}


	// Not sure whether I should do this here
	// having to update the stuff sucks
	// use getDamaged() polymorphic functions
	// don't use polymorphism, use functions inside classes instead
	// psuedocode:
	// CollisionWorthy::damagePlayer(int damageAmt)
	// setHealth(getHealth - damageAmt)
	// if(getHealth() <= 0)
	// setIsAlive(false)
	// return;

	if (getHitPoints() <= 0)
	{
		setIsAlive(false);
	}
	return;
}

GhostRacer::~GhostRacer()
{
	// todo
}

int GhostRacer::getNumHolyWaterGoodies() const
{
	return m_numOfHolyWaterGoodies;
}

void GhostRacer::setNumHolyWaterGoodies(int numHolyWaterGoodies)
{
	m_numOfHolyWaterGoodies = numHolyWaterGoodies;
}

void GhostRacer::increaseHitPoints(int hitpoints)
{
	setHitPoints(getHitPoints() + hitpoints);
	if (getHitPoints() > GHOST_RACER_START_HP) // if increasing hit points goes over max
	{
		setHitPoints(GHOST_RACER_START_HP); // set hitpoints to max
	}
}

bool GhostRacer::move()
{
	// Move ghost racer
	double max_shift_per_tick = 4.0;
	double direction = getDirection(); // double in this case to handle the conversion to radians
	double delta_x = cos(direction * PI / 180.0) * max_shift_per_tick; // change pi constant to something else
	double cur_x = getX();
	double cur_y = getY();
	moveTo(cur_x + delta_x, cur_y);
	return true; // ghost racer is always always after moving IE can never go out of bounds
}

// MobileActors Class FunctionImplementations
MobileActors::MobileActors(int imageID, double startX, double startY, int startDirection, double size, int depth, double horizSpeed, double vertSpeed, bool isAlive, int hitpoints, StudentWorld* ptrToWorld, int movementPlanDistance)
	:CollisionAvoidant(imageID, startX, startY, startDirection, size, depth, horizSpeed, vertSpeed, isAlive, hitpoints, ptrToWorld)
{
	m_movementPlanDistance = movementPlanDistance;
}

MobileActors::~MobileActors()
{

}

int MobileActors::getMovementPlanDistance() const
{
	return m_movementPlanDistance;
}

void MobileActors::setMovementPlanDistance(int movementPlanDistance)
{
	m_movementPlanDistance = movementPlanDistance;
}


// ZombieCab Class Function Implementations
ZombieCab::ZombieCab(StudentWorld* ptrToWorld, double startX, double startY, double vertSpeed)
	:MobileActors(IID_ZOMBIE_CAB, startX, startY, ZOMBIE_CAB_START_DIR, ZOMBIE_CAB_SIZE, ZOMBIE_CAB_DEPTH, ZOMBIE_CAB_START_HORIZ_SPEED, vertSpeed, ZOMBIE_CAB_START_IS_ALIVE, ZOMBIE_CAB_START_HP, ptrToWorld, ZOMBIE_CAB_MOVEMENT_PLAN_DISTANCE)
{
	m_hasDamagedGhostRacer = ZOMBIE_CAB_START_HAS_DAMAGED_GHOST_RACER;

}

ZombieCab::~ZombieCab()
{

}

void ZombieCab::doSomething()
{
	
	if (getIsAlive() == false) // if the ZombieCab is not alive, do nothing
	{
		return;
	}

	if (isOverlapping(getWorld()->getPlayer())) // if the ZombieCab is overlapping with the ghostRacer
	{
		if (getHasDamagedGhostRacer() != true)
		{
			getWorld()->playSound(SOUND_VEHICLE_CRASH);
			getWorld()->getPlayer()->setHitPoints(getWorld()->getPlayer()->getHitPoints() - DAMAGE_ZOMBIE_CAB_TO_GHOST_RACER);
			if (getX() <= getWorld()->getPlayer()->getX())
			{
				setHorizSpeed(-5);
				setDirection(120 + randInt(0, 19));
			}
			else
			{
				setHorizSpeed(5);
				setDirection(60 - randInt(0, 19));
			}
		}
		setHasDamagedGhostRacer(true);
	}

	// Moving the ZombieCab
	if (move() == false) // if after moving, the Actor is not alive or is out of bounds
	{
		return;
	}

	if (getVertSpeed() > getWorld()->getGhostRacerVertSpeed()) // if the ZombieCab is moving up the screen
	{
		bool hasCollisionWorthyActorFront = false; // keeps track if there is a collision worthy actor in front of the ZombieCab in the current lane
		int cabLane = getLane(); // current lane of ZombieCab
		double closestYCoordTop = static_cast<double>(VIEW_HEIGHT) + 1; // keeps track of closest actor's Y coord in front of the ZombieCab in the current lane
		// Check Actors for closest Actor
		if (getWorld()->getPlayer()->isCollisionAvoidant()) // check GhostRacer
		{
			if (getWorld()->getPlayer()->getLane() == cabLane) // if the GhostRacer and the ZombieCab are in the same lane
			{
				if (getWorld()->getPlayer()->getY() > getY()) // if the GhostRacer is above the ZombieCab
				{
					hasCollisionWorthyActorFront = true;
					closestYCoordTop = min(closestYCoordTop, getWorld()->getPlayer()->getY());
				}
			}
		}
		getWorld()->zombieCabGetClosestActorAbove(this, closestYCoordTop, hasCollisionWorthyActorFront, cabLane);
		double difference = abs(getY() - closestYCoordTop);
		if (hasCollisionWorthyActorFront && (difference < ZOMBIE_CAB_CLOSEST_DISTANCE)) // if there is a collision worthy actor in front of the ZombieCab in the current lane and that Actor is less than 96 pixels infront of the ZombieCab
		{
			setVertSpeed(getVertSpeed() - ZOMBIE_CAB_CHANGE_VERT_SPEED);
			return;
		}
	}
	if(getVertSpeed() <= getWorld()->getGhostRacerVertSpeed())// if the ZombieCab is moving down the screen or not moving
	{
		bool hasCollisionWorthyActorBelow = false; // keeps track if there is a collision worthy acyor behind the the ZombieCab in the current lane
		int cabLane = getLane(); // current lane of ZombieCab
		double closestYCoordBot = -1; // keeps track of closest actor's Y coord beind the ZombieCab in the current lane
		getWorld()->zombieCabGetClosestActorBelow(this, closestYCoordBot, hasCollisionWorthyActorBelow, cabLane);
		double difference = abs(getY() - closestYCoordBot);
		if (hasCollisionWorthyActorBelow && (difference < ZOMBIE_CAB_CLOSEST_DISTANCE)) // if there is a collision worthy actor behind the ZombieCab in the current lane that's not GhostRacer and it's less than 96 pixels behind the ZombieCab
		{
			setVertSpeed(getVertSpeed() + ZOMBIE_CAB_CHANGE_VERT_SPEED);
			return;
		}
	}
	setMovementPlanDistance(getMovementPlanDistance() - 1); // decrement movement plan distance
	if (getMovementPlanDistance() > 0)
	{
		return;
	}
	setMovementPlanDistance(randInt(4, 32));
	setVertSpeed(getVertSpeed() + randInt(-2, 2));
	return;
}

bool ZombieCab::getHasDamagedGhostRacer() const
{
	return m_hasDamagedGhostRacer;
}

void ZombieCab::setHasDamagedGhostRacer(bool hasDamagedGhostRacer)
{
	m_hasDamagedGhostRacer = hasDamagedGhostRacer;
}

bool ZombieCab::getBlessed()
{
	setHitPoints(getHitPoints() - DAMAGE_HOLY_WATER_PROJECTILE);
	if (getHitPoints() <= 0)
	{
		setIsAlive(false);
		getWorld()->playSound(SOUND_VEHICLE_DIE);
		int chanceAddOilSlick = randInt(1, 5);
		if (chanceAddOilSlick == 1)
		{
			getWorld()->addOilSlick(this);
		}
		getWorld()->increaseScore(SCORE_INCREASE_ZOMBIE_CAB);
	}
	else
	{
		getWorld()->playSound(SOUND_VEHICLE_HURT);
	}
	return true;
}

// Pedestrian Class Function Implementations
Pedestrian::Pedestrian(int imageID, int startDirection, double size, int depth, double horizSpeed, double vertSpeed, bool isAlive, int hitpoints, StudentWorld* ptrToWorld, int movementPlanDistance)
	: MobileActors(imageID, randInt(0, VIEW_WIDTH), VIEW_HEIGHT, startDirection, size, depth, horizSpeed, vertSpeed, isAlive, hitpoints, ptrToWorld, movementPlanDistance)
{

}

Pedestrian::~Pedestrian()
{

}

void Pedestrian::doSomething()
{
	if (getIsAlive() == false) // if the Pedestrian is not alive
	{
		return;
	}
	if (isOverlapping(getWorld()->getPlayer())) // if Pedestrian is overlapping with player
	{
		overlapWithGhostRacer();
		return;
	}

	doDifferentiatedStuffBeforeMoving(); // before moving, ZombiePedestrian and HumanPedestrian do different things

	// move Pedestrian
	if (move() == false) // if after moving, Pedestrian is out of bounds do nothing
	{
		return;
	}
	doDifferentiatedStuffAfterMoving(); // after moving, ZombiePedestrian and HumanPedestrian do different things
}

// HumanPedestrian Class Function Implementations
HumanPedestrian::HumanPedestrian(StudentWorld* ptrToWorld)
	:Pedestrian(IID_HUMAN_PED, HUMAN_PEDESTRIAN_START_DIR, HUMAN_PEDESTRIAN_SIZE, HUMAN_PEDESTRIAN_DEPTH, HUMAN_PEDESTRIAN_START_HORIZ_SPEED, HUMAN_PEDESTRIAN_START_VERT_SPEED, HUMAN_PEDESTRIAN_START_IS_ALIVE, HUMAN_PEDESTRIAN_START_HP, ptrToWorld, HUMAN_PEDESTRIAN_MOVEMENT_PLAN_DISTANCE)
{

}

HumanPedestrian::~HumanPedestrian()
{

}

/*
void HumanPedestrian::doSomething()
{
	if (getIsAlive() == false) // if the human pedestrian is not alive
	{
		return;
	}
	// can only be "hit" by the player
	if (isOverlapping(getWorld()->getPlayer())) // if the ghostRacer runs over a human pedestrian
	{
		getWorld()->getPlayer()->setIsAlive(false); //
		return;
	}

	// move HumanPedestrian
	if (move() == false) // if after moving, HumanPed is out of bounds
	{
		return;
	}
	setMovementPlanDistance(getMovementPlanDistance() - 1);
	if (getMovementPlanDistance() > 0)
	{
		return;
	}
	// Change horizontal speed to a random int between -3 and 3 NOT INCLUDING ZERO
	do
	{
		setHorizSpeed(randInt(-3, 3));
	} while (getHorizSpeed() == 0);
	setMovementPlanDistance(randInt(4, 32)); // change movement plan distance to a random int between 4 and 32 inclusive

	if (getHorizSpeed() < 0) // if horiz speed is negative
	{
		setDirection(180); // make the human pedestrian face left
	}
	else if (getHorizSpeed() > 0)// if horiz speed is positive
	{
		setDirection(0); // make the human pedestrian face right
	}
	return;
}
*/


void HumanPedestrian::overlapWithGhostRacer()
{
	getWorld()->getPlayer()->setIsAlive(false); // after overlapping with GhostRacer, GhostRacer is "dead"
	return;
}

void HumanPedestrian::doDifferentiatedStuffBeforeMoving()
{
	return;
}

void HumanPedestrian::doDifferentiatedStuffAfterMoving()
{
	setMovementPlanDistance(getMovementPlanDistance() - 1);
	if (getMovementPlanDistance() > 0)
	{
		return;
	}
	// Change horizontal speed to a random int between -3 and 3 NOT INCLUDING ZERO
	do
	{
		setHorizSpeed(randInt(-3, 3));
	} while (getHorizSpeed() == 0);
	setMovementPlanDistance(randInt(4, 32)); // change movement plan distance to a random int between 4 and 32 inclusive

	if (getHorizSpeed() < 0) // if horiz speed is negative
	{
		setDirection(180); // make the human pedestrian face left
	}
	else if (getHorizSpeed() > 0)// if horiz speed is positive
	{
		setDirection(0); // make the human pedestrian face right
	}
	return;
}

bool HumanPedestrian::getBlessed()
{
	setHorizSpeed(getHorizSpeed() * -1); // change direction
	if (getHorizSpeed() < 0) // if horiz speed is negative
	{
		setDirection(180); // make the human pedestrian face left
	}
	else if (getHorizSpeed() > 0)// if horiz speed is positive
	{
		setDirection(0); // make the human pedestrian face right
	}
	getWorld()->playSound(SOUND_PED_HURT);
	return true;
}

// ZombiePedestrian Class Function Implementations
ZombiePedestrian::ZombiePedestrian(StudentWorld* ptrToWorld)
	:Pedestrian(IID_ZOMBIE_PED, ZOMBIE_PEDESTRIAN_START_DIR, ZOMBIE_PEDESTRIAN_SIZE, ZOMBIE_PEDESTRIAN_DEPTH, ZOMBIE_PEDESTRIAN_START_HORIZ_SPEED, ZOMBIE_PEDESTRIAN_START_VERT_SPEED, ZOMBIE_PEDESTRIAN_START_IS_ALIVE, ZOMBIE_PEDESTRIAN_START_HP, ptrToWorld, ZOMBIE_PEDESTRIAN_MOVEMENT_PLAN_DISTANCE)
{
	m_ticksToGrunt = ZOMBIE_PEDESTRIAN_START_TICKS_TO_GRUNTS;
}

ZombiePedestrian::~ZombiePedestrian()
{

}

/*
void ZombiePedestrian::doSomething()
{
	if (getIsAlive() == false)
	{
		return;
	}
	// can only get hit by a player
	if (isOverlapping(getWorld()->getPlayer())) // if the ghostRacer crashes into a zombiePedestrian
	{
		setHitPoints(getHitPoints() - 2); // ZombiePed is damaged by two points
		getWorld()->getPlayer()->setHitPoints(getWorld()->getPlayer()->getHitPoints() - 5); // GhostRacer is damaged by 5 points
		if (getHitPoints() <= 0)
		{
			setIsAlive(false);
			getWorld()->playSound(SOUND_PED_DIE);
			getWorld()->increaseScore(SCORE_INCREASE_ZOMBIE_PED);
		}
		else
		{
			getWorld()->playSound(SOUND_PED_HURT);
		}
		return;
	}
	double distanceToPlayer = abs(getWorld()->getPlayer()->getX() - getX());
	if (distanceToPlayer <= 30 && getY() > getWorld()->getPlayer()->getY()) // if the ZombiePedestrian is 30 pixels to the left or the right of the GhostRacer and is in front of the GhostRacer
	{
		setDirection(DOWNWARD_DIRECTION); // set direction to down direction
		if (getX() < getWorld()->getPlayer()->getX()) // if ZombiePedestrian is to the left of the GShostRider
		{
			setHorizSpeed(1);
		}
		else if (getX() > getWorld()->getPlayer()->getX()) // if ZombiePedestrian is to the right of the GhostRider
		{
			setHorizSpeed(-1);
		}
		else // they have the same x coordinate
		{
			setHorizSpeed(0);
		}
		setTicksToGrunt(getTicksToGrunt() - 1); // decrement by one
		if (getTicksToGrunt() <= 0)
		{
			getWorld()->playSound(SOUND_ZOMBIE_ATTACK);
			setTicksToGrunt(20);
		}
	}

	// move ZombiePedestrian
	if (move() == false) // if after moving the ZombiePed is out of bounds
	{
		return;
	}
	if (getMovementPlanDistance() > 0)
	{
		setMovementPlanDistance(getMovementPlanDistance() - 1); // decrement movement plan distance
		return;
	}
	else
	{
		// Change horizontal speed to a random int between -3 and 3 NOT INCLUDING ZERO
		do
		{
			setHorizSpeed(randInt(-3, 3));
		} while (getHorizSpeed() == 0);
		setMovementPlanDistance(randInt(4, 32)); // change movement plan distance to a random int between 4 and 32 inclusive
		if (getHorizSpeed() < 0) // if horiz speed is negative
		{
			setDirection(180); // make the human pedestrian face left
		}
		else // if horiz speed is positive
		{
			setDirection(0); // make the human pedestrian face right
		}
		return;
	}
	return;
}
*/

void ZombiePedestrian::overlapWithGhostRacer()
{
	setHitPoints(getHitPoints() - 2); // ZombiePed is damaged by two points
	getWorld()->getPlayer()->setHitPoints(getWorld()->getPlayer()->getHitPoints() - 5); // GhostRacer is damaged by 5 points
	if (getHitPoints() <= 0)
	{
		setIsAlive(false);
		getWorld()->playSound(SOUND_PED_DIE);
		getWorld()->increaseScore(SCORE_INCREASE_ZOMBIE_PED);
	}
	else
	{
		getWorld()->playSound(SOUND_PED_HURT);
	}
	return;
}

void ZombiePedestrian::doDifferentiatedStuffBeforeMoving()
{
	double distanceToPlayer = abs(getWorld()->getPlayer()->getX() - getX());
	if (distanceToPlayer <= 30 && getY() > getWorld()->getPlayer()->getY()) // if the ZombiePedestrian is 30 pixels to the left or the right of the GhostRacer and is in front of the GhostRacer
	{
		setDirection(DOWNWARD_DIRECTION); // set direction to down direction
		if (getX() < getWorld()->getPlayer()->getX()) // if ZombiePedestrian is to the left of the GShostRider
		{
			setHorizSpeed(1);
		}
		else if (getX() > getWorld()->getPlayer()->getX()) // if ZombiePedestrian is to the right of the GhostRider
		{
			setHorizSpeed(-1);
		}
		else // they have the same x coordinate
		{
			setHorizSpeed(0);
		}
		setTicksToGrunt(getTicksToGrunt() - 1); // decrement by one
		if (getTicksToGrunt() <= 0)
		{
			getWorld()->playSound(SOUND_ZOMBIE_ATTACK);
			setTicksToGrunt(20);
		}
	}
}

void ZombiePedestrian::doDifferentiatedStuffAfterMoving()
{
	if (getMovementPlanDistance() > 0)
	{
		setMovementPlanDistance(getMovementPlanDistance() - 1); // decrement movement plan distance
		return;
	}
	else
	{
		// Change horizontal speed to a random int between -3 and 3 NOT INCLUDING ZERO
		do
		{
			setHorizSpeed(randInt(-3, 3));
		} while (getHorizSpeed() == 0);
		setMovementPlanDistance(randInt(4, 32)); // change movement plan distance to a random int between 4 and 32 inclusive
		if (getHorizSpeed() < 0) // if horiz speed is negative
		{
			setDirection(180); // make the human pedestrian face left
		}
		else // if horiz speed is positive
		{
			setDirection(0); // make the human pedestrian face right
		}
		return;
	}
	return;
}

double ZombiePedestrian::getTicksToGrunt() const
{
	return m_ticksToGrunt;
}

void ZombiePedestrian::setTicksToGrunt(double ticksToGrunt)
{
	m_ticksToGrunt = ticksToGrunt;
}

bool ZombiePedestrian::getBlessed()
{
	setHitPoints(getHitPoints() - DAMAGE_HOLY_WATER_PROJECTILE); // damage the zombie pedestrian by one point
	if (getHitPoints() <= 0)
	{
		setIsAlive(false);
		getWorld()->playSound(SOUND_PED_DIE);
		int chanceAddHealingGoodie = randInt(1, 5);
		if (chanceAddHealingGoodie == 1)
		{
			getWorld()->addHealingGoodie(this);
		}
		getWorld()->increaseScore(SCORE_INCREASE_ZOMBIE_PED); // increase score by 150
	}
	else
	{
		getWorld()->playSound(SOUND_PED_HURT);
	}
	return true;
}

// NonCollisionAvoidant Class Function Implementations
NonCollisionAvoidant::NonCollisionAvoidant(int imageID, double startX, double startY, int startDirection, double size, int depth, double horizSpeed, double vertSpeed, bool isAlive, StudentWorld* ptrToWorld)
	:Actor(imageID, startX, startY, startDirection, size, depth, horizSpeed, vertSpeed, isAlive, ptrToWorld)
{

}

NonCollisionAvoidant::~NonCollisionAvoidant()
{
	// todo
}

bool NonCollisionAvoidant::isCollisionAvoidant()
{
	return false;
}

// HolyWaterProjectile Class Function Implementations
HolyWaterProjectile::HolyWaterProjectile(StudentWorld* ptrToWorld, double startX, double startY, int startDir)
	:NonCollisionAvoidant(IID_HOLY_WATER_PROJECTILE, startX, startY, startDir, HOLY_WATER_PROJECTILE_SIZE, HOLY_WATER_PROJECTILE_DEPTH, HOLY_WATER_PROJECTILE_HORIZ_SPEED, HOLY_WATER_PROJECTILE_VERT_SPEED, HOLY_WATER_PROJECTILE_START_IS_ALIVE, ptrToWorld)
{
	m_startX = startX;
	m_startY = startY;
	m_startDir = startDir;
	m_maxTravelDistance = HOLY_WATER_PROJECTILE_MAX_TRAVEL_DISTANCE;
}

HolyWaterProjectile::~HolyWaterProjectile()
{

}

void HolyWaterProjectile::doSomething()
{
	if (getIsAlive() == false) // if holy water projectile is not alive, do nothing
	{
		return;
	}
	// check to see if the projectile has activated
	getWorld()->checkProjectileCollision(this);
	if (getIsAlive() == false) // if a projectie damages a player, immediately return
	{
		return;
	}
	
	if (move() == false) // if after moving projectile is not alive
	{
		return;
	}
	return;
}

/*
double HolyWaterProjectile::getStartX() const
{
	return m_startX;
}

double HolyWaterProjectile::getStartY() const
{
	return m_startY;
}

double HolyWaterProjectile::getMaxTravelDistance() const
{
	return m_maxTravelDistance;
}
*/

bool HolyWaterProjectile::move()
{
	moveForward(SPRITE_HEIGHT); // move projectile
	if (getX() < 0 || getY() < 0 || getX() > VIEW_WIDTH || getY() > VIEW_HEIGHT) // if the Actor is out of bounds, set isAlive is false
	{
		setIsAlive(false);
		return false;
	}

	// Check if the holywater projectile moved 160 pixels
	double curX = getX();
	double curY = getY();
	double distanceMoved = sqrt((pow(m_startX - curX, 2)) + (pow(m_startY - curY, 2)));
	if (distanceMoved >= m_maxTravelDistance) // if the holy water projectile has moved more than its max travel distance
	{
		setIsAlive(false);
		return false;
	}
	return true;
}

// OilSlick Class Function Implementations
OilSlick::OilSlick(StudentWorld* ptrToWorld)
	:NonCollisionAvoidant(IID_OIL_SLICK, randInt(LEFT_EDGE, RIGHT_EDGE), VIEW_HEIGHT, OIL_SLICK_START_DIR, randInt(2, 5), OIL_SLICK_DEPTH, OIL_SLICK_START_HORIZ_SPEED, OIL_SLICK_START_VERT_SPEED, OIL_SLICK_START_IS_ALIVE, ptrToWorld)
{

}

OilSlick::OilSlick(StudentWorld* ptrToWorld, double startX, double startY)
	:NonCollisionAvoidant(IID_OIL_SLICK, startX, startY, OIL_SLICK_START_DIR, randInt(2, 5), OIL_SLICK_DEPTH, OIL_SLICK_START_HORIZ_SPEED, OIL_SLICK_START_VERT_SPEED, OIL_SLICK_START_IS_ALIVE, ptrToWorld)
{

}

OilSlick::~OilSlick()
{

}

void OilSlick::doSomething()
{
	if (move() == false) // move Actor, if out of bounds after moving do immediately return
	{
		return;
	}
	if (isOverlapping(getWorld()->getPlayer())) // if the player runs over an oilslick, make the player spin
	{
		getWorld()->playSound(SOUND_OIL_SLICK);

		// Tell ghostracer to spin itself
		int direction = randInt(0, 1); // used for chance to go clockwise or counterclockwise
									   // if direction is 0, go clockwise
									   // if direction is 1, go counterclockwise
		int randDirection = randInt(5, 20); // change in direction
		if (direction == 0) // move clockwise, subtracting to direction of ghostRacer
		{
			// 
			if ((getWorld()->getPlayer()->getDirection() - randDirection) >= MIN_DIRECTION) // if moving clockwise doesn't go under the limit of 60 degrees
			{
				// move clockwise randDirection degrees
				getWorld()->getPlayer()->setDirection((getWorld()->getPlayer()->getDirection() - randDirection));
			}
			else
			{
				// move counterclockwise randDirection degrees
				getWorld()->getPlayer()->setDirection((getWorld()->getPlayer()->getDirection() + randDirection));
			}
		}
		else // move counterclockwise, adding to direction of ghostRacer
		{
			if ((getWorld()->getPlayer()->getDirection() + randDirection) <= MAX_DIRECTION) // if moving counterclockwise doesn't go over the limit of 120 degrees
			{
				// move counterclockwise randDirection degrees
				getWorld()->getPlayer()->setDirection((getWorld()->getPlayer()->getDirection() + randDirection));
			}
			else
			{
				// move clockwise randDirection degrees
				getWorld()->getPlayer()->setDirection((getWorld()->getPlayer()->getDirection() - randDirection));
			}
		}

	}
	return;
}

// BorderLine Class Function Implementations
BorderLine::BorderLine(StudentWorld* ptrToWorld, int imageID, double startX, double startY)
	:NonCollisionAvoidant(imageID, startX, startY, BORDER_LINE_START_DIR, BORDER_LINE_SIZE, BORDER_LINE_DEPTH, BORDER_LINE_HORIZ_SPEED, BORDER_LINE_VERT_SPEED, BORDER_LINE_START_IS_ALIVE, ptrToWorld)
{

}

BorderLine::~BorderLine()
{

}

void BorderLine::doSomething()
{
	if (move() == false) // move BorderLine, if after moving BorderLine is out of bounds, immediately return
	{
		return;
	}
}

// Goodie Class Function Implementations
Goodie::Goodie(int imageID, double startX, double startY, int startDirection, double size, int depth, double horizSpeed, double vertSpeed, bool isAlive, StudentWorld* ptrToWorld)
	:NonCollisionAvoidant(imageID, startX, startY, startDirection, size, depth, horizSpeed, vertSpeed, isAlive, ptrToWorld)
{

}

Goodie::~Goodie()
{

}

void Goodie::doSomething()
{
	if (move() == false) // move. if after moving, Goodie is out of bounds, immediately return
	{
		return;
	}
	if (isOverlapping(getWorld()->getPlayer()))
	{
		overlapWithGhostRacer();
	}
	doDifferentiatedStuff();
	return;
}

void Goodie::doDifferentiatedStuff()
{
	return;
}

// HealingGoodie Class Function Implementations
HealingGoodie::HealingGoodie(StudentWorld *ptrToWorld, double startX, double startY)
	:Goodie(IID_HEAL_GOODIE, startX, startY, HEALING_GOODIE_START_DIR, HEALING_GOODIE_SIZE, HEALING_GOODIE_DEPTH, HEALING_GOODIE_HORIZ_SPEED, HEALING_GOODIE_VERT_SPEED, HEALING_GOODIE_START_IS_ALIVE, ptrToWorld)
{

}

HealingGoodie::~HealingGoodie()
{

}

/*
void HealingGoodie::doSomething()
{
	if (move() == false) // move. if after moving, HealingGoodie is out of bounds, immediately return
	{
		return;
	}
	if (isOverlapping(getWorld()->getPlayer()))
	{
		getWorld()->getPlayer()->increaseHitPoints(HEALING_GOODIE_HEAL);
		setIsAlive(false); // after healing, delete goodie
		getWorld()->playSound(SOUND_GOT_GOODIE);
		getWorld()->increaseScore(SCORE_INCREASE_HEALING_GOODIE);
	}
	return;
}
*/

bool HealingGoodie::getBlessed()
{
	setIsAlive(false);
	return true;
}

void HealingGoodie::overlapWithGhostRacer()
{
	getWorld()->getPlayer()->increaseHitPoints(HEALING_GOODIE_HEAL);
	setIsAlive(false); // after healing, delete goodie
	getWorld()->playSound(SOUND_GOT_GOODIE);
	getWorld()->increaseScore(SCORE_INCREASE_HEALING_GOODIE);
}

// SoulGoodie Class Function Implementations
SoulGoodie::SoulGoodie(StudentWorld* ptrToWorld)
	:Goodie(IID_SOUL_GOODIE, randInt(LEFT_EDGE, RIGHT_EDGE), VIEW_HEIGHT, SOUL_GOODIE_START_DIR, SOUL_GOODIE_SIZE, SOUL_GOODIE_DEPTH, SOUL_GOODIE_HORIZ_SPEED, SOUL_GOODIE_VERT_SPEED, SOUL_GOODIE_START_IS_ALIVE, ptrToWorld)
{

}

SoulGoodie::~SoulGoodie()
{

}

/*
void SoulGoodie::doSomething()
{
	if (move() == false) // move. if after moving, SoulGoodie is out of bounds, immediately return
	{
		return;
	}
	if (isOverlapping(getWorld()->getPlayer()))
	{
		getWorld()->decSoulsToSave();
		setIsAlive(false); // after overlapping with ghostRacer, should disappear
		getWorld()->playSound(SOUND_GOT_SOUL);
		getWorld()->increaseScore(SCORE_INCREASE_SOUL_GOODIE);
	}
	setDirection(getDirection() - 10);
	if (getDirection() < 0)
	{
		setDirection(359 - getDirection());
	}
	return;
}
*/

void SoulGoodie::overlapWithGhostRacer()
{
	getWorld()->decSoulsToSave();
	setIsAlive(false); // after overlapping with ghostRacer, should disappear
	getWorld()->playSound(SOUND_GOT_SOUL);
	getWorld()->increaseScore(SCORE_INCREASE_SOUL_GOODIE);
}

void SoulGoodie::doDifferentiatedStuff()
{
	setDirection(getDirection() - 10);
	if (getDirection() < 0)
	{
		setDirection(359 - getDirection());
	}
}
// HolyWaterGoodieClass Function Implementations
HolyWaterGoodie::HolyWaterGoodie(StudentWorld* ptrToWorld)
	:Goodie(IID_HOLY_WATER_GOODIE, randInt(LEFT_EDGE, RIGHT_EDGE), VIEW_HEIGHT, HOLY_WATER_GOODIE_START_DIR, HOLY_WATER_GOODIE_SIZE, HOLY_WATER_GOODIE_DEPTH, HOLY_WATER_GOODIE_HORIZ_SPEED, HOLY_WATER_GOODIE_VERT_SPEED, HOLY_WATER_GOODIE_START_IS_ALIVE, ptrToWorld)
{

}

HolyWaterGoodie::~HolyWaterGoodie()
{

}

/*
void HolyWaterGoodie::doSomething()
{
	if (move() == false) // move. if after moving, HolyWaterGoodie is out of bounds, immediately return
	{
		return;
	}
	if (isOverlapping(getWorld()->getPlayer()))
	{
		getWorld()->getPlayer()->setNumHolyWaterGoodies(getWorld()->getPlayer()->getNumHolyWaterGoodies() + HOLY_WATER_GOODIE_INCREASE_CHARGES);
		setIsAlive(false); // after getting picked up by ghostRacer, goodie should disappear
		getWorld()->increaseScore(SCORE_INCREASE_HOLY_WATER_GOODIE);
		getWorld()->playSound(SOUND_GOT_GOODIE);
	}
	return;
}
*/

void HolyWaterGoodie::overlapWithGhostRacer()
{
	getWorld()->getPlayer()->setNumHolyWaterGoodies(getWorld()->getPlayer()->getNumHolyWaterGoodies() + HOLY_WATER_GOODIE_INCREASE_CHARGES);
	setIsAlive(false); // after getting picked up by ghostRacer, goodie should disappear
	getWorld()->increaseScore(SCORE_INCREASE_HOLY_WATER_GOODIE);
	getWorld()->playSound(SOUND_GOT_GOODIE);
}

bool HolyWaterGoodie::getBlessed()
{
	setIsAlive(false); // if holy water projectile overlaps with holy water goodie, holy water gooodie should disappear
	return true;
}