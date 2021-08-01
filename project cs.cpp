#include <simplecpp>
#include <set>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <composite.h>
#include <sprite.h>
using namespace simplecpp;
using namespace std;

//movingObject.h
#ifndef _MOVINGOBJECT_INCLUDED_
#define _MOVINGOBJECT_INCLUDED_


#include <stdlib.h>
using namespace simplecpp;

int featureavail = 2;
int lives = 1;

void heading()
{

	cout<<"**********************************************************************************"<<endl;
	cout<<"**********************************************************************************"<<endl<<endl;
	cout<<"                       WELCOME TO THE                               "<<endl<<endl;
	cout<<"           ***             *      ******* *******  *******             "<<endl;
	cout<<"           ***            * *     **      **       *     *             "<<endl;
	cout<<"           ***          *** ***   ******* *******  *     *             "<<endl;
	cout<<"           *********   *********       **      **  *     *             "<<endl;
	cout<<"           ********* ****    **** ******* *******  *******             "<<endl<<endl;
	cout<<"**********************************************************************************"<<endl;
	cout<<"**********************************************************************************"<<endl;
	wait(3);
    if (system("CLS")) system("clear");

}

void rules()//All the rules
{
	cout<<"Welcome to the world of coins and lasso and the rules are as follows: "<<endl;
	cout<<"1. There is a lasso and there are multiple coins. You are supposed to catch the coins with the lasso."<<endl;
	cout<<"2. There are 4 types of coins Magnet, Bomb, MedKit and Normal:"<<endl;
	cout<<"  a. If you catch a magnet all the coins in a certain area will get attracted. "<<endl;
	cout<<"  b.If you catch a bomb you loose a life."<<endl;
	cout<<"  c. If u catch a MedKit you get an extra life."<<endl;
	cout<<"3. You Have 1 life but there are special coins called medkits which increase your life and feature called extra life "<<endl;
	cout<<"   which can increase the number of lives that you have."<<endl;
	cout<<"4. Everytime you yank the lasso the number of coins you have caught will be displayed."<<endl;
	cout<<"5. Number of the Lives left and Coins collected will also be displayed."<<endl;
	cout<<"6. There are 3 levels: "<<endl;
	cout<<"  a. In 1st level the difficulty level is easy."<<endl;
	cout<<"  b. 2nd level is attained after u collect 5 coins and the difficulty level is medium."<<endl;
	cout<<"  c. 3rd level is attained after collecting 10 coins from the start and it is hard."<<endl;
	cout<<"7. If you cross the 3rd level You win the game."<<endl;
	cout<<"8. The difficulty of the levels increases as the speed of the coin douls with each level."<<endl;
	cout<<"9. The controls are as follows:"<<endl;
	cout<<"  a. Press 'a' and 'd' to adjust the direction in which you want to launch the lasso."<<endl;
	cout<<"  b. Press 'w' and 's' respectively to increase and decrease the speed with which u want to launch the lasso."<<endl;
	cout<<"  c. Press 'y' to yank the lasso."<<endl;
	cout<<"  d. Press 'l' to loop the lasso."<<endl;
	cout<<"  e. Press 'e' to launch the lasso"<<endl;
	cout<<"  f. Press 'h' for help and then check the terminal."<<endl;
	cout<<"  g. Press 'i' to avail 2 extra lives by playing a guessing game."<<endl;
	cout<<"  h. Press 'q' to exit the game."<<endl;
	cout<<"10. The feature of extra life can be availed by pressing 'i'. To win and get an extra life you will have to "<<endl;
	cout<<"guess the number between 0-20 which the computer chose. This feature can only be used 2 times"<<endl;
	cout<<endl<<"Click on the Canvas to continue."<<endl;
	cout<<endl;
	wait(20);
	if (system("CLS")) system("clear");

}

//this is a small game which will give u an oppurtunity for an extra life if u win it

