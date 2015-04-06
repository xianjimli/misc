#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <sqlite3.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"

enum
{
	COL_ID,
	COL_NAME,
	COL_COMPANY,
	COL_MOBILE_PHONE,
	COL_OFFICE_PHONE,
	COL_ADDRESS,
	COL_POST_CODE,
	COL_BIRTHDAY,
	COL_NR
};

#define lookup_entry(widget, name) GTK_ENTRY(lookup_widget(widget, name))
typedef void (*OnEditDoneFunc)(gpointer user_data, Contact* contact);

void main_window_on_edit_done(gpointer user_data, Contact* contact)
{
	GtkWidget*   main_window = GTK_WIDGET(user_data);
	GtkTreeView* tree_view = GTK_TREE_VIEW(lookup_widget(user_data, "treeview_contacts"));
	GtkListStore* model = GTK_LIST_STORE(gtk_tree_view_get_model(tree_view));
	GtkTreeIter*  edit_iter = (GtkTreeIter*)g_object_get_data(G_OBJECT(main_window), "edit_iter");

	GtkTreeIter* iter = NULL;
	GtkTreeIter new_iter = {0};

	if(edit_iter != NULL)
	{
		g_object_set_data(G_OBJECT(main_window), "edit_iter", NULL);
		iter = edit_iter;
	}
	else
	{
		gtk_list_store_append (model, &new_iter);
		iter = &new_iter;
	}

	if(contact != NULL)
	{
		gtk_list_store_set (model, iter, COL_NAME, contact->name, -1);
		gtk_list_store_set (model, iter, COL_COMPANY, contact->company, -1);
		gtk_list_store_set (model, iter, COL_MOBILE_PHONE, contact->mobile_phone, -1);
		gtk_list_store_set (model, iter, COL_OFFICE_PHONE, contact->office_phone, -1);
		gtk_list_store_set (model, iter, COL_ADDRESS, contact->address, -1);
		gtk_list_store_set (model, iter, COL_POST_CODE, contact->post_code, -1);
		gtk_list_store_set (model, iter, COL_BIRTHDAY, contact->birthday, -1);
	}

	if(edit_iter != NULL)
	{
		gtk_tree_iter_free(edit_iter);
	}

	return;
}

void main_window_init(GtkWidget* main_window)
{
	int i = 0;
	GtkCellRenderer* renderer = NULL;
	GtkTreeView* tree_view = GTK_TREE_VIEW(lookup_widget(main_window, "treeview_contacts"));

	const char* titles[COL_NR] = 
	{
		N_("ID"), 
		N_("Name"), 
		N_("Company"), 
		N_("Mobile phone"), 
		N_("Office phone"), 
		N_("Address"), 
		N_("Post code"), 
		N_("Birthday")
	};

	for(i = COL_NAME; i < COL_NR; i++)
	{
		GtkTreeViewColumn*  col = gtk_tree_view_column_new();
    	GtkCellRenderer* renderer = gtk_cell_renderer_text_new();
		gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), col);
    	gtk_tree_view_column_set_title(col, _(titles[i]));
		gtk_tree_view_column_set_clickable(col, TRUE);

    	g_object_set (renderer, "xalign", 0.0, NULL);
	    gtk_tree_view_column_pack_start(col, renderer, FALSE);
    	gtk_tree_view_column_add_attribute(col, renderer, "text", i);
    }

	GtkListStore* model = gtk_list_store_new (COL_NR,  G_TYPE_INT, G_TYPE_STRING,
		G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	gtk_tree_view_set_model(tree_view, GTK_TREE_MODEL(model));
	gtk_tree_view_set_headers_visible(tree_view, TRUE);

	return;
}

GtkWidget* main_window_create_edit_window (GtkWidget* main_window, Contact* contact)
{
	GtkWidget* edit_window = create_edit_window();
	
	g_object_set_data(G_OBJECT(edit_window), "on_edit_done", main_window_on_edit_done);
	g_object_set_data(G_OBJECT(edit_window), "on_edit_done_ctx", main_window);

	if(contact == NULL)
	{
		return edit_window;
	}

	gtk_entry_set_text(lookup_entry(edit_window, "entry_name"), contact->name);
	gtk_entry_set_text(lookup_entry(edit_window, "entry_company"), contact->company);
	gtk_entry_set_text(lookup_entry(edit_window, "entry_mobile_phone"), contact->mobile_phone);
	gtk_entry_set_text(lookup_entry(edit_window, "entry_office_phone"), contact->office_phone);
	gtk_entry_set_text(lookup_entry(edit_window, "entry_address"), contact->address);
	gtk_entry_set_text(lookup_entry(edit_window, "entry_post_code"), contact->post_code);
	gtk_entry_set_text(lookup_entry(edit_window, "entry_birthday"), contact->birthday);

	return edit_window;
}

void
main_window_on_button_add_clicked      (gpointer user_data,
                                        GtkButton* button)
{
	GtkWidget* win = main_window_create_edit_window(GTK_WIDGET(user_data), NULL);
	gtk_widget_show(win);

	return;
}


