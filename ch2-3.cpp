#include <iostream>
#include "CppTrafficLight_E.hpp"
#include "CTrafficLight_E.h"

/*****************************************/
/* Half-baked procedural vector class... */

// This is somehow supposed to be the "procedural" version of a class??
// Some of the commentary from Bjorne motivating the idea of classes
// implies that classes are the only way to couple data to operations
// on that data, but that's far from the truth. See any one of the many
// C collection libraries out there, including my own ccol!
// As far as I can tell, the main advantages OOP languages (like C++) offer
// are "zero-overhead" abstractions, mechanisms like interfaces and mix-ins,
// and an easier time generic programming.
// Otherwise, you can still separate implementation from interface, have
// _actually_ "private" invisible members and methods, and even do generic
// programming.

struct HalfBakedVector_S
{
   size_t sz;
   double * elements;
};

void VectorInit( HalfBakedVector_S&, size_t );
void VectorPrintToStdout( struct HalfBakedVector_S& self );
void VectorFree( struct HalfBakedVector_S& );
/*****************************************/
/*****************************************/

class Vector
{
   private:
      double * elements;
      size_t sz;

   public:
      Vector(size_t sz):
         // The lines below are for the private variables of the class and
         // are called the initializer list.
	 // 🗒: The '=' syntax won't work here. It needs to be the {} pair.
	 // 🗒: The order of initialization is based on the ordering of the
	 // 	private member declarations! Note the order of this list...
         elements { new double[sz] },
         sz {sz}
         {
            /* Empty constructor body */
         }
      
      ~Vector()
      {
         delete[] elements;
      }
      
      double& operator [] (int i)  // Operator [] overload (subscript function)
      {
         return elements[i];
      }

      size_t Size()
      {
         return sz;
      }
      
      void Print()
      {
         for ( size_t i = 0; i < sz; i++ )
         {
            std::cout << elements[i] << " ";
         }
         std::cout << std::endl;
      }      
};

/*****************************************/

int main(void)
{
   /* Half-baked procedural vector class usage */
   struct HalfBakedVector_S vec1;
   VectorInit( vec1, 10 );
   // Print uninitialized elements of the vector...
   VectorPrintToStdout(vec1);
   VectorFree(vec1);

   /* First-draft of custom C++ vector class usage */
   Vector vec2(10);
   vec2.Print();
   // vec2's array will automatically be free'd when vec2 goes out of scope
   // and its destructor is called.

   /* Enums */
   std::cout << std::endl;

   enum CTrafficLight_E c_traffic_light = Red;
   CppTrafficLight_E cpp_traffic_light = CppTrafficLight_E::Red;

   std::cout << "Initial Enum Values: " << std::endl <<
                "\tC-Style Enum: " << CTrafficLight_E_ToString(c_traffic_light) << std::endl <<
                "\tC++-Style Enum: " << cpp_traffic_light << std::endl;

   // Increment enums
   c_traffic_light = (enum CTrafficLight_E)(c_traffic_light + 1);
   cpp_traffic_light++;

   std::cout << "Increment: " << std::endl <<
                "\tC-Style Enum: " << CTrafficLight_E_ToString(c_traffic_light) << std::endl <<
                "\tC++-Style Enum: " << cpp_traffic_light << std::endl;

   // Increment enums
   c_traffic_light = (enum CTrafficLight_E)(c_traffic_light + 2);
   cpp_traffic_light++;
   cpp_traffic_light++;

   std::cout << "Incremented Twice More: " << std::endl <<
                "\tC-Style Enum: " << CTrafficLight_E_ToString(c_traffic_light) << std::endl <<
                "\tC++-Style Enum: " << cpp_traffic_light << std::endl;

   // Range-for over the enumeration
   // Won't work because increment operation wraps around, so we never get to
   // end().
//   std::cout << '\n';
//   for ( CppTrafficLight_E val : CppTrafficLight_E{} )
//   {
//      std::cout << val << ", ";
//   }
//   std::cout << '\n';
}

/*****************************************/
void VectorInit( struct HalfBakedVector_S& self, size_t sz )
{
   self.elements = new double[sz];
   self.sz = sz;
}

// Apparently, C++ lets you omit the `struct` keyword when declaring a struct
// type... As if it's an automatic typedef. I dislike that... But given how
// often aggergate types are typedef'd away in many places, this appeases
// that (laziness).
void VectorPrintToStdout( HalfBakedVector_S& self )
{
   for ( size_t i = 0; i < self.sz; i++ )
   {
      std::cout << self.elements[i] << " ";
   }
   std::cout << std::endl;
}

void VectorFree( struct HalfBakedVector_S& self )
{
   delete self.elements;
}
/*****************************************/
