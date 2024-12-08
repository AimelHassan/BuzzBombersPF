
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <fstream>

using namespace std;
using namespace sf;


//TODO:   IMPLEMENT:
//        leaderboard
//        make level switch screen
//        FIX TELEPORT ISSUE
//        PERFECT THE SCORING SYSTEM NIGGA
//        infant bee
//BUGS : BEES DISAPPEAR SOMETIMES WHEN HIT A BEEHIVE AND BELOW IS A HONEY COMB, FIX TELEPORTING LOGIC NIGGA THIS SHIT IS SO HARD
//TODO: GO THROUGH THE CODE AND REFINE IT,  CODE REFACTORING, REMOVING AI COMMENTS, BREAKING DOWN LOGIC INTO SMALLER FUNCTIONS
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
void drawPlayer(RenderWindow& window, float& player_x, float& player_y, int spraycanState, float sizemultiplier);
void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock);
void drawBullet(RenderWindow& window, float& bullet_x, float& bullet_y, Sprite& bulletSprite);
void movePlayer(float& player_x, float player_y, int boundaryLeft,  int boundaryRight,  float speed, int flowerCord[][2], int flowerActive[], const int MAX_FLOWERS, bool& resetCall, int& spraycanLives, bool& inMenu);
void fireBullet(float& bullet_x, float& bullet_y, bool& bullet_exists, float player_x, float player_y, int& sprays, int& spraycanState, int& spraycanLives, bool& inGameEnd, bool& resetCall);
void beesGenerator(float beesX[], float beesY[], int beeTypes[], bool beesActive[], int beesTier[], bool beesDirection[], int MAX_BEES, int WORKER_BEE, int currentgameLevel, int& beeCount, bool resetCall, int& regularbeeCount, Clock& hunterBeeClock, int& hunterbeeCount, Clock& beeClock);


void moveBees(float beesX[], float beesY[], int beesTier[], bool beesDirection[], int beeTypes[], bool beesActive[], int MAX_BEES, float deltaTime, int WORKER_BEE, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS,int flowerCord[][2], int flowerActive[], const int MAX_FLOWERS,float beehiveCord[][2], bool beehiveActive[], int MAX_BEEHIVES,bool& firstbeeLEFT, bool& firstbeeRIGHT);


void drawBees(RenderWindow& window);
bool checkBeeCollision(float bullet_x, float bullet_y, float beesX[], float beesY[], int beeTypes[], bool beesActive[], int beesTier[], bool beesDirection[], int MAX_BEES, int WORKER_BEE, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS, int& playerScore, int honeycombTier[]);
void drawBees(RenderWindow& window, float beesX[], float beesY[], int beeTypes[], bool beesActive[], int beesTier[], bool beesDirection[], int MAX_BEES, int WORKER_BEE);
void drawHoneycombs(RenderWindow& window, 
                    float honeycombX[], float honeycombY[], 
                    int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS);             
void generateHoneycomb(float bee_x, float bee_y, int beeType, 
                       float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS, int beeTier, int honeycombTier[]);
bool checkHoneyCombCollision(float bullet_x, float bullet_y, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS,float powerupCords[][2], bool powerupActive[], int powerupType[], float powerupTimer[], int MaxPowerups);
void drawFlowers(RenderWindow& window, int flowerCord[][2], int flowerActive[], const int MAX_FLOWERS );
bool flowerGenerator(float beeX, float beeY, int flowerCord[][2], int flowerActive[], const int MAX_FLOWERS, bool& firstbeeLEFT, bool& firstbeeRIGHT);
void generateHummingbird(float deltatime,float& hummingbirdX, float& hummingbirdY, bool& hummingbirdActive, float honeycombX[], float honeycombY[], bool honeycombActive[], int MAX_HONEYCOMBS, bool& isBirdSick, Clock& sickClock, bool& isFlyingToEdge, int& playerScore, int honeycombTier[], int honeycombType[], Clock& hummingbirdClock,const int MaxPowerups,float powerupCords[][2],bool powerupActive[],float powerupTimer[],int powerupType[]);
void drawHummingbird(RenderWindow& window, float hummingbirdX, float hummingbirdY, bool isBirdSick, bool hummingbirdActive);
bool checkBirdCollision(float& hummingbirdX, float& hummingbirdY, 
                        float bulletX, float bulletY,
                        bool& hummingbirdActive, bool& isBirdSick, 
                        int& collidedBulletCount, Clock& sickClock, bool& isFlyingToEdge);
void generateBeeHive(float beeX, float beeY, int MAX_BEES, float beehiveCord[][2], bool beehiveActive[], int MAX_BEEHIVES);
void drawBeeHive(RenderWindow& window, float beehiveCord[][2], bool beehiveActive[], int MAX_BEEHIVES );
bool checkBeeHiveCollision(float bullet_x, float bullet_y, float beehiveCord[][2], bool beehiveActive[], int MAX_BEEHIVES);
void resetGame(float& player_x, float& player_y, 
               float& bullet_x, float& bullet_y, bool& bullet_exists,
               int MAX_BEES, float beesX[], float beesY[], int beeTypes[], 
               bool beesActive[], int beesTier[], bool beesDirection[],
               int MAX_HONEYCOMBS, float honeycombX[], float honeycombY[], 
               int honeycombType[], bool honeycombActive[],
               int MAX_FLOWERS, int flowerCord[][2], int flowerActive[],
               int MAX_BEEHIVES, float beehiveCord[][2], bool beehiveActive[],
               float& hummingbirdX, float& hummingbirdY, bool& hummingbirdActive, 
               bool& isBirdSick, bool& isFlyingToEdge, 
               int& currentLevel, int& sprays, int& spraycanLives, int& spraycanState, int& beeCount, bool& firstbeeLEFT, bool& firstbeeRIGHT, int& regularbeeCount, Clock& hunterBeeClock, int& hunterbeeCount, Clock& beeClock, Clock& hummingbirdClock);
               
void resetLevel(bool& resetCall, int& spraycanLives, bool& inMenu);
void honeycombPreGenerator(float honeycombX[], float honeycombY[], bool honeycombActive[], int honeycombType[], int MAX_HONEYCOMB, int currentLevel, int honeycombTier[], float beehiveCord[][2], bool beehiveActive[], int MAX_BEEHIVES);
void callGameEnd( bool& inGameEnd, bool& resetCall);
void detectBees(int& beeCount, bool beeActive[], bool& inGameEnd, bool& resetCall, int MAX_BEES);
void drawScore(RenderWindow& window, int playerScore);
void drawPlayerLives(RenderWindow& window, int spraycanLives);
void sortleaderboard(string leaderboard[][2], int MAX_PLAYERS);
void storeleaderboard(string leaderboard[][2], int MAX_PLAYERS);
void readleaderboard(string leaderboard[][2], int MAX_PLAYERS);

void checkSprayCanLives(int& spraycanLives, bool& inGameEnd, bool& resetCall);
void generatePowerUp(float powerupCords[][2], bool powerupActive[], int powerupType[], float powerupTimer[], int MaxPowerups,float honeycombX, float honeycombY);
void updatePowerUps(float player_x, float player_y, float deltaTime, float powerupCords[][2],bool powerupActive[],float powerupTimer[],int powerupType[], const int MaxPowerups, bool power[],    float& speedmultiplier,float& sizemultiplier, float powerTimer[]);
void drawPowerUps(RenderWindow& window, float powerupCords[][2], bool powerupActive[], int MaxPowerups, int powerupType[], float powerupTimer[], float powerTimer[]);
void powerHandler(float powerTimer[], bool power[], float& sizemultiplier, float& speedmultiplier);

///infant bee////
void spawnInfantBees(
    float beehiveCord[][2], 
    bool beehiveActive[], 
    int MAX_BEEHIVES, 
    float& globalSpawnTimer, 
    float deltaTime
);
void initializeInfantBees(int initialCapacity);

void moveInfantBees(
    float deltaTime, 
    float honeycombX[], 
    float honeycombY[], 
    bool honeycombActive[], 
    int MAX_HONEYCOMBS
);
void cleanupInfantBees();
void addInfantBee(float x, float y);
void expandInfantBeeArrays();
void drawInfantBee(RenderWindow& window);
/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// Write your functions declarations here. Some have been written for you. //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////


