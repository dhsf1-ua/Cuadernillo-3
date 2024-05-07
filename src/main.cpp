#include <iostream>
#include "include/tabbcalendario.h"
using namespace std;

int
main(void)
{
  //Comprobar borrar hoja
  
  TABBCalendario a,b,c;
  TCalendario c7(7, 7,2000,(char *)"fecha"),c4(4,4,2000,(char *)"fecha"),c10(10,10,2000,(char *)"fecha");
  TCalendario c2(2,2,2000,(char *)"fecha"),c5(5,5,2000,(char *)"fecha"),c8(8,8,2000,(char *)"fecha"),c9(9,9,2000,(char *)"fecha");
  TCalendario c3(3,3,2000,(char *)"fecha"),c1(1,1,2000,(char *)"fecha"),c12(12,12,2000,(char *)"fecha"),c6(6,6,2000,(char *)"fecha");
  
  
  a.Insertar(c7);
  a.Insertar(c4);
  a.Insertar(c10);
  a.Insertar(c2);
  a.Insertar(c5);
  a.Insertar(c8);
  a.Insertar(c9);
  
  
  cout<<a<<endl;
  
  return 0;
}