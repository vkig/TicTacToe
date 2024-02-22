//
// Created by vkig on 2021. 04. 20..
//

#ifndef GWIDGET_GWIDGET_HPP
#define GWIDGET_GWIDGET_HPP

#include "../graphics.hpp"
#include <iostream>

class Application;

class GWidget {
protected:
    Application * parent;
    int posX, posY, width, height, borderSize;
    bool selected{}, hidden, enabled;
    genv::color main;
    genv::color borderColor;
    genv::canvas graphicRepr;
public:
    GWidget();
    GWidget(Application* _parent, int x, int y, int _width, int _height, int _borderSize = 2, genv::color _mainColor = genv::color(224, 224, 224),
            genv::color _borderColor = genv::color(255, 255, 255));
    virtual void action(genv::event& ev) = 0;
    virtual void show();
    virtual void hide();
    [[nodiscard]] bool isHidden() const;
    [[nodiscard]] virtual bool isMouseOnIt(int ex, int ey) const;
    virtual void setBorderSize(int bs);
    virtual void resize(int _width, int _height);
    virtual void changePosition(int x, int y);
    virtual void select();
    virtual void deselect();
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
    [[nodiscard]] int getPosX() const;
    [[nodiscard]] int getPosY() const;
    [[nodiscard]] bool isSelected() const;
    void setEnable(bool value);
    [[nodiscard]] bool isEnabled() const;
};


#endif //GWIDGET_GWIDGET_HPP