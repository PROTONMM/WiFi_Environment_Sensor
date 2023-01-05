idf_component_register(
				SRCS main.c aht15_task.c 
				INCLUDE_DIRS ""
				EMBED_FILES ""
                )

target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")