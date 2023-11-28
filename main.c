#include "class.h"

#define CLASS_BEGIN_C1 \
    constructor(\
        self->id=self->sid="C1";\
        self->print=_C1Print;\
        printf("init C1\n");\
    ),\
    destructor(\
        printf("fini C1\n");\
    ),\
    public(\
        const char *id;\
        void(*print)(struct C1 *self);\
    ),\
    private(\
        const char *sid;\
    )
CLASS_END(C1);

#define CLASS_BEGIN_C2 \
    inherit(C1),\
    constructor(\
        self->id=self->sid="C2";\
        self->print=_C2Print;\
        printf("init C2\n");\
    ),\
    destructor(\
        printf("fini C2\n");\
    ),\
    public(\
        void(*_)(C2 *self);\
        const char *sid;\
        void(*f)(C2 *self);\
    )

CLASS_END(C2);


void _C1Print(C1 *self){
    printf("C1_id:%s (%s)\n",self->id,self->sid);
}

void _C2Print(C2 *self){
    printf("C2_id:%s (%s)\n",self->id,self->sid);
}


int  main(int argc,char *argv[]){
    C2 c2=CLASS(C2);
    c2.print(&c2);
    c2.destructor(&c2);
    return 0;
}