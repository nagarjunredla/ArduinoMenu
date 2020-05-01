/* -*- C++ -*- */
#pragma once

#include "path.h"

namespace Menu {

  //wrap remaining content on a `Tag role`
  template<Tag role>
  struct Wrap {
    template<typename I>
    struct Part:I {
      using This=Wrap<role>;
      using Base=I;
      using Base::print;
      template<typename Nav,typename Out,Op op=Op::Printing>
      inline void print(Nav& nav,Out& out,PathRef ref=self) {
        out.template fmt<role,true>(nav.pos(),true,Base::enabled(),nav.mode());
        Base::template print<Nav,Out,op>(nav,out,ref);
        out.template fmt<role,false>(nav.pos(),true,Base::enabled(),nav.mode());
      }
    };
  };

  template<typename... O> using WrapPanel=Wrap<Tag::Panel>;
  template<typename... O> using WrapMenu=Wrap<Tag::Menu>;
  template<typename... O> using WrapTitle=Wrap<Tag::Title>;
  template<typename... O> using WrapBody=Wrap<Tag::Body>;
  template<typename... O> using WrapItem=Wrap<Tag::Item>;
  template<typename... O> using WrapIndex=Wrap<Tag::Index>;
  template<typename... O> using WrapCursor=Wrap<Tag::Cursor>;
  template<typename... O> using WrapName=Wrap<Tag::Name>;
  template<typename... O> using WrapMode=Wrap<Tag::Mode>;
  template<typename... O> using WrapValue=Wrap<Tag::Value>;
  template<typename... O> using WrapUnit=Wrap<Tag::Unit>;
  template<typename... O> using WrapRaw=Wrap<Tag::Raw>;

  //insert a block if content to be printed as `Tag tole` format
  template<Tag role,Expr... R>
  struct As {
    template<typename I>
    struct Part:I,private Chain<R...,Empty>::template To<Obj<Item<R...>>> {
      using Base=I;
      using This=As<role,R...>;
      using RoleBlock=typename Chain<R...,Empty>::template To<Obj<Item<R...>>>;
      using Base::Base;
      using RoleBlock::RoleBlock;
      // RoleBlock blk;
      using Type=typename Base::Type;
      using Base::printMenu;
      using Base::printTitle;
      using Base::cmd;
      using Base::printItems;
      using Base::changed;
      using Base::enable;
      using Base::enabled;
      using Base::size;
      using Base::activate;
      using Base::parentPrint;
      using Base::walkPath;
      using Base::obj;
      using Base::id;
      template<typename Nav,typename Out,Op op=Op::Printing>
      inline void print(Nav& nav,Out& out) {
        out.template fmt<role,true>(nav.pos(),true,Base::enabled(),nav.mode());
        RoleBlock::template print<Nav,Out,op>(nav,out);
        out.template fmt<role,false>(nav.pos(),true,Base::enabled(),nav.mode());
        Base::template print<Nav,Out,op>(nav,out);
      }
    };
  };

  template<Expr... O> using AsPanel=As<Tag::Panel,O...>;
  template<Expr... O> using AsMenu=As<Tag::Menu,O...>;
  template<Expr... O> using AsTitle=As<Tag::Title,O...>;
  template<Expr... O> using AsBody=As<Tag::Body,O...>;
  template<Expr... O> using AsItem=As<Tag::Item,O...>;
  template<Expr... O> using AsIndex=As<Tag::Index,O...>;
  template<Expr... O> using AsCursor=As<Tag::Cursor,O...>;
  template<Expr... O> using AsName=As<Tag::Name,O...>;
  template<Expr... O> using AsMode=As<Tag::Mode,O...>;
  template<Expr... O> using AsValue=As<Tag::Value,O...>;
  template<Expr... O> using AsUnit=As<Tag::Unit,O...>;
  template<Expr... O> using AsRaw=As<Tag::Raw,O...>;

};