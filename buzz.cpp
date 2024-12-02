
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;


//TODO:  IMPLEMENT GRID UPDATES FOR ALL FUNCS, IMPLEMENT BEE HIVE, IMPLEMENT HUMMINGBIRD, IMPLEMENT SCORE BOARD, IMPLEMENT MENU AND LEVELS

// Initializing Dimensions.
// resolutionX and resolutionY determine the rendering resolution.

const int resolutionX = 800; //the original buzz bombers has dimensions  159 x 98, these dimensions are scaled 5x for our game
const int resolutionY = 480;
const int boxPixelsX = 32;
const int boxPixelsY = 32;
const int gameRows =resolutionY / boxPixelsY; // Total rows on grid
const int gameColumns = (resolutionX / boxPixelsX); // Total columns on grid

// Initializing GameGrid.
int gameGrid[gameRows][gameColumns] = {0};

void printGameGrid() ;
void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite);
void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock);
void drawBullet(RenderWindow& window, float& bullet_x, float& bullet_y, Sprite& bulletSprite);
void movePlayer(float& player_x, float player_y, int boundaryLeft,  int boundaryRight,  float speed, int flowerCord[][2], int flowerActive[], const int MAX_FLOWERS);
void fireBullet(float& bullet_x, float& bullet_y, bool& bullet_exists, float player_x, float player_y);
void beesGenerator(float beesX[], float beesY[], int beeTypes[], bool beesActive[], int beesTier[], bool beesDirection[], int MAX_BEES, int WORKER_BEE);
void moveBees(float beesX[], float beesY[], int beesTier[], bool beesDirection[], int beeTypes[], bool beesActive[], int MAX_BEES, float deltaTime, int WORKER_BEE, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS,int flowerCord[][2], int flowerActive[], const int MAX_FLOWERS);
void drawBees(RenderWindow& window);
bool checkBeeCollision(float bullet_x, float bullet_y, float beesX[], float beesY[], int beeTypes[], bool beesActive[], int beesTier[], bool beesDirection[], int MAX_BEES, int WORKER_BEE, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS);
void drawBees(RenderWindow& window, float beesX[], float beesY[], int beeTypes[], bool beesActive[], int beesTier[], bool beesDirection[], int MAX_BEES, int WORKER_BEE);
void drawHoneycombs(RenderWindow& window, 
                    float honeycombX[], float honeycombY[], 
                    int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS);             
void generateHoneycomb(float bee_x, float bee_y, int beeType, 
                       float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS);
bool checkHoneyCombCollision(float bullet_x, float bullet_y, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS);
void drawFlowers(RenderWindow& window, int flowerCord[][2], int flowerActive[], const int MAX_FLOWERS );
bool flowerGenerator(float beeX, float beeY, int flowerCord[][2], int flowerActive[], const int MAX_FLOWERS);
/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// Write your functions declarations here. Some have been written for you. //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////


