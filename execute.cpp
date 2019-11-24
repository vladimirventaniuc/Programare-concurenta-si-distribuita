#include <stdlib.h> 
#include <stdio.h> 
#include <iostream>
#include <string>

using namespace std;
int main()
{
  string parameters[5] = {"rotate90", "rotate180","rotate270","invertColors","blurImage"};
  for(int i=0;i<=2;i++){
    for(int i=0;i<5;i++){
      string toExecute = "./col-img-display images/47mb.jpg ";
      // string toExecute2 = "./secv-img-display images/47mb.jpg ";
      toExecute = toExecute + parameters[i];
      // toExecute2 = toExecute2 + parameters[i];
      cout<<toExecute<<endl;
      // cout<<toExecute2<<endl;
      // cout<<parameters[i];
      system (toExecute.c_str());  
      // system (toExecute2.c_str());  
    }
    
  }
  system("./calculateAvrage");
  
  
  return 0;
}