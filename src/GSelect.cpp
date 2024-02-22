//
// Created by vkig on 2021. 04. 20..
//

#include "GSelect.hpp"
#include <stack>
#include <utility>

GSelect::GSelect() = default;

GSelect::GSelect(Application* _parent, int x, int y, int _width, int _height, int _borderSize, int _scrollHeight,
                 std::vector<std::string> _items, genv::color _main, genv::color _borderColor) : GWidget(_parent, x, y, _width, _height,
                                                                                                         _borderSize, _main, _borderColor){
    items = std::move(_items);
    expanded = false;
    selectedItem = -1;
    basicHeight = _height;
    sliderDragged =false;

    //graphic representation
    graphicRepr = genv::canvas(width, height);
    graphicRepr.load_font("times.ttf", int(height*2.0/3.0));

    //scroll settings
    itemHeight = graphicRepr.cdescent()+graphicRepr.cascent();
    scrollHeight = std::min(_scrollHeight,int(itemHeight*items.size()));
    itemsOnScroll = scrollHeight / itemHeight + 2;
    itemsGraphRepr = genv::canvas(width, scrollHeight);
    itemsGraphRepr.load_font("times.ttf", int(height*2.0/3.0));

    //slider and scroll button
    int a =  height- 2 * borderSize;
    buttonDown = GButton(_parent, posX + width - borderSize - a, posY + borderSize, a, a, 1, genv::color(224, 224, 224),
                         genv::color(0, 0, 0), nullptr, GButton::DOWN, genv::color(0, 0, 0));
    int sh = std::max(15, scrollHeight/std::max(1,int(items.size()+3-itemsOnScroll)) - borderSize);
    slider = GButton(_parent, posX + width - borderSize - a, posY + height, a, sh, 0, genv::color(0, 170, 255), genv::color(0, 0, 0),
                     nullptr, GButton::LABELED);

    //resize if it is needed
    if(width < graphicRepr.twidth("-- Válasszon a listából --")+a+ 2 * borderSize)
    {
        width = graphicRepr.twidth("-- Válasszon a listából --")+a+ 2 * borderSize;
        resize(width, height);
    }
}

void GSelect::show() {
    // simple state
    graphicRepr << genv::move_to(borderSize, borderSize) << main << genv::box_to(width - buttonDown.getWidth() - borderSize - 1, basicHeight - borderSize - 1);
    GWidget::show();
    if(selectedItem != -1)
    {
        graphicRepr<<genv::move_to(borderSize + graphicRepr.twidth("-"), basicHeight / 2 - (graphicRepr.cascent() + graphicRepr.cdescent()) / 2)
                   <<genv::color(0, 0, 0)<<genv::text(items[selectedItem]);
    }
    else{
        graphicRepr<<genv::move_to(borderSize + graphicRepr.twidth("-"), basicHeight / 2 - (graphicRepr.cascent() + graphicRepr.cdescent()) / 2)
        <<genv::color(0, 0, 0)<<genv::text("- Válasszon a listából -");
    }
    genv::gout<<genv::stamp(graphicRepr, posX, posY);
    buttonDown.show();
    // expanded state
    if(expanded){
        showScroll();
        slider.show();
    }
    else{
        genv::gout << genv::move_to(posX, posY + basicHeight) << genv::color(0, 0, 0 ) << genv::box(width, scrollHeight);
    }
}

