#include "fs-uae.h"
#include <stdlib.h>
#include <uae/uae.h>
#include <fs/emu.h>
#include <fs/i18n.h>

static fs_emu_action g_actions[] = {
    { INPUTEVENT_MOUSE1_HORIZ, "action_mouse_0_horiz", 0 },
    { INPUTEVENT_MOUSE1_VERT, "action_mouse_0_vert", 0 },
    { INPUTEVENT_MOUSE1_HORIZ_INV, "action_mouse_0_horiz_inv", 0 },
    { INPUTEVENT_MOUSE1_VERT_INV, "action_mouse_0_vert_inv", 0 },
    { INPUTEVENT_MOUSE1_UP, "action_mouse_0_up", 0 },
    { INPUTEVENT_MOUSE1_DOWN, "action_mouse_0_down", 0 },
    { INPUTEVENT_MOUSE1_LEFT, "action_mouse_0_left", 0 },
    { INPUTEVENT_MOUSE1_RIGHT, "action_mouse_0_right", 0 },
    { INPUTEVENT_MOUSE1_WHEEL, "action_mouse_0_wheel", 0 },
    { INPUTEVENT_MOUSE_CDTV_HORIZ, "action_mouse_cdtv_horiz", 0 },
    { INPUTEVENT_MOUSE_CDTV_VERT, "action_mouse_cdtv_vert", 0 },
    { INPUTEVENT_MOUSE_CDTV_UP, "action_mouse_cdtv_up", 0 },
    { INPUTEVENT_MOUSE_CDTV_DOWN, "action_mouse_cdtv_down", 0 },
    { INPUTEVENT_MOUSE_CDTV_LEFT, "action_mouse_cdtv_left", 0 },
    { INPUTEVENT_MOUSE_CDTV_RIGHT, "action_mouse_cdtv_right", 0 },
    { INPUTEVENT_JOY1_HORIZ, "action_joy_0_horiz", 0 },
    { INPUTEVENT_JOY1_VERT, "action_joy_0_vert", 0 },
    { INPUTEVENT_JOY1_HORIZ_POT, "action_joy_0_horiz_pot", 0 },
    { INPUTEVENT_JOY1_VERT_POT, "action_joy_0_vert_pot", 0 },
    { INPUTEVENT_JOY1_HORIZ_POT_INV, "action_joy_0_horiz_pot_inv", 0 },
    { INPUTEVENT_JOY1_VERT_POT_INV, "action_joy_0_vert_pot_inv", 0 },
    { INPUTEVENT_JOY1_LEFT, "action_joy_0_left", 0 },
    { INPUTEVENT_JOY1_RIGHT, "action_joy_0_right", 0 },
    { INPUTEVENT_JOY1_UP, "action_joy_0_up", 0 },
    { INPUTEVENT_JOY1_DOWN, "action_joy_0_down", 0 },
    { INPUTEVENT_JOY1_LEFT_UP, "action_joy_0_left_up", 0 },
    { INPUTEVENT_JOY1_LEFT_DOWN, "action_joy_0_left_down", 0 },
    { INPUTEVENT_JOY1_RIGHT_UP, "action_joy_0_right_up", 0 },
    { INPUTEVENT_JOY1_RIGHT_DOWN, "action_joy_0_right_down", 0 },
    { INPUTEVENT_JOY1_FIRE_BUTTON, "action_joy_0_fire_button", 0 },
    { INPUTEVENT_JOY1_2ND_BUTTON, "action_joy_0_2nd_button", 0 },
    { INPUTEVENT_JOY1_3RD_BUTTON, "action_joy_0_3rd_button", 0 },
    { INPUTEVENT_JOY1_CD32_PLAY, "action_joy_0_cd32_play", 0 },
    { INPUTEVENT_JOY1_CD32_RWD, "action_joy_0_cd32_rwd", 0 },
    { INPUTEVENT_JOY1_CD32_FFW, "action_joy_0_cd32_ffw", 0 },
    { INPUTEVENT_JOY1_CD32_GREEN, "action_joy_0_cd32_green", 0 },
    { INPUTEVENT_JOY1_CD32_YELLOW, "action_joy_0_cd32_yellow", 0 },
    { INPUTEVENT_JOY1_CD32_RED, "action_joy_0_cd32_red", 0 },
    { INPUTEVENT_JOY1_CD32_BLUE, "action_joy_0_cd32_blue", 0 },
    { INPUTEVENT_MOUSE2_HORIZ, "action_mouse_1_horiz", 0 },
    { INPUTEVENT_MOUSE2_VERT, "action_mouse_1_vert", 0 },
    { INPUTEVENT_MOUSE2_HORIZ_INV, "action_mouse_1_horiz_inv", 0 },
    { INPUTEVENT_MOUSE2_VERT_INV, "action_mouse_1_vert_inv", 0 },
    { INPUTEVENT_MOUSE2_UP, "action_mouse_1_up", 0 },
    { INPUTEVENT_MOUSE2_DOWN, "action_mouse_1_down", 0 },
    { INPUTEVENT_MOUSE2_LEFT, "action_mouse_1_left", 0 },
    { INPUTEVENT_MOUSE2_RIGHT, "action_mouse_1_right", 0 },
    { INPUTEVENT_JOY2_HORIZ, "action_joy_1_horiz", 0 },
    { INPUTEVENT_JOY2_VERT, "action_joy_1_vert", 0 },
    { INPUTEVENT_JOY2_HORIZ_POT, "action_joy_1_horiz_pot", 0 },
    { INPUTEVENT_JOY2_VERT_POT, "action_joy_1_vert_pot", 0 },
    { INPUTEVENT_JOY2_HORIZ_POT_INV, "action_joy_1_horiz_pot_inv", 0 },
    { INPUTEVENT_JOY2_VERT_POT_INV, "action_joy_1_vert_pot_inv", 0 },
    { INPUTEVENT_JOY2_LEFT, "action_joy_1_left", 0 },
    { INPUTEVENT_JOY2_RIGHT, "action_joy_1_right", 0 },
    { INPUTEVENT_JOY2_UP, "action_joy_1_up", 0 },
    { INPUTEVENT_JOY2_DOWN, "action_joy_1_down", 0 },
    { INPUTEVENT_JOY2_LEFT_UP, "action_joy_1_left_up", 0 },
    { INPUTEVENT_JOY2_LEFT_DOWN, "action_joy_1_left_down", 0 },
    { INPUTEVENT_JOY2_RIGHT_UP, "action_joy_1_right_up", 0 },
    { INPUTEVENT_JOY2_RIGHT_DOWN, "action_joy_1_right_down", 0 },
    { INPUTEVENT_JOY2_FIRE_BUTTON, "action_joy_1_fire_button", 0 },
    { INPUTEVENT_JOY2_2ND_BUTTON, "action_joy_1_2nd_button", 0 },
    { INPUTEVENT_JOY2_3RD_BUTTON, "action_joy_1_3rd_button", 0 },
    { INPUTEVENT_JOY2_CD32_PLAY, "action_joy_1_cd32_play", 0 },
    { INPUTEVENT_JOY2_CD32_RWD, "action_joy_1_cd32_rwd", 0 },
    { INPUTEVENT_JOY2_CD32_FFW, "action_joy_1_cd32_ffw", 0 },
    { INPUTEVENT_JOY2_CD32_GREEN, "action_joy_1_cd32_green", 0 },
    { INPUTEVENT_JOY2_CD32_YELLOW, "action_joy_1_cd32_yellow", 0 },
    { INPUTEVENT_JOY2_CD32_RED, "action_joy_1_cd32_red", 0 },
    { INPUTEVENT_JOY2_CD32_BLUE, "action_joy_1_cd32_blue", 0 },
    { INPUTEVENT_LIGHTPEN_HORIZ, "action_lightpen_horiz", 0 },
    { INPUTEVENT_LIGHTPEN_VERT, "action_lightpen_vert", 0 },
    { INPUTEVENT_LIGHTPEN_LEFT, "action_lightpen_left", 0 },
    { INPUTEVENT_LIGHTPEN_RIGHT, "action_lightpen_right", 0 },
    { INPUTEVENT_LIGHTPEN_UP, "action_lightpen_up", 0 },
    { INPUTEVENT_LIGHTPEN_DOWN, "action_lightpen_down", 0 },
    { INPUTEVENT_PAR_JOY1_HORIZ, "action_par_joy_0_horiz", 0 },
    { INPUTEVENT_PAR_JOY1_VERT, "action_par_joy_0_vert", 0 },
    { INPUTEVENT_PAR_JOY1_LEFT, "action_par_joy_0_left", 0 },
    { INPUTEVENT_PAR_JOY1_RIGHT, "action_par_joy_0_right", 0 },
    { INPUTEVENT_PAR_JOY1_UP, "action_par_joy_0_up", 0 },
    { INPUTEVENT_PAR_JOY1_DOWN, "action_par_joy_0_down", 0 },
    { INPUTEVENT_PAR_JOY1_LEFT_UP, "action_par_joy_0_left_up", 0 },
    { INPUTEVENT_PAR_JOY1_LEFT_DOWN, "action_par_joy_0_left_down", 0 },
    { INPUTEVENT_PAR_JOY1_RIGHT_UP, "action_par_joy_0_right_up", 0 },
    { INPUTEVENT_PAR_JOY1_RIGHT_DOWN, "action_par_joy_0_right_down", 0 },
    { INPUTEVENT_PAR_JOY1_FIRE_BUTTON, "action_par_joy_0_fire_button", 0 },
    { INPUTEVENT_PAR_JOY1_2ND_BUTTON, "action_par_joy_0_2nd_button", 0 },
    { INPUTEVENT_PAR_JOY2_HORIZ, "action_par_joy_1_horiz", 0 },
    { INPUTEVENT_PAR_JOY2_VERT, "action_par_joy_1_vert", 0 },
    { INPUTEVENT_PAR_JOY2_LEFT, "action_par_joy_1_left", 0 },
    { INPUTEVENT_PAR_JOY2_RIGHT, "action_par_joy_1_right", 0 },
    { INPUTEVENT_PAR_JOY2_UP, "action_par_joy_1_up", 0 },
    { INPUTEVENT_PAR_JOY2_DOWN, "action_par_joy_1_down", 0 },
    { INPUTEVENT_PAR_JOY2_LEFT_UP, "action_par_joy_1_left_up", 0 },
    { INPUTEVENT_PAR_JOY2_LEFT_DOWN, "action_par_joy_1_left_down", 0 },
    { INPUTEVENT_PAR_JOY2_RIGHT_UP, "action_par_joy_1_right_up", 0 },
    { INPUTEVENT_PAR_JOY2_RIGHT_DOWN, "action_par_joy_1_right_down", 0 },
    { INPUTEVENT_PAR_JOY2_FIRE_BUTTON, "action_par_joy_1_fire_button", 0 },
    { INPUTEVENT_PAR_JOY2_2ND_BUTTON, "action_par_joy_1_2nd_button", 0 },
    { INPUTEVENT_KEY_F1, "action_key_f1", 0 },
    { INPUTEVENT_KEY_F2, "action_key_f2", 0 },
    { INPUTEVENT_KEY_F3, "action_key_f3", 0 },
    { INPUTEVENT_KEY_F4, "action_key_f4", 0 },
    { INPUTEVENT_KEY_F5, "action_key_f5", 0 },
    { INPUTEVENT_KEY_F6, "action_key_f6", 0 },
    { INPUTEVENT_KEY_F7, "action_key_f7", 0 },
    { INPUTEVENT_KEY_F8, "action_key_f8", 0 },
    { INPUTEVENT_KEY_F9, "action_key_f9", 0 },
    { INPUTEVENT_KEY_F10, "action_key_f10", 0 },
    { INPUTEVENT_KEY_ESC, "action_key_esc", 0 },
    { INPUTEVENT_KEY_TAB, "action_key_tab", 0 },
    { INPUTEVENT_KEY_CTRL, "action_key_ctrl", 0 },
    { INPUTEVENT_KEY_CAPS_LOCK, "action_key_caps_lock", 0 },
    { INPUTEVENT_KEY_SHIFT_LEFT, "action_key_shift_left", 0 },
    { INPUTEVENT_KEY_ALT_LEFT, "action_key_alt_left", 0 },
    { INPUTEVENT_KEY_AMIGA_LEFT, "action_key_amiga_left", 0 },
    { INPUTEVENT_KEY_AMIGA_RIGHT, "action_key_amiga_right", 0 },
    { INPUTEVENT_KEY_ALT_RIGHT, "action_key_alt_right", 0 },
    { INPUTEVENT_KEY_SHIFT_RIGHT, "action_key_shift_right", 0 },
    { INPUTEVENT_KEY_SPACE, "action_key_space", 0 },
    { INPUTEVENT_KEY_CURSOR_UP, "action_key_cursor_up", 0 },
    { INPUTEVENT_KEY_CURSOR_DOWN, "action_key_cursor_down", 0 },
    { INPUTEVENT_KEY_CURSOR_LEFT, "action_key_cursor_left", 0 },
    { INPUTEVENT_KEY_CURSOR_RIGHT, "action_key_cursor_right", 0 },
    { INPUTEVENT_KEY_HELP, "action_key_help", 0 },
    { INPUTEVENT_KEY_DEL, "action_key_del", 0 },
    { INPUTEVENT_KEY_BACKSPACE, "action_key_backspace", 0 },
    { INPUTEVENT_KEY_RETURN, "action_key_return", 0 },
    { INPUTEVENT_KEY_A, "action_key_a", 0 },
    { INPUTEVENT_KEY_B, "action_key_b", 0 },
    { INPUTEVENT_KEY_C, "action_key_c", 0 },
    { INPUTEVENT_KEY_D, "action_key_d", 0 },
    { INPUTEVENT_KEY_E, "action_key_e", 0 },
    { INPUTEVENT_KEY_F, "action_key_f", 0 },
    { INPUTEVENT_KEY_G, "action_key_g", 0 },
    { INPUTEVENT_KEY_H, "action_key_h", 0 },
    { INPUTEVENT_KEY_I, "action_key_i", 0 },
    { INPUTEVENT_KEY_J, "action_key_j", 0 },
    { INPUTEVENT_KEY_K, "action_key_k", 0 },
    { INPUTEVENT_KEY_L, "action_key_l", 0 },
    { INPUTEVENT_KEY_M, "action_key_m", 0 },
    { INPUTEVENT_KEY_N, "action_key_n", 0 },
    { INPUTEVENT_KEY_O, "action_key_o", 0 },
    { INPUTEVENT_KEY_P, "action_key_p", 0 },
    { INPUTEVENT_KEY_Q, "action_key_q", 0 },
    { INPUTEVENT_KEY_R, "action_key_r", 0 },
    { INPUTEVENT_KEY_S, "action_key_s", 0 },
    { INPUTEVENT_KEY_T, "action_key_t", 0 },
    { INPUTEVENT_KEY_U, "action_key_u", 0 },
    { INPUTEVENT_KEY_V, "action_key_v", 0 },
    { INPUTEVENT_KEY_W, "action_key_w", 0 },
    { INPUTEVENT_KEY_X, "action_key_x", 0 },
    { INPUTEVENT_KEY_Y, "action_key_y", 0 },
    { INPUTEVENT_KEY_Z, "action_key_z", 0 },
    { INPUTEVENT_KEY_ENTER, "action_key_enter", 0 },
    { INPUTEVENT_KEY_NP_0, "action_key_np_0", 0 },
    { INPUTEVENT_KEY_NP_1, "action_key_np_1", 0 },
    { INPUTEVENT_KEY_NP_2, "action_key_np_2", 0 },
    { INPUTEVENT_KEY_NP_3, "action_key_np_3", 0 },
    { INPUTEVENT_KEY_NP_4, "action_key_np_4", 0 },
    { INPUTEVENT_KEY_NP_5, "action_key_np_5", 0 },
    { INPUTEVENT_KEY_NP_6, "action_key_np_6", 0 },
    { INPUTEVENT_KEY_NP_7, "action_key_np_7", 0 },
    { INPUTEVENT_KEY_NP_8, "action_key_np_8", 0 },
    { INPUTEVENT_KEY_NP_9, "action_key_np_9", 0 },
    { INPUTEVENT_KEY_NP_PERIOD, "action_key_np_period", 0 },
    { INPUTEVENT_KEY_NP_ADD, "action_key_np_add", 0 },
    { INPUTEVENT_KEY_NP_SUB, "action_key_np_sub", 0 },
    { INPUTEVENT_KEY_NP_MUL, "action_key_np_mul", 0 },
    { INPUTEVENT_KEY_NP_DIV, "action_key_np_div", 0 },
    { INPUTEVENT_KEY_NP_LPAREN, "action_key_np_lparen", 0 },
    { INPUTEVENT_KEY_NP_RPAREN, "action_key_np_rparen", 0 },
    { INPUTEVENT_KEY_2B, "action_key_2b", 0 },
    { INPUTEVENT_KEY_30, "action_key_30", 0 },
    { INPUTEVENT_KEY_BACKQUOTE, "action_key_backquote", 0 },
    { INPUTEVENT_KEY_1, "action_key_1", 0 },
    { INPUTEVENT_KEY_2, "action_key_2", 0 },
    { INPUTEVENT_KEY_3, "action_key_3", 0 },
    { INPUTEVENT_KEY_4, "action_key_4", 0 },
    { INPUTEVENT_KEY_5, "action_key_5", 0 },
    { INPUTEVENT_KEY_6, "action_key_6", 0 },
    { INPUTEVENT_KEY_7, "action_key_7", 0 },
    { INPUTEVENT_KEY_8, "action_key_8", 0 },
    { INPUTEVENT_KEY_9, "action_key_9", 0 },
    { INPUTEVENT_KEY_0, "action_key_0", 0 },
    { INPUTEVENT_KEY_SUB, "action_key_sub", 0 },
    { INPUTEVENT_KEY_EQUALS, "action_key_equals", 0 },
    { INPUTEVENT_KEY_BACKSLASH, "action_key_backslash", 0 },
    { INPUTEVENT_KEY_LEFTBRACKET, "action_key_leftbracket", 0 },
    { INPUTEVENT_KEY_RIGHTBRACKET, "action_key_rightbracket", 0 },
    { INPUTEVENT_KEY_SEMICOLON, "action_key_semicolon", 0 },
    { INPUTEVENT_KEY_SINGLEQUOTE, "action_key_singlequote", 0 },
    { INPUTEVENT_KEY_COMMA, "action_key_comma", 0 },
    { INPUTEVENT_KEY_PERIOD, "action_key_period", 0 },
    { INPUTEVENT_KEY_DIV, "action_key_div", 0 },
    { INPUTEVENT_MOUSEWHEEL_DOWN, "action_mousewheel_down", 0 },
    { INPUTEVENT_MOUSEWHEEL_UP, "action_mousewheel_up", 0 },
    { INPUTEVENT_KEY_CDTV_STOP, "action_key_cdtv_stop", 0 },
    { INPUTEVENT_KEY_CDTV_PLAYPAUSE, "action_key_cdtv_playpause", 0 },
    { INPUTEVENT_KEY_CDTV_PREV, "action_key_cdtv_prev", 0 },
    { INPUTEVENT_KEY_CDTV_NEXT, "action_key_cdtv_next", 0 },
    { INPUTEVENT_KEY_CDTV_REW, "action_key_cdtv_rew", 0 },
    { INPUTEVENT_KEY_CDTV_FF, "action_key_cdtv_ff", 0 },
    { INPUTEVENT_KEY_0E, "action_key_0e", 0 },
    { INPUTEVENT_KEY_1C, "action_key_1c", 0 },
    { INPUTEVENT_KEY_2C, "action_key_2c", 0 },
    { INPUTEVENT_KEY_3B, "action_key_3b", 0 },
    { INPUTEVENT_KEY_68, "action_key_68", 0 },
    { INPUTEVENT_KEY_69, "action_key_69", 0 },
    { INPUTEVENT_KEY_6A, "action_key_6a", 0 },
    { INPUTEVENT_KEY_6C, "action_key_6c", 0 },
    { INPUTEVENT_KEY_78, "action_key_78", 0 },
    { INPUTEVENT_KEY_79, "action_key_79", 0 },
    { INPUTEVENT_KEY_7A, "action_key_7a", 0 },
    { INPUTEVENT_KEY_7B, "action_key_7b", 0 },
    { INPUTEVENT_KEY_7C, "action_key_7c", 0 },
    { INPUTEVENT_KEY_7D, "action_key_7d", 0 },
    { INPUTEVENT_KEY_7E, "action_key_7e", 0 },
    { INPUTEVENT_KEY_7F, "action_key_7f", 0 },
    { INPUTEVENT_SPC_FREEZEBUTTON, "action_activate_cartridge", 0 },
    { INPUTEVENT_SPC_EFLOPPY0, "action_eject_floppy_0", 0 },
    { INPUTEVENT_SPC_EFLOPPY1, "action_eject_floppy_1", 0 },
    { INPUTEVENT_SPC_EFLOPPY2, "action_eject_floppy_2", 0 },
    { INPUTEVENT_SPC_EFLOPPY3, "action_eject_floppy_3", 0 },
    { INPUTEVENT_SPC_PAUSE, "action_pause", 0 },
    { INPUTEVENT_SPC_WARP, "action_warp", 0 },
    { INPUTEVENT_SPC_IRQ7, "action_irq_7", 0 },
    { INPUTEVENT_SPC_STATEREWIND, "action_state_rewind", 0 },
    { INPUTEVENT_SPC_STATECURRENT, "action_state_current", 0 },
    { INPUTEVENT_SPC_STATECAPTURE, "action_state_capture", 0 },
    { INPUTEVENT_SPC_VOLUME_DOWN, "action_volume_down", 0 },
    { INPUTEVENT_SPC_VOLUME_UP, "action_volume_up", 0 },
    { INPUTEVENT_SPC_VOLUME_MUTE, "action_volume_mute", 0 },
    { INPUTEVENT_SPC_MASTER_VOLUME_DOWN, "action_master_volume_down", 0 },
    { INPUTEVENT_SPC_MASTER_VOLUME_UP, "action_master_volume_up", 0 },
    { INPUTEVENT_SPC_MASTER_VOLUME_MUTE, "action_master_volume_mute", 0 },
    { INPUTEVENT_SPC_QUIT, "action_quit", 0 },
    { INPUTEVENT_SPC_SOFTRESET, "action_soft_reset", 0 },
    { INPUTEVENT_SPC_HARDRESET, "action_hard_reset", 0 },
    { INPUTEVENT_SPC_SWITCHINTERPOL, "action_switch_interpol", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_NEXT, "action_disk_swapper_next", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_PREV, "action_disk_swapper_prev", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_INSERT0, "action_disk_swapper_insert_0", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_INSERT1, "action_disk_swapper_insert_1", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_INSERT2, "action_disk_swapper_insert_2", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_INSERT3, "action_disk_swapper_insert_3", 0 },
    { INPUTEVENT_SPC_DISK_PREV0, "action_disk_prev_0", 0 },
    { INPUTEVENT_SPC_DISK_PREV1, "action_disk_prev_1", 0 },
    { INPUTEVENT_SPC_DISK_PREV2, "action_disk_prev_2", 0 },
    { INPUTEVENT_SPC_DISK_PREV3, "action_disk_prev_3", 0 },
    { INPUTEVENT_SPC_DISK_NEXT0, "action_disk_next_0", 0 },
    { INPUTEVENT_SPC_DISK_NEXT1, "action_disk_next_1", 0 },
    { INPUTEVENT_SPC_DISK_NEXT2, "action_disk_next_2", 0 },
    { INPUTEVENT_SPC_DISK_NEXT3, "action_disk_next_3", 0 },
    { INPUTEVENT_SPC_ARCADIA_DIAGNOSTICS, "action_arcadia_diagnostics", 0 },
    { INPUTEVENT_SPC_ARCADIA_PLAYER1, "action_arcadia_player_1", 0 },
    { INPUTEVENT_SPC_ARCADIA_PLAYER2, "action_arcadia_player_2", 0 },
    { INPUTEVENT_SPC_ARCADIA_COIN1, "action_arcadia_coin_1", 0 },
    { INPUTEVENT_SPC_ARCADIA_COIN2, "action_arcadia_coin_2", 0 },
    { INPUTEVENT_SPC_CDTV_FRONT_PANEL_STOP, "action_cdtv_front_panel_stop", 0 },
    { INPUTEVENT_SPC_CDTV_FRONT_PANEL_PLAYPAUSE, "action_cdtv_front_panel_playpause", 0 },
    { INPUTEVENT_SPC_CDTV_FRONT_PANEL_PREV, "action_cdtv_front_panel_prev", 0 },
    { INPUTEVENT_SPC_CDTV_FRONT_PANEL_NEXT, "action_cdtv_front_panel_next", 0 },
    { INPUTEVENT_SPC_CDTV_FRONT_PANEL_REW, "action_cdtv_front_panel_rew", 0 },
    { INPUTEVENT_SPC_CDTV_FRONT_PANEL_FF, "action_cdtv_front_panel_ff", 0 },
    { INPUTEVENT_SPC_STATESAVE1, "action_save_state_1", 0 },
    { INPUTEVENT_SPC_STATESAVE2, "action_save_state_2", 0 },
    { INPUTEVENT_SPC_STATESAVE3, "action_save_state_3", 0 },
    { INPUTEVENT_SPC_STATESAVE4, "action_save_state_4", 0 },
    { INPUTEVENT_SPC_STATESAVE5, "action_save_state_5", 0 },
    { INPUTEVENT_SPC_STATESAVE6, "action_save_state_6", 0 },
    { INPUTEVENT_SPC_STATESAVE7, "action_save_state_7", 0 },
    { INPUTEVENT_SPC_STATESAVE8, "action_save_state_8", 0 },
    { INPUTEVENT_SPC_STATESAVE9, "action_save_state_9", 0 },
    { INPUTEVENT_SPC_STATERESTORE1, "action_restore_state_1", 0 },
    { INPUTEVENT_SPC_STATERESTORE2, "action_restore_state_2", 0 },
    { INPUTEVENT_SPC_STATERESTORE3, "action_restore_state_3", 0 },
    { INPUTEVENT_SPC_STATERESTORE4, "action_restore_state_4", 0 },
    { INPUTEVENT_SPC_STATERESTORE5, "action_restore_state_5", 0 },
    { INPUTEVENT_SPC_STATERESTORE6, "action_restore_state_6", 0 },
    { INPUTEVENT_SPC_STATERESTORE7, "action_restore_state_7", 0 },
    { INPUTEVENT_SPC_STATERESTORE8, "action_restore_state_8", 0 },
    { INPUTEVENT_SPC_STATERESTORE9, "action_restore_state_9", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_0_0, "action_drive_0_insert_floppy_0", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_0_1, "action_drive_0_insert_floppy_1", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_0_2, "action_drive_0_insert_floppy_2", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_0_3, "action_drive_0_insert_floppy_3", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_0_4, "action_drive_0_insert_floppy_4", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_0_5, "action_drive_0_insert_floppy_5", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_0_6, "action_drive_0_insert_floppy_6", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_0_7, "action_drive_0_insert_floppy_7", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_0_8, "action_drive_0_insert_floppy_8", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_0_9, "action_drive_0_insert_floppy_9", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_0_10, "action_drive_0_insert_floppy_10", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_0_11, "action_drive_0_insert_floppy_11", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_0_12, "action_drive_0_insert_floppy_12", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_0_13, "action_drive_0_insert_floppy_13", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_0_14, "action_drive_0_insert_floppy_14", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_0_15, "action_drive_0_insert_floppy_15", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_0_16, "action_drive_0_insert_floppy_16", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_0_17, "action_drive_0_insert_floppy_17", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_0_18, "action_drive_0_insert_floppy_18", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_0_19, "action_drive_0_insert_floppy_19", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_1_0, "action_drive_1_insert_floppy_0", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_1_1, "action_drive_1_insert_floppy_1", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_1_2, "action_drive_1_insert_floppy_2", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_1_3, "action_drive_1_insert_floppy_3", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_1_4, "action_drive_1_insert_floppy_4", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_1_5, "action_drive_1_insert_floppy_5", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_1_6, "action_drive_1_insert_floppy_6", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_1_7, "action_drive_1_insert_floppy_7", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_1_8, "action_drive_1_insert_floppy_8", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_1_9, "action_drive_1_insert_floppy_9", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_1_10, "action_drive_1_insert_floppy_10", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_1_11, "action_drive_1_insert_floppy_11", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_1_12, "action_drive_1_insert_floppy_12", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_1_13, "action_drive_1_insert_floppy_13", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_1_14, "action_drive_1_insert_floppy_14", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_1_15, "action_drive_1_insert_floppy_15", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_1_16, "action_drive_1_insert_floppy_16", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_1_17, "action_drive_1_insert_floppy_17", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_1_18, "action_drive_1_insert_floppy_18", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_1_19, "action_drive_1_insert_floppy_19", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_2_0, "action_drive_2_insert_floppy_0", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_2_1, "action_drive_2_insert_floppy_1", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_2_2, "action_drive_2_insert_floppy_2", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_2_3, "action_drive_2_insert_floppy_3", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_2_4, "action_drive_2_insert_floppy_4", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_2_5, "action_drive_2_insert_floppy_5", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_2_6, "action_drive_2_insert_floppy_6", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_2_7, "action_drive_2_insert_floppy_7", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_2_8, "action_drive_2_insert_floppy_8", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_2_9, "action_drive_2_insert_floppy_9", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_2_10, "action_drive_2_insert_floppy_10", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_2_11, "action_drive_2_insert_floppy_11", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_2_12, "action_drive_2_insert_floppy_12", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_2_13, "action_drive_2_insert_floppy_13", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_2_14, "action_drive_2_insert_floppy_14", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_2_15, "action_drive_2_insert_floppy_15", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_2_16, "action_drive_2_insert_floppy_16", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_2_17, "action_drive_2_insert_floppy_17", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_2_18, "action_drive_2_insert_floppy_18", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_2_19, "action_drive_2_insert_floppy_19", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_3_0, "action_drive_3_insert_floppy_0", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_3_1, "action_drive_3_insert_floppy_1", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_3_2, "action_drive_3_insert_floppy_2", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_3_3, "action_drive_3_insert_floppy_3", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_3_4, "action_drive_3_insert_floppy_4", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_3_5, "action_drive_3_insert_floppy_5", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_3_6, "action_drive_3_insert_floppy_6", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_3_7, "action_drive_3_insert_floppy_7", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_3_8, "action_drive_3_insert_floppy_8", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_3_9, "action_drive_3_insert_floppy_9", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_3_10, "action_drive_3_insert_floppy_10", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_3_11, "action_drive_3_insert_floppy_11", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_3_12, "action_drive_3_insert_floppy_12", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_3_13, "action_drive_3_insert_floppy_13", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_3_14, "action_drive_3_insert_floppy_14", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_3_15, "action_drive_3_insert_floppy_15", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_3_16, "action_drive_3_insert_floppy_16", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_3_17, "action_drive_3_insert_floppy_17", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_3_18, "action_drive_3_insert_floppy_18", 0 },
    { INPUTEVENT_SPC_DISKSWAPPER_3_19, "action_drive_3_insert_floppy_19", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_0_NONE, "action_joyport_0_mode_none", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_0_MOUSE, "action_joyport_0_mode_mouse", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_0_DJOY, "action_joyport_0_mode_djoy", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_0_GAMEPAD, "action_joyport_0_mode_gamepad", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_0_AJOY, "action_joyport_0_mode_ajoy", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_0_CDTVJOY, "action_joyport_0_mode_cdtvjoy", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_0_CD32JOY, "action_joyport_0_mode_cd32joy", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_0_LIGHTPEN, "action_joyport_0_mode_lightpen", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_1_NONE, "action_joyport_1_mode_none", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_1_MOUSE, "action_joyport_1_mode_mouse", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_1_DJOY, "action_joyport_1_mode_djoy", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_1_GAMEPAD, "action_joyport_1_mode_gamepad", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_1_AJOY, "action_joyport_1_mode_ajoy", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_1_CDTVJOY, "action_joyport_1_mode_cdtvjoy", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_1_CD32JOY, "action_joyport_1_mode_cd32joy", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_1_LIGHTPEN, "action_joyport_1_mode_lightpen", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_2_NONE, "action_joyport_2_mode_none", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_2_MOUSE, "action_joyport_2_mode_mouse", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_2_DJOY, "action_joyport_2_mode_djoy", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_2_GAMEPAD, "action_joyport_2_mode_gamepad", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_2_AJOY, "action_joyport_2_mode_ajoy", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_2_CDTVJOY, "action_joyport_2_mode_cdtvjoy", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_2_CD32JOY, "action_joyport_2_mode_cd32joy", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_2_LIGHTPEN, "action_joyport_2_mode_lightpen", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_3_NONE, "action_joyport_3_mode_none", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_3_MOUSE, "action_joyport_3_mode_mouse", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_3_DJOY, "action_joyport_3_mode_djoy", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_3_GAMEPAD, "action_joyport_3_mode_gamepad", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_3_AJOY, "action_joyport_3_mode_ajoy", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_3_CDTVJOY, "action_joyport_3_mode_cdtvjoy", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_3_CD32JOY, "action_joyport_3_mode_cd32joy", 0 },
    { INPUTEVENT_AMIGA_JOYPORT_MODE_3_LIGHTPEN, "action_joyport_3_mode_lightpen", 0 },

    { INPUTEVENT_SPC_ENTERDEBUGGER, "action_enter_debugger", 0 },

    { 65536, "action_none", 0 },
    { 0, 0, 0 },
};

