
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;


//TODO:  IMPLEMENT GRID UPDATES FOR ALL FUNCS, IMPLEMENT SCORE BOARD, IMPLEMENT MENU AND LEVELS
//ACHIEVEMENT: TELEPORTING PLAYERRR LETS GOOOOOOOOO


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
void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite, int spraycanState);
void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock);
void drawBullet(RenderWindow& window, float& bullet_x, float& bullet_y, Sprite& bulletSprite);
void movePlayer(float& player_x, float player_y, int boundaryLeft,  int boundaryRight,  float speed, int flowerCord[][2], int flowerActive[], const int MAX_FLOWERS);
void fireBullet(float& bullet_x, float& bullet_y, bool& bullet_exists, float player_x, float player_y, int& sprays, int& spraycanState, int& spraycanLives);
void beesGenerator(float beesX[], float beesY[], int beeTypes[], bool beesActive[], int beesTier[], bool beesDirection[], int MAX_BEES, int WORKER_BEE);


void moveBees(float beesX[], float beesY[], int beesTier[], bool beesDirection[], int beeTypes[], bool beesActive[], int MAX_BEES, float deltaTime, int WORKER_BEE, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS,int flowerCord[][2], int flowerActive[], const int MAX_FLOWERS,float beehiveCord[][2], bool beehiveActive[], int MAX_BEEHIVES);


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
void generateHummingbird(float& hummingbirdX, float& hummingbirdY, bool& hummingbirdActive, float honeycombX[], float honeycombY[], bool honeycombActive[], int MAX_HONEYCOMBS, bool& isBirdSick, Clock& sickClock, bool& isFlyingToEdge);
void drawHummingbird(RenderWindow& window, float hummingbirdX, float hummingbirdY, bool isBirdSick, bool hummingbirdActive);
bool checkBirdCollision(float& hummingbirdX, float& hummingbirdY, 
                        float bulletX, float bulletY,
                        bool& hummingbirdActive, bool& isBirdSick, 
                        int& collidedBulletCount, Clock& sickClock, bool& isFlyingToEdge);