int main()
{
	srand(time(0));

	// Declaring RenderWindow.
	RenderWindow window(VideoMode(resolutionX, resolutionY), "Buzz Bombers", Style::Close | Style::Titlebar);

	// Used to position your window on every launch. Use according to your needs.
	window.setPosition(Vector2i(500, 200));

	// Initializing Background Music.
	Music bgMusic;
	if (!bgMusic.openFromFile("Music/Music3.ogg")) {
    cout << "Error: Could not load music file!" << endl;
	}
	bgMusic.setVolume(50);
	bgMusic.setLoop(true);
	bgMusic.play();

	// Initializing Player and Player Sprites.
	float player_x = (gameColumns / 2) * boxPixelsX;
	float player_y = (gameRows - 4) * boxPixelsY;

	Texture playerTexture;
	Sprite playerSprite;
	playerTexture.loadFromFile("Textures/spray.png");
        playerSprite.setTextureRect(IntRect(10, 0, playerTexture.getSize().x, playerTexture.getSize().y));
	playerSprite.setTexture(playerTexture);


		// Initializing Bullet and Bullet Sprites
		// Data for bullet / Spray pellet

	float bullet_x = player_x;
	float bullet_y = player_y;
	bool bullet_exists = true;

	Clock bulletClock;
	Texture bulletTexture;
	Sprite bulletSprite;
	bulletTexture.loadFromFile("Textures/bullet.png");
	bulletSprite.setTexture(bulletTexture);
	bulletSprite.setScale(2, 2);
	bulletSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

	// The ground on which player moves

	RectangleShape groundRectangle(Vector2f(960, 64));
	groundRectangle.setPosition(0, (gameRows - 2) * boxPixelsY);
	groundRectangle.setFillColor(Color::Red);
        
        //BEES NIGGA
        int MAX_BEES = 50;
        int WORKER_BEE = 0;
        int KILLER_BEE = 1;

        // Bee Arrays
        float beesX[MAX_BEES];
        float beesY[MAX_BEES];
        int beeTypes[MAX_BEES] = {0};
        bool beesActive[MAX_BEES] = {0};
        int beesTier[MAX_BEES];
        bool beesDirection[MAX_BEES]; // true = right, false = left
        Clock movementClock;
        
        //HONEYCOMBSSS
        int MAX_HONEYCOMBS = 100;
        float honeycombX[MAX_HONEYCOMBS];
        float honeycombY[MAX_HONEYCOMBS];
        int honeycombType[MAX_HONEYCOMBS];
        bool honeycombActive[MAX_HONEYCOMBS] = {0};
  
        //flowers
        const int MAX_FLOWERS = 100;
        int flowerCord[MAX_FLOWERS][2] = {0};
        int flowerActive[MAX_FLOWERS] = {0};
                
        
        
        
        
            
	while (window.isOpen()) {
        float deltaTime = movementClock.restart().asSeconds(); //gets the time between each frame reload (every run of the game loop)
  
              printGameGrid();
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed) {
				return 0;
			}
		}
 
		///////////////////////////////////////////////////////////////
		//                                                           //
		// Call Your Functions Here. Some have been written for you. //
		// Be vary of the order you call them, SFML draws in order.  //
		//                                                           //
		///////////////////////////////////////////////////////////////
                beesGenerator(beesX, beesY ,beeTypes, beesActive, beesTier, beesDirection, MAX_BEES, WORKER_BEE);  
                movePlayer(player_x, player_y, 0, resolutionX - boxPixelsX, 0.32, flowerCord,flowerActive,MAX_FLOWERS);
                moveBees(beesX,beesY, beesTier,  beesDirection, beeTypes,  beesActive,  MAX_BEES,  deltaTime,  WORKER_BEE, honeycombX, honeycombY,honeycombType,honeycombActive,MAX_HONEYCOMBS, flowerCord, flowerActive, MAX_FLOWERS);
                fireBullet(bullet_x, bullet_y, bullet_exists, player_x, player_y);
    
		if (bullet_exists == true)
		{       
			moveBullet(bullet_y, bullet_exists, bulletClock);
			drawBullet(window, bullet_x, bullet_y, bulletSprite);
			//simple functionality to check if bullet has hit bee
			//simple functionality to check if bullet hit honeycomb
			if (checkBeeCollision( bullet_x, bullet_y, beesX, beesY ,beeTypes, beesActive, beesTier, beesDirection, MAX_BEES, WORKER_BEE, honeycombX, honeycombY, honeycombType, honeycombActive,  MAX_HONEYCOMBS)) 
			{
                          bullet_exists = false;			
			}else{
			if (checkHoneyCombCollision( bullet_x, bullet_y,honeycombX, honeycombY,honeycombType, honeycombActive,  MAX_HONEYCOMBS)){
			bullet_exists = false;
			}
			}
		}
		else
		{
			bullet_x = player_x;
			bullet_y = player_y+64;
		}
                
		drawPlayer(window, player_x, player_y, playerSprite);
                drawBees(window, beesX, beesY ,beeTypes, beesActive, beesTier, beesDirection, MAX_BEES, WORKER_BEE);
		window.draw(groundRectangle);
		drawHoneycombs(window, honeycombX, honeycombY, honeycombType, honeycombActive, MAX_HONEYCOMBS);
		drawFlowers(window, flowerCord,flowerActive,MAX_FLOWERS);
		window.display();
		window.clear();
	}
}