void extralife()
{
	featureavail--;
	int number = rand()%20;
	cout<<"For an extra life you will need to guess what number the computer chose between 0 - 20"<<endl;
	cout<<"Please enter your guess: "<<endl;
	int guess;
	cin>>guess;

	if(guess == number)
	{
		cout<<"Yeah!!!! You won and you get an extra Life!!"<<endl;
		lives++;
		cout<<"You can avail this feature "<<featureavail<<" times"<<endl;
		cout<<"Please return to your game."<<endl<<endl;
		return;
	}

	else
	{
		cout<<"Better Luck Nextime!!!"<<endl;
		cout<<"You can avail this feature "<<featureavail<<" times"<<endl;
		cout<<"Please return to your game."<<endl<<endl;
		return;
	}

}

class MovingObject : public Sprite {
public:
  vector<Sprite*> parts;
  double vx, vy;
  double ax, ay;
  bool paused;
  void initMO(double argvx, double argvy, double argax, double argay, bool argpaused=true) {
    vx=argvx; vy=argvy; ax=argax; ay=argay; paused=argpaused;
  }
 MovingObject(double argvx, double argvy, double argax, double argay, bool argpaused=true)
    : Sprite() {
    initMO(argvx, argvy, argax, argay, argpaused);
  }
 MovingObject(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : Sprite() {
   double angle_rad = angle_deg*PI/180.0;
   double argvx = speed*cos(angle_rad);
   double argvy = -speed*sin(angle_rad);
   initMO(argvx, argvy, argax, argay, argpaused);
  }
  void set_vx(double argvx) { vx = argvx; }
  void set_vy(double argvy) { vy = argvy; }
  void set_ax(double argax) { ax = argax; }
  void set_ay(double argay) { ay = argay; }
  double getXPos();
  double getYPos();
  void reset_all(double argx, double argy, double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta);

  void pause() { paused = true; }
  void unpause() { paused = false; }
  bool isPaused() { return paused; }

  void addPart(Sprite* p) {
    parts.push_back(p);
  }
  void nextStep(double t);
  void getAttachedTo(MovingObject *m);
};

#endif

//MovingObject.cpp

void MovingObject::nextStep(double t) {
  if(paused) { return; }
  //cerr << "x=" << getXPos() << ",y=" << getYPos() << endl;
  //cerr << "vx=" << vx << ",vy=" << vy << endl;
  //cerr << "ax=" << ax << ",ay=" << ay << endl;

  for(size_t i=0; i<parts.size(); i++){
    parts[i]->move(vx*t, vy*t);
  }
  vx += ax*t;
  vy += ay*t;
} // End MovingObject::nextStep()

double MovingObject::getXPos() {
  return (parts.size() > 0) ? parts[0]->getX() : -1;
}

double MovingObject::getYPos() {
  return (parts.size() > 0) ? parts[0]->getY() : -1;
}

void MovingObject::reset_all(double argx, double argy, double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) {
  for(size_t i=0; i<parts.size(); i++){
    parts[i]->moveTo(argx, argy);
  }
  double angle_rad = angle_deg*PI/180.0;
  double argvx = speed*cos(angle_rad);
  double argvy = -speed*sin(angle_rad);
  vx = argvx; vy = argvy; ax = argax; ay = argay; paused = argpaused;
} // End MovingObject::reset_all()

void MovingObject::getAttachedTo(MovingObject *m) {
  double xpos = m->getXPos();
  double ypos = m->getYPos();
  for(size_t i=0; i<parts.size(); i++){
    parts[i]->moveTo(xpos, ypos);
  }
  initMO(m->vx, m->vy, m->ax, m->ay, m->paused);
}

//coin.h
#ifndef __COIN_H__
#define __COIN_H__



class Coin : public MovingObject {

  public:
  double coin_start_x;
  double coin_start_y;
  double release_speed;
  double release_angle_deg;
  double coin_ax;
  double coin_ay;
  string type; //Introducing a string to dinstinguish between types of coins

  // Moving parts
  Circle coin_circle;

 Coin(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    coin_ax = argax;
    coin_ay = argay;
    initCoin();
  }
  Coin(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta, string type) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    coin_ax = argax;
    coin_ay = argay;
    initCoin(type);
  }

  void initCoin();
  void initCoin(string t);
  void resetCoin();
  void nextStep(double t);

}; // End class Coin

#endif
vector<Coin*> mycoins;

