set -euo

case "$1" in
    start)
        meson build --cross cross_compiling_config.toml && (cd build && ninja)
        meson build-rel --cross cross_compiling_config.toml --buildtype release && (cd build && ninja)
        ;;
    clean)
        rm -rf build build-rel
        ;;
    *)
        echo "Invalid command."
esac