////////////////////////////////////////////////////////////////////////////
//                                                                        //
// Write your functions definitions here. Some have been written for you. //
//                                                                        //
////////////////////////////////////////////////////////////////////////////

void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite) {
	playerSprite.setPosition(player_x, player_y);
	window.draw(playerSprite);
}
void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock) {
	if (bulletClock.getElapsedTime().asMilliseconds() < 20)
		return;

	bulletClock.restart();
	bullet_y -= 10;
	if (bullet_y < -32)
		bullet_exists = false;
		
}
void drawBullet(sf::RenderWindow& window, float& bullet_x, float& bullet_y, Sprite& bulletSprite) {
	bulletSprite.setPosition(bullet_x, bullet_y);
	window.draw(bulletSprite);
}
/////////////START OF MY FUNCTIONS :D//////////////////

//time to make function to move the player
void movePlayer(float& player_x, float player_y, int boundaryLeft, int boundaryRight, float speed, int flowerCord[][2], int flowerActive[], const int MAX_FLOWERS) {
    int oldGridX = static_cast<int>(player_x) / boxPixelsX;
    int oldGridY = static_cast<int>(player_y) / boxPixelsY;
    bool canMoveRight = true;
    bool canMoveLeft = true;

    // Texture size (32x32)
    const int textureSize = 32;
    
    // first we make a check if player is currently overlapping with a flower
    bool playerOverlappingFlower = false;
    for (int i = 0; i < MAX_FLOWERS; i++) {
        if (flowerActive[i]) {
            //this is a flower box
            float flowerLeft = flowerCord[i][0];
            float flowerRight = flowerLeft + textureSize - 1;
            //player box
            float playerLeft = player_x;
            float playerRight = playerLeft + textureSize - 1;
            
            if (playerRight >= flowerLeft && playerLeft <= flowerRight) {
                playerOverlappingFlower = true;
                break;
            }
        }
    }

    // If player is overlapping a flower
    if (playerOverlappingFlower) {
        // we will first try to move right
        float newX = player_x + textureSize;
        canMoveRight = true;
        
        for (int i = 0; i < MAX_FLOWERS; i++) {
            if (flowerActive[i]) {
                float flowerLeft = flowerCord[i][0];
                float flowerRight = flowerLeft + textureSize - 1;
                
                if (newX + textureSize - 1 >= flowerLeft && newX <= flowerRight) {
                    canMoveRight = false;
                    break;
                }
            }
        }
        
        // If can't move right, try left
        if (!canMoveRight) {
            newX = player_x - textureSize;
            canMoveLeft = true;
            
            for (int i = 0; i < MAX_FLOWERS; i++) {
                if (flowerActive[i]) {
                    float flowerLeft = flowerCord[i][0];
                    float flowerRight = flowerLeft + textureSize - 1;
                    
                    if (newX + textureSize - 1 >= flowerLeft && newX <= flowerRight) {
                        canMoveLeft = false;
                        break;
                    }
                }
            }
            if (canMoveLeft) {
                  player_x = newX;}
          }else {
              player_x = newX;
          
          }
    }

    // Check for flower collision when moving left
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        if (player_x > boundaryLeft) {
            float NewX = player_x - speed;
            canMoveLeft = true;

            // Check collisions with each active flower
            for (int i = 0; i < MAX_FLOWERS; i++) {
                if (flowerActive[i]) {
                    // Flower box 
                    float flowerLeft = flowerCord[i][0];
                    float flowerRight = flowerLeft + textureSize - 1;

                    // Player's new horizontal position
                    float playerLeft = NewX;
                    float playerRight = playerLeft + textureSize - 1;

                    // Check if horizontal bounds overlap
                    if (playerRight >= flowerLeft && playerLeft <= flowerRight) {
                        canMoveLeft = false;
                        break;
                    }
                }
            }

            // we move if no collision and within boundary
            if (canMoveLeft) {
                 player_x = NewX;
                
                // Calculate new grid position
                int newGridX = static_cast<int>(player_x) / boxPixelsX;
                int newGridY = static_cast<int>(player_y) / boxPixelsY;
                
                // Clear old grid position
                gameGrid[oldGridY][oldGridX] = 0;
                
                // Mark the new grid position
                gameGrid[newGridY][newGridX] = 1;
            }
        }
    }

    // same stuff as for left but now for right
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        if (player_x < boundaryRight) {
            float NewX = player_x + speed;
            canMoveRight = true;

            // Check collisions with each active flower
            for (int i = 0; i < MAX_FLOWERS; i++) {
                if (flowerActive[i]) {
                    // Flower horizontal bounds
                    float flowerLeft = flowerCord[i][0];
                    float flowerRight = flowerLeft + textureSize - 1;

                    // Player's new horizontal position
                    float playerLeft = NewX;
                    float playerRight = playerLeft + textureSize - 1;

                    // Check if horizontal bounds overlap
                    if (playerRight >= flowerLeft && playerLeft <= flowerRight) {
                        canMoveRight = false;
                        break;
                    }
                }
            }

            // Move if no collision and within boundary
            if (canMoveRight) {
                  player_x = NewX;
                
                // Calculate new grid position
                int newGridX = static_cast<int>(player_x) / boxPixelsX;
                int newGridY = static_cast<int>(player_y) / boxPixelsY;
                
                // Clear old grid position
                gameGrid[oldGridY][oldGridX] = 0;
                
                // Mark new grid position
                gameGrid[newGridY][newGridX] = 1;
            }
        }
    }

    // If no movement, ensure the current grid position remains marked
    if (!Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right)) {
        gameGrid[oldGridY][oldGridX] = 1;
    }
    
