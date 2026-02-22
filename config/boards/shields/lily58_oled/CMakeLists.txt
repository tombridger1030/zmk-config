if(CONFIG_SHIELD_LILY58_OLED)
    target_sources(app PRIVATE
        custom_status_screen.c
        widgets/owl.c
        widgets/moon.c
    )
endif()
