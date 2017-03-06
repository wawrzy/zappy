//
// Created by saum_j on 6/13/16.
//

#include <string>
#include <unistd.h>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include "Trantorien.hpp"
#include "Conversion.hpp"

void    Trantorien::initialise_cpylevel()
{
    this->cpy_level[1]["linemate"] = 1;
    this->cpy_level[1]["deraumere"] = 0;
    this->cpy_level[1]["sibur"] = 0;
    this->cpy_level[1]["mendiane"] = 0;
    this->cpy_level[1]["phiras"] = 0;
    this->cpy_level[1]["thystame"] = 0;
    this->cpy_level[1]["joueur"] = 1;

    this->cpy_level[2]["linemate"] = 1;
    this->cpy_level[2]["deraumere"] = 1;
    this->cpy_level[2]["sibur"] = 1;
    this->cpy_level[2]["mendiane"] = 0;
    this->cpy_level[2]["phiras"] = 0;
    this->cpy_level[2]["thystame"] = 0;
    this->cpy_level[2]["joueur"] = 2;

    this->cpy_level[3]["linemate"] = 2;
    this->cpy_level[3]["deraumere"] = 0;
    this->cpy_level[3]["sibur"] = 1;
    this->cpy_level[3]["mendiane"] = 0;
    this->cpy_level[3]["phiras"] = 2;
    this->cpy_level[3]["thystame"] = 0;
    this->cpy_level[3]["joueur"] = 2;

    this->cpy_level[4]["linemate"] = 1;
    this->cpy_level[4]["deraumere"] = 1;
    this->cpy_level[4]["sibur"] = 2;
    this->cpy_level[4]["mendiane"] = 0;
    this->cpy_level[4]["phiras"] = 1;
    this->cpy_level[4]["thystame"] = 0;
    this->cpy_level[4]["joueur"] = 4;

    this->cpy_level[5]["linemate"] = 1;
    this->cpy_level[5]["deraumere"] = 2;
    this->cpy_level[5]["sibur"] = 1;
    this->cpy_level[5]["mendiane"] = 3;
    this->cpy_level[5]["phiras"] = 0;
    this->cpy_level[5]["thystame"] = 0;
    this->cpy_level[5]["joueur"] = 4;

    this->cpy_level[6]["linemate"] = 1;
    this->cpy_level[6]["deraumere"] = 2;
    this->cpy_level[6]["sibur"] = 3;
    this->cpy_level[6]["mendiane"] = 0;
    this->cpy_level[6]["phiras"] = 1;
    this->cpy_level[6]["thystame"] = 0;
    this->cpy_level[6]["joueur"] = 6;

    this->cpy_level[7]["linemate"] = 2;
    this->cpy_level[7]["deraumere"] = 2;
    this->cpy_level[7]["sibur"] = 2;
    this->cpy_level[7]["mendiane"] = 2;
    this->cpy_level[7]["phiras"] = 2;
    this->cpy_level[7]["thystame"] = 1;
    this->cpy_level[7]["joueur"] = 6;
}

void	Trantorien::initialise_level()
{
    this->level[1]["linemate"] = 1;
    this->level[1]["deraumere"] = 0;
    this->level[1]["sibur"] = 0;
    this->level[1]["mendiane"] = 0;
    this->level[1]["phiras"] = 0;
    this->level[1]["thystame"] = 0;
    this->level[1]["joueur"] = 1;

    this->level[2]["linemate"] = 1;
    this->level[2]["deraumere"] = 1;
    this->level[2]["sibur"] = 1;
    this->level[2]["mendiane"] = 0;
    this->level[2]["phiras"] = 0;
    this->level[2]["thystame"] = 0;
    this->level[2]["joueur"] = 2;

    this->level[3]["linemate"] = 2;
    this->level[3]["deraumere"] = 0;
    this->level[3]["sibur"] = 1;
    this->level[3]["mendiane"] = 0;
    this->level[3]["phiras"] = 2;
    this->level[3]["thystame"] = 0;
    this->level[3]["joueur"] = 2;

    this->level[4]["linemate"] = 1;
    this->level[4]["deraumere"] = 1;
    this->level[4]["sibur"] = 2;
    this->level[4]["mendiane"] = 0;
    this->level[4]["phiras"] = 1;
    this->level[4]["thystame"] = 0;
    this->level[4]["joueur"] = 4;

    this->level[5]["linemate"] = 1;
    this->level[5]["deraumere"] = 2;
    this->level[5]["sibur"] = 1;
    this->level[5]["mendiane"] = 3;
    this->level[5]["phiras"] = 0;
    this->level[5]["thystame"] = 0;
    this->level[5]["joueur"] = 4;

    this->level[6]["linemate"] = 1;
    this->level[6]["deraumere"] = 2;
    this->level[6]["sibur"] = 3;
    this->level[6]["mendiane"] = 0;
    this->level[6]["phiras"] = 1;
    this->level[6]["thystame"] = 0;
    this->level[6]["joueur"] = 6;

    this->level[7]["linemate"] = 2;
    this->level[7]["deraumere"] = 2;
    this->level[7]["sibur"] = 2;
    this->level[7]["mendiane"] = 2;
    this->level[7]["phiras"] = 2;
    this->level[7]["thystame"] = 1;
    this->level[7]["joueur"] = 6;
}

Trantorien::Trantorien(std::string const team)
{
    this->_level = 1;
    this->_team = team;
    this->_id = -1;
    this->_cmd = 0;
    this->connected = false;
    this->dim_map = false;
    this->_to_go = -1;
    this->_group = 0;
    this->_search = "";
    this->_dir = "";
    this->_i_turn = 0;
    this->_incantation = true;
    this->_pose = false;
    this->_to_feed = 10;
    this->_can_be_co = 1;

    this->initialise_level();
    this->initialise_cpylevel();

    this->actions["pose"] = &Trantorien::takeInventory;
    this->actions["prend"] = &Trantorien::putInventory;
    this->actions["voir"] = &Trantorien::see;
    this->actions["inventaire"] = &Trantorien::Inventory;
    this->actions["incantation"] = &Trantorien::upLevel;
    this->to_move[1] = &Trantorien::move_forward;
    this->to_move[2] = &Trantorien::move_foleft;
    this->to_move[3] = &Trantorien::move_left;
    this->to_move[4] = &Trantorien::move_baleft;
    this->to_move[5] = &Trantorien::move_back;
    this->to_move[6] = &Trantorien::move_baright;
    this->to_move[7] = &Trantorien::move_right;
    this->to_move[8] = &Trantorien::move_foright;
}

