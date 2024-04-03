/***********************************************************************
 * Header File:
 *    TEST HOWITZER
 * Author:
 *    Fabian Diaz Santiago and Josue Molina
 * Summary:
 *    All the unit tests for Howitzer
 ************************************************************************/


#pragma once

#include "howitzer.h"
#include "unitTest.h"

/*******************************
 * TEST HOWITZER
 * A friend class for Howitzer which contains the Howitzer unit tests
 ********************************/
class TestHowitzer : public UnitTest
{
public:
   void run()
   {
      // Ticket 1: Getters
      defaultConstructor();
      getPosition_zero();
      getPosition_middle();
      getMuzzleVelocity_slow();
      getMuzzleVelocity_standard();
      getElevation_up();
      getElevation_right();
      getElevation_left();

      // Ticket 2: Setters
      generatePosition_small();
      generatePosition_large();
      raise_rightDown();
      raise_rightUp();
      raise_leftDown();
      raise_leftUp();
      rotate_clock();
      rotate_counterClock();
      rotate_wrapClock();
      rotate_wrapCounterClock();

      report("Howitzer");
   }

private:
   double metersFromPixels = -1.0;

   /*****************************************************************
    *****************************************************************
    * CONSTRUCTOR
    *****************************************************************
    *****************************************************************/

    /*********************************************
     * name:    DEFAULT CONSTRUCTOR
     * input:   nothing
     * output:  zeros
     *********************************************/
   void defaultConstructor()
   {
       // exercise
       Howitzer h;

       // Verify
       assertEquals(h.position.x, 0.0);       
       assertEquals(h.position.y, 0.0);
       assertEquals(h.muzzleVelocity, DEFAULT_MUZZLE_VELOCITY);
       assertEquals(h.elevation.radians, 0.7853); // 45.0 / 180 * 3.14159 = 0.7853 radians
   }// teardown

   /*****************************************************************
    *****************************************************************
    * GETTERS
    *****************************************************************
    *****************************************************************/

    /*********************************************
     * name:    GET POSITION ZERO
     * input:   h.pos=(0,0)
     * output:  pos=(0,0)
     *********************************************/
   void getPosition_zero()
   {
      // setup
      Howitzer h;
      h.position.x = 0.0;
      h.position.y = 0.0;

      // Exercise
      Position& pos = h.getPosition();

      // Verify
      assertEquals(pos.x, 0.0);
      assertEquals(pos.y, 0.0);
      assertEquals(h.position.x, 0.0);
      assertEquals(h.position.y, 0.0);
   }// teardown

   /*********************************************
    * name:    GET POSITION MIDDLE
     * input:   h.pos=(123.4, 567.8)
     * output:  pos=(123.4, 567.8)
    *********************************************/
   void getPosition_middle()
   {
       // setup
       Howitzer h;
       h.position.x = 123.4;
       h.position.y = 567.8;

       // Exercise
       Position& pos = h.getPosition();

       // Verify
       assertEquals(pos.x, 123.4);
       assertEquals(pos.y, 567.8);
       assertEquals(h.position.x, 123.4);
       assertEquals(h.position.y, 567.8);
   }// teardown

   /*********************************************
    * name:    GET MUZZLE VELOCITY - SLOW SPEED
     * input:   h.muzzleVelocity=(24.68)
     * output:  m=24.68
    *********************************************/
   void getMuzzleVelocity_slow()
   {
       // Setup
       Howitzer h;
       h.muzzleVelocity = 24.68;
       double m = -99.9;

       // Exercise
       m = h.getMuzzleVelocity();

       // Verify
       assertEquals(m, 24.68);
       assertEquals(h.muzzleVelocity, 24.68);

   }// teardown

   /*********************************************
    * name:    GET MUZZLE VELOCITY - STANDARD SPEED
     * input:   h.muzzleVelocity=(827.00)
     * output:  m=827
    *********************************************/
   void getMuzzleVelocity_standard()
   {
       // Setup
       Howitzer h;
       h.muzzleVelocity = 827.00;
       double m = -99.9;

       // Exercise
       m = h.getMuzzleVelocity();

       // Verify
       assertEquals(m, 827.00);
       assertEquals(h.muzzleVelocity, 827.00);
   }// teardown

   /*********************************************
    * name:    GET ELEVATION - up
     * input:   h.elevation=0
     * output:  e=0
    *********************************************/
   void getElevation_up()
   {
       // Setup
       Howitzer h;
       h.elevation = 0.0;

       // Exercise 
       const Angle& e = h.getElevation();

       // Verify
       assertEquals(e.radians, 0.0);
   }// teardown

   /*********************************************
    * name:    GET ELEVATION - right
     * input:   h.elevation=0.4
     * output:  e=0.4
    *********************************************/
   void getElevation_right()
   {
       // Setup
       Howitzer h;
       h.elevation = 0.4;

       // Exercise 
       const Angle& e = h.getElevation();

       // Verify
       assertEquals(e.radians, 0.0069); // 0.4 / 180 * 3.14159 = 0.0069 radians
   }// teardown

   /*********************************************
    * name:    GET ELEVATION - left
     * input:   h.elevation=5.8
     * output:  e=5.8
    *********************************************/
   void getElevation_left()
   {
       // Setup
       Howitzer h;
       h.elevation = 5.8;

       // Exercise 
       const Angle& e = h.getElevation();

       // Verify
       assertEquals(e.radians, 0.1012); // 5.8 / 180 * 3.14159 = 0.1012 radians
   }// teardown

