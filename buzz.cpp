
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;
using namespace sf;


//TODO:   IMPLEMENT:
//        TEST THE GAME
//         time left = 3 hrs!!
//TODO: GO THROUGH THE CODE AND REFINE IT,  CODE REFACTORING, BREAKING DOWN LOGIC INTO SMALLER FUNCTIONS
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
void movePlayer(float& player_x, float player_y, int boundaryLeft,  int boundaryRight,  float speed, int flowerCord[][2], int flowerActive[], const int flowers_Max, bool& resetCall, int& spraycanLives, bool& menu_State);
void fireBullet(float& bullet_x, float& bullet_y, bool& bullet_exists, float player_x, float player_y, int& sprays, int& spraycanState, int& spraycanLives, bool& gameEnd_State, bool& resetCall);
void beesGenerator(float beesX[], float beesY[], int beeTypes[], bool beesActive[], int beesTier[], bool beesDirection[], int bees_Max, int WORKER_BEE, int currentgameLevel, int& beeCount, bool resetCall, int& regularbeeCount, Clock& hunterBeeClock, int& hunterbeeCount, Clock& beeClock);


void moveBees(float beesX[], float beesY[], int beesTier[], bool beesDirection[], int beeTypes[], bool beesActive[], int bees_Max, float deltaTime, int WORKER_BEE, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int honeycombs_Max,int flowerCord[][2], int flowerActive[], const int flowers_Max,float beehiveCord[][2], bool beehiveActive[], int beehives_Max,bool& firstbeeLEFT, bool& firstbeeRIGHT, int beehiveTier[], bool beePlantedFlower[]);


void drawBees(RenderWindow& window);
bool checkBeeCollision(float bullet_x, float bullet_y, float beesX[], float beesY[], int beeTypes[], bool beesActive[], int beesTier[], bool beesDirection[], int bees_Max, int WORKER_BEE, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int honeycombs_Max, int& playerScore, int honeycombTier[]);
void drawBees(RenderWindow& window, float beesX[], float beesY[], int beeTypes[], bool beesActive[], int beesTier[], bool beesDirection[], int bees_Max, int WORKER_BEE);
void drawHoneycombs(RenderWindow& window, 
                    float honeycombX[], float honeycombY[], 
                    int honeycombType[], bool honeycombActive[], int honeycombs_Max);             
void generateHoneycomb(float bee_x, float bee_y, int beeType, 
                       float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int honeycombs_Max, int beeTier, int honeycombTier[]);
bool checkHoneyCombCollision(float bullet_x, float bullet_y, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int honeycombs_Max,float powerupCords[][2], bool powerupActive[], int powerupType[], float powerupTimer[], int powerups_Max, int currentLevel);
void drawFlowers(RenderWindow& window, int flowerCord[][2], int flowerActive[], const int flowers_Max );
bool flowerGenerator(float beeX, float beeY, int flowerCord[][2], int flowerActive[], const int flowers_Max, bool& firstbeeLEFT, bool& firstbeeRIGHT, bool& beePlantedFlower);
void generateHummingbird(float deltatime,float& hummingbirdX, float& hummingbirdY, bool& hummingbirdActive, float honeycombX[], float honeycombY[], bool honeycombActive[], int honeycombs_Max, bool& isBirdSick, Clock& sickClock, bool& isFlyingToEdge, int& playerScore, int honeycombTier[], int honeycombType[], Clock& hummingbirdClock,const int powerups_Max,float powerupCords[][2],bool powerupActive[],float powerupTimer[],int powerupType[], Clock& pauseClock, int currentLevel);
void drawHummingbird(RenderWindow& window, float hummingbirdX, float hummingbirdY, bool isBirdSick, bool hummingbirdActive);
bool checkBirdCollision(float& hummingbirdX, float& hummingbirdY, 
                        float bulletX, float bulletY,
                        bool& hummingbirdActive, bool& isBirdSick, 
                        int& collidedBulletCount, Clock& sickClock, bool& isFlyingToEdge);
void generateBeeHive(float beeX, float beeY, int bees_Max, float beehiveCord[][2], bool beehiveActive[], int beehives_Max, int beehiveTier[], int beeTier);
void drawBeeHive(RenderWindow& window, float beehiveCord[][2], bool beehiveActive[], int beehives_Max );
bool checkBeeHiveCollision(float bullet_x, float bullet_y, float beehiveCord[][2], bool beehiveActive[], int beehives_Max);
void awardCans(int& spraycanLives, int playerScore);


void resetGame(float& player_x, float& player_y,  float& bullet_x, float& bullet_y,  bool& bullet_exists, int& playerScore,int bees_Max,  float beesX[], float beesY[],  int beeTypes[],  bool beesActive[],  int beesTier[], bool beesDirection[], int& beeCount,int& regularbeeCount,int& hunterBeeCount,bool& firstbeeLEFT, bool& firstbeeRIGHT,int honeycombs_Max, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[],int flowers_Max, int flowerCord[][2], int flowerActive[],int beehives_Max, float beehiveCord[][2], bool beehiveActive[],float& hummingbirdX, float& hummingbirdY, bool& hummingbirdActive, bool& isBirdSick, bool& isFlyingToEdge,Clock& pauseClock,int& currentLevel,int& sprays, int& spraycanLives, int& spraycanState,Clock& hunterBeeClock, Clock& beeClock, Clock& hummingbirdClock,bool power[], float powerTimer[],float& speedmultiplier, float& sizemultiplier,bool& pre_generated,bool& hive_pregenerated,bool beePlantedFlower[]);



void resetLevel(bool& resetCall, int& spraycanLives, bool& menu_State);
void honeycombPreGenerator(float honeycombX[], float honeycombY[], bool honeycombActive[], int honeycombType[], int MAX_HONEYCOMB, int currentLevel, int honeycombTier[], float beehiveCord[][2], bool beehiveActive[], int beehives_Max, bool& generated, bool& hivegenerated);
void callGameEnd( bool& gameEnd_State, bool& resetCall);
void detectBees(int& beeCount, bool beeActive[], bool& gameEnd_State, bool& resetCall, int bees_Max, bool& inLevelSwitch, int& sprays, int& currentLevel,Clock& levelSwitchClock, float beehiveCord[][2], bool beehiveActive[], int beehiveTier[], int beehives_Max, int& playerScore);
void drawScore(RenderWindow& window, int playerScore);
void drawPlayerLives(RenderWindow& window, int spraycanLives);
void sortleaderboard(char leaderboard_names[][50], int leaderboard_scores[], int ld_Positions);
void storeleaderboard(char leaderboard_names[][50], int leaderboard_scores[], int ld_Positions);
void readleaderboard(char leaderboard_names[][50], int leaderboard_scores[], int ld_Positions);

void checkSprayCanLives(int& spraycanLives, bool& gameEnd_State, bool& resetCall);
void generatePowerUp(float powerupCords[][2], bool powerupActive[], int powerupType[], float powerupTimer[], int powerups_Max,float honeycombX, float honeycombY);
void updatePowerUps(float player_x, float player_y, float deltaTime, float powerupCords[][2],bool powerupActive[],float powerupTimer[],int powerupType[], const int powerups_Max, bool power[],    float& speedmultiplier,float& sizemultiplier, float powerTimer[]);
void drawPowerUps(RenderWindow& window, float powerupCords[][2], bool powerupActive[], int powerups_Max, int powerupType[], float powerupTimer[], float powerTimer[]);
void powerHandler(float powerTimer[], bool power[], float& sizemultiplier, float& speedmultiplier);
void beehivescore_handler(int& playerScore, float beehiveCord[][2], bool beehiveActive[], int beehiveTier[], int beehives_Max);
void nextLevel(bool& resetCall, int& sprays, bool& inLevelSwitch, int& currentLevel, bool& gameEnd_State);
int stringToInt(string str);
///infant bee////

void initializeinfantBee_arrays(float**& infantBeeCordinates, bool*& infantBeesActive, int maxInfantBees);
void cleanupInfantBees(float**& infantBeeCordinates, bool*& infantBeesActive,  int maxInfantBees);
void infantbee_spawner(float**& infantBeeCordinates, bool*& infantBeesActive,  float beehiveCord[][2], bool beehiveActive[], int beehives_Max, float beehiveCooldownTimers[], bool beehiveCanSpawn[], float deltaTime, Clock& globalSpawnTimer, int& maxInfantBees);
void update_infantBees(float deltaTime, float honeycombX[], float honeycombY[], bool honeycombActive[], int honeycombs_Max, float**& infantBeeCordinates, bool*& infantBeesActive, int maxInfantBees,bool beesActive[], int beesTier[], bool beesDirection[], int bees_Max, int beeTypes[], float beesX[], float beesY[], float beehiveCord[][2], int beehives_Max, bool beehiveActive[], int beehiveTier[]);
void addInfantBee(float x, float y, float**& infantBeeCordinates, bool*& infantBeesActive, int& maxInfantBees);
void expandInfantBeeArrays(float**& infantBeeCordinates, bool*& infantBeesActive,  int& maxInfantBees) ;
void drawInfantBee(RenderWindow& windo, float**& infantBeeCordinates, bool*& infantBeesActive, int maxInfantBees);
void generate_hunterbee(float infantBeeX, float infantBeeY,  int bees_Max, bool beesActive[], bool beesDirection[], int beesTier[], int beeTypes[], float beesX[], float beesY[]); 
bool checkInfantBeeCollision(float**& infantBeeCordinates, bool*& infantBeesActive, float bulletX, float bulletY, int& maxInfantBees, int& playerScore);

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// Write your functions declarations here. Some have been written for you. //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////


