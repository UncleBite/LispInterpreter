
class InterpreterSemanticError: public std::runtime_error {
public:
  InterpreterSemanticError(const std::string& message): std::runtime_error(message){};
};

