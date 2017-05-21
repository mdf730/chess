// new2.cpp
// this program tests some of gfxnew's new features,
// including detecting several keyboard and mouse events,
// and changing the mouse cursor

#include <iostream>
using namespace std;

#include "gfxnew.h"

int main()
{
  char c;   
  int event; 
  bool ispressed = false;   // flag for keyboard events
  bool isclicked = false;   // flag for mouse events

  gfx_open(600, 500, "My window"); 

  while(true) { 
    if((event = gfx_event_waiting()) != 0) {   // if 'something' is happening
      c = gfx_wait();

      // keyboard events
      if (c >= 32 && c <= 126) {     // range of most keyboard keys
        if(event == 1) {             // key press event
          cout << "you pressed key: " << c << endl;
          ispressed = true;
        } else if (event == 2) {     // key release event
          if(ispressed) cout << "you released key: " << c << endl;
          ispressed = 0;
        }
      }

      // mouse events
      if (c == 1 || c == 2 || c == 3) {    // mouse click (left, middle, or right)
        if(event == 3) {             // mouse down event
          cout << "you clicked mouse button " << (int)c << endl;
          isclicked = true;
        } else if (event == 4) {     // mouse release event
          if(isclicked) cout << "you unclicked mouse button " << (int)c << endl;
          isclicked = false;
        }
      }

      if (event == 5) {              // mouse move event
        cout << "mouse is moving; it's at: ";
        cout << "(" << gfx_xpos() << "," << gfx_ypos() << ")" << endl;
      }

      // try a few cursors
      if (c == '=') gfx_changecursor(XC_crosshair);
      if (c == 'w') gfx_changecursor(XC_watch);
      if (c == 'a') gfx_changecursor(XC_arrow);
      if (c == 'g') gfx_changecursor(XC_gumby);
      if (c == 'h') gfx_changecursor(XC_hand1);
      if (c == 't') gfx_changecursor(XC_heart);
      if (c == 'p') gfx_changecursor(XC_pencil);

      // exit the loop
      if (c == 'q')  break;
    }
  }

  return 0;
}