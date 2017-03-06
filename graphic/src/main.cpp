/*
** main.cpp for main in /home/wawrzy-j/Documents/Projets/PSU/PSU_2015_zappy/graphic/src
**
** Made by wawrzy-j
** Login   <wawrzy-j@wawrzy-j>
**
** Started on  Mon Jun 13 13:48:27 2016 wawrzy-j
** Last update Mon Jun 13 18:07:58 2016 wawrzy-j
*/

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include "Trantor.hpp"
#include "Error.hpp"

int checkArgs(char **av)
{
   for (int i = 0; av[2][i]; i++) {
       if (av[2][i] < '0' || av[2][i] > '9')
           return (1);
    }
    return (0);
}

int main(int ac, char **av)
{
  int ret;

  if (ac != 3 || checkArgs(av) == 1)
  {
    std::cerr << "Usage : " << av[0] << " IP PORT" << std::endl;
    return (1);
  }

  Trantor *trantor = new Trantor(std::string(av[1]), atoi(av[2]));
    
  ret = trantor->core();
  
  delete trantor;


  return (ret);
}