Trantorien::~Trantorien()
{
  actions.clear();
  _messages.clear();
  friends.clear();
  level.clear();
  _inventory.clear();
  _see.clear();
}


//FONCTION D ENVOI AU SERVEUR
int Trantorien::move_forward(Network *network)
{
  std::queue<std::string> to_send;

  this->_i_turn = 0;
  this->command = "avance";
  to_send.push("avance");
  network->write_to_server(to_send);
  if (network->check_return(this) == -1)
    return (-1);
  return (0);
}

int Trantorien::Turn(Network *network)
{
  std::queue<std::string> to_send;

  ++this->_i_turn;
  this->command = this->_dir;
  to_send.push(this->_dir);
  network->write_to_server(to_send);
  this->_dir = "";
  if (network->check_return(this) == -1)
    return (-1);
  return (0);
}

int Trantorien::send_takeObject(std::string _object_, Network *network)
{
  std::queue<std::string> to_send;

  this->command = "prend ";
  this->command += _object_;
  to_send.push("prend ");
  to_send.push(_object_);
  network->write_to_server(to_send);
  if (network->check_return(this) == -1)
    return (-1);
  return (0);
}

int Trantorien::send_putObject(std::string _object_, Network *network)
{
  std::queue<std::string> to_send;

  this->command = "pose ";
  this->command += _object_;
  to_send.push("pose ");
  to_send.push(_object_);
  network->write_to_server(to_send);
  if (network->check_return(this) == -1)
    return (-1);
  return (0);
}

int Trantorien::fork(Network *network)
{
  std::queue<std::string> to_send;

  this->command = "fork";
  to_send.push("fork");
  network->write_to_server(to_send);
    if (network->check_return(this) == -1)
      return (-1);
    return (0);
}

int Trantorien::connect_nbr(Network *network)
{
  std::queue<std::string> to_send;

  this->command = "connect_nbr";
  to_send.push("connect_nbr");
  network->write_to_server(to_send);
    if (network->check_return(this) == -1)
      return (-1);
    return (0);
}

int Trantorien::send_see(Network *network)
{
  std::queue<std::string> to_send;

  this->command = "voir";
  to_send.push("voir");
  network->write_to_server(to_send);
    if (network->check_return(this) == -1)
      return (-1);
    return (0);
}

int Trantorien::send_eject(Network *network)
{
  std::queue<std::string> to_send;

  this->command = "expulse";
  to_send.push("expulse");
  network->write_to_server(to_send);
    if (network->check_return(this) == -1)
      return (-1);
    return (0);
}

int Trantorien::incantation(Network *network)
{
  std::queue<std::string> to_send;

  this->command = "incantation";
  to_send.push("incantation");
  network->write_to_server(to_send);
  if (network->check_return(this) == -1)
    return (-1);
    if (this->_incantation == false)
    {
        this->_incantation = true;
        return (0);
    }
  this->command = "incantation";
  if (network->check_return(this) == -1)
    return (-1);
    if (this->_incantation == false)
    {
        this->_incantation = true;
        return (0);
    }
  return (0);
}

int Trantorien::send_Inventory(Network *network)
{
  std::queue<std::string> to_send;

  this->command = "inventaire";
  to_send.push("inventaire");
  network->write_to_server(to_send);
  if (network->check_return(this) == -1)
    return (-1);
  return (0);
}

int Trantorien::send_message(std::string _message_, Network *network)
{
  std::queue<std::string> to_send;
  std::string message;
  Conversion convert(this->_team);

  this->command = "broadcast ";
  to_send.push("broadcast ");
  message = std::to_string(this->_cmd);
  ++_cmd;
  if (_cmd == 2147483647)
    _cmd = 0;
  message += " team:";
  message += this->_team;
  message += " assoc:";
  for (std::vector<int>::const_iterator it = this->friends.begin(); it != this->friends.end(); ++it) {
    message += std::to_string(*it);
    if (it + 1 != this->friends.end()) {
      message += ":";
    }
  }
  message += " moi:";
  message += std::to_string(this->_id);
  message += " message:";
  message += _message_;
  message += " LVL:";
  message += std::to_string(this->_level);
  this->command += message;
  to_send.push(convert.Crypt(message));
  network->write_to_server(to_send);
  if (this->_id == 0)
    this->_id = 1;
  if (network->check_return(this) == -1) {
      return (-1);
  }
  return (0);
}


//FONCTION POUR L IA
int Trantorien::ElementHere(int cases, std::string element)
{
  std::list<std::string> objects_case;
  int nb_player = 0;
  int to_return = -1;

  objects_case = this->_see[cases];
  for(std::list<std::string>::const_iterator it = objects_case.begin(); it != objects_case.end(); ++it)
    {
      if (*it == element)
	    to_return = cases;
      if (*it == "joueur")
        ++nb_player;
    }
    if (nb_player > 0 && element != "nourriture" && cases != 0)
      return (-1);
  return (to_return);
}

int Trantorien::ElementCases(std::string element)
{
  int cases = 0;
  int near = -1;
  int near_case = 0;
  int lvl = 0;

  while (lvl <= this->_level)
    {
      if (this->ElementHere(cases, element) != -1)
	{
	  this->_dir = "";
	  return (lvl);
	}
      ++lvl;
      near_case = cases + lvl;
      cases = cases + 2 * lvl;
      while (near_case < cases && near == -1)
	{
	  if (this->ElementHere(near_case, element) != -1)
	    {
	      this->_dir = "gauche";
	      near = lvl;
	    }
	  ++near_case;
	}
      while (++near_case <= cases + lvl && near == -1)
	{
	  if (this->ElementHere(near_case, element) != -1)
	    {
	      this->_dir = "droite";
	      near = lvl;
	    }
	}
    }
  return (near);
}

