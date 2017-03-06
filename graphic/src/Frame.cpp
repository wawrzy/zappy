//
// Created by rottaf on 6/14/16.
//

#include <iostream>
#include "Frame.hh"

zappy::Frame::Frame() {
  this->loop = false;
}

zappy::Frame::~Frame() {

}

void zappy::Frame::setOrigin(sf::IntRect const &rect) {
  this->origin = rect;
}

sf::IntRect const &zappy::Frame::getOrigin() const {
  return this->origin;
}

std::vector<int> const &zappy::Frame::getIndexs() const {
  return this->indexs;
}

std::vector<int> &zappy::Frame::getIndexs() {
  return this->indexs;
}

void zappy::Frame::setIndexs(std::vector<int> const &idxs) {
  this->indexs = idxs;
}

void zappy::Frame::setLoop(bool bo) {
  this->loop = bo;
}

bool zappy::Frame::getLoop() const {
  return this->loop;
}

void zappy::Frame::setMaxTime(int time) {
  this->max_time = time;
}

int zappy::Frame::getMaxTime() const {
  return this->max_time;
}

sf::IntRect const zappy::Frame::getSubRect() const {
  return sf::IntRect(this->origin.left + this->mapFrame[this->indexs[this->actual_i]].left,
                     this->origin.top,
                     this->mapFrame[this->indexs[this->actual_i]].width,
                     this->mapFrame[this->indexs[this->actual_i]].height);
}

void zappy::Frame::update(int tick) {
  if ((tick - this->start_tick) % (this->max_time / this->indexs.size()) == 0) {
    this->actual_i += 1;
    if (this->actual_i >= static_cast<int>(this->indexs.size())) {
      if (this->loop) {
        this->actual_i = 0;
      }
      else {
        this->actual_i -= 1;
      }
    }
  }
}

void zappy::Frame::start(int tick) {
  this->actual_i = 0;
  this->start_tick = tick;
}

void zappy::Frame::setMapFrame(std::vector<sf::IntRect> map) {
  this->mapFrame = map;
}

int zappy::Frame::getStartTick() const {
  return this->start_tick;
}