int main(){

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
	
	
	
	/////////////MENU//////////////////
	  Font menuFont;
          if (!menuFont.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
              return -1;
          }

          Text titleText("Buzz Bombers", menuFont, 50);
          titleText.setFillColor(Color::White);
          titleText.setPosition(resolutionX/2 - titleText.getLocalBounds().width/2, 100); //using local bounds to make sure it is in middle of screen
          Text level1Text("Level 1", menuFont, 30);
          level1Text.setFillColor(Color::White);
          level1Text.setPosition(resolutionX/2 - level1Text.getLocalBounds().width/2, 190);
          Text level2Text("Level 2", menuFont, 30);
          level2Text.setFillColor(Color::White);
          level2Text.setPosition(resolutionX/2 - level2Text.getLocalBounds().width/2, 230);
          Text level3Text("Level 3", menuFont, 30);
          level3Text.setFillColor(Color::White);
          level3Text.setPosition(resolutionX/2 - level3Text.getLocalBounds().width/2, 270);
          Text exitText("Exit", menuFont, 30);
          exitText.setFillColor(Color::White);
          exitText.setPosition(resolutionX/2 - exitText.getLocalBounds().width/2, 330);
          bool inMenu = true;
          
  /////////////////////////GAME END///////////////////////////
      bool inGameEnd = false;

      Text endGameText;
      Text namePromptText;
      Text nameInputText;
      RectangleShape nameInputBox;
      bool isNameInputActive = false;
      
      
    endGameText.setFont(menuFont);
    endGameText.setString("Game Over");
    endGameText.setCharacterSize(60);
    endGameText.setFillColor(Color::White);
    endGameText.setPosition(resolutionX/2 - endGameText.getLocalBounds().width/2, 200);
    namePromptText.setFont(menuFont);
    namePromptText.setString("Enter Your Name:");
    namePromptText.setCharacterSize(30);
    namePromptText.setFillColor(Color::White);
    namePromptText.setPosition(resolutionX/2 - namePromptText.getLocalBounds().width/2, 300);
    nameInputBox.setSize(Vector2f(400, 50));
    nameInputBox.setFillColor(Color::Transparent);
    nameInputBox.setOutlineColor(Color::White);
    nameInputBox.setOutlineThickness(2);
    nameInputBox.setPosition(resolutionX/2 - 200, 350);
    nameInputText.setFont(menuFont);
    nameInputText.setCharacterSize(30);
    nameInputText.setFillColor(Color::White);
    nameInputText.setPosition(resolutionX/2 - 190, 355);
    
    /////////////////////////////////////////////////////////////////

	// Initializing Player and Player Sprites.
	bool running = false;
	float player_x = (gameColumns / 2) * boxPixelsX;
	float player_y = (gameRows - 4) * boxPixelsY;
	int playerScore = 0;
        //Initializing the leaderboard array over here
        const int MAX_PLAYERS = 100;
        string leaderboard[MAX_PLAYERS][2];
        readleaderboard(leaderboard, MAX_PLAYERS);
        
        
        
        


	


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
	groundRectangle.setPosition(0, (gameRows -2) * boxPixelsY);
	groundRectangle.setFillColor(Color::Red);
        
        //BEES NIGGA
        int MAX_BEES = 50;
        int WORKER_BEE = 0;
        int KILLER_BEE = 1;
        int beeCount = 0;
        Clock beeClock;
        int regularbeeCount = 0;
        Clock hunterBeeClock;
         int hunterBeeCount = 0;
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
        int honeycombTier[] = {0};
        //flowers
        const int MAX_FLOWERS = 100;
        int flowerCord[MAX_FLOWERS][2] = {0};
        int flowerActive[MAX_FLOWERS] = {0};
        bool firstbeeLEFT = false;
        bool firstbeeRIGHT = false;
    
        
        // Hummingbird Variables
        float hummingbirdX = -100; // Start off-screen
        float hummingbirdY = -100; // Start off-screen
        bool hummingbirdActive = false;
        bool isBirdSick = false;
        Clock sickClock;
        int collidedBulletCount = 0;
        bool isFlyingToEdge;
        Clock hummingbirdClock;
        
        
        //BEE HIVE 
        int MAX_BEEHIVES = 100;
       float beehiveCord[MAX_BEEHIVES][2] = {0};
       bool beehiveActive[MAX_BEEHIVES] = {0};

        
      //spray can
      int sprays = 7;
      int spraycanLives =1;
      int spraycanState = 6;
      
      //POWER UPS
      const int MaxPowerups = 100;
      float powerupCords[MaxPowerups][2] ={0};
      bool powerupActive[MaxPowerups] = {0};
      float powerupTimer[MaxPowerups] = {0};
      int powerupType[MaxPowerups] = {0};
        bool power[4] ={0};
        float speedmultiplier = 1.0f;
        float sizemultiplier = 1.0f;
        float powerTimer[4] = {0}; //4 power ups timers

        
        // Current game level
        int currentLevel = 4;
        //reset call
        bool resetCall = false;
          running = true;
          bool exit = false;
          
          const int MAX_NAME_LENGTH = 20;
          char playerName[MAX_NAME_LENGTH + 1] = {0}; // +1 for null terminator
          int  nameLength = 0;
          RectangleShape enterButton;
          Text enterButtonText;
          
          enterButton.setSize(Vector2f(100, 50)); // Adjust size as needed
        enterButton.setFillColor(Color::Green);
        enterButton.setPosition(resolutionX/2-50, 420);

        enterButtonText.setString("Enter");
        enterButtonText.setCharacterSize(24);
        enterButtonText.setFillColor(Color::White);
        enterButtonText.setPosition(resolutionX/2, 400);
        
         float globalInfantBeeSpawnTimer = 0.0f;
          initializeInfantBees(10);
          
	while (window.isOpen() && exit == false) {
        float deltaTime = movementClock.restart().asSeconds(); //gets the time between each frame reload (every run of thegame loop)
      if (inGameEnd) {
        Event endEvent;
        while (window.pollEvent(endEvent)) {
            if (endEvent.type == Event::Closed) 
                return 0;
            // Mouse click to activate/deactivate input box
            if (endEvent.type == Event::MouseButtonPressed) {
                Vector2i mousePos = Mouse::getPosition(window);
                
                // Input box activation
                if (nameInputBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    isNameInputActive = true;
                    nameInputBox.setOutlineColor(Color::Green);
                } else {
                    isNameInputActive = false;
                    nameInputBox.setOutlineColor(Color::White);
                }

                // Enter button click
                if (enterButton.getGlobalBounds().contains(mousePos.x, mousePos.y) && nameLength != 0) {
                    cout<<playerName<<endl;
                    inGameEnd = false;
                    inMenu = true;
                    playerName[0] = '\0';
                    nameLength = 0;
                    
                    
                }
            }

            // Text input handling (only when input box is active)
          if (isNameInputActive && endEvent.type == Event::TextEntered) {
              if (endEvent.text.unicode == '\b') {
                  // Backspace
                  if (nameLength > 0) {
                      playerName[--nameLength] = '\0';
                  }
              }
              else if (isprint(endEvent.text.unicode) && nameLength < MAX_NAME_LENGTH) {
                  playerName[nameLength++] = static_cast<char>(endEvent.text.unicode);
                  playerName[nameLength] = '\0'; // Null-terminate
              }

              // Update displayed text
              nameInputText.setString(playerName);
          }
        }

        // Clear the window
     window.clear(Color::Black);
    window.draw(endGameText);
    window.draw(namePromptText);
    window.draw(nameInputBox);
    window.draw(nameInputText);
    window.draw(enterButtonText);
    window.draw(enterButton);
    window.display();
}

          else{
              // Game event handling
              Event gameEvent;
              while (window.pollEvent(gameEvent)) {
                  if (gameEvent.type == Event::Closed) 
                      return 0;
              }
            
          /*if (resetCall) {
          cout<<"reset call is true"<<endl;
               resetGame(player_x,  player_y, 
                bullet_x, bullet_y,  bullet_exists,
                MAX_BEES, beesX, beesY, beeTypes, 
                beesActive, beesTier,  beesDirection,
                MAX_HONEYCOMBS, honeycombX,  honeycombY, 
                honeycombType,  honeycombActive,
               MAX_FLOWERS,  flowerCord,  flowerActive,
                MAX_BEEHIVES, beehiveCord, beehiveActive,
               hummingbirdX, hummingbirdY, hummingbirdActive, 
                isBirdSick,  isFlyingToEdge, 
              currentLevel, sprays,spraycanLives, spraycanState, beeCount, firstbeeLEFT,firstbeeRIGHT, regularbeeCount,  hunterBeeClock, hunterBeeCount, beeClock, hummingbirdClock);
              
              resetCall = !resetCall;
          }*/
            
            
  
		///////////////////////////////////////////////////////////////
		//                                                           //
		// Call Your Functions Here. Some have been written for you. //
		// Be vary of the order you call them, SFML draws in order.  //
		//                                                           //
		///////////////////////////////////////////////////////////////
		   

                             spawnInfantBees(
                    beehiveCord, 
                    beehiveActive, 
                    MAX_BEEHIVES, 
                    globalInfantBeeSpawnTimer, 
                    deltaTime
                );
                        moveInfantBees(
            deltaTime, 
            honeycombX, 
            honeycombY, 
            honeycombActive, 
            MAX_HONEYCOMBS
        );
		cout<<"timer:" <<powerTimer[0]<<endl;
		cout<<speedmultiplier <<":"<<sizemultiplier<<endl;
		cout<<power[0]<<" "<<power[1]<<" "<<power[2]<<" "<<power[3]<<endl;
		powerHandler(powerTimer, power, sizemultiplier, speedmultiplier);
                updatePowerUps(player_x, player_y,deltaTime, powerupCords,powerupActive,powerupTimer,powerupType, MaxPowerups, power, speedmultiplier, sizemultiplier, powerTimer);
                honeycombPreGenerator(honeycombX, honeycombY, honeycombActive, honeycombType, MAX_HONEYCOMBS, currentLevel, honeycombTier, beehiveCord, beehiveActive, MAX_BEEHIVES);
                beesGenerator(beesX, beesY ,beeTypes, beesActive, beesTier, beesDirection, MAX_BEES, WORKER_BEE, currentLevel, beeCount, resetCall,regularbeeCount, hunterBeeClock, hunterBeeCount,  beeClock);  
               movePlayer(player_x, player_y, 0, resolutionX - boxPixelsX, 0.5*speedmultiplier, flowerCord,flowerActive,MAX_FLOWERS, resetCall, spraycanLives, inMenu);
                moveBees(beesX,beesY, beesTier,  beesDirection, beeTypes,  beesActive,  MAX_BEES,  deltaTime,  WORKER_BEE, honeycombX, honeycombY,honeycombType,honeycombActive,MAX_HONEYCOMBS, flowerCord, flowerActive, MAX_FLOWERS, beehiveCord, beehiveActive, MAX_BEEHIVES, firstbeeLEFT, firstbeeRIGHT);
                fireBullet(bullet_x, bullet_y, bullet_exists, player_x, player_y, sprays, spraycanState, spraycanLives, inGameEnd, resetCall);
                generateHummingbird(deltaTime,hummingbirdX, hummingbirdY, hummingbirdActive, honeycombX, honeycombY, honeycombActive, MAX_HONEYCOMBS, isBirdSick, sickClock, isFlyingToEdge, playerScore, honeycombTier, honeycombType, hummingbirdClock,MaxPowerups,  powerupCords,powerupActive, powerupTimer, powerupType);
		if (bullet_exists == true)
		{       
			moveBullet(bullet_y, bullet_exists, bulletClock);
			drawBullet(window, bullet_x, bullet_y, bulletSprite);
			//simple functionality to check if bullet has hit bee
			//simple functionality to check if bullet hit honeycomb
			//blah blah hummingbird check
			if (checkBeeCollision( bullet_x, bullet_y, beesX, beesY ,beeTypes, beesActive, beesTier, beesDirection, MAX_BEES, WORKER_BEE, honeycombX, honeycombY, honeycombType, honeycombActive,  MAX_HONEYCOMBS,  playerScore, honeycombTier)) 
			{
                          bullet_exists = false;			
			}else if (checkHoneyCombCollision( bullet_x, bullet_y,honeycombX, honeycombY,honeycombType, honeycombActive,  MAX_HONEYCOMBS,powerupCords, powerupActive, powerupType,powerupTimer, MaxPowerups)){
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
                
		drawPlayer(window, player_x, player_y, spraycanState, sizemultiplier);
                drawBees(window, beesX, beesY ,beeTypes, beesActive, beesTier, beesDirection, MAX_BEES, WORKER_BEE);
		window.draw(groundRectangle);
		drawHoneycombs(window, honeycombX, honeycombY, honeycombType, honeycombActive, MAX_HONEYCOMBS);
		drawFlowers(window, flowerCord,flowerActive,MAX_FLOWERS);
		drawBeeHive( window, beehiveCord, beehiveActive, MAX_BEEHIVES);
		drawHummingbird(window, hummingbirdX, hummingbirdY, isBirdSick, hummingbirdActive);
		detectBees(beeCount, beesActive,inGameEnd ,resetCall,MAX_BEES);
		
                checkSprayCanLives(spraycanLives,inGameEnd,resetCall) ;
                drawScore( window, playerScore);
		drawPlayerLives(window, spraycanLives);
		drawPowerUps(window, powerupCords, powerupActive,  MaxPowerups, powerupType, powerupTimer, powerTimer);
		 drawInfantBee(window ); 
		window.display();
		window.clear();
		

	}
	}
	cleanupInfantBees();
 }
 
 
////////////////////////////////////////////////////////////////////////////
//                                                                        //
// Write your functions definitions here. Some have been written for you. //
//                                                                        //
////////////////////////////////////////////////////////////////////////////

void drawPlayer(RenderWindow& window, float& player_x, float& player_y, int spraycanState, float sizemultiplier) {
   static Texture playerTexture;
   static bool textureLoaded = false;
   Sprite playerSprite;

   // Load texture only once
   if (!textureLoaded) {
       if (!playerTexture.loadFromFile("Textures/spray.png")) {
           std::cerr << "Failed to load player texture!" << std::endl;
           return;
       }
       textureLoaded = true;
   }

   playerSprite.setTexture(playerTexture);
   playerSprite.setTextureRect(IntRect(10, 0, playerTexture.getSize().x, playerTexture.getSize().y));
   
   // Set scale based on size multiplier
   playerSprite.setScale(sizemultiplier, sizemultiplier);
   
   // Adjust position based on scale
   float adjusted_y = player_y - (boxPixelsY * (sizemultiplier-1) *2);
   playerSprite.setPosition(player_x, adjusted_y);
   window.draw(playerSprite);
   
   const int decreaseConstant = 4;
   RectangleShape stateRect(Vector2f((boxPixelsX - 10) * sizemultiplier, (boxPixelsY - decreaseConstant * spraycanState) * sizemultiplier));
   stateRect.setFillColor(Color::White);
   stateRect.setPosition(player_x + 10*sizemultiplier, adjusted_y + boxPixelsY * sizemultiplier + decreaseConstant * spraycanState);
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
void drawBullet(RenderWindow& window, float& bullet_x, float& bullet_y, Sprite& bulletSprite) {
	bulletSprite.setPosition(bullet_x, bullet_y);
	window.draw(bulletSprite);
}
/////////////START OF MY FUNCTIONS :D//////////////////
//RESET FUNCTION FOR EVERYTHING --MAKING THIS AFTER SOME TIME BUT PLACING IT AT TOP FOR EASE OF ACCESS
void resetGame(float& player_x, float& player_y, 
               float& bullet_x, float& bullet_y, bool& bullet_exists,
               int MAX_BEES, float beesX[], float beesY[], int beeTypes[], 
               bool beesActive[], int beesTier[], bool beesDirection[],
               int MAX_HONEYCOMBS, float honeycombX[], float honeycombY[], 
               int honeycombType[], bool honeycombActive[],
               int MAX_FLOWERS, int flowerCord[][2], int flowerActive[],
               int MAX_BEEHIVES, float beehiveCord[][2], bool beehiveActive[],
               float& hummingbirdX, float& hummingbirdY, bool& hummingbirdActive, 
               bool& isBirdSick, bool& isFlyingToEdge, 
               int& currentLevel, int& sprays, int& spraycanLives, int& spraycanState, int& beeCount, bool& firstbeeLEFT, bool& firstbeeRIGHT, int& regularbeeCount, Clock& hunterBeeClock, int& hunterbeeCount, Clock& beeClock, Clock& hummingbirdClock) 
{
cout<<"reset call called";
    // Reset player position
    player_x = (gameColumns / 2) * boxPixelsX;
    player_y = (gameRows - 4) * boxPixelsY;

    // Reset bullet
    bullet_x = player_x;
    bullet_y = player_y + 64;
    bullet_exists = false;

    // Reset bees
    for (int i = 0; i < MAX_BEES; ++i) {
        beesX[i] = 0;
        beesY[i] = 0;
        beeTypes[i] = 0;
        beesActive[i] = false;
        beesTier[i] = 0;
        beesDirection[i] = true;
    }
    beeCount = 0;
    firstbeeLEFT = false;
    firstbeeRIGHT =false;
    
    regularbeeCount = 0;
    hunterBeeClock.restart();
    hunterbeeCount = 0;
    beeClock.restart();
    // Reset honeycombs
    for (int i = 0; i < MAX_HONEYCOMBS; ++i) {
        honeycombX[i] = 0;
        honeycombY[i] = 0;
        honeycombType[i] = 0;
        honeycombActive[i] = false;
    }

    // Reset flowers
    for (int i = 0; i < MAX_FLOWERS; ++i) {
        flowerCord[i][0] = 0;
        flowerCord[i][1] = 0;
        flowerActive[i] = false;
    }

    // Reset beehives
    for (int i = 0; i < MAX_BEEHIVES; ++i) {
        beehiveCord[i][0] = 0;
        beehiveCord[i][1] = 0;
        beehiveActive[i] = false;
    }

    // Reset hummingbird
    hummingbirdX = -100;
    hummingbirdY = -100;
    hummingbirdActive = false;
    isBirdSick = false;
    isFlyingToEdge = false;
    hummingbirdClock.restart();

    // Reset spray states
    sprays = 0;
    spraycanState = 4;
    
    
}
void callGameEnd(bool& inGameEnd, bool& resetCall) {
    cout << "GAME ENDED B" << endl;
   //inGameEnd = true;
   //resetCall = true;

}

void detectBees(int& beeCount, bool beeActive[], bool& inGameEnd, bool& resetCall, int MAX_BEES){
    static bool gameEnded = false;
    bool nobee = true;
    
    for(int i = 0; i < MAX_BEES; i++){
        if (beeActive[i]) {
            nobee = false;
            break;
        }
    }
    
    if ((beeCount == 20 || beeCount == 30)){
        if(nobee && !gameEnded){
            cout << "Force game end in detectBees" << endl;
            callGameEnd(inGameEnd, resetCall);
        }
    }
}



void checkSprayCanLives(int& spraycanLives, bool& inGameEnd, bool& resetCall) {

static bool gameEnded = false;

    if (spraycanLives == 0 && !gameEnded) {
        cout << "Game End Called due to no spray can lives." << endl;
        callGameEnd(inGameEnd, resetCall);
        gameEnded = true; // Set the flag to true to prevent further calls
    }

}

//time to make function to move the player
void movePlayer(float& player_x, float player_y, int boundaryLeft, int boundaryRight, float speed, int flowerCord[][2], int flowerActive[], const int MAX_FLOWERS, bool& resetCall, int& spraycanLives,bool& inMenu) {
    int oldGridX = static_cast<int>(player_x) / boxPixelsX;
    int oldGridY = static_cast<int>(player_y) / boxPixelsY;
    bool canMoveRight = true;
    bool canMoveLeft = true;
    bool forcedMove = false;
    bool teleported = false;
    const int textureSize = 32;

    // Comprehensive overlap and forced move check
    bool playerOverlappingFlower = false;

    // Check if player is currently overlapping with a flower
    for (int i = 0; i < MAX_FLOWERS; i++) {
        if (flowerActive[i]) {
            float flowerLeft = flowerCord[i][0];
            float flowerRight = flowerLeft + textureSize - 1;
            float playerLeft = player_x;
            float playerRight = playerLeft + textureSize - 1;
            
            if (playerRight >= flowerLeft && playerLeft <= flowerRight) {
                playerOverlappingFlower = true;
                break;
            }
        }
    }

    // Enhanced forced move logic
    if (playerOverlappingFlower) {
        // Try moving in both directions with more flexible checks
        float possibleMoves[] = {player_x + textureSize, player_x - textureSize};
        bool moveOptions[] = {true, true};

        for (int dir = 0; dir < 2; dir++) {
            float newX = possibleMoves[dir];
            
            // Check screen boundaries
            if (newX < 0 || newX + textureSize > resolutionX) {
                moveOptions[dir] = false;
                continue;
            }

            // Check flower collisions
            for (int i = 0; i < MAX_FLOWERS; i++) {
                if (flowerActive[i]) {
                    float flowerLeft = flowerCord[i][0];
                    float flowerRight = flowerLeft + textureSize - 1;
                    
                    if (newX + textureSize - 1 >= flowerLeft && newX <= flowerRight) {
                        moveOptions[dir] = false;
                        break;
                    }
                }
            }
        }

        // Choose a valid move if possible
        if (moveOptions[0] || moveOptions[1]) {
            player_x = moveOptions[0] ? possibleMoves[0] : possibleMoves[1];
            
            // Clear old grid position
            gameGrid[oldGridY][oldGridX] = 0;
            
            // Calculate and mark new grid position
            int newGridX = static_cast<int>(player_x) / boxPixelsX;
            int newGridY = static_cast<int>(player_y) / boxPixelsY;
            gameGrid[newGridY][newGridX] = 1;
            
            forcedMove = true;
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
                    float flowerRight = flowerLeft + textureSize + 1;

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

            // Move if no collision and within boundary
            if (canMoveLeft) {
                player_x = NewX;
                
                // Clear old grid position
                gameGrid[oldGridY][oldGridX] = 0;
                
                // Calculate and mark new grid position
                int newGridX = static_cast<int>(player_x) / boxPixelsX;
                int newGridY = static_cast<int>(player_y) / boxPixelsY;
                gameGrid[newGridY][newGridX] = 1;
            }
        }
    }

    // Check for flower collision when moving right
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
                
                // Clear old grid position
                gameGrid[oldGridY][oldGridX] = 0;
                
                // Calculate and mark new grid position
                int newGridX = static_cast<int>(player_x) / boxPixelsX;
                int newGridY = static_cast<int>(player_y) / boxPixelsY;
                gameGrid[newGridY][newGridX] = 1;
            }
        }
    }


      bool teleportPossible = false;
      for (int x = 0; x < gameColumns; x++) {
          // Check if there's a free space in the ground row
          if (gameGrid[gameRows - 3][x] == 0 && gameGrid[gameRows - 4][x] != 1) {
              teleportPossible = true;
              break;
          }
      }

    // Check for flowers immediately adjacent to the player
    bool flowerOnImmediateRight = false;
    bool flowerOnImmediateLeft = false;

    for (int i = 0; i < MAX_FLOWERS; i++) {
        if (flowerActive[i]) {
            float flowerLeft = flowerCord[i][0]; 
            float flowerRight = flowerLeft + textureSize - 1;

            // Immediate Right Check
            if (player_x + textureSize >= flowerLeft - 5 && 
                player_x + textureSize <= flowerLeft + textureSize + 5) {
                flowerOnImmediateRight = true;
            }
            
            // Immediate Left Check
            if (player_x <= flowerRight + 5 && player_x >= flowerLeft - 5) {
                flowerOnImmediateLeft = true;
            }
        }
    }

      // Teleportation logic when completely blocked
      if ((flowerOnImmediateLeft && flowerOnImmediateRight) || 
          (flowerOnImmediateLeft && player_x <= boundaryLeft) || 
          (flowerOnImmediateRight && player_x >= boundaryRight)) {
          
          float playerMidpoint = player_x + (textureSize / 2.0f);
          float closestEmptySpace = -1;
          float minDistance = resolutionX;

          // Loop through entire screen width to find empty space
          for (float potentialX = 0; potentialX <= resolutionX - textureSize; potentialX += 1.0f) {
              // Skip the space the player is currently occupying
              if (potentialX >= player_x && potentialX <= player_x + textureSize - 1) {
                  continue;
              }

              bool spaceIsFree = true;

              // Check if this space is free of flowers
              for (int i = 0; i < MAX_FLOWERS; i++) {
                  if (flowerActive[i]) {
                      float flowerLeft = flowerCord[i][0];
                      float flowerRight = flowerLeft + textureSize - 1;
                      float playerTestLeft = potentialX;
                      float playerTestRight = potentialX + textureSize - 1;

                      // If potential teleport space overlaps with a flower, mark as not free
                      if (playerTestRight >= flowerLeft && playerTestLeft <= flowerRight) {
                          spaceIsFree = false;
                          break;
                      }
                  }
              }

              // If space is free, find the closest empty space to current player position
              if (spaceIsFree) {
                  float distance = abs(potentialX - player_x);
                  if (distance < minDistance) {
                      minDistance = distance;
                      closestEmptySpace = potentialX;
                  }
              }
          }

          // Teleport to the closest empty space if found
          if (closestEmptySpace != -1) {
              player_x = closestEmptySpace;
              teleported = true;
              cout << "Teleported to nearest empty space" << endl;
          } else {
              // If no empty space found, handle game end
              cout << "Game End - No Possible Moves" << endl;
              //resetLevel(resetCall, spraycanLives, inMenu);
              
          }
      }


    // Ensure grid position is correctly marked
    if (!Keyboard::isKeyPressed(Keyboard::Left) && 
        !Keyboard::isKeyPressed(Keyboard::Right) && 
        !teleported) {
        gameGrid[oldGridY][oldGridX] = 1;
    }

    if (forcedMove) {
        gameGrid[oldGridY][oldGridX] = 0;
    }

    if (teleported) {
        gameGrid[oldGridY][oldGridX] = 0;
    }
    
    
//end of function
}

