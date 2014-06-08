#include <gio/gio.h>

#ifdef  NO BUILTIN XML
//TODO install conf
#endif

#ifndef NO_BUILTIN_XML
gchar **hostnamed_config_xml =
"<!DOCTYPE busconfig PUBLIC"
"         \"-//freedesktop//DTD D-BUS Bus Configuration 1.0//EN\""
"         \"http://www.freedesktop.org/standards/dbus/1.0/busconfig.dtd\">"
"<busconfig>"
"   <!-- Only members of 'wheel' and user 'daemon' may set hostnames -->"
"   <policy group=\"wheel\">"
"       <allow own=\"org.freedesktop.hostname1\"/>"
"       <allow send_destination=\"org.freedesktop.hostname1\"/>"
"       <allow receive_sender=\"org.freedesktop.hostname1\"/>"
"   </policy>"
"   <policy user=\"daemon\">"
"       <allow own=\"org.freedesktop.hostname1\"/>"
"       <allow send_destination=\"org.freedesktop.hostname1\"/>"
"       <allow receive_sender=\"org.freedesktop.hostname1\"/>"
"    </policy>"
"</busconfig>";

gchar **hostnamed_ispect_xml =
"<!-- Taken from Gentoo Linux's OpenRC settingsd -->"
"<node name=\"/org/freedesktop/hostname1\">"
"    <interface name=\"org.freedesktop.hostname1\">"
"        <method name=\"SetHostname\">"
"            <arg direction=\"in\" type=\"s\" name=\"name\"/>"
"            <arg direction=\"in\" type=\"b\" name=\"user_interaction\"/>"
"        </method>"
"        <method name=\"SetStaticHostname\">"
"            <arg direction=\"in\" type=\"s\" name=\"name\"/>"
"            <arg direction=\"in\" type=\"b\" name=\"user_interaction\"/>"
"        </method>"
"        <method name=\"SetPrettyHostname\">"
"            <arg direction=\"in\" type=\"s\" name=\"name\"/>"
"            <arg direction=\"in\" type=\"b\" name=\"user_interaction\"/>"
"        </method>"
"        <method name=\"SetIconName\">"
"            <arg direction=\"in\" type=\"s\" name=\"name\"/>"
"            <arg direction=\"in\" type=\"b\" name=\"user_interaction\"/>"
"        </method>"
"        <property name=\"Hostname\" type=\"s\" access=\"read\"/>"
"        <property name=\"StaticHostname\" type=\"s\" access=\"read\"/>"
"        <property name=\"PrettyHostname\" type=\"s\" access=\"read\"/>"
"        <property name=\"IconName\" type=\"s\" access=\"read\"/>"
"    </interface>"
"</node>";
