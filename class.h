#ifndef CLASS_H
#define CLASS_H

#include "macro.h"

#define CLASS_END(_name_) \
    typedef struct _name_ _name_;\
    struct _name_{void(*destructor)(void*); _CLASS_LOOP(_CLASS_END(_name_))};\
    static void M_JOIN(_wrng_,_name_)();\
    static void M_JOIN(_dtor_,_name_)(void *p){_CLASS_LOOP(_CLASS_DESTRUCT(_name_,p)) return; (void)M_JOIN(_wrng_,_name_);}\
    static void M_JOIN(_wrng_,_name_)(){(void)M_JOIN(_dtor_,_name_);}\
    _name_  M_JOIN(_cbs_,_name_)

#define CLASS(_type_) (*({\
    if(!M_JOIN(_cbs_,_type_).destructor){\
        _CLASS_LOOP(_CLASS_CONSTRUCT(_type_,(void*)&M_JOIN(_cbs_,_type_)))\
        M_JOIN(_cbs_,_type_).destructor=M_JOIN(_dtor_,_type_); \
    }(const _type_*)&M_JOIN(_cbs_,_type_);\
}))

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _CLASS_INH_inherit(...) __VA_ARGS__
#define _CLASS_INH_public(...)
#define _CLASS_INH_private(...)
#define _CLASS_INH_constructor(...)
#define _CLASS_INH_destructor(...)

#define _CLASS_PBL_inherit(...)
#define _CLASS_PBL_public(...) __VA_ARGS__
#define _CLASS_PBL_private(...)
#define _CLASS_PBL_constructor(...)
#define _CLASS_PBL_destructor(...)

#define _CLASS_PRV_inherit(...)
#define _CLASS_PRV_public(...)
#define _CLASS_PRV_private(...) __VA_ARGS__
#define _CLASS_PRV_constructor(...)
#define _CLASS_PRV_destructor(...)

#define _CLASS_CTR_inherit(...)
#define _CLASS_CTR_public(...)
#define _CLASS_CTR_private(...)
#define _CLASS_CTR_constructor(...) __VA_ARGS__
#define _CLASS_CTR_destructor(...)

#define _CLASS_DTR_inherit(...)
#define _CLASS_DTR_public(...)
#define _CLASS_DTR_private(...)
#define _CLASS_DTR_constructor(...)
#define _CLASS_DTR_destructor(...) __VA_ARGS__

#define _CLASS_INH(...) _CLASS_INH_##__VA_ARGS__
#define _CLASS_PBL(...) _CLASS_PBL_##__VA_ARGS__
#define _CLASS_PRV(...) _CLASS_PRV_##__VA_ARGS__
#define _CLASS_CTR(...) _CLASS_CTR_##__VA_ARGS__
#define _CLASS_DTR(...) _CLASS_DTR_##__VA_ARGS__
#define _CLASS_PRV0(...)
#define _CLASS_PRV1(_p_,...) struct{__VA_ARGS__}_pad##_p_[1][1][1];

#define _CLASS_LOOP(...)  _CLASS_LOOP0(_CLASS_LOOP0(_CLASS_LOOP0(__VA_ARGS__)))
#define _CLASS_LOOP0(...) _CLASS_LOOP1(_CLASS_LOOP1(_CLASS_LOOP1(__VA_ARGS__)))
#define _CLASS_LOOP1(...) _CLASS_LOOP2(_CLASS_LOOP2(_CLASS_LOOP2(__VA_ARGS__)))
#define _CLASS_LOOP2(...) _CLASS_LOOP3(_CLASS_LOOP3(_CLASS_LOOP3(__VA_ARGS__)))
#define _CLASS_LOOP3(...) __VA_ARGS__

#define _CLASS_DECL CLASS_BEGIN_
#define _CLASS_BASE(_name_) M_FOREACH(_CLASS_INH,M_JOIN(_CLASS_DECL,_name_))

#define _CLASS_END(_name_,...)\
    M_WHEN(_CLASS_BASE(_name_))( M_OBSTRUCT(__CLASS_END)()(_CLASS_BASE(_name_),_CLASS_BASE(_name_)) ) \
    M_FOREACH(_CLASS_PBL,M_JOIN(_CLASS_DECL,_name_))\
    M_IF(M_IS_ARG(__VA_ARGS__))(\
        M_OVERLOAD_AE(_CLASS_PRV,M_FOREACH(_CLASS_PRV,M_JOIN(_CLASS_DECL,_name_)))(__VA_ARGS__,M_FOREACH(_CLASS_PRV,M_JOIN(_CLASS_DECL,_name_))) , \
        M_FOREACH(_CLASS_PRV,M_JOIN(_CLASS_DECL,_name_))\
    )

#define _CLASS_CONSTRUCT(_type_,_var_) \
    M_WHEN(_CLASS_BASE(_type_))( M_OBSTRUCT(__CLASS_CONSTRUCT)()(_CLASS_BASE(_type_),(_var_)) )\
    {_type_ *self=(_var_); M_FOREACH(_CLASS_CTR,M_JOIN(_CLASS_DECL,_type_)) if(0)(void)self;}

#define _CLASS_DESTRUCT(_type_,_var_) \
    {_type_ *self=(_var_); M_FOREACH(_CLASS_DTR,M_JOIN(_CLASS_DECL,_type_)) if(0)(void)self;}\
    M_WHEN(_CLASS_BASE(_type_))( M_OBSTRUCT(__CLASS_DESTRUCT)()(_CLASS_BASE(_type_),(_var_)) )

#define __CLASS_END() _CLASS_END
#define __CLASS_DESTRUCT() _CLASS_DESTRUCT
#define __CLASS_CONSTRUCT() _CLASS_CONSTRUCT

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // CLASS_H