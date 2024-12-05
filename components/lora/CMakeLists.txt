idf_component_register(SRCS "lora.c"
			REQUIRES "driver"
                    INCLUDE_DIRS "include"
)

#target_compile_options(${COMPONENT_LIB} PUBLIC -fpermissive -std=gnu++23)