void generateBeeHive(float beeX, float beeY, int MAX_BEES, float beehiveCord[][2], bool beehiveActive[], int MAX_BEEHIVES);
void drawBeeHive(RenderWindow& window, float beehiveCord[][2], bool beehiveActive[], int MAX_BEEHIVES );
bool checkBeeHiveCollision(float bullet_x, float bullet_y, float beehiveCord[][2], bool beehiveActive[], int MAX_BEEHIVES);


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
                
        
        // Hummingbird Variables
        float hummingbirdX = -100; // Start off-screen
        float hummingbirdY = -100; // Start off-screen
        bool hummingbirdActive = false;
        bool isBirdSick = false;
        Clock sickClock;
        int collidedBulletCount = 0;
        bool isFlyingToEdge;   
        
        
        //BEE HIVE 
        int MAX_BEEHIVES = 100;
       float beehiveCord[MAX_BEEHIVES][2] = {0};
       bool beehiveActive[MAX_BEEHIVES] = {0};

        
      //spray can
      int sprays = 0;
      int spraycanLives = 2;
      int spraycanState = 0;
  
        honeycombX[1] = 128;
        honeycombY[1] = 64;
        honeycombActive[1] = 0;
        honeycombType[1] = 0;
        honeycombX[2] = 0;
        honeycombY[2] = 96;
        honeycombType[2] = 0;
        honeycombActive[2] = 1;
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
                movePlayer(player_x, player_y, 0, resolutionX - boxPixelsX, 0.32, flowerCord,flowerActive,MAX_FLOWERS);
                moveBees(beesX,beesY, beesTier,  beesDirection, beeTypes,  beesActive,  MAX_BEES,  deltaTime,  WORKER_BEE, honeycombX, honeycombY,honeycombType,honeycombActive,MAX_HONEYCOMBS, flowerCord, flowerActive, MAX_FLOWERS, beehiveCord, beehiveActive, MAX_BEEHIVES);
                fireBullet(bullet_x, bullet_y, bullet_exists, player_x, player_y, sprays, spraycanState, spraycanLives);
                generateHummingbird(hummingbirdX, hummingbirdY, hummingbirdActive, honeycombX, honeycombY, honeycombActive, MAX_HONEYCOMBS, isBirdSick, sickClock, isFlyingToEdge);
		if (bullet_exists == true)
		{       
			moveBullet(bullet_y, bullet_exists, bulletClock);
			drawBullet(window, bullet_x, bullet_y, bulletSprite);
			//simple functionality to check if bullet has hit bee
			//simple functionality to check if bullet hit honeycomb
			//blah blah hummingbird check
			if (checkBeeCollision( bullet_x, bullet_y, beesX, beesY ,beeTypes, beesActive, beesTier, beesDirection, MAX_BEES, WORKER_BEE, honeycombX, honeycombY, honeycombType, honeycombActive,  MAX_HONEYCOMBS)) 
			{
                          bullet_exists = false;			
			}else if (checkHoneyCombCollision( bullet_x, bullet_y,honeycombX, honeycombY,honeycombType, honeycombActive,  MAX_HONEYCOMBS)){
			bullet_exists = false;
			}else if(checkBeeHiveCollision(bullet_x, bullet_y, beehiveCord, beehiveActive,MAX_BEEHIVES)){
			bullet_exists = false;
			}
			else if(checkBirdCollision(hummingbirdX,hummingbirdY, bullet_x, bullet_y,
                        hummingbirdActive, isBirdSick, 
                        collidedBulletCount,  sickClock, isFlyingToEdge)){
			
			bullet_exists = false;
			}
			
			
		}
		else
		{
			bullet_x = player_x;
			bullet_y = player_y+64;
		}
                
		drawPlayer(window, player_x, player_y, playerSprite, spraycanState);
                drawBees(window, beesX, beesY ,beeTypes, beesActive, beesTier, beesDirection, MAX_BEES, WORKER_BEE);
		window.draw(groundRectangle);
		drawHoneycombs(window, honeycombX, honeycombY, honeycombType, honeycombActive, MAX_HONEYCOMBS);
		drawFlowers(window, flowerCord,flowerActive,MAX_FLOWERS);
		drawBeeHive( window, beehiveCord, beehiveActive, MAX_BEEHIVES);
		drawHummingbird(window, hummingbirdX, hummingbirdY, isBirdSick, hummingbirdActive);
		window.display();
		window.clear();
	}
}

////////////////////////////////////////////////////////////////////////////
//                                                                        //
// Write your functions definitions here. Some have been written for you. //
//                                                                        //
////////////////////////////////////////////////////////////////////////////

void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite, int spraycanState) {
    playerSprite.setPosition(player_x, player_y);
    window.draw(playerSprite);
    const int decreaseConstant = 4;
    // Create white rectangle for spray can state
    RectangleShape stateRect(Vector2f(boxPixelsX -10, boxPixelsY-decreaseConstant*spraycanState));
    stateRect.setFillColor(Color::White);
    stateRect.setPosition(player_x +10, player_y + boxPixelsY + decreaseConstant*spraycanState);
    window.draw(stateRect);
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
    bool forcedMove = false;
    // Texture size (32x32)
    const int textureSize = 32;
    
    //THIS IS FOR OVERLAPPING FLOWER and PLAYER
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

    if (playerOverlappingFlower) {
        // we will first try to move right
        forcedMove = true;
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
        }
        
        // Update grid position if movement is possible
        if (canMoveRight || canMoveLeft) {
            // Clear the old grid position
            gameGrid[oldGridY][oldGridX] = 0;
            
            // Update player position
            player_x = newX;
            
            // Calculate and mark new grid position
            int newGridX = static_cast<int>(player_x) / boxPixelsX;
            int newGridY = static_cast<int>(player_y) / boxPixelsY;
            gameGrid[newGridY][newGridX] = 1;
        }
    }
    
