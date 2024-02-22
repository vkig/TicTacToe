//
// Created by vkig on 2021. 04. 20..
//

#include "GSetNumber.hpp"
#include <string>

GSetNumber::GSetNumber() : GWidget(nullptr,0, 0, 50, 20, 2){
    number = 0;
    min = 0;
    max = 255;
    graphicRepr.load_font("assets/DS-DIGIB.TTF", height);
    int a = (height- 2 * borderSize) / 2;
    buttonUp = GButton(nullptr, posX + width - borderSize - a, posY + borderSize, a, a, 1, genv::color(224, 224, 224),
                       genv::color(0, 0, 0), nullptr, GButton::UP, genv::color(0, 0, 0));
    buttonDown = GButton(nullptr, posX + width - borderSize - a, posY + borderSize + a, a, a, 1, genv::color(224, 224, 224),
                         genv::color(0, 0, 0), nullptr, GButton::DOWN, genv::color(0, 0, 0));
    if(std::max(graphicRepr.twidth(std::to_string(min)), graphicRepr.twidth(std::to_string(max))) > width - a - 4 * borderSize){
        resize(std::max(graphicRepr.twidth(std::to_string(min)), graphicRepr.twidth(std::to_string(max)))+a+ 4 * borderSize, height);
    }
}

GSetNumber::GSetNumber(Application* _parent, int x, int y, int _width, int _height, int _borderSize, int _number, int _min, int _max,
                       genv::color _mainColor, genv::color _borderColor) : GWidget(_parent, x, y, _width, _height, _borderSize, _mainColor, _borderColor),
                                                                           number(_number), min(_min), max(_max){
    graphicRepr.load_font("assets/DS-DIGIB.TTF", height);
    int a = (_height- 2 * borderSize) / 2;
    buttonUp = GButton(_parent, x + width - borderSize - a, y + borderSize, a, a, 1, genv::color(224, 224, 224),
                       genv::color(0, 0, 0), nullptr, GButton::UP, genv::color(0, 0, 0));
    buttonDown = GButton(_parent, x + width - borderSize - a, y + borderSize + a, a, a, 1, genv::color(224, 224, 224),
                         genv::color(0, 0, 0), nullptr, GButton::DOWN, genv::color(0, 0, 0));
    if(std::max(graphicRepr.twidth(std::to_string(min)), graphicRepr.twidth(std::to_string(max))) > width - a - 4 * borderSize){
        resize(std::max(graphicRepr.twidth(std::to_string(min)), graphicRepr.twidth(std::to_string(max)))+a+ 4 * borderSize, height);
    }
}

void GSetNumber::resize(int _width, int _height) {
    width = _width;
    height = _height;
    int a = (_height- 2 * borderSize) / 2;
    graphicRepr = genv::canvas(width, height);
    graphicRepr.load_font("assets/DS-DIGIB.TTF", height);
    buttonUp.resize(a, a);
    buttonDown.resize(a, a);
    buttonUp.changePosition(posX + _width - borderSize - a, posY + borderSize);
    buttonDown.changePosition(posX + _width - borderSize - a, posY + borderSize + a);
}

void GSetNumber::show() {
    GWidget::show();
    std::string num = std::to_string(number);
    graphicRepr << genv::move_to((width - buttonUp.getWidth()) / 2 - graphicRepr.twidth(num) / 2, height / 2 - (graphicRepr.cascent() + graphicRepr.cdescent()) / 2) << genv::color(0, 0, 0) << genv::text(num);
    genv::gout<<genv::stamp(graphicRepr, posX, posY);
    buttonUp.show();
    buttonDown.show();
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
        if(buttonUp.isMouseOnIt(ev.pos_x, ev.pos_y)){
            if(ev.button == genv::btn_left) {
                increase();
            }
            buttonUp.action(ev);
            buttonDown.deselect();
            show();
        }
        else if(buttonDown.isMouseOnIt(ev.pos_x, ev.pos_y)){
            if(ev.button == genv::btn_left) {
                decrease();
            }
            buttonUp.deselect();
            buttonDown.action(ev);
            show();
        }
        else if(buttonUp.isSelected() || buttonDown.isSelected()){
            buttonUp.deselect();
            buttonDown.deselect();
            show();
        }
    }
}

void GSetNumber::changePosition(int x, int y) {
    posX = x;
    posY = y;
    int a = (height- 2 * borderSize) / 2;
    buttonUp.changePosition(x + width - borderSize - a, y + borderSize);
    buttonDown.changePosition(x + width - borderSize - a, y + borderSize + a);
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
    buttonDown.deselect();
    buttonUp.deselect();
}

