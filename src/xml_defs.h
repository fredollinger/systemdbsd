const GString hostnamed_config_xml_def[] = {
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>",
"<!DOCTYPE busconfig PUBLIC",
"        \"-//freedesktop//DTD D-BUS Bus Configuration 1.0//EN\"",
"        \"http://www.freedesktop.org/standards/dbus/1.0/busconfig.dtd\">",
"<busconfig>",
"    <!-- Only members of 'wheel' and user 'daemon' may set hostnames -->",
"    <policy group=\"wheel\">",
"        <allow own=\"org.freedesktop.hostname1\"/>",
"        <allow send_destination=\"org.freedesktop.hostname1\"/>",
"        <allow receive_sender=\"org.freedesktop.hostname1\"/>",
"    </policy>",
"    <policy user=\"daemon\">",
"        <allow own=\"org.freedesktop.hostname1\"/>",
"        <allow send_destination=\"org.freedesktop.hostname1\"/>",
"        <allow receive_sender=\"org.freedesktop.hostname1\"/>",
"    </policy>",
"</busconfig>"};

const GString hostnamed_ispect_xml_def[] = {
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>",
"<!DOCTYPE node PUBLIC",
"        \"-//freedesktop//DTD D-BUS Object Introspection 1.0//EN\"",
"        \"http://www.freedesktop.org/standards/dbus/1.0/introspect.dtd\">",
"<!-- Taken from Gentoo Linux's OpenRC settingsd -->",
"<node name=\"/org/freedesktop/hostname1\">",
"    <interface name=\"org.freedesktop.hostname1\">",
"        <method name=\"SetHostname\">",
"            <arg direction=\"in\" type=\"s\" name=\"name\"/>",
"            <arg direction=\"in\" type=\"b\" name=\"user_interaction\"/>",
"        </method>",
"        <method name=\"SetStaticHostname\">",
"            <arg direction=\"in\" type=\"s\" name=\"name\"/>",
"            <arg direction=\"in\" type=\"b\" name=\"user_interaction\"/>",
"        </method>",
"        <method name=\"SetPrettyHostname\">",
"            <arg direction=\"in\" type=\"s\" name=\"name\"/>",
"            <arg direction=\"in\" type=\"b\" name=\"user_interaction\"/>",
"        </method>",
"        <method name=\"SetIconName\">",
"            <arg direction=\"in\" type=\"s\" name=\"name\"/>",
"            <arg direction=\"in\" type=\"b\" name=\"user_interaction\"/>",
"        </method>",
"        <property name=\"Hostname\" type=\"s\" access=\"read\"/>",
"        <property name=\"StaticHostname\" type=\"s\" access=\"read\"/>",
"        <property name=\"PrettyHostname\" type=\"s\" access=\"read\"/>",
"        <property name=\"IconName\" type=\"s\" access=\"read\"/>",
"    </interface>",
"</node>"};

const GString timedated_config_xml_def[] = {
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>",
"<!DOCTYPE busconfig PUBLIC",
"        \"-//freedesktop//DTD D-BUS Bus Configuration 1.0//EN\"",
"        \"http://www.freedesktop.org/standards/dbus/1.0/busconfig.dtd\">",
"<busconfig>",
"    <!-- Only members of 'wheel' and user 'daemon' may change time settings -->",
"    <policy group=\"wheel\">",
"        <allow own=\"org.freedesktop.timedate1\"/>",
"        <allow send_destination=\"org.freedesktop.timedate1\"/>",
"        <allow receive_sender=\"org.freedesktop.timedate1\"/>",
"    </policy>",
"    <policy user=\"daemon\">",
"       <allow own=\"org.freedesktop.timedate1\"/>",
"       <allow send_destination=\"org.freedesktop.timedate1\"/>",
"       <allow receive_sender=\"org.freedesktop.timedate1\"/>",
"    </policy>",
"</busconfig>"};