/////////////////////////////////////////////////////////

    // check for flower collision when moving left
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
                
            }
        }
    }

                int newGridX = static_cast<int>(player_x) / boxPixelsX;
                int newGridY = static_cast<int>(player_y) / boxPixelsY;
                
                // Clear old grid position
                gameGrid[oldGridY][oldGridX] = 0;
                
                // Mark the new grid position
                gameGrid[newGridY][newGridX] = 1;
                
                
                //same shit for left but now for right
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
          bool flowerOnImmediateRight = false;
          bool flowerOnImmediateLeft = false;

        for (int i = 0; i < MAX_FLOWERS; i++) {
            if (flowerActive[i]) {
           
           float flowerLeft = flowerCord[i][0]; 
                //same logic as the overlapping just we need to look through the whole array
                float flowerRight = flowerLeft + textureSize - 1;
                //basically we need to look at the immediate left and right of the player
                // immediate Right Check
                if (player_x + textureSize >= flowerLeft - 5 && 
                    player_x + textureSize <= flowerLeft + textureSize + 5) {

                    flowerOnImmediateRight = true;
                }
                
                // immediate Left Check
                if (player_x <= flowerRight +5 && player_x >= flowerLeft - 5) {

                    flowerOnImmediateLeft = true;
                }
            }
        }
        
        if ( (flowerOnImmediateLeft && flowerOnImmediateRight) || (flowerOnImmediateLeft && player_x <= boundaryLeft) || 
    (flowerOnImmediateRight && player_x >= boundaryRight)){
            cout<<"player is stuck\n";
            float playerLeft = player_x;
            float playerRight = playerLeft + textureSize - 1;
            for(int i =0; i < gameColumns; i++){
                if(gameGrid[gameRows -3][i] == 0 && gameGrid[gameRows - 4][i] != 1){
                    printGameGrid();
                    int teleportAT = i * boxPixelsX;
                     if (abs(player_x - teleportAT) <= 10) {
                        cout << "Game End";
                    }
                    else {
                        cout<<"teleported";
                    }
                    player_x = teleportAT;
                    break;
                } 
            }
          
          }
        
        
        
    

    // If no movement, ensure the current grid position remains marked
    if (!Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right)) {
        gameGrid[oldGridY][oldGridX] = 1;
    }
    if (forcedMove){
        gameGrid[oldGridY][oldGridX] = 0;
    }
    
    
    

//end of function
}




//bullet boom boom
void fireBullet(float& bullet_x, float& bullet_y, bool& bullet_exists, float player_x, float player_y, int& sprays, int& spraycanState, int& spraycanLives) {
    static bool wasSpacePressed = false; // Tracks if Space was pressed in the previous frame
    static int totalSprays = 0;
    bool isSpacePressed = Keyboard::isKeyPressed(Keyboard::Space);

    if (isSpacePressed && !wasSpacePressed && !bullet_exists) { // Fire only on the first press
        bullet_exists = true;
        bullet_x = player_x;
        bullet_y = player_y;
        sprays++;
    }
    cout<<sprays<<endl;
    if(sprays ==8){
      spraycanState += 1;
      totalSprays += sprays;
      sprays = 0;
    }
    cout<<totalSprays<<endl;
    if(totalSprays == 56){
      spraycanLives -=1;
      totalSprays = 0;
      spraycanState =0;
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
            maxBeeCount = 22;
            break;
        case 2:
            maxBeeCount = 20;
            break;
        case 3:
            maxBeeCount = 30;
            break;
    }
    int delay = (beeCount < 10) ? 1 : 2; // 2 seconds for the first 6, 10 seconds for the rest
    int beeNum = (beeCount < 10)? 1 : 2; // 1 bee for first 6, 2 bees for rest
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
cout<<beeCount<<endl;
        // Restart the clock
        beeClock.restart();
    }
    
}