void GSelect::action(genv::event &ev) {
    if(ev.type == genv::ev_mouse){
        // ha az egér a widget felett van
        if(isMouseOnIt(ev.pos_x, ev.pos_y))
        {
            if(ev.button == genv::btn_left)
            {
                if (buttonDown.isMouseOnIt(ev.pos_x, ev.pos_y) || (!expanded && !buttonDown.isMouseOnIt(ev.pos_x, ev.pos_y)))
                {
                    if(buttonDown.isMouseOnIt(ev.pos_x, ev.pos_y))
                        buttonDown.action(ev);
                    expand();
                    show();
                }
                else if(slider.isMouseOnIt(ev.pos_x, ev.pos_y))
                {
                    dragSlider(ev.pos_x, ev.pos_y);
                }
                if(isOnScroll(ev.pos_x, ev.pos_y))
                {
                    selectItem(ev.pos_y);
                }
            }
            if(ev.button == genv::btn_wheeldown && isOnScroll(ev.pos_x, ev.pos_y))
            {
                scrollDown();
            }
            if(ev.button == genv::btn_wheelup && isOnScroll(ev.pos_x, ev.pos_y))
            {
                scrollUp();
            }
        }
        if(ev.button == 0 && sliderDragged)
        {
            slider.changePosition(slider.getPosX(), std::min(posY + height - borderSize - slider.getHeight(), std::max(posY + basicHeight, ev.pos_y - dy)));
            showScroll();
            show();
        }
        if(ev.button == -genv::btn_left)
        {
            if (isSelected())
            {
                buttonDown.action(ev);
            }
            if(sliderDragged)
            {
                dropSlider();
            }
            if(buttonDown.isSelected())
            {
                buttonDown.deselect();
                buttonDown.show();
            }
        }
    }
}

void GSelect::resize(int _width, int _height) {
    // size values
    width = _width;
    height = _height;
    basicHeight = _height;

    // graphic representations
    graphicRepr = genv::canvas(width, height);
    graphicRepr.load_font("times.ttf", int(height*2.0/3.0));
    itemsGraphRepr = genv::canvas(width, scrollHeight);
    itemsGraphRepr.load_font("times.ttf", int(height*2.0/3.0));
    itemHeight = graphicRepr.cdescent()+graphicRepr.cascent();
    itemsOnScroll = scrollHeight / itemHeight + 2;

    // scroll button and slider
    int a = (_height- 2 * borderSize);
    buttonDown.resize(a, a);
    buttonDown.changePosition(posX + _width - borderSize - a, posY + borderSize);
    int sh = std::max(15, scrollHeight/std::max(1,int(items.size()+3-itemsOnScroll)) - borderSize);
    slider.changePosition(posX + width - borderSize - a, posY + height);
    slider.resize(a,sh);
}

void GSelect::changePosition(int x, int y) {
    posX = x;
    posY = y;
    int a = (basicHeight- 2 * borderSize);
    buttonDown.changePosition(x + width - borderSize - a, y + borderSize);
    slider.changePosition(posX + width - borderSize - a, posY + basicHeight);
}

void GSelect::addItem(const std::string& item) {
    items.push_back(item);
    int a = (basicHeight- 2 * borderSize);
    int sh = std::max(15, scrollHeight/std::max(1,int(items.size()+3-itemsOnScroll)) - borderSize);
    slider.resize(a,sh);
    slider.changePosition(slider.getPosX(),std::min(posY + basicHeight + scrollHeight - borderSize - slider.getHeight(), slider.getPosY() + scrollHeight / std::max(1, int(items.size()))));
}

void GSelect::removeItem(const std::string &item) {
    std::stack<std::vector<std::string>::iterator> should_delete;
    int i=0;
    for(auto it = items.begin();it!=items.end();it++)
    {
        if(*it == item)
        {
            should_delete.push(it);
            if(i == selectedItem)
            {
                selectedItem = -1;
            }
        }
        i++;
    }
    while(!should_delete.empty()){
        items.erase(should_delete.top());
        should_delete.pop();
    }
    int a = (basicHeight- 2 * borderSize);
    int sh = std::max(15, scrollHeight/std::max(1,int(items.size()+3-itemsOnScroll)) - borderSize);
    slider.resize(a,sh);
    slider.changePosition(slider.getPosX(),std::min(posY + basicHeight + scrollHeight - borderSize - slider.getHeight(), slider.getPosY() + scrollHeight / std::max(1, int(items.size()))));
}

std::string GSelect::getSelected() const {
    if(selectedItem != -1)
    {
        return items[selectedItem];
    }
    return "";
}