bool	connect_null(std::string _message)
{
  if (_message.find("moi:0") != std::string::npos && _message.find("message:connected") != std::string::npos)
    return (true);
  return (false);
}

int	add_id(int id)
{
  return (++id);
}

void	Trantorien::check_co()
{
  std::vector<std::string>::iterator it;
  std::map<int, std::map<std::string, int> > to_copy;

  while ((it = std::find_if(this->_messages.begin(), this->_messages.end(), connect_null)) != this->_messages.end())
    {
      this->_alive.clear();
      ++_id;
      to_copy[_id] = this->_inventory[_id - 1];
      std::transform(this->friends.begin(), this->friends.end(), this->friends.begin(), add_id);
      for (std::vector<int>::iterator it = this->friends.begin(); it != this->friends.end(); ++it)
	{
	  to_copy[*it] = this->_inventory[*it - 1];
    this->_alive[*it] = 0;
	}
      this->_inventory = to_copy;
      this->_messages.erase(it);
    }
}

std::vector<std::string>::iterator	Trantorien::message_item()
{
  int i = 0;
  size_t b_assoc;

  while (this->_messages.begin() + i != this->_messages.end())
    {
      b_assoc = (this->_messages[i]).find(std::to_string(_id));
      while (b_assoc != std::string::npos && (b_assoc == 0 || this->_messages[i][b_assoc - 1] != ':'
					      || !this->_messages[i][b_assoc + std::to_string(_id).length()] || (this->_messages[i][b_assoc + std::to_string(_id).length()] != ':' && this->_messages[i][b_assoc + std::to_string(_id).length()] != ' ')))
	b_assoc = this->_messages[i].find(std::to_string(_id), b_assoc + 1);
      if (b_assoc != std::string::npos && this->_messages[i].find("message:trouver ") != std::string::npos)
	return (this->_messages.begin() + i);
      ++i;
    }
  return (this->_messages.end());
}

void	Trantorien::checkItem()
{
  std::vector<std::string>::iterator it;
  size_t b_assoc;
  std::string item;

  while ((it = this->message_item()) != this->_messages.end() && !this->friends.empty())
    {
      std::istringstream message(&((*it)[(*it).find("trouver ") + 8]));
      std::getline(message, item, ' ');
      if (this->level[_level][item] != 0) {
          this->level[_level][item] -= 1;
	  b_assoc = (*it).find("moi:");
	  b_assoc = b_assoc + 4;
	  b_assoc = atoi(&(*it)[b_assoc]);
          this->_inventory[b_assoc][item] += 1;
      }
      if (this->_search == item && this->level[_level][item] <= 0)
	{
	  this->_to_go = -1;
	  this->_search = "";
	  this->_dir = "";
	}
      this->_messages.erase(it);
    }
}

void Trantorien::send_All_Inventory(Network *network)
{
    for(std::map<std::string, int>::iterator it = this->_inventory[this->_id].begin(); it != this->_inventory[this->_id].end(); it++)
    {
        for (int i = 0; i < it->second; i++)
        {
            if (it->first != "nourriture") {
                this->send_message("trouver " + it->first, network);
                this->level[_level][it->first] -= 1;
            }
        }
    }
}

int Trantorien::check_ok(Network *network)
{
  std::vector<std::string>::iterator it;
  size_t b_assoc;

  if (!this->temporary_friend.empty())
  {
    this->temporary_friend.clear();
  }
  it = this->_messages.begin();
  while (it != this->_messages.end())
    {
      b_assoc = (*it).find(std::to_string(_id));
      while (b_assoc != std::string::npos && (b_assoc == 0 || (*it)[b_assoc - 1] != ':' ||
					      !(*it)[b_assoc + std::to_string(_id).length()] || ((*it)[b_assoc + std::to_string(_id).length()] != ' ' && (*it)[b_assoc + std::to_string(_id).length()] != ':')))
	b_assoc = (*it).find(std::to_string(_id), b_assoc + 1);
      if (b_assoc != std::string::npos && (*it).find("message:ok ") != std::string::npos && this->check_can_add(*it))
	{
	  b_assoc = (*it).find("moi:");
	  b_assoc = b_assoc + 4;
	  b_assoc = atoi(&(*it)[b_assoc]);
    this->_group = 0;
	  if (std::find(friends.begin(), friends.end(), b_assoc) == this->friends.end())
    {
      this->_alive[b_assoc] = 0;
      this->add_friend(b_assoc, *it);
      this->temporary_friend.clear();
	    this->_messages.erase(it);
	    if (friends.size() + 1 == static_cast<unsigned int>(this->level[_level]["joueur"]))
            send_All_Inventory(network);
            return (1);
    }
	}
      ++it;
    }
  return (0);
}

int Trantorien::check_joan(Network *network)
{
  int i = 0;
  size_t b_assoc;

  if (!this->temporary_friend.empty())
  {
    this->temporary_friend.clear();
  }
  while (this->_messages.begin() + i != this->_messages.end())
    {
      b_assoc = this->_messages[i].find(std::to_string(_id));
      while (b_assoc != std::string::npos && (b_assoc == 0 || this->_messages[i][b_assoc - 1] != ':'
					      || !this->_messages[i][b_assoc + std::to_string(_id).length()] || (this->_messages[i][b_assoc + std::to_string(_id).length()] != ' ' && this->_messages[i][b_assoc + std::to_string(_id).length()] != ':')))
	b_assoc = this->_messages[i].find(std::to_string(_id), b_assoc + 1);
      if (b_assoc != std::string::npos && this->_messages[i].find("message:joan ") != std::string::npos && this->check_can_add(this->_messages[i]))
	{
	  b_assoc = this->_messages[i].find("moi:");
	  b_assoc = b_assoc + 4;
	  b_assoc = atoi(&this->_messages[i][b_assoc]);
	  if (std::find(friends.begin(), friends.end(), b_assoc) == this->friends.end())
    {
      this->_alive[b_assoc] = 0;
      this->_group = 0;
      this->add_friend(b_assoc, this->_messages[i]);
      this->temporary_friend.clear();
	    if (this->send_message("ok", network) == -1)
	      return (-1);
	    this->_messages.erase(this->_messages.begin() + i);
      if (this->friends.size() + 1 == static_cast<unsigned int>(this->level[_level]["joueur"]))
          send_All_Inventory(network);
	    return (1);
    }
	}
      ++i;
    }
  return (0);
}

