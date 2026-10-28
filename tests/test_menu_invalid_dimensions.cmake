execute_process(
    COMMAND "${APP}"
    INPUT_FILE "${INPUT}"
    OUTPUT_VARIABLE output
    RESULT_VARIABLE result
    ENCODING UTF-8
)

if(NOT result EQUAL 0)
    message(FATAL_ERROR "Program exited with ${result}")
endif()

string(FIND "${output}" "Некорректные размеры" position)
if(position EQUAL -1)
    message(FATAL_ERROR "Expected invalid-dimensions warning; got: ${output}")
endif()
