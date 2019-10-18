    #include <iostream>
    #include <cmath>
    using namespace std;

int cube (int number)
{
  int kub;
  kub=pow(number,3);
  return kub;
}


    int main()
    {    
        int number;
        cout << "Enter a number: ";
        cin >> number;
        
        cout << "kub je  " << cube(number);    
        return 0;
    }


