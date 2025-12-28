/*	@(#)defs.h	1.7	*/
/*
 * UNIX shell
 *
 * Bell Telephone Laboratories
 *
 */


/* error exits from various parts of shell */
#include <compat.h>
#include 	<sys/types.h>
#include 	<unistd.h>
#include 	<stdlib.h>
#include 	<fcntl.h>
#include 	<sys/wait.h>
#include 	<sys/times.h>
#define 	ERROR		1
#define 	SYNBAD		2
#define 	SIGFAIL 	2000
#define	 	SIGFLG		0200

/* command tree */
#define 	FPRS		0x0100
#define 	FINT		0x0200
#define 	FAMP		0x0400
#define 	FPIN		0x0800
#define 	FPOU		0x1000
#define 	FPCL		0x2000
#define 	FCMD		0x4000
#define 	COMMSK		0x00F0
#define		CNTMSK		0x000F

#define 	TCOM		0x0000
#define 	TPAR		0x0010
#define 	TFIL		0x0020
#define 	TLST		0x0030
#define 	TIF			0x0040
#define 	TWH			0x0050
#define 	TUN			0x0060
#define 	TSW			0x0070
#define 	TAND		0x0080
#define 	TORF		0x0090
#define 	TFORK		0x00A0
#define 	TFOR		0x00B0
#define		TFND		0x00C0

/* execute table */
#define 	SYSSET		1
#define 	SYSCD		2
#define 	SYSEXEC		3
#define 	SYSNEWGRP 	4
#define 	SYSTRAP		5
#define 	SYSEXIT		6
#define 	SYSSHFT 	7
#define 	SYSWAIT		8
#define 	SYSCONT 	9
#define 	SYSBREAK	10
#define 	SYSEVAL 	11
#define 	SYSDOT		12
#define 	SYSTIMES 	14
#define 	SYSXPORT	15
#define 	SYSNULL 	16
#define 	SYSREAD 	17

#define 	SYSUMASK 	20

#define 	SYSECHO		22
#define		SYSPWD		24
#define 	SYSRETURN	25
#define		SYSUNS		26
#define		SYSMEM		27
#define		SYSWHATIS  	28
#define		SYSBLTIN	29

/* used for input and output of shell */
#define 	INIO 		19

/*io nodes*/
#define 	USERIO		10
#define 	IOUFD		15
#define 	IODOC		16
#define 	IOPUT		32
#define 	IOAPP		64
#define 	IOMOV		128
#define 	IORDW		256
#define 	INPIPE		0
#define 	OTPIPE		1

/* arg list terminator */
#define 	ENDARGS		0

#include	"mac.h"
#include	"mode.h"
#include	"name.h"
#include	<signal.h>


/*	error catching */
extern int 		errno;

/* result type declarations */

#ifdef	BSD4_2
#define	shalloc		malloc
#define	shfree		free
#endif

extern char				*shalloc(unsigned);
extern void				shfree(void *);
extern char				*make(char *);
extern char				*movstr(char *, char *);
extern char				*movstrn(char *, char *, int);
extern char				*quotedstring(char *);
extern char				*strf(struct namnod *);
extern BOOL				chkid(char *);
extern struct trenod	*cmd(int, int);
extern struct trenod	*makefork(int, struct trenod *);
extern struct namnod	*lookup(char *);
extern struct namnod	*findnam(char *);
extern struct dolnod	*useargs();
extern float			expr();
extern char				*catpath(char *, char *);
extern char				*getpath(char *);
extern char				*nextpath(char *);

extern char				*mactrim(char *);
extern char				*macro(char *);
extern char				*execs(char *, char **);
extern void				exname(struct namnod *);
extern char				*staknam(struct namnod *);
extern void				printnam(struct namnod *);
extern void				printro(struct namnod *);
extern void				printexp(struct namnod *);
extern char				**sh_setenv();
extern long				time(long *);
extern void				prs_2buff(char *, char *);
extern void				prc_buff(int);
extern void				prs_buff(char *);
extern void				prn_buff(int);
extern void				prs_cntl(char *);
extern void				flushb();
extern long				lseek(int, long, int);

