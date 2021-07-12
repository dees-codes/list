#include <iomanip>
#include <iostream>
#include "list.h"

using namespace std;

int main(int argc, char* argv[])
{
  if (argc != 2)
    {
      cerr << "Incorrect number of arguments." <<endl;
      return 1;
    }

  srand(static_cast<unsigned>(time(nullptr)));
  unsigned array_size {static_cast<unsigned>(stoul(argv[1]))};

  

  // put n random values into the list???

  
  List <unsigned> list1;

  for (unsigned count {0}; count < array_size; count++)
    {
      list1.push_back(static_cast<unsigned>(rand()%1500 + 1));
      } 
  
  /* for (unsigned count {0}; count < array_size; count++)
    {
      list1.push_back(static_cast<unsigned>(rand()));
      }
      cerr << array_size << ' ' << list1.reverse() << endl;*/



  unsigned value_to_find {static_cast<unsigned>(rand()%1500 + 1) };

  unsigned op=0;

  list1.find(value_to_find, op);
  
  //cout << "The value to find was" << value_to_find << endl;
  cerr <<  array_size  << ' ' << op << endl;

  return 0;
}