int Trantorien::check_team(Network *network)
{
  size_t b_assoc;
  int i = 0;

  if (!this->temporary_friend.empty())
  {
    this->temporary_friend.clear();
    return (0);
  }
    while (this->_messages.begin() + i != this->_messages.end())
    {
        if ((*(this->_messages.begin() + i)).find("LVL:" + std::to_string(_level)) != std::string::npos && (*(this->_messages.begin() + i)).find("message:group") != std::string::npos && this->check_can_add(*(this->_messages.begin() + i)))
        {
          this->_group = 0;
            b_assoc = (*(this->_messages.begin() + i)).find("moi:");
            b_assoc = b_assoc + 4;
            b_assoc = atoi(&(*(this->_messages.begin() + i))[b_assoc]);
            if (std::find(friends.begin(), friends.end(), b_assoc) == this->friends.end())
            {
              this->add_friend(b_assoc, this->_messages[i]);
              if (this->send_message("joan", network) == -1)
                return (-1);
              this->unadd_friend();
              this->_messages.erase(this->_messages.begin() + i);
              return (1);
            }
          }
        ++i;
    }
  return (0);
}

bool Trantorien::check_can_add(std::string mess)
{
    size_t b_assoc;
    int nb_friend = 0;
    int to_save = 0;

    b_assoc = mess.find("assoc:");
    b_assoc = b_assoc + 6;
    if (mess[b_assoc] == ' ')
      return (true);
    to_save = atoi(&mess[b_assoc]);
    if (std::find(this->friends.begin(), this->friends.end(), to_save) == this->friends.end() && to_save != this->_id)
      ++nb_friend;
    while ((b_assoc = (mess.find(":", b_assoc) + 1)) != std::string::npos && b_assoc < mess.find("moi:"))
    {
      to_save = atoi(&mess[b_assoc]);
      if (std::find(this->friends.begin(), this->friends.end(), to_save) == this->friends.end() && to_save != this->_id)
        ++nb_friend;
    }
    if (this->friends.size() + 1 + nb_friend + this->temporary_friend.size() <= static_cast<unsigned int>(this->level[_level]["joueur"]))
      return (true);
    return (false);
}

void Trantorien::add_friend(size_t b_assoc, std::string mess)
{
    int to_save = 0;
    
    this->temporary_friend.push_back(b_assoc);
    this->friends.push_back(b_assoc);
    b_assoc = mess.find("assoc:");
    b_assoc = b_assoc + 6;
    if (mess[b_assoc] == ' ')
      return ;
    to_save = atoi(&mess[b_assoc]);
    if (std::find(this->friends.begin(), this->friends.end(), to_save) == this->friends.end() && to_save != this->_id) {
      this->temporary_friend.push_back(to_save);
      this->friends.push_back(to_save);
    }
    while ((b_assoc = (mess.find(":", b_assoc) + 1)) != std::string::npos && b_assoc < mess.find("moi:"))
    {
      to_save = atoi(&mess[b_assoc]);
      if (std::find(this->friends.begin(), this->friends.end(), to_save) == this->friends.end() && to_save != this->_id) {
        this->temporary_friend.push_back(to_save);
        this->friends.push_back(to_save);
      }
    }
}

void Trantorien::unadd_friend()
{
  std::vector<int>::iterator it;

  for (std::vector<int>::iterator it_temp = this->temporary_friend.begin(); it_temp != this->temporary_friend.end(); ++it_temp)
  {
    if ((it = std::find(this->friends.begin(), this->friends.end(), *it_temp)) != this->friends.end())
      this->friends.erase(it);
  }
}

void Trantorien::check_send_incantation()
{
  int j;
  size_t b_assoc;

  j = 0;
  while (this->friends.begin() + j != this->friends.end()) {
    int i = 0;
    bool exist = false;
    while (this->_messages.begin() + i != this->_messages.end()) {
      if ((*(this->_messages.begin() + i)).find("moi:" + std::to_string(this->friends[j])) != std::string::npos &&
      (*(this->_messages.begin() + i)).find("message:incantation") != std::string::npos) {
         b_assoc = (this->_messages[i]).find(std::to_string(_id));
     while (b_assoc != std::string::npos && (b_assoc == 0 || this->_messages[i][b_assoc - 1] != ':'
	 				      || !this->_messages[i][b_assoc + std::to_string(_id).length()] || (this->_messages[i][b_assoc + std::to_string(_id).length()] != ':' && this->_messages[i][b_assoc + std::to_string(_id).length()] != ' ')))
	 b_assoc = this->_messages[i].find(std::to_string(_id), b_assoc + 1);
       if (b_assoc == std::string::npos) {
         exist = false;
       _alive[this->friends[j]] = 10;
       }
       else
        exist = true;
      }
        i++;
    }
    if (exist == false) {
      _alive[this->friends[j]] += 1;
    }
    else {
      _alive[this->friends[j]] = 0;
    }
    if (_alive[this->friends[j]] > 10) {
      this->_to_feed = 10;
      this->friends.erase(this->friends.begin() + j);
    }
    else
      ++j;
  }
}

int Trantorien::move_foleft(Network *network)
{
  if (this->move_forward(network) == -1)
    return (-1);
  this->_dir = "gauche";
  if (this->Turn(network) == -1)
    return (-1);
  if (this->move_forward(network) == -1)
    return (-1);
  return (0);
}

int Trantorien::move_left(Network *network)
{
  this->_dir = "gauche";
  if (this->Turn(network) == -1)
    return (-1);
  if (this->move_forward(network) == -1)
    return (-1);
  return (0);
}

