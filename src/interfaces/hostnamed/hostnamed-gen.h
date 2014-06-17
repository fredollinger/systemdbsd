/*
 * Generated by gdbus-codegen 2.40.0. DO NOT EDIT.
 *
 * The license of this code is the same as for the source it was derived from.
 */

#ifndef __HOSTNAMED_GEN_H__
#define __HOSTNAMED_GEN_H__

#include <gio/gio.h>

G_BEGIN_DECLS


/* ------------------------------------------------------------------------ */
/* Declarations for org.freedesktop.hostname1 */

#define HOSTNAMED_TYPE_ (hostnamed__get_type ())
#define HOSTNAMED_(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), HOSTNAMED_TYPE_, Hostnamed))
#define HOSTNAMED_IS_(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), HOSTNAMED_TYPE_))
#define HOSTNAMED__GET_IFACE(o) (G_TYPE_INSTANCE_GET_INTERFACE ((o), HOSTNAMED_TYPE_, HostnamedIface))

struct _Hostnamed;
typedef struct _Hostnamed Hostnamed;
typedef struct _HostnamedIface HostnamedIface;

struct _HostnamedIface
{
  GTypeInterface parent_iface;


  gboolean (*handle_set_hostname) (
    Hostnamed *object,
    GDBusMethodInvocation *invocation,
    const gchar *arg_name,
    gboolean arg_user_interaction);

  gboolean (*handle_set_icon_name) (
    Hostnamed *object,
    GDBusMethodInvocation *invocation,
    const gchar *arg_name,
    gboolean arg_user_interaction);

  gboolean (*handle_set_pretty_hostname) (
    Hostnamed *object,
    GDBusMethodInvocation *invocation,
    const gchar *arg_name,
    gboolean arg_user_interaction);

  gboolean (*handle_set_static_hostname) (
    Hostnamed *object,
    GDBusMethodInvocation *invocation,
    const gchar *arg_name,
    gboolean arg_user_interaction);

  const gchar * (*get_hostname) (Hostnamed *object);

  const gchar * (*get_icon_name) (Hostnamed *object);

  const gchar * (*get_pretty_hostname) (Hostnamed *object);

  const gchar * (*get_static_hostname) (Hostnamed *object);

};

GType hostnamed__get_type (void) G_GNUC_CONST;

GDBusInterfaceInfo *hostnamed__interface_info (void);
guint hostnamed__override_properties (GObjectClass *klass, guint property_id_begin);


/* D-Bus method call completion functions: */
void hostnamed__complete_set_hostname (
    Hostnamed *object,
    GDBusMethodInvocation *invocation);

void hostnamed__complete_set_static_hostname (
    Hostnamed *object,
    GDBusMethodInvocation *invocation);

void hostnamed__complete_set_pretty_hostname (
    Hostnamed *object,
    GDBusMethodInvocation *invocation);

void hostnamed__complete_set_icon_name (
    Hostnamed *object,
    GDBusMethodInvocation *invocation);