//end of function
}




//bullet boom boom
void fireBullet(float& bullet_x, float& bullet_y, bool& bullet_exists, float player_x, float player_y) {
    static bool wasSpacePressed = false; // Tracks if Space was pressed in the previous frame

    bool isSpacePressed = Keyboard::isKeyPressed(Keyboard::Space);

    if (isSpacePressed && !wasSpacePressed && !bullet_exists) { // Fire only on the first press
        bullet_exists = true;
        bullet_x = player_x;
        bullet_y = player_y;
    }

    // this makes it so that continous firing is not allowed by holding space bar
    // the function gets called on every game loop, if the spacebar has been held during two game loops, the bullet wont fire, if the space bar was not pressed in the second game loop then it would fire
    wasSpacePressed = isSpacePressed;
}

// Current game level
int currentLevel = 1;

// A GODDAMN BEE GENERATORRRRRR
void beesGenerator(float beesX[], float beesY[], int beeTypes[], bool beesActive[], int beesTier[], bool beesDirection[], int MAX_BEES, int WORKER_BEE) {
    // we use static variables to maintain state between function calls
    static Clock beeClock;
    static int beeCount = 0;


    // ddetermine bee counts based on level
    int maxBeeCount = 0;
    switch (currentLevel) {
        case 1:
            maxBeeCount = 20;
            break;
        case 2:
            maxBeeCount = 20;
            break;
        case 3:
            maxBeeCount = 30;
            break;
    }
    int delay = (beeCount < 6) ? 1 : 10; // 2 seconds for the first 6, 10 seconds for the rest
    int beeNum = (beeCount < 6)? 1 : 2; // 1 bee for first 6, 2 bees for rest
    // now we generate 2 bees every 2 seconds after initial 6
    if (beeClock.getElapsedTime().asSeconds() >= delay && beeCount < maxBeeCount) {
        int newBeesGenerated = 0;
        int startPoint = 1;
        for (int i = 0; i < MAX_BEES && newBeesGenerated < beeNum; i++) {
            if (!beesActive[i]) {
                if (delay == 2){
                beesActive[i] = true;
                beeTypes[i] = WORKER_BEE;
                        // Alternate between left and right edges
                        if (beeCount % 2 == 0) {
                            // Left edge
                            beesX[i] = 0;
                            beesDirection[i] = true; // Move right
                        } else {
                            // Right edge
                            beesX[i] = resolutionX - boxPixelsX ;
                            beesDirection[i] = false; // Move left
                        }
                beesTier[i] = rand() % 2; // Random starting tier
                (beesTier[i] == 1) ? beesY[i] = boxPixelsY : beesY[i] = boxPixelsY * 2;
                  
                  
                  
                beeCount++;
                newBeesGenerated++;
                printGameGrid();
              }else{
                beesActive[i] = true;
                beeTypes[i] = WORKER_BEE;
                startPoint = rand() % 2;
                (startPoint == 1)? beesX[i] = 0 : beesX[i] = resolutionX - boxPixelsX;
                beesTier[i] = rand() % 2; // Random starting tier
                (beesTier[i] == 1) ? beesY[i] = boxPixelsY : beesY[i] = boxPixelsY * 2;
                beesDirection[i] = (startPoint == 1)? 1: 0; // Random initial direction
                
                
                beeCount++;
                newBeesGenerated++;
                printGameGrid();
            }
          }
        }
cout<<beeCount<<endl;
        // Restart the clock
        beeClock.restart();
    }
    
}

