set shell := ["bash", "-cu"]

format:
    @echo "Running clang-format..."
    @find include src tests tools examples -type f \
        \( -name '*.c' -o -name '*.h' \) -print0 \
        | xargs -0 clang-format-20 -i
