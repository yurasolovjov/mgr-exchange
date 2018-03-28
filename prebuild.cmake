GET_DIRECTORY_PROPERTY( HAS_PARENT PARENT_DIRECT)

MACRO( BUILD_BOOST BOOST_ROOT LIBRARIES)

    set(ExternalBoostRoot ${CMAKE_SOURCE_DIR}/external/boost-1.66.0)
    set(BOOTSTRAP_CMD ${ExternalBoostRoot}/bootstrap.bat)
    set(BOOTSTRAP_ARGS gcc)
    set(B2_CMD ${ExternalBoostRoot}/b2.exe)
    set(B2_ARGS_1 "headers")
    set(B2_ARGS_2 "--build-type=minimal --toolset=gcc --prefix=C:\\boost_1_66_0_local install")



    foreach(LIB IN LISTS ${LIBRARIES})
        string(CONCAT B2_ARGS_2 "--with-${LIB} " ${B2_ARGS_2})
    endforeach()

    set(B2_ARGS ${B2_ARGS_1} ${B2_ARGS_2})

    if(EXISTS ${BOOTSTRAP_CMD})
        message("Execute command: ${BOOTSTRAP_CMD} ${BOOTSTRAP_ARGS}")
        execute_process(COMMAND cmd /c  "${BOOTSTRAP_CMD} ${BOOTSTRAP_ARGS}"
                        WORKING_DIRECTORY ${ExternalBoostRoot}
                        RESULT_VARIABLE BS_RESULT
                        OUTPUT_VARIABLE BS_OUTPUT
                        ERROR_VARIABLE BS_ERROR)

        if(EXISTS ${B2_CMD})

            foreach(args ${B2_ARGS})
                message("Execute command: ${B2_CMD} ${args}")
                execute_process(COMMAND cmd /c "${B2_CMD} ${args}"
                                WORKING_DIRECTORY ${ExternalBoostRoot}
                                RESULT_VARIABLE BS_RESULT
                                OUTPUT_VARIABLE BS_OUTPUT
                                ERROR_VARIABLE BS_ERROR)
            endforeach()
        endif()
    endif()
ENDMACRO()
