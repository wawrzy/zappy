//
// Created by rottaf on 6/20/16.
//

#include <iostream>
#include "MapTrantor.hh"

MapTrantor::MapTrantor() {
  this->_image.loadFromFile("graphic/media/Square.png");

  this->_texture.loadFromImage(this->_image);

  this->_origX = 0;
  this->_origY = 0;
  this->_maxX = 0;
  this->_maxY = 0;
  this->_oldMaxX = 0;
  this->_oldMaxY = 0;

  this->_imageRes.loadFromFile("graphic/media/sdl_files/resources.bmp");
  this->_imageRes.createMaskFromColor(sf::Color::Blue);

  this->_textureRes.loadFromImage(this->_imageRes);
  
  this->_imageEgg.loadFromFile("graphic/media/sdl_files/egg.bmp");
  this->_imageEgg.createMaskFromColor(sf::Color::Blue);

  this->_textureEgg.loadFromImage(this->_imageEgg);
}

MapTrantor::~MapTrantor() {
  this->_cleanAll();
}

Case const *MapTrantor::getCase(int x, int y) const {
  return this->_cases[(y * this->_maxX) + x];
}

Case *MapTrantor::getCase(int x, int y) {
  return this->_cases[(y * this->_maxX) + x];
}

void MapTrantor::setCase(int x, int y, Case *newCase) {
  this->_cases[(y * this->_maxX) + x] = newCase;
}

std::vector<sf::Sprite *> const MapTrantor::getAllSprites() const {
  return this->_sprites;
}

std::list<sf::Sprite> const & MapTrantor::getAllResourcesSprites() {
  this->_spritesRes.clear();
  int decalX = (this->_texture.getSize().x / 2) - (this->_textureRes.getSize().x / NB_RESSOURCES / 2);
  int decalY = -(this->_textureRes.getSize().y / 2);
  int decalYEgg = -(this->_textureEgg.getSize().y / 2);
  int decalXEgg = (this->_texture.getSize().x / 2) - (this->_textureEgg.getSize().x / NB_RESSOURCES / 2);
  
  for (unsigned int i = 0; i < this->_cases.size(); i++) {
    std::list<DescRes> caseRes = this->_cases[i]->getAllResources();
    for (std::list<DescRes>::iterator it = caseRes.begin(); it != caseRes.end(); ++it) {
      this->_spritesRes.push_back(sf::Sprite(this->_textureRes));
      this->_spritesRes.back().setTextureRect(sf::IntRect((*it).type * (this->_textureRes.getSize().x / NB_RESSOURCES),
                                                          0,
                                                          (this->_textureRes.getSize().x / NB_RESSOURCES),
                                                          this->_textureRes.getSize().y));
      this->_spritesRes.back().setPosition(this->getPixelX((*it).pos.x, (*it).pos.y) + decalX, this->getPixelY((*it).pos.x, (*it).pos.y) + decalY);
    }
    
    std::list<DescRes> caseEgg = this->_cases[i]->getAllEggs();
    
    for (std::list<DescRes>::iterator it = caseEgg.begin(); it != caseEgg.end(); ++it) {
        this->_spritesRes.push_back(sf::Sprite(this->_textureEgg));
        this->_spritesRes.back().setPosition(this->getPixelX((*it).pos.x, (*it).pos.y) + decalXEgg, this->getPixelY((*it).pos.x, (*it).pos.y) + decalYEgg);
    }
    
    
  }
  return this->_spritesRes;
}

int MapTrantor::getMaxX() const {
  return this->_maxX;
}

void MapTrantor::setMaxX(int x) {
  this->_maxX = x;
}

int MapTrantor::getMaxY() const {
  return this->_maxY;
}

void MapTrantor::setMaxY(int y) {
  this->_maxY = y;
}

bool MapTrantor::hasSizeMapChanged() {
  if (this->_maxX != this->_oldMaxX || this->_maxY != this->_oldMaxY) {
    this->_oldMaxX = this->_maxX;
    this->_oldMaxY = this->_maxY;
    return true;
  }
  return false;
}

int MapTrantor::getOrigX() const {
  return this->_origX;
}

void MapTrantor::setOrigX(int x) {
  this->_origX = x;
  this->_resetPositionSprites();
}

int MapTrantor::getOrigY() const {
  return this->_origY;
}

void MapTrantor::setOrigY(int y) {
  this->_origY = y;
  this->_resetPositionSprites();
}

sf::Texture const &MapTrantor::getTexture() const {
  return this->_texture;
}

void MapTrantor::setTexture(sf::Texture &texture) {
  this->_texture = texture;
}

void MapTrantor::create(int x, int y) {
  this->_cleanAll();
  this->_maxX = x;
  this->_maxY = y;
  for (int i = 0; i < (x * y); i++) {
    this->_cases.push_back(new Case(i % this->_maxX, i / this->_maxX));
    this->_sprites.push_back(new sf::Sprite);
    this->_sprites.back()->setTexture(this->_texture);
    this->_sprites.back()->setPosition(this->getPixelX(i % this->_maxX, i / this->_maxX),
                                       this->getPixelY(i % this->_maxX, i / this->_maxX) - (this->_texture.getSize().y / 2));
  }
}

float MapTrantor::getPixelX(float x, float y) const {
  int caseSize = this->_texture.getSize().x / 2;
  return (caseSize * this->_maxX) + (y * caseSize) - (x * caseSize) + this->_origX;
}

float MapTrantor::getPixelY(float x, float y) const {
  int caseSize = this->_texture.getSize().y / 2;
  return (caseSize * this->_maxY) - (x * caseSize) - (y * caseSize) + this->_origY;
}

sf::Vector2i MapTrantor::getPosFromPixel(int pixelX, int pixelY) const {
  sf::Vector2i pos;

  int range = -1;
  int index = -1;
  for (unsigned int i = 0; i < this->_sprites.size(); i++) {
    int new_range = sqrt(pow(pixelX - (this->_sprites[i]->getPosition().x + (this->_texture.getSize().x / 2)), 2) +
                         pow(pixelY - (this->_sprites[i]->getPosition().y + (this->_texture.getSize().y / 2)), 2));
    if ((new_range < range || index == -1) && new_range < 60) {
      range = new_range;
      index = i;
    }
  }
  if (index != -1) {
    pos.x = index % this->_maxX;
    pos.y = index / this->_maxX;
  }
  else {
    pos.x = -1;
    pos.y = -1;
  }
  return (pos);
}

void MapTrantor::_cleanAll() {
  for (unsigned int i = 0; i < this->_cases.size(); i++) {
  //  delete this->_cases[i];
  }
  this->_cases.clear();

  for (unsigned int i = 0; i < this->_sprites.size(); i++) {
  //  delete this->_sprites[i];
  }
  this->_sprites.clear();
}

void MapTrantor::_resetPositionSprites() {
    for (int i = 0; i < (this->_maxX * this->_maxY); i++) {
    this->_sprites[i]->setPosition(this->getPixelX(i % this->_maxX, i / this->_maxX),
                                       this->getPixelY(i % this->_maxX, i / this->_maxX) - (this->_texture.getSize().y / 2));
  }
}