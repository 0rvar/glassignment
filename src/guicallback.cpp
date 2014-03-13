#include "guicallback.hpp"

GdkColor gui_light_color;
GdkColor gui_ambient_color;

extern "C" void on_off_chooser_selection_changed(GtkFileChooser *filechooser, gpointer user_data) {
  gchar* filename = gtk_file_chooser_get_filename(filechooser);
  state.newModelFilename = filename;
}

extern "C" void on_flip_normals_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
  gboolean b = togglebutton->active;
  state.render.flip_normals = (bool)b;
  state.shouldReload = true;
}

extern "C" void on_move_mode_changed(GtkComboBox *combobox, gpointer user_data) {
  gint index = gtk_combo_box_get_active(combobox);
  printf("Move mode chosen: %d\n", index);
  //TODO
}

extern "C" void on_light_x_value_changed(GtkSpinButton*spinbutton,gpointer user_data) {
  gdouble value = gtk_spin_button_get_value(spinbutton);
  state.lighting.light_position.x = float(value);
  state.shouldUpdate = true;
}

extern "C" void on_light_y_value_changed(GtkSpinButton *spinbutton,gpointer user_data) {
  gdouble value = gtk_spin_button_get_value(spinbutton);
  state.lighting.light_position.y= float(value);
  state.shouldUpdate = true;
}

extern "C" void on_light_z_value_changed(GtkSpinButton*spinbutton, gpointer user_data) {
  gdouble value = gtk_spin_button_get_value(spinbutton);
  state.lighting.light_position.z = float(value);
  state.shouldUpdate = true;
}

extern "C" gboolean on_I_light_r_value_changing(GtkRange *range, gpointer user_data) {
  gui_set_color(range, &gui_light_color.red);
  gui_draw_color_shower(gui_light_shower, &gui_light_color);
  gtk_widget_queue_draw(gui_light_shower);

  return FALSE;
}

extern "C" gboolean on_I_light_g_value_changing(GtkRange *range, gpointer user_data) {
  gui_set_color(range, &gui_light_color.green);
  gui_draw_color_shower(gui_light_shower, &gui_light_color);
  gtk_widget_queue_draw(gui_light_shower);

  return FALSE;
}

extern "C" gboolean on_I_light_b_value_changing(GtkRange *range, gpointer user_data) {
  gui_set_color(range, &gui_light_color.blue);
  gui_draw_color_shower(gui_light_shower, &gui_light_color);
  gtk_widget_queue_draw(gui_light_shower);

  return FALSE;
}

extern "C" void on_I_light_value_changed(GdkColor color) {
  state.lighting.light_intensity = vec4(
    color.red   / 65536.0, 
    color.blue  / 65536.0,
    color.green / 65536.0
  );
  state.shouldUpdate = true;
}

extern "C" void on_I_light_r_value_changed (GtkRange *range, gpointer user_data) {
  on_I_light_r_value_changing(range, user_data);
  on_I_light_value_changed(gui_light_color);
}

extern "C" void on_I_light_g_value_changed (GtkRange *range, gpointer user_data) {
  on_I_light_g_value_changing(range, user_data);
  on_I_light_value_changed(gui_light_color);
}

extern "C" void on_I_light_b_value_changed (GtkRange *range, gpointer user_data) {
  on_I_light_b_value_changing(range, user_data);
  on_I_light_value_changed(gui_light_color);
}

extern "C" gboolean on_I_ambient_r_value_changing(GtkRange *range, gpointer user_data) {
  gui_set_color(range, &gui_ambient_color.red);
  gui_draw_color_shower(gui_ambient_shower, &gui_ambient_color);
  gtk_widget_queue_draw(gui_ambient_shower);

  return FALSE;
}

extern "C" gboolean on_I_ambient_g_value_changing(GtkRange *range, gpointer user_data) {
  gui_set_color(range, &gui_ambient_color.green);
  gui_draw_color_shower(gui_ambient_shower, &gui_ambient_color);
  gtk_widget_queue_draw(gui_ambient_shower);

  return FALSE;
}

