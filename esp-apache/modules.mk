mod_esp.la: mod_esp.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_esp.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_esp.la