int Trantorien::move_baleft(Network *network)
{
  this->_dir = "gauche";
  if (this->Turn(network) == -1)
    return (-1);
  if (this->move_forward(network) == -1)
    return (-1);
  this->_dir = "gauche";
  if (this->Turn(network) == -1)
    return (-1);
  if (this->move_forward(network) == -1)
    return (-1);
  return (0);
}

int Trantorien::move_back(Network *network)
{
  this->_dir = "gauche";
  if (this->Turn(network) == -1)
    return (-1);
    this->_dir = "gauche";
  if (this->Turn(network) == -1)
    return (-1);
  if (this->move_forward(network) == -1)
    return (-1);
  return (0);
}

int Trantorien::move_baright(Network *network)
{
  this->_dir = "droite";
  if (this->Turn(network) == -1)
    return (-1);
  if (this->move_forward(network) == -1)
    return (-1);
  this->_dir = "droite";
  if (this->Turn(network) == -1)
    return (-1);
  if (this->move_forward(network) == -1)
    return (-1);
  return (0);
}

int Trantorien::move_right(Network *network)
{
  this->_dir = "droite";
  if (this->Turn(network) == -1)
    return (-1);
  if (this->move_forward(network) == -1)
    return (-1);
  return (0);
}

int Trantorien::move_foright(Network *network)
{
  if (this->move_forward(network) == -1)
    return (-1);
  this->_dir = "droite";
  if (this->Turn(network) == -1)
    return (-1);
  if (this->move_forward(network) == -1)
    return (-1);
  return (0);
}

int Trantorien::check_msg_poser(int older, Network *network)
{
    int i = 0;
    int older_i = -1;

    while (this->_messages.begin() + i != this->_messages.end()) {
        if ((*(this->_messages.begin() + i)).find("moi:" + std::to_string(older)) != std::string::npos &&
            (*(this->_messages.begin() + i)).find("message:poser") != std::string::npos)
            older_i = i;
        i++;
    }
    if (older_i == -1)
        return (0);
    this->send_see(network);
    if (static_cast<unsigned int>(peopleOnCase()) == (this->friends.size() + 1) && atoi(this->_messages[older_i].c_str()) == 0 && (*(this->_messages.begin() + older_i)).find("moi:" + std::to_string(older)) != std::string::npos &&
        (*(this->_messages.begin() + older_i)).find("message:poser") != std::string::npos) {
        this->putObjectCase(network);
        this->send_message("toutposer", network);
        this->_pose = true;
        this->_messages.clear();
        return (1);
    }
    else if (atoi(this->_messages[older_i].c_str()) != 0 && (*(this->_messages.begin() + older_i)).find("moi:" + std::to_string(older)) != std::string::npos &&
             (*(this->_messages.begin() + older_i)).find("message:poser") != std::string::npos)
    {
        if ((this->*to_move[atoi((this->_messages[older_i]).c_str())])(network) == -1)
            return (-1);
    }
    return (0);
}

int Trantorien::check_msg_spartiate(int older)
{
    int i = 0;
    while (this->_messages.begin() + i != this->_messages.end()) {
        if ((*(this->_messages.begin() + i)).find("moi:" + std::to_string(older)) != std::string::npos &&
            (*(this->_messages.begin() + i)).find("message:spartiate") != std::string::npos)
            {
              this->_pose = false;
              this->_to_feed = 10;
              this->_to_go = -1;
              this->_search = "";
              this->initialise_level();
              this->_messages.clear();
              return (1);
          }
        i++;
    }
    return (0);
}

bool Trantorien::check_msg_toutposer()
{
    int i;
    int older_mess;

    for(unsigned int j = 0; j < this->friends.size(); j++)
    {
        i = 0;
        older_mess = -1;
        while (this->_messages.begin() + i != this->_messages.end()) {
            if ((*(this->_messages.begin() + i)).find("moi:" + std::to_string(this->friends[j])) != std::string::npos &&
                (*(this->_messages.begin() + i)).find("message:toutposer") != std::string::npos) {
                older_mess = i;
            }
            i++;
        }
        if (older_mess == -1) {
            return false;
        }
    }
    return true;
}

int Trantorien::check_msg_incantation(int older, Network *network)
{
    int i = 0;
    int older_mess = -1;

    while (this->_messages.begin() + i != this->_messages.end()) {
        if ((*(this->_messages.begin() + i)).find("moi:" + std::to_string(older)) != std::string::npos &&
            (*(this->_messages.begin() + i)).find("message:incantation") != std::string::npos) {
              older_mess = i;
        }
        i++;
    }
    if (older_mess != -1) {
      if (atoi((*(this->_messages.begin() + older_mess)).c_str()))
        if ((this->*to_move[atoi((*(this->_messages.begin() + older_mess)).c_str())])(network) == -1)
            return (-1);
    }
    this->erase_incant();
    return (0);
}

bool Trantorien::check_incantation()
{
for (std::vector<int>::const_iterator it = this->friends.begin(); it != this->friends.end(); ++it) {
    int i = 0;
    int older_mess = -1;
    while (this->_messages.begin() + i != this->_messages.end()) {
        if ((*(this->_messages.begin() + i)).find("moi:" + std::to_string(*it)) != std::string::npos &&
            (*(this->_messages.begin() + i)).find("message:incantation") != std::string::npos) {
              older_mess = i;
        }
        i++;
    }
    if (older_mess != -1) {
        return (true);
    }
  }
    return (false);
}

void Trantorien::erase_incant()
{
  int i;

  i = 0;
  while (this->_messages.begin() + i != this->_messages.end()) {
      if ((*(this->_messages.begin() + i)).find("message:incantation") != std::string::npos) {
        this->_messages.erase(this->_messages.begin() + i);
      }
      else
        i++;
  }
}

