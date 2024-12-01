
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

// Initializing Dimensions.
// resolutionX and resolutionY determine the rendering resolution.

const int resolutionX = 795; //the original buzz bombers has dimensions  159 x 98, these dimensions are scaled 5x for our game
const int resolutionY = 480;
const int boxPixelsX = 32;
const int boxPixelsY = 32;
const int gameRows = resolutionX / boxPixelsX; // Total rows on grid
const int gameColumns = resolutionY / boxPixelsY; // Total columns on grid

// Initializing GameGrid.
int gameGrid[gameRows][gameColumns] = {};


void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite);
void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock);
void drawBullet(RenderWindow& window, float& bullet_x, float& bullet_y, Sprite& bulletSprite);
void movePlayer(float& player_x,  int boundaryLeft,  int boundaryRight,  float speed);
void fireBullet(float& bullet_x, float& bullet_y, bool& bullet_exists, float player_x, float player_y);
void beesGenerator(float beesX[], float beesY[], int beeTypes[], bool beesActive[], int beesTier[], bool beesDirection[], int MAX_BEES, int WORKER_BEE);
void moveBees(float beesX[], float beesY[], int beesTier[], bool beesDirection[], int beeTypes[], bool beesActive[], int MAX_BEES, float deltaTime, int WORKER_BEE, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS);
void drawBees(RenderWindow& window);
bool checkBeeCollision(float bullet_x, float bullet_y, float beesX[], float beesY[], int beeTypes[], bool beesActive[], int beesTier[], bool beesDirection[], int MAX_BEES, int WORKER_BEE, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS);
void drawBees(RenderWindow& window, float beesX[], float beesY[], int beeTypes[], bool beesActive[], int beesTier[], bool beesDirection[], int MAX_BEES, int WORKER_BEE);
void drawHoneycombs(RenderWindow& window, 
                    float honeycombX[], float honeycombY[], 
                    int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS);
                    
void generateHoneycomb(float bee_x, float bee_y, int beeType, 
                       float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS);
/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// Write your functions declarations here. Some have been written for you. //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////


int main()
{
      cout<<gameRows<<endl;
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
	float player_x = (gameRows / 2) * boxPixelsX;
	float player_y = (gameColumns - 4) * boxPixelsY;

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
	bulletSprite.setScale(3, 3);
	bulletSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

	// The ground on which player moves

	RectangleShape groundRectangle(Vector2f(960, 64));
	groundRectangle.setPosition(0, (gameColumns - 2) * boxPixelsY);
	groundRectangle.setFillColor(Color::Green);
        
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
        bool honeycombActive[MAX_HONEYCOMBS];
        // Initialize arrays
        for (int i = 0; i < MAX_HONEYCOMBS; i++) {
            honeycombActive[i] = false;
        }
            
	while (window.isOpen()) {
        float deltaTime = movementClock.restart().asSeconds(); //gets the time between each frame reload (every run of the game loop)
        
        
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
                movePlayer(player_x, 0, resolutionX - boxPixelsX, 0.2);
                moveBees(beesX,beesY, beesTier,  beesDirection, beeTypes,  beesActive,  MAX_BEES,  deltaTime,  WORKER_BEE, honeycombX, honeycombY,honeycombType,honeycombActive,MAX_HONEYCOMBS);
                fireBullet(bullet_x, bullet_y, bullet_exists, player_x, player_y);
    
		if (bullet_exists == true)
		{       
			moveBullet(bullet_y, bullet_exists, bulletClock);
			drawBullet(window, bullet_x, bullet_y, bulletSprite);
			//simple functionality to check if bullet has hit bee
			//TODO: Add honey comb generation
			if (checkBeeCollision( bullet_x, bullet_y, beesX, beesY ,beeTypes, beesActive, beesTier, beesDirection, MAX_BEES, WORKER_BEE, honeycombX, honeycombY, honeycombType, honeycombActive,  MAX_HONEYCOMBS)) 
			{
                          bullet_exists = false;			
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
void movePlayer(float& player_x,  int boundaryLeft,  int boundaryRight,  float speed) {
    if (Keyboard::isKeyPressed(Keyboard::Left)) { //detects if left key is pressed
        if (player_x > boundaryLeft) {//also boundary check to avoid going off screen
            player_x -= speed; 
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {//detects if right key is pressed
        if (player_x < boundaryRight) { //similar boundary check
            player_x += speed; 
        }
      }
  }
  
  
//function to fire bullet boom boom
void fireBullet(float& bullet_x, float& bullet_y, bool& bullet_exists, float player_x, float player_y){
    if (Keyboard::isKeyPressed(Keyboard::Space) && !bullet_exists) { //detects space bar and if bullet doesnt alrdy exist
        bullet_exists = true;
        bullet_x = player_x; 
        bullet_y = player_y;
        
    }
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
            }
          }
        }

        // Restart the clock
        beeClock.restart();
    }
  
}

// MOVE BEES MOVEEEEEE
void moveBees(float beesX[], float beesY[], int beesTier[], bool beesDirection[], int beeTypes[], bool beesActive[], int MAX_BEES, float deltaTime, int WORKER_BEE, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS) {
  //static variabless to store state of pauses of bees across calls
  static Clock BeePauseClock;
  static float pauseStartTime[100] = {0}; // Store pause start time for each bee
  static bool paused[100] = {false};
  float PAUSE_DURATION = 4.0f;    
  
    for (int i = 0; i < MAX_BEES; i++) {
        if (beesActive[i]) {
            //we set the speed based on bee type
            float speed = (beeTypes[i] == WORKER_BEE) ? 200.0f : 100.0f;

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

            // If no honeycomb collision, check screen boundaries
            if (!bounced) {
              if (beesX[i] <= 0) {
                beesX[i] = 0;  // Stop at the left edge
                beesDirection[i] = !beesDirection[i];  // Reverse direction
                beesY[i] += boxPixelsY;  // Drop to the next tier
                beesTier[i]++;           // Increment tier
            } else if (beesX[i] >= resolutionX - boxPixelsX) {
                beesX[i] = resolutionX - boxPixelsX;  // Stop at the right edge
                beesDirection[i] = !beesDirection[i];  // Reverse direction
                beesY[i] += boxPixelsY;  // Drop to the next tier
                beesTier[i]++;           // Increment tier
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


// Function to generate a honeycomb when a bee is hit
void generateHoneycomb(float bee_x, float bee_y, int beeType, 
                       float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS) {
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
