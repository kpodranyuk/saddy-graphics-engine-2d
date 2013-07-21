/*! \file movitem.h
    \author DVK, HiddenSeeker

	Describes a movable items

	A movable item, is an item, that moves in one direction, until reaches
	an end of screen, or some other condition. Also it rotates. 
*/
#include "../renderer.h"
#include <math.h>
#include "statemachine.h"
#include "rigid_body.h"
#include "collisionmanager.h"
#include "../texturemanager.h"
#pragma once

typedef hPointF Vector;

class MovingObject: public Collidable
{
 SAD_OBJECT
 protected:
	     float m_angle;
 public: 
	 /*! Only calls a parent constructor 
	 */
	 inline MovingObject(const hst::rect< ::s3d::point > & rect,
		 const hRectF & texrect):Collidable(sad::TextureManager::ref()->get("objects"),rect,texrect)
	 {
		 m_angle=0;
	 }
	 inline float angle() { return m_angle; }
	 virtual void render();
	 virtual ~MovingObject();
};

class PlayerBullet: public MovingObject 
{
 SAD_OBJECT
 public:
        /*! Creates an item
		    \param[in] vec direction, that will be reached in second
		    \param[in] pos position, where it's being drawn
	    */
	    PlayerBullet(
		             const Vector & vec,
					 const ::s3d::point &  pos 
			        );
		~PlayerBullet();
};


class EnemyBullet: public MovingObject 
{
 SAD_OBJECT
 public:
        /*! Creates an item
		    \param[in] vec direction, that will be reached in second
		    \param[in] pos position, where it's being drawn
	     */
	    EnemyBullet(
		             const Vector & vec,
		             const ::s3d::point & pos
			        );
		~EnemyBullet();
};

class Bonus: public MovingObject
{
 SAD_OBJECT
 public:
        /*! Creates an item
		    \param[in] vec direction, that will be reached in second
		    \param[in] pos position
	     */
	    Bonus(
		      const Vector & vec,
		      const hPointF &  pos
			 );
		~Bonus();
};


class Enemy: public MovingObject 
{
 SAD_OBJECT
 public:
        /*! Creates an item
		    \param[in] vec direction, that will be reached in second
		    \param[in] pos position
	     */
	    Enemy(
		             const Vector & vec,
		             const hPointF &  pos 
			        );
		~Enemy();
};

#define SHOOT_FREQ 450
class ShootingEnemy: public MovingObject 
{
 SAD_OBJECT
 private:
	     clock_t m_lastclock;
 public:
        /*! Creates an item
		    \param[in] vec direction, that will be reached in second
	     */
	    ShootingEnemy(
		             const Vector & vec,
		             const hPointF &  pos 
			        );
		/*! Renders an enemy
		*/
		void render();
		~ShootingEnemy();
};
#define EMAX_LIFES 3 
class SuperShootingEnemy: public MovingObject
{
 SAD_OBJECT
 private:
	     clock_t m_lastclock;
		 int     m_lifes;   //!< Amount of lifes
 public:
	    /*! Decrement lifes
		*/
	    void hit();
        /*! Creates an item
		    \param[in] vec direction, that will be reached in second
	     */
	    SuperShootingEnemy(
		             const Vector & vec,
		             const hPointF &  pos 
			        );
		/*! Renders an enemy
		*/
		void render();
		~SuperShootingEnemy();
};

#define SPAWN_FREQ 350
#define SPAWN_FREQ4 200
#define IDLE_RAIN  1
#define REAL_SPAWN 2
#define BOUND_X1 0.0f
#define BOUND_X2  (sad::Renderer::ref()->settings().width())
#define BOUND_Y1 0.0f
#define BOUND_Y2  (sad::Renderer::ref()->settings().height())
/*! Class, that periodicly emits some enemies
*/
class EnemyEmitter:public sad::BasicNode
{
 SAD_OBJECT
 private:
	     clock_t m_clk;
		 void (EnemyEmitter::*m_r)();
 public:
	     EnemyEmitter(int what=REAL_SPAWN);
		 void render();
		 void renderRain();
		 void renderSpawn();
		 ~EnemyEmitter();
};

