#include <gtk/gtk.h>
#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Widget structure for passing multiple widgets
typedef struct {
    GtkWidget *entry;
    GtkWidget *label;
} Widgets;

// Shared queue
GAsyncQueue *queue;

// Mutex and condition variables for synchronization
GMutex mutex;
GCond cond;

// Producer thread function
void *producer(gpointer data) {
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(data));
    g_async_queue_push(queue, g_strdup(text));
    g_cond_signal(&cond);
    return NULL;
}

// Consumer thread function
void *consumer(gpointer data) {
    g_mutex_lock(&mutex);
    while(g_async_queue_length(queue) == 0) {
        g_cond_wait(&cond, &mutex);
    }
    gchar *text = g_async_queue_pop(queue);
    gtk_label_set_text(GTK_LABEL(data), text);
    g_free(text);
    g_mutex_unlock(&mutex);
    return NULL;
}

void send_message(GtkWidget* widget, gpointer data) {
    // Signal producer thread
    Widgets *widgets = (Widgets *) data;
    GtkWidget *entry = widgets->entry;
    GtkWidget *label = widgets->label;
    g_thread_new("producer", producer, entry);
    g_thread_new("consumer", consumer, label);
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *entry_vbox;
    
    GError *error = NULL;
    GThread *producer_thread, *consumer_thread;


    Widgets widgets;
    GtkWidget *description;
    GtkWidget *label;
    GtkWidget *entry;
    GtkWidget *button;

    GtkWidget *menubar;
    GtkWidget *fileMenu;
    GtkWidget *fileMi;
    GtkWidget *quitMi;

    // Initialize threads
    gdk_threads_init();

    // Initialize GTK and window
    gtk_init(&argc, &argv);
    

    // Declarations
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    vbox = gtk_vbox_new(FALSE, 0);
    entry_vbox = gtk_vbox_new(FALSE, 0);

    menubar = gtk_menu_bar_new();
    fileMenu = gtk_menu_new();
    fileMi = gtk_menu_item_new_with_label("File");
    quitMi = gtk_menu_item_new_with_label("Quit");

    label = gtk_label_new("");
    description = gtk_label_new("Send a text message:");
    entry = gtk_entry_new();
    button = gtk_button_new_with_label("Send Message");
    queue = g_async_queue_new();

    widgets.entry = entry;
    widgets.label = label;

    // Initialize mutex and condition variables
    queue = g_async_queue_new();
    g_mutex_init(&mutex);
    g_cond_init(&cond);

    // Window Properties
    gtk_window_set_title(GTK_WINDOW(window), "Lab 9");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 300);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_widget_show(window);

    // Create container subclass for menu bar
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Menu Bar Properties
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi), fileMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quitMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), fileMi);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    // Button Properties
    gtk_widget_set_tooltip_text(button, "Send Message");
    g_signal_connect(button, "clicked", 
        G_CALLBACK(send_message), &widgets);  
        
    // Add buttons to container and container to vbox
    gtk_box_pack_start (GTK_BOX (entry_vbox), label, TRUE, TRUE, 0); 
    gtk_box_pack_start (GTK_BOX (entry_vbox), description, TRUE, TRUE, 0);    
    gtk_box_pack_start (GTK_BOX (entry_vbox), entry, TRUE, TRUE, 0);    
    gtk_box_pack_start (GTK_BOX (vbox), entry_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);

    gtk_widget_show_all(window);

    g_signal_connect(window, "destroy",
        G_CALLBACK(gtk_main_quit), NULL);  
    g_signal_connect(G_OBJECT(quitMi), "activate",
        G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    
    gdk_threads_enter();
    gtk_main();

    // Wait for threads to finish
    g_thread_join(producer_thread);
    g_thread_join(consumer_thread);
    gdk_threads_leave();

    // Free mutex and condition variables
    g_mutex_clear(&mutex);
    g_cond_clear(&cond);
    // g_cond_clear(&producer_cv);
    // g_cond_clear(&consumer_cv);

    return 0;
}
// Print entire contents of message queue
// printf("Message Queue Contents:\n");
// for(int i = 0; i < MAX_QUEUE_SIZE; i++) {
//     printf("%s\n", message_queue[i]);
// }
// for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
//     // printf("%s\n", message_queue[(queue_front + i) % MAX_QUEUE_SIZE]);
// }
