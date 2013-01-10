#ifndef __ELIB_H_
#define __ELIB_H_

/*�漰��֧�ֿ�ĵط�ֻ���ñ��ļ��Ϳ�����*/

#ifdef __OS_LINUX_VER
	#include <sys/types.h>
	#include <strings.h>
	#include <stdbool.h>  //! for use bool,true,false
	#include "mtypes.h"
#else
	#include <stdio.h>
	#include <tchar.h>
	#include <wtypes.h>
#endif  /*__OS_LINUX_VER*/

#include "lang.h"
#include "krnllib.h"
#include "fnshare.h"
#include "cmem.h"
#include "lib2.h"


#endif /*__ELIB_H_*/
