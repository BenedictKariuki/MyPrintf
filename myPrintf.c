/* ===========================================================================
 * File		: my_printf.c
 * Description	: My own implementation of printf() C standard library function
 *
 * Author	: Benedict K. Mutindi
 * Created	: 2026-07-30
 * Version	: 0.1.0
 *
 * Compiler	: GCC
 * Platform	: Linux (x86, 32-bit)
 * ========================================================================== */


#include <unistd.h>

/* write a char to the stdout */
#define putchar(x) write(1, chardup(x), 1)

/* bitwise masks to track state */
#define _WAIT_CHAR 0x1 // 00 01
#define _WAIT_FMT 0x2 // 00 10

typedef unsigned char State;

/* from char to null-terminated string */
char* chardup(char c){
	static char buf[2];
	char* p = buf;
	*p++ = c;
	*p = '\0';
	return buf;
}

/* find length of a string */
unsigned int strlen(char* str){
	char* p;
	unsigned int n;
	for(p=str, n=0; *p; p++,n++);
	return n;
}

/* write a string to the stdout */
int puts(char* str){
	unsigned int n = strlen(str);
	if(n<1) return -1;
	return write(1, str, n);	
}

/* convert an integer to a string */
void itoa(unsigned char* digits, int i){
	int n = i, x = 0;
	if(i<0){
	   n = -n;
	}
	for(n, x; n!=0; x++,n/=10){
	   *(digits + x) = (unsigned char)((n % 10) + 0x30);
	}
	if(i<0){
	  *(digits + x) = '-';
	  x++;
	}
	*(digits+x) = '\0';

	int l_ptr = 0, r_ptr = strlen(digits) - 1, tmp;
	while(l_ptr < r_ptr){
	  tmp = *(digits + l_ptr);
	  *(digits + l_ptr) = *(digits + r_ptr);
	  *(digits + r_ptr) = tmp;
	  l_ptr++;
	  r_ptr--;
	}
}

/* macro to read the first address for args passed in 32-bit systems */
#ifndef x86ARGS
#define x86ARGS
#define Args(arg) \
	unsigned int _x; \
	asm("mov %%ebp, %0":"=r"(_x)); \
	_x += 8; \
	arg = (unsigned int*)_x;
#endif

int my_printf(const char* fmt, ...){
	unsigned int* p;	
	const char* fmt_str;
	State s;
	Args(p);
	
	s = _WAIT_CHAR;
	fmt_str = fmt;

	// parse format string
	while(*fmt_str){
	  if(s & _WAIT_CHAR){
	    switch(*fmt_str){
	      case '%':
		s = _WAIT_FMT;
		break;
	      default:
		putchar(*fmt_str);
	    }
	  }
  	  else if(s & _WAIT_FMT){
            switch(*fmt_str){
	      case '%':
		putchar(*fmt_str);
		s = _WAIT_CHAR;
		break;
	      case 's':
		 p++;
		 puts((unsigned char*)*p);
		 s = _WAIT_CHAR;
		 break;
	      case 'c':
		 p++;
		 putchar((unsigned char)*p);
 		 s = _WAIT_CHAR;
		 break;
	      case 'd':
		 p++;
		 unsigned char d[12];
		 itoa(d, *p);
		 puts(d);
		 s = _WAIT_CHAR;
		 break;
	      default:
		 s = _WAIT_CHAR;
		 p++;
		 break;
	    }
	  }	  
	fmt_str++;	
	}
	return 0;
}

int main(){
	
	my_printf("Name: %s Age: %d Grade: %c\n", "Benedict", -8, 'A');

	return 0;
}
