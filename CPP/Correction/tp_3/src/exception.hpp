// Gardien //---------------------------------------------------------------------------------------
#ifndef EXCEPTION_HPP_e2de9d8bffa542748c65a181aaf7a778
#define EXCEPTION_HPP_e2de9d8bffa542748c65a181aaf7a778

// Entetes //---------------------------------------------------------------------------------------
#include <exception>
#include <demangle.hpp>

// Classe  E x c e p t i o n C h a i n e //---------------------------------------------------------
class ExceptionChaine : public std::exception {
 //----------------------------------------------------------------------------------------Attributs
 private:
  std::string message_;

 //-------------------------------------------------------------------------------------Constructeur
 public:
  ExceptionChaine(const std::string & type)
  : message_("Conversion en chaine impossible pour '" + demangle(type) + "'") {}

  // Constructeur template (question subsidiaire)
  // template <typename T> ExceptionChaine(const T &)
  // : message_("Conversion en chaine impossible pour '" + demangle(typeid(T).name()) + "'") {}

 //---------------------------------------------------------------------------------------------What
 public:
  const char * what() const noexcept override { return message_.c_str(); }
};

// Fin //-------------------------------------------------------------------------------------------
#endif