//lasso.h
#ifndef __LASSO_H__
#define __LASSO_H__

//#define WINDOW_X 1200
//#define WINDOW_Y 960
#define WINDOW_X 800
#define WINDOW_Y 600

#define STEP_TIME 0.05

#define PLAY_X_START 100
#define PLAY_Y_START 0
#define PLAY_X_WIDTH (WINDOW_X-PLAY_X_START)
#define PLAY_Y_HEIGHT (WINDOW_Y-100)

#define LASSO_X_OFFSET 100
#define LASSO_Y_HEIGHT 100
#define LASSO_BAND_LENGTH LASSO_X_OFFSET
#define LASSO_THICKNESS 5

#define COIN_GAP 1

#define RELEASE_ANGLE_STEP_DEG 5
#define MIN_RELEASE_ANGLE_DEG 0
#define MAX_RELEASE_ANGLE_DEG (360-RELEASE_ANGLE_STEP_DEG)
#define INIT_RELEASE_ANGLE_DEG 45

#define RELEASE_SPEED_STEP 20
#define MIN_RELEASE_SPEED 0
#define MAX_RELEASE_SPEED 200
#define INIT_RELEASE_SPEED 100

#define COIN_SPEED 120
#define COIN_ANGLE_DEG 90

#define LASSO_G 30
#define COIN_G 30

#define LASSO_SIZE 10
#define LASSO_RADIUS 50
#define COIN_SIZE 5

class Lasso : public MovingObject {
  double lasso_start_x;
  double lasso_start_y;
  double release_speed;
  double release_angle_deg;
  double lasso_ax;
  double lasso_ay;
  int mindist = LASSO_RADIUS; //minimum distance between the coin and the center

  // Moving parts
  Circle lasso_circle;
  Circle lasso_loop;

  // Non-moving parts
  Line lasso_line;
  Line lasso_band;

  // State info
  bool lasso_looped;
  set <Coin*> the_coin;//introducing a set to store the pointers of coins which are being yanked
  int num_coins;

  void initLasso();
 public:
 Lasso(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    lasso_ax = argax;
    lasso_ay = argay;
    initLasso();
  }

  void draw_lasso_band();
  void yank();
  void loopit();
  void addAngle(double angle_deg);
  void addSpeed(double speed);

  void nextStep(double t);
  void check_for_coin(Coin *coin);
  int getNumCoins() { return num_coins; }

}; // End class Lasso

#endif

//coin.h

void Coin::initCoin() {
  int startx = (rand()%(700-100+1)+100);
  int starty = (rand()%(450));
  coin_start_x = startx;
  coin_start_y = starty;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  coin_circle.setColor(COLOR("blue"));
  coin_circle.setFill(true);
  addPart(&coin_circle);
}

void Coin::initCoin(string t) {
  int startx = (rand()%(700-100+1)+100);
  int starty = (rand()%(450));
  coin_start_x = startx;
  coin_start_y = starty;
  type = t;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  //Assigning colors according to their types
  if(t == "magnet")
  {
  	  coin_circle.setColor(COLOR("red"));
      coin_circle.setFill(true);
  }
  else if(t == "bomb")
  {
  	  coin_circle.setColor(COLOR("black"));
      coin_circle.setFill(true);
  }
  else if(t == "medkit")
  {
  	  coin_circle.setColor(COLOR("green"));
      coin_circle.setFill(true);
  }
  else
  {
  	  coin_circle.setColor(COLOR("blue"));
  	  coin_circle.setFill(true);
  }
  addPart(&coin_circle);
}

void Coin::resetCoin() {
  int angle = (rand()%(180)); // randomizing angle
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = angle;
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}

void Coin::nextStep(double t) { //increasing the velocity
  if(paused) { return; }
  //cerr << "x=" << getXPos() << ",y=" << getYPos() << endl;
  //cerr << "vx=" << vx << ",vy=" << vy << endl;
  //cerr << "ax=" << ax << ",ay=" << ay << endl;

  for(size_t i=0; i<parts.size(); i++){
    parts[i]->move(vx*t, vy*t);
  }
  double x = getXPos();
  double y = getYPos();
  vx += ax*t;
  vy += ay*t;
  if(fabs(x-PLAY_X_START)<(1e-5) || fabs(x-WINDOW_X)<(1e-5))
  {
  	vy = -vy;
  }
  else if(fabs(y)<(1e-5) || fabs(y-PLAY_Y_HEIGHT)<(1e-5))
  {
  	vx = -vy;
  }
} // End MovingObject::nextStep()