int Trantorien::getObject(int forward, std::string object, Network *network)
{
  int save;
  int cas;

  save = forward;
  cas = 0;
    if (forward < 0)
        return 0;
    while (forward > 0)
    {
      if (forward % 3 == 0 && this->incantationPossible() && object == "nourriture" && this->friends.size() > 0 && !this->_pose)
        this->send_message("incantation", network);
      if (std::find(this->_see[cas].begin(), this->_see[cas].end(), "nourriture") != this->_see[cas].end() && this->_inventory[this->_id]["nourriture"] <= 20) {
        this->_search = object;
        this->send_takeObject("nourriture", network);
      }
      this->move_forward(network);
        cas = cas + 2 * (save - forward);
        forward--;
    }
    if (object == "nourriture" && this->incantationPossible() && this->friends.size() > 0 && !this->_pose)
    this->send_message("incantation", network);
    if (!this->_dir.empty())
    {
        this->Turn(network);
        this->move_forward(network);
        if (this->send_see(network) == -1)
            return -1;
        this->_to_go = this->ElementCases(this->_search);
        if (this->_to_go != 0)
            getObject(this->_to_go, object, network);
    }
    if (object == "nourriture" || this->level[this->_level][object] > 0) {
        this->send_takeObject(object, network);
    }
    this->_dir = "";
    return 1;
}

std::string Trantorien::nearestObject()
{
    std::list<std::string> objects_case;
    int pos = 0;
    int compt = 0;
    int nb_player;
    std::string wanted;

    for(int i = -1; i < this->_level; i++)
    {
        pos = pos + compt;
        objects_case = this->_see[pos];
        wanted = "";
        nb_player = 0;
        for (std::list<std::string>::const_iterator it = objects_case.begin(); it != objects_case.end(); ++it)
        {
            if (wanted == "" && *it != "joueur" && this->_inventory[this->_id][*it] < this->level[this->_level][*it])
                wanted = *it;
            if (*it == "joueur")
            ++nb_player;
        }
        if ((nb_player == 0 && wanted != "") || pos == 0)
          return (wanted);
        compt += 2;
    }
    for(size_t i = 0; i < this->_see.size(); i++)
    {
        objects_case = this->_see[i];
        wanted = "";
        nb_player = 0;
        for (std::list<std::string>::const_iterator it = objects_case.begin(); it != objects_case.end(); ++it)
        {
            if (wanted == "" && *it != "joueur" && this->_inventory[this->_id][*it] < this->level[this->_level][*it])
                wanted = *it;
            if (*it == "joueur")
            ++nb_player;
        }
        if (nb_player == 0 && wanted != "")
          return (wanted);
    }
    return "";
}

std::string Trantorien::objectNeed()
{
    for(std::map<std::string, int>::iterator it = this->level[this->_level].begin(); it != this->level[this->_level].end(); it++)
    {
        if (it->first != "joueur" && it->second > 0)
            return it->first;
    }
    return "";
}

void Trantorien::getObjectCase(Network *network)
{
    std::list <std::string> objects_case;

    this->send_see(network);
    objects_case = this->_see[0];
    for (std::list<std::string>::const_iterator it = objects_case.begin(); it != objects_case.end(); ++it)
    {
        if (*it != "joueur")
            this->send_takeObject(*it, network);
    }
}

void Trantorien::putObjectCase(Network *network)
{
    this->initialise_level();

    for(std::map<std::string, int>::iterator it = this->_inventory[this->_id].begin(); it != this->_inventory[this->_id].end(); it++)
    {
        for (int i = 0; i < it->second; i++)
        {
            if (this->level[this->_level][it->first] > 0)
            {
                this->send_putObject(it->first, network);
            }
        }
    }
}

bool Trantorien::incantationPossible()
{
    if (this->friends.size() + 1 == static_cast<unsigned int>(this->level[_level]["joueur"]) &&
        this->level[this->_level]["linemate"] <= 0 &&
        this->level[this->_level]["deraumere"] <= 0 &&
        this->level[this->_level]["sibur"] <= 0 &&
        this->level[this->_level]["mendiane"] <= 0 &&
        this->level[this->_level]["phiras"] <= 0 &&
        this->level[this->_level]["thystame"] <= 0)
        return true;
    return false;
}

int Trantorien::peopleOnCase()
{
    int count = 0;
    std::list <std::string> objects_case;

    objects_case = this->_see[0];
    for (std::list<std::string>::const_iterator it = objects_case.begin(); it != objects_case.end(); ++it)
    {
        if (*it == "joueur")
            count++;
    }  
    return (count);
}

int Trantorien::olderTrantorien()
{
    int older = this->_id;

    for(unsigned int i = 0; i < this->friends.size(); i++)
    {
        if (this->friends[i] > older)
            older = this->friends[i];
    }
    return older;
}

bool Trantorien::goodObjectOnCase(void)
{
    std::map<std::string, int> nb_object;
    std::list <std::string> objects_case;

    objects_case = this->_see[0];
    nb_object["linemate"] = 0;
    nb_object["deraumere"] = 0;
    nb_object["sibur"] = 0;
    nb_object["mendiane"] = 0;
    nb_object["phiras"] = 0;
    nb_object["thystame"] = 0;

    for (std::list<std::string>::const_iterator it = objects_case.begin(); it != objects_case.end(); ++it)
    {
        if (*it != "joueur" && *it != "nourriture")
            nb_object[*it] += 1;
    }

    if (nb_object["linemate"] == this->cpy_level[this->_level]["linemate"] &&
        nb_object["deraumere"] == this->cpy_level[this->_level]["deraumere"] &&
        nb_object["sibur"] == this->cpy_level[this->_level]["sibur"] &&
        nb_object["mendiane"] == this->cpy_level[this->_level]["mendiane"] &&
        nb_object["phiras"] == this->cpy_level[this->_level]["phiras"] &&
        nb_object["thystame"] == this->cpy_level[this->_level]["thystame"])
        return (true);
    return (false);
}