/* D-Bus method calls: */
void hostnamed__call_set_hostname (
    Hostnamed *proxy,
    const gchar *arg_name,
    gboolean arg_user_interaction,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean hostnamed__call_set_hostname_finish (
    Hostnamed *proxy,
    GAsyncResult *res,
    GError **error);

gboolean hostnamed__call_set_hostname_sync (
    Hostnamed *proxy,
    const gchar *arg_name,
    gboolean arg_user_interaction,
    GCancellable *cancellable,
    GError **error);

void hostnamed__call_set_static_hostname (
    Hostnamed *proxy,
    const gchar *arg_name,
    gboolean arg_user_interaction,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean hostnamed__call_set_static_hostname_finish (
    Hostnamed *proxy,
    GAsyncResult *res,
    GError **error);

gboolean hostnamed__call_set_static_hostname_sync (
    Hostnamed *proxy,
    const gchar *arg_name,
    gboolean arg_user_interaction,
    GCancellable *cancellable,
    GError **error);

void hostnamed__call_set_pretty_hostname (
    Hostnamed *proxy,
    const gchar *arg_name,
    gboolean arg_user_interaction,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean hostnamed__call_set_pretty_hostname_finish (
    Hostnamed *proxy,
    GAsyncResult *res,
    GError **error);

gboolean hostnamed__call_set_pretty_hostname_sync (
    Hostnamed *proxy,
    const gchar *arg_name,
    gboolean arg_user_interaction,
    GCancellable *cancellable,
    GError **error);

void hostnamed__call_set_icon_name (
    Hostnamed *proxy,
    const gchar *arg_name,
    gboolean arg_user_interaction,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean hostnamed__call_set_icon_name_finish (
    Hostnamed *proxy,
    GAsyncResult *res,
    GError **error);

gboolean hostnamed__call_set_icon_name_sync (
    Hostnamed *proxy,
    const gchar *arg_name,
    gboolean arg_user_interaction,
    GCancellable *cancellable,
    GError **error);



/* D-Bus property accessors: */
const gchar *hostnamed__get_hostname (Hostnamed *object);
gchar *hostnamed__dup_hostname (Hostnamed *object);
void hostnamed__set_hostname (Hostnamed *object, const gchar *value);

const gchar *hostnamed__get_static_hostname (Hostnamed *object);
gchar *hostnamed__dup_static_hostname (Hostnamed *object);
void hostnamed__set_static_hostname (Hostnamed *object, const gchar *value);

const gchar *hostnamed__get_pretty_hostname (Hostnamed *object);
gchar *hostnamed__dup_pretty_hostname (Hostnamed *object);
void hostnamed__set_pretty_hostname (Hostnamed *object, const gchar *value);

const gchar *hostnamed__get_icon_name (Hostnamed *object);
gchar *hostnamed__dup_icon_name (Hostnamed *object);
void hostnamed__set_icon_name (Hostnamed *object, const gchar *value);


/* ---- */

#define HOSTNAMED_TYPE__PROXY (hostnamed__proxy_get_type ())
#define HOSTNAMED__PROXY(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), HOSTNAMED_TYPE__PROXY, HostnamedProxy))
#define HOSTNAMED__PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), HOSTNAMED_TYPE__PROXY, HostnamedProxyClass))
#define HOSTNAMED__PROXY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), HOSTNAMED_TYPE__PROXY, HostnamedProxyClass))
#define HOSTNAMED_IS__PROXY(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), HOSTNAMED_TYPE__PROXY))
#define HOSTNAMED_IS__PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), HOSTNAMED_TYPE__PROXY))

typedef struct _HostnamedProxy HostnamedProxy;
typedef struct _HostnamedProxyClass HostnamedProxyClass;
typedef struct _HostnamedProxyPrivate HostnamedProxyPrivate;

struct _HostnamedProxy
{
  /*< private >*/
  GDBusProxy parent_instance;
  HostnamedProxyPrivate *priv;
};

struct _HostnamedProxyClass
{
  GDBusProxyClass parent_class;
};

GType hostnamed__proxy_get_type (void) G_GNUC_CONST;

void hostnamed__proxy_new (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
Hostnamed *hostnamed__proxy_new_finish (
    GAsyncResult        *res,
    GError             **error);
Hostnamed *hostnamed__proxy_new_sync (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);

void hostnamed__proxy_new_for_bus (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
Hostnamed *hostnamed__proxy_new_for_bus_finish (
    GAsyncResult        *res,
    GError             **error);
Hostnamed *hostnamed__proxy_new_for_bus_sync (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);


/* ---- */

#define HOSTNAMED_TYPE__SKELETON (hostnamed__skeleton_get_type ())
#define HOSTNAMED__SKELETON(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), HOSTNAMED_TYPE__SKELETON, HostnamedSkeleton))
#define HOSTNAMED__SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), HOSTNAMED_TYPE__SKELETON, HostnamedSkeletonClass))
#define HOSTNAMED__SKELETON_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), HOSTNAMED_TYPE__SKELETON, HostnamedSkeletonClass))
#define HOSTNAMED_IS__SKELETON(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), HOSTNAMED_TYPE__SKELETON))
#define HOSTNAMED_IS__SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), HOSTNAMED_TYPE__SKELETON))

typedef struct _HostnamedSkeleton HostnamedSkeleton;
typedef struct _HostnamedSkeletonClass HostnamedSkeletonClass;
typedef struct _HostnamedSkeletonPrivate HostnamedSkeletonPrivate;

struct _HostnamedSkeleton
{
  /*< private >*/
  GDBusInterfaceSkeleton parent_instance;
  HostnamedSkeletonPrivate *priv;
};

struct _HostnamedSkeletonClass
{
  GDBusInterfaceSkeletonClass parent_class;
};

GType hostnamed__skeleton_get_type (void) G_GNUC_CONST;

Hostnamed *hostnamed__skeleton_new (void);


G_END_DECLS

#endif /* __HOSTNAMED_GEN_H__ */
