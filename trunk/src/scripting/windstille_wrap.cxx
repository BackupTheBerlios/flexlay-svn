/* -*- buffer-read-only: t -*- vi: set ro: */
/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.17u-20021128-1508
 * 
 * This file is not intended to be easily readable and contains a number of 
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG 
 * interface file instead. 
 * ----------------------------------------------------------------------------- */

/* Implementation : GUILE */

extern "C" {

extern void
SWIG_init (void)
;

}

#ifdef __cplusplus
template<class T> class SwigValueWrapper {
    T *tt;
public:
    inline SwigValueWrapper() : tt(0) { }
    inline ~SwigValueWrapper() { if (tt) delete tt; } 
    inline SwigValueWrapper& operator=(const T& t) { tt = new T(t); return *this; }
    inline operator T&() const { return *tt; }
    inline T *operator&() { return tt; }
};                                                    
#endif

/* -*- c -*-
 * -----------------------------------------------------------------------
 * swig_lib/guile/guiledec.swg
 * Copyright (C) 2000 Matthias Koeppe
 *
 * Guile configuration file -- declarations
 * ----------------------------------------------------------------------- */

#define SWIGGUILE
#include "guile/gh.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(SWIG_NOINCLUDE)
#	define SWIGSTATIC
#elif defined(SWIG_GLOBAL)
#	define SWIGSTATIC
#else
#	define SWIGSTATIC static
#endif

#define GH_NOT_PASSED    SCM_UNDEFINED
#define GH_UNSPECIFIED   SCM_UNSPECIFIED

#define SWIG_APPEND_VALUE(object)						\
    if (gswig_result == GH_UNSPECIFIED)						\
        gswig_result = object;							\
    else {									\
        if (!gswig_list_p) {							\
	    gswig_list_p = 1;							\
	    gswig_result = gh_list(gswig_result, object, GH_NOT_PASSED);	\
        }									\
        else									\
            gswig_result = gh_append2(gswig_result,				\
                                      gh_list(object, GH_NOT_PASSED));		\
    }

#define GUILE_APPEND_RESULT SWIG_APPEND_VALUE
  
/* scm_values was implemented on C level in 1.4.1, and the prototype
   is not included in libguile.h, so play safe and lookup `values'... */
#define GUILE_MAYBE_VALUES						\
    if (gswig_list_p)							\
        gswig_result = gh_apply(gh_lookup("values"), gswig_result);
    
#define GUILE_MAYBE_VECTOR				\
    if (gswig_list_p)					\
        gswig_result = gh_list_to_vector(gswig_result);

static char *
SWIG_scm2str (SCM s)
{
  return gh_scm2newstr (s, NULL);
}

#define GSWIG_scm2str SWIG_scm2str

/* SCM_CHAR and SCM_CHARP were introduced in Guile 1.4; the following is for
   1.3.4 compatibility. */
#ifndef SCM_CHAR
#  define SCM_CHAR SCM_ICHR
#endif
#ifndef SCM_CHARP
#  define SCM_CHARP SCM_ICHRP
#endif

/* This function replaces gh_scm2char, which is broken in Guile 1.4 */
static char
GSWIG_scm2char (SCM s)
{
  if (SCM_CHARP(s)) return SCM_CHAR(s);
  scm_wrong_type_arg(NULL, 0, s);
}
#define gh_scm2char GSWIG_scm2char

/* More 1.3.4 compatibility */
#ifndef SCM_INPUT_PORT_P
#  define SCM_INPUT_PORT_P SCM_INPORTP
#  define SCM_OUTPUT_PORT_P SCM_OUTPORTP
#endif

/* Type system */

typedef void *(*swig_converter_func)(void *);
typedef struct swig_type_info *(*swig_dycast_func)(void **);

typedef struct SwigPtrType SwigPtrType;

typedef struct swig_type_info {
  const char  *name;
  swig_converter_func converter;
  const char  *str;
  void        *clientdata;
  size_t tag;
  swig_dycast_func        dcast;
} swig_type_info;

SWIGSTATIC void
SWIG_Guile_RegisterTypes (swig_type_info **table,
			  swig_type_info **init);

/* Register a new type-mapping with the type-checker.  origtype is the
   original datatype and newtype is an equivalent type.  cast is optional
   pointer to a function to cast pointer values between types (this is
   typically used to cast pointers from derived classes to base classes in
   C++).  */

SWIGSTATIC void
SWIG_RegisterMapping (const char *origtype, const char *newtype,
                      swig_converter_func cast);


/* Dynamic pointer casting. Down an inheritance hierarchy */
SWIGSTATIC swig_type_info * 
SWIG_TypeDynamicCast(swig_type_info *ty, void **ptr);

/* Register SWIG smobs with Guile.  */
SWIGSTATIC void
SWIG_Guile_Init();

