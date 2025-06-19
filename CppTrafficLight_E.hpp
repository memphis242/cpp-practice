#include <iostream>

enum class CppTrafficLight_E
{
   Green,
   Yellow,
   Red,
   NumOfTrafficLightOptions
};

CppTrafficLight_E& operator ++ (CppTrafficLight_E& light);
CppTrafficLight_E operator ++ (CppTrafficLight_E& light, int);
std::ostream& operator << ( std::ostream& os, CppTrafficLight_E light );
