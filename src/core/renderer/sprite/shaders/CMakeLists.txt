set(DEFAULT_SHADERS_OUTPUT_DIR ${CMAKE_BINARY_DIR}/resources/shaders)
file(MAKE_DIRECTORY ${DEFAULT_SHADERS_OUTPUT_DIR})

set(DEFAULT_SHADER_FILES
        sprite_fragment.glsl
        sprite_vertex.glsl
)
set(GENERATED_SHADERS_CPP "")

foreach(SHADER_FILE ${DEFAULT_SHADER_FILES})
    get_filename_component(SHADER_NAME ${SHADER_FILE} NAME_WE)
    set(OUTPUT_CPP ${DEFAULT_SHADERS_OUTPUT_DIR}/${SHADER_NAME}.cpp)
    list(APPEND GENERATED_SHADERS_CPP ${OUTPUT_CPP})

    add_custom_command(
            OUTPUT ${OUTPUT_CPP}
            COMMAND ${CMAKE_COMMAND}
            -DINPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/${SHADER_FILE}
            -DOUTPUT_FILE=${OUTPUT_CPP}
            -DSHADER_NAME=${SHADER_NAME}
            -P "${CMAKE_CURRENT_SOURCE_DIR}/embed_shader.cmake"
            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${SHADER_FILE}
            COMMENT "Embedding shader ${SHADER_FILE} → ${OUTPUT_CPP}"
            VERBATIM
    )
endforeach()

add_custom_target(GenerateShaders ALL DEPENDS ${GENERATED_SHADERS_CPP})

set(GENERATED_DEFAULT_SHADERS_CPP ${GENERATED_SHADERS_CPP} PARENT_SCOPE)