void GSelect::showScroll(bool init) {
    if(scrollHeight-slider.getHeight() > 0){
        topItem = ((slider.getPosY() - (posY + basicHeight)) * (int(items.size()) - itemsOnScroll + 3)) / (scrollHeight - slider.getHeight());
    } else {
        topItem = 0;
    }
    int toIdx = topItem + itemsOnScroll;
    if(topItem + itemsOnScroll >= items.size())
    {
        toIdx = (int) items.size();
    }
    itemsGraphRepr << genv::move_to(0, 0) << borderColor << genv::box_to(width - 1, scrollHeight - 1) << genv::move_to(borderSize, 0) <<
                   main << genv::box_to(width - 1 - borderSize, scrollHeight - 1 - borderSize);
    if(selectedItem != -1 && selectedItem >= topItem && selectedItem < toIdx)
    {
        itemsGraphRepr << genv::move_to(borderSize, itemHeight * (selectedItem - topItem)) << genv::color(40, 170, 240) <<
                       genv::box(width - 3 * borderSize - slider.getWidth(), std::min(itemHeight, scrollHeight - itemsGraphRepr.y() - borderSize));
    }
    itemsGraphRepr << genv::move_to(borderSize + itemsGraphRepr.twidth("-"), itemHeight / 2 - (itemsGraphRepr.cascent() + itemsGraphRepr.cdescent()) / 2) <<
                   genv::color(0, 0, 0);
    for(int i = topItem; i < toIdx; i++){
        if(itemsGraphRepr.y() < scrollHeight) {
            int yTmp = itemsGraphRepr.y();
            if (i == selectedItem) {
                itemsGraphRepr << genv::color(255, 255, 255) << genv::text(items[i])
                               << genv::move(-itemsGraphRepr.twidth(items[i]),
                                             itemsGraphRepr.cascent() + itemsGraphRepr.cdescent())
                               << genv::color(0, 0, 0);
            } else {
                itemsGraphRepr << genv::text(items[i]);
                itemsGraphRepr << genv::move(-itemsGraphRepr.twidth(items[i]),
                                                                     itemsGraphRepr.cascent() +
                                                                     itemsGraphRepr.cdescent());
            }
            if(yTmp == itemsGraphRepr.y()){
                break;
            }
        }
    }
    itemsGraphRepr << genv::move_to(0,scrollHeight-1) << borderColor << genv::line_to(width - 1, scrollHeight - 1);
    genv::gout<<genv::stamp(itemsGraphRepr, posX, posY + basicHeight);
}

void GSelect::  expand() {
    if(expanded)
    {
        height = basicHeight;
        buttonDown.changeType(GButton::DOWN);
    }
    else
    {
        height = height + scrollHeight;
        buttonDown.changeType(GButton::UP);
    }
    expanded = !expanded;
}

void GSelect::dragSlider(int ex, int ey) {
    if(slider.isMouseOnIt(ex, ey))
    {
        sliderDragged = true;
        dx = ex - slider.getPosX();
        dy = ey - slider.getPosY();
    }
}

void GSelect::dropSlider() {
    sliderDragged = false;
}

void GSelect::scrollUp() {
    slider.changePosition(slider.getPosX(),std::max(posY + basicHeight, slider.getPosY() - scrollHeight / std::max(1, int(items.size()))));
    show();
}

void GSelect::scrollDown() {
    slider.changePosition(slider.getPosX(),std::min(posY + basicHeight + scrollHeight - borderSize - slider.getHeight(), slider.getPosY() + scrollHeight / std::max(1, int(items.size()))));
    show();
}

void GSelect::selectItem(int ey) {
    if(selectedItem == (ey - posY - basicHeight) / itemHeight + topItem)
    {
        selectedItem = (ey - posY - basicHeight) / itemHeight + topItem;
        expand();
    }
    else
    {
        selectedItem = (ey - posY - basicHeight) / itemHeight + topItem;
    }
    if(selectedItem >= items.size())
    {
        selectedItem = -1;
    }
    show();
}

bool GSelect::isOnScroll(int ex, int ey) {
    return (ex >= posX + borderSize && ex < posX + width - borderSize - slider.getWidth() && ey >= posY + basicHeight + borderSize && ey < posY + basicHeight + scrollHeight - borderSize);
}

void GSelect::deselect() {
    GWidget::deselect();
    if(expanded)
    {
        expand();
    }
}




