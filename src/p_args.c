# 1 "args.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "args.c"
# 22 "args.c"
# 1 "/usr/include/stdlib.h" 1 3 4
# 10 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/machine/ieeefp.h" 1 3 4
# 11 "/usr/include/stdlib.h" 2 3 4
# 1 "/usr/include/_ansi.h" 1 3 4
# 15 "/usr/include/_ansi.h" 3 4
# 1 "/usr/include/newlib.h" 1 3 4
# 16 "/usr/include/_ansi.h" 2 3 4
# 1 "/usr/include/sys/config.h" 1 3 4



# 1 "/usr/include/machine/ieeefp.h" 1 3 4
# 5 "/usr/include/sys/config.h" 2 3 4
# 1 "/usr/include/sys/features.h" 1 3 4
# 6 "/usr/include/sys/config.h" 2 3 4
# 226 "/usr/include/sys/config.h" 3 4
# 1 "/usr/include/cygwin/config.h" 1 3 4
# 227 "/usr/include/sys/config.h" 2 3 4
# 17 "/usr/include/_ansi.h" 2 3 4
# 12 "/usr/include/stdlib.h" 2 3 4




# 1 "/usr/lib/gcc/i686-pc-cygwin/4.5.3/include/stddef.h" 1 3 4
# 211 "/usr/lib/gcc/i686-pc-cygwin/4.5.3/include/stddef.h" 3 4
typedef unsigned int size_t;
# 323 "/usr/lib/gcc/i686-pc-cygwin/4.5.3/include/stddef.h" 3 4
typedef short unsigned int wchar_t;
# 17 "/usr/include/stdlib.h" 2 3 4

# 1 "/usr/include/sys/reent.h" 1 3 4
# 13 "/usr/include/sys/reent.h" 3 4
# 1 "/usr/include/_ansi.h" 1 3 4
# 14 "/usr/include/sys/reent.h" 2 3 4
# 1 "/usr/include/sys/_types.h" 1 3 4
# 12 "/usr/include/sys/_types.h" 3 4
# 1 "/usr/include/machine/_types.h" 1 3 4






# 1 "/usr/include/machine/_default_types.h" 1 3 4
# 25 "/usr/include/machine/_default_types.h" 3 4
typedef signed char __int8_t ;
typedef unsigned char __uint8_t ;
# 35 "/usr/include/machine/_default_types.h" 3 4
typedef signed short __int16_t;
typedef unsigned short __uint16_t;
# 45 "/usr/include/machine/_default_types.h" 3 4
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
# 57 "/usr/include/machine/_default_types.h" 3 4
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
# 75 "/usr/include/machine/_default_types.h" 3 4
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
# 98 "/usr/include/machine/_default_types.h" 3 4
typedef signed long long __int64_t;
typedef unsigned long long __uint64_t;
# 8 "/usr/include/machine/_types.h" 2 3 4
# 13 "/usr/include/sys/_types.h" 2 3 4
# 1 "/usr/include/sys/lock.h" 1 3 4
# 14 "/usr/include/sys/lock.h" 3 4
typedef void *_LOCK_T;
# 44 "/usr/include/sys/lock.h" 3 4
void __cygwin_lock_init(_LOCK_T *);
void __cygwin_lock_init_recursive(_LOCK_T *);
void __cygwin_lock_fini(_LOCK_T *);
void __cygwin_lock_lock(_LOCK_T *);
int __cygwin_lock_trylock(_LOCK_T *);
void __cygwin_lock_unlock(_LOCK_T *);
# 14 "/usr/include/sys/_types.h" 2 3 4


typedef long _off_t;







typedef short __dev_t;




typedef unsigned short __uid_t;


typedef unsigned short __gid_t;



__extension__ typedef long long _off64_t;







typedef long _fpos_t;





typedef _off64_t _fpos64_t;
# 60 "/usr/include/sys/_types.h" 3 4
typedef signed int _ssize_t;
# 72 "/usr/include/sys/_types.h" 3 4
# 1 "/usr/lib/gcc/i686-pc-cygwin/4.5.3/include/stddef.h" 1 3 4
# 352 "/usr/lib/gcc/i686-pc-cygwin/4.5.3/include/stddef.h" 3 4
typedef unsigned int wint_t;
# 73 "/usr/include/sys/_types.h" 2 3 4



typedef struct
{
  int __count;
  union
  {
    wint_t __wch;
    unsigned char __wchb[4];
  } __value;
} _mbstate_t;



typedef _LOCK_T _flock_t;




typedef void *_iconv_t;
# 15 "/usr/include/sys/reent.h" 2 3 4






typedef unsigned long __ULong;
# 37 "/usr/include/sys/reent.h" 3 4
struct _reent;






struct _Bigint
{
  struct _Bigint *_next;
  int _k, _maxwds, _sign, _wds;
  __ULong _x[1];
};


struct __tm
{
  int __tm_sec;
  int __tm_min;
  int __tm_hour;
  int __tm_mday;
  int __tm_mon;
  int __tm_year;
  int __tm_wday;
  int __tm_yday;
  int __tm_isdst;
};







struct _on_exit_args {
 void * _fnargs[32];
 void * _dso_handle[32];

 __ULong _fntypes;


 __ULong _is_cxa;
};
# 95 "/usr/include/sys/reent.h" 3 4
struct _atexit {
 struct _atexit *_next;
 int _ind;

 void (*_fns[32])(void);
        struct _on_exit_args _on_exit_args;
};
# 128 "/usr/include/sys/reent.h" 3 4
struct __sbuf {
 unsigned char *_base;
 int _size;
};
# 192 "/usr/include/sys/reent.h" 3 4
struct __sFILE {
  unsigned char *_p;
  int _r;
  int _w;
  short _flags;
  short _file;
  struct __sbuf _bf;
  int _lbfsize;






  void * _cookie;

  _ssize_t (__attribute__((__cdecl__)) * _read) (struct _reent *, void *, char *, int)
                     ;
  _ssize_t (__attribute__((__cdecl__)) * _write) (struct _reent *, void *, const char *, int)
                            ;
  _fpos_t (__attribute__((__cdecl__)) * _seek) (struct _reent *, void *, _fpos_t, int);
  int (__attribute__((__cdecl__)) * _close) (struct _reent *, void *);


  struct __sbuf _ub;
  unsigned char *_up;
  int _ur;


  unsigned char _ubuf[3];
  unsigned char _nbuf[1];


  struct __sbuf _lb;


  int _blksize;
  _off_t _offset;


  struct _reent *_data;



  _flock_t _lock;

  _mbstate_t _mbstate;
  int _flags2;
};
# 249 "/usr/include/sys/reent.h" 3 4
struct __sFILE64 {
  unsigned char *_p;
  int _r;
  int _w;
  short _flags;
  short _file;
  struct __sbuf _bf;
  int _lbfsize;

  struct _reent *_data;


  void * _cookie;

  _ssize_t (__attribute__((__cdecl__)) * _read) (struct _reent *, void *, char *, int)
                     ;
  _ssize_t (__attribute__((__cdecl__)) * _write) (struct _reent *, void *, const char *, int)
                            ;
  _fpos_t (__attribute__((__cdecl__)) * _seek) (struct _reent *, void *, _fpos_t, int);
  int (__attribute__((__cdecl__)) * _close) (struct _reent *, void *);


  struct __sbuf _ub;
  unsigned char *_up;
  int _ur;


  unsigned char _ubuf[3];
  unsigned char _nbuf[1];


  struct __sbuf _lb;


  int _blksize;
  int _flags2;

  _off64_t _offset;
  _fpos64_t (__attribute__((__cdecl__)) * _seek64) (struct _reent *, void *, _fpos64_t, int);


  _flock_t _lock;

  _mbstate_t _mbstate;
};
typedef struct __sFILE64 __FILE;





struct _glue
{
  struct _glue *_next;
  int _niobs;
  __FILE *_iobs;
};
# 328 "/usr/include/sys/reent.h" 3 4
struct _rand48 {
  unsigned short _seed[3];
  unsigned short _mult[3];
  unsigned short _add;




};
# 600 "/usr/include/sys/reent.h" 3 4
struct _reent
{
  int _errno;




  __FILE *_stdin, *_stdout, *_stderr;

  int _inc;
  char _emergency[25];

  int _current_category;
  const char *_current_locale;

  int __sdidinit;

  void (__attribute__((__cdecl__)) * __cleanup) (struct _reent *);


  struct _Bigint *_result;
  int _result_k;
  struct _Bigint *_p5s;
  struct _Bigint **_freelist;


