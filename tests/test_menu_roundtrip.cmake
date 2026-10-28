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

foreach(expected IN ITEMS
    "Матрица создана"
    "7 7 7 "
    "Максимумы строк: 7 7"
    "Минимумы столбцов: 7 7 7"
)
    string(FIND "${output}" "${expected}" position)
    if(position EQUAL -1)
        message(FATAL_ERROR "Expected '${expected}'; got: ${output}")
    endif()
endforeach()
