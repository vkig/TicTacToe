//
// Created by vkig on 2021. 04. 20..
//

#ifndef GWIDGET_GWIDGET_HPP
#define GWIDGET_GWIDGET_HPP

#include "graphics.hpp"
#include <iostream>

class Application;

class GWidget {
protected:
    Application * parent;
    int posx, posy, width, height, bordersize;
    bool selected, hidden, enabled;
    genv::color main;
    genv::color borderc;
    genv::canvas graphicRepr;
public:
    GWidget();
    GWidget(Application* _parent, int x, int y, int _width, int _height, int _bordersize = 2, genv::color _main = genv::color(224, 224, 224),
            genv::color _bordercolor = genv::color(255, 255, 255));
    virtual void action(genv::event& ev) = 0;
    virtual void show();
    virtual void hide();
    bool isHidden();
    virtual bool isMouseOnIt(int ex, int ey) const;
    virtual void setBorderSize(int bs);
    virtual void resize(int _width, int _height);
    virtual void changePosition(int x, int y);
    virtual void select();
    virtual void deselect();
    int getWidth() const;
    int getHeight() const;
    int getPosX() const;
    int getPosY() const;
    bool isSelected() const;
    void setEnable(bool value);
    bool isEnabled();
};


#endif //GWIDGET_GWIDGET_HPP