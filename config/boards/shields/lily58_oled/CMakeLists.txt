if(CONFIG_SHIELD_LILY58_OLED AND CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM)
    target_sources(app PRIVATE
        custom_status_screen.c
        widgets/owl.c
        widgets/moon.c
    )
endif()
