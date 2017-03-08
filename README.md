# zappy

## Project

Zappy is a virtual game that we have to do in second year of Epitech.
This is a small strategic game where your player, controlled by an AI needs to feed himself and gather ressources to "elevate".

[zappy subject](docs/zappy-en.pdf)

| Client (AI)   | Server        | Graphic   |
|:-------------:|:-------------:|:---------:|
| C++           | C             | C++ / SFML|

## Build
```Shell
# On ubuntu / mint / debian
sudo ./script/install_glew_ubuntu.sh

# On other os : install glew1.1 and g++-4.9

make && make zappy_graphic
```


## Run zappy
```Shell

./script/test.sh
# or
./zappy_server
 -p port
 -x width of the world
 -y height of the world
 -n name_of_team_1 name_of_team_2 ...
 -c number of clients allowed at the game beginning
 -t time delay for executing actions (frequence).

./zappy_ai
 -n team_name 
 -p port 
 [-h hostname]
# (./zappy_ai * number_player_in_team)

./zappy_graphic 
 ip
 port


```
