GET_DIRECTORY_PROPERTY( HAS_PARENT PARENT_DIRECT)

#MACRO( BUILD_BOOST BOOST_ROOT LIBRARIES)
#ENDMACRO()

set(ExternalBoostRoot ${CMAKE_SOURCE_DIR}/external/boost-1.66.0)
set(BOOTSTRAP_CMD ${ExternalBoostRoot}/bootstrap.bat)
set(BOOTSTRAP_ARGS gcc)
set(B2_CMD ${ExternalBoostRoot}/b2.exe)
set(B2_ARGS_1 "headers")
set(B2_ARGS_2 "--build-type=minimal --with-program_options --toolset=gcc --prefix=C:\\boost_1_66_0_local install")

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

#
# run bootstrap
#
#if(WIN32)
#  if(MSVC10)
#    set(VCVARS_CMD "C:\\Program^ Files^ ^(x86^)\\Microsoft^ Visual^ Studio^ 10.0\\VC\\vcvarsall.bat")
#  elseif(MSVC11)
#    set(VCVARS_CMD "C:\\Program^ Files^ ^(x86^)\\Microsoft^ Visual^ Studio^ 11.0\\VC\\vcvarsall.bat")
#  elseif(MSVC12)
#    set(VCVARS_CMD "C:\\Program^ Files^ ^(x86^)\\Microsoft^ Visual^ Studio^ 12.0\\VC\\vcvarsall.bat")
#  # elseif(...)
#   # add more options here
#  endif(MSVC10)
#  set(BOOTSTRAP_CMD "${VCVARS_CMD} & bootstrap.bat")
#  message("Executing command: ${BOOTSTRAP_CMD}")
#  execute_process(COMMAND cmd /c "${BOOTSTRAP_CMD}" WORKING_DIRECTORY ${APT_BOOST_SRC}
#                RESULT_VARIABLE BS_RESULT OUTPUT_VARIABLE BS_OUTPUT ERROR_VARIABLE BS_ERROR)
#  if(NOT EXISTS ${APT_BOOST_SRC}/b2.exe)
#    message(FATAL_ERROR "Failed running cmd /c ${BOOTSTRAP_CMD} in ${APT_BOOST_SRC}:\n${BS_OUTPUT}\n${BS_ERROR}\n")
#  else(NOT EXISTS ${APT_BOOST_SRC}/b2.exe)
#    message("bootstrap output:\n${BS_OUTPUT}")
#  endif(NOT EXISTS ${APT_BOOST_SRC}/b2.exe)
#else(WIN32)
#  set(BOOTSTRAP_CMD "./bootstrap.sh")
#  set(BOOTSTRAP_ARGS "--prefix=${APT_BOOST_BIN}")
#  message("Executing command: ${BOOTSTRAP_CMD} ${BOOTSTRAP_ARGS}")
#  execute_process(COMMAND "${BOOTSTRAP_CMD}" ${BOOTSTRAP_ARGS} WORKING_DIRECTORY ${APT_BOOST_SRC}
#                RESULT_VARIABLE BS_RESULT OUTPUT_VARIABLE BS_OUTPUT ERROR_VARIABLE BS_ERROR)
#  if(NOT BS_RESULT EQUAL 0)
#    message(FATAL_ERROR "Failed running ${BOOTSTRAP_CMD} ${BOOTSTRAP_ARGS} in ${APT_BOOST_SRC}:\n${BS_OUTPUT}\n${BS_ERROR}\n")
#  endif()
#endif(WIN32)
##
## run b2
##
#set(B2_ARGS "link=static" "threading=multi" "runtime-link=static" "variant=release")
#foreach(COMP IN LISTS APT_BOOST_COMPONENTS)
#  set(B2_ARGS "--with-${COMP}" ${B2_ARGS})
#endforeach(COMP IN LISTS APT_BOOST_COMPONENTS)
#if(WIN32)
#  if(MSVC11)
#    set(B2_ARGS "--toolset=msvc-11.0" ${B2_ARGS})
#  elseif(MSVC12)
#    set(B2_ARGS "--toolset=msvc-12.0" ${B2_ARGS})
#  endif(MSVC11)
#  file(TO_NATIVE_PATH ${APT_BOOST_BIN} APT_BOOST_BIN_WIN)
#  set(B2_ARGS "--prefix=${APT_BOOST_BIN_WIN}" ${B2_ARGS} "architecture=x86" "address-model=64")
#endif(WIN32)
#set(B2_ARGS ${B2_ARGS} install)
#set(B2_CMD "./b2")
#message("Executing command: ${B2_CMD} ${B2_ARGS}")
#execute_process(COMMAND ${B2_CMD} ${B2_ARGS} WORKING_DIRECTORY ${APT_BOOST_SRC}
#                RESULT_VARIABLE B2_RESULT OUTPUT_VARIABLE B2_OUTPUT ERROR_VARIABLE B2_ERROR)
#if(NOT B2_RESULT EQUAL 0)
#  message(FATAL_ERROR "Failed running ${B2_CMD} in ${APT_BOOST_SRC}:\n${B2_OUTPUT}\n${B2_ERROR}\n")
#endif()