/* Initialization function for this SWIG module; actually renamed by a
   #define */
/* extern void SWIG_init(); */

/* Get a pointer value from a smob.  If there is a type-mismatch,
   return nonzero; on success, return 0.  */
SWIGSTATIC int
SWIG_Guile_GetPtr (SCM s, void **result, swig_type_info *type);

/* Get a pointer value from a smob.  If there is a type-mismatch,
   signal a wrong-type-arg error for the given argument number. */
SWIGSTATIC void *
SWIG_Guile_MustGetPtr (SCM s, swig_type_info *type,
		       int argnum, const char *func_name);

/* Make a smob from a pointer and typeinfo.  */
SWIGSTATIC SCM
SWIG_Guile_MakePtr (void *ptr, swig_type_info *type);

/* Get arguments from an argument list */
SWIGSTATIC int
SWIG_Guile_GetArgs (SCM *dest, SCM rest,
		    int reqargs, int optargs,
		    const char *procname);

typedef SCM (*swig_guile_proc)();

#ifdef __cplusplus
}
#endif

/* guiledec.swg ends here */

/* -*- c -*-
 * -----------------------------------------------------------------------
 * swig_lib/guile/guile.swg
 *
 * Guile configuration file.
 * ----------------------------------------------------------------------- */

/* SWIG pointer structure */

