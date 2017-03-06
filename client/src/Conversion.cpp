//
// Conversion.cpp for zappy in /home/olivie_e/PSU_2015_zappy/client/src
// 
// Made by ekaterina olivier
// Login   <olivie_e@epitech.net>
// 
// Started on  Fri Jun 17 13:43:40 2016 ekaterina olivier
// Last update Tue Jun 21 14:43:52 2016 ekaterina olivier
//

#include <iostream>
#include "Conversion.hpp"

Conversion::Conversion(std::string team)
{
  this->_team = team;
}

Conversion::~Conversion() {

}

int Conversion::Char_to_string(char c)
{
  if (c >= 'a' && c <= 'z')
    return (c - 'a');
  if (c >= 'A' && c <= 'Z')
    return (c - 'A');
  if (c >= '0' && c <= '9')
    return (c - '0');
  return (-1);
}

std::string Conversion::Crypt(std::string to_crypt)
{
  int	i = -1;
  int	j = 0;
  int	crypt = 0;

  while (to_crypt[++i])
    {
      if (!_team[j])
	j = 0;
      if (((to_crypt[i] >= 'a' && to_crypt[i] <= 'z') || (to_crypt[i] >= 'A' && to_crypt[i] <= 'Z') || (to_crypt[i] >= '0' && to_crypt[i] <= '9')) &&
	  ((_team[j] >= 'a' && _team[j] <= 'z') || (_team[j] >= 'A' && _team[j] <= 'Z') || (_team[j] >= '0' && _team[j] <= '9')))
	{
	  crypt = this->Char_to_string(_team[j]);
	  while (crypt)
	    {
	      to_crypt[i] += 1;
	      if (to_crypt[i] == 'z' + 1)
		to_crypt[i] = 'a';
	      if (to_crypt[i] == 'Z' + 1)
		to_crypt[i] = 'A';
	      if (to_crypt[i] == '9' + 1)
		to_crypt[i] = '0';
	      --crypt;
	    }
	}
      ++j;
    }
  return (to_crypt);
}

bool Conversion::CanDecrypt(__attribute__((unused)) std::string to_decrypt)
{
  std::string check;
  check = this->Decrypt(to_decrypt);
  if (check.find("team:" + _team) == std::string::npos || check.find("LVL:") == std::string::npos ||
    check.find("moi:") == std::string::npos || check.find("assoc:") == std::string::npos) {
    	return (false);
  }
  return (true);
}

std::string Conversion::Decrypt(std::string to_decrypt)
{
   int	i = -1;
   int	j = 0;
   int	decrypt = 0;

  while (to_decrypt[++i])
    {
      if (!_team[j])
	j = 0;
      if (((to_decrypt[i] >= 'a' && to_decrypt[i] <= 'z') || (to_decrypt[i] >= 'A' && to_decrypt[i] <= 'Z') || (to_decrypt[i] >= '0' && to_decrypt[i] <= '9')) &&
	  ((_team[j] >= 'a' && _team[j] <= 'z') || (_team[j] >= 'A' && _team[j] <= 'Z') || (_team[j] >= '0' && _team[j] <= '9')))
	{
	  decrypt = this->Char_to_string(_team[j]);
	  while (decrypt)
	    {
	      to_decrypt[i] -= 1;
	      if (to_decrypt[i] == 'a' - 1)
		to_decrypt[i] = 'z';
	      if (to_decrypt[i] == 'A' - 1)
		to_decrypt[i] = 'Z';
	      if (to_decrypt[i] == '0' - 1)
		to_decrypt[i] = '9';
	      --decrypt;
	    }
	}
      ++j;
    }
  return (to_decrypt);
}
