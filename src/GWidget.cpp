//
// Created by vkig on 2021. 04. 20..
//

#include "GWidget.hpp"
#include <algorithm>

GWidget::GWidget() : main(genv::color(224, 224, 224)), borderColor(genv::color(255, 255, 255)) {
    parent = nullptr;
    hidden = false;
    enabled = true;
    posX = 0;
    posY = 0;
    width = 10;
    height = 10;
    borderSize = 2;
    graphicRepr = genv::canvas(width, height);
    graphicRepr.load_font("assets/times.ttf", std::min(int(height*2.0/3.0), 32));
}

GWidget::GWidget(Application* _parent, int x, int y, int _width, int _height, int _borderSize, genv::color _mainColor, genv::color _borderColor)
                : main(_mainColor), borderColor(_borderColor){
    parent = _parent;
    hidden = false;
    enabled = true;
    posX = x;
    posY = y;
    width = _width;
    height = _height;
    borderSize = _borderSize;
    selected = false;
    graphicRepr = genv::canvas(width, height);
    graphicRepr.load_font("assets/times.ttf", std::min(int(height*2.0/3.0), 32));
}

bool GWidget::isMouseOnIt(int ex, int ey) const {
    return (ex >= posX && ex < posX + width && ey >= posY && ey < posY + height) && !hidden && enabled;
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
        graphicRepr << borderColor << genv::move_to(0, 0) << genv::box_to(width - 1, height - 1);
    }
    graphicRepr << main << genv::move_to(borderSize, borderSize)
                   << genv::box_to(width - borderSize - 1, height - borderSize - 1);
    genv::gout<<genv::stamp(graphicRepr, posX, posY);
}

void GWidget::hide() {
    hidden=true;
    genv::gout << genv::move_to(posX, posY) << genv::color(0, 0, 0) << genv::box_to(posX + width - 1, posY + height - 1);
}

bool GWidget::isHidden() const {
    return hidden;
}

void GWidget::setBorderSize(int bs) {
    borderSize = bs;
}

void GWidget::changePosition(int x, int y) {
    posX = x;
    posY = y;
}

int GWidget::getWidth() const{
    return width;
}

int GWidget::getHeight() const {
    return height;
}

int GWidget::getPosX() const {
    return posX;
}

int GWidget::getPosY() const {
    return posY;
}

void GWidget::select() {
    if(enabled)
        selected = true;
}

void GWidget::deselect() {
    selected = false;
}

bool GWidget::isSelected() const {
    return selected;
}

void GWidget::setEnable(bool value) {
    enabled = value;
}

bool GWidget::isEnabled() const {
    return enabled;
}


