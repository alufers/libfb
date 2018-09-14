#include <stdio.h>
#include <api.h>
#include <gio/gio.h>
#include <libsoup/soup.h>
#include <glib.h>
static GMainLoop *loop = NULL;

static void onError (FbApi* api, GError* err, gpointer data) {
  printf(err->message);
  g_main_loop_quit(loop);
}

static void onConnect (FbApi* api) {
  printf("Connected ");

  // fb_api_message(api, 100002974638116, FALSE, "eluwa witam z api");
}
static void authed (FbApi* api) {
  printf("Authorization done");
  fb_api_connect(api, FALSE);
  

}
typedef struct fb_api_user fb_api_user_t;

static void contacts (FbApi* api, GSList *users) {
  printf("ddd: Contacts");
  GSList        *l;

  
  for (l = users; l != NULL; l = l->next) {
    FbApiUser* user = (FbApiUser*)l->data;
      printf(user->name);
      guint64 myVal = user->uid;
      printf("value: %" G_GUINT64_FORMAT "\n", myVal);
      
  }
  g_main_loop_quit(loop);
}

int main(int argc, char **argv) {
  printf("fblib.\n");

  GSocketClient* sock = g_socket_client_new();
  SoupSession* sesssion = soup_session_new();
  g_object_set(G_OBJECT(sesssion), "use-thread-context", TRUE, NULL);

  
  g_socket_client_set_timeout(sock, 10);
  FbApi* api = fb_api_new(sock, sesssion);
  g_signal_connect(api, "error", G_CALLBACK(onError), NULL);
  g_signal_connect(api, "connect", G_CALLBACK(onConnect), NULL);
  g_signal_connect(api, "contacts", G_CALLBACK(contacts), NULL);
  g_signal_connect(api, "auth", G_CALLBACK(authed), NULL);
  
  fb_api_rehash(api);
  
  fb_api_auth(api, "mail", "pass");
  loop = g_main_loop_new(soup_session_get_async_context(sesssion), TRUE);
  g_main_run(loop);
  return 0;
}