// MOVE BEES MOVEEEEEE
void moveBees(float beesX[], float beesY[], int beesTier[], bool beesDirection[], int beeTypes[], bool beesActive[], int MAX_BEES, float deltaTime, int WORKER_BEE, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS,int flowerCord[][2], int flowerActive[], const int MAX_FLOWERS) {
            
  //static variabless to store state of pauses of bees across calls
  static Clock BeePauseClock;
  static float pauseStartTime[100] = {0}; // Store pause start time for each bee
  static bool paused[100] = {false};
  float PAUSE_DURATION = 4.0f;    
  
    for (int i = 0; i < MAX_BEES; i++) {
        if (beesActive[i]) {
        
            //we set the speed based on bee type
            float speed = (beeTypes[i] == WORKER_BEE) ? 500.0f : 100.0f;

            // Calculate movement using deltaTime
            float movement = speed * deltaTime;
               if (paused[i]) {
                  if (BeePauseClock.getElapsedTime().asSeconds() - pauseStartTime[i] >= PAUSE_DURATION) {
                    paused[i] = false; // Resume movement
                  } else {

                    continue; // Skip movement while paused
                    }
              }

            // Trigger pause with a random number
            int randomNum = rand() % 10000;
            if (randomNum == 5) {
                paused[i] = true; // Mark as paused
                pauseStartTime[i] = BeePauseClock.getElapsedTime().asSeconds();
                continue; // Skip this frame's movement
            }
            // Move horizontally based on direction
            if (beesDirection[i]) {
                beesX[i] += (beeTypes[i] == WORKER_BEE) ? movement: 2;
            } else {
                beesX[i] -= (beeTypes[i] == WORKER_BEE) ? movement: 2;
            }
            
            // Check collision with honeycombs
            bool bounced = false;
            for (int j = 0; j < MAX_HONEYCOMBS; j++) {
                if (honeycombActive[j]) {
                    if (abs(beesX[i] - honeycombX[j]) < boxPixelsX && 
                        abs(beesY[i] - honeycombY[j]) < boxPixelsY) {
                        // Reverse direction
                        beesDirection[i] = !beesDirection[i];
                        
                        // For worker bees, drop to next tier
                        if (beeTypes[i] == WORKER_BEE) {
                            beesY[i] += boxPixelsY;
                            beesTier[i]++;
                        }
                        bounced = true;
                        break;
                    }
                }
            }
        float lastRow = (gameRows - 3) * boxPixelsY;
            // If no honeycomb collision, check screen boundaries
            if (!bounced) {
              if (beesX[i] <= 0 && beesY[i] < lastRow) {
                beesX[i] = 0;  // Stop at the left edge
                beesDirection[i] = !beesDirection[i];  // Reverse direction
                beesY[i] += boxPixelsY;  // Drop to the next tier
                beesTier[i]++;           // Increment tier
            } else if (beesX[i] >= resolutionX - boxPixelsX && beesY[i] <lastRow) {
                beesX[i] = resolutionX - boxPixelsX;  // Stop at the right edge
                beesDirection[i] = !beesDirection[i];  // Reverse direction
                beesY[i] += boxPixelsY;  // Drop to the next tier
                beesTier[i]++;           // Increment tier
            }
            //if it is on last row, dont drop it down just change its direction
            else if (beesY[i]>= lastRow && beesX[i] <= 0 || beesX[i]>= resolutionX - boxPixelsX ){
                  beesDirection[i] = !beesDirection[i];
                  }            
                }
           
            if (beesY[i] >= lastRow){
                if (flowerGenerator(beesX[i],beesY[i],flowerCord,flowerActive,MAX_FLOWERS)){
                    //if flower generated
                    beesActive[i] = false;
                }           
              }
            // Deactivate bee if it reaches bottom
            if (beesY[i] >= resolutionY) {
                beesActive[i] = false;
            }

        }
    }
}