extern void				clear_buff();
/* Standard IO and Shell utilities */
extern void				prs(char *);
extern void				prc(int);
extern void				prn(int);
extern void				prp();
extern void				exitsh(int);
extern void				setup_env();
extern int				options(int, char **);
extern void				replace(char **, char *);
extern void				assnum(char **, int);
extern void				stdsigs();
extern void				settmp();
extern void				dfault(struct namnod *, char *);
extern int				pathopen(char *, char *);
extern int				estabf(char *);
extern int				chkopen(char *);
extern void				done(int);
extern void				Ldup(int, int);
extern void				setmail(char *);
extern void				chkmail();
extern int				readc();
extern int				execute(struct trenod *, int, int, int *, int *);
extern void				rmtemp(void *);
extern void				rmfunctmp();
extern void				stakchk();
extern void				tdystak(char *);
extern void				setstak(char *);
extern void				pushstak(int);
extern void				itos(int);
extern int				word();
extern int				length(char *);
extern int				skipc();
extern int				nextc(int);
extern void				chkpr();
extern void				push(struct fileblk *);
extern int				pop();
extern void				initf(int);
extern void				execexp(char *, void *);
extern void				error(char *);
extern void				clearup();
extern void				chktrap();
extern int				syslook(char *, struct sysnod *, int);
extern void				execprint(char **);
extern void				popargs();
extern void				pushargs(char **);
extern void				restore(int);
extern int				initio(struct ionod *, int);
extern void				free_val(struct namx *);
extern int				special(char *);
extern void				setlist(struct argnod *, int);
extern int				stoi(char *);
extern void				clrsig(int);
extern int				ignsig(int);
extern void				getsig(int);
extern void				setsig(int);
extern void				attrib(struct namnod *, int);
extern int				any(int, char *);
extern int				cf(char *, char *);
extern int				create(char *);
extern int				tmpfil(struct tempblk *);
extern int				poptemp();
extern int				savefd(int);
extern void				addblok(unsigned);
extern void				await(int, int);
extern int				readvar(char **);
extern void				namscan(void (*)(struct namnod *));
extern void				what_is(char *);
extern void				unset_name(char *);
extern void				chkmem();
extern void				post(int);
extern void				swap_iodoc_nm(struct ionod *);
extern void				postclr();
extern void				sh_rename(int, int);
extern void				failed(char *, char *, int);
extern void				assign(struct namnod *, char *);
extern void				chkpipe(int *);
extern void				link_iodocs(struct ionod *);
extern void				free_arg(struct argnod *);
extern void				freefunc(char *);
extern struct dolnod	*freeargs(struct dolnod *);
extern struct dolnod	*clean_args(struct dolnod *);
extern char				*simple(char *);
extern int				getarg(struct comnod *);
extern char				**scan(int);
extern void				copy(struct ionod *);
extern int				expand(char *, int);
extern void				makearg(struct argnod *);
extern void				subst(int, int);
extern void				freetree(struct trenod *);
extern void				freeio(struct ionod *);
extern void				freereg(struct regnod *);
extern void				prfstr(char *);
extern void				prf(struct trenod *);
extern void				prarg(struct argnod *);
extern void				prio(struct ionod *);
extern void				prfqstr(char *);
extern int				gmatch(char *, char *);
extern void				trim(char *);
extern void				prt(long);
extern void				oldsigs();
extern int				execa(char **);
extern void				dochdir(char *, char *);
extern void				setargs(char **);
extern void				prot_env();
extern void				setname(char *, int);

#define 	attrib(n,f)		(n->namflg |= f)
#ifdef	CRAY
#define 	round(a,b)		((((a)+(b))-1)&~((b)-1))
#define		sround(a,b)		((char *)((long)(a+(b-1))&077777777))
#else
#define 	round(a,b)		(((long)((long)(a)+(b)-1))&~((long)(b)-1))
#define		sround			round
#endif
#define 	closepipe(x)	(close(x[INPIPE]), close(x[OTPIPE]))
#define 	eq(a,b)			(cf(a,b)==0)
#define 	max(a,b)		((a)>(b)?(a):(b))
#define 	assert(x)		;

/* temp files and io */
extern int				output;
extern int				ioset;
extern struct ionod		*iotemp;	/* files to be deleted sometime */
extern struct ionod		*fiotemp;	/* function files to be deleted sometime */
extern struct ionod		*iopend;	/* documents waiting to be read at NL */
extern struct fdsave	fdmap[];


/* substitution */
extern int				dolc;
extern char				**dolv;
extern struct dolnod	*argfor;
extern struct argnod	*gchain;

/* stak stuff */
#include		"stak.h"

/* string constants */
extern char				atline[];
extern char				readmsg[];
extern char				colon[];
extern char				minus[];
extern char				nullstr[];
extern char				sptbnl[];
extern char				unexpected[];
extern char				endoffile[];
extern char				synmsg[];

