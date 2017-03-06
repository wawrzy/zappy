#include <strings.h>
#include <iostream>
#include <sstream>
#include "Player.hpp"

Player::Player(std::string name, std::string team, zappy::ORIENTATION orientation, int level, int x, int y, MapTrantor const & map) : _anim(this->_sprite), _map(map)
{
    this->_name = name;
    this->_team = team;
    this->_orientation = orientation;
    this->_level = level;
    this->_oldlevel = level;
    this->_x = x;
    this->_y = y;
    this->_incantation = false;
    this->_fork = false;

    this->_inventory[0] = 0;
    this->_inventory[1] = 0;
    this->_inventory[2] = 0;
    this->_inventory[3] = 0;
    this->_inventory[4] = 0;
    this->_inventory[5] = 0;
    this->_inventory[6] = 0;

    this->_image.push_back(sf::Image());
    this->_texture.push_back(sf::Texture());
    for (unsigned int i = 1; i <= 8; i ++) {
        std::ostringstream os;
        os << i;
        this->_image.push_back(sf::Image());
        this->_texture.push_back(sf::Texture());
        this->_image[i].loadFromFile("graphic/media/sdl_files/mage_charset" + os.str() + ".bmp");
        this->_image[i].createMaskFromColor(sf::Color::Blue);

        this->_texture[i].loadFromImage(this->_image[i]);
    }

    this->_timeToMove = 20;
    this->_sprite.setTexture(this->_texture[this->_level]);
    this->_anim.startIdle();
    this->_anim.update(0);
    this->_oldX = x;
    this->_oldY = y;
    this->_sprite.setPosition(this->getPixelX(x, y), this->getPixelY(x, y));
    this->_lastTick = -1;
    this->_startTick = -1;
    this->alive = true;

    this->_tickLeftBroadcast = 0;
    this->_imageBroadcast.loadFromFile("graphic/media/sdl_files/broadcast.bmp");
    this->_imageBroadcast.createMaskFromColor(sf::Color::Blue);
    this->_textureBroadcast.loadFromImage(this->_imageBroadcast);
    this->_spriteBroadcast.setTexture(this->_textureBroadcast);

    if (!this->_soundBufferBroadcast.loadFromFile("graphic/media/Sound of a Murloc.wav"))
        std::cout << "Fail load" << std::endl;
    this->_soundBroadcast.setBuffer(this->_soundBufferBroadcast);
    this->_soundBroadcast.setVolume(MAX_VOLUME_MURLOC);
}

Player::~Player()
{
}

std::string Player::getName() const
{
    return (this->_name);
}

std::string Player::getTeam() const
{
    return (this->_team);
}

zappy::ORIENTATION Player::getOrientation() const
{
    return (this->_orientation);
}

void Player::setOrientation(zappy::ORIENTATION orientation)
{
    this->_anim.setOrientation(orientation);
    this->_orientation = orientation;
}

void    Player::addRessource(enum RESSOURCE it, int nb)
{
    this->_inventory[it] += nb;
}

void    Player::delRessource(enum RESSOURCE it, int nb)
{
    this->_inventory[it] -= nb;
}

void Player::setLevel(int level)
{
    this->_level = level;
}

int Player::getLevel() const
{
    return (this->_level);
}

void Player::setPos(int x, int y)
{
    this->_x = x;
    this->_y = y;
}

int Player::getPosX() const
{
    return (this->_x);
}

int Player::getPosY() const
{
    return (this->_y);
}

void Player::setIncantation(bool status)
{
    this->_incantation = status;
}

bool Player::getIncantation() const
{
    return (this->_incantation);
}

int Player::getRessource(enum RESSOURCE id)
{
    return (this->_inventory[id]);
}

void Player::setFork(bool status)
{
    this->_fork = status;
}

bool Player::getFork() const
{
    return (this->_fork);
}

