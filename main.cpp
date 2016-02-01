#include "manager.h"

int main(int, char*[]) {
   try {
      Manager* manager;
      do
      {
       manager = new Manager();
       manager->play();
      }while(manager->checkReset());
   delete manager;
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
