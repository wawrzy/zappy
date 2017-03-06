#ifndef ERROR_HPP_
# define ERROR_HPP_

# include <stdexcept>
# include <string>

  class   Error : public std::exception {
    private:
      std::string   mess;

    public:

      Error(std::string const& mess){
        this->mess = mess;
      }

      virtual ~Error() throw() {}

      const char   *what() const throw() {
        return (this->mess.c_str());
      }

  };

#endif /* !ERROR_HPP_ */