static int hotkey_function(int key_code, int key_mod) {
    //write_log("hotkey: %d mod %d\n", key_code, key_mod);
    switch (key_code) {
    case FS_ML_KEY_R:
        fs_emu_log("hot key: soft reset\n");
        fs_emu_warning(_("Soft Reset"));
        fs_emu_queue_action(INPUTEVENT_SPC_SOFTRESET, 1);
        return 0;
    case FS_ML_KEY_T:
        fs_emu_log("hot key: hard reset\n");
        fs_emu_warning(_("Hard Reset"));
        fs_emu_queue_action(INPUTEVENT_SPC_HARDRESET, 1);
        return 0;
    case FS_ML_KEY_A:
        fs_emu_log("hot key: freeze button\n");
        fs_emu_queue_action(INPUTEVENT_SPC_FREEZEBUTTON, 1);
        return 0;
    case FS_ML_KEY_D:
        fs_emu_log("hot key: enter debugger\n");
        if (fs_config_get_boolean("console_debugger") == 1) {
            fs_emu_warning(_("Activated debugger"));
            fs_emu_queue_action(INPUTEVENT_SPC_ENTERDEBUGGER, 1);
        }
        else {
            fs_emu_warning(_("Option \"%s\" is not enabled"),
                    "console_debugger");
        }
        return 0;
    }
    return 0;
}

void fs_uae_configure_actions() {
    fs_log("fs_uae_configure_actions\n");
    fs_emu_set_actions(g_actions);
    for (int i = 0; i < FS_UAE_NUM_INPUT_PORTS; i++) {
        fs_uae_read_override_actions_for_port(i);
    }
    fs_emu_set_hotkey_function(hotkey_function);
}
