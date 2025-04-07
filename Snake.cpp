#include <NonBlockingGame.h>
#include <iostream>
#include <time.h>
#include <vector>


//
//  The purpose of this assignment is to learn to 1. The classic game of Snake.
//  Move a "snake" (line of sprites) along a 2D grid attempting to run over a
//  randomly placed object to help it grow. 2. If it runs into itself the game is over
//  and the player has lost. 3. The object of the game is to make the snake as big as possible.
//
using namespace bridges::game;
using namespace std;

// this keeps a list of elements (squares) that represents the snake object
// linked list since it can grow as the game progresses
class Block {
  public:
    Block *next = nullptr;
    int x;
    int y;
    Block() {
      x = 0;
      y = 0;
    }
    Block(int x, int y) {
      this->x = x;
      this->y = y;
    }
};

struct Snake : public NonBlockingGame {
  long frameTime;
  long nextFrameTime;

  // keep an element to represent something the snake would consume to grow,
  // for instance, an apple and keep track of the snake head (both will be elements of
  // type Block
  Block fruit;

  Block* head = new Block;


  // keep track of snake direction (can move in all 4 directions, its last direction
  // and current direction
  
  enum Direction {


  int frame = 0;

  // create the game grid
  Snake(int assID, std::string username, std::string apikey)
    : NonBlockingGame (0, username, apikey, 30, 30) {
  }

  virtual void initialize() override {
    srand(time(NULL));
  	setTitle("Snake");
  	setDescription("Snake: Eat the food, not yourself! Use the arrow keys to move.");

    // create the snake of some number of elements,
    // perform all initializations, place the apple

    paint();
  }

  void handleInput() {
    // Use the 4 arrow keys to move the snake in a particular direction
  }

  // update snake position
  void updatePosition() {

    // Move the snake one position, based on its direction and update
    // the linked list


    // handle edge cases - check to make sure the snake
    // doesnt go off the edge of the board; can do a wrap around
    // in X or Y to handle it. Must handle all 4 directions the snake
    // might be traveling..
  }

  // locate apple at new position
  void plantApple() {
    // randomly position the apple, taking care to ensure that it doesnt
    // intersect with the snake position.
  }

  // check if snake has found the apple
  void detectApple() {
    // if apple is found, snake consumes it and update the board and plant
    // a new apple on the board.
  }


  // check if snake ate itself! Yuk!
  void detectDeath() {

  }


  // redraw
  void paint() {

    // draw the board, the apple and the snake
    // make sure to choose colors so that snake and apple are clearly visible.
  }

  // handle input, check if apple was detected, update position, redraw,
  // detect if snake ate itself. To adjust speed of game and make it playable,
  // keep the frame counter
  // and perform updates every n frames or so.
  virtual void gameLoop() override {
  }
};

// Initialize your game
// Call your game class with your assignment id, username, and api key
int main (int argc, char** argv) {
  Snake g(122, "BRIDGES_USER_ID", "BRIDGES_API_KEY");
  
  
  g.start();
}