void
main_window_on_button_delete_clicked   (gpointer user_data,
                                        GtkButton* button)
{
	GtkTreeIter       treeiter = {0};
	GtkTreeSelection* selection = NULL;
	GtkTreeView* tree_view = GTK_TREE_VIEW(lookup_widget(user_data, "treeview_contacts"));
	GtkListStore* model = GTK_LIST_STORE(gtk_tree_view_get_model(tree_view));

	selection   = gtk_tree_view_get_selection(tree_view);

	if(gtk_tree_selection_get_selected(selection, (GtkTreeModel**)&model, &treeiter))
	{
		gtk_list_store_remove(model, &treeiter);
	}

	return;	
}

static void main_window_get_contact(GtkTreeModel* model, GtkTreeIter* iter, Contact* contact)
{
	GValue value = {0};
	gtk_tree_model_get_value(GTK_TREE_MODEL(model), iter, COL_NAME, &value);
	contact->name = g_strdup(g_value_get_string(&value));

	g_value_unset(&value);
	gtk_tree_model_get_value(GTK_TREE_MODEL(model), iter, COL_COMPANY, &value);
	contact->company = g_strdup(g_value_get_string(&value));

	g_value_unset(&value);
	gtk_tree_model_get_value(GTK_TREE_MODEL(model), iter, COL_MOBILE_PHONE, &value);
	contact->mobile_phone = g_strdup(g_value_get_string(&value));

	g_value_unset(&value);
	gtk_tree_model_get_value(GTK_TREE_MODEL(model), iter, COL_OFFICE_PHONE, &value);
	contact->office_phone = g_strdup(g_value_get_string(&value));

	g_value_unset(&value);
	gtk_tree_model_get_value(GTK_TREE_MODEL(model), iter, COL_ADDRESS, &value);
	contact->address = g_strdup(g_value_get_string(&value));
	
	g_value_unset(&value);
	gtk_tree_model_get_value(GTK_TREE_MODEL(model), iter, COL_POST_CODE, &value);
	contact->post_code = g_strdup(g_value_get_string(&value));
	
	g_value_unset(&value);
	gtk_tree_model_get_value(GTK_TREE_MODEL(model), iter, COL_BIRTHDAY, &value);
	contact->birthday = g_strdup(g_value_get_string(&value));

	return;
}

void
main_window_on_button_edit_clicked     (gpointer user_data,
                                        GtkButton* button)
{
	GtkTreeIter       treeiter = {0};
	GtkTreeSelection* selection = NULL;
	GtkWidget* main_window = GTK_WIDGET(user_data);
	GtkTreeView* tree_view = GTK_TREE_VIEW(lookup_widget(user_data, "treeview_contacts"));
	GtkListStore* model = GTK_LIST_STORE(gtk_tree_view_get_model(tree_view));

	selection   = gtk_tree_view_get_selection(tree_view);

	if(gtk_tree_selection_get_selected(selection, (GtkTreeModel**)&model, &treeiter))
	{
		Contact contact = {0};

		main_window_get_contact(GTK_TREE_MODEL(model), &treeiter, &contact);

		g_object_set_data(G_OBJECT(main_window), "edit_iter", gtk_tree_iter_copy(&treeiter));
		GtkWidget* win = main_window_create_edit_window(GTK_WIDGET(user_data), &contact);

		gtk_widget_show(win);

		g_free(contact.name);
		g_free(contact.company);
		g_free(contact.mobile_phone);
		g_free(contact.office_phone);
		g_free(contact.address);
		g_free(contact.post_code);
		g_free(contact.birthday);
	}

	return;
}

void
main_window_on_button_find_clicked     (gpointer user_data,
                                        GtkButton* button)
{
	return;
}

#define DB_FILE_NAME "contacts.db"

static int db_load_callback(gpointer user_data, int argc, char **argv, char **azColName)
{
	int i = 0;
	GtkTreeIter iter = {0};
	GtkTreeModel* model = GTK_TREE_MODEL(user_data);
	gtk_list_store_append (GTK_LIST_STORE(model), &iter);
	
	const char* col_names[COL_NR] = 
	{
		"rowid", 
		"name", 
		"company", 
		"mobile_phone", 
		"office_phone", 
		"address", 
		"post_code", 
		"birthday"
	};

	for(i=0; i<argc; i++)
	{
		int j = 0;
		for(j = 0; j < COL_NR; j++)
		{
			if(strcmp(azColName[i], col_names[j]) == 0)
			{
				gtk_list_store_set(GTK_LIST_STORE(model), &iter, j, argv[i], -1);
				break;
			}
		}
	}

  return 0;
}

void
main_window_on_button_load_clicked     (gpointer user_data,
                                        GtkButton* button)
{
	sqlite3 *db = NULL;
	int ret = sqlite3_open(DB_FILE_NAME, &db);

	if(ret == 0)
	{
		char* error = NULL;
		const char* sql = "select * from contacts;";
		GtkTreeView* tree_view = GTK_TREE_VIEW(lookup_widget(user_data, "treeview_contacts"));
		GtkListStore* model = GTK_LIST_STORE(gtk_tree_view_get_model(tree_view));
		gtk_list_store_clear(model);

		if((ret = sqlite3_exec(db, sql, db_load_callback, model, &error)) != 0)
		{
			g_debug("ret=%d error=%s", ret, error);
			g_free(error);
		}

		sqlite3_close(db)	;
	}

	return;
}

