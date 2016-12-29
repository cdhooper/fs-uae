#ifndef UAE_IDECONTROLLERS_H
#define UAE_IDECONTROLLERS_H

#include "uae/types.h"
#ifdef FSUAE
#include "uae/memory.h"
#endif

// Other IDE controllers

void idecontroller_free(void);
void idecontroller_reset(void);
void idecontroller_rethink(void);
void idecontroller_hsync(void);

void gvp_add_ide_unit(int ch, struct uaedev_config_info *ci, struct romconfig *rc);
bool gvp_ide_rom_autoconfig_init(struct autoconfig_info *aci);
bool gvp_ide_controller_autoconfig_init(struct autoconfig_info *aci);

void alf_add_ide_unit(int ch, struct uaedev_config_info *ci, struct romconfig *rc);
bool alf_init(struct autoconfig_info *aci);

void apollo_add_ide_unit(int ch, struct uaedev_config_info *ci, struct romconfig *rc);
bool apollo_init_hd(struct autoconfig_info *aci);
bool apollo_init_cpu(struct autoconfig_info *aci);

void masoboshi_add_idescsi_unit (int ch, struct uaedev_config_info *ci, struct romconfig *rc);
bool masoboshi_init(struct autoconfig_info *aci);

void adide_add_ide_unit(int ch, struct uaedev_config_info *ci, struct romconfig *rc);
bool adide_init(struct autoconfig_info *aci);

void mtec_add_ide_unit(int ch, struct uaedev_config_info *ci, struct romconfig *rc);
bool mtec_init(struct autoconfig_info *aci);

bool rochard_init(struct autoconfig_info *aci);
void rochard_add_idescsi_unit(int ch, struct uaedev_config_info *ci, struct romconfig *rc);

bool golemfast_init(struct autoconfig_info *aci);
void golemfast_add_idescsi_unit(int ch, struct uaedev_config_info *ci, struct romconfig *rc);

bool buddha_init(struct autoconfig_info *aci);
void buddha_add_ide_unit(int ch, struct uaedev_config_info *ci, struct romconfig *rc);

uae_u32 REGPARAM3 apollo_ide_lget (uaecptr addr) REGPARAM;
uae_u32 REGPARAM3 apollo_ide_wget (uaecptr addr) REGPARAM;
uae_u32 REGPARAM3 apollo_ide_bget (uaecptr addr) REGPARAM;
void REGPARAM3 apollo_ide_lput (uaecptr addr, uae_u32 l) REGPARAM;
void REGPARAM3 apollo_ide_wput (uaecptr addr, uae_u32 w) REGPARAM;
void REGPARAM3 apollo_ide_bput (uaecptr addr, uae_u32 b) REGPARAM;
extern const uae_u8 apollo_autoconfig[16];
extern const uae_u8 apollo_autoconfig_060[16];

void x86_ide_hd_put(int portnum, uae_u16 v, int);
uae_u16 x86_ide_hd_get(int portnum, int);
bool x86_at_hd_init_1(struct autoconfig_info *aci);
void x86_add_at_hd_unit_1(int ch, struct uaedev_config_info *ci, struct romconfig *rc);
bool x86_at_hd_init_2(struct autoconfig_info *aci);
void x86_add_at_hd_unit_2(int ch, struct uaedev_config_info *ci, struct romconfig *rc);
bool x86_at_hd_init_xt(struct autoconfig_info *aci);
void x86_add_at_hd_unit_xt(int ch, struct uaedev_config_info *ci, struct romconfig *rc);

#endif /* UAE_IDECONTROLLERS_H */
