#ifndef TL_H__
#define TL_H__

#include <stddef.h>
#include <stdbool.h>

#include "trial-lang-conf.h"
#include "trial-lang/value.h"

typedef struct tl_callinfo {
  struct tl_proc *proc;
  int argc;
} tl_callinfo;

typedef struct {
  tl_value *sp;
  tl_value *stbase;
  tl_value *stend;

  tl_value sDEFINE;
  tl_value sCONS;
  tl_value sLAMBDA;
  tl_value sADD;
  tl_value sSUB;
  tl_value sMUL;
  tl_value sDIV;

  tl_callinfo *ci;
  tl_callinfo *cibase;
  tl_callinfo *ciend;

  struct tl_env *global_env;
  struct heap_page *heap;
  struct tl_object *arena[TL_ARENA_SIZE];
  int arena_idx;
} tl_state;

typedef tl_value (*tl_func_t)(tl_state *);

tl_state *tl_open();
void tl_close(tl_state *);

void *tl_alloc(tl_state *, size_t);
void *tl_realloc(tl_state *, void *, size_t);
struct tl_object *tl_obj_alloc(tl_state *, size_t, enum tl_tt);
void tl_free(tl_state *, void *);

void tl_gc_protect(tl_state *, tl_value);
int tl_gc_arena_preserve(tl_state *);
void tl_gc_arena_restore(tl_state *, int);

void tl_get_args(tl_state *, const char *, ...);
void tl_defun(tl_state *, const char *, tl_func_t);

tl_value tl_cons(tl_state *, tl_value, tl_value);
tl_value tl_car(tl_state *, tl_value);
tl_value tl_cdr(tl_state *, tl_value);

bool tl_eq_p(tl_state *, tl_value, tl_value);

tl_value tl_intern_cstr(tl_state *, const char *);

tl_value tl_parse(tl_state *, const char *);

tl_value tl_run(tl_state *, struct tl_proc *, tl_value);
struct tl_proc *tl_codegen(tl_state *, tl_value, struct tl_env *);

void tl_raise(tl_state *, const char *);
void tl_debug(tl_state *, tl_value);

#endif
