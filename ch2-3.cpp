// Standard Library
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cmath>
#include <string>

// User-Defined Headers
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

struct HalfBakedVector
{
   size_t len;
   double * elements;
};

void VectorInit( HalfBakedVector&, size_t );
void VectorPrintToStdout( struct HalfBakedVector& self );
void VectorFree( struct HalfBakedVector& );
double VectorElementAt( struct HalfBakedVector& self, int32_t idx );
void VectorSetElementAt( struct HalfBakedVector& self, int32_t idx, double val);
/*****************************************/
/*****************************************/

class Vector
{
   public:
      Vector(size_t m_len):
         // The lines below are for the private variables of the class and
         // are called the initializer list.
	 // 🗒: The '=' syntax won't work here. It needs to be the {} pair.
	 // 🗒: The order of initialization is based on the ordering of the
	 // 	private member declarations! Note the order of this list...
         m_elements { new double[m_len] },
         m_len {m_len}
         {
            /* Empty constructor body */
         }

      ~Vector()
      {
         delete[] m_elements;
      }

      double& operator [] (int i)  // Operator [] overload (subscript function)
      {
         if ( std::abs(i) >= m_len )
         {
            throw std::out_of_range(
                     std::string("Vector::operator[] idx ≥ vec len! idx: ") +
                     std::to_string(i) +
                     std::string(", vector length: ") +
                     std::to_string(_len) +
                     std::string(", max valid idx: ") +
                     std::to_string(_len - 1)
                  );
         }

         size_t idx = i;
         if ( i < 0 )
         {
            // Wrap-around. Allows for convenient indexing of last element
            idx = m_len + i;
         }

         return m_elements[idx];
      }

      size_t len() const
      {
         return m_len;
      }

      double * begin(void) const
      {
         return &m_elements[0];
      }

      double * end(void) const
      {
         return &m_elements[m_len];
      }

      void Print(void) const
      {
         for ( const auto& x : *this )
         {
            std::cout << x << " ";
         }
         std::cout << '\n';
      }

   private:
      double * m_elements;
      size_t m_len;
};

/*****************************************/

int main(void)
{
   /* Half-baked procedural vector class usage */
   struct HalfBakedVector vec1;
   VectorInit( vec1, 10 );
   for ( int32_t i = 0; i < 10; i++ )
   {
      VectorSetElementAt( vec1, i, (double)i * 2.5 );
   }
   std::cout << "vec1:" << '\n';
   VectorPrintToStdout(vec1);

   /* First-draft of custom C++ vector class usage */
   Vector vec2(10);
   for ( int32_t i = 0; i < 10; i++ )
   {
      vec2[i] = (double)i * 2.5;
   }
   std::cout << "vec2:" << '\n';
   vec2.Print();

   std::cout << '\n';
   std::cout << "Negative Indexing Demo:" << '\n';
   std::cout << "VectorElementAt(vec1, -1): " << VectorElementAt(vec1, -1) << '\n';
   std::cout << "vec2[-1]: " << vec2[-1] << '\n';

   std::cout << '\n';
   std::cout << "Exception Demo:" << '\n';
   try
   {
      vec2[10000];
   } catch ( std::out_of_range& e )
   {
      std::cout << "Caught out-of-bounds access on vec2[10000];" << '\n' <<
                   '\t' << e.what();
   }
   std::cout << '\n';

   try
   {
      vec2[-10000];
   } catch ( std::out_of_range& e )
   {
      std::cout << "Caught out-of-bounds access on vec2[-10000];" << '\n' <<
                   '\t' << e.what();
   }
   std::cout << '\n';

   VectorFree(vec1);
   // vec2's array will automatically be free'd when vec2 goes out of scope
   // and its destructor is called, so no need to explicitly free. RAII for ya!

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
   std::cout << '\n';
   std::cout << "Attempting range-for loop to print out all possible CppTrafficLight_E values:";
   std::cout << '\n';
   i = 0;
   for ( CppTrafficLight_E val : CppTrafficLight_E{} )
   {
      std::cout << val << ", ";
      if ( ++i > 10 ) break;
   }
   std::cout << "(stopped after " << i << " iterations)";
   std::cout << '\n' << '\t';
   std::cout << "Does not work right because the ++ operator is set to wrap-around once we get"
                " to the last valid enum, and range-for loops need a way to identify when the"
                " iterator has incremented past the end to end the range-for." << '\n';
}

/*****************************************/
void VectorInit( struct HalfBakedVector& self, size_t len )
{
   self.elements = new double[len];
   self.len = len;
}

// Apparently, C++ lets you omit the `struct` keyword when declaring a struct
// type... As if it's an automatic typedef. I dislike that... But given how
// often aggergate types are typedef'd away in many places, this appeases
// that (laziness).
void VectorPrintToStdout( HalfBakedVector& self )
{
   for ( size_t i = 0; i < self.len; i++ )
   {
      std::cout << self.elements[i] << " ";
   }
   std::cout << std::endl;
}

void VectorFree( struct HalfBakedVector& self )
{
   delete self.elements;
}

double VectorElementAt( struct HalfBakedVector& self, int32_t idx )
{
   int64_t i = std::abs(idx);
   if ( i >= (int32_t)self.len )
   {
      // TODO: Return error for out-of-bounds?
      return std::nan("");
   }

   // Wrap around to allow for negative indexing (convenient for indexing end
   // of vector), like v[-1].
   if ( idx < 0 )
   {
      i = idx + self.len;
   }

   return self.elements[i];
}

void VectorSetElementAt( struct HalfBakedVector& self, int32_t idx, double val)
{
   int64_t i = std::abs(idx);
   if ( i >= (int32_t)self.len )
   {
      // TODO: Return error for out-of-bounds?
      return;
   }

   // Wrap around to allow for negative indexing (convenient for indexing end
   // of vector), like v[-1].
   if ( i < 0 )
   {
      i += self.len;
   }

   self.elements[i] = val;

   return;
}
/*****************************************/
