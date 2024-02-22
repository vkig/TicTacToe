//
// Created by vkig on 2021. 04. 20..
//

#include "GButton.hpp"

#include <utility>
#include "Application.hpp"

GButton::GButton() : GWidget(nullptr, 0, 0, 100, 30) {
    _type = LABELED;
    text = "Button";
    textColor = genv::color(255, 255, 255);
    pressed = false;
    enabled = true;
    f = nullptr;
}

GButton::GButton(Application* _parent, int x, int y, int _width, int _height, int _bordersize, genv::color _main, genv::color _bordercolor, std::function<void()> _f,
                 type _t, genv::color _textcolor, std::string _text) : GWidget(_parent, x, y, _width, _height, _bordersize, _main, _bordercolor) {
    f = std::move(_f);
    text = std::move(_text);
    textColor = _textcolor;
    _type = _t;
    pressed = false;
    enabled = true;
}

void GButton::show() {
    GWidget::show();
    if(selected && pressed) {
        graphicRepr<<genv::color(0, 255, 255);
    }
    else {
        graphicRepr << textColor;
    }
    if(_type == LABELED){
        graphicRepr<<genv::move_to(width/2-graphicRepr.twidth(text)/2,height/2-(graphicRepr.cascent()+graphicRepr.cdescent())/2)<<genv::text(text);
    }
    else if(_type == UP){
        for(int i = 0;i<width;i++)
        {
            for (int j = 0; j < height; j++) {
                if(2.0/3.0*height > j && j > -1.5*height/width*(i-1.0/2.0*width)+ 1.0/3.0*height &&
                        j > 1.5*height/width*(i-1.0/2.0*width)+ 1.0/3.0*height)
                {
                    graphicRepr<<genv::move_to(i, j)<<genv::dot;
                }
            }
        }
    }
    else if(_type == DOWN){
        for(int i = 0;i<width;i++)
        {
            for (int j = 0; j < height; j++) {
                if(1.0/3.0*height < j && j < -1.5*height/width*(i-1.0/2.0*width)+ 2.0/3.0*height &&
                   j < 1.5*height/width*(i-1.0/2.0*width)+ 2.0/3.0*height)
                {
                    graphicRepr<<genv::move_to(i, j)<<genv::dot;
                }
            }
        }
    }
    genv::gout<<genv::stamp(graphicRepr, posX, posY);
}

void GButton::action(genv::event& ev) {
    if(ev.type == genv::ev_mouse && isMouseOnIt(ev.pos_x, ev.pos_y) && enabled)
    {
        if(ev.button == genv::btn_left)
        {
            select();
            press();
            show();
        }
        else if(ev.button == -genv::btn_left)
        {
            if(f){
                f();
            }
            release();
            show();
        }
    }
}

void GButton::press() {
    pressed = true;
}

void GButton::release() {
    pressed = false;
}

void GButton::changeType(type _t) {
    _type = _t;
}

void GButton::setText(std::string _text) {
    this->text = std::move(_text);
    show();
}





