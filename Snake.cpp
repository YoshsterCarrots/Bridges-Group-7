#include <NonBlockingGame.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <cstdlib>


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

	~Block() {
		if (next != nullptr) {
			delete next;
		}
		delete this;
	}
};

struct Snake : public NonBlockingGame {
  long frameTime;
  long nextFrameTime;

  // keep an element to represent something the snake would consume to grow,
  // for instance, an apple and keep track of the snake head (both will be elements of
  // type Block
  Block* head;
  Block apple;

  // keep track of snake direction (can move in all 4 directions, its last direction
  // and current direction
  
  enum Direction {
	  UP, RIGHT, DOWN, LEFT
  };

  Direction currDir = UP;
  Direction prevDir = UP; //Not sure what to use this for...

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
	srand(time(0));

	head = new Block(15, 15);
	plantApple();
	//TODO: Initialize colors

    paint();
  }

  void handleInput() {
    // Use the 4 arrow keys to move the snake in a particular direction
	prevDir = currDir;
	if (keyUp() || keyW()) {
		currDir = UP;
	}
	else if (keyRight() || keyD()) {
		currDir = RIGHT;
	}
	else if (keyDown() || keyS()) {
		currDir = DOWN;
	}
	else if (keyLeft() || keyA()) {
		currDir = LEFT;
	}
  }

  // update snake position
  void updatePosition() {

    // Move the snake one position, based on its direction and update
    // the linked list
	
	//Kerney said we just need to add a new one onto the front and remove the one at the back
	Block* temp = new Block(head->x, head->y);
	temp->next = head;
	head = temp;

	if (currDir == UP) {
		head->y -= 1;
	}
	if (head->y < 0) {
		head->y = 29;
	}
	if (currDir == RIGHT) {
		head->x += 1;
	}
	if (head->x > 29) {
		head->x = 0;
	}
	if (currDir == DOWN) {
		head->y += 1;
	}
	if (head->y > 29) {
		head->y = 0;
	}
	if (currDir == LEFT) {
		head->x -= 1;
	}
	if (head->x < 0) {
		head->x = 29;
	}

	detectApple();

	for (Block* segment = head; segment != nullptr; segment = segment->next) {
		if (segment->next = nullptr) {
			delete segment;
			break;
		}
	}

	detectDeath();

    // handle edge cases - check to make sure the snake
    // doesnt go off the edge of the board; can do a wrap around
    // in X or Y to handle it. Must handle all 4 directions the snake
    // might be traveling..
  }

  // locate apple at new position
  void plantApple() {
    // randomly position the apple, taking care to ensure that it doesnt
    // intersect with the snake position.
	apple.x = rand() % 30;
	apple.y = rand() % 30;
	for (Block* segment = head; segment != nullptr; segment = segment->next) {
		if (apple.x == segment->x && apple.y == segment->y) {
			plantApple();
			break;
		}
	}
  }

  // check if snake has found the apple
  void detectApple() {
    // if apple is found, snake consumes it and update the board and plant
    // a new apple on the board.	
	if (apple.x == head->x && apple.y == head->y) {
		for (Block* segment = head; segment != nullptr; segment = segment->next) {
			if (segment->next == nullptr) {
				Block* temp = new Block(segment->x, segment->y);
				plantApple();
			}
		}
	}
  }


  // check if snake ate itself! Yuk!
  void detectDeath() {
	for (Block* segment = head->next; segment != nullptr; segment = segment->next) {
		if (head->x == segment->x && head->y == segment->y) {
			//Any other stuff we want to do before game over goes here
			delete head;
			quit();
		}
	}
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
	  //initialize();
	  handleInput();
	  updatePosition();
	  paint();

  }
};

// Initialize your game
// Call your game class with your assignment id, username, and api key
int main (int argc, char** argv) {
  Snake g(122, "BRIDGES_USER_ID", "BRIDGES_API_KEY");
  
  
  g.start();
}

