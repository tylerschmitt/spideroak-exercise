add_library(crypto SHARED
    crypto.hpp
    crypto.cpp
)

set(OPENSSL_ROOT_DIR /usr/local/opt/openssl/)

find_package(OpenSSL REQUIRED)
target_link_libraries(crypto PUBLIC OpenSSL::SSL)