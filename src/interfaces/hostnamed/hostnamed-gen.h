/*
 * Generated by gdbus-codegen 2.40.0. DO NOT EDIT.
 *
 * The license of this code is the same as for the source it was derived from.
 */

#ifndef __SRC_INTERFACES_HOSTNAMED_HOSTNAMED_GEN_H__
#define __SRC_INTERFACES_HOSTNAMED_HOSTNAMED_GEN_H__

#include <gio/gio.h>

G_BEGIN_DECLS


/* ------------------------------------------------------------------------ */
/* Declarations for org.freedesktop.hostname1 */

#define HOSTNAMED_TYPE_HOSTNAME1 (hostnamed_hostname1_get_type ())
#define HOSTNAMED_HOSTNAME1(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), HOSTNAMED_TYPE_HOSTNAME1, hostnamedHostname1))
#define HOSTNAMED_IS_HOSTNAME1(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), HOSTNAMED_TYPE_HOSTNAME1))
#define HOSTNAMED_HOSTNAME1_GET_IFACE(o) (G_TYPE_INSTANCE_GET_INTERFACE ((o), HOSTNAMED_TYPE_HOSTNAME1, hostnamedHostname1Iface))

struct _hostnamedHostname1;
typedef struct _hostnamedHostname1 hostnamedHostname1;
typedef struct _hostnamedHostname1Iface hostnamedHostname1Iface;

struct _hostnamedHostname1Iface
{
  GTypeInterface parent_iface;


  gboolean (*handle_set_chassis) (
    hostnamedHostname1 *object,
    GDBusMethodInvocation *invocation,
    const gchar *arg_unnamed_arg0,
    gboolean arg_unnamed_arg1);

  gboolean (*handle_set_hostname) (
    hostnamedHostname1 *object,
    GDBusMethodInvocation *invocation,
    const gchar *arg_unnamed_arg0,
    gboolean arg_unnamed_arg1);

  gboolean (*handle_set_icon_name) (
    hostnamedHostname1 *object,
    GDBusMethodInvocation *invocation,
    const gchar *arg_unnamed_arg0,
    gboolean arg_unnamed_arg1);

  gboolean (*handle_set_pretty_hostname) (
    hostnamedHostname1 *object,
    GDBusMethodInvocation *invocation,
    const gchar *arg_unnamed_arg0,
    gboolean arg_unnamed_arg1);

  gboolean (*handle_set_static_hostname) (
    hostnamedHostname1 *object,
    GDBusMethodInvocation *invocation,
    const gchar *arg_unnamed_arg0,
    gboolean arg_unnamed_arg1);

  const gchar * (*get_chassis) (hostnamedHostname1 *object);

  const gchar * (*get_hostname) (hostnamedHostname1 *object);

  const gchar * (*get_icon_name) (hostnamedHostname1 *object);

  const gchar * (*get_kernel_name) (hostnamedHostname1 *object);

  const gchar * (*get_kernel_release) (hostnamedHostname1 *object);

  const gchar * (*get_kernel_version) (hostnamedHostname1 *object);

  const gchar * (*get_operating_system_cpename) (hostnamedHostname1 *object);

  const gchar * (*get_operating_system_pretty_name) (hostnamedHostname1 *object);

  const gchar * (*get_pretty_hostname) (hostnamedHostname1 *object);

  const gchar * (*get_static_hostname) (hostnamedHostname1 *object);

};

GType hostnamed_hostname1_get_type (void) G_GNUC_CONST;

GDBusInterfaceInfo *hostnamed_hostname1_interface_info (void);
guint hostnamed_hostname1_override_properties (GObjectClass *klass, guint property_id_begin);


/* D-Bus method call completion functions: */
void hostnamed_hostname1_complete_set_hostname (
    hostnamedHostname1 *object,
    GDBusMethodInvocation *invocation);

void hostnamed_hostname1_complete_set_static_hostname (
    hostnamedHostname1 *object,
    GDBusMethodInvocation *invocation);

void hostnamed_hostname1_complete_set_pretty_hostname (
    hostnamedHostname1 *object,
    GDBusMethodInvocation *invocation);

void hostnamed_hostname1_complete_set_icon_name (
    hostnamedHostname1 *object,
    GDBusMethodInvocation *invocation);

void hostnamed_hostname1_complete_set_chassis (
    hostnamedHostname1 *object,
    GDBusMethodInvocation *invocation);