int main(){
        srand(static_cast<unsigned int>(time(0)));
	// Declaring RenderWindow.
	RenderWindow window(VideoMode(resolutionX, resolutionY), "Buzz Bombers", Style::Close | Style::Titlebar);

	// Used to position your window on every launch. Use according to your needs.
	window.setPosition(Vector2i(300, 150));

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
          Text level4Text("BOSS LEVEL", menuFont, 30);
          level4Text.setFillColor(Color::Red);
          level4Text.setPosition(resolutionX/2 - level3Text.getLocalBounds().width/2 - 30, 320);
          Text exitText("Exit", menuFont, 30);
          exitText.setFillColor(Color::White);
          exitText.setPosition(resolutionX/2 - exitText.getLocalBounds().width/2, 390);
          
          
  /////////////////////////GAME END///////////////////////////
   

      Text endGameText;
      Text namePromptText;
      Text nameInputText;
      RectangleShape nameInputBox;
      bool isNameInputActive = false;
      const int MAX_NAME_LENGTH = 20;
      char playerName[MAX_NAME_LENGTH + 1] = {0}; // +1 for null terminator
      int  nameLength = 0;
      RectangleShape enterButton;
      Text enterButtonText;
          
      enterButton.setSize(Vector2f(100, 50)); 
      enterButton.setFillColor(Color::Green);
      enterButton.setPosition(resolutionX/2-50, 420);

        enterButtonText.setString("Enter");
        enterButtonText.setCharacterSize(24);
        enterButtonText.setFillColor(Color::White);
        enterButtonText.setPosition(resolutionX/2, 400);
      
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
    float nameInputBoxX = nameInputBox.getPosition().x;
    float nameInputBoxY = nameInputBox.getPosition().y;
    float nameInputBoxWidth = nameInputBox.getLocalBounds().width;
    float nameInputBoxHeight = nameInputBox.getLocalBounds().height;

    float enterButtonX = enterButton.getPosition().x;
    float enterButtonY = enterButton.getPosition().y;
    float enterButtonWidth = enterButton.getLocalBounds().width;
    float enterButtonHeight = enterButton.getLocalBounds().height;
    
    /////////////////////////////////////////////////////////////////

	// Initializing Player and Player Sprites.
	bool running = false;
	float player_x = (gameColumns / 2) * boxPixelsX;
	float player_y = (gameRows - 4) * boxPixelsY;
	int playerScore = 0;
        const int players_MAX = 100;
        const int ld_Positions = 5;
        char leaderboard_names[ld_Positions][50] = {};
        int leaderboard_scores[ld_Positions] = {0};
        readleaderboard(leaderboard_names, leaderboard_scores,ld_Positions);
        sortleaderboard( leaderboard_names, leaderboard_scores, ld_Positions);
        
        
        


	


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
        int bees_Max= 50;
        int WORKER_BEE = 0;
        int KILLER_BEE = 1;
        int beeCount = 0;
        Clock beeClock;
        int regularbeeCount = 0;
        Clock hunterBeeClock;
         int hunterBeeCount = 0;
        // Bee Arrays
        float beesX[bees_Max];
        float beesY[bees_Max];
        int beeTypes[bees_Max] = {0};
        bool beesActive[bees_Max] = {0};
        int beesTier[bees_Max];
        bool beesDirection[bees_Max]; // true = right, false = left
        bool beePlantedFlower[bees_Max] = {0};
        Clock movementClock;
        
        //HONEYCOMBSSS
        const int honeycombs_Max = 100;
        float honeycombX[honeycombs_Max];
        float honeycombY[honeycombs_Max];
        int honeycombType[honeycombs_Max];
        bool honeycombActive[honeycombs_Max] = {0};
        int honeycombTier[honeycombs_Max] = {0};
        bool pre_generated = false;
        bool hive_pregenerated = false;
        //flowers
        const int flowers_Max = 100;
        int flowerCord[flowers_Max][2] = {0};
        int flowerActive[flowers_Max] = {0};
        bool firstbeeLEFT = false;
        bool firstbeeRIGHT = false;
        
        //hummingbird
        float hummingbirdX = -100; 
        float hummingbirdY = -100; 
        bool hummingbirdActive = false;
        bool isBirdSick = false;
        Clock sickClock;
        int collidedBulletCount = 0;
        bool isFlyingToEdge;
        Clock hummingbirdClock;
        Clock pauseClock;
        
        //BEE HIVE 
       int beehives_Max = 100;
       float beehiveCord[beehives_Max][2] = {0};
       bool beehiveActive[beehives_Max] = {0};
       float beehiveCooldownTimers[beehives_Max] = {5.0f};
        for (int i = 0; i < beehives_Max; ++i) {
          beehiveCooldownTimers[i] = 0;
        }
       bool beehiveCanSpawn[beehives_Max];
       for (int i = 0; i < beehives_Max; ++i) {
          beehiveCanSpawn[i] = true;
        }
        int beehiveTier[beehives_Max] = {0};
     
        
      //spray can
      int sprays = 0;
      int spraycanLives =3;
      int spraycanState = 0;
      
      //POWER UPS
      const int powerups_Max = 100;
      float powerupCords[powerups_Max][2] ={0};
      bool powerupActive[powerups_Max] = {0};
      float powerupTimer[powerups_Max] = {0};
      int powerupType[powerups_Max] = {0};
      bool power[4] ={0};
      float speedmultiplier = 1.0f;
      float sizemultiplier = 1.0f;
      float powerTimer[4] = {0}; //4 power ups timers
      
      //INFANT BEE
      bool* infantBeesActive = nullptr;       
      int maxInfantBees = 1;              
      float **infantBeeCordinates = nullptr;
      Clock globalSpawnTimer;

        
        // game states
        int currentLevel = 1;
        bool resetCall = false;
        bool exit = false;
        bool leaderboard_State = false; 
        bool levelSwitch_State = false;
        Clock levelSwitchClock;
        const float levelswitch_Duration = 5.0f;
        bool gameEnd_State = false;
        bool menu_State = true;
         


     


        initializeinfantBee_arrays(infantBeeCordinates,  infantBeesActive, maxInfantBees);
          
	while (window.isOpen() && exit == false) {
        float deltaTime = movementClock.restart().asSeconds(); //gets the time between each frame reload (every run of thegame loop)
        
        /*over here we have our game states that dynamically switch based on game input*/
              if (gameEnd_State) {
                  Event endEvent;
                  while (window.pollEvent(endEvent)) {
                      if (endEvent.type == Event::Closed) 
                          return 0;

                      if (endEvent.type == Event::MouseButtonPressed) {
                          Vector2i mousePos = Mouse::getPosition(window);
                          
                          if (mousePos.x >= nameInputBoxX && mousePos.x <= nameInputBoxX + nameInputBoxWidth &&
                              mousePos.y >= nameInputBoxY && mousePos.y <= nameInputBoxY + nameInputBoxHeight) {
                              isNameInputActive = true;
                              nameInputBox.setOutlineColor(Color::Green);
                          } else {
                              isNameInputActive = false;
                              nameInputBox.setOutlineColor(Color::White);
                          }
                          
                        if (mousePos.x >= enterButtonX && mousePos.x <= enterButtonX + enterButtonWidth &&
                           mousePos.y >= enterButtonY && mousePos.y <= enterButtonY + enterButtonHeight && nameLength != 0) {
                           // once user clicks the enter button the name is added to the leaderboard array, we find the free index and then assign the char array to the leadderboard array
                           int freeIndex = -1;
                           for (int i = 0; i < players_MAX; i++) {
                               if (leaderboard_names[i][0] == 0) {
                                   freeIndex = i;
                                   break;
                               }
                           }

                           if (freeIndex == -1) {
                               int lowestIndex = 0;
                               for (int i = 1; i < players_MAX; i++) {
                                   if (leaderboard_scores[i] < leaderboard_scores[lowestIndex]) {
                                       lowestIndex = i;
                                   }
                               }

                               if (playerScore > leaderboard_scores[lowestIndex]) {
                                   for (int i = 0; i < 50; i++) {
                                       leaderboard_names[lowestIndex][i] = 0;
                                   }

                                   for (int i = 0; i < 50 && playerName[i] != 0; i++) {
                                       leaderboard_names[lowestIndex][i] = playerName[i];
                                   }
                                   leaderboard_names[lowestIndex][49] = 0;
                                   leaderboard_scores[lowestIndex] = playerScore;
                                   gameEnd_State = false;
                                   leaderboard_State = true;
                               }
                           } else {
                               for (int i = 0; i < 50 && playerName[i] != 0; i++) {
                                   leaderboard_names[freeIndex][i] = playerName[i];
                               }
                               leaderboard_names[freeIndex][49] = 0;
                               leaderboard_scores[freeIndex] = playerScore;
                               gameEnd_State = false;
                               leaderboard_State = true;
                           }
                        }
                      }
                      
                      if (isNameInputActive && endEvent.type == Event::TextEntered) {
                          if (endEvent.text.unicode == '\b') {
                              if (nameLength > 0) {
                                  playerName[--nameLength] = '\0';
                              }
                          }
                          else if (isprint(endEvent.text.unicode) && nameLength < MAX_NAME_LENGTH) {
                              playerName[nameLength++] = static_cast<char>(endEvent.text.unicode);
                              playerName[nameLength] = '\0';
                          }
                          nameInputText.setString(playerName);
                      }
                  }
                  
                  window.clear(Color::Black);
                  window.draw(endGameText);
                  window.draw(namePromptText);
                  window.draw(nameInputBox);
                  window.draw(nameInputText);
                  window.draw(enterButtonText);
                  window.draw(enterButton);
                  window.display();
              }

            else if (leaderboard_State) {
                Event leaderboardEvent;
                while (window.pollEvent(leaderboardEvent)) {
                    if (leaderboardEvent.type == Event::Closed)
                        return 0;
                    
                    if (leaderboardEvent.type == Event::MouseButtonPressed) {
                        Vector2i mousePos = Mouse::getPosition(window);
  
                        int exitButtonX = 50;
                        int exitButtonY = window.getSize().y - 100;
                        int exitButtonWidth = 100;
                        int exitButtonHeight = 50;
                        
                      //this one button is responsible for storing in the leaderboard when player exits
                        if (mousePos.x >= exitButtonX && mousePos.x <= exitButtonX + exitButtonWidth &&
                            mousePos.y >= exitButtonY && mousePos.y <= exitButtonY + exitButtonHeight) {
                            leaderboard_State = false;
                            storeleaderboard( leaderboard_names, leaderboard_scores, ld_Positions);
                             playerName[0] = '\0';
                             nameLength = 0;
                            exit = true;
                        }
                    }
                }
                
                window.clear(Color::Black);
                
                
                Text currentPlayerText;
                currentPlayerText.setFont(menuFont);
                currentPlayerText.setCharacterSize(24);
                currentPlayerText.setString("Current Player: " + string(playerName));
                currentPlayerText.setPosition(50, 50);
                window.draw(currentPlayerText);
                
                
                Text currentScoreText;
                currentScoreText.setFont(menuFont);
                currentScoreText.setCharacterSize(24);
                currentScoreText.setString("Current Score: " + to_string(playerScore));
                currentScoreText.setPosition(50, 100);
                window.draw(currentScoreText);
                
                
                Text leaderboardTitle;
                leaderboardTitle.setFont(menuFont);
                leaderboardTitle.setCharacterSize(30);
                leaderboardTitle.setString("Leaderboard");
                leaderboardTitle.setPosition(50, 150);
                window.draw(leaderboardTitle);
                
                
                Text entryText;
                Text entry2Text;
                entryText.setFont(menuFont);
                entryText.setCharacterSize(20);
                entry2Text.setFont(menuFont);
                entry2Text.setCharacterSize(20);
                
                for (int i = 0; i < ld_Positions; i++) {
                    entryText.setString(to_string(i+1) + ". " + leaderboard_names[i]);
                    entryText.setPosition(50, 200 + i * 30);
                    window.draw(entryText);
                    entry2Text.setString( "Score: " + to_string(leaderboard_scores[i]));
                    entry2Text.setPosition(200, 200 + i * 30);
                    window.draw(entry2Text);
                }

                
                RectangleShape exitButton;
                exitButton.setPosition(50, window.getSize().y - 100);
                exitButton.setSize(Vector2f(100, 50));
                exitButton.setFillColor(Color::Black);
                exitButton.setOutlineColor(Color::Red);
                exitButton.setOutlineThickness(2);
                window.draw(exitButton);
                
                Text exitText;
                exitText.setFont(menuFont);
                exitText.setCharacterSize(20);
                exitText.setString("EXIT");
                exitText.setFillColor(Color::Red);
                exitText.setPosition(70, window.getSize().y - 90);
                window.draw(exitText);
                
                window.display();
            }else if (menu_State) {
                  Event menuEvent;
                  while (window.pollEvent(menuEvent)) {
                      if (menuEvent.type == Event::Closed)
                          return 0;
                      
                      if (menuEvent.type == Event::MouseButtonPressed) {
                          Vector2i mousePos = Mouse::getPosition(window);
                        
                          if (mousePos.x >= level1Text.getPosition().x && 
                              mousePos.x <= level1Text.getPosition().x + level1Text.getLocalBounds().width &&
                              mousePos.y >= level1Text.getPosition().y && 
                              mousePos.y <= level1Text.getPosition().y + level1Text.getLocalBounds().height) {
                              currentLevel = 1;
                               level1Text.setOutlineColor(Color::Green);
                              menu_State = false;
                          }
                          

                          if (mousePos.x >= level2Text.getPosition().x && 
                              mousePos.x <= level2Text.getPosition().x + level2Text.getLocalBounds().width &&
                              mousePos.y >= level2Text.getPosition().y && 
                              mousePos.y <= level2Text.getPosition().y + level2Text.getLocalBounds().height) {
                              currentLevel = 2;
                              menu_State = false;
                              
                          }

                          if (mousePos.x >= level3Text.getPosition().x && 
                              mousePos.x <= level3Text.getPosition().x + level3Text.getLocalBounds().width &&
                              mousePos.y >= level3Text.getPosition().y && 
                              mousePos.y <= level3Text.getPosition().y + level3Text.getLocalBounds().height) {
                              currentLevel = 3;
                              menu_State = false;
                          }
                          if (mousePos.x >= level4Text.getPosition().x && 
                              mousePos.x <= level4Text.getPosition().x + level4Text.getLocalBounds().width &&
                              mousePos.y >= level4Text.getPosition().y && 
                              mousePos.y <= level4Text.getPosition().y + level4Text.getLocalBounds().height) {
                              currentLevel = 4;
                              menu_State = false;
                          }
                          if (mousePos.x >= exitText.getPosition().x && 
                              mousePos.x <= exitText.getPosition().x + exitText.getLocalBounds().width &&
                              mousePos.y >= exitText.getPosition().y && 
                              mousePos.y <= exitText.getPosition().y + exitText.getLocalBounds().height) {
                              return 0; 
                          }
                      }
                  }

                  window.clear(Color::Black);
                  window.draw(titleText);
                  window.draw(level1Text);
                  window.draw(level2Text);
                  window.draw(level3Text);
                  window.draw(level4Text);
                  window.draw(exitText);
                  window.display();
                  
              }else if (levelSwitch_State) {
                  
                Event levelSwitchEvent;
                while (window.pollEvent(levelSwitchEvent)) {
                    if (levelSwitchEvent.type == Event::Closed)
                        return 0;
                }

                  window.clear(Color::Black);

                  Text levelText;
                  levelText.setFont(menuFont);
                  levelText.setCharacterSize(50);
                  levelText.setFillColor(Color::White);
                  
                  levelText.setString("Level " + to_string(currentLevel));
                  
                  FloatRect textBounds = levelText.getLocalBounds();
                  levelText.setOrigin(textBounds.left + textBounds.width/2.0f, 
                                      textBounds.top + textBounds.height/2.0f);
                  levelText.setPosition(window.getSize().x / 2.0f,window.getSize().y / 2.0f);

                  window.draw(levelText);
                  window.display();

                  if (levelSwitchClock.getElapsedTime().asSeconds() >= levelswitch_Duration) {
                      levelSwitch_State = false;
                  }
              }    
      
          else{
            ///////////////////START OF GAME////////////////////////
              Event gameEvent;
              while (window.pollEvent(gameEvent)) {
                  if (gameEvent.type == Event::Closed) 
                      return 0;
              }
            
          if (resetCall) {
             resetGame(
              player_x, player_y,
              bullet_x, bullet_y, bullet_exists, playerScore,
              bees_Max, beesX, beesY, beeTypes, beesActive, beesTier, beesDirection,
              beeCount, regularbeeCount, hunterBeeCount, 
              firstbeeLEFT, firstbeeRIGHT,
              honeycombs_Max, honeycombX, honeycombY, honeycombType, honeycombActive,
              flowers_Max, flowerCord, flowerActive,
              beehives_Max, beehiveCord, beehiveActive,
              hummingbirdX, hummingbirdY, hummingbirdActive, 
              isBirdSick, isFlyingToEdge,pauseClock,
              currentLevel, sprays, spraycanLives, spraycanState,
              hunterBeeClock, beeClock, hummingbirdClock,
              power, powerTimer, speedmultiplier, sizemultiplier, pre_generated, hive_pregenerated, beePlantedFlower
          );
              resetCall = !resetCall;
          }
            
            
  
		///////////////////////////////////////////////////////////////
		//                                                           //
		// Call Your Functions Here. Some have been written for you. //
		// Be vary of the order you call them, SFML draws in order.  //
		//                                                           //
		///////////////////////////////////////////////////////////////
		  if (currentLevel == 4){
                infantbee_spawner(infantBeeCordinates, infantBeesActive,  beehiveCord, beehiveActive, beehives_Max,  beehiveCooldownTimers, beehiveCanSpawn, deltaTime, globalSpawnTimer, maxInfantBees);
                update_infantBees(deltaTime,honeycombX, honeycombY,  honeycombActive,honeycombs_Max, infantBeeCordinates,  infantBeesActive,  maxInfantBees, beesActive, beesTier,  beesDirection,bees_Max,  beeTypes,  beesX,  beesY, beehiveCord, beehives_Max, beehiveActive, beehiveTier);
                  }
		powerHandler(powerTimer, power, sizemultiplier, speedmultiplier);
                updatePowerUps(player_x, player_y,deltaTime, powerupCords,powerupActive,powerupTimer,powerupType, powerups_Max, power, speedmultiplier, sizemultiplier, powerTimer);
                honeycombPreGenerator(honeycombX, honeycombY, honeycombActive, honeycombType, honeycombs_Max, currentLevel, honeycombTier, beehiveCord, beehiveActive, beehives_Max, pre_generated, hive_pregenerated);
                beesGenerator(beesX, beesY ,beeTypes, beesActive, beesTier, beesDirection, bees_Max, WORKER_BEE, currentLevel, beeCount, resetCall,regularbeeCount, hunterBeeClock, hunterBeeCount,  beeClock);  
               movePlayer(player_x, player_y, 0, resolutionX - boxPixelsX, 0.5*speedmultiplier, flowerCord,flowerActive,flowers_Max, resetCall, spraycanLives, menu_State);
                moveBees(beesX,beesY, beesTier,  beesDirection, beeTypes,  beesActive,  bees_Max,  deltaTime,  WORKER_BEE, honeycombX, honeycombY,honeycombType,honeycombActive,honeycombs_Max, flowerCord, flowerActive, flowers_Max, beehiveCord, beehiveActive, beehives_Max, firstbeeLEFT, firstbeeRIGHT, beehiveTier, beePlantedFlower);
                fireBullet(bullet_x, bullet_y, bullet_exists, player_x, player_y, sprays, spraycanState, spraycanLives, gameEnd_State, resetCall);
                generateHummingbird(deltaTime,hummingbirdX, hummingbirdY, hummingbirdActive, honeycombX, honeycombY, honeycombActive, honeycombs_Max, isBirdSick, sickClock, isFlyingToEdge, playerScore, honeycombTier, honeycombType, hummingbirdClock,powerups_Max,  powerupCords,powerupActive, powerupTimer, powerupType, pauseClock, currentLevel);
		if (bullet_exists == true)
		{       
			moveBullet(bullet_y, bullet_exists, bulletClock);
			drawBullet(window, bullet_x, bullet_y, bulletSprite);
			//simple functionality to check if bullet has hit bee
			//simple functionality to check if bullet hit honeycomb
			//blah blah hummingbird check
			if (checkBeeCollision( bullet_x, bullet_y, beesX, beesY ,beeTypes, beesActive, beesTier, beesDirection, bees_Max, WORKER_BEE, honeycombX, honeycombY, honeycombType, honeycombActive,  honeycombs_Max,  playerScore, honeycombTier)) 
			{
                          bullet_exists = false;			
			}else if (checkHoneyCombCollision( bullet_x, bullet_y,honeycombX, honeycombY,honeycombType, honeycombActive,  beehives_Max,powerupCords, powerupActive, powerupType,powerupTimer, powerups_Max, currentLevel)){
			bullet_exists = false;
			}else if(checkBeeHiveCollision(bullet_x, bullet_y, beehiveCord, beehiveActive,beehives_Max)){
			bullet_exists = false;
			}
			else if(checkBirdCollision(hummingbirdX,hummingbirdY, bullet_x, bullet_y,
                        hummingbirdActive, isBirdSick, 
                        collidedBulletCount,  sickClock, isFlyingToEdge)){
			
			bullet_exists = false;
			}else if(checkInfantBeeCollision(infantBeeCordinates, infantBeesActive, bullet_x,  bullet_y,  maxInfantBees, playerScore)){
			    bullet_exists = false;
			  }
			
			
		}
		else
		{
			bullet_x = player_x;
			bullet_y = player_y+64;
		}
                awardCans( spraycanLives,playerScore);
		drawPlayer(window, player_x, player_y, spraycanState, sizemultiplier);
                drawBees(window, beesX, beesY ,beeTypes, beesActive, beesTier, beesDirection, bees_Max, WORKER_BEE);
		window.draw(groundRectangle);
		drawHoneycombs(window, honeycombX, honeycombY, honeycombType, honeycombActive, honeycombs_Max);
		drawFlowers(window, flowerCord,flowerActive,flowers_Max);
		drawBeeHive( window, beehiveCord, beehiveActive, beehives_Max);
		drawHummingbird(window, hummingbirdX, hummingbirdY, isBirdSick, hummingbirdActive);
		detectBees(beeCount,  beesActive, gameEnd_State,  resetCall, bees_Max,  levelSwitch_State, sprays, currentLevel, levelSwitchClock, beehiveCord, beehiveActive,beehiveTier, beehives_Max, playerScore);
                checkSprayCanLives(spraycanLives,gameEnd_State,resetCall) ;
                drawScore( window, playerScore);
		drawPlayerLives(window, spraycanLives);
		drawPowerUps(window, powerupCords, powerupActive,  powerups_Max, powerupType, powerupTimer, powerTimer);
		drawInfantBee(window,infantBeeCordinates,infantBeesActive, maxInfantBees); 
		window.display();
		window.clear();
		

	}
	}
	cleanupInfantBees(infantBeeCordinates,infantBeesActive, maxInfantBees);

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
   if (!textureLoaded) {
       if (!playerTexture.loadFromFile("Textures/spray.png")) {
           std::cerr << "Failed to load player texture!" << std::endl;
           return;
       }
       textureLoaded = true;
   }

   playerSprite.setTexture(playerTexture);
   playerSprite.setTextureRect(IntRect(10, 0, playerTexture.getSize().x, playerTexture.getSize().y));
   
   
   playerSprite.setScale(sizemultiplier, sizemultiplier);
  
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
void resetGame(float& player_x, float& player_y,  float& bullet_x, float& bullet_y,  bool& bullet_exists, int& playerScore,int bees_Max,  float beesX[], float beesY[],  int beeTypes[],  bool beesActive[],  int beesTier[], bool beesDirection[], int& beeCount,int& regularbeeCount,int& hunterBeeCount,bool& firstbeeLEFT, bool& firstbeeRIGHT,int honeycombs_Max, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[],int flowers_Max, int flowerCord[][2], int flowerActive[],int beehives_Max, float beehiveCord[][2], bool beehiveActive[],float& hummingbirdX, float& hummingbirdY, bool& hummingbirdActive, bool& isBirdSick, bool& isFlyingToEdge,Clock& pauseClock,int& currentLevel,int& sprays, int& spraycanLives, int& spraycanState,Clock& hunterBeeClock, Clock& beeClock, Clock& hummingbirdClock,bool power[], float powerTimer[],float& speedmultiplier, float& sizemultiplier,bool& pre_generated,bool& hive_pregenerated,bool beePlantedFlower[]) {
    
    
    /*made this function to reset all game variables to starting conditions*/
    
    player_x = (gameColumns / 2) * boxPixelsX;
    player_y = (gameRows - 4) * boxPixelsY;
    bullet_x = player_x;
    bullet_y = player_y;
    bullet_exists = true;


    
    beeCount = 0;
    regularbeeCount = 0;
    hunterBeeCount = 0;
    firstbeeLEFT = false;
    firstbeeRIGHT = false;
    

  
    for (int i = 0; i < bees_Max; ++i) {
        if (i < bees_Max) {
            beesX[i] = 0;
            beesY[i] = 0;
            beeTypes[i] = 0;
            beesActive[i] = false;
            beesTier[i] = 0;
            beesDirection[i] = false;
            beePlantedFlower = 0;
        }
    }

    
    for (int i = 0; i < honeycombs_Max; ++i) {
        if (i < honeycombs_Max) {
            honeycombX[i] = 0;
            honeycombY[i] = 0;
            honeycombType[i] = 0;
            honeycombActive[i] = false;
        }
    }
    pre_generated = false;
    hive_pregenerated =false;

    
    for (int i = 0; i < flowers_Max; ++i) {
        if (i < flowers_Max) {
            flowerCord[i][0] = 0;
            flowerCord[i][1] = 0;
            flowerActive[i] = 0;
        }
    }

    
    for (int i = 0; i < beehives_Max; ++i) {
        if (i < beehives_Max) {
            beehiveCord[i][0] = 0;
            beehiveCord[i][1] = 0;
            beehiveActive[i] = false;
        }
    }

    
    hummingbirdX = -100;
    hummingbirdY = -100;
    hummingbirdActive = false;
    isBirdSick = false;
    isFlyingToEdge = false;
    
    
    sprays = 0;
    spraycanState = 0;

  
    hunterBeeClock.restart();
    beeClock.restart();
    hummingbirdClock.restart();
    pauseClock.restart();
    
    for (int i = 0; i < 4; ++i) {
        power[i] = false;
        powerTimer[i] = 0;
    }
    speedmultiplier = 1.0f;
    sizemultiplier = 1.0f;
}
void callGameEnd(bool& gameEnd_State, bool& resetCall) {
    cout << "GAME ENDED B" << endl;
   gameEnd_State = true;
   resetCall = true;
  

}
void resetLevel(bool& resetCall, int&spraycanLives, bool& gameEnd_State){

    if (spraycanLives > 0) {
        spraycanLives--;
        resetCall = true;
    }
    else {
      gameEnd_State = true;
      resetCall = true;
    }
}

void nextLevel(bool& resetCall, int& sprays, bool& inLevelSwitch, int& currentLevel, bool& gameEnd_State){
      if(currentLevel >=4){
        gameEnd_State = true;
        resetCall = true;

      }else{
        resetCall = true;
        sprays = 0;
        currentLevel++;
        inLevelSwitch = true;;
}
}

void detectBees(int& beeCount, bool beeActive[], bool& gameEnd_State, bool& resetCall, int bees_Max, bool& inLevelSwitch, int& sprays, int& currentLevel,Clock& levelSwitchClock, float beehiveCord[][2], bool beehiveActive[], int beehiveTier[], int beehives_Max, int& playerScore){
    static bool gameEnded = false;
    bool nobee = true;
//detect bees if there are no bees active AND the count is reached for a level to be complete that means all bees dead so we go to next level
    for(int i = 0; i < bees_Max; i++){
        if (beeActive[i]) {
            nobee = false;
            break;
        }
    }
    
    if ((beeCount == 20 || beeCount == 30)){
        if(nobee && !gameEnded){
            cout << "next level in detectBees" << endl;
            levelSwitchClock.restart();
            nextLevel(resetCall, sprays,inLevelSwitch, currentLevel, gameEnd_State);
            beehivescore_handler( playerScore,  beehiveCord, beehiveActive, beehiveTier, beehives_Max);
        }
    }
}

void awardCans(int& spraycanLives, int playerScore){
//can awaring system les gooooo
  static int num_awards = 0;
  
  if(num_awards ==0){
    if(playerScore == 20000){
      spraycanLives++;
      num_awards++;
    }
  }
  else if(num_awards == 1){
      if(playerScore == 40000){
      spraycanLives++;
      num_awards++;
      }
  }
  else if(num_awards >= 2){
    if (playerScore >= 80000 && (playerScore - 80000) % 80000 == 0) {
        spraycanLives++;
        num_awards++;
    }
}

}

void checkSprayCanLives(int& spraycanLives, bool& gameEnd_State, bool& resetCall) {
static bool gameEnded = false;
    if (spraycanLives == 0 && !gameEnded) {
        cout << "no spray can lives." << endl;
        callGameEnd(gameEnd_State, resetCall);
        gameEnded = true; 
    }

}

//time to make function to move the player
void movePlayer(float& player_x, float player_y, int boundaryLeft, int boundaryRight, float speed, int flowerCord[][2], int flowerActive[], const int flowers_Max, bool& resetCall, int& spraycanLives,bool& menu_State) {
    int oldGridX = static_cast<int>(player_x) / boxPixelsX;
    int oldGridY = static_cast<int>(player_y) / boxPixelsY;
    bool canMoveRight = true;
    bool canMoveLeft = true;
    bool forcedMove = false;
    bool teleported = false;
    bool playerStepping_Flower = false;


/* 
man i hate teleporting what the heck man khair
i added comments around harder parts for me to remember and for my future github visitors :D

*/

    for (int i = 0; i < flowers_Max; i++) {
        if (flowerActive[i]) {
            float flowerLeft = flowerCord[i][0];
            float flowerRight = flowerLeft + boxPixelsX - 1;
            float playerLeft = player_x;
            float playerRight = playerLeft + boxPixelsX - 1;
            //the above variables are the flowers "box" defined 
            if (playerRight >= flowerLeft && playerLeft <= flowerRight) {
                playerStepping_Flower = true;
                break;
            }
        }
    }


/*now if there is a player on flower we shall try to move both left and right hence the array 
no flower on a side then we move to that side */
    if (playerStepping_Flower) {
        float possibleMoves[] = {player_x + boxPixelsX, player_x - boxPixelsX};
        bool moveOptions[] = {true, true};

        for (int dir = 0; dir < 2; dir++) {
            float newX = possibleMoves[dir];
            
            if (newX < 0 || newX + boxPixelsX > resolutionX) {
                moveOptions[dir] = false;
                continue;
            }

            for (int i = 0; i < flowers_Max; i++) {
                if (flowerActive[i]) {
                    float flowerLeft = flowerCord[i][0];
                    float flowerRight = flowerLeft + boxPixelsX - 1;
                    
                    if (newX + boxPixelsX - 1 >= flowerLeft && newX <= flowerRight) {
                        moveOptions[dir] = false;
                        break;
                    }
                }
            }
        }
        if (moveOptions[0] || moveOptions[1]) {
            player_x = moveOptions[0] ? possibleMoves[0] : possibleMoves[1];
          
            gameGrid[oldGridY][oldGridX] = 0;
            
            int newGridX = static_cast<int>(player_x) / boxPixelsX;
            int newGridY = static_cast<int>(player_y) / boxPixelsY;
            gameGrid[newGridY][newGridX] = 1;
            
            forcedMove = true;
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        if (player_x > boundaryLeft) {
            float NewX = player_x - speed;
            canMoveLeft = true;

            for (int i = 0; i < flowers_Max; i++) {
                if (flowerActive[i]) {

                    float flowerLeft = flowerCord[i][0];
                    float flowerRight = flowerLeft + boxPixelsX + 1;

                    float playerLeft = NewX;
                    float playerRight = playerLeft + boxPixelsX - 1;

                    if (playerRight >= flowerLeft && playerLeft <= flowerRight) {
                        canMoveLeft = false;
                        break;
                    }
                }
            }

            if (canMoveLeft) {
                player_x = NewX;
              
                gameGrid[oldGridY][oldGridX] = 0;
                
                int newGridX = static_cast<int>(player_x) / boxPixelsX;
                int newGridY = static_cast<int>(player_y) / boxPixelsY;
                gameGrid[newGridY][newGridX] = 1;
            }
        }
    }


    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        if (player_x < boundaryRight) {
            float NewX = player_x + speed;
            canMoveRight = true;

            for (int i = 0; i < flowers_Max; i++) {
                if (flowerActive[i]) {
                    float flowerLeft = flowerCord[i][0];
                    float flowerRight = flowerLeft + boxPixelsX- 1;
                    float playerLeft = NewX;
                    float playerRight = playerLeft + boxPixelsX - 1;
                    if (playerRight >= flowerLeft && playerLeft <= flowerRight) {
                        canMoveRight = false;
                        break;
                    }
                }
            }

            if (canMoveRight) {
                player_x = NewX;
                gameGrid[oldGridY][oldGridX] = 0;
                int newGridX = static_cast<int>(player_x) / boxPixelsX;
                int newGridY = static_cast<int>(player_y) / boxPixelsY;
                gameGrid[newGridY][newGridX] = 1;
            }
        }
    }


/* using bounding box and some boxpixels we check if there is a flower on both sides if there is try to tp to a place
where no flowers on immediate but if there is no place like this means game ended
we did this instead of using the above logic because it would not be checking in a good threshold rather we would be stuck
*/

    bool flowerOnImmediateRight = false;
    bool flowerOnImmediateLeft = false;

    for (int i = 0; i < flowers_Max; i++) {
        if (flowerActive[i]) {
            float flowerLeft = flowerCord[i][0]; 
            float flowerRight = flowerLeft + boxPixelsX - 1;

            if (player_x + boxPixelsX >= flowerLeft - 5 && 
                player_x + boxPixelsX <= flowerLeft + boxPixelsX + 5) {
                flowerOnImmediateRight = true;
            }
            
            if (player_x <= flowerRight + 5 && player_x >= flowerLeft - 5) {
                flowerOnImmediateLeft = true;
            }
        }
    }

      if ((flowerOnImmediateLeft && flowerOnImmediateRight) || 
          (flowerOnImmediateLeft && player_x <= boundaryLeft) || 
          (flowerOnImmediateRight && player_x >= boundaryRight)) {
          
          float playerMidpoint = player_x + (boxPixelsX / 2.0f);
          float closestEmptySpace = -1;
          float minDistance = resolutionX;

//at first i was using grid but it was misaligned so here we looped through the whole X axis to find a spot
          for (float potentialX = 0; potentialX <= resolutionX - boxPixelsX; potentialX += 1.0f) {
              if (potentialX >= player_x && potentialX <= player_x + boxPixelsX - 1) {
              //skipping the spot of the player
                  continue;
              }
//if a space is free then we need more checks to make sure that the place isnt also surrounded by flowers
              bool spaceIsFree = true;           
              for (int i = 0; i < flowers_Max; i++) {
                  if (flowerActive[i]) {
                      float flowerLeft = flowerCord[i][0];
                      float flowerRight = flowerLeft + boxPixelsX - 1;
                      float playerTestLeft = potentialX;
                      float playerTestRight = potentialX + boxPixelsX - 1; 
                      if (playerTestRight >= flowerLeft && playerTestLeft <= flowerRight) {
                          spaceIsFree = false;
                          break;}
                      if (playerTestRight + boxPixelsX >= flowerLeft && playerTestLeft - boxPixelsX <= flowerRight){
                          spaceIsFree = false;
                          break;
                      }
                      
                  }
              }if (spaceIsFree) {
                  float distance = abs(potentialX - player_x);
                  if (distance < minDistance) {
                      minDistance = distance;
                      closestEmptySpace = potentialX;
                  }
              }
          }

          if (closestEmptySpace != -1) {
              player_x = closestEmptySpace;
              teleported = true;
              cout << "Teleported to nearest empty space" << endl;
          } else {
              
              cout << "Game End - No Possible Moves" << endl;
              resetLevel(resetCall, spraycanLives, menu_State);
              
          }
      }


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



//bullet boom boom
void fireBullet(float& bullet_x, float& bullet_y, bool& bullet_exists, float player_x, float player_y, int& sprays, int& spraycanState, int& spraycanLives, bool& gameEnd_State, bool& resetCall) {
    static bool wasSpacePressed = false; 
    static int totalSprays = 0;
    bool isSpacePressed = Keyboard::isKeyPressed(Keyboard::Space);
    static bool gameEndCalled = false;

    if (isSpacePressed && !wasSpacePressed && !bullet_exists) {
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
void beesGenerator(float beesX[], float beesY[], int beeTypes[], bool beesActive[], int beesTier[], bool beesDirection[], int bees_Max, int WORKER_BEE, int currentLevel, int& beeCount, bool resetCall, int& regularbeeCount, Clock& hunterBeeClock, int& hunterBeeCount, Clock& beeClock ) {
    int maxBeeCount = 0;
    int regularBees = 0;
    int hunterBees = 0;


    switch (currentLevel) {
        case 1:
            maxBeeCount = 20;
            regularBees = 20;
            break;
        case 2:
            maxBeeCount = 20;
            regularBees = 15;
            hunterBees = 5;
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
    
     
        
    int delay = (regularbeeCount < 10) ? 2: 6; // 2 seconds for the first 6, 10 seconds for the rest
    int beeNum = (regularbeeCount < 10)? 1 : 2; // 1 bee for first 6, 2 bees for rest
    if (beeClock.getElapsedTime().asSeconds() >= delay && regularbeeCount < regularBees) {
          int newBeesGenerated = 0;
          int startPoint = 1;
          int beesToGenerate = min(beeNum, regularBees - regularbeeCount);

        for (int i = 0; i < bees_Max && newBeesGenerated < beesToGenerate; i++) {
            if (!beesActive[i]) {
                if (delay == 2){
                beesActive[i] = true;
                beeTypes[i] = WORKER_BEE;
                        if (beeCount % 2 == 0) {
                            beesX[i] = 0;
                            beesDirection[i] = true; 
                        } else {
                            beesX[i] = resolutionX - boxPixelsX ;
                            beesDirection[i] = false; 
                        }
                beesTier[i] = rand() % 2; 
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
                beesTier[i] = rand() % 2; 
                (beesTier[i] == 1) ? beesY[i] = boxPixelsY : beesY[i] = boxPixelsY * 2;
                beesDirection[i] = (startPoint == 1)? 1: 0; 
                newBeesGenerated++;
                regularbeeCount++;
  
                            
            }
          }
        }
        beeClock.restart();
    }
    
    const float hunterbee_spawntimer = 7.0f;
    if (currentLevel >= 2 && hunterBeeCount < hunterBees) {
        if (hunterBeeCount == 0 && hunterBeeClock.getElapsedTime().asSeconds() >= hunterbee_spawntimer) {
            for (int i = 0; i < bees_Max; i++) {
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
                
                    beesTier[i] = rand() % 2;
                    (beesTier[i] == 1) ? beesY[i] = boxPixelsY : beesY[i] = boxPixelsY * 2;
                    hunterBeeCount++;
                    beeCount++;
                    hunterBeeClock.restart();
                    break;
                }
            }
        }
      else if (hunterBeeCount > 0 && hunterBeeClock.getElapsedTime().asSeconds() >= hunterbee_spawntimer + 3 && hunterBeeCount < hunterBees) {
      int startHunter;
        for (int i = 0; i < bees_Max; i++) {
            if (!beesActive[i]) {
                beesActive[i] = true;
                beeTypes[i] = 1;
                startHunter = rand() % 2;
                (startHunter == 1)? beesX[i] = 0 : beesX[i] = resolutionX - boxPixelsX;
                beesTier[i] = rand() % 2;
                (beesTier[i] == 1) ? beesY[i] = boxPixelsY : beesY[i] = boxPixelsY * 2;
                beesDirection[i] = (startHunter == 1)? 1: 0; 
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
void moveBees(float beesX[], float beesY[], int beesTier[], bool beesDirection[], int beeTypes[], bool beesActive[], int bees_Max, float deltaTime, int WORKER_BEE, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int honeycombs_Max,int flowerCord[][2], int flowerActive[], const int flowers_Max, float beehiveCord[][2], bool beehiveActive[], int beehives_Max, bool& firstbeeLEFT, bool& firstbeeRIGHT, int beehiveTier[], bool beePlantedFlower[]) {
  
  /* seperated movement for hunter and worker bees so that its easier to manage
  hunter bees dont collide with obstacles so had to keep them seperate
  if the bee collides with a honeycomb it just moves down and if there is a honeycomb beneath it makes a beehive
  it does this by comparing the x and y coordinates of bee and the obstacle
  for the pause mechanism, pause is triggered randomly if the number is 5 out of 10000 i found these odds to give a good chance of pausing bee wihout over pausing
  
  also made sure that after making a flower, the bee exits by reversing the direction this was done by using a new array called beePlantedFlower[]
  */
  
  
  
  static Clock BeePauseClock;
  static float pauseStartTime[100] = {0}; 
  static bool paused[100] = {false};
  float PAUSE_DURATION = 4.0f;  
  const float bee_Speed = 200.0f;
  const float hunterbee_Speed = 400.0f;
  
    for (int i = 0; i < bees_Max; i++) {
        if (beesActive[i]) {
            float speed = (beeTypes[i] == WORKER_BEE) ? bee_Speed : hunterbee_Speed;
            float movement = speed * deltaTime;
            if(beeTypes[i] == WORKER_BEE){
               if (paused[i]) {
                  if (BeePauseClock.getElapsedTime().asSeconds() - pauseStartTime[i] >= PAUSE_DURATION) {
                    paused[i] = false; 
                  } else {

                    continue; 
                    }
              }
        
            int randomNum = rand() % 5000;
            if (randomNum == 5) {
                paused[i] = true; 
                pauseStartTime[i] = BeePauseClock.getElapsedTime().asSeconds();
                continue; 
            }
          }
            if (beesDirection[i]) {
                beesX[i] += movement;
            } else {
                beesX[i] -=movement;
            }

         if(beeTypes[i] == WORKER_BEE){
            bool bounced = false;
            for (int j = 0; j < honeycombs_Max; j++) {
                if (honeycombActive[j]) {
                    if (abs(beesX[i] - honeycombX[j]) < boxPixelsX && abs(beesY[i] - honeycombY[j])<boxPixelsY){
                        beesX[i] = (beesDirection[i]) ? honeycombX[j] - boxPixelsX : honeycombX[j] + boxPixelsX; 
                        beesDirection[i] = !beesDirection[i];
                        
                        if (beeTypes[i] == WORKER_BEE) {
                            float newBeeY = beesY[i] + boxPixelsY;
                            bool honeycombBelow = false; 
                            
                          for (int k = 0; k < honeycombs_Max; k++) {
                                if (honeycombActive[k] && abs(beesX[i] - honeycombX[k]) < boxPixelsX && abs(newBeeY - honeycombY[k]) < boxPixelsY) {
                                    honeycombBelow = true;
                                    generateBeeHive(beesX[i],  beesY[i], bees_Max,  beehiveCord,beehiveActive, beehives_Max, beehiveTier, beesTier[i]);
                                    beesActive[i] = false;
                                    cout<<"x";
                                    break;
                                }
                            }
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
          for (int j = 0; j < beehives_Max; j++) {
              if (beehiveActive[j]) {
                  if (abs(beesX[i] - beehiveCord[j][0]) < boxPixelsX && abs(beesY[i] - beehiveCord[j][1]) < boxPixelsY) {
                      beesX[i] = (beesDirection[i]) ? 
                      beehiveCord[j][0] - boxPixelsX : 
                      beehiveCord[j][0] + boxPixelsX;
                      beesDirection[i] = !beesDirection[i];
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
            if (!bounced) {
              if (beesX[i] <= 0 && beesY[i] < lastRow) {
                beesX[i] = 1; 
                beesDirection[i] = !beesDirection[i];  
                
                float newBeeY = beesY[i] + boxPixelsY;
                bool honeycombBelow = false;            
                for (int k = 0; k < honeycombs_Max; k++) {
                if (honeycombActive[k] && abs(beesX[i] - honeycombX[k]) < boxPixelsX && abs(newBeeY - honeycombY[k]) < boxPixelsY) {
                    honeycombBelow = true;
                    generateBeeHive(beesX[i],  beesY[i], bees_Max,  beehiveCord,beehiveActive, beehives_Max, beehiveTier, beesTier[i]);
                    beesActive[i] = false;
                    cout<<"x";
                    break;
                }
            }
                            
                if (!honeycombBelow) {
                    beesY[i] = newBeeY;
                    beesTier[i]++;
                  }
              }
             else if (beesX[i] >= resolutionX - boxPixelsX && beesY[i] <lastRow) {
                beesX[i] = resolutionX - boxPixelsX;  
                beesDirection[i] = !beesDirection[i];  
                float newBeeY = beesY[i] + boxPixelsY;
                bool honeycombBelow = false;         
                for (int k = 0; k < honeycombs_Max; k++) {
                if (honeycombActive[k] && abs(beesX[i] - honeycombX[k]) < boxPixelsX && abs(newBeeY - honeycombY[k]) < boxPixelsY) {
                    honeycombBelow = true;
                    generateBeeHive(beesX[i],  beesY[i], bees_Max,  beehiveCord,beehiveActive, beehives_Max, beehiveTier, beesTier[i]);
                    beesActive[i] = false;
                    cout<<"x";
                    break;
                }
            }
                            
                if (!honeycombBelow) {
                    beesY[i] = newBeeY;
                    beesTier[i]++;
                  }
            }
             }
           
                if (beesY[i] >= lastRow) {
                    bool flowerPlanted = flowerGenerator(beesX[i], beesY[i], flowerCord, flowerActive, flowers_Max, firstbeeRIGHT, firstbeeLEFT, beePlantedFlower[i]);
                    if (flowerPlanted) {
                        beesDirection[i] = !beesDirection[i];
                        beePlantedFlower[i] = true;}
                    if (beesX[i] <= 0 && beePlantedFlower[i] || beesX[i] >= resolutionX - boxPixelsX && beePlantedFlower[i]) {
                            beesActive[i] = false;
                            beePlantedFlower[i] = false;}  
                    else if (beesY[i] >= lastRow && (beesX[i] <= 0 || beesX[i] >= resolutionX - boxPixelsX)) {
                        beesDirection[i] = !beesDirection[i];
                        beesX[i] = (beesX[i] <=0)? 1: resolutionX - boxPixelsX - 5;
                    } 
                }

              
                if (beesY[i] >= resolutionY) {
                    beesActive[i] = false;
                }

        }
        
          else {//hunter bee movement
              float lastRow = (gameRows - 3) * boxPixelsY;
              
              if (beesDirection[i]) {
                  beesX[i] += speed * deltaTime;
              } else {
                  beesX[i] -= speed * deltaTime;
              }
              if (beesX[i] <= 0) {
                  beesX[i] = 0;
                  beesDirection[i] = !beesDirection[i];
                  float newBeeY = beesY[i] + boxPixelsY;
                  beesY[i] = newBeeY;
                  beesTier[i]++;
              }             
              else if (beesX[i] >= resolutionX - boxPixelsX) {
                  beesX[i] = resolutionX - boxPixelsX;  
                  beesDirection[i] = !beesDirection[i];  
                  float newBeeY = beesY[i] + boxPixelsY;
                  beesY[i] = newBeeY;
                  beesTier[i]++;
              }
             
              if (beesY[i] >= lastRow) {        
                  bool flowerPlanted = flowerGenerator(beesX[i], beesY[i], flowerCord, flowerActive, flowers_Max, firstbeeRIGHT, firstbeeLEFT, beePlantedFlower[i]);
                  if (flowerPlanted) {
                      beesDirection[i] = !beesDirection[i];
                      beePlantedFlower[i] = true;
                  }
                  if ((beesX[i] <= 0 || beesX[i] >= resolutionX - boxPixelsX) && beePlantedFlower[i]) {
                      beesActive[i] = false;
                      beePlantedFlower[i] = false;
                  }
              }

              if (beesY[i] >= resolutionY) {

                  beesActive[i] = false;
                }
              }
  }
}
}

// Function to check collision between bullet and bees
bool checkBeeCollision(float bullet_x, float bullet_y, float beesX[], float beesY[], int beeTypes[], bool beesActive[], int beesTier[], bool beesDirection[], int bees_Max, int WORKER_BEE, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int honeycombs_Max, int& playerScore, int honeycombTier[]) {
    for (int i = 0; i < bees_Max; i++) {
        if (beesActive[i]) { 
            if (abs(bullet_x - beesX[i]) < boxPixelsX && 
                abs(bullet_y - beesY[i]) < boxPixelsY) {
                generateHoneycomb(beesX[i], beesY[i], beeTypes[i], 
                                  honeycombX, honeycombY, honeycombType, honeycombActive, honeycombs_Max, beesTier[i], honeycombTier);
                
                (beeTypes[i] == WORKER_BEE)? playerScore += 100 : playerScore += 1000;
                beesActive[i] = false;
                return true;
            }
        }
    }
    return false;
}

// Function to draw bees

void drawBees(RenderWindow& window, float beesX[], float beesY[], int beeTypes[], bool beesActive[], int beesTier[], bool beesDirection[], int bees_Max, int WORKER_BEE) {
    Texture workerBeeTexture, killerBeeTexture, reversedworkerBeeTexture, reversedkillerBeeTexture;
    workerBeeTexture.loadFromFile("Textures/bee.png");
    killerBeeTexture.loadFromFile("Textures/Fast_bee.png");
    reversedworkerBeeTexture.loadFromFile("Textures/reversedbee.png");
    reversedkillerBeeTexture.loadFromFile("Textures/reversedkillerbee.png");
    static int currentFrame= 0;
    Sprite beeSprite;
    IntRect frames[] = {
            IntRect(0, 0, 32, 32),  
            IntRect(32, 0, 32, 32)  
        };
        currentFrame = (currentFrame + 1) % 2;
        beeSprite.setTextureRect(frames[currentFrame]);
    for (int i = 0; i < bees_Max; i++) {
         if (beesActive[i]) {
            if (beeTypes[i] == WORKER_BEE){
                if(beesDirection[i] == false)// false = left
                  beeSprite.setTexture(workerBeeTexture);
                else beeSprite.setTexture(reversedworkerBeeTexture);
            }
            else {
                if(beesDirection[i] == false)// false = left
                  beeSprite.setTexture(killerBeeTexture);
                else beeSprite.setTexture(reversedkillerBeeTexture);}
            beeSprite.setPosition(beesX[i], beesY[i]);
            window.draw(beeSprite);    
      }
    }
}
//time for those honey pie i mean honey combs


//generatinggg a honeycomb when a bee is hit
void generateHoneycomb(float bee_x, float bee_y, int beeType, 
                       float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int honeycombs_Max,int beeTier, int honeycombTier[]) {
                       
    for (int i = 0; i < honeycombs_Max; i++) {
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


void honeycombPreGenerator(float honeycombX[], float honeycombY[], bool honeycombActive[], int honeycombType[], int MAX_HONEYCOMB, int currentLevel, int honeycombTier[], float beehiveCord[][2], bool beehiveActive[], int beehives_Max, bool& generated, bool& hivegenerated) {

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
        //make sure its divisble by 32
        honeycombX[i] = (rand() % ((resolutionX - 100) / 32)) * 32 + 50;
        int availableTiers = gameRows - 4; 
        int randomTier = rand() % availableTiers;
        honeycombY[i] = boxPixelsY * (randomTier + 1); 
        honeycombActive[i] = true;
        honeycombType[i] = 0;
        honeycombTier[i] = randomTier;
    }
    generated = true;
  }
  else {
  }
  if (!hivegenerated && currentLevel == 4){
  //beehive pregenerationnn
  for (int i = 0; i < beehiveCount; i++) {
        //make sure its divisble by 32 aka box pixels
        beehiveCord[i][0] = (rand() % ((resolutionX - 100) / 32)) * 32 + 50;
        int availableTiers = gameRows - 4; 
        int randomTier = rand() % availableTiers;
        beehiveCord[i][1] = boxPixelsY * (randomTier + 1); 
        beehiveActive[i] = true;
    }
    hivegenerated = true;
  }
  else {
      
  }
}


//draw the honeycombssss
void drawHoneycombs(RenderWindow& window, 
                    float honeycombX[], float honeycombY[], 
                    int honeycombType[], bool honeycombActive[], int honeycombs_Max) {
    Texture yellowHoneycombTexture, redHoneycombTexture;
    yellowHoneycombTexture.loadFromFile("Textures/honeycomb.png");
    redHoneycombTexture.loadFromFile("Textures/honeycomb_red.png");

    Sprite honeycombSprite;
    for (int i = 0; i < honeycombs_Max; i++) {
        if (honeycombActive[i]) {
            honeycombSprite.setTexture(honeycombType[i] == 0 ? yellowHoneycombTexture : redHoneycombTexture);
            honeycombSprite.setPosition(honeycombX[i], honeycombY[i]);
            window.draw(honeycombSprite);
        }
    }
}

//function to check collision between bullet and honeycomb
bool checkHoneyCombCollision(float bullet_x, float bullet_y, float honeycombX[], float honeycombY[], int honeycombType[], bool honeycombActive[], int honeycombs_Max, float powerupCords[][2], bool powerupActive[], int powerupType[], float powerupTimer[], int powerups_Max, int currentLevel){
   for (int i = 0; i < honeycombs_Max; i++) {
        if (honeycombActive[i]) {
            if (abs(bullet_x - honeycombX[i]) < boxPixelsX && 
                abs(bullet_y - honeycombY[i]) < boxPixelsY) { 
                if (honeycombType[i] == 1 && currentLevel == 4){ // 1 = RED HONEYCOMB 
                generatePowerUp(powerupCords, powerupActive, powerupType,powerupTimer, powerups_Max,honeycombX[i],honeycombY[i]);
                }
                honeycombActive[i] = false;
                return true;
            }
        }
    }
    return false;
}



// FLOWERSSSSS

bool flowerGenerator(float beeX, float beeY, int flowerCord[][2], int flowerActive[], const int flowers_Max, bool& firstBeeLEFT, bool& firstBeeRIGHT, bool& beePlantedFlower) {
// we check if bee is just above ground and aligned with grid

/*comprehensive explaination by me: bhai we need to generate flowers but the first bees from left and right generate two flowers so for the first bees we dont deactivate them and let them plant another flower, for all the other bees we check if there is a position that is free from other players and then plant flower there this is done by checking if there is any active flower positioned at the bee coordinates at that moment got it? */

if (beeY >= (gameRows - 3) * boxPixelsY) {
    if (static_cast<int>(beeX) % boxPixelsX == 0) {
        if (beeX == 0 || beeX < boxPixelsX) {
            if (!firstBeeLEFT)  {
                for (int i = 0; i < flowers_Max; i++) {
                    if (!flowerActive[i]) {
                        flowerActive[i] = true;
                        flowerCord[i][0] = static_cast<int>(beeX);
                        flowerCord[i][1] = static_cast<int>(beeY);
                        int gridX = static_cast<int>(flowerCord[i][0]) / boxPixelsX;
                        int gridY = static_cast<int>(flowerCord[i][1]) / boxPixelsY;
                        gameGrid[gridY][gridX] = 2; 
                              
                        firstBeeLEFT = true;
                        return false;  // dont deactivate bee if it is the first flower
                    }
                }
            }
        }
        else if (beeX >= resolutionX - boxPixelsX) {
            if (!firstBeeRIGHT) {
              for (int i = 0; i < flowers_Max; i++) {
                    if (!flowerActive[i]) {
                        flowerActive[i] = true;
                        flowerCord[i][0] = static_cast<int>(beeX);
                        flowerCord[i][1] = static_cast<int>(beeY);
                        int gridX = static_cast<int>(flowerCord[i][0]) / boxPixelsX;
                        int gridY = static_cast<int>(flowerCord[i][1]) / boxPixelsY;
                        gameGrid[gridY][gridX] = 2; 
                                
                        firstBeeRIGHT = true;
                        return false;  
                    }
                }
            }
        }
        else if (firstBeeLEFT || firstBeeRIGHT) {
            for (int i = 0; i < flowers_Max; i++) {
              if (!flowerActive[i] && !beePlantedFlower) {
                 bool positionOccupied = false;
                    for (int j = 0; j < flowers_Max; j++) {
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
                        gameGrid[gridY][gridX] = 2; 
                        beePlantedFlower = true;
                        return true;  
            }
            }
        }
     }
  }
    return false;
}
return false;}





void drawFlowers(RenderWindow& window, int flowerCord[][2], int flowerActive[], const int flowers_Max ) {
    Texture flowerTexture;
    flowerTexture.loadFromFile("Textures/flower.png");
    Sprite flowerSprite;
    flowerSprite.setTexture(flowerTexture);

    for (int i = 0; i < flowers_Max; i++) {
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


void generateHummingbird(float deltaTime,float& hummingbirdX, float& hummingbirdY, bool& hummingbirdActive, 
                         float honeycombX[], float honeycombY[], bool honeycombActive[], 
                         int honeycombs_Max, bool& isBirdSick, Clock& sickClock, bool& isFlyingToEdge, int& playerScore, int honeycombTier[], int honeycombType[],Clock& hummingbirdClock,const int powerups_Max, float powerupCords[][2],bool powerupActive[],float powerupTimer[],int powerupType[], Clock& pauseClock, int currentLevel) {
  
    
    static int hummingbirdMoves = 0; 
    static float foodX = 0; 
    static float foodY = 0; 
    static bool newfoodNeeded = true; 
    static bool isPaused = false;
    const float foodreached_THRESHOLD = 1.0f;
    const float birdpause_Duration = 2.0f;
    const float hummingbirdspawn_timer = 12.0f;
      /* complex logic explaination: 
      the bird moves birdlculated everytime they are needed, if the bird is sick the flying to edge bool becomes true and the sequence for the bird to move to edge starts. Every third food is a honeycomb. use pythogras to calc the displace to each honeycomb and find the nearest.
      */

   if (isFlyingToEdge) {
      static bool foodCalculated = false;
      if (!foodCalculated) {
          float leftDistance = hummingbirdX;
          float rightDistance = resolutionX - (hummingbirdX + boxPixelsX);
          float minDistance = min({leftDistance, rightDistance});
          if (minDistance == leftDistance) {
              foodX = 0;
              foodY = hummingbirdY;
          } else if (minDistance == rightDistance) {
              foodX = resolutionX - boxPixelsX;
              foodY = hummingbirdY;
          }
          foodCalculated = true; 
      }

      float edgeSpeed = 300.0f; 
      if (hummingbirdX < foodX) {
          hummingbirdX += edgeSpeed * deltaTime;
          if (hummingbirdX > foodX) hummingbirdX = foodX;
      } else {
          hummingbirdX -= edgeSpeed * deltaTime;
          if (hummingbirdX < foodX) hummingbirdX = foodX; // Fixed comparison
      }

      if (hummingbirdY < foodY) {
          hummingbirdY += edgeSpeed * deltaTime;
          if (hummingbirdY > foodY) hummingbirdY = foodY;
      } else {
          hummingbirdY -= edgeSpeed * deltaTime;
          if (hummingbirdY < foodY) hummingbirdY = foodY;
      }


      if (abs(hummingbirdX - foodX) < 1.0f && abs(hummingbirdY - foodY) < 1.0f) {
          isFlyingToEdge = false;  
          foodCalculated = false; 
          hummingbirdActive = false; 
      }
    }

    if (!hummingbirdActive && !isBirdSick && hummingbirdClock.getElapsedTime().asSeconds() >= hummingbirdspawn_timer) {
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
        hummingbirdMoves= 0;
        newfoodNeeded = true; 
    }
    if (isBirdSick && sickClock.getElapsedTime().asSeconds() >= 5) {
        isBirdSick = false; 
    }


    if (hummingbirdActive) {
        if (newfoodNeeded) {
            // we see if new position needed
            foodX = rand() % (resolutionX - boxPixelsX);
            foodY = rand() % resolutionY;
            if (foodY >= (gameRows - 3) * boxPixelsY){
              foodY = rand()%resolutionY;
            }else{ 
            newfoodNeeded = false; 
        }
        }


        float speed = 150.0f; 
    /////////movement////////////
        if (hummingbirdX < foodX) {
            hummingbirdX += speed * deltaTime;
            if (hummingbirdX > foodX) hummingbirdX = foodX; 
        } 
        else {
            hummingbirdX -= speed * deltaTime;
            if (hummingbirdX < foodX) hummingbirdX = foodX; 
        }

        if (hummingbirdY < foodY) {
            hummingbirdY += speed * deltaTime;
            if (hummingbirdY > foodY) hummingbirdY = foodY; 
        } else 
        {
            hummingbirdY -= speed * deltaTime;
            if (hummingbirdY < foodY) hummingbirdY = foodY; 
        }

        if (abs(hummingbirdX - foodX) < foodreached_THRESHOLD && 
            abs(hummingbirdY - foodY) < foodreached_THRESHOLD) {
            if (!isPaused) {
            isPaused = true;
            pauseClock.restart();
    } else {

        if (pauseClock.getElapsedTime().asSeconds() >= birdpause_Duration) {
            hummingbirdMoves++;
            newfoodNeeded = true; 
            isPaused = false; 
            for (int i = 0; i < honeycombs_Max; i++){
                    if(honeycombActive[i]){
                        if(honeycombX[i] == foodX && honeycombY[i] == foodY){
                        if (currentLevel == 4)
                            {generatePowerUp(powerupCords, powerupActive, powerupType,powerupTimer, powerups_Max,honeycombX[i],honeycombY[i]);}
                            
                        /////////////////////assigning scores//////////////////
                            if (honeycombType[i] == 0){ // 0 = WORKER_BEE
                              if(honeycombTier[i] == 0 || honeycombTier[i] == 1){
                                  playerScore += 1000;
                                  
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
                            if(honeycombTier[i] == 0 || honeycombTier[i] == 1){
                                  playerScore += 2000;}
                              else if (honeycombTier[i] == 2 || honeycombTier[i] == 3 || honeycombTier[i] == 4){
                                  playerScore += 1800;
                                  }
                              else {
                                    playerScore += 1500;
                                  }
                              }
                            honeycombActive[i] = false; 
                          }
                    }  
                    
                }
          }
        }
    }

        // third move is alwayys to honeycomb
        if (hummingbirdMoves >= 3) {
            float nearestDistance = 10000000000;
            int nearestHoneycombIndex = -1;
        //using pythogras formula to calculate displacement
            for (int i = 0; i < honeycombs_Max; i++) {
                if (honeycombActive[i]) {
                float distance = (honeycombX[i] - hummingbirdX) * (honeycombX[i] - hummingbirdX) + (honeycombY[i] - hummingbirdY) * (honeycombY[i] - hummingbirdY); 
                distance = distance * 0.5;
                    if (distance < nearestDistance) {
                        nearestDistance = distance; 
                        nearestHoneycombIndex = i; 
                    }

                }

            }

            if (nearestHoneycombIndex != -1) {
                foodX = honeycombX[nearestHoneycombIndex];
                foodY = honeycombY[nearestHoneycombIndex];
                newfoodNeeded = false; 
                hummingbirdMoves= 0;

          }
      }
  }
}
bool checkBirdCollision(float& hummingbirdX, float& hummingbirdY, float bulletX, float bulletY,bool& hummingbirdActive, bool& isBirdSick,int& collidedBulletCount,  Clock& sickClock, bool& isFlyingToEdge) {
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
        return true; 
    }
    return false; 
}




//Humming BIRD DRAW
void drawHummingbird(RenderWindow& window, float hummingbirdX, float hummingbirdY, bool isBirdSick, bool hummingbirdActive) {
    static Texture normalTexture;
    static Texture sickTexture;
    static bool isNormalTextureLoaded = false;
    static bool isSickTextureLoaded = false;
    static int currentFrame = 0;

    if (hummingbirdActive) {
        if (!isNormalTextureLoaded) {
            if (!normalTexture.loadFromFile("Textures/bird.png")) {
                return;
            }
            isNormalTextureLoaded = true;
        }

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
            IntRect(0, 0, 32, 32),  
            IntRect(32, 0, 32, 32)  
        };
        currentFrame = (currentFrame + 1) % 2;
        hummingbirdSprite.setTextureRect(frames[currentFrame]);

        hummingbirdSprite.setPosition(hummingbirdX, hummingbirdY);
        window.draw(hummingbirdSprite);
    }
}



//BOYS BEE HIVE TIME
void generateBeeHive(float beeX, float beeY, int bees_Max, float beehiveCord[][2], bool beehiveActive[], int beehives_Max, int beehiveTier[], int beeTier){
    for (int i = 0; i < beehives_Max ; i++) {
        if (!beehiveActive[i]) {
            beehiveCord[i][0] = beeX;
            beehiveCord[i][1] = beeY;
            beehiveActive[i] = true;
            beehiveTier[i] = beeTier;
            break;
        }
    }
}

bool checkBeeHiveCollision(float bullet_x, float bullet_y, float beehiveCord[][2], bool beehiveActive[], int beehives_Max) {
   for (int i = 0; i < beehives_Max; i++) {
        if (beehiveActive[i]) {
            if (abs(bullet_x - beehiveCord[i][0]) < boxPixelsX && 
                abs(bullet_y - beehiveCord[i][1]) < boxPixelsY) {
                beehiveActive[i] = false;
                return true;
            }
        }
    }
    return false;   
}


void beehivescore_handler(int& playerScore, float beehiveCord[][2], bool beehiveActive[], int beehiveTier[], int beehives_Max){
  
  for(int i = 0; i < beehives_Max; i++){
      if(beehiveActive[i]){
        if(beehiveTier[i] == 0 || beehiveTier[i] == 1){
          playerScore += 2000;
        
        }
        else if(beehiveTier[i] == 2 || beehiveTier[i] == 3|| beehiveTier[i] == 4){
        playerScore +=1600;
        
        }
      else { playerScore +=1000;}
      }
  
  }

}

void drawBeeHive(RenderWindow& window, float beehiveCord[][2], bool beehiveActive[], int beehives_Max ) {
    Texture beehiveTexture;
    beehiveTexture.loadFromFile("Textures/hive1.png");
    Sprite beehiveSprite;
    beehiveSprite.setTexture(beehiveTexture);

    for (int i = 0; i < beehives_Max; i++) {
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
   scoreText.setPosition(resolutionX - boxPixelsX*5, (gameRows - 2)*boxPixelsY + 10);
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


///////////////////////LEADERBOARDS///////////////////////////



void readleaderboard(char leaderboard_names[][50], int leaderboard_scores[], int ld_Positions) {
    ifstream file("leaderboard.txt");
    string line;
    int index = 0;

    while (getline(file, line) && index < ld_Positions) {
        int comma = line.find(',');
        
        string scoreStr = line.substr(0, comma);
        if (scoreStr.empty()) scoreStr = "0";
        leaderboard_scores[index] = stoi(scoreStr);
        string name = line.substr(comma + 1);
        for (int i = 0; i < name.length() && i < 49; ++i) {
            leaderboard_names[index][i] = name[i];
        }
        leaderboard_names[index][name.length()] = '\0';

        index++;
    }
}

void sortleaderboard(char leaderboard_names[][50], int leaderboard_scores[], int ld_Positions) {
//decided to use bubble sort
    for (int i = 0; i < ld_Positions - 1; i++) {
        for (int j = 0; j < ld_Positions - i - 1; j++) {
            if (leaderboard_names[j][0] == 0 || leaderboard_names[j+1][0] == 0) continue;

            if (leaderboard_scores[j] < leaderboard_scores[j+1]) {
                swap(leaderboard_scores[j], leaderboard_scores[j+1]);

                char tempName[50];
                for (int k = 0; k < 50; k++) {
                    tempName[k] = leaderboard_names[j][k];
                    leaderboard_names[j][k] = leaderboard_names[j+1][k];
                    leaderboard_names[j+1][k] = tempName[k];}
                  
                  }
              }
          }
}

void storeleaderboard(char leaderboard_names[][50], int leaderboard_scores[], int ld_Positions) {
    ofstream file("leaderboard.txt");

    for (int i = 0; i < ld_Positions; i++) {
        if (leaderboard_names[i][0] == 0) continue;
        int score = leaderboard_scores[i];
        string scoreStr = to_string(score);
        file << scoreStr << "," << leaderboard_names[i] << endl;
    }
}

//////////////////////////////////////POWERUPSSSSSSS//////////////////////////////////////////////

void updatePowerUps(float player_x, float player_y, float deltaTime, float powerupCords[][2], bool powerupActive[], float powerupTimer[], int powerupType[], const int powerups_Max, bool power[], float& speedmultiplier, float& sizemultiplier, float powerTimer[]) {
    
    /* power ups are treated same as a bee, each function call the falling speed is minused from y cordinate and when it reaches the last row it stays there
    using a switch statement we assign the power up when player collides with it
    
    */
    
    
    const float falling_Speed = 20.0f * deltaTime;
    const float powerup_size = 32.0f;
    const float lastROW = (gameRows - 3) * boxPixelsY;
    const float timer_Decrement = 0.002f;


    for (int i = 0; i < powerups_Max; i++) {
        if (powerupActive[i]) {
            powerupCords[i][1] += falling_Speed;
            if (powerupCords[i][1] >= lastROW) {
                powerupCords[i][1] = lastROW;
            }

            if (powerupCords[i][1] >= lastROW) {
                powerupTimer[i] -= timer_Decrement;
                if (powerupTimer[i] <= 0) {
                    powerupActive[i] = false; 
                }
            }

            if (player_x < powerupCords[i][0] + powerup_size && player_x + boxPixelsX > powerupCords[i][0] && player_y + boxPixelsX ==powerupCords[i][1]){ 
              powerupActive[i] = false;
              switch (powerupType[i]) {
                    case 0: 
                        if (power[1]) {
                            power[1] = false;
                            speedmultiplier = 1.0f; 
                            powerTimer[1] = 0; 
                        } else {
                            power[0] = true;
                            speedmultiplier = 2.0f;
                            powerTimer[0] = 10.0f; 
                        }
                        break;

                    case 1: 
                        if (power[0]) {
                            power[0] = false;
                            speedmultiplier = 1.0f; 
                            powerTimer[0] = 0; 
                        } else {
                            power[1] = true;
                            speedmultiplier = 0.5f;
                            powerTimer[1] = 10.0f; 
                        }
                        break;

                    case 2: 
                        if (power[3]) {
                            power[3] = false;
                            sizemultiplier = 1.0f; 
                            powerTimer[3] = 0; 
                        } else {
                            power[2] = true;
                            sizemultiplier = 1.5f;
                            powerTimer[2] = 10.0f; 
                        }
                        break;

                    case 3:
                        if (power[2]) {
                            power[2] = false;
                            sizemultiplier = 1.0f; 
                            powerTimer[2] = 0; 
                        } else {
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
void drawPowerUps(RenderWindow& window, float powerupCords[][2], bool powerupActive[], int powerups_Max, int powerupType[], float powerupTimer[], float powerTimer[]) {
   /* different colors for every rectangle P*/
   
   Texture powerUpTextures[4];
    powerUpTextures[0].loadFromFile("Sprites/Speed_inc.png");
    powerUpTextures[1].loadFromFile("Sprites/Speed_dec.png");
    powerUpTextures[2].loadFromFile("Sprites/Height_inc.png");
    powerUpTextures[3].loadFromFile("Sprites/Height_dec.png");
        Color powerUpTimerColors[4] = {
        Color::Green,   
        Color::Red,     
        Color::Blue,    
        Color::Yellow   
    };
    Sprite powerUpSprites[4];
    for (int i = 0; i < 4; i++) {
        powerUpSprites[i].setTexture(powerUpTextures[i]);
    }
    //timer above the sprites
    for (int i = 0; i < powerups_Max; i++) {
        if (powerupActive[i]) {
            powerUpSprites[powerupType[i]].setPosition(powerupCords[i][0], powerupCords[i][1]);
            window.draw(powerUpSprites[powerupType[i]]);

            IntRect timerRect(powerupCords[i][0], powerupCords[i][1] - 15,powerupTimer[i] * 5, 5);

            RectangleShape timerShape(Vector2f(timerRect.width, timerRect.height));
            timerShape.setPosition(timerRect.left- 7, timerRect.top);
            timerShape.setFillColor(Color::Green);
            window.draw(timerShape);
        }
    }
  //timer when power up is picked up 
    IntRect powerUpTimerRects[4] = {
        IntRect(100, 50, powerTimer[0] * 10, 10),   
        IntRect(100, 50, powerTimer[1] * 10, 10),   
        IntRect(100, 70, powerTimer[2] * 10, 10),   
        IntRect(100, 70, powerTimer[3] * 10, 10)    
    };

    for (int i = 0; i < 4; i++) {
        RectangleShape PtimerShape(Vector2f(powerUpTimerRects[i].width, powerUpTimerRects[i].height));
        PtimerShape.setPosition(powerUpTimerRects[i].left, powerUpTimerRects[i].top);
        PtimerShape.setFillColor(powerUpTimerColors[i]);
        window.draw(PtimerShape);
    }
}


void generatePowerUp(float powerupCords[][2], bool powerupActive[], int powerupType[], float powerupTimer[], int powerups_Max,float honeycombX, float honeycombY) {
    const float powerUp_timer = 10.0f;
    for (int j = 0; j < powerups_Max; j++) {
        if (!powerupActive[j]) {
            powerupType[j] = rand() % 4;
            powerupCords[j][0] = honeycombX;
            powerupCords[j][1] = honeycombY;
            powerupActive[j] = true;
            powerupTimer[j] = powerUp_timer; 
            break;
        }
    }
}
void powerHandler(float powerTimer[], bool power[], float& sizemultiplier, float& speedmultiplier) {
  // this function is needed to disable two same power ups 
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
    //this code over here disables two opposing powers and when its time runs out
    for (int i = 0; i < 4; i++) {
        if (powerTimer[i] > 0) {
            powerTimer[i] -= 0.002f;
        } else {
            powerTimer[i] = 0;
      
            switch(i) {
                case 0: 
                    if (power[0]) {
                        power[0] = false;
                        speedmultiplier = 1.0f;
                    }
                    break;
                case 1: 
                    if (power[1]) {
                        power[1] = false;
                        speedmultiplier = 1.0f;
                    }
                    break;
                case 2: 
                    if (power[2]) {
                        power[2] = false;
                        sizemultiplier = 1.0f;
                    }
                    break;
                case 3: 
                    if (power[3]) {
                        power[3] = false;
                        sizemultiplier = 1.0f;
                    }
                    break;
          }
      }
    }
    
    }


////////////////////INFANT BEEEEEEEEEEEEE///////////////////////////////////////


void initializeinfantBee_arrays(float**& infantBeeCordinates, bool*& infantBeesActive, int maxInfantBees){

  infantBeeCordinates = new float*[maxInfantBees];
    for(int i = 0; i< maxInfantBees; i++){
      infantBeeCordinates[i] = new float[2];
      }
    infantBeesActive = new bool[maxInfantBees];

    
    for (int i = 0; i < maxInfantBees; ++i) {
        infantBeeCordinates[i][0] = 0;
        infantBeeCordinates[i][1] = 0;
        infantBeesActive[i] = false;
    }
}


void expandInfantBeeArrays(float**& infantBeeCordinates, bool*& infantBeesActive, int& maxInfantBees) {

    int newCapacity = maxInfantBees +2;
    float** tempCordinates = new float*[newCapacity];
    for(int i = 0; i< newCapacity; i++){
      tempCordinates[i] = new float[2];
      }
    bool* tempActive = new bool[newCapacity];
    

    
    //making sure to replace old values into new expanded array 
    //NOTE: the new extra slots are intialized to default
    for (int i = 0; i < maxInfantBees; ++i) {
        tempCordinates[i][0] = infantBeeCordinates[i][0];
        tempCordinates[i][1] = infantBeeCordinates[i][1];
        tempActive[i] = infantBeesActive[i];}
    
    for (int i = maxInfantBees; i < newCapacity; ++i) {
        tempCordinates[i][0] = 0;
        tempCordinates[i][1] = 0;
        tempActive[i] = false;}
    
//over here we are deleting the older array to free up that memory so new expanded array can be referenced to it
    for (int i = 0; i < maxInfantBees; ++i) {
      delete[] infantBeeCordinates[i]; }
    delete[] infantBeeCordinates; 
    delete[] infantBeesActive;
    
    infantBeeCordinates = tempCordinates;        
    infantBeesActive = tempActive;
    maxInfantBees = newCapacity;
}

void addInfantBee(float x, float y, float**& infantBeeCordinates, bool*& infantBeesActive, int& maxInfantBees) {
    int index_first_inactive = -1;
    for (int i = 0; i < maxInfantBees; ++i) {
        if (!infantBeesActive[i]) {
            index_first_inactive = i;
            break;
        }
    }

    //if no active slot then expand the array and then we did minus 2 since the new inactive slot will be at the end of the new array
    if (index_first_inactive == -1) {
        expandInfantBeeArrays(infantBeeCordinates, infantBeesActive, maxInfantBees);
        index_first_inactive = maxInfantBees - 2;
    }

    infantBeeCordinates[index_first_inactive][0] = x;
    infantBeeCordinates[index_first_inactive][1] = y;
    infantBeesActive[index_first_inactive] = true;
}

// Move infant bees
void update_infantBees(float deltaTime, float honeycombX[], float honeycombY[], bool honeycombActive[], int honeycombs_Max, float**& infantBeeCordinates, bool*& infantBeesActive, int maxInfantBees, bool beesActive[], int beesTier[], bool beesDirection[], int bees_Max, int beeTypes[], float beesX[], float beesY[], float beehiveCord[][2], int beehives_Max, bool beehiveActive[], int beehiveTier[]) {
    const float INFANT_BEE_SPEED = 30.0f;
    const float WOBBLE = 1.0f * deltaTime;
    static bool wobbleDirection = false;
    /* 
    I gave wobble to the infant bee to simulate some wobbly infant bee
    we did some collision detection using bounding box and abs approach
    and yeah this function just checks deals with infant bee
    */
    for (int i = 0; i < maxInfantBees; ++i) {
        if (infantBeesActive[i]) {
          bool top_blocked = false;
           for (int j = 0; j < honeycombs_Max; ++j) {
                if (honeycombActive[j]) {
                if (abs(infantBeeCordinates[i][0] - honeycombX[j]) <= 32 && 
                        honeycombY[j] - (infantBeeCordinates[i][1] - 10) <= 1 && 
                        honeycombY[j] - (infantBeeCordinates[i][1] - 10) >= 0) {
                        top_blocked = true;              
                        bool left_Blocked = false;
                        bool right_Blocked = false;
                        for (int k = 0; k < honeycombs_Max; k++) {
                            if (honeycombActive[k]) {
                                if (abs(infantBeeCordinates[i][0] - honeycombX[k]) <= boxPixelsX && 
                                    honeycombX[k] < infantBeeCordinates[i][0]) {
                                    left_Blocked = true;
                                }
                                if (abs(infantBeeCordinates[i][0] - honeycombX[k]) <= 32 && 
                                    honeycombX[k] > infantBeeCordinates[i][0]) {
                                    right_Blocked = true;
                              }
                          }
                        }
                        //calculating infant bee tier for the beehive function
                        int infantBeeTier = (infantBeeCordinates[i][1]/32) + 1;
                        if (left_Blocked && right_Blocked) {
                            infantBeesActive[i] = false;
                            generateBeeHive( infantBeeCordinates[i][0], infantBeeCordinates[i][1], bees_Max,  beehiveCord,beehiveActive, beehives_Max, beehiveTier, infantBeeTier);}
                        else if (!left_Blocked) {
                            infantBeeCordinates[i][0] -= INFANT_BEE_SPEED * deltaTime;}
                        else if (!right_Blocked) {
                            infantBeeCordinates[i][0] += INFANT_BEE_SPEED * deltaTime;
                        break;}
                   }
                }
                }
            
            if (!top_blocked) {
                infantBeeCordinates[i][1] -= INFANT_BEE_SPEED * deltaTime;
                (wobbleDirection)? infantBeeCordinates[i][1] -= WOBBLE : infantBeeCordinates[i][1] += WOBBLE; //added a wobble to show organic movement cuz why not :p
                }

            if (infantBeeCordinates[i][1] <= 0) {
                infantBeesActive[i] = false;
                generate_hunterbee(infantBeeCordinates[i][0], infantBeeCordinates[i][1], bees_Max, beesActive, beesDirection, beesTier, beeTypes, beesX, beesY); 
                continue;
            }
          }
        }
}

void infantbee_spawner(float**& infantBeeCordinates, bool*& infantBeesActive,  float beehiveCord[][2], bool beehiveActive[], int beehives_Max, float beehiveCooldownTimers[], bool beehiveCanSpawn[], float deltaTime, Clock& globalSpawnTimer, int& maxInfantBees){
    const float MAX_SPAWN_INTERVAL = 10.0f;
    const float INITIAL_COOLDOWN = 5.0f;
    const float SHRINK_FACTOR = 0.3f;
    static int infantBeeCount = 0;

    // to keep the game difficultiy we use a combination of shrink factor and infant bee count as the count increases the timer limit decreases
    float timer_limit = MAX_SPAWN_INTERVAL - (SHRINK_FACTOR * infantBeeCount);
    timer_limit = max(5.0f, timer_limit);

//global spawn timer is compared against our dynamic spawn timer
    if (globalSpawnTimer.getElapsedTime().asSeconds() >= timer_limit) {
            int random_bee_hive = rand() % beehives_Max;
            if (beehiveActive[random_bee_hive] && beehiveCanSpawn[random_bee_hive]) {
                addInfantBee(beehiveCord[random_bee_hive][0], beehiveCord[random_bee_hive][1], infantBeeCordinates, infantBeesActive, maxInfantBees);
                beehiveCanSpawn[random_bee_hive] = false;
                beehiveCooldownTimers[random_bee_hive] = INITIAL_COOLDOWN;
                globalSpawnTimer.restart();
                infantBeeCount++;
            }

        for (int i = 0; i < beehives_Max; i++) {
            if (beehiveActive[i] && !beehiveCanSpawn[i]) {
                beehiveCooldownTimers[i] -= deltaTime;
            }
            if (beehiveCooldownTimers[i] <= 0) {
                beehiveCanSpawn[i] = true;
                beehiveCooldownTimers[i] = 0.0f;
            }
        }
    }
    else {
       
    }
}



void generate_hunterbee(float infantBeeX,float infantBeeY, int bees_Max, bool beesActive[], bool beesDirection[], int beesTier[], int beeTypes[], float beesX[], float beesY[]){
float lastROW = (gameRows - 3) * boxPixelsY;
//this function generates the hunter bee when the uh infant bee reaches top
  for(int i = 0; i <bees_Max;i++){
    if(!beesActive[i]){
      beesActive[i] = true;
      beeTypes[i] = 1; //1 = KILLER BEE
      beesX[i] = infantBeeX;
      beesY[i] = 0;
      beesDirection[i] = rand() % 2;
      beesTier[i] = 1;
      break;
      }
        }
}

bool checkInfantBeeCollision(float**& infantBeeCordinates, bool*& infantBeesActive, float bulletX, float bulletY, int& maxInfantBees, int& playerScore) {
    for (int i = 0; i < maxInfantBees; i++) {
        if (infantBeesActive[i]) {
            bool collided = (bulletX >= infantBeeCordinates[i][0] - 20 &&
                             bulletX <= infantBeeCordinates[i][0] + 20 &&
                             bulletY >= infantBeeCordinates[i][1] &&
                             bulletY <= infantBeeCordinates[i][1] + 20);
            
            if (collided) {
                infantBeesActive[i] = false;
                playerScore -= 500;
                return true;
            }
        }
    }
    
    return false;
}

// Cleanup function
void cleanupInfantBees(float**& infantBeeCordinates, bool*& infantBeesActive, int maxInfantBees) {

    for (int i = 0; i < maxInfantBees; ++i) {
        delete[] infantBeeCordinates[i]; 
    }
    
    
    delete[] infantBeeCordinates; 
    delete[] infantBeesActive;    
    infantBeeCordinates = nullptr;
    infantBeesActive = nullptr;
    maxInfantBees = 0;

}

void drawInfantBee(RenderWindow& window, float**& infantBeeCordinates, bool*& infantBeesActive, int maxInfantBees) {
    static Texture beeTexture;
    static bool isTextureLoaded = false;
    static int currentFrame = 0;
for (int index = 0; index < maxInfantBees; index++){
    if (infantBeesActive[index]) {
        if (!isTextureLoaded) {
            if (!beeTexture.loadFromFile("Sprites/BeeSheet.png")) {
                return;
            }
            isTextureLoaded = true;}
        Sprite beeSprite;
        beeSprite.setTexture(beeTexture);
        IntRect frames[] = {
            IntRect(0, 0, 32, 32),  
            IntRect(32, 0, 32, 32),  
            IntRect(64, 0, 32, 32), 
            IntRect(96, 0, 32, 32), 
            IntRect(128, 0, 32, 32) 
        };
        currentFrame = (currentFrame + 1) % 5;
        beeSprite.setTextureRect(frames[currentFrame]);
        beeSprite.setPosition(infantBeeCordinates[index][0], infantBeeCordinates[index][1]);
        window.draw(beeSprite);
    }
}
}