//reset level function
void resetLevel(bool& resetCall, int&spraycanLives, bool& inMenu){

    if (spraycanLives > 0) {
        spraycanLives--;
        resetCall = true;
    }
    else {
        inMenu = true;
    }
}






//bullet boom boom
void fireBullet(float& bullet_x, float& bullet_y, bool& bullet_exists, float player_x, float player_y, int& sprays, int& spraycanState, int& spraycanLives, bool& inGameEnd, bool& resetCall) {
    static bool wasSpacePressed = false; // Tracks if Space was pressed in the previous frame
    static int totalSprays = 0;
    bool isSpacePressed = Keyboard::isKeyPressed(Keyboard::Space);
    static bool gameEndCalled = false;



    if (isSpacePressed && !wasSpacePressed && !bullet_exists) { // Fire only on the first press
        bullet_exists = true;
        bullet_x = player_x;
        bullet_y = player_y;
        sprays++;
    }
    if(sprays ==8){
      spraycanState += 1;
      totalSprays += sprays;
      sprays = 0;
    }
    if (spraycanState == 7 && spraycanLives > 0){
      spraycanState = 0;
      spraycanLives--;
    }


    // this makes it so that continous firing is not allowed by holding space bar
    // the function gets called on every game loop, if the spacebar has been held during two game loops, the bullet wont fire, if the space bar was not pressed in the second game loop then it would fire
    wasSpacePressed = isSpacePressed;
}