static int db_save_callback(gpointer user_data, int argc, char **argv, char **azColName)
{
	return 0;
}

#define NONE_STR(str) (str) != NULL ? (str) : ""
static gboolean save_data(GtkTreeModel *model, GtkTreePath *path, GtkTreeIter *iter, gpointer data)
{
	sqlite3 *db = data;
	Contact contact = {0};
	main_window_get_contact(GTK_TREE_MODEL(model), iter, &contact);

	if(contact.name != NULL)
	{
		char* error = NULL;
		char* sql = g_strdup_printf("insert into contacts (name,company,mobile_phone,office_phone,address,post_code,birthday) values ('%s', '%s', '%s','%s','%s','%s','%s');", NONE_STR(contact.name), NONE_STR(contact.company), NONE_STR(contact.mobile_phone),NONE_STR(contact.office_phone),NONE_STR(contact.address),NONE_STR(contact.post_code),NONE_STR(contact.birthday));

		int ret = sqlite3_exec(db, sql, db_save_callback, NULL, &error);
		if(ret != 0)
		{
			g_debug("ret=%d error=%s", ret, error);
			g_free(error);
		}
	}

	return FALSE;
}

void
main_window_on_button_save_clicked     (gpointer user_data,
                                        GtkButton* button)
{
	sqlite3 *db = NULL;
	int ret = sqlite3_open(DB_FILE_NAME, &db);
	GtkTreeView* tree_view = GTK_TREE_VIEW(lookup_widget(user_data, "treeview_contacts"));
	GtkListStore* model = GTK_LIST_STORE(gtk_tree_view_get_model(tree_view));

	if(ret == 0)
	{
		char* error = NULL;
		const char* sql = "create table IF NOT EXISTS contacts (name char(20), company char(20), mobile_phone char(20), office_phone char (20), address char(60), post_code char(10), birthday date);";
		int ret = sqlite3_exec(db, sql, db_save_callback, user_data, &error);
		if(ret != 0)
		{
			g_debug("ret=%d error=%s", ret, error);
			g_free(error);
		}

		sql = "delete from contacts;";
		ret = sqlite3_exec(db, sql, db_save_callback, user_data, &error);
		if(ret != 0)
		{
			g_debug("ret=%d error=%s", ret, error);
			g_free(error);
		}
		
		gtk_tree_model_foreach(GTK_TREE_MODEL(model), save_data, db);

		sqlite3_close(db);
	}

	return;
}


void
main_window_on_button_exit_clicked     (gpointer user_data,
                                        GtkButton* button)
{
	gtk_widget_destroy(GTK_WIDGET(user_data));

	gtk_main_quit();

	return;
}


void
edit_window_on_button_ok_clicked       (gpointer user_data,
                                        GtkButton* button)
{
	GtkWidget* edit_window = GTK_WIDGET(user_data);
	OnEditDoneFunc on_edit_done = g_object_get_data(G_OBJECT(user_data), "on_edit_done");
	gpointer on_edit_done_ctx = g_object_get_data(G_OBJECT(user_data), "on_edit_done_ctx");

	if(on_edit_done != NULL)
	{
		Contact* contact = g_new0(Contact, 1);

		contact->name = (char*)gtk_entry_get_text(lookup_entry(edit_window, "entry_name"));
		contact->company = (char*)gtk_entry_get_text(lookup_entry(edit_window, "entry_company"));
		contact->mobile_phone = (char*)gtk_entry_get_text(lookup_entry(edit_window, "entry_mobile_phone"));
		contact->office_phone = (char*)gtk_entry_get_text(lookup_entry(edit_window, "entry_office_phone"));
		contact->address = (char*)gtk_entry_get_text(lookup_entry(edit_window, "entry_address"));
		contact->post_code = (char*)gtk_entry_get_text(lookup_entry(edit_window, "entry_post_code"));
		contact->birthday = (char*)gtk_entry_get_text(lookup_entry(edit_window, "entry_birthday"));
		
		on_edit_done(on_edit_done_ctx, contact);
		g_free(contact);
	}

	gtk_widget_destroy(edit_window);

	return;
}


void
edit_window_on_button_cancel_clicked   (gpointer user_data,
                                        GtkButton* button)
{
	GtkWidget* edit_window = GTK_WIDGET(user_data);
	OnEditDoneFunc on_edit_done = g_object_get_data(G_OBJECT(user_data), "on_edit_done");
	gpointer on_edit_done_ctx = g_object_get_data(G_OBJECT(user_data), "on_edit_done_ctx");

	if(on_edit_done != NULL)
	{
		on_edit_done(on_edit_done_ctx, NULL);
	}

	gtk_widget_destroy(GTK_WIDGET(user_data));

	return;
}