/* D-Bus method calls: */
void hostnamed_hostname1_call_set_hostname (
    hostnamedHostname1 *proxy,
    const gchar *arg_unnamed_arg0,
    gboolean arg_unnamed_arg1,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean hostnamed_hostname1_call_set_hostname_finish (
    hostnamedHostname1 *proxy,
    GAsyncResult *res,
    GError **error);

gboolean hostnamed_hostname1_call_set_hostname_sync (
    hostnamedHostname1 *proxy,
    const gchar *arg_unnamed_arg0,
    gboolean arg_unnamed_arg1,
    GCancellable *cancellable,
    GError **error);

void hostnamed_hostname1_call_set_static_hostname (
    hostnamedHostname1 *proxy,
    const gchar *arg_unnamed_arg0,
    gboolean arg_unnamed_arg1,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean hostnamed_hostname1_call_set_static_hostname_finish (
    hostnamedHostname1 *proxy,
    GAsyncResult *res,
    GError **error);

gboolean hostnamed_hostname1_call_set_static_hostname_sync (
    hostnamedHostname1 *proxy,
    const gchar *arg_unnamed_arg0,
    gboolean arg_unnamed_arg1,
    GCancellable *cancellable,
    GError **error);

void hostnamed_hostname1_call_set_pretty_hostname (
    hostnamedHostname1 *proxy,
    const gchar *arg_unnamed_arg0,
    gboolean arg_unnamed_arg1,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean hostnamed_hostname1_call_set_pretty_hostname_finish (
    hostnamedHostname1 *proxy,
    GAsyncResult *res,
    GError **error);

gboolean hostnamed_hostname1_call_set_pretty_hostname_sync (
    hostnamedHostname1 *proxy,
    const gchar *arg_unnamed_arg0,
    gboolean arg_unnamed_arg1,
    GCancellable *cancellable,
    GError **error);

void hostnamed_hostname1_call_set_icon_name (
    hostnamedHostname1 *proxy,
    const gchar *arg_unnamed_arg0,
    gboolean arg_unnamed_arg1,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean hostnamed_hostname1_call_set_icon_name_finish (
    hostnamedHostname1 *proxy,
    GAsyncResult *res,
    GError **error);

gboolean hostnamed_hostname1_call_set_icon_name_sync (
    hostnamedHostname1 *proxy,
    const gchar *arg_unnamed_arg0,
    gboolean arg_unnamed_arg1,
    GCancellable *cancellable,
    GError **error);

void hostnamed_hostname1_call_set_chassis (
    hostnamedHostname1 *proxy,
    const gchar *arg_unnamed_arg0,
    gboolean arg_unnamed_arg1,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean hostnamed_hostname1_call_set_chassis_finish (
    hostnamedHostname1 *proxy,
    GAsyncResult *res,
    GError **error);

gboolean hostnamed_hostname1_call_set_chassis_sync (
    hostnamedHostname1 *proxy,
    const gchar *arg_unnamed_arg0,
    gboolean arg_unnamed_arg1,
    GCancellable *cancellable,
    GError **error);



/* D-Bus property accessors: */
const gchar *hostnamed_hostname1_get_hostname (hostnamedHostname1 *object);
gchar *hostnamed_hostname1_dup_hostname (hostnamedHostname1 *object);
void hostnamed_hostname1_set_hostname (hostnamedHostname1 *object, const gchar *value);

const gchar *hostnamed_hostname1_get_static_hostname (hostnamedHostname1 *object);
gchar *hostnamed_hostname1_dup_static_hostname (hostnamedHostname1 *object);
void hostnamed_hostname1_set_static_hostname (hostnamedHostname1 *object, const gchar *value);

const gchar *hostnamed_hostname1_get_pretty_hostname (hostnamedHostname1 *object);
gchar *hostnamed_hostname1_dup_pretty_hostname (hostnamedHostname1 *object);
void hostnamed_hostname1_set_pretty_hostname (hostnamedHostname1 *object, const gchar *value);

const gchar *hostnamed_hostname1_get_icon_name (hostnamedHostname1 *object);
gchar *hostnamed_hostname1_dup_icon_name (hostnamedHostname1 *object);
void hostnamed_hostname1_set_icon_name (hostnamedHostname1 *object, const gchar *value);

const gchar *hostnamed_hostname1_get_chassis (hostnamedHostname1 *object);
gchar *hostnamed_hostname1_dup_chassis (hostnamedHostname1 *object);
void hostnamed_hostname1_set_chassis (hostnamedHostname1 *object, const gchar *value);

const gchar *hostnamed_hostname1_get_kernel_name (hostnamedHostname1 *object);
gchar *hostnamed_hostname1_dup_kernel_name (hostnamedHostname1 *object);
void hostnamed_hostname1_set_kernel_name (hostnamedHostname1 *object, const gchar *value);

const gchar *hostnamed_hostname1_get_kernel_release (hostnamedHostname1 *object);
gchar *hostnamed_hostname1_dup_kernel_release (hostnamedHostname1 *object);
void hostnamed_hostname1_set_kernel_release (hostnamedHostname1 *object, const gchar *value);

const gchar *hostnamed_hostname1_get_kernel_version (hostnamedHostname1 *object);
gchar *hostnamed_hostname1_dup_kernel_version (hostnamedHostname1 *object);
void hostnamed_hostname1_set_kernel_version (hostnamedHostname1 *object, const gchar *value);

const gchar *hostnamed_hostname1_get_operating_system_pretty_name (hostnamedHostname1 *object);
gchar *hostnamed_hostname1_dup_operating_system_pretty_name (hostnamedHostname1 *object);
void hostnamed_hostname1_set_operating_system_pretty_name (hostnamedHostname1 *object, const gchar *value);

const gchar *hostnamed_hostname1_get_operating_system_cpename (hostnamedHostname1 *object);
gchar *hostnamed_hostname1_dup_operating_system_cpename (hostnamedHostname1 *object);
void hostnamed_hostname1_set_operating_system_cpename (hostnamedHostname1 *object, const gchar *value);


/* ---- */

#define HOSTNAMED_TYPE_HOSTNAME1_PROXY (hostnamed_hostname1_proxy_get_type ())
#define HOSTNAMED_HOSTNAME1_PROXY(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), HOSTNAMED_TYPE_HOSTNAME1_PROXY, hostnamedHostname1Proxy))
#define HOSTNAMED_HOSTNAME1_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), HOSTNAMED_TYPE_HOSTNAME1_PROXY, hostnamedHostname1ProxyClass))
#define HOSTNAMED_HOSTNAME1_PROXY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), HOSTNAMED_TYPE_HOSTNAME1_PROXY, hostnamedHostname1ProxyClass))
#define HOSTNAMED_IS_HOSTNAME1_PROXY(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), HOSTNAMED_TYPE_HOSTNAME1_PROXY))
#define HOSTNAMED_IS_HOSTNAME1_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), HOSTNAMED_TYPE_HOSTNAME1_PROXY))

typedef struct _hostnamedHostname1Proxy hostnamedHostname1Proxy;
typedef struct _hostnamedHostname1ProxyClass hostnamedHostname1ProxyClass;
typedef struct _hostnamedHostname1ProxyPrivate hostnamedHostname1ProxyPrivate;

struct _hostnamedHostname1Proxy
{
  /*< private >*/
  GDBusProxy parent_instance;
  hostnamedHostname1ProxyPrivate *priv;
};

struct _hostnamedHostname1ProxyClass
{
  GDBusProxyClass parent_class;
};

GType hostnamed_hostname1_proxy_get_type (void) G_GNUC_CONST;

void hostnamed_hostname1_proxy_new (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
hostnamedHostname1 *hostnamed_hostname1_proxy_new_finish (
    GAsyncResult        *res,
    GError             **error);
hostnamedHostname1 *hostnamed_hostname1_proxy_new_sync (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);

void hostnamed_hostname1_proxy_new_for_bus (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
hostnamedHostname1 *hostnamed_hostname1_proxy_new_for_bus_finish (
    GAsyncResult        *res,
    GError             **error);
hostnamedHostname1 *hostnamed_hostname1_proxy_new_for_bus_sync (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);


/* ---- */

#define HOSTNAMED_TYPE_HOSTNAME1_SKELETON (hostnamed_hostname1_skeleton_get_type ())
#define HOSTNAMED_HOSTNAME1_SKELETON(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), HOSTNAMED_TYPE_HOSTNAME1_SKELETON, hostnamedHostname1Skeleton))
#define HOSTNAMED_HOSTNAME1_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), HOSTNAMED_TYPE_HOSTNAME1_SKELETON, hostnamedHostname1SkeletonClass))
#define HOSTNAMED_HOSTNAME1_SKELETON_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), HOSTNAMED_TYPE_HOSTNAME1_SKELETON, hostnamedHostname1SkeletonClass))
#define HOSTNAMED_IS_HOSTNAME1_SKELETON(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), HOSTNAMED_TYPE_HOSTNAME1_SKELETON))
#define HOSTNAMED_IS_HOSTNAME1_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), HOSTNAMED_TYPE_HOSTNAME1_SKELETON))

typedef struct _hostnamedHostname1Skeleton hostnamedHostname1Skeleton;
typedef struct _hostnamedHostname1SkeletonClass hostnamedHostname1SkeletonClass;
typedef struct _hostnamedHostname1SkeletonPrivate hostnamedHostname1SkeletonPrivate;

struct _hostnamedHostname1Skeleton
{
  /*< private >*/
  GDBusInterfaceSkeleton parent_instance;
  hostnamedHostname1SkeletonPrivate *priv;
};

struct _hostnamedHostname1SkeletonClass
{
  GDBusInterfaceSkeletonClass parent_class;
};

GType hostnamed_hostname1_skeleton_get_type (void) G_GNUC_CONST;

hostnamedHostname1 *hostnamed_hostname1_skeleton_new (void);


G_END_DECLS

#endif /* __SRC_INTERFACES_HOSTNAMED_HOSTNAMED_GEN_H__ */
