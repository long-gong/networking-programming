set(target_name "printargs_v1")
add_executable(${target_name} printargs_v1.c)

set(target_name "printargs_v2")
add_executable(${target_name} printargs_v2.c)

set(target_name "printenv")
add_executable(${target_name} printenv.c)

set(target_name "clean_")
add_executable(${target_name} clean.c)

set(target_name "error_handler")
add_library(${target_name} STATIC error_handler.c)

set(target_name "simple_cat")
add_executable(${target_name} simple_cat.c)
target_link_libraries(${target_name} error_handler)

set(target_name "simple_cat_v2")
add_executable(${target_name} simple_cat_v2.c)
target_link_libraries(${target_name} error_handler)

set(target_name "signal_ops")
add_executable(${target_name} signal_ops.c)
target_link_libraries(${target_name} error_handler)

set(target_name "signal_ops_v2")
add_executable(${target_name} signal_ops_v2.c)
target_link_libraries(${target_name} error_handler)

set(target_name "fork_me")
add_executable(${target_name} fork_me.c)
target_link_libraries(${target_name} error_handler)