  int _cvtlen;
  char *_cvtbuf;

  union
    {
      struct
        {
          unsigned int _unused_rand;
          char * _strtok_last;
          char _asctime_buf[26];
          struct __tm _localtime_buf;
          int _gamma_signgam;
          __extension__ unsigned long long _rand_next;
          struct _rand48 _r48;
          _mbstate_t _mblen_state;
          _mbstate_t _mbtowc_state;
          _mbstate_t _wctomb_state;
          char _l64a_buf[8];
          char _signal_buf[24];
          int _getdate_err;
          _mbstate_t _mbrlen_state;
          _mbstate_t _mbrtowc_state;
          _mbstate_t _mbsrtowcs_state;
          _mbstate_t _wcrtomb_state;
          _mbstate_t _wcsrtombs_state;
   int _h_errno;
        } _reent;



      struct
        {

          unsigned char * _nextf[30];
          unsigned int _nmalloc[30];
        } _unused;
    } _new;



  struct _atexit *_atexit;
  struct _atexit _atexit0;



  void (**(_sig_func))(int);




  struct _glue __sglue;
  __FILE __sf[3];
};
# 793 "/usr/include/sys/reent.h" 3 4
extern struct _reent *_impure_ptr ;
extern struct _reent *const _global_impure_ptr ;

void _reclaim_reent (struct _reent *);







  struct _reent * __attribute__((__cdecl__)) __getreent (void);
# 19 "/usr/include/stdlib.h" 2 3 4
# 1 "/usr/include/machine/stdlib.h" 1 3 4
# 17 "/usr/include/machine/stdlib.h" 3 4
char *mkdtemp (char *);
# 20 "/usr/include/stdlib.h" 2 3 4

# 1 "/usr/include/alloca.h" 1 3 4
# 22 "/usr/include/stdlib.h" 2 3 4



# 1 "/usr/include/cygwin/stdlib.h" 1 3 4
# 14 "/usr/include/cygwin/stdlib.h" 3 4
# 1 "/usr/include/cygwin/wait.h" 1 3 4
# 15 "/usr/include/cygwin/stdlib.h" 2 3 4






__uint32_t arc4random(void);
void arc4random_addrandom(unsigned char *, int);
void arc4random_buf(void *, size_t);
void arc4random_stir(void);
__uint32_t arc4random_uniform(__uint32_t);

const char *getprogname (void);
void setprogname (const char *);


char *realpath (const char *, char *);
char *canonicalize_file_name (const char *);
int unsetenv (const char *);
char *initstate (unsigned seed, char *state, size_t size);
long random (void);
char *setstate (const char *state);
void srandom (unsigned);
char *ptsname (int);
int ptsname_r(int, char *, size_t);
int getpt (void);
int grantpt (int);
int unlockpt (int);


int posix_openpt (int);
int posix_memalign (void **, size_t, size_t);






extern void * memalign (size_t, size_t);
extern void * valloc (size_t);
# 26 "/usr/include/stdlib.h" 2 3 4




typedef struct
{
  int quot;
  int rem;
} div_t;

typedef struct
{
  long quot;
  long rem;
} ldiv_t;


typedef struct
{
  long long int quot;
  long long int rem;
} lldiv_t;







int __attribute__((__cdecl__)) __locale_mb_cur_max (void);



void __attribute__((__cdecl__)) abort (void) __attribute__ ((noreturn));
int __attribute__((__cdecl__)) abs (int);
int __attribute__((__cdecl__)) atexit (void (*__func)(void));
double __attribute__((__cdecl__)) atof (const char *__nptr);

float __attribute__((__cdecl__)) atoff (const char *__nptr);

int __attribute__((__cdecl__)) atoi (const char *__nptr);
int __attribute__((__cdecl__)) _atoi_r (struct _reent *, const char *__nptr);
long __attribute__((__cdecl__)) atol (const char *__nptr);
long __attribute__((__cdecl__)) _atol_r (struct _reent *, const char *__nptr);
void * __attribute__((__cdecl__)) bsearch (const void * __key, const void * __base, size_t __nmemb, size_t __size, int (__attribute__((__cdecl__)) * _compar) (const void *, const void *))



                                                         ;
void * __attribute__((__cdecl__)) calloc (size_t __nmemb, size_t __size) ;
div_t __attribute__((__cdecl__)) div (int __numer, int __denom);
void __attribute__((__cdecl__)) exit (int __status) __attribute__ ((noreturn));
void __attribute__((__cdecl__)) free (void *) ;
char * __attribute__((__cdecl__)) getenv (const char *__string);
char * __attribute__((__cdecl__)) _getenv_r (struct _reent *, const char *__string);
char * __attribute__((__cdecl__)) _findenv (const char *, int *);
char * __attribute__((__cdecl__)) _findenv_r (struct _reent *, const char *, int *);

extern char *suboptarg;
int __attribute__((__cdecl__)) getsubopt (char **, char * const *, char **);

long __attribute__((__cdecl__)) labs (long);
ldiv_t __attribute__((__cdecl__)) ldiv (long __numer, long __denom);
void * __attribute__((__cdecl__)) malloc (size_t __size) ;
int __attribute__((__cdecl__)) mblen (const char *, size_t);
int __attribute__((__cdecl__)) _mblen_r (struct _reent *, const char *, size_t, _mbstate_t *);
int __attribute__((__cdecl__)) mbtowc (wchar_t *, const char *, size_t);
int __attribute__((__cdecl__)) _mbtowc_r (struct _reent *, wchar_t *, const char *, size_t, _mbstate_t *);
int __attribute__((__cdecl__)) wctomb (char *, wchar_t);
int __attribute__((__cdecl__)) _wctomb_r (struct _reent *, char *, wchar_t, _mbstate_t *);
size_t __attribute__((__cdecl__)) mbstowcs (wchar_t *, const char *, size_t);
size_t __attribute__((__cdecl__)) _mbstowcs_r (struct _reent *, wchar_t *, const char *, size_t, _mbstate_t *);
size_t __attribute__((__cdecl__)) wcstombs (char *, const wchar_t *, size_t);
size_t __attribute__((__cdecl__)) _wcstombs_r (struct _reent *, char *, const wchar_t *, size_t, _mbstate_t *);


char * __attribute__((__cdecl__)) mkdtemp (char *);
int __attribute__((__cdecl__)) mkostemp (char *, int);
int __attribute__((__cdecl__)) mkostemps (char *, int, int);
int __attribute__((__cdecl__)) mkstemp (char *);
int __attribute__((__cdecl__)) mkstemps (char *, int);
char * __attribute__((__cdecl__)) mktemp (char *) __attribute__ ((__warning__ ("the use of `mktemp' is dangerous; use `mkstemp' instead")));

char * __attribute__((__cdecl__)) _mkdtemp_r (struct _reent *, char *);
int __attribute__((__cdecl__)) _mkostemp_r (struct _reent *, char *, int);
int __attribute__((__cdecl__)) _mkostemps_r (struct _reent *, char *, int, int);
int __attribute__((__cdecl__)) _mkstemp_r (struct _reent *, char *);
int __attribute__((__cdecl__)) _mkstemps_r (struct _reent *, char *, int);
char * __attribute__((__cdecl__)) _mktemp_r (struct _reent *, char *) __attribute__ ((__warning__ ("the use of `mktemp' is dangerous; use `mkstemp' instead")));

void __attribute__((__cdecl__)) qsort (void * __base, size_t __nmemb, size_t __size, int(*_compar)(const void *, const void *));
int __attribute__((__cdecl__)) rand (void);
void * __attribute__((__cdecl__)) realloc (void * __r, size_t __size) ;

void * __attribute__((__cdecl__)) reallocf (void * __r, size_t __size);

void __attribute__((__cdecl__)) srand (unsigned __seed);
double __attribute__((__cdecl__)) strtod (const char *__n, char **__end_PTR);
double __attribute__((__cdecl__)) _strtod_r (struct _reent *,const char *__n, char **__end_PTR);

float __attribute__((__cdecl__)) strtof (const char *__n, char **__end_PTR);







long __attribute__((__cdecl__)) strtol (const char *__n, char **__end_PTR, int __base);
long __attribute__((__cdecl__)) _strtol_r (struct _reent *,const char *__n, char **__end_PTR, int __base);
unsigned long __attribute__((__cdecl__)) strtoul (const char *__n, char **__end_PTR, int __base);
unsigned long __attribute__((__cdecl__)) _strtoul_r (struct _reent *,const char *__n, char **__end_PTR, int __base);

