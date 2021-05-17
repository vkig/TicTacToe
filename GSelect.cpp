//
// Created by vkig on 2021. 04. 20..
//

#include "GSelect.hpp"
#include <stack>

GSelect::GSelect() {

}

GSelect::GSelect(Application* _parent, int x, int y, int _width, int _height, int _bordersize, int _scrollHeight,
                 std::vector<std::string> _items, genv::color _main, genv::color _borderc) : GWidget(_parent, x, y, _width, _height,
                _bordersize,_main, _borderc){
    items = _items;
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
    int a =  height-2*bordersize;
    buttondown = GButton(_parent, posx+width-bordersize-a, posy+bordersize, a, a, 1, genv::color(224, 224, 224),
                         genv::color(0, 0, 0), nullptr,GButton::DOWN, genv::color(0, 0, 0));
    int sh = std::max(15, scrollHeight/std::max(1,int(items.size()+3-itemsOnScroll)) - bordersize);
    slider = GButton(_parent, posx+width-bordersize-a,posy+height,a,sh,0,genv::color(0, 170, 255),genv::color(0, 0, 0),
                     nullptr,GButton::LABELED);

    //resize if it is needed
    if(width < graphicRepr.twidth("-- Válasszon a listából --")+a+2*bordersize)
    {
        width = graphicRepr.twidth("-- Válasszon a listából --")+a+2*bordersize;
        resize(width, height);
    }
}

void GSelect::show() {
    // simple state
    graphicRepr << genv::move_to(bordersize, bordersize)<<main<<genv::box_to(width - buttondown.getWidth() - bordersize - 1, basicHeight - bordersize - 1);
    GWidget::show();
    if(selectedItem != -1)
    {
        graphicRepr<<genv::move_to(bordersize+graphicRepr.twidth("-"), basicHeight/2-(graphicRepr.cascent()+graphicRepr.cdescent())/2)
                   <<genv::color(0, 0, 0)<<genv::text(items[selectedItem]);
    }
    else{
        graphicRepr<<genv::move_to(bordersize+graphicRepr.twidth("-"), basicHeight/2-(graphicRepr.cascent()+graphicRepr.cdescent())/2)
        <<genv::color(0, 0, 0)<<genv::text("- Válasszon a listából -");
    }
    genv::gout<<genv::stamp(graphicRepr, posx, posy);
    buttondown.show();
    // expanded state
    if(expanded){
        showScroll();
        slider.show();
    }
    else{
        genv::gout<<genv::move_to(posx, posy+basicHeight)<<genv::color(0, 0, 0 )<<genv::box(width, scrollHeight);
    }
}

