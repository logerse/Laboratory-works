#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

class UserInterface {
protected:
  int GetUserChoice(void)
  {
    int result = 0;
    std::cout << ">>> ";
    std::cin >> result;
    return result;
  };

  void PrintMenu(void)
  {
    printf("\E[H");
    printf("\E[J");
    std::cout << "#----- Menu -----#" << std::endl;
    PrintMenuOptions();
    std::cout << "#----------------#" << std::endl;
  };

  void PrintMenu(const char *err)
  {
    PrintMenu();
    std::cout << "[X] Error: " << err << std::endl;
    std::cout << "#----------------#" << std::endl;
  };
  virtual void PrintMenuOptions(void) = 0;
public:
  virtual void Start(void) = 0;
};