#ifdef __cplusplus
extern "C" {
#endif

struct SwigCast {
  unsigned short      type;		  /* Index into SwigPtrTbl          */
  void               *(*cast)(void *);    /* Pointer casting function       */
  struct SwigCast    *next;		  /* Linked list pointer            */
};

struct SwigPtrType {
  const char         *name;               /* Datatype name                  */
  const char	     *prettyname;         /* Pretty datatype name           */
  unsigned short      tag;		  /* Index in SwigPtrTable          */
  struct SwigCast    *cast;		  /* List of compatible types       */
};

/* Some variables  */

static int SwigPtrMax  = 64;            /* Max entries that can be held */
                                        /* (may be adjusted dynamically) */
static int SwigPtrN    = 0;             /* Current number of entries */
static int SwigPtrSort = 0;             /* Status flag indicating sort */

/* Pointer table */
static SwigPtrType *SwigPtrList = 0;    /* Table containing types and
					   equivalences; items will only
                                           be appended */
static size_t *SwigPtrTbl = 0;          /* Sorted indirect table; items will
					   be inserted */

/* Sort comparison function */
static int
swigsort (const void *data1, const void *data2)
{
  size_t index1 = * (size_t *) data1;
  size_t index2 = * (size_t *) data2;
  return strcmp(SwigPtrList[index1].name, SwigPtrList[index2].name);
}

/* Register a new datatype with the type-checker */
SWIGSTATIC size_t
SWIG_RegisterType (const char *type, const char *prettyname)
{
  int i;

  /* Allocate the pointer table if necessary */
  if (!SwigPtrList) {
    SwigPtrList = (SwigPtrType *) malloc(SwigPtrMax*sizeof(SwigPtrType));
    SwigPtrTbl = (size_t *) malloc(SwigPtrMax*sizeof(size_t));
    SwigPtrN = 0;
  }
  /* Grow the table if necessary */
  if (SwigPtrN >= SwigPtrMax) {
    SwigPtrMax = 2*SwigPtrMax;
    SwigPtrList = (SwigPtrType *) realloc((char *) SwigPtrList,
					  SwigPtrMax*sizeof(SwigPtrType));
    SwigPtrTbl = (size_t *) realloc((char *) SwigPtrTbl,
				    SwigPtrMax*sizeof(size_t));
  }
  /* Look up type */
  for (i = 0; i < SwigPtrN; i++)
    if (strcmp(SwigPtrList[i].name,type) == 0) {
      if (prettyname!=NULL)
	SwigPtrList[i].prettyname = prettyname;
      return i;
    }
  {
    struct SwigPtrType *t;
    size_t tag;
#if 0
    fprintf(stderr, "New type: %s\n", type);
#endif
    tag = SwigPtrTbl[SwigPtrN] = SwigPtrN;
    t = &SwigPtrList[tag];
    t->name = type;
    t->prettyname = prettyname;
    t->tag = SwigPtrN;
    t->cast = NULL;
    SwigPtrN++;
    SwigPtrSort = 0; 
    return tag;
  }
}

/* Register two data types and their mapping with the type checker. */
SWIGSTATIC void
SWIG_RegisterMapping (const char *origtype, const char *newtype,
		      swig_converter_func cast)
{
  size_t t = SWIG_RegisterType(origtype, NULL);

  if (newtype!=NULL) {
    size_t t1 = SWIG_RegisterType(newtype, NULL);
    struct SwigCast *c;
    /* Check for existing cast */
    for (c = SwigPtrList[t].cast; c && c->type!=t1; c=c->next) /* nothing */;
    if (c) {
      if (cast) c->cast = cast;
    }
    else {
      c = (struct SwigCast *) malloc(sizeof(struct SwigCast));
      c->type = t1;
      c->cast = cast;
      c->next = SwigPtrList[t].cast;
      SwigPtrList[t].cast = c;
    }
  }
}

/* Sort table */

static void
SWIG_SortTable (void)
{
  qsort ((void *) SwigPtrTbl, SwigPtrN, sizeof(size_t), swigsort);
  /* Indicate that everything is sorted */
  SwigPtrSort = 1;
}

/* Look up pointer-type entry in table */

static int
swigcmp (const void *key, const void *data)
{
  char *k = (char *) key;
  size_t index = *(size_t *)data;
  return strcmp(k, SwigPtrList[index].name);
}

static SwigPtrType *
SWIG_GetPtrType (const char *_t)
{
  size_t *result;
  if (!SwigPtrSort) SWIG_SortTable();
  result = (size_t *) bsearch(_t, SwigPtrTbl, SwigPtrN, sizeof(size_t), swigcmp);
  if (result!=NULL) return SwigPtrList+*result;
  else return NULL;
}

/* Cast a pointer if possible; returns 1 if successful */

static int
SWIG_Cast (void *source, size_t source_type,
	   void **ptr, size_t dest_type)
{
  if (dest_type != source_type) {
    /* We have a type mismatch.  Will have to look through our type
       mapping table to figure out whether or not we can accept this
       datatype.  */
    struct SwigCast *c;
    for (c = SwigPtrList[dest_type].cast;
	 c && c->type!=source_type; c = c->next) /* nothing */;
    if (c) {
      /* Get pointer value. */
      if (c->cast) *ptr = (*(c->cast))(source);
      else *ptr = source;
      return 1;
    }
    /* Didn't find any sort of match for this data.
       Get the pointer value and return false.  */
    *ptr = source;
    return 0;
  } else {
    /* Found a match on the first try.  Return pointer value.  */
    *ptr = source;
    return 1;
  }
}

/* Dynamic pointer casting. Down an inheritance hierarchy */
SWIGSTATIC swig_type_info * 
SWIG_TypeDynamicCast(swig_type_info *ty, void **ptr) 
{
  swig_type_info *lastty = ty;
  if (!ty || !ty->dcast) return ty;
  while (ty && (ty->dcast)) {
     ty = (*ty->dcast)(ptr);
     if (ty) lastty = ty;
  }
  return lastty;
}

/* Function for getting a pointer value */

static unsigned long swig_tag = 0;

SWIGSTATIC SCM
SWIG_Guile_MakePtr (void *ptr, swig_type_info *type)
{
  if (ptr==NULL) return SCM_EOL;
  SCM_RETURN_NEWSMOB((((unsigned long)type->tag << 16) | swig_tag),
		     ptr);
}

/* Return 0 if successful. */
SWIGSTATIC int
SWIG_Guile_GetPtr(SCM s, void **result, swig_type_info *type)
{
  if (SCM_NULLP(s)) {
    *result = NULL;
    return 0;
  }
  else if (SCM_NIMP(s)
	   && (unsigned long) SCM_TYP16(s) == swig_tag) {
    if (type) 
      return !SWIG_Cast((void *) SCM_CDR(s),
			(long) SCM_CAR(s) >> 16,
			result, type->tag);
    else {
      *result = (void *) SCM_CDR(s);
      return 0;
    }
  }
  return 1;
}

SWIGSTATIC void *
SWIG_Guile_MustGetPtr (SCM s, swig_type_info *type,
		       int argnum, const char *func_name)
{
  void *result;
  if (SWIG_Guile_GetPtr(s, &result, type)) {
    /* type mismatch */
    scm_wrong_type_arg((char *) func_name, argnum, s);
  }
  return result;
}

/* Init */

static int
print_swig (SCM swig_smob, SCM port, scm_print_state *pstate)
{
  scm_puts((char *) "#<swig ", port);
  if (SwigPtrList[(long) SCM_CAR(swig_smob) >> 16].prettyname != NULL)
    scm_puts((char*) SwigPtrList[(long) SCM_CAR(swig_smob) >> 16].prettyname, port);
  else scm_puts((char*) SwigPtrList[(long) SCM_CAR(swig_smob) >> 16].name, port);
  scm_puts((char *) " ", port);
  scm_intprint((long) SCM_CDR(swig_smob), 16, port);
  scm_puts((char *) ">", port);
  /* non-zero means success */
  return 1;
}

static SCM
equalp_swig (SCM A, SCM B)
{
  if (SCM_CAR(A) == SCM_CAR(B)
      && SCM_CDR(A) == SCM_CDR(B))
    return SCM_BOOL_T;
  else return SCM_BOOL_F;
}

SWIGSTATIC void
SWIG_Guile_Init (void)
{
  if (swig_tag == 0) {
    swig_tag = scm_make_smob_type_mfpe((char *) "swig", 0, NULL, NULL,
				       print_swig, equalp_swig);
  }
}

/* Convert datatype table */

SWIGSTATIC
void SWIG_Guile_RegisterTypes(swig_type_info **table,
			      swig_type_info **init)
{
  for (; *init; table++, init++) {
    swig_type_info *type = *table = *init;
    const char *origname = type->name;
    /* Register datatype itself and store pointer back */
    type->tag = SWIG_RegisterType(origname, type->str);
    /* Register compatible types */
    for (type++; type->name; type++)
      SWIG_RegisterMapping(origname, type->name, type->converter);
  }    
}

SWIGSTATIC int
SWIG_Guile_GetArgs (SCM *dest, SCM rest,
		    int reqargs, int optargs,
		    const char *procname)
{
  int i;
  int num_args_passed = 0;
  for (i = 0; i<reqargs; i++) {
    if (!SCM_CONSP(rest))
      scm_wrong_num_args(gh_str02scm((char *) procname));
    *dest++ = SCM_CAR(rest);
    rest = SCM_CDR(rest);
    num_args_passed++;
  }
  for (i = 0; i<optargs && SCM_CONSP(rest); i++) {
    *dest++ = SCM_CAR(rest);
    rest = SCM_CDR(rest);
    num_args_passed++;
  }
  for (; i<optargs; i++)
    *dest++ = GH_NOT_PASSED;
  if (!SCM_NULLP(rest))
    scm_wrong_num_args(gh_str02scm((char *) procname));
  return num_args_passed;
}

#ifdef __cplusplus
}
#endif