// MOVE BEES MOVEEEEEE
void moveBees(float beesX[], float beesY[], int beesTier[], bool beesDirection[], int beeTypes[], bool beesActive[], int MAX_BEES, float deltaTime, int WORKER_BEE, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS,int flowerCord[][2], int flowerActive[], const int MAX_FLOWERS, float beehiveCord[][2], bool beehiveActive[], int MAX_BEEHIVES) {
            
  //static variabless to store state of pauses of bees across calls
  static Clock BeePauseClock;
  static float pauseStartTime[100] = {0}; // Store pause start time for each bee
  static bool paused[100] = {false};
  float PAUSE_DURATION = 4.0f;    
  
    for (int i = 0; i < MAX_BEES; i++) {
        if (beesActive[i]) {
        
            //we set the speed based on bee type
            float speed = (beeTypes[i] == WORKER_BEE) ? 800.0f : 100.0f;

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
                        // Reverse direction and also reset its X to before honeycomb
                        beesX[i] = (beesDirection[i]) ? 
                        honeycombX[j] - boxPixelsX : 
                        honeycombX[j] + boxPixelsX;
                        beesDirection[i] = !beesDirection[i];
                        
                        // For worker bees, drop to next tier
                        if (beeTypes[i] == WORKER_BEE) {
                            float newBeeY = beesY[i] + boxPixelsY;
                            bool honeycombBelow = false; // use a bool to track honey comb below
                            
                          for (int k = 0; k < MAX_HONEYCOMBS; k++) {
                            //same collision logic as above
                                if (honeycombActive[k] && 
                                    abs(beesX[i] - honeycombX[k]) < boxPixelsX && 
                                    abs(newBeeY - honeycombY[k]) < boxPixelsY) {
                                    honeycombBelow = true;
                                    generateBeeHive(beesX[i],  beesY[i], MAX_BEES,  beehiveCord,beehiveActive, MAX_BEEHIVES);
                                    beesActive[i] = false;
                                    cout<<"x";
                                    break;
                                }
                            }
                            // If no honeycomb below, move bee down
                            if (!honeycombBelow) {
                                beesY[i] = newBeeY;
                                beesTier[i]++;
                            }
                        }
                        
                        bounced = true;
                        break;
                    }
                }
            }
            
