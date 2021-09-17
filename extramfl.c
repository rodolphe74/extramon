#include <cmoc.h>
#include "extramfl.h"

char static_buffer[16];
struct float_struct static_float_temp;

void print_float(struct float_struct *fs)
{
	printf("(%02x %02x %02x %02x %02x - %02x)%c%c", fs->exp, fs->ho, fs->mo, fs->lo, fs->sgn, fs->valtyp, 10, 13);
}

void init_extra()
{
	asm {
		LDB #RESETW
		JSR EXTRA
	}
}

void fin(char *float_value, struct float_struct *fs)
{
	asm {
	LDA #4
	STA VALTYP

	LDY float_value
	LDB #FIN
	JSR EXTRA
	}
	
	fs->exp = *((unsigned char *) FACEXP);
	fs->ho = *((unsigned char *) FACHO);
	fs->mo = *((unsigned char *) FACMO);
	fs->lo = *((unsigned char *) FACLO);
	fs->sgn = *((unsigned char *) FACSGN);
	fs->valtyp = *((unsigned char *) VALTYP);
}

char *pufout(struct float_struct *fs)
{
	*((unsigned char *) FACEXP) = fs->exp;
	*((unsigned char *) FACHO) = fs->ho;
	*((unsigned char *) FACMO) = fs->mo;
	*((unsigned char *) FACLO) = fs->lo;
	*((unsigned char *) FACSGN) = fs->sgn;
	
	char *pbuffer = static_buffer;
	
	asm {
	LDA #4
	STA VALTYP
	LDA #6
	STA DPWID
	LDA #2
	STA FLDWID
	LDA #129
	STA PUMASK
	LDY :pbuffer
	LDB #PUFOUT
	JSR EXTRA
	}
	
	unsigned int start = *((unsigned int *) FACMO);
	char *pstart = (char *) start;
	//~ printf("FACMO:%02x%c%c", pstart, 10, 13);
	return pstart;

	// DEBUG
	//~ while(*pstart > 0) {
		//~ printf(">%02x ", *pstart);
		//~ result[count] = *pstart;
		//~ pstart++;
	//~ }
}

unsigned int to_unsigned_int(struct float_struct *fs)
{
	
	*((unsigned char *) FACEXP) = fs->exp;
	*((unsigned char *) FACHO) = fs->ho;
	*((unsigned char *) FACMO) = fs->mo;
	*((unsigned char *) FACLO) = fs->lo;
	*((unsigned char *) FACSGN) = fs->sgn;
	
	char *pbuffer = static_buffer;
	
	asm {
	LDA #4
	STA VALTYP
	LDA #0
	STA DPWID
	LDA #6
	STA FLDWID
	LDA #128
	STA PUMASK
	LDY :pbuffer
	LDB #PUFOUT
	JSR EXTRA
	}
	
	unsigned int start = *((unsigned int *) FACMO);
	char *pstart = (char *) start;
	
	int size = strlen(pstart) - 1;
	int mul = 1;
	
	unsigned int result = 0;
	for (int i = size; i >= 1; i--) {
		result += (*(pstart + i) - '0') * mul;
		if (result >= 65535) return 65535;
		mul *= 10;
	}
	
	return result;
}

unsigned int to_int(struct float_struct *fs)
{
	
	*((unsigned char *) FACEXP) = fs->exp;
	*((unsigned char *) FACHO) = fs->ho;
	*((unsigned char *) FACMO) = fs->mo;
	*((unsigned char *) FACLO) = fs->lo;
	*((unsigned char *) FACSGN) = fs->sgn;
	
	char *pbuffer = static_buffer;
	
	asm {
	LDA #4
	STA VALTYP
	LDA #0
	STA DPWID
	LDA #6
	STA FLDWID
	LDA #128
	STA PUMASK
	LDY :pbuffer
	LDB #PUFOUT
	JSR EXTRA
	}
	
	unsigned int start = *((unsigned int *) FACMO);
	char *pstart = (char *) start;
	
	int size = strlen(pstart) - 1;
	int mul = 1;
	
	unsigned int result = 0;
	for (int i = size; i >= 1; i--) {
		result += (*(pstart + i) - '0') * mul;
		if (result >= 32767) return 32767;
		mul *= 10;
	}
	
	if (*(pstart) == '-') result = (0-result);
	
	return result;
}

void unary_op(struct float_struct *fac, struct float_struct *result, unsigned char op)
{
	*((unsigned char *) FACEXP) = fac->exp;
	*((unsigned char *) FACHO) = fac->ho;
	*((unsigned char *) FACMO) = fac->mo;
	*((unsigned char *) FACLO) = fac->lo;
	*((unsigned char *) FACSGN) = fac->sgn;
	
	asm {
	LDA #4
	STA VALTYP
	LDB :op
	JSR EXTRA
	}
	
	result->exp = *((unsigned char *) FACEXP);
	result->ho = *((unsigned char *) FACHO);
	result->mo = *((unsigned char *) FACMO);
	result->lo = *((unsigned char *) FACLO);
	result->sgn = *((unsigned char *) FACSGN);
	result->valtyp = *((unsigned char *) VALTYP);
}

void binary_op(struct float_struct *fac, struct float_struct *arg, struct float_struct *result, unsigned char op)
{
	*((unsigned char *) FACEXP) = fac->exp;
	*((unsigned char *) FACHO) = fac->ho;
	*((unsigned char *) FACMO) = fac->mo;
	*((unsigned char *) FACLO) = fac->lo;
	*((unsigned char *) FACSGN) = fac->sgn;
	
	*((unsigned char *) ARGEXP) = arg->exp;
	*((unsigned char *) ARGHO) = arg->ho;
	*((unsigned char *) ARGMO) = arg->mo;
	*((unsigned char *) ARGLO) = arg->lo;
	*((unsigned char *) ARGSGN) = arg->sgn;
	
	asm {
	LDA #4
	STA VALTYP
	LDB :op
	JSR EXTRA
	}
	
	result->exp = *((unsigned char *) FACEXP);
	result->ho = *((unsigned char *) FACHO);
	result->mo = *((unsigned char *) FACMO);
	result->lo = *((unsigned char *) FACLO);
	result->sgn = *((unsigned char *) FACSGN);
	result->valtyp = *((unsigned char *) VALTYP);
}


char cmp(struct float_struct *fac, struct float_struct *arg)
{
	// neg -> fac < arg
	// 0   -> fac = arg
	// pos -> fac > arg
	binary_op(fac, arg, &static_float_temp, SUBGO);	/* ARG - FAC */	
		
	if (static_float_temp.exp == 0 && static_float_temp.ho == 0
		&& static_float_temp.mo == 0 && static_float_temp.lo == 0
		&& static_float_temp.sgn == 0) {
		return 0;
	} else if (static_float_temp.sgn == 0) {
		// arg > fac
		return -1;
	} else /* if (static_float_temp.sgn == 255) */ {
		// fac -> arg
		return 1;
	}
}
