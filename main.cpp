#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <gtk/gtk.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server.h"
#include "client.h"
#include "dbmanager.h"
#include <openssl/crypto.h>


const std::string DB_PATH = "/home/edward/Development/SocketTalk/db/sockettalk.db";

typedef struct
{
    GtkWidget *window;
    GtkWidget *email_label;
    GtkWidget *email_entry;
    GtkWidget *password_label;
    GtkWidget *password_entry;
    GtkWidget *login_button;
} AppData;

static void on_login_button_clicked(GtkWidget *widget, gpointer user_data)
{
    g_print("Button clicked!\n");
}

static void create_main_window(AppData *data, GtkApplication *app)
{
    data->window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(data->window), "Login");
    gtk_window_set_default_size(GTK_WINDOW(data->window), 800, 600);
}

static void create_input_elements(AppData *data)
{
    GtkWidget *grid = gtk_grid_new();
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(data->window), main_box);

    gtk_widget_set_halign(main_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(main_box, GTK_ALIGN_CENTER);

    gtk_box_pack_start(GTK_BOX(main_box), grid, TRUE, TRUE, 0);

    GtkWidget *email_label = gtk_label_new("Email:");
    GtkWidget *password_label = gtk_label_new("Password:");
    gtk_grid_attach(GTK_GRID(grid), email_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), password_label, 0, 1, 1, 1);

    GtkWidget *email_entry = gtk_entry_new();
    GtkWidget *password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    gtk_grid_attach(GTK_GRID(grid), email_entry, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), password_entry, 1, 1, 1, 1);

    GtkWidget *login_button = gtk_button_new_with_label("Login");
    g_signal_connect(login_button, "clicked", G_CALLBACK(on_login_button_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), login_button, 0, 2, 2, 1);

    gtk_widget_set_halign(email_label, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(password_label, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(email_entry, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(password_entry, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(login_button, GTK_ALIGN_CENTER);

    gtk_widget_set_margin_bottom(email_label, 20);
    gtk_widget_set_margin_bottom(email_entry, 20);
    gtk_widget_set_margin_start(email_entry, 20);
    gtk_widget_set_margin_start(password_entry, 20);

    gtk_widget_set_margin_top(login_button, 20);

    gtk_widget_set_valign(email_label, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(password_label, GTK_ALIGN_CENTER);
}

static void activate(GtkApplication *app, gpointer user_data)
{
    AppData *data = (AppData *)user_data;
    create_main_window(data, app);
    create_input_elements(data);

    g_signal_connect(data->login_button, "clicked", G_CALLBACK(on_login_button_clicked), NULL);

    GtkCssProvider *cssProvider = gtk_css_provider_new();
    const gchar *css = "window { background-color: #133337; }";
    gtk_css_provider_load_from_data(cssProvider, css, -1, NULL);

    GtkStyleContext *context = gtk_widget_get_style_context(data->window);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_widget_show_all(data->window);
}

int main(int argc, char **argv)
{

    // GtkApplication *app;
    // int status;

    // AppData data;
    // app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    // g_signal_connect(app, "activate", G_CALLBACK(activate), &data);

    // status = g_application_run(G_APPLICATION(app), argc, argv);

    // g_object_unref(app);

    DatabaseManager &dbManager = DatabaseManager::getInstance();
    dbManager.connect("sockettalk.db");
    dbManager.createTables();

    Server server(8080);
    Client client("127.0.0.1", 8080);

    server.start();
    
    return 0;
}