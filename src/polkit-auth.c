/*
 * Copyright (c) 2014 Ian Sutton <ian@kremlin.cc>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <unistd.h>
#include <limits.h>
#include <string.h>

#include <glib/gprintf.h>
#include <glib-unix.h>
#include <polkit/polkit.h>

#include "polkit-auth.h"

static gboolean is_valid_action(GList *action_list, const gchar *action) {

    PolkitActionDescription *action_descr;
    action_descr = (PolkitActionDescription *)g_list_first(action_list);

    while((action_descr = (PolkitActionDescription *)g_list_next(action_list)))
        if(!g_strcmp0(action, polkit_action_description_get_action_id(action_descr)))
            return TRUE;

    return FALSE;
}

check_auth_result polkit_try_auth(const gchar *bus, const gchar *action) {

    GList           *valid_actions;
    PolkitAuthority *auth;
    PolkitSubject   *subj;
    PolkitAuthorizationResult *result;
    gboolean authorized, challenge;

    auth  = NULL;
    subj  = NULL;
    result = NULL;
    valid_actions = NULL;
    authorized = challenge = FALSE;

    auth = polkit_authority_get_sync(NULL, NULL); /* TODO timeout for this */
    subj = polkit_system_bus_name_new(bus);
    valid_actions = polkit_authority_enumerate_actions_sync(auth, NULL, NULL);

   if(!auth || !valid_actions)
        return ERROR_GENERIC; /* extremely unlikely */
    else if(!subj)
        return ERROR_BADBUS;
    else if(!is_valid_action(valid_actions, action))
        return ERROR_BADACTION;

   if(!(result = polkit_authority_check_authorization_sync(auth, subj, action, NULL, POLKIT_CHECK_AUTHORIZATION_FLAGS_ALLOW_USER_INTERACTION, NULL, NULL)))
        return ERROR_GENERIC; /* TODO pass, check gerror and return more relevant error */

    authorized = polkit_authorization_result_get_is_authorized(result);
    challenge = polkit_authorization_result_get_is_challenge(result);

    /* free()'s before return */
    if(valid_actions)
        g_object_unref(valid_actions);
    if(auth)
        g_object_unref(auth);
    if(subj)
        g_object_unref(subj);
    if(result)
        g_object_unref(result);

    if(authorized) {

        if(challenge)
            return AUTHORIZED_BY_PROMPT;
        
        return AUTHORIZED_NATIVELY;

    } else if(challenge)
        return UNAUTHORIZED_FAILED_PROMPT;

    return UNAUTHORIZED_NATIVELY;
}
