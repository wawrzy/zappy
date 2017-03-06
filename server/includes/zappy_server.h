/*
** zappy_server.h for zappy_server in /home/braun_s/rendu/Projects/PSU/PSU_2015_zappy/server
**
** Made by Sascha Braun
** Login   <braun_s@epitech.net>
**
** Started on  Sat Jun 25 14:27:45 2016 Sascha Braun
** Last update Sun Jun 26 14:52:14 2016 tanguy acker
*/

#ifndef ZAPPY_SERVER_H_
# define ZAPPY_SERVER_H_

# define MAX_BUF_SIZE	(1000000)
# define MAX_MSG_SIZE	(512)
# define MAX_REQUESTS	(10)

# define TIME_NSEC	(1000000000)
# define TIME_USEC	(1000000)

# define ECLOSION_TIME	(300)
# define FOOD_TIME	(126)
# define RESSOURCE_NUM	(7)
# define ELEVATIONS_NUM	(7)
# define DIRECTION_NUM	(4)
# define CMDS_CLI_NUM	(12)
# define CMDS_GRA_NUM	(26)
# define ELEVATIONS_NUM	(7)

# define ABS(nb)	((nb < 0) ? (-nb) : (nb))
# define USIGNED(nb)	((nb < 0) ? 0 : nb)

# define FOOD_RATIO	(55)
# define LINE_RATIO	(14)
# define DERA_RATIO	(8)
# define SIBU_RATIO	(10)
# define MEND_RATIO	(5)
# define PHIR_RATIO	(6)
# define THYS_RATIO	(2)

# define SPAWN_TICKS	(128)
# define MIN_RESSOURCES	(100)
# define RESS_PER_FIELD	(2)
# define MAX_PER_FIELD	(9)

# include <sys/socket.h>
# include <time.h>

enum RESSOURCE
  {
    FOOD = 0,
    LINEMATE = 1,
    DERAUMERE = 2,
    SIBUR = 3,
    MENDIANE = 4,
    PHIRAS = 5,
    THYSTAME = 6,
    UNKNOWN = 7
  };

enum DIRECTION
  {
    NORTH,
    OST,
    SOUTH,
    WEST
  };

enum MODE
  {
    NONE,
    CLIENT,
    GRAPHIC
  };

struct s_client;
struct s_player;
struct s_server;

typedef struct		s_vector2d
{
  int			x;
  int			y;
}			t_vector2d;

typedef struct		s_inventory
{
  int			ressources[RESSOURCE_NUM];
}			t_inventory;

typedef struct		s_elevation
{
  int			level;
  int			player_num;
  t_inventory		costs;
}			t_elevation;

typedef struct		s_players
{
  struct s_players	*next;
  struct s_player	*player;
}			t_players;

typedef struct		s_case
{
  t_players		*players;
  t_inventory		objects;
  int			need_update;
}			t_case;

typedef struct		s_world
{
  int			width;
  int			height;
  t_case		*cases;
}			t_world;

typedef struct		s_team
{
  struct s_team		*next;
  t_players		*players;
  char			*name;
}			t_team;

typedef struct		s_command
{
  char			*cmd;
  int			tickdelay;
  void			(*callback)(struct s_server *, struct s_client *);
  int			(*validate)(struct s_server *, struct s_client *);
}			t_command;

typedef struct		s_request
{
  struct s_request	*next;
  t_command		*command;
  char			*args;
}			t_request;

typedef struct		s_egg
{
  struct s_egg		*next;
  t_team		*team;
  t_vector2d		pos;
  int			tick_eclosion;
  int			id;
}			t_egg;

typedef struct		s_player
{
  struct s_client	*client;
  enum DIRECTION	orientation;
  t_inventory		inventory;
  t_team		*team;
  t_vector2d		pos;
  int			tick_food;
  int			elevation;
  int			incantating;
  int			id;
}			t_player;

typedef struct		s_client
{
  struct s_client	*next;
  struct s_player	*player;
  t_request		*requests;
  enum MODE		mode;
  int			tick_request;
  int			sockfd;
  int			quit;
  char			writebuf[MAX_BUF_SIZE];
  int			writebuf_pos;
  char			*cmd_args;
  char			*id;
  char			*ip;
}			t_client;

typedef struct		s_gameloop
{
  int			frequence;
  struct timespec	time_start;
  struct timespec	time_current;
  long			time_elapsed;
  int			ticktime;
  int			tick;
}			t_gameloop;

typedef struct		s_server
{
  t_world		world;
  t_gameloop		gameloop;
  t_egg			*eggs;
  t_team		*teams;
  t_client		*clients;
  t_command		commands_graphic[CMDS_GRA_NUM];
  t_command		commands_client[CMDS_CLI_NUM];
  t_elevation		elevations[ELEVATIONS_NUM];
  fd_set		writefds;
  fd_set		readfds;
  int			teamsize;
  int			sockfd;
  int			fdmax;
  int			port;
}			t_server;

void		log_msg_client(t_server *server, t_client *client, char *msg);
void		log_msg_server(t_server *server, t_client *client, char *msg);
void		log_notify(t_server *server, t_client *client, char *msg);

