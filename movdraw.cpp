#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <iostream>
#include <cmath>

using namespace std;

// LED DISPLAY CLASS
class MyDisplay : public Fl_Group {
     int _value;         // 0 - 100
public:
     MyDisplay(int X, int Y, int W, int H, const char*L=0) : Fl_Group(X,Y,W,H,L) {
         _value = 0;
     }
     void value(int val) {
         _value = val;
         redraw();
     }
     void draw() {
         Fl_Group::draw();
         // TRIGGER GRAPHIC DRAWING CODE
         fl_color(82);//42
         int w = 1;
         for ( int t=0; t<_value; t+=2) {
             float f = ( t / 100.0 );            // f = 0.0 ~ 1.0
             float f2 = ( abs(t-50) / 100.0 );   // f = .5 ~ 0 ~ .5
             int xoff = (int)( f2 * f2 * 100 + .5);
             w += 1;
             int x1 = x() + 10 + xoff;
             int x2 = x() + 10 + w + xoff;
             int y1 = y() + h() - 10 - t;
             fl_line(x1, y1, x2, y1);
         }
     }
};
//
// TEST THE CLASS -- Send a sine wave to the class off a timer
//
MyDisplay *disp = 0;
void Timer_CB(void *) {
     static float f = 6.28/4; f += .1;
     float v = ( sin(f) + 1.0 ) * .5;    // sine wave: 0 ~ 1
     v = v * 100;                        // sine wave: 0 ~ 100
     disp->value((int)(v + .5));
     Fl::repeat_timeout(0.03, Timer_CB);
}


int main()
{
     Fl_Double_Window win(240,240);
     disp = new MyDisplay(20,20,240-40,240-40);
     disp->box(FL_BORDER_BOX);
     disp->value(100);
     Fl::add_timeout(1.0, Timer_CB);
     win.show();
     return(Fl::run());
}
