#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Chart.H>

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    Fl_Window *win = new Fl_Window(1000, 480);
    Fl_Chart  *chart = new Fl_Chart(20, 20, win->w()-40, win->h()-40, "Chart");
    chart->bounds(-125.0, 125.0);
    chart->type(FL_FILLED_CHART);//FL_BAR_CHART,FL_SPIKE_CHART,FL_FILLED_CHART
    for ( double t=0; t<15; t+=0.5 ) {
        double val = sin(t) * 125.0;
        static char val_str[20];
        sprintf(val_str, "%.0lf", val);
        chart->add(val, val_str, (val<0)?FL_RED:FL_GREEN);
    }
    win->resizable(win);
    win->show();
    return(Fl::run());
}