// A GODDAMN BEE GENERATORRRRRR
void beesGenerator(float beesX[], float beesY[], int beeTypes[], bool beesActive[], int beesTier[], bool beesDirection[], int MAX_BEES, int WORKER_BEE, int currentLevel, int& beeCount, bool resetCall, int& regularbeeCount, Clock& hunterBeeClock, int& hunterBeeCount, Clock& beeClock ) {
    // we use static variables to maintain state between function calls

        
    // ddetermine bee counts based on level
    int maxBeeCount = 0;
    int regularBees = 0;
    int hunterBees = 0;


    switch (currentLevel) {
        case 1:
            maxBeeCount = 20;
            regularBees = 20;
            break;
        case 2:
            maxBeeCount = 10;
            regularBees = 0;
            hunterBees = 10;
            break;
        case 3:
            maxBeeCount = 30;
            regularBees = 20;
            hunterBees = 10;
            break;   
            
      case 4:
            maxBeeCount = 35;
            regularBees = 20;
            hunterBees = 15;
            break;
    }
    
     
        
    int delay = (regularbeeCount < 10) ? 1 : 2; // 2 seconds for the first 6, 10 seconds for the rest
    int beeNum = (regularbeeCount < 10)? 1 : 2; // 1 bee for first 6, 2 bees for rest
    // now we generate 2 bees every 2 seconds after initial 6

    if (beeClock.getElapsedTime().asSeconds() >= delay && regularbeeCount < regularBees) {
          int newBeesGenerated = 0;
          int startPoint = 1;
          int beesToGenerate = min(beeNum, regularBees - regularbeeCount);

        for (int i = 0; i < MAX_BEES && newBeesGenerated < beesToGenerate; i++) {
 
            if (!beesActive[i]) {
                if (delay == 2){
                beesActive[i] = true;
                beeTypes[i] = WORKER_BEE;
                        // Alternate between left and right edges
                        if (beeCount % 2 == 0) {
                            beesX[i] = 0;
                            beesDirection[i] = true; // Move right
                        } else {
                            beesX[i] = resolutionX - boxPixelsX ;
                            beesDirection[i] = false; // Move left
                        }
                beesTier[i] = rand() % 2; // Random starting tier
                (beesTier[i] == 1) ? beesY[i] = boxPixelsY : beesY[i] = boxPixelsY * 2;
                  
                  
                  
                beeCount++;
                newBeesGenerated++;
                regularbeeCount++;
      
              }else{
                beeCount++;
                beesActive[i] = true;
                beeTypes[i] = WORKER_BEE;
                startPoint = rand() % 2;
                (startPoint == 1)? beesX[i] = 0 : beesX[i] = resolutionX - boxPixelsX;
                beesTier[i] = rand() % 2; // Random starting tier
                (beesTier[i] == 1) ? beesY[i] = boxPixelsY : beesY[i] = boxPixelsY * 2;
                beesDirection[i] = (startPoint == 1)? 1: 0; // Random initial direction
                newBeesGenerated++;
                regularbeeCount++;
  
                            
            }
          }
        }
        // Restart the clock
        beeClock.restart();
    }
    

    if (currentLevel >= 2 && hunterBeeCount < hunterBees) {

        // First hunter bee starts after 15 seconds
        if (hunterBeeCount == 0 && hunterBeeClock.getElapsedTime().asSeconds() >= 4) {
            for (int i = 0; i < MAX_BEES; i++) {
                if (!beesActive[i]) {
                    beesActive[i] = true;
                    beeTypes[i] = 1;
                    int startHunter = rand() % 2;
                    if (startHunter == 0){ 
                    beesX[i] = 0;
                    beesDirection[i] = true;
                    }
                    else {  beesX[i] = resolutionX-boxPixelsX;
                    beesDirection[i] = false;
                    }
                  
                    // Random tier placement
                    beesTier[i] = rand() % 2;
                    (beesTier[i] == 1) ? beesY[i] = boxPixelsY : beesY[i] = boxPixelsY * 2;
                    hunterBeeCount++;
                    beeCount++;
                    hunterBeeClock.restart();
                    break;
                }
            }
        }
        // Subsequent hunter bees spawn every 7 seconds
      else if (hunterBeeCount > 0 && hunterBeeClock.getElapsedTime().asSeconds() >= 3 && hunterBeeCount < hunterBees) {
      int startHunter;
        for (int i = 0; i < MAX_BEES; i++) {
            if (!beesActive[i]) {
                beesActive[i] = true;
                beeTypes[i] = 1;
                startHunter = rand() % 2;
                (startHunter == 1)? beesX[i] = 0 : beesX[i] = resolutionX - boxPixelsX;
                beesTier[i] = rand() % 2;
                (beesTier[i] == 1) ? beesY[i] = boxPixelsY : beesY[i] = boxPixelsY * 2;
                beesDirection[i] = (startHunter == 1)? 1: 0; // Random initial direction
                hunterBeeCount++;
                beeCount++;
                hunterBeeClock.restart();
                break;

            }
        }
    }

    }
          
}

