/*	@(#)error.c	1.4	*/
/*
 * UNIX shell
 *
 * Bell Telephone Laboratories
 *
 */

#include	"defs.h"
#include	<errno.h>
#include	<string.h>

/* ========	error handling	======== */

void
failed(char *s1, char *s2, int per)
{
	prp();
	flushb();
	prs_cntl(s1);
	flushb();
	if (s2)
	{
		prs(colon);
		prs(s2);
	}
	if (per && errno != 0)
	{
		prs(colon);
		prs(strerror(errno));
	}
	newline();
	exitsh(ERROR);
}

void
error(char *s)
{
	failed(s, NIL, 0);
}

void
exitsh(int xno)
{
	/*
	 * Arrive here from `FATAL' errors
	 *  a) exit command,
	 *  b) default trap,
	 *  c) fault with no trap set.
	 *
	 * Action is to return to command level or exit.
	 */
	exitval = xno;
	flags |= eflag;
	if ((flags & (forked | errflg | ttyflg)) != ttyflg)
		done(0);
	else
	{
		clearup();
		restore(0);
		clear_buff();
		execbrk = breakcnt = funcnt = 0;
		longjmp(errshell, 1);
	}
}

void
done(int sig)
{
	register char	*t;

	if (t = trapcom[0])
	{
		trapcom[0] = 0;
		execexp(t, 0);
		shfree(t);
	}
	else
		chktrap();

	rmtemp(0);
	rmfunctmp();

#ifdef ACCT
	doacct();
#endif
	exit(exitval);
}

void
rmtemp(void *base)
{
	while (iotemp > (struct ionod *)base)
	{
		unlink(iotemp->ioname);
		shfree(iotemp->iolink);
		iotemp = iotemp->iolst;
	}
}

void
rmfunctmp()
{
	while (fiotemp)
	{
		unlink(fiotemp->ioname);
		fiotemp = fiotemp->iolst;
	}
}