int __attribute__((__cdecl__)) system (const char *__string);


long __attribute__((__cdecl__)) a64l (const char *__input);
char * __attribute__((__cdecl__)) l64a (long __input);
char * __attribute__((__cdecl__)) _l64a_r (struct _reent *,long __input);
int __attribute__((__cdecl__)) on_exit (void (*__func)(int, void *),void * __arg);
void __attribute__((__cdecl__)) _Exit (int __status) __attribute__ ((noreturn));
int __attribute__((__cdecl__)) putenv (char *__string);
int __attribute__((__cdecl__)) _putenv_r (struct _reent *, char *__string);
void * __attribute__((__cdecl__)) _reallocf_r (struct _reent *, void *, size_t);
int __attribute__((__cdecl__)) setenv (const char *__string, const char *__value, int __overwrite);
int __attribute__((__cdecl__)) _setenv_r (struct _reent *, const char *__string, const char *__value, int __overwrite);

char * __attribute__((__cdecl__)) gcvt (double,int,char *);
char * __attribute__((__cdecl__)) gcvtf (float,int,char *);
char * __attribute__((__cdecl__)) fcvt (double,int,int *,int *);
char * __attribute__((__cdecl__)) fcvtf (float,int,int *,int *);
char * __attribute__((__cdecl__)) ecvt (double,int,int *,int *);
char * __attribute__((__cdecl__)) ecvtbuf (double, int, int*, int*, char *);
char * __attribute__((__cdecl__)) fcvtbuf (double, int, int*, int*, char *);
char * __attribute__((__cdecl__)) ecvtf (float,int,int *,int *);
char * __attribute__((__cdecl__)) dtoa (double, int, int, int *, int*, char**);
int __attribute__((__cdecl__)) rand_r (unsigned *__seed);

double __attribute__((__cdecl__)) drand48 (void);
double __attribute__((__cdecl__)) _drand48_r (struct _reent *);
double __attribute__((__cdecl__)) erand48 (unsigned short [3]);
double __attribute__((__cdecl__)) _erand48_r (struct _reent *, unsigned short [3]);
long __attribute__((__cdecl__)) jrand48 (unsigned short [3]);
long __attribute__((__cdecl__)) _jrand48_r (struct _reent *, unsigned short [3]);
void __attribute__((__cdecl__)) lcong48 (unsigned short [7]);
void __attribute__((__cdecl__)) _lcong48_r (struct _reent *, unsigned short [7]);
long __attribute__((__cdecl__)) lrand48 (void);
long __attribute__((__cdecl__)) _lrand48_r (struct _reent *);
long __attribute__((__cdecl__)) mrand48 (void);
long __attribute__((__cdecl__)) _mrand48_r (struct _reent *);
long __attribute__((__cdecl__)) nrand48 (unsigned short [3]);
long __attribute__((__cdecl__)) _nrand48_r (struct _reent *, unsigned short [3]);
unsigned short *
       __attribute__((__cdecl__)) seed48 (unsigned short [3]);
unsigned short *
       __attribute__((__cdecl__)) _seed48_r (struct _reent *, unsigned short [3]);
void __attribute__((__cdecl__)) srand48 (long);
void __attribute__((__cdecl__)) _srand48_r (struct _reent *, long);
long long __attribute__((__cdecl__)) atoll (const char *__nptr);
long long __attribute__((__cdecl__)) _atoll_r (struct _reent *, const char *__nptr);
long long __attribute__((__cdecl__)) llabs (long long);
lldiv_t __attribute__((__cdecl__)) lldiv (long long __numer, long long __denom);


long long __attribute__((__cdecl__)) strtoll (const char *__n, char **__end_PTR, int __base);


long long __attribute__((__cdecl__)) _strtoll_r (struct _reent *, const char *__n, char **__end_PTR, int __base);


unsigned long long __attribute__((__cdecl__)) strtoull (const char *__n, char **__end_PTR, int __base);


unsigned long long __attribute__((__cdecl__)) _strtoull_r (struct _reent *, const char *__n, char **__end_PTR, int __base);
# 213 "/usr/include/stdlib.h" 3 4
char * __attribute__((__cdecl__)) _dtoa_r (struct _reent *, double, int, int, int *, int*, char**);







int __attribute__((__cdecl__)) _system_r (struct _reent *, const char *);

void __attribute__((__cdecl__)) __eprintf (const char *, const char *, unsigned int, const char *);
# 233 "/usr/include/stdlib.h" 3 4

# 23 "args.c" 2
# 1 "/usr/include/string.h" 1 3 4
# 12 "/usr/include/string.h" 3 4
# 1 "/usr/include/sys/cdefs.h" 1 3 4
# 44 "/usr/include/sys/cdefs.h" 3 4
# 1 "/usr/lib/gcc/i686-pc-cygwin/4.5.3/include/stddef.h" 1 3 4
# 149 "/usr/lib/gcc/i686-pc-cygwin/4.5.3/include/stddef.h" 3 4
typedef int ptrdiff_t;
# 45 "/usr/include/sys/cdefs.h" 2 3 4
# 1 "/usr/lib/gcc/i686-pc-cygwin/4.5.3/include/stdint.h" 1 3 4


# 1 "/usr/include/stdint.h" 1 3 4
# 14 "/usr/include/stdint.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 15 "/usr/include/stdint.h" 2 3 4





typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;



typedef long long int64_t;



typedef unsigned char uint8_t;
typedef unsigned short uint16_t;


typedef unsigned int uint32_t;




typedef unsigned long long uint64_t;




typedef signed char int_least8_t;
typedef short int_least16_t;
typedef int int_least32_t;



typedef long long int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned short uint_least16_t;
typedef unsigned int uint_least32_t;



typedef unsigned long long uint_least64_t;




typedef signed char int_fast8_t;





typedef int int_fast16_t;
typedef int int_fast32_t;
typedef long long int_fast64_t;


typedef unsigned char uint_fast8_t;





typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
typedef unsigned long long uint_fast64_t;
# 93 "/usr/include/stdint.h" 3 4
typedef int intptr_t;





typedef unsigned int uintptr_t;
# 108 "/usr/include/stdint.h" 3 4
typedef long long intmax_t;
typedef unsigned long long uintmax_t;
# 4 "/usr/lib/gcc/i686-pc-cygwin/4.5.3/include/stdint.h" 2 3 4
# 46 "/usr/include/sys/cdefs.h" 2 3 4
# 13 "/usr/include/string.h" 2 3 4




# 1 "/usr/lib/gcc/i686-pc-cygwin/4.5.3/include/stddef.h" 1 3 4
# 18 "/usr/include/string.h" 2 3 4



void * __attribute__((__cdecl__)) memchr (const void *, int, size_t);
int __attribute__((__cdecl__)) memcmp (const void *, const void *, size_t);
void * __attribute__((__cdecl__)) memcpy (void *, const void *, size_t);
void * __attribute__((__cdecl__)) memmove (void *, const void *, size_t);
void * __attribute__((__cdecl__)) memset (void *, int, size_t);
char *__attribute__((__cdecl__)) strcat (char *, const char *);
char *__attribute__((__cdecl__)) strchr (const char *, int);
int __attribute__((__cdecl__)) strcmp (const char *, const char *);
int __attribute__((__cdecl__)) strcoll (const char *, const char *);
char *__attribute__((__cdecl__)) strcpy (char *, const char *);
size_t __attribute__((__cdecl__)) strcspn (const char *, const char *);
char *__attribute__((__cdecl__)) strerror (int);
size_t __attribute__((__cdecl__)) strlen (const char *);
char *__attribute__((__cdecl__)) strncat (char *, const char *, size_t);
int __attribute__((__cdecl__)) strncmp (const char *, const char *, size_t);
char *__attribute__((__cdecl__)) strncpy (char *, const char *, size_t);
char *__attribute__((__cdecl__)) strpbrk (const char *, const char *);
char *__attribute__((__cdecl__)) strrchr (const char *, int);
size_t __attribute__((__cdecl__)) strspn (const char *, const char *);
char *__attribute__((__cdecl__)) strstr (const char *, const char *);


char *__attribute__((__cdecl__)) strtok (char *, const char *);


size_t __attribute__((__cdecl__)) strxfrm (char *, const char *, size_t);


char *__attribute__((__cdecl__)) strtok_r (char *, const char *, char **);