const GString timedated_ispect_xml_def[] = {
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>",
"<!DOCTYPE node PUBLIC",
"        \"-//freedesktop//DTD D-BUS Object Introspection 1.0//EN\"",
"        \"http://www.freedesktop.org/standards/dbus/1.0/introspect.dtd\">",
"<!-- Taken from Gentoo Linux's OpenRC settingsd -->",
"<node name=\"/org/freedesktop/timedate1\">",
"    <interface name=\"org.freedesktop.timedate1\">",
"        <method name=\"SetTime\">",
"            <arg direction=\"in\" type=\"x\" name=\"usec_utc\"/>",
"            <arg direction=\"in\" type=\"b\" name=\"relative\"/>",
"            <arg direction=\"in\" type=\"b\" name=\"user_interaction\"/>",
"        </method>",
"        <method name=\"SetTimezone\">",
"            <arg direction=\"in\" type=\"s\" name=\"timezone\"/>",
"            <arg direction=\"in\" type=\"b\" name=\"user_interaction\"/>",
"        </method>",
"        <method name=\"SetLocalRTC\">",
"            <arg direction=\"in\" type=\"b\" name=\"local_rtc\"/>",
"            <arg direction=\"in\" type=\"b\" name=\"fix_system\"/>",
"            <arg direction=\"in\" type=\"b\" name=\"user_interaction\"/>",
"        </method>",
"        <method name=\"SetNTP\">",
"            <arg direction=\"in\" type=\"b\" name=\"use_ntp\"/>",
"            <arg direction=\"in\" type=\"b\" name=\"user_interaction\"/>",
"        </method>",
"        <property name=\"Timezone\" type=\"s\" access=\"read\"/>",
"        <property name=\"LocalRTC\" type=\"b\" access=\"read\"/>",
"        <property name=\"NTP\" type=\"b\" access=\"read\"/>",
"    </interface>",
"</node>"};

const GString localed_config_xml_def[] = {
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>",
"<!DOCTYPE busconfig PUBLIC",
"        \"-//freedesktop//DTD D-BUS Bus Configuration 1.0//EN\"",
"        \"http://www.freedesktop.org/standards/dbus/1.0/busconfig.dtd\">",
"<busconfig>",
"    <!-- Only members of 'wheel' and user 'daemon' may change system-wide locales -->",
"    <policy group=\"wheel\">",
"        <allow own=\"org.freedesktop.locale1\"/>",
"        <allow send_destination=\"org.freedesktop.locale1\"/>",
"        <allow receive_sender=\"org.freedesktop.locale1\"/>",
"    </policy>",
"    <policy user=\"daemon\">",
"       <allow own=\"org.freedesktop.locale1\"/>",
"       <allow send_destination=\"org.freedesktop.locale1\"/>",
"       <allow receive_sender=\"org.freedesktop.locale1\"/>",
"    </policy>",
"</busconfig>"};

const GString localed_ispect_xml_def[] = {
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>",
"<!DOCTYPE node PUBLIC",
"        \"-//freedesktop//DTD D-BUS Object Introspection 1.0//EN\"",
"        \"http://www.freedesktop.org/standards/dbus/1.0/introspect.dtd\">",
"<!-- Taken from Gentoo Linux's OpenRC settingsd -->",
"<node name=\"/org/freedesktop/locale1\">",
"    <interface name=\"org.freedesktop.locale1\">",
"        <method name=\"SetLocale\">",
"            <arg direction=\"in\" type=\"as\" name=\"locale\" />",
"            <arg direction=\"in\" type=\"b\" name=\"user_interaction\" />",
"        </method>",
"        <method name=\"SetVConsoleKeyboard\">",
"            <arg direction=\"in\" type=\"s\" name=\"keymap\" />",
"            <arg direction=\"in\" type=\"s\" name=\"keymap_toggle\" />",
"            <arg direction=\"in\" type=\"b\" name=\"convert\" />",
"            <arg direction=\"in\" type=\"b\" name=\"user_interaction\" />",
"        </method>",
"        <method name=\"SetX11Keyboard\">",
"            <arg direction=\"in\" type=\"s\" name=\"layout\" />",
"            <arg direction=\"in\" type=\"s\" name=\"model\" />",
"            <arg direction=\"in\" type=\"s\" name=\"variant\" />",
"            <arg direction=\"in\" type=\"s\" name=\"options\" />",
"            <arg direction=\"in\" type=\"b\" name=\"convert\" />",
"            <arg direction=\"in\" type=\"b\" name=\"user_interaction\" />",
"        </method>",
"        <property name=\"Locale\" type=\"as\" access=\"read\" />",
"        <property name=\"VConsoleKeymap\" type=\"s\" access=\"read\" />",
"        <property name=\"VConsoleKeymapToggle\" type=\"s\" access=\"read\" />",
"        <property name=\"X11Layout\" type=\"s\" access=\"read\" />",
"        <property name=\"X11Model\" type=\"s\" access=\"read\" />",
"        <property name=\"X11Variant\" type=\"s\" access=\"read\" />",
"        <property name=\"X11Options\" type=\"s\" access=\"read\" />",
"    </interface>",
"</node>"};