// Function to check collision between bullet and bees
bool checkBeeCollision(float bullet_x, float bullet_y, float beesX[], float beesY[], int beeTypes[], bool beesActive[], int beesTier[], bool beesDirection[], int MAX_BEES, int WORKER_BEE, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS) {
    for (int i = 0; i < MAX_BEES; i++) {
        if (beesActive[i]) {
            // Simple collision detection
            if (abs(bullet_x - beesX[i]) < boxPixelsX && 
                abs(bullet_y - beesY[i]) < boxPixelsY) {
                // Generate honeycomb when bee is hit
                generateHoneycomb(beesX[i], beesY[i], beeTypes[i], 
                                  honeycombX, honeycombY, honeycombType, honeycombActive, MAX_HONEYCOMBS);
                
                // Bee hit
                beesActive[i] = false;
                return true;
            }
        }
    }
    return false;
}

// Function to draw bees
void drawBees(RenderWindow& window, float beesX[], float beesY[], int beeTypes[], bool beesActive[], int beesTier[], bool beesDirection[], int MAX_BEES, int WORKER_BEE) {
    Texture workerBeeTexture, killerBeeTexture;
    workerBeeTexture.loadFromFile("Textures/Regular_bee.png");
    killerBeeTexture.loadFromFile("Textures/Fast_bee.png");

    Sprite beeSprite;
    for (int i = 0; i < MAX_BEES; i++) {
        if (beesActive[i]) {
            // Choose texture based on bee type
            beeSprite.setTexture(beeTypes[i] == WORKER_BEE ? workerBeeTexture : killerBeeTexture);
            beeSprite.setPosition(beesX[i], beesY[i]);
            window.draw(beeSprite);
        }
    }
}

//time for those honey pie i mean honey combs


//generatinggg a honeycomb when a bee is hit
void generateHoneycomb(float bee_x, float bee_y, int beeType, 
                       float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS) {
                       
    static Clock honeytransformClock;
    for (int i = 0; i < MAX_HONEYCOMBS; i++) {
        if (!honeycombActive[i]) {
            honeycombX[i] = bee_x;
            honeycombY[i] = bee_y;
            honeycombType[i] = beeType;
            honeycombActive[i] = true;
            break;
        }
    }
}

//draw the honeycombssss
void drawHoneycombs(RenderWindow& window, 
                    float honeycombX[], float honeycombY[], 
                    int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS) {
    Texture yellowHoneycombTexture, redHoneycombTexture;
    yellowHoneycombTexture.loadFromFile("Textures/honeycomb.png");
    redHoneycombTexture.loadFromFile("Textures/honeycomb_red.png");

    Sprite honeycombSprite;
    for (int i = 0; i < MAX_HONEYCOMBS; i++) {
        if (honeycombActive[i]) {
            // Choose texture based on honeycomb type
            honeycombSprite.setTexture(honeycombType[i] == 0 ? yellowHoneycombTexture : redHoneycombTexture);
            honeycombSprite.setPosition(honeycombX[i], honeycombY[i]);
            window.draw(honeycombSprite);
        }
    }
}

//function to check collision between bullet and honeycomb
bool checkHoneyCombCollision(float bullet_x, float bullet_y, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS){
   for (int i = 0; i < MAX_HONEYCOMBS; i++) {
        if (honeycombActive[i]) {
            // Simple collision detection
            if (abs(bullet_x - honeycombX[i]) < boxPixelsX && 
                abs(bullet_y - honeycombY[i]) < boxPixelsY) {
                
                // remove honeycomb
                honeycombActive[i] = false;
                return true;
            }
        }
    }
    return false;
}