int __attribute__((__cdecl__)) bcmp (const void *, const void *, size_t);
void __attribute__((__cdecl__)) bcopy (const void *, void *, size_t);
void __attribute__((__cdecl__)) bzero (void *, size_t);
int __attribute__((__cdecl__)) ffs (int);
char *__attribute__((__cdecl__)) index (const char *, int);
void * __attribute__((__cdecl__)) memccpy (void *, const void *, int, size_t);
void * __attribute__((__cdecl__)) mempcpy (void *, const void *, size_t);
void * __attribute__((__cdecl__)) memmem (const void *, size_t, const void *, size_t);
void * __attribute__((__cdecl__)) memrchr (const void *, int, size_t);
char *__attribute__((__cdecl__)) rindex (const char *, int);
char *__attribute__((__cdecl__)) stpcpy (char *, const char *);
char *__attribute__((__cdecl__)) stpncpy (char *, const char *, size_t);
int __attribute__((__cdecl__)) strcasecmp (const char *, const char *);
char *__attribute__((__cdecl__)) strcasestr (const char *, const char *);
char *__attribute__((__cdecl__)) strchrnul (const char *, int);


char *__attribute__((__cdecl__)) strdup (const char *);


char *__attribute__((__cdecl__)) _strdup_r (struct _reent *, const char *);


char *__attribute__((__cdecl__)) strndup (const char *, size_t);


char *__attribute__((__cdecl__)) _strndup_r (struct _reent *, const char *, size_t);
# 86 "/usr/include/string.h" 3 4
int __attribute__((__cdecl__)) strerror_r (int, char *, size_t) __asm__ ("_" "__xpg_strerror_r");





size_t __attribute__((__cdecl__)) strlcat (char *, const char *, size_t);
size_t __attribute__((__cdecl__)) strlcpy (char *, const char *, size_t);
int __attribute__((__cdecl__)) strncasecmp (const char *, const char *, size_t);
size_t __attribute__((__cdecl__)) strnlen (const char *, size_t);
char *__attribute__((__cdecl__)) strsep (char **, const char *);
char *__attribute__((__cdecl__)) strlwr (char *);
char *__attribute__((__cdecl__)) strupr (char *);

char *__attribute__((__cdecl__)) strsignal (int __signo);


int __attribute__((__cdecl__)) strtosigno (const char *__name);



char * __attribute__((__cdecl__)) _strerror_r (struct _reent *, int, int, int *);
# 139 "/usr/include/string.h" 3 4
# 1 "/usr/include/sys/string.h" 1 3 4
# 140 "/usr/include/string.h" 2 3 4


# 24 "args.c" 2
# 1 "/usr/include/stdio.h" 1 3 4
# 35 "/usr/include/stdio.h" 3 4
# 1 "/usr/lib/gcc/i686-pc-cygwin/4.5.3/include/stddef.h" 1 3 4
# 36 "/usr/include/stdio.h" 2 3 4


# 1 "/usr/lib/gcc/i686-pc-cygwin/4.5.3/include/stdarg.h" 1 3 4
# 40 "/usr/lib/gcc/i686-pc-cygwin/4.5.3/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 39 "/usr/include/stdio.h" 2 3 4
# 47 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/sys/types.h" 1 3 4
# 69 "/usr/include/sys/types.h" 3 4
# 1 "/usr/lib/gcc/i686-pc-cygwin/4.5.3/include/stddef.h" 1 3 4
# 70 "/usr/include/sys/types.h" 2 3 4
# 1 "/usr/include/machine/types.h" 1 3 4
# 19 "/usr/include/machine/types.h" 3 4
typedef long int __off_t;
typedef int __pid_t;

__extension__ typedef long long int __loff_t;
# 71 "/usr/include/sys/types.h" 2 3 4
# 92 "/usr/include/sys/types.h" 3 4
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;



typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;



typedef unsigned long clock_t;




typedef long time_t;







struct timespec {
  time_t tv_sec;
  long tv_nsec;
};


struct itimerspec {
  struct timespec it_interval;
  struct timespec it_value;
};

typedef long daddr_t;
typedef char * caddr_t;
# 175 "/usr/include/sys/types.h" 3 4
typedef int pid_t;
# 185 "/usr/include/sys/types.h" 3 4
typedef _ssize_t ssize_t;
# 204 "/usr/include/sys/types.h" 3 4
typedef unsigned short nlink_t;
# 226 "/usr/include/sys/types.h" 3 4
typedef long fd_mask;







typedef struct _types_fd_set {
 fd_mask fds_bits[(((64)+(((sizeof (fd_mask) * 8))-1))/((sizeof (fd_mask) * 8)))];
} _types_fd_set;
# 257 "/usr/include/sys/types.h" 3 4
typedef unsigned long clockid_t;




typedef unsigned long timer_t;



typedef unsigned long useconds_t;
typedef long suseconds_t;
# 455 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/cygwin/types.h" 1 3 4
# 21 "/usr/include/cygwin/types.h" 3 4
# 1 "/usr/include/endian.h" 1 3 4
# 15 "/usr/include/endian.h" 3 4
# 1 "/usr/include/bits/endian.h" 1 3 4
# 16 "/usr/include/endian.h" 2 3 4
# 32 "/usr/include/endian.h" 3 4
# 1 "/usr/include/byteswap.h" 1 3 4
# 18 "/usr/include/byteswap.h" 3 4
static __inline unsigned short
bswap_16 (unsigned short __x)
{
  return (__x >> 8) | (__x << 8);
}

static __inline unsigned int
bswap_32 (unsigned int __x)
{
  return (bswap_16 (__x & 0xffff) << 16) | (bswap_16 (__x >> 16));
}

static __inline unsigned long long
bswap_64 (unsigned long long __x)
{
  return (((unsigned long long) bswap_32 (__x & 0xffffffffull)) << 32) | (bswap_32 (__x >> 32));
}
# 33 "/usr/include/endian.h" 2 3 4
# 22 "/usr/include/cygwin/types.h" 2 3 4




typedef struct timespec timespec_t;




typedef struct timespec timestruc_t;
# 40 "/usr/include/cygwin/types.h" 3 4
typedef _off64_t off_t;



typedef __loff_t loff_t;



typedef __int16_t __dev16_t;
typedef __uint32_t dev_t;




typedef __int32_t blksize_t;




typedef __int32_t __blkcnt32_t;
typedef __int64_t blkcnt_t;





typedef unsigned long fsblkcnt_t;





typedef unsigned long fsfilcnt_t;




typedef unsigned short __uid16_t;
typedef __uint32_t uid_t;




typedef unsigned short __gid16_t;
typedef __uint32_t gid_t;





typedef __uint32_t __ino32_t;

typedef __uint64_t ino_t;





typedef __uint32_t id_t;
# 112 "/usr/include/cygwin/types.h" 3 4
struct flock {
 short l_type;
 short l_whence;
 off_t l_start;
 off_t l_len;
 pid_t l_pid;
};



typedef long long key_t;







typedef unsigned long vm_offset_t;




typedef unsigned long vm_size_t;




typedef void *vm_object_t;




typedef unsigned char u_int8_t;



typedef __uint16_t u_int16_t;



typedef __uint32_t u_int32_t;



typedef __uint64_t u_int64_t;




typedef __int32_t register_t;




typedef char *addr_t;




typedef unsigned mode_t;





typedef struct __pthread_t {char __dummy;} *pthread_t;
typedef struct __pthread_mutex_t {char __dummy;} *pthread_mutex_t;

typedef struct __pthread_key_t {char __dummy;} *pthread_key_t;
typedef struct __pthread_attr_t {char __dummy;} *pthread_attr_t;
typedef struct __pthread_mutexattr_t {char __dummy;} *pthread_mutexattr_t;
typedef struct __pthread_condattr_t {char __dummy;} *pthread_condattr_t;
typedef struct __pthread_cond_t {char __dummy;} *pthread_cond_t;


typedef struct
{
  pthread_mutex_t mutex;
  int state;
}
pthread_once_t;
typedef struct __pthread_spinlock_t {char __dummy;} *pthread_spinlock_t;
typedef struct __pthread_rwlock_t {char __dummy;} *pthread_rwlock_t;
typedef struct __pthread_rwlockattr_t {char __dummy;} *pthread_rwlockattr_t;
# 219 "/usr/include/cygwin/types.h" 3 4
# 1 "/usr/include/sys/sysmacros.h" 1 3 4
# 14 "/usr/include/sys/sysmacros.h" 3 4
# 1 "/usr/include/sys/types.h" 1 3 4
# 15 "/usr/include/sys/sysmacros.h" 2 3 4

