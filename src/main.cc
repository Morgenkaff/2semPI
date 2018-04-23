#include <iostream>
#include "pin_ctrl.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    
    PinCtrl pin_ctrl;
    
    cout << "Pin initialized: " << pin_base.init() << endl;
    
    return 0;
    
}
