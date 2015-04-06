#include <gtk/gtk.h>


void
main_window_on_button_add_clicked      (gpointer user_data,
                                        GtkButton* button);

void
main_window_on_button_delete_clicked   (gpointer user_data,
                                        GtkButton* button);

void
main_window_on_button_edit_clicked     (gpointer user_data,
                                        GtkButton* button);
void
main_window_on_button_find_clicked     (gpointer user_data,
                                        GtkButton* button);

void
main_window_on_button_load_clicked     (gpointer user_data,
                                        GtkButton* button);

void
main_window_on_button_save_clicked     (gpointer user_data,
                                        GtkButton* button);

void
main_window_on_button_exit_clicked     (gpointer user_data,
                                        GtkButton* button);

void
edit_window_on_button_ok_clicked       (gpointer user_data,
                                        GtkButton* button);

void
edit_window_on_button_cancel_clicked   (gpointer user_data,
                                        GtkButton* button);

void main_window_init(GtkWidget* main_window);

typedef struct _Contact
{
	char* name;
	char* company;
	char* mobile_phone;
	char* office_phone;
	char* address;
	char* post_code;
	char* birthday;
}Contact;