void GSelect::action(genv::event &ev) {
    if(ev.type == genv::ev_mouse){
        // ha az egér a widget felett van
        if(isMouseOnIt(ev.pos_x, ev.pos_y))
        {
            if(ev.button == genv::btn_left)
            {
                if (buttondown.isMouseOnIt(ev.pos_x, ev.pos_y) || (!expanded && !buttondown.isMouseOnIt(ev.pos_x, ev.pos_y)))
                {
                    if(buttondown.isMouseOnIt(ev.pos_x, ev.pos_y))
                        buttondown.action(ev);
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
            slider.changePosition(slider.getPosX(), std::min(posy+height-bordersize-slider.getHeight(),std::max(posy + basicHeight,ev.pos_y-dy)));
            showScroll();
            show();
        }
        if(ev.button == -genv::btn_left)
        {
            if (isSelected())
            {
                buttondown.action(ev);
            }
            if(sliderDragged)
            {
                dropSlider();
            }
            if(buttondown.isSelected())
            {
                buttondown.deselect();
                buttondown.show();
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
    int a = (_height-2*bordersize);
    buttondown.resize(a,a);
    buttondown.changePosition(posx+_width-bordersize-a, posy+bordersize);
    int sh = std::max(15, scrollHeight/std::max(1,int(items.size()+3-itemsOnScroll)) - bordersize);
    slider.changePosition(posx+width-bordersize-a,posy+height);
    slider.resize(a,sh);
}

void GSelect::changePosition(int x, int y) {
    posx = x;
    posy = y;
    int a = (basicHeight-2*bordersize);
    buttondown.changePosition(x+width-bordersize-a, y+bordersize);
    slider.changePosition(posx+width-bordersize-a,posy+basicHeight);
}

void GSelect::addItem(std::string item) {
    items.push_back(item);
    int a = (basicHeight-2*bordersize);
    int sh = std::max(15, scrollHeight/std::max(1,int(items.size()+3-itemsOnScroll)) - bordersize);
    slider.resize(a,sh);
    slider.changePosition(slider.getPosX(),std::min(posy+basicHeight+scrollHeight-bordersize-slider.getHeight(),slider.getPosY() + scrollHeight / std::max(1,int(items.size()))));
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
    int a = (basicHeight-2*bordersize);
    int sh = std::max(15, scrollHeight/std::max(1,int(items.size()+3-itemsOnScroll)) - bordersize);
    slider.resize(a,sh);
    slider.changePosition(slider.getPosX(),std::min(posy+basicHeight+scrollHeight-bordersize-slider.getHeight(),slider.getPosY() + scrollHeight / std::max(1,int(items.size()))));
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
        topItem = ((slider.getPosY() - (posy + basicHeight)) * (int(items.size()) - itemsOnScroll + 3)) / (scrollHeight - slider.getHeight());
    } else {
        topItem = 0;
    }
    int toidx = topItem + itemsOnScroll;
    if(topItem + itemsOnScroll >= items.size())
    {
        toidx = items.size();
    }
    itemsGraphRepr << genv::move_to(0, 0) << borderc << genv::box_to(width-1, scrollHeight-1) << genv::move_to(bordersize, 0)<<
    main<<genv::box_to(width-1-bordersize, scrollHeight-1-bordersize);
    if(selectedItem != -1 && selectedItem >= topItem && selectedItem < toidx)
    {
        itemsGraphRepr << genv::move_to(bordersize, itemHeight*(selectedItem - topItem)) << genv::color(40, 170, 240) <<
        genv::box(width - 3*bordersize - slider.getWidth(), std::min(itemHeight, scrollHeight-itemsGraphRepr.y()-bordersize));
    }
    itemsGraphRepr << genv::move_to(bordersize+itemsGraphRepr.twidth("-"), itemHeight/2-(itemsGraphRepr.cascent()+itemsGraphRepr.cdescent())/2)<<
    genv::color(0, 0, 0);
    for(int i = topItem;i<toidx;i++){
        if(itemsGraphRepr.y() < scrollHeight) {
            int ytmp = itemsGraphRepr.y();
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
            if(ytmp == itemsGraphRepr.y()){
                break;
            }
        }
    }
    itemsGraphRepr << genv::move_to(0,scrollHeight-1)<<borderc<<genv::line_to(width- 1, scrollHeight - 1);
    genv::gout<<genv::stamp(itemsGraphRepr,posx, posy+basicHeight);
}

void GSelect::  expand() {
    if(expanded)
    {
        height = basicHeight;
        buttondown.changeType(GButton::DOWN);
    }
    else
    {
        height = height + scrollHeight;
        buttondown.changeType(GButton::UP);
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
    slider.changePosition(slider.getPosX(),std::max(posy + basicHeight,slider.getPosY() - scrollHeight / std::max(1,int(items.size()))));
    show();
}

void GSelect::scrollDown() {
    slider.changePosition(slider.getPosX(),std::min(posy+basicHeight+scrollHeight-bordersize-slider.getHeight(),slider.getPosY() + scrollHeight / std::max(1,int(items.size()))));
    show();
}

void GSelect::selectItem(int ey) {
    if(selectedItem == (ey - posy - basicHeight)/itemHeight + topItem)
    {
        selectedItem = (ey - posy - basicHeight)/itemHeight + topItem;
        expand();
    }
    else
    {
        selectedItem = (ey - posy - basicHeight)/itemHeight + topItem;
    }
    if(selectedItem >= items.size())
    {
        selectedItem = -1;
    }
    show();
}

bool GSelect::isOnScroll(int ex, int ey) {
    return (ex >= posx + bordersize && ex < posx + width - bordersize - slider.getWidth() && ey >= posy + basicHeight + bordersize && ey < posy + basicHeight + scrollHeight - bordersize);
}

void GSelect::deselect() {
    GWidget::deselect();
    if(expanded)
    {
        expand();
    }
}