//collision with bee hive
for (int j = 0; j < MAX_BEEHIVES; j++) {
    if (beehiveActive[j]) {
        if (abs(beesX[i] - beehiveCord[j][0]) < boxPixelsX && 
            abs(beesY[i] - beehiveCord[j][1]) < boxPixelsY) {
            beesX[i] = (beesDirection[i]) ? 
            beehiveCord[j][0] - boxPixelsX : 
            beehiveCord[j][0] + boxPixelsX;
            beesDirection[i] = !beesDirection[i];
            // For worker bees, drop to next tier
            if (beeTypes[i] == WORKER_BEE) {
                float newBeeY = beesY[i] + boxPixelsY;
                bool beehiveBelow = false;
                beesY[i] = newBeeY;
                beesTier[i]++;
                
              }
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
                
                float newBeeY = beesY[i] + boxPixelsY;
                bool honeycombBelow = false; // use a bool to track honey comb below            
                for (int k = 0; k < MAX_HONEYCOMBS; k++) {
                //same collision logic as above
                if (honeycombActive[k] && 
                abs(beesX[i] - honeycombX[k]) < boxPixelsX && 
                abs(newBeeY - honeycombY[k]) < boxPixelsY) {
                    honeycombBelow = true;
                    generateBeeHive(beesX[i],  beesY[i], MAX_BEES,  beehiveCord,beehiveActive, MAX_BEEHIVES);
                    beesActive[i] = false;
                    cout<<"x";
                    break;
                }
            }
                            
                // If no honeycomb below, move bee down
                if (!honeycombBelow) {
                    beesY[i] = newBeeY;
                    beesTier[i]++;
                  }
              }
             else if (beesX[i] >= resolutionX - boxPixelsX && beesY[i] <lastRow) {
                beesX[i] = resolutionX - boxPixelsX;  // Stop at the right edge
                beesDirection[i] = !beesDirection[i];  // Reverse direction
                float newBeeY = beesY[i] + boxPixelsY;
                bool honeycombBelow = false; // use a bool to track honey comb below            
                for (int k = 0; k < MAX_HONEYCOMBS; k++) {
                //same collision logic as above
                if (honeycombActive[k] && 
                abs(beesX[i] - honeycombX[k]) < boxPixelsX && 
                abs(newBeeY - honeycombY[k]) < boxPixelsY) {
                    honeycombBelow = true;
                    generateBeeHive(beesX[i],  beesY[i], MAX_BEES,  beehiveCord,beehiveActive, MAX_BEEHIVES);
                    beesActive[i] = false;
                    cout<<"x";
                    break;
                }
            }
                            
                // If no honeycomb below, move bee down
                if (!honeycombBelow) {
                    beesY[i] = newBeeY;
                    beesTier[i]++;
                  }
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

//HUMMINGBIRD LETS GOOOOOOOOOOOO

const float TARGET_REACHED_THRESHOLD = 1.0f;
void generateHummingbird(float& hummingbirdX, float& hummingbirdY, bool& hummingbirdActive, 
                         float honeycombX[], float honeycombY[], bool honeycombActive[], 
                         int MAX_HONEYCOMBS, bool& isBirdSick, Clock& sickClock, bool& isFlyingToEdge) {

    static Clock pauseClock;
    static Clock hummingbirdClock;
    static int hummingbirdMovementCount = 0; // Keep track of movement count
    static float targetX = 0; // Target X position
    static float targetY = 0; // Target Y position
    static bool newTargetNeeded = true; // Flag to indicate if a new target is needed
    static bool isPaused = false;

   if (isFlyingToEdge) {
        static bool targetCalculated = false;
        if (!targetCalculated) {
            float leftDistance = hummingbirdX;
            float rightDistance = resolutionX - (hummingbirdX + boxPixelsX);

            float minDistance = min({leftDistance, rightDistance});
            if (minDistance == leftDistance) {
                targetX = 0;
                targetY = hummingbirdY;
            } else if (minDistance == rightDistance) {
                targetX = resolutionX - boxPixelsX;
                targetY = hummingbirdY;
            }
            targetCalculated = true; // Prevent recalculation
        }

        // Move towards the calculated edge
        float speed = 10.0f; // Speed of the hummingbird
        float deltaTime = 0.016f; // Assuming 60 FPS
        if (hummingbirdX < targetX) {
            hummingbirdX += speed * deltaTime;
            if (hummingbirdX > targetX) hummingbirdX = targetX;
        } else {
            hummingbirdX -= speed * deltaTime;
            if (hummingbirdX < targetX) hummingbirdX = targetX;
        }

        if (hummingbirdY < targetY) {
            hummingbirdY += speed * deltaTime;
            if (hummingbirdY > targetY) hummingbirdY = targetY;
        } else {
            hummingbirdY -= speed * deltaTime;
            if (hummingbirdY < targetY) hummingbirdY = targetY;
        }

        // If the bird has reached the edge, reset its state
        if (abs(hummingbirdX - targetX) < 1.0f && abs(hummingbirdY - targetY) < 1.0f) {
            isFlyingToEdge = false;  // Reset flying state
            targetCalculated = false; // Reset for the next flight
            hummingbirdActive = false; // Despawn the bird
        }
    }


    // Check if the hummingbird should be generated
    if (!hummingbirdActive && !isBirdSick && hummingbirdClock.getElapsedTime().asSeconds() >= 4) {
        // Generate at a random edge
        int edge = rand() % 4; // 0 = left, 1 = right, 2 = top, 3 = bottom
        switch (edge) {
            case 0: // Left edge
                hummingbirdX = 0;
                hummingbirdY = rand() % resolutionY;
                break;
            case 1: // Right edge
                hummingbirdX = resolutionX - boxPixelsX;
                hummingbirdY = rand() % resolutionY;
                break;
            case 2: // Top edge
                hummingbirdX = rand() % resolutionX;
                hummingbirdY = 0;
                break;
            case 3: // Bottom edge
                hummingbirdX = rand() % resolutionX;
                hummingbirdY = resolutionY - boxPixelsY;
                break;
        }

        hummingbirdActive = true;
        hummingbirdMovementCount = 0; // Reset movement count
        newTargetNeeded = true; // Set flag to generate a new target
    }
        // Check if bird has been sick for 5 seconds
    if (isBirdSick && sickClock.getElapsedTime().asSeconds() >= 5) {
        isBirdSick = false; // Heal the bird
    }


    // If the hummingbird is active, move it

    if (hummingbirdActive) {
        if (newTargetNeeded) {
            // Generate a new random target position
            targetX = rand() % (resolutionX - boxPixelsX);
            targetY = rand() % resolutionY;
            if (targetY >= (gameRows - 3) * boxPixelsY){
              targetY = rand()%resolutionY;
            }else{ 
            newTargetNeeded = false; // Reset the flag
        }}


        // Move towards the target position
        float speed = 10.0f; // Speed of the hummingbird
        float deltaTime = 0.016f; // Assuming 60 FPS
        // Move towards the target
        if (hummingbirdX < targetX) {
            hummingbirdX += speed * deltaTime;
            if (hummingbirdX > targetX) hummingbirdX = targetX; // Snap to target
        } 
        else {
            hummingbirdX -= speed * deltaTime;
            if (hummingbirdX < targetX) hummingbirdX = targetX; // Snap to target
        }

        if (hummingbirdY < targetY) {
            hummingbirdY += speed * deltaTime;
            if (hummingbirdY > targetY) hummingbirdY = targetY; // Snap to target
        } else 
        {
            hummingbirdY -= speed * deltaTime;
            if (hummingbirdY < targetY) hummingbirdY = targetY; // Snap to target
        }


        // Check if reached the target using simple arithmetic
        if (abs(hummingbirdX - targetX) < TARGET_REACHED_THRESHOLD && 
            abs(hummingbirdY - targetY) < TARGET_REACHED_THRESHOLD) {
            if (!isPaused) {
            // Start the pause
            isPaused = true;
            pauseClock.restart(); // Reset the pause clock
    } else {

        // Check if the pause duration has elapsed
        if (pauseClock.getElapsedTime().asSeconds() >= 2) {
            hummingbirdMovementCount++;
            newTargetNeeded = true; // Set flag to generate a new target
            isPaused = false; // Reset the pause flag
            for (int i = 0; i < MAX_HONEYCOMBS; i++){
                    if(honeycombActive[i]){
                        if(honeycombX[i] == targetX && honeycombY[i] == targetY){
                            honeycombActive[i] = false;
                          }
                    
                    }  
                    
                }
          }
        }
    }

        // If the hummingbird has moved to the third target, find the nearest honeycomb
        if (hummingbirdMovementCount >= 3) {

            // Find the nearest honeycomb

            float nearestDistance = 10000000000;
            int nearestHoneycombIndex = -1;

            for (int i = 0; i < MAX_HONEYCOMBS; i++) {
                if (honeycombActive[i]) {
                float distance = (honeycombX[i] - hummingbirdX) * (honeycombX[i] - hummingbirdX) + (honeycombY[i] - hummingbirdY) * (honeycombY[i] - hummingbirdY); //using pythogras formula to calculate displacement
                distance = distance * 0.5;
                    if (distance < nearestDistance) {
                        nearestDistance = distance; //if the displacement is lesser than the nearest distance
                        nearestHoneycombIndex = i; //then that is the new nearest distance
                    }

                }

            }

            if (nearestHoneycombIndex != -1) {
                targetX = honeycombX[nearestHoneycombIndex];
                targetY = honeycombY[nearestHoneycombIndex];
                newTargetNeeded = false; // Reset the flag to avoid generating a new target
                hummingbirdMovementCount = 0;

            }

        }

    }

}
bool checkBirdCollision(float& hummingbirdX, float& hummingbirdY, 
                        float bulletX, float bulletY,
                        bool& hummingbirdActive, bool& isBirdSick, 
                        int& collidedBulletCount,  
                        Clock& sickClock, bool& isFlyingToEdge) {
    bool collided = (bulletX >= hummingbirdX - 20 &&
                     bulletX <= hummingbirdX + 20 &&
                     bulletY >= hummingbirdY &&
                     bulletY <= hummingbirdY + 20);

    if (collided) {
        collidedBulletCount++;
        if (collidedBulletCount >= 3) {
            isBirdSick = true;
            sickClock.restart();
            isFlyingToEdge = true;
            collidedBulletCount = 0;
        }
        return true; // Collision detected
    }
    return false; // No collision
}




//Humming BIRD DRAW
void drawHummingbird(RenderWindow& window, float hummingbirdX, float hummingbirdY, bool isBirdSick, bool hummingbirdActive) {
    static Texture normalTexture;
    static Texture sickTexture;
    static bool isNormalTextureLoaded = false;
    static bool isSickTextureLoaded = false;
    static int currentFrame = 0;

    if (hummingbirdActive) {
        // Load normal texture
        if (!isNormalTextureLoaded) {
            if (!normalTexture.loadFromFile("Textures/bird.png")) {
                return;
            }
            isNormalTextureLoaded = true;
        }

        // Load sick texture
        if (!isSickTextureLoaded) {
            if (!sickTexture.loadFromFile("Textures/birdsick.png")) {
                return;
            }
            isSickTextureLoaded = true;
        }
        
        Sprite hummingbirdSprite;
        if (isBirdSick) {
            hummingbirdSprite.setTexture(sickTexture);
        } else {
            hummingbirdSprite.setTexture(normalTexture);
        }
        
        IntRect frames[] = {
            IntRect(0, 0, 32, 32),  // Frame 1
            IntRect(32, 0, 32, 32)  // Frame 2
        };
        currentFrame = (currentFrame + 1) % 2;
        hummingbirdSprite.setTextureRect(frames[currentFrame]);

        // Set position and draw
        hummingbirdSprite.setPosition(hummingbirdX, hummingbirdY);
        window.draw(hummingbirdSprite);
    }
}



//BOYS BEE HIVE TIME
void generateBeeHive(float beeX, float beeY, int MAX_BEES, float beehiveCord[][2], bool beehiveActive[], int MAX_BEEHIVES){
cout<<"y";
    for (int i = 0; i < MAX_BEEHIVES ; i++) {
        if (!beehiveActive[i]) {
            beehiveCord[i][0] = beeX;
            beehiveCord[i][1] = beeY;
            beehiveActive[i] = true;
            break;
        }
    }
}

bool checkBeeHiveCollision(float bullet_x, float bullet_y, float beehiveCord[][2], bool beehiveActive[], int MAX_BEEHIVES) {
   for (int i = 0; i < MAX_BEEHIVES; i++) {
        if (beehiveActive[i]) {
            // Simple collision detection
            if (abs(bullet_x - beehiveCord[i][0]) < boxPixelsX && 
                abs(bullet_y - beehiveCord[i][1]) < boxPixelsY) {
                // remove beehive
                beehiveActive[i] = false;
                return true;
            }
        }
    }
    return false;   
}



void drawBeeHive(RenderWindow& window, float beehiveCord[][2], bool beehiveActive[], int MAX_BEEHIVES ) {
    Texture beehiveTexture;
    beehiveTexture.loadFromFile("Textures/hive1.png");
    Sprite beehiveSprite;
    beehiveSprite.setTexture(beehiveTexture);

    for (int i = 0; i < MAX_BEEHIVES; i++) {
        if (beehiveActive[i]) {
            beehiveSprite.setPosition(static_cast<float>(beehiveCord[i][0]), static_cast<float>(beehiveCord[i][1]));
            window.draw(beehiveSprite);
        }
    }
}
