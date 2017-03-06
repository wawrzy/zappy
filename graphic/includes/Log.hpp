

#ifndef LOG_HPP__
# define LOG_HPP__

# include <SFML/Graphics.hpp>
# include <vector>
# include <string>

class Log
{
    private:

    sf::RenderWindow *_window;

    int _posX;
    int _posY;
    int _width;
    int _height;
    
    bool _display;
    
    std::vector<std::string> _logs;
    std::vector<std::string> _from;
    std::vector<sf::Color> _colors;

    public:

    Log(sf::RenderWindow *, int, int, int, int);
    ~Log();
    void display();
    void write(std::string, std::string, sf::Color);
    void setDisplay();
};

#endif /* !LOG_HPP__ */