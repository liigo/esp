#ifndef __ESPMODE_FNE_H__
#define __ESPMODE_FNE_H__

//���а���һϵ�к���, ��Apaacheģ��(mod_esp.mod)��ȡ����
extern const ESPClientAPI* g_pESPFuncs;

bool IsESPRuntimeAvailable(); //����true��ʾ: mod_esp.so + espmod.fne ����Ϲ���

#endif //__ESPMODE_FNE_H__