bool Trantorien::goodFriends()
{
    int i;
    int older_mess;

    for(unsigned int j = 0; j < this->friends.size(); j++)
    {
        i = 0;
        older_mess = -1;
        while (this->_messages.begin() + i != this->_messages.end()) {
            if ((*(this->_messages.begin() + i)).find("moi:" + std::to_string(this->friends[j])) != std::string::npos &&
                (*(this->_messages.begin() + i)).find("message:incantation") != std::string::npos) {
                older_mess = i;
            }
            i++;
        }
        if (older_mess != -1) {
            if (atoi((*(this->_messages.begin() + older_mess)).c_str()))
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    return true;
}

void Trantorien::checkObjectCase(Network *network)
{
    this->send_see(network);
    this->initialise_level();
    std::list<std::string> objects_case;

    objects_case = this->_see[0];
    for(std::list<std::string>::const_iterator it = objects_case.begin(); it != objects_case.end(); ++it)
    {
        if (*it != "joueur" && *it != "nourriture")
            this->level[this->_level][*it] -= 1;
    }
    for(std::map<std::string, int>::iterator it = this->level[this->_level].begin(); it != this->level[this->_level].end(); it++)
    {
        while (this->level[this->_level][it->first] > 0 && it->first != "joueur" && it->first != "nourriture")
        {
            this->send_putObject(it->first, network);
            this->level[this->_level][it->first] -= 1;
        }
        while (this->level[this->_level][it->first] < 0 && it->first != "joueur" && it->first != "nourriture")
        {
            this->send_takeObject(it->first, network);
            this->level[this->_level][it->first] += 2;
        }
    }
}

int Trantorien::launchAI(Network *network)
{
  int	to_ret;
  std::string object_to_find;

  if (this->_id == -1)
    return (this->send_name_to_server(network));
  if (this->connected == false || this->_id == -1)
    return (0);
  this->check_co();
  if (this->_level > 1 && this->_group > 40)
  {
    this->connect_nbr(network);
    if (this->_can_be_co == 0)
    {
      this->fork(network);
      this->_group = 0;
    }
  }
  this->checkItem();
  if (this->_see.empty()) {
    return (this->send_see(network));
  }
  if (this->_search == "nourriture" && this->_inventory[_id]["nourriture"] > 20)
    this->_search = "";
  if (this->_i_turn == 4)
    {
      if (this->_search == "nourriture" && this->incantationPossible() && this->friends.size() > 0 && !this->_pose)
      this->send_message("incantation", network);
      if (this->move_forward(network) == -1)
	      return (-1);
      if (this->move_forward(network) == -1)
	      return (-1);
      return (this->move_forward(network));
    }
  if (this->_inventory[_id]["nourriture"] <= this->_to_feed && !this->_pose)
    {
        if (this->send_see(network) == -1)
          return (-1);
          if (this->_to_feed < 5)
            this->_to_feed = 10;
      this->_search = "nourriture";
      _to_go = this->ElementCases("nourriture");
    }
    if (this->check_incantation() && this->_search != ""  && this->_search != "nourriture" && this->friends.size() > 0)
      this->_search = "";
  if (_to_go == -1 && (this->_inventory[_id]["nourriture"] <= this->_to_feed || this->_search != ""))
    {
      this->_dir = "gauche";
      if (this->Turn(network) == -1)
        return (-1);
      if (this->send_see(network) == -1)
        return (-1);
      _to_go = this->ElementCases(this->_search);
      return (0);
    }
  if (friends.size() + 1 != static_cast<unsigned int>(this->level[_level]["joueur"]) && this->_search != "nourriture")
    {
      to_ret = 0;
      if (this->check_ok(network) == 0 && friends.size() + 1 != static_cast<unsigned int>(this->level[_level]["joueur"]))
	    {
	      if ((to_ret = this->check_joan(network)) == 0)
	        {
	          if ((to_ret = this->check_team(network)) == 0)
	          {
		          if (send_message("group", network) == -1)
		            return (-1);
              ++_group;
              this->send_Inventory(network);
		          if (to_ret == -1)
		            return (-1);
		          return (this->send_Inventory(network));
	          }
	        }
	    }
      if (to_ret == -1)
	      return (-1);
    }
    if (this->_search != "" && !this->_pose)
    {
        this->getObject(this->ElementCases(this->_search), this->_search, network);
    }
    else if (this->incantationPossible() || (this->friends.size() > 0 && this->check_incantation()) || this->_pose) {
        if (this->_level == 1)
        {
            if (peopleOnCase() > 1)
                this->send_eject(network);
            this->checkObjectCase(network);
            this->incantation(network);
            this->_pose = false;
        }
        else
        {
            this->_to_feed = 5;
            int older = olderTrantorien();
            if (older == this->_id)
            {
                this->send_message("incantation", network);
                this->send_see(network);
                this->check_send_incantation();
                if (peopleOnCase() == this->level[_level]["joueur"] && this->goodFriends())
                {
                    if (!goodObjectOnCase())
                    {
                      this->_pose = true;
                        this->send_message("poser", network);
                    }
                    if (this->check_msg_toutposer())
                    {
                        this->checkObjectCase(network);
                        this->incantation(network);
                        this->_pose = false;
                    }
                }
                else if (!_pose && static_cast<unsigned int>(peopleOnCase()) != (this->friends.size() + 1) && this->goodFriends() && peopleOnCase() > 1)
                    this->send_eject(network);
                else if (!_pose)
                    this->getObjectCase(network);
                else
                  {
                    this->_pose = false;
                  }
            }
            else
            {
              if (!this->_pose)
                this->send_message("incantation", network);
                if ((to_ret = this->check_msg_spartiate(older)) == -1)
                    return (-1);
                else if (!this->_pose && to_ret == 0 && (to_ret = this->check_msg_poser(older, network)) == -1) {
                    return (-1);
                }
                else if (to_ret == 0 && !this->_pose)
                {
                    this->check_send_incantation();
                  if (this->check_msg_incantation(older, network) == -1)
                     return (-1);
                }
            }
            if (!this->_pose && this->send_Inventory(network) == -1)
            return (-1);
        }
    }
    else {
        object_to_find = this->nearestObject();
        if (!object_to_find.empty()) {
            this->_search = object_to_find;
            this->getObject(this->ElementCases(object_to_find), object_to_find, network);
        }
        else
	  this->_search = objectNeed();
    }
    return (0);
}

//FONCTION RETOUR COMMANDE
void Trantorien::upLevel(std::string arg, Network *network)
{
    if (arg != "ko")
    {
        this->_level += 1;
        this->_pose = false;
    }
    else
        this->_incantation = false;
        this->_to_go = -1;
        this->_search = "";
    this->_to_feed = 10;
    if (olderTrantorien() == _id && this->friends.size() > 0)
     this->send_message("spartiate", network);
    this->send_Inventory(network);
    this->send_see(network);
    this->initialise_level();
    if (arg != "ko" && this->_level != 6 && this->friends.size() != 0){
      this->send_All_Inventory(network);
    }
    else if (arg != "ko" && this->_level == 6)
    this->friends.clear();
      this->check_co();
      this->checkItem();
      this->_messages.clear();
}

void Trantorien::putInventory(std::string arg, Network *network)
{
    if (this->level[this->_level][arg] > 0)
    {
        if (arg != "nourriture" && this->friends.size() > 0)
            this->send_message("trouver " + arg, network);
    }
    this->_search = "";
    this->_to_go = -1;
    this->_inventory[this->_id][arg] += 1;
    this->level[this->_level][arg] -= 1;
}

void Trantorien::takeInventory(std::string arg, __attribute__((unused))Network *network)
{
    this->_inventory[this->_id][arg] -= 1;
}

void Trantorien::see(std::string _line_, __attribute__((unused))Network *network)
{
    _line_ = _line_.erase(0, 1);
    _line_ = _line_.substr(0, _line_.size() - 1);
    std::istringstream list_object(_line_);
    std::string tmp;
    std::string object;

    for(int i = 0; std::getline(list_object, tmp, ','); i++) {
        this->_see[i].clear();
        std::istringstream objects_case(tmp.erase(0, 1));
        while (std::getline(objects_case, object, ' ')) {
            this->_see[i].push_back(object);
        }
    }
}

void Trantorien::Inventory(std::string _line_, __attribute__((unused))Network *network)
{
    _line_.erase(0, 1);
    std::istringstream list_object(_line_);
    std::string nb_object;
    std::string object;
    int number;
    std::size_t pos;

    for(int i = 0; std::getline(list_object, nb_object, ','); i++) {
        pos = nb_object.find(" ");
        object = nb_object.substr(0, pos);
        number = atoi((nb_object.substr(pos + 1, nb_object.length())).c_str());
        this->_inventory[this->_id][object] = number;
    }
}

//FONCTION SET ET GET
std::string Trantorien::getTeam(void) const
{
    return this->_team;
}

int Trantorien::getLevel(void) const
{
    return this->_level;
}

void Trantorien::setId(int id)
{
    this->_id = id;
    this->_inventory[id]["linemate"] = 0;
    this->_inventory[id]["deraumere"] = 0;
    this->_inventory[id]["sibur"] = 0;
    this->_inventory[id]["mendiane"] = 0;
    this->_inventory[id]["phiras"] = 0;
    this->_inventory[id]["thystame"] = 0;
    this->_inventory[id]["nourriture"] = 10;
}

int Trantorien::getId(void) const
{
    return this->_id;
}


//FONCTION CHECK MESSAGE
int Trantorien::check_message(void)
{
    std::string mot;
    std::istringstream iss(this->reponse);
    std::getline(iss, mot, ' ');
    if (mot == "message")
        return (0);
    return (1);
}

void Trantorien::add_message_to_list()
{
  size_t begin;
  std::string direct;

  Conversion convert(this->_team);
  begin = this->reponse.find(",");
  direct = std::to_string(atoi(&(this->reponse[8])));
  if (begin == std::string::npos)
    return ;
  this->reponse = &this->reponse[begin + 1];
  if (convert.CanDecrypt(this->reponse) == false)
    return ;
  this->_messages.push_back(direct + " " + convert.Decrypt(this->reponse));
}

//LIAISON AVEC LE SERVEUR
int Trantorien::check_retour_server(void)
{
    std::string mot;
    std::istringstream iss(this->reponse);
    std::getline(iss, mot, ' ');
    if (mot == "ok" || mot == "ko" || mot == "linemate" || mot == "deraumere" ||
        mot == "sibur" || mot == "mendiane" || mot == "phiras" || mot == "thystame" ||
        mot == "joueur" || mot == "elevation" || mot == "niveau" || mot == "{" || mot == "{nourriture" || mot == "{linemate" ||
        mot == "{deraumere" || mot == "{sibur" || mot == "{mendiane" || mot == "{phiras" || mot == "{thystame" || (mot[0] >= '0' && mot[0] <= '9'))
        return (0);
    return (1);
}

int Trantorien::send_name_to_server(Network *network)
{
    std::queue<std::string> to_send;


    this->command = this->_team;
    to_send.push(this->_team);
    network->write_to_server(to_send);
    if (this->connected == false)
        if (network->check_return(this) == -1)
            return (-1);
    if (this->getId() == -1)
        if (network->check_return(this) == -1)
            return (-1);
    if (this->dim_map == false)
        if (network->check_return(this) == -1)
            return (-1);
    this->send_message("connected", network);
    return (0);
}

int Trantorien::analyse(Network *network)
{
  int retour;
  std::string mot;
  std::string arg;

  std::istringstream iss(this->command);
  std::istringstream iss_rep(this->reponse);

  if ((retour = this->check_retour_server()) == 1)
    {
	    if (!this->check_message())
        this->add_message_to_list();
      return (1);
    }
  std::getline(iss_rep, arg, ' ');
  if (this->_pose && arg == "niveau" && olderTrantorien() != this->_id && this->friends.size() > 0)
  {
    (this->*actions["incantation"])(this->reponse, network);
    return (0);
  }
  std::getline(iss, mot, ' ');
  if (mot == "connect_nbr")
  {
    this->_can_be_co = atoi(this->reponse.c_str());
    return (0);
  }
  if (mot == "prend" || mot == "pose")
    {
      std::getline(iss, arg, ' ');
      if (this->reponse != "ko") {
          (this->*actions[mot])(arg, network);
      }
      else if (this->reponse == "ko" && mot == "prend") {
        if (this->send_see(network) == -1)
          return (-1);
          _to_go = this->ElementCases(arg);
      }
    }
    if (this->command == "voir" || this->command == "inventaire" || (this->command == "incantation" && this->reponse != "elevation en cours"))
    {
        (this->*actions[mot])(this->reponse, network);
    }
  this->command = "";
  this->reponse = "";
  return (0);
}
