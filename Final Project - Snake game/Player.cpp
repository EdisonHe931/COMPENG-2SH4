#include "Player.h"
#include "MacUILib.h"
#include <iostream>
#include "Food.h"

// Default Constructor
Player::Player()
   : player(nullptr), foodlist(nullptr), mainGameMechsRef(nullptr), myDir(STOP), speed(1), rowNums(0), colNums(0)
{ }

// Parameterized Constructor
Player::Player(GameMechs* thisGMRef, Food* thisFood)
   : mainGameMechsRef(thisGMRef), foodlist(thisFood), myDir(STOP), speed(1)
{
   player = new objPosArrayList();

   // Initialize board dimensions
   rowNums = mainGameMechsRef->getBoardWidth();
   colNums = mainGameMechsRef->getBoardHeight();

   // Snake start pos
   int startX = rowNums / 2;
   int startY = colNums / 2;

   char headSymbol = '@';
   char bodySymbol = '+';

   // Snake starts with length 2
   for (int i = 0; i < 2; i++)
   {
       player->insertHead(objPos(startX - i, startY, (i == 0) ? headSymbol : bodySymbol));
   }
   headsymbol = '@';
   bodysymbol = 'o';
}

// Destructor
Player::~Player()
{
   delete player;
}

// Copy Constructor
Player::Player(const Player& pp)
{
   mainGameMechsRef = pp.mainGameMechsRef;
   foodlist = pp.foodlist;
   myDir = pp.myDir;
   rowNums = pp.rowNums;
   colNums = pp.colNums;
   speed = pp.speed;

   player = new objPosArrayList(*pp.player);
   headsymbol = pp.headsymbol;
   bodysymbol = pp.bodysymbol;
}

// Copy Assignment Operator
Player& Player::operator=(const Player& pp)
{
   if (this != &pp)
   {
       delete player;

       mainGameMechsRef = pp.mainGameMechsRef;
       foodlist = pp.foodlist;
       myDir = pp.myDir;
       rowNums = pp.rowNums;
       colNums = pp.colNums;
       speed = pp.speed;

       player = new objPosArrayList(*pp.player);
       headsymbol = pp.headsymbol;
       bodysymbol = pp.bodysymbol;
   }
   return *this;
}

// Get the player pos list
objPosArrayList* Player::getPlayerPos() const
{
   return player;
}

// Update player direction based on input
void Player::updatePlayerDir()
{
   if (mainGameMechsRef->getUserInput() != 0) // Check if theres input
   {
       switch (mainGameMechsRef->getUserInput())
       {
       case 32: // Space key: Exit the game
           mainGameMechsRef->setExitGame();
           break;
       case 'w': case 'W': if (myDir != DOWN) myDir = UP; break;
       case 'a': case 'A': if (myDir != RIGHT) myDir = LEFT; break;
       case 's': case 'S': if (myDir != UP) myDir = DOWN; break;
       case 'd': case 'D': if (myDir != LEFT) myDir = RIGHT; break;
       default:
           break; // Ignore invalid input
       }
       mainGameMechsRef->resetUserInput();
   }
}

// Move the player (snake)
void Player::movePlayer()
{
   int x = player->getHeadElement().pos->x;
   int y = player->getHeadElement().pos->y;

   // Remove head and add as body
   player->removeHead();
   player->insertHead(objPos(x, y, bodysymbol));

   // Update the head position based on direction
   switch (myDir)
   {
   case UP:    x--; break;
   case DOWN:  x++; break;
   case LEFT:  y--; break;
   case RIGHT: y++; break;
   default:    break; 
   }

   // Wraparound 
   if (x > rowNums - 2) x = 1;
   if (x < 1) x = rowNums - 2;
   if (y > colNums - 2) y = 1;
   if (y < 1) y = colNums - 2;

   // Insert the new head
   objPos newHead(x, y, headsymbol);
   player->insertHead(newHead);

   // Check if food is consumed
   if (checkFoodConsumption())
   {
       increasePlayerLength();
       mainGameMechsRef->updateScore(player->getSize());
       foodlist->generateFood(*player, rowNums, colNums);
   }
   else
   {
       player->removeTail(); // Remove tail if no food eaten
   }

   // Check for self-collision
   if (checkselfcollision())
   {
       mainGameMechsRef->setLoseGame();
   }

   // Check for win condition
   if (player->getSize() > 50)
   {
       mainGameMechsRef->setWinGame();
   }
}

// Check if food is consumed
bool Player::checkFoodConsumption()
{
   objPos head = player->getHeadElement();
   for (int i = 0; i < FOOD_SPAWN_CAP; i++)
   {
       objPos food = foodlist->getFoodPos(i);
       if (head.pos->x == food.pos->x && head.pos->y == food.pos->y)
       {
           return true;
       }
   }
   return false;
}

// Increase the snake length
void Player::increasePlayerLength()
{
   objPos newTail = player->getTailElement();
   player->insertTail(newTail);
}

// Check if the snake eat itself
bool Player::checkselfcollision()
{
   objPos head = player->getHeadElement();
   for (int i = 2; i < player->getSize(); i++) 
   {
       objPos segment = player->getElement(i);
       if (head.pos->x == segment.pos->x && head.pos->y == segment.pos->y)
       {
           return true; // Collision detected
       }
   }
   return false;
}

// Get speed
int Player::getSpeed() const
{
   return speed;
}

// Set speed
void Player::setSpeed(int s)
{
   if (s >= 1 && s <= 5)
   {
       speed = s;
   }
}

Food* Player::getFoodlist() const
{
   return foodlist;
}