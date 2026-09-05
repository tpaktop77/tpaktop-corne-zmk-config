/*
 * Copyright (c) 2026 tpak
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT tpak_behavior_os_set

#include <zephyr/device.h>
#include <zephyr/sys/util.h>

#include <drivers/behavior.h>
#include <zmk/behavior.h>

#include <tpak/os_profile.h>

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

static int on_os_set_pressed(struct zmk_behavior_binding *binding,
                             struct zmk_behavior_binding_event event) {
        (void)event;
        return tpak_os_profile_set(binding->param1);
}

static int on_os_set_released(struct zmk_behavior_binding *binding,
                              struct zmk_behavior_binding_event event) {
        (void)binding;
        (void)event;
        return ZMK_BEHAVIOR_OPAQUE;
}

#if IS_ENABLED(CONFIG_ZMK_BEHAVIOR_METADATA)

static const struct behavior_parameter_value_metadata os_set_param1_values[] = {
        {.display_name = "Windows", .type = BEHAVIOR_PARAMETER_VALUE_TYPE_VALUE,
         .value = OS_WINDOWS},
        {.display_name = "macOS", .type = BEHAVIOR_PARAMETER_VALUE_TYPE_VALUE,
         .value = OS_MACOS},
        {.display_name = "Linux", .type = BEHAVIOR_PARAMETER_VALUE_TYPE_VALUE,
         .value = OS_LINUX},
};

static const struct behavior_parameter_metadata_set os_set_param_metadata_sets[] = {{
        .param1_values = os_set_param1_values,
        .param1_values_len = ARRAY_SIZE(os_set_param1_values),
}};

static const struct behavior_parameter_metadata os_set_param_metadata = {
        .sets_len = ARRAY_SIZE(os_set_param_metadata_sets),
        .sets = os_set_param_metadata_sets,
};

#endif /* CONFIG_ZMK_BEHAVIOR_METADATA */

static const struct behavior_driver_api behavior_os_set_driver_api = {
        .binding_pressed = on_os_set_pressed,
        .binding_released = on_os_set_released,
        .locality = BEHAVIOR_LOCALITY_CENTRAL,
#if IS_ENABLED(CONFIG_ZMK_BEHAVIOR_METADATA)
        .parameter_metadata = &os_set_param_metadata,
#endif /* CONFIG_ZMK_BEHAVIOR_METADATA */
};

#define OS_SET_INST(n)                                                                             \
        BEHAVIOR_DT_INST_DEFINE(n, NULL, NULL, NULL, NULL, POST_KERNEL,                            \
                                CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,                               \
                                &behavior_os_set_driver_api);

DT_INST_FOREACH_STATUS_OKAY(OS_SET_INST)

#endif /* DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT) */