void Player::moveTo(int x, int y, zappy::ORIENTATION orientation) {
    this->_startTick = this->_lastTick;
    this->_oldX = this->_x;
    this->_oldY = this->_y;
    this->_x = x;
    this->_y = y;
    if (this->_getDistance() > 2.5) {
        this->_oldX = this->_x;
        this->_oldY = this->_y;
    }
    this->_anim.setOrientation(orientation);
    if (this->_oldX != this->_x || this->_y != this->_oldY) {
        this->_anim.startMove(this->_timeToMove);
    }
}

void Player::update(int tick) {
    if (this->_oldlevel != this->_level) {
        this->_oldlevel = this->_level;
        this->_sprite.setTexture(this->_texture[this->_level]);
    }

    this->_anim.update(tick);
    if (this->_x != this->_oldX || this->_y != this->_oldY) {
        this->_oldX = this->_updateX();
        this->_oldY = this->_updateY();
        this->_sprite.setPosition(this->getPixelX(this->_oldX, this->_oldY), this->getPixelY(this->_oldX, this->_oldY));
    }
    this->_sprite.setPosition(this->getPixelX(this->_oldX, this->_oldY), this->getPixelY(this->_oldX, this->_oldY));
    this->_updateBroadcast();
    this->_lastTick = tick;
}

float Player::getPixelX(float x, float y) {
    return this->_map.getPixelX(x, y) - (this->_sprite.getTextureRect().width / 2) + (this->_map.getTexture().getSize().x / 2);
}

float Player::getPixelY(float x, float y) {
    return this->_map.getPixelY(x, y) - (this->_sprite.getTextureRect().height) + 15;
}

sf::Sprite const &Player::getSprite() const {
    return this->_sprite;
}

void Player::activeBroadcast(int tick) {
    this->_tickLeftBroadcast = tick;
    this->_soundBroadcast.play();
}

bool Player::isBroadcasting() const {
    return this->_tickLeftBroadcast > 0;
}

sf::Sprite const & Player::getBroadcastSprite() {
    return this->_spriteBroadcast;
}

sf::Sound & Player::getBroadcastSound() {
    return this->_soundBroadcast;
}

zappy::AnimationPlayer const & Player::getAnim() const {
    return this->_anim;
}

zappy::AnimationPlayer & Player::getAnim() {
    return this->_anim;
}

bool Player::isAlive() const {
    return this->alive;
}

void Player::kill() {
    this->alive = false;
}

float Player::_updateX() {
    if (this->_oldX < this->_x) {
        this->_oldX += 1 /  static_cast<float>(this->_timeToMove);
        if (this->_oldX > this->_x)
            this->_oldX = this->_x;
    } else if (this->_oldX > this->_x) {
        this->_oldX -= 1 /  static_cast<float>(this->_timeToMove);
        if (this->_oldX < this->_x)
            this->_oldX = this->_x;
    }
    return this->_oldX;
}

float Player::_updateY() {
    if (this->_oldY < this->_y) {
        this->_oldY += 1 /  static_cast<float>(this->_timeToMove);
        if (this->_oldY > this->_y)
            this->_oldY = this->_y;
    } else if (this->_oldY > this->_y) {
        this->_oldY -= 1 /  static_cast<float>(this->_timeToMove);
        if (this->_oldY < this->_y)
            this->_oldY = this->_y;
    }
    return this->_oldY;
}

void Player::_updateBroadcast() {
    if (this->_tickLeftBroadcast > 0){
        this->_tickLeftBroadcast -= 1;
        this->_spriteBroadcast.setPosition(this->_sprite.getPosition().x, this->_sprite.getPosition().y - this->_textureBroadcast.getSize().y + 20);
    }
}

float Player::_getDistance() {
    //return (ABS(this->_y - this->_oldY) + ABS(this->_x - this->_oldX));
    return sqrt(pow(this->_x - this->_oldX, 2) + pow(this->_y - this->_oldY, 2));
}