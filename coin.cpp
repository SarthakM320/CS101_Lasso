#include "coin.h"
#include "lasso.h"

void Coin::initCoin() {
  int startx = (rand()%(700-100+1)+100);
  int starty = (rand()%(450));
  coin_start_x = startx;
  coin_start_y = starty;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  coin_circle.setColor(COLOR("blue"));
  coin_circle.setFill(true);
  addPart(&coin_circle);
  cout<<"Coin initialised"<<endl; 
}
void Coin::initCoin(string t) {
  int startx = (rand()%(700-100+1)+100);
  int starty = (rand()%(450));
  coin_start_x = startx;
  coin_start_y = starty;
  type = t;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  coin_circle.setColor(COLOR("blue"));
  coin_circle.setFill(true);
  addPart(&coin_circle);
  cout<<"Coin initialised"<<endl; 
}

void Coin::resetCoin() {
  int angle = (rand()%(180))
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
  if(getXpos<)
  vx += ax*t;
  vy += ay*t;
} // End MovingObject::nextStep()