extern __inline__ __attribute__ ((__always_inline__)) int gnu_dev_major(dev_t);
extern __inline__ __attribute__ ((__always_inline__)) int gnu_dev_minor(dev_t);
extern __inline__ __attribute__ ((__always_inline__)) dev_t gnu_dev_makedev(int, int);

extern __inline__ __attribute__ ((__always_inline__)) int
gnu_dev_major(dev_t dev)
{
 return (int)(((dev) >> 16) & 0xffff);
}

extern __inline__ __attribute__ ((__always_inline__)) int
gnu_dev_minor(dev_t dev)
{
 return (int)((dev) & 0xffff);
}

extern __inline__ __attribute__ ((__always_inline__)) dev_t
gnu_dev_makedev(int maj, int min)
{
 return (((maj) << 16) | ((min) & 0xffff));
}
# 220 "/usr/include/cygwin/types.h" 2 3 4
# 456 "/usr/include/sys/types.h" 2 3 4
# 48 "/usr/include/stdio.h" 2 3 4



typedef __FILE FILE;


typedef _fpos64_t fpos_t;







# 1 "/usr/include/sys/stdio.h" 1 3 4
# 35 "/usr/include/sys/stdio.h" 3 4


ssize_t __attribute__((__cdecl__)) getline (char **, size_t *, FILE *);
ssize_t __attribute__((__cdecl__)) getdelim (char **, size_t *, int, FILE *);


# 63 "/usr/include/stdio.h" 2 3 4
# 168 "/usr/include/stdio.h" 3 4
FILE * __attribute__((__cdecl__)) tmpfile (void);
char * __attribute__((__cdecl__)) tmpnam (char *);
int __attribute__((__cdecl__)) fclose (FILE *);
int __attribute__((__cdecl__)) fflush (FILE *);
FILE * __attribute__((__cdecl__)) freopen (const char *, const char *, FILE *);
void __attribute__((__cdecl__)) setbuf (FILE *, char *);
int __attribute__((__cdecl__)) setvbuf (FILE *, char *, int, size_t);
int __attribute__((__cdecl__)) fprintf (FILE *, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;
int __attribute__((__cdecl__)) fscanf (FILE *, const char *, ...) __attribute__ ((__format__ (__scanf__, 2, 3)))
                                                           ;
int __attribute__((__cdecl__)) printf (const char *, ...) __attribute__ ((__format__ (__printf__, 1, 2)))
                                                            ;
int __attribute__((__cdecl__)) scanf (const char *, ...) __attribute__ ((__format__ (__scanf__, 1, 2)))
                                                           ;
int __attribute__((__cdecl__)) sscanf (const char *, const char *, ...) __attribute__ ((__format__ (__scanf__, 2, 3)))
                                                           ;
int __attribute__((__cdecl__)) vfprintf (FILE *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
int __attribute__((__cdecl__)) vprintf (const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 1, 0)))
                                                            ;
