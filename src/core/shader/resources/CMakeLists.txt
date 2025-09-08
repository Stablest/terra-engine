#set(DEFAULT_SHADERS_OUTPUT_DIR ${CMAKE_BINARY_DIR}/resources/shaders)
#
#set(DEFAULT_SHADER_FILES
#        default_frag.glsl
#        default_vertex.glsl)
#
#set(GENERATED_SHADERS_CPP "")
#
#function(embed_shader INPUT_FILE OUTPUT_FILE VAR_NAME)
#    get_filename_component(OUTPUT_DIR "${OUTPUT_FILE}" DIRECTORY)
#    file(MAKE_DIRECTORY "${OUTPUT_DIR}")
#    file(READ "${INPUT_FILE}" GLSL_CONTENTS)
#    string(REPLACE "\\" "\\\\" GLSL_CONTENTS "${GLSL_CONTENTS}")
#    string(REPLACE "\"" "\\\"" GLSL_CONTENTS "${GLSL_CONTENTS}")
#    file(WRITE "${OUTPUT_FILE}" "const char* ${VAR_NAME} = R\"SHADER(\n${GLSL_CONTENTS}\n)SHADER\";\n")
#endfunction()
#
#foreach(SHADER_FILE ${DEFAULT_SHADER_FILES})
#    get_filename_component(SHADER_NAME ${SHADER_FILE} NAME_WE)
#    set(OUTPUT_CPP ${DEFAULT_SHADERS_OUTPUT_DIR}/${SHADER_NAME}.cpp)
#    # Embed shader
#    embed_shader(${CMAKE_CURRENT_SOURCE_DIR}/${SHADER_FILE} ${OUTPUT_CPP} ${SHADER_NAME}_shader)
#    list(APPEND GENERATED_SHADERS_CPP ${OUTPUT_CPP})
#endforeach()
#
#set(GENERATED_DEFAULT_SHADERS_CPP ${GENERATED_SHADERS_CPP} PARENT_SCOPE)

set(DEFAULT_SHADERS_OUTPUT_DIR ${CMAKE_BINARY_DIR}/resources/shaders)
file(MAKE_DIRECTORY ${DEFAULT_SHADERS_OUTPUT_DIR})

set(DEFAULT_SHADER_FILES
        default_frag.glsl
        default_vertex.glsl
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
            -P ${CMAKE_CURRENT_SOURCE_DIR}/embed_shader.cmake
            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${SHADER_FILE}
            COMMENT "Embedding shader ${SHADER_FILE} → ${OUTPUT_CPP}"
            VERBATIM
    )
endforeach()

# Custom target to group all shader generation commands
add_custom_target(GenerateShaders ALL DEPENDS ${GENERATED_SHADERS_CPP})

set(GENERATED_DEFAULT_SHADERS_CPP ${GENERATED_SHADERS_CPP} PARENT_SCOPE)
