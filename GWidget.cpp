//
// Created by vkig on 2021. 04. 20..
//

#include "GWidget.hpp"
#include <algorithm>

GWidget::GWidget() : main(genv::color(224, 224, 224)), borderc(genv::color(255, 255, 255)) {
    parent = nullptr;
    hidden = false;
    posx = 0;
    posy = 0;
    width = 10;
    height = 10;
    bordersize = 2;
    graphicRepr = genv::canvas(width, height);
    graphicRepr.load_font("times.ttf", std::min(int(height*2.0/3.0), 32));
}

GWidget::GWidget(Application* _parent, int x, int y, int _width, int _height, int _bordersize, genv::color _main, genv::color _borderc)
                : main(_main), borderc(_borderc){
    parent = _parent;
    hidden = false;
    posx = x;
    posy = y;
    width = _width;
    height = _height;
    bordersize = _bordersize;
    selected = false;
    graphicRepr = genv::canvas(width, height);
    graphicRepr.load_font("times.ttf", std::min(int(height*2.0/3.0), 32));
}

bool GWidget::isMouseOnIt(int ex, int ey) const {
    return (ex >= posx && ex < posx + width && ey >= posy && ey < posy + height);
}

void GWidget::resize(int _width, int _height) {
    width = _width;
    height = _height;
    graphicRepr = genv::canvas(width, height);
}

void GWidget::show() {
    hidden = false;
    if(selected) {
        genv::color c = genv::color(0, 255, 255);
        graphicRepr << c << genv::move_to(0, 0) << genv::box_to( width - 1,   height - 1);
    }
    else {
        graphicRepr << borderc << genv::move_to(0, 0) << genv::box_to(width - 1, height - 1);
    }
    graphicRepr << main << genv::move_to(bordersize, bordersize)
                   << genv::box_to( width - bordersize - 1,height - bordersize - 1);
    genv::gout<<genv::stamp(graphicRepr, posx, posy);
}

void GWidget::hide() {
    hidden=true;
    genv::gout<<genv::move_to(posx, posy)<<genv::color(0, 0, 0)<<genv::box_to(posx + width -1, posy + height - 1);
}

bool GWidget::isHidden() {
    return hidden;
}

void GWidget::setBorderSize(int bs) {
    bordersize = bs;
}

void GWidget::changePosition(int x, int y) {
    posx = x;
    posy = y;
}

int GWidget::getWidth() const{
    return width;
}

int GWidget::getHeight() const {
    return height;
}

int GWidget::getPosX() const {
    return posx;
}

int GWidget::getPosY() const {
    return posy;
}

void GWidget::select() {
    selected = true;
}

void GWidget::deselect() {
    selected = false;
}

bool GWidget::isSelected() const {
    return selected;
}


