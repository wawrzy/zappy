//

#include <SFML/Graphics/Rect.hpp>
#include "AnimationPlayer.hh"

//
// Created by rottaf on 6/14/16.
//

zappy::DescAnimation::DescAnimation(const std::string &name, int speed, bool loop) : _name(name) {
  this->_speed = speed;
  this->_loop = loop;
}

zappy::AnimationPlayer::AnimationPlayer(sf::Sprite & sprite) : _sprite(sprite) {
  std::vector<sf::IntRect> mapFrame;
  for (int i = 0; i < 16; i++) {
    mapFrame.push_back(sf::IntRect(i * 34, 0, 34, 75));
  }
  mapFrame[9] = sf::IntRect(311, 0, 34, 75);
  mapFrame[10] = sf::IntRect(347, 0, 42, 75);
  mapFrame[11] = sf::IntRect(388, 0, 42, 75);
  mapFrame[12] = sf::IntRect(428, 0, 36, 75);
  mapFrame[13] = sf::IntRect(464, 0, 34, 75);
  mapFrame[14] = sf::IntRect(498, 0, 34, 75);
  mapFrame[15] = sf::IntRect(532, 0, 34, 75);

  this->_frame.setMapFrame(mapFrame);

  this->_indexAnimation["move1"].push_back(0);
  this->_indexAnimation["move1"].push_back(1);
  this->_indexAnimation["move1"].push_back(2);
  this->_indexAnimation["move1"].push_back(3);
  this->_indexAnimation["move1"].push_back(5);
  this->_indexAnimation["move1"].push_back(7);
  //this->_indexAnimation["move1"].push_back(8);

  this->_indexAnimation["move2"].push_back(0);
  this->_indexAnimation["move2"].push_back(1);
  this->_indexAnimation["move2"].push_back(2);
  this->_indexAnimation["move2"].push_back(3);
  this->_indexAnimation["move2"].push_back(4);
  this->_indexAnimation["move2"].push_back(5);
  this->_indexAnimation["move2"].push_back(6);
  this->_indexAnimation["move2"].push_back(7);
  //this->_indexAnimation["move2"].push_back(8);

  this->_indexAnimation["die1"].push_back(12);
  this->_indexAnimation["die1"].push_back(13);
  this->_indexAnimation["die1"].push_back(14);
  this->_indexAnimation["die1"].push_back(15);

  this->_indexAnimation["idle1"].push_back(8);
  this->_indexAnimation["idle1"].push_back(1);

  this->_indexAnimation["pickup"].push_back(12);
  this->_indexAnimation["pickup"].push_back(13);
  this->_indexAnimation["pickup"].push_back(14);
  this->_indexAnimation["pickup"].push_back(13);
  this->_indexAnimation["pickup"].push_back(12);

  this->_indexAnimation["incantation"].push_back(9);
  this->_indexAnimation["incantation"].push_back(10);
  this->_indexAnimation["incantation"].push_back(11);
  this->_indexAnimation["incantation"].push_back(12);
  this->_indexAnimation["incantation"].push_back(11);
  this->_indexAnimation["incantation"].push_back(10);

  this->setOrientation(zappy::SOUTH);
  this->_animated = true;
}

zappy::AnimationPlayer::~AnimationPlayer() {

}

void zappy::AnimationPlayer::setOrientation(zappy::ORIENTATION new_orientation) {
  switch (new_orientation) {
    case zappy::NORTH:
      this->_frame.setOrigin(sf::IntRect(0, 160, 0, 0));
      this->_move = "move2";
      break;
    case zappy::SOUTH:
      this->_frame.setOrigin(sf::IntRect(0, 70, 0, 0));
      this->_move = "move1";
      break;
    case zappy::WEST:
      this->_frame.setOrigin(sf::IntRect(0, 250, 0, 0));
      this->_move = "move2";
      break;
    case zappy::EAST:
      this->_frame.setOrigin(sf::IntRect(0, 0, 0, 0));
      this->_move = "move1";
      break;
    default:
      break;
  }
}

void zappy::AnimationPlayer::_clean() {
  this->_queueAnimation.clear();
  this->_queueAnimation.push_back(new DescAnimation("BEGIN"));
}

void zappy::AnimationPlayer::addMove(int speed, bool loop) {
  this->_queueAnimation.push_back(new DescAnimation(this->_move, speed, loop));
}

void zappy::AnimationPlayer::addDie(int speed, bool loop) {
  this->_queueAnimation.push_back(new DescAnimation("die1", speed, loop));
}

void zappy::AnimationPlayer::addIdle(int speed, bool loop) {
  this->_queueAnimation.push_back(new DescAnimation("idle1", speed, loop));
}

void zappy::AnimationPlayer::addPickUp(int speed, bool loop) {
  this->_queueAnimation.push_back(new DescAnimation("pickup", speed, loop));
}

void zappy::AnimationPlayer::addIncantation(int speed, bool loop){
  this->_queueAnimation.push_back(new DescAnimation("incantation", speed, loop));
}

void zappy::AnimationPlayer::startMove(int speed, bool loop) {
  this->_clean();
  this->addMove(speed, loop);
  this->addIdle();
}

void zappy::AnimationPlayer::startDie(int speed, bool loop) {
  this->_clean();
  this->addDie(speed, loop);
}

void zappy::AnimationPlayer::startIdle(int speed, bool loop) {
  this->_clean();
  this->addIdle(speed, loop);
}

void zappy::AnimationPlayer::startPickUp(int speed, bool loop) {
  this->_clean();
  this->addPickUp(speed, loop);
  this->addIdle();
}

void zappy::AnimationPlayer::startIncantation(int speed, bool loop) {
  this->_clean();
  this->addIncantation(speed, loop);
}

void zappy::AnimationPlayer::update(int tick) {
  if (! this->_queueAnimation.empty()) {
    this->_animated = true;
    if (this->_queueAnimation.front()->_name == "BEGIN" ||
        (! this->_queueAnimation.front()->_loop && tick - this->_frame.getStartTick() >= this->_queueAnimation.front()->_speed)) {

      delete this->_queueAnimation.front();
      this->_queueAnimation.pop_front();

      if (this->_queueAnimation.empty()) {
        return;
      }
      this->_frame.setIndexs(this->_indexAnimation[this->_queueAnimation.front()->_name]);
      this->_frame.start(tick);
      this->_frame.setMaxTime(this->_queueAnimation.front()->_speed);
      this->_frame.setLoop(this->_queueAnimation.front()->_loop);
    }

    this->_frame.update(tick);
    this->_sprite.setTextureRect(this->_frame.getSubRect());
  }
  else
    this->_animated = false;
}

bool zappy::AnimationPlayer::isAnimated() const {
  return this->_animated;
}