// MOVE BEES MOVEEEEEE
void moveBees(float beesX[], float beesY[], int beesTier[], bool beesDirection[], int beeTypes[], bool beesActive[], int MAX_BEES, float deltaTime, int WORKER_BEE, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS,int flowerCord[][2], int flowerActive[], const int MAX_FLOWERS, float beehiveCord[][2], bool beehiveActive[], int MAX_BEEHIVES, bool& firstbeeLEFT, bool& firstbeeRIGHT) {
            
  //static variabless to store state of pauses of bees across calls
  static Clock BeePauseClock;
  static float pauseStartTime[100] = {0}; // Store pause start time for each bee
  static bool paused[100] = {false};
  float PAUSE_DURATION = 4.0f;    
  
    for (int i = 0; i < MAX_BEES; i++) {
        if (beesActive[i]) {
        
            //we set the speed based on bee type
            float speed = (beeTypes[i] == WORKER_BEE) ? 800.0f : 1000.0f;

            // Calculate movement using deltaTime
            float movement = speed * deltaTime;
            
            if(beeTypes[i] == WORKER_BEE){
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
          }
            // Move horizontally based on direction
            if (beesDirection[i]) {
                beesX[i] += movement;
            } else {
                beesX[i] -=movement;
            }
         
         
         if(beeTypes[i] == WORKER_BEE){
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
                if (flowerGenerator(beesX[i],beesY[i],flowerCord,flowerActive,MAX_FLOWERS, firstbeeRIGHT, firstbeeLEFT)){
                    //if flower generated
                    beesActive[i] = false;
                }           
              }
            // Deactivate bee if it reaches bottom
            if (beesY[i] >= resolutionY) {
                beesActive[i] = false;
            }

        }
        
      else {//hunter bee movement
          float lastRow = (gameRows - 3) * boxPixelsY;
          if (beesX[i] <= 0 && beesY[i] < lastRow) {
              beesX[i] = 0;  // Stop at the left edge
              beesDirection[i] = !beesDirection[i];
              float newBeeY = beesY[i] + boxPixelsY;
              beesY[i] = newBeeY;
              beesTier[i]++;
              }             
              else if (beesX[i] >= resolutionX - boxPixelsX && beesY[i] <lastRow) {
                beesX[i] = resolutionX - boxPixelsX-3;  // Stop at the right edge
                beesDirection[i] = !beesDirection[i];  // Reverse direction
                float newBeeY = beesY[i] + boxPixelsY;
                beesY[i] = newBeeY;
                beesTier[i]++;

            }
             //if it is on last row, dont drop it down just change its direction
            else if (beesY[i]>= lastRow && beesX[i] <= 0 || beesX[i]>= resolutionX - boxPixelsX ){
                  beesDirection[i] = !beesDirection[i];
                  }            
                
           
            if (beesY[i] >= lastRow){
                if (flowerGenerator(beesX[i],beesY[i],flowerCord,flowerActive,MAX_FLOWERS, firstbeeRIGHT, firstbeeLEFT)){
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
}

// Function to check collision between bullet and bees
bool checkBeeCollision(float bullet_x, float bullet_y, float beesX[], float beesY[], int beeTypes[], bool beesActive[], int beesTier[], bool beesDirection[], int MAX_BEES, int WORKER_BEE, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS, int& playerScore, int honeycombTier[]) {
    for (int i = 0; i < MAX_BEES; i++) {
        if (beesActive[i]) {
            // we detect collision and then generate honey comb 
            if (abs(bullet_x - beesX[i]) < boxPixelsX && 
                abs(bullet_y - beesY[i]) < boxPixelsY) {
                generateHoneycomb(beesX[i], beesY[i], beeTypes[i], 
                                  honeycombX, honeycombY, honeycombType, honeycombActive, MAX_HONEYCOMBS, beesTier[i], honeycombTier);
                
                //after honey comb is generated, calculate score
                (beeTypes[i] == WORKER_BEE)? playerScore += 100 : playerScore += 1000;
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
                       float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS,int beeTier, int honeycombTier[]) {
                       
    for (int i = 0; i < MAX_HONEYCOMBS; i++) {
        if (!honeycombActive[i]) {
            honeycombX[i] = bee_x;
            honeycombY[i] = bee_y;
            honeycombType[i] = beeType;
            honeycombActive[i] = true;
            honeycombTier[i] = beeTier;
            break;
        }
    }
}


void honeycombPreGenerator(float honeycombX[], float honeycombY[], bool honeycombActive[], int honeycombType[], int MAX_HONEYCOMB, int currentLevel, int honeycombTier[], float beehiveCord[][2], bool beehiveActive[], int MAX_BEEHIVES) {

    static bool generated = false;
    // Reset all honeycombs to inactive first
    static bool hivegenerated = false;
        int honeycombCount = 0;
    int beehiveCount= 0;
        switch (currentLevel) {
        case 1:
            honeycombCount = 3;
            break;
        case 2:
            honeycombCount = 9;
            break;
        case 3:
            honeycombCount = 15;
            break;
        case 4:
            honeycombCount = 15;
            beehiveCount = 5;
            break;
}
  
    
    if (!generated){
    for (int i = 0; i < MAX_HONEYCOMB; i++) {
        honeycombActive[i] = false;
        honeycombType[i] = 0;
    }


    for (int i = 0; i < honeycombCount; i++) {
        // we choose x position but make sure it is divisble by 32 so that they dont overlap also some margn from edge
        honeycombX[i] = (rand() % ((resolutionX - 100) / 32)) * 32 + 50;
        int availableTiers = gameRows - 4; 
        int randomTier = rand() % availableTiers;
        honeycombY[i] = boxPixelsY * (randomTier + 1); 
        // Activate the honeycomb
        honeycombActive[i] = true;
        honeycombType[i] = 0;
        honeycombTier[i] = randomTier;
    }
    generated = true;
  }
  else {
      //do nothing
  }
  if (!hivegenerated && currentLevel == 4){
  //beehive pregenerationnn
  for (int i = 0; i < beehiveCount; i++) {
        // we choose x position but make sure it is divisble by 32 so that they dont overlap also some margn from edge
        beehiveCord[i][0] = (rand() % ((resolutionX - 100) / 32)) * 32 + 50;
        int availableTiers = gameRows - 4; 
        int randomTier = rand() % availableTiers;
        beehiveCord[i][1] = boxPixelsY * (randomTier + 1); 
        // Activate the honeycomb
        beehiveActive[i] = true;
    }
    hivegenerated = true;
  }
  else {
      //do nothing
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
            honeycombSprite.setTexture(honeycombType[i] == 0 ? yellowHoneycombTexture : redHoneycombTexture);
            honeycombSprite.setPosition(honeycombX[i], honeycombY[i]);
            window.draw(honeycombSprite);
        }
    }
}

//function to check collision between bullet and honeycomb
bool checkHoneyCombCollision(float bullet_x, float bullet_y, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int MAX_HONEYCOMBS, float powerupCords[][2], bool powerupActive[], int powerupType[], float powerupTimer[], int MaxPowerups){
   for (int i = 0; i < MAX_HONEYCOMBS; i++) {
        if (honeycombActive[i]) {
            // Simple collision detection
            if (abs(bullet_x - honeycombX[i]) < boxPixelsX && 
                abs(bullet_y - honeycombY[i]) < boxPixelsY) { 
                if (honeycombType[i] == 1){
                //red honeycomb
                generatePowerUp(powerupCords, powerupActive, powerupType,powerupTimer, MaxPowerups,honeycombX[i],honeycombY[i]);
                }
                // remove honeycomb
                honeycombActive[i] = false;
                return true;
            }
        }
    }
    return false;
}



// FLOWERSSSSS

bool flowerGenerator(float beeX, float beeY, int flowerCord[][2], int flowerActive[], const int MAX_FLOWERS, bool& firstBeeLEFT, bool& firstBeeRIGHT) {
 

    // we check if bee is just above ground and aligned with grid
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
void generateHummingbird(float deltaTime,float& hummingbirdX, float& hummingbirdY, bool& hummingbirdActive, 
                         float honeycombX[], float honeycombY[], bool honeycombActive[], 
                         int MAX_HONEYCOMBS, bool& isBirdSick, Clock& sickClock, bool& isFlyingToEdge, int& playerScore, int honeycombTier[], int honeycombType[],Clock& hummingbirdClock,const int MaxPowerups, float powerupCords[][2],bool powerupActive[],float powerupTimer[],int powerupType[]) {
  
    static Clock pauseClock; 
    static int hummingbirdMovementCount = 0; 
    static float targetX = 0; 
    static float targetY = 0; 
    static bool newTargetNeeded = true; 
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
            targetCalculated = true; // we are preventing recalculation
        }

        // fly to the edge we will increment the speed based on X and Y cords of bird and trget
        float speed = 30.0f; // Speed of the hummingbird
        if (hummingbirdX < targetX) {
            hummingbirdX += speed * deltaTime;
            if (hummingbirdX > targetX) hummingbirdX = targetX; //if bird accidentally exceeds the target then snap back to position
        } else {
            hummingbirdX -= speed * deltaTime;
            if (hummingbirdX < targetX) hummingbirdX = targetX; //same as above
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
            isFlyingToEdge = false;  
            targetCalculated = false; 
            hummingbirdActive = false; 
        }
    }


    // all the checks for generating hummingbird
    if (!hummingbirdActive && !isBirdSick && hummingbirdClock.getElapsedTime().asSeconds() >= 4) {
        int edge = rand() % 4; // 0 = left, 1 = right, 2 = top, 3 = bottom
        switch (edge) {
            case 0: 
                hummingbirdX = 0;
                hummingbirdY = rand() % resolutionY;
                break;
            case 1: 
                hummingbirdX = resolutionX - boxPixelsX;
                hummingbirdY = rand() % resolutionY;
                break;
            case 2: 
                hummingbirdX = rand() % resolutionX;
                hummingbirdY = 0;
                break;
            case 3: 
                hummingbirdX = rand() % resolutionX;
                hummingbirdY = resolutionY - boxPixelsY;
                break;
        }

        hummingbirdActive = true;
        hummingbirdMovementCount = 0;
        newTargetNeeded = true; 
    }
    if (isBirdSick && sickClock.getElapsedTime().asSeconds() >= 5) {
        isBirdSick = false; 
    }


    // If the hummingbird is active, fly it
    if (hummingbirdActive) {
        if (newTargetNeeded) {
            // we see if new position needed
            targetX = rand() % (resolutionX - boxPixelsX);
            targetY = rand() % resolutionY;
            if (targetY >= (gameRows - 3) * boxPixelsY){
              targetY = rand()%resolutionY;
            }else{ 
            newTargetNeeded = false; // Reset the flag
        }}


        // Move towards the target position
        float speed = 50.0f; // Speed of the hummingbird
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
                            generatePowerUp(powerupCords, powerupActive, powerupType,powerupTimer, MaxPowerups,honeycombX[i],honeycombY[i]);
                            
                            // now we assign scores
                            if (honeycombType[i] == 0){
                              if(honeycombTier[i] == 0 || honeycombTier[i] == 1){
                                  playerScore += 1000;
                                  cout<<"a"<<endl;
                              }
                              else if (honeycombTier[i] == 2 || honeycombTier[i] == 3 || honeycombTier[i] == 4){
                                  playerScore += 800;
                                  }
                              else {
                                    playerScore += 500;
                                  }
                              
                              }
                              else {
                               //functionality for red honeycombs
                              }
                            honeycombActive[i] = false; 
                          }
                    }  
                    
                }
          }
        }
    }

        // If the hummingbird has moved to the third target, find the nearest honeycomb
        if (hummingbirdMovementCount >= 0) {

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

void drawScore(RenderWindow& window, int playerScore) {
   Font font;
   font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");

   Text scoreText;
   scoreText.setFont(font);
   scoreText.setString(to_string(playerScore));
   scoreText.setCharacterSize(24);
   scoreText.setFillColor(Color::White);
   scoreText.setPosition(resolutionX - boxPixelsX*2, (gameRows - 2)*boxPixelsY + 10); //adjusting the score position on screen
   window.draw(scoreText);
}

void drawPlayerLives(RenderWindow& window, int spraycanLives) {
    if (spraycanLives <= 0) {
        return; 
    }

    Texture playerlifeTexture;
    if (!playerlifeTexture.loadFromFile("Textures/spray.png")) {

        return;
    }
    Sprite lifeSprites[spraycanLives]; 
    for (int i = 0; i < spraycanLives - 1; i++) {
        lifeSprites[i].setTexture(playerlifeTexture);
        lifeSprites[i].setPosition(32 + (40 * i), (gameRows - 2) * boxPixelsX);
        window.draw(lifeSprites[i]);
    }
}

void readleaderboard(string leaderboard[][2], int MAX_PLAYERS) {
    ifstream inFile("leaderboard.txt");
    string name, score;
    char ch;
    int index = 0;

    if (!inFile || inFile.peek() == EOF) {
        return;
    }

    while (inFile.get(ch) && index < MAX_PLAYERS) {
        if (ch == ',') {
            leaderboard[index][0] = name;
            name = "";
        } else if (ch == '\n') {
            leaderboard[index][1] = name;
            name.clear();
            index++;
        } else {
            name += ch;
        }
    }


    inFile.close();
}



void sortleaderboard(string leaderboard[][2], int MAX_PLAYERS) {
    // Bubble sort with error handling
    for (int i = 0; i < MAX_PLAYERS - 1; i++) {
        for (int j = 0; j < MAX_PLAYERS - i - 1; j++) {

            if (leaderboard[j][0].empty() || leaderboard[j+1][0].empty()) 
                continue;
            int score1 = 0, score2 = 0;          
            for (char c : leaderboard[j][0]) {
                if (c >= '0' && c <= '9')
                    score1 = score1 * 10 + (c - '0');
            }

            for (char c : leaderboard[j+1][0]) {
                if (c >= '0' && c <= '9')
                    score2 = score2 * 10 + (c - '0');
            }
            // Swap if needed
            if (score1 < score2) {
                string tempScore = leaderboard[j][0];
                string tempName = leaderboard[j][1];
                leaderboard[j][0] = leaderboard[j+1][0];
                leaderboard[j][1] = leaderboard[j+1][1];
                leaderboard[j+1][0] = tempScore;
                leaderboard[j+1][1] = tempName;
            }
        }
  }
}


void storeleaderboard(string leaderboard[][2], int MAX_PLAYERS) {

    ofstream file("leaderboard.txt");

    if (!file.is_open()) return;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (!leaderboard[i][0].empty() && !leaderboard[i][1].empty()) {
            file << leaderboard[i][0] << "," << leaderboard[i][1] << endl;

        }

    }
    file.close();
}
///POWERUPSSSSSSS

void updatePowerUps(float player_x, float player_y, float deltaTime, float powerupCords[][2], bool powerupActive[], float powerupTimer[], int powerupType[], const int MaxPowerups, bool power[], float& speedmultiplier, float& sizemultiplier, float powerTimer[]) {
    
    const float FALLINGSPEED = 20.0f * deltaTime;
    const float POWERUP_SIZE = 32.0f;
    const float lastROW = (gameRows - 3) * boxPixelsY;
    const float TIMER_DECREMENT = 0.002f;

    // Update power-ups
    for (int i = 0; i < MaxPowerups; i++) {
        if (powerupActive[i]) {
            // Move the power-up down
            powerupCords[i][1] += FALLINGSPEED;

            // Stop it at the last row
            if (powerupCords[i][1] >= lastROW) {
                powerupCords[i][1] = lastROW;
            }

            // Decrement the power-up timer only if it has reached the last row
            if (powerupCords[i][1] >= lastROW) {
                powerupTimer[i] -= TIMER_DECREMENT;
                if (powerupTimer[i] <= 0) {
                    powerupActive[i] = false; // Deactivate the power-up if the timer expires
                }
            }

            // Check for collision with the player
            if (player_x < powerupCords[i][0] + POWERUP_SIZE && player_x + boxPixelsX > powerupCords[i][0] && player_y == powerupCords[i][1] - 32) {
                // Power-up triggered
                powerupActive[i] = false;

                // Handle power-up activation with improved cancellation logic
                switch (powerupType[i]) {
                    case 0: // Speed UP
                        if (power[1]) {
                            // Cancel out Speed DOWN
                            power[1] = false;
                            speedmultiplier = 1.0f; 
                            powerTimer[1] = 0; 
                        } else {
                            // Activate Speed UP
                            power[0] = true;
                            speedmultiplier = 2.0f;
                            powerTimer[0] = 10.0f; 
                        }
                        break;

                    case 1: // Speed DOWN
                        if (power[0]) {
                            // Cancel out Speed UP
                            power[0] = false;
                            speedmultiplier = 1.0f; 
                            powerTimer[0] = 0; 
                        } else {
                            // Activate Speed DOWN
                            power[1] = true;
                            speedmultiplier = 0.5f;
                            powerTimer[1] = 10.0f; 
                        }
                        break;

                    case 2: // Size UP
                        if (power[3]) {
                            // Cancel out Size DOWN
                            power[3] = false;
                            sizemultiplier = 1.0f; 
                            powerTimer[3] = 0; 
                        } else {
                            // Activate Size UP
                            power[2] = true;
                            sizemultiplier = 1.5f;
                            powerTimer[2] = 10.0f; 
                        }
                        break;

                    case 3: // Size DOWN
                        if (power[2]) {
                            // Cancel out Size UP
                            power[2] = false;
                            sizemultiplier = 1.0f; 
                            powerTimer[2] = 0; 
                        } else {
                            // Activate Size DOWN
                            power[3] = true;
                            sizemultiplier = 0.5f;
                            powerTimer[3] = 10.0f; 
                        }
                        break;
                }
            }
        }
    }
}
void drawPowerUps(RenderWindow& window, float powerupCords[][2], bool powerupActive[], int MaxPowerups, int powerupType[], float powerupTimer[], float powerTimer[]) {
    Texture powerUpTextures[4];
    powerUpTextures[0].loadFromFile("Sprites/Speed_inc.png");
    powerUpTextures[1].loadFromFile("Sprites/Speed_dec.png");
    powerUpTextures[2].loadFromFile("Sprites/Height_inc.png");
    powerUpTextures[3].loadFromFile("Sprites/Height_dec.png");
        Color powerUpTimerColors[4] = {
        Color::Green,   // Timer 1 
        Color::Red,     // Timer 2
        Color::Blue,    // Timer 3
        Color::Yellow   // Timer 4
    };
    //power up sprites over here
    Sprite powerUpSprites[4];
    for (int i = 0; i < 4; i++) {
        powerUpSprites[i].setTexture(powerUpTextures[i]);
    }
    //timer above the sprites
    for (int i = 0; i < MaxPowerups; i++) {
        if (powerupActive[i]) {
            powerUpSprites[powerupType[i]].setPosition(powerupCords[i][0], powerupCords[i][1]);
            window.draw(powerUpSprites[powerupType[i]]);

            // draw the rectangle for timer
            IntRect timerRect(powerupCords[i][0], powerupCords[i][1] - 15,powerupTimer[i] * 5, 5);

            RectangleShape timerShape(Vector2f(timerRect.width, timerRect.height));
            timerShape.setPosition(timerRect.left- 7, timerRect.top);
            timerShape.setFillColor(Color::Green);
            window.draw(timerShape);
        }
    }
  //timer when power up is picked up 


    IntRect powerUpTimerRects[4] = {
        IntRect(100, 50, powerTimer[0] * 10, 10),   // Timer 1
        IntRect(100, 50, powerTimer[1] * 10, 10),   // Timer 2
        IntRect(100, 70, powerTimer[2] * 10, 10),   // Timer 3
        IntRect(100, 70, powerTimer[3] * 10, 10)    // Timer 4
    };

    for (int i = 0; i < 4; i++) {
        RectangleShape PtimerShape(Vector2f(powerUpTimerRects[i].width, powerUpTimerRects[i].height));
        PtimerShape.setPosition(powerUpTimerRects[i].left, powerUpTimerRects[i].top);
        PtimerShape.setFillColor(powerUpTimerColors[i]);
        window.draw(PtimerShape);
    }
}


void generatePowerUp(float powerupCords[][2], bool powerupActive[], int powerupType[], float powerupTimer[], int MaxPowerups,float honeycombX, float honeycombY) {
    for (int j = 0; j < MaxPowerups; j++) {
        if (!powerupActive[j]) {
            powerupType[j] = rand() % 4;
            powerupCords[j][0] = honeycombX;
            powerupCords[j][1] = honeycombY;
            powerupActive[j] = true;
            powerupTimer[j] = 10.0f; // 10 seconds duration
            break;
        }
    }
}
void powerHandler(float powerTimer[], bool power[], float& sizemultiplier, float& speedmultiplier) {
  
  
  //over here what we do is disable opposing power ups
    if (power[0] && power[1]) {
        power[0] = false;
        power[1] = false;
        speedmultiplier = 1.0f;
        powerTimer[0] = 0;
        powerTimer[1] = 0;
    }
    if (power[2] && power[3]) {
       power[2] = false;
        power[3] = false;
        sizemultiplier = 1.0f;
        powerTimer[2] = 0;
        powerTimer[3] = 0;
    }
    //timer decrement and when it reaches zero disable everything
    for (int i = 0; i < 4; i++) {
        if (powerTimer[i] > 0) {
            powerTimer[i] -= 0.002f;
        } else {
            powerTimer[i] = 0;
      
            switch(i) {
                case 0: // Speed UP
                    if (power[0]) {
                        power[0] = false;
                        speedmultiplier = 1.0f;
                    }
                    break;
                case 1: // Speed DOWN
                    if (power[1]) {
                        power[1] = false;
                        speedmultiplier = 1.0f;
                    }
                    break;
                case 2: // Size UP
                    if (power[2]) {
                        power[2] = false;
                        sizemultiplier = 1.0f;
                    }
                    break;
                case 3: // Size DOWN
                    if (power[3]) {
                        power[3] = false;
                        sizemultiplier = 1.0f;
                    }
                    break;
          }
      }
    }
}





// Global pointers for infant bee management
float* infantBeesX = nullptr;       // Dynamic array of X coordinates
float* infantBeesY = nullptr;        // Dynamic array of Y coordinates
bool* infantBeesActive = nullptr;    // Dynamic array of active states
int* infantBeeTimer = nullptr;       // Dynamic array of individual timers
int maxInfantBees = 0;               // Current maximum capacity
int currentInfantBeeCount = 0;       // Current number of infant bees

// Initialize infant bee arrays
void initializeInfantBees(int initialCapacity) {
    // Allocate initial arrays
    maxInfantBees = initialCapacity;
    
    // Allocate dynamic arrays
    infantBeesX = new float[maxInfantBees];
    infantBeesY = new float[maxInfantBees];
    infantBeesActive = new bool[maxInfantBees];
    infantBeeTimer = new int[maxInfantBees];
    
    // Initialize all to default values
    for (int i = 0; i < maxInfantBees; ++i) {
        infantBeesX[i] = 0.0f;
        infantBeesY[i] = 0.0f;
        infantBeesActive[i] = false;
        infantBeeTimer[i] = 0;
    }
}

// Dynamically expand infant bee arrays
void expandInfantBeeArrays() {
    // Calculate new capacity (double the current)
    int newCapacity = maxInfantBees * 2;
    
    // Create temporary arrays
    float* tempX = new float[newCapacity];
    float* tempY = new float[newCapacity];
    bool* tempActive = new bool[newCapacity];
    int* tempTimer = new int[newCapacity];
    
    // Copy existing data
    for (int i = 0; i < maxInfantBees; ++i) {
        tempX[i] = infantBeesX[i];
        tempY[i] = infantBeesY[i];
        tempActive[i] = infantBeesActive[i];
        tempTimer[i] = infantBeeTimer[i];
    }
    
    // Initialize new slots
    for (int i = maxInfantBees; i < newCapacity; ++i) {
        tempX[i] = 0.0f;
        tempY[i] = 0.0f;
        tempActive[i] = false;
        tempTimer[i] = 0;
    }
    
    // Free old arrays
    delete[] infantBeesX;
    delete[] infantBeesY;
    delete[] infantBeesActive;
    delete[] infantBeeTimer;
    
    // Update pointers
    infantBeesX = tempX;
    infantBeesY = tempY;
    infantBeesActive = tempActive;
    infantBeeTimer = tempTimer;
    
    // Update capacity
    maxInfantBees = newCapacity;
}

// Add a new infant bee
void addInfantBee(float x, float y) {
    // Check if we need to expand arrays
    if (currentInfantBeeCount >= maxInfantBees) {
        expandInfantBeeArrays();
    }
    
    // Find first inactive slot
    int index = -1;
    for (int i = 0; i < maxInfantBees; ++i) {
        if (!infantBeesActive[i]) {
            index = i;
            break;
        }
    }
    
    // If no inactive slot found, return
    if (index == -1) return;
    
    // Add infant bee
    infantBeesX[index] = x;
    infantBeesY[index] = y;
    infantBeesActive[index] = true;
    infantBeeTimer[index] = 0;
    
    // Increment bee count
    currentInfantBeeCount++;
}

// Move infant bees
void moveInfantBees(
    float deltaTime, 
    float honeycombX[], 
    float honeycombY[], 
    bool honeycombActive[], 
    int MAX_HONEYCOMBS
) {
    const float INFANT_BEE_SPEED = 50.0f;
    
    for (int i = 0; i < maxInfantBees; ++i) {
        // Only move active infant bees
        if (infantBeesActive[i]) {
            // Move upward
            infantBeesY[i] -= INFANT_BEE_SPEED * deltaTime;
            
            // Collision detection
            bool blocked = false;
            for (int j = 0; j < MAX_HONEYCOMBS; ++j) {
                if (honeycombActive[j]) {
                    // Simple collision check
                    if (abs(infantBeesX[i] - honeycombX[j]) < 32 && 
                        abs(infantBeesY[i] - honeycombY[j]) < 32) {
                        blocked = true;
                        
                        // Move left or right
                        if (infantBeesX[i] > honeycombX[j]) {
                            infantBeesX[i] -= INFANT_BEE_SPEED * deltaTime;
                        } else {
                            infantBeesX[i] += INFANT_BEE_SPEED * deltaTime;
                        }
                        break;
                    }
                }
            }
            
            // Optional: Add transformation logic here
        }
    }
}

// Spawn infant bees
void spawnInfantBees(
    float beehiveCord[][2], 
    bool beehiveActive[], 
    int MAX_BEEHIVES, 
    float& globalSpawnTimer, 
    float deltaTime
) {
    const float SPAWN_INTERVAL = 4.0f;
    globalSpawnTimer += deltaTime;
    
    if (globalSpawnTimer >= SPAWN_INTERVAL) {
        // Find an active beehive
        for (int i = 0; i < MAX_BEEHIVES; ++i) {
            if (beehiveActive[i]) {
                // Spawn at beehive location
                addInfantBee(beehiveCord[i][0], beehiveCord[i][1]+32);
                globalSpawnTimer = 0.0f;
                break;
            }
        }
    }
}

// Cleanup function
void cleanupInfantBees() {
    // Free all dynamically allocated memory
    delete[] infantBeesX;
    delete[] infantBeesY;
    delete[] infantBeesActive;
    delete[] infantBeeTimer;
    
    // Reset pointers and counts
    infantBeesX = nullptr;
    infantBeesY = nullptr;
    infantBeesActive = nullptr;
    infantBeeTimer = nullptr;
    maxInfantBees = 0;
    currentInfantBeeCount = 0;
}

void drawInfantBee(RenderWindow& window) {
    static Texture beeTexture;
    static bool isTextureLoaded = false;
    static int currentFrame = 0;


for (int index = 0; index < maxInfantBees; index++){
    if (infantBeesActive[index]) {
        // Load the bee texture
        if (!isTextureLoaded) {
            if (!beeTexture.loadFromFile("Sprites/BeeSheet.png")) {
                return;
            }
            isTextureLoaded = true;
        }

        Sprite beeSprite;
        beeSprite.setTexture(beeTexture);

        // Define the 5 frames for the infant bee animation
        IntRect frames[] = {
            IntRect(0, 0, 32, 32),  // Frame 1
            IntRect(32, 0, 32, 32),  // Frame 2
            IntRect(64, 0, 32, 32),  // Frame 3
            IntRect(96, 0, 32, 32),  // Frame 4
            IntRect(128, 0, 32, 32)  // Frame 5
        };

        // Update the current frame and set the sprite's texture rect
        currentFrame = (currentFrame + 1) % 5;
        beeSprite.setTextureRect(frames[currentFrame]);

        // Set position and draw
        beeSprite.setPosition(infantBeesX[index], infantBeesY[index]);
        window.draw(beeSprite);
    }
}
}
