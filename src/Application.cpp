//
// Created by vkig on 2021. 04. 29..
//

#include "Application.hpp"

using namespace genv;

Application::Application() = default;

void Application::eventManager() {
    genv::event ev;
    GWidget* focus = nullptr;
    bool init = true;
    while(init || (gin>>ev && ev.keycode != key_escape)) {
        if (ev.type == ev_mouse && ev.button == btn_left) {
            if (!focus || !focus->isMouseOnIt(ev.pos_x, ev.pos_y)) {
                if (focus) {
                    focus->deselect();
                    focus->show();
                }
                focus = nullptr;
                for (GWidget *ptr : widgets) {
                    if (ptr->isMouseOnIt(ev.pos_x, ev.pos_y)) {
                        focus = ptr;
                        focus->select();
                        focus->show();
                    }
                }
            }
        }
        if (focus) {
            focus->action(ev);
        }
        for (GWidget * w : widgets) {
            if(!w->isHidden()){
                w->show();
            }
        }
        if(init){
            init = false;
        }
        gout << refresh;
    }
}

void Application::addWidget(GWidget * w) {
    widgets.push_back(w);
}