//lasso.cpp

void Lasso::draw_lasso_band() {
  double len = (release_speed/MAX_RELEASE_SPEED)*LASSO_BAND_LENGTH;
  double arad = release_angle_deg*PI/180.0;
  double xlen = len*cos(arad);
  double ylen = len*sin(arad);
  lasso_band.reset(lasso_start_x, lasso_start_y, (lasso_start_x-xlen), (lasso_start_y+ylen));
  lasso_band.setThickness(LASSO_THICKNESS);
} // End Lasso::draw_lasso_band()

void Lasso::initLasso() {
  lasso_start_x = (PLAY_X_START+LASSO_X_OFFSET);
  lasso_start_y = (PLAY_Y_HEIGHT-LASSO_Y_HEIGHT);
  lasso_circle.reset(lasso_start_x, lasso_start_y, LASSO_SIZE);
  lasso_circle.setColor(COLOR("red"));
  lasso_circle.setFill(true);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setColor(COLOR("green"));
  lasso_loop.setFill(true);
  addPart(&lasso_circle);
  addPart(&lasso_loop);
  lasso_looped = false;
  num_coins = 0;
  lasso_line.reset(lasso_start_x, lasso_start_y, lasso_start_x, lasso_start_y);
  lasso_line.setColor(COLOR("green"));

  lasso_band.setColor(COLOR("blue"));
  draw_lasso_band();

} // End Lasso::initLasso()

void Lasso::yank() {
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setFill(true);
  lasso_looped = false;
  for(auto coin: the_coin)//iterating throught the set and increasing the number of coins caught
  {
  	if(coin != NULL) {
        num_coins++;
        coin->resetCoin();
    }
  }
  the_coin.clear(); //clearing the set or deleting all the elements once the coins are counted
  mindist = LASSO_RADIUS;
  char caught_coin[5];
  Text caughtCoinText(WINDOW_X/2,100,caught_coin);
  sprintf(caught_coin, "You Caught %d coins", i); //showing the number of coins caught
  caughtCoinText.setMessage(caught_coin);
  wait(2);
} // End Lasso::yank()

void Lasso::loopit() {
  if(lasso_looped) { return; } // Already looped
  lasso_loop.reset(getXPos(), getYPos(), LASSO_RADIUS);
  lasso_loop.setFill(false);
  lasso_looped = true;
} // End Lasso::loopit()