int __attribute__((__cdecl__)) vsprintf (char *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
int __attribute__((__cdecl__)) fgetc (FILE *);
char * __attribute__((__cdecl__)) fgets (char *, int, FILE *);
int __attribute__((__cdecl__)) fputc (int, FILE *);
int __attribute__((__cdecl__)) fputs (const char *, FILE *);
int __attribute__((__cdecl__)) getc (FILE *);
int __attribute__((__cdecl__)) getchar (void);
char * __attribute__((__cdecl__)) gets (char *);
int __attribute__((__cdecl__)) putc (int, FILE *);
int __attribute__((__cdecl__)) putchar (int);
int __attribute__((__cdecl__)) puts (const char *);
int __attribute__((__cdecl__)) ungetc (int, FILE *);
size_t __attribute__((__cdecl__)) fread (void *, size_t _size, size_t _n, FILE *);
size_t __attribute__((__cdecl__)) fwrite (const void * , size_t _size, size_t _n, FILE *);



int __attribute__((__cdecl__)) fgetpos (FILE *, fpos_t *);

int __attribute__((__cdecl__)) fseek (FILE *, long, int);



int __attribute__((__cdecl__)) fsetpos (FILE *, const fpos_t *);

long __attribute__((__cdecl__)) ftell ( FILE *);
void __attribute__((__cdecl__)) rewind (FILE *);
void __attribute__((__cdecl__)) clearerr (FILE *);
int __attribute__((__cdecl__)) feof (FILE *);
int __attribute__((__cdecl__)) ferror (FILE *);
void __attribute__((__cdecl__)) perror (const char *);

FILE * __attribute__((__cdecl__)) fopen (const char *_name, const char *_type);
int __attribute__((__cdecl__)) sprintf (char *, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;
int __attribute__((__cdecl__)) remove (const char *);
int __attribute__((__cdecl__)) rename (const char *, const char *);
# 236 "/usr/include/stdio.h" 3 4
int __attribute__((__cdecl__)) fseeko (FILE *, off_t, int);
off_t __attribute__((__cdecl__)) ftello ( FILE *);




int __attribute__((__cdecl__)) asiprintf (char **, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;
char * __attribute__((__cdecl__)) asniprintf (char *, size_t *, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
char * __attribute__((__cdecl__)) asnprintf (char *, size_t *, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int __attribute__((__cdecl__)) asprintf (char **, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;

int __attribute__((__cdecl__)) diprintf (int, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;

int __attribute__((__cdecl__)) fcloseall (void);
int __attribute__((__cdecl__)) fiprintf (FILE *, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;
int __attribute__((__cdecl__)) fiscanf (FILE *, const char *, ...) __attribute__ ((__format__ (__scanf__, 2, 3)))
                                                           ;
int __attribute__((__cdecl__)) iprintf (const char *, ...) __attribute__ ((__format__ (__printf__, 1, 2)))
                                                            ;
int __attribute__((__cdecl__)) iscanf (const char *, ...) __attribute__ ((__format__ (__scanf__, 1, 2)))
                                                           ;
int __attribute__((__cdecl__)) siprintf (char *, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;
int __attribute__((__cdecl__)) siscanf (const char *, const char *, ...) __attribute__ ((__format__ (__scanf__, 2, 3)))
                                                           ;
int __attribute__((__cdecl__)) snprintf (char *, size_t, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int __attribute__((__cdecl__)) sniprintf (char *, size_t, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
char * __attribute__((__cdecl__)) tempnam (const char *, const char *);
int __attribute__((__cdecl__)) vasiprintf (char **, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
char * __attribute__((__cdecl__)) vasniprintf (char *, size_t *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
char * __attribute__((__cdecl__)) vasnprintf (char *, size_t *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int __attribute__((__cdecl__)) vasprintf (char **, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
int __attribute__((__cdecl__)) vdiprintf (int, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
int __attribute__((__cdecl__)) vfiprintf (FILE *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
int __attribute__((__cdecl__)) vfiscanf (FILE *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 2, 0)))
                                                           ;
int __attribute__((__cdecl__)) vfscanf (FILE *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 2, 0)))
                                                           ;
int __attribute__((__cdecl__)) viprintf (const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 1, 0)))
                                                            ;
int __attribute__((__cdecl__)) viscanf (const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 1, 0)))
                                                           ;
int __attribute__((__cdecl__)) vscanf (const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 1, 0)))
                                                           ;
int __attribute__((__cdecl__)) vsiprintf (char *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
int __attribute__((__cdecl__)) vsiscanf (const char *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 2, 0)))
                                                           ;
int __attribute__((__cdecl__)) vsniprintf (char *, size_t, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int __attribute__((__cdecl__)) vsnprintf (char *, size_t, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int __attribute__((__cdecl__)) vsscanf (const char *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 2, 0)))
                                                           ;
# 313 "/usr/include/stdio.h" 3 4
FILE * __attribute__((__cdecl__)) fdopen (int, const char *);

int __attribute__((__cdecl__)) fileno (FILE *);
int __attribute__((__cdecl__)) getw (FILE *);
int __attribute__((__cdecl__)) pclose (FILE *);
FILE * __attribute__((__cdecl__)) popen (const char *, const char *);
int __attribute__((__cdecl__)) putw (int, FILE *);
void __attribute__((__cdecl__)) setbuffer (FILE *, char *, int);
int __attribute__((__cdecl__)) setlinebuf (FILE *);
int __attribute__((__cdecl__)) getc_unlocked (FILE *);
int __attribute__((__cdecl__)) getchar_unlocked (void);
void __attribute__((__cdecl__)) flockfile (FILE *);
int __attribute__((__cdecl__)) ftrylockfile (FILE *);
void __attribute__((__cdecl__)) funlockfile (FILE *);
int __attribute__((__cdecl__)) putc_unlocked (int, FILE *);
int __attribute__((__cdecl__)) putchar_unlocked (int);
# 338 "/usr/include/stdio.h" 3 4
int __attribute__((__cdecl__)) dprintf (int, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;

FILE * __attribute__((__cdecl__)) fmemopen (void *, size_t, const char *);


FILE * __attribute__((__cdecl__)) open_memstream (char **, size_t *);

int __attribute__((__cdecl__)) renameat (int, const char *, int, const char *);

int __attribute__((__cdecl__)) vdprintf (int, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;







int __attribute__((__cdecl__)) _asiprintf_r (struct _reent *, char **, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
char * __attribute__((__cdecl__)) _asniprintf_r (struct _reent *, char *, size_t *, const char *, ...) __attribute__ ((__format__ (__printf__, 4, 5)))
                                                            ;
char * __attribute__((__cdecl__)) _asnprintf_r (struct _reent *, char *, size_t *, const char *, ...) __attribute__ ((__format__ (__printf__, 4, 5)))
                                                            ;
int __attribute__((__cdecl__)) _asprintf_r (struct _reent *, char **, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int __attribute__((__cdecl__)) _diprintf_r (struct _reent *, int, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int __attribute__((__cdecl__)) _dprintf_r (struct _reent *, int, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int __attribute__((__cdecl__)) _fclose_r (struct _reent *, FILE *);
int __attribute__((__cdecl__)) _fcloseall_r (struct _reent *);
FILE * __attribute__((__cdecl__)) _fdopen_r (struct _reent *, int, const char *);
int __attribute__((__cdecl__)) _fflush_r (struct _reent *, FILE *);
int __attribute__((__cdecl__)) _fgetc_r (struct _reent *, FILE *);
char * __attribute__((__cdecl__)) _fgets_r (struct _reent *, char *, int, FILE *);




int __attribute__((__cdecl__)) _fgetpos_r (struct _reent *, FILE *, fpos_t *);
int __attribute__((__cdecl__)) _fsetpos_r (struct _reent *, FILE *, const fpos_t *);

int __attribute__((__cdecl__)) _fiprintf_r (struct _reent *, FILE *, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int __attribute__((__cdecl__)) _fiscanf_r (struct _reent *, FILE *, const char *, ...) __attribute__ ((__format__ (__scanf__, 3, 4)))
                                                           ;
FILE * __attribute__((__cdecl__)) _fmemopen_r (struct _reent *, void *, size_t, const char *);
FILE * __attribute__((__cdecl__)) _fopen_r (struct _reent *, const char *, const char *);
FILE * __attribute__((__cdecl__)) _freopen_r (struct _reent *, const char *, const char *, FILE *);
int __attribute__((__cdecl__)) _fprintf_r (struct _reent *, FILE *, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int __attribute__((__cdecl__)) _fpurge_r (struct _reent *, FILE *);
int __attribute__((__cdecl__)) _fputc_r (struct _reent *, int, FILE *);
int __attribute__((__cdecl__)) _fputs_r (struct _reent *, const char *, FILE *);
size_t __attribute__((__cdecl__)) _fread_r (struct _reent *, void *, size_t _size, size_t _n, FILE *);
int __attribute__((__cdecl__)) _fscanf_r (struct _reent *, FILE *, const char *, ...) __attribute__ ((__format__ (__scanf__, 3, 4)))
                                                           ;
int __attribute__((__cdecl__)) _fseek_r (struct _reent *, FILE *, long, int);
int __attribute__((__cdecl__)) _fseeko_r (struct _reent *, FILE *, _off_t, int);
long __attribute__((__cdecl__)) _ftell_r (struct _reent *, FILE *);
_off_t __attribute__((__cdecl__)) _ftello_r (struct _reent *, FILE *);
void __attribute__((__cdecl__)) _rewind_r (struct _reent *, FILE *);
size_t __attribute__((__cdecl__)) _fwrite_r (struct _reent *, const void * , size_t _size, size_t _n, FILE *);
int __attribute__((__cdecl__)) _getc_r (struct _reent *, FILE *);
int __attribute__((__cdecl__)) _getc_unlocked_r (struct _reent *, FILE *);
int __attribute__((__cdecl__)) _getchar_r (struct _reent *);
int __attribute__((__cdecl__)) _getchar_unlocked_r (struct _reent *);
char * __attribute__((__cdecl__)) _gets_r (struct _reent *, char *);
int __attribute__((__cdecl__)) _iprintf_r (struct _reent *, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;
int __attribute__((__cdecl__)) _iscanf_r (struct _reent *, const char *, ...) __attribute__ ((__format__ (__scanf__, 2, 3)))
                                                           ;
FILE * __attribute__((__cdecl__)) _open_memstream_r (struct _reent *, char **, size_t *);
void __attribute__((__cdecl__)) _perror_r (struct _reent *, const char *);
int __attribute__((__cdecl__)) _printf_r (struct _reent *, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;
int __attribute__((__cdecl__)) _putc_r (struct _reent *, int, FILE *);
int __attribute__((__cdecl__)) _putc_unlocked_r (struct _reent *, int, FILE *);
int __attribute__((__cdecl__)) _putchar_unlocked_r (struct _reent *, int);
int __attribute__((__cdecl__)) _putchar_r (struct _reent *, int);
int __attribute__((__cdecl__)) _puts_r (struct _reent *, const char *);
int __attribute__((__cdecl__)) _remove_r (struct _reent *, const char *);
int __attribute__((__cdecl__)) _rename_r (struct _reent *, const char *_old, const char *_new)
                                          ;
int __attribute__((__cdecl__)) _scanf_r (struct _reent *, const char *, ...) __attribute__ ((__format__ (__scanf__, 2, 3)))
                                                           ;
int __attribute__((__cdecl__)) _siprintf_r (struct _reent *, char *, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int __attribute__((__cdecl__)) _siscanf_r (struct _reent *, const char *, const char *, ...) __attribute__ ((__format__ (__scanf__, 3, 4)))
                                                           ;
int __attribute__((__cdecl__)) _sniprintf_r (struct _reent *, char *, size_t, const char *, ...) __attribute__ ((__format__ (__printf__, 4, 5)))
                                                            ;
int __attribute__((__cdecl__)) _snprintf_r (struct _reent *, char *, size_t, const char *, ...) __attribute__ ((__format__ (__printf__, 4, 5)))
                                                            ;
int __attribute__((__cdecl__)) _sprintf_r (struct _reent *, char *, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int __attribute__((__cdecl__)) _sscanf_r (struct _reent *, const char *, const char *, ...) __attribute__ ((__format__ (__scanf__, 3, 4)))
                                                           ;
char * __attribute__((__cdecl__)) _tempnam_r (struct _reent *, const char *, const char *);
FILE * __attribute__((__cdecl__)) _tmpfile_r (struct _reent *);
char * __attribute__((__cdecl__)) _tmpnam_r (struct _reent *, char *);
int __attribute__((__cdecl__)) _ungetc_r (struct _reent *, int, FILE *);
int __attribute__((__cdecl__)) _vasiprintf_r (struct _reent *, char **, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
char * __attribute__((__cdecl__)) _vasniprintf_r (struct _reent*, char *, size_t *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 4, 0)))
                                                            ;
char * __attribute__((__cdecl__)) _vasnprintf_r (struct _reent*, char *, size_t *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 4, 0)))
                                                            ;
int __attribute__((__cdecl__)) _vasprintf_r (struct _reent *, char **, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int __attribute__((__cdecl__)) _vdiprintf_r (struct _reent *, int, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int __attribute__((__cdecl__)) _vdprintf_r (struct _reent *, int, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int __attribute__((__cdecl__)) _vfiprintf_r (struct _reent *, FILE *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int __attribute__((__cdecl__)) _vfiscanf_r (struct _reent *, FILE *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 3, 0)))
                                                           ;
int __attribute__((__cdecl__)) _vfprintf_r (struct _reent *, FILE *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int __attribute__((__cdecl__)) _vfscanf_r (struct _reent *, FILE *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 3, 0)))
                                                           ;
int __attribute__((__cdecl__)) _viprintf_r (struct _reent *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
int __attribute__((__cdecl__)) _viscanf_r (struct _reent *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 2, 0)))
                                                           ;
int __attribute__((__cdecl__)) _vprintf_r (struct _reent *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
int __attribute__((__cdecl__)) _vscanf_r (struct _reent *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 2, 0)))
                                                           ;
int __attribute__((__cdecl__)) _vsiprintf_r (struct _reent *, char *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int __attribute__((__cdecl__)) _vsiscanf_r (struct _reent *, const char *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 3, 0)))
                                                           ;
int __attribute__((__cdecl__)) _vsniprintf_r (struct _reent *, char *, size_t, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 4, 0)))
                                                            ;
int __attribute__((__cdecl__)) _vsnprintf_r (struct _reent *, char *, size_t, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 4, 0)))
                                                            ;
int __attribute__((__cdecl__)) _vsprintf_r (struct _reent *, char *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int __attribute__((__cdecl__)) _vsscanf_r (struct _reent *, const char *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 3, 0)))
                                                           ;



int __attribute__((__cdecl__)) fpurge (FILE *);
ssize_t __attribute__((__cdecl__)) __getdelim (char **, size_t *, int, FILE *);
ssize_t __attribute__((__cdecl__)) __getline (char **, size_t *, FILE *);
# 515 "/usr/include/stdio.h" 3 4
int __attribute__((__cdecl__)) __srget_r (struct _reent *, FILE *);
int __attribute__((__cdecl__)) __swbuf_r (struct _reent *, int, FILE *);







FILE *__attribute__((__cdecl__)) funopen (const void * __cookie, int (*__readfn)(void * __c, char *__buf, int __n), int (*__writefn)(void * __c, const char *__buf, int __n), _fpos64_t (*__seekfn)(void * __c, _fpos64_t __off, int __whence), int (*__closefn)(void * __c))



                              ;
FILE *__attribute__((__cdecl__)) _funopen_r (struct _reent *, const void * __cookie, int (*__readfn)(void * __c, char *__buf, int __n), int (*__writefn)(void * __c, const char *__buf, int __n), _fpos64_t (*__seekfn)(void * __c, _fpos64_t __off, int __whence), int (*__closefn)(void * __c))



                              ;
# 552 "/usr/include/stdio.h" 3 4
typedef ssize_t cookie_read_function_t(void *__cookie, char *__buf, size_t __n);
typedef ssize_t cookie_write_function_t(void *__cookie, const char *__buf,
     size_t __n);

typedef int cookie_seek_function_t(void *__cookie, _off64_t *__off,
       int __whence);



typedef int cookie_close_function_t(void *__cookie);
typedef struct
{


  cookie_read_function_t *read;
  cookie_write_function_t *write;
  cookie_seek_function_t *seek;
  cookie_close_function_t *close;
} cookie_io_functions_t;
FILE *__attribute__((__cdecl__)) fopencookie (void *__cookie, const char *__mode, cookie_io_functions_t __functions)
                                                         ;
FILE *__attribute__((__cdecl__)) _fopencookie_r (struct _reent *, void *__cookie, const char *__mode, cookie_io_functions_t __functions)
                                                         ;
# 595 "/usr/include/stdio.h" 3 4
extern __inline__ __attribute__ ((__always_inline__)) int __sgetc_r(struct _reent *__ptr, FILE *__p);

extern __inline__ __attribute__ ((__always_inline__)) int __sgetc_r(struct _reent *__ptr, FILE *__p)
  {
    int __c = (--(__p)->_r < 0 ? __srget_r(__ptr, __p) : (int)(*(__p)->_p++));
    if ((__p->_flags & 0x4000) && (__c == '\r'))
      {
      int __c2 = (--(__p)->_r < 0 ? __srget_r(__ptr, __p) : (int)(*(__p)->_p++));
      if (__c2 == '\n')
        __c = __c2;
      else
        ungetc(__c2, __p);
      }
    return __c;
  }
# 683 "/usr/include/stdio.h" 3 4

# 25 "args.c" 2
# 1 "/usr/lib/gcc/i686-pc-cygwin/4.5.3/include/stdarg.h" 1 3 4
# 102 "/usr/lib/gcc/i686-pc-cygwin/4.5.3/include/stdarg.h" 3 4
typedef __gnuc_va_list va_list;
# 26 "args.c" 2
# 1 "/usr/include/libgen.h" 1 3 4
# 16 "/usr/include/libgen.h" 3 4


extern char *basename (char *path);
extern char *dirname (char *path);


# 27 "args.c" 2
# 1 "/usr/include/getopt.h" 1 3 4
# 45 "/usr/include/getopt.h" 3 4
extern int __attribute__((dllimport)) opterr;
extern int __attribute__((dllimport)) optind;
extern int __attribute__((dllimport)) optopt;
extern int __attribute__((dllimport)) optreset;
extern char __attribute__((dllimport)) *optarg;


int getopt (int, char * const *, const char *);
# 68 "/usr/include/getopt.h" 3 4
struct option {
 const char *name;
 int has_arg;
 int *flag;
 int val;
};

int getopt_long (int, char *const *, const char *, const struct option *, int *);
int getopt_long_only (int, char *const *, const char *, const struct option *, int *);
# 28 "args.c" 2

# 1 "args.h" 1
# 25 "args.h"
# 1 "types.h" 1
# 25 "types.h"
# 1 "str_list.h" 1
# 25 "str_list.h"
struct wb_str_list {
 char *str;
 struct wb_str_list *next;
};

void wb_list_free(struct wb_str_list *list);
struct wb_str_list *wb_list_append(struct wb_str_list *list, const char *str);
struct wb_str_list *wb_list_prepend(struct wb_str_list *list, const char *str);
# 26 "types.h" 2
# 88 "types.h"
struct curl_response {
 size_t size;
 char *data;
};

struct options {
 char *username, *password;
 char *dir;
 char *query;
 unsigned char toplist;
 int color;
 int images, images_per_page;
 unsigned char flags, purity, boards;
 int res_x, res_y;
 unsigned char res_opt;
 float aspect_ratio;
 unsigned char sort_by, sort_order;
};
# 26 "args.h" 2

void wb_parse_args(int argc, char *argv[], struct options *options);
# 30 "args.c" 2
# 1 "error.h" 1
# 27 "error.h"
void wb_verror(const char *format, va_list args);
void wb_error(const char *format, ...);
void wb_verror_no_prefix(const char *format, va_list args);
void wb_error_no_prefix(const char *format, ...);
# 31 "args.c" 2







static const char *WB_TOPLIST_INTERVALS[] = {
 "0", "1d", "3d", "1w", "2w", "1m", "2m", "3m"
};
static const unsigned char WB_TOPLIST_INTERVAL_IDS[] = {
 8, 1, 2,
 3, 4, 5, 6,
 7
};




static const char *WB_SORT_TYPES_SHORT[] = {
 "r", "v", "d", "f"
};
static const char *WB_SORT_TYPES_LONG[] = {
 "relevance", "views", "date", "favorites"
};
static const unsigned char WB_SORT_TYPE_IDS[] = {
 1, 2, 3, 4
};







static char *APP_INVOKE_NAME = "wb";

static const char *ABOUT = "wb -- A wallbase.cc image downloader";
static const char *BUG_ADDRESS = "<mntnorv+bugs@gmail.com>";

static const char *LONG_HELP = "  -a, --aspect=ASPECT        Search for images with this aspect ratio\n  -A, --anime, --manga       Search in the Anime / Manga board\n  -c, --color=COLOR          Search for images containing this color\n  -d, --download-dir=DIR     Directory to download images to (defaults to\n                             current directory)\n  -G, --general              Search in the Wallpapers / General board\n  -H, --high-res             Search in the High Resolution board\n  -K, --sketchy              Search for sketchy images\n  -n, --images=COUNT         Number of images to download\n  -N, --nsfw                 Search for NSFW images (requires wallbase.cc login\n                             information)\n  -p, --password=PASSWORD    wallbase.cc password, required for NSFW content\n      --print-only           Print image URLs to stdout (do not download\n                             images)\n  -q, --query=STRING         Search for images related to this string\n  -r, --resolution=RES       Search for images with at least or exactly this\n                             resolution\n  -s, --sort=SORT            Specify the sort order\n  -S, --sfw                  Search for SFW images\n  -t, --toplist=INTERVAL     Get the top images in the specified time interval\n  -u, --username=USERNAME    wallbase.cc username, required for NSFW content\n  -h, --help                 Give this help list\n      --usage                Give a short usage message\n  -V, --version              Print program version\n\nMandatory or optional arguments to long options are also mandatory or optional\nfor any corresponding short options.";
# 104 "args.c"
static const char *FORMAT_SHORT_USAGE = "Usage: %s [OPTION...]";
static const char *FORMAT_LONG_USAGE = "Usage: %s [-AGHKNShV] [-a ASPECT] [-c COLOR] [-d DIR] [-n COUNT]\n            [-p PASSWORD] [-q STRING] [-r RES] [-s SORT] [-t INTERVAL]\n            [-u USERNAME]\n";




static const char *FORMAT_SHORT_HELP = "Try '%s --help' or '%s --usage' for more information.";

static const char *FORMAT_VERSION = "wb, version %s\nCopyright (C) 2013 Mantas Norvaiša\nLicense GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\nThis is free software: you are free to change and redistribute it.\nThere is NO WARRANTY, to the extent permitted by law.\n";
# 122 "args.c"
static const char *GETOPT_SHORT_OPTIONS = "a:c:d:n:p:q:r:s:t:u:AGHKNShV";
static struct option GETOPT_LONG_OPTIONS[] = {

 {"aspect", 1, 0, 'a'},
 {"color", 1, 0, 'c'},
 {"download-dir", 1, 0, 'd'},
 {"images", 1, 0, 'n'},
 {"password", 1, 0, 'p'},
 {"query", 1, 0, 'q'},
 {"resolution", 1, 0, 'r'},
 {"sort", 1, 0, 's'},
 {"toplist", 1, 0, 't'},
 {"username", 1, 0, 'u'},


 {"anime", 0, 0, 'A'},
 {"manga", 0, 0, 'A'},
 {"general", 0, 0, 'G'},
 {"high-res", 0, 0, 'H'},
 {"sketchy", 0, 0, 'K'},
 {"nsfw", 0, 0, 'N'},
 {"sfw", 0, 0, 'S'},
 {"help", 0, 0, 'h'},
 {"version", 0, 0, 'V'},


 {"usage", 0, 0, 300},
 {"print-only", 0, 0, 301},
 {0}
};
# 163 "args.c"
void
invalid_arg_error(char *name, char *arg) {
 wb_error("invalid %s -- %s", name, arg);
 wb_error_no_prefix(FORMAT_SHORT_HELP, APP_INVOKE_NAME, APP_INVOKE_NAME);
}




void
print_full_help() {
 printf(FORMAT_SHORT_USAGE, APP_INVOKE_NAME);
 printf("\n%s\n\n%s\n\n", ABOUT, LONG_HELP);
 printf("Report bugs to %s\n", BUG_ADDRESS);
}




void
print_full_usage() {
 printf(FORMAT_LONG_USAGE, APP_INVOKE_NAME);
}




void
print_version() {
 printf(FORMAT_VERSION, VERSION);
}
# 203 "args.c"
int
find_in_array(const char *str, const char *array[], int arr_size) {
 int i;
 for (i = 0; i < arr_size; i++) {
  if (strcmp(str, array[i]) == 0) {
   return i;
  }
 }
 return -1;
}
# 222 "args.c"
int
parse_aspect_ratio(char *arg, struct options *options) {
 int num;
 char *temp_arg, *num_end;

 temp_arg = arg;


 num = strtol(temp_arg, &num_end, 10);
 if (num <= 0) {
  return -1;
 } else {
  options->aspect_ratio = num;
  temp_arg = num_end;
 }


 if (temp_arg[0] != ':') {
  return -1;
 } else {
  temp_arg++;
 }


 num = strtol(temp_arg, &num_end, 10);
 if (temp_arg + strlen(temp_arg) != num_end || num <= 0) {
  return -1;
 } else {
  options->aspect_ratio = options->aspect_ratio / num;
 }

 return 0;
}
# 265 "args.c"
int
parse_color(char *arg, struct options *options) {
 int num;
 char *num_end;

 num = strtol(arg, &num_end, 16);
 if (arg + strlen(arg) != num_end || num < 0 || num > 0xFFFFFF) {
  return -1;
 } else {
  options->color = num;
 }

 return 0;
}
# 288 "args.c"
int
parse_image_number(char *arg, struct options *options) {
 int num;
 char *num_end;

 num = strtol(arg, &num_end, 10);
 if (arg + strlen(arg) != num_end || num <= 0) {
  return -1;
 } else {
  options->images = num;
 }

 return 0;
}
# 311 "args.c"
int
parse_resolution(char *arg, struct options *options) {
 int num;
 char *temp_arg, *num_end;

 temp_arg = arg;


 if (temp_arg[0] == '=') {
  options->res_opt = 0;
  temp_arg++;
 }


 num = strtol(temp_arg, &num_end, 10);
 if (num <= 0) {
  return -1;
 } else {
  options->res_x = num;
  temp_arg = num_end;
 }


 if (temp_arg[0] != 'x') {
  return -1;
 } else {
  temp_arg++;
 }


 num = strtol(temp_arg, &num_end, 10);
 if (temp_arg + strlen(temp_arg) != num_end || num <= 0) {
  return -1;
 } else {
  options->res_y = num;
 }

 return 0;
}
# 359 "args.c"
int
parse_sort(char *arg, struct options *options) {
 int index;
 char *temp_arg;

 temp_arg = arg;


 if (temp_arg[0] == '+') {
  options->sort_order = 0;
  temp_arg++;
 } else if (temp_arg[0] == '-') {
  options->sort_order = 1;
  temp_arg++;
 }


 index = find_in_array(temp_arg, WB_SORT_TYPES_SHORT, (sizeof(WB_SORT_TYPE_IDS) / sizeof(WB_SORT_TYPE_IDS[0])));
 if (index != -1) {
  options->sort_by = WB_SORT_TYPE_IDS[index];
  return 0;
 }


 index = find_in_array(temp_arg, WB_SORT_TYPES_LONG, (sizeof(WB_SORT_TYPE_IDS) / sizeof(WB_SORT_TYPE_IDS[0])));
 if (index != -1) {
  options->sort_by = WB_SORT_TYPE_IDS[index];
  return 0;
 }

 return -1;
}
# 399 "args.c"
int
parse_toplist_interval(char *arg, struct options *options) {
 int index;


 index = find_in_array(arg, WB_TOPLIST_INTERVALS, (sizeof(WB_TOPLIST_INTERVALS) / sizeof(WB_TOPLIST_INTERVALS[0])));
 if (index != -1) {
  options->toplist = WB_TOPLIST_INTERVAL_IDS[index];
  return 0;
 }

 return -1;
}
# 422 "args.c"
int
parse_opt(int key, char *arg, struct options *options) {
 switch(key) {



  case 'a':
   if (parse_aspect_ratio(arg, options) == -1) {
    invalid_arg_error("aspect ratio", arg);
    return -1;
   }
   break;
  case 'c':
   if (parse_color(arg, options) == -1) {
    invalid_arg_error("color", arg);
    return -1;
   }
   break;
  case 'd':
   options->dir = arg;
   break;
  case 'n':
   if (parse_image_number(arg, options) == -1) {
    invalid_arg_error("number of images", arg);
    return -1;
   }
   break;
  case 'p':
   options->password = arg;
   break;
  case 'q':
   options->query = arg;
   break;
  case 'r':
   if (parse_resolution(arg, options) == -1) {
    invalid_arg_error("resolution", arg);
    return -1;
   }
   break;
  case 's':
   if (parse_sort(arg, options) == -1) {
    invalid_arg_error("sort type", arg);
    return -1;
   }
   break;
  case 't':
   if (parse_toplist_interval(arg, options) == -1) {
    invalid_arg_error("toplist interval", arg);
    return -1;
   }
   break;
  case 'u':
   options->username = arg;
   break;



  case 'S':
   options->purity |= 0x01;
   break;
  case 'K':
   options->purity |= 0x02;
   break;
  case 'N':
   options->purity |= 0x04;
   break;
  case 'G':
   options->boards |= 0x01;
   break;
  case 'A':
   options->boards |= 0x02;
   break;
  case 'H':
   options->boards |= 0x04;
   break;
  case 301:
   options->flags |= 0x01;
   break;



  case 'h':
   print_full_help();
   return -1;
  case 'V':
   print_version();
   return -1;
  case 300:
   print_full_usage();
   return -1;
  case '?':
   wb_error_no_prefix(FORMAT_SHORT_HELP, APP_INVOKE_NAME, APP_INVOKE_NAME);
   return -1;
  default:
   return -1;
 }

 return 0;
}
# 531 "args.c"
void
wb_parse_args(int argc, char *argv[], struct options *options) {
 int key, option_index;


 APP_INVOKE_NAME = basename(argv[0]);


 while ((key = getopt_long(argc, argv, GETOPT_SHORT_OPTIONS,
  GETOPT_LONG_OPTIONS, &option_index)) != -1) {

  if (parse_opt(key, optarg, options) != 0) {
   exit(1);
  }
 }
}
