//
// Created by vkig on 2021. 04. 20..
//

#include "GSetNumber.hpp"
#include <string>

GSetNumber::GSetNumber() : GWidget(nullptr,0, 0, 50, 20, 2){
    number = 0;
    min = 0;
    max = 255;
    graphicRepr.load_font("DS-DIGIB.TTF", height);
    int a =  (height-2*bordersize)/2;
    buttonup = GButton(nullptr,posx+width-bordersize-a, posy+bordersize, a, a, 1, genv::color(224, 224, 224),
                       genv::color(0, 0, 0), nullptr, GButton::UP, genv::color(0, 0, 0));
    buttondown = GButton(nullptr,posx+width-bordersize-a, posy+bordersize+a, a, a, 1, genv::color(224, 224, 224),
                         genv::color(0, 0, 0), nullptr, GButton::DOWN, genv::color(0, 0, 0));
    if(std::max(graphicRepr.twidth(std::to_string(min)), graphicRepr.twidth(std::to_string(max))) > width - a - 4*bordersize){
        resize(std::max(graphicRepr.twidth(std::to_string(min)), graphicRepr.twidth(std::to_string(max)))+a+4*bordersize, height);
    }
}

GSetNumber::GSetNumber(Application* _parent, int x, int y, int _width, int _height, int _bordersize, int _number, int _min, int _max,
                       genv::color _main,genv::color _bordercolor) : GWidget(_parent, x, y, _width, _height, _bordersize, _main, _bordercolor),
                       number(_number), min(_min), max(_max){
    graphicRepr.load_font("DS-DIGIB.TTF", height);
    int a =  (_height-2*bordersize)/2;
    buttonup = GButton(_parent, x+width-bordersize-a, y+bordersize, a, a, 1, genv::color(224, 224, 224),
                       genv::color(0, 0, 0), nullptr, GButton::UP, genv::color(0, 0, 0));
    buttondown = GButton(_parent, x+width-bordersize-a, y+bordersize+a, a, a, 1, genv::color(224, 224, 224),
                         genv::color(0, 0, 0), nullptr, GButton::DOWN, genv::color(0, 0, 0));
    if(std::max(graphicRepr.twidth(std::to_string(min)), graphicRepr.twidth(std::to_string(max))) > width - a - 4*bordersize){
        resize(std::max(graphicRepr.twidth(std::to_string(min)), graphicRepr.twidth(std::to_string(max)))+a+4*bordersize, height);
    }
}

void GSetNumber::resize(int _width, int _height) {
    width = _width;
    height = _height;
    int a = (_height-2*bordersize)/2;
    graphicRepr = genv::canvas(width, height);
    graphicRepr.load_font("DS-DIGIB.TTF", height);
    buttonup.resize(a,a);
    buttondown.resize(a,a);
    buttonup.changePosition(posx + _width-bordersize-a,posy+bordersize);
    buttondown.changePosition(posx+_width-bordersize-a, posy+bordersize+a);
}

void GSetNumber::show() {
    GWidget::show();
    std::string num = std::to_string(number);
    graphicRepr<<genv::move_to((width-buttonup.getWidth())/2-graphicRepr.twidth(num)/2, height/2-(graphicRepr.cascent()+graphicRepr.cdescent())/2)<<genv::color(0, 0, 0)<<genv::text(num);
    genv::gout<<genv::stamp(graphicRepr, posx, posy);
    buttonup.show();
    buttondown.show();
}

void GSetNumber::action(genv::event &ev) {
    if(ev.type == genv::ev_key)
    {
        if(ev.keycode == genv::key_pgup)
        {
            increase(10);
            show();
        }
        else if(ev.keycode == genv::key_pgdn)
        {
            decrease(10);
            show();
        }
        else if(ev.keycode == genv::key_up)
        {
            increase();
            show();
        }
        else if(ev.keycode == genv::key_down)
        {
            decrease();
            show();
        }
    }
    else if(ev.type == genv::ev_mouse && (ev.button == genv::btn_left || ev.button == -genv::btn_left))
    {
        if(buttonup.isMouseOnIt(ev.pos_x, ev.pos_y)){
            if(ev.button == genv::btn_left) {
                increase();
            }
            buttonup.action(ev);
            buttondown.deselect();
            show();
        }
        else if(buttondown.isMouseOnIt(ev.pos_x, ev.pos_y)){
            if(ev.button == genv::btn_left) {
                decrease();
            }
            buttonup.deselect();
            buttondown.action(ev);
            show();
        }
        else if(buttonup.isSelected() || buttondown.isSelected()){
            buttonup.deselect();
            buttondown.deselect();
            show();
        }
    }
}

void GSetNumber::changePosition(int x, int y) {
    posx = x;
    posy = y;
    int a = (height-2*bordersize)/2;
    buttonup.changePosition(x+width-bordersize-a,y+bordersize);
    buttondown.changePosition(x+width-bordersize-a, y+bordersize+a);
}

int GSetNumber::getValue() const {
    return number;
}

void GSetNumber::increase(int value) {
    if(number+value <= max)
        number+=value;
    else
        number = max;
}

void GSetNumber::decrease(int value) {
    if(number-value >= min)
        number-=value;
    else
        number = min;
}

void GSetNumber::deselect() {
    GWidget::deselect();
    buttondown.deselect();
    buttonup.deselect();
}