void Lasso::addAngle(double angle_deg) {
  release_angle_deg += angle_deg;
  if(release_angle_deg < MIN_RELEASE_ANGLE_DEG) { release_angle_deg = MIN_RELEASE_ANGLE_DEG; }
  if(release_angle_deg > MAX_RELEASE_ANGLE_DEG) { release_angle_deg = MAX_RELEASE_ANGLE_DEG; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addAngle()

void Lasso::addSpeed(double speed) {
  release_speed += speed;
  if(release_speed < MIN_RELEASE_SPEED) { release_speed = MIN_RELEASE_SPEED; }
  if(release_speed > MAX_RELEASE_SPEED) { release_speed = MAX_RELEASE_SPEED; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addSpeed()

void Lasso::nextStep(double stepTime) {
  draw_lasso_band();
  MovingObject::nextStep(stepTime);
  if(getYPos() > PLAY_Y_HEIGHT)
  {
  	yank();
  }
  lasso_line.reset(lasso_start_x, lasso_start_y, getXPos(), getYPos());
} // End Lasso::nextStep()

void Lasso::check_for_coin(Coin *coinPtr) {
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double coin_x = coinPtr->getXPos();
  double coin_y = coinPtr->getYPos();
  double xdiff = (lasso_x - coin_x);
  double ydiff = (lasso_y - coin_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
  if(distance <=  mindist)
  {
    the_coin.insert(coinPtr);//adding the pointer of the coin to the_coin set defined earlier
    coinPtr->getAttachedTo(this);
    if((coinPtr -> type == "magnet"))//changing the minimum distance accordin to the type of the coin caught 
    {
  		mindist = 300;
	}
	else if((coinPtr -> type == "bomb"))
	{
		lives--;//decreasing the lives
		mindist = -1;
	}
	if(coinPtr -> type == "medkit")
	{
		lives ++;//increasing the lives
	}
  }
} // End Lasso::check_for_coin()



main_program {

  heading();
  rules();
  initCanvas("Lasso", WINDOW_X, WINDOW_Y);
  getClick();
  int stepCount = 0;
  float stepTime = STEP_TIME;
  float runTime = -1; // sec; -ve means infinite
  float currTime = 0;


  char level[3];
  int levels = 1;
  Text levelindicator(WINDOW_X/2,480,level);


  // Draw lasso at start position
  double release_speed = INIT_RELEASE_SPEED; // m/s
  int angle_lasso = (rand()%(180));//randomizing the motion
  double release_angle_deg = angle_lasso; // degrees
  double lasso_ax = 0;
  double lasso_ay = LASSO_G;
  bool paused = true;
  bool rtheta = true;
  Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);

  Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
  b1.setColor(COLOR("blue"));
  Line b2(PLAY_X_START, 0, PLAY_X_START, WINDOW_Y);
  b2.setColor(COLOR("blue"));

  settextstyle(3,0,1);
  string msg("Cmd: _");
  Text charPressed(PLAY_X_START+50, PLAY_Y_HEIGHT+20, msg);
  char coinScoreStr[256];

  char live[256];
  sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
  Text coinScore(PLAY_X_START+50, PLAY_Y_HEIGHT+50, coinScoreStr);

  Text lv(WINDOW_X/2,550,live);//showing number of lives left

  Text help(710,580,"Press 'h' to help");

  Text instructions(WINDOW_X/2,WINDOW_Y/2,"Check the terminal for further instructions");
  instructions.hide();

  Text extralifefeature(670,560,"Press 'i' to get an extra life");

  Text nolife(WINDOW_X/2,WINDOW_Y/2,"Sorry you can't avail this feature!! TOO BADD!!");
  nolife.hide();

  int nocoins = rand()%10 + 1;
  int t=0;
  while(t<nocoins)//initialising the coins along with the special coins
  {
  	paused = true; rtheta = true;
    double coin_speed = COIN_SPEED;//120 m/s
    int angle_coin = (rand()%(180));
    double coin_angle_deg = angle_coin;//90 degrees
    double coin_ax = 0;
    double coin_ay = COIN_G;//30
	if(t == 1)
	{
		Coin* my_current_coin = new Coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta, "bomb");
    	mycoins.push_back(my_current_coin);
   		t++;
		continue;
	}
	if(t == 2)
	{
		Coin* my_current_coin = new Coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta, "magnet");
    	mycoins.push_back(my_current_coin);
   		t++;
   		continue;
	}
	if(t == 3)
	{
		Coin* my_current_coin = new Coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta, "medkit");
    	mycoins.push_back(my_current_coin);
   		t++;
   		continue;
	}
    Coin* my_current_coin = new Coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta, "normal");
    mycoins.push_back(my_current_coin);
    t++;
  }


  // After every COIN_GAP sec, make the coin jump
  double last_coin_jump_end = 0;

  // When t is pressed, throw lasso
  // If lasso within range, make coin stick
  // When y is pressed, yank lasso
  // When l is pressed, loop lasso
  // When q is pressed, quit
  bool check_lvl3 = true;//checking when to increase the level will be used further
  bool check_lvl2 = true;
  bool check_lvl1 = true;

  while(lives>0 && lasso.getNumCoins() < 15) {


    if((runTime > 0) && (currTime > runTime)) { break; }
        //declaration of a new coin
    if(mycoins.size()<= 10)//keeping the number of coins = 10
    {
        paused = true; rtheta = true;
        double coin_speed = COIN_SPEED;//120 m/s
        int angle_coin = (rand()%(180));
        double coin_angle_deg = angle_coin;//90 degrees
        double coin_ax = 0;
        double coin_ay = COIN_G;//30
        Coin* my_current_coin = new Coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
        mycoins.push_back(my_current_coin);
    }

    if(check_lvl1)//checking whether the player has crossed level 1
    {
    	if(lasso.getNumCoins()>=5)
    	{
    		levels ++;
	    	for(auto coin: mycoins)
	    	{
	    		coin->vx *= 2;
	    		coin->vy *= 2;
			}
			check_lvl1 = false;
		}
	}

    if(check_lvl2)//checking whether the player has crossed level 2
    {
    	if(lasso.getNumCoins()>=10)
    	{
    		levels ++;
	    	for(auto coin: mycoins)
	    	{
	    		coin->vx *= 2;
	    		coin->vy *= 2;
			}
			check_lvl2 = false;
		}
	}

    if(check_lvl3)//checking whether the player has crossed level 3
    {
    	if(lasso.getNumCoins()>=15)
    	{
    		levels ++;
	    	for(auto coin: mycoins)
	    	{
	    		coin->vx *= 2;//increasing the speed with each level
	    		coin->vy *= 2;
			}
			check_lvl3 = false;
		}
	}

	sprintf(level, "LEVEL %d", levels);
  	levelindicator.setMessage(level);//displaying the level

	    //declaration over
    bool br = false;
    XEvent e;
    bool pendingEv = checkEvent(e);
    if(pendingEv) {
      char c = charFromEvent(e);
      msg[msg.length()-1] = c;
      charPressed.setMessage(msg);
      switch(c) {
      case 't':
		lasso.unpause();
		break;
      case 'y':
		lasso.yank();
		break;
      case 'l':
		lasso.loopit();
		for(auto coin:mycoins)
		{
	      lasso.check_for_coin(coin);
	    }
		//wait(STEP_TIME*5);
		break;
      case 'a':
		if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
		break;
      case 'd':
		if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
		break;
	  case 's':
		if(lasso.isPaused()) { lasso.addSpeed(-RELEASE_SPEED_STEP); }
		break;
      case 'w':
		if(lasso.isPaused()) { lasso.addSpeed(+RELEASE_SPEED_STEP); }
		break;
      case 'q':
	    br = true;
	    break;
      case 'h': // showing the instructions again
	    instructions.show();
	    wait(3);
	    instructions.hide();
	    rules();
    	break;
      case 'i': // activating the extra life game
	    if(featureavail>0)
	    {
	    	instructions.show();
	    	wait(3);
	    	instructions.hide();
	    	extralife();
		}
		else
		{
			nolife.show();
			wait(2);
			nolife.hide();
		}
		break;
      default:
	    break;
      }
    }

    if(br)
    {
        break;
    }

    lasso.nextStep(stepTime);

    for(auto coin: mycoins)
    {
        if(coin != nullptr)
        {
          coin -> nextStep(stepTime);
          if(coin -> isPaused()) {
            if((currTime-last_coin_jump_end) >= COIN_GAP) {
             coin -> unpause();
            }
          }

          if(coin -> getYPos() > PLAY_Y_HEIGHT) {
            coin -> resetCoin();
            last_coin_jump_end = currTime;
            }
        }
    }

    sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());//showing the score
    coinScore.setMessage(coinScoreStr);

    sprintf(live, "You have %d lives left", lives); //showing the number of lives
    lv.setMessage(live);

    stepCount++;
    currTime += stepTime;
    wait(stepTime);
  } // End for while when lives get over or num_coins = 15

  //Showcasing the final score before exiting the program
  if(lasso.getNumCoins() == 15)
  {
  	Text win(WINDOW_X/2, 250, "Congrats!! YOU Won!!!");
  }
  Text finalScore(WINDOW_X/2,WINDOW_Y/2,coinScoreStr); // showing the final score once the game ends
  sprintf(coinScoreStr, "Your Score is %d", lasso.getNumCoins());
  finalScore.setMessage(coinScoreStr);

  wait(3);
} // End main_program
