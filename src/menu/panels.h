/* -*- C++ -*- */
#pragma once

////////////////////////////////////////////////////
// Rui Azevedo - Apr2019
// neu-rah (ruihfazevedo@gmail.com)
// panels describe output geometry


#include "../menu.h"
#include "out.h"

namespace Menu {

  //static panel
  template<size_t x,size_t y,size_t w,size_t h,typename O=Void>
  struct StaticPanel:public O {
    static inline size_t posX() {return x;}
    static inline size_t posY() {return y;}
    static inline size_t width() {return w;}
    static inline size_t height() {return h;}
  };

  //dynamic panel, do we need this?
  // class Panel {
  //   public:
  //     inline size_t posX() const {return x;}
  //     inline size_t posY() const {return y;}
  //     inline size_t width() const {return w;}
  //     inline size_t height() const {return h;}
  //   protected:
  //   size_t x,y,w,h;
  // };

  ////////////////////////////////////////////////////
  // views describe the progressin of a panel, tracking its free spece during print
  // its nor really a clipping, we are just accounting for variable size options

  //we dont care... as in serial device, we just print
  // struct FreeView {
  //   inline FreeView() {}
  //   static inline size_t freeX() {return -1;}
  //   static inline size_t freeY() {return -1;}
  //   static inline size_t free() {return -1;}
  //   static inline size_t posX() {return 0;}
  //   static inline size_t posY() {return 0;}
  //   static inline void useX(size_t ux=1) {}
  //   static inline void useY(size_t uy=1) {}
  //   inline operator bool() const {return true;}
  //   inline operator int() const {return free();}
  //   inline void newView() {}
  // };

  //track space usage
  template<typename O>
  class Viewport:public O {
    public:
      // using O::O;
      inline Viewport() {newView();}
      inline Viewport(const Viewport<O>& o) {fx=o.width();fy=o.height()-1;}
      inline size_t freeX() const {return fx;}
      inline size_t freeY() const {return fy;}
      inline size_t free() const {return fx+width()*fy;}
      inline size_t posX() const {return (width()-fx)+O::posX();}
      inline size_t posY() const {return (height()-fy)+O::posY()-1;}
      inline void useX(size_t ux=1) {if (fx) fx-=ux; else useY();}
      inline void useY(size_t uy=1) {
        if (!fy) fx=0;
        else {
          fy-=uy;
          fx=width();
        }
      }
      inline operator bool() const {return fx||fy;}
      inline operator int() const {return free();}
      inline void newView() {fx=O::width();fy=O::height()-1;}
      inline void endl() {useY(1);}
    protected:
      size_t fx,fy;
  };

};//Menu