extern "C" gboolean on_I_ambient_b_value_changing(GtkRange *range, gpointer user_data) {
  gui_set_color(range, &gui_ambient_color.blue);
  gui_draw_color_shower(gui_ambient_shower, &gui_ambient_color);
  gtk_widget_queue_draw(gui_ambient_shower);

  return FALSE;
}

extern "C" void on_I_ambient_value_changed(GdkColor color) {
  printf("ambient light set Irgb=(%i,%i,%i)\n",color.red,color.green,color.blue);
  state.lighting.ambient_intensity = vec4(
    color.red   / 65536.0, 
    color.blue  / 65536.0,
    color.green / 65536.0
  );
  state.shouldUpdate = true;
}

extern "C" void on_I_ambient_r_value_changed(GtkRange *range, gpointer user_data) {
  on_I_ambient_r_value_changing(range, user_data);
  on_I_ambient_value_changed(gui_ambient_color);
}

extern "C" void on_I_ambient_g_value_changed(GtkRange *range, gpointer user_data) {
  on_I_ambient_g_value_changing(range, user_data);
  on_I_ambient_value_changed(gui_ambient_color);
}

extern "C" void on_I_ambient_b_value_changed(GtkRange *range, gpointer user_data) {
  on_I_ambient_b_value_changing(range, user_data);
  on_I_ambient_value_changed(gui_ambient_color);
}

extern "C" void on_ambient_value_changed(GdkColor color) {
  printf("Ambient color set rgb=(%i,%i,%i)\n",color.red,color.green,color.blue);
}

extern "C" void on_k_ambient_r_value_changed(GtkRange *range, gpointer user_data) {
  gdouble value = gtk_range_get_value(range);
  state.lighting.material_ambient.x = float(value);
  state.shouldUpdate = true;
}

extern "C" void on_k_ambient_g_value_changed(GtkRange *range, gpointer user_data) {
  gdouble value = gtk_range_get_value(range);
  state.lighting.material_ambient.y = float(value);
  state.shouldUpdate = true;
}

extern "C" void on_k_ambient_b_value_changed(GtkRange *range, gpointer user_data) {
  gdouble value = gtk_range_get_value(range);
  state.lighting.material_ambient.z = float(value);
  state.shouldUpdate = true;
}

extern "C" void on_k_diffuse_r_value_changed(GtkRange *range, gpointer user_data) {
  gdouble value = gtk_range_get_value(range);
  state.lighting.material_diffuse.x = float(value);
  state.shouldUpdate = true;
}

extern "C" void on_k_diffuse_g_value_changed(GtkRange *range, gpointer user_data) {
  gdouble value = gtk_range_get_value(range);
  state.lighting.material_diffuse.y = float(value);
  state.shouldUpdate = true;
}

extern "C" void on_k_diffuse_b_value_changed (GtkRange *range, gpointer user_data) {
  gdouble value = gtk_range_get_value(range);
  state.lighting.material_diffuse.z = float(value);
  state.shouldUpdate = true;
}

extern "C" void on_k_specular_r_value_changed(GtkRange *range, gpointer user_data) {
  gdouble value = gtk_range_get_value(range);
  state.lighting.material_specular.x = float(value);
  state.shouldUpdate = true;
}

extern "C" void on_k_specular_g_value_changed(GtkRange *range, gpointer user_data) {
  gdouble value = gtk_range_get_value(range);
  state.lighting.material_specular.y = float(value);
  state.shouldUpdate = true;
}

extern "C" void on_k_specular_b_value_changed(GtkRange *range, gpointer user_data) {
  gdouble value = gtk_range_get_value(range);
  state.lighting.material_specular.z = float(value);
  state.shouldUpdate = true;
}

extern "C" void on_phong_value_changed(GtkSpinButton *spinbutton, gpointer user_data) {
  gint32 value = (gint32)round(gtk_spin_button_get_value(spinbutton));
  printf("Phong changed!\n");
  state.lighting.phong = int(value);
  state.shouldUpdate = true;
}

extern "C" void on_win_destroy_event() {
  exit(0);
}

extern "C" gboolean on_ambient_shower_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer user_data)  {
  gui_draw_color_shower(widget, &gui_ambient_color);

  return TRUE;
}

extern "C" gboolean on_light_shower_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer user_data) {
  gui_draw_color_shower(widget, &gui_light_color);

  return TRUE;
}
