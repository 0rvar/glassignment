#ifndef _GUICALLBACK_H_
#define _GUICALLBACK_H_

#include <gtk/gtk.h>
#include <stdlib.h>
#include <math.h>

#include "guicontrol.hpp"
#include "state.hpp"

/* GLOBAL VARIABLES */

extern GdkColor gui_light_color;
extern GdkColor gui_ambient_color;
extern GtkWidget *gui_light_shower;
extern GtkWidget *gui_ambient_shower;
extern State state;

/* CALLBACKS FROM GUI */

extern "C" void     on_off_chooser_selection_changed(GtkFileChooser*, gpointer);
extern "C" void     on_flip_normals_toggled(GtkToggleButton*, gpointer);
extern "C" void     on_move_mode_changed(GtkComboBox*, gpointer);
extern "C" void     on_light_x_value_changed(GtkSpinButton*, gpointer);
extern "C" void     on_light_y_value_changed(GtkSpinButton*, gpointer);
extern "C" void     on_light_z_value_changed(GtkSpinButton*, gpointer);
extern "C" void     on_I_light_value_changed(GdkColor);
extern "C" gboolean on_I_light_r_value_changing(GtkRange*,gpointer);
extern "C" void     on_I_light_r_value_changed(GtkRange*,gpointer);
extern "C" gboolean on_I_light_g_value_changing(GtkRange*, gpointer);
extern "C" void     on_I_light_g_value_changed(GtkRange*, gpointer);
extern "C" gboolean on_I_light_b_value_changing(GtkRange*, gpointer);
extern "C" void     on_I_light_b_value_changed(GtkRange*, gpointer);
extern "C" void     on_I_light_value_changed(GdkColor);
extern "C" gboolean on_I_ambient_r_value_changing(GtkRange*, gpointer);
extern "C" void     on_I_ambient_r_value_changed(GtkRange*, gpointer);
extern "C" gboolean on_I_ambient_g_value_changing(GtkRange*, gpointer);
extern "C" void     on_I_ambient_g_value_changed(GtkRange*, gpointer);
extern "C" gboolean on_I_ambient_b_value_changing(GtkRange*, gpointer);
extern "C" void     on_I_ambient_b_value_changed(GtkRange*, gpointer);
extern "C" void     on_k_ambient_r_value_changed(GtkRange*, gpointer);
extern "C" void     on_k_ambient_g_value_changed(GtkRange*, gpointer);
extern "C" void     on_k_ambient_b_value_changed(GtkRange*, gpointer);
extern "C" void     on_k_diffuse_r_value_changed(GtkRange*, gpointer);
extern "C" void     on_k_diffuse_g_value_changed(GtkRange*, gpointer);
extern "C" void     on_k_diffuse_b_value_changed(GtkRange*, gpointer);
extern "C" void     on_k_specular_r_value_changed(GtkRange*, gpointer);
extern "C" void     on_k_specular_g_value_changed(GtkRange*, gpointer);
extern "C" void     on_k_specular_b_value_changed(GtkRange*, gpointer);
extern "C" void     on_phong_value_changed(GtkSpinButton*, gpointer);
extern "C" gboolean on_light_shower_expose_event(GtkWidget*, GdkEventExpose*, gpointer);
extern "C" gboolean on_ambient_shower_expose_event(GtkWidget*, GdkEventExpose*, gpointer);
extern "C" void     on_win_destroy_event();

#endif
