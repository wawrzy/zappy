
//
// Trantorien.hpp for zappy in /home/olivie_e/PSU_2015_zappy/client/includes
// 
// Made by joan saum
// Login   <saum_j@epitech.net>
// 
// Started on  Tue Jun 14 11:03:05 2016 joan saum
// Last update Mon Jun 20 17:26:54 2016 ekaterina olivier
//

#ifndef TRANTORIEN_HPP
#define TRANTORIEN_HPP

#include <map>
#include <vector>
#include <list>
#include "Network.hpp"

class Trantorien
{

public:

  typedef void (Trantorien::*FuncType)(std::string object, Network *network);
  typedef int (Trantorien::*FuncMove)(Network *network);

public:
    Trantorien(std::string team);
    ~Trantorien();

public:
    int move_forward(Network *network);
    int Turn(Network *network);
    int send_takeObject(std::string _object_, Network *network);
    int send_putObject(std::string _object_, Network *network);
    int fork(Network *network);
    int connect_nbr(Network *network);
    int send_see(Network *network);
    int send_eject(Network *network);
    int incantation(Network *network);
    int send_Inventory(Network *network);
    int send_message(std::string _message_, Network *network);

    int launchAI(Network *network);
    void setId(int id);
    int getId(void) const;
    std::string getTeam(void) const;
    int getLevel(void) const;
    int analyse(Network *network);

private:
    void initialise_level();
	void initialise_cpylevel();

    void putInventory(std::string arg, Network *network);
    void takeInventory(std::string arg, Network *network);
    void Inventory(std::string _line_, Network *network);
    void see(std::string _line_, Network *network);
    void upLevel(std::string arg, Network *network);
    int getObject(int forward, std::string object, Network *network);
    std::string nearestObject();
    int olderTrantorien();

    void send_All_Inventory(Network *network);
    std::string objectNeed();

    void getObjectCase(Network *network);
    void putObjectCase(Network *network);
    int peopleOnCase();
	void checkObjectCase(Network *network);

    bool incantationPossible();
	bool goodObjectOnCase(void);
	bool goodFriends();

    void add_message_to_list();
    int check_message(void);

    int check_retour_server(void);
    int send_name_to_server(Network *network);

    int ElementCases(std::string element);
    int ElementHere(int cases, std::string element);

    void check_co();
    std::vector<std::string>::iterator message_item();
    void checkItem();

    int check_ok(Network *network);
    int check_joan(Network *network);
    int check_team(Network *network);
    bool check_can_add(std::string mess);
    void add_friend(size_t b_assoc, std::string mess);
    void unadd_friend();

	int check_msg_incantation(int older, Network *network);
	int check_msg_poser(int older, Network *network);
	void check_send_incantation();
	int check_msg_spartiate(int older);
	bool check_msg_toutposer();
    bool check_incantation();
    void erase_incant();


public:
    std::string reponse;
    bool connected;
    bool dim_map;
	std::string _team;

private:
    std::map<std::string, FuncType> actions;
    std::string command;
    std::vector<std::string> _messages;
    int _cmd;

    std::vector<int> friends;
    std::vector<int> temporary_friend;
    int _group;
	std::map<int, int> _alive;
    std::map<int, std::map<std::string, int> > level;
	std::map<int, std::map<std::string, int> > cpy_level;
    std::map<int, std::map<std::string, int> > _inventory;
    bool _incantation;
	bool _pose;

    std::map<int, FuncMove> to_move;
	int move_foleft(Network *network);
	int move_left(Network *network);
	int move_baleft(Network *network);
	int move_back(Network *network);
	int move_baright(Network *network);
	int move_right(Network *network);
	int move_foright(Network *network);

    std::map<int, std::list<std::string> > _see;
    std::string _dir;
    int _to_go;
    std::string _search;
    int _i_turn;

    int _level;
    int _id;
    int _can_be_co;
    int _to_feed;
};

#endif //TRANTORIEN_HPP
