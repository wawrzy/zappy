#ifndef CONTENT_HPP_
# define CONTENT_HPP_

# include <SFML/Graphics.hpp>
# include "Case.hpp"

  class   Content {

    private:

    sf::RenderWindow *_window;

    int _posX;
    int _posY;
    
    bool _display;

    sf::Font _font;

    private:
    
    void write_eggs(Case *, sf::Color);
    void write_food(Case *, sf::Color);
    void write_linemate(Case *, sf::Color);
    void write_deraumere(Case *, sf::Color);
    void write_sibur(Case *, sf::Color);
    void write_mendiane(Case *, sf::Color);
    void write_phiras(Case *, sf::Color);
    void write_thystame(Case *, sf::Color);

    public:

    Content(sf::RenderWindow *, int, int);
    ~Content();

    void display_case(Case *, bool, sf::Color);
    void display(bool);
    
  };

#endif /* !CONTENT_HPP_ */