/* name tree and words */
extern struct sysnod	reserved[];
extern int				no_reserved;
extern struct sysnod	commands[];
extern int				no_commands;

extern int				wdval;
extern int				wdnum;
extern int				fndef;
extern struct argnod			*wdarg;
extern int				wdset;
extern BOOL				reserv;

/* prompting */
extern char				stdprompt[];
extern char				supprompt[];
extern char				profile[];

/* built in names */
extern struct namnod	fngnod;
extern struct namnod	cdpnod;
extern struct namnod	ifsnod;
extern struct namnod	histnod;
extern struct namnod	homenod;
extern struct namnod	mailnod;
extern struct namnod	pathnod;
extern struct namnod	ps1nod;
extern struct namnod	ps2nod;
extern struct namnod	acctnod;

/* special names */
extern char				flagadr[];
extern char				*pcsadr;
extern char				*pidadr;
extern char				*cmdadr;

extern char				defpath[];

/* names always present */
extern char				mailname[];
extern char				homename[];
extern char				pathname[];
extern char				cdpname[];
extern char				ifsname[];
extern char				histname[];
extern char				ps1name[];
extern char				ps2name[];
extern char				acctname[];

/* transput */
extern char				tmpout[];
extern char				*tmpnam;
extern int				serial;

#define		TMPNAM 		7

extern struct fileblk	*standin;

#define 	input		(standin->fdes)
#define 	eof			(standin->feof)

extern int				peekc;
extern int				peekn;
extern int				histfd;
extern char				*comdiv;
extern char				devnull[];

/* flags */
#define		noexec		01
#define		sysflg		01
#define		intflg		02
#define		prompt		04
#define		setflg		010
#define		errflg		020
#define		ttyflg		040
#define		forked		0100
#define		oneflg		0200
#define		protflg		0400
#define		waiting		01000
#define		stdflg		02000
#define		STDFLG		's'
#define		execpr		04000
#define		readpr		010000
#define		keyflg		020000
#define		nofngflg	0200000
#define		exportflg	0400000

extern long				flags;
extern int				rwait;	/* flags read waiting */

/* error exits from various parts of shell */
#include	<setjmp.h>
extern jmp_buf			subshell;
extern jmp_buf			errshell;

/* fault handling */
#include	"brkincr.h"

extern unsigned			brkincr;
#define 	MINTRAP		0
#define 	MAXTRAP		32

#define 	TRAPSET		2
#define 	SIGSET		4
#define 	SIGMOD		8
#define 	SIGCAUGHT	16

extern void				fault(int);
extern BOOL				trapnote;
extern char				*trapcom[];
extern BOOL				trapflg[];

/* name tree and words */
extern char				**environ;
extern char				numbuf[];
extern BOOL				nosubst;
extern char				export[];
extern char				duperr[];

/* execflgs */
extern int				exitval;
extern int				retval;
extern BOOL				execbrk;
extern int				loopcnt;
extern int				breakcnt;
extern int				funcnt;

/* messages */
extern char				mailmsg[];
extern char				coredump[];
extern char				badopt[];
extern char				badparam[];
extern char				unset[];
extern char				badsub[];
extern char				nospace[];
extern char				nostack[];
extern char				notfound[];
extern char				notbltin[];
extern char				badtrap[];
extern char				baddir[];
extern char				badshift[];
extern char				execpmsg[];
extern char				notid[];
extern char				badcreate[];
extern char				nofork[];
extern char				noswap[];
extern char				piperr[];
extern char				badopen[];
extern char				badnum[];
extern char				arglist[];
extern char				txtbsy[];
extern char				toobig[];
extern char				badexec[];
extern char				badfile[];
extern char				badreturn[];
extern char				badexport[];
extern char				badunset[];
extern char				nohome[];
extern char				badperm[];
extern char				badfname[];

/*	'builtin' error messages	*/

extern char				btest[];
extern char				badop[];

/*	fork constant	*/

#define 	FORKLIM 	32

extern address			end[];

#include	"sctype.h"

extern int				wasintr;	/* used to tell if break or delete is hit
				   					 *  while executing a wait
									 */
extern int				eflag;


/*
 * Find out if it is time to go away.
 * `trapnote' is set to SIGSET when fault is seen and
 * no trap has been set.
 */

#define		sigchk()	if (trapnote & SIGSET)	\
							exitsh(exitval ? exitval : SIGFAIL)

#define 	exitset()	retval = exitval