const GString logind_config_xml_def[] = {
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>",
"<!DOCTYPE busconfig PUBLIC",
"        \"-//freedesktop//DTD D-BUS Bus Configuration 1.0//EN\"",
"        \"http://www.freedesktop.org/standards/dbus/1.0/busconfig.dtd\">",
"<busconfig>",
"    <!-- TODO: figure out nessecary logind permissions -->",
"    <policy group=\"wheel\">",
"        <allow own=\"org.freedesktop.login1\"/>",
"        <allow send_destination=\"org.freedesktop.login1\"/>",
"        <allow receive_sender=\"org.freedesktop.login1\"/>",
"    </policy>",
"    <policy user=\"daemon\">",
"       <allow own=\"org.freedesktop.login1\"/>",
"       <allow send_destination=\"org.freedesktop.login1\"/>",
"       <allow receive_sender=\"org.freedesktop.login1\"/>",
"    </policy>",
"</busconfig>"};

const GString logind_ispect_xml_def[] = {
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>",
"<!DOCTYPE node PUBLIC",
"        \"-//freedesktop//DTD D-BUS Object Introspection 1.0//EN\"",
"        \"http://www.freedesktop.org/standards/dbus/1.0/introspect.dtd\">",
"<node name=\"/org/freedesktop/login1\">",
"    <interface name=\"org.freedesktop.DBus.Peer\">",
"        <method name=\"Ping\" />",
"        <method name=\"GetMachineId\">",
"            <arg type=\"s\" name=\"machine_uuid\" direction=\"out\" />",
"        </method>",
"    </interface>",
"    <interface name=\"org.freedesktop.DBus.Introspectable\">",
"        <method name=\"Introspect\">",
"            <arg name=\"data\" type=\"s\" direction=\"out\" />",
"        </method>",
"    </interface>",
"    <interface name=\"org.freedesktop.DBus.Properties\">",
"        <method name=\"Get\">",
"            <arg name=\"interface\" direction=\"in\" type=\"s\" />",
"            <arg name=\"property\" direction=\"in\" type=\"s\" />",
"            <arg name=\"value\" direction=\"out\" type=\"v\" />",
"        </method>",
"        <method name=\"GetAll\">",
"            <arg name=\"interface\" direction=\"in\" type=\"s\" />",
"            <arg name=\"properties\" direction=\"out\" type=\"a{sv}\" />",
"        </method>",
"        <method name=\"Set\">",
"            <arg name=\"interface\" direction=\"in\" type=\"s\" />",
"            <arg name=\"property\" direction=\"in\" type=\"s\" />",
"            <arg name=\"value\" direction=\"in\" type=\"v\" />",
"        </method>",
"        <signal name=\"PropertiesChanged\">",
"            <arg type=\"s\" name=\"interface\" direction=\"in\" />",
"            <arg type=\"a{sv}\" name=\"changed_properties\" direction=\"in\" />",
"            <arg type=\"as\" name=\"invalidated_properties\" direction=\"in\" />",
"        </signal>",
"    </interface>",
"    <interface name=\"org.freedesktop.login1.Manager\">",
"        <property name=\"NAutoVTs\" type=\"u\" access=\"read\">",
"            <annotation name=\"org.freedesktop.DBus.Property.EmitsChangedSignal\" value=\"const\" />",
"        </property>",
"        <property name=\"KillOnlyUsers\" type=\"as\" access=\"read\">",
"            <annotation name=\"org.freedesktop.DBus.Property.EmitsChangedSignal\" value=\"const\" />",
"        </property>",
"        <property name=\"KillExcludeUsers\" type=\"as\" access=\"read\">",
"            <annotation name=\"org.freedesktop.DBus.Property.EmitsChangedSignal\" value=\"const\" />",
"        </property>",
"        <property name=\"KillUserProcesses\" type=\"b\" access=\"read\">",
"            <annotation name=\"org.freedesktop.DBus.Property.EmitsChangedSignal\" value=\"const\" />",
"        </property>",
"        <property name=\"IdleHint\" type=\"b\" access=\"read\" />",
"        <property name=\"IdleSinceHint\" type=\"t\" access=\"read\" />",
"        <property name=\"IdleSinceHintMonotonic\" type=\"t\" access=\"read\" />",
"        <property name=\"BlockInhibited\" type=\"s\" access=\"read\" />",
"        <property name=\"DelayInhibited\" type=\"s\" access=\"read\" />",
"        <property name=\"InhibitDelayMaxUSec\" type=\"t\" access=\"read\">",
"            <annotation name=\"org.freedesktop.DBus.Property.EmitsChangedSignal\" value=\"const\" />",
"        </property>",
"        <property name=\"HandlePowerKey\" type=\"s\" access=\"read\">",
"            <annotation name=\"org.freedesktop.DBus.Property.EmitsChangedSignal\" value=\"const\" />",
"        </property>",
"        <property name=\"HandleSuspendKey\" type=\"s\" access=\"read\">",
"            <annotation name=\"org.freedesktop.DBus.Property.EmitsChangedSignal\" value=\"const\" />",
"        </property>",
"        <property name=\"HandleHibernateKey\" type=\"s\" access=\"read\">",
"            <annotation name=\"org.freedesktop.DBus.Property.EmitsChangedSignal\" value=\"const\" />",
"        </property>",
"        <property name=\"HandleLidSwitch\" type=\"s\" access=\"read\">",
"            <annotation name=\"org.freedesktop.DBus.Property.EmitsChangedSignal\" value=\"const\" />",
"        </property>",
"        <property name=\"IdleAction\" type=\"s\" access=\"read\">",
"            <annotation name=\"org.freedesktop.DBus.Property.EmitsChangedSignal\" value=\"const\" />",
"        </property>",
"        <property name=\"IdleActionUSec\" type=\"t\" access=\"read\">",
"            <annotation name=\"org.freedesktop.DBus.Property.EmitsChangedSignal\" value=\"const\" />",
"        </property>",
"        <property name=\"PreparingForShutdown\" type=\"b\" access=\"read\">",
"            <annotation name=\"org.freedesktop.DBus.Property.EmitsChangedSignal\" value=\"false\" />",
"        </property>",
"        <property name=\"PreparingForSleep\" type=\"b\" access=\"read\">",
"            <annotation name=\"org.freedesktop.DBus.Property.EmitsChangedSignal\" value=\"false\" />",
"        </property>",
"        <method name=\"GetSession\">",
"            <arg type=\"s\" direction=\"in\" />",
"            <arg type=\"o\" direction=\"out\" />",
"        </method>",
"        <method name=\"GetSessionByPID\">",
"            <arg type=\"u\" direction=\"in\" />",
"            <arg type=\"o\" direction=\"out\" />",
"        </method>",
"        <method name=\"GetUser\">",
"            <arg type=\"u\" direction=\"in\" />",
"            <arg type=\"o\" direction=\"out\" />",
"        </method>",
"        <method name=\"GetUserByPID\">",
"            <arg type=\"u\" direction=\"in\" />",
"            <arg type=\"o\" direction=\"out\" />",
"        </method>",
"        <method name=\"GetSeat\">",
"            <arg type=\"s\" direction=\"in\" />",
"            <arg type=\"o\" direction=\"out\" />",
"        </method>",
"        <method name=\"ListSessions\">",
"            <arg type=\"a(susso)\" direction=\"out\" />",
"        </method>",
"        <method name=\"ListUsers\">",
"            <arg type=\"a(uso)\" direction=\"out\" />",
"        </method>",
"        <method name=\"ListSeats\">",
"            <arg type=\"a(so)\" direction=\"out\" />",
"        </method>",
"        <method name=\"ListInhibitors\">",
"            <arg type=\"a(ssssuu)\" direction=\"out\" />",
"        </method>",
"        <method name=\"CreateSession\">",
"            <arg type=\"u\" direction=\"in\" />",
"            <arg type=\"u\" direction=\"in\" />",
"            <arg type=\"s\" direction=\"in\" />",
"            <arg type=\"s\" direction=\"in\" />",
"            <arg type=\"s\" direction=\"in\" />",
"            <arg type=\"s\" direction=\"in\" />",
"            <arg type=\"s\" direction=\"in\" />",
"            <arg type=\"u\" direction=\"in\" />",
"            <arg type=\"s\" direction=\"in\" />",
"            <arg type=\"s\" direction=\"in\" />",
"            <arg type=\"b\" direction=\"in\" />",
"            <arg type=\"s\" direction=\"in\" />",
"            <arg type=\"s\" direction=\"in\" />",
"            <arg type=\"a(sv)\" direction=\"in\" />",
"            <arg type=\"s\" direction=\"out\" />",
"            <arg type=\"o\" direction=\"out\" />",
"            <arg type=\"s\" direction=\"out\" />",
"            <arg type=\"h\" direction=\"out\" />",
"            <arg type=\"u\" direction=\"out\" />",
"            <arg type=\"s\" direction=\"out\" />",
"            <arg type=\"u\" direction=\"out\" />",
"            <arg type=\"b\" direction=\"out\" />",
"            <annotation name=\"org.freedesktop.systemd1.Privileged\" value=\"true\" />",
"        </method>",
"        <method name=\"ReleaseSession\">",
"            <arg type=\"s\" direction=\"in\" />",
"            <annotation name=\"org.freedesktop.systemd1.Privileged\" value=\"true\" />",
"        </method>",
"        <method name=\"ActivateSession\">",
"            <arg type=\"s\" direction=\"in\" />",
"        </method>",
"        <method name=\"ActivateSessionOnSeat\">",
"            <arg type=\"s\" direction=\"in\" />",
"            <arg type=\"s\" direction=\"in\" />",
"        </method>",
"        <method name=\"LockSession\">",
"            <arg type=\"s\" direction=\"in\" />",
"            <annotation name=\"org.freedesktop.systemd1.Privileged\" value=\"true\" />",
"        </method>",
"        <method name=\"UnlockSession\">",
"            <arg type=\"s\" direction=\"in\" />",
"            <annotation name=\"org.freedesktop.systemd1.Privileged\" value=\"true\" />",
"        </method>",
"        <method name=\"LockSessions\">",
"            <annotation name=\"org.freedesktop.systemd1.Privileged\" value=\"true\" />",
"        </method>",
"        <method name=\"UnlockSessions\">",
"            <annotation name=\"org.freedesktop.systemd1.Privileged\" value=\"true\" />",
"        </method>",
"        <method name=\"KillSession\">",
"            <arg type=\"s\" direction=\"in\" />",
"            <arg type=\"s\" direction=\"in\" />",
"            <arg type=\"i\" direction=\"in\" />",
"            <annotation name=\"org.freedesktop.systemd1.Privileged\" value=\"true\" />",
"        </method>",
"        <method name=\"KillUser\">",
"            <arg type=\"u\" direction=\"in\" />",
"            <arg type=\"i\" direction=\"in\" />",
"            <annotation name=\"org.freedesktop.systemd1.Privileged\" value=\"true\" />",
"        </method>",
"        <method name=\"TerminateSession\">",
"            <arg type=\"s\" direction=\"in\" />",
"            <annotation name=\"org.freedesktop.systemd1.Privileged\" value=\"true\" />",
"        </method>",
"        <method name=\"TerminateUser\">",
"            <arg type=\"u\" direction=\"in\" />",
"            <annotation name=\"org.freedesktop.systemd1.Privileged\" value=\"true\" />",
"        </method>",
"        <method name=\"TerminateSeat\">",
"            <arg type=\"s\" direction=\"in\" />",
"            <annotation name=\"org.freedesktop.systemd1.Privileged\" value=\"true\" />",
"        </method>",
"        <method name=\"SetUserLinger\">",
"            <arg type=\"u\" direction=\"in\" />",
"            <arg type=\"b\" direction=\"in\" />",
"            <arg type=\"b\" direction=\"in\" />",
"        </method>",
"        <method name=\"AttachDevice\">",
"            <arg type=\"s\" direction=\"in\" />",
"            <arg type=\"s\" direction=\"in\" />",
"            <arg type=\"b\" direction=\"in\" />",
"        </method>",
"        <method name=\"FlushDevices\">",
"            <arg type=\"b\" direction=\"in\" />",
"        </method>",
"        <method name=\"PowerOff\">",
"            <arg type=\"b\" direction=\"in\" />",
"        </method>",
"        <method name=\"Reboot\">",
"            <arg type=\"b\" direction=\"in\" />",
"        </method>",
"        <method name=\"Suspend\">",
"            <arg type=\"b\" direction=\"in\" />",
"        </method>",
"        <method name=\"Hibernate\">",
"            <arg type=\"b\" direction=\"in\" />",
"        </method>",
"        <method name=\"HybridSleep\">",
"            <arg type=\"b\" direction=\"in\" />",
"        </method>",
"        <method name=\"CanPowerOff\">",
"            <arg type=\"s\" direction=\"out\" />",
"        </method>",
"        <method name=\"CanReboot\">",
"            <arg type=\"s\" direction=\"out\" />",
"        </method>",
"        <method name=\"CanSuspend\">",
"            <arg type=\"s\" direction=\"out\" />",
"        </method>",
"        <method name=\"CanHibernate\">",
"            <arg type=\"s\" direction=\"out\" />",
"        </method>",
"        <method name=\"CanHybridSleep\">",
"            <arg type=\"s\" direction=\"out\" />",
"        </method>",
"        <method name=\"Inhibit\">",
"            <arg type=\"s\" direction=\"in\" />",
"            <arg type=\"s\" direction=\"in\" />",
"            <arg type=\"s\" direction=\"in\" />",
"            <arg type=\"s\" direction=\"in\" />",
"            <arg type=\"h\" direction=\"out\" />",
"        </method>",
"        <signal name=\"SessionNew\">",
"            <arg type=\"s\" direction=\"in\" />",
"            <arg type=\"o\" direction=\"in\" />",
"        </signal>",
"        <signal name=\"SessionRemoved\">",
"            <arg type=\"s\" direction=\"in\" />",
"            <arg type=\"o\" direction=\"in\" />",
"        </signal>",
"        <signal name=\"UserNew\">",
"            <arg type=\"u\" direction=\"in\" />",
"            <arg type=\"o\" direction=\"in\" />",
"        </signal>",
"        <signal name=\"UserRemoved\">",
"            <arg type=\"u\" direction=\"in\" />",
"            <arg type=\"o\" direction=\"in\" />",
"        </signal>",
"        <signal name=\"SeatNew\">",
"            <arg type=\"s\" direction=\"in\" />",
"            <arg type=\"o\" direction=\"in\" />",
"        </signal>",
"        <signal name=\"SeatRemoved\">",
"            <arg type=\"s\" direction=\"in\" />",
"            <arg type=\"o\" direction=\"in\" />",
"        </signal>",
"        <signal name=\"PrepareForShutdown\">",
"            <arg type=\"b\" direction=\"in\" />",
"        </signal>",
"        <signal name=\"PrepareForSleep\">",
"            <arg type=\"b\" direction=\"in\" />",
"        </signal>",
"    </interface>",
"</node>" };