/* guile.swg ends here */


/* -------- TYPES TABLE (BEGIN) -------- */

#define  SWIGTYPE_p_CL_Component swig_types[0] 
static swig_type_info *swig_types[2];

/* -------- TYPES TABLE (END) -------- */


#include "editor.hxx"
#include "game.hxx"

static SCM
_wrap_push_component (SCM s_0)
{
    #define FUNC_NAME "push-component"
    CL_Component *arg1 = (CL_Component *) 0 ;
    CL_Component *result;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    {
        if (SWIG_Guile_GetPtr(s_0, (void **) &arg1, SWIGTYPE_p_CL_Component))
        scm_wrong_type_arg(FUNC_NAME, 1, s_0);
    }
    gh_defer_ints();
    result = (CL_Component *)push_component(arg1);
    
    gh_allow_ints();
    {
        gswig_result = SWIG_Guile_MakePtr (result, SWIGTYPE_p_CL_Component);
    }
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_pop_component ()
{
    #define FUNC_NAME "pop-component"
    SCM gswig_result;
    int gswig_list_p = 0;
    
    gh_defer_ints();
    pop_component();
    
    gh_allow_ints();
    gswig_result = GH_UNSPECIFIED;
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_tile_selector_create (SCM s_0, SCM s_1, SCM s_2, SCM s_3)
{
    #define FUNC_NAME "tile-selector-create"
    int arg1 ;
    int arg2 ;
    int arg3 ;
    int arg4 ;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    {
        arg1 = gh_scm2int(s_0);
    }
    {
        arg2 = gh_scm2int(s_1);
    }
    {
        arg3 = gh_scm2int(s_2);
    }
    {
        arg4 = gh_scm2int(s_3);
    }
    gh_defer_ints();
    tile_selector_create(arg1,arg2,arg3,arg4);
    
    gh_allow_ints();
    gswig_result = GH_UNSPECIFIED;
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_editor_set_brush_tile (SCM s_0)
{
    #define FUNC_NAME "editor-set-brush-tile"
    int arg1 ;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    {
        arg1 = gh_scm2int(s_0);
    }
    gh_defer_ints();
    editor_set_brush_tile(arg1);
    
    gh_allow_ints();
    gswig_result = GH_UNSPECIFIED;
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_editor_get_brush_tile ()
{
    #define FUNC_NAME "editor-get-brush-tile"
    int result;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    gh_defer_ints();
    result = (int)editor_get_brush_tile();
    
    gh_allow_ints();
    {
        gswig_result = gh_int2scm(result);
    }
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_editor_set_tool (SCM s_0)
{
    #define FUNC_NAME "editor-set-tool"
    SCM arg1 ;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    arg1=s_0;
    gh_defer_ints();
    editor_set_tool(arg1);
    
    gh_allow_ints();
    gswig_result = GH_UNSPECIFIED;
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_tilemap_set_active_layer (SCM s_0)
{
    #define FUNC_NAME "tilemap-set-active-layer"
    int arg1 ;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    {
        arg1 = gh_scm2int(s_0);
    }
    gh_defer_ints();
    tilemap_set_active_layer(arg1);
    
    gh_allow_ints();
    gswig_result = GH_UNSPECIFIED;
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_editor_add_window (SCM s_0, SCM s_1, SCM s_2, SCM s_3, SCM s_4)
{
    #define FUNC_NAME "editor-add-window"
    int arg1 ;
    int arg2 ;
    int arg3 ;
    int arg4 ;
    char *arg5 ;
    CL_Component *result;
    int must_free5 = 0 ;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    {
        arg1 = gh_scm2int(s_0);
    }
    {
        arg2 = gh_scm2int(s_1);
    }
    {
        arg3 = gh_scm2int(s_2);
    }
    {
        arg4 = gh_scm2int(s_3);
    }
    {
        arg5 = SWIG_scm2str(s_4);
        must_free5 = 1;
    }
    gh_defer_ints();
    result = (CL_Component *)editor_add_window(arg1,arg2,arg3,arg4,(char const *)arg5);
    
    gh_allow_ints();
    {
        gswig_result = SWIG_Guile_MakePtr (result, SWIGTYPE_p_CL_Component);
    }
    if (must_free5 && arg5) scm_must_free(arg5);
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_editor_add_button_func (SCM s_0, SCM s_1, SCM s_2, SCM s_3, SCM s_4, SCM s_5)
{
    #define FUNC_NAME "editor-add-button-func"
    int arg1 ;
    int arg2 ;
    int arg3 ;
    int arg4 ;
    char *arg5 ;
    SCM arg6 ;
    CL_Component *result;
    int must_free5 = 0 ;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    {
        arg1 = gh_scm2int(s_0);
    }
    {
        arg2 = gh_scm2int(s_1);
    }
    {
        arg3 = gh_scm2int(s_2);
    }
    {
        arg4 = gh_scm2int(s_3);
    }
    {
        arg5 = SWIG_scm2str(s_4);
        must_free5 = 1;
    }
    arg6=s_5;
    gh_defer_ints();
    result = (CL_Component *)editor_add_button_func(arg1,arg2,arg3,arg4,(char const *)arg5,arg6);
    
    gh_allow_ints();
    {
        gswig_result = SWIG_Guile_MakePtr (result, SWIGTYPE_p_CL_Component);
    }
    if (must_free5 && arg5) scm_must_free(arg5);
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_editor_add_button (SCM s_0, SCM s_1, SCM s_2, SCM s_3, SCM s_4)
{
    #define FUNC_NAME "editor-add-button"
    int arg1 ;
    int arg2 ;
    int arg3 ;
    int arg4 ;
    char *arg5 ;
    CL_Component *result;
    int must_free5 = 0 ;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    {
        arg1 = gh_scm2int(s_0);
    }
    {
        arg2 = gh_scm2int(s_1);
    }
    {
        arg3 = gh_scm2int(s_2);
    }
    {
        arg4 = gh_scm2int(s_3);
    }
    {
        arg5 = SWIG_scm2str(s_4);
        must_free5 = 1;
    }
    gh_defer_ints();
    result = (CL_Component *)editor_add_button(arg1,arg2,arg3,arg4,(char const *)arg5);
    
    gh_allow_ints();
    {
        gswig_result = SWIG_Guile_MakePtr (result, SWIGTYPE_p_CL_Component);
    }
    if (must_free5 && arg5) scm_must_free(arg5);
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_editor_add_label (SCM s_0, SCM s_1, SCM s_2)
{
    #define FUNC_NAME "editor-add-label"
    int arg1 ;
    int arg2 ;
    char *arg3 ;
    CL_Component *result;
    int must_free3 = 0 ;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    {
        arg1 = gh_scm2int(s_0);
    }
    {
        arg2 = gh_scm2int(s_1);
    }
    {
        arg3 = SWIG_scm2str(s_2);
        must_free3 = 1;
    }
    gh_defer_ints();
    result = (CL_Component *)editor_add_label(arg1,arg2,(char const *)arg3);
    
    gh_allow_ints();
    {
        gswig_result = SWIG_Guile_MakePtr (result, SWIGTYPE_p_CL_Component);
    }
    if (must_free3 && arg3) scm_must_free(arg3);
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_editor_add_inputbox (SCM s_0, SCM s_1, SCM s_2, SCM s_3, SCM s_4)
{
    #define FUNC_NAME "editor-add-inputbox"
    int arg1 ;
    int arg2 ;
    int arg3 ;
    int arg4 ;
    char *arg5 ;
    CL_Component *result;
    int must_free5 = 0 ;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    {
        arg1 = gh_scm2int(s_0);
    }
    {
        arg2 = gh_scm2int(s_1);
    }
    {
        arg3 = gh_scm2int(s_2);
    }
    {
        arg4 = gh_scm2int(s_3);
    }
    {
        arg5 = SWIG_scm2str(s_4);
        must_free5 = 1;
    }
    gh_defer_ints();
    result = (CL_Component *)editor_add_inputbox(arg1,arg2,arg3,arg4,(char const *)arg5);
    
    gh_allow_ints();
    {
        gswig_result = SWIG_Guile_MakePtr (result, SWIGTYPE_p_CL_Component);
    }
    if (must_free5 && arg5) scm_must_free(arg5);
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_component_on_click (SCM s_0, SCM s_1)
{
    #define FUNC_NAME "component-on-click"
    CL_Component *arg1 = (CL_Component *) 0 ;
    SCM arg2 ;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    {
        if (SWIG_Guile_GetPtr(s_0, (void **) &arg1, SWIGTYPE_p_CL_Component))
        scm_wrong_type_arg(FUNC_NAME, 1, s_0);
    }
    arg2=s_1;
    gh_defer_ints();
    component_on_click(arg1,arg2);
    
    gh_allow_ints();
    gswig_result = GH_UNSPECIFIED;
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_inputbox_get_text (SCM s_0)
{
    #define FUNC_NAME "inputbox-get-text"
    CL_Component *arg1 = (CL_Component *) 0 ;
    char *result;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    {
        if (SWIG_Guile_GetPtr(s_0, (void **) &arg1, SWIGTYPE_p_CL_Component))
        scm_wrong_type_arg(FUNC_NAME, 1, s_0);
    }
    gh_defer_ints();
    result = (char *)inputbox_get_text(arg1);
    
    gh_allow_ints();
    {
        gswig_result = gh_str02scm(result);
    }
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_window_get_client_area (SCM s_0)
{
    #define FUNC_NAME "window-get-client-area"
    CL_Component *arg1 = (CL_Component *) 0 ;
    CL_Component *result;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    {
        if (SWIG_Guile_GetPtr(s_0, (void **) &arg1, SWIGTYPE_p_CL_Component))
        scm_wrong_type_arg(FUNC_NAME, 1, s_0);
    }
    gh_defer_ints();
    result = (CL_Component *)window_get_client_area(arg1);
    
    gh_allow_ints();
    {
        gswig_result = SWIG_Guile_MakePtr (result, SWIGTYPE_p_CL_Component);
    }
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_window_close (SCM s_0)
{
    #define FUNC_NAME "window-close"
    CL_Component *arg1 = (CL_Component *) 0 ;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    {
        if (SWIG_Guile_GetPtr(s_0, (void **) &arg1, SWIGTYPE_p_CL_Component))
        scm_wrong_type_arg(FUNC_NAME, 1, s_0);
    }
    gh_defer_ints();
    window_close(arg1);
    
    gh_allow_ints();
    gswig_result = GH_UNSPECIFIED;
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_component_hide (SCM s_0)
{
    #define FUNC_NAME "component-hide"
    CL_Component *arg1 = (CL_Component *) 0 ;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    {
        if (SWIG_Guile_GetPtr(s_0, (void **) &arg1, SWIGTYPE_p_CL_Component))
        scm_wrong_type_arg(FUNC_NAME, 1, s_0);
    }
    gh_defer_ints();
    component_hide(arg1);
    
    gh_allow_ints();
    gswig_result = GH_UNSPECIFIED;
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_component_show (SCM s_0)
{
    #define FUNC_NAME "component-show"
    CL_Component *arg1 = (CL_Component *) 0 ;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    {
        if (SWIG_Guile_GetPtr(s_0, (void **) &arg1, SWIGTYPE_p_CL_Component))
        scm_wrong_type_arg(FUNC_NAME, 1, s_0);
    }
    gh_defer_ints();
    component_show(arg1);
    
    gh_allow_ints();
    gswig_result = GH_UNSPECIFIED;
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_editor_quit ()
{
    #define FUNC_NAME "editor-quit"
    SCM gswig_result;
    int gswig_list_p = 0;
    
    gh_defer_ints();
    editor_quit();
    
    gh_allow_ints();
    gswig_result = GH_UNSPECIFIED;
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_screen_get_width ()
{
    #define FUNC_NAME "screen-get-width"
    int result;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    gh_defer_ints();
    result = (int)screen_get_width();
    
    gh_allow_ints();
    {
        gswig_result = gh_int2scm(result);
    }
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_screen_get_height ()
{
    #define FUNC_NAME "screen-get-height"
    int result;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    gh_defer_ints();
    result = (int)screen_get_height();
    
    gh_allow_ints();
    {
        gswig_result = gh_int2scm(result);
    }
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_map_get_data (SCM s_0)
{
    #define FUNC_NAME "map-get-data"
    int arg1 ;
    SCM result;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    {
        arg1 = gh_scm2int(s_0);
    }
    gh_defer_ints();
    result = (SCM)map_get_data(arg1);
    
    gh_allow_ints();
    gswig_result=result;
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_map_get_width ()
{
    #define FUNC_NAME "map-get-width"
    int result;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    gh_defer_ints();
    result = (int)map_get_width();
    
    gh_allow_ints();
    {
        gswig_result = gh_int2scm(result);
    }
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_map_get_height ()
{
    #define FUNC_NAME "map-get-height"
    int result;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    gh_defer_ints();
    result = (int)map_get_height();
    
    gh_allow_ints();
    {
        gswig_result = gh_int2scm(result);
    }
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_map_set_size (SCM s_0, SCM s_1)
{
    #define FUNC_NAME "map-set-size"
    int arg1 ;
    int arg2 ;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    {
        arg1 = gh_scm2int(s_0);
    }
    {
        arg2 = gh_scm2int(s_1);
    }
    gh_defer_ints();
    map_set_size(arg1,arg2);
    
    gh_allow_ints();
    gswig_result = GH_UNSPECIFIED;
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_map_resize (SCM s_0, SCM s_1)
{
    #define FUNC_NAME "map-resize"
    int arg1 ;
    int arg2 ;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    {
        arg1 = gh_scm2int(s_0);
    }
    {
        arg2 = gh_scm2int(s_1);
    }
    gh_defer_ints();
    map_resize(arg1,arg2);
    
    gh_allow_ints();
    gswig_result = GH_UNSPECIFIED;
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_map_clear ()
{
    #define FUNC_NAME "map-clear"
    SCM gswig_result;
    int gswig_list_p = 0;
    
    gh_defer_ints();
    map_clear();
    
    gh_allow_ints();
    gswig_result = GH_UNSPECIFIED;
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_editor_new (SCM s_0, SCM s_1)
{
    #define FUNC_NAME "editor-new"
    int arg1 ;
    int arg2 ;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    {
        arg1 = gh_scm2int(s_0);
    }
    {
        arg2 = gh_scm2int(s_1);
    }
    gh_defer_ints();
    editor_new(arg1,arg2);
    
    gh_allow_ints();
    gswig_result = GH_UNSPECIFIED;
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_editor_load (SCM s_0)
{
    #define FUNC_NAME "editor-load"
    char *arg1 ;
    int must_free1 = 0 ;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    {
        arg1 = SWIG_scm2str(s_0);
        must_free1 = 1;
    }
    gh_defer_ints();
    editor_load((char const *)arg1);
    
    gh_allow_ints();
    gswig_result = GH_UNSPECIFIED;
    if (must_free1 && arg1) scm_must_free(arg1);
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_file_dialog ()
{
    #define FUNC_NAME "file-dialog"
    SCM gswig_result;
    int gswig_list_p = 0;
    
    gh_defer_ints();
    file_dialog();
    
    gh_allow_ints();
    gswig_result = GH_UNSPECIFIED;
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_game_play (SCM s_0)
{
    #define FUNC_NAME "game-play"
    char *arg1 ;
    int must_free1 = 0 ;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    {
        arg1 = SWIG_scm2str(s_0);
        must_free1 = 1;
    }
    gh_defer_ints();
    game_play((char const *)arg1);
    
    gh_allow_ints();
    gswig_result = GH_UNSPECIFIED;
    if (must_free1 && arg1) scm_must_free(arg1);
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_game_add_water (SCM s_0, SCM s_1, SCM s_2, SCM s_3)
{
    #define FUNC_NAME "game-add-water"
    int arg1 ;
    int arg2 ;
    int arg3 ;
    int arg4 ;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    {
        arg1 = gh_scm2int(s_0);
    }
    {
        arg2 = gh_scm2int(s_1);
    }
    {
        arg3 = gh_scm2int(s_2);
    }
    {
        arg4 = gh_scm2int(s_3);
    }
    gh_defer_ints();
    game_add_water(arg1,arg2,arg3,arg4);
    
    gh_allow_ints();
    gswig_result = GH_UNSPECIFIED;
    
    return gswig_result;
    #undef FUNC_NAME
}


static SCM
_wrap_game_set_player (SCM s_0, SCM s_1)
{
    #define FUNC_NAME "game-set-player"
    float arg1 ;
    float arg2 ;
    SCM gswig_result;
    int gswig_list_p = 0;
    
    {
        arg1 = gh_scm2double(s_0);
    }
    {
        arg2 = gh_scm2double(s_1);
    }
    gh_defer_ints();
    game_set_player(arg1,arg2);
    
    gh_allow_ints();
    gswig_result = GH_UNSPECIFIED;
    
    return gswig_result;
    #undef FUNC_NAME
}


#ifdef __cplusplus
extern "C" {
#endif

/* -------- TYPE CONVERSION AND EQUIVALENCE RULES (BEGIN) -------- */

static swig_type_info _swigt__p_CL_Component[] = {{"_p_CL_Component", 0, "CL_Component *", 0},{"_p_CL_Component"},{0}};

static swig_type_info *swig_types_initial[] = {
_swigt__p_CL_Component, 
0
};


/* -------- TYPE CONVERSION AND EQUIVALENCE RULES (END) -------- */

#ifdef __cplusplus
}
#endif
extern void
SWIG_init (void)
{
    SWIG_Guile_Init();
    gh_new_procedure("push-component", (swig_guile_proc) _wrap_push_component, 1, 0, 0);
    gh_new_procedure("pop-component", (swig_guile_proc) _wrap_pop_component, 0, 0, 0);
    gh_new_procedure("tile-selector-create", (swig_guile_proc) _wrap_tile_selector_create, 4, 0, 0);
    gh_new_procedure("editor-set-brush-tile", (swig_guile_proc) _wrap_editor_set_brush_tile, 1, 0, 0);
    gh_new_procedure("editor-get-brush-tile", (swig_guile_proc) _wrap_editor_get_brush_tile, 0, 0, 0);
    gh_new_procedure("editor-set-tool", (swig_guile_proc) _wrap_editor_set_tool, 1, 0, 0);
    gh_new_procedure("tilemap-set-active-layer", (swig_guile_proc) _wrap_tilemap_set_active_layer, 1, 0, 0);
    gh_new_procedure("editor-add-window", (swig_guile_proc) _wrap_editor_add_window, 5, 0, 0);
    gh_new_procedure("editor-add-button-func", (swig_guile_proc) _wrap_editor_add_button_func, 6, 0, 0);
    gh_new_procedure("editor-add-button", (swig_guile_proc) _wrap_editor_add_button, 5, 0, 0);
    gh_new_procedure("editor-add-label", (swig_guile_proc) _wrap_editor_add_label, 3, 0, 0);
    gh_new_procedure("editor-add-inputbox", (swig_guile_proc) _wrap_editor_add_inputbox, 5, 0, 0);
    gh_new_procedure("component-on-click", (swig_guile_proc) _wrap_component_on_click, 2, 0, 0);
    gh_new_procedure("inputbox-get-text", (swig_guile_proc) _wrap_inputbox_get_text, 1, 0, 0);
    gh_new_procedure("window-get-client-area", (swig_guile_proc) _wrap_window_get_client_area, 1, 0, 0);
    gh_new_procedure("window-close", (swig_guile_proc) _wrap_window_close, 1, 0, 0);
    gh_new_procedure("component-hide", (swig_guile_proc) _wrap_component_hide, 1, 0, 0);
    gh_new_procedure("component-show", (swig_guile_proc) _wrap_component_show, 1, 0, 0);
    gh_new_procedure("editor-quit", (swig_guile_proc) _wrap_editor_quit, 0, 0, 0);
    gh_new_procedure("screen-get-width", (swig_guile_proc) _wrap_screen_get_width, 0, 0, 0);
    gh_new_procedure("screen-get-height", (swig_guile_proc) _wrap_screen_get_height, 0, 0, 0);
    gh_new_procedure("map-get-data", (swig_guile_proc) _wrap_map_get_data, 1, 0, 0);
    gh_new_procedure("map-get-width", (swig_guile_proc) _wrap_map_get_width, 0, 0, 0);
    gh_new_procedure("map-get-height", (swig_guile_proc) _wrap_map_get_height, 0, 0, 0);
    gh_new_procedure("map-set-size", (swig_guile_proc) _wrap_map_set_size, 2, 0, 0);
    gh_new_procedure("map-resize", (swig_guile_proc) _wrap_map_resize, 2, 0, 0);
    gh_new_procedure("map-clear", (swig_guile_proc) _wrap_map_clear, 0, 0, 0);
    gh_new_procedure("editor-new", (swig_guile_proc) _wrap_editor_new, 2, 0, 0);
    gh_new_procedure("editor-load", (swig_guile_proc) _wrap_editor_load, 1, 0, 0);
    gh_new_procedure("file-dialog", (swig_guile_proc) _wrap_file_dialog, 0, 0, 0);
    gh_new_procedure("game-play", (swig_guile_proc) _wrap_game_play, 1, 0, 0);
    gh_new_procedure("game-add-water", (swig_guile_proc) _wrap_game_add_water, 4, 0, 0);
    gh_new_procedure("game-set-player", (swig_guile_proc) _wrap_game_set_player, 2, 0, 0);
    SWIG_Guile_RegisterTypes(swig_types, swig_types_initial);
}

extern "C" {
    /* Linkage: simple */
    
}

