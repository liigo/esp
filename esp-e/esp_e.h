#ifndef __ESPMODE_FNE_H__
#define __ESPMODE_FNE_H__

//其中包含一系列函数, 从Apaache模块(mod_esp.mod)获取而来
extern const ESPClientAPI* g_pESPFuncs;

bool IsESPRuntimeAvailable(); //返回true表示: mod_esp.so + espmod.fne 已配合工作

#endif //__ESPMODE_FNE_H__
