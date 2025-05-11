echo Configuring .clangd
echo -ne "---\nCompileFlags:\n  Add: [-I"$(pwd)"/include]\n..." > .clangd
