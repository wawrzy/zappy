//
// Conversion.hpp for zappy in /home/olivie_e/PSU_2015_zappy/client/includes
// 
// Made by ekaterina olivier
// Login   <olivie_e@epitech.net>
// 
// Started on  Fri Jun 17 13:33:20 2016 ekaterina olivier
// Last update Fri Jun 17 16:24:07 2016 ekaterina olivier
//

#ifndef CONVERSION_HPP
#define CONVERSION_HPP

#include <string>
#include <map>

class Conversion
{
  std::string _team;

  int Char_to_string(char c);
public:
  Conversion(std::string team);
  ~Conversion();

  std::string Crypt(std::string to_crypt);

  bool CanDecrypt(std::string to_crypt);
  std::string Decrypt(std::string to_decrypt);
};

#endif //CONVERSION_HPP