int		set_worldpos(int n, int max);
t_case		*get_worldcase(t_world *world, int x, int y);
int		world_generate(t_world *world);
int		world_generate_ressources(t_world *world);
void		world_free(t_world *world);

enum RESSOURCE	identify_ressource(char *ressource);

void		set_vector2d(t_vector2d *vec, int x, int y);
void		rotate_vector2d(t_vector2d *vec, t_vector2d *rotation);

void		inventory_init(t_inventory *inventory);
void		init_ressources(int ress[RESSOURCE_NUM]);
int		count_ressources(int ress[RESSOURCE_NUM]);

void		check_ressources(t_server *server, int randomize);
void		check_food(t_server *server);

int		start_server(t_server *server);
void		close_server(t_server *server, int exitcode);

void		handle_connection(t_server *server);
t_client	*handle_deconnection(t_server *server, t_client *client);

int		update_gametick(t_server *server);
void		handle_signals(t_server *server);
int		handle_user(t_server *server, t_client *client);
void		handle_write(t_server *server, t_client *client);
void		msg_write(t_server *server, t_client *client,
			  char *msg, int bfree);
char		*new_msg(char *fmt, ...);
char		*get_cmdline(const int fd);
int		set_mode(t_server *, t_client *, char *cmd);

t_client	*clients_add(t_client *list, t_server *server,
			     int fd, char *ip);
t_client	*clients_del(t_client *list, t_client *client);
int		clients_fdmax(t_client *list);

t_team		*team_add(t_team *list, char *name);
t_team		*team_del(t_team *list, t_team *team);
t_team		*team_get(t_team *list, char *name);
int		team_count_slots(t_server *server, t_team *list);

t_request	*requests_push(t_request *list, t_command *, char *cmd);
t_request	*requests_pop(t_request *list);
int		requests_count(t_request *list);

t_players	*players_add(t_players *list, t_player *player);
t_players	*players_del(t_players *list, t_players *player);
t_players	*players_get(t_players *list, t_player *player);

t_egg		*eggs_add(t_egg *list, t_server *server, t_player *parent);
t_egg		*eggs_del(t_egg *list, t_egg *elem);
void		check_eggs(t_server *server);

t_player	*player_new(t_server *server, t_team *team, int x, int y);
t_player	*player_del(t_player *player);
int		player_team_join(t_player *player, t_team *team);
int		player_team_leave(t_player *player);

void		case_enter(t_player *player, t_case *mcase);
void		case_leave(t_player *player, t_case *mcase);

void		elevation_costs(t_case *, t_elevation *);

void		init_elevations(t_server *);
void		init_orientations(t_vector2d dirs[DIRECTION_NUM]);
void		init_directional_grid(t_vector2d grid[9], t_vector2d *dir);
void		get_direction(t_vector2d *vec, enum DIRECTION);
enum DIRECTION	get_random_orientation();

void		init_commands_client(t_server *server);
void		init_commands_graphic(t_server *server);
t_command	*find_command(t_server *server, t_client *client, char *cmd);
int		exec_command(t_server *server, t_client *client, t_command *);
int		exec_action(t_server *server, t_client *client);

int		validate_none(t_server *, t_client *);
int		validate_args(t_server *, t_client *);
int		validate_incantation(t_server *, t_client *);
int		valid_prerequisites(t_case *, t_player *, t_elevation *);

void		cmd_move_forward(t_server *, t_client *);
void		cmd_turn_right(t_server *, t_client *);
void		cmd_turn_left(t_server *, t_client *);
void		cmd_view(t_server *, t_client *);
void		cmd_inventory(t_server *, t_client *);
void		cmd_pickup_object(t_server *, t_client *);
void		cmd_putdown_object(t_server *, t_client *);
void		cmd_expulse(t_server *, t_client *);
void		cmd_broadcast(t_server *, t_client *);
void		cmd_incantation(t_server *, t_client *);
void		cmd_fork(t_server *, t_client *);
void		cmd_connect_nbr(t_server *, t_client *);

void		graph_map_size(t_server *, t_client *);
void		graph_bcontent(t_server *, t_client *);
void		graph_bcontent_int(t_server *, t_client *, int, int);
void		graph_mcontent(t_server *, t_client *);
void		graph_team_name(t_server *, t_client *);
void		graph_all_player(t_server *, t_client *);
void		graph_new_player(t_server *, t_player *);
void		graph_player_pos(t_server *, t_player *);
void		graph_player_lvl(t_server *, t_player *, t_client *);
void		graph_inventory(t_server *, t_player *);
void		graph_start_incantation(t_server *, t_client *, t_case *);
void		graph_end_incantation(t_server *, t_client *, t_case *);
void		graph_new_egg(t_server *, t_egg *, t_player *);
void		graph_throw(t_server *, t_player *, int);
void		graph_take(t_server *, t_player *, int);
void		graph_death(t_server *, t_player *);
void		graph_birth(t_server *, t_egg *);
void		graph_egg_hunger(t_server *, t_client *);
void		graph_get_tick(t_server *, t_client *);
void		graph_end(t_server *, char *);
void		graph_server_msg(t_server *, t_client *);
void		graph_unknown_cmd(t_server *, t_client *);
void		graph_bad_parameter(t_server *, t_client *);

#endif /* !ZAPPY_SERVER_H_ */
