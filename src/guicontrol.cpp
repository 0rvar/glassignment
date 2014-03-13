#include "guicontrol.hpp"

static GtkBuilder *builder;
static GtkWidget *window;

GtkWidget *gui_light_shower;
GtkWidget *gui_ambient_shower;

gchar* gui_get_off_file() {
  return gtk_file_chooser_get_filename((GtkFileChooser*)gtk_builder_get_object(builder,"off_chooser"));
}

void gui_set_off_file(gchar* filename) {
  gtk_file_chooser_set_filename((GtkFileChooser*)gtk_builder_get_object(builder, "off_chooser"), filename);
}

void gui_set_move_mode(gint index) {
  gtk_combo_box_set_active((GtkComboBox*)gtk_builder_get_object(builder,"move_mode"), index < -1 ? -1 : index > 1 ? 1 : index);
}

gint gui_get_move_mode() {
  return gtk_combo_box_get_active((GtkComboBox*)gtk_builder_get_object(builder,"move_mode"));
}


void gui_set_flip_normals(gboolean b) {
 gtk_toggle_button_set_active((GtkToggleButton*)gtk_builder_get_object(builder,"flip_normals"), b);
}


gboolean gui_get_flip_normals(void) {
  return gtk_toggle_button_get_active((GtkToggleButton*)gtk_builder_get_object(builder,"flip_normals"));
}

void gui_set_I_light(vec4 color) {
  gtk_range_set_value((GtkRange*)gtk_builder_get_object(builder,"I_light_r"),color.x);
  gtk_range_set_value((GtkRange*)gtk_builder_get_object(builder,"I_light_g"),color.y);
  gtk_range_set_value((GtkRange*)gtk_builder_get_object(builder,"I_light_b"),color.z);
}

GdkColor gui_get_I_light() {
  return gui_light_color;
}

void gui_set_I_ambient(vec4 color) {
  gtk_range_set_value((GtkRange*)gtk_builder_get_object(builder,"I_ambient_r"),color.x);
  gtk_range_set_value((GtkRange*)gtk_builder_get_object(builder,"I_ambient_g"),color.y);
  gtk_range_set_value((GtkRange*)gtk_builder_get_object(builder,"I_ambient_b"),color.z);
}

GdkColor gui_get_I_ambient(){
  return gui_ambient_color;
}

void gui_set_k_ambient(vec4 k) {
  gtk_range_set_value((GtkRange*)gtk_builder_get_object(builder,"k_ambient_r"), k.x);
  gtk_range_set_value((GtkRange*)gtk_builder_get_object(builder,"k_ambient_g"), k.y);
  gtk_range_set_value((GtkRange*)gtk_builder_get_object(builder,"k_ambient_b"), k.z);
}

void gui_get_k_ambient(gdouble k[3]) {
  k[0] = gtk_range_get_value((GtkRange*)gtk_builder_get_object(builder,"k_ambient_r"));
  k[1] = gtk_range_get_value((GtkRange*)gtk_builder_get_object(builder,"k_ambient_g"));
  k[2] = gtk_range_get_value((GtkRange*)gtk_builder_get_object(builder,"k_ambient_b"));
}

void gui_set_k_diffuse(vec4 k) {
  gtk_range_set_value((GtkRange*)gtk_builder_get_object(builder,"k_diffuse_r"), k.x);
  gtk_range_set_value((GtkRange*)gtk_builder_get_object(builder,"k_diffuse_g"), k.y);
  gtk_range_set_value((GtkRange*)gtk_builder_get_object(builder,"k_diffuse_b"), k.z);
}

void gui_get_k_diffuse(gdouble k[3]) {
  k[0] = gtk_range_get_value((GtkRange*)gtk_builder_get_object(builder,"k_diffuse_r"));
  k[1] = gtk_range_get_value((GtkRange*)gtk_builder_get_object(builder,"k_diffuse_g"));
  k[2] = gtk_range_get_value((GtkRange*)gtk_builder_get_object(builder,"k_diffuse_b"));
}


void gui_set_k_specular(vec4 k) {
  gtk_range_set_value((GtkRange*)gtk_builder_get_object(builder,"k_specular_r"), k.x);
  gtk_range_set_value((GtkRange*)gtk_builder_get_object(builder,"k_specular_g"), k.y);
  gtk_range_set_value((GtkRange*)gtk_builder_get_object(builder,"k_specular_b"), k.z);
}


void gui_get_k_specular(gdouble k[3]) {
  k[0] = gtk_range_get_value((GtkRange*)gtk_builder_get_object(builder,"k_specular_r"));
  k[1] = gtk_range_get_value((GtkRange*)gtk_builder_get_object(builder,"k_specular_g"));
  k[2] = gtk_range_get_value((GtkRange*)gtk_builder_get_object(builder,"k_specular_b"));
}

void gui_set_phong(guint16 phong) {
  gtk_spin_button_set_value((GtkSpinButton*)gtk_builder_get_object(builder,"phong"), 1 > phong ? 1 : phong);
}

gdouble gui_get_phong() {
  return gtk_spin_button_get_value((GtkSpinButton*)gtk_builder_get_object(builder,"phong"));
}

void gui_set_light_pos(vec3 p) {
  gtk_spin_button_set_value((GtkSpinButton*)gtk_builder_get_object(builder,"light_x"), p.x);
  gtk_spin_button_set_value((GtkSpinButton*)gtk_builder_get_object(builder,"light_y"), p.y);
  gtk_spin_button_set_value((GtkSpinButton*)gtk_builder_get_object(builder,"light_z"), p.z);
}

void guiInitWindow(const char* name) {
  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, name, (GError**)NULL);
  window = (GtkWidget *)(gtk_builder_get_object (builder, "window"));
  gtk_builder_connect_signals (builder, NULL);

  gui_light_shower = (GtkWidget *)gtk_builder_get_object(builder,"light_shower");
  gui_ambient_shower = (GtkWidget *)gtk_builder_get_object(builder,"ambient_shower");
}

/* Initialize GTK.
 */
void guiInit(int *argc, char** argv) {
  gtk_init(argc, &argv);
}

/* Calls a single GTK main loop iteration to process 
 * events (non-blocking).
 */
void guiMainIteration() {
  gtk_main_iteration_do(0);
}

void gui_draw_color_shower(GtkWidget *widget, GdkColor *color) {
  GdkGC *gc = gdk_gc_new((GdkDrawable*)widget->window);
  GdkColormap *cm = gtk_widget_get_colormap(widget);
  gdk_colormap_alloc_color(cm, color, FALSE, TRUE);
  gdk_gc_set_foreground(gc, color);
  gdk_draw_rectangle(widget->window, gc, TRUE, 0, 0, 
   widget->allocation.height, widget->allocation.width);
  g_object_unref(gc);
}

void gui_set_color(GtkRange *range, guint16 *color) {
  gdouble dvalue = gtk_range_get_value(range);
  guint16 ivalue = (guint32)(dvalue*65535.0);
  *color = ivalue; 
}



