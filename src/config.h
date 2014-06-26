/*our buffers for xml config file contents */
static gchar **hostnamed_ispect_xml, **hostnamed_dbus_xml,
             **localed_ispect_xml,   **localed_dbus_xml,
             **timedated_ispect_xml, **timedated_dbus_xml,
             **logind_ispect_xml,    **logind_dbus_xml;

/* manually increment this if adding new functionality/config files */
static const guint XML_FILE_COUNT = 8;

static gchar **xml_contents[] = {
        hostnamed_ispect_xml, hostnamed_dbus_xml,
        localed_ispect_xml,   localed_dbus_xml,
        timedated_ispect_xml, timedated_dbus_xml,
        logind_ispect_xml,    logind_dbus_xml
};

/* TODO ifdef allowed editable xml only take files that meet exact sizes
 * of ones hashed below */

#ifndef ALLOW_EDITED_XML

static const gchar *hostnamed_dbus_sum   = "ad7536541463e426388c7562b0e7a693c3b646539b3ae163a7caf6ad95f10e08";
static const gchar *hostnamed_ispect_sum = "4a41b3c3b0169fb7859ed5a2bde9c8c92f2b67e5e22b6e240cb6f41f6d2e69db";
static const gchar *localed_dbus_sum     = "fd3a5e13f660ca393d66e518eb5ba1b94e26ad055f7485955ba0070eec4e217c";
static const gchar *localed_ispect_sum   = "3ef138659ebfd3a8b7bb11d658ed80867493e774d69ff5c70e26b39b6fef6378";
static const gchar *logind_dbus_sum      = "f698082a6b6c42aa0d9dbd8726adfe84ef08bb84779128fefc6bb40c9476b70b";
static const gchar *logind_ispect_sum    = "557f98d71d1b4e62ecc5c7558db72f2293e42ee8ee9722ec3ffcffd9681a6bf3";
static const gchar *timedated_dbus_sum   = "d7d67482a821cbc7a6ab3a68f1c00e0dc61a98c3c317461abe8b7aba7ac7b864";
static const gchar *timedated_ispect_sum = "f576cb908636a285c9cd2e42a71ad243a0d5eb0ff12398f0627cce56c15a8268";

#endif

static gboolean populate_xml_data_dir() {

}

static gboolean read_xml_from_installconf() {

}
