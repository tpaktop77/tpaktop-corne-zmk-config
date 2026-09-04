/*
 * Copyright (c) 2026 tpak
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT tpak_behavior_os_action

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>

#include <zephyr/device.h>

#include <drivers/behavior.h>
#include <dt-bindings/zmk/keys.h>
#include <zmk/behavior.h>
#include <zmk/keymap.h>

#include <dt-bindings/tpak/os_profile.h>
#include <tpak/os_profile.h>

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

// The complete OS-specific mapping is intentionally centralized here.
static const uint32_t action_keycodes[OS_PROFILE_COUNT][OS_ACTION_COUNT] = {
        [OS_WINDOWS] = {
                [OS_ACTION_COPY] = LC(C),
                [OS_ACTION_PASTE] = LC(V),
                [OS_ACTION_CUT] = LC(X),
                [OS_ACTION_UNDO] = LC(Z),
                [OS_ACTION_REDO] = LC(LS(Z)),
                [OS_ACTION_SELECT_ALL] = LC(A),
                [OS_ACTION_WORD_PREVIOUS] = LC(LEFT),
                [OS_ACTION_WORD_NEXT] = LC(RIGHT),
                [OS_ACTION_WORD_BACKSPACE] = LC(BSPC),
                [OS_ACTION_WORD_DELETE] = LC(DEL),
                [OS_ACTION_APP_SWITCH] = LA(TAB),
                [OS_ACTION_TASK_VIEW] = LG(TAB),
                [OS_ACTION_VOICE] = LG(H),
        },
        [OS_MACOS] = {
                [OS_ACTION_COPY] = LG(C),
                [OS_ACTION_PASTE] = LG(V),
                [OS_ACTION_CUT] = LG(X),
                [OS_ACTION_UNDO] = LG(Z),
                [OS_ACTION_REDO] = LG(LS(Z)),
                [OS_ACTION_SELECT_ALL] = LG(A),
                [OS_ACTION_WORD_PREVIOUS] = LA(LEFT),
                [OS_ACTION_WORD_NEXT] = LA(RIGHT),
                [OS_ACTION_WORD_BACKSPACE] = LA(BSPC),
                [OS_ACTION_WORD_DELETE] = LA(DEL),
                [OS_ACTION_APP_SWITCH] = LG(TAB),
                [OS_ACTION_TASK_VIEW] = LC(UP),
                [OS_ACTION_VOICE] = C_VOICE_COMMAND,
        },
        [OS_LINUX] = {
                [OS_ACTION_COPY] = LC(INS),
                [OS_ACTION_PASTE] = LS(INS),
                [OS_ACTION_CUT] = LS(DEL),
                [OS_ACTION_UNDO] = LC(Z),
                [OS_ACTION_REDO] = LC(LS(Z)),
                [OS_ACTION_SELECT_ALL] = LC(A),
                [OS_ACTION_WORD_PREVIOUS] = LC(LEFT),
                [OS_ACTION_WORD_NEXT] = LC(RIGHT),
                [OS_ACTION_WORD_BACKSPACE] = LC(BSPC),
                [OS_ACTION_WORD_DELETE] = LC(DEL),
                [OS_ACTION_APP_SWITCH] = LA(TAB),
                [OS_ACTION_TASK_VIEW] = LG(TAB),
                [OS_ACTION_VOICE] = LG(H),
        },
};

struct behavior_os_action_config {
        struct zmk_behavior_binding key_press;
};

struct behavior_os_action_data {
        uint32_t active_keycodes[OS_ACTION_COUNT];
        bool active[OS_ACTION_COUNT];
};

static int invoke_key_press(const struct behavior_os_action_config *config, uint32_t keycode,
                            struct zmk_behavior_binding_event event, bool pressed) {
        struct zmk_behavior_binding key_press = config->key_press;
        key_press.param1 = keycode;
        return zmk_behavior_invoke_binding(&key_press, event, pressed);
}

static int on_os_action_pressed(struct zmk_behavior_binding *binding,
                                struct zmk_behavior_binding_event event) {
        if (binding->param1 >= OS_ACTION_COUNT) {
                return -EINVAL;
        }

        const struct device *dev = zmk_behavior_get_binding(binding->behavior_dev);
        if (dev == NULL) {
                return -ENODEV;
        }

        struct behavior_os_action_data *data = dev->data;
        const struct behavior_os_action_config *config = dev->config;
        const uint32_t action = binding->param1;

        if (data->active[action]) {
                return -EBUSY;
        }

        const uint32_t keycode = action_keycodes[tpak_os_profile_get()][action];
        data->active_keycodes[action] = keycode;
        data->active[action] = true;

        const int result = invoke_key_press(config, keycode, event, true);
        if (result < 0) {
                data->active[action] = false;
        }

        return result;
}

static int on_os_action_released(struct zmk_behavior_binding *binding,
                                 struct zmk_behavior_binding_event event) {
        if (binding->param1 >= OS_ACTION_COUNT) {
                return -EINVAL;
        }

        const struct device *dev = zmk_behavior_get_binding(binding->behavior_dev);
        if (dev == NULL) {
                return -ENODEV;
        }

        struct behavior_os_action_data *data = dev->data;
        const struct behavior_os_action_config *config = dev->config;
        const uint32_t action = binding->param1;

        if (!data->active[action]) {
                return ZMK_BEHAVIOR_OPAQUE;
        }

        const uint32_t keycode = data->active_keycodes[action];
        data->active[action] = false;
        return invoke_key_press(config, keycode, event, false);
}

static const struct behavior_driver_api behavior_os_action_driver_api = {
        .binding_pressed = on_os_action_pressed,
        .binding_released = on_os_action_released,
        .locality = BEHAVIOR_LOCALITY_CENTRAL,
};

#define OS_ACTION_INST(n)                                                                          \
        static struct behavior_os_action_data behavior_os_action_data_##n;                        \
        static const struct behavior_os_action_config behavior_os_action_config_##n = {           \
                .key_press = ZMK_KEYMAP_EXTRACT_BINDING(0, DT_DRV_INST(n)),                        \
        };                                                                                         \
        BEHAVIOR_DT_INST_DEFINE(n, NULL, NULL, &behavior_os_action_data_##n,                        \
                                &behavior_os_action_config_##n, POST_KERNEL,                        \
                                CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,                               \
                                &behavior_os_action_driver_api);

DT_INST_FOREACH_STATUS_OKAY(OS_ACTION_INST)

#endif /* DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT) */