   /*****************************************************************
    *****************************************************************
    * SETTERS
    *****************************************************************
    *****************************************************************/

    /*********************************************
     * name:    GENERATE POSITION small board
     * input:   (10px, 10px)
     * output:  0 <= x <= 9
     *********************************************/
   void generatePosition_small()
   {
       // Setup
       Howitzer h;
       h.position.x = 10;
       h.position.y = 10;

       // Exercise 
       h.generatePosition(h.getPosition());

       // Verify
       double x = h.getPosition().getPixelsX();
       assert(0 <= x && x <= 9);

   }// teardown

    /*********************************************
    * name:    GENERATE POSITION large board
    * input:   (1000px, 1000px)
    * output:  0 <= x <= 900
    *********************************************/
   void generatePosition_large()
   {
       // Setup
       Howitzer h;
       h.position.x = 1000;
       h.position.y = 1000;

       // Exercise 
       h.generatePosition(h.getPosition());

       // Verify
       double x = h.getPosition().getPixelsX();
       assert(0 <= x && x <= 900);
   }// teardown

   /*********************************************
    * name:    RAISE to the right/down
    * input:   h.elevation=0.5radians  raise(-0.1)
    * output:  h.elevation=0.6radians
    *********************************************/
   void raise_rightDown()
   {
       // Setup
       Howitzer h; 
       h.elevation.radians = 0.5;               

       // Exercise 
       h.raise(-0.1);

       // Verify
       assertEquals(h.elevation.radians, 0.6);
   }// teardown

   /*********************************************
    * name:    RAISE to the right/up
    * input:   h.elevation=0.5radians  raise(0.1)
    * output:  h.elevation=0.4radians
    *********************************************/
   void raise_rightUp()
   {
       // Setup
       Howitzer h;
       h.elevation.radians = 0.5;               

       // Exercise 
       h.raise(0.1);

       // Verify
       assertEquals(h.elevation.radians, 0.4);
   }// teardown

   /*********************************************
    * name:    RAISE to the left down
    * input:   h.elevation=-0.5radians  raise(-0.1)
    * output:  h.elevation=-0.6radians
    *********************************************/
   void raise_leftDown()
   {
       // Setup
       Howitzer h;
       h.elevation.radians = 5.783;  // This equals  -0.5 radians

       // Exercise 
       h.raise(-0.1);

       // Verify
       assertEquals(h.elevation.radians, 5.683); // This equals  -0.6 radians
   }// teardown

   /*********************************************
    * name:    RAISE to the left up
    * input:   h.elevation=-0.5radians  raise(0.1)
    * output:  h.elevation=0.4radians
    *********************************************/
   void raise_leftUp()
   {
      // Setup
      Howitzer h;
      h.elevation.radians = -5.783;             // This equals  -0.5 radians

      // Exercise 
      h.raise(0.1);

      // Verify
      assertEquals(h.elevation.radians, 0.4001);   // This equals  0.4 radians
   }// teardown

   /*********************************************
    * name:    ROTATE CLOCKWISE no wrapping
    * input:   h.elevation=1.23 rotate=.3
    * output:  h.elevation=1.53
    *********************************************/
   void rotate_clock()
   {
       // Setup
       Howitzer h;
       h.elevation.radians = 1.23;

       // Exercise 
       h.rotate(0.3);

       // Verify
       assertEquals(h.elevation.radians, 1.53);
   }// teardown

   /*********************************************
    * name:    ROTATE COUNTER CLOCKWISE no wrapping
    * input:   h.elevation=1.23 rotate=-.3
    * output:  h.elevation=0.93
    *********************************************/
   void rotate_counterClock()
   {
       // Setup
       Howitzer h;
       h.elevation.radians = 1.23;

       // Exercise 
       h.rotate(-0.3);

       // Verify
       assertEquals(h.elevation.radians, 0.93);    
   }// teardown

   /*********************************************
    * name:    ROTATE CLOCKWISE CLOCKWISE WRAP BY 2PI
    * input:   h.elevation=6.1 rotate=.2
    * output:  h.elevation=.1
    *********************************************/
   void rotate_wrapClock()
   {
       // Setup
       Howitzer h; 
       h.elevation.radians = 6.1;

       // Exercise 
       h.rotate(0.2);

       // Verify
       assertEquals(h.elevation.radians, 0.0168);         // ask this!!!! (0.0168)
   }// teardown

   /*********************************************
    * name:    ROTATE COUNTER CLOCKWISE WRAP BY 4PI
    * input:   h.elevation=0.1 rotate=-.2 - 4PI
    * output:  h.elevation=6.1
    *********************************************/
   void rotate_wrapCounterClock()
   {
       // Setup
       Howitzer h;
       h.elevation.radians = 0.1;

       // Exercise 
       h.rotate(-0.2);

       // Verify
       assertEquals(h.elevation.radians, 6.1831);        // ask this!!!! (8331)
   }// teardown

   /*****************************************************************
    *****************************************************************
    * STANDARD FIXTURE
    *****************************************************************
    *****************************************************************/

   // setup standard fixture - set the zoom to 1100m per pixel
   void setupStandardFixture()
   {
      Position p;
      metersFromPixels = p.metersFromPixels;
      p.metersFromPixels = 1100.0;
   }

   // teardown the standard fixture - reset the zoom to what it was previously
   void teardownStandardFixture()
   {
      assert(metersFromPixels != -1.0);
      Position p;
      p.metersFromPixels = metersFromPixels;
   }
};
