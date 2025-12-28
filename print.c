/*	@(#)print.c	1.5	*/
/*
 * UNIX shell
 *
 * Bell Telephone Laboratories
 *
 */

#include	"defs.h"
#include	<sys/param.h>
#ifdef		CRAY
#include	<sys/machd.h>
#else
#ifndef	HZ
#define	HZ	60
#endif
#endif

#define		BUFLEN		256

static char	buffer[BUFLEN];
static int	index = 0;
char		numbuf[12];

extern void	prc_buff();
extern void	prs_buff();
extern void	prs_2buff();
extern void	prn_buff();
extern void	prs_cntl();
extern void	prn_buff();

/*
 * printing and io conversion
 */
void
prp()
{
	if (cmdadr)
	{
		prs_cntl(cmdadr);
		flushb();
		prs(colon);
	}
}

void
prs(char *as)
{
	register char	*s;

	if ((s = as) && length(s) > 1)
		write(output, s, length(s) - 1);
}

void
prc(int c)
{
	char realc;
	realc = c;
	if (c)
		write(output, &realc, 1);
}

void
prt(long t)
{
	register int hr, min, sec;

	t += HZ / 2;
	t /= HZ;
	sec = t % HZ;
	t /= HZ;
	min = t % HZ;

	if (hr = t / HZ)
	{
		prn_buff(hr);
		prc_buff('h');
	}

	prn_buff(min);
	prc_buff('m');
	prn_buff(sec);
	prc_buff('s');
}

void
prn(int n)
{
	itos(n);

	prs(numbuf);
}

void
itos(int n)
{
	register char *abuf = numbuf;
	register unsigned int a, i;

	if (n < 0)
	{
		*abuf++ = '-';
		a = -n;
	}
	else
		a = n;

	i = 1;
	while (i <= a / 10 && i < 1000000000)
		i *= 10;

	while (i > 0)
	{
		*abuf++ = (a / i) % 10 + '0';
		i /= 10;
	}

	*abuf = 0;
}

int
stoi(char *icp)
{
	register char	*cp = icp;
	register int	r = 0;
	register char	c;

	while ((c = *cp, digit(c)) && c && r >= 0)
	{
		r = r * 10 + c - '0';
		cp++;
	}
	if (r < 0 || cp == icp)
		failed(icp, badnum, 0);
	else
		return(r);
}

void
prl(long n)
{
	int i;

	i = 11;
	while (n > 0 && --i >= 0)
	{
		numbuf[i] = n % 10 + '0';
		n /= 10;
	}
	numbuf[11] = '\0';
	prs_buff(&numbuf[i]);
}

void
flushb()
{
	if (index)
	{
		buffer[index] = '\0';
		write(1, buffer, length(buffer) - 1);
		index = 0;
	}
}

void
prc_buff(c)
	char c;
{
	if (c)
	{
		if (index + 1 >= BUFLEN)
			flushb();

		buffer[index++] = c;
	}
	else
	{
		flushb();
		write(1, &c, 1);
	}
}

/* rob */
void
prs_2buff(s, t)
	char *s, *t;
{
	prs_buff(s);
	prs_buff(t);
}

void
prs_buff(s)
	char *s;
{
	register int len = length(s) - 1;

	if (index + len >= BUFLEN)
		flushb();

	if (len >= BUFLEN)
		write(1, s, len);
	else
	{
		movstr(s, &buffer[index]);
		index += len;
	}
}


void
clear_buff()
{
	index = 0;
}


void
prs_cntl(char *s)
{
	register char c;

	while (*s != '\0') 
	{
		c = (*s & 0177) ;
		
		/* translate a control character into a printable sequence */

		if (c < '\040') 
		{	/* assumes ASCII char */
			prc_buff('^');
			prc_buff(c + 0100);	/* assumes ASCII char */
		}
		else if (c == 0177) 
		{	/* '\0177' does not work */
			prc_buff('^');
			prc_buff('?');
		}
		else 
		{	/* printable character */
			prc_buff(c);
		}

		++s;
	}
}


void
prn_buff(n)
	int	n;
{
	itos(n);

	prs_buff(numbuf);
}
char *
quotedstring(s)
	register char *s;
{
	register char *t = s;
	register char *outp=locstak();
	register int quoting=0;
	while(*t)
		if(any(*t++, " \t\n\\\"'`;&|$*[](){}<>")){
			while(*s){
				if(*s == '\''){
					if(quoting)
						pushstak(*s);	/* end quote */
					pushstak('\\');
					quoting=0;
				}else if(!quoting){
					pushstak('\'');
					quoting=1;
				}
				pushstak(*s++);
			}
			if(quoting)
				pushstak('\'');
			break;
		}
	do
		pushstak(*s);
	while(*s++);
	staktop=stakbot;
	return outp;
}