// FLOWERSSSSS


bool flowerGenerator(float beeX, float beeY, int flowerCord[][2], int flowerActive[], const int MAX_FLOWERS) {
    //static variables to remember if there has been a first bee or not
    static bool firstBeeLEFT = false;
    static bool firstBeeRIGHT = false;
    
    // Check if bee is just above ground and aligned with grid
    if (beeY >= (gameRows - 3) * boxPixelsY) {
        if (static_cast<int>(beeX) % boxPixelsX == 0) {
            // first bee from left entersss
            if (beeX == 0 || beeX < boxPixelsX) {
                if (!firstBeeLEFT) //if this IS the first bee {
                    for (int i = 0; i < MAX_FLOWERS; i++) {
                        if (!flowerActive[i]) {
                                flowerActive[i] = true;
                                flowerCord[i][0] = static_cast<int>(beeX);
                                flowerCord[i][1] = static_cast<int>(beeY);
                                int gridX = static_cast<int>(flowerCord[i][0]) / boxPixelsX;
                                int gridY = static_cast<int>(flowerCord[i][1]) / boxPixelsY;
                                gameGrid[gridY][gridX] = 2; // mark the flower on grid
                                      
                                firstBeeLEFT = true;
                                return false;  // dont deactivate bee if it is the first flower
                            }
                        }
                    }
                
            
            // First bee from right
            else if (beeX >= resolutionX - boxPixelsX) {
                if (!firstBeeRIGHT) {
                    for (int i = 0; i < MAX_FLOWERS; i++) {
                        if (!flowerActive[i]) {
                                flowerActive[i] = true;
                                flowerCord[i][0] = static_cast<int>(beeX);
                                flowerCord[i][1] = static_cast<int>(beeY);
                                int gridX = static_cast<int>(flowerCord[i][0]) / boxPixelsX;
                                int gridY = static_cast<int>(flowerCord[i][1]) / boxPixelsY;
                                gameGrid[gridY][gridX] = 2; // mark the flower on grid
                                
                                firstBeeRIGHT = true;
                                return false;  // No need to deactivate bee yet
                            }
                        }
                    }
                }
            
            // Subsequent bees generate one flower
            else if (firstBeeLEFT || firstBeeRIGHT) {
                for (int i = 0; i < MAX_FLOWERS; i++) {
                    if (!flowerActive[i]) {
                        bool positionOccupied = false;
                        // Check if position is already occupied
                        for (int j = 0; j < MAX_FLOWERS; j++) {
                            if (flowerActive[j] && 
                                flowerCord[j][0] == static_cast<int>(beeX) && 
                                flowerCord[j][1] == static_cast<int>(beeY)) {
                                positionOccupied = true;
                                break;
                            }
                        }
                        
                        if (!positionOccupied) {
                            flowerActive[i] = true;
                            flowerCord[i][0] = static_cast<int>(beeX);
                            flowerCord[i][1] = static_cast<int>(beeY);
                            int gridX = static_cast<int>(flowerCord[i][0]) / boxPixelsX;
                            int gridY = static_cast<int>(flowerCord[i][1]) / boxPixelsY;
                            gameGrid[gridY][gridX] = 2; // mark the flower on grid                         
                            return true;  // Deactivate bee
                        }
                    }
                }
            }
        }
    }
    
    return false; // No flower generated, bee continues
}





void drawFlowers(RenderWindow& window, int flowerCord[][2], int flowerActive[], const int MAX_FLOWERS ) {
    Texture flowerTexture;
    flowerTexture.loadFromFile("Textures/flower.png");
    Sprite flowerSprite;
    flowerSprite.setTexture(flowerTexture);

    for (int i = 0; i < MAX_FLOWERS; i++) {
        if (flowerActive[i]) {
            flowerSprite.setPosition(static_cast<float>(flowerCord[i][0]), static_cast<float>(flowerCord[i][1]));
            window.draw(flowerSprite);
        }
    }
}
void printGameGrid() {
    for (int y = 0; y < gameRows; y++) {
        for (int x = 0; x < gameColumns; x++) {
            cout << gameGrid[y][x] << " ";
        }
        cout << endl;
    }
}

